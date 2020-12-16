#include QMK_KEYBOARD_H

#define _MAIN 0
#define _FN 1

#define KC_UNDO LCTL(KC_Z)
#define KC_REDO LCTL(KC_Y)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT(
    KC_UNDO,  KC_REDO,  KC_A,
    KC_C,     KC_D,     KC_S
  ),

  [_FN] = LAYOUT(
    KC_F13, KC_F14, KC_F15,
    KC_F16, KC_F17, KC_F18
  )
};

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
            if (active) {
                set_single_persistent_default_layer(_FN);
            } else {
                set_single_persistent_default_layer(_MAIN);
            }
        }
    }
}