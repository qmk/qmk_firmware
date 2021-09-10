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
 */ 

// Following line imports reading of RGB settings
#if defined RGB_MATRIX_ENABLE
extern rgb_config_t rgb_matrix_config;
#endif

#if defined(KEYBOARD_splitkb_kyria_rev1)
static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
  oled_write_P(qmk_logo, false);
}
#endif



#if defined(KEYBOARD_crkbd_rev1)
// These are my images for keyboard layout
// Naming scheme is <layer>_left/right{_keyboardLayout}{_modifiers}
//static const char PROGMEM base0_L_dvor_nomod[][4] = {};
//static const char PROGMEM base0_L_dvor_shift[][4] = {};
//static const char PROGMEM base0_R_dvor_nomod[][4] = {};
//static const char PROGMEM base0_R_dvor_shift[][4] = {};
//static const char PROGMEM char1_L[][4] = {};
//static const char PROGMEM char1_R[][4] = {};
//static const char PROGMEM game2_L[][4] = {};
//static const char PROGMEM medi3_R[][4] = {};
//static const char PROGMEM navi4_R[][4] = {};
//static const char PROGMEM symb5_R_dvor[][4] = {};
//static const char PROGMEM numb6_L_dvor_nomod[][4] = {};
//static const char PROGMEM numb6_L_dvor_shift[][4] = {};
//static const char PROGMEM func7_L[][4] = {};
//static const char PROGMEM mous8_L[][4] = {};
//static const char PROGMEM musi9_L[][4] = {};
static const char PROGMEM musi9_R[4][42] = {
    {   0x00, 0x00, 0x00, 0xfe, 0x04, 0x18, 0x04, 0xfe, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0xfe, 0x00, 
0x8c, 0x12, 0x12, 0x12, 0xe4, 0x00, 0x00, 0x02, 0xfe, 0x02, 0x00, 0x00, 0xfc, 0x02, 0x02, 0x02, 
0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe7, 0x73, 0x00, 0x00}, {
        0x00, 0x00, 0x00, 0x81, 0x60, 0x10, 0x60, 0x81, 0x60, 0x10, 0x00, 0x01, 0x01, 0x01, 0xe0, 0xe0, 
0x60, 0x61, 0x61, 0x61, 0x60, 0xf8, 0x70, 0x21, 0x01, 0x01, 0xc0, 0xe0, 0x60, 0x01, 0xf9, 0xf9, 
0x00, 0x60, 0xe0, 0xc0, 0x00, 0x00, 0x9c, 0xce, 0x00, 0x00}, {
        0x18, 0x24, 0x4b, 0x48, 0x48, 0x4c, 0x4b, 0x48, 0x4b, 0x2c, 0x18, 0x00, 0x00, 0x00, 0x4f, 0xe7, 
0xf0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7e, 0x7f, 0x00, 0x0f, 0x3f, 0x70, 0x60, 0xc0, 0xc1, 0xc1, 
0xc0, 0x60, 0x70, 0x3f, 0x0f, 0x00, 0x73, 0x39, 0x00, 0x00}, {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x08, 0xf8, 0x08, 0xf0, 0x00, 0x70, 0x88, 0x88, 0x88, 
0x71, 0x00, 0x70, 0x88, 0x88, 0x48, 0xff, 0x00, 0x70, 0xa8, 0xa8, 0xa8, 0xb0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xce, 0xe7, 0x00, 0x00}  };

static void render_test(void) {
    // Oled set cursor does characters; so moves in 8x6
    // Oled write raw does not advance the cursor; it has to be done seperately.
    oled_write_raw_P(musi9_R[0], 42);
    oled_set_cursor(8, 0);
    oled_write("This text", false);
    oled_advance_page(false);
    oled_write_raw_P(musi9_R[1], 42);
    oled_set_cursor(8, 1);
    oled_write("is a test", false);
    oled_advance_page(false);
    oled_write_raw_P(musi9_R[2], 42);
    oled_set_cursor(8, 2);
    oled_write("for me to", false);
    oled_advance_page(false);
    oled_write_raw_P(musi9_R[3], 42);
    oled_set_cursor(8, 3);
    oled_write("check it.", false);
}
#endif

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
            itoa(rgb_matrix_config.mode, rgb_temp4, 10);
            oled_write(rgb_temp4, false);
            oled_write(" h", false);
            itoa(rgb_matrix_config.hsv.h, rgb_temp4, 10);
            oled_write(rgb_temp4, false);
            oled_write(" s", false);
            itoa(rgb_matrix_config.hsv.s, rgb_temp4, 10);
            oled_write(rgb_temp4, false);
            oled_write(" v", false);
            itoa(rgb_matrix_config.hsv.v, rgb_temp4, 10);
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
    encoder_state_string(0, this_layer, encoder_temp6);
    oled_write(encoder_temp6, false);
    oled_write(" EN1:", false);
    encoder_state_string(1, this_layer, encoder_temp6);
    oled_write(encoder_temp6, false);
#endif
    oled_write("\n", false);

}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        #if defined(KEYBOARD_splitkb_kyria_rev1)
        render_qmk_logo();
        render_status();
        #endif
    } else {
        #if defined(KEYBOARD_splitkb_kyria_rev1)
        render_qmk_logo();
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
        #endif
    }
}
