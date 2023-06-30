#include "quantum.h"
#include <stdio.h>

#define L_QWERTY 0
#define L_GAME 1
#define L_LOWER 2
#define L_RAISE 3
#define L_ADJUST 4
#define L_ALT 5
#define L_ADJUST_TRI (L_ADJUST | L_RAISE | L_LOWER)

char default_layer_str[24];

const char *default_layer(void) {

    switch (get_highest_layer(layer_state))
    {
    case 0:
        oled_write_ln("QWRTY", false);
        break;
    case 1:
        oled_write_ln("GAME", false);
        break;
    default:
        oled_write_ln("Undef", false);
    }

    return default_layer_str;
}
