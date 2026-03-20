#pragma once
#include <stdint.h>
#include <string.h>
#include "knxprod.h"

// ============================================================
//  OFM-VisuServer — Runtime Configuration Structures
// ============================================================

// Capacities
#define VIS_MAX_ROOMS       8
#define VIS_MAX_FLOORS      8
#define VIS_MAX_WIDGETS     14
#define VIS_MAX_FAVORITES   16
#define VIS_KO_BLOCK_SIZE   4   // 4 KOs per widget slot
#define VIS_MAX_TOKENS      4   // max concurrent sessions
#define VIS_MAX_WS_CLIENTS  4   // max WebSocket clients
#define VIS_MAX_AUTH_IPS    4   // IPs tracked for brute-force

// API protocol version — bump on breaking changes
#define VIS_API_VERSION     1

// Screensaver modes
#define VIS_SAVER_OFF   0
#define VIS_SAVER_DIM   1
#define VIS_SAVER_CLOCK 2

// Theme
#define VIS_THEME_DARK  0
#define VIS_THEME_LIGHT 1
#define VIS_THEME_AUTO  2

// Widget types
enum VisuWidgetType : uint8_t {
    VWT_EMPTY      = 0,
    VWT_SWITCH     = 1,
    VWT_DIMMER     = 2,
    VWT_BLIND      = 3,
    VWT_THERMOSTAT = 4,
    VWT_SCENE      = 5,
    VWT_RGB        = 6,
    VWT_VALUE      = 7,
    VWT_CAMERA     = 8,
    VWT_BUTTON     = 9,
    VWT_MUSIC      = 10,
};

// Trade (Gewerk) types
enum VisuTrade : uint8_t {
    VTR_NONE    = 0,
    VTR_LIGHT   = 1,
    VTR_SHADING = 2,
    VTR_CLIMATE = 3,
    VTR_MUSIC   = 4,
    VTR_SCENE   = 5,
    VTR_CAMERA  = 6,
    VTR_ENERGY  = 7,
};

// DPT selection (for Value/Button widget)
enum VisuDptSel : uint8_t {
    VDPT_1  = 0,  // DPT 1.xxx  1-bit boolean
    VDPT_5  = 1,  // DPT 5.xxx  8-bit unsigned
    VDPT_7  = 2,  // DPT 7.xxx  16-bit unsigned
    VDPT_9  = 3,  // DPT 9.xxx  16-bit float
    VDPT_12 = 4,  // DPT 12.xxx 32-bit unsigned
    VDPT_13 = 5,  // DPT 13.xxx 32-bit signed
    VDPT_14 = 6,  // DPT 14.xxx 32-bit float (IEEE754)
    VDPT_17 = 7,  // DPT 17.001 scene number
    VDPT_20 = 8,  // DPT 20.xxx 1-byte enum
};

// KO role (determines flags, direction)
enum VisuKoRole : uint8_t {
    VKR_CMD    = 0,  // Command: C W T       (send to bus)
    VKR_STATUS = 1,  // Status:  C R U       (receive from bus)
    VKR_BIDIR  = 2,  // Bidirectional: C R W T U
};

// Returns byte size for a DPT selection
inline uint8_t visDptSize(VisuDptSel d) {
    switch (d) {
        case VDPT_1:  return 1;
        case VDPT_5:  return 1;
        case VDPT_7:  return 2;
        case VDPT_9:  return 2;
        case VDPT_12: return 4;
        case VDPT_13: return 4;
        case VDPT_14: return 4;
        case VDPT_17: return 1;
        case VDPT_20: return 1;
        default:      return 1;
    }
}

// Returns DPT major number string for JSON
inline const char* visDptStr(VisuDptSel d) {
    switch (d) {
        case VDPT_1:  return "1.001";
        case VDPT_5:  return "5.001";
        case VDPT_7:  return "7.001";
        case VDPT_9:  return "9.001";
        case VDPT_12: return "12.001";
        case VDPT_13: return "13.001";
        case VDPT_14: return "14.001";
        case VDPT_17: return "17.001";
        case VDPT_20: return "20.001";
        default:      return "1.001";
    }
}

// Per-KO cache entry
struct VisuKoEntry {
    uint16_t koIndex;    // absolute KO index in the group object table
    uint8_t  dptMajor;   // DPT major (1,5,7,9,12,13,14,17,20)
    uint8_t  role;       // VisuKoRole
    uint8_t  value[4];   // cached raw value (max 4 bytes for all supported DPTs)
    bool     valid;      // true after first value received/read
};

// Per-widget runtime data
struct VisuWidget {
    VisuWidgetType type;
    char     name[21];           // 20 char + null
    uint8_t  icon;               // icon enum index
    uint8_t  tileSize;           // 0=auto, 1=small(1x1), 2=large(2x2), 3=wide(1x2)
    uint8_t  sortOrder;          // 0-16 sort order within section
    uint8_t  w;                  // (legacy, unused)
    uint8_t  h;                  // (legacy, unused)
    VisuTrade trade;
    VisuDptSel dpt;              // for VWT_VALUE / VWT_BUTTON
    char     cameraUrl[33];      // for VWT_CAMERA (32 chars + null)
    VisuKoEntry kos[VIS_KO_BLOCK_SIZE];
    uint8_t  koCount;            // number of active KOs (0 for EMPTY/CAMERA)
};

// Per-room runtime data
struct VisuRoom {
    char     name[21];
    uint8_t  icon;
    uint8_t  floorIdx;           // 0-based index into floors[]
    uint8_t  order;
    uint8_t  widgetCount;
    VisuWidget widgets[VIS_MAX_WIDGETS];
};

// Per-floor runtime data
struct VisuFloor {
    char    name[21];
    uint8_t order;
};

// Favorite entry (room+widget reference)
struct VisuFavorite {
    uint8_t roomIdx;
    uint8_t widgetIdx;
    bool    valid;
};

// Global runtime config
struct VisuGlobalConfig {
    char    deviceName[21];
    bool    authEnabled;
    uint32_t authPin;            // 4-digit PIN stored as uint32
    uint8_t  authMaxAttempts;
    uint8_t  authLockoutMin;
    uint8_t  theme;              // VIS_THEME_*
    uint8_t  heartbeatSec;
    bool    dashboardEnabled;
    uint8_t  visibleFloors;      // 1-8
    uint8_t  visibleRooms;       // 1-8
    uint8_t  screensaverMin;     // 0=off
    uint8_t  screensaverMode;    // VIS_SAVER_*
};

// Session token (auth)
struct VisuSessionToken {
    char     token[33];   // 32 hex chars + null
    uint32_t expiresMs;   // millis()-based expiry
    uint32_t srcIp;
    bool     valid;
};

// Per-IP auth tracking (brute-force protection)
struct VisuAuthAttempt {
    uint32_t srcIp;
    uint8_t  failCount;
    uint32_t lockedUntilMs;
};

// ============================================================
//  ETS Parameter Offset Defines (absolute addresses)
//  knxprod.h provides VIS_VIS* names; we alias to shorter names
//  used throughout the firmware.  The #ifndef guards let the
//  aliases co-exist when knxprod.h is included first.
// ============================================================

// Global params — alias to knxprod.h generated names
#ifdef VIS_VISDeviceName
  #define VIS_DeviceName          VIS_VISDeviceName
  #define VIS_Flags1              VIS_VISAuthEnabled   // flags byte (same abs offset for all flag bits)
  #define VIS_AuthPIN             VIS_VISAuthPIN
  #define VIS_AuthMaxAttempts     VIS_VISAuthMaxAttempts
  #define VIS_AuthLockoutMin      VIS_VISAuthLockoutMin
  #define VIS_HeartbeatSec        VIS_VISHeartbeatSec
  #define VIS_VisibleFloors       VIS_VISVisibleFloors
  #define VIS_VisibleRooms        VIS_VISVisibleRooms
  #define VIS_ScreensaverMin      VIS_VISScreensaverMin
#else
  #error "knxprod.h must be included before VisuConfig.h — VIS parameter defines are required"
#endif

// Derived flag masks (MSB-first bit numbering, matches OpenKNXproducer output)
#define VIS_AuthEnabledMask       VIS_VISAuthEnabledMask
#define VIS_DashboardEnabledMask  VIS_VISDashboardEnabledMask
#define VIS_ThemeMask             VIS_VISThemeMask
#define VIS_ThemeShift            VIS_VISThemeShift
#define VIS_SaverModeMask         VIS_VISScreensaverModeMask
#define VIS_SaverModeShift        VIS_VISScreensaverModeShift

// Floor block — derive base/stride from knxprod.h FL0/FL1
#ifdef VIS_VISFL0Name
  #define VIS_FloorBase           VIS_VISFL0Name
  #define VIS_FloorStride         (VIS_VISFL1Name - VIS_VISFL0Name)
  #define VIS_FL0Name             VIS_VISFL0Name
  #define VIS_FL0Order            VIS_VISFL0Order
#else
  #define VIS_FloorBase           255
  #define VIS_FloorStride         21
  #define VIS_FL0Name             255
  #define VIS_FL0Order            275
#endif

// Favorite block — derive from knxprod.h FAV0/FAV1
#ifdef VIS_VISFAV0Room
  #define VIS_FavBase             VIS_VISFAV0Room
  #define VIS_FavStride           (VIS_VISFAV1Room - VIS_VISFAV0Room)
  #define VIS_FAV0Room            VIS_VISFAV0Room
  #define VIS_FAV0Widget          VIS_VISFAV0Widget
#else
  #define VIS_FavBase             423
  #define VIS_FavStride           2
  #define VIS_FAV0Room            423
  #define VIS_FAV0Widget          424
#endif

// Room (channel) template
#ifdef VIS_ParamBlockOffset
  #define VIS_RoomBase            VIS_ParamBlockOffset
  #define VIS_RoomStride          VIS_ParamBlockSize
  // Room header offsets (channel-relative, from knxprod.h VIS_CH* defines)
  #define VIS_RxName_Off          VIS_CHRoomName
  #define VIS_RxIcon_Off          VIS_CHRoomIcon
  #define VIS_RxFloor_Off         VIS_CHRoomFloor
  #define VIS_RxOrder_Off         VIS_CHRoomOrder
  #define VIS_RxVisibleWidgets_Off VIS_CHVisibleWidgets
  // Widget slot offsets within channel
  #define VIS_WzBase_Off          VIS_CHWz0Type    // first widget starts here
  #define VIS_WzStride            (VIS_CHWz1Type - VIS_CHWz0Type)
  #define VIS_WzType_Off          0
  #define VIS_WzName_Off          (VIS_CHWz0Name - VIS_CHWz0Type)
  #define VIS_WzIcon_Off          (VIS_CHWz0Icon - VIS_CHWz0Type)
  #define VIS_WzTileSize_Off      (VIS_CHWz0TileSize - VIS_CHWz0Type)
  #define VIS_WzSortOrder_Off     (VIS_CHWz0SortOrder - VIS_CHWz0Type)
  #define VIS_WzWidth_Off         (VIS_CHWz0Width - VIS_CHWz0Type)
  #define VIS_WzHeight_Off        (VIS_CHWz0Height - VIS_CHWz0Type)
  #define VIS_WzTrade_Off         (VIS_CHWz0Trade - VIS_CHWz0Type)
  #define VIS_WzDpt_Off           (VIS_CHWz0Dpt - VIS_CHWz0Type)
  #define VIS_WzCamUrl_Off        (VIS_CHWz0CamUrl - VIS_CHWz0Type)
#else
  #define VIS_RoomBase            455
  #define VIS_RoomStride          626
  #define VIS_RxName_Off          0
  #define VIS_RxIcon_Off          20
  #define VIS_RxFloor_Off         21
  #define VIS_RxOrder_Off         22
  #define VIS_RxVisibleWidgets_Off 23
  #define VIS_WzBase_Off          24
  #define VIS_WzStride            43
  #define VIS_WzType_Off          0
  #define VIS_WzName_Off          1
  #define VIS_WzIcon_Off          21
  #define VIS_WzTileSize_Off      22
  #define VIS_WzSortOrder_Off     23
  #define VIS_WzWidth_Off         24
  #define VIS_WzHeight_Off        25
  #define VIS_WzTrade_Off         26
  #define VIS_WzDpt_Off           27
  #define VIS_WzCamUrl_Off        28
#endif

// KO index calculation: base + room*64 + widget*4 + koOffset
// VIS_KoBase MUST match KoOffset="400" in HueGateway-Dev/Release.xml
// and const KO_OFFSET=400 in app.js.  Change all three together if you renumber.
#ifndef VIS_KoBase
  #define VIS_KoBase              400  // directly after FCB end (250+15*10=400): LOG(100-249), FCB(250-399), VIS(400-911)
  #define VIS_KoRoomStride        56   // 14 widgets × 4 KOs
  #define VIS_KoWidgetStride      4
#endif

// FCB-style aliases: OpenKNXproducer generates these from templ.xml
// Used in C++ as: knx.paramData(VIS_ParamBlockOffset + roomIdx * VIS_ParamBlockSize + VIS_RxName_Off)
#ifndef VIS_ParamBlockOffset
  #define VIS_ParamBlockOffset    VIS_RoomBase   // alias; real value from knxprod.h
#endif
#ifndef VIS_ParamBlockSize
  #define VIS_ParamBlockSize      VIS_RoomStride // alias; real value from knxprod.h
#endif

// Helper macros for parameter access (room rIdx, widget wIdx)
#define VIS_RoomOffset(rIdx)      (VIS_RoomBase + (rIdx) * VIS_RoomStride)
#define VIS_RxName(rIdx)          (VIS_RoomOffset(rIdx) + VIS_RxName_Off)
#define VIS_RxIcon(rIdx)          (VIS_RoomOffset(rIdx) + VIS_RxIcon_Off)
#define VIS_RxFloor(rIdx)         (VIS_RoomOffset(rIdx) + VIS_RxFloor_Off)
#define VIS_RxOrder(rIdx)         (VIS_RoomOffset(rIdx) + VIS_RxOrder_Off)
#define VIS_RxVisibleWidgets(rIdx) (VIS_RoomOffset(rIdx) + VIS_RxVisibleWidgets_Off)

#define VIS_WzOffset(rIdx, wIdx)  (VIS_RoomOffset(rIdx) + VIS_WzBase_Off + (wIdx) * VIS_WzStride)
#define VIS_WzType(rIdx, wIdx)    (VIS_WzOffset(rIdx, wIdx) + VIS_WzType_Off)
#define VIS_WzName(rIdx, wIdx)    (VIS_WzOffset(rIdx, wIdx) + VIS_WzName_Off)
#define VIS_WzIcon(rIdx, wIdx)    (VIS_WzOffset(rIdx, wIdx) + VIS_WzIcon_Off)
#define VIS_WzTileSize(rIdx, wIdx) (VIS_WzOffset(rIdx, wIdx) + VIS_WzTileSize_Off)
#define VIS_WzSortOrder(rIdx, wIdx) (VIS_WzOffset(rIdx, wIdx) + VIS_WzSortOrder_Off)
#define VIS_WzWidth(rIdx, wIdx)   (VIS_WzOffset(rIdx, wIdx) + VIS_WzWidth_Off)
#define VIS_WzHeight(rIdx, wIdx)  (VIS_WzOffset(rIdx, wIdx) + VIS_WzHeight_Off)
#define VIS_WzTrade(rIdx, wIdx)   (VIS_WzOffset(rIdx, wIdx) + VIS_WzTrade_Off)
#define VIS_WzDpt(rIdx, wIdx)     (VIS_WzOffset(rIdx, wIdx) + VIS_WzDpt_Off)
#define VIS_WzCamUrl(rIdx, wIdx)  (VIS_WzOffset(rIdx, wIdx) + VIS_WzCamUrl_Off)

#define VIS_FloorOffset(fIdx)     (VIS_FloorBase + (fIdx) * VIS_FloorStride)
#define VIS_FLxName(fIdx)         (VIS_FloorOffset(fIdx))
#define VIS_FLxOrder(fIdx)        (VIS_FloorOffset(fIdx) + 20)

#define VIS_FavOffset(favIdx)     (VIS_FavBase + (favIdx) * VIS_FavStride)
#define VIS_FAVxRoom(favIdx)      (VIS_FavOffset(favIdx))
#define VIS_FAVxWidget(favIdx)    (VIS_FavOffset(favIdx) + 1)

// KO index for a given room/widget/position
#define VIS_KO(room, widget, pos) (VIS_KoBase + (room) * VIS_KoRoomStride + (widget) * VIS_KoWidgetStride + (pos))

// Widget type → KO count
inline uint8_t visKoCount(VisuWidgetType t) {
    switch (t) {
        case VWT_SWITCH:     return 2;
        case VWT_DIMMER:     return 3;
        case VWT_BLIND:      return 4;
        case VWT_THERMOSTAT: return 3;
        case VWT_SCENE:      return 1;
        case VWT_RGB:        return 3;
        case VWT_VALUE:      return 1;
        case VWT_CAMERA:     return 0;
        case VWT_BUTTON:     return 1;
        case VWT_MUSIC:      return 3;
        default:             return 0;
    }
}

// DPT string for a given widget KO (fixed per widget type EXCEPT Value/Button where dpt is configured)
inline const char* visKoDptStr(VisuWidgetType type, VisuDptSel configDpt, uint8_t koIdx) {
    switch (type) {
        case VWT_SWITCH:     return "1.001";
        case VWT_DIMMER:     return (koIdx == 0) ? "1.001" : "5.001";
        case VWT_BLIND:      return (koIdx == 0 || koIdx == 3) ? "1.001" : "5.001";
        case VWT_THERMOSTAT: return (koIdx == 0 || koIdx == 1) ? "9.001" : "20.102";
        case VWT_SCENE:      return "17.001";
        case VWT_RGB:        return (koIdx == 0) ? "1.001" : (koIdx == 1) ? "232.600" : "5.001";
        case VWT_VALUE:      return visDptStr(configDpt);
        case VWT_BUTTON:     return visDptStr(configDpt);
        case VWT_MUSIC:      return (koIdx == 1) ? "5.001" : "1.001";
        default:             return "1.001";
    }
}

// KO role for a given widget type + KO index
inline VisuKoRole visKoRole(VisuWidgetType type, uint8_t koIdx) {
    switch (type) {
        case VWT_SWITCH:
            return (koIdx == 0) ? VKR_CMD : VKR_STATUS;
        case VWT_DIMMER:
            return (koIdx == 2) ? VKR_STATUS : VKR_CMD;
        case VWT_BLIND:
            return (koIdx == 1 || koIdx == 2) ? VKR_BIDIR : VKR_CMD;
        case VWT_THERMOSTAT:
            return (koIdx == 0) ? VKR_STATUS : VKR_BIDIR;
        case VWT_SCENE:
            return VKR_CMD;
        case VWT_RGB:
            return (koIdx == 0) ? VKR_CMD : VKR_BIDIR;
        case VWT_VALUE:
            return VKR_STATUS;
        case VWT_BUTTON:
            return VKR_CMD;
        case VWT_MUSIC:
            return VKR_CMD;
        default:
            return VKR_CMD;
    }
}

// Icon name strings for JSON (room icons, indexed by icon enum value)
inline const char* visRoomIconName(uint8_t icon) {
    static const char* names[] = {
        "living-room", "kitchen", "bathroom", "bedroom",
        "kids-room", "hallway", "office", "garden",
        "garage", "basement", "dining-room", "terrace"
    };
    if (icon < 12) return names[icon];
    return "room";
}

// Trade ID strings for JSON
inline const char* visTradeId(VisuTrade t) {
    switch (t) {
        case VTR_LIGHT:   return "light";
        case VTR_SHADING: return "shading";
        case VTR_CLIMATE: return "climate";
        case VTR_MUSIC:   return "music";
        case VTR_SCENE:   return "scene";
        case VTR_CAMERA:  return "camera";
        case VTR_ENERGY:  return "energy";
        default:          return "none";
    }
}

// Widget type string for JSON
inline const char* visWidgetTypeStr(VisuWidgetType t) {
    switch (t) {
        case VWT_SWITCH:     return "switch";
        case VWT_DIMMER:     return "dimmer";
        case VWT_BLIND:      return "blind";
        case VWT_THERMOSTAT: return "thermostat";
        case VWT_SCENE:      return "scene";
        case VWT_RGB:        return "rgb";
        case VWT_VALUE:      return "value";
        case VWT_CAMERA:     return "camera";
        case VWT_BUTTON:     return "button";
        case VWT_MUSIC:      return "music";
        default:             return "empty";
    }
}
