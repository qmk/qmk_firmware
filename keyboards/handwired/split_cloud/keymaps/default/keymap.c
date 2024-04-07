/* Copyright 2023 Cloud Chagnon
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

// clang-format off

enum layer_names {
    _QWERTY,
    _COLEMAK,
    _DVORAK,
    _LOWER,
    _RAISE,
    _PLOVER,
    _ADJUST
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    DVORAK,
    PLOVER,
    EXT_PLV
};

#define ST_BOLT QK_STENO_BOLT
#define ST_GEM QK_STENO_GEMINI

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl | GUI  | Alt  |RCtrl |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_ortho_5x12(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL ,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
        KC_LCTL, KC_LGUI, KC_LALT, KC_RCTL, TL_LOWR, KC_SPC, KC_SPC, TL_UPPR, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    /* Colemak
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl | GUI  | Alt  |RCtrl |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_COLEMAK] = LAYOUT_ortho_5x12(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,   KC_J,   KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL ,
        KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,   KC_H,   KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_K,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
        KC_LCTL, KC_LGUI, KC_LALT, KC_RCTL, TL_LOWR, KC_SPC, KC_SPC, TL_UPPR, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    /* Dvorak
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Del  |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl | GUI  | Alt  |RCtrl |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_DVORAK] = LAYOUT_ortho_5x12(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_BSPC,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,  KC_F,    KC_G,    KC_C,    KC_R,    KC_L,  KC_DEL,
        KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,  KC_D,    KC_H,    KC_T,    KC_N,    KC_S,  KC_SLSH,
        KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,  KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,  KC_ENT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_RCTL, TL_LOWR, KC_SPC, KC_SPC, TL_UPPR, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
    ),

    /* Lower
     * ,-----------------------------------------------------------------------------------.
     * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
     * `-----------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT_ortho_5x12(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_DEL ,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
    ),

    /* Raise
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / | Pg Up| Pg Dn|      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
     * `-----------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT_ortho_5x12(
        KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,     KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,     KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL ,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,  KC_F4,    KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        _______, KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ),

    /* Plover layer (http://opensteno.org)
     * ,-----------------------------------------------------------------------------------.
     * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |  FN  |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Exit |      |      |   A  |   O  |      |      |   E  |   U  |  PWR | RES1 | RES2 |
     * `-----------------------------------------------------------------------------------'
     */

    [_PLOVER] = LAYOUT_ortho_5x12(
        STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC ,
        STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR ,
        XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR ,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        EXT_PLV, XXXXXXX, XXXXXXX, XXXXXXX, STN_A,   STN_O,   STN_E,   STN_U,   XXXXXXX, STN_PWR, STN_RE1, STN_RE2
    ),

    /* Adjust (Lower + Raise)
     * ,-----------------------------------------------------------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      | Reset| Debug|      |      |      |      |      |      |      |      |  Del |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |      |Aud cy|Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |TXBOLT|GEM RP|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT_ortho_5x12(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 ,
        _______, QK_BOOT, DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL ,
        _______, _______, _______, _______, _______, _______, _______, QWERTY,  COLEMAK, DVORAK,  PLOVER,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ST_BOLT, ST_GEM ,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )

};

// clang-format on

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
        case DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            return false;
        case PLOVER:
            if (!record->event.pressed) {
                layer_on(_PLOVER);
            }
            return false;
        case EXT_PLV:
            if (record->event.pressed) {
                layer_off(_PLOVER);
            }
            return false;
    }
    return true;
};
