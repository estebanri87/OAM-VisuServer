# Plan: OFM-VisuServer — KNX WebUI Visualization Module

## Zusammenfassung

Neues OpenKNX-Modul **OFM-VisuServer** für eine moderne WebUI-Visualisierung im Stil von **Basalte Core / Loxone / Optimus Edge** auf dem REG1 Base Lan TP.

**Kernprinzipien:**
- Rein darstellend — keine eigene Logik, nur KO-basierte KNX-Kommunikation
- Vollständig per **ETS parametrierbar** (Stockwerke, Räume, Widget-Positionen, Gewerk-Zuordnung)
- **Festes 6×4 Grid-Layout** pro Raum (Basalte Core Stil) — Tile-Positionen per ETS vorgegeben, **proportionale Skalierung** auf allen Bildschirmgrößen (kein Spalten-Umbruch)
- **Gewerk-Übersichtsseiten** (Licht, Beschattung, Heizung, Musik, Szenen, Kameras, Energie) mit Stockwerk-Gruppierung
- WebSocket + REST API (ESP-IDF `httpd_ws_handler`)
- Kiosk-Browser-tauglich (Tablets, Touch-Panels, Fullscreen) mit Screensaver/Auto-Dim
- Baut auf bestehendem **OFM-WebUI** Modul auf
- **KO-Budget:** max. 512 KOs (8 Räume × 16 Widgets × 4 KO-Block) — innerhalb MAIN_MaxKoNumber=780
- **Unterstützte DPTs:** 1, 5, 7, 9, 12, 13, 14, 17, 20, 232 (kein DPT 16 — max. 4 Bytes pro Wert)

---

## Navigationskonzept (3 Ebenen)

```
┌──────────────────────────────────────────────────┐
│  🏠 Dashboard  │  🚪 Räume  │  💡🪟🌡️🎵🎬📷⚡  │
│  (Favoriten)   │ (je Raum   │  (Gewerk-Über-    │
│                │   6×4 Grid) │   sichtsseiten)   │
└──────────────────────────────────────────────────┘
```

1. **Dashboard** — Favoriten-Widgets, schneller Überblick
2. **Räume** — Einzelne Räume mit festem 6×4 Grid (Basalte Core Stil)
3. **Gewerke** — 7 Übersichtsseiten, alle Widgets eines Gewerks nach Stockwerk gruppiert

**Hauptnavigation:**
- Alle Bildschirmgrößen: Linke Sidebar (eingeklappt auf schmalen Screens, Hamburger-Icon)
- Grid skaliert proportional via `vw`-Einheiten — **keine Spaltenänderung**, immer 6×4

**Tabs:** Dashboard | Räume | Licht | Beschattung | Heizung/Klima | Musik | Szenen | Kameras | Energie

---

## Phase 1: Modul-Grundstruktur

### Step 1.1 — Projektstruktur

```
OFM-VisuServer/
├── library.json                     # Modul-Metadata
├── LICENSE
├── README.md
├── doc/
│   └── Applikationsbeschreibung-VisuServer.md
├── src/
│   ├── VisuServerModule.h           # OpenKNX::Module Hauptklasse
│   ├── VisuServerModule.cpp
│   ├── VisuWebSocket.h              # WebSocket-Handler
│   ├── VisuWebSocket.cpp
│   ├── VisuConfig.h                 # ETS-Parameter → Runtime-Structs
│   ├── VisuConfig.cpp
│   ├── VisuServer.share.xml         # ETS-Parameter & UI-Definition
│   ├── VisuServer.templ.xml         # Widget-Channel-Template
│   └── VisuServer.script.js         # ETS-Hilfsskripte
├── include/                          # Generierte file_*.h nach Build
└── www/
    ├── index.html                    # SPA Shell
    ├── app.js                        # Frontend-Logik
    ├── style.css                     # Basalte/Loxone/Optimus Design
    └── icons.svg                     # SVG Sprite Sheet (~30 Icons)
```

### Step 1.2 — library.json

Vorlage: `OFM-Network/library.json`
- Name: "OFM-VisuServer"
- Version: 0.1.0
- Description: "WebUI Visualization for KNX"

### Step 1.3 — VisuServerModule Klasse

Extends `OpenKNX::Module` (NICHT ChannelOwner — Widgets sind keine eigenständigen Channel-Loops).

**Zu implementierende Methoden:**

| Methode | Aufgabe |
|---------|---------|
| `name()` | → "VisuServer" |
| `version()` | → MODULE_VisuServer_Version |
| `setup(bool configured)` | ETS-Parameter lesen, Raum/Widget/Gewerk-Structs aufbauen, Endpoints bei openknxWebUI registrieren |
| `loop(bool configured)` | WebSocket-Polling, Heartbeat |
| `processInputKo(GroupObject &ko)` | KO-Wertänderung cachen + an alle WebSocket-Clients broadcasten |
| `processCommand()` | Diagnose-Befehle (Status, verbundene Clients, Config-Dump) |

**Integration:** Registriert sich bei `openknxWebUI` via `addHandler()` und `addPage()` für REST-Endpoints und statische Dateien.

**Referenz-Dateien:**
- `OFM-Network/src/NetworkModule.h/.cpp` — Lifecycle-Pattern
- `OFM-WebUI/src/WebUI.h` — addHandler(), addPage() API

---

## Phase 2: ETS-Parametrierung

### Step 2.1 — Parameter-Hierarchie

**Räume sind ETS-Channels** (nicht einzelne Widget-Slots). Jeder Raum-Channel enthält 16 Widget-Slot-Parameterblöcke inline.

```
Stockwerke (8 max, globale Parameter)
  └── Räume (8 max, je ein ETS-Channel)
       └── Widget-Slots (16 pro Raum, festes 6×4 Grid)
            └── Gewerk-Zuordnung (manuell pro Widget)
```

### Step 2.2 — Globale Parameter (~56 Bytes)

| Parameter | Typ | Bits | Beschreibung |
|-----------|-----|------|-------------|
| `VIS_DeviceName` | Text | 128 | Anzeigename der Visualisierung |
| `VIS_AuthEnabled` | Bool | 1 | PIN-Schutz aktiv/inaktiv |
| `VIS_AuthPIN` | Zahl | 32 | 4-stelliger numerischer PIN |
| `VIS_AuthMaxAttempts` | Uint4 | 4 | Max. Fehlversuche vor Lockout (3-10, Default: 5) |
| `VIS_AuthLockoutMin` | Uint8 | 8 | Lockout-Dauer in Minuten (1-60, Default: 5) |
| `VIS_Theme` | Enum | 2 | Dark / Light / Auto |
| `VIS_HeartbeatSec` | Uint8 | 8 | WebSocket-Heartbeat Interval (Sekunden) |
| `VIS_DashboardEnabled` | Bool | 1 | Dashboard/Favoriten aktiv |
| `VIS_VisibleFloors` | Uint4 | 4 | Anzahl sichtbare Stockwerke (1-8) |
| `VIS_ScreensaverMin` | Uint8 | 8 | Screensaver-Timeout in Minuten (0=aus, 1-60) |
| `VIS_ScreensaverMode` | Enum | 2 | Screensaver-Modus (Abdunkeln / Uhr / Aus) |

### Step 2.3 — Stockwerk-Parameter (je ~24 Bytes × 8 = ~192 Bytes)

| Parameter | Typ | Bits | Beschreibung |
|-----------|-----|------|-------------|
| `VIS_FLxName` | Text | 160 | Stockwerk-Name (z.B. "Erdgeschoss", "OG1") |
| `VIS_FLxOrder` | Uint4 | 4 | Sortierposition |

### Step 2.4 — Raum-Parameter (ETS-Channel, je ~28 Bytes × 8 = ~224 Bytes)

Jeder Raum ist ein **ETS-Channel** (VisuServer.templ.xml). Die Raum-Parameter bilden den Channel-Header.

| Parameter | Typ | Bits | Beschreibung |
|-----------|-----|------|-------------|
| `VIS_RxName` | Text | 160 | Raum-Name |
| `VIS_RxIcon` | Enum | 5 | Raum-Icon (Wohnzimmer, Küche, Bad, Schlafzimmer, Kinderzimmer, Flur, Büro, Garten, Garage, Keller, Esszimmer, Terrasse, ...) |
| `VIS_RxFloor` | Uint4 | 4 | **Stockwerk-Zuordnung** (Referenz auf VIS_FLx) |
| `VIS_RxVisibleWidgets` | Uint5 | 5 | Anzahl sichtbare Widget-Slots (1-16) |
| `VIS_RxOrder` | Uint4 | 4 | Sortierposition innerhalb des Stockwerks |

### Step 2.5 — Widget-Slot-Parameter im festen 6×4 Grid

**16 Slots pro Raum × 8 Räume = 128 Widget-Slots**
**Je ~34 Bytes = ~4.352 Bytes**

| Parameter | Typ | Bits | Beschreibung |
|-----------|-----|------|-------------|
| `VIS_RxWzType` | Enum | 4 | Widget-Typ (siehe Tabelle unten) |
| `VIS_RxWzName` | Text | 160 | Widget-Name |
| `VIS_RxWzIcon` | Enum | 5 | Widget-Icon-Auswahl |
| **`VIS_RxWzCol`** | Uint3 | 3 | **Grid-Spalte (0-5)** |
| **`VIS_RxWzRow`** | Uint3 | 3 | **Grid-Zeile (0-3)** |
| **`VIS_RxWzWidth`** | Enum | 2 | **Tile-Breite: 1, 2 oder 3 Spalten** |
| **`VIS_RxWzHeight`** | Enum | 2 | **Tile-Höhe: 1 oder 2 Zeilen** |
| **`VIS_RxWzTrade`** | Enum | 4 | **Gewerk-Zuordnung (manuell)** |
| `VIS_RxWzDPT` | Enum | 4 | DPT-Auswahl bei Typ=Wert/Taster (siehe unterstützte DPTs) |
| (Typ-spezifisch) | variabel | — | Kamera-URL (32B) nur bei Typ=Kamera |

**Widget-Typen (VIS_RxWzType):**

| Wert | Typ | KOs | Beschreibung |
|------|-----|-----|-------------|
| 0 | Leer | 0 | Slot nicht belegt |
| 1 | Switch | 2 | Licht An/Aus |
| 2 | Dimmer | 3 | Licht mit Slider |
| 3 | Jalousie | 4 | Auf/Ab, Position, Lamelle, Stop |
| 4 | Thermostat | 3 | Ist/Soll-Temperatur, Modus |
| 5 | Szene | 1 | Szenen-Aufruf |
| 6 | RGB/RGBW | 3 | Schalten, Farbe (DPT 232.600), Helligkeit |
| 7 | Wert-Anzeige | 1 | Sensor, Zähler (DPT wählbar) |
| 8 | Kamera | 0 | MJPEG-Bild (URL aus Parameter, kein KO) |
| 9 | Taster | 1 | Beliebigen KO-Wert senden (DPT wählbar) |
| 10 | Musik | 3 | Play/Pause, Volume, Next/Prev |

**Unterstützte DPTs (VIS_RxWzDPT für Wert/Taster):**

| Wert | DPT | Bytes | Beschreibung |
|------|-----|-------|-------------|
| 0 | 1.xxx | 1 | Boolean (An/Aus, Ja/Nein) |
| 1 | 5.xxx | 1 | Unsigned 8-Bit (%, 0-255) |
| 2 | 7.xxx | 2 | Unsigned 16-Bit (Zähler) |
| 3 | 9.xxx | 2 | 16-Bit Float (Temperatur, Feuchte) |
| 4 | 12.xxx | 4 | Unsigned 32-Bit (Zähler) |
| 5 | 13.xxx | 4 | Signed 32-Bit (Zähler) |
| 6 | 14.xxx | 4 | IEEE 754 Float (Leistung, Energie) |
| 7 | 17.001 | 1 | Szene (0-63) |
| 8 | 20.xxx | 1 | Enum (HVAC-Modus etc.) |

> **Hinweis:** DPT 16.001 (14-Byte-String) wird **nicht** unterstützt — alle Cache-Werte müssen in max. 4 Bytes passen.

**Gewerk-Zuordnung (VIS_RxWzTrade):**

| Wert | Gewerk | Gewerk-Seite |
|------|--------|-------------|
| 0 | Keine | Widget erscheint auf keiner Gewerk-Seite |
| 1 | Licht | 💡 Licht-Übersicht |
| 2 | Beschattung | 🪟 Beschattung-Übersicht |
| 3 | Heizung/Klima | 🌡️ Heizung/Klima-Übersicht |
| 4 | Musik | 🎵 Musik-Übersicht |
| 5 | Szene | 🎬 Szenen-Übersicht |
| 6 | Kamera | 📷 Kamera-Übersicht |
| 7 | Energie | ⚡ Energie-Übersicht |

### Step 2.6 — Dashboard/Favoriten (16 × 2 Bytes = 32 Bytes)

| Parameter | Typ | Bits | Beschreibung |
|-----------|-----|------|-------------|
| `VIS_FAVxRoom` | Uint4 | 4 | Raum-Index (1-8) |
| `VIS_FAVxWidget` | Uint5 | 5 | Widget-Slot (1-16) |

### Step 2.7 — Gesamter Parameter-Bedarf

```
Globale Parameter:        ~    56 Bytes
8 Stockwerke:             ~   192 Bytes
8 Räume (Channel-Header):~   224 Bytes
128 Widget-Slots:         ~ 4.352 Bytes
16 Favoriten:             ~    32 Bytes
─────────────────────────────────────
GESAMT:                   ~ 4.856 Bytes
```

→ Passt komfortabel in ESP32-Flash (MAIN_ParameterSize=12.279, Reserve über 7KB für andere Module)

### Step 2.8 — KO-Struktur

Jeder Widget-Slot bekommt einen **festen KO-Block mit 4 KOs**. Je nach Typ unterschiedlich belegt.
Nicht benötigte KOs im Block bleiben reserviert (kein GA zugewiesen).

| Widget-Typ | KO1 | KO2 | KO3 | KO4 |
|------------|-----|-----|-----|-----|
| Switch | Schalten (DPT 1.001) | Status (DPT 1.001) | — | — |
| Dimmer | Schalten (DPT 1.001) | Wert (DPT 5.001) | Status (DPT 5.001) | — |
| Jalousie | Auf/Ab (DPT 1.008) | Position (DPT 5.001) | Lamelle (DPT 5.001) | Stop (DPT 1.001) |
| Thermostat | Ist-Temp (DPT 9.001) | Soll-Temp (DPT 9.001) | Modus (DPT 20.102) | — |
| Szene | Szene (DPT 17.001) | — | — | — |
| RGB/RGBW | Schalten (DPT 1.001) | Farbe (DPT 232.600, 3 Byte RGB) | Helligkeit (DPT 5.001) | — |
| Wert | Wert (DPT wählbar) | — | — | — |
| Kamera | — (kein KO) | — | — | — |
| Taster | Senden (DPT wählbar) | — | — | — |
| Musik | Play/Pause (DPT 1.001) | Volume (DPT 5.001) | Next/Prev (DPT 1.001) | — |

**KO-Flags:**

| Rolle | Communication (C) | Read (R) | Write (W) | Transmit (T) | Update (U) |
|-------|:-:|:-:|:-:|:-:|:-:|
| Befehl-KO (z.B. Schalten, Auf/Ab, Senden) | ✓ | — | ✓ | ✓ | — |
| Status-KO (z.B. Status, Ist-Temp, Wert) | ✓ | ✓ | — | — | ✓ |
| Bidirektional (z.B. Soll-Temp, Position) | ✓ | ✓ | ✓ | ✓ | ✓ |

**Kapazität:**
- Max: 128 Slots × 4 KOs = **512 KOs** (theoretisch, Slots mit Typ=0/Kamera belegen keine KOs)
- Typisch: ~40-60 aktive Widgets × Ø2,5 effektive KOs = **~100-150 effektive KOs**
- **Innerhalb MAIN_MaxKoNumber=780** (mit Reserve für andere Module)

### Step 2.9 — ETS Dynamic UI (choose-Elemente)

- `VIS_VisibleFloors` steuert Sichtbarkeit der Stockwerk-Parameter
- `VIS_RxVisibleWidgets` steuert Widget-Slot-Sichtbarkeit pro Raum (1-16)
- `VIS_RxWzType` steuert typ-spezifische Parameter:
  - Kamera-URL nur bei Typ=Kamera
  - DPT-Auswahl (`VIS_RxWzDPT`) nur bei Typ=Wert/Taster
  - Grid-Position (Col/Row/Width/Height) bei allen Typen außer "Leer"
- Raum-Channels werden per `visAddRoom()`/`visRemoveRoom()` dynamisch sichtbar
- **Vorlage:** `OFM-FunctionBlocks/src/FunctionBlocks.share.xml` (Channel-Visibility-Pattern)

### Step 2.10 — ETS Tab-Anordnung

```
📋 Allgemein
  ├── Gerätename
  ├── Theme (Dark/Light/Auto)
  ├── Authentifizierung (aktivierbar + PIN + Max-Versuche + Lockout)
  ├── Dashboard aktivieren
  ├── Screensaver (Timeout + Modus)

📋 Stockwerke
  ├── Anzahl sichtbare Stockwerke
  ├── Stockwerk 1: Name, Sortierung
  ├── Stockwerk 2: Name, Sortierung
  ├── ... (bis 8)

📋 Raum 1 (ETS-Channel)
  ├── Name, Icon, Stockwerk-Zuordnung, Sortierung
  ├── Anzahl sichtbare Widgets (1-16)
  ├── Widget 1: Typ, Name, Icon, Spalte, Zeile, Breite, Höhe, Gewerk, [DPT]
  ├── Widget 2: ...
  ├── ... (bis 16)

📋 Raum 2 ... 📋 Raum 8 (je ein ETS-Channel)

📋 Favoriten
  ├── Favorit 1: Raum + Widget-Referenz
  ├── ... (bis 16)
```

### Step 2.11 — VisuServer.script.js

ETS-Hilfsskripte für komfortablere Bedienung:
- `visAddRoom()` — Nächsten Raum-Channel sichtbar machen
- `visRemoveRoom()` — Letzten Raum-Channel ausblenden
- `visAddWidget(roomIdx)` — Nächsten Widget-Slot im Raum aktivieren
- `visRemoveWidget(roomIdx)` — Letzten Widget-Slot deaktivieren
- **Vorlage:** `FunctionBlocks.script.js` (fcbAddChannel/fcbRemoveChannel Pattern)

---

## Phase 3: WebSocket-Server & REST API

### Step 3.1 — VisuWebSocket

**Endpoint:** `/openknx/visu/ws`
**Technologie:** ESP-IDF `httpd_ws_handler` (ab ESP-IDF v4.4+ verfügbar)
**Max Clients:** 4 gleichzeitig

> **Hinweis (H1):** Die aktuelle pioarduino-Platform muss ESP-IDF ≥4.4 liefern, damit `httpd_ws_handler` verfügbar ist. Im `setup()` wird `httpd_ws_handler` geprüft — falls nicht vorhanden, Fallback auf Polling via REST `/state` (degraded mode). Vor Implementierung ESP-IDF-Version in `platformio.ini` verifizieren.

**Server-Konfiguration:**
```cpp
httpd_config_t config = HTTPD_DEFAULT_CONFIG();
config.max_open_sockets = 12;  // Default=7, erhöht für 4 WS + statische Assets + REST
config.lru_purge_enable = true; // Älteste idle-Verbindung bei Knappheit schließen
```

**Binary-Protokoll (effizient auf ESP32):**

| Byte 0 (Type) | Richtung | Payload | Beschreibung |
|----------------|----------|---------|-------------|
| `0x01` | Server→Client | `ko_hi, ko_lo, dpt, value[1-4]` | KO-Update |
| `0x02` | Client→Server | `ko_hi, ko_lo, dpt, value[1-4]` | KO-Write (Befehl senden) |
| `0x03` | Server→Client | (siehe Full-State unten) | Initialer Full-State nach Auth |
| `0x10` | Server→Client | `config_version (uint32)` | Config-Version geändert → Client soll `/config` neu laden |
| `0xFF` | Beide | (leer) | Heartbeat/Ping |

**Authentifizierung:** Einheitlich über REST-Token (siehe Step 3.2). WebSocket-Verbindung sendet Session-Token als Query-Parameter: `ws://host/openknx/visu/ws?token=xxx`. Server validiert Token vor Upgrade. Kein separater binärer PIN-Austausch über WebSocket.

**Full-State (0x03):** Nach erfolgreicher Verbindung sendet der Server den kompletten KO-Cache als Folge von `0x01`-Frames, gefolgt von einem `0x03` als Abschlussmarker.

### Step 3.2 — REST API Endpoints

Registriert via `openknxWebUI.addHandler()`:

| Method | Endpoint | Response | Beschreibung |
|--------|----------|----------|-------------|
| GET | `/openknx/visu` | HTML (gzip) | SPA index.html |
| GET | `/openknx/visu/app.js` | JS (gzip) | Frontend-Logik |
| GET | `/openknx/visu/style.css` | CSS (gzip) | Styling |
| GET | `/openknx/visu/icons.svg` | SVG (gzip) | Icon-Sprite |
| GET | `/openknx/visu/config` | JSON (chunked) | Raum/Widget/Gewerk-Konfiguration mit DPT-Info |
| GET | `/openknx/visu/state` | JSON (chunked) | Aktuelle KO-Werte aller Widgets (Fallback ohne WS) |
| POST | `/openknx/visu/auth` | JSON | PIN-Validierung → Session-Token |

**Statische Assets:** Aggressive Cache-Header setzen (`Cache-Control: max-age=86400, immutable`) für `.js`, `.css`, `.svg` — reduziert parallele Verbindungen nach erstmaligem Laden.

**Config-Endpoint (`/config`):** JSON wird per **Chunked Transfer Encoding** (`httpd_resp_send_chunk()`) gestreamt — kein kompletter JSON-String im Heap. Raumweise serialisieren:
1. JSON-Header + floors + rooms-Array öffnen
2. Je Raum: Widgets als Array streamen → `httpd_resp_send_chunk()`
3. Favorites + Trades + JSON-Footer

**Auth-Endpoint (`/auth`):**
```
POST /openknx/visu/auth
Body: { "pin": "1234" }
→ 200 { "token": "a1b2c3...", "expires": 86400 }
→ 401 { "error": "invalid_pin", "remaining": 4 }
→ 429 { "error": "locked", "retry_after": 300 }
```
- **Session-Token:** 16 Byte random hex, 24h Gültigkeit, max. 4 aktive Tokens
- **Brute-Force-Schutz:** Nach `VIS_AuthMaxAttempts` Fehlversuchen → Lockout für `VIS_AuthLockoutMin` Minuten (IP-basiert, bis zu 4 IPs tracked)
- Token wird für REST-Requests als `Authorization: Bearer <token>` Header und für WebSocket als Query-Parameter verwendet

### Step 3.3 — Config-JSON Struktur

```json
{
  "apiVersion": 1,
  "configVersion": 42,
  "name": "Mein Haus",
  "theme": "dark",
  "auth": false,
  "dashboard": true,
  "screensaver": { "timeout": 10, "mode": "dim" },
  "floors": [
    { "id": 0, "name": "Erdgeschoss", "order": 0 },
    { "id": 1, "name": "Obergeschoss", "order": 1 }
  ],
  "rooms": [
    {
      "id": 0,
      "name": "Wohnzimmer",
      "icon": "living-room",
      "floor": 0,
      "order": 0
    }
  ],
  "widgets": [
    {
      "room": 0,
      "slot": 0,
      "type": "dimmer",
      "name": "Deckenleuchte",
      "icon": "ceiling-light",
      "col": 0,
      "row": 0,
      "w": 2,
      "h": 1,
      "trade": "light",
      "kos": [
        { "idx": 200, "dpt": "1.001", "role": "cmd" },
        { "idx": 201, "dpt": "5.001", "role": "cmd" },
        { "idx": 202, "dpt": "5.001", "role": "status" }
      ]
    },
    {
      "room": 0,
      "slot": 1,
      "type": "blind",
      "name": "Jalousie Süd",
      "icon": "blind",
      "col": 2,
      "row": 0,
      "w": 2,
      "h": 1,
      "trade": "shading",
      "kos": [
        { "idx": 204, "dpt": "1.008", "role": "cmd" },
        { "idx": 205, "dpt": "5.001", "role": "bidir" },
        { "idx": 206, "dpt": "5.001", "role": "bidir" },
        { "idx": 207, "dpt": "1.001", "role": "cmd" }
      ]
    }
  ],
  "favorites": [
    { "room": 0, "widget": 0 },
    { "room": 0, "widget": 1 }
  ],
  "trades": [
    { "id": "light", "name": "Licht", "icon": "light-bulb" },
    { "id": "shading", "name": "Beschattung", "icon": "blind" },
    { "id": "climate", "name": "Heizung/Klima", "icon": "thermostat" },
    { "id": "music", "name": "Musik", "icon": "speaker" },
    { "id": "scene", "name": "Szenen", "icon": "scene" },
    { "id": "camera", "name": "Kameras", "icon": "camera" },
    { "id": "energy", "name": "Energie", "icon": "energy" }
  ]
}
```

**Felder `apiVersion` und `configVersion`:**
- `apiVersion`: Integer, wird bei Breaking Changes am Protokoll/JSON-Format erhöht. Frontend prüft gegen erwartete Version.
- `configVersion`: Monoton steigender Counter (persistent in Flash). Wird bei jedem ETS-Download inkrementiert. WebSocket-Clients erhalten `0x10`-Frame bei Änderung und laden `/config` neu.

### Step 3.4 — KO-Wert-Cache

```cpp
struct WidgetKoCache {
    uint16_t koIndex;
    uint8_t  dpt;       // DPT-Major (1, 5, 7, 9, 12, 13, 14, 17, 20, 232)
    uint8_t  value[4];  // max 4 Bytes — ausreichend für alle unterstützten DPTs
};
// Max: 128 Slots × 4 KOs = 512 Einträge (nur aktive alloziert)
```

> **Hinweis:** `value[4]` reicht für alle unterstützten DPTs (max. 4 Bytes bei DPT 12/13/14). DPT 16.001 (14 Bytes) wird bewusst nicht unterstützt.

**Startup-Verhalten — KNX GroupValueRead Throttling:**
- Bei `setup()`: GroupValueRead-Anforderungen für alle konfigurierten Status-KOs (C+R+U Flags)
- **Gedrosselt:** Max. **10 GroupValueRead/Sekunde** (≈1 pro 100ms Timer-Intervall) um KNX-Bus-Flooding zu vermeiden
- Reihenfolge: Sichtbare Räume zuerst, dann restliche
- Bei `processInputKo()`: Wert im Cache aktualisieren + WebSocket-Broadcast an alle verbundenen Clients
- Bei WebSocket-Neuverbindung: Full-State aus Cache senden (Folge von `0x01`-Frames + `0x03`-Marker)

---

## Phase 4: WebUI Frontend (Vanilla JS SPA)

### Step 4.1 — HTML Shell (index.html)

```html
<!DOCTYPE html>
<html lang="de">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1,
        maximum-scale=1, user-scalable=no">
  <meta name="apple-mobile-web-app-capable" content="yes">
  <meta name="theme-color" content="#0d0d1a">
  <title>OpenKNX Visu</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <nav id="sidebar"></nav>
  <main id="content"></main>
  <nav id="tabbar"></nav>
  <script src="app.js"></script>
</body>
</html>
```

### Step 4.2 — CSS Design (style.css)

**Design-Philosophie — 3 Inspirationen:**

| Aspekt | Basalte Core | Loxone | Optimus Edge |
|--------|-------------|--------|-------------|
| Farben | Tiefes Dunkelblau-Schwarz (#0d0d1a → #1a1a2e) | Status-Farben (Grün=An, Grau=Aus) | Sanfte Farbverläufe |
| Tiles | Glasmorphism (backdrop-filter: blur) | Kachelbasiertes Grid | Große abgerundete Ecken (16px) |
| Akzente | Warmweiß (#f5f0e8), Gold (#c9a84c) | Blau=Klima, Orange=Warnung | Weiche Schatten |
| Touch | Minimal, elegant | Funktional | ≥56px Touch-Targets |
| Animation | Subtil | Kaum | 200-300ms ease-out Transitions |

**Grid-Layout für Raum-Ansicht — Proportionale Skalierung (K2-Fix):**

Das 6×4 Grid skaliert **proportional** auf allen Bildschirmgrößen via `vw`-Einheiten.
**Keine Spaltenänderung** — das Grid bleibt immer 6×4, wird nur kleiner/größer.

```css
:root {
  --grid-cols: 6;
  --grid-rows: 4;
  --grid-gap: clamp(4px, 0.8vw, 12px);
  --grid-pad: clamp(8px, 1.2vw, 16px);
}

.room-grid {
  display: grid;
  grid-template-columns: repeat(var(--grid-cols), 1fr);
  grid-template-rows: repeat(var(--grid-rows), 1fr);
  gap: var(--grid-gap);
  padding: var(--grid-pad);
  height: calc(100vh - 60px);   /* Sidebar/Header abziehen */
  width: calc(100vw - var(--sidebar-width, 0px));
  overflow: hidden;             /* Kein Scrolling im Grid */
}

.widget-tile {
  grid-column: var(--col) / span var(--w);
  grid-row: var(--row) / span var(--h);
  background: rgba(255, 255, 255, 0.05);
  backdrop-filter: blur(10px);
  border: 1px solid rgba(255, 255, 255, 0.08);
  border-radius: clamp(8px, 1.2vw, 16px);
  padding: clamp(8px, 1vw, 16px);
  transition: all 0.25s ease-out;
  min-width: 0;
  min-height: 0;
  overflow: hidden;
}

.widget-tile.active {
  background: rgba(201, 168, 76, 0.15);
  border-color: rgba(201, 168, 76, 0.3);
}
```

**Smartphone-Ansicht (<600px):** Sidebar wird zum Hamburger-Menü (Overlay), Grid füllt gesamte Breite. Tiles werden klein aber bleiben im 6×4-Raster — Icons und Text skalieren via `clamp()`. Bei extrem kleinen Screens wird horizontales Scrolling mit `overflow-x: auto` erlaubt.

**Sidebar-Verhalten:**

| Breakpoint | Sidebar | Grid-Breite |
|------------|---------|-------------|
| ≥1024px | Permanent sichtbar (200px) | `calc(100vw - 200px)` |
| 600-1023px | Eingeklappt (48px Icons) | `calc(100vw - 48px)` |
| <600px | Hamburger-Overlay | `100vw` |

**Gewerk-Seiten Layout:**

```css
.trade-page {
  padding: var(--grid-pad);
  overflow-y: auto;    /* Scrollbar auf Gewerk-Seiten erlaubt */
}

.trade-floor-section {
  margin-bottom: 24px;
}

.trade-floor-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 12px 0;
  border-bottom: 1px solid rgba(255, 255, 255, 0.1);
}

.trade-floor-header .bulk-action {
  /* "Alles aus"-Button pro Stockwerk */
  background: rgba(255, 60, 60, 0.2);
  border-radius: 8px;
  padding: 8px 16px;
  min-height: 44px;   /* Touch-Target Minimum */
}

.trade-widgets {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(140px, 1fr));
  gap: 12px;
  padding: 12px 0;
}
```

**Connection-Status Overlay (M2-Fix):**

```css
.connection-overlay {
  position: fixed;
  inset: 0;
  background: rgba(0, 0, 0, 0.85);
  display: flex;
  align-items: center;
  justify-content: center;
  z-index: 1000;
  /* Wird bei WebSocket-Disconnect angezeigt */
}

.connection-overlay .spinner { /* Reconnect-Animation */ }
.connection-overlay .message { color: #f5f0e8; }
```

**Loading/Splash Screen (M3-Fix):**

```css
.loading-screen {
  position: fixed;
  inset: 0;
  background: #0d0d1a;
  display: flex;
  align-items: center;
  justify-content: center;
  z-index: 2000;
  transition: opacity 0.5s ease-out;
}
/* Wird nach Config-Load + erstem Full-State ausgeblendet */
```

**Screensaver (M4-Fix):**

```css
.screensaver {
  position: fixed;
  inset: 0;
  z-index: 900;
  transition: opacity 1s ease-out;
  pointer-events: all;   /* Beliebiger Touch/Klick beendet Screensaver */
}

.screensaver--dim {
  background: rgba(0, 0, 0, 0.92);
}

.screensaver--clock {
  background: #000;
  /* Zentrierte Uhr, Datum, Außentemperatur (falls Wert-Widget vorhanden) */
}
```

### Step 4.3 — JavaScript SPA (app.js)

**Architektur (Vanilla JS, Ziel: ~60-80KB minified+gzipped):**

```
VisuApp
├── Router                    (Hash-basiert: #dashboard, #room/0, #trade/light)
├── State                     (Zentraler KO-Wert-Store + Config-Cache)
│   ├── configVersion         (Vergleich mit Server-Push 0x10)
│   └── apiVersion            (Kompatibilitätsprüfung)
│
├── WSClient                  (WebSocket mit Auto-Reconnect)
│   ├── connect(token?)
│   ├── send(type, payload)
│   ├── onMessage(handler)
│   ├── onDisconnect(handler) → zeigt ConnectionOverlay
│   └── reconnect()           (exponential backoff: 1s, 2s, 4s, 8s, max 30s)
│
├── Views
│   ├── LoadingView           (Splash: Logo + Spinner, bis Config+State geladen)
│   ├── AuthView              (PIN-Numpad, fullscreen, Fehlversuch-Counter)
│   ├── DashboardView         (Favoriten im Grid, Wetter/Status-Header)
│   ├── RoomListView          (Raum-Übersicht, nach Stockwerk gruppiert)
│   ├── RoomView              (6×4 Grid, feste Widget-Positionen)
│   ├── TradeView             (Gewerk-Übersichtsseite)
│   │   ├── TradeFloorSection (Stockwerk-Header + Widget-Liste)
│   │   └── TradeBulkActions  ("Alle aus/zu" pro Stockwerk)
│   └── SettingsView          (Theme-Umschaltung, optional)
│
├── Overlays
│   ├── ConnectionOverlay     (WS-Disconnect: "Verbindung unterbrochen..." + Spinner)
│   ├── ScreensaverOverlay    (nach VIS_ScreensaverMin Inaktivität → Dim/Uhr)
│   └── GridOverlapWarning    (Warnung bei überlappenden Tiles, nur in Debug/Preview)
│
└── WidgetFactory
    ├── SwitchWidget           (Tap-Toggle, Status-LED)
    ├── DimmerWidget           (Tap-Toggle + horizontaler Slider, %-Anzeige)
    ├── BlindWidget            (Auf/Ab/Stop, Position + Lamellen-Slider)
    ├── ThermostatWidget       (Ist/Soll-Anzeige, +/- Tasten, Modus-Icon)
    ├── SceneWidget            (Tap-Aktivierung, Icon)
    ├── RGBWidget              (Tap-Toggle, Farb-Popup mit HSV-Picker → DPT 232.600)
    ├── ValueWidget            (Nur Anzeige mit Einheit und Trend-Pfeil)
    ├── CameraWidget           (MJPEG <img> mit externer URL, Refresh)
    ├── ButtonWidget           (Tap-Send mit konfig. Wert, Bestätigung)
    └── MusicWidget            (Play/Pause, Lautstärke-Slider, Next/Prev)
```

**Startup-Sequenz:**
1. `LoadingView` anzeigen (Splash)
2. `GET /config` laden → Config parsen, `apiVersion` prüfen
3. Falls `auth: true` → `AuthView` anzeigen, PIN eingeben, Token erhalten
4. WebSocket verbinden (`?token=xxx` falls Auth)
5. Full-State empfangen (0x01-Folge + 0x03-Marker)
6. `LoadingView` ausblenden → Router startet (Dashboard oder erster Raum)

**Grid-Overlap-Erkennung (M1-Fix):**
Beim Rendern eines Raum-Grids wird ein Occupancy-Array (6×4 boolean) aufgebaut. Wenn ein Widget eine Zelle belegt, die bereits belegt ist, wird:
- Das überlappende Widget rot hervorgehoben (border: 2px solid red)
- Eine Warnung im `console.warn()` ausgegeben
- Optional: Toast-Benachrichtigung "Widget X überlappt mit Widget Y"
(Überlappung ist ein ETS-Konfigurationsfehler, nicht Runtime-kritisch)

**Screensaver-Logik (M4-Fix):**
- Timer startet bei jeder Touch/Mouse/Keyboard-Interaktion neu
- Nach `screensaver.timeout` Minuten Inaktivität → `ScreensaverOverlay` einblenden
- Beliebiger Touch/Klick beendet Screensaver (kein Durchklicken auf darunterliegende Widgets)
- Modus "dim": Screen abdunkeln (92% Schwarz-Overlay)
- Modus "clock": Schwarzer Hintergrund + große Uhrzeit + Datum

**CameraWidget — Mixed-Content-Hinweis (M6-Fix):**
> Kamera-URLs müssen über denselben Protokoll-Typ wie die Visu erreichbar sein. Bei HTTPS-Zugriff auf die Visu können HTTP-MJPEG-Streams vom Browser blockiert werden (Mixed Content). Empfehlung: Entweder Visu über HTTP betreiben oder Kamera-URLs ebenfalls über HTTPS konfigurieren. Kein Proxy durch ESP32 — zu wenig RAM für Video-Streaming.

**Browser-Kompatibilität:**
- Ziel: Chrome/Chromium ≥90 (Kiosk-Browser typisch), Safari ≥15, Firefox ≥90
- `backdrop-filter: blur()` → Fallback: solider dunkler Hintergrund für Browser ohne Support
- Touch-Events: `pointer-events` API bevorzugt (Mouse + Touch uniform)

**Touch-Interaktionen:**

| Geste | Aktion |
|-------|--------|
| Tap | Schalten / Aktivieren |
| Horizontal-Slide | Dimmer-Wert, Jalousie-Position |
| Long-Press (500ms) | Detail-Popup (RGB-Picker, Thermostat-Detail) |
| Swipe links/rechts | Raum wechseln |

**Gewerk-Seiten Interaktion:**

| Aktion | Effekt |
|--------|--------|
| Tap auf Stockwerk-"Alles aus" | Sendet Aus-Befehl an alle KO1 der Licht-Widgets im Stockwerk |
| Tap auf Stockwerk-"Alle zu" | Sendet Zu-Befehl an alle Jalousie-KOs im Stockwerk |
| Einzelne Widget-Controls | Toggle/Slider wie in Raum-Ansicht |

### Step 4.4 — SVG Icons (icons.svg als Sprite)

~30 monochrome Icons via `<symbol id="icon-xxx">` + `<use href="#icon-xxx">`:

**Gewerke:** light-bulb, blind, thermostat, speaker, scene, camera, energy
**Widgets:** ceiling-light, spot-light, floor-lamp, wall-light, roller-blind, awning, radiator, ac-unit, play, pause, volume, sensor, counter, cam-stream, push-button
**Räume:** living-room, kitchen, bathroom, bedroom, kids-room, hallway, office, garden, garage, basement, dining-room, terrace
**UI:** star (Favorit), gear (Settings), home, back, menu, power-off, chevron-left, chevron-right

---

## Phase 5: Integration in OAM-VisuServer

### Step 5.1 — main.cpp erweitern

```cpp
#include "VisuServerModule.h"
// ...
openknx.addModule(10, openknxVisuServerModule);
```

**Datei:** `OAM-VisuServer/src/main.cpp`

### Step 5.2 — Applikations-XML

Im VisuServer.xml (oder im neuen Applikations-XML):
```xml
<op:define prefix="VIS" ModuleType="15"
  share="../lib/OFM-VisuServer/src/VisuServer.share.xml"
  template="../lib/OFM-VisuServer/src/VisuServer.templ.xml"
  NumChannels="8"
  KoOffset="200"
  KoBlockSize="64">
  <op:verify File="../lib/OFM-VisuServer/library.json"
    ModuleVersion="%VIS_VerifyVersion%" />
</op:define>
```

> **Erklärung:** 8 Channels = 8 Räume. Jeder Raum-Channel hat KoBlockSize=64 (16 Widgets × 4 KOs pro Widget). KoOffset=200 → letztes KO = 200 + 8×64 = 712, passt in MAIN_MaxKoNumber=780.

### Step 5.3 — platformio.custom.ini

```ini
build_flags =
  ${env.build_flags}
  -D MODULE_VisuServer
```

(minimize.py ist bereits in extra_scripts konfiguriert)

---

## Relevante Dateien

### Neu zu erstellen

| Datei | Beschreibung | Vorlage |
|-------|-------------|---------|
| `OFM-VisuServer/library.json` | Modul-Metadata | `OFM-Network/library.json` |
| `OFM-VisuServer/src/VisuServerModule.h/.cpp` | Hauptmodul | `OFM-Network/src/NetworkModule.h/.cpp` |
| `OFM-VisuServer/src/VisuWebSocket.h/.cpp` | WebSocket-Handler | — |
| `OFM-VisuServer/src/VisuConfig.h/.cpp` | ETS → Runtime-Structs | — |
| `OFM-VisuServer/src/VisuServer.share.xml` | ETS-Parameter | `OFM-FunctionBlocks/src/FunctionBlocks.share.xml` |
| `OFM-VisuServer/src/VisuServer.templ.xml` | Widget-Template | `OFM-FunctionBlocks/src/FunctionBlocks.templ.xml` |
| `OFM-VisuServer/src/VisuServer.script.js` | ETS-Skripte | `FunctionBlocks.script.js` |
| `OFM-VisuServer/www/index.html` | SPA Shell | — |
| `OFM-VisuServer/www/app.js` | Frontend | — |
| `OFM-VisuServer/www/style.css` | Design | — |
| `OFM-VisuServer/www/icons.svg` | Icon-Sprite | — |

### Zu modifizieren

| Datei | Änderung |
|-------|---------|
| `OAM-VisuServer/src/main.cpp` | VisuServerModule registrieren |
| `OAM-VisuServer/platformio.custom.ini` | Build-Flag ergänzen |
| `OAM-VisuServer/include/versions.h` | MODULE_VisuServer_Version |
| `OAM-VisuServer/src/VisuServer.xml` | VIS-Modul-Block hinzufügen |

### Referenz

| Datei | Warum relevant |
|-------|---------------|
| `OFM-WebUI/src/WebUI.h` | addHandler(), addPage(), getHandler() API |
| `OFM-WebUI/scripts/pio/minimize.py` | www/ → Header-Komprimierung |
| `OFM-FunctionBlocks/src/FunctionBlocks.share.xml` | ETS Channel-Pattern |
| `OFM-FunctionBlocks/src/FunctionBlocks.script.js` | ETS Script-Pattern |
| `OGM-HardwareConfig/include/HardwareConfig/OpenKNX/REG1.h` | Hardware-Specs ESP32 |
| `OGM-Common/src/OpenKNX/Module.h` | Module-Interface |

---

## Verification

1. **Build:** PlatformIO `develop_REG1_LAN_TP_BASE` kompiliert erfolgreich
2. **ETS:** `OpenKNXproducer create` erzeugt gültige knxprod.h mit VIS_-Parametern und ≤512 KOs
3. **KO-Budget:** Prüfen dass KoOffset + NumChannels × KoBlockSize ≤ MAIN_MaxKoNumber (200 + 512 = 712 ≤ 780)
4. **Parameter-Budget:** MAIN_ParameterSize ausreichend (~4.856 VIS + andere Module ≤ 12.279 Bytes)
5. **REST Config:** `/openknx/visu/config` liefert JSON mit `apiVersion`, `configVersion`, Stockwerken, Räumen, Grid-Positionen, Gewerk-Zuordnungen, DPT-Info pro KO
6. **Chunked Transfer:** Config-JSON wird per Chunked Transfer Encoding gestreamt (kein Heap-Overflow bei 8 Räumen × 16 Widgets)
7. **Raum-Ansicht:** Tiles erscheinen exakt an per ETS definierten Grid-Positionen (Col/Row/Width/Height)
8. **Proportionale Skalierung:** Grid bleibt 6×4 auf allen Bildschirmgrößen, skaliert via vw-Einheiten
9. **Grid-Overlap:** Überlappende Tiles werden rot markiert + Console-Warnung
10. **Gewerk-Seite Licht:** Zeigt alle Widgets mit trade=light, korrekt nach Stockwerk gruppiert
11. **Gewerk-Seite Beschattung:** Zeigt alle Jalousie-Widgets, Bulk-"Alle zu" funktioniert
12. **Stockwerk-Bulk-Action:** "Alles Licht aus (EG)" schaltet alle Licht-KOs im EG ab
13. **Widget-Interaktion:** Toggle/Slider sendet KO-Wert, Status wird per WebSocket reflektiert
14. **KO-Flags:** Befehl-KOs haben C+W+T, Status-KOs haben C+R+U, Bidirektionale haben C+R+W+T+U
15. **Startup-Throttling:** GroupValueRead ≤10/sec, kein KNX-Bus-Flooding nach Neustart
16. **Multi-Client:** 2 Browser gleichzeitig — Änderung in einem wird in beiden angezeigt
17. **Socket-Kapazität:** max_open_sockets=12, 4 WS-Clients + statische Assets parallel möglich
18. **Kiosk-Test:** Touch-Gesten funktionieren, kein Scrolling auf Grid-Seite, Sidebar verhält sich je nach Breakpoint
19. **Dashboard:** Konfigurierte Favoriten werden korrekt angezeigt und bedienbar
20. **Auth:** PIN-Eingabe blockiert Zugriff, falscher PIN wird abgelehnt, Lockout nach Max-Versuchen
21. **Auth-Token:** WebSocket-Verbindung mit gültigem Token wird akzeptiert, ohne Token bei Auth=true abgelehnt
22. **Loading Screen:** Splash wird angezeigt bis Config+State geladen, dann smooth ausgeblendet
23. **Screensaver:** Nach konfiguriertem Timeout wird Dim/Uhr-Overlay angezeigt, Touch beendet es
24. **Disconnect-Overlay:** Bei WebSocket-Trennung erscheint Overlay mit Reconnect-Spinner
25. **Config-Update:** Bei configVersion-Änderung (0x10-Frame) lädt Client Config automatisch neu
26. **DPT-Korrektheit:** RGB-Widget sendet DPT 232.600 (3-Byte RGB), Wert-Widget nutzt konfigurierte DPT
27. **ESP-IDF WebSocket:** httpd_ws_handler verfügbar und funktional auf aktueller Platform-Version
28. **Flash:** www-Assets < 100KB gzipped im Build-Output

---

## Entscheidungen

| Entscheidung | Begründung |
|-------------|-----------|
| **Festes 6×4 Grid** (Basalte Core) | Tiles per ETS auf Spalte+Zeile platziert — kein dynamisches Auto-Layout, volle Kontrolle für den Integrator |
| **Proportionale vw-Skalierung** statt Spaltenumbruch | Grid bleibt immer 6×4, wird nur proportional kleiner/größer. Verhindert, dass ETS-definierte Positionen auf kleineren Screens kaputt gehen (K2-Fix) |
| **Gewerk-Zuordnung manuell per ETS** | Jedes Widget bekommt explizit ein Gewerk — erlaubt flexible Zuordnung (z.B. "Stehlampe Musik" unter Musik statt Licht) |
| **Räume als ETS-Channels** (nicht Widget-Slots) | 8 Raum-Channels statt 128/288 Einzel-Channels — handhabbar in ETS, performant in OpenKNXproducer (H6-Fix) |
| **8 Räume × 16 Widgets = 128 Slots** | 512 KOs max, passt in MAIN_MaxKoNumber=780 mit Reserve. ~4.9KB Parameter, passt in 12.279B mit Reserve (K1-Fix) |
| **4 KOs pro Widget-Block** | Statt 6 — ausreichend für alle Widget-Typen. RGB nutzt DPT 232.600 (3-Byte-Combined) statt Einzel-R/G/B/W. Musik nutzt Next/Prev statt Track-String |
| **DPT 16.001 nicht unterstützt** | Werte bis max 4 Bytes — `value[4]` im Cache reicht für DPT 1-14, 17, 20, 232. DPT 16 (14 Bytes) würde Cache verdreifachen (K3-Fix) |
| **Explizite DPT-Tabelle** | 9 unterstützte DPT-Familien, klar definiert. Frontend weiß per Config-JSON wie jeder KO-Wert zu decodieren ist (H2/H3-Fix) |
| **Einheitliche Token-Auth** über REST | PIN-Validierung nur per POST `/auth` → Session-Token. WS nutzt Token als Query-Parameter. Kein separater binärer PIN-Mechanismus über WebSocket (H4-Fix) |
| **Brute-Force-Schutz für PIN** | Max-Versuche + Lockout per ETS konfigurierbar. IP-basiertes Tracking (M5-Fix) |
| **GroupValueRead-Throttling** | Max 10/Sekunde bei Startup statt Bus-Flooding mit 100-500 Reads gleichzeitig (H5-Fix) |
| **max_open_sockets=12** | ESP-IDF Default=7 zu knapp für 4 WS + parallele Asset-Requests. LRU-Purge aktiviert (H7-Fix) |
| **Chunked Transfer Encoding** für Config-JSON | Raumweise Serialisierung statt kompletter JSON-String im Heap — vermeidet 30-80KB Heap-Allokation (K4-Fix) |
| **KO-Flags explizit definiert** | Befehl: C+W+T, Status: C+R+U, Bidirektional: C+R+W+T+U — verhindert fehlende Read-Flags oder ungewollte Status-Writes (K5-Fix) |
| **apiVersion + configVersion** in Config-JSON | API-Breaking-Changes erkennbar, Config-Änderungen per WebSocket-Push notifiziert (M7/M8-Fix) |
| **Loading Screen + Connection Overlay** | Sauberer Startup-Flow statt leerer Seite, klares Feedback bei WS-Disconnect mit Auto-Reconnect (M2/M3-Fix) |
| **Screensaver per ETS konfigurierbar** | Timeout + Modus (Dim/Uhr/Aus) als ETS-Parameter. Wichtig für Wand-Panels im Dauerbetrieb (M4-Fix) |
| **Grid-Overlap-Erkennung** im Frontend | Rot markierte Tiles + Console-Warnung bei Konfigurationsfehlern. Runtime-unkritisch, aber hilft beim Debugging (M1-Fix) |
| **Kamera nur externe MJPEG-URL** + Mixed-Content-Hinweis | Kein Proxy durch ESP32. Empfehlung: gleicher Protokolltyp (HTTP/HTTPS) wie Visu (M6-Fix) |
| **8 Stockwerke max** | Deckt Einfamilienhaus bis kleines Bürogebäude ab |
| **7 Gewerk-Seiten** | Licht, Beschattung, Heizung/Klima, Musik, Szenen, Kameras, Energie |
| **Stockwerk-Bulk-Aktionen** | Kernfeature für schnelles "alles aus/zu" pro Stockwerk auf Gewerk-Seiten |
| **Vanilla JS** statt Framework | ESP32 hat ~100KB Budget für Web-Assets nach gzip |
| **Binary WebSocket** für KO-Updates | Effizienter als JSON auf ESP32; JSON nur für initiale Config via REST |
| **OFM-WebUI als Basis** | Baut darauf auf, ersetzt es nicht |
| **Scope-Grenze** | Nur Visualisierung & Bedienung — kein Scheduling, keine Logik-Config in der WebUI |
