/* Copyright 2021 Katrina (@PepperKats)
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

#define _QWERTY 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* ┌───┐   ┌───────┐┌───┬───┬───┐┌───┬───┬───┐
     * │ESC│   │KC_BSPC││F1 │F2 │F3 ││F4 │F5 │F6 │
     * └───┘   └───────┘└───┴───┴───┘└───┴───┴───┘
     * ┌───┬───┬───┬───┐┌───┬───┬───┐
     * │NUM│ / │ * │ - ││PAS│SCR│PSC│
     * ├───┼───┼───┼───┤├───┼───┼───│
     * │ 7 │ 8 │ 9 │   ││INS│HOM│PGU│
     * ├───┼───┼───│ + │├───┼───┼───│
     * │ 4 │ 5 │ 6 │   ││END│DEL│PGD│
     * ├───┼───┼───┼───┤└───┼───┼───┘
     * │ 1 │ 2 │ 3 │ E │    │UP │    
     * ├───┼───┼───│ N │┌───┼───┼───┐┌───┬───┬───┐
     * │   0   │DEL│ T ││LFT│DWN│RHT││ O │ O │ O │
     * └───┴───┴───┴───┘└───┴───┴───┘└───┴───┴───┘
     */
    [_QWERTY] = LAYOUT(
        KC_ESC,           KC_BSPC,          RGB_RMOD, RGB_TOG, RGB_MOD,   QK_MAKE,   QK_REBOOT,   QK_BOOTLOADER,
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, KC_PAUS,  KC_SCRL, KC_PSCR, 
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_INS,   KC_HOME, KC_PGUP, 
        KC_P4,   KC_P5,   KC_P6,            KC_END,   KC_DEL,  KC_PGDN, 
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,           KC_UP,
        KC_P0,            KC_PDOT,          KC_LEFT,  KC_DOWN, KC_RGHT,  KC_HOME,    KC_END,        KC_B
    )
};

//Knobs
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] =   { ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};
#endif

/*NOTE FOR PERSON MODIFYING KEYMAP
The large knob press is mapped as KC_B, despite it not having one.
I'm not quite sure why, but the only reason it can't be clicked is because the potentiometer is different.
If you were to replace it with one that can be clicked, it would work. I shorted it and it does work.*/

//Display
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    render_logo();
    return false;
}