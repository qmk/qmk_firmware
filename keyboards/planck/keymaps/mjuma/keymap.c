/* Copyright 2017-2021 M Juma
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
#include "muse.h"

enum planck_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _GAMING,
    _ADJUST,
    _FN,
    _SPACE_FN
};

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    GAMING
};

enum taps {
    TD_SHIFT_CAPS = 0
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_SHIFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
};

// Fillers to make layering more clear
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FN MO(_FN)
#define SPACE_FN LT(_SPACE_FN, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | GEsc |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | FN   | GUI  | Alt  |Lower |  Space FN   |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,      KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    QK_GESC,           KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,      KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    TD(TD_SHIFT_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,      KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_ENT),
    KC_LCTL,           FN,      KC_LALT, KC_LGUI, LOWER,   SPACE_FN,  SPACE_FN,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |   *  |   4  |   5  |   6  |   -  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |   /  |   1  |   2  |   3  |   +  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Space    |      |   0  |   .  |   =  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,     KC_7,     KC_8,    KC_9,     KC_0,     KC_BSPC,
    _______, _______, _______, _______, _______, _______, KC_PAST,  KC_4,     KC_5,    KC_6,     KC_PMNS,  KC_BSLS,
    _______, _______, _______, _______, _______, _______, KC_PSLS,  KC_1,     KC_2,    KC_3,     KC_PPLS,  MT(MOD_LSFT, KC_ENT),
    _______, _______, _______, _______, _______, KC_SPC,  KC_SPC,   _______,  KC_0,    KC_PDOT,  KC_PEQL,  _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |   /  |   {  |   [  |   ]  |   }  |   \  |   -  |   =  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |   _  |   +  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Space    |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    _______, _______, _______, KC_SLSH,    KC_LCBR,  KC_LBRC,  KC_RBRC,  KC_RCBR, KC_BSLS, KC_MINS, KC_EQL,  KC_PIPE,
    _______, _______, _______, _______,    _______,  _______,  _______,  _______, _______, KC_UNDS, KC_PLUS, MT(MOD_LSFT, KC_ENT),
    _______, _______, _______, _______,    _______,  KC_SPC,   KC_SPC,   _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* fn
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F11 |  F12 |  F13 |  F14 |  F15 |      |INSERT| Home | PgUp |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |DELETE| End  | PgDn |      | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Space    |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FN] = LAYOUT_planck_grid(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,    KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
    _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,   KC_F15,   _______,  KC_INS,  KC_HOME, KC_PGUP, _______, _______,
    _______, _______, _______, _______, _______,  _______,  _______,  KC_DEL,  KC_END,  KC_PGDN, _______, MT(MOD_LSFT, KC_ENT),
    _______, _______, _______, _______, _______,  KC_SPC,   KC_SPC,   _______, _______, _______, _______, _______
),

/* Space fn
 * ,------------------------------------------------------------------------------------.
 * |PRNT SC|      |  UP  |      |      |      |      |      |      |      |      |      |
 * |-------+------+------+------+------+-------------+------+------+------+------+------|
 * |       | LEFT | DOWN | RIGHT|      |      | LEFT | DOWN |  UP  | RIGHT|      |      |
 * |-------+------+------+------+------+------|------+------+------+------+------+------|
 * |       |ALT+1 |ALT+2 |ALT+3 |ALT+4 |ALT+5 |ALT+6 |ALT+7 |ALT+8 |ALT+9 |ALT+10|      |
 * |-------+------+------+------+------+------+------+------+------+------+------+------|
 * |       |      |      |      |VOLDWN|             |VOL UP| PREV | MUTE |PLY/PS| NEXT |
 * `------------------------------------------------------------------------------------'
 */
[_SPACE_FN] = LAYOUT_planck_grid(
    KC_PSCR, _______,    KC_UP,      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______, KC_LEFT,    KC_DOWN,    KC_RIGHT,   _______,    _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   _______,    _______,
    _______, LALT(KC_1), LALT(KC_2), LALT(KC_3), LALT(KC_4), LALT(KC_5), LALT(KC_6), LALT(KC_7), LALT(KC_8), LALT(KC_9), LALT(KC_0), _______,
    _______, _______,    _______,    _______,    KC_VOLD,    _______,    _______,    KC_VOLU,    KC_MPRV,    KC_MUTE,    KC_MPLY,    KC_MNXT
),

/* Gaming Layer
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | FN   | GUI  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_GAMING] = LAYOUT_planck_grid(
    KC_TAB,            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,      KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    QK_GESC,           KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,      KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    TD(TD_SHIFT_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,      KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_ENT),
    KC_LCTL, FN,       KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,    RAISE,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Boot |Debug |      |      |      |      |DMREC1|DMREC2|      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |GAMING|      |      |      |      |      |DMPLY1|DMPLY2|Audoff|Aud on|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |DMRSTP|      |Musoff|Mus on|MusMod|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |AG_TOG|      |             |      |      |Voice-|Voice+|      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, QK_BOOT, DB_TOGG,   _______,   _______,  _______, _______, DM_REC1, DM_REC2,   _______,   _______,   _______,
    _______, TG(_GAMING), ___,   _______,   _______,  _______, _______, DM_PLY1, DM_PLY2,   AU_OFF,    AU_ON,     _______,
    _______, _______, _______,   _______,   _______,  _______, _______, DM_RSTP, _______,   MU_OFF,    MU_ON,     MU_NEXT,
    _______, _______, _______,   AG_TOGG,   _______,  _______, _______, _______, _______,   AU_PREV,   AU_NEXT,    _______
)

};

/* Layer Change Code
 * Runs everytime the layer gets changed
 */
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}

void matrix_scan_user(void) {
    #ifdef AUDIO_ENABLE
        if (muse_mode) {
            if (muse_counter == 0) {
                uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
                if (muse_note != last_muse_note) {
                    stop_note(compute_freq_for_midi_note(last_muse_note));
                    play_note(compute_freq_for_midi_note(muse_note), 0xF);
                    last_muse_note = muse_note;
                }
            }
            muse_counter = (muse_counter + 1) % muse_tempo;
        }
    #endif
}

/* Controls which keycodes are processed when in music mode
 * Return: false if key should be honored in music mode
 */
bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
            return false;
        default:
            return true;
    }
}
