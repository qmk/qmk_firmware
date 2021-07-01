#include "fun.h"
#include "mike1808.h"
#include "print.h"

static bool wpm_rgb_enabled = false;
static uint8_t rgb_mode;

void rgb_matrix_indicators_keymap(void) {
    if (wpm_rgb_enabled && rgb_matrix_is_enabled()) {
        uint8_t wpm = get_current_wpm();
        dprintf("WPM = %d\n", wpm);
        HSV hsv = rgb_matrix_get_hsv();
        hsv.h = wpm;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    }
}

bool process_record_fun(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && keycode == KC_WPM_RGB) {
        if (wpm_rgb_enabled) {
            wpm_rgb_enabled = false;
            rgb_matrix_mode(rgb_mode);
        } else {
            wpm_rgb_enabled = true;
            rgb_mode = rgb_matrix_get_mode();
            rgb_matrix_enable();
            rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        }

        return false;
    }

    return true;
}
