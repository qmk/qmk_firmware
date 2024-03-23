/* Copyright 2015-2023 Jack Humbert
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

enum planck_layers { _QWERTY, _NUMPAD, _WORKMAN, _LWR, _RSE, _NAV, _ADJ };

enum planck_keycodes { 
    QWERTY = SAFE_RANGE,
    COLEMAK, 
    DVORAK, 
    PLOVER, 
    WORKMAN, 
    BACKLIT, 
    EXT_PLV, 
    LWR, 
    RSE, 
    NUMPAD, 
    NAVMO, 
    NATG, 
    ADJ, 
    DF0, 
    DF1, 
    DF2
 };

#define LWR MO(_LWR)
#define RSE MO(_RSE)
#define QWERTY MO(_QWERTY)
#define NUMPAD MO(_NUMPAD)
#define WORKMAN MO(_WORKMAN)
#define NAVMO MO(_NAV)
#define NAVTG TG(_NAV)
#define ADJ MO(_ADJ)
#define DF0 DF(_QWERTY)
#define DF1 DF(_NUMPAD)
#define DF2 DF(_WORKMAN)

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY (LAYER 0)
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | BKSP |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TAB  |A/GUI |S/ALT |D/CTRL|F/SHFT|   G  |   H  |J/SHFT|K/CTRL|L/ALT | ;/GUI|  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAP L|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |ENTER |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | NAV  | CAPSW|      |      | LWR  |NUMPD |SPACE |  RSE |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    KC_TAB, LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G, KC_H, RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN), KC_QUOT,
    KC_CAPS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT ,
    NAVTG, CW_TOGG, XXXXXXX, XXXXXXX, LWR, NUMPAD, KC_SPC, RSE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* NUMBER PAD (LAYER 1)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |PAGEUP| HOME | END  |      |      | NUM 7| NUM 8| NUM 9|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |PAGEDN| NUMLK| DEL  |      |      | NUM 4| NUM 5| NUM 6|   *  |  +   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | NUM 1| NUM 2| NUM 3|  /   |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | NAV  |      |      |      |      |      |      | SPACE| NUM 0|   .  | ENTER|      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, KC_PGUP, KC_HOME, KC_END, XXXXXXX, XXXXXXX, KC_P7, KC_P8, KC_P9, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_PGDN, KC_NUM, KC_DEL, XXXXXXX, XXXXXXX, KC_P4, KC_P5, KC_P6, KC_PSLS, KC_PPLS,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P1, KC_P2, KC_P3, KC_PAST, KC_PMNS,
    NAVTG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC, KC_P0, KC_PDOT, KC_PENT, XXXXXXX
),

/* WORKMAN (LAYER 2)
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   Q  |   D  |   R  |   W  |   B  |   J  |   F  |   U  |   P  |   ;  | BKSP |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TAB  |A/GUI |S/ALT |H/CTRL|T/SHFT|   G  |   H  |N/SHFT|E/CTRL|O/ALT | I/GUI|  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAP L|   Z  |   X  |   M  |   C  |   V  |   K  |   L  |   ,  |   .  |   /  |ENTER |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | NAV  | CAPSW|      |      | LOWER| NUMPD| SPACE| RAISE|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_WORKMAN] = LAYOUT_planck_grid(
    KC_ESC, KC_Q, KC_D, KC_R, KC_W, KC_B, KC_J, KC_F, KC_U, KC_P, KC_SCLN, KC_BSPC,
    KC_TAB, LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_H), LSFT_T(KC_T), KC_G, KC_H, RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_O), RGUI_T(KC_I), C_QUOT,
    XXXXXXX, KC_Z, KC_X, KC_M, KC_C, KC_V, KC_K, KC_L, KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
    NAVTG, CW_TOGG, XXXXXXX, XXXXXXX, LWR, NUMPAD, KC_SPC, RSE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* LOWER (LAYER 3)
 * ,-----------------------------------------------------------------------------------.
 * |      |  1!  |  2@  |  3#  |  4$  |  5%  |  6^  |  7&  |  8*  |  9(  |  0)  | BS   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  `~  | -_  |LSFT/=+|      |      |RSFT/[{| ]}  |  \|  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      | SPACE| ADJ  |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LWR] = LAYOUT_planck_grid(
    XXXXXXX, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
    XXXXXXX, XXXXXXX, KC_GRV, KC_MINS, LSFT_T(KC_EQL), XXXXXXX, XXXXXXX, RSFT_T(KC_LBRC), KC_RBRC, KC_BSLS, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC, ADJ, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* RAISE (LAYER 4)
 * ,-----------------------------------------------------------------------------------.
 * | F1   | F2   | F3   | F4   | F5   | F6   | F7   | F8   | F9   | F10  | F11  | F12  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | PREV | PLAY | NEXT |VOL - |VOL + | MUTE |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | ADJ  |      | SPACE|      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RSE] = LAYOUT_planck_grid(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
    KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ADJ, XXXXXXX, KC_SPC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* NAV (LAYER 5)
 * ,-----------------------------------------------------------------------------------.
 * |  DF0 |      |      |      |      |      |      |      |  UP  |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | LGUI | LALT | LCTRL| LSHFT|      |      | LEFT | DOWN | RIGHT|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRANS|      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAV] = LAYOUT_planck_grid(
    DF0, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust (Lower + Raise)  (LAYER 6)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |EEPROM|MUSmod|Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      | <EEPROM = 
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof| TTD  | TTP  | TTU  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | DF0  | DF1  | DF2  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJ] = LAYOUT_planck_grid(
    XXXXXXX, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL ,
    XXXXXXX, EE_CLR, MU_NEXT, AU_ON, AU_OFF, AG_NORM, AG_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, AU_PREV, AU_NEXT, MU_ON, MU_OFF, MI_ON, MI_OFF, DT_DOWN, DT_PRNT, DT_UP, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DF0, DF1, DF2, XXXXXXX, XXXXXXX
)

};
/* clang-format on */

#ifdef AUDIO_ENABLE
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                print("mode just switched to qwerty and this is a huge string\n");
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
        case DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            return false;
            break;
        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RSFT);
            }
            return false;
            break;
        case PLOVER:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(plover_song);
#endif
                layer_off(_RAISE);
                layer_off(_LOWER);
                layer_off(_ADJUST);
                layer_on(_PLOVER);
                if (!eeconfig_is_enabled()) {
                    eeconfig_init();
                }
                keymap_config.raw  = eeconfig_read_keymap();
                keymap_config.nkro = 1;
                eeconfig_update_keymap(keymap_config.raw);
            }
            return false;
            break;
        case EXT_PLV:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(plover_gb_song);
#endif
                layer_off(_PLOVER);
            }
            return false;
            break;
    }
    return true;
}

/* clang-format off */
float melody[8][2][2] = {
    {{440.0f, 8}, {440.0f, 24}}, 
    {{440.0f, 8}, {440.0f, 24}}, 
    {{440.0f, 8}, {440.0f, 24}}, 
    {{440.0f, 8}, {440.0f, 24}}, 
    {{440.0f, 8}, {440.0f, 24}}, 
    {{440.0f, 8}, {440.0f, 24}}, 
    {{440.0f, 8}, {440.0f, 24}}, 
    {{440.0f, 8}, {440.0f, 24}},
};
/* clang-format on */

#define JUST_MINOR_THIRD 1.2
#define JUST_MAJOR_THIRD 1.25
#define JUST_PERFECT_FOURTH 1.33333333
#define JUST_TRITONE 1.42222222
#define JUST_PERFECT_FIFTH 1.33333333

#define ET12_MINOR_SECOND 1.059463
#define ET12_MAJOR_SECOND 1.122462
#define ET12_MINOR_THIRD 1.189207
#define ET12_MAJOR_THIRD 1.259921
#define ET12_PERFECT_FOURTH 1.33484
#define ET12_TRITONE 1.414214
#define ET12_PERFECT_FIFTH 1.498307	

deferred_token tokens[8];

uint32_t reset_note(uint32_t trigger_time, void *note) {
    *(float*)note = 440.0f;
    return 0;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    cancel_deferred_exec(tokens[index]);
    if (clockwise) {
        melody[index][1][0] = melody[index][1][0] * ET12_MINOR_SECOND;
        melody[index][0][0] = melody[index][1][0] / ET12_PERFECT_FIFTH;
        audio_play_melody(&melody[index], 2, false);
    } else {
        melody[index][1][0] = melody[index][1][0] / ET12_MINOR_SECOND;
        melody[index][0][0] = melody[index][1][0] * ET12_TRITONE;
        audio_play_melody(&melody[index], 2, false);
    }
    tokens[index] = defer_exec(1000, reset_note, &melody[index][1][0]);
    return false;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) {
                    PLAY_SONG(plover_song);
                }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) {
                    PLAY_SONG(plover_gb_song);
                }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
    }
    return true;
}