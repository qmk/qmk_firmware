#include "quantum.h"

void eeconfig_init_kb(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable(); // Enable RGB underglow by default
    rgblight_sethsv(0, 255, 255);
#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 5); // Set to RGB_RAINBOW_SWIRL animation by default
#endif
#endif

    eeconfig_update_kb(0);
    eeconfig_init_user();
}
