# OGM-HardwareConfig

OpenKNX Hardware Definition Headers

## Regeln

jede Geräte-Pindefinition wird von einem

```
#ifdef DEVICE_<DeviceID-Macro>
    #define DEVICE_ID "<DeviceID>"
    #define DEVICE_NAME "<DeviceName>"
    
    // Pindefinitionen
    // #define PROG_LED_PIN 7
    // etc. ...
#endif
```
eingeschlossen.


`<DeviceID>` darf aus a-z, A-Z, 0-9, _ und - bestehen. OpenKNX-Ready und andere HW wird ein jeweilig einheitlichen Präfix vorangestellt.  
Maximallänge: am besten nicht länger als 16 Zeichen
Beispiel: `PiPico-BCU-Connector` (OpenKNX) oder `SMARTMF-Modbus-RTU-3BE` (OpenKNX-Ready, Präfix SMARTMF)


`<DeviceID-Macro>` wird aus der `<DeviceID>` gebildet, wobei alle Kleinbuchstaben durch Großbuchstaben und - durch _ ersetzt werden.  
Beispiel: `SMARTMF-Modbus-RTU-3BE` wird zu `SMARTMF_MODBUS_RTU_3BE` und somit zu `DEVICE_SMARTMF_MODBUS_RTU_3BE`


`<DeviceName>` darf aus allen Asciizeichen bestehen. Möglichst keine Klammern verwenden.
Maximallänge: am besten nicht länger als 32 Zeichen

## Wichtig:
`<DeviceID>` und `<DeviceName>` müssen exakt so lauten, wir auch in der Geräteliste im Wiki definiert.  
https://openknx.atlassian.net/wiki/spaces/OPENKNXDEV/database/131098?atl_f=PAGETREE


## Work-in-progress !
Regeln hinterfragen, ggf. abgestimmte Änderungen hier einpflegen.

