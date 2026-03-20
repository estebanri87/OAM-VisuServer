#pragma once


#define paramDelay(time) (uint32_t)( \
            (time & 0xC000) == 0xC000 ? (time & 0x3FFF) * 100 : \
            (time & 0xC000) == 0x0000 ? (time & 0x3FFF) * 1000 : \
            (time & 0xC000) == 0x4000 ? (time & 0x3FFF) * 60000 : \
            (time & 0xC000) == 0x8000 ? ((time & 0x3FFF) > 1000 ? 3600000 : \
                                         (time & 0x3FFF) * 3600000 ) : 0 )
                                             
#define ETS_ModuleId_NONE 0
#define ETS_ModuleId_BASE 1
#define ETS_ModuleId_NET 2
#define ETS_ModuleId_UCT 3
#define ETS_ModuleId_VIS 4
#define ETS_ModuleId_LOG 5
#define ETS_ModuleId_FCB 6
#define MAIN_FirmwareName "Visu Server (Beta)"
#define MAIN_OpenKnxId 0xAF
#define MAIN_ApplicationNumber 42
#define MAIN_ApplicationVersion 1
#define MAIN_FirmwareRevision 0
#define MAIN_ApplicationEncoding iso-8859-15
#define MAIN_ParameterSize 14037
#define MAIN_MaxKoNumber 847
#define MAIN_OrderNumber "OpenKNX-SR-VIS"
#define BASE_ModuleVersion 23
#define NET_ModuleVersion 5
#define UCT_ModuleVersion 5
#define VIS_ModuleVersion 1
#define LOG_ModuleVersion 64
#define FCB_ModuleVersion 9
// Parameter with single occurrence


#define BASE_StartupDelayBase                     0      // 2 Bits, Bit 7-6
#define     BASE_StartupDelayBaseMask 0xC0
#define     BASE_StartupDelayBaseShift 6
#define BASE_StartupDelayTime                     0      // 14 Bits, Bit 13-0
#define     BASE_StartupDelayTimeMask 0x3FFF
#define     BASE_StartupDelayTimeShift 0
#define BASE_HeartbeatDelayBase                   2      // 2 Bits, Bit 7-6
#define     BASE_HeartbeatDelayBaseMask 0xC0
#define     BASE_HeartbeatDelayBaseShift 6
#define BASE_HeartbeatDelayTime                   2      // 14 Bits, Bit 13-0
#define     BASE_HeartbeatDelayTimeMask 0x3FFF
#define     BASE_HeartbeatDelayTimeShift 0
#define BASE_Timezone                             4      // 5 Bits, Bit 7-3
#define     BASE_TimezoneMask 0xF8
#define     BASE_TimezoneShift 3
#define BASE_CombinedTimeDate                     4      // 1 Bit, Bit 2
#define     BASE_CombinedTimeDateMask 0x04
#define     BASE_CombinedTimeDateShift 2
#define BASE_SummertimeAll                        4      // 2 Bits, Bit 1-0
#define     BASE_SummertimeAllMask 0x03
#define     BASE_SummertimeAllShift 0
#define BASE_SummertimeDE                         4      // 2 Bits, Bit 1-0
#define     BASE_SummertimeDEMask 0x03
#define     BASE_SummertimeDEShift 0
#define BASE_SummertimeWorld                      4      // 2 Bits, Bit 1-0
#define     BASE_SummertimeWorldMask 0x03
#define     BASE_SummertimeWorldShift 0
#define BASE_SummertimeKO                         4      // 2 Bits, Bit 1-0
#define     BASE_SummertimeKOMask 0x03
#define     BASE_SummertimeKOShift 0
#define BASE_TimezoneCustom                       5      // char*, 63 Byte
#define     BASE_TimezoneCustomLength 63
#define BASE_Latitude                            69      // float
#define BASE_Longitude                           73      // float
#define BASE_Diagnose                            78      // 1 Bit, Bit 7
#define     BASE_DiagnoseMask 0x80
#define     BASE_DiagnoseShift 7
#define BASE_Watchdog                            78      // 1 Bit, Bit 6
#define     BASE_WatchdogMask 0x40
#define     BASE_WatchdogShift 6
#define BASE_ReadTimeDate                        78      // 1 Bit, Bit 5
#define     BASE_ReadTimeDateMask 0x20
#define     BASE_ReadTimeDateShift 5
#define BASE_HeartbeatExtended                   78      // 1 Bit, Bit 4
#define     BASE_HeartbeatExtendedMask 0x10
#define     BASE_HeartbeatExtendedShift 4
#define BASE_InternalTime                        78      // 1 Bit, Bit 3
#define     BASE_InternalTimeMask 0x08
#define     BASE_InternalTimeShift 3
#define BASE_ManualSave                          78      // 3 Bits, Bit 2-0
#define     BASE_ManualSaveMask 0x07
#define     BASE_ManualSaveShift 0
#define BASE_PeriodicSave                        79      // 8 Bits, Bit 7-0
#define BASE_Info1LedFunc                        80      // 16 Bits, Bit 15-0
#define BASE_Info2LedFunc                        82      // 16 Bits, Bit 15-0
#define BASE_Info3LedFunc                        84      // 16 Bits, Bit 15-0
#define BASE_DefaultLedFunc                      86      // 1 Bit, Bit 7
#define     BASE_DefaultLedFuncMask 0x80
#define     BASE_DefaultLedFuncShift 7
#define BASE_Dummy                               109      // uint8_t
#define BASE_ModuleEnabled_NET                   110      // 1 Bit, Bit 6
#define     BASE_ModuleEnabled_NETMask 0x40
#define     BASE_ModuleEnabled_NETShift 6
#define BASE_ModuleEnabled_UCT                   110      // 1 Bit, Bit 5
#define     BASE_ModuleEnabled_UCTMask 0x20
#define     BASE_ModuleEnabled_UCTShift 5
#define BASE_ModuleEnabled_VIS                   110      // 1 Bit, Bit 4
#define     BASE_ModuleEnabled_VISMask 0x10
#define     BASE_ModuleEnabled_VISShift 4
#define BASE_ModuleEnabled_LOG                   110      // 1 Bit, Bit 3
#define     BASE_ModuleEnabled_LOGMask 0x08
#define     BASE_ModuleEnabled_LOGShift 3
#define BASE_ModuleEnabled_FCB                   110      // 1 Bit, Bit 2
#define     BASE_ModuleEnabled_FCBMask 0x04
#define     BASE_ModuleEnabled_FCBShift 2

// Zeitbasis
#define ParamBASE_StartupDelayBase                    ((knx.paramByte(BASE_StartupDelayBase) & BASE_StartupDelayBaseMask) >> BASE_StartupDelayBaseShift)
// Zeit
#define ParamBASE_StartupDelayTime                    (knx.paramWord(BASE_StartupDelayTime) & BASE_StartupDelayTimeMask)
// Zeit (in Millisekunden)
#define ParamBASE_StartupDelayTimeMS                  (paramDelay(knx.paramWord(BASE_StartupDelayTime)))
// Zeitbasis
#define ParamBASE_HeartbeatDelayBase                  ((knx.paramByte(BASE_HeartbeatDelayBase) & BASE_HeartbeatDelayBaseMask) >> BASE_HeartbeatDelayBaseShift)
// Zeit
#define ParamBASE_HeartbeatDelayTime                  (knx.paramWord(BASE_HeartbeatDelayTime) & BASE_HeartbeatDelayTimeMask)
// Zeit (in Millisekunden)
#define ParamBASE_HeartbeatDelayTimeMS                (paramDelay(knx.paramWord(BASE_HeartbeatDelayTime)))
// Zeitzone
#define ParamBASE_Timezone                            ((knx.paramByte(BASE_Timezone) & BASE_TimezoneMask) >> BASE_TimezoneShift)
// Empfangen über
#define ParamBASE_CombinedTimeDate                    ((bool)(knx.paramByte(BASE_CombinedTimeDate) & BASE_CombinedTimeDateMask))
// Sommerzeit ermitteln durch
#define ParamBASE_SummertimeAll                       (knx.paramByte(BASE_SummertimeAll) & BASE_SummertimeAllMask)
// Sommerzeit ermitteln durch
#define ParamBASE_SummertimeDE                        (knx.paramByte(BASE_SummertimeDE) & BASE_SummertimeDEMask)
// Sommerzeit ermitteln durch
#define ParamBASE_SummertimeWorld                     (knx.paramByte(BASE_SummertimeWorld) & BASE_SummertimeWorldMask)
// Sommerzeit ermitteln durch
#define ParamBASE_SummertimeKO                        (knx.paramByte(BASE_SummertimeKO) & BASE_SummertimeKOMask)
// POSIX TZ-String
#define ParamBASE_TimezoneCustom                      (knx.paramData(BASE_TimezoneCustom))
#define ParamBASE_TimezoneCustomStr                   (knx.paramString(BASE_TimezoneCustom, BASE_TimezoneCustomLength))
// Breitengrad
#define ParamBASE_Latitude                            (knx.paramFloat(BASE_Latitude, Float_Enc_IEEE754Single))
// Längengrad
#define ParamBASE_Longitude                           (knx.paramFloat(BASE_Longitude, Float_Enc_IEEE754Single))
// Diagnoseobjekt anzeigen
#define ParamBASE_Diagnose                            ((bool)(knx.paramByte(BASE_Diagnose) & BASE_DiagnoseMask))
// Watchdog aktivieren
#define ParamBASE_Watchdog                            ((bool)(knx.paramByte(BASE_Watchdog) & BASE_WatchdogMask))
// Bei Neustart vom Bus lesen
#define ParamBASE_ReadTimeDate                        ((bool)(knx.paramByte(BASE_ReadTimeDate) & BASE_ReadTimeDateMask))
// Erweitertes "In Betrieb"
#define ParamBASE_HeartbeatExtended                   ((bool)(knx.paramByte(BASE_HeartbeatExtended) & BASE_HeartbeatExtendedMask))
// InternalTime
#define ParamBASE_InternalTime                        ((bool)(knx.paramByte(BASE_InternalTime) & BASE_InternalTimeMask))
// Manuelles speichern
#define ParamBASE_ManualSave                          (knx.paramByte(BASE_ManualSave) & BASE_ManualSaveMask)
// Zyklisches speichern
#define ParamBASE_PeriodicSave                        (knx.paramByte(BASE_PeriodicSave))
// Info1
#define ParamBASE_Info1LedFunc                        (knx.paramWord(BASE_Info1LedFunc))
// Info2
#define ParamBASE_Info2LedFunc                        (knx.paramWord(BASE_Info2LedFunc))
// Info3
#define ParamBASE_Info3LedFunc                        (knx.paramWord(BASE_Info3LedFunc))
// 
#define ParamBASE_DefaultLedFunc                      ((bool)(knx.paramByte(BASE_DefaultLedFunc) & BASE_DefaultLedFuncMask))
// 
#define ParamBASE_Dummy                               (knx.paramByte(BASE_Dummy))
// NET
#define ParamBASE_ModuleEnabled_NET                   ((bool)(knx.paramByte(BASE_ModuleEnabled_NET) & BASE_ModuleEnabled_NETMask))
// UCT
#define ParamBASE_ModuleEnabled_UCT                   ((bool)(knx.paramByte(BASE_ModuleEnabled_UCT) & BASE_ModuleEnabled_UCTMask))
// VIS
#define ParamBASE_ModuleEnabled_VIS                   ((bool)(knx.paramByte(BASE_ModuleEnabled_VIS) & BASE_ModuleEnabled_VISMask))
// LOG
#define ParamBASE_ModuleEnabled_LOG                   ((bool)(knx.paramByte(BASE_ModuleEnabled_LOG) & BASE_ModuleEnabled_LOGMask))
// FCB
#define ParamBASE_ModuleEnabled_FCB                   ((bool)(knx.paramByte(BASE_ModuleEnabled_FCB) & BASE_ModuleEnabled_FCBMask))

#define BASE_KoHeartbeat 1
#define BASE_KoTime 2
#define BASE_KoDate 3
#define BASE_KoDateTime 4
#define BASE_KoIsSummertime 5
#define BASE_KoManualSave 6
#define BASE_KoDiagnose 7

// In Betrieb
#define KoBASE_Heartbeat                           (knx.getGroupObject(BASE_KoHeartbeat))
// Uhrzeit
#define KoBASE_Time                                (knx.getGroupObject(BASE_KoTime))
// Datum
#define KoBASE_Date                                (knx.getGroupObject(BASE_KoDate))
// Uhrzeit/Datum
#define KoBASE_DateTime                            (knx.getGroupObject(BASE_KoDateTime))
// Sommerzeit aktiv
#define KoBASE_IsSummertime                        (knx.getGroupObject(BASE_KoIsSummertime))
// Speichern
#define KoBASE_ManualSave                          (knx.getGroupObject(BASE_KoManualSave))
// Diagnose
#define KoBASE_Diagnose                            (knx.getGroupObject(BASE_KoDiagnose))

#define NET_HostAddress                         114      // IP address, 4 Byte
#define NET_SubnetMask                          118      // IP address, 4 Byte
#define NET_GatewayAddress                      122      // IP address, 4 Byte
#define NET_NameserverAddress                   126      // IP address, 4 Byte
#define NET_CustomHostname                      130      // 1 Bit, Bit 7
#define     NET_CustomHostnameMask 0x80
#define     NET_CustomHostnameShift 7
#define NET_StaticIP                            130      // 1 Bit, Bit 6
#define     NET_StaticIPMask 0x40
#define     NET_StaticIPShift 6
#define NET_mDNS                                131      // 1 Bit, Bit 7
#define     NET_mDNSMask 0x80
#define     NET_mDNSShift 7
#define NET_HTTP                                131      // 1 Bit, Bit 6
#define     NET_HTTPMask 0x40
#define     NET_HTTPShift 6
#define NET_NTP                                 131      // 1 Bit, Bit 5
#define     NET_NTPMask 0x20
#define     NET_NTPShift 5
#define NET_OTAUpdate                           131      // 2 Bits, Bit 4-3
#define     NET_OTAUpdateMask 0x18
#define     NET_OTAUpdateShift 3
#define NET_HostName                            132      // char*, 24 Byte
#define     NET_HostNameLength 24
#define NET_LanMode                             173      // 4 Bits, Bit 7-4
#define     NET_LanModeMask 0xF0
#define     NET_LanModeShift 4
#define NET_NTPServer                           174      // char*, 50 Byte
#define     NET_NTPServerLength 50

// IP-Adresse
#define ParamNET_HostAddress                         (knx.paramInt(NET_HostAddress))
// Subnetzsmaske
#define ParamNET_SubnetMask                          (knx.paramInt(NET_SubnetMask))
// Standardgateway
#define ParamNET_GatewayAddress                      (knx.paramInt(NET_GatewayAddress))
// Nameserver
#define ParamNET_NameserverAddress                   (knx.paramInt(NET_NameserverAddress))
// Hostname anpassen
#define ParamNET_CustomHostname                      ((bool)(knx.paramByte(NET_CustomHostname) & NET_CustomHostnameMask))
// DHCP
#define ParamNET_StaticIP                            ((bool)(knx.paramByte(NET_StaticIP) & NET_StaticIPMask))
// mDNS
#define ParamNET_mDNS                                ((bool)(knx.paramByte(NET_mDNS) & NET_mDNSMask))
// Weberver
#define ParamNET_HTTP                                ((bool)(knx.paramByte(NET_HTTP) & NET_HTTPMask))
// NTP-Client
#define ParamNET_NTP                                 ((bool)(knx.paramByte(NET_NTP) & NET_NTPMask))
// OTA-Update
#define ParamNET_OTAUpdate                           ((knx.paramByte(NET_OTAUpdate) & NET_OTAUpdateMask) >> NET_OTAUpdateShift)
// Hostname
#define ParamNET_HostName                            (knx.paramData(NET_HostName))
#define ParamNET_HostNameStr                         (knx.paramString(NET_HostName, NET_HostNameLength))
// LAN-Modus
#define ParamNET_LanMode                             ((knx.paramByte(NET_LanMode) & NET_LanModeMask) >> NET_LanModeShift)
// Zeitserver
#define ParamNET_NTPServer                           (knx.paramData(NET_NTPServer))
#define ParamNET_NTPServerStr                        (knx.paramString(NET_NTPServer, NET_NTPServerLength))



#define VIS_VISDeviceName                       225      // char*, 20 Byte
#define     VIS_VISDeviceNameLength 20
#define VIS_VISAuthEnabled                      245      // 1 Bit, Bit 7
#define     VIS_VISAuthEnabledMask 0x80
#define     VIS_VISAuthEnabledShift 7
#define VIS_VISDashboardEnabled                 245      // 1 Bit, Bit 6
#define     VIS_VISDashboardEnabledMask 0x40
#define     VIS_VISDashboardEnabledShift 6
#define VIS_VISTheme                            245      // 2 Bits, Bit 5-4
#define     VIS_VISThemeMask 0x30
#define     VIS_VISThemeShift 4
#define VIS_VISScreensaverMode                  245      // 2 Bits, Bit 3-2
#define     VIS_VISScreensaverModeMask 0x0C
#define     VIS_VISScreensaverModeShift 2
#define VIS_VISAuthPIN                          246      // uint32_t
#define VIS_VISAuthMaxAttempts                  250      // uint8_t
#define VIS_VISAuthLockoutMin                   251      // uint8_t
#define VIS_VISHeartbeatSec                     252      // uint8_t
#define VIS_VISVisibleFloors                    253      // uint8_t
#define VIS_VISScreensaverMin                   254      // uint8_t
#define VIS_VISVisibleRooms                     455      // uint8_t
#define VIS_VISFL0Name                          255      // char*, 20 Byte
#define     VIS_VISFL0NameLength 20
#define VIS_VISFL0Order                         275      // uint8_t
#define VIS_VISFL1Name                          276      // char*, 20 Byte
#define     VIS_VISFL1NameLength 20
#define VIS_VISFL1Order                         296      // uint8_t
#define VIS_VISFL2Name                          297      // char*, 20 Byte
#define     VIS_VISFL2NameLength 20
#define VIS_VISFL2Order                         317      // uint8_t
#define VIS_VISFL3Name                          318      // char*, 20 Byte
#define     VIS_VISFL3NameLength 20
#define VIS_VISFL3Order                         338      // uint8_t
#define VIS_VISFL4Name                          339      // char*, 20 Byte
#define     VIS_VISFL4NameLength 20
#define VIS_VISFL4Order                         359      // uint8_t
#define VIS_VISFL5Name                          360      // char*, 20 Byte
#define     VIS_VISFL5NameLength 20
#define VIS_VISFL5Order                         380      // uint8_t
#define VIS_VISFL6Name                          381      // char*, 20 Byte
#define     VIS_VISFL6NameLength 20
#define VIS_VISFL6Order                         401      // uint8_t
#define VIS_VISFL7Name                          402      // char*, 20 Byte
#define     VIS_VISFL7NameLength 20
#define VIS_VISFL7Order                         422      // uint8_t
#define VIS_VISFAV0Room                         423      // 8 Bits, Bit 7-0
#define VIS_VISFAV0Widget                       424      // uint8_t
#define VIS_VISFAV1Room                         425      // 8 Bits, Bit 7-0
#define VIS_VISFAV1Widget                       426      // uint8_t
#define VIS_VISFAV2Room                         427      // 8 Bits, Bit 7-0
#define VIS_VISFAV2Widget                       428      // uint8_t
#define VIS_VISFAV3Room                         429      // 8 Bits, Bit 7-0
#define VIS_VISFAV3Widget                       430      // uint8_t
#define VIS_VISFAV4Room                         431      // 8 Bits, Bit 7-0
#define VIS_VISFAV4Widget                       432      // uint8_t
#define VIS_VISFAV5Room                         433      // 8 Bits, Bit 7-0
#define VIS_VISFAV5Widget                       434      // uint8_t
#define VIS_VISFAV6Room                         435      // 8 Bits, Bit 7-0
#define VIS_VISFAV6Widget                       436      // uint8_t
#define VIS_VISFAV7Room                         437      // 8 Bits, Bit 7-0
#define VIS_VISFAV7Widget                       438      // uint8_t
#define VIS_VISFAV8Room                         439      // 8 Bits, Bit 7-0
#define VIS_VISFAV8Widget                       440      // uint8_t
#define VIS_VISFAV9Room                         441      // 8 Bits, Bit 7-0
#define VIS_VISFAV9Widget                       442      // uint8_t
#define VIS_VISFAV10Room                        443      // 8 Bits, Bit 7-0
#define VIS_VISFAV10Widget                      444      // uint8_t
#define VIS_VISFAV11Room                        445      // 8 Bits, Bit 7-0
#define VIS_VISFAV11Widget                      446      // uint8_t
#define VIS_VISFAV12Room                        447      // 8 Bits, Bit 7-0
#define VIS_VISFAV12Widget                      448      // uint8_t
#define VIS_VISFAV13Room                        449      // 8 Bits, Bit 7-0
#define VIS_VISFAV13Widget                      450      // uint8_t
#define VIS_VISFAV14Room                        451      // 8 Bits, Bit 7-0
#define VIS_VISFAV14Widget                      452      // uint8_t
#define VIS_VISFAV15Room                        453      // 8 Bits, Bit 7-0
#define VIS_VISFAV15Widget                      454      // uint8_t

// Gerätename
#define ParamVIS_VISDeviceName                       (knx.paramData(VIS_VISDeviceName))
#define ParamVIS_VISDeviceNameStr                    (knx.paramString(VIS_VISDeviceName, VIS_VISDeviceNameLength))
// PIN-Authentifizierung aktivieren
#define ParamVIS_VISAuthEnabled                      ((bool)(knx.paramByte(VIS_VISAuthEnabled) & VIS_VISAuthEnabledMask))
// Dashboard-Seite aktivieren
#define ParamVIS_VISDashboardEnabled                 ((bool)(knx.paramByte(VIS_VISDashboardEnabled) & VIS_VISDashboardEnabledMask))
// Erscheinungsbild
#define ParamVIS_VISTheme                            ((knx.paramByte(VIS_VISTheme) & VIS_VISThemeMask) >> VIS_VISThemeShift)
// Bildschirmschoner-Modus
#define ParamVIS_VISScreensaverMode                  ((knx.paramByte(VIS_VISScreensaverMode) & VIS_VISScreensaverModeMask) >> VIS_VISScreensaverModeShift)
// PIN-Code
#define ParamVIS_VISAuthPIN                          (knx.paramInt(VIS_VISAuthPIN))
// Max. Fehlversuche
#define ParamVIS_VISAuthMaxAttempts                  (knx.paramByte(VIS_VISAuthMaxAttempts))
// Sperrzeit nach Fehlversuchen (Min)
#define ParamVIS_VISAuthLockoutMin                   (knx.paramByte(VIS_VISAuthLockoutMin))
// Heartbeat-Intervall (Sek)
#define ParamVIS_VISHeartbeatSec                     (knx.paramByte(VIS_VISHeartbeatSec))
// Anzahl Etagen
#define ParamVIS_VISVisibleFloors                    (knx.paramByte(VIS_VISVisibleFloors))
// Bildschirmschoner nach (Min, 0=aus)
#define ParamVIS_VISScreensaverMin                   (knx.paramByte(VIS_VISScreensaverMin))
// Anzahl Räume
#define ParamVIS_VISVisibleRooms                     (knx.paramByte(VIS_VISVisibleRooms))
// Etagenname
#define ParamVIS_VISFL0Name                          (knx.paramData(VIS_VISFL0Name))
#define ParamVIS_VISFL0NameStr                       (knx.paramString(VIS_VISFL0Name, VIS_VISFL0NameLength))
// Reihenfolge
#define ParamVIS_VISFL0Order                         (knx.paramByte(VIS_VISFL0Order))
// Etagenname
#define ParamVIS_VISFL1Name                          (knx.paramData(VIS_VISFL1Name))
#define ParamVIS_VISFL1NameStr                       (knx.paramString(VIS_VISFL1Name, VIS_VISFL1NameLength))
// Reihenfolge
#define ParamVIS_VISFL1Order                         (knx.paramByte(VIS_VISFL1Order))
// Etagenname
#define ParamVIS_VISFL2Name                          (knx.paramData(VIS_VISFL2Name))
#define ParamVIS_VISFL2NameStr                       (knx.paramString(VIS_VISFL2Name, VIS_VISFL2NameLength))
// Reihenfolge
#define ParamVIS_VISFL2Order                         (knx.paramByte(VIS_VISFL2Order))
// Etagenname
#define ParamVIS_VISFL3Name                          (knx.paramData(VIS_VISFL3Name))
#define ParamVIS_VISFL3NameStr                       (knx.paramString(VIS_VISFL3Name, VIS_VISFL3NameLength))
// Reihenfolge
#define ParamVIS_VISFL3Order                         (knx.paramByte(VIS_VISFL3Order))
// Etagenname
#define ParamVIS_VISFL4Name                          (knx.paramData(VIS_VISFL4Name))
#define ParamVIS_VISFL4NameStr                       (knx.paramString(VIS_VISFL4Name, VIS_VISFL4NameLength))
// Reihenfolge
#define ParamVIS_VISFL4Order                         (knx.paramByte(VIS_VISFL4Order))
// Etagenname
#define ParamVIS_VISFL5Name                          (knx.paramData(VIS_VISFL5Name))
#define ParamVIS_VISFL5NameStr                       (knx.paramString(VIS_VISFL5Name, VIS_VISFL5NameLength))
// Reihenfolge
#define ParamVIS_VISFL5Order                         (knx.paramByte(VIS_VISFL5Order))
// Etagenname
#define ParamVIS_VISFL6Name                          (knx.paramData(VIS_VISFL6Name))
#define ParamVIS_VISFL6NameStr                       (knx.paramString(VIS_VISFL6Name, VIS_VISFL6NameLength))
// Reihenfolge
#define ParamVIS_VISFL6Order                         (knx.paramByte(VIS_VISFL6Order))
// Etagenname
#define ParamVIS_VISFL7Name                          (knx.paramData(VIS_VISFL7Name))
#define ParamVIS_VISFL7NameStr                       (knx.paramString(VIS_VISFL7Name, VIS_VISFL7NameLength))
// Reihenfolge
#define ParamVIS_VISFL7Order                         (knx.paramByte(VIS_VISFL7Order))
// Raum
#define ParamVIS_VISFAV0Room                         (knx.paramByte(VIS_VISFAV0Room))
// Kachel
#define ParamVIS_VISFAV0Widget                       (knx.paramByte(VIS_VISFAV0Widget))
// Raum
#define ParamVIS_VISFAV1Room                         (knx.paramByte(VIS_VISFAV1Room))
// Kachel
#define ParamVIS_VISFAV1Widget                       (knx.paramByte(VIS_VISFAV1Widget))
// Raum
#define ParamVIS_VISFAV2Room                         (knx.paramByte(VIS_VISFAV2Room))
// Kachel
#define ParamVIS_VISFAV2Widget                       (knx.paramByte(VIS_VISFAV2Widget))
// Raum
#define ParamVIS_VISFAV3Room                         (knx.paramByte(VIS_VISFAV3Room))
// Kachel
#define ParamVIS_VISFAV3Widget                       (knx.paramByte(VIS_VISFAV3Widget))
// Raum
#define ParamVIS_VISFAV4Room                         (knx.paramByte(VIS_VISFAV4Room))
// Kachel
#define ParamVIS_VISFAV4Widget                       (knx.paramByte(VIS_VISFAV4Widget))
// Raum
#define ParamVIS_VISFAV5Room                         (knx.paramByte(VIS_VISFAV5Room))
// Kachel
#define ParamVIS_VISFAV5Widget                       (knx.paramByte(VIS_VISFAV5Widget))
// Raum
#define ParamVIS_VISFAV6Room                         (knx.paramByte(VIS_VISFAV6Room))
// Kachel
#define ParamVIS_VISFAV6Widget                       (knx.paramByte(VIS_VISFAV6Widget))
// Raum
#define ParamVIS_VISFAV7Room                         (knx.paramByte(VIS_VISFAV7Room))
// Kachel
#define ParamVIS_VISFAV7Widget                       (knx.paramByte(VIS_VISFAV7Widget))
// Raum
#define ParamVIS_VISFAV8Room                         (knx.paramByte(VIS_VISFAV8Room))
// Kachel
#define ParamVIS_VISFAV8Widget                       (knx.paramByte(VIS_VISFAV8Widget))
// Raum
#define ParamVIS_VISFAV9Room                         (knx.paramByte(VIS_VISFAV9Room))
// Kachel
#define ParamVIS_VISFAV9Widget                       (knx.paramByte(VIS_VISFAV9Widget))
// Raum
#define ParamVIS_VISFAV10Room                        (knx.paramByte(VIS_VISFAV10Room))
// Kachel
#define ParamVIS_VISFAV10Widget                      (knx.paramByte(VIS_VISFAV10Widget))
// Raum
#define ParamVIS_VISFAV11Room                        (knx.paramByte(VIS_VISFAV11Room))
// Kachel
#define ParamVIS_VISFAV11Widget                      (knx.paramByte(VIS_VISFAV11Widget))
// Raum
#define ParamVIS_VISFAV12Room                        (knx.paramByte(VIS_VISFAV12Room))
// Kachel
#define ParamVIS_VISFAV12Widget                      (knx.paramByte(VIS_VISFAV12Widget))
// Raum
#define ParamVIS_VISFAV13Room                        (knx.paramByte(VIS_VISFAV13Room))
// Kachel
#define ParamVIS_VISFAV13Widget                      (knx.paramByte(VIS_VISFAV13Widget))
// Raum
#define ParamVIS_VISFAV14Room                        (knx.paramByte(VIS_VISFAV14Room))
// Kachel
#define ParamVIS_VISFAV14Widget                      (knx.paramByte(VIS_VISFAV14Widget))
// Raum
#define ParamVIS_VISFAV15Room                        (knx.paramByte(VIS_VISFAV15Room))
// Kachel
#define ParamVIS_VISFAV15Widget                      (knx.paramByte(VIS_VISFAV15Widget))

#define VIS_ChannelCount 8

// Parameter per channel
#define VIS_ParamBlockOffset 456
#define VIS_ParamBlockSize 626
#define VIS_ParamCalcIndex(index) (index + VIS_ParamBlockOffset + _channelIndex * VIS_ParamBlockSize)

#define VIS_CHRoomName                           0      // char*, 20 Byte
#define     VIS_CHRoomNameLength 20
#define VIS_CHRoomIcon                          20      // 8 Bits, Bit 7-0
#define VIS_CHRoomFloor                         21      // 8 Bits, Bit 7-0
#define VIS_CHRoomOrder                         22      // uint8_t
#define VIS_CHVisibleWidgets                    23      // uint8_t
#define VIS_CHWz0Type                           24      // 8 Bits, Bit 7-0
#define VIS_CHWz0Name                           25      // char*, 20 Byte
#define     VIS_CHWz0NameLength 20
#define VIS_CHWz0Icon                           45      // uint8_t
#define VIS_CHWz0TileSize                       46      // 8 Bits, Bit 7-0
#define VIS_CHWz0SortOrder                      47      // uint8_t
#define VIS_CHWz0Width                          48      // 8 Bits, Bit 7-0
#define VIS_CHWz0Height                         49      // 8 Bits, Bit 7-0
#define VIS_CHWz0Trade                          50      // 8 Bits, Bit 7-0
#define VIS_CHWz0Dpt                            51      // 8 Bits, Bit 7-0
#define VIS_CHWz0CamUrl                         52      // char*, 15 Byte
#define     VIS_CHWz0CamUrlLength 15
#define VIS_CHWz1Type                           67      // 8 Bits, Bit 7-0
#define VIS_CHWz1Name                           68      // char*, 20 Byte
#define     VIS_CHWz1NameLength 20
#define VIS_CHWz1Icon                           88      // uint8_t
#define VIS_CHWz1TileSize                       89      // 8 Bits, Bit 7-0
#define VIS_CHWz1SortOrder                      90      // uint8_t
#define VIS_CHWz1Width                          91      // 8 Bits, Bit 7-0
#define VIS_CHWz1Height                         92      // 8 Bits, Bit 7-0
#define VIS_CHWz1Trade                          93      // 8 Bits, Bit 7-0
#define VIS_CHWz1Dpt                            94      // 8 Bits, Bit 7-0
#define VIS_CHWz1CamUrl                         95      // char*, 15 Byte
#define     VIS_CHWz1CamUrlLength 15
#define VIS_CHWz2Type                           110      // 8 Bits, Bit 7-0
#define VIS_CHWz2Name                           111      // char*, 20 Byte
#define     VIS_CHWz2NameLength 20
#define VIS_CHWz2Icon                           131      // uint8_t
#define VIS_CHWz2TileSize                       132      // 8 Bits, Bit 7-0
#define VIS_CHWz2SortOrder                      133      // uint8_t
#define VIS_CHWz2Width                          134      // 8 Bits, Bit 7-0
#define VIS_CHWz2Height                         135      // 8 Bits, Bit 7-0
#define VIS_CHWz2Trade                          136      // 8 Bits, Bit 7-0
#define VIS_CHWz2Dpt                            137      // 8 Bits, Bit 7-0
#define VIS_CHWz2CamUrl                         138      // char*, 15 Byte
#define     VIS_CHWz2CamUrlLength 15
#define VIS_CHWz3Type                           153      // 8 Bits, Bit 7-0
#define VIS_CHWz3Name                           154      // char*, 20 Byte
#define     VIS_CHWz3NameLength 20
#define VIS_CHWz3Icon                           174      // uint8_t
#define VIS_CHWz3TileSize                       175      // 8 Bits, Bit 7-0
#define VIS_CHWz3SortOrder                      176      // uint8_t
#define VIS_CHWz3Width                          177      // 8 Bits, Bit 7-0
#define VIS_CHWz3Height                         178      // 8 Bits, Bit 7-0
#define VIS_CHWz3Trade                          179      // 8 Bits, Bit 7-0
#define VIS_CHWz3Dpt                            180      // 8 Bits, Bit 7-0
#define VIS_CHWz3CamUrl                         181      // char*, 15 Byte
#define     VIS_CHWz3CamUrlLength 15
#define VIS_CHWz4Type                           196      // 8 Bits, Bit 7-0
#define VIS_CHWz4Name                           197      // char*, 20 Byte
#define     VIS_CHWz4NameLength 20
#define VIS_CHWz4Icon                           217      // uint8_t
#define VIS_CHWz4TileSize                       218      // 8 Bits, Bit 7-0
#define VIS_CHWz4SortOrder                      219      // uint8_t
#define VIS_CHWz4Width                          220      // 8 Bits, Bit 7-0
#define VIS_CHWz4Height                         221      // 8 Bits, Bit 7-0
#define VIS_CHWz4Trade                          222      // 8 Bits, Bit 7-0
#define VIS_CHWz4Dpt                            223      // 8 Bits, Bit 7-0
#define VIS_CHWz4CamUrl                         224      // char*, 15 Byte
#define     VIS_CHWz4CamUrlLength 15
#define VIS_CHWz5Type                           239      // 8 Bits, Bit 7-0
#define VIS_CHWz5Name                           240      // char*, 20 Byte
#define     VIS_CHWz5NameLength 20
#define VIS_CHWz5Icon                           260      // uint8_t
#define VIS_CHWz5TileSize                       261      // 8 Bits, Bit 7-0
#define VIS_CHWz5SortOrder                      262      // uint8_t
#define VIS_CHWz5Width                          263      // 8 Bits, Bit 7-0
#define VIS_CHWz5Height                         264      // 8 Bits, Bit 7-0
#define VIS_CHWz5Trade                          265      // 8 Bits, Bit 7-0
#define VIS_CHWz5Dpt                            266      // 8 Bits, Bit 7-0
#define VIS_CHWz5CamUrl                         267      // char*, 15 Byte
#define     VIS_CHWz5CamUrlLength 15
#define VIS_CHWz6Type                           282      // 8 Bits, Bit 7-0
#define VIS_CHWz6Name                           283      // char*, 20 Byte
#define     VIS_CHWz6NameLength 20
#define VIS_CHWz6Icon                           303      // uint8_t
#define VIS_CHWz6TileSize                       304      // 8 Bits, Bit 7-0
#define VIS_CHWz6SortOrder                      305      // uint8_t
#define VIS_CHWz6Width                          306      // 8 Bits, Bit 7-0
#define VIS_CHWz6Height                         307      // 8 Bits, Bit 7-0
#define VIS_CHWz6Trade                          308      // 8 Bits, Bit 7-0
#define VIS_CHWz6Dpt                            309      // 8 Bits, Bit 7-0
#define VIS_CHWz6CamUrl                         310      // char*, 15 Byte
#define     VIS_CHWz6CamUrlLength 15
#define VIS_CHWz7Type                           325      // 8 Bits, Bit 7-0
#define VIS_CHWz7Name                           326      // char*, 20 Byte
#define     VIS_CHWz7NameLength 20
#define VIS_CHWz7Icon                           346      // uint8_t
#define VIS_CHWz7TileSize                       347      // 8 Bits, Bit 7-0
#define VIS_CHWz7SortOrder                      348      // uint8_t
#define VIS_CHWz7Width                          349      // 8 Bits, Bit 7-0
#define VIS_CHWz7Height                         350      // 8 Bits, Bit 7-0
#define VIS_CHWz7Trade                          351      // 8 Bits, Bit 7-0
#define VIS_CHWz7Dpt                            352      // 8 Bits, Bit 7-0
#define VIS_CHWz7CamUrl                         353      // char*, 15 Byte
#define     VIS_CHWz7CamUrlLength 15
#define VIS_CHWz8Type                           368      // 8 Bits, Bit 7-0
#define VIS_CHWz8Name                           369      // char*, 20 Byte
#define     VIS_CHWz8NameLength 20
#define VIS_CHWz8Icon                           389      // uint8_t
#define VIS_CHWz8TileSize                       390      // 8 Bits, Bit 7-0
#define VIS_CHWz8SortOrder                      391      // uint8_t
#define VIS_CHWz8Width                          392      // 8 Bits, Bit 7-0
#define VIS_CHWz8Height                         393      // 8 Bits, Bit 7-0
#define VIS_CHWz8Trade                          394      // 8 Bits, Bit 7-0
#define VIS_CHWz8Dpt                            395      // 8 Bits, Bit 7-0
#define VIS_CHWz8CamUrl                         396      // char*, 15 Byte
#define     VIS_CHWz8CamUrlLength 15
#define VIS_CHWz9Type                           411      // 8 Bits, Bit 7-0
#define VIS_CHWz9Name                           412      // char*, 20 Byte
#define     VIS_CHWz9NameLength 20
#define VIS_CHWz9Icon                           432      // uint8_t
#define VIS_CHWz9TileSize                       433      // 8 Bits, Bit 7-0
#define VIS_CHWz9SortOrder                      434      // uint8_t
#define VIS_CHWz9Width                          435      // 8 Bits, Bit 7-0
#define VIS_CHWz9Height                         436      // 8 Bits, Bit 7-0
#define VIS_CHWz9Trade                          437      // 8 Bits, Bit 7-0
#define VIS_CHWz9Dpt                            438      // 8 Bits, Bit 7-0
#define VIS_CHWz9CamUrl                         439      // char*, 15 Byte
#define     VIS_CHWz9CamUrlLength 15
#define VIS_CHWz10Type                          454      // 8 Bits, Bit 7-0
#define VIS_CHWz10Name                          455      // char*, 20 Byte
#define     VIS_CHWz10NameLength 20
#define VIS_CHWz10Icon                          475      // uint8_t
#define VIS_CHWz10TileSize                      476      // 8 Bits, Bit 7-0
#define VIS_CHWz10SortOrder                     477      // uint8_t
#define VIS_CHWz10Width                         478      // 8 Bits, Bit 7-0
#define VIS_CHWz10Height                        479      // 8 Bits, Bit 7-0
#define VIS_CHWz10Trade                         480      // 8 Bits, Bit 7-0
#define VIS_CHWz10Dpt                           481      // 8 Bits, Bit 7-0
#define VIS_CHWz10CamUrl                        482      // char*, 15 Byte
#define     VIS_CHWz10CamUrlLength 15
#define VIS_CHWz11Type                          497      // 8 Bits, Bit 7-0
#define VIS_CHWz11Name                          498      // char*, 20 Byte
#define     VIS_CHWz11NameLength 20
#define VIS_CHWz11Icon                          518      // uint8_t
#define VIS_CHWz11TileSize                      519      // 8 Bits, Bit 7-0
#define VIS_CHWz11SortOrder                     520      // uint8_t
#define VIS_CHWz11Width                         521      // 8 Bits, Bit 7-0
#define VIS_CHWz11Height                        522      // 8 Bits, Bit 7-0
#define VIS_CHWz11Trade                         523      // 8 Bits, Bit 7-0
#define VIS_CHWz11Dpt                           524      // 8 Bits, Bit 7-0
#define VIS_CHWz11CamUrl                        525      // char*, 15 Byte
#define     VIS_CHWz11CamUrlLength 15
#define VIS_CHWz12Type                          540      // 8 Bits, Bit 7-0
#define VIS_CHWz12Name                          541      // char*, 20 Byte
#define     VIS_CHWz12NameLength 20
#define VIS_CHWz12Icon                          561      // uint8_t
#define VIS_CHWz12TileSize                      562      // 8 Bits, Bit 7-0
#define VIS_CHWz12SortOrder                     563      // uint8_t
#define VIS_CHWz12Width                         564      // 8 Bits, Bit 7-0
#define VIS_CHWz12Height                        565      // 8 Bits, Bit 7-0
#define VIS_CHWz12Trade                         566      // 8 Bits, Bit 7-0
#define VIS_CHWz12Dpt                           567      // 8 Bits, Bit 7-0
#define VIS_CHWz12CamUrl                        568      // char*, 15 Byte
#define     VIS_CHWz12CamUrlLength 15
#define VIS_CHWz13Type                          583      // 8 Bits, Bit 7-0
#define VIS_CHWz13Name                          584      // char*, 20 Byte
#define     VIS_CHWz13NameLength 20
#define VIS_CHWz13Icon                          604      // uint8_t
#define VIS_CHWz13TileSize                      605      // 8 Bits, Bit 7-0
#define VIS_CHWz13SortOrder                     606      // uint8_t
#define VIS_CHWz13Width                         607      // 8 Bits, Bit 7-0
#define VIS_CHWz13Height                        608      // 8 Bits, Bit 7-0
#define VIS_CHWz13Trade                         609      // 8 Bits, Bit 7-0
#define VIS_CHWz13Dpt                           610      // 8 Bits, Bit 7-0
#define VIS_CHWz13CamUrl                        611      // char*, 15 Byte
#define     VIS_CHWz13CamUrlLength 15

// Raumname
#define ParamVIS_CHRoomName                          (knx.paramData(VIS_ParamCalcIndex(VIS_CHRoomName)))
#define ParamVIS_CHRoomNameStr                       (knx.paramString(VIS_ParamCalcIndex(VIS_CHRoomName), VIS_CHRoomNameLength))
// Symbol
#define ParamVIS_CHRoomIcon                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHRoomIcon)))
// Etage
#define ParamVIS_CHRoomFloor                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHRoomFloor)))
// Reihenfolge
#define ParamVIS_CHRoomOrder                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHRoomOrder)))
// Anzahl Kacheln
#define ParamVIS_CHVisibleWidgets                    (knx.paramByte(VIS_ParamCalcIndex(VIS_CHVisibleWidgets)))
// Kachel 1 – Typ
#define ParamVIS_CHWz0Type                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz0Type)))
// Bezeichnung
#define ParamVIS_CHWz0Name                           (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz0Name)))
#define ParamVIS_CHWz0NameStr                        (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz0Name), VIS_CHWz0NameLength))
// Symbol
#define ParamVIS_CHWz0Icon                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz0Icon)))
// Kachelgröße
#define ParamVIS_CHWz0TileSize                       (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz0TileSize)))
// Sortierung
#define ParamVIS_CHWz0SortOrder                      (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz0SortOrder)))
// Breite
#define ParamVIS_CHWz0Width                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz0Width)))
// Höhe
#define ParamVIS_CHWz0Height                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz0Height)))
// Gewerk
#define ParamVIS_CHWz0Trade                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz0Trade)))
// Datenpunkttyp
#define ParamVIS_CHWz0Dpt                            (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz0Dpt)))
// Kamera-URL
#define ParamVIS_CHWz0CamUrl                         (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz0CamUrl)))
#define ParamVIS_CHWz0CamUrlStr                      (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz0CamUrl), VIS_CHWz0CamUrlLength))
// Kachel 2 – Typ
#define ParamVIS_CHWz1Type                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz1Type)))
// Bezeichnung
#define ParamVIS_CHWz1Name                           (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz1Name)))
#define ParamVIS_CHWz1NameStr                        (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz1Name), VIS_CHWz1NameLength))
// Symbol
#define ParamVIS_CHWz1Icon                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz1Icon)))
// Kachelgröße
#define ParamVIS_CHWz1TileSize                       (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz1TileSize)))
// Sortierung
#define ParamVIS_CHWz1SortOrder                      (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz1SortOrder)))
// Breite
#define ParamVIS_CHWz1Width                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz1Width)))
// Höhe
#define ParamVIS_CHWz1Height                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz1Height)))
// Gewerk
#define ParamVIS_CHWz1Trade                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz1Trade)))
// Datenpunkttyp
#define ParamVIS_CHWz1Dpt                            (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz1Dpt)))
// Kamera-URL
#define ParamVIS_CHWz1CamUrl                         (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz1CamUrl)))
#define ParamVIS_CHWz1CamUrlStr                      (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz1CamUrl), VIS_CHWz1CamUrlLength))
// Kachel 3 – Typ
#define ParamVIS_CHWz2Type                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz2Type)))
// Bezeichnung
#define ParamVIS_CHWz2Name                           (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz2Name)))
#define ParamVIS_CHWz2NameStr                        (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz2Name), VIS_CHWz2NameLength))
// Symbol
#define ParamVIS_CHWz2Icon                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz2Icon)))
// Kachelgröße
#define ParamVIS_CHWz2TileSize                       (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz2TileSize)))
// Sortierung
#define ParamVIS_CHWz2SortOrder                      (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz2SortOrder)))
// Breite
#define ParamVIS_CHWz2Width                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz2Width)))
// Höhe
#define ParamVIS_CHWz2Height                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz2Height)))
// Gewerk
#define ParamVIS_CHWz2Trade                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz2Trade)))
// Datenpunkttyp
#define ParamVIS_CHWz2Dpt                            (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz2Dpt)))
// Kamera-URL
#define ParamVIS_CHWz2CamUrl                         (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz2CamUrl)))
#define ParamVIS_CHWz2CamUrlStr                      (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz2CamUrl), VIS_CHWz2CamUrlLength))
// Kachel 4 – Typ
#define ParamVIS_CHWz3Type                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz3Type)))
// Bezeichnung
#define ParamVIS_CHWz3Name                           (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz3Name)))
#define ParamVIS_CHWz3NameStr                        (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz3Name), VIS_CHWz3NameLength))
// Symbol
#define ParamVIS_CHWz3Icon                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz3Icon)))
// Kachelgröße
#define ParamVIS_CHWz3TileSize                       (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz3TileSize)))
// Sortierung
#define ParamVIS_CHWz3SortOrder                      (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz3SortOrder)))
// Breite
#define ParamVIS_CHWz3Width                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz3Width)))
// Höhe
#define ParamVIS_CHWz3Height                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz3Height)))
// Gewerk
#define ParamVIS_CHWz3Trade                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz3Trade)))
// Datenpunkttyp
#define ParamVIS_CHWz3Dpt                            (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz3Dpt)))
// Kamera-URL
#define ParamVIS_CHWz3CamUrl                         (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz3CamUrl)))
#define ParamVIS_CHWz3CamUrlStr                      (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz3CamUrl), VIS_CHWz3CamUrlLength))
// Kachel 5 – Typ
#define ParamVIS_CHWz4Type                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz4Type)))
// Bezeichnung
#define ParamVIS_CHWz4Name                           (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz4Name)))
#define ParamVIS_CHWz4NameStr                        (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz4Name), VIS_CHWz4NameLength))
// Symbol
#define ParamVIS_CHWz4Icon                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz4Icon)))
// Kachelgröße
#define ParamVIS_CHWz4TileSize                       (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz4TileSize)))
// Sortierung
#define ParamVIS_CHWz4SortOrder                      (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz4SortOrder)))
// Breite
#define ParamVIS_CHWz4Width                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz4Width)))
// Höhe
#define ParamVIS_CHWz4Height                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz4Height)))
// Gewerk
#define ParamVIS_CHWz4Trade                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz4Trade)))
// Datenpunkttyp
#define ParamVIS_CHWz4Dpt                            (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz4Dpt)))
// Kamera-URL
#define ParamVIS_CHWz4CamUrl                         (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz4CamUrl)))
#define ParamVIS_CHWz4CamUrlStr                      (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz4CamUrl), VIS_CHWz4CamUrlLength))
// Kachel 6 – Typ
#define ParamVIS_CHWz5Type                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz5Type)))
// Bezeichnung
#define ParamVIS_CHWz5Name                           (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz5Name)))
#define ParamVIS_CHWz5NameStr                        (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz5Name), VIS_CHWz5NameLength))
// Symbol
#define ParamVIS_CHWz5Icon                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz5Icon)))
// Kachelgröße
#define ParamVIS_CHWz5TileSize                       (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz5TileSize)))
// Sortierung
#define ParamVIS_CHWz5SortOrder                      (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz5SortOrder)))
// Breite
#define ParamVIS_CHWz5Width                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz5Width)))
// Höhe
#define ParamVIS_CHWz5Height                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz5Height)))
// Gewerk
#define ParamVIS_CHWz5Trade                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz5Trade)))
// Datenpunkttyp
#define ParamVIS_CHWz5Dpt                            (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz5Dpt)))
// Kamera-URL
#define ParamVIS_CHWz5CamUrl                         (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz5CamUrl)))
#define ParamVIS_CHWz5CamUrlStr                      (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz5CamUrl), VIS_CHWz5CamUrlLength))
// Kachel 7 – Typ
#define ParamVIS_CHWz6Type                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz6Type)))
// Bezeichnung
#define ParamVIS_CHWz6Name                           (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz6Name)))
#define ParamVIS_CHWz6NameStr                        (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz6Name), VIS_CHWz6NameLength))
// Symbol
#define ParamVIS_CHWz6Icon                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz6Icon)))
// Kachelgröße
#define ParamVIS_CHWz6TileSize                       (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz6TileSize)))
// Sortierung
#define ParamVIS_CHWz6SortOrder                      (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz6SortOrder)))
// Breite
#define ParamVIS_CHWz6Width                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz6Width)))
// Höhe
#define ParamVIS_CHWz6Height                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz6Height)))
// Gewerk
#define ParamVIS_CHWz6Trade                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz6Trade)))
// Datenpunkttyp
#define ParamVIS_CHWz6Dpt                            (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz6Dpt)))
// Kamera-URL
#define ParamVIS_CHWz6CamUrl                         (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz6CamUrl)))
#define ParamVIS_CHWz6CamUrlStr                      (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz6CamUrl), VIS_CHWz6CamUrlLength))
// Kachel 8 – Typ
#define ParamVIS_CHWz7Type                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz7Type)))
// Bezeichnung
#define ParamVIS_CHWz7Name                           (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz7Name)))
#define ParamVIS_CHWz7NameStr                        (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz7Name), VIS_CHWz7NameLength))
// Symbol
#define ParamVIS_CHWz7Icon                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz7Icon)))
// Kachelgröße
#define ParamVIS_CHWz7TileSize                       (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz7TileSize)))
// Sortierung
#define ParamVIS_CHWz7SortOrder                      (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz7SortOrder)))
// Breite
#define ParamVIS_CHWz7Width                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz7Width)))
// Höhe
#define ParamVIS_CHWz7Height                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz7Height)))
// Gewerk
#define ParamVIS_CHWz7Trade                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz7Trade)))
// Datenpunkttyp
#define ParamVIS_CHWz7Dpt                            (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz7Dpt)))
// Kamera-URL
#define ParamVIS_CHWz7CamUrl                         (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz7CamUrl)))
#define ParamVIS_CHWz7CamUrlStr                      (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz7CamUrl), VIS_CHWz7CamUrlLength))
// Kachel 9 – Typ
#define ParamVIS_CHWz8Type                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz8Type)))
// Bezeichnung
#define ParamVIS_CHWz8Name                           (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz8Name)))
#define ParamVIS_CHWz8NameStr                        (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz8Name), VIS_CHWz8NameLength))
// Symbol
#define ParamVIS_CHWz8Icon                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz8Icon)))
// Kachelgröße
#define ParamVIS_CHWz8TileSize                       (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz8TileSize)))
// Sortierung
#define ParamVIS_CHWz8SortOrder                      (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz8SortOrder)))
// Breite
#define ParamVIS_CHWz8Width                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz8Width)))
// Höhe
#define ParamVIS_CHWz8Height                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz8Height)))
// Gewerk
#define ParamVIS_CHWz8Trade                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz8Trade)))
// Datenpunkttyp
#define ParamVIS_CHWz8Dpt                            (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz8Dpt)))
// Kamera-URL
#define ParamVIS_CHWz8CamUrl                         (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz8CamUrl)))
#define ParamVIS_CHWz8CamUrlStr                      (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz8CamUrl), VIS_CHWz8CamUrlLength))
// Kachel 10 – Typ
#define ParamVIS_CHWz9Type                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz9Type)))
// Bezeichnung
#define ParamVIS_CHWz9Name                           (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz9Name)))
#define ParamVIS_CHWz9NameStr                        (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz9Name), VIS_CHWz9NameLength))
// Symbol
#define ParamVIS_CHWz9Icon                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz9Icon)))
// Kachelgröße
#define ParamVIS_CHWz9TileSize                       (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz9TileSize)))
// Sortierung
#define ParamVIS_CHWz9SortOrder                      (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz9SortOrder)))
// Breite
#define ParamVIS_CHWz9Width                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz9Width)))
// Höhe
#define ParamVIS_CHWz9Height                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz9Height)))
// Gewerk
#define ParamVIS_CHWz9Trade                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz9Trade)))
// Datenpunkttyp
#define ParamVIS_CHWz9Dpt                            (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz9Dpt)))
// Kamera-URL
#define ParamVIS_CHWz9CamUrl                         (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz9CamUrl)))
#define ParamVIS_CHWz9CamUrlStr                      (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz9CamUrl), VIS_CHWz9CamUrlLength))
// Kachel 11 – Typ
#define ParamVIS_CHWz10Type                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz10Type)))
// Bezeichnung
#define ParamVIS_CHWz10Name                          (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz10Name)))
#define ParamVIS_CHWz10NameStr                       (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz10Name), VIS_CHWz10NameLength))
// Symbol
#define ParamVIS_CHWz10Icon                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz10Icon)))
// Kachelgröße
#define ParamVIS_CHWz10TileSize                      (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz10TileSize)))
// Sortierung
#define ParamVIS_CHWz10SortOrder                     (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz10SortOrder)))
// Breite
#define ParamVIS_CHWz10Width                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz10Width)))
// Höhe
#define ParamVIS_CHWz10Height                        (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz10Height)))
// Gewerk
#define ParamVIS_CHWz10Trade                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz10Trade)))
// Datenpunkttyp
#define ParamVIS_CHWz10Dpt                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz10Dpt)))
// Kamera-URL
#define ParamVIS_CHWz10CamUrl                        (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz10CamUrl)))
#define ParamVIS_CHWz10CamUrlStr                     (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz10CamUrl), VIS_CHWz10CamUrlLength))
// Kachel 12 – Typ
#define ParamVIS_CHWz11Type                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz11Type)))
// Bezeichnung
#define ParamVIS_CHWz11Name                          (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz11Name)))
#define ParamVIS_CHWz11NameStr                       (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz11Name), VIS_CHWz11NameLength))
// Symbol
#define ParamVIS_CHWz11Icon                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz11Icon)))
// Kachelgröße
#define ParamVIS_CHWz11TileSize                      (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz11TileSize)))
// Sortierung
#define ParamVIS_CHWz11SortOrder                     (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz11SortOrder)))
// Breite
#define ParamVIS_CHWz11Width                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz11Width)))
// Höhe
#define ParamVIS_CHWz11Height                        (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz11Height)))
// Gewerk
#define ParamVIS_CHWz11Trade                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz11Trade)))
// Datenpunkttyp
#define ParamVIS_CHWz11Dpt                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz11Dpt)))
// Kamera-URL
#define ParamVIS_CHWz11CamUrl                        (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz11CamUrl)))
#define ParamVIS_CHWz11CamUrlStr                     (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz11CamUrl), VIS_CHWz11CamUrlLength))
// Kachel 13 – Typ
#define ParamVIS_CHWz12Type                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz12Type)))
// Bezeichnung
#define ParamVIS_CHWz12Name                          (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz12Name)))
#define ParamVIS_CHWz12NameStr                       (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz12Name), VIS_CHWz12NameLength))
// Symbol
#define ParamVIS_CHWz12Icon                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz12Icon)))
// Kachelgröße
#define ParamVIS_CHWz12TileSize                      (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz12TileSize)))
// Sortierung
#define ParamVIS_CHWz12SortOrder                     (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz12SortOrder)))
// Breite
#define ParamVIS_CHWz12Width                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz12Width)))
// Höhe
#define ParamVIS_CHWz12Height                        (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz12Height)))
// Gewerk
#define ParamVIS_CHWz12Trade                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz12Trade)))
// Datenpunkttyp
#define ParamVIS_CHWz12Dpt                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz12Dpt)))
// Kamera-URL
#define ParamVIS_CHWz12CamUrl                        (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz12CamUrl)))
#define ParamVIS_CHWz12CamUrlStr                     (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz12CamUrl), VIS_CHWz12CamUrlLength))
// Kachel 14 – Typ
#define ParamVIS_CHWz13Type                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz13Type)))
// Bezeichnung
#define ParamVIS_CHWz13Name                          (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz13Name)))
#define ParamVIS_CHWz13NameStr                       (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz13Name), VIS_CHWz13NameLength))
// Symbol
#define ParamVIS_CHWz13Icon                          (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz13Icon)))
// Kachelgröße
#define ParamVIS_CHWz13TileSize                      (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz13TileSize)))
// Sortierung
#define ParamVIS_CHWz13SortOrder                     (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz13SortOrder)))
// Breite
#define ParamVIS_CHWz13Width                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz13Width)))
// Höhe
#define ParamVIS_CHWz13Height                        (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz13Height)))
// Gewerk
#define ParamVIS_CHWz13Trade                         (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz13Trade)))
// Datenpunkttyp
#define ParamVIS_CHWz13Dpt                           (knx.paramByte(VIS_ParamCalcIndex(VIS_CHWz13Dpt)))
// Kamera-URL
#define ParamVIS_CHWz13CamUrl                        (knx.paramData(VIS_ParamCalcIndex(VIS_CHWz13CamUrl)))
#define ParamVIS_CHWz13CamUrlStr                     (knx.paramString(VIS_ParamCalcIndex(VIS_CHWz13CamUrl), VIS_CHWz13CamUrlLength))

// deprecated
#define VIS_KoOffset 400

// Communication objects per channel (multiple occurrence)
#define VIS_KoBlockOffset 400
#define VIS_KoBlockSize 56

#define VIS_KoCalcNumber(index) (index + VIS_KoBlockOffset + _channelIndex * VIS_KoBlockSize)
#define VIS_KoCalcIndex(number) ((number >= VIS_KoCalcNumber(0) && number < VIS_KoCalcNumber(VIS_KoBlockSize)) ? (number - VIS_KoBlockOffset) % VIS_KoBlockSize : -1)
#define VIS_KoCalcChannel(number) ((number >= VIS_KoBlockOffset && number < VIS_KoBlockOffset + VIS_ChannelCount * VIS_KoBlockSize) ? (number - VIS_KoBlockOffset) / VIS_KoBlockSize : -1)

#define VIS_KoCHWz0KO0 0
#define VIS_KoCHWz0KO1 1
#define VIS_KoCHWz0KO2 2
#define VIS_KoCHWz0KO3 3
#define VIS_KoCHWz1KO0 4
#define VIS_KoCHWz1KO1 5
#define VIS_KoCHWz1KO2 6
#define VIS_KoCHWz1KO3 7
#define VIS_KoCHWz2KO0 8
#define VIS_KoCHWz2KO1 9
#define VIS_KoCHWz2KO2 10
#define VIS_KoCHWz2KO3 11
#define VIS_KoCHWz3KO0 12
#define VIS_KoCHWz3KO1 13
#define VIS_KoCHWz3KO2 14
#define VIS_KoCHWz3KO3 15
#define VIS_KoCHWz4KO0 16
#define VIS_KoCHWz4KO1 17
#define VIS_KoCHWz4KO2 18
#define VIS_KoCHWz4KO3 19
#define VIS_KoCHWz5KO0 20
#define VIS_KoCHWz5KO1 21
#define VIS_KoCHWz5KO2 22
#define VIS_KoCHWz5KO3 23
#define VIS_KoCHWz6KO0 24
#define VIS_KoCHWz6KO1 25
#define VIS_KoCHWz6KO2 26
#define VIS_KoCHWz6KO3 27
#define VIS_KoCHWz7KO0 28
#define VIS_KoCHWz7KO1 29
#define VIS_KoCHWz7KO2 30
#define VIS_KoCHWz7KO3 31
#define VIS_KoCHWz8KO0 32
#define VIS_KoCHWz8KO1 33
#define VIS_KoCHWz8KO2 34
#define VIS_KoCHWz8KO3 35
#define VIS_KoCHWz9KO0 36
#define VIS_KoCHWz9KO1 37
#define VIS_KoCHWz9KO2 38
#define VIS_KoCHWz9KO3 39
#define VIS_KoCHWz10KO0 40
#define VIS_KoCHWz10KO1 41
#define VIS_KoCHWz10KO2 42
#define VIS_KoCHWz10KO3 43
#define VIS_KoCHWz11KO0 44
#define VIS_KoCHWz11KO1 45
#define VIS_KoCHWz11KO2 46
#define VIS_KoCHWz11KO3 47
#define VIS_KoCHWz12KO0 48
#define VIS_KoCHWz12KO1 49
#define VIS_KoCHWz12KO2 50
#define VIS_KoCHWz12KO3 51
#define VIS_KoCHWz13KO0 52
#define VIS_KoCHWz13KO1 53
#define VIS_KoCHWz13KO2 54
#define VIS_KoCHWz13KO3 55

// Raum %C% Kachel 1 Steuerung
#define KoVIS_CHWz0KO0                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz0KO0)))
// Raum %C% Kachel 1 Status
#define KoVIS_CHWz0KO1                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz0KO1)))
// Raum %C% Kachel 1 Wert
#define KoVIS_CHWz0KO2                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz0KO2)))
// Raum %C% Kachel 1 Zusatz
#define KoVIS_CHWz0KO3                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz0KO3)))
// Raum %C% Kachel 2 Steuerung
#define KoVIS_CHWz1KO0                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz1KO0)))
// Raum %C% Kachel 2 Status
#define KoVIS_CHWz1KO1                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz1KO1)))
// Raum %C% Kachel 2 Wert
#define KoVIS_CHWz1KO2                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz1KO2)))
// Raum %C% Kachel 2 Zusatz
#define KoVIS_CHWz1KO3                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz1KO3)))
// Raum %C% Kachel 3 Steuerung
#define KoVIS_CHWz2KO0                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz2KO0)))
// Raum %C% Kachel 3 Status
#define KoVIS_CHWz2KO1                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz2KO1)))
// Raum %C% Kachel 3 Wert
#define KoVIS_CHWz2KO2                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz2KO2)))
// Raum %C% Kachel 3 Zusatz
#define KoVIS_CHWz2KO3                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz2KO3)))
// Raum %C% Kachel 4 Steuerung
#define KoVIS_CHWz3KO0                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz3KO0)))
// Raum %C% Kachel 4 Status
#define KoVIS_CHWz3KO1                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz3KO1)))
// Raum %C% Kachel 4 Wert
#define KoVIS_CHWz3KO2                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz3KO2)))
// Raum %C% Kachel 4 Zusatz
#define KoVIS_CHWz3KO3                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz3KO3)))
// Raum %C% Kachel 5 Steuerung
#define KoVIS_CHWz4KO0                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz4KO0)))
// Raum %C% Kachel 5 Status
#define KoVIS_CHWz4KO1                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz4KO1)))
// Raum %C% Kachel 5 Wert
#define KoVIS_CHWz4KO2                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz4KO2)))
// Raum %C% Kachel 5 Zusatz
#define KoVIS_CHWz4KO3                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz4KO3)))
// Raum %C% Kachel 6 Steuerung
#define KoVIS_CHWz5KO0                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz5KO0)))
// Raum %C% Kachel 6 Status
#define KoVIS_CHWz5KO1                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz5KO1)))
// Raum %C% Kachel 6 Wert
#define KoVIS_CHWz5KO2                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz5KO2)))
// Raum %C% Kachel 6 Zusatz
#define KoVIS_CHWz5KO3                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz5KO3)))
// Raum %C% Kachel 7 Steuerung
#define KoVIS_CHWz6KO0                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz6KO0)))
// Raum %C% Kachel 7 Status
#define KoVIS_CHWz6KO1                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz6KO1)))
// Raum %C% Kachel 7 Wert
#define KoVIS_CHWz6KO2                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz6KO2)))
// Raum %C% Kachel 7 Zusatz
#define KoVIS_CHWz6KO3                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz6KO3)))
// Raum %C% Kachel 8 Steuerung
#define KoVIS_CHWz7KO0                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz7KO0)))
// Raum %C% Kachel 8 Status
#define KoVIS_CHWz7KO1                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz7KO1)))
// Raum %C% Kachel 8 Wert
#define KoVIS_CHWz7KO2                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz7KO2)))
// Raum %C% Kachel 8 Zusatz
#define KoVIS_CHWz7KO3                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz7KO3)))
// Raum %C% Kachel 9 Steuerung
#define KoVIS_CHWz8KO0                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz8KO0)))
// Raum %C% Kachel 9 Status
#define KoVIS_CHWz8KO1                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz8KO1)))
// Raum %C% Kachel 9 Wert
#define KoVIS_CHWz8KO2                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz8KO2)))
// Raum %C% Kachel 9 Zusatz
#define KoVIS_CHWz8KO3                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz8KO3)))
// Raum %C% Kachel 10 Steuerung
#define KoVIS_CHWz9KO0                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz9KO0)))
// Raum %C% Kachel 10 Status
#define KoVIS_CHWz9KO1                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz9KO1)))
// Raum %C% Kachel 10 Wert
#define KoVIS_CHWz9KO2                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz9KO2)))
// Raum %C% Kachel 10 Zusatz
#define KoVIS_CHWz9KO3                            (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz9KO3)))
// Raum %C% Kachel 11 Steuerung
#define KoVIS_CHWz10KO0                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz10KO0)))
// Raum %C% Kachel 11 Status
#define KoVIS_CHWz10KO1                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz10KO1)))
// Raum %C% Kachel 11 Wert
#define KoVIS_CHWz10KO2                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz10KO2)))
// Raum %C% Kachel 11 Zusatz
#define KoVIS_CHWz10KO3                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz10KO3)))
// Raum %C% Kachel 12 Steuerung
#define KoVIS_CHWz11KO0                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz11KO0)))
// Raum %C% Kachel 12 Status
#define KoVIS_CHWz11KO1                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz11KO1)))
// Raum %C% Kachel 12 Wert
#define KoVIS_CHWz11KO2                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz11KO2)))
// Raum %C% Kachel 12 Zusatz
#define KoVIS_CHWz11KO3                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz11KO3)))
// Raum %C% Kachel 13 Steuerung
#define KoVIS_CHWz12KO0                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz12KO0)))
// Raum %C% Kachel 13 Status
#define KoVIS_CHWz12KO1                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz12KO1)))
// Raum %C% Kachel 13 Wert
#define KoVIS_CHWz12KO2                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz12KO2)))
// Raum %C% Kachel 13 Zusatz
#define KoVIS_CHWz12KO3                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz12KO3)))
// Raum %C% Kachel 14 Steuerung
#define KoVIS_CHWz13KO0                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz13KO0)))
// Raum %C% Kachel 14 Status
#define KoVIS_CHWz13KO1                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz13KO1)))
// Raum %C% Kachel 14 Wert
#define KoVIS_CHWz13KO2                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz13KO2)))
// Raum %C% Kachel 14 Zusatz
#define KoVIS_CHWz13KO3                           (knx.getGroupObject(VIS_KoCalcNumber(VIS_KoCHWz13KO3)))

#define LOG_VisibleChannels                     5464      // uint8_t
#define LOG_VacationKo                          5465      // 1 Bit, Bit 7
#define     LOG_VacationKoMask 0x80
#define     LOG_VacationKoShift 7
#define LOG_HolidayKo                           5465      // 1 Bit, Bit 6
#define     LOG_HolidayKoMask 0x40
#define     LOG_HolidayKoShift 6
#define LOG_VacationRead                        5465      // 1 Bit, Bit 5
#define     LOG_VacationReadMask 0x20
#define     LOG_VacationReadShift 5
#define LOG_HolidaySend                         5465      // 1 Bit, Bit 4
#define     LOG_HolidaySendMask 0x10
#define     LOG_HolidaySendShift 4
#define LOG_Neujahr                             5466      // 1 Bit, Bit 7
#define     LOG_NeujahrMask 0x80
#define     LOG_NeujahrShift 7
#define LOG_DreiKoenige                         5466      // 1 Bit, Bit 6
#define     LOG_DreiKoenigeMask 0x40
#define     LOG_DreiKoenigeShift 6
#define LOG_Weiberfastnacht                     5466      // 1 Bit, Bit 5
#define     LOG_WeiberfastnachtMask 0x20
#define     LOG_WeiberfastnachtShift 5
#define LOG_Rosenmontag                         5466      // 1 Bit, Bit 4
#define     LOG_RosenmontagMask 0x10
#define     LOG_RosenmontagShift 4
#define LOG_Fastnachtsdienstag                  5466      // 1 Bit, Bit 3
#define     LOG_FastnachtsdienstagMask 0x08
#define     LOG_FastnachtsdienstagShift 3
#define LOG_Aschermittwoch                      5466      // 1 Bit, Bit 2
#define     LOG_AschermittwochMask 0x04
#define     LOG_AschermittwochShift 2
#define LOG_Frauentag                           5466      // 1 Bit, Bit 1
#define     LOG_FrauentagMask 0x02
#define     LOG_FrauentagShift 1
#define LOG_Gruendonnerstag                     5466      // 1 Bit, Bit 0
#define     LOG_GruendonnerstagMask 0x01
#define     LOG_GruendonnerstagShift 0
#define LOG_Karfreitag                          5467      // 1 Bit, Bit 7
#define     LOG_KarfreitagMask 0x80
#define     LOG_KarfreitagShift 7
#define LOG_Ostersonntag                        5467      // 1 Bit, Bit 6
#define     LOG_OstersonntagMask 0x40
#define     LOG_OstersonntagShift 6
#define LOG_Ostermontag                         5467      // 1 Bit, Bit 5
#define     LOG_OstermontagMask 0x20
#define     LOG_OstermontagShift 5
#define LOG_TagDerArbeit                        5467      // 1 Bit, Bit 4
#define     LOG_TagDerArbeitMask 0x10
#define     LOG_TagDerArbeitShift 4
#define LOG_Himmelfahrt                         5467      // 1 Bit, Bit 3
#define     LOG_HimmelfahrtMask 0x08
#define     LOG_HimmelfahrtShift 3
#define LOG_Pfingstsonntag                      5467      // 1 Bit, Bit 2
#define     LOG_PfingstsonntagMask 0x04
#define     LOG_PfingstsonntagShift 2
#define LOG_Pfingstmontag                       5467      // 1 Bit, Bit 1
#define     LOG_PfingstmontagMask 0x02
#define     LOG_PfingstmontagShift 1
#define LOG_Fronleichnam                        5467      // 1 Bit, Bit 0
#define     LOG_FronleichnamMask 0x01
#define     LOG_FronleichnamShift 0
#define LOG_Friedensfest                        5468      // 1 Bit, Bit 7
#define     LOG_FriedensfestMask 0x80
#define     LOG_FriedensfestShift 7
#define LOG_MariaHimmelfahrt                    5468      // 1 Bit, Bit 6
#define     LOG_MariaHimmelfahrtMask 0x40
#define     LOG_MariaHimmelfahrtShift 6
#define LOG_DeutscheEinheit                     5468      // 1 Bit, Bit 5
#define     LOG_DeutscheEinheitMask 0x20
#define     LOG_DeutscheEinheitShift 5
#define LOG_Reformationstag                     5468      // 1 Bit, Bit 4
#define     LOG_ReformationstagMask 0x10
#define     LOG_ReformationstagShift 4
#define LOG_Allerheiligen                       5468      // 1 Bit, Bit 3
#define     LOG_AllerheiligenMask 0x08
#define     LOG_AllerheiligenShift 3
#define LOG_BussBettag                          5468      // 1 Bit, Bit 2
#define     LOG_BussBettagMask 0x04
#define     LOG_BussBettagShift 2
#define LOG_Advent1                             5468      // 1 Bit, Bit 1
#define     LOG_Advent1Mask 0x02
#define     LOG_Advent1Shift 1
#define LOG_Advent2                             5468      // 1 Bit, Bit 0
#define     LOG_Advent2Mask 0x01
#define     LOG_Advent2Shift 0
#define LOG_Advent3                             5469      // 1 Bit, Bit 7
#define     LOG_Advent3Mask 0x80
#define     LOG_Advent3Shift 7
#define LOG_Advent4                             5469      // 1 Bit, Bit 6
#define     LOG_Advent4Mask 0x40
#define     LOG_Advent4Shift 6
#define LOG_Heiligabend                         5469      // 1 Bit, Bit 5
#define     LOG_HeiligabendMask 0x20
#define     LOG_HeiligabendShift 5
#define LOG_Weihnachtstag1                      5469      // 1 Bit, Bit 4
#define     LOG_Weihnachtstag1Mask 0x10
#define     LOG_Weihnachtstag1Shift 4
#define LOG_Weihnachtstag2                      5469      // 1 Bit, Bit 3
#define     LOG_Weihnachtstag2Mask 0x08
#define     LOG_Weihnachtstag2Shift 3
#define LOG_Silvester                           5469      // 1 Bit, Bit 2
#define     LOG_SilvesterMask 0x04
#define     LOG_SilvesterShift 2
#define LOG_Nationalfeiertag                    5469      // 1 Bit, Bit 1
#define     LOG_NationalfeiertagMask 0x02
#define     LOG_NationalfeiertagShift 1
#define LOG_MariaEmpfaengnis                    5469      // 1 Bit, Bit 0
#define     LOG_MariaEmpfaengnisMask 0x01
#define     LOG_MariaEmpfaengnisShift 0
#define LOG_NationalfeiertagSchweiz             5470      // 1 Bit, Bit 7
#define     LOG_NationalfeiertagSchweizMask 0x80
#define     LOG_NationalfeiertagSchweizShift 7
#define LOG_Totensonntag                        5470      // 1 Bit, Bit 6
#define     LOG_TotensonntagMask 0x40
#define     LOG_TotensonntagShift 6
#define LOG_Weltkindertag                       5470      // 1 Bit, Bit 5
#define     LOG_WeltkindertagMask 0x20
#define     LOG_WeltkindertagShift 5
#define LOG_UserFormula1                        5471      // char*, 99 Byte
#define     LOG_UserFormula1Length 99
#define LOG_UserFormula1Active                  5570      // 1 Bit, Bit 7
#define     LOG_UserFormula1ActiveMask 0x80
#define     LOG_UserFormula1ActiveShift 7
#define LOG_UserFormula2                        5571      // char*, 99 Byte
#define     LOG_UserFormula2Length 99
#define LOG_UserFormula2Active                  5670      // 1 Bit, Bit 7
#define     LOG_UserFormula2ActiveMask 0x80
#define     LOG_UserFormula2ActiveShift 7
#define LOG_UserFormula3                        5671      // char*, 99 Byte
#define     LOG_UserFormula3Length 99
#define LOG_UserFormula3Active                  5770      // 1 Bit, Bit 7
#define     LOG_UserFormula3ActiveMask 0x80
#define     LOG_UserFormula3ActiveShift 7
#define LOG_UserFormula4                        5771      // char*, 99 Byte
#define     LOG_UserFormula4Length 99
#define LOG_UserFormula4Active                  5870      // 1 Bit, Bit 7
#define     LOG_UserFormula4ActiveMask 0x80
#define     LOG_UserFormula4ActiveShift 7
#define LOG_UserFormula5                        5871      // char*, 99 Byte
#define     LOG_UserFormula5Length 99
#define LOG_UserFormula5Active                  5970      // 1 Bit, Bit 7
#define     LOG_UserFormula5ActiveMask 0x80
#define     LOG_UserFormula5ActiveShift 7
#define LOG_UserFormula6                        5971      // char*, 99 Byte
#define     LOG_UserFormula6Length 99
#define LOG_UserFormula6Active                  6070      // 1 Bit, Bit 7
#define     LOG_UserFormula6ActiveMask 0x80
#define     LOG_UserFormula6ActiveShift 7
#define LOG_UserFormula7                        6071      // char*, 99 Byte
#define     LOG_UserFormula7Length 99
#define LOG_UserFormula7Active                  6170      // 1 Bit, Bit 7
#define     LOG_UserFormula7ActiveMask 0x80
#define     LOG_UserFormula7ActiveShift 7
#define LOG_UserFormula8                        6171      // char*, 99 Byte
#define     LOG_UserFormula8Length 99
#define LOG_UserFormula8Active                  6270      // 1 Bit, Bit 7
#define     LOG_UserFormula8ActiveMask 0x80
#define     LOG_UserFormula8ActiveShift 7
#define LOG_UserFormula9                        6271      // char*, 99 Byte
#define     LOG_UserFormula9Length 99
#define LOG_UserFormula9Active                  6370      // 1 Bit, Bit 7
#define     LOG_UserFormula9ActiveMask 0x80
#define     LOG_UserFormula9ActiveShift 7
#define LOG_UserFormula10                       6371      // char*, 99 Byte
#define     LOG_UserFormula10Length 99
#define LOG_UserFormula10Active                 6470      // 1 Bit, Bit 7
#define     LOG_UserFormula10ActiveMask 0x80
#define     LOG_UserFormula10ActiveShift 7
#define LOG_UserFormula11                       6471      // char*, 99 Byte
#define     LOG_UserFormula11Length 99
#define LOG_UserFormula11Active                 6570      // 1 Bit, Bit 7
#define     LOG_UserFormula11ActiveMask 0x80
#define     LOG_UserFormula11ActiveShift 7
#define LOG_UserFormula12                       6571      // char*, 99 Byte
#define     LOG_UserFormula12Length 99
#define LOG_UserFormula12Active                 6670      // 1 Bit, Bit 7
#define     LOG_UserFormula12ActiveMask 0x80
#define     LOG_UserFormula12ActiveShift 7
#define LOG_UserFormula13                       6671      // char*, 99 Byte
#define     LOG_UserFormula13Length 99
#define LOG_UserFormula13Active                 6770      // 1 Bit, Bit 7
#define     LOG_UserFormula13ActiveMask 0x80
#define     LOG_UserFormula13ActiveShift 7
#define LOG_UserFormula14                       6771      // char*, 99 Byte
#define     LOG_UserFormula14Length 99
#define LOG_UserFormula14Active                 6870      // 1 Bit, Bit 7
#define     LOG_UserFormula14ActiveMask 0x80
#define     LOG_UserFormula14ActiveShift 7
#define LOG_UserFormula15                       6871      // char*, 99 Byte
#define     LOG_UserFormula15Length 99
#define LOG_UserFormula15Active                 6970      // 1 Bit, Bit 7
#define     LOG_UserFormula15ActiveMask 0x80
#define     LOG_UserFormula15ActiveShift 7
#define LOG_UserFormula16                       6971      // char*, 99 Byte
#define     LOG_UserFormula16Length 99
#define LOG_UserFormula16Active                 7070      // 1 Bit, Bit 7
#define     LOG_UserFormula16ActiveMask 0x80
#define     LOG_UserFormula16ActiveShift 7
#define LOG_UserFormula17                       7071      // char*, 99 Byte
#define     LOG_UserFormula17Length 99
#define LOG_UserFormula17Active                 7170      // 1 Bit, Bit 7
#define     LOG_UserFormula17ActiveMask 0x80
#define     LOG_UserFormula17ActiveShift 7
#define LOG_UserFormula18                       7171      // char*, 99 Byte
#define     LOG_UserFormula18Length 99
#define LOG_UserFormula18Active                 7270      // 1 Bit, Bit 7
#define     LOG_UserFormula18ActiveMask 0x80
#define     LOG_UserFormula18ActiveShift 7
#define LOG_UserFormula19                       7271      // char*, 99 Byte
#define     LOG_UserFormula19Length 99
#define LOG_UserFormula19Active                 7370      // 1 Bit, Bit 7
#define     LOG_UserFormula19ActiveMask 0x80
#define     LOG_UserFormula19ActiveShift 7
#define LOG_UserFormula20                       7371      // char*, 99 Byte
#define     LOG_UserFormula20Length 99
#define LOG_UserFormula20Active                 7470      // 1 Bit, Bit 7
#define     LOG_UserFormula20ActiveMask 0x80
#define     LOG_UserFormula20ActiveShift 7
#define LOG_UserFormula21                       7471      // char*, 99 Byte
#define     LOG_UserFormula21Length 99
#define LOG_UserFormula21Active                 7570      // 1 Bit, Bit 7
#define     LOG_UserFormula21ActiveMask 0x80
#define     LOG_UserFormula21ActiveShift 7
#define LOG_UserFormula22                       7571      // char*, 99 Byte
#define     LOG_UserFormula22Length 99
#define LOG_UserFormula22Active                 7670      // 1 Bit, Bit 7
#define     LOG_UserFormula22ActiveMask 0x80
#define     LOG_UserFormula22ActiveShift 7
#define LOG_UserFormula23                       7671      // char*, 99 Byte
#define     LOG_UserFormula23Length 99
#define LOG_UserFormula23Active                 7770      // 1 Bit, Bit 7
#define     LOG_UserFormula23ActiveMask 0x80
#define     LOG_UserFormula23ActiveShift 7
#define LOG_UserFormula24                       7771      // char*, 99 Byte
#define     LOG_UserFormula24Length 99
#define LOG_UserFormula24Active                 7870      // 1 Bit, Bit 7
#define     LOG_UserFormula24ActiveMask 0x80
#define     LOG_UserFormula24ActiveShift 7
#define LOG_UserFormula25                       7871      // char*, 99 Byte
#define     LOG_UserFormula25Length 99
#define LOG_UserFormula25Active                 7970      // 1 Bit, Bit 7
#define     LOG_UserFormula25ActiveMask 0x80
#define     LOG_UserFormula25ActiveShift 7
#define LOG_UserFormula26                       7971      // char*, 99 Byte
#define     LOG_UserFormula26Length 99
#define LOG_UserFormula26Active                 8070      // 1 Bit, Bit 7
#define     LOG_UserFormula26ActiveMask 0x80
#define     LOG_UserFormula26ActiveShift 7
#define LOG_UserFormula27                       8071      // char*, 99 Byte
#define     LOG_UserFormula27Length 99
#define LOG_UserFormula27Active                 8170      // 1 Bit, Bit 7
#define     LOG_UserFormula27ActiveMask 0x80
#define     LOG_UserFormula27ActiveShift 7
#define LOG_UserFormula28                       8171      // char*, 99 Byte
#define     LOG_UserFormula28Length 99
#define LOG_UserFormula28Active                 8270      // 1 Bit, Bit 7
#define     LOG_UserFormula28ActiveMask 0x80
#define     LOG_UserFormula28ActiveShift 7
#define LOG_UserFormula29                       8271      // char*, 99 Byte
#define     LOG_UserFormula29Length 99
#define LOG_UserFormula29Active                 8370      // 1 Bit, Bit 7
#define     LOG_UserFormula29ActiveMask 0x80
#define     LOG_UserFormula29ActiveShift 7
#define LOG_UserFormula30                       8371      // char*, 99 Byte
#define     LOG_UserFormula30Length 99
#define LOG_UserFormula30Active                 8470      // 1 Bit, Bit 7
#define     LOG_UserFormula30ActiveMask 0x80
#define     LOG_UserFormula30ActiveShift 7

// Verfügbare Kanäle
#define ParamLOG_VisibleChannels                     (knx.paramByte(LOG_VisibleChannels))
// Urlaubsbehandlung aktivieren?
#define ParamLOG_VacationKo                          ((bool)(knx.paramByte(LOG_VacationKo) & LOG_VacationKoMask))
// Feiertage auf dem Bus verfügbar machen?
#define ParamLOG_HolidayKo                           ((bool)(knx.paramByte(LOG_HolidayKo) & LOG_HolidayKoMask))
// Nach Neustart Urlaubsinfo lesen?
#define ParamLOG_VacationRead                        ((bool)(knx.paramByte(LOG_VacationRead) & LOG_VacationReadMask))
// Nach Neuberechnung Feiertagsinfo senden?
#define ParamLOG_HolidaySend                         ((bool)(knx.paramByte(LOG_HolidaySend) & LOG_HolidaySendMask))
// 1. Neujahr
#define ParamLOG_Neujahr                             ((bool)(knx.paramByte(LOG_Neujahr) & LOG_NeujahrMask))
// 2. Heilige Drei Könige
#define ParamLOG_DreiKoenige                         ((bool)(knx.paramByte(LOG_DreiKoenige) & LOG_DreiKoenigeMask))
// 3. Weiberfastnacht
#define ParamLOG_Weiberfastnacht                     ((bool)(knx.paramByte(LOG_Weiberfastnacht) & LOG_WeiberfastnachtMask))
// 4. Rosenmontag
#define ParamLOG_Rosenmontag                         ((bool)(knx.paramByte(LOG_Rosenmontag) & LOG_RosenmontagMask))
// 5. Fastnachtsdienstag
#define ParamLOG_Fastnachtsdienstag                  ((bool)(knx.paramByte(LOG_Fastnachtsdienstag) & LOG_FastnachtsdienstagMask))
// 6. Aschermittwoch
#define ParamLOG_Aschermittwoch                      ((bool)(knx.paramByte(LOG_Aschermittwoch) & LOG_AschermittwochMask))
// 7. Frauentag
#define ParamLOG_Frauentag                           ((bool)(knx.paramByte(LOG_Frauentag) & LOG_FrauentagMask))
// 8. Gründonnerstag
#define ParamLOG_Gruendonnerstag                     ((bool)(knx.paramByte(LOG_Gruendonnerstag) & LOG_GruendonnerstagMask))
// 9. Karfreitag
#define ParamLOG_Karfreitag                          ((bool)(knx.paramByte(LOG_Karfreitag) & LOG_KarfreitagMask))
// 10. Ostersonntag
#define ParamLOG_Ostersonntag                        ((bool)(knx.paramByte(LOG_Ostersonntag) & LOG_OstersonntagMask))
// 11. Ostermontag
#define ParamLOG_Ostermontag                         ((bool)(knx.paramByte(LOG_Ostermontag) & LOG_OstermontagMask))
// 12. Tag der Arbeit
#define ParamLOG_TagDerArbeit                        ((bool)(knx.paramByte(LOG_TagDerArbeit) & LOG_TagDerArbeitMask))
// 13. Christi Himmelfahrt
#define ParamLOG_Himmelfahrt                         ((bool)(knx.paramByte(LOG_Himmelfahrt) & LOG_HimmelfahrtMask))
// 14. Pfingstsonntag
#define ParamLOG_Pfingstsonntag                      ((bool)(knx.paramByte(LOG_Pfingstsonntag) & LOG_PfingstsonntagMask))
// 15. Pfingstmontag
#define ParamLOG_Pfingstmontag                       ((bool)(knx.paramByte(LOG_Pfingstmontag) & LOG_PfingstmontagMask))
// 16. Fronleichnam
#define ParamLOG_Fronleichnam                        ((bool)(knx.paramByte(LOG_Fronleichnam) & LOG_FronleichnamMask))
// 17. Hohes Friedensfest
#define ParamLOG_Friedensfest                        ((bool)(knx.paramByte(LOG_Friedensfest) & LOG_FriedensfestMask))
// 18. Mariä Himmelfahrt
#define ParamLOG_MariaHimmelfahrt                    ((bool)(knx.paramByte(LOG_MariaHimmelfahrt) & LOG_MariaHimmelfahrtMask))
// 19. Tag der Deutschen Einheit
#define ParamLOG_DeutscheEinheit                     ((bool)(knx.paramByte(LOG_DeutscheEinheit) & LOG_DeutscheEinheitMask))
// 20. Reformationstag
#define ParamLOG_Reformationstag                     ((bool)(knx.paramByte(LOG_Reformationstag) & LOG_ReformationstagMask))
// 21. Allerheiligen
#define ParamLOG_Allerheiligen                       ((bool)(knx.paramByte(LOG_Allerheiligen) & LOG_AllerheiligenMask))
// 22. Buß- und Bettag
#define ParamLOG_BussBettag                          ((bool)(knx.paramByte(LOG_BussBettag) & LOG_BussBettagMask))
// 23. Erster Advent
#define ParamLOG_Advent1                             ((bool)(knx.paramByte(LOG_Advent1) & LOG_Advent1Mask))
// 24. Zweiter Advent
#define ParamLOG_Advent2                             ((bool)(knx.paramByte(LOG_Advent2) & LOG_Advent2Mask))
// 25. Dritter Advent
#define ParamLOG_Advent3                             ((bool)(knx.paramByte(LOG_Advent3) & LOG_Advent3Mask))
// 26. Vierter Advent
#define ParamLOG_Advent4                             ((bool)(knx.paramByte(LOG_Advent4) & LOG_Advent4Mask))
// 27. Heiligabend
#define ParamLOG_Heiligabend                         ((bool)(knx.paramByte(LOG_Heiligabend) & LOG_HeiligabendMask))
// 28. Erster Weihnachtstag
#define ParamLOG_Weihnachtstag1                      ((bool)(knx.paramByte(LOG_Weihnachtstag1) & LOG_Weihnachtstag1Mask))
// 29. Zweiter Weihnachtstag
#define ParamLOG_Weihnachtstag2                      ((bool)(knx.paramByte(LOG_Weihnachtstag2) & LOG_Weihnachtstag2Mask))
// 30. Silvester
#define ParamLOG_Silvester                           ((bool)(knx.paramByte(LOG_Silvester) & LOG_SilvesterMask))
// 31. Nationalfeiertag (AT)
#define ParamLOG_Nationalfeiertag                    ((bool)(knx.paramByte(LOG_Nationalfeiertag) & LOG_NationalfeiertagMask))
// 32. Maria Empfängnis (AT)
#define ParamLOG_MariaEmpfaengnis                    ((bool)(knx.paramByte(LOG_MariaEmpfaengnis) & LOG_MariaEmpfaengnisMask))
// 33. Nationalfeiertag (CH)
#define ParamLOG_NationalfeiertagSchweiz             ((bool)(knx.paramByte(LOG_NationalfeiertagSchweiz) & LOG_NationalfeiertagSchweizMask))
// 34. Totensonntag
#define ParamLOG_Totensonntag                        ((bool)(knx.paramByte(LOG_Totensonntag) & LOG_TotensonntagMask))
// 35. Weltkindertag
#define ParamLOG_Weltkindertag                       ((bool)(knx.paramByte(LOG_Weltkindertag) & LOG_WeltkindertagMask))
// Formeldefinition
#define ParamLOG_UserFormula1                        (knx.paramData(LOG_UserFormula1))
#define ParamLOG_UserFormula1Str                     (knx.paramString(LOG_UserFormula1, LOG_UserFormula1Length))
// Benutzerformel 1 aktiv
#define ParamLOG_UserFormula1Active                  ((bool)(knx.paramByte(LOG_UserFormula1Active) & LOG_UserFormula1ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula2                        (knx.paramData(LOG_UserFormula2))
#define ParamLOG_UserFormula2Str                     (knx.paramString(LOG_UserFormula2, LOG_UserFormula2Length))
// Benutzerformel 2 aktiv
#define ParamLOG_UserFormula2Active                  ((bool)(knx.paramByte(LOG_UserFormula2Active) & LOG_UserFormula2ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula3                        (knx.paramData(LOG_UserFormula3))
#define ParamLOG_UserFormula3Str                     (knx.paramString(LOG_UserFormula3, LOG_UserFormula3Length))
// Benutzerformel 3 aktiv
#define ParamLOG_UserFormula3Active                  ((bool)(knx.paramByte(LOG_UserFormula3Active) & LOG_UserFormula3ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula4                        (knx.paramData(LOG_UserFormula4))
#define ParamLOG_UserFormula4Str                     (knx.paramString(LOG_UserFormula4, LOG_UserFormula4Length))
// Benutzerformel 4 aktiv
#define ParamLOG_UserFormula4Active                  ((bool)(knx.paramByte(LOG_UserFormula4Active) & LOG_UserFormula4ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula5                        (knx.paramData(LOG_UserFormula5))
#define ParamLOG_UserFormula5Str                     (knx.paramString(LOG_UserFormula5, LOG_UserFormula5Length))
// Benutzerformel 5 aktiv
#define ParamLOG_UserFormula5Active                  ((bool)(knx.paramByte(LOG_UserFormula5Active) & LOG_UserFormula5ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula6                        (knx.paramData(LOG_UserFormula6))
#define ParamLOG_UserFormula6Str                     (knx.paramString(LOG_UserFormula6, LOG_UserFormula6Length))
// Benutzerformel 6 aktiv
#define ParamLOG_UserFormula6Active                  ((bool)(knx.paramByte(LOG_UserFormula6Active) & LOG_UserFormula6ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula7                        (knx.paramData(LOG_UserFormula7))
#define ParamLOG_UserFormula7Str                     (knx.paramString(LOG_UserFormula7, LOG_UserFormula7Length))
// Benutzerformel 7 aktiv
#define ParamLOG_UserFormula7Active                  ((bool)(knx.paramByte(LOG_UserFormula7Active) & LOG_UserFormula7ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula8                        (knx.paramData(LOG_UserFormula8))
#define ParamLOG_UserFormula8Str                     (knx.paramString(LOG_UserFormula8, LOG_UserFormula8Length))
// Benutzerformel 8 aktiv
#define ParamLOG_UserFormula8Active                  ((bool)(knx.paramByte(LOG_UserFormula8Active) & LOG_UserFormula8ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula9                        (knx.paramData(LOG_UserFormula9))
#define ParamLOG_UserFormula9Str                     (knx.paramString(LOG_UserFormula9, LOG_UserFormula9Length))
// Benutzerformel 9 aktiv
#define ParamLOG_UserFormula9Active                  ((bool)(knx.paramByte(LOG_UserFormula9Active) & LOG_UserFormula9ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula10                       (knx.paramData(LOG_UserFormula10))
#define ParamLOG_UserFormula10Str                    (knx.paramString(LOG_UserFormula10, LOG_UserFormula10Length))
// Benutzerformel 10 aktiv
#define ParamLOG_UserFormula10Active                 ((bool)(knx.paramByte(LOG_UserFormula10Active) & LOG_UserFormula10ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula11                       (knx.paramData(LOG_UserFormula11))
#define ParamLOG_UserFormula11Str                    (knx.paramString(LOG_UserFormula11, LOG_UserFormula11Length))
// Benutzerformel 11 aktiv
#define ParamLOG_UserFormula11Active                 ((bool)(knx.paramByte(LOG_UserFormula11Active) & LOG_UserFormula11ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula12                       (knx.paramData(LOG_UserFormula12))
#define ParamLOG_UserFormula12Str                    (knx.paramString(LOG_UserFormula12, LOG_UserFormula12Length))
// Benutzerformel 12 aktiv
#define ParamLOG_UserFormula12Active                 ((bool)(knx.paramByte(LOG_UserFormula12Active) & LOG_UserFormula12ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula13                       (knx.paramData(LOG_UserFormula13))
#define ParamLOG_UserFormula13Str                    (knx.paramString(LOG_UserFormula13, LOG_UserFormula13Length))
// Benutzerformel 13 aktiv
#define ParamLOG_UserFormula13Active                 ((bool)(knx.paramByte(LOG_UserFormula13Active) & LOG_UserFormula13ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula14                       (knx.paramData(LOG_UserFormula14))
#define ParamLOG_UserFormula14Str                    (knx.paramString(LOG_UserFormula14, LOG_UserFormula14Length))
// Benutzerformel 14 aktiv
#define ParamLOG_UserFormula14Active                 ((bool)(knx.paramByte(LOG_UserFormula14Active) & LOG_UserFormula14ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula15                       (knx.paramData(LOG_UserFormula15))
#define ParamLOG_UserFormula15Str                    (knx.paramString(LOG_UserFormula15, LOG_UserFormula15Length))
// Benutzerformel 15 aktiv
#define ParamLOG_UserFormula15Active                 ((bool)(knx.paramByte(LOG_UserFormula15Active) & LOG_UserFormula15ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula16                       (knx.paramData(LOG_UserFormula16))
#define ParamLOG_UserFormula16Str                    (knx.paramString(LOG_UserFormula16, LOG_UserFormula16Length))
// Benutzerformel 16 aktiv
#define ParamLOG_UserFormula16Active                 ((bool)(knx.paramByte(LOG_UserFormula16Active) & LOG_UserFormula16ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula17                       (knx.paramData(LOG_UserFormula17))
#define ParamLOG_UserFormula17Str                    (knx.paramString(LOG_UserFormula17, LOG_UserFormula17Length))
// Benutzerformel 17 aktiv
#define ParamLOG_UserFormula17Active                 ((bool)(knx.paramByte(LOG_UserFormula17Active) & LOG_UserFormula17ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula18                       (knx.paramData(LOG_UserFormula18))
#define ParamLOG_UserFormula18Str                    (knx.paramString(LOG_UserFormula18, LOG_UserFormula18Length))
// Benutzerformel 18 aktiv
#define ParamLOG_UserFormula18Active                 ((bool)(knx.paramByte(LOG_UserFormula18Active) & LOG_UserFormula18ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula19                       (knx.paramData(LOG_UserFormula19))
#define ParamLOG_UserFormula19Str                    (knx.paramString(LOG_UserFormula19, LOG_UserFormula19Length))
// Benutzerformel 19 aktiv
#define ParamLOG_UserFormula19Active                 ((bool)(knx.paramByte(LOG_UserFormula19Active) & LOG_UserFormula19ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula20                       (knx.paramData(LOG_UserFormula20))
#define ParamLOG_UserFormula20Str                    (knx.paramString(LOG_UserFormula20, LOG_UserFormula20Length))
// Benutzerformel 20 aktiv
#define ParamLOG_UserFormula20Active                 ((bool)(knx.paramByte(LOG_UserFormula20Active) & LOG_UserFormula20ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula21                       (knx.paramData(LOG_UserFormula21))
#define ParamLOG_UserFormula21Str                    (knx.paramString(LOG_UserFormula21, LOG_UserFormula21Length))
// Benutzerformel 21 aktiv
#define ParamLOG_UserFormula21Active                 ((bool)(knx.paramByte(LOG_UserFormula21Active) & LOG_UserFormula21ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula22                       (knx.paramData(LOG_UserFormula22))
#define ParamLOG_UserFormula22Str                    (knx.paramString(LOG_UserFormula22, LOG_UserFormula22Length))
// Benutzerformel 22 aktiv
#define ParamLOG_UserFormula22Active                 ((bool)(knx.paramByte(LOG_UserFormula22Active) & LOG_UserFormula22ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula23                       (knx.paramData(LOG_UserFormula23))
#define ParamLOG_UserFormula23Str                    (knx.paramString(LOG_UserFormula23, LOG_UserFormula23Length))
// Benutzerformel 23 aktiv
#define ParamLOG_UserFormula23Active                 ((bool)(knx.paramByte(LOG_UserFormula23Active) & LOG_UserFormula23ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula24                       (knx.paramData(LOG_UserFormula24))
#define ParamLOG_UserFormula24Str                    (knx.paramString(LOG_UserFormula24, LOG_UserFormula24Length))
// Benutzerformel 24 aktiv
#define ParamLOG_UserFormula24Active                 ((bool)(knx.paramByte(LOG_UserFormula24Active) & LOG_UserFormula24ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula25                       (knx.paramData(LOG_UserFormula25))
#define ParamLOG_UserFormula25Str                    (knx.paramString(LOG_UserFormula25, LOG_UserFormula25Length))
// Benutzerformel 25 aktiv
#define ParamLOG_UserFormula25Active                 ((bool)(knx.paramByte(LOG_UserFormula25Active) & LOG_UserFormula25ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula26                       (knx.paramData(LOG_UserFormula26))
#define ParamLOG_UserFormula26Str                    (knx.paramString(LOG_UserFormula26, LOG_UserFormula26Length))
// Benutzerformel 26 aktiv
#define ParamLOG_UserFormula26Active                 ((bool)(knx.paramByte(LOG_UserFormula26Active) & LOG_UserFormula26ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula27                       (knx.paramData(LOG_UserFormula27))
#define ParamLOG_UserFormula27Str                    (knx.paramString(LOG_UserFormula27, LOG_UserFormula27Length))
// Benutzerformel 27 aktiv
#define ParamLOG_UserFormula27Active                 ((bool)(knx.paramByte(LOG_UserFormula27Active) & LOG_UserFormula27ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula28                       (knx.paramData(LOG_UserFormula28))
#define ParamLOG_UserFormula28Str                    (knx.paramString(LOG_UserFormula28, LOG_UserFormula28Length))
// Benutzerformel 28 aktiv
#define ParamLOG_UserFormula28Active                 ((bool)(knx.paramByte(LOG_UserFormula28Active) & LOG_UserFormula28ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula29                       (knx.paramData(LOG_UserFormula29))
#define ParamLOG_UserFormula29Str                    (knx.paramString(LOG_UserFormula29, LOG_UserFormula29Length))
// Benutzerformel 29 aktiv
#define ParamLOG_UserFormula29Active                 ((bool)(knx.paramByte(LOG_UserFormula29Active) & LOG_UserFormula29ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula30                       (knx.paramData(LOG_UserFormula30))
#define ParamLOG_UserFormula30Str                    (knx.paramString(LOG_UserFormula30, LOG_UserFormula30Length))
// Benutzerformel 30 aktiv
#define ParamLOG_UserFormula30Active                 ((bool)(knx.paramByte(LOG_UserFormula30Active) & LOG_UserFormula30ActiveMask))

#define LOG_KoVacation 15
#define LOG_KoHoliday1 16
#define LOG_KoHoliday2 17

// Urlaub
#define KoLOG_Vacation                            (knx.getGroupObject(LOG_KoVacation))
// Welcher Feiertag ist heute?
#define KoLOG_Holiday1                            (knx.getGroupObject(LOG_KoHoliday1))
// Welcher Feiertag ist morgen?
#define KoLOG_Holiday2                            (knx.getGroupObject(LOG_KoHoliday2))

#define LOG_ChannelCount 50

// Parameter per channel
#define LOG_ParamBlockOffset 8471
#define LOG_ParamBlockSize 87
#define LOG_ParamCalcIndex(index) (index + LOG_ParamBlockOffset + _channelIndex * LOG_ParamBlockSize)

#define LOG_fChannelDelayBase                    0      // 2 Bits, Bit 7-6
#define     LOG_fChannelDelayBaseMask 0xC0
#define     LOG_fChannelDelayBaseShift 6
#define LOG_fChannelDelayTime                    0      // 14 Bits, Bit 13-0
#define     LOG_fChannelDelayTimeMask 0x3FFF
#define     LOG_fChannelDelayTimeShift 0
#define LOG_fLogic                               2      // 8 Bits, Bit 7-0
#define LOG_fCalculate                           3      // 2 Bits, Bit 1-0
#define     LOG_fCalculateMask 0x03
#define     LOG_fCalculateShift 0
#define LOG_fDisable                             3      // 1 Bit, Bit 2
#define     LOG_fDisableMask 0x04
#define     LOG_fDisableShift 2
#define LOG_fTGate                               3      // 1 Bit, Bit 4
#define     LOG_fTGateMask 0x10
#define     LOG_fTGateShift 4
#define LOG_fOInternalOn                         3      // 1 Bit, Bit 5
#define     LOG_fOInternalOnMask 0x20
#define     LOG_fOInternalOnShift 5
#define LOG_fOInternalOff                        3      // 1 Bit, Bit 6
#define     LOG_fOInternalOffMask 0x40
#define     LOG_fOInternalOffShift 6
#define LOG_fTrigger                             4      // 8 Bits, Bit 7-0
#define LOG_fTriggerE1                           4      // 1 Bit, Bit 0
#define     LOG_fTriggerE1Mask 0x01
#define     LOG_fTriggerE1Shift 0
#define LOG_fTriggerE2                           4      // 1 Bit, Bit 1
#define     LOG_fTriggerE2Mask 0x02
#define     LOG_fTriggerE2Shift 1
#define LOG_fTriggerI1                           4      // 1 Bit, Bit 2
#define     LOG_fTriggerI1Mask 0x04
#define     LOG_fTriggerI1Shift 2
#define LOG_fTriggerI2                           4      // 1 Bit, Bit 3
#define     LOG_fTriggerI2Mask 0x08
#define     LOG_fTriggerI2Shift 3
#define LOG_fTriggerTime                         4      // 8 Bits, Bit 7-0
#define LOG_fTriggerGateClose                    5      // 2 Bits, Bit 7-6
#define     LOG_fTriggerGateCloseMask 0xC0
#define     LOG_fTriggerGateCloseShift 6
#define LOG_fTriggerGateOpen                     5      // 2 Bits, Bit 5-4
#define     LOG_fTriggerGateOpenMask 0x30
#define     LOG_fTriggerGateOpenShift 4
#define LOG_fE1ConvertInt                        6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertIntMask 0xF0
#define     LOG_fE1ConvertIntShift 4
#define LOG_fE1Convert                           6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertMask 0xF0
#define     LOG_fE1ConvertShift 4
#define LOG_fE1ConvertFloat                      6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertFloatMask 0xF0
#define     LOG_fE1ConvertFloatShift 4
#define LOG_fE1ConvertSpecial                    6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertSpecialMask 0xF0
#define     LOG_fE1ConvertSpecialShift 4
#define LOG_fE1ConvertBool                       6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertBoolMask 0xF0
#define     LOG_fE1ConvertBoolShift 4
#define LOG_fE1                                  6      // 2 Bits, Bit 1-0
#define     LOG_fE1Mask 0x03
#define     LOG_fE1Shift 0
#define LOG_fE1Dpt                               7      // 8 Bits, Bit 7-0
#define LOG_fE1RepeatBase                        8      // 2 Bits, Bit 7-6
#define     LOG_fE1RepeatBaseMask 0xC0
#define     LOG_fE1RepeatBaseShift 6
#define LOG_fE1RepeatTime                        8      // 14 Bits, Bit 13-0
#define     LOG_fE1RepeatTimeMask 0x3FFF
#define     LOG_fE1RepeatTimeShift 0
#define LOG_fE1OtherKO                          10      // uint16_t
#define LOG_fE1OtherKORel                       10      // int16_t
#define LOG_fE1Default                          12      // 2 Bits, Bit 1-0
#define     LOG_fE1DefaultMask 0x03
#define     LOG_fE1DefaultShift 0
#define LOG_fE1DefaultExt                       12      // 2 Bits, Bit 1-0
#define     LOG_fE1DefaultExtMask 0x03
#define     LOG_fE1DefaultExtShift 0
#define LOG_fE1DefaultEEPROM                    12      // 1 Bit, Bit 2
#define     LOG_fE1DefaultEEPROMMask 0x04
#define     LOG_fE1DefaultEEPROMShift 2
#define LOG_fE1DefaultRepeat                    12      // 1 Bit, Bit 3
#define     LOG_fE1DefaultRepeatMask 0x08
#define     LOG_fE1DefaultRepeatShift 3
#define LOG_fE1UseOtherKO                       12      // 2 Bits, Bit 5-4
#define     LOG_fE1UseOtherKOMask 0x30
#define     LOG_fE1UseOtherKOShift 4
#define LOG_fE1LowDelta                         13      // int32_t
#define LOG_fE1HighDelta                        17      // int32_t
#define LOG_fE1LowDeltaFloat                    13      // float
#define LOG_fE1HighDeltaFloat                   17      // float
#define LOG_fE1LowDeltaDouble                   13      // float
#define LOG_fE1HighDeltaDouble                  17      // float
#define LOG_fE1Low0Valid                        20      // 1 Bit, Bit 7
#define     LOG_fE1Low0ValidMask 0x80
#define     LOG_fE1Low0ValidShift 7
#define LOG_fE1Low1Valid                        20      // 1 Bit, Bit 6
#define     LOG_fE1Low1ValidMask 0x40
#define     LOG_fE1Low1ValidShift 6
#define LOG_fE1Low2Valid                        20      // 1 Bit, Bit 5
#define     LOG_fE1Low2ValidMask 0x20
#define     LOG_fE1Low2ValidShift 5
#define LOG_fE1Low3Valid                        20      // 1 Bit, Bit 4
#define     LOG_fE1Low3ValidMask 0x10
#define     LOG_fE1Low3ValidShift 4
#define LOG_fE1Low4Valid                        20      // 1 Bit, Bit 3
#define     LOG_fE1Low4ValidMask 0x08
#define     LOG_fE1Low4ValidShift 3
#define LOG_fE1Low5Valid                        20      // 1 Bit, Bit 2
#define     LOG_fE1Low5ValidMask 0x04
#define     LOG_fE1Low5ValidShift 2
#define LOG_fE1Low6Valid                        20      // 1 Bit, Bit 1
#define     LOG_fE1Low6ValidMask 0x02
#define     LOG_fE1Low6ValidShift 1
#define LOG_fE1Low0Dpt2                         13      // 8 Bits, Bit 7-0
#define LOG_fE1Low1Dpt2                         14      // 8 Bits, Bit 7-0
#define LOG_fE1Low2Dpt2                         15      // 8 Bits, Bit 7-0
#define LOG_fE1Low3Dpt2                         16      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt2Fix                       13      // 8 Bits, Bit 7-0
#define LOG_fE1Low0Dpt3Dir                      13      // 5 Bits, Bit 7-3
#define     LOG_fE1Low0Dpt3DirMask 0xF8
#define     LOG_fE1Low0Dpt3DirShift 3
#define LOG_fE1Low0Dpt3Dim                      13      // 3 Bits, Bit 2-0
#define     LOG_fE1Low0Dpt3DimMask 0x07
#define     LOG_fE1Low0Dpt3DimShift 0
#define LOG_fE1Low1Dpt3Dir                      14      // 5 Bits, Bit 7-3
#define     LOG_fE1Low1Dpt3DirMask 0xF8
#define     LOG_fE1Low1Dpt3DirShift 3
#define LOG_fE1Low1Dpt3Dim                      14      // 3 Bits, Bit 2-0
#define     LOG_fE1Low1Dpt3DimMask 0x07
#define     LOG_fE1Low1Dpt3DimShift 0
#define LOG_fE1Low2Dpt3Dir                      15      // 5 Bits, Bit 7-3
#define     LOG_fE1Low2Dpt3DirMask 0xF8
#define     LOG_fE1Low2Dpt3DirShift 3
#define LOG_fE1Low2Dpt3Dim                      15      // 3 Bits, Bit 2-0
#define     LOG_fE1Low2Dpt3DimMask 0x07
#define     LOG_fE1Low2Dpt3DimShift 0
#define LOG_fE1Low3Dpt3Dir                      16      // 5 Bits, Bit 7-3
#define     LOG_fE1Low3Dpt3DirMask 0xF8
#define     LOG_fE1Low3Dpt3DirShift 3
#define LOG_fE1Low3Dpt3Dim                      16      // 3 Bits, Bit 2-0
#define     LOG_fE1Low3Dpt3DimMask 0x07
#define     LOG_fE1Low3Dpt3DimShift 0
#define LOG_fE1LowDpt3FixDir                    13      // 5 Bits, Bit 7-3
#define     LOG_fE1LowDpt3FixDirMask 0xF8
#define     LOG_fE1LowDpt3FixDirShift 3
#define LOG_fE1LowDpt3FixDim                    13      // 3 Bits, Bit 2-0
#define     LOG_fE1LowDpt3FixDimMask 0x07
#define     LOG_fE1LowDpt3FixDimShift 0
#define LOG_fE1LowDpt5                          13      // uint8_t
#define LOG_fE1HighDpt5                         17      // uint8_t
#define LOG_fE1Low0Dpt5In                       13      // uint8_t
#define LOG_fE1Low1Dpt5In                       14      // uint8_t
#define LOG_fE1Low2Dpt5In                       15      // uint8_t
#define LOG_fE1Low3Dpt5In                       16      // uint8_t
#define LOG_fE1Low4Dpt5In                       17      // uint8_t
#define LOG_fE1Low5Dpt5In                       18      // uint8_t
#define LOG_fE1Low6Dpt5In                       19      // uint8_t
#define LOG_fE1LowDpt5Fix                       13      // uint8_t
#define LOG_fE1LowDpt5001                       13      // uint8_t
#define LOG_fE1HighDpt5001                      17      // uint8_t
#define LOG_fE1Low0Dpt5xIn                      13      // uint8_t
#define LOG_fE1Low1Dpt5xIn                      14      // uint8_t
#define LOG_fE1Low2Dpt5xIn                      15      // uint8_t
#define LOG_fE1Low3Dpt5xIn                      16      // uint8_t
#define LOG_fE1Low4Dpt5xIn                      17      // uint8_t
#define LOG_fE1Low5Dpt5xIn                      18      // uint8_t
#define LOG_fE1Low6Dpt5xIn                      19      // uint8_t
#define LOG_fE1LowDpt5xFix                      13      // uint8_t
#define LOG_fE1LowDpt6                          13      // int8_t
#define LOG_fE1HighDpt6                         17      // int8_t
#define LOG_fE1Low0Dpt6In                       13      // int8_t
#define LOG_fE1Low1Dpt6In                       14      // int8_t
#define LOG_fE1Low2Dpt6In                       15      // int8_t
#define LOG_fE1Low3Dpt6In                       16      // int8_t
#define LOG_fE1Low4Dpt6In                       17      // int8_t
#define LOG_fE1Low5Dpt6In                       18      // int8_t
#define LOG_fE1Low6Dpt6In                       19      // int8_t
#define LOG_fE1LowDpt6Fix                       13      // int8_t
#define LOG_fE1LowDpt7                          13      // uint16_t
#define LOG_fE1HighDpt7                         17      // uint16_t
#define LOG_fE1Low0Dpt7In                       13      // uint16_t
#define LOG_fE1Low1Dpt7In                       15      // uint16_t
#define LOG_fE1Low2Dpt7In                       17      // uint16_t
#define LOG_fE1LowDpt7Fix                       13      // uint16_t
#define LOG_fE1LowDpt8                          13      // int16_t
#define LOG_fE1HighDpt8                         17      // int16_t
#define LOG_fE1Low0Dpt8In                       13      // int16_t
#define LOG_fE1Low1Dpt8In                       15      // int16_t
#define LOG_fE1Low2Dpt8In                       17      // int16_t
#define LOG_fE1LowDpt8Fix                       13      // int16_t
#define LOG_fE1LowDpt9                          13      // float
#define LOG_fE1HighDpt9                         17      // float
#define LOG_fE1LowDpt9Fix                       13      // float
#define LOG_fE1LowDpt12                         13      // uint32_t
#define LOG_fE1HighDpt12                        17      // uint32_t
#define LOG_fE1LowDpt12Fix                      13      // uint32_t
#define LOG_fE1LowDpt13                         13      // int32_t
#define LOG_fE1HighDpt13                        17      // int32_t
#define LOG_fE1LowDpt13Fix                      13      // int32_t
#define LOG_fE1LowDpt14                         13      // float
#define LOG_fE1HighDpt14                        17      // float
#define LOG_fE1LowDpt14Fix                      13      // float
#define LOG_fE1Low0Dpt17                        13      // 8 Bits, Bit 7-0
#define LOG_fE1Low1Dpt17                        14      // 8 Bits, Bit 7-0
#define LOG_fE1Low2Dpt17                        15      // 8 Bits, Bit 7-0
#define LOG_fE1Low3Dpt17                        16      // 8 Bits, Bit 7-0
#define LOG_fE1Low4Dpt17                        17      // 8 Bits, Bit 7-0
#define LOG_fE1Low5Dpt17                        18      // 8 Bits, Bit 7-0
#define LOG_fE1Low6Dpt17                        19      // 8 Bits, Bit 7-0
#define LOG_fE1Low7Dpt17                        20      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt17Fix                      13      // 8 Bits, Bit 7-0
#define LOG_fE1LowDptRGB                        13      // int32_t
#define LOG_fE1HighDptRGB                       17      // int32_t
#define LOG_fE1LowDptRGBFix                     13      // int32_t
#define LOG_fE2ConvertInt                       21      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertIntMask 0xF0
#define     LOG_fE2ConvertIntShift 4
#define LOG_fE2Convert                          21      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertMask 0xF0
#define     LOG_fE2ConvertShift 4
#define LOG_fE2ConvertFloat                     21      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertFloatMask 0xF0
#define     LOG_fE2ConvertFloatShift 4
#define LOG_fE2ConvertSpecial                   21      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertSpecialMask 0xF0
#define     LOG_fE2ConvertSpecialShift 4
#define LOG_fE2ConvertBool                      21      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertBoolMask 0xF0
#define     LOG_fE2ConvertBoolShift 4
#define LOG_fE2                                 21      // 2 Bits, Bit 1-0
#define     LOG_fE2Mask 0x03
#define     LOG_fE2Shift 0
#define LOG_fE2Dpt                              22      // 8 Bits, Bit 7-0
#define LOG_fE2RepeatBase                       23      // 2 Bits, Bit 7-6
#define     LOG_fE2RepeatBaseMask 0xC0
#define     LOG_fE2RepeatBaseShift 6
#define LOG_fE2RepeatTime                       23      // 14 Bits, Bit 13-0
#define     LOG_fE2RepeatTimeMask 0x3FFF
#define     LOG_fE2RepeatTimeShift 0
#define LOG_fE2OtherKO                          25      // uint16_t
#define LOG_fE2OtherKORel                       25      // int16_t
#define LOG_fE2Default                          27      // 2 Bits, Bit 1-0
#define     LOG_fE2DefaultMask 0x03
#define     LOG_fE2DefaultShift 0
#define LOG_fE2DefaultExt                       27      // 2 Bits, Bit 1-0
#define     LOG_fE2DefaultExtMask 0x03
#define     LOG_fE2DefaultExtShift 0
#define LOG_fE2DefaultEEPROM                    27      // 1 Bit, Bit 2
#define     LOG_fE2DefaultEEPROMMask 0x04
#define     LOG_fE2DefaultEEPROMShift 2
#define LOG_fE2DefaultRepeat                    27      // 1 Bit, Bit 3
#define     LOG_fE2DefaultRepeatMask 0x08
#define     LOG_fE2DefaultRepeatShift 3
#define LOG_fE2UseOtherKO                       27      // 2 Bits, Bit 5-4
#define     LOG_fE2UseOtherKOMask 0x30
#define     LOG_fE2UseOtherKOShift 4
#define LOG_fE2LowDelta                         28      // int32_t
#define LOG_fE2HighDelta                        32      // int32_t
#define LOG_fE2LowDeltaFloat                    28      // float
#define LOG_fE2HighDeltaFloat                   32      // float
#define LOG_fE2LowDeltaDouble                   28      // float
#define LOG_fE2HighDeltaDouble                  32      // float
#define LOG_fE2Low0Valid                        35      // 1 Bit, Bit 7
#define     LOG_fE2Low0ValidMask 0x80
#define     LOG_fE2Low0ValidShift 7
#define LOG_fE2Low1Valid                        35      // 1 Bit, Bit 6
#define     LOG_fE2Low1ValidMask 0x40
#define     LOG_fE2Low1ValidShift 6
#define LOG_fE2Low2Valid                        35      // 1 Bit, Bit 5
#define     LOG_fE2Low2ValidMask 0x20
#define     LOG_fE2Low2ValidShift 5
#define LOG_fE2Low3Valid                        35      // 1 Bit, Bit 4
#define     LOG_fE2Low3ValidMask 0x10
#define     LOG_fE2Low3ValidShift 4
#define LOG_fE2Low4Valid                        35      // 1 Bit, Bit 3
#define     LOG_fE2Low4ValidMask 0x08
#define     LOG_fE2Low4ValidShift 3
#define LOG_fE2Low5Valid                        35      // 1 Bit, Bit 2
#define     LOG_fE2Low5ValidMask 0x04
#define     LOG_fE2Low5ValidShift 2
#define LOG_fE2Low6Valid                        35      // 1 Bit, Bit 1
#define     LOG_fE2Low6ValidMask 0x02
#define     LOG_fE2Low6ValidShift 1
#define LOG_fE2Low0Dpt2                         28      // 8 Bits, Bit 7-0
#define LOG_fE2Low1Dpt2                         29      // 8 Bits, Bit 7-0
#define LOG_fE2Low2Dpt2                         30      // 8 Bits, Bit 7-0
#define LOG_fE2Low3Dpt2                         31      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt2Fix                       28      // 8 Bits, Bit 7-0
#define LOG_fE2Low0Dpt3Dir                      28      // 5 Bits, Bit 7-3
#define     LOG_fE2Low0Dpt3DirMask 0xF8
#define     LOG_fE2Low0Dpt3DirShift 3
#define LOG_fE2Low0Dpt3Dim                      28      // 3 Bits, Bit 2-0
#define     LOG_fE2Low0Dpt3DimMask 0x07
#define     LOG_fE2Low0Dpt3DimShift 0
#define LOG_fE2Low1Dpt3Dir                      29      // 5 Bits, Bit 7-3
#define     LOG_fE2Low1Dpt3DirMask 0xF8
#define     LOG_fE2Low1Dpt3DirShift 3
#define LOG_fE2Low1Dpt3Dim                      29      // 3 Bits, Bit 2-0
#define     LOG_fE2Low1Dpt3DimMask 0x07
#define     LOG_fE2Low1Dpt3DimShift 0
#define LOG_fE2Low2Dpt3Dir                      30      // 5 Bits, Bit 7-3
#define     LOG_fE2Low2Dpt3DirMask 0xF8
#define     LOG_fE2Low2Dpt3DirShift 3
#define LOG_fE2Low2Dpt3Dim                      30      // 3 Bits, Bit 2-0
#define     LOG_fE2Low2Dpt3DimMask 0x07
#define     LOG_fE2Low2Dpt3DimShift 0
#define LOG_fE2Low3Dpt3Dir                      31      // 5 Bits, Bit 7-3
#define     LOG_fE2Low3Dpt3DirMask 0xF8
#define     LOG_fE2Low3Dpt3DirShift 3
#define LOG_fE2Low3Dpt3Dim                      31      // 3 Bits, Bit 2-0
#define     LOG_fE2Low3Dpt3DimMask 0x07
#define     LOG_fE2Low3Dpt3DimShift 0
#define LOG_fE2LowDpt3FixDir                    28      // 5 Bits, Bit 7-3
#define     LOG_fE2LowDpt3FixDirMask 0xF8
#define     LOG_fE2LowDpt3FixDirShift 3
#define LOG_fE2LowDpt3FixDim                    28      // 3 Bits, Bit 2-0
#define     LOG_fE2LowDpt3FixDimMask 0x07
#define     LOG_fE2LowDpt3FixDimShift 0
#define LOG_fE2LowDpt5                          28      // uint8_t
#define LOG_fE2HighDpt5                         32      // uint8_t
#define LOG_fE2Low0Dpt5In                       28      // uint8_t
#define LOG_fE2Low1Dpt5In                       29      // uint8_t
#define LOG_fE2Low2Dpt5In                       30      // uint8_t
#define LOG_fE2Low3Dpt5In                       31      // uint8_t
#define LOG_fE2Low4Dpt5In                       32      // uint8_t
#define LOG_fE2Low5Dpt5In                       33      // uint8_t
#define LOG_fE2Low6Dpt5In                       34      // uint8_t
#define LOG_fE2LowDpt5Fix                       28      // uint8_t
#define LOG_fE2LowDpt5001                       28      // uint8_t
#define LOG_fE2HighDpt5001                      32      // uint8_t
#define LOG_fE2Low0Dpt5xIn                      28      // uint8_t
#define LOG_fE2Low1Dpt5xIn                      29      // uint8_t
#define LOG_fE2Low2Dpt5xIn                      30      // uint8_t
#define LOG_fE2Low3Dpt5xIn                      31      // uint8_t
#define LOG_fE2Low4Dpt5xIn                      32      // uint8_t
#define LOG_fE2Low5Dpt5xIn                      33      // uint8_t
#define LOG_fE2Low6Dpt5xIn                      34      // uint8_t
#define LOG_fE2LowDpt5xFix                      28      // uint8_t
#define LOG_fE2LowDpt6                          28      // int8_t
#define LOG_fE2HighDpt6                         32      // int8_t
#define LOG_fE2Low0Dpt6In                       28      // int8_t
#define LOG_fE2Low1Dpt6In                       29      // int8_t
#define LOG_fE2Low2Dpt6In                       30      // int8_t
#define LOG_fE2Low3Dpt6In                       31      // int8_t
#define LOG_fE2Low4Dpt6In                       32      // int8_t
#define LOG_fE2Low5Dpt6In                       33      // int8_t
#define LOG_fE2Low6Dpt6In                       34      // int8_t
#define LOG_fE2LowDpt6Fix                       28      // int8_t
#define LOG_fE2LowDpt7                          28      // uint16_t
#define LOG_fE2HighDpt7                         32      // uint16_t
#define LOG_fE2Low0Dpt7In                       28      // uint16_t
#define LOG_fE2Low1Dpt7In                       30      // uint16_t
#define LOG_fE2Low2Dpt7In                       32      // uint16_t
#define LOG_fE2LowDpt7Fix                       28      // uint16_t
#define LOG_fE2LowDpt8                          28      // int16_t
#define LOG_fE2HighDpt8                         32      // int16_t
#define LOG_fE2Low0Dpt8In                       28      // int16_t
#define LOG_fE2Low1Dpt8In                       30      // int16_t
#define LOG_fE2Low2Dpt8In                       32      // int16_t
#define LOG_fE2LowDpt8Fix                       28      // int16_t
#define LOG_fE2LowDpt9                          28      // float
#define LOG_fE2HighDpt9                         32      // float
#define LOG_fE2LowDpt9Fix                       28      // float
#define LOG_fE2LowDpt12                         28      // uint32_t
#define LOG_fE2HighDpt12                        32      // uint32_t
#define LOG_fE2LowDpt12Fix                      28      // uint32_t
#define LOG_fE2LowDpt13                         28      // int32_t
#define LOG_fE2HighDpt13                        32      // int32_t
#define LOG_fE2LowDpt13Fix                      28      // int32_t
#define LOG_fE2LowDpt14                         28      // float
#define LOG_fE2HighDpt14                        32      // float
#define LOG_fE2LowDpt14Fix                      28      // float
#define LOG_fE2Low0Dpt17                        28      // 8 Bits, Bit 7-0
#define LOG_fE2Low1Dpt17                        29      // 8 Bits, Bit 7-0
#define LOG_fE2Low2Dpt17                        30      // 8 Bits, Bit 7-0
#define LOG_fE2Low3Dpt17                        31      // 8 Bits, Bit 7-0
#define LOG_fE2Low4Dpt17                        32      // 8 Bits, Bit 7-0
#define LOG_fE2Low5Dpt17                        33      // 8 Bits, Bit 7-0
#define LOG_fE2Low6Dpt17                        34      // 8 Bits, Bit 7-0
#define LOG_fE2Low7Dpt17                        35      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt17Fix                      28      // 8 Bits, Bit 7-0
#define LOG_fE2LowDptRGB                        28      // int32_t
#define LOG_fE2HighDptRGB                       32      // int32_t
#define LOG_fE2LowDptRGBFix                     28      // int32_t
#define LOG_fTd1DuskDawn                         6      // 4 Bits, Bit 7-4
#define     LOG_fTd1DuskDawnMask 0xF0
#define     LOG_fTd1DuskDawnShift 4
#define LOG_fTd2DuskDawn                         6      // 4 Bits, Bit 3-0
#define     LOG_fTd2DuskDawnMask 0x0F
#define     LOG_fTd2DuskDawnShift 0
#define LOG_fTd3DuskDawn                         7      // 4 Bits, Bit 7-4
#define     LOG_fTd3DuskDawnMask 0xF0
#define     LOG_fTd3DuskDawnShift 4
#define LOG_fTd4DuskDawn                         7      // 4 Bits, Bit 3-0
#define     LOG_fTd4DuskDawnMask 0x0F
#define     LOG_fTd4DuskDawnShift 0
#define LOG_fTd5DuskDawn                         8      // 4 Bits, Bit 7-4
#define     LOG_fTd5DuskDawnMask 0xF0
#define     LOG_fTd5DuskDawnShift 4
#define LOG_fTd6DuskDawn                         8      // 4 Bits, Bit 3-0
#define     LOG_fTd6DuskDawnMask 0x0F
#define     LOG_fTd6DuskDawnShift 0
#define LOG_fTd7DuskDawn                         9      // 4 Bits, Bit 7-4
#define     LOG_fTd7DuskDawnMask 0xF0
#define     LOG_fTd7DuskDawnShift 4
#define LOG_fTd8DuskDawn                         9      // 4 Bits, Bit 3-0
#define     LOG_fTd8DuskDawnMask 0x0F
#define     LOG_fTd8DuskDawnShift 0
#define LOG_fTYearDay                           10      // 2 Bits, Bit 7-6
#define     LOG_fTYearDayMask 0xC0
#define     LOG_fTYearDayShift 6
#define LOG_fTHoliday                           10      // 2 Bits, Bit 5-4
#define     LOG_fTHolidayMask 0x30
#define     LOG_fTHolidayShift 4
#define LOG_fTRestoreState                      10      // 2 Bits, Bit 3-2
#define     LOG_fTRestoreStateMask 0x0C
#define     LOG_fTRestoreStateShift 2
#define LOG_fTVacation                          10      // 2 Bits, Bit 1-0
#define     LOG_fTVacationMask 0x03
#define     LOG_fTVacationShift 0
#define LOG_fTd1ValueNum                        11      // uint8_t
#define LOG_fTd2ValueNum                        12      // uint8_t
#define LOG_fTd3ValueNum                        13      // uint8_t
#define LOG_fTd4ValueNum                        14      // uint8_t
#define LOG_fTd5ValueNum                        15      // uint8_t
#define LOG_fTd6ValueNum                        16      // uint8_t
#define LOG_fTd7ValueNum                        17      // uint8_t
#define LOG_fTd8ValueNum                        18      // uint8_t
#define LOG_fTd1Value                           20      // 1 Bit, Bit 7
#define     LOG_fTd1ValueMask 0x80
#define     LOG_fTd1ValueShift 7
#define LOG_fTd1Degree                          20      // 6 Bits, Bit 6-1
#define     LOG_fTd1DegreeMask 0x7E
#define     LOG_fTd1DegreeShift 1
#define LOG_fTd1HourAbs                         20      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourAbsMask 0x3E
#define     LOG_fTd1HourAbsShift 1
#define LOG_fTd1HourRel                         20      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourRelMask 0x3E
#define     LOG_fTd1HourRelShift 1
#define LOG_fTd1HourRelShort                    20      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourRelShortMask 0x3E
#define     LOG_fTd1HourRelShortShift 1
#define LOG_fTd1MinuteAbs                       20      // 6 Bits, Bit 0--5
#define LOG_fTd1MinuteRel                       20      // 6 Bits, Bit 0--5
#define LOG_fTd1Weekday                         21      // 3 Bits, Bit 2-0
#define     LOG_fTd1WeekdayMask 0x07
#define     LOG_fTd1WeekdayShift 0
#define LOG_fTd2Value                           22      // 1 Bit, Bit 7
#define     LOG_fTd2ValueMask 0x80
#define     LOG_fTd2ValueShift 7
#define LOG_fTd2Degree                          22      // 6 Bits, Bit 6-1
#define     LOG_fTd2DegreeMask 0x7E
#define     LOG_fTd2DegreeShift 1
#define LOG_fTd2HourAbs                         22      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourAbsMask 0x3E
#define     LOG_fTd2HourAbsShift 1
#define LOG_fTd2HourRel                         22      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourRelMask 0x3E
#define     LOG_fTd2HourRelShift 1
#define LOG_fTd2HourRelShort                    22      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourRelShortMask 0x3E
#define     LOG_fTd2HourRelShortShift 1
#define LOG_fTd2MinuteAbs                       22      // 6 Bits, Bit 0--5
#define LOG_fTd2MinuteRel                       22      // 6 Bits, Bit 0--5
#define LOG_fTd2Weekday                         23      // 3 Bits, Bit 2-0
#define     LOG_fTd2WeekdayMask 0x07
#define     LOG_fTd2WeekdayShift 0
#define LOG_fTd3Value                           24      // 1 Bit, Bit 7
#define     LOG_fTd3ValueMask 0x80
#define     LOG_fTd3ValueShift 7
#define LOG_fTd3Degree                          24      // 6 Bits, Bit 6-1
#define     LOG_fTd3DegreeMask 0x7E
#define     LOG_fTd3DegreeShift 1
#define LOG_fTd3HourAbs                         24      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourAbsMask 0x3E
#define     LOG_fTd3HourAbsShift 1
#define LOG_fTd3HourRel                         24      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourRelMask 0x3E
#define     LOG_fTd3HourRelShift 1
#define LOG_fTd3HourRelShort                    24      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourRelShortMask 0x3E
#define     LOG_fTd3HourRelShortShift 1
#define LOG_fTd3MinuteAbs                       24      // 6 Bits, Bit 0--5
#define LOG_fTd3MinuteRel                       24      // 6 Bits, Bit 0--5
#define LOG_fTd3Weekday                         25      // 3 Bits, Bit 2-0
#define     LOG_fTd3WeekdayMask 0x07
#define     LOG_fTd3WeekdayShift 0
#define LOG_fTd4Value                           26      // 1 Bit, Bit 7
#define     LOG_fTd4ValueMask 0x80
#define     LOG_fTd4ValueShift 7
#define LOG_fTd4Degree                          26      // 6 Bits, Bit 6-1
#define     LOG_fTd4DegreeMask 0x7E
#define     LOG_fTd4DegreeShift 1
#define LOG_fTd4HourAbs                         26      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourAbsMask 0x3E
#define     LOG_fTd4HourAbsShift 1
#define LOG_fTd4HourRel                         26      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourRelMask 0x3E
#define     LOG_fTd4HourRelShift 1
#define LOG_fTd4HourRelShort                    26      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourRelShortMask 0x3E
#define     LOG_fTd4HourRelShortShift 1
#define LOG_fTd4MinuteAbs                       26      // 6 Bits, Bit 0--5
#define LOG_fTd4MinuteRel                       26      // 6 Bits, Bit 0--5
#define LOG_fTd4Weekday                         27      // 3 Bits, Bit 2-0
#define     LOG_fTd4WeekdayMask 0x07
#define     LOG_fTd4WeekdayShift 0
#define LOG_fTd5Value                           28      // 1 Bit, Bit 7
#define     LOG_fTd5ValueMask 0x80
#define     LOG_fTd5ValueShift 7
#define LOG_fTd5Degree                          28      // 6 Bits, Bit 6-1
#define     LOG_fTd5DegreeMask 0x7E
#define     LOG_fTd5DegreeShift 1
#define LOG_fTd5HourAbs                         28      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourAbsMask 0x3E
#define     LOG_fTd5HourAbsShift 1
#define LOG_fTd5HourRel                         28      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourRelMask 0x3E
#define     LOG_fTd5HourRelShift 1
#define LOG_fTd5HourRelShort                    28      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourRelShortMask 0x3E
#define     LOG_fTd5HourRelShortShift 1
#define LOG_fTd5MinuteAbs                       28      // 6 Bits, Bit 0--5
#define LOG_fTd5MinuteRel                       28      // 6 Bits, Bit 0--5
#define LOG_fTd5Weekday                         29      // 3 Bits, Bit 2-0
#define     LOG_fTd5WeekdayMask 0x07
#define     LOG_fTd5WeekdayShift 0
#define LOG_fTd6Value                           30      // 1 Bit, Bit 7
#define     LOG_fTd6ValueMask 0x80
#define     LOG_fTd6ValueShift 7
#define LOG_fTd6Degree                          30      // 6 Bits, Bit 6-1
#define     LOG_fTd6DegreeMask 0x7E
#define     LOG_fTd6DegreeShift 1
#define LOG_fTd6HourAbs                         30      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourAbsMask 0x3E
#define     LOG_fTd6HourAbsShift 1
#define LOG_fTd6HourRel                         30      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourRelMask 0x3E
#define     LOG_fTd6HourRelShift 1
#define LOG_fTd6HourRelShort                    30      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourRelShortMask 0x3E
#define     LOG_fTd6HourRelShortShift 1
#define LOG_fTd6MinuteAbs                       30      // 6 Bits, Bit 0--5
#define LOG_fTd6MinuteRel                       30      // 6 Bits, Bit 0--5
#define LOG_fTd6Weekday                         31      // 3 Bits, Bit 2-0
#define     LOG_fTd6WeekdayMask 0x07
#define     LOG_fTd6WeekdayShift 0
#define LOG_fTd7Value                           32      // 1 Bit, Bit 7
#define     LOG_fTd7ValueMask 0x80
#define     LOG_fTd7ValueShift 7
#define LOG_fTd7Degree                          32      // 6 Bits, Bit 6-1
#define     LOG_fTd7DegreeMask 0x7E
#define     LOG_fTd7DegreeShift 1
#define LOG_fTd7HourAbs                         32      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourAbsMask 0x3E
#define     LOG_fTd7HourAbsShift 1
#define LOG_fTd7HourRel                         32      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourRelMask 0x3E
#define     LOG_fTd7HourRelShift 1
#define LOG_fTd7HourRelShort                    32      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourRelShortMask 0x3E
#define     LOG_fTd7HourRelShortShift 1
#define LOG_fTd7MinuteAbs                       32      // 6 Bits, Bit 0--5
#define LOG_fTd7MinuteRel                       32      // 6 Bits, Bit 0--5
#define LOG_fTd7Weekday                         33      // 3 Bits, Bit 2-0
#define     LOG_fTd7WeekdayMask 0x07
#define     LOG_fTd7WeekdayShift 0
#define LOG_fTd8Value                           34      // 1 Bit, Bit 7
#define     LOG_fTd8ValueMask 0x80
#define     LOG_fTd8ValueShift 7
#define LOG_fTd8Degree                          34      // 6 Bits, Bit 6-1
#define     LOG_fTd8DegreeMask 0x7E
#define     LOG_fTd8DegreeShift 1
#define LOG_fTd8HourAbs                         34      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourAbsMask 0x3E
#define     LOG_fTd8HourAbsShift 1
#define LOG_fTd8HourRel                         34      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourRelMask 0x3E
#define     LOG_fTd8HourRelShift 1
#define LOG_fTd8HourRelShort                    34      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourRelShortMask 0x3E
#define     LOG_fTd8HourRelShortShift 1
#define LOG_fTd8MinuteAbs                       34      // 6 Bits, Bit 0--5
#define LOG_fTd8MinuteRel                       34      // 6 Bits, Bit 0--5
#define LOG_fTd8Weekday                         35      // 3 Bits, Bit 2-0
#define     LOG_fTd8WeekdayMask 0x07
#define     LOG_fTd8WeekdayShift 0
#define LOG_fTy1Weekday1                        28      // 1 Bit, Bit 7
#define     LOG_fTy1Weekday1Mask 0x80
#define     LOG_fTy1Weekday1Shift 7
#define LOG_fTy1Weekday2                        28      // 1 Bit, Bit 6
#define     LOG_fTy1Weekday2Mask 0x40
#define     LOG_fTy1Weekday2Shift 6
#define LOG_fTy1Weekday3                        28      // 1 Bit, Bit 5
#define     LOG_fTy1Weekday3Mask 0x20
#define     LOG_fTy1Weekday3Shift 5
#define LOG_fTy1Weekday4                        28      // 1 Bit, Bit 4
#define     LOG_fTy1Weekday4Mask 0x10
#define     LOG_fTy1Weekday4Shift 4
#define LOG_fTy1Weekday5                        28      // 1 Bit, Bit 3
#define     LOG_fTy1Weekday5Mask 0x08
#define     LOG_fTy1Weekday5Shift 3
#define LOG_fTy1Weekday6                        28      // 1 Bit, Bit 2
#define     LOG_fTy1Weekday6Mask 0x04
#define     LOG_fTy1Weekday6Shift 2
#define LOG_fTy1Weekday7                        28      // 1 Bit, Bit 1
#define     LOG_fTy1Weekday7Mask 0x02
#define     LOG_fTy1Weekday7Shift 1
#define LOG_fTy1Day                             28      // 7 Bits, Bit 7-1
#define     LOG_fTy1DayMask 0xFE
#define     LOG_fTy1DayShift 1
#define LOG_fTy1IsWeekday                       28      // 1 Bit, Bit 0
#define     LOG_fTy1IsWeekdayMask 0x01
#define     LOG_fTy1IsWeekdayShift 0
#define LOG_fTy1Month                           29      // 4 Bits, Bit 7-4
#define     LOG_fTy1MonthMask 0xF0
#define     LOG_fTy1MonthShift 4
#define LOG_fTy2Weekday1                        30      // 1 Bit, Bit 7
#define     LOG_fTy2Weekday1Mask 0x80
#define     LOG_fTy2Weekday1Shift 7
#define LOG_fTy2Weekday2                        30      // 1 Bit, Bit 6
#define     LOG_fTy2Weekday2Mask 0x40
#define     LOG_fTy2Weekday2Shift 6
#define LOG_fTy2Weekday3                        30      // 1 Bit, Bit 5
#define     LOG_fTy2Weekday3Mask 0x20
#define     LOG_fTy2Weekday3Shift 5
#define LOG_fTy2Weekday4                        30      // 1 Bit, Bit 4
#define     LOG_fTy2Weekday4Mask 0x10
#define     LOG_fTy2Weekday4Shift 4
#define LOG_fTy2Weekday5                        30      // 1 Bit, Bit 3
#define     LOG_fTy2Weekday5Mask 0x08
#define     LOG_fTy2Weekday5Shift 3
#define LOG_fTy2Weekday6                        30      // 1 Bit, Bit 2
#define     LOG_fTy2Weekday6Mask 0x04
#define     LOG_fTy2Weekday6Shift 2
#define LOG_fTy2Weekday7                        30      // 1 Bit, Bit 1
#define     LOG_fTy2Weekday7Mask 0x02
#define     LOG_fTy2Weekday7Shift 1
#define LOG_fTy2Day                             30      // 7 Bits, Bit 7-1
#define     LOG_fTy2DayMask 0xFE
#define     LOG_fTy2DayShift 1
#define LOG_fTy2IsWeekday                       30      // 1 Bit, Bit 0
#define     LOG_fTy2IsWeekdayMask 0x01
#define     LOG_fTy2IsWeekdayShift 0
#define LOG_fTy2Month                           31      // 4 Bits, Bit 7-4
#define     LOG_fTy2MonthMask 0xF0
#define     LOG_fTy2MonthShift 4
#define LOG_fTy3Weekday1                        32      // 1 Bit, Bit 7
#define     LOG_fTy3Weekday1Mask 0x80
#define     LOG_fTy3Weekday1Shift 7
#define LOG_fTy3Weekday2                        32      // 1 Bit, Bit 6
#define     LOG_fTy3Weekday2Mask 0x40
#define     LOG_fTy3Weekday2Shift 6
#define LOG_fTy3Weekday3                        32      // 1 Bit, Bit 5
#define     LOG_fTy3Weekday3Mask 0x20
#define     LOG_fTy3Weekday3Shift 5
#define LOG_fTy3Weekday4                        32      // 1 Bit, Bit 4
#define     LOG_fTy3Weekday4Mask 0x10
#define     LOG_fTy3Weekday4Shift 4
#define LOG_fTy3Weekday5                        32      // 1 Bit, Bit 3
#define     LOG_fTy3Weekday5Mask 0x08
#define     LOG_fTy3Weekday5Shift 3
#define LOG_fTy3Weekday6                        32      // 1 Bit, Bit 2
#define     LOG_fTy3Weekday6Mask 0x04
#define     LOG_fTy3Weekday6Shift 2
#define LOG_fTy3Weekday7                        32      // 1 Bit, Bit 1
#define     LOG_fTy3Weekday7Mask 0x02
#define     LOG_fTy3Weekday7Shift 1
#define LOG_fTy3Day                             32      // 7 Bits, Bit 7-1
#define     LOG_fTy3DayMask 0xFE
#define     LOG_fTy3DayShift 1
#define LOG_fTy3IsWeekday                       32      // 1 Bit, Bit 0
#define     LOG_fTy3IsWeekdayMask 0x01
#define     LOG_fTy3IsWeekdayShift 0
#define LOG_fTy3Month                           33      // 4 Bits, Bit 7-4
#define     LOG_fTy3MonthMask 0xF0
#define     LOG_fTy3MonthShift 4
#define LOG_fTy4Weekday1                        34      // 1 Bit, Bit 7
#define     LOG_fTy4Weekday1Mask 0x80
#define     LOG_fTy4Weekday1Shift 7
#define LOG_fTy4Weekday2                        34      // 1 Bit, Bit 6
#define     LOG_fTy4Weekday2Mask 0x40
#define     LOG_fTy4Weekday2Shift 6
#define LOG_fTy4Weekday3                        34      // 1 Bit, Bit 5
#define     LOG_fTy4Weekday3Mask 0x20
#define     LOG_fTy4Weekday3Shift 5
#define LOG_fTy4Weekday4                        34      // 1 Bit, Bit 4
#define     LOG_fTy4Weekday4Mask 0x10
#define     LOG_fTy4Weekday4Shift 4
#define LOG_fTy4Weekday5                        34      // 1 Bit, Bit 3
#define     LOG_fTy4Weekday5Mask 0x08
#define     LOG_fTy4Weekday5Shift 3
#define LOG_fTy4Weekday6                        34      // 1 Bit, Bit 2
#define     LOG_fTy4Weekday6Mask 0x04
#define     LOG_fTy4Weekday6Shift 2
#define LOG_fTy4Weekday7                        34      // 1 Bit, Bit 1
#define     LOG_fTy4Weekday7Mask 0x02
#define     LOG_fTy4Weekday7Shift 1
#define LOG_fTy4Day                             34      // 7 Bits, Bit 7-1
#define     LOG_fTy4DayMask 0xFE
#define     LOG_fTy4DayShift 1
#define LOG_fTy4IsWeekday                       34      // 1 Bit, Bit 0
#define     LOG_fTy4IsWeekdayMask 0x01
#define     LOG_fTy4IsWeekdayShift 0
#define LOG_fTy4Month                           35      // 4 Bits, Bit 7-4
#define     LOG_fTy4MonthMask 0xF0
#define     LOG_fTy4MonthShift 4
#define LOG_fI1                                 36      // 2 Bits, Bit 7-6
#define     LOG_fI1Mask 0xC0
#define     LOG_fI1Shift 6
#define LOG_fI1Kind                             36      // 2 Bits, Bit 5-4
#define     LOG_fI1KindMask 0x30
#define     LOG_fI1KindShift 4
#define LOG_fI1AsTrigger                        36      // 1 Bit, Bit 3
#define     LOG_fI1AsTriggerMask 0x08
#define     LOG_fI1AsTriggerShift 3
#define LOG_fI1InternalInputType                36      // 1 Bit, Bit 2
#define     LOG_fI1InternalInputTypeMask 0x04
#define     LOG_fI1InternalInputTypeShift 2
#define LOG_fI1Function                         37      // uint8_t
#define LOG_fI1FunctionRel                      37      // int8_t
#define LOG_fI1StatusLed                        37      // 16 Bits, Bit 15-0
#define LOG_fI2                                 39      // 2 Bits, Bit 7-6
#define     LOG_fI2Mask 0xC0
#define     LOG_fI2Shift 6
#define LOG_fI2Kind                             39      // 2 Bits, Bit 5-4
#define     LOG_fI2KindMask 0x30
#define     LOG_fI2KindShift 4
#define LOG_fI2AsTrigger                        39      // 1 Bit, Bit 3
#define     LOG_fI2AsTriggerMask 0x08
#define     LOG_fI2AsTriggerShift 3
#define LOG_fI2InternalInputType                39      // 1 Bit, Bit 2
#define     LOG_fI2InternalInputTypeMask 0x04
#define     LOG_fI2InternalInputTypeShift 2
#define LOG_fI2Function                         40      // uint8_t
#define LOG_fI2FunctionRel                      40      // int8_t
#define LOG_fI2StatusLed                        40      // 16 Bits, Bit 15-0
#define LOG_fOStairtimeBase                     42      // 2 Bits, Bit 7-6
#define     LOG_fOStairtimeBaseMask 0xC0
#define     LOG_fOStairtimeBaseShift 6
#define LOG_fOStairtimeTime                     42      // 14 Bits, Bit 13-0
#define     LOG_fOStairtimeTimeMask 0x3FFF
#define     LOG_fOStairtimeTimeShift 0
#define LOG_fOBlinkBase                         44      // 2 Bits, Bit 7-6
#define     LOG_fOBlinkBaseMask 0xC0
#define     LOG_fOBlinkBaseShift 6
#define LOG_fOBlinkTime                         44      // 14 Bits, Bit 13-0
#define     LOG_fOBlinkTimeMask 0x3FFF
#define     LOG_fOBlinkTimeShift 0
#define LOG_fODelayOnBase                       46      // 2 Bits, Bit 7-6
#define     LOG_fODelayOnBaseMask 0xC0
#define     LOG_fODelayOnBaseShift 6
#define LOG_fODelayOnTime                       46      // 14 Bits, Bit 13-0
#define     LOG_fODelayOnTimeMask 0x3FFF
#define     LOG_fODelayOnTimeShift 0
#define LOG_fODelayOffBase                      48      // 2 Bits, Bit 7-6
#define     LOG_fODelayOffBaseMask 0xC0
#define     LOG_fODelayOffBaseShift 6
#define LOG_fODelayOffTime                      48      // 14 Bits, Bit 13-0
#define     LOG_fODelayOffTimeMask 0x3FFF
#define     LOG_fODelayOffTimeShift 0
#define LOG_fORepeatOnBase                      50      // 2 Bits, Bit 7-6
#define     LOG_fORepeatOnBaseMask 0xC0
#define     LOG_fORepeatOnBaseShift 6
#define LOG_fORepeatOnTime                      50      // 14 Bits, Bit 13-0
#define     LOG_fORepeatOnTimeMask 0x3FFF
#define     LOG_fORepeatOnTimeShift 0
#define LOG_fORepeatOffBase                     52      // 2 Bits, Bit 7-6
#define     LOG_fORepeatOffBaseMask 0xC0
#define     LOG_fORepeatOffBaseShift 6
#define LOG_fORepeatOffTime                     52      // 14 Bits, Bit 13-0
#define     LOG_fORepeatOffTimeMask 0x3FFF
#define     LOG_fORepeatOffTimeShift 0
#define LOG_fODelay                             54      // 1 Bit, Bit 7
#define     LOG_fODelayMask 0x80
#define     LOG_fODelayShift 7
#define LOG_fODelayOnRepeat                     54      // 2 Bits, Bit 6-5
#define     LOG_fODelayOnRepeatMask 0x60
#define     LOG_fODelayOnRepeatShift 5
#define LOG_fODelayOnReset                      54      // 1 Bit, Bit 4
#define     LOG_fODelayOnResetMask 0x10
#define     LOG_fODelayOnResetShift 4
#define LOG_fODelayOffRepeat                    54      // 2 Bits, Bit 3-2
#define     LOG_fODelayOffRepeatMask 0x0C
#define     LOG_fODelayOffRepeatShift 2
#define LOG_fODelayOffReset                     54      // 1 Bit, Bit 1
#define     LOG_fODelayOffResetMask 0x02
#define     LOG_fODelayOffResetShift 1
#define LOG_fOStair                             54      // 1 Bit, Bit 0
#define     LOG_fOStairMask 0x01
#define     LOG_fOStairShift 0
#define LOG_fORetrigger                         55      // 1 Bit, Bit 7
#define     LOG_fORetriggerMask 0x80
#define     LOG_fORetriggerShift 7
#define LOG_fOStairOff                          55      // 1 Bit, Bit 6
#define     LOG_fOStairOffMask 0x40
#define     LOG_fOStairOffShift 6
#define LOG_fORepeat                            55      // 1 Bit, Bit 5
#define     LOG_fORepeatMask 0x20
#define     LOG_fORepeatShift 5
#define LOG_fOOutputFilter                      55      // 2 Bits, Bit 4-3
#define     LOG_fOOutputFilterMask 0x18
#define     LOG_fOOutputFilterShift 3
#define LOG_fOSendOnChange                      55      // 1 Bit, Bit 2
#define     LOG_fOSendOnChangeMask 0x04
#define     LOG_fOSendOnChangeShift 2
#define LOG_fODpt                               56      // 8 Bits, Bit 7-0
#define LOG_fOOnAll                             57      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt1                            58      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt2                            58      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt3Dir                         58      // 5 Bits, Bit 7-3
#define     LOG_fOOnDpt3DirMask 0xF8
#define     LOG_fOOnDpt3DirShift 3
#define LOG_fOOnDpt3Dim                         58      // 3 Bits, Bit 2-0
#define     LOG_fOOnDpt3DimMask 0x07
#define     LOG_fOOnDpt3DimShift 0
#define LOG_fOOnDpt5                            58      // uint8_t
#define LOG_fOOnDpt5001                         58      // uint8_t
#define LOG_fOOnDpt6                            58      // int8_t
#define LOG_fOOnDpt7                            58      // uint16_t
#define LOG_fOOnDpt8                            58      // int16_t
#define LOG_fOOnDpt9                            58      // float
#define LOG_fOOnDpt12                           58      // uint32_t
#define LOG_fOOnDpt13                           58      // int32_t
#define LOG_fOOnDpt14                           58      // float
#define LOG_fOOnDpt16                           58      // char*, 14 Byte
#define     LOG_fOOnDpt16Length 14
#define LOG_fOOnDpt17                           58      // 8 Bits, Bit 7-0
#define LOG_fOOnRGB                             58      // 24 Bits, Bit 31-8
#define     LOG_fOOnRGBMask 0xFFFFFF00
#define     LOG_fOOnRGBShift 8
#define LOG_fOOnLedProvider                     62      // 3 Bits, Bit 2-0
#define     LOG_fOOnLedProviderMask 0x07
#define     LOG_fOOnLedProviderShift 0
#define LOG_fOOnLedEffect                       63      // 3 Bits, Bit 2-0
#define     LOG_fOOnLedEffectMask 0x07
#define     LOG_fOOnLedEffectShift 0
#define LOG_fOOnLedDuration                     64      // uint16_t
#define LOG_fOOnPAArea                          58      // 4 Bits, Bit 7-4
#define     LOG_fOOnPAAreaMask 0xF0
#define     LOG_fOOnPAAreaShift 4
#define LOG_fOOnPALine                          58      // 4 Bits, Bit 3-0
#define     LOG_fOOnPALineMask 0x0F
#define     LOG_fOOnPALineShift 0
#define LOG_fOOnPADevice                        59      // uint8_t
#define LOG_fOOnFunction                        58      // 8 Bits, Bit 7-0
#define LOG_fOOnKOKind                          63      // 2 Bits, Bit 7-6
#define     LOG_fOOnKOKindMask 0xC0
#define     LOG_fOOnKOKindShift 6
#define LOG_fOOnKONumber                        58      // uint16_t
#define LOG_fOOnKONumberRel                     58      // int16_t
#define LOG_fOOnKODpt                           60      // 8 Bits, Bit 7-0
#define LOG_fOOnKOSend                          63      // 2 Bits, Bit 5-4
#define     LOG_fOOnKOSendMask 0x30
#define     LOG_fOOnKOSendShift 4
#define LOG_fOOnKOSendNumber                    64      // uint16_t
#define LOG_fOOnKOSendNumberRel                 64      // int16_t
#define LOG_fOOffAll                            72      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt1                           73      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt2                           73      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt3Dir                        73      // 5 Bits, Bit 7-3
#define     LOG_fOOffDpt3DirMask 0xF8
#define     LOG_fOOffDpt3DirShift 3
#define LOG_fOOffDpt3Dim                        73      // 3 Bits, Bit 2-0
#define     LOG_fOOffDpt3DimMask 0x07
#define     LOG_fOOffDpt3DimShift 0
#define LOG_fOOffDpt5                           73      // uint8_t
#define LOG_fOOffDpt5001                        73      // uint8_t
#define LOG_fOOffDpt6                           73      // int8_t
#define LOG_fOOffDpt7                           73      // uint16_t
#define LOG_fOOffDpt8                           73      // int16_t
#define LOG_fOOffDpt9                           73      // float
#define LOG_fOOffDpt12                          73      // uint32_t
#define LOG_fOOffDpt13                          73      // int32_t
#define LOG_fOOffDpt14                          73      // float
#define LOG_fOOffDpt16                          73      // char*, 14 Byte
#define     LOG_fOOffDpt16Length 14
#define LOG_fOOffDpt17                          73      // 8 Bits, Bit 7-0
#define LOG_fOOffRGB                            73      // 24 Bits, Bit 31-8
#define     LOG_fOOffRGBMask 0xFFFFFF00
#define     LOG_fOOffRGBShift 8
#define LOG_fOOffLedProvider                    77      // 3 Bits, Bit 2-0
#define     LOG_fOOffLedProviderMask 0x07
#define     LOG_fOOffLedProviderShift 0
#define LOG_fOOffLedEffect                      78      // 3 Bits, Bit 2-0
#define     LOG_fOOffLedEffectMask 0x07
#define     LOG_fOOffLedEffectShift 0
#define LOG_fOOffLedDuration                    79      // uint16_t
#define LOG_fOOffPAArea                         73      // 4 Bits, Bit 7-4
#define     LOG_fOOffPAAreaMask 0xF0
#define     LOG_fOOffPAAreaShift 4
#define LOG_fOOffPALine                         73      // 4 Bits, Bit 3-0
#define     LOG_fOOffPALineMask 0x0F
#define     LOG_fOOffPALineShift 0
#define LOG_fOOffPADevice                       74      // uint8_t
#define LOG_fOOffFunction                       73      // 8 Bits, Bit 7-0
#define LOG_fOOffKOKind                         78      // 2 Bits, Bit 7-6
#define     LOG_fOOffKOKindMask 0xC0
#define     LOG_fOOffKOKindShift 6
#define LOG_fOOffKONumber                       73      // uint16_t
#define LOG_fOOffKONumberRel                    73      // int16_t
#define LOG_fOOffKODpt                          75      // 8 Bits, Bit 7-0
#define LOG_fOOffKOSend                         78      // 2 Bits, Bit 5-4
#define     LOG_fOOffKOSendMask 0x30
#define     LOG_fOOffKOSendShift 4
#define LOG_fOOffKOSendNumber                   79      // uint16_t
#define LOG_fOOffKOSendNumberRel                79      // int16_t

// Zeit bis der Kanal nach einem Neustart aktiv wird
#define ParamLOG_fChannelDelayBase                   ((knx.paramByte(LOG_ParamCalcIndex(LOG_fChannelDelayBase)) & LOG_fChannelDelayBaseMask) >> LOG_fChannelDelayBaseShift)
// Zeit bis der Kanal nach einem Neustart aktiv wird
#define ParamLOG_fChannelDelayTime                   (knx.paramWord(LOG_ParamCalcIndex(LOG_fChannelDelayTime)) & LOG_fChannelDelayTimeMask)
// Zeit bis der Kanal nach einem Neustart aktiv wird (in Millisekunden)
#define ParamLOG_fChannelDelayTimeMS                 (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fChannelDelayTime))))
// Logik-Operation
#define ParamLOG_fLogic                              (knx.paramByte(LOG_ParamCalcIndex(LOG_fLogic)))
// Logik auswerten
#define ParamLOG_fCalculate                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fCalculate)) & LOG_fCalculateMask)
// Kanal deaktivieren (zu Testzwecken)
#define ParamLOG_fDisable                            ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fDisable)) & LOG_fDisableMask))
// Tor geht sofort wieder zu
#define ParamLOG_fTGate                              ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTGate)) & LOG_fTGateMask))
// Wert EIN intern weiterleiten
#define ParamLOG_fOInternalOn                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fOInternalOn)) & LOG_fOInternalOnMask))
// Wert AUS intern weiterleiten
#define ParamLOG_fOInternalOff                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fOInternalOff)) & LOG_fOInternalOffMask))
// Logik sendet ihren Wert weiter
#define ParamLOG_fTrigger                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fTrigger)))
//           Eingang 1
#define ParamLOG_fTriggerE1                          ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerE1)) & LOG_fTriggerE1Mask))
//           Eingang 2
#define ParamLOG_fTriggerE2                          ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerE2)) & LOG_fTriggerE2Mask))
//           Interner Eingang 3
#define ParamLOG_fTriggerI1                          ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerI1)) & LOG_fTriggerI1Mask))
//           Interner Eingang 4
#define ParamLOG_fTriggerI2                          ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerI2)) & LOG_fTriggerI2Mask))
// Logik sendet ihren Wert weiter
#define ParamLOG_fTriggerTime                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerTime)))
// Beim schließen vom Tor wird
#define ParamLOG_fTriggerGateClose                   ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerGateClose)) & LOG_fTriggerGateCloseMask) >> LOG_fTriggerGateCloseShift)
// Beim öffnen vom Tor wird
#define ParamLOG_fTriggerGateOpen                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerGateOpen)) & LOG_fTriggerGateOpenMask) >> LOG_fTriggerGateOpenShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE1ConvertInt                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1ConvertInt)) & LOG_fE1ConvertIntMask) >> LOG_fE1ConvertIntShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE1Convert                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Convert)) & LOG_fE1ConvertMask) >> LOG_fE1ConvertShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE1ConvertFloat                     ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1ConvertFloat)) & LOG_fE1ConvertFloatMask) >> LOG_fE1ConvertFloatShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE1ConvertSpecial                   ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1ConvertSpecial)) & LOG_fE1ConvertSpecialMask) >> LOG_fE1ConvertSpecialShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE1ConvertBool                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1ConvertBool)) & LOG_fE1ConvertBoolMask) >> LOG_fE1ConvertBoolShift)
// Eingang 1
#define ParamLOG_fE1                                 (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1)) & LOG_fE1Mask)
// DPT für Eingang
#define ParamLOG_fE1Dpt                              (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Dpt)))
// Eingang wird gelesen alle
#define ParamLOG_fE1RepeatBase                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1RepeatBase)) & LOG_fE1RepeatBaseMask) >> LOG_fE1RepeatBaseShift)
// Eingang wird gelesen alle
#define ParamLOG_fE1RepeatTime                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1RepeatTime)) & LOG_fE1RepeatTimeMask)
// Eingang wird gelesen alle (in Millisekunden)
#define ParamLOG_fE1RepeatTimeMS                     (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fE1RepeatTime))))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fE1OtherKO                          (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1OtherKO)))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fE1OtherKORel                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1OtherKORel)))
// Falls Vorbelegung aus dem Speicher nicht möglich oder nicht gewünscht, dann vorbelegen mit
#define ParamLOG_fE1Default                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Default)) & LOG_fE1DefaultMask)
// Eingang vorbelegen mit
#define ParamLOG_fE1DefaultExt                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1DefaultExt)) & LOG_fE1DefaultExtMask)
// Eingangswert speichern und beim nächsten Neustart als Vorbelegung nutzen?
#define ParamLOG_fE1DefaultEEPROM                    ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1DefaultEEPROM)) & LOG_fE1DefaultEEPROMMask))
// Nur so lange zyklisch lesen, bis erstes Telegramm eingeht
#define ParamLOG_fE1DefaultRepeat                    ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1DefaultRepeat)) & LOG_fE1DefaultRepeatMask))
// Kommunikationsobjekt für Eingang
#define ParamLOG_fE1UseOtherKO                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1UseOtherKO)) & LOG_fE1UseOtherKOMask) >> LOG_fE1UseOtherKOShift)
// Von-Wert
#define ParamLOG_fE1LowDelta                         ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDelta)))
// Bis-Wert
#define ParamLOG_fE1HighDelta                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1HighDelta)))
// Von-Wert
#define ParamLOG_fE1LowDeltaFloat                    (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDeltaFloat), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE1HighDeltaFloat                   (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1HighDeltaFloat), Float_Enc_IEEE754Single))
// Von-Wert
#define ParamLOG_fE1LowDeltaDouble                   (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDeltaDouble), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE1HighDeltaDouble                  (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1HighDeltaDouble), Float_Enc_IEEE754Single))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low0Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Valid)) & LOG_fE1Low0ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low1Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Valid)) & LOG_fE1Low1ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low2Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Valid)) & LOG_fE1Low2ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low3Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Valid)) & LOG_fE1Low3ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low4Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low4Valid)) & LOG_fE1Low4ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low5Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low5Valid)) & LOG_fE1Low5ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low6Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low6Valid)) & LOG_fE1Low6ValidMask))
// Eingang ist EIN, wenn Wert gleich
#define ParamLOG_fE1Low0Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE1Low1Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE1Low2Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE1Low3Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt2)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt2Fix                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt2Fix)))
// Eingang ist EIN, wenn Wert gleich
#define ParamLOG_fE1Low0Dpt3Dir                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt3Dir)) & LOG_fE1Low0Dpt3DirMask) >> LOG_fE1Low0Dpt3DirShift)
// 
#define ParamLOG_fE1Low0Dpt3Dim                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt3Dim)) & LOG_fE1Low0Dpt3DimMask)
// ... oder wenn Wert gleich 
#define ParamLOG_fE1Low1Dpt3Dir                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt3Dir)) & LOG_fE1Low1Dpt3DirMask) >> LOG_fE1Low1Dpt3DirShift)
// 
#define ParamLOG_fE1Low1Dpt3Dim                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt3Dim)) & LOG_fE1Low1Dpt3DimMask)
// ... oder wenn Wert gleich 
#define ParamLOG_fE1Low2Dpt3Dir                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt3Dir)) & LOG_fE1Low2Dpt3DirMask) >> LOG_fE1Low2Dpt3DirShift)
// 
#define ParamLOG_fE1Low2Dpt3Dim                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt3Dim)) & LOG_fE1Low2Dpt3DimMask)
// ... oder wenn Wert gleich 
#define ParamLOG_fE1Low3Dpt3Dir                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt3Dir)) & LOG_fE1Low3Dpt3DirMask) >> LOG_fE1Low3Dpt3DirShift)
// 
#define ParamLOG_fE1Low3Dpt3Dim                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt3Dim)) & LOG_fE1Low3Dpt3DimMask)
// Eingang ist konstant
#define ParamLOG_fE1LowDpt3FixDir                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt3FixDir)) & LOG_fE1LowDpt3FixDirMask) >> LOG_fE1LowDpt3FixDirShift)
// 
#define ParamLOG_fE1LowDpt3FixDim                    (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt3FixDim)) & LOG_fE1LowDpt3FixDimMask)
// Von-Wert
#define ParamLOG_fE1LowDpt5                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt5)))
// Bis-Wert
#define ParamLOG_fE1HighDpt5                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1HighDpt5)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE1Low0Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low1Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low2Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low3Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low4Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low4Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low5Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low5Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low6Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low6Dpt5In)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt5Fix                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt5Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt5001                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt5001)))
// Bis-Wert
#define ParamLOG_fE1HighDpt5001                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1HighDpt5001)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE1Low0Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low1Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low2Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low3Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low4Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low4Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low5Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low5Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low6Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low6Dpt5xIn)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt5xFix                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt5xFix)))
// Von-Wert
#define ParamLOG_fE1LowDpt6                          ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt6)))
// Bis-Wert
#define ParamLOG_fE1HighDpt6                         ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1HighDpt6)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE1Low0Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low1Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low2Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low3Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low4Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low4Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low5Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low5Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low6Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low6Dpt6In)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt6Fix                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt6Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt7                          (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1LowDpt7)))
// Bis-Wert
#define ParamLOG_fE1HighDpt7                         (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1HighDpt7)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE1Low0Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low0Dpt7In)))
// ... oder bei Wert
#define ParamLOG_fE1Low1Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low1Dpt7In)))
// ... oder bei Wert
#define ParamLOG_fE1Low2Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low2Dpt7In)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt7Fix                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1LowDpt7Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt8                          ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1LowDpt8)))
// Bis-Wert
#define ParamLOG_fE1HighDpt8                         ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1HighDpt8)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE1Low0Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low0Dpt8In)))
// ... oder bei Wert
#define ParamLOG_fE1Low1Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low1Dpt8In)))
// ... oder bei Wert
#define ParamLOG_fE1Low2Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low2Dpt8In)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt8Fix                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1LowDpt8Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt9                          (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDpt9), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE1HighDpt9                         (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1HighDpt9), Float_Enc_IEEE754Single))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt9Fix                       (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDpt9Fix), Float_Enc_IEEE754Single))
// Von-Wert
#define ParamLOG_fE1LowDpt12                         (knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDpt12)))
// Bis-Wert
#define ParamLOG_fE1HighDpt12                        (knx.paramInt(LOG_ParamCalcIndex(LOG_fE1HighDpt12)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt12Fix                      (knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDpt12Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt13                         ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDpt13)))
// Bis-Wert
#define ParamLOG_fE1HighDpt13                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1HighDpt13)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt13Fix                      ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDpt13Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt14                         (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDpt14), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE1HighDpt14                        (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1HighDpt14), Float_Enc_IEEE754Single))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt14Fix                      (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDpt14Fix), Float_Enc_IEEE754Single))
// Eingang ist EIN bei Szene
#define ParamLOG_fE1Low0Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low1Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low2Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low3Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low4Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low4Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low5Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low5Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low6Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low6Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low7Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low7Dpt17)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt17Fix                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt17Fix)))
// Von-Wert
#define ParamLOG_fE1LowDptRGB                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDptRGB)))
// Bis-Wert
#define ParamLOG_fE1HighDptRGB                       ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1HighDptRGB)))
// Eingang ist konstant
#define ParamLOG_fE1LowDptRGBFix                     ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDptRGBFix)))
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE2ConvertInt                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2ConvertInt)) & LOG_fE2ConvertIntMask) >> LOG_fE2ConvertIntShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE2Convert                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Convert)) & LOG_fE2ConvertMask) >> LOG_fE2ConvertShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE2ConvertFloat                     ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2ConvertFloat)) & LOG_fE2ConvertFloatMask) >> LOG_fE2ConvertFloatShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE2ConvertSpecial                   ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2ConvertSpecial)) & LOG_fE2ConvertSpecialMask) >> LOG_fE2ConvertSpecialShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE2ConvertBool                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2ConvertBool)) & LOG_fE2ConvertBoolMask) >> LOG_fE2ConvertBoolShift)
// Eingang 2
#define ParamLOG_fE2                                 (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2)) & LOG_fE2Mask)
// DPT für Eingang
#define ParamLOG_fE2Dpt                              (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Dpt)))
// Eingang wird gelesen alle
#define ParamLOG_fE2RepeatBase                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2RepeatBase)) & LOG_fE2RepeatBaseMask) >> LOG_fE2RepeatBaseShift)
// Eingang wird gelesen alle
#define ParamLOG_fE2RepeatTime                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2RepeatTime)) & LOG_fE2RepeatTimeMask)
// Eingang wird gelesen alle (in Millisekunden)
#define ParamLOG_fE2RepeatTimeMS                     (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fE2RepeatTime))))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fE2OtherKO                          (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2OtherKO)))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fE2OtherKORel                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2OtherKORel)))
// Falls Vorbelegung aus dem Speicher nicht möglich oder nicht gewünscht, dann vorbelegen mit
#define ParamLOG_fE2Default                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Default)) & LOG_fE2DefaultMask)
// Eingang vorbelegen mit
#define ParamLOG_fE2DefaultExt                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2DefaultExt)) & LOG_fE2DefaultExtMask)
// Eingangswert speichern und beim nächsten Neustart als Vorbelegung nutzen?
#define ParamLOG_fE2DefaultEEPROM                    ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2DefaultEEPROM)) & LOG_fE2DefaultEEPROMMask))
// Nur so lange zyklisch lesen, bis erstes Telegramm eingeht
#define ParamLOG_fE2DefaultRepeat                    ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2DefaultRepeat)) & LOG_fE2DefaultRepeatMask))
// Kommunikationsobjekt für Eingang
#define ParamLOG_fE2UseOtherKO                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2UseOtherKO)) & LOG_fE2UseOtherKOMask) >> LOG_fE2UseOtherKOShift)
// Von-Wert
#define ParamLOG_fE2LowDelta                         ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDelta)))
// Bis-Wert
#define ParamLOG_fE2HighDelta                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2HighDelta)))
// Von-Wert
#define ParamLOG_fE2LowDeltaFloat                    (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDeltaFloat), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE2HighDeltaFloat                   (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2HighDeltaFloat), Float_Enc_IEEE754Single))
// Von-Wert
#define ParamLOG_fE2LowDeltaDouble                   (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDeltaDouble), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE2HighDeltaDouble                  (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2HighDeltaDouble), Float_Enc_IEEE754Single))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low0Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Valid)) & LOG_fE2Low0ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low1Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Valid)) & LOG_fE2Low1ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low2Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Valid)) & LOG_fE2Low2ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low3Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Valid)) & LOG_fE2Low3ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low4Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low4Valid)) & LOG_fE2Low4ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low5Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low5Valid)) & LOG_fE2Low5ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low6Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low6Valid)) & LOG_fE2Low6ValidMask))
// Eingang ist EIN, wenn Wert gleich
#define ParamLOG_fE2Low0Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE2Low1Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE2Low2Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE2Low3Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt2)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt2Fix                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt2Fix)))
// Eingang ist EIN, wenn Wert gleich
#define ParamLOG_fE2Low0Dpt3Dir                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt3Dir)) & LOG_fE2Low0Dpt3DirMask) >> LOG_fE2Low0Dpt3DirShift)
// 
#define ParamLOG_fE2Low0Dpt3Dim                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt3Dim)) & LOG_fE2Low0Dpt3DimMask)
// ... oder wenn Wert gleich 
#define ParamLOG_fE2Low1Dpt3Dir                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt3Dir)) & LOG_fE2Low1Dpt3DirMask) >> LOG_fE2Low1Dpt3DirShift)
// 
#define ParamLOG_fE2Low1Dpt3Dim                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt3Dim)) & LOG_fE2Low1Dpt3DimMask)
// ... oder wenn Wert gleich 
#define ParamLOG_fE2Low2Dpt3Dir                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt3Dir)) & LOG_fE2Low2Dpt3DirMask) >> LOG_fE2Low2Dpt3DirShift)
// 
#define ParamLOG_fE2Low2Dpt3Dim                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt3Dim)) & LOG_fE2Low2Dpt3DimMask)
// ... oder wenn Wert gleich 
#define ParamLOG_fE2Low3Dpt3Dir                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt3Dir)) & LOG_fE2Low3Dpt3DirMask) >> LOG_fE2Low3Dpt3DirShift)
// 
#define ParamLOG_fE2Low3Dpt3Dim                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt3Dim)) & LOG_fE2Low3Dpt3DimMask)
// Eingang ist konstant
#define ParamLOG_fE2LowDpt3FixDir                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt3FixDir)) & LOG_fE2LowDpt3FixDirMask) >> LOG_fE2LowDpt3FixDirShift)
// 
#define ParamLOG_fE2LowDpt3FixDim                    (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt3FixDim)) & LOG_fE2LowDpt3FixDimMask)
// Von-Wert
#define ParamLOG_fE2LowDpt5                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt5)))
// Bis-Wert
#define ParamLOG_fE2HighDpt5                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2HighDpt5)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE2Low0Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low1Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low2Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low3Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low4Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low4Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low5Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low5Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low6Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low6Dpt5In)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt5Fix                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt5Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt5001                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt5001)))
// Bis-Wert
#define ParamLOG_fE2HighDpt5001                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2HighDpt5001)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE2Low0Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low1Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low2Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low3Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low4Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low4Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low5Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low5Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low6Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low6Dpt5xIn)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt5xFix                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt5xFix)))
// Von-Wert
#define ParamLOG_fE2LowDpt6                          ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt6)))
// Bis-Wert
#define ParamLOG_fE2HighDpt6                         ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2HighDpt6)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE2Low0Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low1Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low2Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low3Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low4Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low4Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low5Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low5Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low6Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low6Dpt6In)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt6Fix                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt6Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt7                          (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2LowDpt7)))
// Bis-Wert
#define ParamLOG_fE2HighDpt7                         (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2HighDpt7)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE2Low0Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low0Dpt7In)))
// ... oder bei Wert
#define ParamLOG_fE2Low1Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low1Dpt7In)))
// ... oder bei Wert
#define ParamLOG_fE2Low2Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low2Dpt7In)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt7Fix                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2LowDpt7Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt8                          ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2LowDpt8)))
// Bis-Wert
#define ParamLOG_fE2HighDpt8                         ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2HighDpt8)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE2Low0Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low0Dpt8In)))
// ... oder bei Wert
#define ParamLOG_fE2Low1Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low1Dpt8In)))
// ... oder bei Wert
#define ParamLOG_fE2Low2Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low2Dpt8In)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt8Fix                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2LowDpt8Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt9                          (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDpt9), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE2HighDpt9                         (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2HighDpt9), Float_Enc_IEEE754Single))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt9Fix                       (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDpt9Fix), Float_Enc_IEEE754Single))
// Von-Wert
#define ParamLOG_fE2LowDpt12                         (knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDpt12)))
// Bis-Wert
#define ParamLOG_fE2HighDpt12                        (knx.paramInt(LOG_ParamCalcIndex(LOG_fE2HighDpt12)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt12Fix                      (knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDpt12Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt13                         ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDpt13)))
// Bis-Wert
#define ParamLOG_fE2HighDpt13                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2HighDpt13)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt13Fix                      ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDpt13Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt14                         (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDpt14), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE2HighDpt14                        (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2HighDpt14), Float_Enc_IEEE754Single))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt14Fix                      (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDpt14Fix), Float_Enc_IEEE754Single))
// Eingang ist EIN bei Szene
#define ParamLOG_fE2Low0Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low1Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low2Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low3Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low4Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low4Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low5Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low5Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low6Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low6Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low7Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low7Dpt17)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt17Fix                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt17Fix)))
// Von-Wert
#define ParamLOG_fE2LowDptRGB                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDptRGB)))
// Bis-Wert
#define ParamLOG_fE2HighDptRGB                       ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2HighDptRGB)))
// Eingang ist konstant
#define ParamLOG_fE2LowDptRGBFix                     ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDptRGBFix)))
// Zeitbezug
#define ParamLOG_fTd1DuskDawn                        ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1DuskDawn)) & LOG_fTd1DuskDawnMask) >> LOG_fTd1DuskDawnShift)
// Zeitbezug
#define ParamLOG_fTd2DuskDawn                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2DuskDawn)) & LOG_fTd2DuskDawnMask)
// Zeitbezug
#define ParamLOG_fTd3DuskDawn                        ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3DuskDawn)) & LOG_fTd3DuskDawnMask) >> LOG_fTd3DuskDawnShift)
// Zeitbezug
#define ParamLOG_fTd4DuskDawn                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4DuskDawn)) & LOG_fTd4DuskDawnMask)
// Zeitbezug
#define ParamLOG_fTd5DuskDawn                        ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5DuskDawn)) & LOG_fTd5DuskDawnMask) >> LOG_fTd5DuskDawnShift)
// Zeitbezug
#define ParamLOG_fTd6DuskDawn                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6DuskDawn)) & LOG_fTd6DuskDawnMask)
// Zeitbezug
#define ParamLOG_fTd7DuskDawn                        ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7DuskDawn)) & LOG_fTd7DuskDawnMask) >> LOG_fTd7DuskDawnShift)
// Zeitbezug
#define ParamLOG_fTd8DuskDawn                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8DuskDawn)) & LOG_fTd8DuskDawnMask)
// Typ der Zeitschaltuhr
#define ParamLOG_fTYearDay                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTYearDay)) & LOG_fTYearDayMask) >> LOG_fTYearDayShift)
// Feiertagsbehandlung
#define ParamLOG_fTHoliday                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTHoliday)) & LOG_fTHolidayMask) >> LOG_fTHolidayShift)
// Bei Neustart letzte Schaltzeit nachholen
#define ParamLOG_fTRestoreState                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTRestoreState)) & LOG_fTRestoreStateMask) >> LOG_fTRestoreStateShift)
// Urlaubsbehandlung
#define ParamLOG_fTVacation                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fTVacation)) & LOG_fTVacationMask)
// Zahlenwert
#define ParamLOG_fTd1ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1ValueNum)))
// Zahlenwert
#define ParamLOG_fTd2ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2ValueNum)))
// Zahlenwert
#define ParamLOG_fTd3ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3ValueNum)))
// Zahlenwert
#define ParamLOG_fTd4ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4ValueNum)))
// Zahlenwert
#define ParamLOG_fTd5ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5ValueNum)))
// Zahlenwert
#define ParamLOG_fTd6ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6ValueNum)))
// Zahlenwert
#define ParamLOG_fTd7ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7ValueNum)))
// Zahlenwert
#define ParamLOG_fTd8ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8ValueNum)))
// Schaltwert
#define ParamLOG_fTd1Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1Value)) & LOG_fTd1ValueMask))
// Grad
#define ParamLOG_fTd1Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1Degree)) & LOG_fTd1DegreeMask) >> LOG_fTd1DegreeShift)
// Stunde
#define ParamLOG_fTd1HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1HourAbs)) & LOG_fTd1HourAbsMask) >> LOG_fTd1HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd1HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1HourRel)) & LOG_fTd1HourRelMask) >> LOG_fTd1HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd1HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1HourRelShort)) & LOG_fTd1HourRelShortMask) >> LOG_fTd1HourRelShortShift)
// Minute
#define ParamLOG_fTd1MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1MinuteAbs)))
// Minute
#define ParamLOG_fTd1MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1MinuteRel)))
// Wochentag
#define ParamLOG_fTd1Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1Weekday)) & LOG_fTd1WeekdayMask)
// Schaltwert
#define ParamLOG_fTd2Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2Value)) & LOG_fTd2ValueMask))
// Grad
#define ParamLOG_fTd2Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2Degree)) & LOG_fTd2DegreeMask) >> LOG_fTd2DegreeShift)
// Stunde
#define ParamLOG_fTd2HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2HourAbs)) & LOG_fTd2HourAbsMask) >> LOG_fTd2HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd2HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2HourRel)) & LOG_fTd2HourRelMask) >> LOG_fTd2HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd2HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2HourRelShort)) & LOG_fTd2HourRelShortMask) >> LOG_fTd2HourRelShortShift)
// Minute
#define ParamLOG_fTd2MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2MinuteAbs)))
// Minute
#define ParamLOG_fTd2MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2MinuteRel)))
// Wochentag
#define ParamLOG_fTd2Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2Weekday)) & LOG_fTd2WeekdayMask)
// Schaltwert
#define ParamLOG_fTd3Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3Value)) & LOG_fTd3ValueMask))
// Grad
#define ParamLOG_fTd3Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3Degree)) & LOG_fTd3DegreeMask) >> LOG_fTd3DegreeShift)
// Stunde
#define ParamLOG_fTd3HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3HourAbs)) & LOG_fTd3HourAbsMask) >> LOG_fTd3HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd3HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3HourRel)) & LOG_fTd3HourRelMask) >> LOG_fTd3HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd3HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3HourRelShort)) & LOG_fTd3HourRelShortMask) >> LOG_fTd3HourRelShortShift)
// Minute
#define ParamLOG_fTd3MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3MinuteAbs)))
// Minute
#define ParamLOG_fTd3MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3MinuteRel)))
// Wochentag
#define ParamLOG_fTd3Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3Weekday)) & LOG_fTd3WeekdayMask)
// Schaltwert
#define ParamLOG_fTd4Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4Value)) & LOG_fTd4ValueMask))
// Grad
#define ParamLOG_fTd4Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4Degree)) & LOG_fTd4DegreeMask) >> LOG_fTd4DegreeShift)
// Stunde
#define ParamLOG_fTd4HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4HourAbs)) & LOG_fTd4HourAbsMask) >> LOG_fTd4HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd4HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4HourRel)) & LOG_fTd4HourRelMask) >> LOG_fTd4HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd4HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4HourRelShort)) & LOG_fTd4HourRelShortMask) >> LOG_fTd4HourRelShortShift)
// Minute
#define ParamLOG_fTd4MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4MinuteAbs)))
// Minute
#define ParamLOG_fTd4MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4MinuteRel)))
// Wochentag
#define ParamLOG_fTd4Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4Weekday)) & LOG_fTd4WeekdayMask)
// Schaltwert
#define ParamLOG_fTd5Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5Value)) & LOG_fTd5ValueMask))
// Grad
#define ParamLOG_fTd5Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5Degree)) & LOG_fTd5DegreeMask) >> LOG_fTd5DegreeShift)
// Stunde
#define ParamLOG_fTd5HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5HourAbs)) & LOG_fTd5HourAbsMask) >> LOG_fTd5HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd5HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5HourRel)) & LOG_fTd5HourRelMask) >> LOG_fTd5HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd5HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5HourRelShort)) & LOG_fTd5HourRelShortMask) >> LOG_fTd5HourRelShortShift)
// Minute
#define ParamLOG_fTd5MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5MinuteAbs)))
// Minute
#define ParamLOG_fTd5MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5MinuteRel)))
// Wochentag
#define ParamLOG_fTd5Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5Weekday)) & LOG_fTd5WeekdayMask)
// Schaltwert
#define ParamLOG_fTd6Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6Value)) & LOG_fTd6ValueMask))
// Grad
#define ParamLOG_fTd6Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6Degree)) & LOG_fTd6DegreeMask) >> LOG_fTd6DegreeShift)
// Stunde
#define ParamLOG_fTd6HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6HourAbs)) & LOG_fTd6HourAbsMask) >> LOG_fTd6HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd6HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6HourRel)) & LOG_fTd6HourRelMask) >> LOG_fTd6HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd6HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6HourRelShort)) & LOG_fTd6HourRelShortMask) >> LOG_fTd6HourRelShortShift)
// Minute
#define ParamLOG_fTd6MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6MinuteAbs)))
// Minute
#define ParamLOG_fTd6MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6MinuteRel)))
// Wochentag
#define ParamLOG_fTd6Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6Weekday)) & LOG_fTd6WeekdayMask)
// Schaltwert
#define ParamLOG_fTd7Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7Value)) & LOG_fTd7ValueMask))
// Grad
#define ParamLOG_fTd7Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7Degree)) & LOG_fTd7DegreeMask) >> LOG_fTd7DegreeShift)
// Stunde
#define ParamLOG_fTd7HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7HourAbs)) & LOG_fTd7HourAbsMask) >> LOG_fTd7HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd7HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7HourRel)) & LOG_fTd7HourRelMask) >> LOG_fTd7HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd7HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7HourRelShort)) & LOG_fTd7HourRelShortMask) >> LOG_fTd7HourRelShortShift)
// Minute
#define ParamLOG_fTd7MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7MinuteAbs)))
// Minute
#define ParamLOG_fTd7MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7MinuteRel)))
// Wochentag
#define ParamLOG_fTd7Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7Weekday)) & LOG_fTd7WeekdayMask)
// Schaltwert
#define ParamLOG_fTd8Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8Value)) & LOG_fTd8ValueMask))
// Grad
#define ParamLOG_fTd8Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8Degree)) & LOG_fTd8DegreeMask) >> LOG_fTd8DegreeShift)
// Stunde
#define ParamLOG_fTd8HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8HourAbs)) & LOG_fTd8HourAbsMask) >> LOG_fTd8HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd8HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8HourRel)) & LOG_fTd8HourRelMask) >> LOG_fTd8HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd8HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8HourRelShort)) & LOG_fTd8HourRelShortMask) >> LOG_fTd8HourRelShortShift)
// Minute
#define ParamLOG_fTd8MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8MinuteAbs)))
// Minute
#define ParamLOG_fTd8MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8MinuteRel)))
// Wochentag
#define ParamLOG_fTd8Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8Weekday)) & LOG_fTd8WeekdayMask)
// Mo
#define ParamLOG_fTy1Weekday1                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday1)) & LOG_fTy1Weekday1Mask))
// Di
#define ParamLOG_fTy1Weekday2                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday2)) & LOG_fTy1Weekday2Mask))
// Mi
#define ParamLOG_fTy1Weekday3                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday3)) & LOG_fTy1Weekday3Mask))
// Do
#define ParamLOG_fTy1Weekday4                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday4)) & LOG_fTy1Weekday4Mask))
// Fr
#define ParamLOG_fTy1Weekday5                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday5)) & LOG_fTy1Weekday5Mask))
// Sa
#define ParamLOG_fTy1Weekday6                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday6)) & LOG_fTy1Weekday6Mask))
// So
#define ParamLOG_fTy1Weekday7                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday7)) & LOG_fTy1Weekday7Mask))
// Tag
#define ParamLOG_fTy1Day                             ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Day)) & LOG_fTy1DayMask) >> LOG_fTy1DayShift)
// Wochentag
#define ParamLOG_fTy1IsWeekday                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1IsWeekday)) & LOG_fTy1IsWeekdayMask))
// Monat
#define ParamLOG_fTy1Month                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Month)) & LOG_fTy1MonthMask) >> LOG_fTy1MonthShift)
// Mo
#define ParamLOG_fTy2Weekday1                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday1)) & LOG_fTy2Weekday1Mask))
// Di
#define ParamLOG_fTy2Weekday2                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday2)) & LOG_fTy2Weekday2Mask))
// Mi
#define ParamLOG_fTy2Weekday3                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday3)) & LOG_fTy2Weekday3Mask))
// Do
#define ParamLOG_fTy2Weekday4                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday4)) & LOG_fTy2Weekday4Mask))
// Fr
#define ParamLOG_fTy2Weekday5                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday5)) & LOG_fTy2Weekday5Mask))
// Sa
#define ParamLOG_fTy2Weekday6                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday6)) & LOG_fTy2Weekday6Mask))
// So
#define ParamLOG_fTy2Weekday7                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday7)) & LOG_fTy2Weekday7Mask))
// Tag
#define ParamLOG_fTy2Day                             ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Day)) & LOG_fTy2DayMask) >> LOG_fTy2DayShift)
// Wochentag
#define ParamLOG_fTy2IsWeekday                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2IsWeekday)) & LOG_fTy2IsWeekdayMask))
// Monat
#define ParamLOG_fTy2Month                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Month)) & LOG_fTy2MonthMask) >> LOG_fTy2MonthShift)
// Mo
#define ParamLOG_fTy3Weekday1                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday1)) & LOG_fTy3Weekday1Mask))
// Di
#define ParamLOG_fTy3Weekday2                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday2)) & LOG_fTy3Weekday2Mask))
// Mi
#define ParamLOG_fTy3Weekday3                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday3)) & LOG_fTy3Weekday3Mask))
// Do
#define ParamLOG_fTy3Weekday4                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday4)) & LOG_fTy3Weekday4Mask))
// Fr
#define ParamLOG_fTy3Weekday5                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday5)) & LOG_fTy3Weekday5Mask))
// Sa
#define ParamLOG_fTy3Weekday6                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday6)) & LOG_fTy3Weekday6Mask))
// So
#define ParamLOG_fTy3Weekday7                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday7)) & LOG_fTy3Weekday7Mask))
// Tag
#define ParamLOG_fTy3Day                             ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Day)) & LOG_fTy3DayMask) >> LOG_fTy3DayShift)
// Wochentag
#define ParamLOG_fTy3IsWeekday                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3IsWeekday)) & LOG_fTy3IsWeekdayMask))
// Monat
#define ParamLOG_fTy3Month                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Month)) & LOG_fTy3MonthMask) >> LOG_fTy3MonthShift)
// Mo
#define ParamLOG_fTy4Weekday1                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday1)) & LOG_fTy4Weekday1Mask))
// Di
#define ParamLOG_fTy4Weekday2                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday2)) & LOG_fTy4Weekday2Mask))
// Mi
#define ParamLOG_fTy4Weekday3                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday3)) & LOG_fTy4Weekday3Mask))
// Do
#define ParamLOG_fTy4Weekday4                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday4)) & LOG_fTy4Weekday4Mask))
// Fr
#define ParamLOG_fTy4Weekday5                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday5)) & LOG_fTy4Weekday5Mask))
// Sa
#define ParamLOG_fTy4Weekday6                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday6)) & LOG_fTy4Weekday6Mask))
// So
#define ParamLOG_fTy4Weekday7                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday7)) & LOG_fTy4Weekday7Mask))
// Tag
#define ParamLOG_fTy4Day                             ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Day)) & LOG_fTy4DayMask) >> LOG_fTy4DayShift)
// Wochentag
#define ParamLOG_fTy4IsWeekday                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4IsWeekday)) & LOG_fTy4IsWeekdayMask))
// Monat
#define ParamLOG_fTy4Month                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Month)) & LOG_fTy4MonthMask) >> LOG_fTy4MonthShift)
// Interner Eingang 3
#define ParamLOG_fI1                                 ((knx.paramByte(LOG_ParamCalcIndex(LOG_fI1)) & LOG_fI1Mask) >> LOG_fI1Shift)
// Art der Verknüpfung
#define ParamLOG_fI1Kind                             ((knx.paramByte(LOG_ParamCalcIndex(LOG_fI1Kind)) & LOG_fI1KindMask) >> LOG_fI1KindShift)
// Internen Eingang als Trigger nutzen(ist immer logisch EIN)
#define ParamLOG_fI1AsTrigger                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fI1AsTrigger)) & LOG_fI1AsTriggerMask))
// Interner Eingang wird versorgt vom
#define ParamLOG_fI1InternalInputType                ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fI1InternalInputType)) & LOG_fI1InternalInputTypeMask))
// Internen Eingang verbinden mit Kanal Nr.
#define ParamLOG_fI1Function                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fI1Function)))
// Internen Eingang verbinden mit Kanal Nr.
#define ParamLOG_fI1FunctionRel                      ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fI1FunctionRel)))
// Statuskanal
#define ParamLOG_fI1StatusLed                        (knx.paramWord(LOG_ParamCalcIndex(LOG_fI1StatusLed)))
// Interner Eingang 4
#define ParamLOG_fI2                                 ((knx.paramByte(LOG_ParamCalcIndex(LOG_fI2)) & LOG_fI2Mask) >> LOG_fI2Shift)
// Art der Verknüpfung
#define ParamLOG_fI2Kind                             ((knx.paramByte(LOG_ParamCalcIndex(LOG_fI2Kind)) & LOG_fI2KindMask) >> LOG_fI2KindShift)
// Internen Eingang als Trigger nutzen(ist immer logisch EIN)
#define ParamLOG_fI2AsTrigger                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fI2AsTrigger)) & LOG_fI2AsTriggerMask))
// Interner Eingang wird versorgt vom
#define ParamLOG_fI2InternalInputType                ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fI2InternalInputType)) & LOG_fI2InternalInputTypeMask))
// Internen Eingang verbinden mit Kanal Nr.
#define ParamLOG_fI2Function                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fI2Function)))
// Internen Eingang verbinden mit Kanal Nr.
#define ParamLOG_fI2FunctionRel                      ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fI2FunctionRel)))
// Statuskanal
#define ParamLOG_fI2StatusLed                        (knx.paramWord(LOG_ParamCalcIndex(LOG_fI2StatusLed)))
// Zeit für Treppenlicht
#define ParamLOG_fOStairtimeBase                     ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOStairtimeBase)) & LOG_fOStairtimeBaseMask) >> LOG_fOStairtimeBaseShift)
// Zeit für Treppenlicht
#define ParamLOG_fOStairtimeTime                     (knx.paramWord(LOG_ParamCalcIndex(LOG_fOStairtimeTime)) & LOG_fOStairtimeTimeMask)
// Zeit für Treppenlicht (in Millisekunden)
#define ParamLOG_fOStairtimeTimeMS                   (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fOStairtimeTime))))
// Treppenlicht blinkt im Rhythmus
#define ParamLOG_fOBlinkBase                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOBlinkBase)) & LOG_fOBlinkBaseMask) >> LOG_fOBlinkBaseShift)
// Treppenlicht blinkt im Rhythmus
#define ParamLOG_fOBlinkTime                         (knx.paramWord(LOG_ParamCalcIndex(LOG_fOBlinkTime)) & LOG_fOBlinkTimeMask)
// Treppenlicht blinkt im Rhythmus (in Millisekunden)
#define ParamLOG_fOBlinkTimeMS                       (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fOBlinkTime))))
// EINschalten wird verzögert um
#define ParamLOG_fODelayOnBase                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOnBase)) & LOG_fODelayOnBaseMask) >> LOG_fODelayOnBaseShift)
// EINschalten wird verzögert um
#define ParamLOG_fODelayOnTime                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fODelayOnTime)) & LOG_fODelayOnTimeMask)
// EINschalten wird verzögert um (in Millisekunden)
#define ParamLOG_fODelayOnTimeMS                     (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fODelayOnTime))))
// AUSschalten wird verzögert um
#define ParamLOG_fODelayOffBase                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOffBase)) & LOG_fODelayOffBaseMask) >> LOG_fODelayOffBaseShift)
// AUSschalten wird verzögert um
#define ParamLOG_fODelayOffTime                      (knx.paramWord(LOG_ParamCalcIndex(LOG_fODelayOffTime)) & LOG_fODelayOffTimeMask)
// AUSschalten wird verzögert um (in Millisekunden)
#define ParamLOG_fODelayOffTimeMS                    (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fODelayOffTime))))
// EIN-Telegramm wird wiederholt alle
#define ParamLOG_fORepeatOnBase                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fORepeatOnBase)) & LOG_fORepeatOnBaseMask) >> LOG_fORepeatOnBaseShift)
// EIN-Telegramm wird wiederholt alle
#define ParamLOG_fORepeatOnTime                      (knx.paramWord(LOG_ParamCalcIndex(LOG_fORepeatOnTime)) & LOG_fORepeatOnTimeMask)
// EIN-Telegramm wird wiederholt alle (in Millisekunden)
#define ParamLOG_fORepeatOnTimeMS                    (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fORepeatOnTime))))
// AUS-Telegramm wird wiederholt alle
#define ParamLOG_fORepeatOffBase                     ((knx.paramByte(LOG_ParamCalcIndex(LOG_fORepeatOffBase)) & LOG_fORepeatOffBaseMask) >> LOG_fORepeatOffBaseShift)
// AUS-Telegramm wird wiederholt alle
#define ParamLOG_fORepeatOffTime                     (knx.paramWord(LOG_ParamCalcIndex(LOG_fORepeatOffTime)) & LOG_fORepeatOffTimeMask)
// AUS-Telegramm wird wiederholt alle (in Millisekunden)
#define ParamLOG_fORepeatOffTimeMS                   (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fORepeatOffTime))))
// Ausgang schaltet zeitverzögert
#define ParamLOG_fODelay                             ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fODelay)) & LOG_fODelayMask))
// Erneutes EIN führt zu
#define ParamLOG_fODelayOnRepeat                     ((knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOnRepeat)) & LOG_fODelayOnRepeatMask) >> LOG_fODelayOnRepeatShift)
// Darauffolgendes AUS führt zu
#define ParamLOG_fODelayOnReset                      ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOnReset)) & LOG_fODelayOnResetMask))
// Erneutes AUS führt zu
#define ParamLOG_fODelayOffRepeat                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOffRepeat)) & LOG_fODelayOffRepeatMask) >> LOG_fODelayOffRepeatShift)
// Darauffolgendes EIN führt zu
#define ParamLOG_fODelayOffReset                     ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOffReset)) & LOG_fODelayOffResetMask))
// Ausgang hat eine Treppenlichtfunktion
#define ParamLOG_fOStair                             ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fOStair)) & LOG_fOStairMask))
// Treppenlicht kann verlängert werden
#define ParamLOG_fORetrigger                         ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fORetrigger)) & LOG_fORetriggerMask))
// Treppenlicht kann ausgeschaltet werden
#define ParamLOG_fOStairOff                          ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fOStairOff)) & LOG_fOStairOffMask))
// Ausgang wiederholt zyklisch
#define ParamLOG_fORepeat                            ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fORepeat)) & LOG_fORepeatMask))
// Wiederholungsfilter
#define ParamLOG_fOOutputFilter                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOutputFilter)) & LOG_fOOutputFilterMask) >> LOG_fOOutputFilterShift)
// Sendeverhalten für Ausgang
#define ParamLOG_fOSendOnChange                      ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fOSendOnChange)) & LOG_fOSendOnChangeMask))
// DPT für Ausgang
#define ParamLOG_fODpt                               (knx.paramByte(LOG_ParamCalcIndex(LOG_fODpt)))
// Wert für EIN senden?
#define ParamLOG_fOOnAll                             (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnAll)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt1                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt1)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt2                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt2)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt3Dir                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt3Dir)) & LOG_fOOnDpt3DirMask) >> LOG_fOOnDpt3DirShift)
// 
#define ParamLOG_fOOnDpt3Dim                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt3Dim)) & LOG_fOOnDpt3DimMask)
//     Wert für EIN senden als 
#define ParamLOG_fOOnDpt5                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt5)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt5001                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt5001)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt6                            ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt6)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt7                            (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnDpt7)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt8                            ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnDpt8)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt9                            (knx.paramFloat(LOG_ParamCalcIndex(LOG_fOOnDpt9), Float_Enc_IEEE754Single))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt12                           (knx.paramInt(LOG_ParamCalcIndex(LOG_fOOnDpt12)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt13                           ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fOOnDpt13)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt14                           (knx.paramFloat(LOG_ParamCalcIndex(LOG_fOOnDpt14), Float_Enc_IEEE754Single))
//     Wert für EIN senden als 
#define ParamLOG_fOOnDpt16                           (knx.paramData(LOG_ParamCalcIndex(LOG_fOOnDpt16)))
#define ParamLOG_fOOnDpt16Str                        (knx.paramString(LOG_ParamCalcIndex(LOG_fOOnDpt16), LOG_fOOnDpt16Length))
//     Wert für EIN senden als 
#define ParamLOG_fOOnDpt17                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt17)))
//     Wert für EIN senden als (3-Byte-RGB)
#define ParamLOG_fOOnRGB                             ((knx.paramInt(LOG_ParamCalcIndex(LOG_fOOnRGB)) & LOG_fOOnRGBMask) >> LOG_fOOnRGBShift)
//     Status-LED Kanal
#define ParamLOG_fOOnLedProvider                     (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnLedProvider)) & LOG_fOOnLedProviderMask)
//     Status-LED Effekt
#define ParamLOG_fOOnLedEffect                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnLedEffect)) & LOG_fOOnLedEffectMask)
//     Status-LED Effektdauer
#define ParamLOG_fOOnLedDuration                     (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnLedDuration)))
// 
#define ParamLOG_fOOnPAArea                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnPAArea)) & LOG_fOOnPAAreaMask) >> LOG_fOOnPAAreaShift)
// 
#define ParamLOG_fOOnPALine                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnPALine)) & LOG_fOOnPALineMask)
// 
#define ParamLOG_fOOnPADevice                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnPADevice)))
//     Wert für EIN ermitteln als
#define ParamLOG_fOOnFunction                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnFunction)))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fOOnKOKind                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnKOKind)) & LOG_fOOnKOKindMask) >> LOG_fOOnKOKindShift)
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fOOnKONumber                        (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnKONumber)))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fOOnKONumberRel                     ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnKONumberRel)))
//     DPT des Kommunikationsobjekts
#define ParamLOG_fOOnKODpt                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnKODpt)))
//     Wert für EIN an ein zusätzliches    KO senden?
#define ParamLOG_fOOnKOSend                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnKOSend)) & LOG_fOOnKOSendMask) >> LOG_fOOnKOSendShift)
//         Nummer des zusätzlichen KO
#define ParamLOG_fOOnKOSendNumber                    (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnKOSendNumber)))
//         Nummer des zusätzlichen KO
#define ParamLOG_fOOnKOSendNumberRel                 ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnKOSendNumberRel)))
// Wert für AUS senden?
#define ParamLOG_fOOffAll                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffAll)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt1                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt1)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt2                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt2)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt3Dir                        ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt3Dir)) & LOG_fOOffDpt3DirMask) >> LOG_fOOffDpt3DirShift)
// 
#define ParamLOG_fOOffDpt3Dim                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt3Dim)) & LOG_fOOffDpt3DimMask)
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt5                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt5)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt5001                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt5001)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt6                           ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt6)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt7                           (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffDpt7)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt8                           ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffDpt8)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt9                           (knx.paramFloat(LOG_ParamCalcIndex(LOG_fOOffDpt9), Float_Enc_IEEE754Single))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt12                          (knx.paramInt(LOG_ParamCalcIndex(LOG_fOOffDpt12)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt13                          ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fOOffDpt13)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt14                          (knx.paramFloat(LOG_ParamCalcIndex(LOG_fOOffDpt14), Float_Enc_IEEE754Single))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt16                          (knx.paramData(LOG_ParamCalcIndex(LOG_fOOffDpt16)))
#define ParamLOG_fOOffDpt16Str                       (knx.paramString(LOG_ParamCalcIndex(LOG_fOOffDpt16), LOG_fOOffDpt16Length))
//     Wert für AUS senden als 
#define ParamLOG_fOOffDpt17                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt17)))
//     Wert für AUS senden als (3-Byte-RGB)
#define ParamLOG_fOOffRGB                            ((knx.paramInt(LOG_ParamCalcIndex(LOG_fOOffRGB)) & LOG_fOOffRGBMask) >> LOG_fOOffRGBShift)
//     Status-LED-Kanal
#define ParamLOG_fOOffLedProvider                    (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffLedProvider)) & LOG_fOOffLedProviderMask)
//     Status-LED Effekt
#define ParamLOG_fOOffLedEffect                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffLedEffect)) & LOG_fOOffLedEffectMask)
//     Status-LED Effektdauer
#define ParamLOG_fOOffLedDuration                    (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffLedDuration)))
// 
#define ParamLOG_fOOffPAArea                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffPAArea)) & LOG_fOOffPAAreaMask) >> LOG_fOOffPAAreaShift)
// 
#define ParamLOG_fOOffPALine                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffPALine)) & LOG_fOOffPALineMask)
// 
#define ParamLOG_fOOffPADevice                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffPADevice)))
//     Wert für AUS ermitteln als
#define ParamLOG_fOOffFunction                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffFunction)))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fOOffKOKind                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffKOKind)) & LOG_fOOffKOKindMask) >> LOG_fOOffKOKindShift)
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fOOffKONumber                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffKONumber)))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fOOffKONumberRel                    ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffKONumberRel)))
//     DPT des Kommunikationsobjekts
#define ParamLOG_fOOffKODpt                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffKODpt)))
//     Wert für AUS an ein zusätzliches    KO senden?
#define ParamLOG_fOOffKOSend                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffKOSend)) & LOG_fOOffKOSendMask) >> LOG_fOOffKOSendShift)
//         Nummer des zusätzlichen KO
#define ParamLOG_fOOffKOSendNumber                   (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffKOSendNumber)))
//         Nummer des zusätzlichen KO
#define ParamLOG_fOOffKOSendNumberRel                ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffKOSendNumberRel)))

// deprecated
#define LOG_KoOffset 100

// Communication objects per channel (multiple occurrence)
#define LOG_KoBlockOffset 100
#define LOG_KoBlockSize 3

#define LOG_KoCalcNumber(index) (index + LOG_KoBlockOffset + _channelIndex * LOG_KoBlockSize)
#define LOG_KoCalcIndex(number) ((number >= LOG_KoCalcNumber(0) && number < LOG_KoCalcNumber(LOG_KoBlockSize)) ? (number - LOG_KoBlockOffset) % LOG_KoBlockSize : -1)
#define LOG_KoCalcChannel(number) ((number >= LOG_KoBlockOffset && number < LOG_KoBlockOffset + LOG_ChannelCount * LOG_KoBlockSize) ? (number - LOG_KoBlockOffset) / LOG_KoBlockSize : -1)

#define LOG_KoKOfE1 0
#define LOG_KoKOfE2 1
#define LOG_KoKOfO 2

// Eingang 1
#define KoLOG_KOfE1                               (knx.getGroupObject(LOG_KoCalcNumber(LOG_KoKOfE1)))
// Eingang 2
#define KoLOG_KOfE2                               (knx.getGroupObject(LOG_KoCalcNumber(LOG_KoKOfE2)))
// Ausgang
#define KoLOG_KOfO                                (knx.getGroupObject(LOG_KoCalcNumber(LOG_KoKOfO)))

#define FCB_VisibleChannels                     12821      // uint8_t

// Verfügbare Kanäle
#define ParamFCB_VisibleChannels                     (knx.paramByte(FCB_VisibleChannels))

#define FCB_ChannelCount 15

// Parameter per channel
#define FCB_ParamBlockOffset 12822
#define FCB_ParamBlockSize 81
#define FCB_ParamCalcIndex(index) (index + FCB_ParamBlockOffset + _channelIndex * FCB_ParamBlockSize)

#define FCB_CHChannelType                        0      // 8 Bits, Bit 7-0
#define FCB_CHChannelDisabled                    1      // 1 Bit, Bit 7
#define     FCB_CHChannelDisabledMask 0x80
#define     FCB_CHChannelDisabledShift 7
#define FCB_CHLogicKo0D                          2      // 2 Bits, Bit 7-6
#define     FCB_CHLogicKo0DMask 0xC0
#define     FCB_CHLogicKo0DShift 6
#define FCB_CHLogicKo1D                          2      // 2 Bits, Bit 5-4
#define     FCB_CHLogicKo1DMask 0x30
#define     FCB_CHLogicKo1DShift 4
#define FCB_CHLogicKo2D                          2      // 2 Bits, Bit 3-2
#define     FCB_CHLogicKo2DMask 0x0C
#define     FCB_CHLogicKo2DShift 2
#define FCB_CHLogicKo3D                          2      // 2 Bits, Bit 1-0
#define     FCB_CHLogicKo3DMask 0x03
#define     FCB_CHLogicKo3DShift 0
#define FCB_CHLogicKo4D                          3      // 2 Bits, Bit 7-6
#define     FCB_CHLogicKo4DMask 0xC0
#define     FCB_CHLogicKo4DShift 6
#define FCB_CHLogicKo5D                          3      // 2 Bits, Bit 5-4
#define     FCB_CHLogicKo5DMask 0x30
#define     FCB_CHLogicKo5DShift 4
#define FCB_CHLogicKo6D                          3      // 2 Bits, Bit 3-2
#define     FCB_CHLogicKo6DMask 0x0C
#define     FCB_CHLogicKo6DShift 2
#define FCB_CHLogicKo7D                          3      // 2 Bits, Bit 1-0
#define     FCB_CHLogicKo7DMask 0x03
#define     FCB_CHLogicKo7DShift 0
#define FCB_CHLogicKo8D                          4      // 2 Bits, Bit 7-6
#define     FCB_CHLogicKo8DMask 0xC0
#define     FCB_CHLogicKo8DShift 6
#define FCB_CHLogicOutInv                        4      // 1 Bit, Bit 4
#define     FCB_CHLogicOutInvMask 0x10
#define     FCB_CHLogicOutInvShift 4
#define FCB_CHLogicBehavOut                      4      // 1 Bit, Bit 3
#define     FCB_CHLogicBehavOutMask 0x08
#define     FCB_CHLogicBehavOutShift 3
#define FCB_CHLogicBehavKo0                      5      // 4 Bits, Bit 7-4
#define     FCB_CHLogicBehavKo0Mask 0xF0
#define     FCB_CHLogicBehavKo0Shift 4
#define FCB_CHLogicBehavKo1                      5      // 4 Bits, Bit 3-0
#define     FCB_CHLogicBehavKo1Mask 0x0F
#define     FCB_CHLogicBehavKo1Shift 0
#define FCB_CHLogicBehavKo2                      6      // 4 Bits, Bit 7-4
#define     FCB_CHLogicBehavKo2Mask 0xF0
#define     FCB_CHLogicBehavKo2Shift 4
#define FCB_CHLogicBehavKo3                      6      // 4 Bits, Bit 3-0
#define     FCB_CHLogicBehavKo3Mask 0x0F
#define     FCB_CHLogicBehavKo3Shift 0
#define FCB_CHLogicBehavKo4                      7      // 4 Bits, Bit 7-4
#define     FCB_CHLogicBehavKo4Mask 0xF0
#define     FCB_CHLogicBehavKo4Shift 4
#define FCB_CHLogicBehavKo5                      7      // 4 Bits, Bit 3-0
#define     FCB_CHLogicBehavKo5Mask 0x0F
#define     FCB_CHLogicBehavKo5Shift 0
#define FCB_CHLogicBehavKo6                      8      // 4 Bits, Bit 7-4
#define     FCB_CHLogicBehavKo6Mask 0xF0
#define     FCB_CHLogicBehavKo6Shift 4
#define FCB_CHLogicBehavKo7                      8      // 4 Bits, Bit 3-0
#define     FCB_CHLogicBehavKo7Mask 0x0F
#define     FCB_CHLogicBehavKo7Shift 0
#define FCB_CHLogicBehavKo8                      9      // 4 Bits, Bit 7-4
#define     FCB_CHLogicBehavKo8Mask 0xF0
#define     FCB_CHLogicBehavKo8Shift 4
#define FCB_CHBayesianPrior                     10      // uint8_t
#define FCB_CHBayesianThreshold                 11      // uint8_t
#define FCB_CHBayesianEnableProbOutput          12      // 1 Bit, Bit 7
#define     FCB_CHBayesianEnableProbOutputMask 0x80
#define     FCB_CHBayesianEnableProbOutputShift 7
#define FCB_CHLogicKo0BayesProbTrue             15      // uint8_t
#define FCB_CHLogicKo0BayesProbFalse            16      // uint8_t
#define FCB_CHLogicKo1BayesProbTrue             17      // uint8_t
#define FCB_CHLogicKo1BayesProbFalse            18      // uint8_t
#define FCB_CHLogicKo2BayesProbTrue             19      // uint8_t
#define FCB_CHLogicKo2BayesProbFalse            20      // uint8_t
#define FCB_CHLogicKo3BayesProbTrue             21      // uint8_t
#define FCB_CHLogicKo3BayesProbFalse            22      // uint8_t
#define FCB_CHLogicKo4BayesProbTrue             23      // uint8_t
#define FCB_CHLogicKo4BayesProbFalse            24      // uint8_t
#define FCB_CHLogicKo5BayesProbTrue             25      // uint8_t
#define FCB_CHLogicKo5BayesProbFalse            26      // uint8_t
#define FCB_CHLogicKo6BayesProbTrue             27      // uint8_t
#define FCB_CHLogicKo6BayesProbFalse            28      // uint8_t
#define FCB_CHLogicKo7BayesProbTrue             29      // uint8_t
#define FCB_CHLogicKo7BayesProbFalse            30      // uint8_t
#define FCB_CHLogicKo8BayesProbTrue             31      // uint8_t
#define FCB_CHLogicKo8BayesProbFalse            32      // uint8_t
#define FCB_CHPrioKo0D                           2      // 2 Bits, Bit 7-6
#define     FCB_CHPrioKo0DMask 0xC0
#define     FCB_CHPrioKo0DShift 6
#define FCB_CHPrioKo1D                           2      // 2 Bits, Bit 5-4
#define     FCB_CHPrioKo1DMask 0x30
#define     FCB_CHPrioKo1DShift 4
#define FCB_CHPrioKo2D                           2      // 2 Bits, Bit 3-2
#define     FCB_CHPrioKo2DMask 0x0C
#define     FCB_CHPrioKo2DShift 2
#define FCB_CHPrioKo3D                           2      // 2 Bits, Bit 1-0
#define     FCB_CHPrioKo3DMask 0x03
#define     FCB_CHPrioKo3DShift 0
#define FCB_CHPrioKo4D                           3      // 2 Bits, Bit 7-6
#define     FCB_CHPrioKo4DMask 0xC0
#define     FCB_CHPrioKo4DShift 6
#define FCB_CHPrioKo5D                           3      // 2 Bits, Bit 5-4
#define     FCB_CHPrioKo5DMask 0x30
#define     FCB_CHPrioKo5DShift 4
#define FCB_CHPrioKo6D                           3      // 2 Bits, Bit 3-2
#define     FCB_CHPrioKo6DMask 0x0C
#define     FCB_CHPrioKo6DShift 2
#define FCB_CHPrioKo7D                           3      // 2 Bits, Bit 1-0
#define     FCB_CHPrioKo7DMask 0x03
#define     FCB_CHPrioKo7DShift 0
#define FCB_CHPrioKo8D                           4      // 2 Bits, Bit 7-6
#define     FCB_CHPrioKo8DMask 0xC0
#define     FCB_CHPrioKo8DShift 6
#define FCB_CHPrioOutputType                     4      // 2 Bits, Bit 5-4
#define     FCB_CHPrioOutputTypeMask 0x30
#define     FCB_CHPrioOutputTypeShift 4
#define FCB_CHPrioOutPKo0                        5      // uint8_t
#define FCB_CHPrioOutByteKo0                     5      // uint8_t
#define FCB_CHPrioOutSceneKo0                    5      // uint8_t
#define FCB_CHPrioOutPKo1                        6      // uint8_t
#define FCB_CHPrioOutByteKo1                     6      // uint8_t
#define FCB_CHPrioOutSceneKo1                    6      // uint8_t
#define FCB_CHPrioOutPKo2                        7      // uint8_t
#define FCB_CHPrioOutByteKo2                     7      // uint8_t
#define FCB_CHPrioOutSceneKo2                    7      // uint8_t
#define FCB_CHPrioOutPKo3                        8      // uint8_t
#define FCB_CHPrioOutByteKo3                     8      // uint8_t
#define FCB_CHPrioOutSceneKo3                    8      // uint8_t
#define FCB_CHPrioOutPKo4                        9      // uint8_t
#define FCB_CHPrioOutByteKo4                     9      // uint8_t
#define FCB_CHPrioOutSceneKo4                    9      // uint8_t
#define FCB_CHPrioOutPKo5                       10      // uint8_t
#define FCB_CHPrioOutByteKo5                    10      // uint8_t
#define FCB_CHPrioOutSceneKo5                   10      // uint8_t
#define FCB_CHPrioOutPKo6                       11      // uint8_t
#define FCB_CHPrioOutByteKo6                    11      // uint8_t
#define FCB_CHPrioOutSceneKo6                   11      // uint8_t
#define FCB_CHPrioOutPKo7                       12      // uint8_t
#define FCB_CHPrioOutByteKo7                    12      // uint8_t
#define FCB_CHPrioOutSceneKo7                   12      // uint8_t
#define FCB_CHPrioOutPKo8                       13      // uint8_t
#define FCB_CHPrioOutByteKo8                    13      // uint8_t
#define FCB_CHPrioOutSceneKo8                   13      // uint8_t
#define FCB_CHPrioOutPDefault                   14      // uint8_t
#define FCB_CHPrioOutByteDefault                14      // uint8_t
#define FCB_CHPrioOutSceneDefault               14      // uint8_t
#define FCB_CHPrioBehavKo0                      15      // 4 Bits, Bit 7-4
#define     FCB_CHPrioBehavKo0Mask 0xF0
#define     FCB_CHPrioBehavKo0Shift 4
#define FCB_CHPrioBehavKo1                      15      // 4 Bits, Bit 3-0
#define     FCB_CHPrioBehavKo1Mask 0x0F
#define     FCB_CHPrioBehavKo1Shift 0
#define FCB_CHPrioBehavKo2                      16      // 4 Bits, Bit 7-4
#define     FCB_CHPrioBehavKo2Mask 0xF0
#define     FCB_CHPrioBehavKo2Shift 4
#define FCB_CHPrioBehavKo3                      16      // 4 Bits, Bit 3-0
#define     FCB_CHPrioBehavKo3Mask 0x0F
#define     FCB_CHPrioBehavKo3Shift 0
#define FCB_CHPrioBehavKo4                      17      // 4 Bits, Bit 7-4
#define     FCB_CHPrioBehavKo4Mask 0xF0
#define     FCB_CHPrioBehavKo4Shift 4
#define FCB_CHPrioBehavKo5                      17      // 4 Bits, Bit 3-0
#define     FCB_CHPrioBehavKo5Mask 0x0F
#define     FCB_CHPrioBehavKo5Shift 0
#define FCB_CHPrioBehavKo6                      18      // 4 Bits, Bit 7-4
#define     FCB_CHPrioBehavKo6Mask 0xF0
#define     FCB_CHPrioBehavKo6Shift 4
#define FCB_CHPrioBehavKo7                      18      // 4 Bits, Bit 3-0
#define     FCB_CHPrioBehavKo7Mask 0x0F
#define     FCB_CHPrioBehavKo7Shift 0
#define FCB_CHPrioBehavKo8                      19      // 4 Bits, Bit 7-4
#define     FCB_CHPrioBehavKo8Mask 0xF0
#define     FCB_CHPrioBehavKo8Shift 4
#define FCB_CHPrioBehavOut                      19      // 1 Bit, Bit 3
#define     FCB_CHPrioBehavOutMask 0x08
#define     FCB_CHPrioBehavOutShift 3
#define FCB_CHAggWeight                          2      // 1 Bit, Bit 7
#define     FCB_CHAggWeightMask 0x80
#define     FCB_CHAggWeightShift 7
#define FCB_CHAggType                            2      // 7 Bits, Bit 6-0
#define     FCB_CHAggTypeMask 0x7F
#define     FCB_CHAggTypeShift 0
#define FCB_CHAggKo0D                            3      // 2 Bits, Bit 7-6
#define     FCB_CHAggKo0DMask 0xC0
#define     FCB_CHAggKo0DShift 6
#define FCB_CHAggKo1D                            3      // 2 Bits, Bit 5-4
#define     FCB_CHAggKo1DMask 0x30
#define     FCB_CHAggKo1DShift 4
#define FCB_CHAggKo2D                            3      // 2 Bits, Bit 3-2
#define     FCB_CHAggKo2DMask 0x0C
#define     FCB_CHAggKo2DShift 2
#define FCB_CHAggKo3D                            3      // 2 Bits, Bit 1-0
#define     FCB_CHAggKo3DMask 0x03
#define     FCB_CHAggKo3DShift 0
#define FCB_CHAggKo4D                            4      // 2 Bits, Bit 7-6
#define     FCB_CHAggKo4DMask 0xC0
#define     FCB_CHAggKo4DShift 6
#define FCB_CHAggKo5D                            4      // 2 Bits, Bit 5-4
#define     FCB_CHAggKo5DMask 0x30
#define     FCB_CHAggKo5DShift 4
#define FCB_CHAggKo6D                            4      // 2 Bits, Bit 3-2
#define     FCB_CHAggKo6DMask 0x0C
#define     FCB_CHAggKo6DShift 2
#define FCB_CHAggKo7D                            4      // 2 Bits, Bit 1-0
#define     FCB_CHAggKo7DMask 0x03
#define     FCB_CHAggKo7DShift 0
#define FCB_CHAggKo8D                            5      // 2 Bits, Bit 7-6
#define     FCB_CHAggKo8DMask 0xC0
#define     FCB_CHAggKo8DShift 6
#define FCB_CHAggBehavOut                        5      // 1 Bit, Bit 5
#define     FCB_CHAggBehavOutMask 0x20
#define     FCB_CHAggBehavOutShift 5
#define FCB_CHAggOutputRounding                  5      // 1 Bit, Bit 3
#define     FCB_CHAggOutputRoundingMask 0x08
#define     FCB_CHAggOutputRoundingShift 3
#define FCB_CHAggOutputOverflow                  5      // 2 Bits, Bit 2-1
#define     FCB_CHAggOutputOverflowMask 0x06
#define     FCB_CHAggOutputOverflowShift 1
#define FCB_CHAggInputDpt                        6      // 8 Bits, Bit 7-0
#define FCB_CHAggOutputDptEff                    7      // 8 Bits, Bit 7-0
#define FCB_CHAggKo0W                            8      // int8_t
#define FCB_CHAggKo1W                            9      // int8_t
#define FCB_CHAggKo2W                           10      // int8_t
#define FCB_CHAggKo3W                           11      // int8_t
#define FCB_CHAggKo4W                           12      // int8_t
#define FCB_CHAggKo5W                           13      // int8_t
#define FCB_CHAggKo6W                           14      // int8_t
#define FCB_CHAggKo7W                           15      // int8_t
#define FCB_CHAggKo8W                           16      // int8_t
#define FCB_CHCountDownTimeStartKo               2      // 4 Bits, Bit 7-4
#define     FCB_CHCountDownTimeStartKoMask 0xF0
#define     FCB_CHCountDownTimeStartKoShift 4
#define FCB_CHCountDownDelayBase                 3      // 2 Bits, Bit 7-6
#define     FCB_CHCountDownDelayBaseMask 0xC0
#define     FCB_CHCountDownDelayBaseShift 6
#define FCB_CHCountDownDelayTime                 3      // 14 Bits, Bit 13-0
#define     FCB_CHCountDownDelayTimeMask 0x3FFF
#define     FCB_CHCountDownDelayTimeShift 0
#define FCB_CHCountDownTimeOffset                5      // 4 Bits, Bit 7-4
#define     FCB_CHCountDownTimeOffsetMask 0xF0
#define     FCB_CHCountDownTimeOffsetShift 4
#define FCB_CHCountDownTrigger                   5      // 4 Bits, Bit 3-0
#define     FCB_CHCountDownTriggerMask 0x0F
#define     FCB_CHCountDownTriggerShift 0
#define FCB_CHCountDownTemplate                  6      // char*, 14 Byte
#define     FCB_CHCountDownTemplateLength 14
#define FCB_CHCountDownTemplate1h               20      // char*, 14 Byte
#define     FCB_CHCountDownTemplate1hLength 14
#define FCB_CHCountDownTemplate1m               34      // char*, 14 Byte
#define     FCB_CHCountDownTemplate1mLength 14
#define FCB_CHCountDownTemplateEnd              48      // char*, 14 Byte
#define     FCB_CHCountDownTemplateEndLength 14
#define FCB_CHCountDownTextPause                62      // char*, 1 Byte
#define     FCB_CHCountDownTextPauseLength 1
#define FCB_CHCountDownTextRun                  63      // char*, 1 Byte
#define     FCB_CHCountDownTextRunLength 1
#define FCB_CHCountDownCounterKo                64      // 4 Bits, Bit 7-4
#define     FCB_CHCountDownCounterKoMask 0xF0
#define     FCB_CHCountDownCounterKoShift 4
#define FCB_CHCountDownTextKo                   64      // 2 Bits, Bit 3-2
#define     FCB_CHCountDownTextKoMask 0x0C
#define     FCB_CHCountDownTextKoShift 2
#define FCB_CHCountDownTemplateStopp            65      // char*, 14 Byte
#define     FCB_CHCountDownTemplateStoppLength 14
#define FCB_CHCountDownMaxDelayBase             79      // 2 Bits, Bit 7-6
#define     FCB_CHCountDownMaxDelayBaseMask 0xC0
#define     FCB_CHCountDownMaxDelayBaseShift 6
#define FCB_CHCountDownMaxDelayTime             79      // 14 Bits, Bit 13-0
#define     FCB_CHCountDownMaxDelayTimeMask 0x3FFF
#define     FCB_CHCountDownMaxDelayTimeShift 0
#define FCB_CHMonitoringValueType                2      // 8 Bits, Bit 7-0
#define FCB_CHMonitoringWDEnabled                3      // 1 Bit, Bit 7
#define     FCB_CHMonitoringWDEnabledMask 0x80
#define     FCB_CHMonitoringWDEnabledShift 7
#define FCB_CHMonitoringWDTTimeoutDelayBase      4      // 2 Bits, Bit 7-6
#define     FCB_CHMonitoringWDTTimeoutDelayBaseMask 0xC0
#define     FCB_CHMonitoringWDTTimeoutDelayBaseShift 6
#define FCB_CHMonitoringWDTTimeoutDelayTime      4      // 14 Bits, Bit 13-0
#define     FCB_CHMonitoringWDTTimeoutDelayTimeMask 0x3FFF
#define     FCB_CHMonitoringWDTTimeoutDelayTimeShift 0
#define FCB_CHMonitoringWDBehavior               6      // 4 Bits, Bit 7-4
#define     FCB_CHMonitoringWDBehaviorMask 0xF0
#define     FCB_CHMonitoringWDBehaviorShift 4
#define FCB_CHMonitoringStart                    6      // 2 Bits, Bit 3-2
#define     FCB_CHMonitoringStartMask 0x0C
#define     FCB_CHMonitoringStartShift 2
#define FCB_CHMonitoringWDDpt1                   7      // 8 Bits, Bit 7-0
#define FCB_CHMonitoringWDDpt5                   7      // uint8_t
#define FCB_CHMonitoringWDDpt5001                7      // uint8_t
#define FCB_CHMonitoringWDDpt6                   7      // int8_t
#define FCB_CHMonitoringWDDpt7                   7      // uint16_t
#define FCB_CHMonitoringWDDpt8                   7      // int16_t
#define FCB_CHMonitoringWDDpt9                   7      // float
#define FCB_CHMonitoringWDDpt12                  7      // uint32_t
#define FCB_CHMonitoringWDDpt13                  7      // int32_t
#define FCB_CHMonitoringWDDpt14                  7      // float
#define FCB_CHMonitoringWDDpt16                  7      // char*, 14 Byte
#define     FCB_CHMonitoringWDDpt16Length 14
#define FCB_CHMonitoringMin                     22      // 4 Bits, Bit 7-4
#define     FCB_CHMonitoringMinMask 0xF0
#define     FCB_CHMonitoringMinShift 4
#define FCB_CHMonitoringMinDpt1                 23      // 1 Bit, Bit 7
#define     FCB_CHMonitoringMinDpt1Mask 0x80
#define     FCB_CHMonitoringMinDpt1Shift 7
#define FCB_CHMonitoringMinDpt5                 23      // uint8_t
#define FCB_CHMonitoringMinDpt5001              23      // uint8_t
#define FCB_CHMonitoringMinDpt6                 23      // int8_t
#define FCB_CHMonitoringMinDpt7                 23      // uint16_t
#define FCB_CHMonitoringMinDpt8                 23      // int16_t
#define FCB_CHMonitoringMinDpt9                 23      // float
#define FCB_CHMonitoringMinDpt12                23      // uint32_t
#define FCB_CHMonitoringMinDpt13                23      // int32_t
#define FCB_CHMonitoringMinDpt14                23      // float
#define FCB_CHMonitoringMax                     27      // 4 Bits, Bit 7-4
#define     FCB_CHMonitoringMaxMask 0xF0
#define     FCB_CHMonitoringMaxShift 4
#define FCB_CHMonitoringMaxDpt1                 28      // 1 Bit, Bit 7
#define     FCB_CHMonitoringMaxDpt1Mask 0x80
#define     FCB_CHMonitoringMaxDpt1Shift 7
#define FCB_CHMonitoringMaxDpt5                 28      // uint8_t
#define FCB_CHMonitoringMaxDpt5001              28      // uint8_t
#define FCB_CHMonitoringMaxDpt6                 28      // int8_t
#define FCB_CHMonitoringMaxDpt7                 28      // uint16_t
#define FCB_CHMonitoringMaxDpt8                 28      // int16_t
#define FCB_CHMonitoringMaxDpt9                 28      // float
#define FCB_CHMonitoringMaxDpt12                28      // uint32_t
#define FCB_CHMonitoringMaxDpt13                28      // int32_t
#define FCB_CHMonitoringMaxDpt14                28      // float
#define FCB_CHMonitoringOutput                  32      // 4 Bits, Bit 7-4
#define     FCB_CHMonitoringOutputMask 0xF0
#define     FCB_CHMonitoringOutputShift 4
#define FCB_CHSelectionValueType                 2      // 8 Bits, Bit 7-0
#define FCB_CHSelectionType                      3      // 8 Bits, Bit 7-0
#define FCB_CHSelectionSwitching                 4      // 4 Bits, Bit 7-4
#define     FCB_CHSelectionSwitchingMask 0xF0
#define     FCB_CHSelectionSwitchingShift 4
#define FCB_CHSelectionStateOutput               4      // 1 Bit, Bit 3
#define     FCB_CHSelectionStateOutputMask 0x08
#define     FCB_CHSelectionStateOutputShift 3
#define FCB_CHBlinkerOnDelayBase                 4      // 2 Bits, Bit 7-6
#define     FCB_CHBlinkerOnDelayBaseMask 0xC0
#define     FCB_CHBlinkerOnDelayBaseShift 6
#define FCB_CHBlinkerOnDelayTime                 4      // 14 Bits, Bit 13-0
#define     FCB_CHBlinkerOnDelayTimeMask 0x3FFF
#define     FCB_CHBlinkerOnDelayTimeShift 0
#define FCB_CHBlinkerOffDelayBase                6      // 2 Bits, Bit 7-6
#define     FCB_CHBlinkerOffDelayBaseMask 0xC0
#define     FCB_CHBlinkerOffDelayBaseShift 6
#define FCB_CHBlinkerOffDelayTime                6      // 14 Bits, Bit 13-0
#define     FCB_CHBlinkerOffDelayTimeMask 0x3FFF
#define     FCB_CHBlinkerOffDelayTimeShift 0
#define FCB_CHBlinkerStart                       8      // 4 Bits, Bit 7-4
#define     FCB_CHBlinkerStartMask 0xF0
#define     FCB_CHBlinkerStartShift 4
#define FCB_CHBlinkerStop                        8      // 4 Bits, Bit 3-0
#define     FCB_CHBlinkerStopMask 0x0F
#define     FCB_CHBlinkerStopShift 0
#define FCB_CHBlinkerBreak                       9      // 4 Bits, Bit 7-4
#define     FCB_CHBlinkerBreakMask 0xF0
#define     FCB_CHBlinkerBreakShift 4
#define FCB_CHBlinkerBreakWithoutBreak           9      // 4 Bits, Bit 7-4
#define     FCB_CHBlinkerBreakWithoutBreakMask 0xF0
#define     FCB_CHBlinkerBreakWithoutBreakShift 4
#define FCB_CHBlinkerOutputDpt                   9      // 8 Bits, Bit 3--4
#define FCB_CHBlinkerOnPercentage               10      // uint8_t
#define FCB_CHBlinkerOffPercentage              11      // uint8_t
#define FCB_CHBlinkerCount                      12      // 8 Bits, Bit 7-0
#define FCB_CHBlinkerStartAnzahl                13      // 1 Bit, Bit 7
#define     FCB_CHBlinkerStartAnzahlMask 0x80
#define     FCB_CHBlinkerStartAnzahlShift 7
#define FCB_CHFormatString                       2      // char*, 28 Byte
#define     FCB_CHFormatStringLength 28
#define FCB_CHFormatOff                         30      // char*, 14 Byte
#define     FCB_CHFormatOffLength 14
#define FCB_CHFormatOn                          44      // char*, 14 Byte
#define     FCB_CHFormatOnLength 14
#define FCB_CHFormatThousand                    58      // char*, 1 Byte
#define     FCB_CHFormatThousandLength 1
#define FCB_CHFormatIn1                         59      // 8 Bits, Bit 7-0
#define FCB_CHFormatRoundFloat1                 60      // 2 Bits, Bit 7-6
#define     FCB_CHFormatRoundFloat1Mask 0xC0
#define     FCB_CHFormatRoundFloat1Shift 6
#define FCB_CHFormatRound1                      60      // 2 Bits, Bit 7-6
#define     FCB_CHFormatRound1Mask 0xC0
#define     FCB_CHFormatRound1Shift 6
#define FCB_CHFCBFormatRound5_1                 60      // 1 Bit, Bit 5
#define     FCB_CHFCBFormatRound5_1Mask 0x20
#define     FCB_CHFCBFormatRound5_1Shift 5
#define FCB_CHFormatDecimalPlaces1              60      // 4 Bits, Bit 3-0
#define     FCB_CHFormatDecimalPlaces1Mask 0x0F
#define     FCB_CHFormatDecimalPlaces1Shift 0
#define FCB_CHFormatSignificant1                60      // 4 Bits, Bit 3-0
#define     FCB_CHFormatSignificant1Mask 0x0F
#define     FCB_CHFormatSignificant1Shift 0
#define FCB_CHFormatFillupPrecomma1             61      // 4 Bits, Bit 7-4
#define     FCB_CHFormatFillupPrecomma1Mask 0xF0
#define     FCB_CHFormatFillupPrecomma1Shift 4
#define FCB_CHFormatFillupMode1                 61      // 4 Bits, Bit 7-4
#define     FCB_CHFormatFillupMode1Mask 0xF0
#define     FCB_CHFormatFillupMode1Shift 4
#define FCB_CHFormatFillupAfterComma1           61      // 4 Bits, Bit 3-0
#define     FCB_CHFormatFillupAfterComma1Mask 0x0F
#define     FCB_CHFormatFillupAfterComma1Shift 0
#define FCB_CHFCBFormatRoundType1               62      // 4 Bits, Bit 7-4
#define     FCB_CHFCBFormatRoundType1Mask 0xF0
#define     FCB_CHFCBFormatRoundType1Shift 4
#define FCB_CHFormatFillupLength1               62      // 4 Bits, Bit 3-0
#define     FCB_CHFormatFillupLength1Mask 0x0F
#define     FCB_CHFormatFillupLength1Shift 0
#define FCB_CHFormatBit1                        60      // 8 Bits, Bit 7-0
#define FCB_CHFormatIn2                         63      // 8 Bits, Bit 7-0
#define FCB_CHFormatRoundFloat2                 64      // 2 Bits, Bit 7-6
#define     FCB_CHFormatRoundFloat2Mask 0xC0
#define     FCB_CHFormatRoundFloat2Shift 6
#define FCB_CHFormatRound2                      64      // 2 Bits, Bit 7-6
#define     FCB_CHFormatRound2Mask 0xC0
#define     FCB_CHFormatRound2Shift 6
#define FCB_CHFCBFormatRound5_2                 64      // 1 Bit, Bit 5
#define     FCB_CHFCBFormatRound5_2Mask 0x20
#define     FCB_CHFCBFormatRound5_2Shift 5
#define FCB_CHFormatDecimalPlaces2              64      // 4 Bits, Bit 3-0
#define     FCB_CHFormatDecimalPlaces2Mask 0x0F
#define     FCB_CHFormatDecimalPlaces2Shift 0
#define FCB_CHFormatSignificant2                64      // 4 Bits, Bit 3-0
#define     FCB_CHFormatSignificant2Mask 0x0F
#define     FCB_CHFormatSignificant2Shift 0
#define FCB_CHFormatFillupPrecomma2             65      // 4 Bits, Bit 7-4
#define     FCB_CHFormatFillupPrecomma2Mask 0xF0
#define     FCB_CHFormatFillupPrecomma2Shift 4
#define FCB_CHFormatFillupMode2                 65      // 4 Bits, Bit 7-4
#define     FCB_CHFormatFillupMode2Mask 0xF0
#define     FCB_CHFormatFillupMode2Shift 4
#define FCB_CHFormatFillupAfterComma2           65      // 4 Bits, Bit 3-0
#define     FCB_CHFormatFillupAfterComma2Mask 0x0F
#define     FCB_CHFormatFillupAfterComma2Shift 0
#define FCB_CHFCBFormatRoundType2               66      // 4 Bits, Bit 7-4
#define     FCB_CHFCBFormatRoundType2Mask 0xF0
#define     FCB_CHFCBFormatRoundType2Shift 4
#define FCB_CHFormatFillupLength2               66      // 4 Bits, Bit 3-0
#define     FCB_CHFormatFillupLength2Mask 0x0F
#define     FCB_CHFormatFillupLength2Shift 0
#define FCB_CHFormatBit2                        64      // 8 Bits, Bit 7-0
#define FCB_CHFormatIn3                         67      // 8 Bits, Bit 7-0
#define FCB_CHFormatRoundFloat3                 68      // 2 Bits, Bit 7-6
#define     FCB_CHFormatRoundFloat3Mask 0xC0
#define     FCB_CHFormatRoundFloat3Shift 6
#define FCB_CHFormatRound3                      68      // 2 Bits, Bit 7-6
#define     FCB_CHFormatRound3Mask 0xC0
#define     FCB_CHFormatRound3Shift 6
#define FCB_CHFCBFormatRound5_3                 68      // 1 Bit, Bit 5
#define     FCB_CHFCBFormatRound5_3Mask 0x20
#define     FCB_CHFCBFormatRound5_3Shift 5
#define FCB_CHFormatDecimalPlaces3              68      // 4 Bits, Bit 3-0
#define     FCB_CHFormatDecimalPlaces3Mask 0x0F
#define     FCB_CHFormatDecimalPlaces3Shift 0
#define FCB_CHFormatSignificant3                68      // 4 Bits, Bit 3-0
#define     FCB_CHFormatSignificant3Mask 0x0F
#define     FCB_CHFormatSignificant3Shift 0
#define FCB_CHFormatFillupPrecomma3             69      // 4 Bits, Bit 7-4
#define     FCB_CHFormatFillupPrecomma3Mask 0xF0
#define     FCB_CHFormatFillupPrecomma3Shift 4
#define FCB_CHFormatFillupMode3                 69      // 4 Bits, Bit 7-4
#define     FCB_CHFormatFillupMode3Mask 0xF0
#define     FCB_CHFormatFillupMode3Shift 4
#define FCB_CHFormatFillupAfterComma3           69      // 4 Bits, Bit 3-0
#define     FCB_CHFormatFillupAfterComma3Mask 0x0F
#define     FCB_CHFormatFillupAfterComma3Shift 0
#define FCB_CHFCBFormatRoundType3               70      // 4 Bits, Bit 7-4
#define     FCB_CHFCBFormatRoundType3Mask 0xF0
#define     FCB_CHFCBFormatRoundType3Shift 4
#define FCB_CHFormatFillupLength3               70      // 4 Bits, Bit 3-0
#define     FCB_CHFormatFillupLength3Mask 0x0F
#define     FCB_CHFormatFillupLength3Shift 0
#define FCB_CHFormatBit3                        68      // 8 Bits, Bit 7-0
#define FCB_CHFormatIn4                         71      // 8 Bits, Bit 7-0
#define FCB_CHFormatRoundFloat4                 72      // 2 Bits, Bit 7-6
#define     FCB_CHFormatRoundFloat4Mask 0xC0
#define     FCB_CHFormatRoundFloat4Shift 6
#define FCB_CHFormatRound4                      72      // 2 Bits, Bit 7-6
#define     FCB_CHFormatRound4Mask 0xC0
#define     FCB_CHFormatRound4Shift 6
#define FCB_CHFCBFormatRound5_4                 72      // 1 Bit, Bit 5
#define     FCB_CHFCBFormatRound5_4Mask 0x20
#define     FCB_CHFCBFormatRound5_4Shift 5
#define FCB_CHFormatDecimalPlaces4              72      // 4 Bits, Bit 3-0
#define     FCB_CHFormatDecimalPlaces4Mask 0x0F
#define     FCB_CHFormatDecimalPlaces4Shift 0
#define FCB_CHFormatSignificant4                72      // 4 Bits, Bit 3-0
#define     FCB_CHFormatSignificant4Mask 0x0F
#define     FCB_CHFormatSignificant4Shift 0
#define FCB_CHFormatFillupPrecomma4             73      // 4 Bits, Bit 7-4
#define     FCB_CHFormatFillupPrecomma4Mask 0xF0
#define     FCB_CHFormatFillupPrecomma4Shift 4
#define FCB_CHFormatFillupMode4                 73      // 4 Bits, Bit 7-4
#define     FCB_CHFormatFillupMode4Mask 0xF0
#define     FCB_CHFormatFillupMode4Shift 4
#define FCB_CHFormatFillupAfterComma4           73      // 4 Bits, Bit 3-0
#define     FCB_CHFormatFillupAfterComma4Mask 0x0F
#define     FCB_CHFormatFillupAfterComma4Shift 0
#define FCB_CHFCBFormatRoundType4               74      // 4 Bits, Bit 7-4
#define     FCB_CHFCBFormatRoundType4Mask 0xF0
#define     FCB_CHFCBFormatRoundType4Shift 4
#define FCB_CHFormatFillupLength4               74      // 4 Bits, Bit 3-0
#define     FCB_CHFormatFillupLength4Mask 0x0F
#define     FCB_CHFormatFillupLength4Shift 0
#define FCB_CHFormatBit4                        72      // 8 Bits, Bit 7-0

// Type
#define ParamFCB_CHChannelType                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHChannelType)))
// Kanal deaktivieren (zu Testzwecken)
#define ParamFCB_CHChannelDisabled                   ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHChannelDisabled)) & FCB_CHChannelDisabledMask))
// Eingang 1
#define ParamFCB_CHLogicKo0D                         ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo0D)) & FCB_CHLogicKo0DMask) >> FCB_CHLogicKo0DShift)
// Eingang 2
#define ParamFCB_CHLogicKo1D                         ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo1D)) & FCB_CHLogicKo1DMask) >> FCB_CHLogicKo1DShift)
// Eingang 3
#define ParamFCB_CHLogicKo2D                         ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo2D)) & FCB_CHLogicKo2DMask) >> FCB_CHLogicKo2DShift)
// Eingang 4
#define ParamFCB_CHLogicKo3D                         (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo3D)) & FCB_CHLogicKo3DMask)
// Eingang 5
#define ParamFCB_CHLogicKo4D                         ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo4D)) & FCB_CHLogicKo4DMask) >> FCB_CHLogicKo4DShift)
// Eingang 6
#define ParamFCB_CHLogicKo5D                         ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo5D)) & FCB_CHLogicKo5DMask) >> FCB_CHLogicKo5DShift)
// Eingang 7
#define ParamFCB_CHLogicKo6D                         ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo6D)) & FCB_CHLogicKo6DMask) >> FCB_CHLogicKo6DShift)
// Eingang 8
#define ParamFCB_CHLogicKo7D                         (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo7D)) & FCB_CHLogicKo7DMask)
// Eingang 9
#define ParamFCB_CHLogicKo8D                         ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo8D)) & FCB_CHLogicKo8DMask) >> FCB_CHLogicKo8DShift)
// Invertiert
#define ParamFCB_CHLogicOutInv                       ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicOutInv)) & FCB_CHLogicOutInvMask))
// Sendeverhalten
#define ParamFCB_CHLogicBehavOut                     ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavOut)) & FCB_CHLogicBehavOutMask))
// Initialisierung
#define ParamFCB_CHLogicBehavKo0                     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo0)) & FCB_CHLogicBehavKo0Mask) >> FCB_CHLogicBehavKo0Shift)
// Initialisierung
#define ParamFCB_CHLogicBehavKo1                     (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo1)) & FCB_CHLogicBehavKo1Mask)
// Initialisierung
#define ParamFCB_CHLogicBehavKo2                     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo2)) & FCB_CHLogicBehavKo2Mask) >> FCB_CHLogicBehavKo2Shift)
// Initialisierung
#define ParamFCB_CHLogicBehavKo3                     (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo3)) & FCB_CHLogicBehavKo3Mask)
// Initialisierung
#define ParamFCB_CHLogicBehavKo4                     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo4)) & FCB_CHLogicBehavKo4Mask) >> FCB_CHLogicBehavKo4Shift)
// Initialisierung
#define ParamFCB_CHLogicBehavKo5                     (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo5)) & FCB_CHLogicBehavKo5Mask)
// Initialisierung
#define ParamFCB_CHLogicBehavKo6                     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo6)) & FCB_CHLogicBehavKo6Mask) >> FCB_CHLogicBehavKo6Shift)
// Initialisierung
#define ParamFCB_CHLogicBehavKo7                     (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo7)) & FCB_CHLogicBehavKo7Mask)
// Initialisierung
#define ParamFCB_CHLogicBehavKo8                     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo8)) & FCB_CHLogicBehavKo8Mask) >> FCB_CHLogicBehavKo8Shift)
// Prior-Wahrscheinlichkeit
#define ParamFCB_CHBayesianPrior                     (knx.paramByte(FCB_ParamCalcIndex(FCB_CHBayesianPrior)))
// Schwellwert für binären Ausgang
#define ParamFCB_CHBayesianThreshold                 (knx.paramByte(FCB_ParamCalcIndex(FCB_CHBayesianThreshold)))
// Wahrscheinlichkeits-Ausgang aktivieren
#define ParamFCB_CHBayesianEnableProbOutput          ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHBayesianEnableProbOutput)) & FCB_CHBayesianEnableProbOutputMask))
// P(A|E_1)
#define ParamFCB_CHLogicKo0BayesProbTrue             (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo0BayesProbTrue)))
// P(A|!E_1)
#define ParamFCB_CHLogicKo0BayesProbFalse            (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo0BayesProbFalse)))
// P(A|E_2)
#define ParamFCB_CHLogicKo1BayesProbTrue             (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo1BayesProbTrue)))
// P(A|!E_2)
#define ParamFCB_CHLogicKo1BayesProbFalse            (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo1BayesProbFalse)))
// P(A|E_3)
#define ParamFCB_CHLogicKo2BayesProbTrue             (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo2BayesProbTrue)))
// P(A|!E_3)
#define ParamFCB_CHLogicKo2BayesProbFalse            (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo2BayesProbFalse)))
// P(A|E_4)
#define ParamFCB_CHLogicKo3BayesProbTrue             (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo3BayesProbTrue)))
// P(A|!E_4)
#define ParamFCB_CHLogicKo3BayesProbFalse            (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo3BayesProbFalse)))
// P(A|E_5)
#define ParamFCB_CHLogicKo4BayesProbTrue             (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo4BayesProbTrue)))
// P(A|!E_5)
#define ParamFCB_CHLogicKo4BayesProbFalse            (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo4BayesProbFalse)))
// P(A|E_6)
#define ParamFCB_CHLogicKo5BayesProbTrue             (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo5BayesProbTrue)))
// P(A|!E_6)
#define ParamFCB_CHLogicKo5BayesProbFalse            (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo5BayesProbFalse)))
// P(A|E_7)
#define ParamFCB_CHLogicKo6BayesProbTrue             (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo6BayesProbTrue)))
// P(A|!E_7)
#define ParamFCB_CHLogicKo6BayesProbFalse            (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo6BayesProbFalse)))
// P(A|E_8)
#define ParamFCB_CHLogicKo7BayesProbTrue             (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo7BayesProbTrue)))
// P(A|!E_8)
#define ParamFCB_CHLogicKo7BayesProbFalse            (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo7BayesProbFalse)))
// P(A|E_9)
#define ParamFCB_CHLogicKo8BayesProbTrue             (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo8BayesProbTrue)))
// P(A|!E_9)
#define ParamFCB_CHLogicKo8BayesProbFalse            (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo8BayesProbFalse)))
// Eingang 1
#define ParamFCB_CHPrioKo0D                          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo0D)) & FCB_CHPrioKo0DMask) >> FCB_CHPrioKo0DShift)
// Eingang 2
#define ParamFCB_CHPrioKo1D                          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo1D)) & FCB_CHPrioKo1DMask) >> FCB_CHPrioKo1DShift)
// Eingang 3
#define ParamFCB_CHPrioKo2D                          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo2D)) & FCB_CHPrioKo2DMask) >> FCB_CHPrioKo2DShift)
// Eingang 4
#define ParamFCB_CHPrioKo3D                          (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo3D)) & FCB_CHPrioKo3DMask)
// Eingang 5
#define ParamFCB_CHPrioKo4D                          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo4D)) & FCB_CHPrioKo4DMask) >> FCB_CHPrioKo4DShift)
// Eingang 6
#define ParamFCB_CHPrioKo5D                          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo5D)) & FCB_CHPrioKo5DMask) >> FCB_CHPrioKo5DShift)
// Eingang 7
#define ParamFCB_CHPrioKo6D                          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo6D)) & FCB_CHPrioKo6DMask) >> FCB_CHPrioKo6DShift)
// Eingang 8
#define ParamFCB_CHPrioKo7D                          (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo7D)) & FCB_CHPrioKo7DMask)
// Eingang 9
#define ParamFCB_CHPrioKo8D                          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo8D)) & FCB_CHPrioKo8DMask) >> FCB_CHPrioKo8DShift)
// Type
#define ParamFCB_CHPrioOutputType                    ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutputType)) & FCB_CHPrioOutputTypeMask) >> FCB_CHPrioOutputTypeShift)
// Ausgangswert
#define ParamFCB_CHPrioOutPKo0                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo0)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo0                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo0)))
// Ausgangswert Szenennummer
#define ParamFCB_CHPrioOutSceneKo0                   (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutSceneKo0)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo1                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo1)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo1                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo1)))
// Ausgangswert Szenennummer
#define ParamFCB_CHPrioOutSceneKo1                   (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutSceneKo1)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo2                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo2)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo2                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo2)))
// Ausgangswert Szenennummer
#define ParamFCB_CHPrioOutSceneKo2                   (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutSceneKo2)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo3                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo3)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo3                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo3)))
// Ausgangswert Szenennummer
#define ParamFCB_CHPrioOutSceneKo3                   (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutSceneKo3)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo4                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo4)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo4                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo4)))
// Ausgangswert Szenennummer
#define ParamFCB_CHPrioOutSceneKo4                   (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutSceneKo4)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo5                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo5)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo5                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo5)))
// Ausgangswert Szenennummer
#define ParamFCB_CHPrioOutSceneKo5                   (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutSceneKo5)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo6                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo6)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo6                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo6)))
// Ausgangswert Szenennummer
#define ParamFCB_CHPrioOutSceneKo6                   (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutSceneKo6)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo7                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo7)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo7                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo7)))
// Ausgangswert Szenennummer
#define ParamFCB_CHPrioOutSceneKo7                   (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutSceneKo7)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo8                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo8)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo8                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo8)))
// Ausgangswert Szenennummer
#define ParamFCB_CHPrioOutSceneKo8                   (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutSceneKo8)))
// Ausgangswert wenn alle Eingänge AUS
#define ParamFCB_CHPrioOutPDefault                   (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPDefault)))
// Ausgangswert wenn alle Eingänge AUS
#define ParamFCB_CHPrioOutByteDefault                (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteDefault)))
// Ausgangswert Szenennummer wenn alle Eingänge AUS
#define ParamFCB_CHPrioOutSceneDefault               (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutSceneDefault)))
// Initialisierung
#define ParamFCB_CHPrioBehavKo0                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo0)) & FCB_CHPrioBehavKo0Mask) >> FCB_CHPrioBehavKo0Shift)
// Initialisierung
#define ParamFCB_CHPrioBehavKo1                      (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo1)) & FCB_CHPrioBehavKo1Mask)
// Initialisierung
#define ParamFCB_CHPrioBehavKo2                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo2)) & FCB_CHPrioBehavKo2Mask) >> FCB_CHPrioBehavKo2Shift)
// Initialisierung
#define ParamFCB_CHPrioBehavKo3                      (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo3)) & FCB_CHPrioBehavKo3Mask)
// Initialisierung
#define ParamFCB_CHPrioBehavKo4                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo4)) & FCB_CHPrioBehavKo4Mask) >> FCB_CHPrioBehavKo4Shift)
// Initialisierung
#define ParamFCB_CHPrioBehavKo5                      (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo5)) & FCB_CHPrioBehavKo5Mask)
// Initialisierung
#define ParamFCB_CHPrioBehavKo6                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo6)) & FCB_CHPrioBehavKo6Mask) >> FCB_CHPrioBehavKo6Shift)
// Initialisierung
#define ParamFCB_CHPrioBehavKo7                      (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo7)) & FCB_CHPrioBehavKo7Mask)
// Initialisierung
#define ParamFCB_CHPrioBehavKo8                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo8)) & FCB_CHPrioBehavKo8Mask) >> FCB_CHPrioBehavKo8Shift)
// Sendeverhalten
#define ParamFCB_CHPrioBehavOut                      ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavOut)) & FCB_CHPrioBehavOutMask))
// Gewichtung der Eingänge
#define ParamFCB_CHAggWeight                         ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggWeight)) & FCB_CHAggWeightMask))
// Funktion
#define ParamFCB_CHAggType                           (knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggType)) & FCB_CHAggTypeMask)
// Eingang 1
#define ParamFCB_CHAggKo0D                           ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo0D)) & FCB_CHAggKo0DMask) >> FCB_CHAggKo0DShift)
// Eingang 2
#define ParamFCB_CHAggKo1D                           ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo1D)) & FCB_CHAggKo1DMask) >> FCB_CHAggKo1DShift)
// Eingang 3
#define ParamFCB_CHAggKo2D                           ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo2D)) & FCB_CHAggKo2DMask) >> FCB_CHAggKo2DShift)
// Eingang 4
#define ParamFCB_CHAggKo3D                           (knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo3D)) & FCB_CHAggKo3DMask)
// Eingang 5
#define ParamFCB_CHAggKo4D                           ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo4D)) & FCB_CHAggKo4DMask) >> FCB_CHAggKo4DShift)
// Eingang 6
#define ParamFCB_CHAggKo5D                           ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo5D)) & FCB_CHAggKo5DMask) >> FCB_CHAggKo5DShift)
// Eingang 7
#define ParamFCB_CHAggKo6D                           ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo6D)) & FCB_CHAggKo6DMask) >> FCB_CHAggKo6DShift)
// Eingang 8
#define ParamFCB_CHAggKo7D                           (knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo7D)) & FCB_CHAggKo7DMask)
// Eingang 9
#define ParamFCB_CHAggKo8D                           ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo8D)) & FCB_CHAggKo8DMask) >> FCB_CHAggKo8DShift)
// Sendeverhalten
#define ParamFCB_CHAggBehavOut                       ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggBehavOut)) & FCB_CHAggBehavOutMask))
// Rundungsmodus
#define ParamFCB_CHAggOutputRounding                 ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggOutputRounding)) & FCB_CHAggOutputRoundingMask))
// Bei Überschreiten des Wertebereichs
#define ParamFCB_CHAggOutputOverflow                 ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggOutputOverflow)) & FCB_CHAggOutputOverflowMask) >> FCB_CHAggOutputOverflowShift)
// Wertetype / DPT
#define ParamFCB_CHAggInputDpt                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggInputDpt)))
// DPT Ausgang
#define ParamFCB_CHAggOutputDptEff                   (knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggOutputDptEff)))
// Gewicht Eingang 1
#define ParamFCB_CHAggKo0W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo0W)))
// Gewicht Eingang 2
#define ParamFCB_CHAggKo1W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo1W)))
// Gewicht Eingang 3
#define ParamFCB_CHAggKo2W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo2W)))
// Gewicht Eingang 4
#define ParamFCB_CHAggKo3W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo3W)))
// Gewicht Eingang 5
#define ParamFCB_CHAggKo4W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo4W)))
// Gewicht Eingang 6
#define ParamFCB_CHAggKo5W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo5W)))
// Gewicht Eingang 7
#define ParamFCB_CHAggKo6W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo6W)))
// Gewicht Eingang 8
#define ParamFCB_CHAggKo7W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo7W)))
// Gewicht Eingang 9
#define ParamFCB_CHAggKo8W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo8W)))
// Start mit Zeit
#define ParamFCB_CHCountDownTimeStartKo              ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHCountDownTimeStartKo)) & FCB_CHCountDownTimeStartKoMask) >> FCB_CHCountDownTimeStartKoShift)
// Ablaufzeit Einheit
#define ParamFCB_CHCountDownDelayBase                ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHCountDownDelayBase)) & FCB_CHCountDownDelayBaseMask) >> FCB_CHCountDownDelayBaseShift)
// Ablaufzeit
#define ParamFCB_CHCountDownDelayTime                (knx.paramWord(FCB_ParamCalcIndex(FCB_CHCountDownDelayTime)) & FCB_CHCountDownDelayTimeMask)
// Ablaufzeit (in Millisekunden)
#define ParamFCB_CHCountDownDelayTimeMS              (paramDelay(knx.paramWord(FCB_ParamCalcIndex(FCB_CHCountDownDelayTime))))
// Laufzeit Verringern / Erhöhen
#define ParamFCB_CHCountDownTimeOffset               ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHCountDownTimeOffset)) & FCB_CHCountDownTimeOffsetMask) >> FCB_CHCountDownTimeOffsetShift)
// Auslöser / Ende
#define ParamFCB_CHCountDownTrigger                  (knx.paramByte(FCB_ParamCalcIndex(FCB_CHCountDownTrigger)) & FCB_CHCountDownTriggerMask)
// Standard
#define ParamFCB_CHCountDownTemplate                 (knx.paramData(FCB_ParamCalcIndex(FCB_CHCountDownTemplate)))
#define ParamFCB_CHCountDownTemplateStr              (knx.paramString(FCB_ParamCalcIndex(FCB_CHCountDownTemplate), FCB_CHCountDownTemplateLength))
// kleiner eine Stunde
#define ParamFCB_CHCountDownTemplate1h               (knx.paramData(FCB_ParamCalcIndex(FCB_CHCountDownTemplate1h)))
#define ParamFCB_CHCountDownTemplate1hStr            (knx.paramString(FCB_ParamCalcIndex(FCB_CHCountDownTemplate1h), FCB_CHCountDownTemplate1hLength))
// kleiner eine Minute
#define ParamFCB_CHCountDownTemplate1m               (knx.paramData(FCB_ParamCalcIndex(FCB_CHCountDownTemplate1m)))
#define ParamFCB_CHCountDownTemplate1mStr            (knx.paramString(FCB_ParamCalcIndex(FCB_CHCountDownTemplate1m), FCB_CHCountDownTemplate1mLength))
// Ende
#define ParamFCB_CHCountDownTemplateEnd              (knx.paramData(FCB_ParamCalcIndex(FCB_CHCountDownTemplateEnd)))
#define ParamFCB_CHCountDownTemplateEndStr           (knx.paramString(FCB_ParamCalcIndex(FCB_CHCountDownTemplateEnd), FCB_CHCountDownTemplateEndLength))
// Pause
#define ParamFCB_CHCountDownTextPause                (knx.paramData(FCB_ParamCalcIndex(FCB_CHCountDownTextPause)))
#define ParamFCB_CHCountDownTextPauseStr             (knx.paramString(FCB_ParamCalcIndex(FCB_CHCountDownTextPause), FCB_CHCountDownTextPauseLength))
// Läuft
#define ParamFCB_CHCountDownTextRun                  (knx.paramData(FCB_ParamCalcIndex(FCB_CHCountDownTextRun)))
#define ParamFCB_CHCountDownTextRunStr               (knx.paramString(FCB_ParamCalcIndex(FCB_CHCountDownTextRun), FCB_CHCountDownTextRunLength))
// Zähler
#define ParamFCB_CHCountDownCounterKo                ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHCountDownCounterKo)) & FCB_CHCountDownCounterKoMask) >> FCB_CHCountDownCounterKoShift)
// Text
#define ParamFCB_CHCountDownTextKo                   ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHCountDownTextKo)) & FCB_CHCountDownTextKoMask) >> FCB_CHCountDownTextKoShift)
// Stopp
#define ParamFCB_CHCountDownTemplateStopp            (knx.paramData(FCB_ParamCalcIndex(FCB_CHCountDownTemplateStopp)))
#define ParamFCB_CHCountDownTemplateStoppStr         (knx.paramString(FCB_ParamCalcIndex(FCB_CHCountDownTemplateStopp), FCB_CHCountDownTemplateStoppLength))
// Maximalzeit Einheit
#define ParamFCB_CHCountDownMaxDelayBase             ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHCountDownMaxDelayBase)) & FCB_CHCountDownMaxDelayBaseMask) >> FCB_CHCountDownMaxDelayBaseShift)
// Maximalzeit
#define ParamFCB_CHCountDownMaxDelayTime             (knx.paramWord(FCB_ParamCalcIndex(FCB_CHCountDownMaxDelayTime)) & FCB_CHCountDownMaxDelayTimeMask)
// Maximalzeit (in Millisekunden)
#define ParamFCB_CHCountDownMaxDelayTimeMS           (paramDelay(knx.paramWord(FCB_ParamCalcIndex(FCB_CHCountDownMaxDelayTime))))
// Werttype
#define ParamFCB_CHMonitoringValueType               (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringValueType)))
// Zeitüberwachung aktiv
#define ParamFCB_CHMonitoringWDEnabled               ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringWDEnabled)) & FCB_CHMonitoringWDEnabledMask))
// Watchdog Zeitbasis
#define ParamFCB_CHMonitoringWDTTimeoutDelayBase     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringWDTTimeoutDelayBase)) & FCB_CHMonitoringWDTTimeoutDelayBaseMask) >> FCB_CHMonitoringWDTTimeoutDelayBaseShift)
// Watchdog Zeit
#define ParamFCB_CHMonitoringWDTTimeoutDelayTime     (knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringWDTTimeoutDelayTime)) & FCB_CHMonitoringWDTTimeoutDelayTimeMask)
// Watchdog Zeit (in Millisekunden)
#define ParamFCB_CHMonitoringWDTTimeoutDelayTimeMS   (paramDelay(knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringWDTTimeoutDelayTime))))
// Verhalten bei Zeitüberschreitung
#define ParamFCB_CHMonitoringWDBehavior              ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringWDBehavior)) & FCB_CHMonitoringWDBehaviorMask) >> FCB_CHMonitoringWDBehaviorShift)
// Verhalten beim Start
#define ParamFCB_CHMonitoringStart                   ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringStart)) & FCB_CHMonitoringStartMask) >> FCB_CHMonitoringStartShift)
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt1                  (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt1)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt5                  (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt5)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt5001               (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt5001)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt6                  ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt6)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt7                  (knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt7)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt8                  ((int16_t)knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt8)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt9                  (knx.paramFloat(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt9), Float_Enc_IEEE754Single))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt12                 (knx.paramInt(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt12)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt13                 ((int32_t)knx.paramInt(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt13)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt14                 (knx.paramFloat(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt14), Float_Enc_IEEE754Single))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt16                 (knx.paramData(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt16)))
#define ParamFCB_CHMonitoringWDDpt16Str              (knx.paramString(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt16), FCB_CHMonitoringWDDpt16Length))
// Verhalten bei Wertunterschreitung
#define ParamFCB_CHMonitoringMin                     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMin)) & FCB_CHMonitoringMinMask) >> FCB_CHMonitoringMinShift)
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt1                 ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt1)) & FCB_CHMonitoringMinDpt1Mask))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt5                 (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt5)))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt5001              (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt5001)))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt6                 ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt6)))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt7                 (knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt7)))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt8                 ((int16_t)knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt8)))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt9                 (knx.paramFloat(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt9), Float_Enc_IEEE754Single))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt12                (knx.paramInt(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt12)))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt13                ((int32_t)knx.paramInt(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt13)))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt14                (knx.paramFloat(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt14), Float_Enc_IEEE754Single))
// Verhalten bei Wertüberschreitung
#define ParamFCB_CHMonitoringMax                     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMax)) & FCB_CHMonitoringMaxMask) >> FCB_CHMonitoringMaxShift)
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt1                 ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt1)) & FCB_CHMonitoringMaxDpt1Mask))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt5                 (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt5)))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt5001              (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt5001)))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt6                 ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt6)))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt7                 (knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt7)))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt8                 ((int16_t)knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt8)))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt9                 (knx.paramFloat(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt9), Float_Enc_IEEE754Single))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt12                (knx.paramInt(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt12)))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt13                ((int32_t)knx.paramInt(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt13)))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt14                (knx.paramFloat(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt14), Float_Enc_IEEE754Single))
// Sendeverhalten
#define ParamFCB_CHMonitoringOutput                  ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringOutput)) & FCB_CHMonitoringOutputMask) >> FCB_CHMonitoringOutputShift)
// Datentype
#define ParamFCB_CHSelectionValueType                (knx.paramByte(FCB_ParamCalcIndex(FCB_CHSelectionValueType)))
// Anzahl und Typ der Auswahlen (mit gemeinsamen Auswahl-Eingang)
#define ParamFCB_CHSelectionType                     (knx.paramByte(FCB_ParamCalcIndex(FCB_CHSelectionType)))
// Bei Umschaltung
#define ParamFCB_CHSelectionSwitching                ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHSelectionSwitching)) & FCB_CHSelectionSwitchingMask) >> FCB_CHSelectionSwitchingShift)
// Auswahl Status Objekt
#define ParamFCB_CHSelectionStateOutput              ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHSelectionStateOutput)) & FCB_CHSelectionStateOutputMask))
// Blinker EIN Zeitbasis
#define ParamFCB_CHBlinkerOnDelayBase                ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerOnDelayBase)) & FCB_CHBlinkerOnDelayBaseMask) >> FCB_CHBlinkerOnDelayBaseShift)
// Blinker EIN Zeit
#define ParamFCB_CHBlinkerOnDelayTime                (knx.paramWord(FCB_ParamCalcIndex(FCB_CHBlinkerOnDelayTime)) & FCB_CHBlinkerOnDelayTimeMask)
// Blinker EIN Zeit (in Millisekunden)
#define ParamFCB_CHBlinkerOnDelayTimeMS              (paramDelay(knx.paramWord(FCB_ParamCalcIndex(FCB_CHBlinkerOnDelayTime))))
// Blinker AUS Zeitbasis
#define ParamFCB_CHBlinkerOffDelayBase               ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerOffDelayBase)) & FCB_CHBlinkerOffDelayBaseMask) >> FCB_CHBlinkerOffDelayBaseShift)
// Blinker AUS Zeit
#define ParamFCB_CHBlinkerOffDelayTime               (knx.paramWord(FCB_ParamCalcIndex(FCB_CHBlinkerOffDelayTime)) & FCB_CHBlinkerOffDelayTimeMask)
// Blinker AUS Zeit (in Millisekunden)
#define ParamFCB_CHBlinkerOffDelayTimeMS             (paramDelay(knx.paramWord(FCB_ParamCalcIndex(FCB_CHBlinkerOffDelayTime))))
// Start
#define ParamFCB_CHBlinkerStart                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerStart)) & FCB_CHBlinkerStartMask) >> FCB_CHBlinkerStartShift)
// Ende
#define ParamFCB_CHBlinkerStop                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerStop)) & FCB_CHBlinkerStopMask)
// AUS Telegram am 'Start' Eingang
#define ParamFCB_CHBlinkerBreak                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerBreak)) & FCB_CHBlinkerBreakMask) >> FCB_CHBlinkerBreakShift)
// AUS Telegram am 'Start' Eingang
#define ParamFCB_CHBlinkerBreakWithoutBreak          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerBreakWithoutBreak)) & FCB_CHBlinkerBreakWithoutBreakMask) >> FCB_CHBlinkerBreakWithoutBreakShift)
// Ausgang
#define ParamFCB_CHBlinkerOutputDpt                  (knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerOutputDpt)))
// Wert für EIN
#define ParamFCB_CHBlinkerOnPercentage               (knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerOnPercentage)))
// Wert für AUS
#define ParamFCB_CHBlinkerOffPercentage              (knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerOffPercentage)))
// Anzahl der Blinkvorgänge
#define ParamFCB_CHBlinkerCount                      (knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerCount)))
// Objekt zum Starten mit Anzahl
#define ParamFCB_CHBlinkerStartAnzahl                ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerStartAnzahl)) & FCB_CHBlinkerStartAnzahlMask))
// Format
#define ParamFCB_CHFormatString                      (knx.paramData(FCB_ParamCalcIndex(FCB_CHFormatString)))
#define ParamFCB_CHFormatStringStr                   (knx.paramString(FCB_ParamCalcIndex(FCB_CHFormatString), FCB_CHFormatStringLength))
// Textbaustein Aus
#define ParamFCB_CHFormatOff                         (knx.paramData(FCB_ParamCalcIndex(FCB_CHFormatOff)))
#define ParamFCB_CHFormatOffStr                      (knx.paramString(FCB_ParamCalcIndex(FCB_CHFormatOff), FCB_CHFormatOffLength))
// Textbaustein Ein
#define ParamFCB_CHFormatOn                          (knx.paramData(FCB_ParamCalcIndex(FCB_CHFormatOn)))
#define ParamFCB_CHFormatOnStr                       (knx.paramString(FCB_ParamCalcIndex(FCB_CHFormatOn), FCB_CHFormatOnLength))
// Tausendertrennzeichen
#define ParamFCB_CHFormatThousand                    (knx.paramData(FCB_ParamCalcIndex(FCB_CHFormatThousand)))
#define ParamFCB_CHFormatThousandStr                 (knx.paramString(FCB_ParamCalcIndex(FCB_CHFormatThousand), FCB_CHFormatThousandLength))
// Datentype
#define ParamFCB_CHFormatIn1                         (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatIn1)))
// Runden
#define ParamFCB_CHFormatRoundFloat1                 ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatRoundFloat1)) & FCB_CHFormatRoundFloat1Mask) >> FCB_CHFormatRoundFloat1Shift)
// Runden
#define ParamFCB_CHFormatRound1                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatRound1)) & FCB_CHFormatRound1Mask) >> FCB_CHFormatRound1Shift)
// Auf 5 Runden
#define ParamFCB_CHFCBFormatRound5_1                 ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHFCBFormatRound5_1)) & FCB_CHFCBFormatRound5_1Mask))
// Stellen
#define ParamFCB_CHFormatDecimalPlaces1              (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatDecimalPlaces1)) & FCB_CHFormatDecimalPlaces1Mask)
// Stellenanzahl
#define ParamFCB_CHFormatSignificant1                (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatSignificant1)) & FCB_CHFormatSignificant1Mask)
// Auffüllen
#define ParamFCB_CHFormatFillupPrecomma1             ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupPrecomma1)) & FCB_CHFormatFillupPrecomma1Mask) >> FCB_CHFormatFillupPrecomma1Shift)
// Auffüllen
#define ParamFCB_CHFormatFillupMode1                 ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupMode1)) & FCB_CHFormatFillupMode1Mask) >> FCB_CHFormatFillupMode1Shift)
// Auffüllen nach Komma
#define ParamFCB_CHFormatFillupAfterComma1           (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupAfterComma1)) & FCB_CHFormatFillupAfterComma1Mask)
// Rundungsart
#define ParamFCB_CHFCBFormatRoundType1               ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFCBFormatRoundType1)) & FCB_CHFCBFormatRoundType1Mask) >> FCB_CHFCBFormatRoundType1Shift)
// Stellen
#define ParamFCB_CHFormatFillupLength1               (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupLength1)) & FCB_CHFormatFillupLength1Mask)
// Anzeige als
#define ParamFCB_CHFormatBit1                        (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatBit1)))
// Datentype
#define ParamFCB_CHFormatIn2                         (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatIn2)))
// Runden
#define ParamFCB_CHFormatRoundFloat2                 ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatRoundFloat2)) & FCB_CHFormatRoundFloat2Mask) >> FCB_CHFormatRoundFloat2Shift)
// Runden
#define ParamFCB_CHFormatRound2                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatRound2)) & FCB_CHFormatRound2Mask) >> FCB_CHFormatRound2Shift)
// Auf 5 Runden
#define ParamFCB_CHFCBFormatRound5_2                 ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHFCBFormatRound5_2)) & FCB_CHFCBFormatRound5_2Mask))
// Stellen
#define ParamFCB_CHFormatDecimalPlaces2              (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatDecimalPlaces2)) & FCB_CHFormatDecimalPlaces2Mask)
// Stellenanzahl
#define ParamFCB_CHFormatSignificant2                (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatSignificant2)) & FCB_CHFormatSignificant2Mask)
// Auffüllen
#define ParamFCB_CHFormatFillupPrecomma2             ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupPrecomma2)) & FCB_CHFormatFillupPrecomma2Mask) >> FCB_CHFormatFillupPrecomma2Shift)
// Auffüllen
#define ParamFCB_CHFormatFillupMode2                 ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupMode2)) & FCB_CHFormatFillupMode2Mask) >> FCB_CHFormatFillupMode2Shift)
// Auffüllen nach Komma
#define ParamFCB_CHFormatFillupAfterComma2           (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupAfterComma2)) & FCB_CHFormatFillupAfterComma2Mask)
// Rundungsart
#define ParamFCB_CHFCBFormatRoundType2               ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFCBFormatRoundType2)) & FCB_CHFCBFormatRoundType2Mask) >> FCB_CHFCBFormatRoundType2Shift)
// Stellen
#define ParamFCB_CHFormatFillupLength2               (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupLength2)) & FCB_CHFormatFillupLength2Mask)
// Anzeige als
#define ParamFCB_CHFormatBit2                        (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatBit2)))
// Datentype
#define ParamFCB_CHFormatIn3                         (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatIn3)))
// Runden
#define ParamFCB_CHFormatRoundFloat3                 ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatRoundFloat3)) & FCB_CHFormatRoundFloat3Mask) >> FCB_CHFormatRoundFloat3Shift)
// Runden
#define ParamFCB_CHFormatRound3                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatRound3)) & FCB_CHFormatRound3Mask) >> FCB_CHFormatRound3Shift)
// Auf 5 Runden
#define ParamFCB_CHFCBFormatRound5_3                 ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHFCBFormatRound5_3)) & FCB_CHFCBFormatRound5_3Mask))
// Stellen
#define ParamFCB_CHFormatDecimalPlaces3              (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatDecimalPlaces3)) & FCB_CHFormatDecimalPlaces3Mask)
// Stellenanzahl
#define ParamFCB_CHFormatSignificant3                (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatSignificant3)) & FCB_CHFormatSignificant3Mask)
// Auffüllen
#define ParamFCB_CHFormatFillupPrecomma3             ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupPrecomma3)) & FCB_CHFormatFillupPrecomma3Mask) >> FCB_CHFormatFillupPrecomma3Shift)
// Auffüllen
#define ParamFCB_CHFormatFillupMode3                 ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupMode3)) & FCB_CHFormatFillupMode3Mask) >> FCB_CHFormatFillupMode3Shift)
// Auffüllen nach Komma
#define ParamFCB_CHFormatFillupAfterComma3           (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupAfterComma3)) & FCB_CHFormatFillupAfterComma3Mask)
// Rundungsart
#define ParamFCB_CHFCBFormatRoundType3               ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFCBFormatRoundType3)) & FCB_CHFCBFormatRoundType3Mask) >> FCB_CHFCBFormatRoundType3Shift)
// Stellen
#define ParamFCB_CHFormatFillupLength3               (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupLength3)) & FCB_CHFormatFillupLength3Mask)
// Anzeige als
#define ParamFCB_CHFormatBit3                        (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatBit3)))
// Datentype
#define ParamFCB_CHFormatIn4                         (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatIn4)))
// Runden
#define ParamFCB_CHFormatRoundFloat4                 ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatRoundFloat4)) & FCB_CHFormatRoundFloat4Mask) >> FCB_CHFormatRoundFloat4Shift)
// Runden
#define ParamFCB_CHFormatRound4                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatRound4)) & FCB_CHFormatRound4Mask) >> FCB_CHFormatRound4Shift)
// Auf 5 Runden
#define ParamFCB_CHFCBFormatRound5_4                 ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHFCBFormatRound5_4)) & FCB_CHFCBFormatRound5_4Mask))
// Stellen
#define ParamFCB_CHFormatDecimalPlaces4              (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatDecimalPlaces4)) & FCB_CHFormatDecimalPlaces4Mask)
// Stellenanzahl
#define ParamFCB_CHFormatSignificant4                (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatSignificant4)) & FCB_CHFormatSignificant4Mask)
// Auffüllen
#define ParamFCB_CHFormatFillupPrecomma4             ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupPrecomma4)) & FCB_CHFormatFillupPrecomma4Mask) >> FCB_CHFormatFillupPrecomma4Shift)
// Auffüllen
#define ParamFCB_CHFormatFillupMode4                 ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupMode4)) & FCB_CHFormatFillupMode4Mask) >> FCB_CHFormatFillupMode4Shift)
// Auffüllen nach Komma
#define ParamFCB_CHFormatFillupAfterComma4           (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupAfterComma4)) & FCB_CHFormatFillupAfterComma4Mask)
// Rundungsart
#define ParamFCB_CHFCBFormatRoundType4               ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHFCBFormatRoundType4)) & FCB_CHFCBFormatRoundType4Mask) >> FCB_CHFCBFormatRoundType4Shift)
// Stellen
#define ParamFCB_CHFormatFillupLength4               (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatFillupLength4)) & FCB_CHFormatFillupLength4Mask)
// Anzeige als
#define ParamFCB_CHFormatBit4                        (knx.paramByte(FCB_ParamCalcIndex(FCB_CHFormatBit4)))

// deprecated
#define FCB_KoOffset 250

// Communication objects per channel (multiple occurrence)
#define FCB_KoBlockOffset 250
#define FCB_KoBlockSize 10

#define FCB_KoCalcNumber(index) (index + FCB_KoBlockOffset + _channelIndex * FCB_KoBlockSize)
#define FCB_KoCalcIndex(number) ((number >= FCB_KoCalcNumber(0) && number < FCB_KoCalcNumber(FCB_KoBlockSize)) ? (number - FCB_KoBlockOffset) % FCB_KoBlockSize : -1)
#define FCB_KoCalcChannel(number) ((number >= FCB_KoBlockOffset && number < FCB_KoBlockOffset + FCB_ChannelCount * FCB_KoBlockSize) ? (number - FCB_KoBlockOffset) / FCB_KoBlockSize : -1)

#define FCB_KoCHKO0 0
#define FCB_KoCHKO1 1
#define FCB_KoCHKO2 2
#define FCB_KoCHKO3 3
#define FCB_KoCHKO4 4
#define FCB_KoCHKO5 5
#define FCB_KoCHKO6 6
#define FCB_KoCHKO7 7
#define FCB_KoCHKO8 8
#define FCB_KoCHKO9 9

// 
#define KoFCB_CHKO0                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO0)))
// 
#define KoFCB_CHKO1                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO1)))
// 
#define KoFCB_CHKO2                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO2)))
// 
#define KoFCB_CHKO3                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO3)))
// 
#define KoFCB_CHKO4                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO4)))
// 
#define KoFCB_CHKO5                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO5)))
// 
#define KoFCB_CHKO6                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO6)))
// 
#define KoFCB_CHKO7                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO7)))
// 
#define KoFCB_CHKO8                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO8)))
// 
#define KoFCB_CHKO9                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO9)))



// Header generation for Module 'BASE_KommentarModule'

#define BASE_KommentarModuleCount 0
#define BASE_KommentarModuleModuleParamSize 0
#define BASE_KommentarModuleSubmodulesParamSize 0
#define BASE_KommentarModuleParamSize 0
#define BASE_KommentarModuleParamOffset 14037
#define BASE_KommentarModuleCalcIndex(index, m1) (index + BASE_KommentarModuleParamOffset + _channelIndex * BASE_KommentarModuleCount * BASE_KommentarModuleParamSize + m1 * BASE_KommentarModuleParamSize)



#ifdef MAIN_FirmwareRevision
#ifndef FIRMWARE_REVISION
#define FIRMWARE_REVISION MAIN_FirmwareRevision
#endif
#endif
#ifdef MAIN_FirmwareName
#ifndef FIRMWARE_NAME
#define FIRMWARE_NAME MAIN_FirmwareName
#endif
#endif
