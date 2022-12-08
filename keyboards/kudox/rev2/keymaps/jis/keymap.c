#include QMK_KEYBOARD_H
#include"keymap_japanese.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMB 1

// Shortcut to make keymap more readable
#define SYM_L   MO(_SYMB)

#define KC_ALES LALT_T(KC_ESC)

#define KC_L1SYM LT(_SYMB, KC_LNG1)
#define KC_L2SYM LT(_SYMB, KC_LNG2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_ESC  ,                 KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS ,KC_BSPC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_LNG2,                  KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,JP_AT   ,JP_COLN ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┘                └────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,                                   KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_ENT  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                  ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,                                   KC_UP   ,KC_N    ,KC_M    ,KC_SLSH ,JP_UNDS ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                ┌────────┼────────┼────────┴────────┼────────┼────────┼────────┤
     KC_ALES ,KC_LGUI ,KC_LALT ,KC_DEL  ,KC_L2SYM,KC_SPC  ,KC_ENT  ,                 KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_COMM ,KC_DOT  ,KC_L1SYM,JP_BSLS
  //└────────┴────────┴────────┴────────┴────────┴────────┴────────┘                └────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  ),

  [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,_______ ,                 KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,JP_LPRN ,JP_RPRN ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                 JP_HASH ,JP_DLR  ,JP_PERC ,JP_PLUS ,KC_MINS ,JP_CIRC ,JP_YEN  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┘                └────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,JP_LBRC ,JP_RBRC ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                   JP_AMPR ,KC_SLSH ,JP_ASTR ,KC_SCLN ,JP_COLN ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                  ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,JP_LCBR ,JP_RCBR ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                   KC_VOLU ,XXXXXXX ,XXXXXXX ,KC_LT   ,KC_GT   ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                ┌────────┼────────┼────────┴────────┼────────┼────────┼────────┤
     _______ ,_______ ,KC_LT   ,KC_GT   ,KC_LNG2 ,_______ ,_______ ,                 KC_MUTE ,KC_VOLD ,KC_LNG1 ,_______ ,_______ ,_______ ,KC_DEL
  //└────────┴────────┴────────┴────────┴────────┴────────┴────────┘                └────────┴────────┴────────┴────────┴────────┴────────┴────────┘
  )
};
