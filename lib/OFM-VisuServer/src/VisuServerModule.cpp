#include "VisuServerModule.h"
#include "WebUI.h"
#include <esp_log.h>
#include <esp_random.h>
#include <esp_timer.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Generated asset headers (produced by minimize.py from www/ directory)
#ifdef __has_include
  #if __has_include("../include/file_index_html.h")
    #include "../include/file_index_html.h"
    #define HAS_FILE_INDEX_HTML
  #endif
  #if __has_include("../include/file_app_js.h")
    #include "../include/file_app_js.h"
    #define HAS_FILE_APP_JS
  #endif
  #if __has_include("../include/file_style_css.h")
    #include "../include/file_style_css.h"
    #define HAS_FILE_STYLE_CSS
  #endif
  #if __has_include("../include/file_icons_svg.h")
    #include "../include/file_icons_svg.h"
    #define HAS_FILE_ICONS_SVG
  #endif
#endif

static const char* TAG = "VisuSrv";

// Singleton
VisuServerModule openknxVisuServerModule;

// ---------------------------------------------------------------------------
//  WebSocket callbacks (C-linkage, called from VisuWebSocket.cpp)
// ---------------------------------------------------------------------------
extern "C" void visuWS_onKoWrite(int fd, const uint8_t* data, size_t len) {
    openknxVisuServerModule.handleKoWrite(fd, data, len);
}

void visuWS_setTokenValidator(bool (*fn)(const char*));  // fwd from VisuWebSocket.cpp

static bool tokenValidatorShim(const char* tok) {
    return openknxVisuServerModule.isValidToken(tok);
}

// ---------------------------------------------------------------------------
VisuServerModule::VisuServerModule()
    : _roomCount(0), _floorCount(0), _favCount(0),
      _wsRegistered(false), _httpRegistered(false), _koReadsRequested(false),
      _lastHeartbeatMs(0), _lastKoReadRequestMs(0), _lastEvictMs(0),
      _koLookupCount(0)
{
    memset(&_cfg, 0, sizeof(_cfg));
    memset(_floors, 0, sizeof(_floors));
    memset(_rooms, 0, sizeof(_rooms));
    memset(_favorites, 0, sizeof(_favorites));
    memset(&_flashState, 0, sizeof(_flashState));
    memset(_tokens, 0, sizeof(_tokens));
    memset(_authAttempts, 0, sizeof(_authAttempts));
    memset(_koLookup, 0, sizeof(_koLookup));
    // Mark all token slots as invalid
    for (int i = 0; i < VIS_MAX_TOKENS; i++) _tokens[i].valid = false;
}

// ---------------------------------------------------------------------------
const std::string VisuServerModule::name() { return "VisuServer"; }

const std::string VisuServerModule::version() {
#ifdef MODULE_VisuServer_Version
    return MODULE_VisuServer_Version;
#else
    return "0.1.0";
#endif
}

// ---------------------------------------------------------------------------
void VisuServerModule::setup(bool firstCall) {
    if (!firstCall) return;

    ESP_LOGI(TAG, "setup: loading ETS params");
    loadEtsParams();
    buildKoLookup();

    // Set token validator on WebSocket singleton
    visuWS_setTokenValidator(tokenValidatorShim);

    // If flash state not yet loaded by readFlash, initialise defaults
    if (_flashState.magic != VIS_FLASH_MAGIC) {
        _flashState.magic         = VIS_FLASH_MAGIC;
        _flashState.configVersion = 1;
    }

    ESP_LOGI(TAG, "setup done: %d rooms, %d floors, configVersion=%d",
             _roomCount, _floorCount, _flashState.configVersion);

    // Register Visu as dedicated web service route.
    // Using /visu avoids conflicts with modules that also use '/'.
    WebHandler visuEntry;
    visuEntry.httpd     = { .uri = "/visu", .method = HTTP_GET, .handler = handleGetIndex, .user_ctx = this };
    visuEntry.uri       = "/visu";
    visuEntry.name      = "Visualisierung";
    visuEntry.isVisible = true;
    openknxWebUI.addHandler(visuEntry);
}

// ---------------------------------------------------------------------------
void VisuServerModule::loop(bool firstCall) {
    uint32_t nowMs = (uint32_t)(esp_timer_get_time() / 1000ULL);

    // Register HTTP/WS handlers once, after the WebUI server has started.
    // openknxWebUI.getHandler() returns non-null only after server start.
    if (!_httpRegistered) {
        httpd_handle_t hd = openknxWebUI.getHandler();
        if (hd != nullptr) {
            registerHttpHandlers();
            openknxVisuWS.registerUri(hd);
            _httpRegistered  = true;
            _wsRegistered    = true;
            ESP_LOGI(TAG, "HTTP+WS handlers registered");
        }
    }

    // One-time: request all KO values from bus after startup delay
    if (_httpRegistered && !_koReadsRequested) {
        requestAllKoReads();
        _koReadsRequested = true;
        _lastKoReadRequestMs = nowMs;
    }

    // Heartbeat broadcast
    if (_httpRegistered && _cfg.heartbeatSec > 0) {
        if ((nowMs - _lastHeartbeatMs) >= (uint32_t)_cfg.heartbeatSec * 1000UL) {
            openknxVisuWS.broadcastHeartbeat();
            _lastHeartbeatMs = nowMs;
        }
    }

    // Evict stale WS clients every 10 s
    if ((nowMs - _lastEvictMs) >= 10000UL) {
        openknxVisuWS.evictStale(nowMs, _cfg.heartbeatSec ? _cfg.heartbeatSec : 30);
        expireSessions(nowMs);
        _lastEvictMs = nowMs;
    }
}

// ---------------------------------------------------------------------------
void VisuServerModule::processInputKo(GroupObject& ko) {
    uint16_t koIdx = ko.asap();
    const KoLookup* lk = lookupKo(koIdx);
    if (lk == nullptr) return;

    VisuWidget& w = _rooms[lk->room].widgets[lk->widget];
    VisuKoEntry& entry = w.kos[lk->pos];

    uint8_t size = ko.valueSize();
    if (size > 4) size = 4;
    memcpy(entry.value, ko.valueRef(), size);
    entry.valid = true;

    // Broadcast to WebSocket clients
    openknxVisuWS.broadcastKoUpdate(koIdx, entry.value, size, entry.dptMajor);
}

// ---------------------------------------------------------------------------
//  ETS parameter loading
// ---------------------------------------------------------------------------
void VisuServerModule::loadEtsParams() {
    // Global parameters
    memcpy(_cfg.deviceName, knx.paramData(VIS_DeviceName), 20);
    _cfg.deviceName[20] = '\0';

    uint8_t flags1         = knx.paramByte(VIS_Flags1);
    _cfg.authEnabled       = (flags1 & VIS_AuthEnabledMask) != 0;
    _cfg.dashboardEnabled  = (flags1 & VIS_DashboardEnabledMask) != 0;
    _cfg.theme             = (flags1 & VIS_ThemeMask) >> VIS_ThemeShift;
    _cfg.screensaverMode   = (flags1 & VIS_SaverModeMask) >> VIS_SaverModeShift;

    // AuthPIN as 4-byte big-endian value
    const uint8_t* pinBytes = knx.paramData(VIS_AuthPIN);
    _cfg.authPin = ((uint32_t)pinBytes[0] << 24) | ((uint32_t)pinBytes[1] << 16)
                 | ((uint32_t)pinBytes[2] <<  8) |  (uint32_t)pinBytes[3];

    _cfg.authMaxAttempts = knx.paramByte(VIS_AuthMaxAttempts);
    _cfg.authLockoutMin  = knx.paramByte(VIS_AuthLockoutMin);
    _cfg.heartbeatSec    = knx.paramByte(VIS_HeartbeatSec);
    _cfg.visibleFloors   = knx.paramByte(VIS_VisibleFloors);
    _cfg.visibleRooms    = knx.paramByte(VIS_VisibleRooms);
    _cfg.screensaverMin  = knx.paramByte(VIS_ScreensaverMin);

    if (_cfg.heartbeatSec == 0)   _cfg.heartbeatSec   = 30;
    if (_cfg.visibleFloors == 0)  _cfg.visibleFloors   = 1;
    if (_cfg.visibleRooms == 0)   _cfg.visibleRooms    = 1;
    if (_cfg.visibleRooms > VIS_MAX_ROOMS) _cfg.visibleRooms = VIS_MAX_ROOMS;
    if (_cfg.authMaxAttempts == 0) _cfg.authMaxAttempts = 5;
    if (_cfg.authLockoutMin == 0)  _cfg.authLockoutMin  = 10;

    // Floor parameters
    _floorCount = 0;
    for (uint8_t f = 0; f < VIS_MAX_FLOORS; f++) {
        if (f >= _cfg.visibleFloors) break;
        memcpy(_floors[f].name, knx.paramData(VIS_FLxName(f)), 20);
        _floors[f].name[20] = '\0';
        _floors[f].order    = knx.paramByte(VIS_FLxOrder(f));
        _floorCount++;
    }

    // Favorite parameters
    _favCount = 0;
    for (uint8_t fav = 0; fav < VIS_MAX_FAVORITES; fav++) {
        uint8_t r = knx.paramByte(VIS_FAVxRoom(fav));
        uint8_t w = knx.paramByte(VIS_FAVxWidget(fav));
        if (r == 0xFF || r >= VIS_MAX_ROOMS) continue;
        _favorites[fav].roomIdx   = r;
        _favorites[fav].widgetIdx = w;
        _favorites[fav].valid     = true;
        _favCount++;
    }

    // Room channels (limited by visibleRooms setting)
    _roomCount = 0;
    for (uint8_t r = 0; r < _cfg.visibleRooms; r++) {
        memcpy(_rooms[r].name, knx.paramData(VIS_RxName(r)), 20);
        _rooms[r].name[20] = '\0';
        // Skip room if name is empty or starts with null
        if (_rooms[r].name[0] == '\0') continue;
        _rooms[r].icon     = knx.paramByte(VIS_RxIcon(r));
        _rooms[r].floorIdx = knx.paramByte(VIS_RxFloor(r));
        _rooms[r].order    = knx.paramByte(VIS_RxOrder(r));
        uint8_t numW       = knx.paramByte(VIS_RxVisibleWidgets(r));
        if (numW > VIS_MAX_WIDGETS) numW = VIS_MAX_WIDGETS;
        _rooms[r].widgetCount = numW;

        for (uint8_t w = 0; w < numW; w++) {
            VisuWidget& wz = _rooms[r].widgets[w];
            wz.type  = (VisuWidgetType)knx.paramByte(VIS_WzType(r, w));
            if (wz.type == VWT_EMPTY) continue;

            memcpy(wz.name, knx.paramData(VIS_WzName(r, w)), 20);
            wz.name[20] = '\0';
            wz.icon     = knx.paramByte(VIS_WzIcon(r, w));
            wz.tileSize = knx.paramByte(VIS_WzTileSize(r, w));
            wz.sortOrder= knx.paramByte(VIS_WzSortOrder(r, w));
            wz.w        = knx.paramByte(VIS_WzWidth(r, w));
            wz.h        = knx.paramByte(VIS_WzHeight(r, w));
            wz.trade    = (VisuTrade)   knx.paramByte(VIS_WzTrade(r, w));
            wz.dpt      = (VisuDptSel)  knx.paramByte(VIS_WzDpt(r, w));

            if (wz.type == VWT_CAMERA) {
                memcpy(wz.cameraUrl, knx.paramData(VIS_WzCamUrl(r, w)), 15);
                wz.cameraUrl[15] = '\0';
                wz.koCount = 0;
                continue;
            }

            wz.koCount = visKoCount(wz.type);
            for (uint8_t p = 0; p < wz.koCount; p++) {
                wz.kos[p].koIndex   = VIS_KO(r, w, p);
                wz.kos[p].role      = (uint8_t)visKoRole(wz.type, p);
                // Extract DPT major from DPT string (first component before '.')
                const char* dptStr  = visKoDptStr(wz.type, wz.dpt, p);
                wz.kos[p].dptMajor  = (uint8_t)atoi(dptStr);
                wz.kos[p].valid     = false;
                memset(wz.kos[p].value, 0, 4);
            }
        }
        _roomCount++;
    }
    ESP_LOGI(TAG, "loadEtsParams: %d rooms, %d floors, %d favorites",
             _roomCount, _floorCount, _favCount);
}

// ---------------------------------------------------------------------------
void VisuServerModule::buildKoLookup() {
    _koLookupCount = 0;
    memset(_koLookup, 0, sizeof(_koLookup));
    for (uint8_t r = 0; r < VIS_MAX_ROOMS; r++) {
        for (uint8_t w = 0; w < _rooms[r].widgetCount; w++) {
            VisuWidget& wz = _rooms[r].widgets[w];
            for (uint8_t p = 0; p < wz.koCount; p++) {
                uint16_t koIdx = wz.kos[p].koIndex;
                // Store in flat map by position (KO - VIS_KoBase)
                uint16_t slot = koIdx - VIS_KoBase;
                if (slot < (VIS_MAX_ROOMS * VIS_MAX_WIDGETS * VIS_KO_BLOCK_SIZE)) {
                    _koLookup[slot].room   = r;
                    _koLookup[slot].widget = w;
                    _koLookup[slot].pos    = p;
                    _koLookup[slot].valid  = true;
                    _koLookupCount++;
                }
            }
        }
    }
}

const VisuServerModule::KoLookup* VisuServerModule::lookupKo(uint16_t koIndex) const {
    if (koIndex < VIS_KoBase) return nullptr;
    uint16_t slot = koIndex - VIS_KoBase;
    if (slot >= (VIS_MAX_ROOMS * VIS_MAX_WIDGETS * VIS_KO_BLOCK_SIZE)) return nullptr;
    if (!_koLookup[slot].valid) return nullptr;
    return &_koLookup[slot];
}

// ---------------------------------------------------------------------------
void VisuServerModule::requestAllKoReads() {
    for (uint8_t r = 0; r < VIS_MAX_ROOMS; r++) {
        for (uint8_t w = 0; w < _rooms[r].widgetCount; w++) {
            VisuWidget& wz = _rooms[r].widgets[w];
            for (uint8_t p = 0; p < wz.koCount; p++) {
                if (wz.kos[p].role == VKR_STATUS || wz.kos[p].role == VKR_BIDIR) {
                    knx.getGroupObject(wz.kos[p].koIndex).requestObjectRead();
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
//  Token / Auth
// ---------------------------------------------------------------------------
void VisuServerModule::generateToken(char* outToken32) {
    uint8_t raw[16];
    esp_fill_random(raw, 16);
    for (int i = 0; i < 16; i++) {
        snprintf(outToken32 + i * 2, 3, "%02x", raw[i]);
    }
    outToken32[32] = '\0';
}

bool VisuServerModule::addSession(const char* token, uint32_t srcIp) {
    uint32_t nowMs = (uint32_t)(esp_timer_get_time() / 1000ULL);
    // Session lifetime: 8 hours
    uint32_t expiresMs = nowMs + 8UL * 3600UL * 1000UL;
    for (int i = 0; i < VIS_MAX_TOKENS; i++) {
        if (!_tokens[i].valid) {
            strncpy(_tokens[i].token, token, 32);
            _tokens[i].token[32] = '\0';
            _tokens[i].expiresMs = expiresMs;
            _tokens[i].srcIp     = srcIp;
            _tokens[i].valid     = true;
            return true;
        }
    }
    return false; // table full
}

void VisuServerModule::expireSessions(uint32_t nowMs) {
    for (int i = 0; i < VIS_MAX_TOKENS; i++) {
        if (_tokens[i].valid && (int32_t)(nowMs - _tokens[i].expiresMs) > 0) {
            _tokens[i].valid = false;
        }
    }
}

bool VisuServerModule::isValidToken(const char* token) {
    if (!_cfg.authEnabled) return true;
    if (token == nullptr || token[0] == '\0') return false;
    uint32_t nowMs = (uint32_t)(esp_timer_get_time() / 1000ULL);
    for (int i = 0; i < VIS_MAX_TOKENS; i++) {
        if (_tokens[i].valid &&
            (int32_t)(nowMs - _tokens[i].expiresMs) <= 0 &&
            strncmp(_tokens[i].token, token, 32) == 0) {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
//  Flash state
// ---------------------------------------------------------------------------
void VisuServerModule::writeFlash() {
    openknx.flash.write((uint8_t*)&_flashState, sizeof(VisuFlashState));
}

void VisuServerModule::readFlash(const uint8_t* data, const uint16_t size) {
    if (size >= sizeof(VisuFlashState)) {
        memcpy(&_flashState, data, sizeof(VisuFlashState));
        if (_flashState.magic != VIS_FLASH_MAGIC) {
            _flashState.magic         = VIS_FLASH_MAGIC;
            _flashState.configVersion = 1;
        }
    }
}

void VisuServerModule::bumpConfigVersion() {
    _flashState.configVersion++;
    if (_flashState.configVersion == 0) _flashState.configVersion = 1;
    openknxVisuWS.broadcastConfigVer(_flashState.configVersion);
    openknx.flash.save();
}

// ---------------------------------------------------------------------------
//  Helpers
// ---------------------------------------------------------------------------
VisuRoom* VisuServerModule::findRoom(uint8_t roomIdx) {
    if (roomIdx >= VIS_MAX_ROOMS) return nullptr;
    return &_rooms[roomIdx];
}

VisuWidget* VisuServerModule::findWidget(uint8_t roomIdx, uint8_t widgetIdx) {
    VisuRoom* ro = findRoom(roomIdx);
    if (!ro) return nullptr;
    if (widgetIdx >= ro->widgetCount) return nullptr;
    return &ro->widgets[widgetIdx];
}

// ---------------------------------------------------------------------------
//  KO write from WebSocket client
// ---------------------------------------------------------------------------
void VisuServerModule::handleKoWrite(int fd, const uint8_t* data, size_t len) {
    // Packet format: [0x02][koIdxHi][koIdxLo][dptSize][data...]
    if (len < 5) return;
    if (data[0] != WS_MSG_KO_WRITE) return;

    uint16_t koIdx = ((uint16_t)data[1] << 8) | data[2];
    uint8_t  size  = data[3];
    if (size > 4) size = 4;
    if ((size_t)(4 + size) > len) return;

    const KoLookup* lk = lookupKo(koIdx);
    if (lk == nullptr) {
        ESP_LOGW(TAG, "KoWrite: unknown koIdx=%d", koIdx);
        return;
    }
    VisuWidget& wz = _rooms[lk->room].widgets[lk->widget];
    VisuKoEntry& entry = wz.kos[lk->pos];
    if (entry.role == VKR_STATUS) {
        ESP_LOGW(TAG, "KoWrite: KO %d is read-only", koIdx);
        return;
    }

    // Write to GroupObject (sends on bus)
    GroupObject& go = knx.getGroupObject(koIdx);
    uint8_t raw[4] = {};
    memcpy(raw, &data[4], size);

    switch (entry.dptMajor) {
        case 1: {
            KNXValue kv((bool)(raw[0] & 0x01));
            go.value(kv, DPT_Bool);
            break;
        }
        case 5: {
            KNXValue kv((uint8_t)raw[0]);
            go.value(kv, DPT_Scaling);
            break;
        }
        default:
            // Raw bytes: copy to valueRef and trigger send
            memcpy(go.valueRef(), raw, size);
            go.objectWritten();
            break;
    }

    // Update cache and broadcast
    memcpy(entry.value, raw, size);
    entry.valid = true;
    openknxVisuWS.broadcastKoUpdate(koIdx, entry.value, size, entry.dptMajor);
}

// ---------------------------------------------------------------------------
//  HTTP handler registration
// ---------------------------------------------------------------------------
void VisuServerModule::registerHttpHandlers() {
    httpd_handle_t hd = openknxWebUI.getHandler();
    if (!hd) return;

    httpd_uri_t uris[] = {
        { .uri="/",         .method=HTTP_GET,  .handler=handleGetRootRedirect, .user_ctx=this },
        { .uri="/visu",     .method=HTTP_GET,  .handler=handleGetIndex,    .user_ctx=this },
        { .uri="/visu/",    .method=HTTP_GET,  .handler=handleGetIndex,    .user_ctx=this },
        { .uri="/visu/config",    .method=HTTP_GET,  .handler=handleGetConfig,   .user_ctx=this },
        { .uri="/visu/state",     .method=HTTP_GET,  .handler=handleGetState,    .user_ctx=this },
        { .uri="/visu/auth",      .method=HTTP_POST, .handler=handlePostAuth,    .user_ctx=this },
        { .uri="/visu/ko",        .method=HTTP_POST, .handler=handlePostKo,      .user_ctx=this },
        { .uri="/visu/app.js",    .method=HTTP_GET,  .handler=handleGetAppJs,    .user_ctx=this },
        { .uri="/visu/style.css", .method=HTTP_GET,  .handler=handleGetStyleCss, .user_ctx=this },
        { .uri="/visu/icons.svg", .method=HTTP_GET,  .handler=handleGetIconsSvg, .user_ctx=this },
    };
    for (auto& u : uris) {
        esp_err_t err = httpd_register_uri_handler(hd, &u);
        if (err == ESP_ERR_HTTPD_HANDLER_EXISTS) {
            ESP_LOGI(TAG, "URI already registered: %s", u.uri);
            continue;
        }
        if (err != ESP_OK) {
            ESP_LOGW(TAG, "Failed to register %s: %s", u.uri, esp_err_to_name(err));
        }
    }
}

esp_err_t VisuServerModule::handleGetRootRedirect(httpd_req_t* req) {
    httpd_resp_set_status(req, "302 Found");
    httpd_resp_set_hdr(req, "Location", "/visu");
    httpd_resp_send(req, nullptr, 0);
    return ESP_OK;
}

// ---------------------------------------------------------------------------
//  Auth guard helper
// ---------------------------------------------------------------------------
bool VisuServerModule::checkAuth(httpd_req_t* req) {
    VisuServerModule* self = static_cast<VisuServerModule*>(req->user_ctx);
    if (!self->_cfg.authEnabled) return true;
    // Extract Bearer token from Authorization header
    char authHdr[64] = {};
    if (httpd_req_get_hdr_value_str(req, "Authorization", authHdr, sizeof(authHdr)) != ESP_OK) {
        httpd_resp_set_status(req, "401 Unauthorized");
        httpd_resp_set_hdr(req, "WWW-Authenticate", "Bearer realm=\"VisuServer\"");
        httpd_resp_send(req, "", 0);
        return false;
    }
    // Expect "Bearer <token>"
    const char* token = nullptr;
    if (strncmp(authHdr, "Bearer ", 7) == 0) token = authHdr + 7;
    if (!token || !self->isValidToken(token)) {
        httpd_resp_set_status(req, "401 Unauthorized");
        httpd_resp_set_hdr(req, "WWW-Authenticate", "Bearer realm=\"VisuServer\"");
        httpd_resp_send(req, "", 0);
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------------
//  GET /  → index.html (gzipped)
// ---------------------------------------------------------------------------
esp_err_t VisuServerModule::handleGetIndex(httpd_req_t* req) {
    httpd_resp_set_type(req, "text/html");
#ifdef HAS_FILE_INDEX_HTML
    httpd_resp_set_hdr(req, "Content-Encoding", "gzip");
    httpd_resp_send(req, (const char*)file_index_html, sizeof(file_index_html));
#else
    httpd_resp_send(req, "<html><body><h1>VisuServer</h1><p>Frontend not built yet.</p></body></html>", -1);
#endif
    return ESP_OK;
}

// ---------------------------------------------------------------------------
//  GET /app.js
// ---------------------------------------------------------------------------
esp_err_t VisuServerModule::handleGetAppJs(httpd_req_t* req) {
    httpd_resp_set_type(req, "application/javascript");
#ifdef HAS_FILE_APP_JS
    httpd_resp_set_hdr(req, "Content-Encoding", "gzip");
    httpd_resp_send(req, (const char*)file_app_js, sizeof(file_app_js));
#else
    httpd_resp_send(req, "// app.js not built", -1);
#endif
    return ESP_OK;
}

// ---------------------------------------------------------------------------
//  GET /style.css
// ---------------------------------------------------------------------------
esp_err_t VisuServerModule::handleGetStyleCss(httpd_req_t* req) {
    httpd_resp_set_type(req, "text/css");
#ifdef HAS_FILE_STYLE_CSS
    httpd_resp_set_hdr(req, "Content-Encoding", "gzip");
    httpd_resp_send(req, (const char*)file_style_css, sizeof(file_style_css));
#else
    httpd_resp_send(req, "/* style.css not built */", -1);
#endif
    return ESP_OK;
}

// ---------------------------------------------------------------------------
//  GET /icons.svg
// ---------------------------------------------------------------------------
esp_err_t VisuServerModule::handleGetIconsSvg(httpd_req_t* req) {
    httpd_resp_set_type(req, "image/svg+xml");
#ifdef HAS_FILE_ICONS_SVG
    httpd_resp_set_hdr(req, "Content-Encoding", "gzip");
    httpd_resp_send(req, (const char*)file_icons_svg, sizeof(file_icons_svg));
#else
    httpd_resp_send(req, "<svg xmlns='http://www.w3.org/2000/svg'/>", -1);
#endif
    return ESP_OK;
}

// ---------------------------------------------------------------------------
//  POST /auth  body: {"pin": "1234"}   response: {"token": "...", "expires": ms}
// ---------------------------------------------------------------------------
esp_err_t VisuServerModule::handlePostAuth(httpd_req_t* req) {
    VisuServerModule* self = static_cast<VisuServerModule*>(req->user_ctx);

    // Read body (max 32 bytes for PIN JSON)
    char body[48] = {};
    int received  = httpd_req_recv(req, body, sizeof(body) - 1);
    if (received <= 0) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Empty body");
        return ESP_OK;
    }
    body[received] = '\0';

    // Simple JSON parse for {"pin":"XXXX"} — no full JSON library needed
    // Find "pin":"  value
    const char* pinStart = strstr(body, "\"pin\"");
    if (!pinStart) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Missing pin field");
        return ESP_OK;
    }
    const char* colon = strchr(pinStart + 5, ':');
    if (!colon) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Parse error");
        return ESP_OK;
    }
    // Skip whitespace and quote
    const char* p = colon + 1;
    while (*p == ' ' || *p == '\t') p++;
    if (*p == '"') p++;
    char pinStr[16] = {};
    int pi = 0;
    while (*p && *p != '"' && *p != '}' && pi < 10) pinStr[pi++] = *p++;
    pinStr[pi] = '\0';
    uint32_t pinValue = (uint32_t)strtoul(pinStr, nullptr, 10);

    // Get client IP
    int fd = httpd_req_to_sockfd(req);
    struct sockaddr_in6 addr;
    socklen_t addrLen = sizeof(addr);
    getpeername(fd, (struct sockaddr*)&addr, &addrLen);
    uint32_t srcIp = 0;
    if (addr.sin6_family == AF_INET6) memcpy(&srcIp, &addr.sin6_addr.s6_addr[12], 4);

    // Brute-force check
    uint32_t nowMs = (uint32_t)(esp_timer_get_time() / 1000ULL);
    for (int i = 0; i < VIS_MAX_AUTH_IPS; i++) {
        if (self->_authAttempts[i].srcIp == srcIp) {
            if (self->_authAttempts[i].failCount >= self->_cfg.authMaxAttempts) {
                if ((int32_t)(nowMs - self->_authAttempts[i].lockedUntilMs) < 0) {
                    httpd_resp_set_status(req, "429 Too Many Requests");
                    httpd_resp_send(req, "{\"error\":\"locked\"}", -1);
                    return ESP_OK;
                }
                // Lockout expired
                self->_authAttempts[i].failCount = 0;
            }
            break;
        }
    }

    if (!self->_cfg.authEnabled || pinValue == self->_cfg.authPin) {
        // Generate token
        char tok[33];
        self->generateToken(tok);
        if (!self->addSession(tok, srcIp)) {
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Too many sessions");
            return ESP_OK;
        }
        // Clear fail count for this IP
        for (int i = 0; i < VIS_MAX_AUTH_IPS; i++) {
            if (self->_authAttempts[i].srcIp == srcIp) {
                self->_authAttempts[i].failCount = 0;
                break;
            }
        }
        char resp[80];
        snprintf(resp, sizeof(resp), "{\"token\":\"%s\",\"expires\":28800000}", tok);
        httpd_resp_set_type(req, "application/json");
        httpd_resp_send(req, resp, -1);
    } else {
        // Record failed attempt
        bool found = false;
        int freeSlot = -1;
        for (int i = 0; i < VIS_MAX_AUTH_IPS; i++) {
            if (self->_authAttempts[i].srcIp == srcIp) {
                self->_authAttempts[i].failCount++;
                if (self->_authAttempts[i].failCount >= self->_cfg.authMaxAttempts) {
                    self->_authAttempts[i].lockedUntilMs =
                        nowMs + (uint32_t)self->_cfg.authLockoutMin * 60000UL;
                }
                found = true;
                break;
            }
            if (freeSlot < 0 && self->_authAttempts[i].srcIp == 0) freeSlot = i;
        }
        if (!found && freeSlot >= 0) {
            self->_authAttempts[freeSlot].srcIp     = srcIp;
            self->_authAttempts[freeSlot].failCount  = 1;
            self->_authAttempts[freeSlot].lockedUntilMs = 0;
        }
        httpd_resp_set_status(req, "401 Unauthorized");
        httpd_resp_set_type(req, "application/json");
        httpd_resp_send(req, "{\"error\":\"bad_pin\"}", -1);
    }
    return ESP_OK;
}

// ---------------------------------------------------------------------------
//  GET /config  — full floor/room/widget configuration (JSON, chunked)
// ---------------------------------------------------------------------------
void VisuServerModule::writeConfigJson(httpd_req_t* req) {
    httpd_resp_set_type(req, "application/json");
    // Build JSON incrementally using fixed-size chunks to avoid large heap alloc
    char buf[VIS_CONFIG_CHUNK_SIZE + 64];
    int  pos = 0;

    auto flush = [&]() {
        if (pos > 0) {
            httpd_resp_send_chunk(req, buf, pos);
            pos = 0;
        }
    };
    auto emit = [&](const char* s) {
        int len = strlen(s);
        if (pos + len >= (int)sizeof(buf)) flush();
        memcpy(buf + pos, s, len);
        pos += len;
    };
    auto emitChar = [&](char c) {
        if (pos + 1 >= (int)sizeof(buf)) flush();
        buf[pos++] = c;
    };
    auto emitJsonStr = [&](const char* s) {
        emitChar('"');
        for (const uint8_t* p = (const uint8_t*)s; *p; p++) {
            uint8_t c = *p;
            if (c == '"' || c == '\\') { emitChar('\\'); emitChar((char)c); }
            else if (c < 0x80) { emitChar((char)c); }
            else {
                // Latin-1 byte → UTF-8 two-byte sequence
                emitChar((char)(0xC0 | (c >> 6)));
                emitChar((char)(0x80 | (c & 0x3F)));
            }
        }
        emitChar('"');
    };

    char tmp[32];
    emit("{\"v\":");
    snprintf(tmp, sizeof(tmp), "%d", VIS_API_VERSION);
    emit(tmp);
    emit(",\"cfgVer\":");
    snprintf(tmp, sizeof(tmp), "%d", configVersion());
    emit(tmp);
    emit(",\"device\":");
    emitJsonStr(_cfg.deviceName);
    emit(",\"theme\":");
    snprintf(tmp, sizeof(tmp), "%d", _cfg.theme);
    emit(tmp);
    emit(",\"saver\":{\"mode\":");
    snprintf(tmp, sizeof(tmp), "%d", _cfg.screensaverMode);
    emit(tmp);
    emit(",\"minutes\":");
    snprintf(tmp, sizeof(tmp), "%d", _cfg.screensaverMin);
    emit(tmp);
    emit("},\"auth\":");
    emit(_cfg.authEnabled ? "true" : "false");

    // Floors array
    emit(",\"floors\":[");
    for (uint8_t f = 0; f < _floorCount; f++) {
        if (f > 0) emitChar(',');
        emit("{\"id\":");
        snprintf(tmp, sizeof(tmp), "%d", f);
        emit(tmp);
        emit(",\"name\":");
        emitJsonStr(_floors[f].name);
        emit(",\"order\":");
        snprintf(tmp, sizeof(tmp), "%d", _floors[f].order);
        emit(tmp);
        emitChar('}');
    }
    emit("],\"rooms\":[");

    bool firstRoom = true;
    for (uint8_t r = 0; r < VIS_MAX_ROOMS; r++) {
        if (_rooms[r].name[0] == '\0') continue;
        if (!firstRoom) emitChar(',');
        firstRoom = false;
        emit("{\"id\":");
        snprintf(tmp, sizeof(tmp), "%d", r);
        emit(tmp);
        emit(",\"name\":");
        emitJsonStr(_rooms[r].name);
        emit(",\"icon\":");
        emitJsonStr(visRoomIconName(_rooms[r].icon));
        emit(",\"floor\":");
        snprintf(tmp, sizeof(tmp), "%d", _rooms[r].floorIdx);
        emit(tmp);
        emit(",\"order\":");
        snprintf(tmp, sizeof(tmp), "%d", _rooms[r].order);
        emit(tmp);
        emit(",\"widgets\":[");
        for (uint8_t w = 0; w < _rooms[r].widgetCount; w++) {
            VisuWidget& wz = _rooms[r].widgets[w];
            if (w > 0) emitChar(',');
            emit("{\"id\":");
            snprintf(tmp, sizeof(tmp), "%d", w);
            emit(tmp);
            emit(",\"type\":");
            emitJsonStr(visWidgetTypeStr(wz.type));
            emit(",\"name\":");
            emitJsonStr(wz.name);
            emit(",\"icon\":");
            snprintf(tmp, sizeof(tmp), "%d", wz.icon);
            emit(tmp);
            emit(",\"ts\":");
            snprintf(tmp, sizeof(tmp), "%d", wz.tileSize);
            emit(tmp);
            emit(",\"so\":");
            snprintf(tmp, sizeof(tmp), "%d", wz.sortOrder);
            emit(tmp);
            emit(",\"w\":");
            snprintf(tmp, sizeof(tmp), "%d", wz.w);
            emit(tmp);
            emit(",\"h\":");
            snprintf(tmp, sizeof(tmp), "%d", wz.h);
            emit(tmp);
            emit(",\"trade\":");
            emitJsonStr(visTradeId(wz.trade));
            if (wz.type == VWT_VALUE || wz.type == VWT_BUTTON) {
                emit(",\"dpt\":");
                emitJsonStr(visDptStr(wz.dpt));
            }
            if (wz.type == VWT_CAMERA) {
                emit(",\"url\":");
                emitJsonStr(wz.cameraUrl);
            }
            emit(",\"kos\":[");
            for (uint8_t p = 0; p < wz.koCount; p++) {
                if (p > 0) emitChar(',');
                emit("{\"ko\":");
                snprintf(tmp, sizeof(tmp), "%d", wz.kos[p].koIndex);
                emit(tmp);
                emit(",\"role\":");
                snprintf(tmp, sizeof(tmp), "%d", wz.kos[p].role);
                emit(tmp);
                emit(",\"dpt\":");
                snprintf(tmp, sizeof(tmp), "%d", wz.kos[p].dptMajor);
                emit(tmp);
                emitChar('}');
            }
            emit("]}");
        }
        emit("]}");
    }
    emit("],\"favorites\":[");
    bool firstFav = true;
    for (uint8_t fav = 0; fav < VIS_MAX_FAVORITES; fav++) {
        if (!_favorites[fav].valid) continue;
        if (!firstFav) emitChar(',');
        firstFav = false;
        emit("{\"room\":");
        snprintf(tmp, sizeof(tmp), "%d", _favorites[fav].roomIdx);
        emit(tmp);
        emit(",\"widget\":");
        snprintf(tmp, sizeof(tmp), "%d", _favorites[fav].widgetIdx);
        emit(tmp);
        emitChar('}');
    }
    emit("]}");
    flush();
    httpd_resp_send_chunk(req, nullptr, 0); // end chunked transfer
}

esp_err_t VisuServerModule::handleGetConfig(httpd_req_t* req) {
    if (!checkAuth(req)) return ESP_OK;
    VisuServerModule* self = static_cast<VisuServerModule*>(req->user_ctx);
    self->writeConfigJson(req);
    return ESP_OK;
}

// ---------------------------------------------------------------------------
//  GET /state  — current KO value cache (JSON)
// ---------------------------------------------------------------------------
void VisuServerModule::writeStateJson(httpd_req_t* req) {
    httpd_resp_set_type(req, "application/json");
    char buf[VIS_CONFIG_CHUNK_SIZE + 64];
    int  pos = 0;

    auto flush = [&]() {
        if (pos > 0) { httpd_resp_send_chunk(req, buf, pos); pos = 0; }
    };
    auto emit = [&](const char* s) {
        int len = strlen(s);
        if (pos + len >= (int)sizeof(buf)) flush();
        memcpy(buf + pos, s, len); pos += len;
    };
    auto emitChar = [&](char c) {
        if (pos + 1 >= (int)sizeof(buf)) flush();
        buf[pos++] = c;
    };

    char tmp[32];
    emit("{\"cfgVer\":");
    snprintf(tmp, sizeof(tmp), "%d", configVersion());
    emit(tmp);
    emit(",\"kos\":{");

    bool first = true;
    for (uint8_t r = 0; r < VIS_MAX_ROOMS; r++) {
        for (uint8_t w = 0; w < _rooms[r].widgetCount; w++) {
            VisuWidget& wz = _rooms[r].widgets[w];
            for (uint8_t p = 0; p < wz.koCount; p++) {
                if (!wz.kos[p].valid) continue;
                if (!first) emitChar(',');
                first = false;
                snprintf(tmp, sizeof(tmp), "\"%d\":", wz.kos[p].koIndex);
                emit(tmp);
                // Encode value as hex string for unambiguous JSON transport
                emitChar('"');
                for (uint8_t b = 0; b < visDptSize(wz.dpt) && b < 4; b++) {
                    snprintf(tmp, sizeof(tmp), "%02x", wz.kos[p].value[b]);
                    emit(tmp);
                }
                emitChar('"');
            }
        }
    }
    emit("}}");
    flush();
    httpd_resp_send_chunk(req, nullptr, 0);
}

esp_err_t VisuServerModule::handleGetState(httpd_req_t* req) {
    if (!checkAuth(req)) return ESP_OK;
    VisuServerModule* self = static_cast<VisuServerModule*>(req->user_ctx);
    self->writeStateJson(req);
    return ESP_OK;
}

// ---------------------------------------------------------------------------
//  POST /ko  body: {"ko":200,"value":"01"}  → write GroupObject
// ---------------------------------------------------------------------------
esp_err_t VisuServerModule::handlePostKo(httpd_req_t* req) {
    if (!checkAuth(req)) return ESP_OK;
    VisuServerModule* self = static_cast<VisuServerModule*>(req->user_ctx);

    char body[64] = {};
    int received = httpd_req_recv(req, body, sizeof(body) - 1);
    if (received <= 0) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Empty body");
        return ESP_OK;
    }
    body[received] = '\0';

    // Parse {"ko":<N>,"value":"<hex>"}
    const char* koField = strstr(body, "\"ko\"");
    const char* valField = strstr(body, "\"value\"");
    if (!koField || !valField) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Missing fields");
        return ESP_OK;
    }
    const char* colonK = strchr(koField + 4, ':');
    if (!colonK) { httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, ""); return ESP_OK; }
    uint16_t koIdx = (uint16_t)strtoul(colonK + 1, nullptr, 10);

    const char* colonV = strchr(valField + 7, ':');
    if (!colonV) { httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, ""); return ESP_OK; }
    const char* pv = colonV + 1;
    while (*pv == ' ' || *pv == '"') pv++;
    uint8_t raw[4] = {};
    uint8_t sz = 0;
    char hex[3] = {0};
    while (*pv && *pv != '"' && *pv != '}' && sz < 4) {
        hex[0] = *pv++;
        hex[1] = *pv ? *pv++ : '0';
        hex[2] = '\0';
        raw[sz++] = (uint8_t)strtoul(hex, nullptr, 16);
    }

    // Construct a fake WS_MSG_KO_WRITE packet and reuse handleKoWrite
    uint8_t pkt[9] = { WS_MSG_KO_WRITE,
                       (uint8_t)(koIdx >> 8), (uint8_t)(koIdx & 0xFF),
                       sz,
                       raw[0], raw[1], raw[2], raw[3] };
    self->handleKoWrite(-1, pkt, 4 + sz);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, "{\"ok\":true}", -1);
    return ESP_OK;
}

// ---------------------------------------------------------------------------
//  Console / debug commands
// ---------------------------------------------------------------------------
bool VisuServerModule::processCommand(const std::string cmd, bool diagnose) {
    if (cmd == "visu rooms") {
        for (uint8_t r = 0; r < VIS_MAX_ROOMS; r++) {
            if (_rooms[r].name[0] == '\0') continue;
            openknx.logger.logWithPrefixAndValues("VIS", "Room %d: %s  floor=%d  widgets=%d",
                r, _rooms[r].name, _rooms[r].floorIdx, _rooms[r].widgetCount);
        }
        return true;
    }
    if (cmd == "visu version") {
        openknx.logger.logWithPrefixAndValues("VIS", "VisuServer cfgVer=%d", configVersion());
        return true;
    }
    return false;
}

void VisuServerModule::showHelp() {
    openknx.logger.logWithPrefixAndValues("VIS", "visu rooms    — list configured rooms");
    openknx.logger.logWithPrefixAndValues("VIS", "visu version  — show config version");
}
