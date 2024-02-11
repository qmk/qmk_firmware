
#include "../__init__.h"

uint32_t send_clear_enter_defer(uint32_t trigger_time, void *cb_arg) {
    tap_clear_code(KC_ENT);
    return 0;
}

enum pr_response custom_keys_pr(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case US_SLSR:
            if (record->event.pressed) {
                tap_code16(HK_SRCH);
                tap_code16(HK_SLSR);
            }

            return false;

        case US_3ARR:
            send_repeated_arrow(
                record->event.pressed,
                (void *) SS_TAP(X_RGHT) SS_TAP(X_RGHT) SS_TAP(X_RGHT)
            );

            if (!record->event.pressed) arrow_repeat_rate = arrow_repeat_delay;
            return false;

        case US_3ARL:
            send_repeated_arrow(
                record->event.pressed,
                (void *) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT)
            );

            if (!record->event.pressed) arrow_repeat_rate = arrow_repeat_delay;
            return false;

        case US_3ARU:
            send_repeated_arrow(
                record->event.pressed,
                (void *) SS_TAP(X_UP) SS_TAP(X_UP) SS_TAP(X_UP)
            );

            if (!record->event.pressed) arrow_repeat_rate = arrow_repeat_delay;
            return false;

        case US_3ARD:
            send_repeated_arrow(
                record->event.pressed,
                (void *) SS_TAP(X_DOWN) SS_TAP(X_DOWN) SS_TAP(X_DOWN)
            );

            if (!record->event.pressed) arrow_repeat_rate = arrow_repeat_delay;
            return false;

        case US_LGTG:
            if (record->event.pressed) language_mode = !language_mode;
            return false;

        case US_QTLY:
            if (record->event.pressed) {
                send_lang_independant_string("/q");
                defer_exec(50, send_clear_enter_defer, NULL);
            }

            return false;

        case US_CLER:
            if (!record->event.pressed) return false;

            tap_code16(HK_SALL);
            tap_code16(KC_BSPC);

            return false;

        case US_CWRD:
            if (!record->event.pressed) return false;

            if (is_shift_held()) tap_code16(C(S(KC_F)));
            else caps_word_toggle();

            return false;

        case KC_SCRL:
            current_lang = ENG;

            layer_on(STURDY);
            layer_off(QWERTY);

            return true;

        case US_SNKE:
            if (record->event.pressed) toggle_alt_case_with(KC_UNDS, 1);
            return false;

        case US_CAML:
            if (record->event.pressed) toggle_alt_case_with(KC_LSFT, 0);
            return false;
    }

    return PR_IGNORE;
}
