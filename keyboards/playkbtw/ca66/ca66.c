#include "ca66.h"
#include "config.h"

void bootmagic_lite(void)
{
	// The lite version of TMK's bootmagic.
	// 100% less potential for accidentally making the
	// keyboard do stupid things.

	// We need multiple scans because debouncing can't be turned off.
	matrix_scan();
	wait_ms(DEBOUNCE);
	matrix_scan();

	// If the Esc (matrix 0,0) is held down on power up,
	// reset the EEPROM valid state and jump to bootloader.
	if ( matrix_get_row(0) & (1<<0) )
	{
		// Set the TMK/QMK EEPROM state as invalid.
		eeconfig_disable();
		// Jump to bootloader.
		bootloader_jump();
	}
}

void matrix_init_kb(void)
{
	bootmagic_lite();
	matrix_init_user();
}
