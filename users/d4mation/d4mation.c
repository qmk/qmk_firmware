#include "d4mation.h"

__attribute__ ((weak))
bool process_record_keymap( uint16_t keycode, keyrecord_t *record ) {
    /* If you want macros specific to your keymap, you need to define this function in your keymap */
    return true;
}

__attribute__ ((weak))
void matrix_init_keymap() {
    /* If you want a matrix init specific to your keymap, you need to define this function in your keymap */
}

__attribute__ ((weak))
void matrix_scan_keymap() {
    /* If you want a matrix scan specific to your keymap, you need to define this function in your keymap */
}

__attribute__((weak))
void eeconfig_init_keymap( void ) {}

/* process_record_user() is called in macros.c */

void matrix_init_user( void ) {
    matrix_init_keymap();
}

void matrix_scan_user( void ) {
    matrix_scan_keymap();
}

void eeconfig_init_user( void ) {

    eeconfig_init_keymap();
    keyboard_init();

}