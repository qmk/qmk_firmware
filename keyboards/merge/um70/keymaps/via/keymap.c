/* Copyright 2021 duoshock
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

enum layer_names {
    _BASE,
    _ONE,
    _TWO,
    _THREE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *          .---------------------------.          .-------------------------------.        .---.
 *          |Esc|  1|  2|  3|  4|  5|  6|          |  7|  8|  9|  0|  -|  =|`  |Bsp|        |EC |
 *          |-------------------------.          .---------------------------------|        |---|
 *          |Tab  |  Q|  W|  E|  R|  T|          |  Y|  U|  I|  O|  P|  [|  ]|  \  |        |Hom|
 *   .---.  |-------------------------.          '---------------------------------|        |---|
 *   |M0 |  |CapsL |  A|  S|  D|  F|  G|          |  H|  J|  K|  L|  ;|  :|   Retn |        |End|
 *   |---|  |----------------------------.        '--------------------------------|  .---. '---'
 *   |M1 |  |Shft    |  Z|  X|  C|  V|  B|          |  N|  M|  ,|  ,|  /|  Shift|     |Up |
 *   |---|  |----------------------------|          |---------------------------' .-----------.
 *   |M2 |  |Ctl |Gui |Alt |Fn0 |Space   |          |    Space|   Alt|   Ctl|     |Lef|Dow|Rig|
 *   '---'  '----------------------------'          '-----------------------'     '-----------'
 */

[_BASE] = LAYOUT_rspace_split_bksp(
            KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,                KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRV, KC_BSPC,    KC_MUTE,
            KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T,                     KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,   KC_BSLS,   KC_HOME,
    KC_1,   KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G,                     KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,    KC_ENT,         KC_END,
    KC_2,   KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                     KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,                   KC_UP,
    KC_3,   KC_LCTL, KC_LGUI, KC_LALT, MO(1), KC_SPC,                   KC_SPC, KC_RALT, KC_RCTL,                               KC_LEFT, KC_DOWN, KC_RGHT
),

[_ONE] = LAYOUT_rspace_split_bksp(
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
                KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,         KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, KC_TRNS, KC_TRNS,                               KC_TRNS, KC_TRNS, KC_TRNS
),
[_TWO] = LAYOUT_rspace_split_bksp(
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
                KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,         KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, KC_TRNS, KC_TRNS,                               KC_TRNS, KC_TRNS, KC_TRNS
),
[_THREE] = LAYOUT_rspace_split_bksp(
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
                KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,         KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, KC_TRNS, KC_TRNS,                               KC_TRNS, KC_TRNS, KC_TRNS
),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Master Left */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* Master Right */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}


#ifdef OLED_ENABLE
void suspend_power_down_user(void) {
    oled_off();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_90;
    }

    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,192,224,224,224,224,224,224,224,224,224,224,224,224,224,224,192,192,128,128,192,192,224,224,224,224,224,224,224,224,192,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 15,  3,  1,  0,  1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,254,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,254,254,  0,  0,  0,  0,  0,  0,254,254,254,  0,  0,  0,254,254,254,252,248,224,192,128,224,248,252,254,254,254,  0,  0,128,128,128,128,128,128,  0, 14, 14, 14, 14,142,238,254,254,126, 30,  4,224,248,252, 62, 30, 14, 14, 14, 30, 62,252,248,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,240,192,128,  0,128,255,255,255,255,255,255,255,255,255,255,255,255,255,255,127, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 63, 63,124,112,112,112,112,124, 63, 63, 15,  0,  0,  0,127,127,127,  0,  1,  7, 15, 15,  7,  1,  0,127,127,127,  0,  0,  3,  3,  3,  3,  3,  3,  1,  0,112,124,126, 63, 15,  3,  1,  0,  0,  0, 15, 31, 63,124,120,112,112,112,120,124, 63, 31, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  3,  3,  1,  1,  3,  3,  7,  7,  7,  7,  7,  7,  7,  7,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}


// 32 * 18 Merge logos
static const char PROGMEM merge_logo[] = {
    0xf8, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x0e,
    0x06, 0x04, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf8, 0xf0, 0xc0,
    0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xc0,
    0x80, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x0f,
    0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01,
    0x01, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00
};

uint8_t current_wpm = 0;

static void print_status_narrow(void) {
    oled_set_cursor(0,1);
    oled_write_raw_P(merge_logo, sizeof(merge_logo));
    oled_set_cursor(0,5);
    oled_write_P(PSTR("-----"), false);
    oled_set_cursor(0,6);
    oled_write_P(PSTR("LYR "), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("0"), false);
            break;
        case _ONE:
            oled_write_P(PSTR("1"), false);
            break;
        case _TWO:
            oled_write_P(PSTR("2"), false);
            break;
        case _THREE:
            oled_write_P(PSTR("3"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR(" "), false);
    oled_write_P(PSTR("CAP "), false);
    oled_write_P(PSTR("."), led_usb_state.caps_lock);
    oled_write_P(PSTR("NUM "), false);
    oled_write_P(PSTR("."), led_usb_state.num_lock);
    oled_write_P(PSTR("SCR "), false);
    oled_write_P(PSTR("."), led_usb_state.scroll_lock);
    //oled_write_ln_P(PSTR(" "), false);
    oled_write_P(PSTR("-----"), false);

    // WPM counter Start
    char wpm_str[5];
    oled_set_cursor(0,13);
    wpm_str[4] = '\0';
    uint8_t n = current_wpm;
    wpm_str[3] = '0' + n % 10;
    wpm_str[2] = '0' + (n /= 10) % 10;
    wpm_str[1] = '0' + n / 10;
    wpm_str[0] = ' ';
    oled_write(wpm_str, false);
    oled_set_cursor(0,14);
    oled_write(" WPM ", false);
    // WPM counter End
}

void oled_task_user(void) {
    current_wpm = get_current_wpm();
    if (is_keyboard_master()) {
        print_status_narrow();
        //render_logo();
    } else {
        render_logo();
        //print_status_narrow();
    }
}

#endif
