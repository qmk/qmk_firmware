#include "spidey3.h"

void keyboard_post_init_user(void) {
  print("SPIDEY3: keyboard_post_init_user\n");
  uprintf("         debug_enable=%u\n", debug_enable);
#ifdef RGBLIGHT_ENABLE
  keyboard_post_init_user_rgb();
#endif
}

void eeconfig_init_user(void) {
  print("SPIDEY3: eeconfig_init_user\n");
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
  rgblight_enable();
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  rgblight_sethsv_noeeprom(HSV_RED);
#endif
}
