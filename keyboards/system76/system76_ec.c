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
};

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
            bootloader_jump();
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
            {
                if (data[2] == CMD_LED_INDEX_ALL) {
                    data[3] = rgb_matrix_config.hsv.v;
                    data[4] = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
                    data[1] = 0;
                }
            }
            break;
        case CMD_LED_SET_VALUE:
            {
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
            {
                uint8_t index = data[2];
                if (index < DRIVER_LED_TOTAL) {
                    data[3] = raw_rgb_data[index].r;
                    data[4] = raw_rgb_data[index].g;
                    data[5] = raw_rgb_data[index].b;
                    data[1] = 0;
                } else if (index == CMD_LED_INDEX_ALL) {
                    data[3] = raw_rgb_data[0].r;
                    data[4] = raw_rgb_data[0].g;
                    data[5] = raw_rgb_data[0].b;
                    data[1] = 0;
                }
            }
            break;
        case CMD_LED_SET_COLOR:
            {
                uint8_t index = data[2];
                RGB rgb = {
                    .r = data[3],
                    .g = data[4],
                    .b = data[5],
                };
                if (index < DRIVER_LED_TOTAL) {
                    raw_rgb_data[index] = rgb;
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_raw_rgb);
                    data[1] = 0;
                } else if (index == CMD_LED_INDEX_ALL) {
                    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
                        raw_rgb_data[i] = rgb;
                    }
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_raw_rgb);
                    data[1] = 0;
                }
            }
            break;
#endif // defined(RGB_MATRIX_CUSTOM_KB)
	}

	raw_hid_send(data, length);
}
