/* Copyright 2023 Pi Fisher
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

#define SCREEN_LEFT LCTL(LGUI(KC_LEFT))
#define SCREEN_RIGHT LCTL(LGUI(KC_RIGHT))
#define SCREENSHOT LGUI(LSFT(KC_S))

#ifdef AUDIO_ENABLE
#    include "muse.h"
#endif

enum planck_layers {
    _QWERTY,
    _COLEMAK, // one day…I might learn this
    _RAISE,
    _LOWER,
    _ADJUST,
    _UTILS,
};

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    SHRUG,
    SIGNATURE,
    EMAIL,
    THUMB_U,
    WAVE,
    EYES,
    INTERRO,
};

// needs to be defined, but I don't use it
const uint32_t unicode_map[] PROGMEM = {};

enum tap_dance_declarations {
    TD_DOT_DOTS,
    TD_DASHES,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
    * ,-----------------------------------------------------------------------------------.
    * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | UTILS| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
    * `-----------------------------------------------------------------------------------'
    */
    [_QWERTY] = LAYOUT_planck_grid(
        KC_ESCAPE,      KC_Q,         KC_W,    KC_E,    KC_R,       KC_T,   KC_Y,    KC_U,       KC_I,     KC_O,            KC_P,             KC_BACKSPACE,
        LALT_T(KC_TAB), KC_A,         KC_S,    KC_D,    KC_F,       KC_G,   KC_H,    KC_J,       KC_K,     KC_L,            KC_SEMICOLON,     LGUI_T(KC_QUOTE),
        KC_LSFT,        LCTL_T(KC_Z), KC_X,    KC_C,    KC_V,       KC_B,   KC_N,    KC_M,       KC_COMMA, TD(TD_DOT_DOTS), RCTL_T(KC_SLASH), RSFT_T(KC_ENT),
        MO(_UTILS),     KC_LCTL,      KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC, XXXXXXX, MO(_RAISE), KC_LEFT,  KC_DOWN,         KC_UP,            KC_RIGHT
    ),

    /* Colemak
    * ,-----------------------------------------------------------------------------------.
    * | Esc  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Tab  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  '   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | UTILS| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
    * `-----------------------------------------------------------------------------------'
    */
    [_COLEMAK] = LAYOUT_planck_grid(
        KC_ESCAPE,      KC_Q,         KC_W,    KC_F,    KC_P,       KC_G,   KC_J,    KC_L,       KC_U,     KC_Y,            KC_SEMICOLON,     KC_BACKSPACE,
        LALT_T(KC_TAB), KC_A,         KC_R,    KC_S,    KC_T,       KC_D,   KC_H,    KC_N,       KC_E,     KC_I,            KC_O,             LGUI_T(KC_QUOTE),
        KC_LSFT,        LCTL_T(KC_Z), KC_X,    KC_C,    KC_V,       KC_B,   KC_K,    KC_M,       KC_COMMA, TD(TD_DOT_DOTS), RCTL_T(KC_SLASH), RSFT_T(KC_ENT),
        MO(_UTILS),     KC_LCTL,      KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC, XXXXXXX, MO(_RAISE), KC_LEFT,  KC_DOWN,         KC_UP,            KC_RIGHT
    ),

    /* Raise
    * ,-----------------------------------------------------------------------------------.
    * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_RAISE] = LAYOUT_planck_grid(
        KC_GRAVE,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,          KC_8,     KC_9,            KC_0,             _______,
        KC_DELETE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   TD(TD_DASHES), KC_EQUAL, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH,
        _______,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,       _______,  _______,         _______,          _______,
        _______,   _______, _______, _______, _______, _______, XXXXXXX, _______,       _______,  _______,         _______,          _______
    ),

    /* Lower
    * ,-----------------------------------------------------------------------------------.
    * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      | Home | PgDn | PgUp | End  |
    * `-----------------------------------------------------------------------------------'
    */
    [_LOWER] = LAYOUT_planck_grid(
        KC_TILDE,  KC_EXCLAIM, KC_AT,   KC_HASH, KC_DOLLAR,  KC_PERCENT, KC_CIRCUMFLEX, KC_AMPERSAND,  KC_ASTERISK, KC_LEFT_PAREN,       KC_RIGHT_PAREN,       _______,
        KC_DELETE, KC_F1,      KC_F2,   KC_F3,   KC_F4,      KC_F5,      KC_F6,         KC_UNDERSCORE, KC_PLUS,     KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_PIPE,
        _______,   KC_F7,      KC_F8,   KC_F9,   KC_F10,     KC_F11,     KC_F12,        _______,       _______,     _______,             _______,              _______,
        _______,   _______,    _______, _______, _______,    _______,    XXXXXXX,       _______,       KC_HOME,     KC_PAGE_DOWN,        KC_PAGE_UP,           KC_END
    ),

    /* Adjust (Lower + Raise)
    *                      v------------------------RGB CONTROL--------------------v
    * ,-----------------------------------------------------------------------------------.
    * |      |Qwerty|      |RgbTog|RgbMod| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |Colemk|Music+| AudOn|AudOff|      |      |      |      |      |      | Boot |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |Voice-|Voice+| MusOn|MusOff|MidiOn|MidiOf|      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      | Vol0 | Vol- | Vol+ |RgbTog|
    * `-----------------------------------------------------------------------------------'
    */
    [_ADJUST] = LAYOUT_planck_grid(
        _______, QWERTY,  _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,
        _______, COLEMAK, MU_NEXT, AU_ON,   AU_OFF,  _______, _______, _______, _______, _______, _______, QK_BOOTLOADER,
        _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, XXXXXXX, _______, KC_MUTE, KC_VOLD, KC_VOLU, RGB_TOG
    ),

    /* Utils
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      |      |   👀  |      |      |   👍🏻  |   7  |   8  |   9  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |PrtScn|      |      |      |      |   👋🏻  |   4  |   5  |   6  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      | Undo |      |      |      |      |      |   0  |   1  |   2  |   3  |   ‽  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |C+PgUp|C+PgDn|Scn <-|Scn ->|             |      | email|  sig |shrug?|      |
    * `-----------------------------------------------------------------------------------'
    */
    [_UTILS] = LAYOUT_planck_grid(
        _______, _______,          _______,            EYES,        _______,      _______, THUMB_U, KC_7,    KC_8,  KC_9,      _______, _______,
        _______, _______,          SCREENSHOT,         _______,     _______,      _______, WAVE,    KC_4,    KC_5,  KC_6,      _______, _______,
        _______, LCTL(KC_Z),       _______,            _______,     _______,      _______, KC_0,    KC_1,    KC_2,  KC_3,      INTERRO, _______,
        _______, LCTL(KC_PAGE_UP), LCTL(KC_PAGE_DOWN), SCREEN_LEFT, SCREEN_RIGHT, _______, XXXXXXX, _______, EMAIL, SIGNATURE, SHRUG,   _______
    )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_RSFT, KC_ENTER):
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case SHRUG:
            if (record->event.pressed) {
                send_unicode_string("¯\\_(ツ)_/¯"); // Shruggie
            }
            return false;
        case SIGNATURE:
            if (record->event.pressed) {
                send_unicode_string(SIGNATURE_STRING); // 4∑(-1)^n÷(2n+1) Person Rowing Boat, Fishing Pole
            }
            return false;
        case EMAIL:
            if (record->event.pressed) {
                send_unicode_string(EMAIL_STRING); // Person: Light Skin Tone, Beard @ Person Rowing Boat, Fishing Pole
            }
            return false;
        case THUMB_U:
            if (record->event.pressed) {
                send_unicode_string("👍🏻"); // Thumbs Up: Light Skin Tone
            }
            return false;
        case WAVE:
            if (record->event.pressed) {
                send_unicode_string("👋🏻"); // Waving Hand: Light Skin Tone
            }
            return false;
        case EYES:
            if (record->event.pressed) {
                send_unicode_string("👀"); // Eyes
            }
            return false;
        case INTERRO:
            if (record->event.pressed) {
                send_unicode_string("‽"); // interrobang
            }
            return false;
        default:
            return true;
    }
}

// Music
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

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

// Tap Dance ./…
static bool dot_held;

void dot_dots_each(tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        unregister_code(KC_DOT);
    }
    register_code(KC_DOT);
}

void dot_dots_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        unregister_code(KC_DOT);
        tap_code(KC_BACKSPACE);
        tap_code(KC_BACKSPACE);
        tap_code(KC_BACKSPACE);
        send_unicode_string("…"); // ellipsis
    } else {
        if (state->pressed) {
            dot_held = true;
        } else {
            unregister_code(KC_DOT);
            dot_held = false;
        }
    }
};

void dot_dots_reset(tap_dance_state_t *state, void *user_data) {
    if(dot_held) {
        unregister_code(KC_DOT);
        dot_held = false;
    }
};

// Tap Dance -/–/—
static bool minus_held;

void dashes_each(tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        unregister_code(KC_MINUS);
    }
    register_code(KC_MINUS);
}

void dashes_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            unregister_code(KC_MINUS);
            tap_code(KC_BACKSPACE);
            tap_code(KC_BACKSPACE);
            send_unicode_string("–"); // en dash
            break;
        case 3:
            unregister_code(KC_MINUS);
            tap_code(KC_BACKSPACE);
            tap_code(KC_BACKSPACE);
            tap_code(KC_BACKSPACE);
            send_unicode_string("—"); // em dash
            break;
        default:
            if (state->pressed) {
                minus_held = true;
            } else {
                unregister_code(KC_MINUS);
                minus_held = false;
            }
            break;
    }
};

void dashes_reset(tap_dance_state_t *state, void *user_data) {
    if(minus_held) {
        unregister_code(KC_MINUS);
        minus_held = false;
    }
};

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for period, thrice for ellipsis
    [TD_DOT_DOTS] = ACTION_TAP_DANCE_FN_ADVANCED(dot_dots_each, dot_dots_finished, dot_dots_reset),
    // Tap once for hyphen, twice for en dash, thrice for em dash
    [TD_DASHES] = ACTION_TAP_DANCE_FN_ADVANCED(dashes_each, dashes_finished, dashes_reset),
};
