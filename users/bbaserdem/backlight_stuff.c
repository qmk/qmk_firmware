/*
 * Replaced functions with noeeprom varieties; I don't need retention across
 * booting.
*/
#include "rgb_bl_stuff.h"

extern backlight_config_t backlight_config;

// Backlight LEDs
void matrix_init_backlight(void) {
    backlight_enable();
    backlight_level(2);
#ifdef BACKLIGHT_BREATHING
    breathing_enable();
#endif
}
