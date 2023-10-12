/* Copyright 2023 Paulo Pereira
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#include "keymap_portuguese.h"
#include "features/custom_shift_keys.h"

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

/* tap dance shifts */
typedef struct {
    bool is_press_action;
    int  state;
} tap;

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

enum { LEFT_SHIFT = 0, RIGHT_SHIFT = 1 };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* QWERTY
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  '?  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  +*  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ç  | BACK |
    * |------+------+------+------+------+------|  <>   |    |  ´`   |------+------+------+------+------+------|
    * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |  ,;  |   .: |  _-  |Shift|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE | RGUI | RAlt |
    *                   |      |      |      |/       /         \      \ |      |      |      |
    *                   `-------------------''-------'           '------''--------------------'
    */
    [_QWERTY] = LAYOUT(
        KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
        TD(LEFT_SHIFT),  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_BSPC,
        KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_GRV,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  TD(RIGHT_SHIFT),
                            KC_LALT, KC_LGUI, TL_LOWR, KC_SPC,   KC_ENT,   TL_UPPR,  KC_RGUI, KC_RALT
    ),

    /* LOWER
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |      |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  |  F11 |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |  F1  |      |      |      |      |      |                    | PgUp | HOME |  Up  | END  |  ºª  | F12  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      |      |      |      |      |      |-------.    ,-------| PgDn | Left | Down |Right |  ~^  | DEL  |
    * |------+------+------+------+------+------|  <>   |    |  ´`   |------+------+------+------+------+------|
    * |      |      |      |  <<  |  >|| |  >>  |-------|    |-------|      | Vol+ | Vol- | Mute |  \|  |      |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE | RGUI | RAlt |
    *                   |      |      |      |/       /         \      \ |      |      |      |
    *                   `-------------------''-------'           '------''--------------------'
    */
    [_LOWER] = LAYOUT(
        _______,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                 KC_F7,     KC_F8, KC_F9,  KC_F10,  KC_F11, _______,  
          KC_F1, _______, _______, _______, _______, _______,                 KC_PGUP, KC_HOME, KC_UP,  KC_END, KC_LBRC,  KC_F12,
        _______, _______, _______, _______, _______, _______,                 KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_QUOT, KC_DEL,
        _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT,   _______, _______, _______, KC_VOLU,  KC_VOLD, KC_MUTE, KC_BSLS, _______,
                                    _______, _______, _______,  _______, _______,  _______, _______, _______
    ),

    /* RAISE
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      |   1  |   2  |  3   |  4   |  5   |                    | PgUp | HOME |  Up  | END  |  ºª  |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      |   6  |   7  |  8   |  9   |  0   |-------.    ,-------| PgDn | Left | Down |Right |  ~^  |      |
    * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
    * |      |      |      |  <<  |  >|| |  >>  |-------|    |-------|      | Vol+ | Vol- | Mute |  \|  |      |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE | RGUI | RAlt |
    *                   |      |      |      |/       /         \      \ |      |      |      |
    *                   `-------------------''-------'           '------''--------------------'
    */
    [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,
        _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                   KC_PGUP, KC_HOME, KC_UP,  KC_END, KC_LBRC, _______,
        _______,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_QUOT, _______,
        _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, KC_VOLU,  KC_VOLD, KC_MUTE, KC_BSLS, _______,
                                    _______, _______, _______, _______, _______,  _______, _______, _______
    ),   

    /* ADJUST
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |RGB ON| HUE+ | SAT+ | VAL+ |      | BRG+ |-------.    ,-------|      |      |      |      |      |      |
    * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
    * | MODE | HUE- | SAT- | VAL- |      | BRG- |-------|    |-------|      |      |      |      |      |      |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE | RGUI | RAlt | 
    *                   |      |      |      |/       /         \      \ |      |      |      |
    *                   `----------------------------'           '------''--------------------'
    */

    [_ADJUST] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, KC_BRIU,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, KC_BRID, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                    _______, _______, _______, _______, _______,  _______, _______, _______
    )
};

// SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void        set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_ln(read_layer_state(), false);
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
    } else {
        oled_write(read_logo(), false);
    }
    return false;
}
#endif // OLED_ENABLE


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
    #ifdef OLED_ENABLE
        set_keylog(keycode, record);
    #endif
    }

    return true;
}

/* Tap dance shifts */
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return TD_SINGLE_TAP;
        } else {
            return TD_SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        return TD_DOUBLE_TAP;
    }

    return TD_UNKNOWN;
}

static tap lshifttap_state = {.is_press_action = true, .state = TD_NONE};

static tap rshifttap_state = {.is_press_action = true, .state = TD_NONE};

void lshift_finished(tap_dance_state_t *state, void *user_data) {
    lshifttap_state.state = cur_dance(state);

    switch (lshifttap_state.state) {
        case TD_SINGLE_TAP:
            register_code16(LALT(KC_LEFT));
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LALT(KC_LEFT));
            register_code16(LALT(KC_LEFT));
            break;
        default:
            break;
    }
}

void lshift_reset(tap_dance_state_t *state, void *user_data) {
    switch (lshifttap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code16(LALT(KC_LEFT));
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(LALT(KC_LEFT));
            break;
    }
    lshifttap_state.state = TD_NONE;
}

void rshift_finished(tap_dance_state_t *state, void *user_data) {
    rshifttap_state.state = cur_dance(state);

    switch (rshifttap_state.state) {
        case TD_SINGLE_TAP:
            register_code16(LALT(KC_RGHT));
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_RSFT);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(LALT(KC_RGHT));
            register_code16(LALT(KC_RGHT));
            break;
        default:
            break;
    }
}

void rshift_reset(tap_dance_state_t *state, void *user_data) {
    switch (rshifttap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code16(LALT(KC_RGHT));
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_RSFT);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(LALT(KC_RGHT));
            break;
    }
    rshifttap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [LEFT_SHIFT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lshift_finished, lshift_reset),
    [RIGHT_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rshift_finished, rshift_reset),
};
