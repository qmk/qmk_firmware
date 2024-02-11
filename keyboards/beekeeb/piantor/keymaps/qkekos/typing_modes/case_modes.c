
#include "../__init__.h"

bool is_alt_case_active = false;
uint16_t case_separator;
int case_sep_len;

void toggle_alt_case_with(uint16_t separator, int sep_len) {
    is_alt_case_active = !is_alt_case_active;
    case_separator = separator;
    case_sep_len = sep_len;
    toggle_right_pin();
}

int alt_case_pr(uint16_t keycode, keyrecord_t *record) {
    if (!(record->event.pressed && is_alt_case_active)) return PR_IGNORE;
    if (!(keycode == TH_NUM && record->tap.count)) return PR_IGNORE;

    if (queue(-2) == KC_SPC) {
        is_alt_case_active = false;
        toggle_right_pin();
        multi_tap(KC_BSPC, case_sep_len);
        return PR_IGNORE;
    }

    if (case_separator == KC_LSFT) add_oneshot_mods(MOD_BIT(KC_LSFT));
    else tap_code16(case_separator);

    return PR_FALSE;
}
