#include "quantum.h"
#include <stdio.h>
#include <stdbool.h>

#define L_WINDOWS 0
#define L_LINUX 1
#define L_GAMING 2
#define L_LOWER 3
#define L_RAISE 4
#define L_ADJUST 5
#define L_ADJ 6
#define L_GLOWER 7

char default_layer_str[6];
char highest_layer_str[12];
char caps_state_str[6];
char icon_str[24];

const char *default_layer(void) {
    switch (get_highest_layer(default_layer_state)) {
        case L_WINDOWS:
            snprintf(default_layer_str, sizeof(default_layer_str), "WIN  ");
            break;
        case L_LINUX:
            snprintf(default_layer_str, sizeof(default_layer_str), "TUX  ");
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
        case L_WINDOWS:
        case L_LINUX:
        case L_GAMING:
            snprintf(highest_layer_str, sizeof(highest_layer_str), "BASE ");
            break;
        case L_RAISE:
            snprintf(highest_layer_str, sizeof(highest_layer_str), "RAISE");
            break;
        case L_LOWER:
        case L_GLOWER:
            snprintf(highest_layer_str, sizeof(highest_layer_str), "LOWER");
            break;
        case L_ADJUST:
        case L_ADJ:
            snprintf(highest_layer_str, sizeof(highest_layer_str), "ADJ  ");
            break;
        default:
            snprintf(highest_layer_str, sizeof(highest_layer_str), "Undef");
    }

    return highest_layer_str;
}

const char *caps_state(void) {
    led_t led_state = host_keyboard_led_state();

    switch(led_state.caps_lock) {
        case 1:
            if(!is_caps_word_on()) {
                snprintf(caps_state_str, sizeof(caps_state_str), "CPSLK");
            } else {
                snprintf(caps_state_str, sizeof(caps_state_str), "cpswd");
            }
            break;
        default:
            if(!is_caps_word_on()) {
                snprintf(caps_state_str, sizeof(caps_state_str), "     ");
            } else {
                snprintf(caps_state_str, sizeof(caps_state_str), "CPSWD");
            }
    }

    return caps_state_str;
}

const char *mode_state(void) {
    static char icon_str[] = {
        151,152,10,
        183,184,0
    };

  return icon_str;
}
