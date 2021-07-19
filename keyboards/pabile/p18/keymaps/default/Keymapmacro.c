#include QMK_KEYBOARD_H

enum custom_keycodes {
    BASTARD = SAFE_RANGE,
    RALF, 
    LOU,
    FLO,
};

bool process_record_user(uint16_t keycode, keyrecord_t record) {
    switch (keycode) {
    case BASTARD:
        if (record->event.pressed) {
            // when keycode BASTARD is pressed
            SEND_STRING(KC_LCTL);
            SEND_STRING(C);
        } else {
            // when keycode BASTARD is released
        }
        break;
    case LOU:
        if (record->event.pressed) {
            // when keycode LOU is pressed
            SEND_STRING(KC_LCTL);
            SEND_STRING(V);
        } else {
            // when keycode LOU is released
        }
        break;
    case RALF:
        if (record->event.pressed) {
            // when keycode RALF is pressed
            SEND_STRING(KC_LCTL);
            SEND_STRING(X);
        } else {
            // when keycode RALF is released
        }
        break;
    case FLO:
        if (record->event.pressed) {
            // when keycode BASTARD is pressed
            SEND_STRING("Ich bin der Flo und muss aufs Klo);
            SEND_STRING(KC_PENT);
        } else {
            // when keycode Flo is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                 BASTARD,   LOU,   RALF, KC_FIND,
                 KC_P4,   KC_P5,   KC_P6, KC_PPLS,
        KC_MUTE, KC_P1,   KC_P2,   KC_P3, KC_TAB,
        KC_ESC,  KC_DEL, KC_P0, KC_PDOT, FLO
    )

};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { / First encoder below the controller /
    if (clockwise) {
      tap_code(KC_VOLD); /volume down/
    } else {
      tap_code(KC_VOLU); /volume up/
    }
  } else if (index == 1) { / Second encoder /
    if (clockwise) {
      tap_code16(C(KC_PMNS); /ZOOM IN/
    } else {
      tap_code16(C(KC_PPLS); /ZOOM OUT*/
    }
  }
    return true;
}
