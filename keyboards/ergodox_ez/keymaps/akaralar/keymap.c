/* Copyright 2022 Ahmet Karalar (@akaralar)
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
#include "version.h"
#include "raw_hid.h"

enum layers {
    BASE,  // default layer
    NAVI,  // navigation layer
    MOUS,  // mouse layer
    MDIA,  // media keys layer
    NUMB,  // numbers layer
    CODE,  // code symbols layer
    FUNC,  // Function keys layer
    SPAN,  // Spanish accented letters layer
};

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_MAC_REDO C_REDO
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)
#define SE_SECT_MAC ALGR(KC_6)

enum C_keycodes {
#ifdef ORYX_CONFIGURATOR
    VRSN = EZ_SAFE_RANGE,
#else
    VRSN = SAFE_RANGE,
#endif
    RGB_SLD,
    ST_MACRO_0,
    ST_MACRO_1,
    ST_MACRO_2,
    ST_MACRO_3,
    ST_MACRO_4,
    ST_MACRO_5,
    ST_MACRO_6,
    ST_MACRO_7,
    ST_MACRO_8,
    ST_MACRO_9,
    ST_MACRO_10,
    ST_MACRO_11,
    ST_MACRO_12,
    ST_MACRO_13,
};

#define C_E MEH_T(KC_E)
#define C_R ALL_T(KC_R)

#define C_A MT(MOD_LCTL, KC_A)
#define C_S MT(MOD_LALT, KC_S)
#define C_D MT(MOD_LGUI, KC_D)
#define C_F MT(MOD_LSFT, KC_F)

#define C_U ALL_T(KC_U)
#define C_I MEH_T(KC_I)

#define C_QUOTE MT(MOD_RCTL, KC_QUOTE)
#define C_L MT(MOD_LALT, KC_L)
#define C_K MT(MOD_RGUI, KC_K)
#define C_J MT(MOD_RSFT, KC_J)

#define C_REDO LGUI(LSFT(KC_Z))

#define C_MOOM LALT(LCTL(LSFT(KC_GRAVE)))
#define C_NAV_ALFD LGUI(LCTL(KC_SLASH))
#define C_ACT_ALFD RGUI(RCTL(KC_BSLASH))
#define C_1PASS LALT(LGUI(KC_BSLASH))

#define C_L1 LT(1, KC_SPACE)
#define C_L2 LT(2, KC_TAB)
#define C_L3 LT(3, KC_ESCAPE)
#define C_L4 LT(4, KC_BSPACE)
#define C_L5 LT(5, KC_ENTER)
#define C_L6 LT(6, KC_DELETE)
#define C_L7 MO(7)

#define C_MCR_ST DYN_REC_STOP
#define C_MCR_1R DYN_REC_START1
#define C_MCR_2R DYN_REC_START2
#define C_MCR_1P DYN_MACRO_PLAY1
#define C_MCR_2P DYN_MACRO_PLAY2

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


    /*
     * ,--------------------------------------------------.    ,--------------------------------------------------.
     * |    0   |   1  |   2  |   3  |   4  |   5  |  6   |    |  38  |  39  |  40  |  41  |  42  |  43  |   44   |
     * |--------+------+------+------+------+------+------|    |------+------+------+------+------+------+--------|
     * |    7   |   8  |   9  |  10  |  11  |  12  |  13  |    |  45  |  46  |  47  |  48  |  49  |  50  |   51   |
     * |--------+------+------+------+------+------|      |    |      |------+------+------+------+------+--------|
     * |   14   |  15  |  16  |  17  |  18  |  19  |------|    |------|  52  |  53  |  54  |  55  |  56  |   57   |
     * |--------+------+------+------+------+------|  26  |    |  58  |------+------+------+------+------+--------|
     * |   20   |  21  |  22  |  23  |  24  |  25  |      |    |      |  59  |  60  |  61  |  62  |  63  |   64   |
     * `--------+------+------+------+------+-------------'    `-------------+------+------+------+------+--------'
     *   |  27  |  28  |  29  |  30  |  31  |                                |  65  |  66  |  67  |  68  |  69  |
     *   `----------------------------------'                                `----------------------------------'
     *                                       ,-------------.  ,-------------.
     *                                       |  32  |  33  |  |  70  |  71  |
     *                                ,------+------+------|  |------+------+------.
     *                                |      |      |  34  |  |  72  |      |      |
     *                                |  35  |  36  |------|  |------|  74  |  75  |
     *                                |      |      |  37  |  |  73  |      |      |
     *                                `--------------------'  `--------------------'
     */

[BASE] = LAYOUT_ergodox_pretty(
_______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______ , _______, _______ , _______,
_______, KC_Q   , KC_W   , C_E    , C_R    , KC_T   , _______,      _______, KC_Y   , C_U    , C_I     , KC_O   , KC_P    , _______,
_______, C_A    , C_S    , C_D    , C_F    , KC_G   ,                        KC_H   , C_J    , C_K     , C_L    , C_QUOTE , _______,
_______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , _______,      _______, KC_N   , KC_M   , KC_COMMA, KC_DOT , KC_SLASH, _______,
_______, _______, _______, _______, C_L3   ,                                          C_L6   , _______ , _______, _______ , _______,

                                             _______, _______,      _______, _______,
                                                      _______,      _______,
                                    C_L1   , C_L2   , KC_F24 ,      C_L7   , C_L5   , C_L4
),

[NAVI] = LAYOUT_ergodox_pretty(
_______, _______    , _______   , _______    , _______     , _______, _______,      _______, _______  , _______     , _______    , _______   , _______    , _______,
_______, C_NAV_ALFD , C_ACT_ALFD, KC_MEH     , KC_HYPR     , C_MOOM , _______,      _______, KC_PGUP  , KC_HOME     , KC_UP      , KC_END    , KC_INSERT  , _______,
_______, KC_LCTRL   , KC_LALT   , KC_LGUI    , KC_LSHIFT   , C_1PASS,                        KC_PGDOWN, KC_LEFT     , KC_DOWN    , KC_RIGHT  , KC_CAPSLOCK, _______,
_______, KC_MAC_UNDO, KC_MAC_CUT, KC_MAC_COPY, KC_MAC_PASTE, C_REDO , _______,      _______, C_REDO   , KC_MAC_PASTE, KC_MAC_COPY, KC_MAC_CUT, KC_MAC_UNDO, _______,
_______, _______    , _______   , _______    , XXXXXXX     ,                                            KC_DELETE   , _______    , _______   , _______    , _______,

                                                             XXXXXXX , XXXXXXX,      _______, _______  ,
                                                                       _______,      _______,
                                               _______     , XXXXXXX , XXXXXXX,      _______, KC_ENTER , KC_BSPACE
),

[MOUS] = LAYOUT_ergodox_pretty(
_______, _______ , _______, _______, _______  , _______, _______,      _______, _______      , _______      , _______    , _______       , _______    , _______,
_______, XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX  , XXXXXXX, _______,      _______, KC_MS_WH_UP  , KC_MS_WH_LEFT, KC_MS_UP   , KC_MS_WH_RIGHT, XXXXXXX    , _______,
_______, KC_LCTRL, KC_LALT, KC_LGUI, KC_LSHIFT, XXXXXXX,                        KC_MS_WH_DOWN, KC_MS_LEFT   , KC_MS_DOWN , KC_MS_RIGHT   , XXXXXXX    , _______,
_______, XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX  , XXXXXXX, _______,      _______, C_REDO       , KC_MAC_PASTE , KC_MAC_COPY, KC_MAC_CUT    , KC_MAC_UNDO, _______,
_______, _______ , _______, _______, _______  ,                                                KC_MS_BTN2   , _______    , _______       , _______    , _______,

                                                XXXXXXX, XXXXXXX,      _______, _______      ,
                                                         _______,      _______,
                                     XXXXXXX  , _______, XXXXXXX,      _______, KC_MS_BTN1   , KC_MS_BTN3
),

[MDIA] = LAYOUT_ergodox_pretty(
_______, _______ , _______    , _______, _______  , _______ , _______,      _______, _______           , _______            , _______          , _______        , _______            , _______,
_______, RESET   , WEBUSB_PAIR, XXXXXXX, C_MCR_1P , C_MCR_2P, _______,      _______, RGB_TOG           , KC_BRIGHTNESS_UP   , RGB_HUI          , RGB_SAI        , RGB_VAI            , _______,
_______, KC_LCTRL, KC_LALT    , KC_LGUI, KC_LSHIFT, C_MCR_ST,                        TOGGLE_LAYER_COLOR, KC_MEDIA_PREV_TRACK, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_MEDIA_NEXT_TRACK, _______,
_______, VRSN    , XXXXXXX    , XXXXXXX, C_MCR_1R , C_MCR_2R, _______,      _______, RGB_MOD           , KC_BRIGHTNESS_DOWN , RGB_HUD          , RGB_SAD        , RGB_VAD            , _______,
_______, _______ , _______    , _______, _______  ,                                                      KC_AUDIO_MUTE      , _______          , _______        , _______            , _______,

                                                    XXXXXXX, XXXXXXX,      _______, _______           ,
                                                             _______,      _______,
                                         XXXXXXX  , XXXXXXX, XXXXXXX,      _______, KC_MEDIA_STOP     , KC_MEDIA_PLAY_PAUSE
),

[NUMB] = LAYOUT_ergodox_pretty(
_______, _______    , _______, _______, _______, _______    , _______,      _______, _______, _______  , _______ , _______, _______ , _______,
_______, KC_LBRACKET, KC_7   , KC_8   , KC_9   , KC_RBRACKET, _______,      _______, XXXXXXX, KC_HYPR  , KC_MEH  , XXXXXXX, XXXXXXX , _______,
_______, KC_SCOLON  , KC_4   , KC_5   , KC_6   , KC_EQUAL   ,                        XXXXXXX, KC_RSHIFT, KC_RGUI , KC_RALT, KC_RCTRL, _______,
_______, KC_GRAVE   , KC_1   , KC_2   , KC_3   , KC_BSLASH  , _______,      _______, XXXXXXX, XXXXXXX  , KC_COMMA, KC_DOT , KC_SLASH, _______,
_______, _______    , _______, _______, KC_0,                                                 XXXXXXX  , _______ , _______, _______ , _______,

                                                 XXXXXXX    , XXXXXXX,      _______, _______,
                                                              _______,      _______,
                                        _______, KC_MINUS   , XXXXXXX,      _______, XXXXXXX, _______
),

[CODE] = LAYOUT_ergodox_pretty(
_______, _______  , _______ , _______, _______ , _______ , _______,      _______, _______ , _______    , _______    , _______  , _______ , _______,
_______, KC_SCOLON, KC_PLUS , KC_LABK, KC_RABK , KC_PIPE , _______,      _______, KC_QUOTE, KC_RBRACKET, KC_LBRACKET, KC_ASTR  , KC_TILD , _______,
_______, KC_COLN  , KC_MINUS, KC_LPRN, KC_RPRN , KC_GRAVE,                        KC_DQUO , KC_RCBR    , KC_LCBR    , KC_SLASH , KC_COMMA, _______,
_______, KC_AT    , KC_UNDS , KC_DLR , KC_EXLM , KC_PERC , _______,      _______, KC_AMPR , KC_QUES    , KC_EQUAL   , KC_BSLASH, KC_CIRC , _______,
_______, _______  , _______ , _______, KC_HASH ,                                            XXXXXXX    , _______    , _______  , _______ , _______,

                                                 XXXXXXX , XXXXXXX,      _______, _______ ,
                                                           _______,      _______,
                                       _______ , KC_DOT  , XXXXXXX,      _______, _______ , XXXXXXX
),

[FUNC] = LAYOUT_ergodox_pretty(
_______, _______, _______, _______, _______  , _______, _______,      _______, _______, _______  , _______, _______, _______ , _______,
_______, KC_F12 , KC_F7  , KC_F8  , KC_F9    , XXXXXXX, _______,      _______, XXXXXXX, XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX , _______,
_______, KC_F11 , KC_F4  , KC_F5  , KC_F6    , XXXXXXX,                        XXXXXXX, KC_RSHIFT, KC_RGUI, KC_LALT, KC_RCTRL, _______,
_______, KC_F10 , KC_F1  , KC_F2  , KC_F3    , XXXXXXX, _______,      _______, XXXXXXX, XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX , _______,
_______, _______, _______, _______, KC_ESCAPE,                                          _______  , _______, _______, _______ , _______,

                                               XXXXXXX, XXXXXXX,      _______, _______,
                                                        _______,      _______,
                                    KC_SPACE , KC_TAB , XXXXXXX,      _______, XXXXXXX, XXXXXXX
),

[SPAN] = LAYOUT_ergodox_pretty(
_______, _______, _______, _______   , _______   , _______   , _______,      _______, _______   , _______    , _______    , _______, _______, _______,
_______, XXXXXXX, XXXXXXX, ST_MACRO_0, ST_MACRO_1, _______   , _______,      _______, XXXXXXX   , ST_MACRO_7 , ST_MACRO_8 , XXXXXXX, XXXXXXX, _______,
_______, XXXXXXX, XXXXXXX, ST_MACRO_2, ST_MACRO_3, ST_MACRO_4,                        ST_MACRO_9, ST_MACRO_10, ST_MACRO_11, XXXXXXX, XXXXXXX, _______,
_______, XXXXXXX, XXXXXXX, ST_MACRO_5, ST_MACRO_6, _______   , _______,      _______, XXXXXXX   , ST_MACRO_12, ST_MACRO_13, XXXXXXX, XXXXXXX, _______,
_______, _______, _______, _______   , XXXXXXX   ,                                                XXXXXXX    , _______    , _______, _______, _______,

                                             XXXXXXX, XXXXXXX,      _______, _______,
                                                      _______,      _______,
                                    XXXXXXX, XXXXXXX, XXXXXXX,      _______, XXXXXXX, XXXXXXX
)
};

// clang-format on

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {8,255,255}, {0,0,0}, {0,0,0}, {0,0,0} },

    [1] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {0,0,0}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {163,218,204}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [2] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {122,255,255}, {122,255,255}, {122,255,255}, {122,255,255}, {0,0,0}, {122,255,255}, {122,255,255}, {122,255,255}, {122,255,255}, {0,0,0}, {122,255,255}, {122,255,255}, {122,255,255}, {122,255,255}, {122,255,255}, {122,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {122,255,255}, {122,255,255}, {122,255,255}, {122,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [3] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {119,244,100}, {41,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {41,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [4] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,245,245}, {0,245,245}, {0,0,0}, {0,0,0}, {0,0,0}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,0,0}, {0,0,0}, {0,245,245}, {0,245,245}, {0,245,245}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,0,0}, {0,0,0}, {0,0,0} },

    [5] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {74,255,255}, {0,0,0}, {0,0,0}, {0,0,0} },

    [6] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {211,218,204}, {211,218,204}, {211,218,204}, {211,218,204}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {211,218,204}, {211,218,204}, {211,218,204}, {211,218,204}, {0,0,0}, {211,218,204}, {211,218,204}, {211,218,204}, {211,218,204}, {0,0,0}, {211,218,204}, {211,218,204}, {211,218,204}, {211,218,204}, {211,218,204}, {0,0,0}, {0,0,0}, {0,0,0} },

    [7] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {45,255,255}, {45,255,255}, {0,0,0}, {0,0,0}, {45,255,255}, {45,255,255}, {45,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {45,255,255}, {45,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {45,255,255}, {45,255,255}, {0,0,0}, {0,0,0}, {45,255,255}, {45,255,255}, {45,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {45,255,255}, {45,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
    case 5:
      set_layer_color(5);
      break;
    case 6:
      set_layer_color(6);
      break;
    case 7:
      set_layer_color(7);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ST_MACRO_0:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_E)) SS_DELAY(100) SS_TAP(X_A));
            }
            break;
        case ST_MACRO_1:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_E)) SS_DELAY(100) SS_TAP(X_E));
            }
            break;
        case ST_MACRO_2:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_E)) SS_DELAY(100) SS_TAP(X_I));
            }
            break;
        case ST_MACRO_3:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_E)) SS_DELAY(100) SS_TAP(X_O));
            }
            break;
        case ST_MACRO_4:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_N)) SS_DELAY(100) SS_TAP(X_N));
            }
            break;
        case ST_MACRO_5:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_U)) SS_DELAY(100) SS_TAP(X_U));
            }
            break;
        case ST_MACRO_6:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_E)) SS_DELAY(100) SS_TAP(X_U));
            }
            break;
        case ST_MACRO_7:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_E)) SS_DELAY(100) SS_RSFT(SS_TAP(X_E)));
            }
            break;
        case ST_MACRO_8:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_E)) SS_DELAY(100) SS_RSFT(SS_TAP(X_A)));
            }
            break;
        case ST_MACRO_9:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_N)) SS_DELAY(100) SS_LSFT(SS_TAP(X_N)));
            }
            break;
        case ST_MACRO_10:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_E)) SS_DELAY(100) SS_LSFT(SS_TAP(X_O)));
            }
            break;
        case ST_MACRO_11:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_E)) SS_DELAY(100) SS_LSFT(SS_TAP(X_I)));
            }
            break;
        case ST_MACRO_12:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_E)) SS_DELAY(100) SS_LSFT(SS_TAP(X_U)));
            }
            break;
        case ST_MACRO_13:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_U)) SS_DELAY(100) SS_LSFT(SS_TAP(X_U)));
            }
            break;
        case RGB_SLD:
            if (record->event.pressed) {
                rgblight_mode(1);
            }
          return false;
        case VRSN:
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                return false;
            }
    }

    return true;
}


void matrix_scan_user() {
    led_t led_state = host_keyboard_led_state();
    if (led_state.caps_lock) {
        ergodox_right_led_3_on();
    } else {
        uint8_t layer = get_highest_layer(layer_state);
        if (layer != 3 && layer != 5 && layer != 6 && layer != 7) {
            ergodox_right_led_3_off();
        }
    }

    if (is_caps_word_on()) {
        ergodox_right_led_2_on();
    } else {
        uint8_t layer = get_highest_layer(layer_state);
        if (layer != 2 && layer != 4 && layer != 6 && layer != 7) {
            ergodox_right_led_2_off();
        }        
    }
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    raw_hid_send(data, length);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

    return state;
};
