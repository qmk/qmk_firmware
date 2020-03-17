#include <spidey3.h>

void keyboard_post_init_user(void) {
  print("SPIDEY3: post_init_user\n");
  uprintf("SPIDEY3: debug_enable=%u\n", debug_enable);
}

void matrix_init_user(void) {
  print("SPIDEY3: matrix_init_user\n");
  uprintf("SPIDEY3: debug_enable=%u\n", debug_enable);
#ifdef RGBLIGHT_ENABLE
  matrix_init_user_rgb();
#endif
}

void eeconfig_init_user(void) {
  print("SPIDEY3: eeconfig_init_user\n");
#ifdef UNICODEMAP_ENABLE
  eeconfig_init_user_unicode();
#endif
#ifdef RGBLIGHT_ENABLE
  eeconfig_init_user_rgb();
#endif
}
