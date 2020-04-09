#pragma once

#include "quantum.h"

// My own keycodes.
enum userspace_custom_keycodes {
    PV_ = SAFE_RANGE,

    PV_VRSN,  // Print firmware version.
    PV_MAKE,  // Print the make command of the keyboard.
    PV_FLSH,  // Reset keyboard.

    PV_SSNC,  // Play Sonic Ring.
    PV_SCIN,  // Play Coin Sound.

    PV_TEST,  // For quick testing purposes.

    PV_SAFE_RANGE,  // Used for extra keycodes in individual keymaps.
};

enum tap_dance_indexes {
    // tap dance
    TD_FLSH,  // flash keyboard (as if the physical flash key was pressed)
};

#define ALLM(kc) LCAG(kc)           // Easier name for left ctrl-alt-gui.
#define PV_ESCC CTL_T(KC_ESC)       // esc on tap, ctrl on hold.
#define PV_LOCK LCTL(LSFT(KC_PWR))  // Lock computer.
#define TD_3FLS TD(TD_FLSH)         // Tap dance 3 times for flash.

// Layers.
enum {
    LR_BASE = 0,  // used for basic keys like the surrounding ctrl, cmd, etc

    LR_QWERTY,
    LR_CARPALX,
    LR_GAME1,  // game layout (space on the left thumb, no modifiers, etc)
    LR_GAME2,  // game layout (space on the left thumb, no modifiers, etc, arrows)

    LR_SYMBOL,  // symbol input (!, @, #, etc)
    LR_SYSCTL,  // system control (music, volume, keyboard flash, etc)
    LR_KBCTL,   // keyboard control (version, make, flash, etc)

};

// Layer switchers.
#define BASE TO(LR_BASE)
#define QWERTY TO(LR_QWERTY)
#define CARPALX TO(LR_CARPALX)
#define GAME1 TO(LR_GAME1)
#define GAME2 TO(LR_GAME2)

#define SYMBOL MO(LR_SYMBOL)
#define SYSCTL MO(LR_SYSCTL)
#define KBCTL MO(LR_KBCTL)

// Layout parts for easy reuse between keyboard keymaps.

// Transparent.
// ┌─────┬─────┬─────┬─────┬─────┐
// │     │     │     │     │     │
// └─────┴─────┴─────┴─────┴─────┘
#define ___________________________________________ _______, _______, _______, _______, _______

// Numbers.
// ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
// │  1  │  2  │  3  │  4  │  5  │   │  6  │  7  │  8  │  9  │  0  │
// └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
#define ________________NUMBERS_L__________________ KC_1, KC_2, KC_3, KC_4, KC_5
#define ________________NUMBERS_R__________________ KC_6, KC_7, KC_8, KC_9, KC_0

// F keys.
// ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
// │ F1  │ F2  │ F3  │ F4  │ F5  │   │ F6  │ F7  │ F8  │ F9  │ F10 │
// └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
#define ______________________F_L__________________ KC_F1, KC_F2, KC_F3, KC_F4, KC_F5
#define ______________________F_R__________________ KC_F6, KC_F7, KC_F8, KC_F9, KC_F10

// QWERTY.
// ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
// │  Q  │  W  │  E  │  R  │  T  │   │  Y  │  U  │  I  │  O  │  P  │
// ├─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┤
// │  A  │  S  │  D  ┃  F  ┃  G  │   │  H  ┃  J  ┃  K  │  L  │  ;  │
// ├─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┤
// │  Z  │  X  │  C  │  V  │  B  │   │  N  │  M  │  ,  │  .  │  /  │
// └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
#define _________________QWERTY_L1_________________ KC_Q, KC_W, KC_E, KC_R, KC_T
#define _________________QWERTY_L2_________________ KC_A, KC_S, KC_D, KC_F, KC_G
#define _________________QWERTY_L3_________________ KC_Z, KC_X, KC_C, KC_V, KC_B

#define _________________QWERTY_R1_________________ KC_Y, KC_U, KC_I, KC_O, KC_P
#define _________________QWERTY_R2_________________ KC_H, KC_J, KC_K, KC_L, KC_SCLN
#define _________________QWERTY_R3_________________ KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH

// QWERTY with mods.
// ┌───────┬───────┬───────┲━━━━━━━┱───────┐   ┌───────┲━━━━━━━┱───────┬───────┬───────┐
// │ ctl/A │ sft/S │ cmd/D ┃ opt/F ┃   G   │   │   H   ┃ opt/J ┃ cmd/K │ sft/L │ ctl/; │
// └───────┴───────┴───────┺━━━━━━━┹───────┘   └───────┺━━━━━━━┹───────┴───────┴───────┘
// #define _____________MOD_QWERTY_L2_________________  CTL_T(KC_A), SFT_T(KC_S), GUI_T(KC_D), ALT_T(KC_F),       KC_G
#define _____________MOD_QWERTY_L2_________________ KC_A, KC_S, KC_D, ALT_T(KC_F), KC_G
#define _____________MOD_QWERTY_R2_________________ KC_H, ALT_T(KC_J), GUI_T(KC_K), SFT_T(KC_L), CTL_T(KC_SCLN)

// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
// |  Q  |  G  |  M  |  L  |  W  |   |  Y  |  F  |  I  |  O  |  P  |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  D  |  S  |  T  |  N  |  R  |   |  I  |  A  |  K  |  L  |  ;  |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  Z  |  X  |  C  |  V  |  J  |   |  K  |  P  |  ,  |  .  |  /  |
// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
#define ________________CARPALX_L1_________________ KC_Q, KC_G, KC_M, KC_L, KC_W
#define ________________CARPALX_L2_________________ KC_D, KC_S, KC_T, KC_N, KC_R
#define ________________CARPALX_L3_________________ KC_Z, KC_X, KC_C, KC_V, KC_J

#define ________________CARPALX_R1_________________ KC_Y, KC_F, KC_U, KC_B, KC_SCLN
#define ________________CARPALX_R2_________________ KC_I, KC_A, KC_E, KC_O, KC_H
#define ________________CARPALX_R3_________________ KC_K, KC_P, KC_COMM, KC_DOT, KC_SLSH

// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
// |  !  |  @  |  {  |  }  |  _  |   |  \  |     |  `  |     |     |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  #  |  $  |  (  |  )  |  -  |   |  =  |  &  |  '  |  "  |  |  |
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |  %  |  ^  |  [  |  ]  |  +  |   |  *  |  ~  |  <  |  >  |  /  |
// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
#define _________________SYMBOL_L1_________________ KC_EXLM, KC_AT, KC_LCBR, KC_RCBR, KC_UNDS
#define _________________SYMBOL_L2_________________ KC_HASH, KC_DLR, KC_LPRN, KC_RPRN, KC_MINS
#define _________________SYMBOL_L3_________________ KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_PLUS

#define _________________SYMBOL_R1_________________ KC_BSLS, _______, KC_GRV, _______, _______
#define _________________SYMBOL_R2_________________ KC_EQL, KC_AMPR, KC_QUOT, KC_DQUO, KC_PIPE
#define _________________SYMBOL_R3_________________ KC_ASTR, KC_TILD, KC_LABK, KC_RABK, KC_SLSH

// System Control.
//                                    vol ↓                   ctl ↓
// ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
// │     │     │     │     │     │   │MUTE │HOME │  ↑  │ END │LOCK │
// ├─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┤
// │     │     │     ┃     ┃     │   │VOLUP┃  ←  ┃  ↓  │  →  │SLEEP│ ← arrows
// ├─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┤
// │     │     │     │     │     │   │VOLDN│MPREV│MPLAY│MNEXT│ PWR │ ← music
// └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
#define _________________SYSCTL_L1_________________ XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_BTN1, XXXXXXX
#define _________________SYSCTL_L2_________________ XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_RIGHT, KC_MS_WH_UP
#define _________________SYSCTL_L3_________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_WH_DOWN

//                                                    vol v                                                 ctl v
#define _________________SYSCTL_R1_________________ KC_MUTE, KC_HOME, KC_UP, KC_END, PV_LOCK
#define _________________SYSCTL_R2_________________ KC_VOLU, KC_LEFT, KC_DOWN, KC_RGHT /* < arrows */, KC_SLEP
#define _________________SYSCTL_R3_________________ KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT /* < music */, KC_PWR

// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
// |GAME |CRPLX|XXXXX|XXXXX|XXXXX|   |XXXXX|XXXXX|XXXXX|XXXXX|XXXXX|
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |XXXXX|XXXXX|XXXXX|XXXXX|XXXXX|   |XXXXX|VERSN|MAKE |FLASH|XXXXX|
// ,-----+-----+-----x-----x-----,   ,-----x-----x-----+-----+-----,
// |XXXXX|XXXXX|XXXXX|XXXXX|XXXXX|   |XXXXX|XXXXX|XXXXX|XXXXX|XXXXX|
// ,-----+-----+-----+-----+-----,   ,-----+-----+-----+-----+-----,
#define __________________KBCTL_L1_________________ PV_SSNC, PV_SCIN, PV_TEST, XXXXXXX, XXXXXXX
#define __________________KBCTL_L2_________________ RGB_TOG, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX
#define __________________KBCTL_L3_________________ RGB_MOD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX

#define __________________KBCTL_R1_________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define __________________KBCTL_R2_________________ XXXXXXX, PV_VRSN, PV_MAKE, PV_FLSH, XXXXXXX
#define __________________KBCTL_R3_________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

// We need wrappers in order for these definitions, because they need to be expanded before being used as arguments to the LAYOUT_xxx macro.
#define LAYOUT_ergodox_pretty_wrapper(...) LAYOUT_ergodox_pretty(__VA_ARGS__)
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

// Extra stuff that might be needed.
void     keyboard_post_init_user_keymap(void);
uint32_t layer_state_set_user_keymap(uint32_t state);
