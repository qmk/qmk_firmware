
#include "../__init__.h"

bool proceed_custom_tap(uint16_t keycode, keyrecord_t *record) {
    if (record->tap.count && record->event.pressed) {
        tap_code16(keycode);
        return true;
    }

    return false;
}

bool interceptions_pr(uint16_t keycode, keyrecord_t *record, bool *return_value) {
    *return_value = false;

    switch (keycode) {
        case LT_I:
            if (record->event.pressed && record->tap.count == 2) {
                tap_code16(KC_BSPC);
                add_weak_mods(MOD_BIT(KC_LSFT));
            }

            return false;

        case TH_LNUM:
            if (!record->tap.count) return lower_layer_mo(NUM, record);
            return false;

        case HR_RMLN: return proceed_custom_tap(HK_RMLN, record);
        case HR_SAVE: return proceed_custom_tap(HK_SAVE, record);
        case HR_CPLN: return proceed_custom_tap(HK_CPLN, record);
        case HR_SRCH: return proceed_custom_tap(HK_SRCH, record);
    }

    return false;
}
