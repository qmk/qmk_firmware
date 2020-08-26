/* Copyright 2020 zFrontier
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
#include <print.h>


enum {
    TD_ENTER = 0,
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT( TD(TD_ENTER) ),
};



void keyboard_post_init_user(void) {
    print("zFrontier S01.6 boot...\n");
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
    rgblight_sethsv_noeeprom(0,0,128);
}


void zf_switch_rgb_mode(void) {
    switch (rgblight_get_mode() ) {
        case RGBLIGHT_MODE_BREATHING:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD);
            break;
        case RGBLIGHT_MODE_RAINBOW_MOOD:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
            break;
        case RGBLIGHT_MODE_RAINBOW_SWIRL:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE);
            break;
        case RGBLIGHT_MODE_SNAKE:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT);
            break;
        case RGBLIGHT_MODE_KNIGHT:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_CHRISTMAS);
            break;
        case RGBLIGHT_MODE_CHRISTMAS:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT);
            break;
        case RGBLIGHT_MODE_STATIC_GRADIENT:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
            break;
        case RGBLIGHT_MODE_RGB_TEST:
        default:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
            break;
    }
}

void zf_send_random_string(void) {
    uint8_t tmpu8 = (timer_read() & 0x7);
    switch (tmpu8) {
        case 0:
        case 1:
            SEND_STRING("Sazabi, launching!");
            break;
        case 2:
        case 3:
            SEND_STRING("I, Char Aznable, will purge them, Amuro!");
            break;
        case 4:
        case 5:
            SEND_STRING("Their souls are weighted down by gravity!");
            break;
        case 6:
            SEND_STRING("Go, Axis! With my unpleasant memories!");
            break;
        case 7:
            SEND_STRING("Hello from zFrontier!");
            break;
    }

    tap_code(KC_ENT);
}

void dance_finished(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            register_code(KC_ENTER);
            break;
        case 2:
            zf_switch_rgb_mode();
            break;
        default:
            zf_send_random_string();
            break;
    }
}

void dance_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_ENTER);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ENTER] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_finished, dance_reset)
};
