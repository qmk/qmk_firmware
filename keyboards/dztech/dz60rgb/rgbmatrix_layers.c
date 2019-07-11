#include QMK_KEYBOARD_H
#include <rgblight_list.h>
#include "dz60rgb.h"

#define RGB_OFF 0x00, 0x00, 0x00

// TODO: possibly change _LAYER defines to an enum, in keymap.c
// TODO: determine how to get access to that enum from keymap.c

// TODO: change out color RGB values for their constants to aid readability
// TODO: add proper defines so people can turn this all on and off
// TODO: find a way to allow the user to customize colors (another enum?)

void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue, bool default_layer) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            rgb_matrix_set_color( i, red, green, blue );
        }
    }
}

void rgb_matrix_indicators_user(void) {
    uint8_t this_led = host_keyboard_leds();
    if (!g_suspend_state) {
        switch (biton32(layer_state)) {
            case _LAYER1:
            rgb_matrix_layer_helper(RGB_RED, false); break;
            case _LAYER2:
            rgb_matrix_layer_helper(RGB_GREEN, false); break;
            case _LAYER3:
            rgb_matrix_layer_helper(RGB_BLUE, false); break;
            case _LAYER4:
            rgb_matrix_layer_helper(RGB_YELLOW, false); break;
        }
    }
    if ( this_led & (1<<USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF);
    }
}
