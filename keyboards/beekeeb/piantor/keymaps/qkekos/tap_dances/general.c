
#include "../__init__.h"

tap_dance_action_t tap_dance_actions[] = {
    [TDI_LOCK] = TAP_DANCE_DOUBLE(TDI_LOCK, lock_td),
    [TDI_NUM]  = TAP_DANCE_TAP_HOLD(TDI_NUM, num_td),
    [TDI_LGSW] = TAP_DANCE_TAP_HOLD(TDI_LGSW, lang_td),
    [TDI_PASS] = SEQ_TD(pass_td),
    [TDI_EXLM] = SEQ_TD(exlm_td),
    [TDI_EQL]  = SEQ_TD(eql_td),
    [TDI_DQT]  = SEQ_TD(dqt_td),
    [TDI_BSLS] = SEQ_TD(bsls_td),
    [TDI_UNDS] = SEQ_TD(unds_td),
    [TDI_COLN] = SEQ_TD(coln_td),
    [TDI_ARR]  = SEQ_TD(arr_td),
    [TDI_ECLP] = SEQ_TD(eclp_td),
    [TDI_SALL] = SEQ_TD(sall_td),
    [TDI_MD] = SEQ_TD(md_td),
};

void lock_td(enum td_actions action) {
    double_tap_case(, invert_lock());
}

void num_td(enum td_actions action) {
    tap_hold_case(tap_code16(KC_SPC), invert_num());
}

void lang_td(enum td_actions action) {
    if (language_mode == TRIPLE) {
        tap_hold_case(
            tri_tap_actions[current_lang](),
            tri_hold_actions[current_lang]()
        );
    } else {
        tap_hold_case(
             double_tap_actions[current_lang](),
             double_hold_actions[current_lang]()
        );
    }
}

void invert_lock(void) {
    layer_invert(LOCK);
    toggle_both_pins();
}

void invert_num(void) {
    layer_invert(NUM);
    toggle_both_pins();
}
