#include QMK_KEYBOARD_H
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _BASE,
  _FN1,
  _FN2,
  _FN3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_LBRC ,                 KC_RBRC ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_BSPC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_MINS ,                 KC_EQL  ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSLS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┘                └────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,                                   KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_ENT  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                  ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,                                   KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                ┌────────┼────────┼────────┴────────┼────────┼────────┼────────┤
     KC_LALT ,KC_QUOT ,KC_GRV  ,KC_DEL  ,MO(_FN1),KC_LGUI ,KC_SPC  ,                 KC_SPC  ,KC_RGUI ,TO(_FN2),KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
  //└────────┴────────┴────────┴────────┴────────┴────────┴────────┘                └────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_FN1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F11  ,                 KC_F12  ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_DEL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_DQUO ,KC_QUOT ,KC_GRV  ,KC_ASTR ,KC_PLUS ,KC_EQL  ,                 KC_LPRN ,KC_RPRN ,KC_PIPE ,KC_ASTR ,KC_TILD ,KC_CIRC ,KC_PIPE ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┘                └────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_AT   ,KC_COLN ,KC_GRV  ,KC_SLSH ,KC_MINS ,                                   KC_LBRC ,KC_RBRC ,KC_DOT  ,KC_SLSH ,KC_MINS ,KC_TRNS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                  ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_DOT  ,KC_SLSH ,                                   KC_LCBR ,KC_RCBR ,KC_TRNS ,KC_TRNS ,KC_CIRC ,KC_TRNS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                ┌────────┼────────┼────────┴────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,                 KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_LT   ,KC_UNDS ,KC_CIRC ,KC_GT
  //└────────┴────────┴────────┴────────┴────────┴────────┴────────┘                └────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_FN2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TRNS ,RGB_HUI ,RGB_HUD ,RGB_SAI ,RGB_SAD ,RGB_VAI ,RGB_VAD ,                 RGB_HUI ,RGB_HUD ,RGB_SAI ,RGB_SAD ,RGB_VAI ,RGB_VAD ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,RGB_M_P ,RGB_M_SW ,RGB_M_X,XXXXXXX ,XXXXXXX ,XXXXXXX ,                 RGB_M_P ,RGB_M_SW,RGB_M_X ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┘                └────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,RGB_M_B ,RGB_M_SN ,RGB_M_G,XXXXXXX ,XXXXXXX ,                                   RGB_M_B ,RGB_M_SN,RGB_M_G ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                  ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,RGB_M_R ,RGB_M_K ,RGB_M_T ,XXXXXXX ,XXXXXXX ,                                   RGB_M_R ,RGB_M_K ,RGB_M_T ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                ┌────────┼────────┼────────┴────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,RGB_MOD ,RGB_TOG ,                 RGB_TOG ,RGB_MOD ,TO(_BASE),XXXXXXX,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┴────────┴────────┴────────┘                └────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_FN3] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,                 KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_7    ,KC_8    ,KC_9    ,KC_ASTR ,KC_PLUS ,KC_TRNS ,                 KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┘                └────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_4    ,KC_5    ,KC_6    ,KC_0    ,KC_MINS ,                                   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                  ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_1    ,KC_2    ,KC_3    ,KC_DOT  ,KC_SLSH ,                                   KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                ┌────────┼────────┼────────┴────────┼────────┼────────┼────────┤
     KC_TRNS ,KC_TRNS ,KC_INT3 ,KC_0    ,KC_TRNS ,KC_TRNS ,KC_TRNS ,                 KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
  //└────────┴────────┴────────┴────────┴────────┴────────┴────────┘                └────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  )
};

#ifdef RGBLIGHT_ENABLE
void eeconfig_init_user(void) {
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
};
#endif
