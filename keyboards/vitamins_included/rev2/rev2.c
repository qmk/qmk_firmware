#include "quantum.h"

bool is_keyboard_left(void) {
    #if defined(MASTER_LEFT)
        return is_keyboard_master();
    #elif defined(MASTER_RIGHT)
        return !is_keyboard_master();
    #elif defined(SPLIT_HAND_PIN)
        // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
        gpio_set_pin_input_high(SPLIT_HAND_PIN);
        bool x = !gpio_read_pin(SPLIT_HAND_PIN);
        gpio_set_pin_input(SPLIT_HAND_PIN);
        return x;
    #elif defined(EE_HANDS)
        return eeprom_read_byte(EECONFIG_HANDEDNESS);
    #endif

    return is_keyboard_master();
}
