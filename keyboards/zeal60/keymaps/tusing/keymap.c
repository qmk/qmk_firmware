// Default layout for Zeal60
#include QMK_KEYBOARD_H

// For readability.
#define _______ KC_TRNS
#define   _x_   KC_NO
#define AUD_PRV LCTL(KC_MPRV) // Previous music track
#define AUD_PLY LCTL(KC_MPLY) // Pause music
#define AUD_NXT LCTL(KC_MNXT) // Next music track

// Zeal60-specific keys:
//  EF_INC, EF_DEC,   // next/previous backlight effect
//  H1_INC, H1_DEC,   // Color 1 hue increase/decrease
//  S1_INC, S1_DEC,   // Color 1 saturation increase/decrease
//  H2_INC, H2_DEC,   // Color 2 hue increase/decrease
//  S2_INC, S2_DEC,   // Color 2 saturation increase/decrease
//  BR_INC, BR_DEC,   // backlight brightness increase/decrease

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Default layer: Pressing caps-lock momentarily switches to Layer 1.
// This is the default layer. Pressing an empty keycode on another layer will take you here.
    [0] = {
        {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC},
        {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS},
        {MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,    _x_  },
        {KC_LSFT,   _x_  , KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,   _x_  },
        {KC_LCTL, KC_LGUI, KC_LALT,   _x_  ,   _x_  ,   _x_  ,   _x_  , KC_SPC,    _x_  ,   _x_  , KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT}
    },

// Layer 1: Pressing enter switches to layer 2, where backlight controls live.
// This is a momentary layer: once you let go of caps, you'll be back in layer 1.
    [1] = {
        {KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL },
        {_______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_INS,  KC_DEL,  _______},
        {_______, AUD_PRV, AUD_PLY, AUD_NXT, _______, _______, _______, _______, _______, _______, _______, _______, TO(2)  ,   _x_  },
        {KC_CAPS,   _x_  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _x_  },
        {KC_RCTL, KC_RGUI, KC_RALT,   _x_  ,   _x_  ,   _x_  ,   _x_  , _______,   _x_  ,   _x_  , KC_HOME, KC_PGUP, KC_PGDN,  KC_END}
    },

// Layer 2: Zeal60 and backlight configuration. (Get here quickly by pressing Caps+Enter from Layer 1.)
// This is a persistent layer. Get back to the default layer by pressing enter.
    [2] = {
        {RESET,   EF_DEC,  EF_INC,  BR_DEC,  BR_INC,  ES_DEC,  ES_INC,  _______, _______, _______, _______, _______, _______, _______},
        {_______, H1_DEC,  H1_INC,  S1_DEC,  S1_INC,  _______, _______, _______, _______, _______, _______, _______, _______, _______},
        {_______, H2_DEC,  H2_INC,  S2_DEC,  S2_INC,  _______, _______, _______, _______, _______, _______, _______, TO(0)  ,   _x_  },
        {RGB_MOD,   _x_  , RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, _______, _______, _______, _______, _______, _______, _______,   _x_  },
        {RGB_TOG, RGB_VAD, RGB_VAI,   _x_  ,   _x_  ,   _x_  ,   _x_  , _______,   _x_  ,   _x_  , _______, _______, _______, _______}
    }
};
