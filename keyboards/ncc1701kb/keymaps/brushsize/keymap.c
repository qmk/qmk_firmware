#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* LAYER 0
 * ,-----------------------.
 * |   <<  |  MUTE |  >>   |  ENCODER - PRESS (MUTE) / KNOB (Brush size)
 * |-------+-------+-------|
 * |  STOP |  PLAY | MEDIA | 
 * |-------+-------+-------|
 * | CALC  | MAIL  | PC/FN | 
 * `-----------------------'
 */
[0] = LAYOUT(
  KC_MPRV,       KC_MUTE,      KC_MNXT,
  KC_MSTP,       KC_MPLY,      KC_MSEL,
  KC_CALC,       KC_MAIL,      LT(1, KC_MYCM)
),

/* LAYER 1
 * ,-----------------------.
 * |BL TOG |       | BREATH|
 * |-------+-------+-------|
 * |  BL + | BL -  |BL CYCL|
 * |-------+-------+-------|
 * | BL ON | BL OFF|       |
 * `-----------------------'
 */
[1] = LAYOUT(
  BL_TOGG,  KC_TRNS, BL_BRTG,
  BL_INC, BL_DEC,   BL_STEP,
  BL_ON,   BL_OFF,  KC_TRNS
)

};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_RBRC);
    } else {
      tap_code(KC_LBRC);
    }
  } else if (index == 1) { /* Second encoder */  
    if (clockwise) {
      tap_code(KC_RBRC);
    } else {
      tap_code(KC_LBRC);
    }
  }
}