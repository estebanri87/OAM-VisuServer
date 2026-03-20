#pragma once
/**
 * OpenKNX Hardware definition header file
 * 
 * File: misc.h
 * Hardware: OpenKNX Miscellanous Hardware
 * Responsible: OpenKNX
 *
 *
 * More info about the Hardware visit: https://wiki.OpenKNX.de
 *
 * ATTENTION:
 *    Do not include this file directly.
 *    It will be included by the HardwareConfig.h file.
 */


// PiPico-BCU-Connector
// https://github.com/OpenKNX/OpenKNX/wiki/PiPico-BCU-Connector
    #ifdef DEVICE_PIPICO_BCU_CONNECTOR
        #define DEVICE_HW_ID 0x1F00
        #define DEVICE_ID "PiPico-BCU-Connector"
        #define DEVICE_NAME "OpenKNX PiPico BCU Connector"

        #define PROG_LED_PIN 21
        #define PROG_LED_PIN_ACTIVE_ON HIGH
        #define PROG_BUTTON_PIN 22
        #define SAVE_INTERRUPT_PIN 20
        #define KNX_SERIAL Serial1
        #define KNX_UART_NUM 0
        #define KNX_UART_RX_PIN 1
        #define KNX_UART_TX_PIN 0
    #endif

    // PiPico-BCU-Connector
// https://github.com/OpenKNX/OpenKNX/wiki/PiPico-BCU-Connector
    #ifdef DEVICE_PIPICO2_BCU_CONNECTOR
        #define DEVICE_HW_ID 0x1F01
        #define DEVICE_ID "PiPico2-BCU-Connector"
        #define DEVICE_NAME "OpenKNX PiPico2 BCU Connector"

        #define PROG_LED_PIN 21
        #define PROG_LED_PIN_ACTIVE_ON HIGH
        #define PROG_BUTTON_PIN 22
        #define SAVE_INTERRUPT_PIN 20
        #define KNX_SERIAL Serial1
        #define KNX_UART_NUM 0
        #define KNX_UART_RX_PIN 1
        #define KNX_UART_TX_PIN 0
    #endif