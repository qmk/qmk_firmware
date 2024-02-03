
#include "../__init__.h"

bool is_fence_active = false;
bool was_upper = true;

bool fence_pr(uint16_t keycode, keyrecord_t *record, bool *return_value) {
    *return_value = false;
    if (!record->event.pressed) return false;

    if (keycode == US_FNCE) is_fence_active = !is_fence_active;
    if (keycode == TH_NAV) was_upper = !was_upper;

    if (!is_fence_active) {
        was_upper = true;
        return false;
    }

    bool is_tap_hold = false;

    if (IS_QK_MOD_TAP(keycode) || IS_QK_LAYER_TAP(keycode)) is_tap_hold = true;

    keycode = normalize_keycode(keycode);
    if (!(KC_A <= keycode && keycode <= KC_Z)) return false;

    was_upper = !was_upper;
    if (!was_upper) return false;

    if (is_tap_hold) {
        tap_code16(S(keycode));
        return true;
    } else add_weak_mods(MOD_BIT(KC_LSFT));

    return false;
}
