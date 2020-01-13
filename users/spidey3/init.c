#include <spidey3.h>

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  matrix_init_user_rgb();
#endif
#ifdef UNICODEMAP_ENABLE
  matrix_init_user_unicode();
#endif
}
