#include "quantum.h"
#include <stdio.h>

#define L_QWERTY 0
#define L_GAMING 1
#define L_LOWER 2
#define L_RAISE 3
#define L_ADJUST 4
#define L_ALT 5
#define L_ADJUST_TRI (L_ADJUST | L_RAISE | L_LOWER)

char default_layer_str[6];
char highest_layer_str[12];
char caps_lock_str[6];

const char *default_layer(void) {
    switch (get_highest_layer(default_layer_state)) {
        case L_QWERTY:
            snprintf(default_layer_str, sizeof(default_layer_str), "QWRTY");
            break;
        case L_GAMING:
            snprintf(default_layer_str, sizeof(default_layer_str), "GAME ");
            break;
        default:
            snprintf(default_layer_str, sizeof(default_layer_str), "Undef");
    }

    return default_layer_str;
}

const char *highest_layer(void) {
    switch (get_highest_layer(layer_state)) {
        case L_QWERTY:
        case L_GAMING:
            snprintf(highest_layer_str, sizeof(highest_layer_str), "BASE ");
            break;
        case L_RAISE:
            snprintf(highest_layer_str, sizeof(highest_layer_str), "RAISE");
            break;
        case L_LOWER:
            snprintf(highest_layer_str, sizeof(highest_layer_str), "LOWER");
            break;
        case L_ADJUST:
        case L_ADJUST_TRI:
            snprintf(highest_layer_str, sizeof(highest_layer_str), "ADJ  ");
            break;
        case L_ALT:
            snprintf(highest_layer_str, sizeof(highest_layer_str), "ALT  ");
            break;
        default:
            snprintf(highest_layer_str, sizeof(highest_layer_str), "Undef");
    }

    return highest_layer_str;
}

const char *caps_lock(void) {
    led_t led_state = host_keyboard_led_state();

    switch(led_state.caps_lock) {
        case 1:
            snprintf(caps_lock_str, sizeof(caps_lock_str), "CAPS ");
            break;
        default:
            snprintf(caps_lock_str, sizeof(caps_lock_str), "     ");
    }

    return caps_lock_str;

}
