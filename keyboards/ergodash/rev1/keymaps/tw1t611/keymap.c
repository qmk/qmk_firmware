#include QMK_KEYBOARD_H
#include "keymap_german.h"

enum layers {
  _QWERTZ,
  _MOD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTZ] = LAYOUT( \
    _______ ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,_______ ,                        KC_RSFT ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,_______ ,
    KC_ESC  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_BSPC ,                        KC_DEL  ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,DE_AE   ,
    KC_TAB  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,DE_UNDS ,                        KC_LALT ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,DE_EQL  ,DE_OE   ,
    _______ ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_SPC  ,                        KC_ENT  ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,DE_SS   ,DE_UE   ,
    _______ ,_______ ,_______ ,_______ ,         KC_LCTL ,KC_SPC  ,KC_LSFT ,      MO(_MOD) ,KC_ENT  ,KC_LGUI ,         _______ ,_______ ,_______ ,_______
  ),
  [_MOD] = LAYOUT(
    KC_F11  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,RGB_MOD ,                        RESET   ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F12  ,
    DE_CIRC ,DE_QUOT ,DE_DQOT ,DE_LCBR ,DE_RCBR ,DE_GRV  ,RGB_TOG ,                        _______ ,DE_PERC ,DE_PLUS ,DE_MINS ,DE_ASTR ,DE_SLSH ,DE_BSLS ,
    DE_TILD ,DE_EXLM ,DE_DLR  ,DE_LPRN ,DE_RPRN ,DE_AMPR ,RGB_M_P ,                        _______ ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,DE_QST  ,DE_PIPE ,
    _______ ,DE_AT   ,DE_EURO ,DE_LBRC ,DE_RBRC ,_______ ,_______ ,                        _______ ,DE_HASH ,DE_LESS ,DE_SCLN ,DE_COLN ,DE_MORE ,DE_PARA ,
    _______ ,_______ ,_______ ,_______ ,         _______ ,_______ ,_______ ,      _______ ,_______ ,_______ ,         _______ ,_______ ,_______ ,_______ 
  ),
};