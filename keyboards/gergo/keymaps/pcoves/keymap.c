#include QMK_KEYBOARD_H

#include "pcoves.h"
#include "tapDance.h"

#define LAYER_0 0
#define LAYER_1 1

#define L1_SPC LT(1, KC_SPC)

#define CTL_A CTL_T(KC_A)
#define CTL_SCLN CTL_T(KC_SCLN)

#define SFT_Z SFT_T(KC_Z)
#define SFT_SLSH SFT_T(KC_SLSH)

#define SFT_ENT SFT_T(KC_ENT)

#define RU_TOGGLE RAINBOW_UNICORN_TOGGLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_0] = LAYOUT_gergo(
            KC_TAB,     KC_Q,      KC_W,        KC_E,      KC_R,      KC_T,                                                KC_Y,      KC_U,     KC_I,      KC_O,     KC_P,     _______,
            _______,    CTL_A,     KC_S,        KC_D,      KC_F,      KC_G,    _______,                         _______,   KC_H,      KC_J,     KC_K,      KC_L,     CTL_SCLN, _______,
            _______,    SFT_Z,     KC_X,        KC_C,      KC_V,      KC_B,    _______,   _______,   _______,   _______,   KC_N,      KC_M,     KC_COMM,   KC_DOT,   SFT_SLSH, _______,
                                                        TD(ALT),   SFT_ENT,   TD(LEFT),   _______,   _______,   TD(RIGHT), L1_SPC,    KC_RGUI
            ),

    [LAYER_1] = LAYOUT_gergo(
            KC_F2,     KC_1,      KC_2,      KC_3,      KC_4,      KC_5,                                                KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      RESET,
            KC_F3,     _______,   KC_HOME,   KC_PGDN,   KC_PGUP,   KC_END,  _______,                         _______,   KC_LEFT,   KC_DOWN,   KC_UP,     KC_RGHT,   _______,   EEP_RST,
            KC_F4,     _______,   SECRET0,   SECRET1,   SECRET2,   SECRET3, SECRET4,   _______,   _______,   _______,   EMOTE0,    EMOTE1,    EMOTE2,    EMOTE3,    AUTRUCHE,  RU_TOGGLE,
                                                        _______,   _______, _______,   _______,   _______,   _______,   _______,   _______
            ),
};
// clang-format on
