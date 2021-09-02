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
<<<<<<< HEAD
#include <string.h>
// Grab the print function 
#ifdef ENCODER_ENABLE
#   include "bb-encoder.h"
#endif // ENCODER_ENABLE

/* OLED
 * This contains general purpose oled code
=======
#ifdef ENCODER_ENABLE
    #include "bb-encoder.h"
#endif
/* ROTARY ENCODER
 * This contains my general rotary encoder code
 * Encoders each have a list of different modes they can be in.
 * Each mode also have an on click action as well.
 * Modes can be cycled using either shift-click or ctrl-click
 * Modes can be reset using OS click
 * Some modes are only accessible through some keymap layers
>>>>>>> 1786b2a4f6 (Fixed kyria code to operational)
 */ 

// Allow default to be overwritten by keymap if they return false
__attribute__ ((weak)) bool oled_task_keymap(void) {return true;}

// Do sane defaults for regular oled rendering
void oled_task_user(void) {
    if (oled_task_keymap()) {
        render_status_lite(0, 0);
    }
}

<<<<<<< HEAD
/*-------------------------*\
|*---RENDERING FUNCTIONS---*|
\*-------------------------*/
void render_qmk_logo(uint8_t row, uint8_t col) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,
        0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,
        0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,
        0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
    oled_set_cursor(col, row);
    oled_write_P(qmk_logo, false);
}
=======
static void render_status(void) {
    // Function to print state information
    uint8_t this_layer = get_highest_layer(layer_state);
    uint8_t this_mod =   get_mods();
    // Temporary variable for RGB
    #if defined RGBLIGHT_ENABLE
    static char rgb_temp4[4] = {0};
    #elif defined RGB_MATRIX_ENABLE
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
>>>>>>> 1786b2a4f6 (Fixed kyria code to operational)

void render_layer(uint8_t row, uint8_t col, uint8_t top_layer) {
    // Write the layer state
    oled_set_cursor(col, row);
    oled_write("Layer: ", false);
    switch (top_layer) {
        case _BASE:
            oled_write("Default", false);
            break;
        case _CHAR:
            oled_write("Sp. Chars", false);
            break;
        case _GAME:
            oled_write("Gaming", false);
            break;
        case _MEDI:
            oled_write("Media Ctr", false);
            break;
        case _NAVI:
            oled_write("Navigation", false);
            break;
        case _SYMB:
            oled_write("Symbols", false);
            break;
        case _NUMB:
            oled_write("Numpad", false);
            break;
        case _FUNC:
            oled_write("Funct Keys", false);
            break;
        case _MOUS:
            oled_write("Mouse Keys", false);
            break;
        case _MUSI:
            oled_write("Music Mode", false);
            break;
        default:
            oled_write("???", false);
    }
    oled_advance_page(true);
}

void render_modifiers_lite(uint8_t row, uint8_t col, uint8_t mods) {
    // Write the modifier state
    oled_set_cursor(col, row);
    oled_write((mods & MOD_MASK_SHIFT  ) ? "Shft " : "     ", false);
    oled_write((mods & MOD_MASK_CTRL   ) ? "Ctrl " : "     ", false);
    oled_write((mods & MOD_MASK_ALT    ) ? "Alt"   : "   ",   false);
    oled_write((mods & MOD_BIT(KC_RALT)) ? "G "    : "  ",    false);
    oled_write((mods & MOD_MASK_GUI    ) ? "Meta " : "    ",  false);
    oled_advance_page(true);
}

// Renders the encoder state, 14 characters
void render_encoder(uint8_t row, uint8_t col, uint8_t index, uint8_t layer) {
    oled_set_cursor(col, row);

#   ifdef ENCODER_ENABLE
    static char encoder_temp9[9] = {0};
    oled_write("Enc: ", false);
    encoder_state_string(index, layer, encoder_temp9);
    oled_write(encoder_temp9, false);
#   else // ENCODER_ENABLE
    oled_write("No enc. avail.", false);
#   endif // ENCODER_ENABLE
    oled_advance_page(true);
}

void render_wpm(uint8_t row, uint8_t col) {
    // Renders the WPM, 8 characters
    oled_set_cursor(col, row);
#   ifdef WPM_ENABLE
    static char wpm_temp4[4] = {0};
    oled_write("WPM: ", false);
    itoa(get_current_wpm(), wpm_temp4, 10);
    oled_write(wpm_temp4, false);
    oled_write("      ", false);
#   else // WPM_ENABLE
    oled_write("WPM: N/A", false);
#   endif // WPM_ENABLE
    oled_advance_page(true);
}

// Writes the currently used OLED display layout
void render_keymap(uint8_t row, uint8_t col, bool isLite) {
    // Render the oled layout
    oled_set_cursor(col, row);
    if (isLite) {
        oled_write("KM: ", false);
    } else {
        oled_write("Layout: ", false);
    }
    switch (userspace_config.layout % 3) {
        case 0:
            oled_write("Dvorak", false);
            break;
        case 1:
            oled_write("Tur. F", false);
            break;
        case 2:
            oled_write("Qwerty", false);
            break;
    }
    if (isLite) {
        oled_write(" ", false);
    } else {
        oled_advance_page(true);
    }
}

// Writes the currently used OLED display layout
#ifdef RGB_MATRIX_ENABLE
void render_rgb_lite(uint8_t row, uint8_t col) {
    static char rgb_temp4[4] = {0};
    // Render the oled layout
    oled_set_cursor(col, row);
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
    oled_advance_page(true);
}
#endif // RGB_MATRIX_ENABLE

void render_status_lite(uint8_t row, uint8_t col) {
    // Function to print state information; for low flash memory
    uint8_t this_layer = get_highest_layer(layer_state);
    uint8_t this_mod =   get_mods();

    // Line 1: Layer State
    render_layer(row + 0, col + 0, this_layer);

    // Line 2: Mod or info
    switch (this_layer) {
        // Show RGB mode as an overlay in media mode.
#       ifdef RGB_MATRIX_ENABLE
        case _MEDI:
<<<<<<< HEAD
            render_rgb_lite(row + 1, col + 0);
            break;
#       endif // RGB_MATRIX_ENABLE
=======
            oled_write_P(PSTR("m:"), false);
            itoa(rgblight_config.mode, rgb_temp4, 10);
            oled_write(rgb_temp4, false);
            oled_write_P(PSTR(" h:"), false);
            itoa(rgblight_config.hsv.h, rgb_temp4, 10);
            oled_write(rgb_temp4, false);
            oled_write_P(PSTR(" s:"), false);
            itoa(rgblight_config.hsv.s, rgb_temp4, 10);
            oled_write(rgb_temp4, false);
            oled_write_P(PSTR(" v:"), false);
            itoa(rgblight_config.hsv.v, rgb_temp4, 10);
            oled_write(rgb_temp4, false);
            oled_write_P(PSTR("\n"), false);
            break;
#elif defined RGB_MATRIX_ENABLE
        case _MEDI:
            oled_write_P(PSTR("m"), false);
            itoa(rgb_matrix_config.mode, rgb_temp4, 10);
            oled_write(rgb_temp4, false);
            oled_write_P(PSTR(" h"), false);
            itoa(rgb_matrix_config.hsv.h, rgb_temp4, 10);
            oled_write(rgb_temp4, false);
            oled_write_P(PSTR(" s"), false);
            itoa(rgb_matrix_config.hsv.s, rgb_temp4, 10);
            oled_write(rgb_temp4, false);
            oled_write_P(PSTR(" v"), false);
            itoa(rgb_matrix_config.hsv.v, rgb_temp4, 10);
            oled_write(rgb_temp4, false);
            oled_write_P(PSTR("\n"), false);
            break;
#endif
>>>>>>> 1786b2a4f6 (Fixed kyria code to operational)
        // Show the modifier if nothing else is doing anything
        default:
            render_modifiers_lite(row + 1, col + 0, this_mod);
            break;
    }

<<<<<<< HEAD
    // Line 3: WPM and layout
    render_keymap(row + 2, col + 0, true);
    render_wpm(row + 2, col + 11);

    // Line 4: Encoder states
    oled_write("Encoder: ", false);
#   ifdef SPLIT_KEYBOARD
    if (is_keyboard_left()) {
        render_encoder(row + 3, col + 0, 0, this_layer);
=======
    // Line 3: WPM
    oled_write_P(PSTR("KM: Qwerty WPM: "), false);
#if defined WPM_ENABLE
    itoa(get_current_wpm(), wpm_temp4, 10);
    oled_write(wpm_temp4, false);
#else
    oled_write_P(PSTR("N/A"), false);
#endif
    oled_write_P(PSTR("\n"), false);

    // Line 4: Encoder states
#ifdef ENCODER_ENABLE
    oled_write_P(PSTR("EN0:"), false);
    encoder_state_string(0, this_layer, encoder_temp6);
    oled_write(encoder_temp6, false);
    oled_write_P(PSTR(" EN1:"), false);
    encoder_state_string(1, this_layer, encoder_temp6);
    oled_write(encoder_temp6, false);
#endif
    oled_write_P(PSTR("\n"), false);

}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        #if defined(KEYBOARD_splitkb_kyria_rev1)
        render_qmk_logo();
        #endif
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
>>>>>>> 1786b2a4f6 (Fixed kyria code to operational)
    } else {
        render_encoder(row + 3, col + 0, 1, this_layer);
    }
#   else // SPLIT_KEYBOARD
    render_encoder(row + 3, col + 0, 0, this_layer);
#   endif // SPLIT_KEYBOARD
}
