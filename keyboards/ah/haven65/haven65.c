#include "quantum.h"

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
    if (led_state.caps_lock) {
        rgblight_sethsv_at(0, 0, 255, 0);
    } else {
        rgblight_sethsv_at(0, 0, 0, 0);
    }
  }
    return res;
}
