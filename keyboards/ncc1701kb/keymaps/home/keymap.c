#include QMK_KEYBOARD_H

/*HOME MAPPINGS */

/* Spul U Macro */
enum custom_keycodes {
  M_UMLAUT = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case M_UMLAUT:
  ------------
  
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_5) SS_TAP(X_KP_2) SS_UP(X_RALT));
      } else {
        // when keycode QMKBEST is released
      }
      break;

  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* LAYER 0 */
[0] = LAYOUT( \
  LT(1,KC_ESC),       KC_TAB,      KC_ENT,       \
  LCTL(KC_ENT),       LGUI(KC_E),      LCTL(LSFT(KC_N)),       \
  LCTL(LGUI(KC_LEFT)),       LGUI(KC_TAB),      LCTL(LGUI(KC_RGHT)) \
),

/* LAYER 1 */
[1] = LAYOUT( \
  KC_NO,   LSFT(KC_TAB), KC_MINS, \
  BL_TOGG, BL_STEP, BL_BRTG, \
  M_UMLAUT,     KC_DOT,  KC_TRNS  \
)

};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_DOWNü);
    } else {
      tap_code(KC_UP);
    }
  } else if (index == 1) { /* Second encoder */  
    if (clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
  }
}