#include "jd45.h"
#include "backlight.h"

/* JD45 keymap definition macro
 */
#define KEYMAP( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11, K12, K13, \
	K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, K24, K25, \
	K26, K27, K28, K29, K30, K31, K32, K33, K34, K35, K36, K37, \
	K38, K39, K40, K41, K42, K43, K44, K45, K46, K47 \
) { \
    { KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07, KC_##K08, KC_##K09, KC_##K10, KC_##K11, KC_##K12, KC_##K13 }, \
    { KC_##K14, KC_##K15, KC_##K16, KC_##K17, KC_##K18, KC_##K19, KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_NO    }, \
    { KC_##K26, KC_##K27, KC_##K28, KC_##K29, KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37, KC_NO    }, \
    { KC_##K38, KC_##K39, KC_##K40, KC_##K41, KC_##K42, KC_NO,    KC_##K43, KC_NO,    KC_##K44, KC_##K45, KC_##K46, KC_##K47, KC_NO    }  \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP(
  ESC,  Q,    W,    F,    P,    G,    J,    L,    U,    Y,    SCLN, QUOT, BSPC,
  FN8,  A,    R,    S,    T,    D,    H,    N,    E,    I,    O,     ENT,
  LSFT, Z,    X,    C,    V,    B,    K,    M,    COMM, DOT,  SLSH,  FN6,
  FN4, LGUI, FN7, FN2,  FN1,  SPC,  FN5,  RALT,  FN3, FN0 ),
[1] = KEYMAP(
  TRNS, FN10, FN11, FN12, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, UP, DEL,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, HOME, PGUP, LEFT, RGHT,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, END,  PGDN, DOWN, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS ),
[2] = KEYMAP(
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,    7,    8,    9,    0, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, LBRC,    4,    5,    6,  DOT, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, RBRC,    1,    2,    3, BSLS, TRNS,
  TRNS,FN29, TRNS, TRNS, TRNS, PAUSE,  EQL, MINS, TRNS, TRNS ),
[3] = KEYMAP(
  TRNS, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS ),
[4] = KEYMAP(
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,    7,    8,    9,    0, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, LBRC,    4,    5,    6,  DOT, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, RBRC,    1,    2,    3, BSLS, TRNS,
  TRNS,FN29, TRNS, TRNS, TRNS, PAUSE,  EQL, MINS, TRNS, TRNS ),
};

enum macro_id {
   PSWD1,
   PSWD2,
   PSWD3,
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_MINS),
    [1] = ACTION_LAYER_MOMENTARY(1),  // FN1
    [2] = ACTION_LAYER_MOMENTARY(2),  // FN2
    [3] = ACTION_LAYER_MOMENTARY(3),  // FN3
    [4] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_GRV),
    [5] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_RGUI),
    [6] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_CAPS),
    [7] = ACTION_LAYER_MODS(4, MOD_LSFT),  // FN4
    [8] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_TAB),

    [10] = ACTION_MACRO(PSWD1),
    [11] = ACTION_MACRO(PSWD2),
    [12] = ACTION_MACRO(PSWD3),
    
    [29] = ACTION_BACKLIGHT_TOGGLE(),
    [30] = ACTION_BACKLIGHT_INCREASE(),
    [31] = ACTION_BACKLIGHT_DECREASE()
    
};

/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case PSWD1:
            return (record->event.pressed ?
                    MACRO( I(0), T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(ENT), END ) :
                    MACRO_NONE );
        case PSWD2:
            return (record->event.pressed ?
                    MACRO( I(0), T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(ENT), END ) :
                    MACRO_NONE );
        case PSWD3:
            return (record->event.pressed ?
                    MACRO( I(0), T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(ENT), END ) :
                    MACRO_NONE );
        //case VOLUP:
        //    return (record->event.pressed ?
        //            MACRO( D(VOLU), U(VOLU), END ) :
        //            MACRO_NONE );
        //case ALT_TAB:
        //    return (record->event.pressed ?
        //            MACRO( D(LALT), D(TAB), END ) :
        //            MACRO( U(TAB), END ));
    }
    return MACRO_NONE;
}
