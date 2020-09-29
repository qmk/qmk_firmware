#include "launch_test.h"
#include "raw_hid.h"

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}

static bool keymap_get(uint8_t layer, uint8_t output, uint8_t input, uint16_t *value) {
	if (layer < MATRIX_LAYERS) {
		if (output < MATRIX_ROWS) {
			if (input < MATRIX_COLS) {
				*value = keymap_key_to_keycode(layer, (keypos_t){.row = output, .col = input});
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
		case 9: // KEYMAP_GET
			{
				uint16_t value = 0;
				if (keymap_get(data[2], data[3], data[4], &value)) {
					data[5] = (uint8_t)value;
					data[6] = (uint8_t)(value >> 8);
					data[1] = 0;
				}
			}
			break;
	}

	raw_hid_send(data, length);
}
