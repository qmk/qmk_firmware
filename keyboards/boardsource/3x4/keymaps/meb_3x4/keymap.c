#include QMK_KEYBOARD_H

enum layers {
    NAVPAD,
    CTLPAD,
    NUMPAD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [NAVPAD] = LAYOUT(
  KC_LCTL   ,   LALT(KC_W),   KC_LEFT ,   KC_PGUP,
  KC_LALT   ,   LALT(KC_A),   KC_DOWN ,   KC_UP  ,
  TT(CTLPAD),   KC_SPC    ,   KC_RIGHT,   KC_PGDN
  ),

  [CTLPAD] = LAYOUT(
  KC_LCTL   ,   KC_1      ,   KC_4    ,    KC_7  ,
  KC_LALT   ,   KC_2      ,   KC_5    ,    KC_8  ,
  TT(NAVPAD),   KC_3      ,   KC_6    ,    KC_9
  ),

  [NUMPAD] = LAYOUT(
  KC_P0     ,   KC_P1    ,    KC_P4   ,   KC_P7  ,
  KC_PDOT   ,   KC_P2    ,    KC_P5   ,   KC_P8  ,
  TT(NAVPAD),   KC_P3    ,    KC_P6   ,   KC_P9
  )

};
