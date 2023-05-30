#pragma once

/* key matrix */
#define MATRIX_ROWS 10
#define MATRIX_COLS 7
#define MATRIX_ROW_PINS { B15, B14, B13, B12, A14 }
#define MATRIX_COL_PINS { A8, C9, C8, C7, C6, C13, C14 }
#define MATRIX_ROW_PINS_RIGHT { B13, B14, B15, C6, C7 }
#define MATRIX_COL_PINS_RIGHT { B4, B3, D2, A8, C9, C8, B12 }
#define DIODE_DIRECTION COL2ROW

/* bootmagic lite keys */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 5
#define BOOTMAGIC_LITE_COLUMN_RIGHT 6

/* use 1000hz polling */
#define USB_POLLING_INTERVAL_MS 1

/* set handedness in eeprom */
#define EE_HANDS

/* split communication using serial USART */
#define SERIAL_USART_FULL_DUPLEX   
#define SERIAL_USART_TX_PIN A9    
#define SERIAL_USART_RX_PIN A10   
#define SELECT_SOFT_SERIAL_SPEED 1 // or 0, 2, 3, 4, 5
                                   //  0: 460800 baud
                                   //  1: 230400 baud (default)
                                   //  2: 115200 baud
                                   //  3: 57600 baud
                                   //  4: 38400 baud
                                   //  5: 19200 baud
#define SERIAL_USART_DRIVER SD1    
#define SERIAL_USART_TX_PAL_MODE 7 
#define SERIAL_USART_RX_PAL_MODE 7 
#define SERIAL_USART_TIMEOUT 20   

/* OLED */
#ifdef OLED_ENABLE
#define I2C1_SCL_PIN        B6
#define I2C1_SDA_PIN        B7
#define OLED_BRIGHTNESS 8 // 128 default?
#define OLED_TIMEOUT 500 // ms
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#endif

/* fix STM32 bootloader (no need to use reset jumper) */
#ifndef EARLY_INIT_PERFORM_BOOTLOADER_JUMP
#    define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE
#endif

/* fix USB timeout issues */
// #define SPLIT_USB_TIMEOUT 5000 // 2000 is default
// #define SPLIT_USB_TIMEOUT_POLL 100 // 10 is default
// #define USB_SUSPEND_WAKEUP_DELAY 200 // 0 is default
#define SPLIT_WATCHDOG_ENABLE
// #define SPLIT_WATCHDOG_TIMEOUT 3000

/* typing options */
/* caps word */
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 2000  // 5000 default
/* one shot keys */
#define ONESHOT_TAP_TOGGLE 5  // Tapping this number of times holds the key until tapped once again
#define ONESHOT_TIMEOUT 2000 // 5000 default
/* tapping toggle */
#define TAPPING_TOGGLE 5 // 5 default
/* tapping settings */
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

// WEAR LEVEL BABY
#define FEE_PAGE_SIZE 0x4000
#define FEE_PAGE_COUNT 1
#define FEE_MCU_FLASH_SIZE 512
#define FEE_PAGE_BASE_ADDRESS 0x08004000
#define WEAR_LEVELING_LEGACY_EMULATION_PAGE_SIZE 16384
#define WEAR_LEVELING_LEGACY_EMULATION_PAGE_COUNT 4
#define WEAR_LEVELING_LEGACY_EMULATION_BASE_PAGE_ADDRESS (WEAR_LEVELING_LEGACY_EMULATION_FLASH_BASE + (1 * (WEAR_LEVELING_LEGACY_EMULATION_PAGE_SIZE))) // +16k
#define WEAR_LEVELING_BACKING_SIZE 65536
#define WEAR_LEVELING_LOGICAL_SIZE 4096

//#define USB_SUSPEND_WAKEUP_DELAY 200
