
#include QMK_KEYBOARD_H
#include "quantum.h"
#include "rgblight.h"
#include "tominabox1.h"
#include "mini.h"

//Tap Dance Declarations
enum {
  TD_QUES_ENT = 0,
  TD_SPC_SHFT = 1,
  TD_CTRL_Z = 2,
  TD_CTRL_Y = 3,
  TD_CTRL_C = 4,
  TD_CTRL_V = 5,
  TD_CTRL_A = 6,
  TD_P_BSLS = 7,
  TD_QUOTE = 8,
  TD_SDCOL = 9
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for /?, twice for Enter
  [TD_QUES_ENT]  = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_ENT),
  [TD_SPC_SHFT]  = ACTION_TAP_DANCE_DOUBLE(KC_SPACE, KC_LSFT),
  [TD_CTRL_Z]    = ACTION_TAP_DANCE_DOUBLE(KC_Z, LCTL(KC_Z)),
  [TD_CTRL_Y]    = ACTION_TAP_DANCE_DOUBLE(KC_Y, LCTL(KC_Y)),
  [TD_CTRL_C]    = ACTION_TAP_DANCE_DOUBLE(KC_C, LCTL(KC_C)),
  [TD_CTRL_V]    = ACTION_TAP_DANCE_DOUBLE(KC_V, LCTL(KC_V)),
  [TD_CTRL_A]    = ACTION_TAP_DANCE_DOUBLE(KC_A, LCTL(KC_A)),
  [TD_P_BSLS]    = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_BSLS),
  [TD_QUOTE]     = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_DQT),
  [TD_SDCOL]     = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN)
  // Other declarations would go here, separated by commas, if you have them
};

enum combos {
  combo_ESC,
  combo_BACK,
  combo_TAB,
  combo_PINKYCTRL,
  combo_DELETE,
  combo_ALT
};

const uint16_t PROGMEM esc_combo[] = {KC_1, KC_2, COMBO_END};
const uint16_t PROGMEM bspc_combo[] = {KC_9, KC_0, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM pinkyctrl_combo[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_1, KC_0, COMBO_END};
const uint16_t PROGMEM alt_combo[] = {KC_COMM, KC_DOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [combo_ESC] = COMBO(esc_combo, KC_ESC),
  [combo_BACK] = COMBO(bspc_combo, KC_BSPC),
  [combo_TAB] = COMBO(tab_combo, KC_TAB),
  [combo_PINKYCTRL] = COMBO(pinkyctrl_combo, KC_LCTRL),
  [combo_DELETE] = COMBO(del_combo, KC_DEL),
  [combo_ALT] = COMBO(alt_combo, KC_LALT)
};

#define FN MO(_RAISE)
#define LN MO(_LOWER)

#define xxx KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_space_base(
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
    KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN,
    KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E,  KC_I,KC_O,
    KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, TD(TD_QUES_ENT),
            KC_LALT, KC_LGUI, MT(MOD_LSFT, KC_SPC), MO(_ARROW)
  ),
  // 
  // [_RAISE] = LAYOUT_split_space_base(
  //   TD(TD_QUOTE),      xxx,      xxx,     xxx,     xxx,     xxx,      xxx,       xxx,     KC_PLUS,      KC_MINS,
  //   TD(TD_SDCOL),     KC_UP,     xxx,     xxx,     xxx,     xxx,      xxx,       xxx,      KC_EQL,      KC_UNDS,
  //   KC_LEFT,         KC_DOWN,  KC_RGHT,   xxx,     xxx,     xxx,     xxx,      xxx,   TD(TD_SDCOL),     xxx,
  //   xxx,               xxx,      xxx,     xxx,     xxx,     xxx,    KC_LCBR,   KC_RCBR,     xxx,       	KC_BSLS,
  //                                         LN
  // ),
  //
  // [_LOWER] = LAYOUT_split_space_base(
  //   xxx,          xxx,       xxx,       xxx,       xxx,     xxx,     xxx,     xxx,      xxx,     xxx,
  //   xxx,          xxx,       xxx,       xxx,       xxx,     xxx,     xxx,     xxx,      xxx,     xxx,
  //   LCTL(KC_A),   xxx,       xxx,       xxx,       xxx,     xxx,     xxx,     xxx,      xxx,     xxx,
  //   LCTL(KC_Z),   xxx,   LCTL(KC_C), LCTL(KC_V),   xxx,     xxx,     xxx,     xxx,      xxx,   KC_PIPE,
  //                                       xxx
  // )
};
