#include "zeal_keymap.h"
#include "zeal_eeprom.h"
#include "config.h"
#include "keymap.h" // to get keymaps[][][]


#if USE_KEYMAPS_IN_EEPROM

void *keymap_key_to_eeprom_address(uint8_t layer, uint8_t row, uint8_t column)
{
	// TODO: optimize this with some left shifts
	return EEPROM_KEYMAP_ADDR + ( layer * MATRIX_ROWS * MATRIX_COLS * 2 ) +
		( row * MATRIX_COLS * 2 ) + ( column * 2 );
}

uint16_t keymap_keycode_load(uint8_t layer, uint8_t row, uint8_t column)
{
	void *address = keymap_key_to_eeprom_address(layer, row, column);
	// Big endian, so we can read/write EEPROM directly from host if we want
	uint16_t keycode = eeprom_read_byte(address) << 8;
	keycode |= eeprom_read_byte(address + 1);
	return keycode;
}

void keymap_keycode_save(uint8_t layer, uint8_t row, uint8_t column, uint16_t keycode)
{
	void *address = keymap_key_to_eeprom_address(layer, row, column);
	// Big endian, so we can read/write EEPROM directly from host if we want
	eeprom_update_byte(address, (uint8_t)(keycode >> 8));
	eeprom_update_byte(address+1, (uint8_t)(keycode & 0xFF));
}

void keymap_default_save(void)
{
	// Save "empty" keymaps.
	for ( int layer = 0; layer < EEPROM_KEYMAP_MAX; layer++ )
	{
		for ( int row = 0; row < MATRIX_ROWS; row++ )
		{
			for ( int column = 0; column < MATRIX_COLS; column++ )
			{
				keymap_keycode_save(layer, row, column, KC_EENULL);
			}
		}
	}
}


// This overrides the one in quantum/keymap_common.c
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
	if ( eeprom_is_valid() &&
		 layer < EEPROM_KEYMAP_MAX &&
		 key.row < MATRIX_ROWS && // possibly redundant
		 key.col < MATRIX_COLS ) // possibly redundant
	{
		uint16_t keycode = keymap_keycode_load(layer, key.row, key.col);

		// If keycode is not "empty", return it, otherwise
		// drop down to return the one in flash
		if ( keycode != KC_EENULL)
		{
			return keycode;
		}
	}

	return pgm_read_word(&keymaps[layer][key.row][key.col]);
}
#endif // USE_KEYMAPS_IN_EEPROM

