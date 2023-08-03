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
#include "keymap.h"
#include "tap_dance.h"

#ifdef AUDIO_ENABLE
#    include "muse.h"
#    include "muse_mode.h"
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
    * ,-----------------------------------------------------------------------------------.
    * |  Esc |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |  Tab |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Enter|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | UTILS| Ctrl |  Alt |  GUI | Lower|    Space    | Raise| Left | Down |  Up  | Right|
    * `-----------------------------------------------------------------------------------'
    */
    [_QWERTY] = LAYOUT_planck_grid(
        KC_ESCAPE,      KC_Q,         KC_W,    KC_E,    KC_R,       KC_T,   KC_Y,    KC_U,       KC_I,     KC_O,     KC_P,             KC_BACKSPACE,
        LALT_T(KC_TAB), KC_A,         KC_S,    KC_D,    KC_F,       KC_G,   KC_H,    KC_J,       KC_K,     KC_L,     KC_SEMICOLON,     LGUI_T(KC_QUOTE),
        KC_LSFT,        LCTL_T(KC_Z), KC_X,    KC_C,    KC_V,       KC_B,   KC_N,    KC_M,       KC_COMMA, DOT_DOTS, RCTL_T(KC_SLASH), RSFT_T(KC_ENT),
        MO(_UTILS),     KC_LCTL,      KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC, XXXXXXX, MO(_RAISE), KC_LEFT,  KC_DOWN,  KC_UP,            KC_RIGHT
    ),

    /* Colemak DH
    * ,-----------------------------------------------------------------------------------.
    * |  Esc |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |  Tab |   A  |   R  |   S  |   T  |   G  |   M  |   N  |   E  |   I  |   O  |   '  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |   /  | Enter|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | UTILS| Ctrl |  Alt |  GUI | Lower|    Space    | Raise| Left | Down |  Up  | Right|
    * `-----------------------------------------------------------------------------------'
    */
    [_COLEMAK_DH] = LAYOUT_planck_grid(
        KC_ESCAPE,      KC_Q,         KC_W,    KC_F,    KC_P,       KC_B,   KC_J,    KC_L,       KC_U,     KC_Y,     KC_SEMICOLON,     KC_BACKSPACE,
        LALT_T(KC_TAB), KC_A,         KC_R,    KC_S,    KC_T,       KC_G,   KC_M,    KC_N,       KC_E,     KC_I,     KC_O,             LGUI_T(KC_QUOTE),
        KC_LSFT,        LCTL_T(KC_Z), KC_X,    KC_C,    KC_D,       KC_V,   KC_K,    KC_H,       KC_COMMA, DOT_DOTS, RCTL_T(KC_SLASH), RSFT_T(KC_ENT),
        MO(_UTILS),     KC_LCTL,      KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC, XXXXXXX, MO(_RAISE), KC_LEFT,  KC_DOWN,  KC_UP,            KC_RIGHT
    ),

    /* Raise
    * ,-----------------------------------------------------------------------------------.
    * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |  Del |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |   \  |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_RAISE] = LAYOUT_planck_grid(
        KC_GRAVE,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_8,     KC_9,            KC_0,             _______,
        KC_DELETE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINUS, KC_EQUAL, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH,
        _______,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,  _______,  _______,         _______,          _______,
        _______,   _______, _______, _______, _______, _______, XXXXXXX, _______,  _______,  _______,         _______,          _______
    ),

    /* Lower
    * ,-----------------------------------------------------------------------------------.
    * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |  Del |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |   |  |
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

    /* Music (Only active during music mode, and suppresses everything but turning off music mode)
    * ,-----------------------------------------------------------------------------------.
    * | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | XXXX | XXXX | XXXX | XXXX | XXXX |   EndMuse   | XXXX | XXXX | XXXX | XXXX | XXXX |
    * `-----------------------------------------------------------------------------------'
    */
    [_MUSIC] = LAYOUT_planck_grid(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, END_MUS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /* Adjust (Lower + Raise)
    *                      v------------------------RGB CONTROL--------------------v
    * ,-----------------------------------------------------------------------------------.
    * |      |Qwerty|      |RgbTog|RgbMod| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |Colemk|Music+| AudOn|AudOff|      |      |      |      |      |      | Boot |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |Voice-|Voice+| MusOn|      |MidiOn|MidiOf|      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      | Vol0 | Vol- | Vol+ |RgbTog|
    * `-----------------------------------------------------------------------------------'
    */
    [_ADJUST] = LAYOUT_planck_grid(
        _______, QWERTY,  _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,
        _______, COLEMAK, MU_NEXT, AU_ON,   AU_OFF,  _______, _______, _______, _______, _______, _______, QK_BOOTLOADER,
        _______, AU_PREV, AU_NEXT, MU_ON,   _______, MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, XXXXXXX, _______, KC_MUTE, KC_VOLD, KC_VOLU, RGB_TOG
    ),

    /* Utils
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      |      |  O.O |      | (+1) |   7  |   8  |   9  |      |dashes|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |PrtScn|      |      |      |  hi  |   4  |   5  |   6  |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      | Undo |      |      |      |      |   0  |   1  |   2  |   3  |   ‽  |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |C+PgUp|C+PgDn|Scn <-|Scn ->|             |      | email|  sig |shrug?|      |
    * `-----------------------------------------------------------------------------------'
    */
    [_UTILS] = LAYOUT_planck_grid(
        _______, _______,          _______,            EYES,        _______,      _______, THUMB_U, KC_7,    KC_8,  KC_9,      _______, DASHES,
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
                set_single_persistent_default_layer(_COLEMAK_DH);
            }
            return false;
        case MU_ON:
            if (record->event.pressed) {
                layer_on(_MUSIC);
            }
            return true; // then process keycode
        case END_MUS:
            if (record->event.pressed) {
                layer_off(_MUSIC);
                #ifdef AUDIO_ENABLE
                    music_off();
                #endif
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
