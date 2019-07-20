#include "custom_tap_dance.h"
#include "custom_keycodes.h"
#include "timer_utils.h"

#ifdef TAP_DANCE_ENABLE

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [COMM_QUOT]  = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_QUOT),
  [BACKSPACE] = ACTION_TAP_DANCE_DOUBLE (KC_BSPACE, LCTL(KC_BSPACE)),
  [DELETE] = ACTION_TAP_DANCE_DOUBLE (KC_DELETE, LCTL(KC_DELETE))
};

#else

static uint16_t td_keycode;
static uint16_t td_timer;

const uint16_t PROGMEM td_keymaps[TD_MAX - TD_MIN][2] = {
    [TD_COMM - TD_MIN]  = { KC_COMM, KC_QUOT },
    [TD_BSPC - TD_MIN]  = { KC_BSPACE, LCTL(KC_BSPACE) },
    [TD_DEL - TD_MIN]  = { KC_DELETE, LCTL(KC_DELETE) }
};

static void run_custom_tap_dance(uint8_t i)
{
    tap_code16(pgm_read_word(&td_keymaps[td_keycode - TD_MIN][i]));
    td_keycode = KC_TRANSPARENT;
    td_timer = timer_read() + TAPPING_TERM;
}

bool process_custom_tap_dance(uint16_t keycode, keyrecord_t *record)
{
    if (TD_MIN <= keycode && keycode < TD_MAX)
    {
        if (record->event.pressed)
        {
            if (td_keycode != keycode || timer_expired(td_timer))
            {
                td_keycode = keycode;
                td_timer = timer_read() + TAPPING_TERM;
            }
            else
                run_custom_tap_dance(1);
        }
        return false;
    }

    if (td_keycode != KC_TRANSPARENT)
        run_custom_tap_dance(0);
    return true;
}

void matrix_scan_user(void)
{
    if (td_keycode != KC_TRANSPARENT && timer_expired(td_timer))
        run_custom_tap_dance(0);
}

#endif
