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

#ifdef RGBLIGHT_ENABLE
void shutdown_user(void) { shutdown_user_rgb(); }
#endif
