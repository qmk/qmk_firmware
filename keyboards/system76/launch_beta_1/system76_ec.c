#include <string.h>

#include "dynamic_keymap.h"
#include "raw_hid.h"
#include "version.h"

enum Command {
    // Probe for System76 EC protocol
    CMD_PROBE = 1,
    // Read board string
    CMD_BOARD = 2,
    // Read version string
    CMD_VERSION = 3,
    // Get keyboard map index
    CMD_KEYMAP_GET = 9,
    // Set keyboard map index
    CMD_KEYMAP_SET = 10,
};

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
	}

	raw_hid_send(data, length);
}
