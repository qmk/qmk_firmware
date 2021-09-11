/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "bb-oled.h"
#include <string.h>
// Allow access to encoder_state
#ifdef ENCODER_ENABLE
#include "bb-encoder.h"
#endif // ENCODER_ENABLE

/* OLED
 * This contains general purpose oled code
 */ 

#ifdef ENCODER_ENABLE

#if !defined KEYBOARD_splitkb_kyria_rev1 // Don't include in kyria; space
void encoder_state_string8(uint8_t index, uint8_t layer, char* buffer) {
    // Get the layer straight from the main function
    switch (layer) {
        // If RGB control mode is enabled
        #ifdef RGB_MATRIX_ENABLE
        case _MEDI:
            switch (encoder_state[index].rgb) {
                case 0:
                    strcpy(buffer, "ani mode");
                    break;
                case 1:
                    strcpy(buffer, "hue     ");
                    break;
                case 2:
                    strcpy(buffer, "saturat.");
                    break;
                case 3:
                    strcpy(buffer, "bright. ");
                    break;
                case 4:
                    strcpy(buffer, "ani. spd");
                    break;
                default:
                    strcpy(buffer, " -N/A-  ");
                    break;
            }
            break;
        #endif
        // If pointer control is enabled
        #ifdef MOUSEKEY_ENABLE
        case _MOUS:
            switch (encoder_state[index].point) {
                case 0:
                    strcpy(buffer, "Lateral ");
                    break;
                case 1:
                    strcpy(buffer, "Vertical");
                    break;
                case 2:
                    strcpy(buffer, "Scr. Ver");
                    break;
                case 3:
                    strcpy(buffer, "Scr. Lat");
                    break;
                default:
                    strcpy(buffer, " -N/A-  ");
                    break;
            }
            break;
        #endif
        default:
            switch (encoder_state[index].base) {
                case 0:
                    strcpy(buffer, "Volume  ");
                    break;
                case 1:
                    strcpy(buffer, "Song    ");
                    break;
                case 2:
                    strcpy(buffer, "Sink    ");
                    break;
                case 3:
                    strcpy(buffer, "Src. Vol");
                    break;
                case 4:
                    strcpy(buffer, "Source  ");
                    break;
                case 5:
                    strcpy(buffer, "Arrow LR");
                    break;
                case 6:
                    strcpy(buffer, "Arrow UD");
                    break;
                case 7:
                    strcpy(buffer, "Page U/D");
                    break;
                case 8:
                    strcpy(buffer, "Erase   ");
                    break;
                default:
                    strcpy(buffer, " -N/A-  ");
                    break;
            }
            break;
    }
}
#endif // !KEYBOARD_splitkb_kyria_rev1

void encoder_state_string5(uint8_t index, uint8_t layer, char* buffer) {
    // Get the layer straight from the main function
    switch (layer) {
        // If RGB control mode is enabled
        #ifdef RGB_MATRIX_ENABLE
        case _MEDI:
            switch (encoder_state[index].rgb) {
                case 0:
                    strcpy(buffer, " mode");
                    break;
                case 1:
                    strcpy(buffer, " hue ");
                    break;
                case 2:
                    strcpy(buffer, "satur");
                    break;
                case 3:
                    strcpy(buffer, "value");
                    break;
                case 4:
                    strcpy(buffer, "speed");
                    break;
                default:
                    strcpy(buffer, "!oob!");
                    break;
            }
            break;
        #endif
        // If pointer control is enabled
        #ifdef MOUSEKEY_ENABLE
        case _MOUS:
            switch (encoder_state[index].point) {
                case 0:
                    strcpy(buffer, "m.lat");
                    break;
                case 1:
                    strcpy(buffer, "m.ver");
                    break;
                case 2:
                    strcpy(buffer, "s.ver");
                    break;
                case 3:
                    strcpy(buffer, "s.lat");
                    break;
                default:
                    strcpy(buffer, "!oob!");
                    break;
            }
            break;
        #endif
        default:
            switch (encoder_state[index].base) {
                case 0:
                    strcpy(buffer, " volm");
                    break;
                case 1:
                    strcpy(buffer, " song");
                    break;
                case 2:
                    strcpy(buffer, " sink");
                    break;
                case 3:
                    strcpy(buffer, "s.vol");
                    break;
                case 4:
                    strcpy(buffer, " src ");
                    break;
                case 5:
                    strcpy(buffer, " L/R ");
                    break;
                case 6:
                    strcpy(buffer, " U/D ");
                    break;
                case 7:
                    strcpy(buffer, "pgU/D");
                    break;
                case 8:
                    strcpy(buffer, " del ");
                    break;
                default:
                    strcpy(buffer, "!oob!");
                    break;
            }
            break;
    }
}
#endif // ENCODER_ENABLE

static void render_status(void) {
    // Function to print state information
    uint8_t this_layer = get_highest_layer(layer_state);
    uint8_t this_mod =   get_mods();
    // Temporary variable for RGB
    #if defined RGB_MATRIX_ENABLE
    static char rgb_temp4[4] = {0};
    #endif
    // Temporary variable for WPM string
    #if defined WPM_ENABLE
    static char wpm_temp4[4] = {0};
    #endif
    // Temporary variable for encoder state
    #if defined ENCODER_ENABLE
    static char encoder_temp6[6] = {0};
    #endif
    // Line 1: Layer State
    oled_write("Layer: ", false);
    switch (this_layer) {
        case _BASE:
            oled_write("Default\n", false);
            break;
        case _CHAR:
            oled_write("Sp. Chars\n", false);
            break;
        case _GAME:
            oled_write("Gaming\n", false);
            break;
        case _MEDI:
            oled_write("Media Ctr\n", false);
            break;
        case _NAVI:
            oled_write("Navigation\n", false);
            break;
        case _SYMB:
            oled_write("Symbols\n", false);
            break;
        case _NUMB:
            oled_write("Numpad\n", false);
            break;
        case _FUNC:
            oled_write("Funct Keys\n", false);
            break;
        case _MOUS:
            oled_write("Mouse Keys\n", false);
            break;
        case _MUSI:
            oled_write("Music Mode\n", false);
            break;
        default:
            oled_write("???\n", false);
    }
    // Line 2: Mod or info
    switch (this_layer) {
        // Show RGB mode as an overlay in media mode.
#if defined RGB_MATRIX_ENABLE
        case _MEDI:
            oled_write("m", false);
            itoa(rgb_matrix_get_mode(), rgb_temp4, 10);
            oled_write(rgb_temp4, false);
            oled_write(" h", false);
            itoa(rgb_matrix_get_hue(), rgb_temp4, 10);
            oled_write(rgb_temp4, false);
            oled_write(" s", false);
            itoa(rgb_matrix_get_sat(), rgb_temp4, 10);
            oled_write(rgb_temp4, false);
            oled_write(" v", false);
            itoa(rgb_matrix_get_val(), rgb_temp4, 10);
            oled_write(rgb_temp4, false);
            oled_write("\n", false);
            break;
#endif
        // Show the modifier if nothing else is doing anything
        default:
            oled_write((this_mod & MOD_MASK_SHIFT  ) ? "Shft " : "     ", false);
            oled_write((this_mod & MOD_MASK_CTRL   ) ? "Ctrl " : "     ", false);
            oled_write((this_mod & MOD_MASK_ALT    ) ? "Alt"   : "   ",   false);
            oled_write((this_mod & MOD_BIT(KC_RALT)) ? "G "    : "  ",    false);
            oled_write((this_mod & MOD_MASK_GUI    ) ? "Meta " : "    ",  false);
            oled_write("\n", false);
            break;
    }
    // Line 3: WPM
    oled_write("KM: Qwerty WPM: ", false);
#if defined WPM_ENABLE
    itoa(get_current_wpm(), wpm_temp4, 10);
    oled_write(wpm_temp4, false);
#else
    oled_write("N/A", false);
#endif
    oled_write("\n", false);
    // Line 4: Encoder states
#ifdef ENCODER_ENABLE
    oled_write("EN0:", false);
    encoder_state_string5(0, this_layer, encoder_temp6);
    oled_write(encoder_temp6, false);
    oled_write(" EN1:", false);
    encoder_state_string5(1, this_layer, encoder_temp6);
    oled_write(encoder_temp6, false);
#else
    oled_write("-Encoder unavailable-", false);
#endif
    oled_write("\n", false);
}

// Allow default to be overwritten by keymap if they return false
__attribute__ ((weak)) bool oled_task_keymap(void) {return true;}

// Do sane defaults for regular oled rendering
void oled_task_user(void) {
    if (oled_task_keymap()) {
        render_status();
    }
}
