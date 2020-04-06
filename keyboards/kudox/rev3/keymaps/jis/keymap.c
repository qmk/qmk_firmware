#include QMK_KEYBOARD_H
#include"keymap_jp.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMB 1
#define _LIGHT 2

// Shortcut to make keymap more readable
#define SYM_L2  LT(_SYMB, KC_LANG2)
#define TO_LIGH TO(_LIGHT)
#define TO_QWER TO(_QWERTY)

#define KC_ALES LALT_T(KC_ESC)
#define KC_ALEN LALT_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     JP_ZKHK ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_6    ,                 KC_7    ,KC_8    ,KC_9    ,KC_0    ,JP_MINS ,JP_CIRC ,KC_BSPC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_ESC  ,                 KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,JP_AT   ,JP_SLSH ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┘                └────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,                                   KC_H    ,KC_J    ,KC_K    ,KC_L    ,JP_SCLN ,KC_ENT  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                  ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,                                   KC_N    ,KC_M    ,JP_COMM ,JP_DOT  ,KC_UP   ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                ┌────────┼────────┼────────┴────────┼────────┼────────┼────────┤
     KC_ALES ,JP_YEN  ,JP_COLN ,SYM_L2  ,KC_ALEN ,KC_LGUI ,KC_SPC  ,                 KC_SPC  ,KC_RGUI ,TO_LIGH ,KC_LANG1,KC_LEFT, KC_DOWN ,KC_RIGHT
  //└────────┴────────┴────────┴────────┴────────┴────────┴────────┘                └────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                 KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_DEL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,JP_DQUO ,JP_QUOT ,KC_GRV  ,JP_ASTR ,JP_PLUS ,JP_EQL  ,                 JP_LPRN ,JP_RPRN ,JP_PIPE ,JP_ASTR ,JP_TILD ,JP_CIRC ,JP_PIPE ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┘                └────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,JP_AT   ,JP_COLN ,KC_GRV  ,JP_SLSH ,JP_MINS ,                                   JP_LBRC ,JP_RBRC ,JP_DOT  ,JP_SLSH ,JP_MINS ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                  ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                   JP_LCBR ,JP_RCBR ,_______ ,_______ ,JP_CIRC ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                ┌────────┼────────┼────────┴────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                 _______ ,_______ ,_______ ,_______ ,JP_LABK ,JP_UNDS ,JP_RABK
  //└────────┴────────┴────────┴────────┴────────┴────────┴────────┘                └────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_LIGHT] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,RGB_HUI ,RGB_HUD ,RGB_SAI ,RGB_SAD ,RGB_VAI ,RGB_VAD ,                 RGB_HUI ,RGB_HUD ,RGB_SAI ,RGB_SAD ,RGB_VAI ,RGB_VAD ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,RGB_M_P ,RGB_M_SW ,RGB_M_X,XXXXXXX ,XXXXXXX ,XXXXXXX ,                 RGB_M_P ,RGB_M_SW ,RGB_M_X ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┘                └────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,RGB_M_B ,RGB_M_SN ,RGB_M_G,XXXXXXX ,XXXXXXX ,                                   RGB_M_B ,RGB_M_SN ,RGB_M_G ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                  ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,RGB_M_R ,RGB_M_K ,RGB_M_T ,XXXXXXX ,XXXXXXX ,                                   RGB_M_R ,RGB_M_K ,RGB_M_T ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                ┌────────┼────────┼────────┴────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,RGB_MOD ,RGB_TOG ,                 RGB_TOG ,RGB_MOD ,TO_QWER ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┴────────┴────────┴────────┘                └────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  )

};
