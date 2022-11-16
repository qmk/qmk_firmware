// Copyright 2022 Takuya Urakawa @hsgw (dm9records.com, 5z6p.com)
// Copyright 2022 Richard Dawe
// SPDX-License-Identifier: GPL-2.0-or-later

// Convert this into a printable keymap on Linux using:
/*
grep -A11 '[=] LAYOUT(' keyboards/dm9records/lain/keymaps/richdawe/keymap.c > lain-keymap-richdawe.txt
enscript -v -r -f Courier9 --media=A4 lain-keymap-richdawe.txt -o lain-keymap-richdawe.ps
ps2pdf lain-keymap-richdawe.ps lain-keymap-richdawe.pdf
*/

#include QMK_KEYBOARD_H

enum layers { BASE, NUM, SYM, FUNC };
enum custom_keycodes { LED_EN = SAFE_RANGE };

#define LTS_SPC LT(SYM, KC_SPC)
#define LTN_SPC LT(NUM, KC_SPC)
#define LTF_TAB LT(FUNC, KC_TAB)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
/*
 * ,-----------------------------------------.     ,-----------------------------------.
 * |TbLFn|  Q  /  W  /  E  /  R  /  T  /  {  /     \  Y  \  U  \  I  \  O  \  P  |  \  |
 * |-----------------------------------------/     \-----------------------------------|
 * | Esc |  A  /  S  /  D  /  F  /  G  /  }  /     \  H  \  J  \  K  \  L  \  ;  |  '  |
 * |-----------------------------------------'     \-----------------------------------|
 * |LShft|  Z  /  X  /  C  /  V  /  B  /           \  B  \  N  \  M  \  ,  \  .  |ShEnt|
 * `-----------------------------------'           \-----------------------------------|
 *    |LCtrl|  /LGUI /LAlt /SpLSy/Space/           \SpLNu\SpLNu\Bspc \RAlt \  `  |  /  |
 *    `-----'  `-----------------------'           `-----------------------------------'
 */
        LTF_TAB, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_RBRC,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,               KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SFTENT,
        KC_LCTL,          KC_LGUI, KC_LALT, LTS_SPC, KC_SPC,             LTN_SPC, LTN_SPC, KC_BSPC, KC_RALT, KC_GRV,  KC_SLSH
    ),

    [NUM] = LAYOUT(
/*
 * ,-----------------------------------------.     ,-----------------------------------.
 * |     |     /  1  /  2  /  3  /  :  /  (  /     \  -  \  =  \ Up  \  0  \  .  |     |
 * |-----------------------------------------/     \-----------------------------------|
 * |     |     /  4  /  5  /  6  /  .  /  )  /     \     \Left \Right\     \     |     |
 * |-----------------------------------------'     \-----------------------------------|
 * |     |     /  7  /  8  /  9  /  0  /           \     \     \Down \     \     |     |
 * `-----------------------------------'           \-----------------------------------|
 *    |     |  /     /     /  -  /  -  /           \     \     \     \     \     |     |
 *    `-----'  `-----------------------'           `-----------------------------------'
 */
        _______, XXXXXXX, KC_1,    KC_2,    KC_3,    KC_COLON, KC_LPRN,   KC_MINS, KC_EQL,  KC_UP,    KC_0,    KC_DOT,  XXXXXXX,
        _______, XXXXXXX, KC_4,    KC_5,    KC_6,    KC_DOT,   KC_RPRN,   XXXXXXX, KC_LEFT, KC_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_0,                XXXXXXX, XXXXXXX, KC_DOWN,  XXXXXXX, XXXXXXX, _______,
        _______,          _______, _______, KC_MINS, KC_MINS,             _______, _______, XXXXXXX,  _______, XXXXXXX, XXXXXXX
    ),

    [SYM] = LAYOUT(
/*
 * ,-----------------------------------------.     ,-----------------------------------.
 * |     |     /  !  /  @  /  #  /     /  (  /     \  _  \  +  \PgUp \     \     |     |
 * |-----------------------------------------/     \-----------------------------------|
 * |     |     /  $  /  %  /  ^  /     /  )  /     \     \Home \ End \     \     |     |
 * |-----------------------------------------'     \-----------------------------------|
 * |     |     /  &  /  *  /  (  /  )  /           \     \     \PgDn \     \     |     |
 * `-----------------------------------'           \-----------------------------------|
 *    |     |  /     /     /     /     /           \  -  \  -  \     \     \     |     |
 *    `-----'  `-----------------------'           `-----------------------------------'
 */
        _______, XXXXXXX, S(KC_1), S(KC_2), S(KC_3), XXXXXXX, KC_LPRN,   S(KC_MINS), S(KC_EQL), KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, S(KC_4), S(KC_5), S(KC_6), XXXXXXX, KC_RPRN,   XXXXXXX,    KC_HOME,   KC_END,  XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, S(KC_7), S(KC_8), S(KC_9), S(KC_0),            XXXXXXX,    XXXXXXX,   KC_PGDN, XXXXXXX, XXXXXXX, _______,
        _______,          _______, _______, _______, _______,            KC_MINS,    KC_MINS,   XXXXXXX, _______, XXXXXXX, XXXXXXX
    ),

    [FUNC] = LAYOUT(
/*
 * ,-----------------------------------------.     ,-----------------------------------.
 * |     |     / F1  / F2  / F3  /     /MPrev/     \     \     \     \     \MPlay|     |
 * |-----------------------------------------/     \-----------------------------------|
 * |CapsL|LEDEn/ F4  / F5  / F6  /     /MNext/     \     \VolDn\VolUp\     \     |     |
 * |-----------------------------------------'     \-----------------------------------|
 * |     |     / F7  / F8  / F9  /     /           \     \     \VMute\     \     |     |
 * `-----------------------------------'           \-----------------------------------|
 *    |Bootl|  / F10 / F11 / F12 /     /           \     \     \ Del \     \     |     |
 *    `-----'  `-----------------------'           `-----------------------------------'
 */
        _______, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   XXXXXXX, KC_MPRV,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY, XXXXXXX,
        KC_CAPS, LED_EN,  KC_F4,   KC_F5,   KC_F6,   XXXXXXX, KC_MNXT,   XXXXXXX, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, KC_F7,   KC_F8,   KC_F9,   XXXXXXX,            XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, _______,
        QK_BOOT,          KC_F10,  KC_F11,  KC_F12,  XXXXXXX,            XXXXXXX, XXXXXXX, KC_DEL,  _______, XXXXXXX, XXXXXXX
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LED_EN:
            if (record->event.pressed) {
                lain_enable_leds_toggle();
            }
            return false;
        default:
            break;
    }
    return true;
}

// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case NUM:
            lain_set_led(1, 1);
            lain_set_led(2, 0);
            break;
        case SYM:
            lain_set_led(1, 0);
            lain_set_led(2, 1);
            break;
        case FUNC:
            lain_set_led(1, 1);
            lain_set_led(2, 1);
            break;
        default:
            lain_set_led(1, 0);
            lain_set_led(2, 0);
            break;
    }
    return state;
}

bool led_update_user(led_t led_state) {
    lain_set_led(0, led_state.caps_lock);
    return false;
}
