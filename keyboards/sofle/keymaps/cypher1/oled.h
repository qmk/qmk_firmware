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

#define DATA_LEN 6
char data_str[DATA_LEN] = {0};
uint16_t data_in = 0;

static void put_layer_name(uint16_t layer) {
    switch (layer) {
        case QWERT:
            oled_write_P(PSTR("Qwert"), false);
            break;
        case GAMES:
            oled_write_P(PSTR("Games"), false);
            break;
        case FUNCS:
            oled_write_P(PSTR("Funcs"), false);
            break;
        case CNTRL:
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
    data_str[DATA_LEN-1] = '\0';
    oled_write(data_str, false);

    led_t led_usb_state = host_keyboard_led_state();
    bool invert = led_usb_state.caps_lock;
    oled_set_cursor(0, 4);
    os_variant_t host_os = detected_host_os();
    switch (host_os) {
        case OS_WINDOWS:
            oled_write_ln_P(PSTR("C W\nY I\nP N\nH D\nE O\nR W\n1 S"), invert);
            break;
        case OS_LINUX:
            oled_write_ln_P(PSTR("C L\nY I\nP N\nH U\nE X\nR  \n1  "), invert);
            break;
        case OS_MACOS:
            oled_write_ln_P(PSTR("C M\nY A\nP C\nH  \nE O\nR S\n1  "), invert);
            break;
        case OS_IOS:
            oled_write_ln_P(PSTR("C I\nY O\nP S\nH  \nE  \nR  \n1  "), invert);
            break;
        default:
            oled_write_ln_P(PSTR("C  \nY  \nP  \nH  \nE  \nR  \n1  "), invert);
            break;
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
    return OLED_ROTATION_270;
    // return rotation;
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
