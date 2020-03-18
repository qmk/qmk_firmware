#include <spidey3.h>

void keyboard_post_init_user(void) {
  print("SPIDEY3: keyboard_post_init_user\n");
  uprintf("         debug_enable=%u\n", debug_enable);
#ifdef RGBLIGHT_ENABLE
  keyboard_post_init_user_rgb();
#endif
  // This hack is here because when the persistently set default layer is applied 
  // by tmk on startup, layer_state_set_user() is never called...
  uint8_t def_layer = eeconfig_read_default_layer();
  layer_on(def_layer);
  uprintf("         def_layer=%u\n", def_layer);
}

void eeconfig_init_user(void) {
  print("SPIDEY3: eeconfig_init_user\n");

  layer_off(_OSX);
  eeconfig_update_default_layer(_BASE);
  default_layer_set(_BASE);

#ifdef UNICODEMAP_ENABLE
  eeconfig_init_user_unicode();
#endif

#ifdef RGBLIGHT_ENABLE
  eeconfig_init_user_rgb();
#endif
}
