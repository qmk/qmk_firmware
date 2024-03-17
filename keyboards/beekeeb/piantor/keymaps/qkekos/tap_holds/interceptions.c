
#include "../__init__.h"

int interceptions_pr(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TH_FUNC:
            intercept_tap(SEND_STRING("'s"));

        case TH_LNUM:
            if (!record->tap.count) return lower_layer_mo(NUM, record);
            return PR_IGNORE;

        case HR_RMLN: intercept_tap(tap_code16(HK_RMLN));
        case HR_SAVE: intercept_tap(tap_code16(HK_SAVE));
        case HR_CPLN: intercept_tap(tap_code16(HK_CPLN));
        case HR_SRCH: intercept_tap(tap_code16(HK_SRCH));
    }

    return PR_IGNORE;
}
