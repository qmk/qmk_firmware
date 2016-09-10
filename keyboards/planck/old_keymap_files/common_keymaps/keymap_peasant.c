#include "keymap.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = KEYMAP( /* Native */
      ESC,     Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    FN2, 
      BSPC,    A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, QUOT,
      TAB,     Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, ENT,
      DEL,     LCTL, NO,   LSFT, LALT, SPC,        NO,   LEFT, DOWN, UP,  RGHT), 
    [1] = KEYMAP( /* QWERTY->PHOTOSHOP */
      DELETE,  0,    1,    2,    3,    4,    5,    6,    7,    8,    9,    FN1,
      O,       G,    S,    U,    T,    FN27,  F21,  F10,  F11,  F7,   F8,   F9,
      TAB,     FN4, FN5,  FN6,  F1,   FN7,  F18,  F19,  F23,  F20,  F22,  FN9,
      COMM,    DOT,  FN10, FN11, FN3,  SPC,        FN12, F2,   FN8,  F3,   F14),
    [2] = KEYMAP( /* 2: FN3 PHOTOSHOP */
      ESC,    FN25, FN26,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,
      NO,      NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   FN19, FN20, FN21, 
      C,       NO,  FN22,  FN5,   NO,   FN23, NO,   NO,   NO,   NO,   FN13, NO,
      FN14,    FN15, FN16, FN17, FN3,   SPC,        FN18, NO,   NO,   F24,  NO),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_DEFAULT_LAYER_SET(0),                             // set Qwerty layout
    [2] = ACTION_DEFAULT_LAYER_SET(1),                             // set Photoshop presets
    [3] = ACTION_LAYER_ON_OFF(2),                                  // Photoshop function layer
 
    [4] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL | MOD_LALT, KC_F9),   // photo folder AHK
    [5] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL, KC_I),              // select inverse
    [6] = ACTION_MODS_KEY(MOD_LSFT, KC_M),                         // marquee select
    [7] = ACTION_MODS_KEY(MOD_LALT, KC_BSPC),                      // fill 
    [8] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL | MOD_LALT, KC_X),    // warp
    [9] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT | MOD_LSFT, KC_F12),  // merge all new layer
    [10] = ACTION_MODS_KEY(MOD_LCTL, KC_MINS),                     // zoom out
    [11] = ACTION_MODS_KEY(MOD_LCTL, KC_H),                        // RBG sliders
    [12] = ACTION_MODS_KEY(MOD_LCTL, KC_S),                        // save
    [13] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL, KC_F5),           // layer mask from transparancy 
    [14] = ACTION_MODS_KEY(MOD_LALT, KC_LBRC),                     // prev layer
    [15] = ACTION_MODS_KEY(MOD_LALT, KC_RBRC),                     // next layer
    [16] = ACTION_MODS_KEY(MOD_LCTL, KC_EQL),                      // zoom in
    [17] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL, KC_H),             // HSV sliders
    [18] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL | MOD_LALT, KC_F11), // save as PNG
    [19] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL | MOD_LALT, KC_F7),  // gaussian blur
    [20] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL | MOD_LALT, KC_F8),  // motion blur
    [21] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL, KC_X),            // liquify filter
    [22] = ACTION_MODS_KEY(MOD_LSFT, KC_MINS),                     // prev layer blending
    [23] = ACTION_MODS_KEY(MOD_LSFT | MOD_LALT, KC_N),             // normal layer blending
    [24] = ACTION_MODS_KEY(MOD_LSFT, KC_EQL),                      // next layer blending
    [25] = ACTION_MODS_KEY(MOD_LCTL, KC_Z),                        // step back
    [26] = ACTION_MODS_KEY(MOD_LCTL, KC_Y),                        // step forward
    [27] = ACTION_MODS_KEY(MOD_LCTL, KC_R),                        // rasterize
     
};
