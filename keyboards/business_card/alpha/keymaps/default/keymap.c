/* Copyright 2019 kakunpc
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
#include "lufa.h"
#include "ssd1306.h"
#include "rgblight_list.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    HOME = SAFE_RANGE,
    NAME,
    ADDRESS,
    SKILL,
    SOCIAL,
    ABOUT
};

const uint16_t PROGMEM
keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] =
LAYOUT(/* Base */
        SKILL, SOCIAL, ABOUT, \
        HOME, NAME, ADDRESS
),
};

int type = HOME;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NAME:
            if (record->event.pressed) {
                type = NAME;
                rgblight_sethsv_blue();
                SEND_STRING("2");
            }
            break;
        case ADDRESS:
            if (record->event.pressed) {
                type = ADDRESS;
                rgblight_sethsv_red();
                SEND_STRING("3");
            }
            break;
        case SKILL:
            if (record->event.pressed) {
                type = SKILL;
                rgblight_sethsv_yellow();
                SEND_STRING("4");
            }
            break;
        case SOCIAL:
            if (record->event.pressed) {
                type = SOCIAL;
                rgblight_sethsv_cyan();
                SEND_STRING("5");
            }
            break;
        case ABOUT:
            if (record->event.pressed) {
                type = ABOUT;
                rgblight_sethsv_pink();
                SEND_STRING("6");
            }
            break;

        case HOME:
        default:
            if (record->event.pressed) {
                type = HOME;
                rgblight_sethsv_white();
                SEND_STRING("1");
            }
            break;
    }
    return true;
}

void matrix_init_user(void) { iota_gfx_init(false); }

void matrix_scan_user(void) { iota_gfx_task(); }

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;
    matrix_clear(&matrix);

    switch (type) {
        case NAME:
            matrix_write_P(&matrix, PSTR("NAME\nkakunpc"));
            break;
        case ADDRESS:
            matrix_write_P(&matrix, PSTR("ADDRESS\nDUMMY!!!"));
            break;
        case SKILL:
            matrix_write_P(&matrix, PSTR("SKILL\nProgrammer.\nUnity and C#."));
            break;
        case SOCIAL:
            matrix_write_P(&matrix, PSTR("SOCIAL\nTwitter:kakunpc\nGithub:kakunpc"));
            break;
        case ABOUT:
            matrix_write_P(&matrix, PSTR("ABOUT\nBusiness Card Alpha\ndesigned by kakunpc."));
            break;
        default:
            matrix_write_P(&matrix, PSTR("Try pressing the key.\nYou can see\n    the information."));
            break;
    }

    matrix_update(&display, &matrix);
}

void led_set_user(uint8_t usb_led) {}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_white();
}
