#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                 KC_MUTE,             KC_MEDIA_NEXT_TRACK, KC_MEDIA_PREV_TRACK    ,        KC_MEDIA_PLAY_PAUSE,
                  KC_P1,              KC_P2,    KC_P3,        KC_PDOT,
                  KC_P4,              KC_P5,    KC_P6,        KC_NUBS,
                  KC_P7,              KC_P8,    LT(1, KC_P9), KC_LCTL,
                  KC_ENT,             KC_ESC,   KC_BSPC,      KC_SPC,
                  KC_MINS,            KC_EQL,   KC_DEL,       KC_PGUP
    )

};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder below the controller */
    if (clockwise) {
      tap_code(KC_VOLD); /*volume down*/
    } else {
      tap_code(KC_VOLU); /*volume up*/
    }
  } else if (index == 1) { /* Second encoder */
    if (clockwise) {
      tap_code(KC_WH_U); /*mouse wheel up*/
    } else {
      tap_code(KC_WH_D); /*mouse wheel down*/
    }
  } else if (index == 2) { /* Third encoder */
    if (clockwise) {
      tap_code(KC_PAGE_UP); /*page up*/
    } else {
      tap_code(KC_PAGE_DOWN); /*page down*/
    }
  } else if (index == 4) { /* Fourth encoder */
    if (clockwise) {
      tap_code(KC_KB_VOLUME_UP); /*volume up*/
    } else {
      tap_code(KC_KB_VOLUME_DOWN); /*volume down*/
    }
  }
    return true;
}
