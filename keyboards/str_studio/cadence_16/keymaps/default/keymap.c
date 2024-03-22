/* Copyright 2023 str studio
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

enum custom_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _NUMBER,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * NUMBER
 * ,---------------------------.
 * |      |      |      | Mute |
 * |------+------+------+------|
 * |   7  |   8  |   9  |   -  |
 * |------+------+------+------|
 * |   4  |   5  |   6  |   +  |
 * |------+------+------+------|
 * |   1  |   2  |   3  |  En  |
 * |--------------------|  te  |
 * | LOWR |   0  |  Del |  r   |
 * `---------------------------'
 */

[_NUMBER] = LAYOUT(
                                        KC_MUTE,
   KC_KP_7,     KC_KP_8,    KC_KP_9,    KC_KP_MINUS,
   KC_KP_4,     KC_KP_5,    KC_KP_6,    KC_KP_PLUS,
   KC_KP_1,     KC_KP_2,    KC_KP_3,    KC_KP_ENTER,
   MO(_FN),     KC_KP_0,    KC_KP_DOT
),

/* FUNCTION
 * ,---------------------------.
 * |      |      |      | Mute |
 * |------+------+------+------|
 * | Nlck |  Up  | Bksp |   /  |
 * |------+------+------+------|
 * | Left | Down | Rght |   *  |
 * |------+------+------+------|
 * |      | Home | PgUp |  En  |
 * |--------------------|  te  |
 * |  Fn  | End  | PgDn |  r   |
 * `---------------------------'
 */
 
[_FN] = LAYOUT(
                                            KC_MUTE,
   KC_NUM_LOCK, KC_UP,      KC_BACKSPACE,   KC_KP_SLASH,
   KC_LEFT,     KC_DOWN,    KC_RGHT,        KC_KP_ASTERISK,
   QK_BOOT,     KC_HOME,    KC_PAGE_UP,     KC_KP_ENTER,
   MO(_FN),     KC_END,     KC_PAGE_DOWN
)

};

// ================== Encoder ==================
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_NUMBER] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_FN]     =   { ENCODER_CCW_CW(KC_PGDN, KC_PGUP)  }
    //                  Encoder 1              
};  
#endif


// ================== OLED ==================

#ifdef OLED_ENABLE

static void print_status_narrow(void) {
    // Print current layer
    oled_write_P(PSTR("LAYER: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0: // _NUMBER
            oled_write_P(PSTR("Num\n"), false);
            break;
        case 1: // _FN
            oled_write_P(PSTR("Fn\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("NUMLCK"), !led_usb_state.num_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}

bool oled_task_user(void) {
    print_status_narrow();
    return false;
}

#endif