/*
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
    _SPECIAL1,
    _SPECIAL2,
    _STANDBY
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬
     * │ 7 │ 8 │ 9 │
     * ├───┼───┼───┼
     * │ 4 │ 5 │ 6 │
     * ├───┼───┼───┼
     * │ 1 │ 2 │ 3 │
     * ├───┼───┼───┼
     * │ 0 │ . │Ent│
     * └───┴───┴───┘
     */
    [_BASE] = LAYOUT(
        KC_P7, KC_P8, KC_P9,
        KC_P4, KC_P5, KC_P6,
        KC_P1, KC_P2, KC_P3,
        KC_P0, TO(_SPECIAL1), KC_PENT
    ),
    [_SPECIAL1] = LAYOUT(
        KC_P7, KC_P8, KC_P9,
        KC_P4, KC_P5, KC_P6,
        KC_P1, KC_P2, KC_P3,
        KC_P0, TO(_SPECIAL2), KC_PENT
    ),
    [_SPECIAL2] = LAYOUT(
        KC_P7, KC_P8, KC_P9,
        KC_P4, KC_P5, KC_P6,
        KC_P1, KC_P2, KC_P3,
        KC_P0, TO(_STANDBY), KC_PENT
    ),
    [_STANDBY] = LAYOUT(
        KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO,
        KC_NO, TO(_BASE), KC_NO
    ),

};

#ifdef OLED_ENABLE

        static void render_logo(void) {
            static const char PROGMEM aks_mls_logo[] = {
                0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
                0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
                0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
            };

            // oled_write_P(aks_mls_logo, false);
            oled_write_raw_P(aks_mls_logo, sizeof(aks_mls_logo));
        }

        bool oled_init(oled_rotation_t(OLED_ROTATION_0));

        bool oled_task_user(void) {
            render_logo();

            oled_set_cursor(0, 3);
            // oled_write(PSTR("Layer: "), false);

            switch (get_highest_layer(layer_state)) {
                case _BASE:
                    // oled_write_ln(PSTR("Base"), false);
                    oled_write_ln(PSTR("Default Actions"), false);
                    oled_advance_page(true);
                    oled_advance_page(true);
                    break;
                case _SPECIAL1:
                    // oled_write_ln(PSTR("Special1"), false);
                    oled_write_ln(PSTR("Special Actions 1"), false);
                    oled_advance_page(true);
                    break;
                case _SPECIAL2:
                    // oled_write_ln(PSTR("Special2"), false);
                    oled_write_ln(PSTR("Special Actions 2"), false);
                    oled_advance_page(true);
                    oled_advance_page(true);
                    break;
                case _STANDBY:
                    oled_write_ln(PSTR("Standby Mode"), false);
                    oled_write_ln(PSTR("Keys do nothing"), false);
                    oled_write_ln(PSTR("Layer key re-engages"),     false);
                break;
                default:
                    oled_write_ln_P(PSTR("Undefined"), false);
                    oled_advance_page(true);
                    oled_advance_page(true);

        }

            return false;
        }
#endif
