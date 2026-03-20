#pragma once
#include <OpenKNX.h>
#include "VisuConfig.h"
#include "VisuWebSocket.h"

// ============================================================
//  OFM-VisuServer — VisuServerModule
//  OpenKNX Module providing a Basalte-style KNX WebUI.
// ============================================================

// Flash storage magic word to detect valid savedState
#define VIS_FLASH_MAGIC 0x56534D01u  // "VSM\x01"

// Maximum byte size of a single /config JSON chunk
#define VIS_CONFIG_CHUNK_SIZE 512

// Saved state stored in flash (small, only persists configVersion counter)
struct VisuFlashState {
    uint32_t magic;
    uint16_t configVersion;
};

class VisuServerModule : public OpenKNX::Module {
public:
    VisuServerModule();

    // OpenKNX Module interface
    const std::string name() override;
    const std::string version() override;
    void   setup(bool firstCall) override;
    void   loop(bool firstCall) override;
    void   processInputKo(GroupObject& ko) override;
    bool   processCommand(const std::string cmd, bool diagnose) override;
    void   showHelp() override;
    void   writeFlash() override;
    void   readFlash(const uint8_t* data, const uint16_t size) override;

    // Called by VisuWebSocket on KO_WRITE from client
    void handleKoWrite(int fd, const uint8_t* data, size_t len);

    // Called by VisuWebSocket to check token validity
    bool isValidToken(const char* token);

    // Runtime data (public for WebSocket callback access)
    VisuGlobalConfig    _cfg;
    VisuFloor           _floors[VIS_MAX_FLOORS];
    VisuRoom            _rooms[VIS_MAX_ROOMS];
    VisuFavorite        _favorites[VIS_MAX_FAVORITES];
    uint8_t             _roomCount;
    uint8_t             _floorCount;
    uint8_t             _favCount;

private:
    // Initialise data structures from ETS parameters
    void loadEtsParams();

    // Register HTTP handlers on the WebUI server
    void registerHttpHandlers();

    // Send all current KO values to a newly authenticated client
    void sendFullState(int wsfd);

    // Request all GroupObject reads on the bus (called once after startup delay)
    void requestAllKoReads();

    // Token management
    void generateToken(char* outToken32); // fills 32 hex chars
    bool addSession(const char* token, uint32_t srcIp);
    void expireSessions(uint32_t nowMs);

    // Single HTTP handler functions (static, dispatched via req->user_ctx)
    static esp_err_t handleGetIndex(httpd_req_t* req);
    static esp_err_t handleGetRootRedirect(httpd_req_t* req);
    static esp_err_t handleGetConfig(httpd_req_t* req);
    static esp_err_t handleGetState(httpd_req_t* req);
    static esp_err_t handlePostAuth(httpd_req_t* req);
    static esp_err_t handlePostKo(httpd_req_t* req);
    static esp_err_t handleGetAppJs(httpd_req_t* req);
    static esp_err_t handleGetStyleCss(httpd_req_t* req);
    static esp_err_t handleGetIconsSvg(httpd_req_t* req);

    // Auth guard: returns true if this request carries a valid token.
    // Writes 401 response and returns false if not authenticated.
    static bool checkAuth(httpd_req_t* req);

    // JSON writers called by handleGetConfig/handleGetState
    void writeConfigJson(httpd_req_t* req);
    void writeStateJson(httpd_req_t* req);

    // Internal helpers
    uint16_t configVersion() const { return _flashState.configVersion; }
    void bumpConfigVersion();
    VisuRoom* findRoom(uint8_t roomIdx);
    VisuWidget* findWidget(uint8_t roomIdx, uint8_t widgetIdx);

    // Flash state
    VisuFlashState _flashState;

    // Session tokens
    VisuSessionToken _tokens[VIS_MAX_TOKENS];

    // Auth attempts (brute-force protection)
    VisuAuthAttempt _authAttempts[VIS_MAX_AUTH_IPS];

    // State flags
    bool     _wsRegistered;         // WebSocket URI registered on httpd
    bool     _httpRegistered;       // HTTP URIs registered
    bool     _koReadsRequested;     // one-time initial read
    uint32_t _lastHeartbeatMs;
    uint32_t _lastKoReadRequestMs;
    uint32_t _lastEvictMs;

    // KO index map: for fast lookup in processInputKo
    // Maps absolute KO index → (room, widget, koPos)
    struct KoLookup {
        uint8_t room;
        uint8_t widget;
        uint8_t pos;
        bool    valid;
    };
    // 512 KOs max (rooms 8 × widgets 16 × 4 positions)
    KoLookup _koLookup[VIS_MAX_ROOMS * VIS_MAX_WIDGETS * VIS_KO_BLOCK_SIZE];
    uint16_t _koLookupCount;

    void buildKoLookup();
    const KoLookup* lookupKo(uint16_t koIndex) const;
};

extern VisuServerModule openknxVisuServerModule;
