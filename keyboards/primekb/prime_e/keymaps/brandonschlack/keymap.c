/* Copyright 2020 Brandon Schlack
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "brandonschlack.h"

// Tap Dance declarations
enum {
    TD_LR_BRC,
    TD_SD_QUOT
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for LBracket, twice for RBracket
    [TD_LR_BRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
    // Tap once for Single Quote, twice for Double Quote
    [TD_SD_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQT)
};

#define LWR_B      LT(_LOWER, KC_B)
#define LWR_EQL    LT(_LOWER, KC_EQL)
#define TD_BRC     TD(TD_LR_BRC)
#define TD_QUOT    TD(TD_SD_QUOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT( \
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    TD_BRC,  KC_BSPC, \
        HY_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L,    TD_QUOT,          KC_ENT,  \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    LWR_B,           KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, LOWER,   \
        KC_LCTL, KC_LOPT,                   KC_LCMD, SPC_RAI,	      SPC_RAI,          KC_RCMD,                   KC_ROPT, KC_RCTL  \
    ),

    [_LOWER] = LAYOUT( \
        KC_DEL,  KC_BRMD, KC_BRMU, MC_MSSN, MC_LHPD, _______,         _______, _______, _______, KC_HOME, KC_UP,   KC_PGUP, MC_SLPD, \
        _______, KC_MUTE, KC_VOLU, NXT_WIN, PRV_TAB, MC_BACK,         MC_FWRD, NXT_TAB, _______, KC_LEFT, KC_RGHT,          KC_MPLY, \
        SF_CAPS, KC_MPRV, KC_VOLD, KC_MNXT, _______, PX_AFLL,         OP_AFLL, _______, _______, KC_END,  KC_DOWN, KC_PGDN, _______, \
        _______, _______,                   _______, _______,         _______,          _______,                   _______, _______  \
    ),

    [_RAISE] = LAYOUT( \
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_LBRC,         KC_RBRC, KC_7,    KC_8,    KC_9,    KC_0,    KC_RBRC, _______, \
        _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_MINS,         KC_PLUS, KC_4,    KC_5,    KC_6,    KC_SCLN,          _______, \
        _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  LWR_EQL,         KC_EQL,  KC_1,    KC_2,    KC_3,    _______, KC_BSLS, _______, \
        _______, _______,                   _______, _______,         _______,          _______,                   _______, _______  \
    ),

    [_ADJUST] = LAYOUT( \
        QM_MAKE, _______, _______, EE_CLR,  QK_BOOT, _______,         _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______,          _______, \
        _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, \
        _______, _______,                   _______, _______,         _______,          _______,                   _______, _______  \
    )

/*
    [BLANK] = LAYOUT( \
        _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______,          _______, \
        _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, \
        _______, _______,                   _______, _______,         _______,          _______,                   _______, _______  \
    )
 */
};

void keyboard_pre_init_user(void) {
    setPinOutput(TOP_LED);
    setPinOutput(MIDDLE_LED);
    setPinOutput(BOTTOM_LED);
}

layer_state_t layer_state_set_keymap(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    return state;
}

#ifdef USE_LEDS_FOR_LAYERS
bool led_update_keymap(led_t led_state) {
    writePin(TOP_LED, LED_ON(IS_LAYER_ON(_FN1))); // Use for Layer 1
    writePin(MIDDLE_LED, LED_ON(IS_LAYER_ON(_FN2))); // Use for Layer 2
    writePin(BOTTOM_LED, LED_ON(led_state.caps_lock)); // Use for Caps Lock
    return false; // Override default set by KB
}
#endif
