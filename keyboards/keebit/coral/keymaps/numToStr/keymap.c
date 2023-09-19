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

// Custom Keys
#define KK_COPY LCTL(KC_C)
#define KK_PASTE RCTL(KC_V)
#define KK_MOUSE MO(MouseLayer)

// ###### Tap-Dance ######

enum coral_tapdance {
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

// ###### Layers ######

enum coral_layers {
    BaseLayer,
    NavLayer,
    MouseLayer,
    FnLayer,
};

enum coral_keycodes {
    KK_LOREM = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BaseLayer] = LAYOUT(
        KC_1,    KC_2,  KC_3,    KC_4,    KC_5,   KC_6,           /**/        KC_7,    KC_8,    KC_9,     KC_0,    KC_MINUS, KC_EQUAL,
        KC_TAB,  KC_Q,  KC_W,    KC_E,    KC_R,   KC_T,           /**/        KC_Y,    KC_U,    KC_I,     KC_O,    KC_P,     KC_LBRC,
        KC_GRV,  GUI_A, ALT_S,   SFT_D,   CTL_F,  KC_G,           /**/        KC_H,    CTL_J,   SFT_K,    ALT_L,   GUI_SCLN, KC_QUOTE,
        KC_BSLS, KC_Z,  KC_X,    KC_C,    KC_V,   KC_B,           /**/        KC_N,    KC_M,    KC_COMMA, KC_DOT,  KC_SLASH, KC_RBRC,
                        KK_COPY, KC_PSCR, KC_ESC, L_THUMB, L_ROT, /**/ R_ROT, R_THUMB, KC_BSPC, KC_DEL,   KK_PASTE
    ),
    [NavLayer] = LAYOUT(
        _______, _______, _______, _______, _______, _______,           /**/          KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLU, KC_VOLD,
        _______, _______, _______, _______, _______, _______,           /**/          KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_BRIU, KC_BRID,
        _______, _______, _______, _______, _______, KK_MOUSE,          /**/          KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,           /**/          _______, _______, _______, _______,  _______, KK_LOREM,
                          _______, _______, _______, XXXXXXX,  _______, /**/ _______, _______, _______, _______, _______
    ),
    [MouseLayer] = LAYOUT(
        _______, _______, _______, _______, _______, _______,          /**/          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          /**/          _______, KC_BTN1, KC_BTN2, _______, _______, _______,
        _______, _______, _______, _______, _______, XXXXXXX,          /**/          KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
        _______, _______, _______, _______, _______, _______,          /**/          _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, XXXXXXX, _______, /**/ _______, _______, _______, _______, _______
    ),
    [FnLayer] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,            /**/          _______, _______, _______, _______, _______, _______,
        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           /**/          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          /**/          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,          /**/          _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______, _______, /**/ _______, XXXXXXX, _______, _______, _______
    ),
};

// ###### Combos ######

enum coral_combos {
    CAPS_COMBO,
    COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

// Left and right thumb is CapsLock
const uint16_t PROGMEM caps_combo[] = {L_THUMB, R_THUMB, COMBO_END};

combo_t key_combos[] = {
    [CAPS_COMBO] = COMBO(caps_combo, QK_CAPS_WORD_TOGGLE),
};

// ###### Encoders #######

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BaseLayer] = { ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [NavLayer] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [MouseLayer] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [FnLayer] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
};
#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KK_LOREM:
            if (record->event.pressed) {
                SEND_STRING("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean vitae nibh neque. Etiam sed enim ac ipsum maximus rhoncus id et dui. Nam mi orci, rutrum in ipsum eget, hendrerit aliquam nulla. Maecenas ac nisl nibh. Integer erat mi, molestie vitae aliquet ut, faucibus eget sem. Suspendisse vel lacus interdum, consectetur nisi vitae, vulputate purus. Etiam ut aliquam turpis, id pellentesque ligula. Curabitur semper nisi in facilisis vehicula. Pellentesque felis risus, maximus blandit erat vel, congue sagittis mi. Etiam aliquam arcu sed neque semper laoreet. Sed id posuere libero, sed volutpat sapien.");
            }
            return false;
        // case QK_CAPS_WORD_TOGGLE:
        //     if (record->event.pressed) {
        //         rgblight_setrgb_at(RGB_WHITE, 0);
        //     }
        //     return true;
        default:
            return true;
    }
};
