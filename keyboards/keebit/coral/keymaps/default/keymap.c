// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define SFT_D LSFT_T(KC_D)
#define CTL_F LCTL_T(KC_F)

// Right-hand home row mods
#define CTL_J RCTL_T(KC_J)
#define SFT_K RSFT_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)

// Thumb Keys
#define L_THUMB LT(NavLayer, KC_ENTER)
#define R_THUMB LT(FnLayer, KC_SPACE)

// Rotary
#define L_ROT TD(TD_MNXT_MPREV)
#define R_ROT TD(TD_MPLY_MUTE)


// ###### TAP DANCE ######

enum TapDance {
    TD_MNXT_MPREV,
    TD_MPLY_MUTE,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Media-Next, twice for Media-Previous
    [TD_MNXT_MPREV] = ACTION_TAP_DANCE_DOUBLE(KC_MNXT, KC_MPRV),
    // Tap once for Play/Pause, twice for Audio Mute
    [TD_MPLY_MUTE] = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MUTE),
};

// ###### LAYERS ######

enum Layers {
    BaseLayer,
    FnLayer,
    NavLayer
};

enum CustomKeycodes {
    SS_LOREM = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BaseLayer] = LAYOUT(
        KC_1,    KC_2,  KC_3,    KC_4,    KC_5,   KC_6,           /**/        KC_7,    KC_8,    KC_9,     KC_0,    KC_MINUS, KC_EQUAL,
        KC_TAB,  KC_Q,  KC_W,    KC_E,    KC_R,   KC_T,           /**/        KC_Y,    KC_U,    KC_I,     KC_O,    KC_P,     KC_LBRC,
        KC_GRV,  GUI_A, ALT_S,   SFT_D,   CTL_F,  KC_G,           /**/        KC_H,    CTL_J,   SFT_K,    ALT_L,   GUI_SCLN, KC_QUOTE,
        KC_BSLS, KC_Z,  KC_X,    KC_C,    KC_V,   KC_B,           /**/        KC_N,    KC_M,    KC_COMMA, KC_DOT,  KC_SLASH, KC_RBRC,
                        _______, KC_PSCR, KC_ESC, L_THUMB, L_ROT, /**/ R_ROT, R_THUMB, KC_BSPC, KC_DEL,   _______
    ),
    [NavLayer] = LAYOUT(
        _______, _______, _______, _______, _______, _______,          /**/          KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD, KC_VOLU,
        _______, _______, _______, _______, _______, _______,          /**/          KC_BRID, KC_BRIU, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______,          /**/          KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,          /**/          _______, _______, _______, _______,  _______, SS_LOREM,
                          _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______
    ),
    [FnLayer] = LAYOUT(
        KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,            /**/          _______, _______, _______, _______, _______, _______,
        KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           /**/          _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______,          /**/          _______, _______, _______, _______, _______, _______,
        SS_LOREM, _______, _______, _______, _______, _______,          /**/          _______, _______, _______, _______, _______, _______,
                           _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______
    )
};

// #if defined(ENCODER_MAP_ENABLE)
// const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
//     [BaseLayer] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
// };
// #endif

// ###### OVERRIDES ######

// Shift Left is Home
const key_override_t left_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT, KC_HOME);
// Shift Right is End
const key_override_t right_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_RIGHT, KC_END);
// Shift Up is PageUp
const key_override_t up_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_UP, KC_PGUP);
// Shift Down is PageDown
const key_override_t down_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOWN, KC_PGDN);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &left_key_override,
    &right_key_override,
    &up_key_override,
    &down_key_override,
    NULL // Null terminate the array of overrides!
};


// ###### COMBOS ######

enum combos {
    CAPS_COMBO,
    COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

// Left and right thumb is CapsLock
const uint16_t PROGMEM caps_combo[] = {L_THUMB, R_THUMB, COMBO_END};

combo_t key_combos[] = {
    [CAPS_COMBO] = COMBO(caps_combo, QK_CAPS_WORD_TOGGLE),
};
