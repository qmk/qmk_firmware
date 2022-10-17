#include QMK_KEYBOARD_H

#define _BL 0
#define _HL 1
#define _LL 2

enum keycodes {
  LOW,
  HIGH
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
  * Base Layer (Numbers)
  */
  [_BL] = LAYOUT(
    KC_KP_7,    KC_KP_8,    KC_KP_9,
    KC_KP_4,    KC_KP_5,    KC_KP_6,
    KC_KP_1,    KC_KP_2,    KC_KP_3,
    LOW,        KC_KP_0,    HIGH
  ),
  /*
  * High Layer (Work)
  */
  [_HL] = LAYOUT(
    KC_NUM,          KC_PAST,    KC_NO,
    KC_PMNS,         KC_PENT,    KC_PPLS,
    KC_NO,           KC_PSLS,    KC_NO,
    KC_NO,           KC_PDOT,    KC_NO
  ),
  /*
  * Low Layer (Media)
  */
  [_LL] = LAYOUT(
    KC_NO,    KC_VOLU,    KC_NO,
    KC_MPRV,  KC_MPLY,    KC_MNXT,
    KC_NO,    KC_VOLD,    KC_NO,
    KC_NO,    KC_NO,      KC_NO
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case HIGH:
      if (record->event.pressed) {
        layer_on(_HL);
      }else{
        layer_off(_HL);
        layer_off(_LL);
      }
      return false;
      break;
    case LOW:
      if (record->event.pressed) {
        layer_on(_LL);
      }else{
        layer_off(_LL);
        layer_off(_HL);
      }
      return false;
      break;
  }
  return true;
}
