#pragma once
/**
 * OpenKNX Hardware Definition Header File
 *
 * File: OpenKNX-REG2-PiPico-Hardware.h
 * Hardware: REG2-Pi-Pico Based Boards (V1)
 * Responsible: OpenKNX - Erkan Çolak
 *
 * Defines hardware IO pins and functionalities for OpenKNX REG2-Pi-Pico platform.
 * Includes pin assignments for LEDs, buttons, serial communication, I2C interfaces,
 * terminal board pins, application board pins, and other peripherals. Ensures 
 * compatibility with various configurations:
 * - REG2-Pi-Pico / Pi-Pico2 (Current Versions: V1)
 * - REG2-Pi-Pico W / Pi-Pico2 W with WiFi
 * - Device Display, RTC, Meter support
 * - Ethernet App Board configurations
 *
 * Each configuration is guarded by preprocessor directives to enable/disable features.
 *
 * More info about the Hardware visit: www.openknx.de
 *
 * ATTENTION:
 *    Do not include this file directly.
 *    It will be included by the REG2.h file.
 *
 */

/**
 * Section: Device configurations / use cases ( Device is a full defined hardware has documentation in openknx wiki)
 * OpenKNX REG2-Pi-Pico
 */

/**
 Device Hardware ID Structure:
 
 Bits 15-12: Main Group (4 bits = 16 main groups)
 Bits 11-8:  Subgroup   (4 bits = 16 subgroups)
 Bits 7-0:   Variant    (8 bits = 256 variants)

 Format: 0xHUVV
         H = Main Group
         U = Subgroup
         VV = Variant
  Example: 0x1201 = Main Group 1, Subgroup 2, Variant 1


  Main Group 0x1 = OpenKNX (0x1000-0x1FFF)
├─ 0x10 = REG1  (0x1000-0x10FF) → 256 variants
├─ 0x11 = REG2  (0x1100-0x11FF) → 256 variants
│  ├─ 0x110x = REG2 PiPico    (0x1100-0x110F) → Base, DD, RTC, Meter, ETH
│  ├─ 0x111x = REG2 PiPico W  (0x1110-0x111F) → WiFi variants
│  ├─ 0x112x = REG2 PiPico2   (0x1120-0x112F) → RP2350 variants
│  └─ 0x113x = REG2 PiPico2 W (0x1130-0x113F) → RP2350 WiFi variants
├─ 0x12 = UP1   (0x1200-0x12FF) → 256 variants
├─ 0x13 = XIAO  (0x1300-0x13FF) → 256 variants
│  ├─ 0x130x = XIAO RP2040   (0x1300-0x130F) → KNeoPix, Mini
│  ├─ 0x131x = XIAO RP2350   (0x1310-0x131F) → KNeoPix
│  ├─ 0x132x = XIAO ESP32S3  (0x1320-0x132F) → KNeoPix, Mini
│  ├─ 0x133x = XIAO ESP32C6  (0x1330-0x133F) → KNeoPix, Mini (future)
│  └─ 0x135x = XIAO ESP32C3  (0x1350-0x135F) → KNeoPix, Mini
└─ ... to 0x1F (16 subgroups)

Main Group 0x2 = OpenKNX-Ready (0x2000-0x2FFF)
├─ 0x20 = Partner A
├─ 0x21 = Partner B
└─ ...
Main Group 0x3 = Community Devices (0x3000-0x3FFF)
├─ 0x30 = Device A
├─ 0x31 = Device B
└─ ...
 */


// DEVICE-based definitions (for full device configurations)
#if defined(DEVICE_REG2_PIPICO_V1) \
  || defined(DEVICE_REG2_PIPICO_V1_DD) \
  || defined(DEVICE_REG2_PIPICO_V1_DD_RTC) \
  || defined(DEVICE_REG2_PIPICO_V1_DD_METER) \
  || defined(DEVICE_REG2_PIPICO_V1_ETH) \
  || defined(DEVICE_REG2_PIPICO_V1_ETH_DD) \
  || defined(DEVICE_REG2_PIPICO_W_V1) \
  || defined(DEVICE_REG2_PIPICO_W_V1_DD) \
  || defined(DEVICE_REG2_PIPICO_W_V1_DD_METER) \
  || defined(DEVICE_REG2_PIPICO_W_V1_ETH) \
  || defined(DEVICE_REG2_PIPICO_W_V1_ETH_DD) \
  || defined(DEVICE_REG2_PIPICO_W_V1_DD_RTC)
    #define PREFIX_ID "REG2-PP-V1"               // 12 characters
    #define PREFIX_NAME "OpenKNX REG2 PiPico V1" // 24 characters
#elif defined(DEVICE_REG2_PIPICO2_V1) \
  || defined(DEVICE_REG2_PIPICO2_V1_DD) \
  || defined(DEVICE_REG2_PIPICO2_V1_DD_RTC) \
  || defined(DEVICE_REG2_PIPICO2_V1_DD_METER) \
  || defined(DEVICE_REG2_PIPICO2_V1_ET) \
  || defined(DEVICE_REG2_PIPICO2_V1_ETH_DD) \
  || defined(DEVICE_REG2_PIPICO2_W_V1) \
  || defined(DEVICE_REG2_PIPICO2_W_V1_DD) \
  || defined(DEVICE_REG2_PIPICO2_W_V1_DD_METER) \
  || defined(DEVICE_REG2_PIPICO2_W_V1_ETH) \
  || defined(DEVICE_REG2_PIPICO2_W_V1_ETH_DD) \
  || defined(DEVICE_REG2_PIPICO2_W_V1_DD_RTC)
    #define PREFIX_ID "REG2-PP2-V1"               // 13 characters
    #define PREFIX_NAME "OpenKNX REG2 PiPico2 V1" // 25 characters
#endif


// REG2-Pi-Pico V1 (RP2040)
#if defined(DEVICE_REG2_PIPICO_V1)
    #define DEVICE_HW_ID 0x1100
    #define DEVICE_ID PREFIX_ID
    #define DEVICE_NAME PREFIX_NAME
    #define OKNXHW_REG2_PIPICO_V1_COMMON // Common pins for all REG2-Pi-Pico
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_V1_LED1   // LED1
// #define OKNXHW_REG2_PIPICO_V1_LED2   // LED2
// #define OKNXHW_REG2_PIPICO_V1_LED3   // LED3
#endif

// REG2-Pi-Pico2 V1 (RP2350)
#if defined(DEVICE_REG2_PIPICO2_V1)
    #define DEVICE_HW_ID 0x1120
    #define DEVICE_ID PREFIX_ID
    #define DEVICE_NAME PREFIX_NAME
    #define OKNXHW_REG2_PIPICO_V1_COMMON // Common pins for all REG2-Pi-Pico
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_V1_LED1   // LED1
// #define OKNXHW_REG2_PIPICO_V1_LED2   // LED2
// #define OKNXHW_REG2_PIPICO_V1_LED3   // LED3
#endif

// REG2-Pi-Pico V1 (Device Display, RP2040)
#if defined(DEVICE_REG2_PIPICO_V1_DD)
    #define DEVICE_HW_ID 0x1101
    #define DEVICE_ID PREFIX_ID "-DD"                // 12 + 8 = 20 characters
    #define DEVICE_NAME PREFIX_NAME " DeviceDisplay" // 24 + 16 = 40 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON                 // Common pins for all REG2-Pi-Pico
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_V1_LED1                   // LED1
    // #define OKNXHW_REG2_PIPICO_V1_LED2   // LED2 ToDo: Set Device Display Front Control LED
    // #define OKNXHW_REG2_PIPICO_V1_LED3   // LED3 ToDo: Set Device Display Front Control LED
    #define OKNXHW_REG2_DEVICE_DISPLAY // Device Display Support
#endif

// REG2-Pi-Pico2 V1 (Device Display, RP2350)
#if defined(DEVICE_REG2_PIPICO2_V1_DD)
    #define DEVICE_HW_ID 0x1121
    #define DEVICE_ID PREFIX_ID "-DD"                // 12 + 8 = 20 characters
    #define DEVICE_NAME PREFIX_NAME " DeviceDisplay" // 24 + 16 = 40 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON                 // Common pins for all REG2-Pi-Pico
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_V1_LED1                   // LED1
    // #define OKNXHW_REG2_PIPICO_V1_LED2   // LED2 ToDo: Set Device Display Front Control LED
    // #define OKNXHW_REG2_PIPICO_V1_LED3   // LED3 ToDo: Set Device Display Front Control LED
    #define OKNXHW_REG2_DEVICE_DISPLAY // Device Display Support
#endif

// REG2-Pi-Pico V1 (Device Display + RTC, RP2040)
#if defined(DEVICE_REG2_PIPICO_V1_DD_RTC)
    #define DEVICE_HW_ID 0x1102
    #define DEVICE_ID PREFIX_ID "-DD-RTC"                // 12 + 8 = 20 characters
    #define DEVICE_NAME PREFIX_NAME " DeviceDisplay RTC" // 24 + 16 = 40 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON                 // Common pins for all REG2-Pi-Pico
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_V1_LED1                   // LED1
    // #define OKNXHW_REG2_PIPICO_V1_LED2   // LED2 ToDo: Set Device Display Front Control LED
    // #define OKNXHW_REG2_PIPICO_V1_LED3   // LED3 ToDo: Set Device Display Front Control LED
    #define OKNXHW_REG2_DEVICE_DISPLAY // Device Display Support
    #define OKNXHW_REG2_DEVICE_RTC     // RTC Support
#endif

// REG2-Pi-Pico2 V1 (Device Display + RTC, RP2350)
#if defined(DEVICE_REG2_PIPICO2_V1_DD_RTC)
    #define DEVICE_HW_ID 0x1122
    #define DEVICE_ID PREFIX_ID "-DD-RTC"                // 12 + 8 = 20 characters
    #define DEVICE_NAME PREFIX_NAME " DeviceDisplay RTC" // 24 + 16 = 40 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON                 // Common pins for all REG2-Pi-Pico
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_V1_LED1                   // LED1
    // #define OKNXHW_REG2_PIPICO_V1_LED2   // LED2 ToDo: Set Device Display Front Control LED
    // #define OKNXHW_REG2_PIPICO_V1_LED3   // LED3 ToDo: Set Device Display Front Control LED
    #define OKNXHW_REG2_DEVICE_DISPLAY // Device Display Support
    #define OKNXHW_REG2_DEVICE_RTC     // RTC Support
#endif

// REG2-Pi-Pico V1 (Device Display + Meter, RP2040)
#if defined(DEVICE_REG2_PIPICO_V1_DD_METER)
    #define DEVICE_HW_ID 0x1103
    #define DEVICE_ID PREFIX_ID "-DD-Meter"                // 12 + 8 = 20 characters
    #define DEVICE_NAME PREFIX_NAME " DeviceDisplay Meter" // 24 + 16 = 40 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON                   // Common pins for all REG2-Pi-Pico
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_V1_LED1                     // LED1
    // #define OKNXHW_REG2_PIPICO_V1_LED2   // LED2 ToDo: Set Device Display Front Control LED
    // #define OKNXHW_REG2_PIPICO_V1_LED3   // LED3 ToDo: Set Device Display Front Control LED
    #define OKNXHW_REG2_DEVICE_DISPLAY // Device Display Support
    #define OKNXHW_REG2_METER          // Meter Support
    #define OKNXHW_REG2_DEVICE_RTC     // RTC Support
#endif

// REG2-Pi-Pico2 V1 (Device Display + Meter, RP2350)
#if defined(DEVICE_REG2_PIPICO2_V1_DD_METER)
    #define DEVICE_HW_ID 0x1123
    #define DEVICE_ID PREFIX_ID "-DD-Meter"                // 12 + 8 = 20 characters
    #define DEVICE_NAME PREFIX_NAME " DeviceDisplay Meter" // 24 + 16 = 40 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON                   // Common pins for all REG2-Pi-Pico
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_V1_LED1                     // LED1
    // #define OKNXHW_REG2_PIPICO_V1_LED2   // LED2 ToDo: Set Device Display Front Control LED
    // #define OKNXHW_REG2_PIPICO_V1_LED3   // LED3 ToDo: Set Device Display Front Control LED
    #define OKNXHW_REG2_DEVICE_DISPLAY // Device Display Support
    #define OKNXHW_REG2_METER          // Meter Support
    #define OKNXHW_REG2_DEVICE_RTC     // RTC Support
#endif

// REG2-Pi-Pico V1 ETH App (RP2040)
#if defined(DEVICE_REG2_PIPICO_V1_ETH)
    #define DEVICE_HW_ID 0x1104
    #define DEVICE_ID PREFIX_ID "-ETH"          // 12 + 4 = 16 characters
    #define DEVICE_NAME PREFIX_NAME " Ethernet" // 24 + 9 = 33 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_V1_LED1
    // #define OKNXHW_REG2_PIPICO_V1_LED2   // LED2 ToDo: Set Device Display Front Control LED
    // #define OKNXHW_REG2_PIPICO_V1_LED3   // LED3 ToDo: Set Device Display Front Control LED
    #define OKNXHW_REG2_USING_APP_BOARD
    #define OKNXHW_REG2_PIPICO_APP_ETH
#endif

// REG2-Pi-Pico2 V1 ETH App (RP2350)
#if defined(DEVICE_REG2_PIPICO2_V1_ETH)
    #define DEVICE_HW_ID 0x1124
    #define DEVICE_ID PREFIX_ID "-ETH"          // 12 + 4 = 16 characters
    #define DEVICE_NAME PREFIX_NAME " Ethernet" // 24 + 9 = 33 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_V1_LED1
    // #define OKNXHW_REG2_PIPICO_V1_LED2   // LED2 ToDo: Set Device Display Front Control LED
    // #define OKNXHW_REG2_PIPICO_V1_LED3   // LED3 ToDo: Set Device Display Front Control LED
    #define OKNXHW_REG2_USING_APP_BOARD
    #define OKNXHW_REG2_PIPICO_APP_ETH
#endif

// REG2-Pi-Pico V1 ETH App (Device Display, RP2040)
#if defined(DEVICE_REG2_PIPICO_V1_ETH_DD)
    #define DEVICE_HW_ID 0x1105
    #define DEVICE_ID PREFIX_ID "-ETH"          // 12 + 4 = 16 characters
    #define DEVICE_NAME PREFIX_NAME " Ethernet" // 24 + 9 = 33 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    //#define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_DEVICE_DISPLAY
    #define OKNXHW_REG2_PIPICO_V1_LED1
    // #define OKNXHW_REG2_PIPICO_V1_LED2   // LED2 ToDo: Set Device Display Front Control LED
    // #define OKNXHW_REG2_PIPICO_V1_LED3   // LED3 ToDo: Set Device Display Front Control LED
    #define OKNXHW_REG2_USING_APP_BOARD
    #define OKNXHW_REG2_PIPICO_APP_ETH
#endif

// REG2-Pi-Pico2 V1 ETH App (Device Display, RP2350)
#if defined(DEVICE_REG2_PIPICO2_V1_ETH_DD)
    #define DEVICE_HW_ID 0x1125
    #define DEVICE_ID PREFIX_ID "-ETH"          // 12 + 4 = 16 characters
    #define DEVICE_NAME PREFIX_NAME " Ethernet" // 24 + 9 = 33 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    //#define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_DEVICE_DISPLAY
    #define OKNXHW_REG2_PIPICO_V1_LED1
    // #define OKNXHW_REG2_PIPICO_V1_LED2   // LED2 ToDo: Set Device Display Front Control LED
    // #define OKNXHW_REG2_PIPICO_V1_LED3   // LED3 ToDo: Set Device Display Front Control LED
    #define OKNXHW_REG2_USING_APP_BOARD
    #define OKNXHW_REG2_PIPICO_APP_ETH
#endif

/**
 * Section: Product configurations / use cases
 * OpenKNX REG2-Pi-Pico Wi-Fi
 */

// REG2-Pi-Pico Wi-Fi V1 (RP2040)
#if defined(DEVICE_REG2_PIPICO_W_V1)
    #define DEVICE_HW_ID 0x1110
    #define DEVICE_ID PREFIX_ID "-W"        // 12 + 2 = 14 characters
    #define DEVICE_NAME PREFIX_NAME " WiFi" // 24 + 5 = 29 characters --> + 14 = 43 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_W_V1_LED1
    //#define OKNXHW_REG2_PIPICO_V1_LED2
    //#define OKNXHW_REG2_PIPICO_V1_LED3
#endif

// REG2-Pi-Pico2 Wi-Fi V1 (RP2350)
#if defined(DEVICE_REG2_PIPICO2_W_V1)
    #define DEVICE_HW_ID 0x1130
    #define DEVICE_ID PREFIX_ID "-W"        // 12 + 2 = 14 characters
    #define DEVICE_NAME PREFIX_NAME " WiFi" // 24 + 5 = 29 characters --> + 14 = 43 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_W_V1_LED1
    //#define OKNXHW_REG2_PIPICO_V1_LED2
    //#define OKNXHW_REG2_PIPICO_V1_LED3
#endif

// REG2-Pi-Pico Wi-Fi V1 (Device Display, RP2040)
#if defined(DEVICE_REG2_PIPICO_W_V1_DD)
    #define DEVICE_HW_ID 0x1111
    #define DEVICE_ID PREFIX_ID "-W"        // 12 + 2 = 14 characters
    #define DEVICE_NAME PREFIX_NAME " WiFi" // 24 + 5 = 29 characters --> + 14 = 43 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_W_V1_LED1
    // #define OKNXHW_REG2_PIPICO_V1_LED2
    // #define OKNXHW_REG2_PIPICO_V1_LED3
    #define OKNXHW_REG2_DEVICE_DISPLAY
#endif

// REG2-Pi-Pico2 Wi-Fi V1 (Device Display, RP2350)
#if defined(DEVICE_REG2_PIPICO2_W_V1_DD)
    #define DEVICE_HW_ID 0x1131
    #define DEVICE_ID PREFIX_ID "-W"        // 12 + 2 = 14 characters
    #define DEVICE_NAME PREFIX_NAME " WiFi" // 24 + 5 = 29 characters --> + 14 = 43 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_W_V1_LED1
    // #define OKNXHW_REG2_PIPICO_V1_LED2
    // #define OKNXHW_REG2_PIPICO_V1_LED3
    #define OKNXHW_REG2_DEVICE_DISPLAY
#endif

// REG2-Pi-Pico Wi-Fi V1 (Device Display + RTC, RP2040)
#if defined(DEVICE_REG2_PIPICO_W_V1_DD_RTC)
    #define DEVICE_HW_ID 0x1112
    #define DEVICE_ID PREFIX_ID "-W-DD-RTC"             // 12 + 10 = 22 characters
    #define DEVICE_NAME PREFIX_NAME " WiFi Display RTC" // 24 + 14 = 38 characters --> + 22 = 60 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_W_V1_LED1
    //#define OKNXHW_REG2_PIPICO_V1_LED2
    //#define OKNXHW_REG2_PIPICO_V1_LED3
    #define OKNXHW_REG2_DEVICE_DISPLAY
    #define OKNXHW_REG2_DEVICE_RTC
#endif

// REG2-Pi-Pico2 Wi-Fi V1 (Device Display + RTC, RP2350)
#if defined(DEVICE_REG2_PIPICO2_W_V1_DD_RTC)
    #define DEVICE_HW_ID 0x1132
    #define DEVICE_ID PREFIX_ID "-W-DD-RTC"             // 12 + 10 = 22 characters
    #define DEVICE_NAME PREFIX_NAME " WiFi Display RTC" // 24 + 14 = 38 characters --> + 22 = 60 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_W_V1_LED1
    //#define OKNXHW_REG2_PIPICO_V1_LED2
    //#define OKNXHW_REG2_PIPICO_V1_LED3
    #define OKNXHW_REG2_DEVICE_DISPLAY
    #define OKNXHW_REG2_DEVICE_RTC
#endif

// REG2-Pi-Pico Wi-Fi V1 (Device Display + Meter, RP2040)
#if defined(DEVICE_REG2_PIPICO_W_V1_DD_METER)
    #define DEVICE_HW_ID 0x1113
    #define DEVICE_ID PREFIX_ID "-W-DD-Meter"             // 12 + 8 = 20 characters
    #define DEVICE_NAME PREFIX_NAME " WiFi Display Meter" // 24 + 20 = 44 characters --> + 20 = 64 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_W_V1_LED1
    //#define OKNXHW_REG2_PIPICO_V1_LED2
    //#define OKNXHW_REG2_PIPICO_V1_LED3
    #define OKNXHW_REG2_DEVICE_DISPLAY
    #define OKNXHW_REG2_METER
#endif

// REG2-Pi-Pico2 Wi-Fi V1 (Device Display + Meter, RP2350)
#if defined(DEVICE_REG2_PIPICO2_W_V1_DD_METER)
    #define DEVICE_HW_ID 0x1133
    #define DEVICE_ID PREFIX_ID "-W-DD-Meter"             // 12 + 8 = 20 characters
    #define DEVICE_NAME PREFIX_NAME " WiFi Display Meter" // 24 + 20 = 44 characters --> + 20 = 64 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_W_V1_LED1
    //#define OKNXHW_REG2_PIPICO_V1_LED2
    //#define OKNXHW_REG2_PIPICO_V1_LED3
    #define OKNXHW_REG2_DEVICE_DISPLAY
    #define OKNXHW_REG2_METER
#endif

// REG2-Pi-Pico WiFi V1 ETH App (RP2040)
#if defined(DEVICE_REG2_PIPICO_W_V1_ETH)
    #define DEVICE_HW_ID 0x1114
    #define DEVICE_ID PREFIX_ID "-W-ETH"             // 12 + 6 = 18 characters
    #define DEVICE_NAME PREFIX_NAME " WiFi Ethernet" // 24 + 9 = 33 characters --> + 18 = 51 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_W_V1_LED1
    //#define OKNXHW_REG2_PIPICO_V1_LED2
    //#define OKNXHW_REG2_PIPICO_V1_LED3
    #define OKNXHW_REG2_PIPICO_APP_ETH
#endif

// REG2-Pi-Pico2 WiFi V1 ETH App (RP2350)
#if defined(DEVICE_REG2_PIPICO2_W_V1_ETH)
    #define DEVICE_HW_ID 0x1134
    #define DEVICE_ID PREFIX_ID "-W-ETH"             // 12 + 6 = 18 characters
    #define DEVICE_NAME PREFIX_NAME " WiFi Ethernet" // 24 + 9 = 33 characters --> + 18 = 51 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_W_V1_LED1
    //#define OKNXHW_REG2_PIPICO_V1_LED2
    //#define OKNXHW_REG2_PIPICO_V1_LED3
    #define OKNXHW_REG2_PIPICO_APP_ETH
#endif

// REG2-Pi-Pico WiFi V1 ETH App (Device Display, RP2040)
#if defined(DEVICE_REG2_PIPICO_W_V1_ETH_DD)
    #define DEVICE_HW_ID 0x1115
    #define DEVICE_ID PREFIX_ID "-W-ETH-DD"           // 12 + 12 = 24 characters
    #define DEVICE_NAME PREFIX_NAME " WiFi Ethernet Display" // 24 + 20 = 44 characters --> + 24 = 68 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_W_V1_LED1
    //#define OKNXHW_REG2_PIPICO_V1_LED2
    // #define OKNXHW_REG2_PIPICO_V1_LED3
    #define OKNXHW_REG2_DEVICE_DISPLAY
    #define OKNXHW_REG2_PIPICO_APP_ETH
#endif

// REG2-Pi-Pico2 WiFi V1 ETH App (Device Display, RP2350)
#if defined(DEVICE_REG2_PIPICO2_W_V1_ETH_DD)
    #define DEVICE_HW_ID 0x1135
    #define DEVICE_ID PREFIX_ID "-W-ETH-DD"           // 12 + 12 = 24 characters
    #define DEVICE_NAME PREFIX_NAME " WiFi Ethernet Display" // 24 + 20 = 44 characters --> + 24 = 68 characters
    #define OKNXHW_REG2_PIPICO_V1_COMMON
    #define OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define OKNXHW_REG2_PIPICO_W_V1_LED1
    //#define OKNXHW_REG2_PIPICO_V1_LED2
    // #define OKNXHW_REG2_PIPICO_V1_LED3
    #define OKNXHW_REG2_DEVICE_DISPLAY
    #define OKNXHW_REG2_PIPICO_APP_ETH
#endif

/**
 * Section: Firmware Features (FwF) based IO and Pin Definitions
 * OpenKNX REG2-Pi-Pico
 */

// REG2-Pi-Pico FwF: Device Display Support
#if defined(OKNXHW_REG2_DEVICE_DISPLAY) || defined(OKNXHW_REG2_USING_APP_BOARD)
    // Default pins for the I2C bus to connect the hardware display
    #define OKNXHW_REG2_HWDISPLAY_I2C_INST i2c1 // i2c1 | i2c0

    #ifdef OKNXHW_REG2_USING_APP_BOARD
        #define OKNXHW_REG2_HWDISPLAY_I2C_SDA 22 // GPIO22 | SPI0 SCK | UART1 TX | I2C1 SDA | PWM3 A | ADC2
        #define OKNXHW_REG2_HWDISPLAY_I2C_SCL 15 // GPIO15 | SPI0 TX  | UART1 RX | I2C1 SCL | PWM2 B | ADC3
    #else
        #define OKNXHW_REG2_HWDISPLAY_I2C_SDA 26 // GPIO26 | SPI1 SCK | UART0 CTS | I2C1 SDA | PWM5 A | ADC0
        #define OKNXHW_REG2_HWDISPLAY_I2C_SCL 27 // GPIO27 | SPI1 TX  | UART0 RX  | I2C0 SCL | PWM6 B | ADC1
    #endif
    #define OKNXHW_REG2_HWDISPLAY_I2C_ADDRESS 0x3C // Set here the i2c address of the display. I.e. 0x3C, 0x3D
    #define OKNXHW_REG2_HWRTCLOCK_I2C_ADDRESS 0x68 // Set here the i2c address of the RTC. I.e. 0x68 for DS3231. 0x57 for PCF8523. 0x51 for DS3232
    #define OKNXHW_REG2_DEVICE_DISPLAY_WIDTH 128   // Set here the width of the device display. I.e. 128
    #define OKNXHW_REG2_DEVICE_DISPLAY_HEIGHT 64   // Set here the height of the device display. I.e. 64

    // Set there now the generall setting definition for the OFM-DeviceDisplay
    #define OPENKNX_GPIO_SDA OKNXHW_REG2_HWDISPLAY_I2C_SDA
    #define OPENKNX_GPIO_SCL OKNXHW_REG2_HWDISPLAY_I2C_SCL

    // Define the 8 GPIO Pins of the PCA9557 I2C GPIO Expander
    #define FRONT_CTRL_LEFT   0x100   // PIN 0 (LEFT)
    #define FRONT_CTRL_LED1_R 0x101   // PIN 1 (RED LED)
    #define FRONT_CTRL_LED2_G 0x102   // PIN 2 (GREEN LED)
    #define FRONT_CTRL_LEFT2  0x103   // PIN 3 (LEFT2)
    #define FRONT_CTRL_DOWN   0x104   // PIN 4 (DOWN)
    #define FRONT_CTRL_RIGHT  0x105   // PIN 5 (RIGHT)
    #define FRONT_CTRL_OK     0x106   // PIN 6 (OK / SELECT)
    #define FRONT_CTRL_UP     0x107   // PIN 7 (UP)

    #define OPENKNX_PCA9557_PINS_COUNT 8
    #define OPENKNX_PCA9557_PINS \
                FRONT_CTRL_LEFT, \
                FRONT_CTRL_LED1_R, \
                FRONT_CTRL_LED2_G, \
                FRONT_CTRL_LEFT2, \
                FRONT_CTRL_DOWN, \
                FRONT_CTRL_RIGHT, \
                FRONT_CTRL_OK, \
                FRONT_CTRL_UP

    #define OPENKNX_GPIO_NUM    1         // Total number of GPIO expanders used
    #define OPENKNX_GPIO_TYPES  OPENKNX_GPIO_T_PCA9557
    #define OPENKNX_GPIO_ADDRS  0x18      // PCA9557 I2C address 0x18 (A0-A2 = 0) A0-A2 are connected to GND if A1 is connected to VCC the address is 0x19
    #define OPENKNX_GPIO_INTS   0xFF
    #define OPENKNX_GPIO_WIRE   Wire1     // OKNXHW_REG2_HWDISPLAY_I2C_INST
    #define OPENKNX_GPIO_CLOCK  400000    // I2C Taktfrequenz in Hz (400kHz für schnelle I2C-Kommunikation)

    #define OKNXHW_DEVICE_DISPLAY_I2C_INST    OKNXHW_REG2_HWDISPLAY_I2C_INST
    #define OKNXHW_DEVICE_DISPLAY_I2C_SDA     OKNXHW_REG2_HWDISPLAY_I2C_SDA
    #define OKNXHW_DEVICE_DISPLAY_I2C_SCL     OKNXHW_REG2_HWDISPLAY_I2C_SCL
    #define OKNXHW_DEVICE_DISPLAY_I2C_ADDRESS OKNXHW_REG2_HWDISPLAY_I2C_ADDRESS
    #define OKNXHW_DEVICE_DISPLAY_WIDTH       OKNXHW_REG2_DEVICE_DISPLAY_WIDTH
    #define OKNXHW_DEVICE_DISPLAY_HEIGHT      OKNXHW_REG2_DEVICE_DISPLAY_HEIGHT

#endif // REG2-Pi-Pico FwF: Device Display Support

// REG2-Pi-Pico FwF: Device RTC Support
#ifdef OKNXHW_REG2_DEVICE_RTC
    // Default pins for the I2C bus to connect the hardware RTC - This is the default setting for the DS3231!!
    #define OKNXHW_REG2_HWRTC_I2C_ADDRESS         0x68    // i2c address of the RTC. I.e. 0x68 for DS3231.
    #define OKNXHW_REG2_HWRTC_I2C_EEPROM_ADDRESS  0x57    // Set here the i2c address of the RTC EEPROM. I.e. 0x57 for DS3231.
    #define OKNXHW_REG2_HWRTC_I2C_EEPROM_SIZE     0x1000  // Set here the size of the RTC EEPROM. I.e. 0x1000 for DS3231.
    #define OKNXHW_REG2_HWRTC_SRAM_RTC_USER_START 0x13    // User address start in the DS3231 SRAM. 0x13
    #define OKNXHW_REG2_HWRTC_SRAM_RTC_USER_END   0x3F    // User address end in the DS3231 SRAM. 0x3F
    #define OKNXHW_REG2_HWRTC_SRAM_RTC_USER       45      // (SRAM_RTC_USER_END - SRAM_RTC_USER_START + 1) // User address count in the DS3231 SRAM.

    #define OKNXHW_REG2_HWRTC_I2C_INST i2c1 // i2c1 | i2c0

    #ifdef OKNXHW_REG2_USING_APP_BOARD
        #define OKNXHW_REG2_HWRTC_I2C_SDA 22 // GPIO22 | SPI1 RX  | UART1 TX  | I2C1 SDA | PWM4 A | ADC6
        #define OKNXHW_REG2_HWRTC_I2C_SCL 15 // GPIO15 | SPI1 CSn | UART1 RX  | I2C1 SCL | PWM4 B | ADC7
    #else
        #define OKNXHW_REG2_HWRTC_I2C_SDA 26 // GPIO26 | SPI1 SCK | UART0 CTS | I2C1 SDA | PWM5 A | ADC0
        #define OKNXHW_REG2_HWRTC_I2C_SCL 27 // GPIO27 | SPI1 TX  | UART0 RX  | I2C0 SCL | PWM6 B | ADC1
    #endif

    // Set there now the generall setting definition for the OFM-DeviceRTC
    #define OKNXHW_DEVICE_RTC_EEPROM_I2C_ADDRESS OKNXHW_REG2_HWRTC_I2C_EEPROM_ADDRESS
    #define OKNXHW_DEVICE_RTC_I2C_ADDRESS        OKNXHW_REG2_HWRTC_I2C_ADDRESS
    #define OKNXHW_DEVICE_RTC_I2C_SDA            OKNXHW_REG2_HWRTC_I2C_SDA
    #define OKNXHW_DEVICE_RTC_I2C_SCL            OKNXHW_REG2_HWRTC_I2C_SCL
    #define OKNXHW_DEVICE_RTC_I2C_INST           OKNXHW_REG2_HWRTC_I2C_INST
#endif // REG2-Pi-Pico FwF: Device RTC Support

// REG2-Pi-Pico FwF: Meter Support
#ifdef OKNXHW_REG2_METER
    // Default pins for the Meter Sensors typ Rx/Tx
    #define OKNXHW_REG2_MSENS_1_SDA0_TX_PIN 4 // GPIO4  | SPI0 RX  | UART1 TX  | I2C0 SDA | PWM2 A
    #define OKNXHW_REG2_MSENS_1_SCL0_RX_PIN 5 // GPIO5  | SPI0 TX  | UART1 RX  | I2C0 SCL | PWM2 B
    #define OKNXHW_REG2_MSENS_2_SDA1_TX_PIN 6 // GPIO6  | SPI0 SCK | UART1 CTS | I2C1 SDA | PWM3 A
    #define OKNXHW_REG2_MSENS_2_SCL1_RX_PIN 7 // GPIO7  | SPI0 CSn | UART1 RTS | I2C1 SCL | PWM3 B
#endif                                        // REG2-Pi-Pico (Device Display + Meter)

/**
 * Section: Hardware specific Pin Definitions
 * OpenKNX REG2-Pi-Pico
 */

// REG2-Pi-Pico V1: Info1 LED
#ifdef OKNXHW_REG2_PIPICO_V1_LED1
    #define INFO1_LED_PIN 25 // PiPico Onboard LED
    #define INFO1_LED_PIN_ACTIVE_ON HIGH
#endif

// REG2-Pi-Pico Wifi V1: Info1 LED
#ifdef OKNXHW_REG2_PIPICO_W_V1_LED1
    #define INFO1_LED_PIN LED_BUILTIN // PiPicoW1 GPIO 32 / PiPicoW2 GPIO 64 (Onboard LED WiFi)
    #define INFO1_LED_PIN_ACTIVE_ON HIGH
#endif

// REG2-Pi-Pico V1: Info2 LED
#ifdef OKNXHW_REG2_PIPICO_V1_LED2
    //#define INFO2_LED_PIN 3 // ToDo: Option use of DD Front Control LEDs
    //#define INFO2_LED_PIN_ACTIVE_ON HIGH
#endif
// REG2-Pi-Pico V1: Info3 LED
#ifdef OKNXHW_REG2_PIPICO_V1_LED3
    //#define INFO3_LED_PIN 21 // ToDo: Optional use of DD Front Control LEDs
    //#define INFO3_LED_PIN_ACTIVE_ON HIGH
#endif

// REG2-Pi-Pico V1: Interrupt Pin
#ifdef OKNXHW_REG2_PIPICO_V1_SAVE_INTERRUPT
    #define SAVE_INTERRUPT_PIN 21
#endif

/**
 * Section: Common Hardware (CHW) Pin Definitions
 * REG2-Pi-Pico V1
 */
// REG2-Pi-Pico V1 CHW Pins
#ifdef OKNXHW_REG2_PIPICO_V1_COMMON
    #define PROG_LED_PIN 2
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 20
    #define PROG_BUTTON_PIN_MODE INPUT_PULLUP   // Using internal pullup of the ESP32 (aprox. 45kOhm)
    #define OPENKNX_BUTTON_DEBOUNCE 0           // Software Debouncer in ms. 0 will Disables software debounce. Since we use the hardware debounce.
    #define KNX_SERIAL Serial1 // Uart0
    #define KNX_UART_NUM 0     // Uart0 
    #define KNX_UART_RX_PIN 1
    #define KNX_UART_TX_PIN 0

    // Application board
    #define REG2_APP_PIN1 16 // GPIO16 | SPI0 RX  | UART0 TX  | I2C0 SDA | PWM0 A
    #define REG2_APP_PIN2 17 // GPIO17 | SPI0 CSn | UART0 RX  | I2C0 SCL | PWM0 B
    #define REG2_APP_PIN3 18 // GPIO18 | SPI0 SCK | UART0 CTS | I2C1 SDA | PWM1 A
    #define REG2_APP_PIN4 26 // GPIO26 | SPI1 SCK | UART0 CTS | I2C1 SDA | PWM5 A | ADC0
    #define REG2_APP_PIN5 27 // GPIO27 | SPI1 TX  | UART0 RX  | I2C0 SCL | PWM6 B | ADC1
    #define REG2_APP_PIN6 28 // GPIO28 | SPI1 RX  | UART0 TX  | I2C0 SDA | PWM6 A | ADC2
    #define REG2_APP_PIN7 19 // GPIO19 | SPI0 TX  | UART0 RTS | I2C1 SCL | PWM1 B
    // #define REG2_APP_PIN8 GND
    // #define REG2_APP_PIN9 3V3
    // #define REG2_APP_PIN10 5V (VUSB)

    // Application board extended pins
    #define REG2_APP_PIN11 15 // GPIO15 | SPI1 TX  | UART0 RTS | I2C1 SCL | PWM7 B
    #define REG2_APP_PIN12 14 // GPIO14 | SPI1 SCK | UART0 CTS | I2C1 SDA | PWM7 A
    #define REG2_APP_PIN13 13 // GPIO13 | SPI1 RX  | UART0 TX  | I2C0 SDA | PWM6 B
    #define REG2_APP_PIN14 12 // GPIO12 | SPI1 RX  | UART0 TX  | I2C0 SDA | PWM6 A
    #define REG2_APP_PIN15 11 // GPIO11 | SPI1 TX  | UART1 RTS | I2C1 SCL | PWM7 B
    #define REG2_APP_PIN16 10 // GPIO10 | SPI1 SCK | UART1 CTS | I2C1 SDA | PWM5 A
    // #define REG2_APP_PIN17 GND
    // #define REG2_APP_PIN18 EXT_VCC_IN

    // Terminal board
    #define REG2_TERM_PIN10 22 // GPIO22 | SPI0 SCK | UART1 CTS | I2C1 SDA | PWM3 A
    #define REG2_TERM_PIN9 9   // GPIO9  | SPI1 TX  | UART1 RX  | I2C0 SCL | PWM4 B
    #define REG2_TERM_PIN8 8   // GPIO8  | SPI1 RX  | UART1 TX  | I2C0 SDA | PWM4 A
    #define REG2_TERM_PIN7 7   // GPIO7  | SPI0 CSn | UART1 RTS | I2C1 SCL | PWM3 B
    #define REG2_TERM_PIN6 6   // GPIO6  | SPI0 SCK | UART1 CTS | I2C1 SDA | PWM3 A
    #define REG2_TERM_PIN5 5   // GPIO5  | SPI0 TX  | UART1 RX  | I2C0 SCL | PWM2 B
    #define REG2_TERM_PIN4 4   // GPIO4  | SPI0 RX  | UART1 TX  | I2C0 SDA | PWM2 A

#endif

/**
 * Section: FwF and CHW based Pin Definitions
 * OpenKNX REG2-Pi-Pico
 */

// REG2-Pi-Pico (WiFi) ETH App and FwF
#ifdef OKNXHW_REG2_PIPICO_APP_ETH
    #define ETH_SPI_INTERFACE SPI        // SPI or SPI1, depends on the pins
    #define PIN_ETH_MISO (REG2_APP_PIN1) // ETH_MISO - GPIO16 SPI0 RX UART0 TX I2C0 SDA PWM0_A SIO PIO0 PIO1
    #define PIN_ETH_SS (REG2_APP_PIN2)   // ETH_CS   - GPIO17 SPI0 CSn UART0 RX I2C0 SCL PWM0_B SIO PIO0 PIO1
    #define PIN_ETH_SCK (REG2_APP_PIN3)  // ETH_SCK  - GPIO18 SPI0 SCK UART0 CTS I2C1 SDA PWM1_A SIO PIO0 PIO1
    #define PIN_ETH_MOSI (REG2_APP_PIN7) // ETH_MOSI - GPIO19 SPI0 TX UART0 RTS I2C1 SCL PWM1_B SIO PIO0 PIO1
    #define PIN_ETH_RES (REG2_APP_PIN4)  // ETH_RES  - GPIO27 SPI1 TX UART0 RTS I2C1 SCL PWM5_B SIO PIO0 PIO1
    #define PIN_ETH_INT (REG2_APP_PIN5)  // ETH_RES  - GPIO26 SPI1 SCK UART0 CTS I2C1 SDA PWM5_A SIO PIO0 PIO1

    #define SDCARD_SPI_INTERFACE SPI1        // SPI or SPI1, depends on the pins
    #define PIN_SDCARD_CD (REG2_APP_PIN12)   // Card Detect - GPIO14 SPI1 SCK UART0 CTS I2C1 SDA PWM7_A SIO PIO0 PIO1
    #define PIN_SDCARD_CS (REG2_APP_PIN13)   // Chip Select - GPIO13 SPI1 RX UART0 TX I2C0 SDA PWM6_B SIO PIO0 PIO1
    #define PIN_SDCARD_SCK (REG2_APP_PIN16)  // Clock - GPIO10 SPI1 SCK UART1 CTS I2C1 SDA PWM5_A SIO PIO0 PIO1
    #define PIN_SDCARD_MISO (REG2_APP_PIN14) // Master In Slave Out - GPIO12 SPI1 RX UART0 TX I2C0 SDA PWM6_A SIO PIO0 PIO1
    #define PIN_SDCARD_MOSI (REG2_APP_PIN15) // Master Out Slave In - GPIO11 SPI1 TX UART1 RTS I2C1 SCL PWM7_B SIO PIO0 PIO1
#endif

/* Here is the pinout of the Raspberry Pi Pico and all the possible functions of each pin:

GP0  - SPI0 RX  | UART0 TX  | I2C0 SDA  | PWM0 A  | -
GP1  - SPI0 CSn | UART0 RX  | I2C0 SCL  | PWM0 B  | -
GP2  - SPI0 SCK | UART1 TX  | I2C1 SDA  | PWM1 A  | -
GP3  - SPI0 TX  | UART1 RX  | I2C1 SCL  | PWM1 B  | -
GP4  - SPI0 RX  | UART0 TX  | I2C0 SDA  | PWM2 A  | ADC0
GP5  - SPI0 CSn | UART0 RX  | I2C0 SCL  | PWM2 B  | ADC1
GP6  - SPI0 SCK | UART1 TX  | I2C1 SDA  | PWM3 A  | ADC2
GP7  - SPI0 TX  | UART1 RX  | I2C1 SCL  | PWM3 B  | -
GP8  - SPI1 RX  | UART0 TX  | I2C0 SDA  | PWM4 A  | -
GP9  - SPI1 CSn | UART0 RX  | I2C0 SCL  | PWM4 B  | -
GP10 - SPI1 SCK | UART1 TX  | I2C1 SDA  | PWM5 A  | -
GP11 - SPI1 TX  | UART1 RX  | I2C1 SCL  | PWM5 B  | -
GP12 - SPI1 RX  | UART0 TX  | I2C0 SDA  | PWM6 A  | -
GP13 - SPI1 CSn | UART0 RX  | I2C0 SCL  | PWM6 B  | -
GP14 - SPI1 SCK | UART1 TX  | I2C1 SDA  | PWM7 A  | -
GP15 - SPI1 TX  | UART1 RX  | I2C1 SCL  | PWM7 B  | -
GP16 - SPI0 RX  | UART0 TX  | I2C0 SDA  | PWM0 A  | -
GP17 - SPI0 CSn | UART0 RX  | I2C0 SCL  | PWM0 B  | -
GP18 - SPI0 SCK | UART1 TX  | I2C1 SDA  | PWM1 A  | -
GP19 - SPI0 TX  | UART1 RX  | I2C1 SCL  | PWM1 B  | -
GP20 - SPI0 RX  | UART0 TX  | I2C0 SDA  | PWM2 A  | -
GP21 - SPI0 CSn | UART0 RX  | I2C0 SCL  | PWM2 B  | -
GP22 - SPI1 RX  | UART1 TX  | -         | PWM3 A  | -
GP23 - SPI1 CSn | UART1 RX  | -         | PWM3 B  | -
GP24 - SPI1 SCK | UART0 TX  | -         | PWM4 A  | -
GP25 - SPI1 TX  | UART0 RX  | -         | PWM4 B  | -
GP26 - SPI1 RX  | UART0 TX  | I2C1 SDA  | PWM5 A  | ADC0
GP27 - SPI1 CSn | UART0 RX  | I2C1 SCL  | PWM5 B  | ADC1
GP28 - SPI1 SCK | UART1 TX  | I2C0 SDA  | PWM6 A  | ADC2
GP29 - SPI1 TX  | UART1 RX  | I2C0 SCL  | PWM6 B  | -
*/