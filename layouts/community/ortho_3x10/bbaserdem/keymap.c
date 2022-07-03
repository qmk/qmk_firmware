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
#include QMK_KEYBOARD_H
#include "bbaserdem.h"

#ifdef KEYBOARD_40percentclub_gherkin
    // Flip it
    #undef LAYOUT_ortho_3x10
    #define LAYOUT_ortho_3x10( \
	 K00,   K01,   K02,   K03,   K04,   K05,   K10,   K11,   K12,   K13 , \
	 K14,   K15,   K20,   K21,   K22,   K23,   K24,   K25,   K30,   K31 , \
	 K32,   K33,   K34,   K35,   K40,   K41,   K42,   K43,   K44,   K45   \
    ) { \
	{ K45,   K44,   K43,   K42,   K41,   K40 }, \
	{ K35,   K34,   K33,   K32,   K31,   K30 }, \
	{ K25,   K24,   K23,   K22,   K21,   K20 }, \
	{ K15,   K14,   K13,   K12,   K11,   K10 }, \
	{ K05,   K04,   K03,   K02,   K01,   K00 }  \
    }
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Game pad
 * ,-----------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  | F1  | F2  | F3  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |AdjsL|  Q  |  W  |  E  |  R  | Ent | Tab | Ctr | |^| | Alt |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |Music|  A  |  S  |  D  |  F  | Spc |Shift| <-- | |v| | --> |
 * `-----------------------------------------------------------'
 */
    [_BASE] = LAYOUT_ortho_3x10(
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_F1,  KC_F2,  KC_F3,
    MO(_MEDI),  KC_Q,   KC_W,   KC_E,   KC_R,   KC_ENT, KC_TAB, KC_LCTL,KC_UP,  KC_LALT,
        MU_TOG, KC_A,   KC_S,   KC_D,   KC_F,   KC_SPC, KC_LSFT,KC_LEFT,KC_DOWN,KC_RGHT
    ),
/* Adjust
 * ,-----------------------------------------------------------.
 * | Esc |RGBTg|HueUp|HueDn|SatUp|SatDn|ValUp|ValDn|ModNx|ModPr|
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     |BltTg|Breth|BriUp|BriDn|     |     |Veloc|SpdUp|SpdDn|
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |Music|     |     |     |     |     |     |     |EEprm|Reset|
 * `-----------------------------------------------------------'
 */
    [_MEDI] = LAYOUT_ortho_3x10(
        CK_TOGG,RGB_TOG,RGB_HUI,RGB_HUD,RGB_SAI,RGB_SAD,RGB_VAI,RGB_VAD,RGB_MOD,RGB_RMOD,
        _______,BL_TOGG,BL_BRTG,BL_INC, BL_DEC, XXXXXXX,XXXXXXX,VLK_TOG,RGB_SPI,RGB_SPD,
        AU_TOG, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,EEP_RST,RESET
    ),
    [_MUSI] = LAYOUT_ortho_3x10_wrapper(
        MU_FAST,_MU_08_,MU_REC,
        MU_SLOW,_MU_08_,MU_STOP,
        MU_TOG, _MU_08_,MU_PLAY
    ),
};

// Music map, guitar like.
#ifdef AUDIO_ENABLE
const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_ortho_3x10(
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
     5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9
);
#endif

// RGB matrix code
#ifdef RGB_MATRIX_ENABLE
// Gherkin
#if defined(KEYBOARD_40percentclub_gherkin)
led_config_t g_led_config = {
  { // Key Matrix to LED Index
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED}
}, { // LED Index to Physical Position
    {224,  0}, {168,  0}, {112,  0}, { 56,  0}, {  0,  0},
    {  0, 64}, { 56, 64}, {112, 64}, {168, 64}, {224, 64},
}, { // LED Index to Flag
    2,2,2,2,2,2,2,2,2,2
}};
// Disable layer switching
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {return true;}
#endif // Gherkin
#endif // RGB Matrix
