#include "csc027.h"
#include "custom_rgb.h"

#if defined(RGBLIGHT_ENABLE)

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    uint16_t user_hue = rgblight_get_hue();
    for (uint16_t i = 0; i < 256; ++i) {
        rgblight_sethsv_noeeprom((i + user_hue) % 256, 255, 255);
        wait_ms(5);
    }
    rgblight_sethsv_noeeprom(0, 0, 0);
}

void on_usb_led_off(void) {
    rgblight_sethsv_noeeprom(0, 0, rgblight_get_val() - 85);
}

void on_usb_led_on(void) {
    rgblight_sethsv_noeeprom(0, 0, rgblight_get_val() + 85);
}

#endif
