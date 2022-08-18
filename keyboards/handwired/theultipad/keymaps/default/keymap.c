#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( 
    KC_MPRV, KC_MPLY,   KC_MNXT,   KC_NO,    KC_MUTE,
    KC_NUM,  KC_PSLS,   KC_PAST,   KC_PMNS,
    KC_P7,   KC_P8,     KC_P9,   
    KC_P4,   KC_P5,     KC_P6,     KC_PPLS,
    KC_P1,   KC_P2,     KC_P3,
    KC_P0,   KC_PDOT,   KC_PENT,   MO(1),    MO(3) 
  ),
  [1] = LAYOUT( 
    KC_MPRV, KC_MPLY,   KC_MNXT,   KC_NO,    LCA(KC_F10),
    KC_F10,  KC_F11,    KC_F12,    KC_NO,
    KC_F7,   KC_F8,     KC_F9,   
    KC_F4,   KC_F5,     KC_F6,     KC_PPLS,
    KC_F1,   KC_F2,     KC_F3,
    KC_P0,   KC_PDOT,   KC_PENT,   MO(1),    MO(3)
  ),
  [3] = LAYOUT( 
    KC_MPRV, KC_MPLY,   KC_MNXT,   KC_NO,    LCA(KC_F11),
    KC_NUM,  KC_PSLS,   KC_PAST,   KC_PMNS,
    KC_P7,   KC_P8,     KC_P9,   
    KC_P4,   KC_M,      KC_P6,     KC_PPLS,
    KC_P1,   KC_P2,     KC_P3,
    KC_P0,   KC_PDOT,   LALT(KC_F4),   MO(1),    MO(3) 
  ),


};


bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { 
    if (IS_LAYER_ON(0)){
      if (clockwise) {
      tap_code(KC_VOLU);
      } else {
      tap_code(KC_VOLD);
      }
    }
    if (IS_LAYER_ON(1)){
      if (clockwise) {
      tap_code16(C(KC_Y));
      } else {
      tap_code16(C(KC_Z));
    }
    }
    else if (IS_LAYER_ON(3)){
      if (clockwise) {
      tap_code(KC_WH_D);
      } else {
      tap_code(KC_WH_U);
      }
    }
     
  }
  return false;
}