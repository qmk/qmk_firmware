#include QMK_KEYBOARD_H
#include "keymap_dvp.h"

enum layer_names {
    _BASE_DVORAK,
    _RAISE,
    _KEYPAD,
};

// Mac-specific macros
#define MACCOPY LGUI(DP_C)
#define MACPAST LGUI(DP_V)
#define MACUNDO LGUI(DP_Z)
#define MACREDO LGUI(DP_Y)
#define MACLOCK LGUI(LCTL(DP_Q))

#define LSA_ LSA(KC_NO)
#define SFT_ESC SFT_T(KC_ESC)
#define KEYPAD TG(_KEYPAD)
#define RAISE LM(_RAISE, MOD_LSFT)

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE_DVORAK] = LAYOUT (
           // Left Hand
           MACLOCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
           DP_DLR,  DP_PLUS, DP_LBRC, DP_LCBR, DP_LPRN, DP_AMPR,
           KC_TAB,  DP_SCLN, DP_COMM, DP_DOT,  DP_P,    DP_Y,
           SFT_ESC, DP_A,    DP_O,    DP_E,    DP_U,    DP_I,
           KC_LCTL, DP_QUOT, DP_Q,    DP_J,    DP_K,    DP_X,
                    DP_GRV,  KC_INS,  KC_LEFT, KC_RGHT,
           // Left Thumb
                    KC_LGUI, KC_LALT,
                             MACPAST,
           KC_BSPC, KC_SPC,  MACCOPY,

           // Right Hand
           KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KEYPAD,  RESET,
           DP_EQL,  DP_RPRN, DP_RCBR, DP_RBRC, DP_ASTR, DP_EXLM,
           DP_F,    DP_G,    DP_C,    DP_R,    DP_L,    DP_SLSH,
           DP_D,    DP_H,    DP_T,    DP_N,    DP_S,    DP_MINS,
           DP_B,    DP_M,    DP_W,    DP_V,    DP_Z,    KC_RSFT,
                    KC_DOWN, KC_UP,   DP_AT,   DP_BSLS,
           // Right Thumb
           KEYPAD,  LSA_,
           MACUNDO,
           MACREDO, RAISE, KC_ENT
    ),

[_RAISE] = LAYOUT (
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           DP_TILD, DP_1,    DP_2,    DP_3,    DP_4,    DP_5,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
                    DP_PIPE, _______, _______, _______,
           // Left Thumb
                    _______, _______,
                             _______,
           _______, _______, _______,

           // Right Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           DP_6,    DP_7,    DP_8,    DP_9,    DP_0,    DP_PERC,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
                    _______, _______, DP_CIRC, DP_HASH,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, _______
    ),

[_KEYPAD] = LAYOUT (
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______,
           // Left Thumb
                    _______, _______,
                             _______,
           _______, _______, _______,

           // Right Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, KC_NLCK, KC_PEQL, KC_PSLS, KC_PAST, _______,
           _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______,
           _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
           _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
                    _______, _______, KC_PDOT, KC_PENT,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, KC_P0
    )
};
