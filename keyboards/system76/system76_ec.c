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
extern uint8_t raw_rgb_r;
extern uint8_t raw_rgb_g;
extern uint8_t raw_rgb_b;

static uint8_t led_v = 255;
static uint8_t led_r = 0;
static uint8_t led_g = 0;
static uint8_t led_b = 0;

static uint8_t led_normalize(uint8_t component, uint8_t brightness) {
    uint32_t x = (uint32_t)component;
    x *= brightness; // Multiply by software brightness
    x *= RGB_MATRIX_MAXIMUM_BRIGHTNESS; // Multiply by hardware brightness
    x /= 255; // Divide by maximum software brightness
    x /= 255; // Divide by maximum hardware brightness
    return (uint8_t)x;
}

static void led_update(void) {
    raw_rgb_r = led_normalize(led_r, led_v);
    raw_rgb_g = led_normalize(led_g, led_v);
    raw_rgb_b = led_normalize(led_b, led_v);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_raw_rgb);
}
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
                //TODO: Getting single LEDs?
                if (data[2] == CMD_LED_INDEX_ALL) {
                    data[3] = led_v;
                    data[4] = 255;
                    data[1] = 0;
                }
            }
            break;
        case CMD_LED_SET_VALUE:
            {
                //TODO: Setting single LEDs?
                if (data[2] == CMD_LED_INDEX_ALL) {
                    led_v = data[3];
                    led_update();
                    data[1] = 0;
                }
            }
            break;
        case CMD_LED_GET_COLOR:
            {
                //TODO: Getting single LEDs?
                if (data[2] == CMD_LED_INDEX_ALL) {
                    data[3] = led_r;
                    data[4] = led_g;
                    data[5] = led_b;
                    data[1] = 0;
                }
            }
            break;
        case CMD_LED_SET_COLOR:
            {
                //TODO: Setting single LEDs?
                if (data[2] == CMD_LED_INDEX_ALL) {
                    led_r = data[3];
                    led_g = data[4];
                    led_b = data[5];
                    led_update();
                    data[1] = 0;
                }
            }
            break;
#endif // defined(RGB_MATRIX_CUSTOM_KB)
	}

	raw_hid_send(data, length);
}
