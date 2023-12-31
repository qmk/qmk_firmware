/*
Copyright 2023 Casey Borders

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* QWERTY
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |Backsp|
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
     * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   | Play |LOWER | LGUI | / Enter /       \Space \  | RGUI |RAISE | Mute |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */
    [_QWERTY] = LAYOUT(
      KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,     KC_0, KC_BSPC,
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                             KC_Y,    KC_U,    KC_I,    KC_O,     KC_P, KC_MINS,
      KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                             KC_H,    KC_J,    KC_K,    KC_L,  KC_SCLN, KC_QUOT,
      KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,        KC_RBRC,    KC_N,    KC_M, KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT,
                             KC_MPLY, MO(_LOWER), KC_LGUI,  KC_ENT,        KC_SPC, KC_RGUI, MO(_RAISE), KC_MUTE
    ),
    /* LOWER
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    |      |      |  Up  |      |   \  |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------.    ,-------|      | Left | Down |Right |   =  |      |
     * |------+------+------+------+------+------|   <   |    |   >   |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   | Play |LOWER | LGUI | / Enter /       \Space \  | RGUI |RAISE | Mute |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */
    [_LOWER] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                          _______, _______,   KC_UP, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                          _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,
      _______, _______, _______, _______, _______, _______,   KC_LT,        KC_GT,   _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______,        _______, _______, _______, _______

    ),
    /* RAISE
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      | Vol+ |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      | Prev | Vol- | Next |      |      |-------.    ,-------|      |      |      |      |      |      |
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   | Play |LOWER | LGUI | / Enter /       \Space \  | RGUI |RAISE | Mute |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */
    [_RAISE] = LAYOUT(
       KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                            KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F12,
      _______, _______, KC_VOLU, _______, _______, _______,                          _______, _______,   KC_UP, _______, _______, _______,
      _______, KC_MPRV, KC_VOLD, KC_MNXT, _______, _______,                          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,   KC_LT,        KC_GT,   _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______,        _______, _______, _______, _______

    ),
    /* ADJUST
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    |      |      |      |      | Oper | Out  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   | Play |LOWER | LGUI | / Enter /       \Space \  | RGUI |RAISE | Mute |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, KC_OPER,  KC_OUT,
      _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______,        _______, _______, _______, _______
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
const char *read_timelog(void);

void toggle_pomodoro(void);
const char* read_pomodoro_running(void);
void update_pomodoro_display(void);

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master())
        return OLED_ROTATION_90;
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_ln(read_layer_state(), false);
        oled_write_ln(read_pomodoro_running(), false);
    } else {
        update_pomodoro_display();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && keycode == KC_OPER) {
        toggle_pomodoro();
    }
    return true;
}

#endif // OLED_ENABLE
