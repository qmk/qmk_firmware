#include "vinta.h"

void bootmagic_lite(void)
{
    // The lite version of TMK's bootmagic made by Wilba.
    // 100% less potential for accidentally making the
    // keyboard do stupid things.

    // We need multiple scans because debouncing can't be turned off.
    matrix_scan();
    wait_ms(10);
    matrix_scan();

    // If the Esc and space bar are held down on power up,
    // reset the EEPROM valid state and jump to bootloader.
    // Assumes Esc is at [0,0] and spacebar is at [4,6].
    // This isn't very generalized, but we need something that doesn't
    // rely on user's keymaps in firmware or EEPROM.
    if ( ( matrix_get_row(0) & (1<<0) ) &&
        ( matrix_get_row(4) & (1<<6) ) )
    {
        // Set the TMK/QMK EEPROM state as invalid.
        eeconfig_disable();
        //eeprom_set_valid(false);
        // Jump to bootloader.
        bootloader_jump();
    }
}

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    bootmagic_lite();

    matrix_init_user();
}

void matrix_scan_kb(void) {

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    return process_record_user(keycode, record);
}