#pragma once

// see `wear_leveling_rp2040_flash_config.h`
// currently, using 16MB SPI flash
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 8192

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET               // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25      // Specify a optional status led by GPIO number which blinks when entering the bootloader

#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3

#define ENCODER_A_PINS {NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN}
#define ENCODER_B_PINS {NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN}
#define ENCODER_RESOLUTIONS {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}

#define TRACKBALL_TIMEOUT (5 * 60 * 1000) // 5 mins
