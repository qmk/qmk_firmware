/*
 *  Copyright (C) 2021  System76
 *  Copyright (C) 2021  Jimmy Cassis <KernelOops@outlook.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <string.h>

#include "dynamic_keymap.h"
#include "raw_hid.h"
#include "rgb_matrix.h"
#include "version.h"
#include "keyboard.h"
#include "eeprom.h"
#include "matrix.h"
#include "action_layer.h"
#include "bootloader.h"
#include "wait.h"

enum Command {
    CMD_PROBE         = 1,   // Probe for System76 EC protocol
    CMD_BOARD         = 2,   // Read board string
    CMD_VERSION       = 3,   // Read version string
    CMD_RESET         = 6,   // Reset to bootloader
    CMD_KEYMAP_GET    = 9,   // Get keyboard map index
    CMD_KEYMAP_SET    = 10,  // Set keyboard map index
    CMD_LED_GET_VALUE = 11,  // Get LED value by index
    CMD_LED_SET_VALUE = 12,  // Set LED value by index
    CMD_LED_GET_COLOR = 13,  // Get LED color by index
    CMD_LED_SET_COLOR = 14,  // Set LED color by index
    CMD_LED_GET_MODE  = 15,  // Get LED matrix mode and speed
    CMD_LED_SET_MODE  = 16,  // Set LED matrix mode and speed
    CMD_MATRIX_GET    = 17,  // Get currently pressed keys
    CMD_LED_SAVE      = 18,  // Save LED settings to ROM
    CMD_SET_NO_INPUT  = 19,  // Enable/disable no input mode
};

bool input_disabled = false;

#define CMD_LED_INDEX_ALL 0xFF

static bool keymap_get(uint8_t layer, uint8_t output, uint8_t input, uint16_t *value) {
    if (layer < dynamic_keymap_get_layer_count()) {
        if (output < MATRIX_ROWS) {
            if (input < MATRIX_COLS) {
                *value = dynamic_keymap_get_keycode(layer, output, input);
                return true;
            }
        }
    }
    return false;
}

static bool keymap_set(uint8_t layer, uint8_t output, uint8_t input, uint16_t value) {
    if (layer < dynamic_keymap_get_layer_count()) {
        if (output < MATRIX_ROWS) {
            if (input < MATRIX_COLS) {
                dynamic_keymap_set_keycode(layer, output, input, value);
                return true;
            }
        }
    }
    return false;
}

static bool bootloader_reset    = false;
static bool bootloader_unlocked = false;

void system76_ec_unlock(void) {
#ifdef RGB_MATRIX_CUSTOM_KB
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_unlocked);
#endif
#ifdef SYSTEM76_EC
    bootloader_unlocked = true;
#endif
}

bool system76_ec_is_unlocked(void) { return bootloader_unlocked; }

#ifdef RGB_MATRIX_CUSTOM_KB
enum Mode {
    MODE_SOLID_COLOR = 0,
    MODE_PER_KEY,
    #ifndef DISABLE_RGB_MATRIX_ANIMATIONS
    MODE_CYCLE_ALL,
    MODE_CYCLE_LEFT_RIGHT,
    MODE_CYCLE_UP_DOWN,
    MODE_CYCLE_OUT_IN,
    MODE_CYCLE_OUT_IN_DUAL,
    MODE_RAINBOW_MOVING_CHEVRON,
    MODE_CYCLE_PINWHEEL,
    MODE_CYCLE_SPIRAL,
    MODE_RAINDROPS,
    MODE_SPLASH,
    MODE_MULTISPLASH,
    #endif  // DISABLE_RGB_MATRIX_ANIMATIONS
    MODE_ACTIVE_KEYS,
    MODE_DISABLED,
    MODE_LAST,
};

// clang-format off
static enum rgb_matrix_effects mode_map[] = {
    RGB_MATRIX_SOLID_COLOR,
    RGB_MATRIX_CUSTOM_raw_rgb,
    #ifndef DISABLE_RGB_MATRIX_ANIMATIONS
    RGB_MATRIX_CYCLE_ALL,
    RGB_MATRIX_CYCLE_LEFT_RIGHT,
    RGB_MATRIX_CYCLE_UP_DOWN,
    RGB_MATRIX_CYCLE_OUT_IN,
    RGB_MATRIX_CYCLE_OUT_IN_DUAL,
    RGB_MATRIX_RAINBOW_MOVING_CHEVRON,
    RGB_MATRIX_CYCLE_PINWHEEL,
    RGB_MATRIX_CYCLE_SPIRAL,
    RGB_MATRIX_RAINDROPS,
    RGB_MATRIX_SPLASH,
    RGB_MATRIX_MULTISPLASH,
    #endif  // DISABLE_RGB_MATRIX_ANIMATIONS
    RGB_MATRIX_CUSTOM_active_keys,
    RGB_MATRIX_NONE,
};
// clang-format on

_Static_assert(sizeof(mode_map) == MODE_LAST, "mode_map_length");

rgb_t raw_rgb_data[RGB_MATRIX_LED_COUNT];

// clang-format off
rgb_config_t layer_rgb[DYNAMIC_KEYMAP_LAYER_COUNT] = {
    // Layer 0
    {
        .enable = 1,
        .mode = RGB_MATRIX_DEFAULT_MODE,
        .hsv = {
            .h = RGB_MATRIX_DEFAULT_HUE,
            .s = RGB_MATRIX_DEFAULT_SAT,
            .v = RGB_MATRIX_DEFAULT_VAL,
        },
        .speed = RGB_MATRIX_DEFAULT_SPD,
        .flags = LED_FLAG_KEYLIGHT,
    },
    // Layer 1
    {
        .enable = 1,
        .mode = RGB_MATRIX_CUSTOM_active_keys,
        .hsv = {
            .h = RGB_MATRIX_DEFAULT_HUE,
            .s = RGB_MATRIX_DEFAULT_SAT,
            .v = RGB_MATRIX_DEFAULT_VAL,
        },
        .speed = RGB_MATRIX_DEFAULT_SPD,
        .flags = LED_FLAG_KEYLIGHT,
    },
    // Layer 2
    {
        .enable = 1,
        .mode = RGB_MATRIX_CUSTOM_active_keys,
        .hsv = {
            .h = RGB_MATRIX_DEFAULT_HUE,
            .s = RGB_MATRIX_DEFAULT_SAT,
            .v = RGB_MATRIX_DEFAULT_VAL,
        },
        .speed = RGB_MATRIX_DEFAULT_SPD,
        .flags = LED_FLAG_KEYLIGHT,
    },
    // Layer 3
    {
        .enable = 1,
        .mode = RGB_MATRIX_CUSTOM_active_keys,
        .hsv = {
            .h = RGB_MATRIX_DEFAULT_HUE,
            .s = RGB_MATRIX_DEFAULT_SAT,
            .v = RGB_MATRIX_DEFAULT_VAL,
        },
        .speed = RGB_MATRIX_DEFAULT_SPD,
        .flags = LED_FLAG_KEYLIGHT,
    },
};
// clang-format on

// Read or write EEPROM data with checks for being inside System76 EC region.
static bool system76_ec_eeprom_op(void *buf, uint16_t size, uint16_t offset, bool write) {
    uint16_t addr = SYSTEM76_EC_EEPROM_ADDR + offset;
    uint16_t end  = addr + size;
    // Check for overflow and zero size
    if ((end > addr) && (addr >= SYSTEM76_EC_EEPROM_ADDR) && (end <= (SYSTEM76_EC_EEPROM_ADDR + SYSTEM76_EC_EEPROM_SIZE))) {
        if (write) {
            eeprom_update_block((const void *)buf, (void *)addr, size);
        } else {
            eeprom_read_block((void *)buf, (const void *)addr, size);
        }
        return true;
    } else {
        return false;
    }
}

// Read or write EEPROM RGB parameters.
void system76_ec_rgb_eeprom(bool write) {
    uint16_t layer_rgb_size = sizeof(layer_rgb);
    system76_ec_eeprom_op((void *)layer_rgb, layer_rgb_size, 0, write);
    system76_ec_eeprom_op((void *)raw_rgb_data, sizeof(raw_rgb_data), layer_rgb_size, write);
}

// Update RGB parameters on layer change.
void system76_ec_rgb_layer(layer_state_t layer_state) {
    if (!bootloader_unlocked) {
        uint8_t layer = get_highest_layer(layer_state);
        if (layer < DYNAMIC_KEYMAP_LAYER_COUNT) {
            rgb_matrix_config = layer_rgb[layer];
        }
    }
}
#endif  // RGB_MATRIX_CUSTOM_KB

void raw_hid_receive(uint8_t *data, uint8_t length) {
    // Error response by default, set to success by commands
    data[1] = 1;

    switch (data[0]) {
        case CMD_PROBE:
            // Signature
            data[2] = 0x76;
            data[3] = 0xEC;
            // Version
            data[4] = 0x01;
            data[1] = 0;
            break;
        case CMD_BOARD:
            strncpy((char *)&data[2], QMK_KEYBOARD, length - 2);
            data[1] = 0;
            break;
        case CMD_VERSION:
            strncpy((char *)&data[2], QMK_VERSION, length - 2);
            data[1] = 0;
            break;
        case CMD_RESET:
            if (bootloader_unlocked) {
                data[1] = 0;
                bootloader_reset = true;
            }
            break;
        case CMD_KEYMAP_GET: {
            uint16_t value = 0;
            if (keymap_get(data[2], data[3], data[4], &value)) {
                data[5] = (uint8_t)value;
                data[6] = (uint8_t)(value >> 8);
                data[1] = 0;
            }
        } break;
        case CMD_KEYMAP_SET: {
            uint16_t value = ((uint16_t)data[5]) | (((uint16_t)data[6]) << 8);
            if (keymap_set(data[2], data[3], data[4], value)) {
                data[1] = 0;
            }
        } break;
#ifdef RGB_MATRIX_CUSTOM_KB
        case CMD_LED_GET_VALUE:
            if (!bootloader_unlocked) {
                uint8_t index = data[2];
                for (uint8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++) {
                    if (index == (0xF0 | layer)) {
                        data[3] = layer_rgb[layer].hsv.v;
                        data[4] = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
                        data[1] = 0;
                        break;
                    }
                }
            }
            break;
        case CMD_LED_SET_VALUE:
            if (!bootloader_unlocked) {
                uint8_t index = data[2];
                uint8_t value = data[3];
                if (value >= RGB_MATRIX_MAXIMUM_BRIGHTNESS) {
                    value = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
                }
                for (uint8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++) {
                    if (index == (0xF0 | layer)) {
                        layer_rgb[layer].hsv.v = value;
                        data[1] = 0;
                        system76_ec_rgb_layer(layer_state);
                        break;
                    }
                }
            }
            break;
        case CMD_LED_GET_COLOR:
            if (!bootloader_unlocked) {
                uint8_t index = data[2];
                if (index < RGB_MATRIX_LED_COUNT) {
                    data[3] = raw_rgb_data[index].r;
                    data[4] = raw_rgb_data[index].g;
                    data[5] = raw_rgb_data[index].b;
                    data[1] = 0;
                } else {
                    for (uint8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++) {
                        if (index == (0xF0 | layer)) {
                            data[3] = layer_rgb[layer].hsv.h;
                            data[4] = layer_rgb[layer].hsv.s;
                            data[5] = 0;
                            data[1] = 0;
                            break;
                        }
                    }
                }
            }
            break;
        case CMD_LED_SET_COLOR:
            if (!bootloader_unlocked) {
                uint8_t index = data[2];

                rgb_t rgb = {
                    .r = data[3],
                    .g = data[4],
                    .b = data[5],
                };

                if (index < RGB_MATRIX_LED_COUNT) {
                    raw_rgb_data[index] = rgb;
                    data[1] = 0;
                } else {
                    for (uint8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++) {
                        if (index == (0xF0 | layer)) {
                            layer_rgb[layer].hsv.h = rgb.r;
                            layer_rgb[layer].hsv.s = rgb.g;
                            // Ignore rgb.b
                            data[1] = 0;
                            system76_ec_rgb_layer(layer_state);
                            break;
                        }
                    }
                }
            }
            break;
        case CMD_LED_GET_MODE:
            if (!bootloader_unlocked) {
                uint8_t layer = data[2];
                if (layer < DYNAMIC_KEYMAP_LAYER_COUNT) {
                    enum rgb_matrix_effects mode = layer_rgb[layer].mode;
                    for (uint8_t i = 0; i < MODE_LAST; i++) {
                        if (mode_map[i] == mode) {
                            data[3] = i;
                            data[4] = layer_rgb[layer].speed;
                            data[1] = 0;
                            break;
                        }
                    }
                }
            }
            break;
        case CMD_LED_SET_MODE:
            if (!bootloader_unlocked) {
                uint8_t layer = data[2];
                uint8_t mode  = data[3];
                uint8_t speed = data[4];
                if (layer < DYNAMIC_KEYMAP_LAYER_COUNT && mode < MODE_LAST) {
                    layer_rgb[layer].mode  = mode_map[mode];
                    layer_rgb[layer].speed = speed;
                    data[1] = 0;
                    system76_ec_rgb_layer(layer_state);
                }
            }
            break;
        case CMD_LED_SAVE:
            if (!bootloader_unlocked) {
                system76_ec_rgb_eeprom(true);
                data[1] = 0;
            }
            break;
#endif  // RGB_MATRIX_CUSTOM_KB
        case CMD_MATRIX_GET: {
            // TODO: Improve performance?
            data[2] = matrix_rows();
            data[3] = matrix_cols();

            uint8_t byte = 4;
            uint8_t bit  = 0;

            for (uint8_t row = 0; row < matrix_rows(); row++) {
                for (uint8_t col = 0; col < matrix_cols(); col++) {
                    if (byte < length) {
                        if (matrix_is_on(row, col)) {
                            data[byte] |= (1 << bit);
                        } else {
                            data[byte] &= ~(1 << bit);
                        }
                    }

                    bit++;
                    if (bit >= 8) {
                        byte++;
                        bit = 0;
                    }
                }
            }
            data[1] = 0;
        } break;
        case CMD_SET_NO_INPUT: {
            clear_keyboard();
            input_disabled = data[2] != 0;
            data[1] = 0;
        } break;
    }

    raw_hid_send(data, length);

    if (bootloader_reset) {
        // Give host time to read response
        wait_ms(100);
        // Jump to the bootloader
        bootloader_jump();
    }
}
