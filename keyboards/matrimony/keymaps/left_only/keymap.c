#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FN1 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_A,  KC_B,  KC_C,  KC_D,  QK_GESC,   KC_1,    KC_2,    KC_3,     KC_4,   KC_5,   KC_6,      	KC_7,    KC_8,    KC_9,     KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  MO(_FN1),   KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, \
    KC_E,  KC_F,  KC_G,  KC_H,  KC_TAB,    KC_Q,    KC_W,    KC_E,     KC_R,   KC_T,   		KC_Y,   KC_U,    KC_I,    KC_O,     KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,  MO(_FN1),   KC_P7,   KC_P8,   KC_P9,   KC_PPLS, \
    KC_I,  KC_J,  KC_K,  KC_L,  KC_CAPS,   KC_A,    KC_S,    KC_D,     KC_F,   KC_G,   			KC_H,    KC_J,    KC_K,     KC_L,    KC_SCLN,  KC_QUOT, KC_ENT,   MO(_FN1), 	       KC_P4,   KC_P5,   KC_P6, \
    KC_M,  KC_N,  KC_O,  KC_P,  KC_LSFT,   KC_Z,    KC_X,    KC_C,     KC_V,   KC_B,   			KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,    MO(_FN1),            KC_P1,   KC_P2,   KC_P3, \
    KC_Q,  KC_R,  KC_S,  KC_T,  KC_LCTL,   KC_LGUI, KC_LALT, MO(_FN1), KC_SPC, 					 KC_SPC,  MO(_FN1), KC_RALT, KC_RCTL,  KC_LEFT, KC_DOWN,  KC_RIGHT, 	       KC_P0,   KC_PDOT, KC_PENT),
[_FN1] = LAYOUT(
    KC_PMNS,  KC_PAST, KC_PSLS, KC_NUM,     QK_GESC,   KC_1,    KC_2,    KC_3,     KC_4,   KC_5,   KC_6,      	        KC_7,    KC_8,    KC_9,     KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  MO(_FN1),   KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, \
    KC_PPLS,  KC_P9,   KC_P8,   KC_P7,      KC_TAB,    KC_Q,    KC_W,    KC_E,     KC_R,   KC_T,   		KC_Y,   KC_U,    KC_I,    KC_O,     KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,  MO(_FN1),   KC_P7,   KC_P8,   KC_P9,   KC_PPLS, \
    KC_P6,    KC_P5,   KC_P4,   KC_NO,      KC_CAPS,   KC_A,    KC_S,    KC_D,     KC_F,   KC_G,   			KC_H,    KC_J,    KC_K,     KC_L,    KC_SCLN,  KC_QUOT, KC_ENT,   MO(_FN1), 	       KC_P4,   KC_P5,   KC_P6, \
    KC_P3,    KC_P2,   KC_P1,   KC_NO,      KC_LSFT,   KC_Z,    KC_X,    KC_C,     KC_V,   KC_B,   			KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,    MO(_FN1),            KC_P1,   KC_P2,   KC_P3, \
    KC_PENT,  KC_PDOT, KC_P0,   KC_NO,      KC_LCTL,   KC_LGUI, KC_LALT, MO(_FN1), KC_SPC, 					 KC_SPC,  MO(_FN1), KC_RALT, KC_RCTL,  KC_LEFT, KC_DOWN,  KC_RIGHT, 	       KC_P0,   KC_PDOT, KC_PENT),
}; 
