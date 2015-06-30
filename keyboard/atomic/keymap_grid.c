#include "keymap_common.h"

// GRD: Grid layout

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = KEYMAP_GRD(FN29, FN30, FN31,    3,    4,    5,    6,    7,    8,    9,    0,    MINS, EQL,  BSLS, GRV,   \
                     TAB,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    LBRC, RBRC, BSPC, DEL,   \
                     CAPS, A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, QUOT, ENT,  ENT,  PGUP,  \
                     LSFT, Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, RSFT, RSFT, UP,   PGDN,  \
                     LCTL, LALT, LGUI, SPC,  SPC,  SPC,  SPC,  SPC,  SPC,  RALT, APP,  RCTL, LEFT, DOWN, RGHT), \

};
const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_MOMENTARY(2),  // to Fn overlay
    [3] = ACTION_DEFAULT_LAYER_SET(0), 
    [4] = ACTION_DEFAULT_LAYER_SET(1),  

    [9] = ACTION_MODS_KEY(MOD_LSFT | MOD_RSFT, KC_PAUSE),
 
    [10] = ACTION_MODS_KEY(MOD_LSFT, KC_1),
    [11] = ACTION_MODS_KEY(MOD_LSFT, KC_2),
    [12] = ACTION_MODS_KEY(MOD_LSFT, KC_3),
    [13] = ACTION_MODS_KEY(MOD_LSFT, KC_4),
    [14] = ACTION_MODS_KEY(MOD_LSFT, KC_5),
    [15] = ACTION_MODS_KEY(MOD_LSFT, KC_6),
    [16] = ACTION_MODS_KEY(MOD_LSFT, KC_7),
    [17] = ACTION_MODS_KEY(MOD_LSFT, KC_8),
    [18] = ACTION_MODS_KEY(MOD_LSFT, KC_9),
    [19] = ACTION_MODS_KEY(MOD_LSFT, KC_0),
    [20] = ACTION_MODS_KEY(MOD_LSFT, KC_MINS),
    [21] = ACTION_MODS_KEY(MOD_LSFT, KC_EQL),
    [22] = ACTION_MODS_KEY(MOD_LSFT, KC_GRV),
    [23] = ACTION_MODS_KEY(MOD_LSFT, KC_LBRC),
    [24] = ACTION_MODS_KEY(MOD_LSFT, KC_RBRC),
    [28] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),

    [29] = ACTION_BACKLIGHT_TOGGLE(),
    [30] = ACTION_BACKLIGHT_INCREASE(),
    [31] = ACTION_BACKLIGHT_DECREASE()
};
