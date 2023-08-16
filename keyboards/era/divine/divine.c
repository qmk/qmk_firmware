#include "quantum.h"

void keyboard_post_init_kb(void) {
#ifdef BACKLIGHT_ENABLE
    backlight_enable();
    backlight_level(5);
#endif
}