#include QMK_KEYBOARD_H

// readme
// This keyboard layout is based on the [Workman Dead layout](https://github.com/ojbucao/Workman/tree/master/mac#workman-dead-for-programmers), which uses the comma as a dead key to trigger a second layer.
// Since I have more keys at my disposal on the ErgoDox, I moved the dead key to the bottom right. There are still a lot of
// blanks so still discovering what I like.
// If you aren't familiar with a dead key, the idea is that you tap the dead key which switches the layout. the next key you hit
// triggers the key you pressed AND switches the layout back to the original. For now I do this with a super kludgey macro and I
// look forward to learning about a more elegant way to do the same thing. Until then, this will have to do.

enum layer_names {
    BASE, // default layer
    SYMB, // symbols
    MDIA, // media keys
    DEAD  // dead version of the symbols layer
};

enum custom_keycodes {
    M_100 = SAFE_RANGE,
    M_101,
    M_102,
    M_103,
    M_104,
    M_105,
    M_106,
    M_107,
    M_108,
    M_109,
    M_110,
    M_111,
    M_112,
    M_113,
    M_114,
    M_115,
    M_116,
    M_117,
    M_118,
    M_119,
    M_120,
    M_121,
    M_122,
    M_123,
    M_124,
    M_125,
    M_126,
    M_127,
    M_128,
    M_129,
    M_130
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   D  |   R  |   W  |   B  |  L1  |           |  L1  |   J  |   F  |   U  |   P  |   ;  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Hyper  |   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |   I  |   '    |
 * |--------+------+------+------+------+------|      |           | Meh  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   M  |   C  |   V  |      |           |      |   K  |   L  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      | CTRL |  OPT |  CMD |                                       | Left | Down |  Up  | Right|  L3  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 |Bckspc| Space|------|       |------| Space  |Enter |
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GRV,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
        KC_TAB,         KC_Q,         KC_D,   KC_R,   KC_W,   KC_B,   TG(SYMB),
        ALL_T(KC_ESC),  KC_A,         KC_S,   KC_H,   KC_T,   KC_G,
        KC_LSFT,        KC_Z,         KC_X,   KC_M,   KC_C,   KC_V,   KC_NO,
        KC_NO,          KC_NO,        KC_LCTL,KC_LALT,KC_LGUI,
                                              KC_NO,  KC_NO,
                                                              KC_HOME,
                                               KC_BSPC,KC_SPC,KC_END,
        // right hand
             KC_RGHT,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_MINS,
             TG(SYMB),    KC_J,   KC_F,   KC_U,   KC_P,   KC_SCLN,          KC_BSLS,
                          KC_Y,   KC_N,   KC_E,   KC_O,   KC_I,             KC_QUOT,
             MEH_T(KC_NO),KC_K,   KC_L,   KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
                                  KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,          TG(DEAD),
             KC_NO,        KC_NO,
             KC_PGUP,
             KC_PGDN,KC_SPC,KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   %  |   &  |   ?  |   +  |   @  |      |           |      |   $  |   _  |   [  |   ]  |   !  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   /  |   (  |   =  |   0  |   {  |------|           |------|   }  |   1  |   *  |   )  |   -  |   "    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   6  |   7  |   8  |   9  |   |  |      |           |      |   \  |   2  |   3  |   4  |   5  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,   KC_F1,    KC_F2,    KC_F3,          KC_F4,        KC_F5,          KC_TRNS,
       KC_TRNS,   KC_PERC,  KC_AMPR,  LSFT(KC_SLSH),  LSFT(KC_EQL), KC_AT,          KC_TRNS,
       KC_TRNS,   KC_SLSH,  KC_LPRN,  KC_EQL,         KC_0,     LSFT(KC_LBRC),
       KC_TRNS,   KC_6,     KC_7,     KC_8,           KC_9,     KC_PIPE,        KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,        KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,          KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
       KC_TRNS, KC_DLR,         KC_UNDERSCORE,  KC_LBRC,  KC_RBRC,  KC_EXLM,  KC_F12,
                KC_RCBR,        KC_1,     KC_ASTR,  KC_RPRN,  KC_MINS,  KC_QUOT,
       KC_TRNS, KC_SLSH,        KC_2,     KC_3,     KC_4,     KC_5,     KC_TRNS,
                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
/* Keymap 4: Dead Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  %   |   &  |   ?  |   +  |   @  |      |           |      |   $  |   _  |   [  |   ]  |   !  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   /  |   (  |   =  |   0  |   {  |------|           |------|   }  |   1  |   *  |   )  |   -  |   "    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   6  |   7  |   8  |   9  |   |  |      |           |      |   \  |   2  |   3  |   4  |   5  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[DEAD] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,   KC_F1,    KC_F2,    KC_F3,      KC_F4,    KC_F5,          KC_TRNS,
       KC_TRNS,   M_100,    M_101,    M_102,      M_103,    M_104,          KC_TRNS,
       KC_TRNS,   M_109,   M_110,   M_111,        M_112,    M_113,
       KC_TRNS,   M_120,      M_121,      M_122,            M_123,      M_124,         KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,        KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
       KC_TRNS, M_105,    M_106,    M_107,    M_108,    M_130,    KC_F12,
                M_114,    M_115,    M_116,    M_117,    M_118,    M_119,
       KC_TRNS, M_125,    M_126,    M_127,    M_128,    M_129,    KC_TRNS,
                          KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

void tap_dead_code(uint16_t keycode) {
    layer_clear();
    tap_code16(keycode);
    layer_on(DEAD);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_100:
            if (record->event.pressed) {
                tap_dead_code(S(KC_5));
            }
            return false;
        case M_101:
            if (record->event.pressed) {
                tap_dead_code(S(KC_7));
            }
            return false;
        case M_102:
            if (record->event.pressed) {
                tap_dead_code(S(KC_SLSH));
            }
            return false;
        case M_103:
            if (record->event.pressed) {
                tap_dead_code(S(KC_EQL));
            }
            return false;
        case M_104:
            if (record->event.pressed) {
                tap_dead_code(S(KC_2));
            }
            return false;
        case M_105:
            if (record->event.pressed) {
                tap_dead_code(S(KC_4));
            }
            return false;
        case M_106:
            if (record->event.pressed) {
                tap_dead_code(S(KC_MINS));
            }
            return false;
        case M_107:
            if (record->event.pressed) {
                tap_dead_code(KC_LBRC);
            }
            return false;
        case M_108:
            if (record->event.pressed) {
                tap_dead_code(KC_RBRC);
            }
            return false;
        case M_109:
            if (record->event.pressed) {
                tap_dead_code(KC_SLSH);
            }
            return false;
        case M_110:
            if (record->event.pressed) {
                tap_dead_code(S(KC_9));
            }
            return false;
        case M_111:
            if (record->event.pressed) {
                tap_dead_code(KC_EQL);
            }
            return false;
        case M_112:
            if (record->event.pressed) {
                tap_dead_code(KC_0);
            }
            return false;
        case M_113:
            if (record->event.pressed) {
                tap_dead_code(S(KC_LBRC));
            }
            return false;
        case M_114:
            if (record->event.pressed) {
                tap_dead_code(S(KC_RBRC));
            }
            return false;
        case M_115:
            if (record->event.pressed) {
                tap_dead_code(KC_1);
            }
            return false;
        case M_116:
            if (record->event.pressed) {
                tap_dead_code(S(KC_8));
            }
            return false;
        case M_117:
            if (record->event.pressed) {
                tap_dead_code(S(KC_0));
            }
            return false;
        case M_118:
            if (record->event.pressed) {
                tap_dead_code(KC_MINS);
            }
            return false;
        case M_119:
            if (record->event.pressed) {
                tap_dead_code(S(KC_QUOT));
            }
            return false;
        case M_120:
            if (record->event.pressed) {
                tap_dead_code(KC_6);
            }
            return false;
        case M_121:
            if (record->event.pressed) {
                tap_dead_code(KC_7);
            }
            return false;
        case M_122:
            if (record->event.pressed) {
                tap_dead_code(KC_8);
            }
            return false;
        case M_123:
            if (record->event.pressed) {
                tap_dead_code(KC_9);
            }
            return false;
        case M_124:
            if (record->event.pressed) {
                tap_dead_code(S(KC_BSLS));
            }
            return false;
        case M_125:
            if (record->event.pressed) {
                tap_dead_code(KC_BSLS);
            }
            return false;
        case M_126:
            if (record->event.pressed) {
                tap_dead_code(KC_2);
            }
            return false;
        case M_127:
            if (record->event.pressed) {
                tap_dead_code(KC_3);
            }
            return false;
        case M_128:
            if (record->event.pressed) {
                tap_dead_code(KC_4);
            }
            return false;
        case M_129:
            if (record->event.pressed) {
                tap_dead_code(KC_5);
            }
            return false;
        case M_130:
            if (record->event.pressed) {
                tap_dead_code(S(KC_1));
            }
            return false;
    }
    return true;
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    switch (get_highest_layer(layer_state)) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }
}
