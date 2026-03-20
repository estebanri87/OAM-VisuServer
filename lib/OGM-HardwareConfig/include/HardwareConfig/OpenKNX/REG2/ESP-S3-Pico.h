#pragma once
/**
 * OpenKNX Hardware Definition Header File
 *
 * File: REG2-ESP-S3-Pico.h
 * Hardware: REG2-ESP-S3-Pico Based Boards (V1) (NOT TESTED !!!)
 * Responsible: Erkan Çolak
 *
 * Hardware Info visit: https://github.com/OpenKNX/OpenKNX-Pi-Pico-REG2
 *
 * ATTENTION:
 *    Do not include this file directly.
 *    It will be included by the REG2.h file.
 *
 */

#if defined(DEVICE_REG2_ESP_S3_PICO_V1) \
    || defined(DEVICE_REG2_ESP_S3_PICO_V1_DD) \
    || defined(DEVICE_REG2_ESP_S3_PICO_V1_DD_METER) \
    || defined(DEVICE_REG2_ESP_S3_PICO_W_V1) \
    || defined(DEVICE_REG2_ESP_S3_PICO_W_V1_DD_METER) \
    || defined(DEVICE_REG2_ESP_S3_PICO_W_ETH_V1) \
    || defined(DEVICE_REG2_ESP_S3_PICO_W_ETH_V1_DD_METER)
  
    #define PREFIX_ID "REG2-ESP-V1"                // 12 characters
    #define PREFIX_NAME "OpenKNX REG2 ESP-Pico V1" // 24 characters
#endif

// REG2-ESP-S3-Pico V1 (Base)
#if defined(DEVICE_REG2_ESP_S3_PICO_V1)
    #define DEVICE_ID PREFIX_ID ""
    #define DEVICE_NAME PREFIX_NAME ""                 // 24 characters
    #define OKNXHW_REG2_ESPS3PICO_V1_COMMON          // Common pins for all REG2-ESP-S3-Pico V1
    #define OKNXHW_REG2_ESPS3PICO_V1_SAVE_INTERRUPT
    // #define OKNHW_HAS_SERIALLED_COLOR
    // #define OKNXHW_REG2_PIPICO_V1_LED1                   // LED1
    // #define OKNXHW_REG2_PIPICO_V1_LED2   // LED2 ToDo: Set Device Display Front Control LED
    // #define OKNXHW_REG2_PIPICO_V1_LED3   // LED3 ToDo: Set Device Display Front Control LED
    #define OKNXHW_REG2_ESP_USING_APP_BOARD
    #define OKNXHW_REG2_ESPS3PICO_APP_ETH
#endif


// REG2-ESP-S3-Pico V1 (Device Display)
#if defined(OKNXHW_REG2_ESP_S3_PICO_V1_DD)
    #define DEVICE_ID PREFIX_ID "-DD"                // 12 + 8 = 20 characters
    #define DEVICE_NAME PREFIX_NAME " DeviceDisplay" // 24 + 16 = 40 characters
    #define OKNXHW_REG2_ESPS3PICO_V1_COMMON          // Common pins for all REG2-ESP-S3-Pico V1
    #define OKNXHW_REG2_ESPS3PICO_V1_SAVE_INTERRUPT
    #define OKNHW_HAS_SERIALLED_COLOR
    // #define OKNXHW_REG2_PIPICO_V1_LED1                   // LED1
    // #define OKNXHW_REG2_PIPICO_V1_LED2   // LED2 ToDo: Set Device Display Front Control LED
    // #define OKNXHW_REG2_PIPICO_V1_LED3   // LED3 ToDo: Set Device Display Front Control LED
    #define OKNXHW_REG2_ESP_DEVICE_DISPLAY      // Device Display Support
    #define OKNXHW_REG2_ESP_USING_APP_BOARD
    #define OKNXHW_REG2_ESPS3PICO_APP_ETH
#endif

/**
 * Section: Common Hardware (CHW) Pin Definitions
 * REG2-ESP-S3-Pico V1
 */

// REG2-ESP-S3-Pico V1 CHW Pins
#ifdef OKNXHW_REG2_ESPS3PICO_V1_COMMON
    #ifndef OKNHW_HAS_SERIALLED_COLOR
        #define PROG_LED_PIN 13              // ESP32 GPIO13 | PI PICO GPIO2
        #define PROG_LED_PIN_ACTIVE_ON HIGH
    #endif
    
    #define PROG_BUTTON_PIN 4                   // ESP32 GPIO4  | PI PICO GPIO20
    #define PROG_BUTTON_PIN_MODE INPUT_PULLUP   // Using internal pullup of the ESP32 (aprox. 45kOhm)
    #define OPENKNX_BUTTON_DEBOUNCE 0           // Software Debouncer in ms. 0 will Disables software debounce. Since we use the hardware debounce.
    
    #define KNX_SERIAL Serial1                  // Uart0
    #define KNX_UART_NUM 0                      // Uart0
    #define KNX_UART_RX_PIN 12  // ESP32 GPIO12 | PI PICO GPIO1
    #define KNX_UART_TX_PIN 11  // ESP32 GPIO11 | PI PICO GPIO0

    #define NEOPIX_LED_PIN 21   // RGB LED on the ESP32-S3-Pico
    #define NEOPIX_LED_COUNT 1
    #define NEOPIX_LED_TYPE NEO_GRB + NEO_KHZ800 // WS2812B
    #define NEOPIX_LED_ORDER NEO_GRB
    #define NEOPIX_LED_ACTIVE_ON HIGH

    // Application board
    #define REG2_APP_PIN1 42 // ESP32 GPIO42 | PI PICO GPIO16
    #define REG2_APP_PIN2 41 // ESP32 GPIO41 | PI PICO GPIO17
    #define REG2_APP_PIN3 1  // ESP32 GPIO1  | PI PICO GPIO18
    #define REG2_APP_PIN4 7  // ESP32 GPIO7  | PI PICO GPIO26
    #define REG2_APP_PIN5 8  // ESP32 GPIO8  | PI PICO GPIO27
    #define REG2_APP_PIN6 9  // ESP32 GPIO9  | PI PICO GPIO28
    #define REG2_APP_PIN7 2  // ESP32 GPIO2  | PI PICO GPIO19
    // #define REG2_APP_PIN8 GND
    // #define REG2_APP_PIN9 3V3
    // #define REG2_APP_PIN10 5V (VUSB)

    // Application board extended pins
    #define REG2_APP_PIN11 40 // ESP32 GPIO40 | PI PICO GPIO15
    #define REG2_APP_PIN12 39 // ESP32 GPIO39 | PI PICO GPIO14
    #define REG2_APP_PIN13 38 // ESP32 GPIO38 | PI PICO GPIO13
    #define REG2_APP_PIN14 37 // ESP32 GPIO37 | PI PICO GPIO12
    #define REG2_APP_PIN15 36 // ESP32 GPIO36 | PI PICO GPIO11
    #define REG2_APP_PIN16 35 // ESP32 GPIO35 | PI PICO GPIO10
    // #define REG2_APP_PIN17 GND
    // #define REG2_APP_PIN18 EXT_VCC_IN

    // Terminal board
    #define REG2_TERM_PIN10 6 // ESP32 GPIO | PI PICO GPIO22
    #define REG2_TERM_PIN9 34 // ESP32 GPIO | PI PICO GPIO9
    #define REG2_TERM_PIN8 33 // ESP32 GPIO | PI PICO GPIO8
    #define REG2_TERM_PIN7 18 // ESP32 GPIO | PI PICO GPIO7
    #define REG2_TERM_PIN6 17 // ESP32 GPIO | PI PICO GPIO6
    #define REG2_TERM_PIN5 16 // ESP32 GPIO | PI PICO GPIO5
    #define REG2_TERM_PIN4 15 // ESP32 GPIO | PI PICO GPIO4
#endif

#ifdef OKNXHW_REG2_ESPS3PICO_V1_SAVE_INTERRUPT
    #define SAVE_INTERRUPT_PIN 5 // ESP32 GPIO5 | PI PICO GPIO21
#endif

#ifdef OKNHW_HAS_SERIALLED_COLOR
    #define OPENKNX_SERIALLED_COLOR_RED 50, 0, 0
    #define OPENKNX_SERIALLED_COLOR_GREEN 0, 35, 0
    #define OPENKNX_SERIALLED_COLOR_BLUE 0, 0, 63
    #define OPENKNX_SERIALLED_COLOR_YELLOW 40, 30, 0

    #define OPENKNX_SERIALLED_ENABLE
    #define OPENKNX_SERIALLED_PIN NEOPIX_LED_PIN
    #define OPENKNX_SERIALLED_NUM 4 // NEOPIX_LED_COUNT
    #define PROG_LED_PIN 0
    #define PROG_LED_COLOR OPENKNX_SERIALLED_COLOR_RED
    #define INFO1_LED_PIN 1
    #define INFO1_LED_COLOR OPENKNX_SERIALLED_COLOR_GREEN
    #define INFO2_LED_PIN 2
    #define INFO2_LED_COLOR OPENKNX_SERIALLED_COLOR_BLUE
    #define INFO3_LED_PIN 3
    #define INFO3_LED_COLOR OPENKNX_SERIALLED_COLOR_YELLOW
    #define OPENKNX_LEDEFFECT_PULSE_MIN 50
#endif

/**
 * Section: FwF and CHW based Pin Definitions
 * OpenKNX REG2-ESP-S3-Pico
 */

// REG2-ESP-S3-Pico ETH App and FwF
#ifdef OKNXHW_REG2_ESPS3PICO_APP_ETH

    // Thos are the default pins for the W5500 Ethernet module - Required by ETH.h - ETH PHY support.
    #define ETH_PHY_TYPE          ETH_PHY_W5500 // Using our REG2 W5500 Lite
    #define ETH_PHY_ADDR          1             // ??? PHYs I2C address
    #define ETH_PHY_CS            REG2_APP_PIN2 // PIN_ETH_SS
    #define ETH_PHY_IRQ           REG2_APP_PIN5 // PIN_ETH_INT
    #define ETH_PHY_RST           REG2_APP_PIN4 // PIN_ETH_RES
    #define ETH_PHY_SPI_HOST      SPI2_HOST     // SPI2_HOST | SPI3_HOST
    #define ETH_PHY_SPI_SCK       REG2_APP_PIN3 // PIN_ETH_SCK
    #define ETH_PHY_SPI_MISO      REG2_APP_PIN1 // PIN_ETH_MISO
    #define ETH_PHY_SPI_MOSI      REG2_APP_PIN7 // PIN_ETH_MOSI

    #define PIN_ETH_RES ETH_PHY_RST // Additional define for the ETH PHY reset pin for NetworkModule::initPhy()
    /*
     * @brief DEVICE_INIT(): Function for the Ethernet App (Will be initialy called in Common init function)
     * @note This will initialy deaktivate the W5500 lite by setting the RESET pin to LOW!
     *       The NetworkModule::initPhy() will then activate the W5500 lite by setting the RESET pin to HIGH!
    */
    #define DEVICE_INIT() \
      pinMode(ETH_PHY_RST, OUTPUT), \
      digitalWrite(ETH_PHY_RST, LOW);
    //#define OPENKNX_SD_CARD_MODULE_ENABLE       // Enable the SD Card Module Support 
    #define SDCARD_SPI_INTERFACE HSPI           // HSPI or VSPI, depends on the pins (HSPI is SPI2 on ESP32-S3)
    #define PIN_SDCARD_CD (REG2_APP_PIN12)      // Card Detect - GPIO14 SPI1 SCK UART0 CTS I2C1 SDA PWM7_A SIO PIO0 PIO1
    #define PIN_SDCARD_CS (REG2_APP_PIN13)      // Chip Select - GPIO13 SPI1 RX UART0 TX I2C0 SDA PWM6_B SIO PIO0 PIO1
    #define PIN_SDCARD_SCK (REG2_APP_PIN16)     // Clock - GPIO10 SPI1 SCK UART1 CTS I2C1 SDA PWM5_A SIO PIO0 PIO1
    #define PIN_SDCARD_MISO (REG2_APP_PIN14)    // Master In Slave Out - GPIO12 SPI1 RX UART0 TX I2C0 SDA PWM6_A SIO PIO0 PIO1
    #define PIN_SDCARD_MOSI (REG2_APP_PIN15)    // Master Out Slave In - GPIO11 SPI1 TX UART1 RTS I2C1 SCL PWM7_B SIO PIO0 PIO1
#endif

// REG2-ESP-S3-Pico FwF: Device Display Support
#if defined(OKNXHW_REG2_ESP_DEVICE_DISPLAY) || defined(OKNXHW_REG2_ESP_USING_APP_BOARD)
    // Default pins for the I2C bus to connect the hardware display
    #ifdef ARDUINO_ARCH_ESP32
        #define OKNXHW_REG2_HWDISPLAY_I2C_INST Wire1
    #else
        #define OKNXHW_REG2_HWDISPLAY_I2C_INST i2c1 // i2c1 | i2c0
    #endif

    #ifdef OKNXHW_REG2_ESP_USING_APP_BOARD
        #define OKNXHW_REG2_HWDISPLAY_I2C_SDA REG2_TERM_PIN10  // ESP32 GPIO6  | PI PICO GPIO22
        #define OKNXHW_REG2_HWDISPLAY_I2C_SCL REG2_APP_PIN11 // ESP32 GPIO40 | PI PICO GPIO15
    #else
        #define OKNXHW_REG2_HWDISPLAY_I2C_SDA 7 // ESP32 GPIO7 | PICO GPIO26
        #define OKNXHW_REG2_HWDISPLAY_I2C_SCL 8 // ESP32 GPIO8 | PICO GPIO27
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
    #define FRONT_CTRL_LEFT2  0x103   // PIN 3 (LEFT2) !!
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

    #define OPENKNX_GPIO_NUM    1
    #define OPENKNX_GPIO_TYPES  OPENKNX_GPIO_T_PCA9557
    #define OPENKNX_GPIO_ADDRS  0x18      // PCA9557 I2C address 0x18 (A0-A2 = 0) A0-A2 are connected to GND if A1 is connected to VCC the address is 0x19
    #define OPENKNX_GPIO_INTS   0xFF
    #define OPENKNX_GPIO_WIRE   OKNXHW_REG2_HWDISPLAY_I2C_INST  // Must be the same as OKNXHW_REG2_HWDISPLAY_I2C_INST
    #define OPENKNX_GPIO_CLOCK  400000    // I2C Taktfrequenz in Hz (400kHz für schnelle I2C-Kommunikation)

    #define OKNXHW_DEVICE_DISPLAY_I2C_INST    OKNXHW_REG2_HWDISPLAY_I2C_INST
    #define OKNXHW_DEVICE_DISPLAY_I2C_SDA     OKNXHW_REG2_HWDISPLAY_I2C_SDA
    #define OKNXHW_DEVICE_DISPLAY_I2C_SCL     OKNXHW_REG2_HWDISPLAY_I2C_SCL
    #define OKNXHW_DEVICE_DISPLAY_I2C_ADDRESS OKNXHW_REG2_HWDISPLAY_I2C_ADDRESS
    #define OKNXHW_DEVICE_DISPLAY_WIDTH       OKNXHW_REG2_DEVICE_DISPLAY_WIDTH
    #define OKNXHW_DEVICE_DISPLAY_HEIGHT      OKNXHW_REG2_DEVICE_DISPLAY_HEIGHT

#endif // REG2-ESP-S3-Pico FwF: Device Display Support


// pio board definition for the Waveshare ESP-S3-Pico
/*
[custom_board_ws_esp32s2_pico] // Waveshare ESP32-S2 Pico
platform = espressif32
framework = arduino
board_build.memory_type = qio_opi
board_build.f_cpu = 240000000L
board_build.f_flash = 80000000L
board_build.flash_mode = dio ;qio
board_build.flash_freq = 80m
board_build.flash_size = 16MB
board_build.hwids = [["0x303A", "0x1001"]]
board_build.mcu = esp32s3
board_build.variant = ESP32S3
board_build.extra_flags =
    -D ARDUINO_WAVESHARE_ESP32S3
    -D BOARD_HAS_PSRAM
    -D ARDUINO_USB_CDC_ON_BOOT=0 ; 0 (disabled) so the OPenKNX console is disturbed by the USB-CDC
                                 ; 0 (disabled) → USB-CDC is not activated as a serial port during boot
                                 ; 1 (enabled) → ESP32-S3 pico's virtual COM port (no external USB-UART adapter needed)
    -D ARDUINO_RUNNING_CORE=1
    -D ARDUINO_EVENT_RUNNING_CORE=1
    -D ARDUINO_USB_MODE=1
;   -U BOARD_HAS_PSRAM                    ; Disable PSRAM
;   -D CONFIG_SPIRAM_SUPPORT=0            ; Disable SPIRAM
;   -D CONFIG_SPI_MASTER_IN_IRAM=0        ; Disable SPI Master in IRAM
;   -D CONFIG_SPI_SLAVE_IN_IRAM=0         ; Disable SPI Slave in IRAM
;   -D CONFIG_SPI_FLASH_SHARE_SPI1_BUS=0  ; Disable SPI Flash share SPI1 bus
;   -D CONFIG_SPI_MASTER_IN_IRAM=0        ; Disable SPI Master in IRAM
;   -D CONFIG_SPI_SLAVE_IN_IRAM=0         ; Disable SPI Slave in IRAM
;   -D CONFIG_SPI_FLASH_SHARE_SPI1_BUS=0  ; Disable SPI Flash share SPI1 bus
;   -D CONFIG_ESP_CONSOLE_USB_SERIAL=0    ; Disable USB Serial Console
;   -D CONFIG_ESP_CONSOLE_UART_NONE=1     ; Disable UART Console
;   -D CONFIG_JTAG_ENABLE_ESP32S3=0       ; Disable JTAG
;   -D CONFIG_ESP32S3_DEFAULT_CPU_FREQ_240=1 ; Set CPU frequency to 240MHz
;   -D CONFIG_ESP32S3_DEFAULT_CPU_FREQ_160=0 ; Set CPU frequency to 160MHz
;   -D CONFIG_ESP32S3_DEFAULT_CPU_FREQ_80=0  ; Set CPU frequency to 80MHz
;   -D CONFIG_ESP32S3_DEFAULT_CPU_FREQ_40=0  ; Set CPU frequency to 40MHz
;debug_port = /dev/cu.usbmodem84201
;upload_port = /dev/cu.usbmodem84201
;monitor_port = /dev/cu.usbmodem57640270261
;debug_tool = esp32s3-builtin
upload_speed = 921600
monitor_speed = 115200
*/

/*
Mapping PiPico to ESP-S3-Pico
GPIO0  -> GPIO11        GPIO16 -> GPIO42
GPIO1  -> GPIO12        GPIO17 -> GPIO41
GPIO2  -> GPIO13        GPIO18 -> GPIO1
GPIO3  -> GPIO14        GPIO19 -> GPIO2
GPIO4  -> GPIO15        GPIO20 -> GPIO4
GPIO5  -> GPIO16        GPIO21 -> GPIO5
GPIO6  -> GPIO17        GPIO22 -> GPIO6
GPIO7  -> GPIO18        RUN    -> RUN
GPIO8  -> GPIO33        GPIO26 -> GPIO7
GPIO9  -> GPIO34        GPIO27 -> GPIO8
GPIO10 -> GPIO35        GPIO28 -> GPIO9
GPIO11 -> GPIO36        ADC_VREF -> GPIO10
GPIO12 -> GPIO37        3V3    -> 3V3
GPIO13 -> GPIO38        3v3_EN -> 3v3_EN
GPIO14 -> GPIO39        GND    -> GND
GPIO15 -> GPIO40        VSYS   -> VSYS
                        VBUS   -> VBUS
*/

/*
REG2-ESP-S3-Pico GPIO Pinout and Features

 PiPico    | ESP Pin| Digital I/O | PWM | ADC | I2C  | SPI  | UART  | Special Features          | Debugging (JTAG)
 ----------| -------|-------------|-----|-----|------|------|-------|-------------------------- |-----------------
(GPIO0   ) | GPIO11 | Yes         | Yes | No  | I2C0 | SPI2 | UART0 | -                         | -
(GPIO1   ) | GPIO12 | Yes         | Yes | No  | I2C0 | SPI2 | UART0 | -                         | -
(GPIO2   ) | GPIO13 | Yes         | Yes | No  | I2C0 | SPI2 | UART0 | -                         | -
(GPIO3   ) | GPIO14 | Yes         | Yes | No  | I2C0 | SPI2 | UART0 | -                         | -
(GPIO4   ) | GPIO15 | Yes         | Yes | No  | I2C0 | SPI2 | UART0 | -                         | -
(GPIO5   ) | GPIO16 | Yes         | Yes | No  | I2C1 | SPI3 | UART1 | -                         | -
(GPIO6   ) | GPIO17 | Yes         | Yes | No  | I2C1 | SPI3 | UART1 | -                         | -
(GPIO7   ) | GPIO18 | Yes         | Yes | No  | I2C1 | SPI3 | UART1 | -                         | -
(GPIO8   ) | GPIO33 | Yes         | No  | Yes | No   | No   | No    | ADC1 Channel (Input only) | -
(GPIO9   ) | GPIO34 | Yes         | No  | Yes | No   | No   | No    | ADC1 Channel (Input only) | -
(GPIO10  ) | GPIO35 | Yes (Input) | No  | Yes | No   | No   | No    | ADC1 Channel (Input only) | -
(GPIO11  ) | GPIO36 | Yes         | No  | Yes | No   | No   | No    | ADC1 Channel              | -
(GPIO12  ) | GPIO37 | Yes (Input) | No  | Yes | No   | No   | No    | ADC1 Channel (Input only) | -
(GPIO13  ) | GPIO38 | Yes (Input) | No  | Yes | No   | No   | No    | ADC1 Channel (Input only) |
(GPIO14  ) | GPIO39 | Yes (Input) | No  | Yes | No   | No   | No    | ADC1 Channel (Input only) | JTAG-TCK (Test Clock)
(GPIO15  ) | GPIO40 | Yes         | Yes | No  | No   | No   | No    | -                         | JTAG-TDO (Test Data Out)
(GPIO16  ) | GPIO42 | Yes         | Yes | No  | No   | No   | No    | -                         | JTAG TMS (Test Mode Select)
(GPIO17  ) | GPIO41 | Yes         | Yes | No  | No   | No   | No    | -                         | JTAG TDI (Test Data In)
(GPIO18  ) | GPIO1  | Yes         | Yes | No  | I2C0 | SPI2 | UART0 | -                         | -
(GPIO19  ) | GPIO2  | Yes         | Yes | No  | I2C0 | SPI2 | UART0 | -                         | -
(GPIO20  ) | GPIO4  | Yes         | Yes | No  | I2C0 | SPI2 | UART0 | -                         | -
(GPIO21  ) | GPIO5  | Yes         | Yes | No  | I2C0 | SPI2 | UART0 | -                         | -
(GPIO22  ) | GPIO6  | Yes         | Yes | No  | I2C0 | SPI2 | UART0 | -                         | -
(RUN     ) | RUN    | -           | -   | -   | -    | -    | -     | System reset pin          | -
(GPIO26  ) | GPIO7  | Yes         | Yes | No  | I2C0 | SPI2 | UART0 | -                         | -
(GPIO27  ) | GPIO8  | Yes         | Yes | No  | I2C0 | SPI2 | UART0 | -                         | -
(GPIO28  ) | GPIO9  | Yes         | Yes | No  | I2C0 | SPI2 | UART0 | -                         | -
(ADC_VREF) | GPIO10 | Yes         | Yes | No  | I2C0 | SPI2 | UART0 | -                         | -
*/