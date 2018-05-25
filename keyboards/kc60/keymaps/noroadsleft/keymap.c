
#include QMK_KEYBOARD_H
#include <sendstring_dvorak.h>

// Layer Definitions
#define _QW 0
#define _DV 1
#define _FW 2
#define _FM 3
#define _NP 4
#define _MA 5
//#define _Q2 6


// Keycode Definitions
#define _______ KC_TRNS
#define NO_CHNG KC_TRNS // Note for me for keys I need to leave as Pass-through
#define XXXXXXX KC_NO

#define FW_CAPS LT(_FW, KC_CAPS) // _FW when held, Caps when tapped
#define FM_CAPS LT(_FM, KC_CAPS) // _FM when held, Caps when tapped

#define MC_PSCR LGUI(LSFT(KC_3)) // MacOS Print Screen (Command + Shift + 3)
#define MC_HOME LGUI(KC_LEFT)    // MacOS Home (Command + Left Arrow)
#define MC_END  LGUI(KC_RGHT)    // MacOS End (Command + Right Arrow)
#define MC_UNDO LGUI(KC_Z)       // MacOS Undo
#define MC_CUT  LGUI(KC_X)       // MacOS Cut
#define MC_COPY LGUI(KC_C)       // MacOS Copy
#define MC_PSTE LGUI(KC_V)       // MacOS Paste


// Macro Definitions
enum custom_keycodes {
    M_L3DED = SAFE_RANGE,
    M_GITUP,
    M_GITDN,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case M_L3DED:
                SEND_STRING("lavak3DED "); // this is our macro!
                return false;
            case M_GITUP:
                SEND_STRING("git push "); // this is our macro!
                return false;
            case M_GITDN:
                SEND_STRING("git pull "); // this is our macro!
                return false;
        }
    }
    return true;
};

// Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* QWERTY */
  [_QW] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
    FW_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, KC_RGUI, MO(_FW), KC_RCTL  \
  ),

  /* Dvorak */
  [_DV] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSPC, \
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS, \
    FM_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, KC_ENT,           \
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,                   \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, KC_RGUI, MO(_FM), KC_RCTL  \
  ),

  /* Windows Fn layer */
  [_FW] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  \
    _______, KC_CALC, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_PSCR, KC_SLCK, KC_PAUS, \
    NO_CHNG, _______, _______, _______, _______, _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, KC_PENT,          \
    _______, _______, KC_APP,  BL_DEC,  BL_TOGG, BL_INC,  BL_BRTG, KC_MUTE, KC_VOLD, KC_VOLU, DF(_DV), _______,                   \
    _______, _______, _______,                   TG(_NP),                                     _______, MO(_MA), NO_CHNG, _______  \
  ),

  /* MacOS Fn layer */
  [_FM] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  \
    _______, _______, _______, _______, _______, _______, _______, MC_HOME, KC_UP,   MC_END,  _______, MC_PSCR, _______, _______, \
    NO_CHNG, _______, _______, BL_DEC,  BL_TOGG, BL_INC,  BL_BRTG, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______,          \
    _______, MC_UNDO, MC_CUT,  MC_COPY, MC_PSTE, _______, _______, _______, _______, _______, DF(_QW), _______,                   \
    _______, _______, _______,                   TG(_NP),                                     _______, _______, NO_CHNG, _______  \
  ),

  /* Numpad layer */
  [_NP] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PAST, KC_PSLS, KC_PEQL, _______, \
    _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, KC_PMNS, KC_PENT,          \
    _______, _______, _______, _______, _______, _______, _______, KC_P0,   _______, KC_PDOT, _______, _______,                   \
    _______, _______, _______,                   TG(_NP),                                     _______, _______, NO_CHNG, _______  \
  ),

  /* Macro layer */
  [_MA] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, M_GITUP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, M_GITDN, _______, _______, _______, _______, _______, _______, M_L3DED, _______, _______, _______,          \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   \
    RESET,   _______, _______,                   _______,                                     _______, NO_CHNG, NO_CHNG, _______  \
  ),

};


const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  return MACRO_NONE;
};
