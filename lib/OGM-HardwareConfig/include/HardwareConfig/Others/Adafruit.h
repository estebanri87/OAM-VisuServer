#pragma once
/**
 * OpenKNX Hardware definition header file
 *
 * File: Adafruit.h
 * Hardware: Adafruit
 * Responsible: mgeramb
 *
 *
 * More info about the Hardware visit: https://github.com/OpenKNX/OpenKNX/wiki/Adafruit-ESP32-Feather-V2
 *
 * ATTENTION:
 *    Do not include this file directly.
 *    It will be included by the HardwareConfig.h file.
 */
#pragma region "Adafruit Dev Boards"
// https://github.com/OpenKNX/OpenKNX/wiki/Adafruit-ESP32-Feather-V2
#ifdef DEVICE_ADAFRUIT_ESP32_FEATHER_V2
    #define DEVICE_ID "ADF-ESP32-FEATHER-V2"
    #define DEVICE_NAME "Adafruit ESP32 Feather V2"
    #if !defined(KNX_IP_LAN) && !defined(KNX_IP_WIFI)
        #define KNX_IP_WIFI // Use WIFI by default, if LAN is not defined
    #endif
    #ifndef SERIAL_DEBUG
    #define SERIAL_DEBUG Serial
    #endif
    #ifndef KNX_SERIAL
        #define KNX_SERIAL Serial1
    #endif
    #ifndef KNX_UART_NUM
        #define KNX_UART_NUM 1
    #endif
    #ifndef KNX_UART_RX_PIN
        #define KNX_UART_RX_PIN 34
    #endif
    #ifndef KNX_UART_TX_PIN
        #define KNX_UART_TX_PIN 25
    #endif
    #ifndef OPENKNX_SERIALLED_PIN
        #define OPENKNX_SERIALLED_PIN 0
    #endif
    #ifndef OPENKNX_SERIALLED_POWER_PIN
        #define OPENKNX_SERIALLED_POWER_PIN 2
    #endif
    #ifndef PROG_LED_PIN
        #define PROG_LED_PIN LED_BUILTIN
        #ifndef PROG_LED_PIN_ACTIVE_ON
        #define PROG_LED_PIN_ACTIVE_ON HIGH
        #endif
    #endif
    #ifndef PROG_BUTTON_PIN
        #define PROG_BUTTON_PIN 38
    #endif
    #ifndef PROG_LED_PIN2_ACTIVE_ON
        #define PROG_LED_PIN2_ACTIVE_ON HIGH
    #endif
    #ifndef PROG_LED_PIN3_ACTIVE_ON
        #define PROG_LED_PIN3_ACTIVE_ON HIGH
    #endif

    #ifdef PROG_LED_PIN2
        #define PROG_LED2_INIT() \
            openknx.leds.addLed(new OpenKNX::Led::GPIO(PROG_LED_PIN2, PROG_LED_PIN2_ACTIVE_ON), OpenKNX::Led::LED_TYPE_PROG);
    #else
        #define PROG_LED2_INIT()
    #endif
    #ifdef PROG_LED_PIN3
    #define PROG_LED3_INIT() \
       openknx.leds.addLed(new OpenKNX::Led::GPIO(PROG_LED_PIN3, PROG_LED_PIN3_ACTIVE_ON), OpenKNX::Led::LED_TYPE_PROG);
    #else
        #define PROG_LED3_INIT()
    #endif

    #ifndef OPENKNX_INFOLED1_DEFAULT
        #define OPENKNX_INFOLED1_DEFAULT 10
    #endif

    #define OPENKNX_LEDCOLOR_CALIBRATION {10, 10, 10}
    #ifndef LED_INIT
        #define OPENKNX_SERIALLED_ENABLE
        #define LED_INIT() \
            pinMode(OPENKNX_SERIALLED_POWER_PIN, OUTPUT); \
            digitalWrite(OPENKNX_SERIALLED_POWER_PIN, HIGH); \
            openknx.leds.addLed(new OpenKNX::Led::GPIO(PROG_LED_PIN, PROG_LED_PIN_ACTIVE_ON), OpenKNX::Led::LED_TYPE_PROG); \
            openknx.leds.addLed(new OpenKNX::Led::Serial(0, OPENKNX_SERIALLED_PIN, OpenKNX::Led::Color::Green), OpenKNX::Led::LED_TYPE_INFO1); \
            PROG_LED2_INIT() \
            PROG_LED3_INIT()
    #endif

#endif
#pragma endregion