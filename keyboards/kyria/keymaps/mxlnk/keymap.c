/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

enum layers {
    QWERTY = 0,
    LOWER,
    RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | ESC    |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | LSFT   |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LCTL   |   Z  |   X  |   C  |   V  |   B  | Enter|  (   |  |  )   | Del  |   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * |        |      |      |      |      |      | NAV  |      |  |      | NAV  |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | GUI  | Alt  |  NUM | Space|  {[  |  |  ]}  | Bspc |  NUM | Tab  | ENTER|
 *                        |      |      |  SYM | Shift| Shift|  | Shift| Shift|  SYM |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [QWERTY] = LAYOUT(
      KC_ESC,  KC_Q,   KC_W,   KC_E,    KC_R,    KC_T,                                                                                       KC_Y,      KC_U,      KC_I,   KC_O,    KC_P,    KC_BSLASH,
      KC_LSFT, KC_A,   KC_S,   KC_D,    KC_F,    KC_G,                                                                                       KC_H,      KC_J,      KC_K,   KC_L,    KC_SCLN, KC_QUOT,
      KC_LCTL, KC_Z,   KC_X,   KC_C,    KC_V,    KC_B,      LT(RAISE, KC_ENT), KC_LPRN,             KC_RPRN,             LT(RAISE, KC_DEL),  KC_N,      KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                               KC_LGUI, KC_LALT, OSL(LOWER), LSFT_T(KC_SPC),    LSFT_T(KC_LBRACKET), LSFT_T(KC_RBRACKET), LSFT_T(KC_BSPC),    OSL(LOWER), KC_TAB, KC_ENT
    ),
/*
 * Numpad, Symbols (Lower)
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   `  |  !   |  @   |  &   |  `   |                              |      | 7    | 8    | 9    |  =   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |  #   |  $   | ~    |  *   |                              |      | 4    | 5    | 6    |  *   |  `     |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |  %   |  ^   | €    |      |      |      |  |      |      |      | 1    | 2    | 3    |  +   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |VOL   |      |      |      |      |  |      |      |      |   0  |SLEEP |
 *                        |      |      |      |      |      |  |      |      |      |      |BRIGHT|
 *                        `----------------------------------'  `----------------------------------'
 */
    [LOWER] = LAYOUT(
      _______, KC_GRV , KC_EXLM, KC_AT  , KC_AMPR   , KC_GRV,                                     _______, KC_7,    KC_8,    KC_9, KC_EQL , _______,
      _______, _______, KC_HASH, KC_DLR , KC_TILD   , KC_ASTR,                                     _______, KC_4,    KC_5,    KC_6, KC_ASTR, KC_GRV,
      _______, _______, KC_PERC, KC_CIRC, ALGR(KC_5), _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3, KC_PLUS, _______,
                                 KC_AUDIO_MUTE, _______, _______, _______, _______, _______, _______, _______, KC_0, KC_SYSTEM_SLEEP
    ),
/*
 * Nav, Fun (Raise)
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   F1   | F2   | F3   | F4   |  F5  |  F6  |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    F7  |  F8  |  F9  |  F10 | F11  |  F12 |                              | Left | Down | Up   | Right|      | CapsLk |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |RGBTOG|      |      |      |      |  |      |      |      |      |RGBTOG|
 *                        `----------------------------------'  `----------------------------------'
 */
    [RAISE] = LAYOUT(
      KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                                     _______, KC_PGDN, KC_PGUP,   KC_END,  _______, _______,
      KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,                                     KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 RGB_TOG , _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG
    )
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

// static void render_kyria_logo(void) {
//     static const char PROGMEM kyria_logo[] = {
//         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//         0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//         0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//         0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
//         0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
//         0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//         0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
//     };
//     oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
// }

// static void render_qmk_logo(void) {
//   static const char PROGMEM qmk_logo[] = {
//     0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
//     0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
//     0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

//   oled_write_P(qmk_logo, false);
// }

static void render_status(void) {
    // QMK Logo and version information
    // render_qmk_logo();
    // oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case QWERTY:
            oled_write_P(PSTR("QWERTY\n"), false);
            break;
        case LOWER:
            oled_write_P(PSTR("SYM + NUM\n"), false);
            break;
        case RAISE:
            oled_write_P(PSTR("FUN + NAV\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    // uint8_t led_usb_state = host_keyboard_leds();
    // oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    // oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    // oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    // if (is_keyboard_master()) {
    render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    // } else {
    //     render_kyria_logo();
    // }
}
#endif

int slave_hue_buffer = 0;
void h_change_slave(int change) {
    slave_hue_buffer = (slave_hue_buffer + change) % 256;
    rgblight_sethsv_range(slave_hue_buffer, 255, 255, 10, 20);
}

int master_hue_buffer = 0;
void h_change_master(int change) {
    master_hue_buffer = (master_hue_buffer + change) % 256;
    rgblight_enable_noeeprom();
    rgblight_sethsv_range(master_hue_buffer, 255, 255, 0, 15);
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_range(HSV_BLUE, 0, 10);
    rgblight_sethsv_range(HSV_RED, 10, 20);
}

bool handle_left(bool clockwise) {
    switch (biton32(layer_state))
    {
    case QWERTY:
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
        break;
    case LOWER:
        if (clockwise) {
            tap_code(KC_AUDIO_VOL_UP);
        } else {
            tap_code(KC_AUDIO_VOL_DOWN);
        }
        break;
    default:
        if (clockwise) {
            h_change_master(5);
        } else {
            h_change_master(-5);
        }
        break;
    }
    return true;
}

bool handle_right(bool clockwise) {
    switch (biton32(layer_state))
    {
    case QWERTY:
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
        break;
    case LOWER:
        if (clockwise) {
            tap_code(KC_BRIGHTNESS_UP);
        } else {
            tap_code(KC_BRIGHTNESS_DOWN);
        }
        break;
    default:
        if (clockwise) {
            rgblight_increase_hue();
        } else {
            rgblight_decrease_hue();
        }
        break;
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        handle_left(clockwise);
    }
    else if (index == 1) {
        handle_right(clockwise);
    }
    return true;
}
