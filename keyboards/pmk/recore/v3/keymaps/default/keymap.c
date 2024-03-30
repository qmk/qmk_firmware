// Copyright 2024 Javier Oliver (@joliverMI)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum my_layers {
    _QWERTY,
    _NAV,
    _SYMB,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┬── L1 ──┬── X1 ──┐┌── X1 ──┬── L1 ──┬────────┬────────┬────────┬────────┬────────┬────────┐
   KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5   ,MO(_SYMB),MO(_NAV),MO(_NAV),MO(_SYMB),KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS ,
//├────────┼────────┼────────┼────────┼────────┼────────┼── X2 ──┼── X3 ──┤├── X3 ──┼── X2 ──┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_LBRC ,KC_MPLY, KC_PAUS ,KC_RBRC , KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_EQL  ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┘└────────┴────────┼────────┼────────┼────────┼────────┴────────┴────────┤
   KC_ESC  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,                                     KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_PGUP ,KC_PGDN , KC_HOME ,KC_END , KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┘└────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_LGUI ,KC_PMNS ,MO(_NAV) ,KC_LALT ,KC_LCTL ,KC_BSPC ,KC_DEL  ,                   KC_ENT, KC_SPC  ,MO(_NAV),KC_RALT ,KC_RCTL ,KC_LEFT ,KC_RGHT 
//└────────┴────────┴── T1 ──┴── T2 ──┴── T3 ──┴── T4 ──┴── T5 ──┘                  └── T5 ──┴── T4 ──┴── T3 ──┴── T2 ──┴── T1 ──┴────────┴────────┘
    ),
    [_SYMB] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┬── L1 ──┬── X1 ──┐┌── X1 ──┬── L1 ──┬────────┬────────┬────────┬────────┬────────┬────────┐
   _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,_______ ,_______,  _______ ,_______ ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,_______ ,
//├────────┼────────┼────────┼────────┼────────┼────────┼── X2 ──┼── X3 ──┤├── X3 ──┼── X2 ──┼────────┼────────┼────────┼────────┼────────┼────────┤
   _______ ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_PIPE ,_______ ,_______,  _______ ,KC_RCBR ,KC_PSLS ,KC_P7   ,KC_P8   ,KC_P9   ,KC_PMNS ,_______ ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┘└────────┴────────┼────────┼────────┼────────┼────────┴────────┴────────┤
   _______ ,KC_HASH ,KC_DLR  ,KC_LBRC ,KC_RBRC ,KC_GRV  ,                                     KC_PAST ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PPLS ,_______ ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   _______ ,KC_PERC ,KC_CIRC ,KC_LPRN ,KC_RPRN ,KC_TILD ,_______ ,_______ , _______ ,_______ ,KC_P0   ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PENT ,_______ ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┘└────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                   KC_ENT  ,_______ ,_______ ,_______ ,KC_PDOT ,KC_PENT ,_______ 
//└────────┴────────┴── T1 ──┴── T2 ──┴── T3 ──┴── T4 ──┴── T5 ──┘                  └── T5 ──┴── T4 ──┴── T3 ──┴── T2 ──┴── T1 ──┴────────┴────────┘
    ),
    [_NAV] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┬── L1 ──┬── X1 ──┐┌── X1 ──┬── L1 ──┬────────┬────────┬────────┬────────┬────────┬────────┐
   _______ ,XXXXXXX ,XXXXXXX ,KC_UP   ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX , XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_UP   ,XXXXXXX ,XXXXXXX ,QK_BOOT ,
//├────────┼────────┼────────┼────────┼────────┼────────┼── X2 ──┼── X3 ──┤├── X3 ──┼── X2 ──┼────────┼────────┼────────┼────────┼────────┼────────┤
   _______ ,XXXXXXX ,XXXXXXX ,KC_UP   ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX , XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_UP   ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┴────────┘└────────┴────────┼────────┼────────┼────────┼────────┴────────┴────────┤
   _______ ,KC_LEFT ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_RGHT ,                                     KC_LEFT ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_RGHT ,XXXXXXX ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   _______ ,XXXXXXX ,XXXXXXX ,KC_DOWN ,XXXXXXX ,XXXXXXX ,_______ ,_______ , _______ ,_______ ,XXXXXXX ,XXXXXXX ,KC_DOWN ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┘└────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   _______ ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,XXXXXXX ,XXXXXXX ,                   XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,XXXXXXX ,EE_CLR
//└────────┴────────┴── T1 ──┴── T2 ──┴── T3 ──┴── T4 ──┴── T5 ──┘                  └── T5 ──┴── T4 ──┴── T3 ──┴── T2 ──┴── T1 ──┴────────┴────────┘
    )
};
