#include "quantum.h"

bool is_keyboard_left(void) {
    #if defined(SPLIT_HAND_PIN)
        // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
        gpio_set_pin_input_high(SPLIT_HAND_PIN);
        bool x = !gpio_read_pin(SPLIT_HAND_PIN);
        gpio_set_pin_input(SPLIT_HAND_PIN);
        return x;
    #endif
    if (eeconfig_read_handedness() == EEHANDS_UNSET){
        return is_keyboard_master();
    } else {
        return eeconfig_read_handedness() == EEHANDS_LEFT ? true : false;
    }
}
