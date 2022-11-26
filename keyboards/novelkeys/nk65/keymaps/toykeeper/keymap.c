/* Copyright 2021-2022 Selene ToyKeeper
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

#include "toykeeper.h"
// for LED indicator ... because Wilba Tech doesn't use the standard QMK API
#include "drivers/led/issi/is31fl3733.h"

// TODO: Fix RGB toggle key

#define MY_LAYOUT LAYOUT_65_ansi

// wrap base layers to avoid the need to keep several copies in sync
#define MY_LAYOUT_wrapper(...) MY_LAYOUT(__VA_ARGS__)
#define MY_LAYOUT_base_wrapper(...) MY_LAYOUT_base(__VA_ARGS__)
#define MY_LAYOUT_base(                             K01, K02, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, \
      K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
        K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A \
  ) MY_LAYOUT_wrapper( \
    QK_GESC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , K01    , K02    , KC_BSLS,  TK_STAR, \
    KC_TAB , K11    , K12    , K13    , K14    , K15    , K16    , K17    , K18    , K19    , K1A    , K1B    , K1C    , KC_BSPC,  KC_PGUP, \
    KC_LCTL, K21    , K22    , K23    , K24    , K25    , K26    , K27    , K28    , K29    , K2A    , K2B    ,      KC_ENT ,      KC_PGDN, \
    KC_LSPO, K31    , K32    , K33    , K34    , K35    , K36    , K37    , K38    , K39    , K3A    ,      KC_RSPC,     KC_UP  ,  KC_END , \
    TK_MOON, KC_LGUI, TK_LALT,                   KC_SPC ,                            TK_RCTL, TK_RGUI, TK_MOUS, KC_LEFT, KC_DOWN,  KC_RGHT  \
    )

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* empty, copy/paste and fill in the blanks
[L_EMPTY] = MY_LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,     _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,     _______, _______,
    _______, _______, _______,                   _______,                            _______, _______, _______, _______, _______, _______
    ), */

// base layers: qwerty, dvorak, undvorak, colemak-dh-tk
[L_QWERTY  ] = MY_LAYOUT_base_wrapper(__QWERTY__),
[L_DVORAK  ] = MY_LAYOUT_base_wrapper(__DVORAK__),
[L_UNDVORAK] = MY_LAYOUT_base_wrapper(__UNDVORAK__),
[L_COLEMAK ] = MY_LAYOUT_base_wrapper(__COLEMAK_DH_TK__),

// Number Pad(s)
[L_NUMPAD] = MY_LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,      _______,     _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,     _______, _______,
    _______, _______, _______,                   _______,                            _______, _______, _______, _______, _______, _______
    ),

// Mouse (lower right corner)
[L_MOUSE] = MY_LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_WH_U,
    TK_WARP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      KC_BTN3,     KC_WH_D,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      KC_BTN1,     KC_MS_U, KC_BTN2,
    _______, _______, _______,                   _______,                            _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R
    ),

// Fn1 / Moon (lower left corner)
[L_FN1] = MY_LAYOUT(
    TK_SESC, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , TK_BSTG, _______,
    KC_MPLY, KC_MNXT, KC_MPRV, TK_ANY , _______, _______, _______, KC_WH_U, KC_MS_U, KC_WH_D, _______, _______, _______, KC_DEL , KC_WH_U,
    TK_WARP, DM_PLY2, DM_REC2, _______, _______, _______, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, _______,      KC_BTN3,     KC_WH_D,
    KC_BTN3, DM_PLY1, DM_REC1, _______, _______, _______, TK_WARP, KC_BTN1, KC_BTN3, KC_BTN2, _______,      KC_BTN1,     KC_MS_U, KC_BTN2,
    _______, KC_BTN1, KC_BTN2,                   KC_DEL ,                            _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R
    ),

// Fn2 / Star (upper right corner)
[L_FN2] = MY_LAYOUT(
    QK_BOOT, KC_MYCM, KC_WSCH, KC_F13 , KC_F14 , KC_F15 , KC_F16 , KC_F17 , KC_F18 , KC_F19 , KC_F20 , KC_F21 , KC_F22 , TK_SINS, _______,
    TK_INFO, EF_DEC , EF_INC , BR_DEC , BR_INC , ES_DEC , ES_INC , _______, _______, _______, _______, _______, KC_INS , KC_DEL , KC_F13 ,
    KC_CAPS, H1_DEC , H1_INC , S1_DEC , S1_INC , TK_IUUI, _______, _______, _______, _______, _______, _______,      _______,     KC_WSCH,
    TK_DF_3, H2_DEC , H2_INC , S2_DEC , S2_INC , _______, NK_TOGG, _______, _______, _______, _______,      _______,     KC_PGUP, KC_MYCM,
    TK_DF_0, TK_DF_1, TK_DF_2,                   RGB_TOG,                            KC_APP , _______, _______, KC_HOME, KC_PGDN, KC_END
    )

};


/* Indicator LEDS are part of the LED driver
 * Top LED is blue only. LED driver 2 RGB 7 Green channel
 * Middle LED is blue and red. LED driver 2 RGB 6 Red and Blue channel
 * (but the middle LED doesn't seem to work... at all)
 * Bottom LED is red only LED driver 2 RGB 6 Green channel.
 */
bool led_update_user(led_t led_state) {
    return false;  // don't let _kb() code do anything
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t g2 = 0;
    uint8_t b = 0;

    // top LED: blue (on green channel)
    if (IS_LAYER_ON_STATE(state, L_MOUSE)) g2 = 255;

    // middle LED: blue+red
    if (IS_LAYER_ON_STATE(state, L_FN1)) r = 255;

    // middle LED: blue+red
    if (IS_LAYER_ON_STATE(state, L_FN2)) b = 255;

    // bottom LED: red (on green channel)
    if (IS_LAYER_ON_STATE(state, L_NUMPAD)) g = 255;

    IS31FL3733_set_color( 6+64-1, r, g, b );
    IS31FL3733_set_color( 7+64-1, r, g2, b );

    return state;
}


///// RGB indicators per key /////
// This part is super weird and kludgey,
// because this keyboard uses Wilba Tech's RGB code,
// and it's not compatible with QMK's RGB Matrix,
// so everything below here is an ugly hack.

// highlight color for each layer while active
const uint8_t layer_colors[][3] = {
    [L_QWERTY  ] = {0,0,0},
    [L_DVORAK  ] = {0,0,0},
    [L_UNDVORAK] = {0,0,0},
    [L_COLEMAK ] = {0,0,0},
    [L_NUMPAD  ] = {192,0,0},    // red
    [L_MOUSE   ] = {224,0,16},   // bubble gum pink
    [L_FN1     ] = {255,0,192},  // neon purple-ish
    [L_FN2     ] = {0,200,100},  // mint green
};
const uint8_t layer_indicator_colors[][6] = {
    { L_NUMPAD  , 9,4, 192,  0,  0 },
    { L_MOUSE   ,11,4, 255, 20,255 },
    { L_FN1     , 0,4, 128,255, 32 },
    { L_FN2     ,14,0, 128,255,  0 },
    { 0         , 0,0,   0,  0,  0 },  // stop
};
const uint8_t mod_colors[] = {255,255,16};
const uint8_t mod_indicator_coords[][3] = {
    // mod, x, y
    { 1, 0, 3, },  // L Shift
    { 1,12, 3, },  // R Shift
    { 2, 0, 2, },  // L Ctrl
    { 2, 9, 4, },  // R Ctrl
    { 3, 2, 4, },  // L Alt
    //{ 3, 2, 4, },  // R Alt
    { 4, 1, 4, },  // L GUI
    { 4,10, 4, },  // R GUI
    { 0, 0, 0, },  // stop
};

// these should be defined in a wilbatech .h file, but aren't:
void map_row_column_to_led( uint8_t row, uint8_t column, uint8_t *led );
void backlight_set_color( int index, uint8_t red, uint8_t green, uint8_t blue );

#define NO_LED 255
#define rgb_set_color(i,r,g,b) backlight_set_color(i,r,g,b)
#define rowcol_to_led(row,col,index) map_row_column_to_led(row,col,&index)

// copied and adapted from toykeeper.c
//bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
void backlight_effect_indicators(void) {
    // indicate current status on the RGB matrix
    // (active modifiers and each active non-base layer)

    // light up all keys defined in an active non-base layer
    uint8_t top = get_highest_layer(layer_state);
    if (top >= L_BOTTOM)
    {
        // light up each key according to the
        // highest active non-base layer which defines it
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index;
                rowcol_to_led(row, col, index);

                if (index != NO_LED) {
                    uint16_t kc = 0;
                    for (uint8_t layer=top; (layer>=L_BOTTOM) && (kc<=KC_TRNS); layer--) {
                        if (IS_LAYER_ON(layer)) {
                            kc = keymap_key_to_keycode(layer, (keypos_t){col,row});
                            if (kc > KC_TRNS) {
                                rgb_set_color(index,
                                        layer_colors[layer][0],
                                        layer_colors[layer][1],
                                        layer_colors[layer][2]
                                        );
                            }  // hooray for deep nesting
                        }
                    }
                }
            }
        }
    }

    // light up the indicator key for each active layer with an indicator
    for (uint8_t i=0; ; i++) {
        uint8_t l = layer_indicator_colors[i][0];
        uint8_t x = layer_indicator_colors[i][1];
        uint8_t y = layer_indicator_colors[i][2];
        uint8_t r = layer_indicator_colors[i][3];
        uint8_t g = layer_indicator_colors[i][4];
        uint8_t b = layer_indicator_colors[i][5];
        if (! l) break;
        if (IS_LAYER_ON(l)) {
            uint8_t index;
            rowcol_to_led(y, x, index);
            rgb_set_color(index, r, g, b);
        }
    }

    // light up each active modifier key
    for (uint8_t i=0; ; i++) {
        uint8_t m = mod_indicator_coords[i][0];
        uint8_t x = mod_indicator_coords[i][1];
        uint8_t y = mod_indicator_coords[i][2];
        uint8_t state = 0;
        if (! m) break;
        switch (m) {
            case 1:  // shift
                if (is_caps_word_on() || 
                    ((get_mods() | get_oneshot_mods()) & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))))
                    state = 1;
                break;
            case 2:  // ctrl
                if ((get_mods() | get_oneshot_mods()) & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)))
                    state = 1;
                break;
            case 3:  // alt
                if ((get_mods() | get_oneshot_mods()) & (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT)))
                    state = 1;
                break;
            case 4:  // gui
                if ((get_mods() | get_oneshot_mods()) & (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI)))
                    state = 1;
                break;
        }
        if (state) {
            uint8_t index;
            rowcol_to_led(y, x, index);
            rgb_set_color(index, mod_colors[0], mod_colors[1], mod_colors[2]);
        }
    }

    //return true;
}

