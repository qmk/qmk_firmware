#include <string.h>

#include "dynamic_keymap.h"
#include "raw_hid.h"
#include "rgb_matrix.h"
#include "version.h"

enum Command {
    // Probe for System76 EC protocol
    CMD_PROBE = 1,
    // Read board string
    CMD_BOARD = 2,
    // Read version string
    CMD_VERSION = 3,
    // Reset to bootloader
    CMD_RESET = 6,
    // Get keyboard map index
    CMD_KEYMAP_GET = 9,
    // Set keyboard map index
    CMD_KEYMAP_SET = 10,
    // Get LED value by index
    CMD_LED_GET_VALUE = 11,
    // Set LED value by index
    CMD_LED_SET_VALUE = 12,
    // Get LED color by index
    CMD_LED_GET_COLOR = 13,
    // Set LED color by index
    CMD_LED_SET_COLOR = 14,
    // Get LED matrix mode and speed
    CMD_LED_GET_MODE = 15,
    // Set LED matrix mode and speed
    CMD_LED_SET_MODE = 16,
    // Get currently pressed keys
    CMD_MATRIX_GET = 17,
};

enum Mode {
    MODE_SOLID_COLOR = 0,
    MODE_PER_KEY,
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
    MODE_LAST,
};

static enum rgb_matrix_effects mode_map[] = {
    RGB_MATRIX_SOLID_COLOR,
    RGB_MATRIX_CUSTOM_raw_rgb,
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
};

_Static_assert(sizeof(mode_map) == MODE_LAST, "mode_map_length");

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

static bool bootloader_reset = false;
static bool bootloader_unlocked = false;

void system76_ec_unlock(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_unlocked);
    bootloader_unlocked = true;
}

#if defined(RGB_MATRIX_CUSTOM_KB)
RGB raw_rgb_data[DRIVER_LED_TOTAL];
#endif // defined(RGB_MATRIX_CUSTOM_KB)

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
        case CMD_KEYMAP_GET:
            {
                uint16_t value = 0;
                if (keymap_get(data[2], data[3], data[4], &value)) {
                    data[5] = (uint8_t)value;
                    data[6] = (uint8_t)(value >> 8);
                    data[1] = 0;
                }
            }
            break;
        case CMD_KEYMAP_SET:
            {
                uint16_t value =
                    ((uint16_t)data[5]) |
                    (((uint16_t)data[6]) << 8);
                if (keymap_set(data[2], data[3], data[4], value)) {
                    data[1] = 0;
                }
            }
            break;
#if defined(RGB_MATRIX_CUSTOM_KB)
        case CMD_LED_GET_VALUE:
            if (!bootloader_unlocked) {
                if (data[2] == CMD_LED_INDEX_ALL) {
                    data[3] = rgb_matrix_config.hsv.v;
                    data[4] = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
                    data[1] = 0;
                }
            }
            break;
        case CMD_LED_SET_VALUE:
            if (!bootloader_unlocked) {
                if (data[2] == CMD_LED_INDEX_ALL) {
                    rgb_matrix_sethsv_noeeprom(
                        rgb_matrix_config.hsv.h,
                        rgb_matrix_config.hsv.s,
                        data[3]
                    );
                    data[1] = 0;
                }
            }
            break;
        case CMD_LED_GET_COLOR:
            if (!bootloader_unlocked) {
                uint8_t index = data[2];
                if (index < DRIVER_LED_TOTAL) {
                    data[3] = raw_rgb_data[index].r;
                    data[4] = raw_rgb_data[index].g;
                    data[5] = raw_rgb_data[index].b;
                    data[1] = 0;
                } else if (index == CMD_LED_INDEX_ALL) {
                    data[3] = rgb_matrix_config.hsv.h;
                    data[4] = rgb_matrix_config.hsv.s;
                    data[5] = 255;
                    data[1] = 0;
                }
            }
            break;
        case CMD_LED_SET_COLOR:
            if (!bootloader_unlocked) {
                uint8_t index = data[2];
                RGB rgb = {
                    .r = data[3],
                    .g = data[4],
                    .b = data[5],
                };
                if (index < DRIVER_LED_TOTAL) {
                    raw_rgb_data[index] = rgb;
                    data[1] = 0;
                } else if (index == CMD_LED_INDEX_ALL) {
                    rgb_matrix_sethsv_noeeprom(rgb.r, rgb.g, rgb_matrix_config.hsv.v);
                    data[1] = 0;
                }
            }
            break;
        case CMD_LED_GET_MODE:
            if (!bootloader_unlocked) {
                enum rgb_matrix_effects mode = rgb_matrix_get_mode();
                for (uint8_t i = 0; i < MODE_LAST; i++) {
                    if (mode_map[i] == mode) {
                        data[2] = i;
                        data[3] = rgb_matrix_config.speed;
                        data[1] = 0;
                        break;
                    }
                }
            }
            break;
        case CMD_LED_SET_MODE:
            if (!bootloader_unlocked) {
                if (data[2] < MODE_LAST) {
                    rgb_matrix_mode_noeeprom(mode_map[data[2]]);
                    rgb_matrix_config.speed = data[3];
                    data[1] = 0;
                }
            }
            break;
#endif // defined(RGB_MATRIX_CUSTOM_KB)
        case CMD_MATRIX_GET:
            {
                //TODO: improve performance?
                data[2] = matrix_rows();
                data[3] = matrix_cols();
                uint8_t byte = 4;
                uint8_t bit = 0;
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
            }
            break;
    }

    raw_hid_send(data, length);

    if (bootloader_reset) {
        // Give host time to read response
        wait_ms(100);
        // Jump to the bootloader
        bootloader_jump();
    }
}
