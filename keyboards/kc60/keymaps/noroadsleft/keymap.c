
#include QMK_KEYBOARD_H
#include <sendstring_dvorak.h>


/**********************
** LAYER DEFINITIONS **
**********************/

// BASE LAYERS
#define _QWERTY 0
#define _DVORAK 1
#define _QUAKE2 2
#define _QUAKE2_DVORAK 3
#define _QUAKE2_CONSOLE 4

// FUNCTION LAYERS
#define _FUNCWIN 5
#define _FUNCMAC 6
#define _FUNCQ2 7

// OTHER LAYERS
#define _NUMPAD 8
#define _MACROS 9
#define _SYSTEM 10

// LAYER SHORT CODES
#define _QW _QWERTY
#define _DV _DVORAK
#define _Q2 _QUAKE2
#define _QD _QUAKE2_DVORAK
#define _QC _QUAKE2_CONSOLE
#define _FW _FUNCWIN
#define _FM _FUNCMAC
#define _FQ _FUNCQ2
#define _NP _NUMPAD
#define _MA _MACROS
#define _SY _SYSTEM


// KEYCODE DEFINITIONS
#define _______ KC_TRNS
#define NO_CHNG KC_TRNS // Note for me for keys I need to leave as Pass-through
#define XXXXXXX KC_NO

#define FW_CAPS LT(_FUNCWIN, KC_CAPS) // _FUNCWIN when held, Caps Lock when tapped
#define FM_CAPS LT(_FUNCMAC, KC_CAPS) // _FUNCMAC when held, Caps Lock when tapped
#define Q2_CAPS LT(_FUNCQ2, KC_CAPS)  // _FUNCQ2 when held, Caps Lock when tapped

#define MC_PSCR LGUI(LSFT(KC_3)) // MacOS Print Screen (Command + Shift + 3)
#define MC_HOME LGUI(KC_LEFT)    // MacOS Home (Command + Left Arrow)
#define MC_END  LGUI(KC_RGHT)    // MacOS End (Command + Right Arrow)
#define MC_SALL LGUI(KC_A)       // MacOS Select All
#define MC_UNDO LGUI(KC_Z)       // MacOS Undo
#define MC_CUT  LGUI(KC_X)       // MacOS Cut
#define MC_COPY LGUI(KC_C)       // MacOS Copy
#define MC_PSTE LGUI(KC_V)       // MacOS Paste



// MACRO DEFINITIONS
enum custom_keycodes {
    T_L3DED = SAFE_RANGE,
    G_PUSH,
    G_FTCH,
    G_COMM,
    G_RST,
    G_C10R,
    G_BRCH,
    SIGNA,
    GO_Q2,
    Q2_ON,
    Q2_OFF,
    Q2_ESC,
    Q2_GRV,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            // these are our macros!
            case T_L3DED:
                SEND_STRING("lavak3DED ");
                return false;
            case G_PUSH:
                SEND_STRING("git push origin ");
                return false;
            case G_FTCH:
                SEND_STRING("git fetch upstream");
                return false;
            case G_COMM:
                SEND_STRING("git commit -m \"\"" SS_TAP(X_LEFT));
                layer_off(_MACROS);
                return false;
            case G_RST:
                SEND_STRING("git histt -n 10" SS_TAP(X_ENTER) "git reset --soft ");
                layer_off(_MACROS);
                return false;
            case G_C10R:
                SEND_STRING("cf/");
                layer_off(_MACROS);
                return false;
            case G_BRCH:
                SEND_STRING("$(git branch-name)");
                layer_off(_MACROS);
                return false;
            case SIGNA:
                SEND_STRING("\\- @noroadsleft" SS_TAP(X_ENTER));
                layer_off(_MACROS);
                return false;
            case GO_Q2:
                //default_layer_set(_QWERTY);
                layer_move(_QWERTY); // TO(_QWERTY);
                layer_on(_QUAKE2);
                //layer_off(_SYSTEM);
                return false;
            case Q2_ON:
                SEND_STRING(SS_TAP(X_ENTER));
                layer_on(_DVORAK);
                layer_on(_QUAKE2_DVORAK);
                return false;
            case Q2_OFF:
                SEND_STRING(SS_TAP(X_ENTER));
                layer_move(_QWERTY); // TO(_QWERTY);
                layer_on(_QUAKE2);
                return false;
            case Q2_ESC:
                SEND_STRING(SS_TAP(X_ESCAPE));
                layer_move(_QWERTY); // TO(_QWERTY);
                layer_on(_QUAKE2);
                return false;
            case Q2_GRV:
                SEND_STRING(SS_TAP(X_GRAVE));
                layer_on(_DVORAK);
                layer_on(_QUAKE2_DVORAK);
                layer_on(_QUAKE2_CONSOLE);
                return false;
        }
    }
    return true;
};

// KEYMAPS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /****************
  ** BASE LAYERS **
  ****************/

  /* QWERTY */
  [_QWERTY] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
    FW_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, KC_RGUI, MO(_FW), KC_RCTL  \
  ),

  /* Dvorak */
  [_DVORAK] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSPC, \
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS, \
    FM_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, KC_ENT,           \
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,                   \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, KC_RGUI, MO(_FM), KC_RCTL  \
  ),

  /*************
  ** OVERLAYS **
  *************/

  /* Quake 2 */
  [_QUAKE2] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    Q2_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, Q2_ON,            \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   \
    _______, _______, _______,                   _______,                                     _______, _______, MO(_FQ), _______  \
  ),

  [_QUAKE2_DVORAK] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    Q2_ESC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    Q2_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, Q2_OFF,           \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   \
    _______, _______, _______,                   _______,                                     _______, _______, MO(_FQ), _______  \
  ),

  [_QUAKE2_CONSOLE] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    Q2_ESC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    Q2_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ENT,           \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   \
    _______, _______, _______,                   _______,                                     _______, _______, MO(_FQ), _______  \
  ),

  /********************
  ** FUNCTION LAYERS **
  ********************/

  /* Windows Fn layer */
  [_FUNCWIN] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  \
    _______, KC_CALC, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_PSCR, KC_SLCK, KC_PAUS, \
    NO_CHNG, _______, _______, _______, _______, _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, KC_PENT,          \
    _______, _______, KC_APP,  _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, TG(_SY), _______,                   \
    _______, _______, _______,                   TG(_NP),                                     _______, TG(_MA), NO_CHNG, _______  \
  ),

  /* MacOS Fn layer */
  [_FUNCMAC] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  \
    _______, _______, _______, _______, _______, _______, KC_INS,  MC_HOME, KC_UP,   MC_END,  KC_PGUP, MC_PSCR, _______, _______, \
    NO_CHNG, MC_SALL, _______, _______, _______, _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______,          \
    _______, MC_UNDO, MC_CUT,  MC_COPY, MC_PSTE, _______, _______, _______, _______, _______, TG(_SY), _______,                   \
    _______, _______, _______,                   TG(_NP),                                     _______, _______, NO_CHNG, _______  \
  ),

  /* Quake 2 Fn layer */
  [_FUNCQ2] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    Q2_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  \
    _______, _______, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_PSCR, KC_SLCK, KC_PAUS, \
    NO_CHNG, _______, _______, _______, _______, _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, KC_ENT,           \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TG(_SY), _______,                   \
    _______, _______, _______,                   _______,                                     _______, _______, NO_CHNG, _______  \
  ),

  /*****************
  ** OTHER LAYERS **
  *****************/

  /* Numpad layer */
  [_NUMPAD] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, _______, _______, _______, \
    _______, _______, _______, _______, KC_E,    KC_F,    _______, KC_P4,   KC_P5,   KC_P6,   KC_PAST, KC_PSLS, KC_PEQL, _______, \
    _______, _______, _______, _______, KC_C,    KC_D,    _______, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, KC_PMNS, KC_PENT,          \
    _______, _______, _______, _______, KC_A,    KC_B,    _______, KC_P0,   _______, KC_PDOT, _______, _______,                   \
    _______, _______, _______,                   TG(_NP),                                     _______, _______, NO_CHNG, _______  \
  ),

  /* Macro layer */
  [_MACROS] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    TG(_MA), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, G_PUSH,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, G_RST,   G_FTCH,  G_COMM,  _______, _______, _______, _______, T_L3DED, _______, _______, _______,          \
    _______, _______, _______, G_C10R,  _______, G_BRCH,  SIGNA,   _______, _______, _______, _______, _______,                   \
    _______, _______, _______,                   _______,                                     _______, _______, NO_CHNG, _______  \
  ),

  /* System layer */
  [_SYSTEM] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
    TG(_SY), TO(_QW), TO(_DV), GO_Q2,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,   XXXXXXX, DEBUG,   XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          \
    XXXXXXX, XXXXXXX, XXXXXXX, BL_DEC,  BL_TOGG, BL_INC,  BL_BRTG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   \
    XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,                                     XXXXXXX, XXXXXXX, NO_CHNG, XXXXXXX  \
  ),

};


const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  return MACRO_NONE;
};
