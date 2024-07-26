
#include QMK_KEYBOARD_H

// enable dynamic macro recording
enum root_keycodes {
  FN_LAYR = SAFE_RANGE,
  DYNAMIC_MACRO_RANGE,
};

enum {
  DEF = 0,
  FN1,
  NUM,
  DYN,
};

#include "dynamic_macro.h"


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint16_t macro_kc = (keycode == MO(DYN) ? QK_DYNAMIC_MACRO_RECORD_STOP : keycode);
  
  if (!process_record_dynamic_macro(macro_kc, record)) {
      return false;
  }

  return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* LAYOUT_60_iso_5x1u_split_rshift
 *
 * DEF
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ESC│1  │2  │3  │4  │5  │6  │7  │8  │9  │0  │ß  │´  │Backspc│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │Tab  │Q  │W  │E  │R  │T  │Z  │U  │I  │O  │P  │Ü  │+  │Enter│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │MO1   │A  │S  │D  │F  │G  │H  │J  │K  │L  │Ö  │Ä  │#  │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┤
 * │LSFT│<  │Y  │X  │C  │V  │B  │N  │M  │,  │.  │-  │RShift│MO3│
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
 * │Ctrl│Win │Alt │         Space          │AGr│ ← │ ↓ │ ↑ │ → │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
 *
 * FN1
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │^  │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Del    │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │Rst│   │   │   │   │   │Prt│ScL│Pau│     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │TO2│   │   │Ins│Del│NuL│    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┤
 * │LSFT│   │   │   │MPl│MSt│MPv│MNx│Mut│Vo-│Vo+│   │RShift│   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
 * │Ctrl│Win │Alt │          Ctrl          │AGr│Hom│PgD│PgU│End│
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
 *
 * NUM
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │TO0│   │   │   │   │   │   │7  │8  │9  │   │   │   │Backspc│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │4  │5  │6  │   │   │   │Enter│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │1  │2  │3  │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┤
 * │    │   │   │   │   │   │   │0  │0  │,  │.  │-  │RShift│   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
 * │    │    │    │                        │AGr│   │   │   │   │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
 *
 * DYN
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │MSp│   │   │   │   │   │   │   │   │   │   │   │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │RTg│RMo│RDe│RIn│   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │HDe│HIn│SDe│SIn│   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │      │MSp│
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
 * │    │    │    │                        │   │MS1│MS2│MP1│MP2│
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
*/

#define MacRec1 DM_REC1
#define MacRec2 DM_REC2
#define MacPla1 DM_PLY1
#define MacPla2 DM_PLY2
#define MacStop DM_RSTP

  [DEF] = LAYOUT_60_iso_5x1u_split_rshift(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
    MO(FN1), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(DYN),
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),


  [FN1] = LAYOUT_60_iso_5x1u_split_rshift(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_SCRL, KC_PAUS,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(NUM), XXXXXXX, XXXXXXX, KC_INS,  KC_DEL,  KC_NUM,  XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, KC_RSFT, XXXXXXX,
    _______, _______, _______,                            KC_LCTL,                   _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),

  [NUM] = LAYOUT_60_iso_5x1u_split_rshift(
    TO(DEF), _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, XXXXXXX, XXXXXXX, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P4,   KC_P5,   KC_P6,   XXXXXXX, XXXXXXX, _______, 
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P1,   KC_P2,   KC_P3,   XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P0,   KC_P0,   _______, _______, _______, _______, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
   ),

  [DYN] = LAYOUT_60_iso_5x1u_split_rshift(
    MacStop, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, RGB_TOG, RGB_MOD, RGB_VAD, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
    XXXXXXX, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                   XXXXXXX, MacRec1, MacRec2, MacPla1, MacPla2
   ),
};

