#pragma once
/**
 * Smart-MF OpenKNX ready Hardware definition header file
 *
 * File: Devices.h
 * Hardware: OpenKNX Miscellanous Hardware
 * Responsible: Smart-MF
 *
 * Defines hardware IO pins and functionalities for the Smart-MF Hardware.
 * Includes pin assignments for LEDs, buttons, serial communication, and other peripherals.
 *
 *
 * More info about the Hardware visit: https://www.OpenKNX.de  https://www.Smart-Mf.de
 *
 * ATTENTION:
 *    Do not include this file directly.
 *    It will be included by the HardwareConfig.h file.
 */

/************************************************** */
//  SOM
/************************************************** */
#ifdef DEVICE_SMARTMF_SOM_UP
    #define DEVICE_ID "SOM-UP"
    #define DEVICE_NAME "Smart-MF Soundmodul UP"

    #define SOM_BASE

    #define OPENKNX_BI_GPIO_PINS 4, 5, 19, 18
    #define OPENKNX_BI_GPIO_COUNT 4
    #define OPENKNX_BI_PULSE 14
#endif

#ifdef DEVICE_SMARTMF_SOM_UP_EXT_PWR
    #define DEVICE_ID "SOM-UP-EXT-PWR"
    #define DEVICE_NAME "Smart-MF Soundmodul UP (Ext-Power)"

    #define SOM_BASE
#endif

#ifdef DEVICE_SMARTMF_SOM_REG
    #define DEVICE_ID "SOM-UP-REG"
    #define DEVICE_NAME "Smart-MF Soundmodul REG"

    #define SOM_BASE
#endif

#ifdef SOM_BASE
    #define PROG_LED_PIN 2
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define INFO1_LED_PIN 29
    #define INFO1_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 0
    #define FUNC1_BUTTON_PIN 1
    #define SAVE_INTERRUPT_PIN 13
    #define KNX_UART_NUM 0
    #define KNX_UART_RX_PIN 17
    #define KNX_UART_TX_PIN 16
    #define PLAYER_UART_RX_PIN 9
    #define PLAYER_UART_TX_PIN 8
    #define PLAYER_I2S_MCLK_PIN -1
    #define PLAYER_I2S_BCLK_PIN 8
    #define PLAYER_I2S_DATA_PIN 20
    #define PLAYER_POWER_PIN 3

    #define SmartMF_HardwareRevision_PIN1 10
    #define SmartMF_HardwareRevision_PIN2 11
    #define SmartMF_HardwareRevision_PIN3 12
#endif

/************************************************** */
//  REG 1TE
/************************************************** */

// Smart-MF 1TE 3x Binary Inputs
#ifdef DEVICE_SMARTMF_1TE_BE_3CH
    #define DEVICE_ID "SMARTMF-1TE-BE-3CH"
    #define DEVICE_NAME "Smart-MF S0-Zählermodul"

    #define SMARTMF_HARDWARE_VARIANT_PIN 26
    #define SMARTMF_HARDWARE_REVISION_ID1_PIN 10
    #define SMARTMF_HARDWARE_REVISION_ID2_PIN 11
    #define SMARTMF_HARDWARE_REVISION_ID3_PIN 12

    #define PROG_LED_PIN 1
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 0
    #define SAVE_INTERRUPT_PIN 29
    #define KNX_UART_RX_PIN 17
    #define KNX_UART_TX_PIN 16
    #define KNX_UART_NUM 0

    #define SMARTMF_BE1_PIN 14
    #define SMARTMF_BE2_PIN 15
    #define SMARTMF_BE3_PIN 4

    #define SMARTMF_BE_VCC_PIN 5
#endif

// Smart-MF Logikmopdul
#ifdef DEVICE_SMARTMF_1TE_REG
    #define DEVICE_SMARTMF_1TE_REG_BASE

    #define DEVICE_ID "SMARTMF-1TE-REG"
    #define DEVICE_NAME "Smart-MF 1TE REG"
#endif

// Smart-MF 1-Wire Gateway 1TE
#ifdef DEVICE_SMARTMF_1WIRE_1CH
    #define DEVICE_SMARTMF_1TE_REG_BASE

    #define DEVICE_ID "SMARTMF-1Wire-1CH"
    #define DEVICE_NAME "Smart-MF 1-Wire Gateway 1CH"

    #define I2C_WIRE Wire
    #define I2C_SDA_PIN 20
    #define I2C_SCL_PIN 21
    #define I2C_SDA_1WIRE_PIN 14
    #define I2C_SCL_1WIRE_PIN 15
    #define COUNT_1WIRE_BUSMASTER 1
    #define COUNT_1WIRE_CHANNEL 30
    #define I2C_1WIRE_DEVICE_ADDRESSS 0x18 // Address of DS2484 1-Wire-Busmaster chip
    #define I2C_BUS_1WIRE Wire1
    #define ONEWIRE_5V_ENABLE 5
    #define ONEWIRE_5V_SHORT 4

#endif

// Smart-MF Modbus 1TE
#ifdef DEVICE_SMARTMF_1TE_MODBUS
    #define DEVICE_SMARTMF_1TE_REG_BASE

    #define DEVICE_ID "SMARTMF-1TE-MODBUS"
    #define DEVICE_NAME "Smart-MF 1TE Modbus RTU"

    #define SMARTMF_LED 15

    #define SMARTMF_MODBUS_RX_PIN 5
    #define SMARTMF_MODBUS_TX_PIN 4
    #define SMARTMF_MODBUS_DIR_PIN 14

    #define SMARTMF_HARDWARE_VARIANT_PIN 26
    #define SMARTMF_HARDWARE_REVISION_ID1_PIN 10
    #define SMARTMF_HARDWARE_REVISION_ID2_PIN 11
    #define SMARTMF_HARDWARE_REVISION_ID3_PIN 12

#endif

// Smart-MF Logikmopdul
#ifdef DEVICE_SMARTMF_1TE_REG_BASE

    #define PROG_LED_PIN 1
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 0
    #define SAVE_INTERRUPT_PIN 29
    #define KNX_UART_RX_PIN 17
    #define KNX_UART_TX_PIN 16
    #define KNX_UART_NUM 0

#endif

/************************************************** */
//  REG 2TE
/************************************************** */

// Smart-MF 1-Wire Gateway 3CH
#ifdef DEVICE_SMARTMF_1WIRE_3CH
    #define DEVICE_ID "SMARTMF-1Wire-3CH"
    #define DEVICE_NAME "Smart-MF 1-Wire Gateway 3CH"

    #define SMARTMF_HARDWARE_REVISION_ID1_PIN 2
    #define SMARTMF_HARDWARE_REVISION_ID2_PIN 3
    #define SMARTMF_HARDWARE_REVISION_ID3_PIN 15

    #define PROG_LED_PIN 11
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 14
    #define SAVE_INTERRUPT_PIN 8
    #define KNX_UART_NUM 0
    #define KNX_UART_RX_PIN 1
    #define KNX_UART_TX_PIN 0

    #define SMARTMF_CH1_I2C1_SDA_PIN 6
    #define SMARTMF_CH1_I2C1_SCL_PIN 7

    #define SMARTMF_CH2_I2C0_SDA_PIN 24
    #define SMARTMF_CH2_I2C0_SCL_PIN 25

    #define SMARTMF_CH3_I2C1_SDA_PIN 22
    #define SMARTMF_CH3_I2C1_SCL_PIN 23
#endif

// Smart-MF SML Reader (2x SML + 3x BIN)
#ifdef DEVICE_SMARTMF_2SML_3BE
    #define DEVICE_ID "SMARTMF-2SML-3BE"
    #define DEVICE_NAME "Smart-MF eHZ Schnittstelle"

    #define SMARTMF_HARDWARE_REVISION_ID1_PIN 2
    #define SMARTMF_HARDWARE_REVISION_ID2_PIN 3
    #define SMARTMF_HARDWARE_REVISION_ID3_PIN 15

    #define PROG_LED_PIN 11
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 14
    #define SAVE_INTERRUPT_PIN 8
    #define KNX_UART_NUM 0
    #define KNX_UART_RX_PIN 1
    #define KNX_UART_TX_PIN 0

    #define SMARTMF_BE1_PIN 26
    #define SMARTMF_BE2_PIN 27
    #define SMARTMF_BE3_PIN 29

    #define SMARTMF_SML_PWR_PIN 25
    #define SMARTMF_SML_PWR_FAULT_PIN 24

    #define SMARTMF_SML1_RX_PIN 5
    #define SMARTMF_SML1_TX_PIN 4

    #define SMARTMF_SML2_RX_PIN 23
    #define SMARTMF_SML2_TX_PIN 22
#endif

// Smart-MF Modbus Gateway + 3x BIN
#ifdef DEVICE_SMARTMF_MODBUS_RTU_3BE
    #define DEVICE_ID "SMARTMF-Modbus-RTU-3BE"
    #define DEVICE_NAME "Smart-MF Modbus-RTU Gateway"

    #define SMARTMF_HARDWARE_REVISION_ID1_PIN 2
    #define SMARTMF_HARDWARE_REVISION_ID2_PIN 3
    #define SMARTMF_HARDWARE_REVISION_ID3_PIN 15

    #define PROG_LED_PIN 11
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 14
    #define SAVE_INTERRUPT_PIN 8
    #define KNX_UART_NUM 0
    #define KNX_UART_RX_PIN 1
    #define KNX_UART_TX_PIN 0

    #define SMARTMF_BE1_PIN 25
    #define SMARTMF_BE2_PIN 27
    #define SMARTMF_BE3_PIN 26

    #define SMARTMF_MODBUS_RX_PIN 5
    #define SMARTMF_MODBUS_TX_PIN 4
    #define SMARTMF_MODBUS_DIR_PIN 24
#endif

// Smart-MF Wetterstation Gateway
#ifdef DEVICE_SMARTMF_ECOWITT_WN90LP
    #define DEVICE_ID "SMARTMF-WN90LP"
    #define DEVICE_NAME "Smart-MF Ecowitt WN90LP"

    #define SMARTMF_HARDWARE_REVISION_ID1_PIN 2
    #define SMARTMF_HARDWARE_REVISION_ID2_PIN 3
    #define SMARTMF_HARDWARE_REVISION_ID3_PIN 15

    #define PROG_LED_PIN 11
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 14
    #define SAVE_INTERRUPT_PIN 8
    #define KNX_UART_NUM 0
    #define KNX_UART_RX_PIN 1
    #define KNX_UART_TX_PIN 0

    #define SMARTMF_BE1_PIN 25
    #define SMARTMF_BE2_PIN 27
    #define SMARTMF_BE3_PIN 26

    #define RS485_SERIAL Serial2
    #define RS485_UART_RX_PIN (5)
    #define RS485_UART_TX_PIN (4)
    #define RS485_UART_DIR_PIN (24)

#endif

/************************************************** */
//   Sensormodul
/************************************************** */

// Smart-MF Sensormodul
#ifdef DEVICE_SMARTMF_SENSORMODUL
    #define DEVICE_ID "SMARTMF-SEN-V4"
    #define DEVICE_NAME "Smart-MF Sensormodul V4"

    #define SMARTMF_HARDWARE_REVISION_ID1_PIN 10
    #define SMARTMF_HARDWARE_REVISION_ID2_PIN 11
    #define SMARTMF_HARDWARE_REVISION_ID3_PIN 12
    #define SMARTMF_HARDWARE_REVISION_ID4_PIN 23

    #define SMARTMF_HARDWARE_REVISION_ADC_PIN 26

    #define PROG_LED_PIN 1
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 0
    #define SAVE_INTERRUPT_PIN 29
    #define KNX_UART_NUM 0
    #define KNX_UART_RX_PIN 17
    #define KNX_UART_TX_PIN 16

    #define SMARTMF_BE1_PIN 2
    #define SMARTMF_BE2_PIN 4
    #define SMARTMF_BE3_PIN 6
    #define SMARTMF_BE4_PIN 7

    #define SMARTMF_I2C0_SDA_PIN 20
    #define SMARTMF_I2C0_SCL_PIN 21

    #define SMARTMF_I2C1_SDA_PIN 14
    #define SMARTMF_I2C1_SCL_PIN 15

    #define SMARTMF_BUZZER_PIN 27

    // definitions for legacy support
    #define I2C_RGBLED_DEVICE_ADDRESS 0x60 // Address of PCA9632 RGBW-LED-Driver
    #define I2C_WIRE Wire
    #define I2C_SDA_PIN SMARTMF_I2C0_SDA_PIN
    #define I2C_SCL_PIN SMARTMF_I2C0_SCL_PIN
    #define COUNT_1WIRE_BUSMASTER 1
    #define COUNT_1WIRE_CHANNEL 30
    #define I2C_1WIRE_DEVICE_ADDRESSS 0x18 // Address of DS2484 1-Wire-Busmaster chip
    #define I2C_BUS_1WIRE Wire1
    #define I2C_SDA_1WIRE_PIN SMARTMF_I2C1_SDA_PIN
    #define I2C_SCL_1WIRE_PIN SMARTMF_I2C1_SCL_PIN
    #define ONEWIRE_5V_ENABLE 8
    #define ONEWIRE_5V_SHORT 9
    #define BUZZER_PIN SMARTMF_BUZZER_PIN
    #define HW_ANALOG_ID SMARTMF_HARDWARE_REVISION_ADC_PIN
    #define HW_REVISION_ID1 SMARTMF_HARDWARE_REVISION_ID1_PIN
    #define HW_REVISION_ID2 SMARTMF_HARDWARE_REVISION_ID2_PIN
    #define HW_REVISION_ID3 SMARTMF_HARDWARE_REVISION_ID3_PIN
    #define OPENKNX_BI_GPIO_PINS SMARTMF_BE1_PIN, SMARTMF_BE2_PIN, SMARTMF_BE3_PIN, SMARTMF_BE4_PIN
    #define OPENKNX_BI_GPIO_COUNT 4
    #define OPENKNX_ADC_ADS_ADDR 0x49
    #define OPENKNX_ADC_ADS_GAIN 2
    #define OPENKNX_ADC_ADS_WIRE I2C_BUS_1WIRE
    #define OPENKNX_ADC_ADS_SDA I2C_SDA_1WIRE_PIN
    #define OPENKNX_ADC_ADS_SCL I2C_SCL_1WIRE_PIN

#endif

// Smart-MF GardenControl
#ifdef DEVICE_SMARTMF_GARDENCONTROL
    #define DEVICE_ID "SMARTMF-GC"
    #define DEVICE_NAME "Smart-MF GardenControl"

    #define PROG_LED_PIN 24
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 25
    #define SAVE_INTERRUPT_PIN 23
    #define KNX_UART_RX_PIN 17
    #define KNX_UART_TX_PIN 16
    #define KNX_UART_NUM 0

#endif

/************************************************** */
//   Smart-MF Modbus Gehäuse Außen
/************************************************** */
#ifdef DEVICE_SMARTMF_MODBUS_AUSSEN
    #define DEVICE_ID "SMARTMF-Modbus-Aussen"
    #define DEVICE_NAME "Smart-MF Modbus RTU Aussen"

    #define PROG_LED_PIN 1
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 0
    #define SAVE_INTERRUPT_PIN 29
    #define KNX_UART_RX_PIN 17
    #define KNX_UART_TX_PIN 16
    #define KNX_UART_NUM 0

    #define SMARTMF_LED 15
    #define SMARTMF_MODBUS_RX_PIN 5
    #define SMARTMF_MODBUS_TX_PIN 4
    #define SMARTMF_MODBUS_DIR_PIN 14

    #define SMARTMF_HARDWARE_VARIANT_PIN 26
    #define SMARTMF_HARDWARE_REVISION_ID1_PIN 10
    #define SMARTMF_HARDWARE_REVISION_ID2_PIN 11
    #define SMARTMF_HARDWARE_REVISION_ID3_PIN 12
#endif

/************************************************** */
//   Smart-MF Enocean Gateway V2 RP2040
/************************************************** */
#ifdef DEVICE_SMARTMF_ENOCEANGATEWAY_V2
    #define DEVICE_ID "SMARTMF-ENO"
    #define DEVICE_NAME "Smart-MF Enocean Gateway V2"
    #define PROG_LED_PIN 1
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define INFO_LED_PIN 7
    #define INFO_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 0
    #define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
    #define SAVE_INTERRUPT_PIN 29
    #define KNX_UART_RX_PIN 17
    #define KNX_UART_TX_PIN 16
    #define KNX_UART_NUM 0

    #define OPENKNX_ENO_SERIAL Serial2
    #define OPENKNX_ENO_UART_RX_PIN 5
    #define OPENKNX_ENO_UART_TX_PIN 4
#endif

// Smart-MF Tasterinterface
#ifdef DEVICE_SMARTMF_TASTERINTERFACE
    #define DEVICE_ID "SMARTMF-Taster"
    #define DEVICE_NAME "Smart-MF Tasterinterface"

#endif

// Smart-MF RealPresence 2.0 (HLK)
#ifdef DEVICE_SMARTMF_REALPRESENCE_V2
    #define DEVICE_ID "SMARTMF-RP-V2"
    #define DEVICE_NAME "Smart-MF RealPresence 2.0"

    #define PROG_LED_PIN 18
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 17
    #define INFO_LED_PIN 16
    #define INFO_LED_PIN_ACTIVE_ON HIGH
    #define PRESENCE_LED_PIN 1
    #define PRESENCE_LED_PIN_ACTIVE_ON HIGH
    #define MOVE_LED_PIN 0
    #define MOVE_LED_PIN_ACTIVE_ON HIGH
    #define KNX_UART_NUM 0
    #define KNX_UART_TX_PIN 12
    #define KNX_UART_RX_PIN 13
    #define SAVE_INTERRUPT_PIN 11
    #define I2C_WIRE Wire1
    #define I2C_SDA_PIN 26
    #define I2C_SCL_PIN 27
    #define HF_SERIAL Serial2
    #define HF_SERIAL_SPEED 115200
    #define HF_POWER_PIN 28
    #define HF_UART_TX_PIN 4
    #define HF_UART_RX_PIN 5

#endif