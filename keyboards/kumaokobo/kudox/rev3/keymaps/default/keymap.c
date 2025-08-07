// Copyright Kumao Kobo <kumaokobo@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMB 1
#define _LIGHT 2

// Shortcut to make keymap more readable
#define SYM_L2  LT(_SYMB, KC_LNG2)
#define TO_LIGH TO(_LIGHT)
#define TO_QWER TO(_QWERTY)

#define KC_ALES LALT_T(KC_ESC)
#define KC_ALEN LALT_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_6    ,                 KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS, KC_EQL  ,KC_BSPC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_ESC  ,                 KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_SLSH ,KC_BSLS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┘                └────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,                                   KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_ENT  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                  ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,                                   KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_UP   ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                ┌────────┼────────┼────────┴────────┼────────┼────────┼────────┤
     KC_ALES ,KC_LBRC ,KC_RBRC ,SYM_L2  ,KC_ALEN ,KC_LGUI ,KC_SPC  ,                 KC_SPC  ,KC_RGUI ,TO_LIGH ,KC_LNG1 ,KC_LEFT, KC_DOWN ,KC_RIGHT
  //└────────┴────────┴────────┴────────┴────────┴────────┴────────┘                └────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                 KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_DEL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_DQUO ,KC_QUOT ,KC_GRV  ,KC_ASTR ,KC_PLUS ,KC_EQL  ,                 KC_LPRN ,KC_RPRN ,KC_PIPE ,KC_ASTR ,KC_TILD ,KC_CIRC ,KC_PIPE ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┘                └────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_AT   ,KC_COLN ,KC_GRV  ,KC_SLSH ,KC_MINS ,                                   KC_LBRC ,KC_RBRC ,KC_DOT  ,KC_SLSH ,KC_MINS ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                  ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                   KC_LCBR ,KC_RCBR ,_______ ,_______ ,KC_CIRC ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                ┌────────┼────────┼────────┴────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                 _______ ,_______ ,_______ ,_______ ,KC_LABK ,KC_UNDS ,KC_RABK
  //└────────┴────────┴────────┴────────┴────────┴────────┴────────┘                └────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_LIGHT] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,UG_HUEU ,UG_HUED ,UG_SATU ,UG_SATD ,UG_VALU ,UG_VALD ,                 UG_HUEU ,UG_HUED ,UG_SATU ,UG_SATD ,UG_VALU ,UG_VALD ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,RGB_M_P ,RGB_M_SW ,RGB_M_X,XXXXXXX ,XXXXXXX ,XXXXXXX ,                 RGB_M_P ,RGB_M_SW ,RGB_M_X,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┘                └────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,RGB_M_B ,RGB_M_SN ,RGB_M_G,XXXXXXX ,XXXXXXX ,                                   RGB_M_B ,RGB_M_SN,RGB_M_G ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                  ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,RGB_M_R ,RGB_M_K ,RGB_M_T ,XXXXXXX ,XXXXXXX ,                                   RGB_M_R ,RGB_M_K ,RGB_M_T ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                ┌────────┼────────┼────────┴────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,UG_NEXT ,UG_TOGG ,                 UG_TOGG ,UG_NEXT ,TO_QWER ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┴────────┴────────┴────────┘                └────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  )

};


#ifdef RGBLIGHT_ENABLE
void eeconfig_init_user(void) {
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
};
#endif
