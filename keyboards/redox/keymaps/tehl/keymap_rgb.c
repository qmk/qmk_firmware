#include "keymap.h"
#include "keymap_rgb.h"
#include "rgblight.h"
#include "util.h"

bool is_default_rgb_state = false;

layer_state_t layer_state_set_rgb(layer_state_t state) {
    switch (biton32(state)) {
        case _ADMIN:
            rgblight_sethsv_noeeprom_red();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 2);
            is_default_rgb_state = false;
            break;
        case _NUMPD:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD + 1);
            is_default_rgb_state = false;
            break;
        default:
            // avoid restarting animation on enter/exit _RAISE
            if (!is_default_rgb_state) {
                rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 2);
            }
            is_default_rgb_state = true;
            break;
    }

    return state;
}
