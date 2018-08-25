#ifndef BACKLIGHT_H
#define BACKLIGHT_H

#include <stdbool.h>
#include <stdint.h>

enum backlight_level {
    BACKLIGHT_ALPHA    = 0b0000001,
    BACKLIGHT_MOD      = 0b0000010,
    BACKLIGHT_FROW     = 0b0000100,
    BACKLIGHT_NUMBLOCK = 0b0001000,
    BACKLIGHT_RGB      = 0b0010000,
    BACKLIGHT_SWITCH   = 0b0001111
};

void backlight_init_ports(void);
void backlight_set_state(bool cfg[7]);
void backlight_update_state(void);
void backlight_toggle_rgb(bool enabled);
void backlight_set_rgb(uint8_t cfg[17][3]);
void backlight_set(uint8_t level);

#endif // BACKLIGHT_H