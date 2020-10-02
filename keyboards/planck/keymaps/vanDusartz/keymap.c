/* Copyright 2015-2017 Jack Humbert
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
 *
 * This keymap authored by Peter VanDusartz IV <ImHumble@gmail.com>
 */

#include QMK_KEYBOARD_H
#include "muse.h"

enum planck_layers { _Mac, _PC, _Num_Func, _Sym, _ADJUST };

enum planck_keycodes { QWERTY = SAFE_RANGE, BACKLIT };

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Mac
     * ,-----------------------------------------------------------------------------------.
     * |   Q  |   W  |   E  |   R  |   T  |      |      |   Y  |   U  |   I  |   O  |   P  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   A  |   S  |   D  |   F  |   G  | Esc  |      |   H  |   J  |   K  |   L  |   ;  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   Z  |   X  |   C  |   V  |   B  | Del  |      |   N  |   M  |   ,  |   .  |  "   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |Space | Ctrl |  Alt |  GUI |Shift | Bksp |Tab/NF|Space |Enter | Caps |VolDn |VolUp |
     * `-----------------------------------------------------------------------------------'
     */
    [_Mac] = LAYOUT_planck_grid(
        KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,   KC_NO,                 KC_Y,   KC_U,             KC_I,    KC_O,    KC_P,
        KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_ESC,  KC_NO,                 KC_H,   KC_J,             KC_K,    KC_L,    KC_SCLN,
        KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_DEL,  KC_NO,                 KC_N,   KC_M,             KC_COMM, KC_DOT,  KC_QUOT,
        KC_SPC, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_BSPC, LT(_Num_Func, KC_TAB), KC_SPC, LT(_Sym, KC_ENT), KC_CAPS, KC_VOLD, KC_VOLU
    ),

    /* PC
     * ,-----------------------------------------------------------------------------------.
     * |   Q  |   W  |   E  |   R  |   T  |      |PrtScn|   Y  |   U  |   I  |   O  |   P  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   A  |   S  |   D  |   F  |   G  | Esc  |      |   H  |   J  |   K  |   L  |   ;  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   Z  |   X  |   C  |   V  |   B  | Del  |      |   N  |   M  |   ,  |   .  |  "   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |Space |  GUI |  Alt | Ctrl |Shift | Bksp | Tab  |Space |Enter | Caps |VolDn |VolUp |
     * `-----------------------------------------------------------------------------------'
     */
    [_PC] = LAYOUT_planck_grid(
        KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,   KC_PSCR,               KC_Y,   KC_U,             KC_I,    KC_O,    KC_P,
        KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_ESC,  KC_NO,                 KC_H,   KC_J,             KC_K,    KC_L,    KC_SCLN,
        KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_DEL,  KC_NO,                 KC_N,   KC_M,             KC_COMM, KC_DOT,  KC_QUOT,
        KC_SPC, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_BSPC, LT(_Num_Func, KC_TAB), KC_SPC, LT(_Sym, KC_ENT), KC_CAPS, KC_VOLD, KC_VOLU
    ),

    /* Num_Func
     * ,-----------------------------------------------------------------------------------.
     * |   1  |   2  |   3  |   4  |   5  |  PC  | Mac  |   6  |   7  |   8  |   9  |   0  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |      | Left | Down |  Up  |Right |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      | Home |Pg Dn |Pg Up | End  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |Space | Ctrl | Alt  | GUI  |Shift | Bksp |NumFnc|Space |Enter | Caps |BriDn |BriUp |
     * `-----------------------------------------------------------------------------------'
     */
    [_Num_Func] = LAYOUT_planck_grid(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    DF(_PC), DF(_Mac), KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______,  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,  _______, KC_M,    KC_COMM, KC_DOT,  KC_QUOT,
        _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, KC_BRID, KC_BRIU
    ),

    /* Sym
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   =  |   _  |   $  |      |      |      |      |   /  |   {  |   }  |   *  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   |  |   !  |   @  |   #  |      |      |      |      |   ?  |   (  |   )  |   -  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   ~  |   ^  |   %  |   &  |      |      |      |      |   \  |   [  |   ]  |   +  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |Space | Ctrl | Alt  | GUI  |Shift | Bksp | Tab  |Space |  Sym | Caps |VolDn |VolUp |
     * `-----------------------------------------------------------------------------------'
     */
    [_Sym] = LAYOUT_planck_grid(
        KC_GRV,  KC_EQL,  KC_UNDS, KC_DLR,  _______, _______, _______, _______, KC_U,    KC_I,    KC_O,     KC_P,
        KC_PIPE, KC_EXLM, KC_AT,   KC_HASH, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,    KC_RGHT,
        KC_TILD, KC_CIRC, KC_PERC, KC_AMPR, _______, _______, _______, _______, KC_M,    KC_COMM, KC_DOT,   KC_QUOT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______
    ),

    /* Adjust (Lower + Raise)
     *                      v------------------------RGB CONTROL--------------------v
     * ,-----------------------------------------------------------------------------------.
     * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT_planck_grid(
        _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, _______,
        _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______,  _______, _______, _______,
        _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
    )

};

#ifdef AUDIO_ENABLE
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); }

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
#ifdef BACKLIGHT_ENABLE
                backlight_step();
#endif
#ifdef KEYBOARD_planck_rev5
                writePinLow(E6);
#endif
            } else {
                unregister_code(KC_RSFT);
#ifdef KEYBOARD_planck_rev5
                writePinHigh(E6);
#endif
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

bool     muse_mode      = false;
uint8_t  last_muse_note = 0;
uint16_t muse_counter   = 0;
uint8_t  muse_offset    = 70;
uint16_t muse_tempo     = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo += 1;
            } else {
                muse_tempo -= 1;
            }
        }
    } else {
        if (clockwise) {
#ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_DOWN);
#else
            tap_code(KC_PGDN);
#endif
        } else {
#ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_UP);
#else
            tap_code(KC_PGUP);
#endif
        }
    }
}

void dip_switch_update_user(uint8_t index, bool active) {
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
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
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
