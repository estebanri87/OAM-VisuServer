// VisuServer.script.js
// OpenKNX ETS Scripting for VisuServer module
// This script runs in OpenKNXproducer during ETS application generation.
// It validates widget configurations and generates proper ComObject text labels.

"use strict";

// Widget type constants (must match VisuWidgetType enum in VisuConfig.h)
const VWT_EMPTY     = 0;
const VWT_SWITCH    = 1;
const VWT_DIMMER    = 2;
const VWT_BLIND     = 3;
const VWT_THERMO    = 4;
const VWT_SCENE     = 5;
const VWT_RGB       = 6;
const VWT_VALUE     = 7;
const VWT_CAMERA    = 8;
const VWT_BUTTON    = 9;
const VWT_MUSIC     = 10;

const WIDGET_TYPE_NAMES = [
    "Leer", "Schalter", "Dimmer", "Jalousie", "Thermostat",
    "Szene", "RGB Licht", "Wert", "Kamera", "Taster", "Musik"
];

const WZ_KO_NAMES = [
    ["Befehl", "Status", "Helligkeit", "Farbtemp."],       // VWT_DIMMER
    ["Auf/Ab", "Position", "Lamelle", "Stopp"],             // VWT_BLIND
    ["Soll-Temp.", "Ist-Temp.", "Betriebsart", "Heizen"],  // VWT_THERMO
    ["Szene abruf.", "Szene speich.", "", ""],              // VWT_SCENE
    ["RGB Farbe", "Helligkeit", "Ein/Aus", ""],             // VWT_RGB
    ["Wert lesen", "Wert schreib.", "", ""],               // VWT_VALUE
    ["", "", "", ""],                                       // VWT_CAMERA (no KOs)
    ["Taste", "Status", "", ""],                            // VWT_BUTTON
    ["Play/Pause", "Lautstärke", "Quelle", "Titel"],       // VWT_MUSIC
];

// Called by OpenKNXproducer after loading all module parameters for each channel
function onChannelLoad(channel) {
    const roomName = channel.getParameter("RName") || ("Raum " + (channel.index + 1));
    
    for (let w = 0; w < 16; w++) {
        const hex = w.toString(16).toUpperCase();
        const wType = parseInt(channel.getParameter("W" + hex + "Type") || "0");
        const wName = channel.getParameter("W" + hex + "Name") || "";
        
        if (wType === VWT_EMPTY) {
            // Disable all 4 KOs for empty widget slots
            for (let k = 0; k < 4; k++) {
                const koIdx = w * 4 + k;
                const koId = koIdx.toString().padStart(3, "0");
                channel.setComObjectFlag(koId, "CommunicationFlag", false);
            }
        } else {
            const typeName = WIDGET_TYPE_NAMES[wType] || "Widget";
            const displayName = wName.length > 0 ? wName : typeName;
            
            // Disable KOs for types that don't use them
            const disableKo2 = (wType === VWT_SWITCH || wType === VWT_CAMERA || wType === VWT_BUTTON);
            const disableKo3 = (wType === VWT_SWITCH || wType === VWT_DIMMER || wType === VWT_CAMERA ||
                                 wType === VWT_BUTTON || wType === VWT_VALUE || wType === VWT_RGB);
            
            for (let k = 0; k < 4; k++) {
                const koIdx = w * 4 + k;
                const koIdStr = koIdx.toString().padStart(3, "0");
                
                let label;
                if (wType === VWT_SWITCH) {
                    label = k === 0 ? (roomName + " " + displayName + " Befehl")
                                    : (roomName + " " + displayName + " Status");
                } else if (wType >= VWT_DIMMER && wType <= VWT_MUSIC && wType !== VWT_CAMERA) {
                    const typeIdx = wType - VWT_DIMMER;
                    const koNames = WZ_KO_NAMES[typeIdx] || ["KO" + k, "", "", ""];
                    label = koNames[k] ? (roomName + " " + displayName + " " + koNames[k]) : "";
                } else {
                    label = roomName + " " + displayName + " KO" + k;
                }
                
                // Disable unused KOs
                const disable = (k === 2 && disableKo2) || (k === 3 && disableKo3) ||
                                (wType === VWT_CAMERA);
                channel.setComObjectFlag(koIdStr, "CommunicationFlag", !disable);
                if (label) {
                    channel.setComObjectText(koIdStr, label);
                }
            }
        }
    }
}
