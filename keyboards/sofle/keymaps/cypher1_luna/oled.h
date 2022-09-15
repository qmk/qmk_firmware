 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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
//Sets up what the OLED screens display.

#ifdef OLED_ENABLE

uint16_t data_in = 0;

static void put_layer_name(uint16_t layer) {
    switch (layer) {
        case 0:
            oled_write_P(PSTR("Qwert"), false);
            break;
        case 1:
            oled_write_P(PSTR("Yuiop"), false);
            break;
        case 2:
            oled_write_P(PSTR("Funct"), false);
            break;
        case 3:
            oled_write_P(PSTR("Cntrl"), false);
            break;
        default:
            oled_write_P(PSTR("?????"), false);
            break;
    }
}

static void print_status_narrow(void) {
    // Print current mode
    oled_set_cursor(0, 0);
    put_layer_name(get_highest_layer(layer_state));

    // Print current default layer
    if (get_highest_layer(default_layer_state) != get_highest_layer(layer_state)) {
      oled_set_cursor(0, 1);
      put_layer_name(get_highest_layer(default_layer_state));
    }
    oled_set_cursor(0, 2);
    char    data_str[2];
    oled_set_cursor(0, 14);
    data_str[1] = '\0';
    data_str[0] = '0' + data_in;
    oled_write(data_str, false);

    oled_set_cursor(0, 3);
    led_t led_usb_state = host_keyboard_led_state();
    if (led_usb_state.caps_lock) {
        oled_write_ln_P(PSTR("C\nY\nP\nH\nE\nR\n1"), true);
    } else {
        oled_write_ln_P(PSTR("c\ny\np\nh\ne\nr\n1"), false);
    }
    if (is_keyboard_master()) {
        render_pet(0, 13);
    } else {
        /* wpm counter */
        uint8_t n = get_current_wpm();
        char    wpm_str[4];
        oled_set_cursor(0, 14);
        wpm_str[3] = '\0';
        wpm_str[2] = '0' + n % 10;
        wpm_str[1] = '0' + (n /= 10) % 10;
        wpm_str[0] = '0' + n / 10;
        oled_write(wpm_str, false);

        oled_set_cursor(0, 15);
        oled_write(" wpm", false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    /* KEYBOARD PET VARIABLES START */
    current_wpm   = get_current_wpm();
    led_usb_state = host_keyboard_led_state();
    /* KEYBOARD PET VARIABLES END */

    print_status_narrow();
    return false;
}

#endif
