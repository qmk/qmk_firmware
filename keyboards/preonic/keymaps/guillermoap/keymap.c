/* Copyright 2023 Guillermo Aguirre
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

enum preonic_layers {
    _BASE,
    _GAMING,
    _LOWER,
    _RAISE,
    _CONFIG,
};

enum preonic_keycodes {
    BASE = SAFE_RANGE,
    GAMING,
    LOWER,
    RAISE,
    CONFIG,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Base
 * ,------------------------------------------------------------------------------------------.
 * | Esc         |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |-------------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab         |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |-------------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl        |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |-------------+------+------+------+------+------|------+------+------+------+------+------|
 * | HOLD Shift  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |  /   |
 * | TOGGLE Caps |      |      |      |      |      |      |      |      |      |      |      |
 * |-------------+------+------+------+------+------+------+------+------+------+------+------|
 * | GUI         |  `   |  Alt |Lower |Enter |Enter |Space |Space |Raise | Left | Down |Right |
 * `------------------------------------------------------------------------------------------'
 */
[_BASE] = LAYOUT_preonic_grid(
  KC_ESC,          KC_1,   KC_2,            KC_3,  KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,          KC_Q,   KC_W,            KC_E,  KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_BSLS,
  KC_LCTL,         KC_A,   KC_S,            KC_D,  KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  LSFT_T(KC_CAPS), KC_Z,   KC_X,            KC_C,  KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_UP,   KC_SLSH,
  KC_LGUI,         KC_GRV, LALT_T(KC_RALT), MO(2), KC_ENT, KC_ENT, KC_SPC, KC_SPC, MO(3),   KC_LEFT, KC_DOWN, KC_RGHT
),

/* Gaming
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  `   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |  Alt |Lower |Space |Space |Enter |Enter |Raise | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_GAMING] = LAYOUT_preonic_grid(
  KC_ESC,  KC_1,    KC_2,    KC_3,  KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_BSLS,
  KC_GRV,  KC_A,    KC_S,    KC_D,  KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,  KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_UP,   KC_SLSH,
  KC_LCTL, KC_LGUI, KC_LALT, MO(2), KC_SPC, KC_SPC, KC_ENT, KC_ENT, MO(3),   KC_LEFT, KC_DOWN, KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ▽  |   ▽  | Mute |Vol + | Play |   ▽  |   ▽  |   _  |   +  |   {  |   }  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ▽  |   ▽  | Prev |Vol - | Next |   ▽  |   ▽  |   -  |   =  |   [  |   ]  |  ▽   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   ▽  |CTRL_Z|   ▽  |CTRL_C|   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |CONFIG|   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,      KC_F3,   KC_F4,      KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_TRNS, KC_TRNS,    KC_MUTE, KC_VOLU,    KC_MPLY, KC_TRNS, KC_TRNS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_BSLS,
  KC_TRNS, KC_TRNS,    KC_MPRV, KC_VOLD,    KC_MNXT, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_TRNS,
  KC_TRNS, LCTL(KC_Z), KC_TRNS, LCTL(KC_C), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS,    KC_TRNS, TG(4),   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   {  |   }  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ▽  |   6  |   7  |   8  |   9  |   0  |   ▽  |   ▽  |  Up  |   [  |   ]  |   ▽  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   1  |   2  |   3  |   4  |   5  |   ▽  | Left | Down |Right |   ▽  |   ▽  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  | Home | End  | PgUp |PgDown|   ▽  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  GUI |PrntSc|R Alt |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid(
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL,  KC_DEL,
  KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS, KC_TRNS, KC_UP,   KC_LBRC, KC_RBRC, KC_TRNS,
  KC_LCTL, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,
  KC_RSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_END,  KC_PGUP, KC_PGDN, KC_TRNS,
  KC_RGUI, KC_PSCR, KC_RALT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* Config
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ▽  | Reset| Debug|   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ▽  |   ▽  |   ▽  |Aud on|AudOff|CGnorm|CGswap| Base |Gaming|   ▽  |   ▽  |   ▽  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   ▽  |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |   ▽  |
 * `-----------------------------------------------------------------------------------'
 */
[_CONFIG] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_TRNS, QK_BOOT, DB_TOGG, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,
  KC_TRNS, KC_TRNS, MU_MOD,  AU_ON,   AU_OFF,   CG_NORM, CG_SWAP, DF(0),   DF(1),   KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,   MI_ON,   MI_OFF,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
)
};

/* Encoder
 * Currently using ENCONDER_MAP_ENABLE
 */
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] =   { ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP) },       // Mouse Scroll Down | Mouse Scroll Up
    [_GAMING] = { ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP) },       // Mouse Scroll Down | Mouse Scroll Up
    [_LOWER] =  { ENCODER_CCW_CW(LCTL(KC_TAB), LCTL(LSFT(KC_TAB))) }, // Ctrl + Tab        | Ctrl + Shift + Tab
    [_RAISE] =  { ENCODER_CCW_CW(KC_MS_WH_LEFT, KC_MS_WH_RIGHT) },    // Mouse Scroll Left | Mouse Scroll Right
    [_CONFIG] =  { },
};
#endif

/* Default music config
 * Don't really understand what this does
 */
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_CONFIG);
            } else {
                layer_off(_CONFIG);
            }
            break;
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
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
            return false;
        default:
            return true;
    }
}
