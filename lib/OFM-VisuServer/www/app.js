/* ============================================================
   OpenKNX VisuServer – app.js
   Vanilla ES6 SPA: Auth, WebSocket, Routing, Widget rendering
   ============================================================ */
"use strict";

// ---- Configuration defaults (overridden by /config response) ----
const DEFAULT_RECONNECT_MS = 3000;
const HEARTBEAT_TIMEOUT_MS = 25000;

// ---- Protocol byte codes (must match VisuWebSocket protocol) ----
const MSG_KO_UPDATE    = 0x01;
const MSG_KO_WRITE     = 0x02;
const MSG_FULL_STATE   = 0x03;
const MSG_CONFIG_VER   = 0x10;
const MSG_HEARTBEAT    = 0xFE;
const MSG_AUTH_TOKEN   = 0xFF;
const MSG_AUTH_FAIL    = 0xF0;

// ---- App state -----------------------------------------------
const App = {
  config:      null,   // from GET /config
  koValues:    {},     // koIndex -> Uint8Array raw value
  token:       localStorage.getItem("vis_token") || "",
  wsSocket:    null,
  wsReady:     false,
  route:       null,   // { view, floorIdx, roomIdx }
  saverTimer:  null,
  hbTimer:     null,
  saverMin:    0,
  reconnTimer: null,
  configVer:   -1,
};

const BASE_PATH = location.pathname.startsWith("/visu") ? "/visu" : "";

function apiUrl(path) {
  return BASE_PATH + path;
}

function wsUrl(path) {
  const proto = location.protocol === "https:" ? "wss" : "ws";
  return proto + "://" + location.host + BASE_PATH + path;
}

function roomIconIndex(name) {
  const names = [
    "living-room", "kitchen", "bathroom", "bedroom",
    "kids-room", "hallway", "office", "garden",
    "garage", "basement", "dining-room", "terrace",
  ];
  const idx = names.indexOf(name);
  return idx >= 0 ? idx : 0;
}

function widgetTypeValue(type) {
  const map = {
    empty: 0,
    switch: 1,
    dimmer: 2,
    blind: 3,
    thermostat: 4,
    scene: 5,
    rgb: 6,
    value: 7,
    camera: 8,
    button: 9,
    music: 10,
  };
  return typeof type === "string" ? (map[type] ?? 0) : (type ?? 0);
}

function dptIndexFromString(dpt) {
  const map = {
    "1.001": 0,
    "5.001": 1,
    "7.001": 2,
    "9.001": 3,
    "12.001": 4,
    "13.001": 5,
    "14.001": 6,
    "17.001": 7,
    "20.001": 8,
    "20.102": 8,
  };
  return typeof dpt === "string" ? (map[dpt] ?? 0) : (dpt ?? 0);
}

function normalizeConfig(raw) {
  const rooms = (raw.rooms || []).map(room => ({
    ...room,
    icon: roomIconIndex(room.icon),
    visibleWidgets: (room.widgets || []).length,
    widgets: (room.widgets || []).map(widget => ({
      ...widget,
      type: widgetTypeValue(widget.type),
      dpt: dptIndexFromString(widget.dpt),
      tileSize: widget.ts ?? 0,
      sortOrder: widget.so ?? 0,
      width: widget.w ?? 1,
      height: widget.h ?? 1,
      camUrl: widget.url || "",
    })),
  }));

  return {
    ...raw,
    rooms,
    global: {
      deviceName: raw.device || "OpenKNX Visu",
      floorCount: (raw.floors || []).length || 1,
      dashboard: (raw.favorites || []).length > 0,
      saverMin: raw.saver?.minutes || 0,
      configVer: raw.cfgVer || 0,
    },
  };
}

// ---- DOM refs -----------------------------------------------
const $ = id => document.getElementById(id);
const authOverlay  = $("auth-overlay");
const saverOverlay = $("saver-overlay");
const saverTime    = $("saver-time");
const saverDate    = $("saver-date");
const appEl        = $("app");
const headerTitle  = $("header-title");
const btnBack      = $("btn-back");
const btnHome      = $("btn-home");
const wsIndicator  = $("ws-indicator");
const floorNav     = $("floor-nav");
const views        = {
  floors: $("view-floors"),
  rooms:  $("view-rooms"),
  room:   $("view-room"),
  dash:   $("view-dash"),
};

// ---- Boot sequence ------------------------------------------
async function boot() {
  await loadConfig();
}

// ---- Auth ---------------------------------------------------
let pinBuffer = "";

function showAuth(message) {
  pinBuffer = "";
  updatePinDots();
  const errEl = $("auth-error");
  if (message) {
    errEl.textContent = message;
    errEl.classList.remove("hidden");
  } else {
    errEl.classList.add("hidden");
  }
  authOverlay.classList.remove("hidden");
}

function hideAuth() { authOverlay.classList.add("hidden"); }

function updatePinDots() {
  for (let i = 0; i < 4; i++) {
    const el = $("d" + i);
    el.classList.toggle("filled", i < pinBuffer.length);
  }
}

async function submitPin() {
  if (pinBuffer.length === 0) return;
  try {
    const resp = await fetch(apiUrl("/auth"), {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ pin: pinBuffer }),
    });
    const data = await resp.json();
    if (resp.ok && data.token) {
      App.token = data.token;
      localStorage.setItem("vis_token", data.token);
      hideAuth();
      await loadConfig();
    } else {
      showAuth(data.message || "Falscher PIN");
      pinBuffer = "";
      updatePinDots();
    }
  } catch (e) {
    showAuth("Fehler: " + e.message);
  }
}

document.querySelectorAll(".pin-key").forEach(btn => {
  btn.addEventListener("click", () => {
    const key = btn.dataset.key;
    if (key === "C") {
      pinBuffer = pinBuffer.slice(0, -1);
      updatePinDots();
    } else if (key === "OK") {
      submitPin();
    } else if (pinBuffer.length < 4) {
      pinBuffer += key;
      updatePinDots();
      if (pinBuffer.length === 4) submitPin();
    }
  });
});

// ---- Config loading ----------------------------------------
async function loadConfig() {
  try {
    const resp = await fetch(apiUrl("/config"), {
      headers: { Authorization: "Bearer " + App.token },
    });
    if (resp.status === 401) { App.token = ""; showAuth(); return; }
    if (!resp.ok) throw new Error("HTTP " + resp.status);
    App.config = normalizeConfig(await resp.json());
    App.saverMin = App.config.global?.saverMin || 0;
    App.configVer = App.config.global?.configVer || 0;
    initUI();
    connectWS();
    loadState();
  } catch (e) {
    console.error("Config load error:", e);
    setTimeout(loadConfig, 3000);
  }
}

async function loadState() {
  try {
    const resp = await fetch(apiUrl("/state"), {
      headers: { Authorization: "Bearer " + App.token },
    });
    if (!resp.ok) return;
    const state = await resp.json();
    for (const [k, v] of Object.entries(state.kos || {})) {
      App.koValues[parseInt(k)] = hexToBytes(v);
    }
    refreshAllWidgets();
  } catch (e) {
    console.warn("State load error:", e);
  }
}

// ---- WebSocket ---------------------------------------------
function connectWS() {
  clearTimeout(App.reconnTimer);
  if (App.wsSocket) {
    // Detach old handlers to prevent race condition (old onclose setting wsReady=false)
    App.wsSocket.onopen = null;
    App.wsSocket.onclose = null;
    App.wsSocket.onerror = null;
    App.wsSocket.onmessage = null;
    try { App.wsSocket.close(); } catch (_) {}
  }
  App.wsReady = false;
  const ws = new WebSocket(wsUrl("/ws"));
  ws.binaryType = "arraybuffer";
  App.wsSocket = ws;

  ws.onopen = () => {
    if (App.wsSocket !== ws) return; // stale socket
    setWsDot("on");
    App.wsReady = true;
    scheduleHbTimeout();
    // Send auth token
    const tokBytes = strToBytes(App.token);
    const msg = new Uint8Array(1 + tokBytes.length);
    msg[0] = MSG_AUTH_TOKEN;
    msg.set(tokBytes, 1);
    ws.send(msg);
  };

  ws.onclose = () => {
    if (App.wsSocket !== ws) return; // stale socket
    App.wsReady = false;
    setWsDot("off");
    clearTimeout(App.hbTimer);
    App.reconnTimer = setTimeout(connectWS, DEFAULT_RECONNECT_MS);
  };

  ws.onerror = () => {};

  ws.onmessage = evt => {
    if (App.wsSocket !== ws) return;
    scheduleHbTimeout();
    handleWsMessage(new Uint8Array(evt.data));
  };
}

function scheduleHbTimeout() {
  clearTimeout(App.hbTimer);
  App.hbTimer = setTimeout(() => {
    setWsDot("reconnect");
    if (App.wsSocket) App.wsSocket.close();
  }, HEARTBEAT_TIMEOUT_MS);
}

function handleWsMessage(data) {
  const type = data[0];
  if (type === MSG_HEARTBEAT) return;
  if (type === MSG_AUTH_FAIL) { App.token = ""; showAuth("Sitzung abgelaufen"); return; }
  if (type === MSG_CONFIG_VER) {
    const ver = (data[1] << 8) | data[2];
    if (ver !== App.configVer) loadConfig();
    return;
  }
  if (type === MSG_FULL_STATE) {
    loadConfig();
    loadState();
    return;
  }
  if (type === MSG_KO_UPDATE) {
    let off = 1;
    while (off + 4 < data.length) {
      const koIdx  = (data[off] << 8) | data[off + 1]; off += 2;
      const /* dptMajor */ _ = data[off++];
      const len    = data[off++];
      const value  = data.slice(off, off + len); off += len;
      App.koValues[koIdx] = value;
      updateWidgetByKo(koIdx);
    }
  }
}

function sendKoWrite(koIdx, dptMajor, valueBytes) {
  if (!App.wsReady) {
    console.warn("sendKoWrite: WS not ready, ko=" + koIdx);
    return;
  }
  // Protocol: [0x02][koIdxHi][koIdxLo][size][data...]
  // Backend derives dptMajor from its own config — no need to send it.
  const msg = new Uint8Array(4 + valueBytes.length);
  msg[0] = MSG_KO_WRITE;
  msg[1] = (koIdx >> 8) & 0xff;
  msg[2] = koIdx & 0xff;
  msg[3] = valueBytes.length;
  msg.set(valueBytes, 4);
  console.log("KO_WRITE ko=" + koIdx + " size=" + valueBytes.length + " data=[" + Array.from(valueBytes).join(",") + "]");
  App.wsSocket.send(msg);
}

function setWsDot(state) {
  wsIndicator.className = "ws-dot ws-dot--" + state;
}

// ---- UI init -----------------------------------------------
let _uiInitDone = false;

function initUI() {
  const cfg = App.config;
  buildFloorNav(cfg);
  // Start on dashboard if favorites exist, otherwise floors
  if (cfg.global?.dashboard) {
    navigate("dash");
  } else {
    navigate("floors");
  }
  resetSaverTimer();
  if (!_uiInitDone) {
    _uiInitDone = true;
    document.addEventListener("touchstart", onUserActivity, { passive: true });
    document.addEventListener("mousedown",  onUserActivity);
    btnBack.addEventListener("click", navBack);
    btnHome.addEventListener("click", () => navigate("floors"));
  }
}

function buildFloorNav(cfg) {
  const floorCount = cfg.global?.floorCount || 1;
  const floors = cfg.floors || [];
  // Only show nav if more than 1 floor
  if (floorCount <= 1) return;
  floorNav.innerHTML = "";
  for (let f = 0; f < floorCount; f++) {
    const fl = floors[f] || {};
    const btn = document.createElement("button");
    btn.className = "floor-tab";
    btn.textContent = fl.name || ("Etage " + (f + 1));
    btn.dataset.floorIdx = f;
    btn.addEventListener("click", () => navigate("rooms", { floorIdx: f }));
    floorNav.appendChild(btn);
  }
  floorNav.classList.remove("hidden");
  appEl.classList.add("has-floor-nav");
}

// ---- Router -----------------------------------------------
const history_stack = [];

function navigate(view, params) {
  history_stack.push({ view: App.route?.view, params: App.route?.params });
  App.route = { view, params: params || {} };
  renderView();
}

function navBack() {
  if (history_stack.length > 0) {
    const prev = history_stack.pop();
    App.route = { view: prev.view || "floors", params: prev.params || {} };
    renderView();
  }
}

function renderView() {
  const { view, params } = App.route;
  Object.values(views).forEach(v => v.classList.add("hidden"));
  btnBack.classList.toggle("hidden", history_stack.length <= 1);

  switch (view) {
    case "floors": renderFloors(params); break;
    case "rooms":  renderRooms(params);  break;
    case "room":   renderRoom(params);   break;
    case "dash":   renderDash(params);   break;
    default:       renderFloors({});
  }
}

// ---- View: Floors ------------------------------------------
function renderFloors(params) {
  const cfg = App.config;
  const floorCount = cfg.global?.floorCount || 1;
  const rooms = cfg.rooms || [];
  headerTitle.textContent = cfg.global?.deviceName || "OpenKNX Visu";

  // Group rooms by floor
  const byFloor = {};
  rooms.forEach(r => {
    const f = r.floor || 0;
    if (!byFloor[f]) byFloor[f] = [];
    byFloor[f].push({ room: r, idx: r.id });
  });

  const vEl = views.floors;
  vEl.innerHTML = "";

  if (floorCount <= 1) {
    // Show room cards directly
    const grid = document.createElement("div");
    grid.className = "tile-grid";
    const roomsOnFloor = byFloor[0] || [];
    roomsOnFloor.sort((a, b) => (a.room.order || 0) - (b.room.order || 0));
    roomsOnFloor.forEach(({ room, idx }) => {
      grid.appendChild(makeRoomCard(room, idx));
    });
    if (cfg.global?.dashboard) {
      grid.appendChild(makeDashCard());
    }
    vEl.appendChild(grid);
  } else {
    // Show floor cards
    const grid = document.createElement("div");
    grid.className = "tile-grid";
    for (let f = 0; f < floorCount; f++) {
      const floorData = (cfg.floors || [])[f] || {};
      const roomsHere = byFloor[f] || [];
      const card = document.createElement("div");
      card.className = "room-card span-w2";
      card.innerHTML = `
        <svg class="room-card__icon" viewBox="0 0 24 24"><use href="icons.svg#icon-floors"/></svg>
        <div class="room-card__name">${esc(floorData.name || "Etage " + (f+1))}</div>
        <div class="room-card__count">${roomsHere.length} Räume</div>
      `;
      card.addEventListener("click", () => navigate("rooms", { floorIdx: f }));
      grid.appendChild(card);
    }
    vEl.appendChild(grid);
  }
  vEl.classList.remove("hidden");
}

// ---- View: Rooms on a floor --------------------------------
function renderRooms(params) {
  const { floorIdx = 0 } = params;
  const cfg = App.config;
  const rooms = cfg.rooms || [];
  const floorData = (cfg.floors || [])[floorIdx] || {};
  headerTitle.textContent = floorData.name || ("Etage " + (floorIdx + 1));

  const roomsHere = rooms
    .map(r => ({ room: r, idx: r.id }))
    .filter(({ room }) => (room.floor || 0) === floorIdx)
    .sort((a, b) => (a.room.order || 0) - (b.room.order || 0));

  // Mark active floor tab
  document.querySelectorAll(".floor-tab").forEach(btn => {
    btn.classList.toggle("active", parseInt(btn.dataset.floorIdx) === floorIdx);
  });

  const vEl = views.rooms;
  vEl.innerHTML = "";
  const grid = document.createElement("div");
  grid.className = "tile-grid";
  roomsHere.forEach(({ room, idx }) => grid.appendChild(makeRoomCard(room, idx)));
  vEl.appendChild(grid);
  vEl.classList.remove("hidden");
}

function makeRoomCard(room, roomIdx) {
  const card = document.createElement("div");
  card.className = "room-card span-w2";
  const iconId = roomIconId(room.icon || 0);
  const activeWidgets = (room.widgets || []).filter(w => w.type !== 0);
  card.innerHTML = `
    <svg class="room-card__icon" viewBox="0 0 24 24"><use href="icons.svg#${iconId}"/></svg>
    <div class="room-card__name">${esc(room.name || "Raum " + (roomIdx + 1))}</div>
    <div class="room-card__count">${activeWidgets.length} Kacheln</div>
  `;
  card.addEventListener("click", () => navigate("room", { roomIdx }));
  return card;
}

function makeDashCard() {
  const card = document.createElement("div");
  card.className = "room-card span-w2";
  card.innerHTML = `
    <svg class="room-card__icon" viewBox="0 0 24 24"><use href="icons.svg#icon-dash"/></svg>
    <div class="room-card__name">Favoriten</div>
  `;
  card.addEventListener("click", () => navigate("dash", {}));
  return card;
}

// ---- View: Room widgets ------------------------------------
function renderRoom(params) {
  const { roomIdx = 0 } = params;
  const cfg = App.config;
  const room = (cfg.rooms || []).find(r => r.id === roomIdx);
  if (!room) { navigate("floors"); return; }
  headerTitle.textContent = room.name || ("Raum " + (roomIdx + 1));

  const vEl = views.room;
  vEl.innerHTML = "";
  const grid = document.createElement("div");
  grid.className = "room-grid";

  // Group widgets by section
  const sectionNames = {
    1: "Schalter", 2: "Beleuchtung", 3: "Beschattung",
    4: "Komfort", 5: "Szenen", 6: "Beleuchtung",
    7: "Werte", 8: "Kameras", 9: "Schalter", 10: "Musik"
  };
  const sectionOrder = [5, 1, 9, 2, 6, 10, 8, 3, 4, 7];
  const widgets = room.widgets || [];
  const visible = room.visibleWidgets || 14;
  const active = [];
  for (let w = 0; w < visible && w < widgets.length; w++) {
    const wz = widgets[w];
    if (wz.type === 0) continue;
    active.push({ wz, idx: w });
  }

  // Collect used section types in order
  const usedSections = [];
  const seen = new Set();
  for (const so of sectionOrder) {
    const name = sectionNames[so];
    if (seen.has(name)) continue;
    if (active.some(a => sectionNames[a.wz.type] === name)) {
      usedSections.push(name);
      seen.add(name);
    }
  }

  usedSections.forEach(secName => {
    // Section label
    const label = document.createElement("div");
    label.className = "section-label";
    label.textContent = secName;
    grid.appendChild(label);

    // Widgets in this section
    active.filter(a => sectionNames[a.wz.type] === secName)
      .sort((a, b) => (a.wz.sortOrder || 0) - (b.wz.sortOrder || 0))
      .forEach(a => {
        const tile = makeWidgetTile(a.wz, roomIdx, a.idx);
        grid.appendChild(tile);
      });
  });

  vEl.appendChild(grid);
  vEl.classList.remove("hidden");
}

// ---- View: Dashboard / Favorites ---------------------------
function getGreeting() {
  const h = new Date().getHours();
  if (h < 6) return "Gute Nacht";
  if (h < 12) return "Guten Morgen";
  if (h < 18) return "Guten Tag";
  return "Guten Abend";
}

function renderDash(params) {
  const cfg = App.config;
  const favs = cfg.favorites || [];
  headerTitle.textContent = cfg.global?.deviceName || "OpenKNX Visu";

  const vEl = views.dash;
  vEl.innerHTML = "";

  // Greeting section
  const greeting = document.createElement("div");
  greeting.className = "dash-greeting";
  const activeCount = favs.filter(f => {
    const room = (cfg.rooms || []).find(r => r.id === f.room);
    return room && (room.widgets || []).find(w => w.id === f.widget && w.type !== 0);
  }).length;
  greeting.innerHTML = `
    <div class="dash-greeting__hello">${esc(getGreeting())}</div>
    <div class="dash-greeting__sub">${activeCount} Favorit${activeCount !== 1 ? "en" : ""}</div>
  `;
  vEl.appendChild(greeting);

  // Section title
  const title = document.createElement("div");
  title.className = "dash-section-title";
  title.textContent = "Favoriten";
  vEl.appendChild(title);

  // Favorites as interactive widget tiles
  const grid = document.createElement("div");
  grid.className = "fav-grid";

  favs.forEach(fav => {
    const room = (cfg.rooms || []).find(r => r.id === fav.room);
    if (!room) return;
    const widgetIdx = (room.widgets || []).findIndex(w => w.id === fav.widget);
    if (widgetIdx < 0) return;
    const wz = room.widgets[widgetIdx];
    if (!wz || wz.type === 0) return;
    const tile = makeWidgetTile(wz, fav.room, widgetIdx);
    grid.appendChild(tile);
  });

  vEl.appendChild(grid);
  vEl.classList.remove("hidden");
}

// ---- Widget tile factory -----------------------------------
function makeWidgetTile(wz, roomIdx, widgetIdx) {
  // KO base index for this widget
  const koBase = koBaseFor(roomIdx, widgetIdx);

  const tile = document.createElement("div");
  const typeClass = widgetTypeClass(wz.type);
  tile.className = "widget-tile widget-tile--" + typeClass;
  // Large tiles: tileSize=2 forced large, tileSize=0 auto (large for thermostat/camera/music)
  const isLarge = wz.tileSize === 2 || (wz.tileSize === 0 && (wz.type === 4 || wz.type === 8 || wz.type === 10));
  if (isLarge) {
    tile.classList.add("widget-tile--lg");
  }
  // Wide tiles: tileSize=3 (1 row × 2 cols)
  if (wz.tileSize === 3) {
    tile.classList.add("widget-tile--wide");
  }
  tile.dataset.koBase = koBase;
  tile.dataset.wtype = wz.type;
  tile.dataset.dpt   = wz.dpt || 0;

  const iconId = widgetIconId(wz.icon || 0);
  tile.innerHTML = `
    <div class="widget-tile__header">
      <div class="widget-tile__icon-wrap">
        <svg class="widget-tile__icon" viewBox="0 0 24 24"><use href="icons.svg#${iconId}"/></svg>
      </div>
      <span class="widget-tile__name">${esc(wz.name || widgetTypeName(wz.type))}</span>
    </div>
    <div class="widget-tile__body"></div>
  `;

  const body = tile.querySelector(".widget-tile__body");

  // Register click handler ONCE — reads live state on each click
  bindWidgetAction(tile, wz, koBase);

  renderWidgetBody(tile, body, wz, koBase);
  return tile;
}

// Single click handler per tile — reads current state on each invocation
function bindWidgetAction(tile, wz, koBase) {
  const type = wz.type;

  switch (type) {
    case 1: // Switch
      tile.addEventListener("click", () => {
        const ko1 = App.koValues[koBase + 1] || new Uint8Array(1);
        const on = (ko1[0] & 1) === 1;
        sendKoWrite(koBase, 1, new Uint8Array([on ? 0 : 1]));
        // Optimistic: update local cache and UI immediately
        App.koValues[koBase + 1] = new Uint8Array([on ? 0 : 1]);
        updateWidgetByKo(koBase + 1);
      });
      break;
    case 2: // Dimmer — toggle on/off
      tile.addEventListener("click", () => {
        const ko0 = App.koValues[koBase] || new Uint8Array(1);
        const on = (ko0[0] & 1) === 1;
        sendKoWrite(koBase, 1, new Uint8Array([on ? 0 : 1]));
        App.koValues[koBase] = new Uint8Array([on ? 0 : 1]);
        updateWidgetByKo(koBase);
      });
      break;
    case 5: // Scene
      tile.addEventListener("click", () => {
        const ko0 = App.koValues[koBase] || new Uint8Array(1);
        sendKoWrite(koBase, 17, new Uint8Array([ko0[0]]));
      });
      break;
    case 6: // RGB — toggle on/off
      tile.addEventListener("click", () => {
        const ko0 = App.koValues[koBase] || new Uint8Array(1);
        const on = (ko0[0] & 1) === 1;
        sendKoWrite(koBase, 1, new Uint8Array([on ? 0 : 1]));
      });
      break;
    case 9: // Button — momentary
      tile.addEventListener("click", () => {
        sendKoWrite(koBase, 1, new Uint8Array([1]));
        setTimeout(() => sendKoWrite(koBase, 1, new Uint8Array([0])), 200);
      });
      break;
    case 10: // Music — toggle play/pause
      tile.addEventListener("click", () => {
        const ko0 = App.koValues[koBase] || new Uint8Array(1);
        const playing = (ko0[0] & 1) === 1;
        sendKoWrite(koBase, 1, new Uint8Array([playing ? 0 : 1]));
      });
      break;
    // Thermostat temp-btns are handled in renderWidgetBody (inside body, recreated)
    // Blind, Value, Camera have no tile-level click
  }
}

function renderWidgetBody(tile, body, wz, koBase) {
  const ko0 = App.koValues[koBase]     || new Uint8Array(1);
  const ko1 = App.koValues[koBase + 1] || new Uint8Array(1);
  const type = wz.type;

  switch (type) {
    case 1: { // Switch
      const on = (ko1[0] & 1) === 1;
      tile.classList.toggle("active", on);
      body.innerHTML = `
        <div class="toggle-track">
          <div class="toggle-thumb"></div>
        </div>
        <div class="widget-tile__value">${on ? "EIN" : "AUS"}</div>
      `;
      break;
    }
    case 2: { // Dimmer
      const level = ko1[0] || 0;
      const on = (ko0[0] & 1) === 1;
      tile.classList.toggle("active", on);
      body.innerHTML = `
        <div class="widget-tile__value">${level}<span class="widget-tile__unit">%</span></div>
        <div class="dim-track"><div class="dim-fill" style="width:${level}%"></div></div>
      `;
      break;
    }
    case 3: { // Blind
      const pos = ko1[0] || 0;
      body.innerHTML = `
        <div class="widget-tile__value">${pos}<span class="widget-tile__unit">%</span></div>
        <div class="blind-level">Lamelle: ${ko1[1] || ko0[0] || 0}%</div>
      `;
      break;
    }
    case 4: { // Thermostat
      const setpt = decodeFloat2Byte(ko0) || 0;
      const actual = decodeFloat2Byte(ko1) || 0;
      body.innerHTML = `
        <div class="thermo-ring">
          <div class="widget-tile__value">${actual.toFixed(1)}<span class="widget-tile__unit">°</span></div>
        </div>
        <div class="temp-set">Soll: ${setpt.toFixed(1)} °C</div>
        <div class="temp-btns">
          <button class="temp-btn" data-d="-0.5">&minus;</button>
          <button class="temp-btn" data-d="+0.5">+</button>
        </div>
      `;
      // Thermostat buttons need fresh handlers (they're inside body, which is replaced)
      tile.querySelectorAll(".temp-btn").forEach(btn => {
        btn.addEventListener("click", e => {
          e.stopPropagation();
          const delta = parseFloat(btn.dataset.d);
          const curSetpt = decodeFloat2Byte(App.koValues[koBase] || new Uint8Array(2)) || 0;
          sendKoWrite(koBase, 9, encodeFloat2Byte(curSetpt + delta));
        });
      });
      break;
    }
    case 5: { // Scene
      body.innerHTML = `<div class="widget-tile__value">Szene ${ko0[0] + 1}</div>`;
      break;
    }
    case 6: { // RGB
      const r = ko0[1] || 0, g = ko0[2] || 0, b = ko0[3] || 0;
      const on = (ko0[0] & 1) === 1;
      tile.classList.toggle("active", on);
      body.innerHTML = `
        <div style="display:flex;align-items:center;gap:8px">
          <div class="color-preview" style="background:rgb(${r},${g},${b})"></div>
          <div class="widget-tile__value">${on ? "EIN" : "AUS"}</div>
        </div>
      `;
      break;
    }
    case 7: { // Value display
      const val = decodeValue(ko0, wz.dpt);
      const unit = dptUnit(wz.dpt);
      body.innerHTML = `<div class="widget-tile__value">${val}<span class="widget-tile__unit">${unit}</span></div>`;
      break;
    }
    case 8: { // Camera
      const url = wz.camUrl || "";
      if (url) {
        body.innerHTML = `<img src="${esc(url)}" alt="${esc(wz.name || "Kamera")}" loading="lazy" />`;
      } else {
        body.innerHTML = `<div class="widget-tile__value">Keine URL</div>`;
      }
      break;
    }
    case 9: { // Button
      const on = (ko1[0] & 1) === 1;
      tile.classList.toggle("active", on);
      body.innerHTML = `<div class="widget-tile__value">${on ? "EIN" : "AUS"}</div>`;
      break;
    }
    case 10: { // Music
      const playing = (ko0[0] & 1) === 1;
      tile.classList.toggle("active", playing);
      const vol = ko1[0] || 0;
      body.innerHTML = `
        <div class="widget-tile__value">${playing ? "▶" : "⏸"}</div>
        <div class="widget-tile__unit">Vol: ${vol}%</div>
      `;
      break;
    }
    default:
      body.innerHTML = "";
  }
}

// ---- Live update by KO index --------------------------------
function updateWidgetByKo(koIdx) {
  // find all tiles whose koBase matches this range
  document.querySelectorAll(".widget-tile").forEach(tile => {
    const base = parseInt(tile.dataset.koBase);
    if (koIdx >= base && koIdx < base + 4) {
      const wType = parseInt(tile.dataset.wtype);
      const body = tile.querySelector(".widget-tile__body");
      const roomIdx = koToRoom(base);
      const widgetIdx = (base - koBaseFor(roomIdx, 0)) / 4;
      const room = (App.config?.rooms || [])[roomIdx];
      const wz = room ? (room.widgets || [])[widgetIdx] : null;
      if (wz) renderWidgetBody(tile, body, wz, base);
    }
  });
}

function refreshAllWidgets() {
  document.querySelectorAll(".widget-tile").forEach(tile => {
    const base = parseInt(tile.dataset.koBase);
    const body = tile.querySelector(".widget-tile__body");
    const roomIdx = koToRoom(base);
    const widgetIdx = (base - koBaseFor(roomIdx, 0)) / 4;
    const room = (App.config?.rooms || [])[roomIdx];
    const wz = room ? (room.widgets || [])[widgetIdx] : null;
    if (wz) renderWidgetBody(tile, body, wz, base);
  });
}

// ---- KO index helpers --------------------------------------
// Must match VisuConfig.h: VIS_KoBase=400 and KoOffset="400" in the XML.
// Change all three together if you renumber.
const KO_OFFSET     = 400;
const KO_ROOM_BLOCK = 64; // 16 widgets × 4 KOs

function koBaseFor(roomIdx, widgetIdx) {
  return KO_OFFSET + roomIdx * KO_ROOM_BLOCK + widgetIdx * 4;
}

function koToRoom(koBase) {
  return Math.floor((koBase - KO_OFFSET) / KO_ROOM_BLOCK);
}

// ---- Screensaver -------------------------------------------
function resetSaverTimer() {
  clearTimeout(App.saverTimer);
  if (App.saverMin <= 0) return;
  App.saverTimer = setTimeout(showSaver, App.saverMin * 60 * 1000);
}

function showSaver() {
  saverOverlay.classList.remove("hidden");
  updateSaverClock();
  App.saverTimer = setInterval(updateSaverClock, 1000);
  // Float position to avoid OLED burn-in
  moveSaverText();
}

function hideSaver() {
  saverOverlay.classList.add("hidden");
  clearInterval(App.saverTimer);
  resetSaverTimer();
}

function updateSaverClock() {
  const now = new Date();
  saverTime.textContent = now.toLocaleTimeString("de-DE", { hour: "2-digit", minute: "2-digit" });
  saverDate.textContent = now.toLocaleDateString("de-DE", { weekday: "long", day: "numeric", month: "long" });
}

let saverMoveTimer = null;
function moveSaverText() {
  const maxX = Math.max(0, window.innerWidth  - 280);
  const maxY = Math.max(0, window.innerHeight - 120);
  const x = Math.floor(Math.random() * maxX);
  const y = Math.floor(Math.random() * maxY);
  const el = saverOverlay.querySelector(".saver-content");
  if (el) { el.style.left = x + "px"; el.style.top = y + "px"; }
  saverMoveTimer = setTimeout(moveSaverText, 20000);
}

saverOverlay.addEventListener("click", hideSaver);

function onUserActivity() {
  if (!saverOverlay.classList.contains("hidden")) {
    hideSaver();
    return;
  }
  resetSaverTimer();
}

// ---- DPT encode/decode helpers -----------------------------
function decodeFloat2Byte(bytes) {
  if (!bytes || bytes.length < 2) return 0;
  const raw = (bytes[0] << 8) | bytes[1];
  const sign = (raw & 0x8000) ? -1 : 1;
  const exp  = (raw >> 11) & 0x0F;
  const mant = raw & 0x07FF;
  const mantSigned = (raw & 0x8000) ? (mant - 2048) : mant;
  return sign * 0.01 * mantSigned * Math.pow(2, exp);
}

function encodeFloat2Byte(val) {
  // DPT 9 encoding
  let v = Math.round(val * 100);
  let exp = 0;
  while (v > 2047 || v < -2048) { v >>= 1; exp++; }
  const sign = v < 0 ? 1 : 0;
  const mant = v & 0x07FF;
  const raw = (sign << 15) | (exp << 11) | mant;
  return new Uint8Array([(raw >> 8) & 0xff, raw & 0xff]);
}

function decodeValue(bytes, dpt) {
  if (!bytes || bytes.length === 0) return "–";
  switch (dpt) {
    case 0: return (bytes[0] & 1) ? "EIN" : "AUS";       // DPT 1
    case 1: return bytes[0];                              // DPT 5
    case 2: return (bytes[0] << 8) | bytes[1];           // DPT 7
    case 3: return decodeFloat2Byte(bytes).toFixed(1);   // DPT 9
    case 4: return ((bytes[0]<<24)|(bytes[1]<<16)|(bytes[2]<<8)|bytes[3]) >>> 0; // DPT 12
    case 5: return ((bytes[0]<<24)|(bytes[1]<<16)|(bytes[2]<<8)|bytes[3]) | 0;   // DPT 13
    case 6: {                                             // DPT 14
      const view = new DataView(bytes.buffer, bytes.byteOffset, 4);
      return view.getFloat32(0, false).toFixed(2);
    }
    case 7: return bytes[0] + 1;                         // DPT 17 scene
    case 8: return bytes[0];                             // DPT 20
    default: return bytes[0];
  }
}

function dptUnit(dpt) {
  const units = { 1: "%", 2: "", 3: "", 4: "", 5: "", 7: "", 8: "" };
  return units[dpt] || "";
}

// ---- Name / icon mappings ----------------------------------
function widgetTypeName(type) {
  return ["Leer","Schalter","Dimmer","Jalousie","Thermostat",
          "Szene","RGB","Wert","Kamera","Taster","Musik"][type] || "Widget";
}

function widgetTypeClass(type) {
  return ["empty","switch","dimmer","blind","thermo","scene","rgb","value","camera","button","music"][type] || "unknown";
}

function widgetIconId(iconIdx) {
  const icons = [
    "icon-light","icon-dimmer","icon-blind","icon-thermo","icon-scene",
    "icon-rgb","icon-sensor","icon-camera","icon-button","icon-music",
    "icon-fan","icon-power","icon-door","icon-window","icon-lock",
    "icon-bell","icon-plug","icon-star","icon-up","icon-down",
    "icon-left","icon-right","icon-sun","icon-moon","icon-cloud",
    "icon-fire","icon-drop","icon-leaf","icon-wifi","icon-info",
  ];
  return icons[iconIdx] || "icon-info";
}

function roomIconId(iconIdx) {
  const icons = [
    "icon-room-living","icon-room-kitchen","icon-room-bath","icon-room-bed",
    "icon-room-child","icon-room-hall","icon-room-office","icon-room-garden",
    "icon-room-garage","icon-room-cellar","icon-room-dining","icon-room-terrace",
  ];
  return icons[iconIdx] || "icon-room-living";
}

// ---- String utilities --------------------------------------
function esc(str) {
  return String(str)
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/"/g, "&quot;");
}

function hexToBytes(hex) {
  if (!hex || hex.length % 2 !== 0) return new Uint8Array(0);
  const bytes = new Uint8Array(hex.length / 2);
  for (let i = 0; i < bytes.length; i++) {
    bytes[i] = parseInt(hex.substr(i * 2, 2), 16);
  }
  return bytes;
}

function strToBytes(str) {
  return new TextEncoder().encode(str);
}

// ---- Start -------------------------------------------------
boot();
