/* Copyright 2021 NachoxMacho
*  Copyright 2022 peepeetee
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
* along with this program.  If not, see &lt;http://www.gnu.org/licenses/&gt;.
*/

#include QMK_KEYBOARD_H
#include <print.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┌───┬───┬───┬───┐
     * │ ` │Esc│Tab│MO1│Bsp│
     * ├───┼───┼───┼───┼───┤
     * │ , │Num│ / │ * │ - │
     * ├───┼───┼───┼───┼───┤
     * │Gui│ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┼───┤ + │
     * │Alt│ 4 │ 5 │ 6 │   │
     * ├───┼───┼───┼───┼───┤
     * │Shi│ 1 │ 2 │ 3 │   │
     * ├───┼───┴───┼───┤Ent│
     * │Ctr│ 0     │ . │   │
     * └───┴───────┴───┴───┘
     */
    [0] = LAYOUT_numpad_6x5(
        KC_ESC,     KC_PSCR,    KC_SLCK,    KC_PAUS,    MO(1), 
        KC_GRV,     KC_NLCK,    KC_PSLS,    KC_PAST,    KC_PMNS,
        RGB_TOG,    KC_P7,      KC_P8,      KC_P9,      KC_PPLS,
        KC_LSFT,    KC_P4,      KC_P5,      KC_P6,      
        KC_LALT,    KC_P1,      KC_P2,      KC_P3,      KC_PENT,
        KC_LCTL,    KC_P0,                  KC_PDOT   
    ),

    /*
     * ┌───┌───┐───┬───┬───┐
     * │Rst│ ` │Tab│MO1│Bsp│
     * ├───┼───┘───┼───┼───┤
     * │ , │Num│ / │ * │ - │
     * ├───┼───┼───┼───┼───┤
     * │Gui│Hom│ ↑ │PgU│   │
     * ├───┼───┼───┼───┤ + │
     * │Alt│ ← │   │ → │   │
     * ├───┼───┼───┼───┤───┤
     * │Shi│End│ ↓ │PgD│   │
     * ├───┼───┴───┼───┤Ent│
     * │Ctr│Insert │Del│   │
     * └───┴───────┴───┘───┘
     */
    [1] = LAYOUT_numpad_6x5(
        RESET,      RGB_TOG,    RGB_MOD,    BL_BRTG,    KC_TRNS,
        RGB_RMOD,   RGB_MOD,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        RGB_SPI,    RGB_HUI,    RGB_SAI,    RGB_VAI,    KC_TRNS,
        RGB_SPD,    RGB_HUD,    RGB_SAD,    RGB_VAD,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,                KC_TRNS 
    )

};


void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
    #ifdef CONSOLE_ENABLE
        uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
        enum rgb_matrix_effects temp = rgb_matrix_get_mode();
        uprintf("mode: %d", temp);
    #endif 
    return true;
}



#ifdef RGB_MATRIX_ENABLE
//<define variables here if any>
//<define sub functions here if any>
void rgb_matrix_indicators_user(void) {
    if (rgb_matrix_get_flags() == LED_FLAG_NONE) { //I believe this stops the logic from continuing for that led if there is no LED_FLAG assigned to it from the boardname.c file
        return;
    }
    if (host_keyboard_led_state().num_lock) {    //Will be true if num_lock is on, which activates the logic below
        rgb_matrix_set_color(25, 255,255,255); //NumLock indicator
    }
    else 
    {
        rgb_matrix_set_color(25, 0,0,0);
    }
}
#endif // RGB_MATRIX_ENABLE

