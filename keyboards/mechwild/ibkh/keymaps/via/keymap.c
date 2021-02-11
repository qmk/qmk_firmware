/* Copyright 2021 Kyle McCreery 
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

#define FN1_SPC     LT(1, KC_SPC)
#define FN2_BSPC    LT(2, KC_BSPC)
#define SFT_ENT     RSFT_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
    KC_Q,    KC_S,    KC_E,    KC_R,    KC_T,    FN2_BSPC,          FN1_SPC,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      
    KC_A,             KC_D,    KC_F,    KC_G,                                 KC_H,    KC_J,    KC_K,    KC_L,    SFT_ENT,
                                        KC_C,    KC_V,     KC_B,    KC_N,     KC_M
  ),                                                       

  [1] = LAYOUT(                                            
    _______, KC_W,    _______, _______, _______, KC_DEL,            _______,  KC_ESC,  _______, _______, _______, _______,      
    _______,          _______, _______, _______,                              _______, _______, _______, _______, _______,
                                        KC_Z,    KC_X,     _______, _______,  _______
  ),                                                       

  [2] = LAYOUT(                                            
    _______, _______, _______, _______, _______, _______,           KC_TAB,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      
    _______,          _______, _______, _______,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
                                        RGB_VAD, RGB_VAI,  RGB_TOG, RGB_RMOD, RGB_MOD
  ),                                                       

  [3] = LAYOUT(                                            
    _______, _______, _______, _______, _______, _______,           _______,  _______, _______, _______, _______, _______,      
    _______,          _______, _______, _______,                              _______, _______, _______, _______, _______,
                                        _______, _______,  _______, _______,  _______
  )
};


#ifdef OLED_DRIVER_ENABLE   // OLED Functionality
    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_180;
    }

    static void render_logo(void) {     // Render MechWild "MW" Logo
        static const char PROGMEM logo_1[] = {0x97, 0x98, 0x99, 0x9A,0x00};
        static const char PROGMEM logo_2[] = {0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0x00};
        static const char PROGMEM logo_3[] = {0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xB6, 0x00};
        static const char PROGMEM logo_4[] = {0xB6, 0xB6, 0xB6, 0x9B, 0x9C, 0x9D, 0x9E, 0x00};
        oled_set_cursor(0,0);
        oled_write_P(logo_1, false);
        oled_set_cursor(0,1);
        oled_write_P(logo_2, false);
        oled_set_cursor(0,2);
        oled_write_P(logo_3, false);
        oled_set_cursor(0,3);
        oled_write_P(logo_4, false);
    }

    void oled_task_user(void) {
        render_logo();
	}
#endif