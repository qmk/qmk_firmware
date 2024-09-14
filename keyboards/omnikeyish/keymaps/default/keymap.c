#include QMK_KEYBOARD_H

#define M_PROG DYN_MACRO_PROG

/*    COL1             COL2                  COL3     COL4     COL5     COL6     COL7     COL8     COL9     COL10    COL11    COL12    COL13    COL14    COL15    COL16        COL17    COL18    COL19        COL20    COL21    COL22    COL23 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT_all(
  	  DYN_MACRO_KEY11, DYN_MACRO_KEY12,      KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,      KC_PSCR, KC_SCRL, KC_PAUS,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  	  DYN_MACRO_KEY1,  DYN_MACRO_KEY2,       KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,     KC_INS,  KC_HOME, KC_PGUP,     M_PROG,  KC_PSLS, KC_PAST, KC_PMNS,
  	  DYN_MACRO_KEY3,  DYN_MACRO_KEY4,       KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,     KC_DEL,  KC_END,  KC_PGDN,     KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
  	  DYN_MACRO_KEY5,  DYN_MACRO_KEY6,       KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,      KC_MPRV, KC_MPLY, KC_MNXT,     KC_P4,   KC_P5,   KC_P6,   KC_PEQL,
  	  DYN_MACRO_KEY7,  DYN_MACRO_KEY8,       KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_BSLS,     DB_TOGG, KC_UP,   QK_BOOT,     KC_P1,   KC_P2,   KC_P3,   KC_PENT,
  	  DYN_MACRO_KEY9,  DYN_MACRO_KEY10,      KC_LCTL, KC_LGUI, KC_LALT,                                     KC_SPACE,                  KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,     KC_LEFT, KC_DOWN, KC_RGHT,     KC_P0,            KC_PDOT)
};
