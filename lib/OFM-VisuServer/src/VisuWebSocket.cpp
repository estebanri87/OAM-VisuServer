#include "VisuWebSocket.h"
#include <esp_log.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

extern "C" void visuWS_onKoWrite(int fd, const uint8_t* data, size_t len);

static const char* TAG = "VisuWS";

// Singleton
VisuWebSocket openknxVisuWS;

// ---------------------------------------------------------------------------
// Helpers – forward declaration
// ---------------------------------------------------------------------------
// Token validation callback set by VisuServerModule
static bool (*s_isValidToken)(const char* token) = nullptr;

void visuWS_setTokenValidator(bool (*fn)(const char*)) {
    s_isValidToken = fn;
}

// ---------------------------------------------------------------------------
VisuWebSocket::VisuWebSocket() : _hd(nullptr) {
    for (int i = 0; i < VIS_MAX_WS_CLIENTS; i++) {
        _clients[i].fd             = -1;
        _clients[i].authenticated  = false;
        _clients[i].srcIp          = 0;
        _clients[i].lastPingMs     = 0;
    }
}

// ---------------------------------------------------------------------------
esp_err_t VisuWebSocket::registerUri(httpd_handle_t hd) {
    _hd = hd;
    httpd_uri_t wsUri = {
        .uri       = "/ws",
        .method    = HTTP_GET,
        .handler   = VisuWebSocket::wsUriHandler,
        .user_ctx  = this,
        .is_websocket = true,
    };
    httpd_uri_t wsVisuUri = {
        .uri       = "/visu/ws",
        .method    = HTTP_GET,
        .handler   = VisuWebSocket::wsUriHandler,
        .user_ctx  = this,
        .is_websocket = true,
    };

    esp_err_t err = httpd_register_uri_handler(hd, &wsUri);
    if (err != ESP_OK && err != ESP_ERR_HTTPD_HANDLER_EXISTS) {
        return err;
    }

    err = httpd_register_uri_handler(hd, &wsVisuUri);
    if (err != ESP_OK && err != ESP_ERR_HTTPD_HANDLER_EXISTS) {
        return err;
    }

    return ESP_OK;
}

// ---------------------------------------------------------------------------
bool VisuWebSocket::addClient(int fd, uint32_t srcIp) {
    for (int i = 0; i < VIS_MAX_WS_CLIENTS; i++) {
        if (_clients[i].fd == -1) {
            _clients[i].fd            = fd;
            _clients[i].authenticated = false;
            _clients[i].srcIp         = srcIp;
            _clients[i].lastPingMs    = (uint32_t)(esp_timer_get_time() / 1000);
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
void VisuWebSocket::removeClient(int fd) {
    for (int i = 0; i < VIS_MAX_WS_CLIENTS; i++) {
        if (_clients[i].fd == fd) {
            _clients[i].fd            = -1;
            _clients[i].authenticated = false;
            return;
        }
    }
}

// ---------------------------------------------------------------------------
bool VisuWebSocket::hasClients() const {
    for (int i = 0; i < VIS_MAX_WS_CLIENTS; i++) {
        if (_clients[i].fd != -1 && _clients[i].authenticated) return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
void VisuWebSocket::sendTofd(int fd, const uint8_t* data, size_t len) {
    if (_hd == nullptr || fd < 0) return;
    httpd_ws_frame_t frame = {};
    frame.type    = HTTPD_WS_TYPE_BINARY;
    frame.payload = const_cast<uint8_t*>(data);
    frame.len     = len;
    esp_err_t err = httpd_ws_send_frame_async(_hd, fd, &frame);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "send to fd=%d failed: %s", fd, esp_err_to_name(err));
        removeClient(fd);
    }
}

// ---------------------------------------------------------------------------
void VisuWebSocket::broadcastKoUpdate(uint16_t koIndex, const uint8_t* value, uint8_t size, uint8_t dptMajor) {
    if (!hasClients()) return;
    // Packet: [type:1][koIndex:2][dptMajor:1][size:1][data:size]
    uint8_t buf[5 + 4]; // max value size = 4 bytes
    buf[0] = WS_MSG_KO_UPDATE;
    buf[1] = (koIndex >> 8) & 0xFF;
    buf[2] = koIndex & 0xFF;
    buf[3] = dptMajor;
    buf[4] = size;
    uint8_t safeSize = (size > 4) ? 4 : size;
    memcpy(&buf[5], value, safeSize);
    size_t msgLen = 5 + safeSize;
    for (int i = 0; i < VIS_MAX_WS_CLIENTS; i++) {
        if (_clients[i].fd != -1 && _clients[i].authenticated) {
            sendTofd(_clients[i].fd, buf, msgLen);
        }
    }
}

// ---------------------------------------------------------------------------
void VisuWebSocket::sendFullState(int fd, uint16_t configVersion) {
    // Signal client to re-request /config + /state
    uint8_t buf[3];
    buf[0] = WS_MSG_FULL_STATE;
    buf[1] = (configVersion >> 8) & 0xFF;
    buf[2] = configVersion & 0xFF;
    sendTofd(fd, buf, 3);
}

// ---------------------------------------------------------------------------
void VisuWebSocket::broadcastConfigVer(uint16_t configVersion) {
    uint8_t buf[3];
    buf[0] = WS_MSG_CONFIG_VER;
    buf[1] = (configVersion >> 8) & 0xFF;
    buf[2] = configVersion & 0xFF;
    for (int i = 0; i < VIS_MAX_WS_CLIENTS; i++) {
        if (_clients[i].fd != -1 && _clients[i].authenticated) {
            sendTofd(_clients[i].fd, buf, 3);
        }
    }
}

// ---------------------------------------------------------------------------
void VisuWebSocket::broadcastHeartbeat() {
    uint8_t buf[1] = { WS_MSG_HEARTBEAT };
    for (int i = 0; i < VIS_MAX_WS_CLIENTS; i++) {
        if (_clients[i].fd != -1 && _clients[i].authenticated) {
            sendTofd(_clients[i].fd, buf, 1);
        }
    }
}

// ---------------------------------------------------------------------------
void VisuWebSocket::evictStale(uint32_t nowMs, uint8_t heartbeatSec) {
    uint32_t timeout = (uint32_t)heartbeatSec * 3 * 1000UL; // 3× heartbeat interval
    for (int i = 0; i < VIS_MAX_WS_CLIENTS; i++) {
        if (_clients[i].fd != -1) {
            if ((nowMs - _clients[i].lastPingMs) > timeout) {
                ESP_LOGI(TAG, "Evicting stale WS client fd=%d", _clients[i].fd);
                removeClient(_clients[i].fd);
            }
        }
    }
}

// ---------------------------------------------------------------------------
void VisuWebSocket::handleAuthFrame(int fd, const uint8_t* data, size_t len) {
    if (s_isValidToken == nullptr) return;
    if (len < 3) return; // too short to hold a token
    // Token is 32 hex chars starting at data[1]
    char tok[33] = {};
    uint8_t copyLen = (len - 1 > 32) ? 32 : (uint8_t)(len - 1);
    memcpy(tok, data + 1, copyLen);
    tok[32] = '\0';
    if (s_isValidToken(tok)) {
        for (int i = 0; i < VIS_MAX_WS_CLIENTS; i++) {
            if (_clients[i].fd == fd) {
                _clients[i].authenticated = true;
                _clients[i].lastPingMs    = (uint32_t)(esp_timer_get_time() / 1000);
                ESP_LOGI(TAG, "WS client fd=%d authenticated", fd);
                return;
            }
        }
    } else {
        // Auth failed: send AUTH_FAIL and let client disconnect
        uint8_t fail[1] = { WS_MSG_AUTH_FAIL };
        sendTofd(fd, fail, 1);
    }
}

// ---------------------------------------------------------------------------
// Static URI handler – dispatches to singleton instance stored in user_ctx
esp_err_t VisuWebSocket::wsUriHandler(httpd_req_t* req) {
    VisuWebSocket* self = static_cast<VisuWebSocket*>(req->user_ctx);
    if (req->method == HTTP_GET) {
        // New WebSocket handshake
        int fd = httpd_req_to_sockfd(req);
        // Extract client IP from sockaddr
        struct sockaddr_in6 addr;
        socklen_t addrLen = sizeof(addr);
        getpeername(fd, (struct sockaddr*)&addr, &addrLen);
        uint32_t srcIp = 0;
        // IPv4-mapped-in-IPv6 case: last 4 bytes
        if (addr.sin6_family == AF_INET6) {
            memcpy(&srcIp, &addr.sin6_addr.s6_addr[12], 4);
        }
        if (!self->addClient(fd, srcIp)) {
            ESP_LOGW(TAG, "WS client table full, rejecting fd=%d", fd);
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Too many clients");
            return ESP_OK;
        }
        ESP_LOGI(TAG, "WS client connected fd=%d", fd);
        return ESP_OK;
    }

    // Receive frame
    httpd_ws_frame_t frame = {};
    uint8_t buf[64] = {};
    frame.payload = buf;
    esp_err_t err = httpd_ws_recv_frame(req, &frame, sizeof(buf));
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "ws recv error: %s", esp_err_to_name(err));
        self->removeClient(httpd_req_to_sockfd(req));
        return err;
    }
    int fd = httpd_req_to_sockfd(req);

    if (frame.type == HTTPD_WS_TYPE_CLOSE) {
        self->removeClient(fd);
        return ESP_OK;
    }
    if (frame.type == HTTPD_WS_TYPE_PING) {
        // Update keepalive timestamp
        for (int i = 0; i < VIS_MAX_WS_CLIENTS; i++) {
            if (self->_clients[i].fd == fd) {
                self->_clients[i].lastPingMs = (uint32_t)(esp_timer_get_time() / 1000);
                break;
            }
        }
        // Send PONG
        httpd_ws_frame_t pong = { .type = HTTPD_WS_TYPE_PONG };
        httpd_ws_send_frame(req, &pong);
        return ESP_OK;
    }
    if (frame.type != HTTPD_WS_TYPE_BINARY || frame.len == 0) return ESP_OK;

    uint8_t msgType = buf[0];
    if (msgType == WS_MSG_AUTH_TOKEN) {
        self->handleAuthFrame(fd, buf, frame.len);
        return ESP_OK;
    }
    if (msgType == WS_MSG_HEARTBEAT) {
        for (int i = 0; i < VIS_MAX_WS_CLIENTS; i++) {
            if (self->_clients[i].fd == fd) {
                self->_clients[i].lastPingMs = (uint32_t)(esp_timer_get_time() / 1000);
                break;
            }
        }
        return ESP_OK;
    }
    // KO_WRITE handled by VisuServerModule via a callback
    visuWS_onKoWrite(fd, buf, frame.len);
    return ESP_OK;
}
