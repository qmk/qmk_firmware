
#include "../__init__.h"

int proceed_custom_tap(uint16_t keycode, keyrecord_t *record) {
    if (record->tap.count && record->event.pressed) {
        tap_code16(keycode);
        return false;
    }

    return PR_IGNORE;
}

int interceptions_pr(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TH_FUNC:
            if (record->tap.count && record->event.pressed) {
                SEND_STRING("'s");
                return false;
            }

            return PR_IGNORE;

        case TH_LNUM:
            if (!record->tap.count) return lower_layer_mo(NUM, record);
            return PR_IGNORE;

        case HR_RMLN: return proceed_custom_tap(HK_RMLN, record);
        case HR_SAVE: return proceed_custom_tap(HK_SAVE, record);
        case HR_CPLN: return proceed_custom_tap(HK_CPLN, record);
        case HR_SRCH: return proceed_custom_tap(HK_SRCH, record);
    }

    return PR_IGNORE;
}
