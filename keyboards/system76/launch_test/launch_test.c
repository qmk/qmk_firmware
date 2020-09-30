#include "dynamic_keymap.h"
#include "raw_hid.h"
#include "tmk_core/common/eeprom.h"
#include "version.h"

#include "launch_test.h"

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

bool eeprom_is_valid(void) {
	return (eeprom_read_word(((void*)EEPROM_MAGIC_ADDR)) == EEPROM_MAGIC &&
			eeprom_read_byte(((void*)EEPROM_VERSION_ADDR)) == EEPROM_VERSION);
}

void eeprom_set_valid(bool valid) {
	eeprom_update_word(((void*)EEPROM_MAGIC_ADDR), valid ? EEPROM_MAGIC : 0xFFFF);
	eeprom_update_byte(((void*)EEPROM_VERSION_ADDR), valid ? EEPROM_VERSION : 0xFF);
}

void eeprom_reset(void) {
	// Set the keyboard specific EEPROM state as invalid.
	eeprom_set_valid(false);
	// Set the TMK/QMK EEPROM state as invalid.
	eeconfig_disable();
}

void bootmagic_lite(void) {
	// The lite version of TMK's bootmagic.
	// 100% less potential for accidentally making the
	// keyboard do stupid things.

	// We need multiple scans because debouncing can't be turned off.
	matrix_scan();
	wait_ms(DEBOUNCE);
	wait_ms(DEBOUNCE);
	matrix_scan();

	// If the Esc (matrix 0,0) is held down on power up,
	// reset the EEPROM valid state and jump to bootloader.
	if ( matrix_get_row(0) & (1<<0) ) {
		eeprom_reset();
		bootloader_jump();
	}
}

void matrix_init_kb(void) {
    bootmagic_lite();
    if (!eeprom_is_valid()) {
        dynamic_keymap_reset();
        dynamic_keymap_macro_reset();
        eeprom_set_valid(true);
    }
}
