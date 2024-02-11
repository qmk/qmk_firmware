
#include "../__init__.h"

bool is_fence_active = false;
bool was_upper = true;

enum pr_response fence_pr(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return PR_IGNORE;

    if (keycode == US_FNCE) {
        is_fence_active = !is_fence_active;
        toggle_right_pin();
    }

    if (keycode == TH_NAV) was_upper = !was_upper;

    if (!is_fence_active) {
        was_upper = true;
        return PR_IGNORE;
    }

    bool is_tap_hold = false;

    if (IS_QK_MOD_TAP(keycode) || IS_QK_LAYER_TAP(keycode)) is_tap_hold = true;

    keycode = normalize_keycode(keycode);
    if (!IS_ALPHA_KEY(keycode)) return PR_IGNORE;

    was_upper = !was_upper;
    if (!was_upper) return PR_IGNORE;

    if (is_tap_hold) {
        tap_code16(S(keycode));
        return false;
    } else add_weak_mods(MOD_BIT(KC_LSFT));

    return PR_IGNORE;
}
