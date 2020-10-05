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

/**
 * Layer Names
 */
#define _REEDER   _BASE
enum bdn9_layers {
    _MEDIA = KEYMAP_LAYERS,
    _NAVI,
    _KARABINER
};

/**
 * Keycodes & Macros
 */
#define DF_REDR   DF(_REEDER)          // Set Default Layer to Reeder shortcuts
#define DF_MEDA   DF(_MEDIA)           // Set Default Layer to Media controls
#define DF_NAVI   DF(_NAVI)            // Set Default Layer to Navigation shortcuts
#define DF_KBNR   DF(_KARABINER)       // Set Default Layer to Basic Macro keys

// Tap Dances
enum launchpad_dances {
    TD_SHLD_LGHT = 0,
    TD_SHLD_ADJT,
    TD_REDR_H
};
//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SHLD_LGHT] = ACTION_TAP_DANCE_TRIGGER_LAYER(SINGLE_HOLD, _LIGHT),
    [TD_SHLD_ADJT] = ACTION_TAP_DANCE_TRIGGER_LAYER(SINGLE_HOLD, _ADJUST),
    [TD_REDR_H] = ACTION_TAP_DANCE_DOUBLE(KC_H, KC_R)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Reeder
 * ┌──────┬──────┐
 * │CmdTab│ View │
 * ├──────┼──────┤
 * │PrvSub│PrvItm│
 * ├──────┼──────┤
 * │NxtSub│NxtItm│
 * ├──────┼──────┤
 * │  Clr │ Sync │
 * └──────┴──────┘
 */
[_REEDER] = LAYOUT( \
    CMD_TAB, TD(TD_REDR_H), \
    KC_P, KC_K, \
    KC_N, KC_J, \
    TD(TD_SHLD_LGHT), TD(TD_SHLD_ADJT) \
),

/* Media
 * ┌──────┬──────┐
 * │ Mute │ Play │
 * ├──────┼──────┤
 * │ Vol+ │PrvTrk│
 * ├──────┼──────┤
 * │ Vol- │NxtTrk│
 * ├──────┼──────┤
 * │ Spce │ Plyr │
 * └──────┴──────┘
 */
[_MEDIA] = LAYOUT( \
    KC_MUTE, KC_MPLY, \
    KC_VOLU, KC_MNXT, \
    KC_VOLD, KC_MPRV, \
    TD(TD_SHLD_LGHT), TD(TD_SHLD_ADJT) \
),

/* Navigation
 * ┌──────┬──────┐
 * │ PTab │ NTab │
 * ├──────┼──────┤
 * │ SclL │ SclU │
 * ├──────┼──────┤
 * │ SclR │ SclD │
 * ├──────┼──────┤
 * │LstTab│ClsTab│
 * └──────┴──────┘
 */
[_NAVI] = LAYOUT( \
    PRV_TAB, NXT_TAB, \
    MC_WH_L, MC_WH_U, \
    MC_WH_R, MC_WH_D, \
    TD(TD_SHLD_LGHT), TD(TD_SHLD_ADJT) \
),

/* Macro
 * ┌──────┬──────┐
 * │   1  │  2   │
 * ├──────┼──────┤
 * │   3  │  4   │
 * ├──────┼──────┤
 * │   5  │  6   │
 * ├──────┼──────┤
 * │   7  │  8   │
 * └──────┴──────┘
 */
[_KARABINER] = LAYOUT( \
    KC_P1,     KC_P2, \
    KC_P3,     KC_P4, \
    KC_P5,     KC_P6, \
    TD(TD_SHLD_LGHT), TD(TD_SHLD_ADJT) \
),

/* Lights
 * ┌──────┬──────┐
 * │ THM+ │ HUE+ │
 * ├──────┼──────┤
 * │ SAT- │ SAT+ │
 * ├──────┼──────┤
 * │ VAL- │ VAL+ │
 * ├──────┼──────┤
 * │ XXXX │ Mde+ │
 * └──────┴──────┘
 */
[_LIGHT] = LAYOUT( \
    RGB_THM, RGB_HUI, \
    RGB_SAD, RGB_SAI, \
    RGB_VAD, RGB_VAI, \
    XXXXXXX, RGB_MOD \
),

/* Adjust
 * ┌──────┬──────┐
 * │ Make │ Rset │
 * ├──────┼──────┤
 * │ Redr │ Meda │
 * ├──────┼──────┤
 * │ Navi │ Mcro │
 * ├──────┼──────┤
 * │ Lght │ XXXX │
 * └──────┴──────┘
 */
[_ADJUST] = LAYOUT( \
    QM_MAKE, RESET, \
    DF_REDR, DF_MEDA, \
    DF_NAVI, DF_KBNR, \
    TG_LGHT, XXXXXXX \
)

};

void matrix_init_keymap(void) {
}

// Runs once after keyboard initializes
void keyboard_post_init_keymap(void) {
};

/**
 * Tap Dances
 */
void process_tap_dance_keycode (bool reset, uint8_t toggle_layer) {
    uint16_t keycode = 0;
    switch (toggle_layer) {
        case _LIGHT:
            switch (get_highest_layer(layer_state)) {
                case _REEDER:
                    keycode = KC_L;
                    break;
                case _MEDIA:
                    keycode = KC_SPC;
                    break;
                case _NAVI:
                    keycode = REO_TAB;
                    break;
                case _KARABINER:
                    keycode = KC_P7;
                    break;
            }
            break;
        case _ADJUST:
            switch (get_highest_layer(layer_state)) {
                case _REEDER:
                    keycode = KC_R;
                    break;
                case _MEDIA:
                    keycode = MC_PLYR;
                    break;
                case _NAVI:
                    keycode = CLS_TAB;
                    break;
                case _KARABINER:
                    keycode = KC_P8;
                    break;
            }
            break;
    }
    if (!reset) {
        register_code16(keycode);
    } else {
        unregister_code16(keycode);
    }
}
