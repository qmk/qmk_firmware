/*
 * Copyright (C) 2021-2022 System76
 * Copyright (C) 2021-2025 Jimmy Cassis <KernelOops@outlook.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef RGB_MATRIX_ENABLE
#error "RGB_MATRIX_ENABLE is not enabled"
#endif

#include "system76_ec.h"

#include <string.h>

#if defined(SYSTEM76_EC)
#ifndef RAW_ENABLE
#error "RAW_ENABLE is not enabled"
#endif

#ifndef DYNAMIC_KEYMAP_ENABLE
#error "DYNAMIC_KEYMAP_ENABLE is not enabled"
#endif

#include "raw_hid.h"
#include "version.h"
#include "eeprom.h"
#elif defined(VIA_ENABLE)
#include "via.h"
#include <lib/lib8tion/lib8tion.h>
#endif

#ifdef SYSTEM76_EC
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

bool input_disabled = false;
static bool bootloader_reset = false;
static bool bootloader_unlocked = false;

void system76_ec_unlock(void) {
#ifdef RGB_MATRIX_CUSTOM_KB
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_UNLOCKED);
#endif
    bootloader_unlocked = true;
}

bool system76_ec_is_unlocked(void) {
    return bootloader_unlocked;
}
#else // !SYSTEM76_EC
bool system76_ec_is_unlocked(void) {
    return false;
}
#endif // SYSTEM76_EC

rgb_t raw_rgb_data[RGB_MATRIX_LED_COUNT] = {0};

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
#if DYNAMIC_KEYMAP_LAYER_COUNT > 1
    // Layer 1
    {
        .enable = 1,
#ifdef RGB_MATRIX_CUSTOM_KB
        .mode = RGB_MATRIX_CUSTOM_ACTIVE_KEYS,
#else
        .mode = RGB_MATRIX_SOLID_COLOR,
#endif
        .hsv = {
            .h = RGB_MATRIX_DEFAULT_HUE,
            .s = RGB_MATRIX_DEFAULT_SAT,
            .v = RGB_MATRIX_DEFAULT_VAL,
        },
        .speed = RGB_MATRIX_DEFAULT_SPD,
        .flags = LED_FLAG_KEYLIGHT,
    },
#endif
#if DYNAMIC_KEYMAP_LAYER_COUNT > 2
    // Layer 2
    {
        .enable = 1,
#if defined(RGB_MATRIX_CUSTOM_KB) && defined(SYSTEM76_EC)
        .mode = RGB_MATRIX_CUSTOM_RAW_RGB,
#elif defined(ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON)
        .mode = RGB_MATRIX_RAINBOW_MOVING_CHEVRON,
#endif
        .hsv = (hsv_t){RGB_MATRIX_DEFAULT_HUE, RGB_MATRIX_DEFAULT_SAT, RGB_MATRIX_DEFAULT_VAL},
        .speed = RGB_MATRIX_DEFAULT_SPD,
        .flags = LED_FLAG_KEYLIGHT,
    },
#endif
#if DYNAMIC_KEYMAP_LAYER_COUNT > 3
    // Layer 3
    {
        .enable = 1,
        .mode = RGB_MATRIX_SOLID_COLOR,
        .hsv = (hsv_t){RGB_MATRIX_DEFAULT_HUE, RGB_MATRIX_DEFAULT_SAT, RGB_MATRIX_DEFAULT_VAL},
        .speed = RGB_MATRIX_DEFAULT_SPD,
        .flags = LED_FLAG_KEYLIGHT,
    },
#endif
};
// clang-format on

#ifdef SYSTEM76_EC
// Read or write EEPROM data with checks for being inside System76 EC region.
static bool system76_ec_eeprom_op(void *buf, size_t size, size_t offset, bool write) {
    size_t addr = SYSTEM76_EC_EEPROM_ADDR + offset;
    size_t end = addr + size;
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
    size_t layer_rgb_size = sizeof(layer_rgb);
    system76_ec_eeprom_op((void *)layer_rgb, layer_rgb_size, 0, write);
    system76_ec_eeprom_op((void *)raw_rgb_data, sizeof(raw_rgb_data), layer_rgb_size, write);
}
#endif

// Update RGB parameters on layer change.
void system76_ec_rgb_layer(layer_state_t state) {
    if (!system76_ec_is_unlocked()) {
        uint8_t layer = get_highest_layer(state);
#ifdef DYNAMIC_KEYMAP_ENABLE
        uint8_t layer_count = DYNAMIC_KEYMAP_LAYER_COUNT;
#else
        uint8_t layer_count = keymap_layer_count();
#endif
        if (layer < layer_count) {
            rgb_matrix_sethsv_noeeprom(layer_rgb[layer].hsv.h, layer_rgb[layer].hsv.s, layer_rgb[layer].hsv.v);
            rgb_matrix_set_speed_noeeprom(layer_rgb[layer].speed);
            rgb_matrix_set_flags_noeeprom(layer_rgb[layer].flags);
            if (layer_rgb[layer].mode != RGB_MATRIX_NONE) {
                rgb_matrix_mode_noeeprom(layer_rgb[layer].mode);
            } else {
                rgb_matrix_config.mode = RGB_MATRIX_NONE;
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv_noeeprom(HSV_OFF);
            }
            if (layer_rgb[layer].enable) {
                rgb_matrix_enable_noeeprom();
            } else {
                rgb_matrix_disable_noeeprom();
            }
        }
    }
}

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

#ifndef RGB_MATRIX_CAPS_LOCK_INDEX
    uint8_t index = g_led_config.matrix_co[3][0]; // 38
#else
    uint8_t index = RGB_MATRIX_CAPS_LOCK_INDEX;
#endif
    if (host_keyboard_led_state().caps_lock && (rgb_matrix_get_flags() != LED_FLAG_NONE)) {
        rgb_matrix_set_color(index, RGB_WHITE);
    } else if (rgb_matrix_get_flags() == LED_FLAG_KEYLIGHT) {
        rgb_matrix_set_color(index, RGB_OFF);
    }
    return true;
}

#if defined(SYSTEM76_EC)
void raw_hid_receive(uint8_t *data, uint8_t length) {
    data[1] = 1; // Set "error" response by default; changed to "success" by commands

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
            if (system76_ec_is_unlocked()) {
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
            if (!system76_ec_is_unlocked()) {
                uint8_t index = data[2];
                for (uint8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; ++layer) {
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
            if (!system76_ec_is_unlocked()) {
                uint8_t index = data[2];
                uint8_t value = data[3];
                if (value >= RGB_MATRIX_MAXIMUM_BRIGHTNESS) {
                    value = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
                }
                for (uint8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; ++layer) {
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
            if (!system76_ec_is_unlocked()) {
                uint8_t index = data[2];
                if (index < RGB_MATRIX_LED_COUNT) {
                    data[3] = raw_rgb_data[index].r;
                    data[4] = raw_rgb_data[index].g;
                    data[5] = raw_rgb_data[index].b;
                    data[1] = 0;
                } else {
                    for (uint8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; ++layer) {
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
            if (!system76_ec_is_unlocked()) {
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
                    for (uint8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; ++layer) {
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
            if (!system76_ec_is_unlocked()) {
                uint8_t layer = data[2];
                if (layer < DYNAMIC_KEYMAP_LAYER_COUNT) {
                    enum rgb_matrix_effects mode = layer_rgb[layer].mode;
                    for (uint8_t i = 0; i < MODE_LAST; ++i) {
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
            if (!system76_ec_is_unlocked()) {
                uint8_t layer = data[2];
                uint8_t mode = data[3];
                uint8_t speed = data[4];
                if (layer < DYNAMIC_KEYMAP_LAYER_COUNT && mode < MODE_LAST) {
                    layer_rgb[layer].mode = mode_map[mode];
                    layer_rgb[layer].speed = speed;
                    data[1] = 0;
                    system76_ec_rgb_layer(layer_state);
                }
            }
            break;
        case CMD_LED_SAVE:
            if (!system76_ec_is_unlocked()) {
                system76_ec_rgb_eeprom(true);
                data[1] = 0;
            }
            break;
#endif // RGB_MATRIX_CUSTOM_KB
        case CMD_MATRIX_GET: {
            // TODO: Improve performance?
            data[2] = matrix_rows();
            data[3] = matrix_cols();

            uint8_t byte = 4;
            uint8_t bit = 0;

            for (uint8_t row = 0; row < matrix_rows(); ++row) {
                for (uint8_t col = 0; col < matrix_cols(); ++col) {
                    if (byte < length) {
                        if (matrix_is_on(row, col)) {
                            data[byte] |= (1 << bit);
                        } else {
                            data[byte] &= ~(1 << bit);
                        }
                    }

                    if (++bit >= 8) {
                        ++byte;
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
        reset_keyboard();
    }
}
#elif defined(VIA_ENABLE) // !defined(SYSTEM76_EC)
// Read or write EEPROM RGB parameters.
uint32_t via_rgb_eeprom(bool write) {
    size_t layer_rgb_size = sizeof(layer_rgb);
    uint32_t size = 0;
    if (write) {
        size = via_update_custom_config((const void *)layer_rgb, 0, layer_rgb_size);
    } else {
        size = via_read_custom_config((void *)layer_rgb, 0, layer_rgb_size);
    }
    return size;
}

void via_qmk_rgb_matrix_set_value_kb(uint8_t *data) {
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_qmk_rgb_matrix_brightness: {
            uint8_t value = scale8(value_data[0], RGB_MATRIX_MAXIMUM_BRIGHTNESS);
            layer_rgb[0].hsv.v = value;
            rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), value);
            break;
        }
        case id_qmk_rgb_matrix_effect: {
            if (value_data[0] == 0) {
                layer_rgb[0].enable = 0;
                layer_rgb[0].mode = value_data[0];
                rgb_matrix_disable_noeeprom();
            } else {
                layer_rgb[0].enable = 1;
                layer_rgb[0].mode = value_data[0];
                rgb_matrix_enable_noeeprom();
                rgb_matrix_mode_noeeprom(value_data[0]);
            }
            break;
        }
        case id_qmk_rgb_matrix_effect_speed: {
            layer_rgb[0].speed = value_data[0];
            rgb_matrix_set_speed_noeeprom(value_data[0]);
            break;
        }
        case id_qmk_rgb_matrix_color: {
            layer_rgb[0].hsv.h = value_data[0];
            layer_rgb[0].hsv.s = value_data[1];
            rgb_matrix_sethsv_noeeprom(value_data[0], value_data[1], rgb_matrix_get_val());
            break;
        }
    }
}

void via_qmk_rgb_matrix_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *value_id_and_data = &(data[2]);

    switch (*command_id) {
        case id_custom_set_value: {
            via_qmk_rgb_matrix_set_value_kb(value_id_and_data);
            break;
        }
        case id_custom_get_value: {
            via_qmk_rgb_matrix_get_value(value_id_and_data);
            break;
        }
        case id_custom_save: {
            via_qmk_rgb_matrix_save();
            break;
        }
        default: {
            *command_id = id_unhandled;
            break;
        }
    }
}

void via_custom_value_command(uint8_t *data, uint8_t length) {
    uint8_t *channel_id = &(data[1]);

#ifdef RGB_MATRIX_ENABLE
    if (*channel_id == id_qmk_rgb_matrix_channel) {
        via_qmk_rgb_matrix_command_kb(data, length);
        return;
    }
#endif

    (void)channel_id;

    via_custom_value_command_kb(data, length);
}
#endif // defined(VIA_ENABLE)
