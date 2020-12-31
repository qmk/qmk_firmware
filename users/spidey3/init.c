#include "spidey3.h"

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    keyboard_post_init_user_rgb();
#endif
}

void eeconfig_init_user(void) {
    print("eeconfig_init_user\n");
    set_single_persistent_default_layer(_BASE);
#ifdef UNICODEMAP_ENABLE
    eeconfig_init_user_unicode();
#endif

#ifdef RGBLIGHT_ENABLE
    eeconfig_init_user_rgb();
#endif
}

void shutdown_user() {
#ifdef RGBLIGHT_ENABLE
    clear_rgb_layers();
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    for (int i=0; i<RGBLED_NUM; i++)
        rgblight_setrgb_at(0xFF, 0x80*(i%2), 0, i);
#endif
}
