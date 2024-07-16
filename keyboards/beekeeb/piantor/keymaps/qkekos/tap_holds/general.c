
#include "../__init__.h"

#define REQUIRE_PRIOR_IDLE_MS TAPPING_TERM

#define st_will_perform_2(keycode1, keycode2) \
    st_will_perform((uint16_t[]){keycode1, keycode2, KC_NO}, US_AREP)

#define STURDY_HR_CASES \
         GLT_S: \
    case ALT_T: \
    case SMT_N: \
    case CLT_A: \
    case ALT_E: \
    case LT_I

#define QWERTY_HR_CASES \
         GMT_A: \
    case AMT_S: \
    case SMT_J: \
    case CMT_K: \
    case AMT_L: \
    case LT_SCLN

#define HR_CASES STURDY_HR_CASES: case QWERTY_HR_CASES

uint16_t prev_keycode;
uint16_t next_keycode;
keyrecord_t *next_record;
bool is_pressed[UINT16_MAX];
short next_row;

#define prior_idle_condition \
    timer_elapsed(current_key_timestamp) < REQUIRE_PRIOR_IDLE_MS && \
    current_key_layerstamp <= QWERTY

bool is_homerow_mod_tap(uint16_t keycode) {
    switch (keycode) { case HR_CASES: return true; }
    return false;
}

bool is_ignored_prev_keycode(uint16_t keycode) {
    if (IS_QK_TAP_DANCE(keycode)) return true;
    return false;
}

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    is_pressed[keycode] = record->event.pressed;

    if (record->event.pressed) {
        prev_keycode = next_keycode;
        next_keycode = keycode;

        next_record = record;
        next_row = record->event.key.row;
    }

    if (is_homerow_mod_tap(keycode) && is_alpha_layer_on() && !is_ignored_prev_keycode(prev_keycode)) {
        uint8_t const tap_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);

        if (record->event.pressed && prior_idle_condition) {
            record->keycode = tap_keycode;
            is_pressed[tap_keycode] = true;
        } else if (!record->event.pressed && is_pressed[tap_keycode]) {
            record->keycode = tap_keycode;
            is_pressed[tap_keycode] = false;
        }
    }

    return true;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TH_NAV:
            return next_row >= 4;

        case HR_DEL:
        case HR_RMLN:
        case HR_SAVE:
        case HR_CPLN:
        case HR_SRCH:
            return true;
    }

    if (keycode == TH_REP && st_will_perform_2(US_REP, next_keycode)) {
        return false;
    }

    return get_hold_on_next_key(keycode, next_keycode);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD_NUM:
            return 120;

        case TD_PASS:
            return 1000;
    }

    if (keycode == TH_REP && st_will_perform_2(US_REP, next_keycode)) {
        return TAPPING_TERM + 50;
    }

    return TAPPING_TERM;
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TH_NUM:
        case TH_FUNC:
        case TH_NAV:
        case TH_REP:
        case SMT_F:
        case SMT_J:
        case SMT_D:
            return 0;
    }

    return get_hold_on_next_key(keycode, next_keycode) ? 0 : TAPPING_TERM;
}
