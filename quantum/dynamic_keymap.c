#include "config.h"
#include "keymap.h" // to get keymaps[][][]

#include "dynamic_keymap.h"

#ifdef DYNAMIC_KEYMAP_ENABLE

#ifndef DYNAMIC_KEYMAP_BASE_ADDR
#error DYNAMIC_KEYMAP_BASE_ADDR not defined
#endif

#ifndef DYNAMIC_KEYMAP_LAYER_COUNT
#error DYNAMIC_KEYMAP_LAYER_COUNT not defined
#endif

#define KC_EENULL 0xFFFF // TODO: move to enum quantum_keycodes

void *dynamic_keymap_key_to_eeprom_address(uint8_t layer, uint8_t row, uint8_t column)
{
	// TODO: optimize this with some left shifts
	return ((void*)DYNAMIC_KEYMAP_BASE_ADDR) + ( layer * MATRIX_ROWS * MATRIX_COLS * 2 ) +
		( row * MATRIX_COLS * 2 ) + ( column * 2 );
}

uint16_t dynamic_keymap_keycode_load(uint8_t layer, uint8_t row, uint8_t column)
{
	void *address = dynamic_keymap_key_to_eeprom_address(layer, row, column);
	// Big endian, so we can read/write EEPROM directly from host if we want
	uint16_t keycode = eeprom_read_byte(address) << 8;
	keycode |= eeprom_read_byte(address + 1);
	return keycode;
}

void dynamic_keymap_keycode_save(uint8_t layer, uint8_t row, uint8_t column, uint16_t keycode)
{
	void *address = dynamic_keymap_key_to_eeprom_address(layer, row, column);
	// Big endian, so we can read/write EEPROM directly from host if we want
	eeprom_update_byte(address, (uint8_t)(keycode >> 8));
	eeprom_update_byte(address+1, (uint8_t)(keycode & 0xFF));
}

void dynamic_keymap_default_save(void)
{
	// Save "empty" keymaps.
	for ( int layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++ )
	{
		for ( int row = 0; row < MATRIX_ROWS; row++ )
		{
			for ( int column = 0; column < MATRIX_COLS; column++ )
			{
				dynamic_keymap_keycode_save(layer, row, column, KC_EENULL);
			}
		}
	}
}

// This overrides the one in quantum/keymap_common.c
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
	// This used to test EEPROM for magic bytes, but it was redundant.
	// Test for EEPROM usage change (fresh install, address change, etc.)
	// externally and call dynamic_keymap_default_save()
	if ( layer < DYNAMIC_KEYMAP_LAYER_COUNT &&
		 key.row < MATRIX_ROWS && // possibly redundant
		 key.col < MATRIX_COLS ) // possibly redundant
	{
		uint16_t keycode = dynamic_keymap_keycode_load(layer, key.row, key.col);

		// If keycode is not "empty", return it, otherwise
		// drop down to return the one in flash
		if ( keycode != KC_EENULL)
		{
			return keycode;
		}
	}

	return pgm_read_word(&keymaps[layer][key.row][key.col]);
}

#endif // DYNAMIC_KEYMAP_ENABLE

