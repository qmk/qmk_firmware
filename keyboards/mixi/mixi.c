#include "mixi.h"

void eeconfig_init_kb(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable(); // Enable RGB underglow by default
#ifdef RGBLIGHT_ANIMATIONS
    rgblight_mode(RGBLIGHT_MODE_TWINKLE + 5); // Set to RGB_TWINKLE animation by default
#endif
#endif

    eeconfig_update_kb(0);
    eeconfig_init_user();
}
