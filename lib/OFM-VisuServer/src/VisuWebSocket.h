#pragma once
#include <stdint.h>
#include "VisuConfig.h"

// esp-idf WebSocket + HTTP headers
#include <esp_http_server.h>

// ============================================================
//  OFM-VisuServer — WebSocket Manager
//  * Handles up to VIS_MAX_WS_CLIENTS concurrent connections
//  * Binary message protocol:
//    0x01  KO_UPDATE  : [1 type][2 koIndex][1 dptSize][data...]
//    0x02  KO_WRITE   : [1 type][2 koIndex][1 dptSize][data...]  (client→server)
//    0x03  FULL_STATE : [1 type][2 configVersion]  (server→client after connect)
//    0x10  CONFIG_VER : [1 type][2 configVersion]
//    0xFE  HEARTBEAT  : [1 type]
//    0xFF  AUTH_TOKEN : [1 type][32 token bytes]  (client→server first frame)
// ============================================================

#define WS_MSG_KO_UPDATE    0x01
#define WS_MSG_KO_WRITE     0x02
#define WS_MSG_FULL_STATE   0x03
#define WS_MSG_CONFIG_VER   0x10
#define WS_MSG_HEARTBEAT    0xFE
#define WS_MSG_AUTH_TOKEN   0xFF
#define WS_MSG_AUTH_FAIL    0xF0

// Single slot in the client table
struct WsClient {
    int        fd;           // file descriptor (-1 = free)
    bool       authenticated;
    uint32_t   srcIp;
    uint32_t   lastPingMs;
};

class VisuWebSocket {
public:
    VisuWebSocket();

    // Called once after the HTTP server starts.
    // Registers the /ws URI on hd.
    esp_err_t registerUri(httpd_handle_t hd);

    // Broadcast a KO update to all authenticated clients.
    // buf: raw binary payload; len: byte count
    void broadcastKoUpdate(uint16_t koIndex, const uint8_t* value, uint8_t size, uint8_t dptMajor);

    // Send full-state marker to a specific client (triggers client to re-fetch /config + /state)
    void sendFullState(int fd, uint16_t configVersion);

    // Send config-version change notice to all clients
    void broadcastConfigVer(uint16_t configVersion);

    // Send heartbeat to all authenticated clients (call every heartbeatSec)
    void broadcastHeartbeat();

    // Close a client by fd (called on disconnect)
    void removeClient(int fd);

    // Evict clients that haven't pinged in >2× heartbeatSec (call in loop())
    void evictStale(uint32_t nowMs, uint8_t heartbeatSec);

    // Check whether we have any authenticated clients (saves broadcast cost)
    bool hasClients() const;

private:
    WsClient _clients[VIS_MAX_WS_CLIENTS];

    // Add newly connected fd to the table. Returns true if space was available.
    bool addClient(int fd, uint32_t srcIp);

    // Send a raw binary frame to a single client fd
    void sendTofd(int fd, const uint8_t* data, size_t len);

    // Auth-token handler: checks token against VisuWebSocket's own ptr (filled externally)
    void handleAuthFrame(int fd, const uint8_t* data, size_t len);

    // URI handler (static, dispatches to singleton)
    static esp_err_t wsUriHandler(httpd_req_t* req);

    httpd_handle_t _hd;   // stored after register, used for async sends
};

// Module-level singleton (defined in VisuWebSocket.cpp)
extern VisuWebSocket openknxVisuWS;
