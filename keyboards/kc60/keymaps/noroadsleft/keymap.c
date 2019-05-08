#include QMK_KEYBOARD_H
#include "version.h"
#include <sendstring_dvorak.h>
//#include <sendstring_colemak.h>
#include <print.h>


/**********************
** LAYER DEFINITIONS **
**********************/
enum layers_keymap {
    // BASE LAYERS
    _QWERTY = 0,
    _DVORAK,
    _COLEMAK,
    _MAC,
    _QUAKE2,
    _QUAKE2_DVORAK,
    _QUAKE2_CONSOLE,

    // FUNCTION LAYERS
    _FUNCWIN,
    _FUNCMAC,
    _FUNCQ2,

    // OTHER LAYERS
    _NUMPAD,
    _MACROS,
    _SYSTEM
};

// LAYER SHORT CODES
#define _QW _QWERTY
#define _DV _DVORAK
#define _CM _COLEMAK
#define _MC _MAC
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
#define NO_CHNG KC_TRNS // Note for me for keys I need to leave as Pass-through

#define FW_CAPS LT(_FUNCWIN, KC_CAPS) // _FUNCWIN when held, Caps Lock when tapped
#define FM_CAPS LT(_FUNCMAC, KC_CAPS) // _FUNCMAC when held, Caps Lock when tapped
#define Q2_CAPS LT(_FUNCQ2, KC_CAPS)  // _FUNCQ2 when held, Caps Lock when tapped

#define WN_SALL LCTL(DV_A)       // Windows/Linux Select All
#define WN_UNDO LCTL(DV_Z)       // Windows/Linux Undo
#define WN_CUT  LCTL(DV_X)       // Windows/Linux Cut
#define WN_COPY LCTL(DV_C)       // Windows/Linux Copy
#define WN_PSTE LCTL(DV_V)       // Windows/Linux Paste

#define MC_PSCR LGUI(LSFT(KC_3)) // MacOS Print Screen (Command + Shift + 3)
#define MC_HOME LGUI(KC_LEFT)    // MacOS Home (Command + Left Arrow)
#define MC_END  LGUI(KC_RGHT)    // MacOS End (Command + Right Arrow)
#define MC_SALL LGUI(KC_A)       // MacOS Select All
//#define MC_UNDO LGUI(KC_Z)       // MacOS Undo // replaced by macro
#define MC_CUT  LGUI(KC_X)       // MacOS Cut
#define MC_COPY LGUI(KC_C)       // MacOS Copy
//#define MC_PSTE LGUI(KC_V)       // MacOS Paste // replaced by macro


// MACRO DEFINITIONS
enum custom_keycodes {
    F_CAPS = SAFE_RANGE,
    T_L3DED,
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
    MC_UNDO,
    MC_PSTE,
    NUBS_Z,
    VRSN
};


/*******************
** MODIFIER MASKS **
*******************/
#define MOD_MASK_RALT   (MOD_BIT(KC_RALT))


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        // these are our macros!
        case F_CAPS:
            /*
             * Objective: write a macro that checks the current layers that are
             * enabled, and activates the appropriate function layer.
             */
            if ( biton32(layer_state) == _MAC ) {
                if (record->event.pressed) {
                    layer_on(_FUNCMAC);
                } else {
                    layer_off(_FUNCMAC);
                }
            } else {
                if (record->event.pressed) {
                    layer_on(_FUNCWIN);
                } else {
                    layer_off(_FUNCWIN);
                }
            };
            return false;
        case T_L3DED:
            if (record->event.pressed) {
                SEND_STRING("lavak3DED ");
            };
            return false;
        case G_PUSH:
            if (record->event.pressed) {
                SEND_STRING("git push origin ");
            };
            return false;
        case G_FTCH:
            if (record->event.pressed) {
                if ( get_mods() & MOD_MASK_SHIFT ) {
                    clear_mods();
                    SEND_STRING("git pull upstream ");
                } else {
                    SEND_STRING("git fetch upstream ");
                }
            };
            return false;
        case G_COMM:
            if (record->event.pressed) {
                SEND_STRING("git commit -m \"\"" SS_TAP(X_LEFT));
                layer_off(_MACROS);
            };
            return false;
        case G_BRCH:
            if (record->event.pressed) {
                if ( get_mods() & MOD_MASK_SHIFT ) {
                    clear_mods();
                    SEND_STRING("master");
                } else {
                    SEND_STRING("$(git branch-name)");
                }
                layer_off(_MACROS);
            };
            return false;
        case SIGNA:
            if (record->event.pressed) {
                SEND_STRING("\\- @noroadsleft" SS_TAP(X_ENTER));
                layer_off(_MACROS);
            };
            return false;
        case GO_Q2:
            if (record->event.pressed) {
                //default_layer_set(_QWERTY);
                layer_move(_QWERTY); // TO(_QWERTY);
                layer_on(_QUAKE2);
                //layer_off(_SYSTEM);
            };
            return false;
        case Q2_ON:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ENTER));
                layer_on(_DVORAK);
                layer_on(_QUAKE2_DVORAK);
            };
            return false;
        case Q2_OFF:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ENTER));
                layer_move(_QWERTY); // TO(_QWERTY);
                layer_on(_QUAKE2);
            };
            return false;
        case Q2_ESC:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESCAPE));
                layer_move(_QWERTY); // TO(_QWERTY);
                layer_on(_QUAKE2);
            };
            return false;
        case Q2_GRV:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_GRAVE));
                layer_on(_DVORAK);
                layer_on(_QUAKE2_DVORAK);
                layer_on(_QUAKE2_CONSOLE);
            };
            return false;
        case MC_UNDO:
            if (record->event.pressed) {
                if ( get_mods() & MOD_MASK_SHIFT ) {
                    SEND_STRING( SS_DOWN(X_LSHIFT) SS_DOWN(X_LGUI) SS_TAP(X_Z) SS_UP(X_LGUI) SS_UP(X_LSHIFT) );
                } else {
                    SEND_STRING( SS_DOWN(X_LGUI) SS_TAP(X_Z) SS_UP(X_LGUI) );
                }
            };
            return false;
        case MC_PSTE:
            if (record->event.pressed) {
                if ( get_mods() & MOD_MASK_SHIFT ) {
                    SEND_STRING( SS_DOWN(X_LSHIFT) SS_DOWN(X_LGUI) SS_DOWN(X_LALT) SS_TAP(X_V) SS_UP(X_LALT) SS_UP(X_LGUI) SS_UP(X_LSHIFT) );
                } else {
                    SEND_STRING( SS_DOWN(X_LGUI) SS_TAP(X_V) SS_UP(X_LGUI) );
                }
            };
            return false;
        case NUBS_Z:
            if (record->event.pressed) {
                if ( get_mods() & MOD_MASK_RALT ) {
                    SEND_STRING( SS_DOWN(X_NONUS_BSLASH) );
                } else {
                    SEND_STRING( SS_DOWN(X_Z) );
                }
            } else {
                if ( get_mods() & MOD_MASK_RALT ) {
                    SEND_STRING( SS_UP(X_NONUS_BSLASH) );
                } else {
                    SEND_STRING( SS_UP(X_Z) );
                }
            };
            return false;
        case VRSN:
            if (record->event.pressed) {
                SEND_STRING( QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION );
            }
            return false;
        case KC_1 ... KC_0:
            if (record->event.pressed) {
                if ( get_mods() & MOD_MASK_RALT ) {
                    register_code( keycode + 0x3b );
                } else {
                    register_code( keycode );
                }
            } else {
                if ( get_mods() & MOD_MASK_RALT ) {
                    unregister_code( keycode + 0x3b );
                } else {
                    unregister_code( keycode );
                }
            }
            return false;
    } // switch()
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
        KC_LSFT, NUBS_Z,  KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, KC_RGUI, MO(_FW), KC_RCTL  \
    ),

    /* Dvorak */
    [_DVORAK] = LAYOUT_60_ansi(
        //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSPC, \
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS, \
        FW_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, KC_ENT,           \
        KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,                   \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, KC_RGUI, MO(_FW), KC_RCTL  \
    ),

    /* Colemak */
    [_COLEMAK] = LAYOUT_60_ansi(
        //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS, \
        FW_CAPS, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, KC_ENT,           \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, KC_RGUI, MO(_FW), KC_RCTL  \
    ),

    /****************
    ** OS OVERLAYS **
    ****************/

    /* Mac */
    [_MAC] = LAYOUT_60_ansi(
        //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        FM_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   \
        _______, _______, _______,                   _______,                                     _______, _______, MO(_FM), _______  \
    ),

    /*********************
    ** QUAKE 2 OVERLAYS **
    *********************/

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
        _______, KC_CALC, KC_APP,  _______, _______, _______, KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_PSCR, KC_SLCK, KC_PAUS, \
        NO_CHNG, WN_SALL, _______, _______, _______, _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, KC_PENT,          \
        _______, WN_UNDO, WN_CUT,  WN_COPY, WN_PSTE, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, TG(_SY), _______,                   \
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
        _______, _______, _______, G_FTCH,  G_COMM,  _______, _______, _______, _______, T_L3DED, _______, _______, _______,          \
        _______, _______, _______, _______, _______, G_BRCH,  SIGNA,   _______, _______, _______, _______, _______,                   \
        _______, _______, _______,                   _______,                                     _______, _______, NO_CHNG, _______  \
    ),

    /* System layer */
    [_SYSTEM] = LAYOUT_60_ansi(
        //       2        3        4        5        6        7        8        9        10       11       12       13       14       15       16
        TG(_SY), TO(_QW), TO(_DV), TO(_CM), GO_Q2,   XXXXXXX, XXXXXXX, XXXXXXX, RESET,   XXXXXXX, DEBUG,   XXXXXXX, VRSN,    XXXXXXX, \
        XXXXXXX, XXXXXXX, TG(_MC), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          \
        XXXXXXX, XXXXXXX, XXXXXXX, BL_DEC,  BL_TOGG, BL_INC,  BL_BRTG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   \
        XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,                                     XXXXXXX, XXXXXXX, NO_CHNG, XXXXXXX  \
    ),

};
