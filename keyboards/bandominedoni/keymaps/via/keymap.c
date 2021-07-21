/* Copyright 2021 3araht
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
#ifndef PEDAL_NORMALLY_CLOSED
    _OPEN,
#endif
    _CLOSE,
#ifdef PEDAL_NORMALLY_CLOSED
    _OPEN,
#endif
    _MISC,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_OPEN] = LAYOUT(
                  MI_Gs_1, MI_As_1, MI_Cs_2, MI_F_2, MI_Gs_3,
       MI_E_1, MI_A_1, MI_G_2, MI_Ds_2, MI_F_3, MI_As_2, MI_F_1,
         MI_D_2, MI_A_2, MI_C_3, MI_E_3, MI_C_2, MI_G_1, TG_SWAP,
       MI_E_2, MI_Gs_2, MI_B_2, MI_D_3, MI_Fs_3, MI_Cs_3, MI_Fs_1,
     MI_D_1, MI_B_1, MI_G_3, MI_A_3, MI_Ds_3, MI_Fs_2, MI_Ds_1, MI_C_1,

     MO_SWAP,    MI_B_5, MI_Gs_5, MI_G_5, MI_F_5,     FN_MUTE,
         MI_Cs_3, MI_A_5, MI_Fs_5, MI_E_5, MI_Ds_5, KC_VOLD, KC_VOLU,
        MI_C_3, MI_D_3, MI_G_3, MI_As_4, MI_C_5, MI_D_5,
     TG_SWAP, MI_B_2, MI_E_3, MI_Cs_4, MI_Fs_3, MI_A_3, MI_C_4, MI_E_4,
       MI_A_2, MI_F_3, MI_As_3, MI_Gs_3, MI_B_3, MI_D_4, MI_Gs_4, MI_B_4,
     MI_Gs_2, MI_As_2, MI_Ds_3, MI_F_4, MI_Ds_4, MI_Fs_4, MI_A_4, MI_Cs_5, MI_G_4
    ),

    [_CLOSE] = LAYOUT(
                  MI_Gs_1, MI_As_1, MI_Ds_2, MI_Ds_3, MI_G_3,
       MI_D_1, MI_D_2, MI_As_2, MI_C_3, MI_Cs_2, MI_C_2, MI_Fs_1,
         MI_G_1, MI_G_2, MI_B_2, MI_D_3, MI_F_3, MI_Fs_2, TG_SWAP,
       MI_A_1, MI_E_2, MI_A_2, MI_Cs_3, MI_E_3, MI_Gs_2, MI_B_1,
     MI_E_1, MI_E_2, MI_Fs_3, MI_Gs_3, MI_B_3, MI_F_2, MI_Cs_1, MI_F_1,

     MO_SWAP,    MI_A_5, MI_Gs_5, MI_Fs_5, MI_F_5,     FN_MUTE,
         MI_C_3, MI_G_5, MI_As_4, MI_C_5, MI_Ds_5, KC_VOLD, KC_VOLU,
        MI_D_3, MI_Cs_3, MI_Gs_3, MI_As_3, MI_C_4, MI_D_5,
     TG_SWAP, MI_B_2, MI_Fs_3, MI_Fs_4, MI_G_3, MI_B_3, MI_D_4, MI_G_4,
       MI_A_2, MI_F_3, MI_E_3, MI_A_3, MI_Cs_4, MI_E_4, MI_A_4, MI_Cs_5,
     MI_Gs_2, MI_As_2, MI_Ds_3, MI_F_4, MI_E_4, MI_Gs_4, MI_B_4, MI_E_5, MI_Ds_4
    ),

    [_MISC] = LAYOUT(
                  _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
          _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______, _______,

     _______,        _______, _______, _______, _______,         _______,
                  _______, _______, _______, _______, _______, _______, _______,
                _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______,
         _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FN] = LAYOUT(
                   DF_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

     _______,        MI_OCTD, MI_OCTU, MI_VELD, MI_VELU,         _______,
                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            RGB_SAD, RGB_SAI, RGB_HUD, RGB_HUI, RGB_SPD, RGB_SPI, RGB_VAD, RGB_VAI,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_RMOD, RGB_MOD, EEP_RST, RGB_TOG
    )
};

void eeconfig_init_user(void) {  // EEPROM is getting reset!
  #ifdef RGB_MATRIX_ENABLE
  rgb_matrix_enable();
  rgb_matrix_set_speed(RGB_MATRIX_STARTUP_SPD);
  rgb_matrix_sethsv(HSV_BLUE);

  rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE);
  // rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
  #endif
}

void keyboard_post_init_user(void) {
    //  Set octave to MI_OCT_0
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;

    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;
};

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_user(void) {
    if (rgb_matrix_is_enabled()) {  // turn the lights on when it is enabled.
        uint8_t layer = biton32(layer_state);
        switch (layer) {
            case _CLOSE:
                // rgb_matrix_set_color(pgm_read_byte(&convert_led_location2number[11]),  RGB_RED);         //  RGB_TOG  <- too heavy.

                // Close state indicator
                rgb_matrix_set_color( 0, RGB_DARKWHITE);     //  oc
                break;

            case _FN:
                // rgb_matrix_set_color(pgm_read_byte(&convert_led_location2number[11]),  RGB_RED);         //  RGB_TOG  <- too heavy.
                rgb_matrix_set_color(14, RGB_DARKYELLOW);      //  MI_OCTD
                rgb_matrix_set_color(25, RGB_DARKGREEN);       //  MI_OCTU
                rgb_matrix_set_color(14, RGB_DARKYELLOW);      //  MI_VELD
                rgb_matrix_set_color(25, RGB_DARKGREEN);       //  MI_VELU

                rgb_matrix_set_color( 6, RGB_DARKBLUE);        //  RGB_SAD
                rgb_matrix_set_color( 9, RGB_DARKBLUE);        //  RGB_SAI
                rgb_matrix_set_color(18, RGB_DARKBLUE);        //  RGB_HUD
                rgb_matrix_set_color(21, RGB_DARKBLUE);        //  RGB_HUI
                rgb_matrix_set_color(29, RGB_DARKBLUE);        //  RGB_SPD
                rgb_matrix_set_color(32, RGB_DARKBLUE);        //  RGB_SPI
                rgb_matrix_set_color(36, RGB_DARKBLUE);        //  RGB_VAD
                rgb_matrix_set_color(39, RGB_DARKBLUE);        //  RGB_VAI

                rgb_matrix_set_color(31, RGB_DARKBLUE);        //  RGB_RMOD
                rgb_matrix_set_color(37, RGB_DARKBLUE);        //  RGB_MOD
                rgb_matrix_set_color(38, RGB_DARKPINK);        //  EEP_RST
                rgb_matrix_set_color(40, RGB_DARKRED);         //  RGB_TOG

                rgb_matrix_set_color(41, RGB_DARKORANGE);      //  _FN
                break;
        }
    }
}
#endif
