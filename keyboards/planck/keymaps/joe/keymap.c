#include QMK_KEYBOARD_H
#include "keymap_colemak.h"

#define FN3_ESC LT(6, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_planck_grid( /* Joe colemak */
    FN3_ESC, KC_Q,    KC_W,    KC_F,    KC_P, KC_G,   KC_J,   KC_L, KC_U,    KC_Y,    KC_SCLN, KC_MINS,
    KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T, KC_D,   KC_H,   KC_N, KC_E,    KC_I,    KC_O,    KC_ENT ,
    F(15),   KC_Z,    KC_X,    KC_C,    KC_V, KC_B,   KC_K,   KC_M, KC_COMM, KC_DOT,  KC_UP,   KC_QUOT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_LSFT, MO(4),KC_SPC, KC_SPC, MO(5),KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [1] = LAYOUT_planck_grid( /* Joe soft Colemak */
    FN3_ESC, CM_Q,    CM_W,    CM_F,    CM_P, CM_G,   CM_J,   CM_L, CM_U,    CM_Y,    CM_SCLN, KC_MINS,
    KC_BSPC, CM_A,    CM_R,    CM_S,    CM_T, CM_D,   CM_H,   CM_N, CM_E,    CM_I,    CM_O,    KC_ENT ,
    F(15),   CM_Z,    CM_X,    CM_C,    CM_V, CM_B,   CM_K,   CM_M, KC_COMM, KC_DOT,  KC_UP,   KC_QUOT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_LSFT, MO(4),KC_SPC, KC_SPC, MO(5),KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [2] = LAYOUT_planck_grid( /* Joe NUMPAD */
    FN3_ESC, KC_NO,   KC_UP,   KC_NO,   KC_NO, KC_NO,   LSFT(KC_9), LSFT(KC_0), KC_PSLS, KC_P7, KC_P8,   KC_P9  ,
    KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO,   LSFT(KC_5), KC_PEQL,    KC_PAST, KC_P4, KC_P5,   KC_P6  ,
    F(15),   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,      KC_PCMM,    KC_PMNS, KC_P1, KC_P2,   KC_P3  ,
    KC_LCTL, KC_LGUI, KC_LALT, KC_LSFT, MO(4), KC_TRNS, KC_TRNS,    MO(5),      KC_PPLS, KC_P0, KC_PDOT, KC_PENT
  ),
  [3] = LAYOUT_planck_grid( /* Joe 1337 haxOr5*/
    FN3_ESC, KC_Q,    KC_W,    KC_F,    KC_P, KC_6,   KC_J,   KC_L, KC_U,    KC_Y,    KC_SCLN, KC_MINS,
    KC_BSPC, KC_4,    KC_R,    KC_5,    KC_7, KC_D,   KC_H,   KC_N, KC_3,    KC_1,    KC_0,    KC_ENT ,
    F(15),   KC_Z,    KC_X,    KC_C,    KC_V, KC_B,   KC_K,   KC_M, KC_COMM, KC_DOT,  KC_UP,   KC_QUOT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_LSFT, MO(4),KC_SPC, KC_SPC, MO(5),KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [4] = LAYOUT_planck_grid( /* Joe LOWER fn1 */
    KC_GRV,  KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO, M(3),    M(2),    M(1),    M(0)   ,
    KC_BSPC, KC_1,    KC_2,    KC_3,    KC_4,  KC_5,    KC_6,    KC_7,  KC_8,    KC_9,    KC_0,    KC_TRNS,
    KC_BSLS, KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO, KC_LBRC, KC_RBRC, KC_PGUP, KC_EQL ,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(4), KC_TRNS, KC_TRNS, MO(5), KC_NO,   KC_HOME, KC_PGDN, KC_END 
  ),
  [5] = LAYOUT_planck_grid( /* Joe UPPER fn2 */
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,              KC_F11,              KC_F12             ,
    KC_DEL,  KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, KC_WH_U, KC_BTN4, KC_LEFT, KC_DOWN, KC_UP,               KC_RGHT,             KC_NO              ,
    KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_L, KC_WH_D, KC_WH_R, KC_NO,   KC_NO,   LCTL(KC_PGUP),       LCTL(LALT(KC_UP)),   LCTL(KC_PGDN)      ,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(4),   KC_NO,   KC_NO,   MO(5),   KC_NO,   LCTL(LALT(KC_LEFT)), LCTL(LALT(KC_DOWN)), LCTL(LALT(KC_RGHT))
  ),
  [6] = LAYOUT_planck_grid( /* Joe SPECIAL fn3 */
    KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,    KC_NO,   KC_NO,   KC_NO           ,
    KC_NO,   KC_MPLY, KC_MPRV, KC_MNXT, KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,    KC_NO,   KC_NO,   RESET           ,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,    KC_NO,   KC_NO,   KC_NO           ,
    DF(0),   DF(1),   DF(2),   DF(3),   MO(4), KC_TRNS, KC_TRNS, MO(5), KC_POWER, KC_WAKE, KC_SLEP, LCTL(LALT(KC_L))
  )
};

const uint16_t PROGMEM fn_actions[] = {
    /* tab on tap, shift on hold */
    [15] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_TAB),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case 0:
            /* :) */
            return MACRODOWN( DOWN(KC_LSFT), TYPE(KC_SCLN), TYPE(KC_0), UP(KC_LSFT), END );
            break;
        case 1:
            /* :( */
            return MACRODOWN( DOWN(KC_LSFT), TYPE(KC_SCLN), TYPE(KC_9), UP(KC_LSFT), END );
            break;
        case 2:
            /* (: | :) */
            return MACRODOWN( DOWN(KC_LSFT), TYPE(KC_9), TYPE(KC_SCLN), TYPE(KC_SPC), TYPE(KC_SPC), TYPE(KC_SCLN), TYPE(KC_0), UP(KC_LSFT), TYPE(KC_LEFT), TYPE(KC_LEFT), TYPE(KC_LEFT), END );
            break;
        case 3:
            /* :( | ): */
            return MACRODOWN( DOWN(KC_LSFT), TYPE(KC_SCLN), TYPE(KC_9), TYPE(KC_SPC), TYPE(KC_SPC), TYPE(KC_0), TYPE(KC_SCLN), UP(KC_LSFT), TYPE(KC_LEFT), TYPE(KC_LEFT), TYPE(KC_LEFT), END );
            break;
        default:
            break;
    }
    return MACRO_NONE;
}
