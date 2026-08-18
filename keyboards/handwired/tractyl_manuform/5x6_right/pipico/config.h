#pragma once

// --- Half-Duplex Split Configuration (Single Wire over PIO) ---
// This completely ignores GP0 and handles all RX/TX traffic over GP1
// #define SOFT_SERIAL_PIN         GP1

// Handshake & Handedness
#define SPLIT_WATCHDOG_ENABLE
#define EE_HANDS
#define SPLIT_USB_DETECT

// --- SPI Hardware Configuration ---
#define SPI_SCK_PIN         GP10
#define SPI_MOSI_PIN        GP11
#define SPI_MISO_PIN        GP12
#define PMW3360_CS_PIN      GP13
#define POINTING_DEVICE_CS_PIN GP13

// Tell QMK to use the newly enabled SPI1 block
#define SPI_DRIVER          SPID1

// --- Sensor Axis Rotations ---
#define PMW3360_INVERT_X
#define PMW3360_INVERT_Y
// #define POINTING_DEVICE_ROTATION_90

#define VIA_DYNAMIC_KEYMAP_ENABLE
#define VIA_EEPROM_LAYOUT_OPTIONS_ENABLE

#define USB_ENDPOINT_COUNT 4