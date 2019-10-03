
#include QMK_KEYBOARD_H

// enable dynamic macro recording
enum root_keycodes {
  FN_LAYR = SAFE_RANGE,
  DYNAMIC_MACRO_RANGE,
};

enum {
  DEF = 0,
  FUN,
  DYN,
  NUM,
};

#include "dynamic_macro.h"


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint16_t macro_kc = (keycode == MO(DYN) ? DYN_REC_STOP : keycode);
  
  if (!process_record_dynamic_macro(macro_kc, record)) {
      return false;
  }

  // make FN and FN + RSHIFT work for layers 2 and 3 to start recording with FN+RSHIFT+1 and play the recording with FN+1
  // WIP so pls try after keyboard works as intendet.
/*  bool rshift_pressed = false;
    switch (keycode) {
      case FN_LAYR:
        if (record->event.pressed) {
          if (keyboard_report->mods & MOD_BIT(KC_RSFT)) {
            // if FN + RSHIFT are pressed
            rshift_pressed = true;
            layer_on(3);
          } else {
            // if FN is pressed
            layer_on(2);
          }
        } else {
          // if FN is released
          layer_on(0);

          if (rshift_pressed) {
            layer_off(3);
            rshift_pressed = false;
          } else {
            layer_off(2);
          }
        }
    }*/

  return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* LAYOUT_60_iso_5x1u_split
 *
 * LAYER 1
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ESC│1  │2  │3  │4  │5  │6  │7  │8  │9  │0  │ß  │´  │Backspc│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │Tab  │Q  │W  │E  │R  │T  │Z  │U  │I  │O  │P  │Ü  │+  │Enter│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │MO1   │A  │S  │D  │F  │G  │H  │J  │K  │L  │Ö  │Ä  │#  │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┤
 * │LSFT│<  │Y  │X  │C  │V  │B  │N  │M  │,  │.  │-  │RShift│MO2│
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
 * │Ctrl│Win │Alt │         Space          │AGr│ ← │ ↓ │ ↑ │ → │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
 *
 * LAYER 2
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │^  │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Del    │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │Rst│   │   │   │   │   │Prt│ScL│Pau│     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │Ltg│Lbr│Lde│Lin│   │   │TG3│   │   │Ins│Del│NuL│    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┤
 * │LSFT│   │   │   │MPl│MSt│MPv│MNx│Mut│Vo-│Vo+│   │RShift│   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
 * │Ctrl│Win │Alt │          Ctrl          │AGr│Hom│PgD│PgU│End│
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
 *
 * DYNAMIC MACROS
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │MSp│MS1│MS2│   │   │   │   │   │   │   │   │   │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │MP1│MP2│   │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │      │MSp│
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
 * │    │    │    │                        │   │   │   │   │   │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
 *
 * NUMPAD
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┤
 * │    │   │   │   │   │   │   │   │   │   │   │   │      │   │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
 * │    │    │    │                        │   │   │   │   │   │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
*/

#define MacRec1 DYN_REC_START1
#define MacRec2 DYN_REC_START2
#define MacPla1 DYN_MACRO_PLAY1
#define MacPla2 DYN_MACRO_PLAY2
#define MacStop DYN_REC_STOP

  [DEF] = LAYOUT_60_iso_5x1u_split(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
    MO(FUN), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(DYN),
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),


  [FUN] = LAYOUT_60_iso_5x1u_split(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS,
    _______, BL_TOGG, BL_BRTG, BL_DEC,  BL_INC,  XXXXXXX, XXXXXXX, TG(NUM), XXXXXXX, XXXXXXX, KC_INS,  KC_DEL,  KC_NLCK, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, KC_RSFT, XXXXXXX,
    _______, _______, _______,                            KC_LCTL,                   _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),

  [DYN] = LAYOUT_60_iso_5x1u_split(
    MacStop, MacRec1, MacRec2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, MacPla1, MacPla2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,
    XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
   ),

  [NUM] = LAYOUT_60_iso_5x1u_split(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
   ),

};
