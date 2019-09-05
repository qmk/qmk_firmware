#include "rev2.h"


#ifdef SSD1306OLED
void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    led_set_user(usb_led);
}
#endif

bool is_keyboard_left(void) {
    #if defined(MASTER_LEFT)
        return is_keyboard_master();
    #elif defined(MASTER_RIGHT)
        return !is_keyboard_master();
    #elif defined(SPLIT_HAND_PIN)
        // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
        setPinInputHigh(SPLIT_HAND_PIN);
        bool x = !readPin(SPLIT_HAND_PIN);
        setPinInput(SPLIT_HAND_PIN);
        return x;
    #elif defined(EE_HANDS)
        return eeprom_read_byte(EECONFIG_HANDEDNESS);
    #endif

    return is_keyboard_master();
}

void matrix_init_kb(void) {
	matrix_init_user();
};
