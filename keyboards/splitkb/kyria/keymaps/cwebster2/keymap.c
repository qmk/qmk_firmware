/* Copyright 2020 Casey Webster <casey@e1337.dev>
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
//#include "raw_hid.h"
#define RAW_EPSIZE 8
#include <stdio.h>

#include "cwebster2.h"

#ifdef WPM_ENABLE
char wpm_str[10];
uint16_t wpm_graph_timer = 0;
#endif

#ifdef COMBO_ENABLE
enum combos {
    ZX_COPY,
    CV_PASTE,
    PB_PARENS,
    FP_CURLY,
    DV_SQUARE
};

const uint16_t PROGMEM copy_combo[]  = { KC_Z, KC_X, COMBO_END };
const uint16_t PROGMEM paste_combo[] = { KC_C, KC_D, COMBO_END };
const uint16_t PROGMEM curly_combo[] = { KC_F, KC_P, COMBO_END };
const uint16_t PROGMEM parens_combo[] =  { KC_P, KC_B, COMBO_END };
const uint16_t PROGMEM square_combo[] = { KC_D, KC_V, COMBO_END };

combo_t key_combos[COMBO_COUNT] = {
    [ZX_COPY]  = COMBO(copy_combo, LCTL_T(KC_C)),
    [CV_PASTE] = COMBO(paste_combo, LCTL_T(KC_V)),
    [PB_PARENS] = COMBO(parens_combo, KC_LPRN),
    [FP_CURLY] = COMBO(curly_combo, KC_LCBR),
    [DV_SQUARE] = COMBO(square_combo, KC_LBRC)
};
#endif

#define LAYOUT_kyria_base( \
    L01, L02, L03, L04, L05, R05, R04, R03, R02, R01, \
    L11, L12, L13, L14, L15, R15, R14, R13, R12, R11, \
    L21, L22, L23, L24, L25, R25, R24, R23, R22, R21,  \
              L33, L34, L35, R35, R34, R33 \
    ) \
    LAYOUT_kyria_wrapper ( \
    KC_GRV,   L01, L02, L03, L04, L05,                                      R05, R04, R03, R02, R01, KC_BSLS, \
    KC_CTLBS, L11, L12, L13, L14, L15,                                      R15, R14, R13, R12, R11, KC_QUOT, \
    KC_EQL,   L21, L22, L23, L24, L25, KC_LCCL, KC_LGUI, KC_ALTCL, KC_LSFT, R25, R24, R23, R22, R21, KC_MINS, \
         SCMD_T(KC_LBRC), C_S_T(KC_MINS), L33, L34, L35, R35, R34, R33, TO(_GAME), KC_PSCR \
    )
#define LAYOUT_kyria_base_wrapper(...)       LAYOUT_kyria_base(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 */
    [_QWERTY] = LAYOUT_kyria_base_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
      _______QWERTY_L1______,                 _______QWERTY_R1______,
      _______QWERTY_L2______,                 _______QWERTY_R2______,
      _______QWERTY_L3______,                 _______QWERTY_R3______,
              _______NAKED_L___T____,  _______THUMBS_R_______
 /*           `---------------------'  `---------------------' */
    ),
    [_COLEMAK] = LAYOUT_kyria_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
      KC_GRV,   _______COLEMAK_L1_____,                                                        _______COLEMAK_R1_____, KC_BSLS,
      KC_CTLBS, _______COLEMAK_L2_____,                                                        _______COLEMAK_R2_____, KC_SCLN,
      KC_EQL,   _______COLEMAK_L3_____, KC_LCCL, KC_LGUI,                   KC_ALTCL, KC_LSFT, _______COLEMAK_R3_____, KC_MINS,
       SCMD_T(KC_LBRC), C_S_T(KC_MINS), _______THUMBS_L_______,   _______THUMBS_R_______, TO(_QWERTY), KC_PSCR
 /*           `---------------------'  `---------------------' */
    ),
 // GAME layout -- qwerty without homerow mods
    [_GAME] = LAYOUT_kyria_wrapper(
 /* ,-------------------------------------------.                              ,-------------------------------------------. */
    KC_GRV,   _______COLEMAK_L1_____,                                     _______COLEMAK_R1_____, KC_BSLS,
    KC_CTLBS, KC_A, KC_R, KC_S, KC_T, KC_G,                               KC_M, KC_N, KC_E, KC_I, KC_O, KC_SCLN,
    KC_LSFT,   _______COLEMAK_L3_____, KC_LCCL, KC_LALT,                   KC_ALTCL, KC_LSFT, _______COLEMAK_R3_____, KC_MINS,
       KC_EQL, MO(_NUM), _______NAKED_L___T____,   _______THUMBS_R_______, TO(_COLEMAK), KC_F12
 /*                        `----------------------------------'  `----------------------------------' */
    ),
    [_FN] = LAYOUT_kyria_base_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
      _______FN_______L1____,                 _______INACTIVE_R1____,
      _______FN_______L2____,                 _______INACTIVE_R2____,
      _______FN_______L3____,                 _______NAV______R2____,
              _______FN________T____,  _______INACTIVE__T____
 /*           `---------------------'  `---------------------' */
      ),
    [_SYMBOLS] = LAYOUT_kyria_base_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
      _______SYM______L1____,                 _______INACTIVE_R1____,
      _______SYM______L2____,                 _______INACTIVE_R2____,
      _______SYM______L3____,                 _______INACTIVE_R3____,
              _______SYM_______T____,  _______INACTIVE__T____
 /*           `---------------------'  `---------------------' */
    ),
    [_NUM] = LAYOUT_kyria_base_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
      _______NUM______L1____,                 _______INACTIVE_R1____,
      _______NUM______L2____,                 _______INACTIVE_R2____,
      _______NUM______L3____,                 _______INACTIVE_R3____,
              _______NUM_______T____,  _______INACTIVE__T____
 /*           `---------------------'  `---------------------' */
      ),
    [_NAV] = LAYOUT_kyria_base_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
      _______INACTIVE_L1____,                 _______NAV______R1____,
      _______INACTIVE_L2____,                 _______NAV______R2____,
      _______INACTIVE_L3____,                 _______NAV______R3____,
              _______INACTIVE__T____,  _______NAV_______T____
 /*           `---------------------'  `---------------------' */
      ),
    [_MOUSE] = LAYOUT_kyria_base_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
      _______INACTIVE_L1____,                 _______MOUSE____R1____,
      _______INACTIVE_L2____,                 _______MOUSE____R2____,
      _______INACTIVE_L3____,                 _______MOUSE____R3____,
              _______INACTIVE__T____,  _______MOUSE_____T____
 /*           `---------------------'  `---------------------' */
      ),
    [_MEDIA] = LAYOUT_kyria_base_wrapper(
 /* ,-----------------------.                 ,-----------------------. */
      _______INACTIVE_L1____,                 _______MEDIA____R1____,
      _______INACTIVE_L2____,                 _______MEDIA____R2____,
      _______INACTIVE_L3____,                 _______MEDIA____R3____,
              _______INACTIVE__T____,  _______MEDIA_____T____
 /*           `---------------------'  `---------------------' */
     ),
};

#ifdef RAW_ENABLE
static void send_layer_via_hid(int layer) {
    uint8_t data[RAW_EPSIZE];
    data[0] = 1;
    data[1] = layer;
    raw_hid_send(data, sizeof(data));
    return;
}
#endif


#ifdef RGBLIGHT_LAYERS
const rgblight_segment_t PROGMEM my_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_RED} );
const rgblight_segment_t PROGMEM my_colemak_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_BLUE} );
const rgblight_segment_t PROGMEM my_game_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_RED} );
const rgblight_segment_t PROGMEM my_fn_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_PINK} );
const rgblight_segment_t PROGMEM my_symbols_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_GREEN} );
const rgblight_segment_t PROGMEM my_num_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_CORAL} );
const rgblight_segment_t PROGMEM my_nav_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_GOLDENROD} );
const rgblight_segment_t PROGMEM my_mouse_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_TURQUOISE} );
const rgblight_segment_t PROGMEM my_media_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HSV_MAGENTA} );

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_RED},
    {7, 1, HSV_RED},
    {10, 3, HSV_RED},
    {17, 1, HSV_RED}
);

const rgblight_segment_t PROGMEM my_shift_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 1, HSV_RED},
    {13, 1, HSV_RED}
);

const rgblight_segment_t PROGMEM my_ctrl_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 1, HSV_ORANGE},
    {14, 1, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM my_alt_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 1, HSV_GOLD},
    {15, 1, HSV_GOLD}
);

const rgblight_segment_t PROGMEM my_gui_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 1, HSV_SPRINGGREEN},
    {19, 1, HSV_SPRINGGREEN}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_colemak_layer,
    my_qwerty_layer,
    my_game_layer,
    my_fn_layer,
    my_symbols_layer,
    my_num_layer,
    my_nav_layer,
    my_mouse_layer,
    my_media_layer,
    my_capslock_layer,
    my_shift_layer,
    my_ctrl_layer,
    my_alt_layer,
    my_gui_layer
);

void matrix_scan_keymap(void) {
    uint8_t mods = mod_config(get_mods());
    rgblight_set_layer_state(10, mods & MOD_MASK_SHIFT);
    rgblight_set_layer_state(11, mods & MOD_MASK_CTRL);
    rgblight_set_layer_state(12, mods & MOD_MASK_ALT);
    rgblight_set_layer_state(13, mods & MOD_MASK_GUI);
}
#endif

void keyboard_post_init_user(void) {
    rgblight_sethsv_noeeprom(HSV_BLUE);
    keyboard_post_init_rgb();
#ifdef RGBLIGHT_LAYERS
    rgblight_layers = my_rgb_layers;
#else
    rgblight_sethsv_noeeprom(HSV_BLUE);
#endif
    /*debug_enable=true;*/
    /*debug_matrix=true;*/
}

//todo https://github.com/qmk/qmk_firmware/blob/debdc6379c7a72815df1f53e3406479381d243af/keyboards/crkbd/keymaps/soundmonster/keymap.c RGBRST

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_LAYERS
    for (int i = _QWERTY; i < __LAST; i++) {
        rgblight_set_layer_state(i, layer_state_cmp(state, i));
    }
#  ifdef RAW_ENABLE
    send_layer_via_hid(state);
#  endif
#endif
    return state;
}

#ifdef RGBLIGHT_LAYERS
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(9, led_state.caps_lock);
    return true;
}
#endif

#ifdef OLED_ENABLE
void suspend_power_down_user() {
    oled_clear();
    oled_off();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_logo(void) {
  /*static const char PROGMEM qmk_logo[] = {*/
  /*  0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,*/
  /*  0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,*/
  /*  0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};*/

    static const char PROGMEM logo[] = {
        // canvas is 128x64.  need 16 padding
        // 80x32
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x60, 0xe0, 0xf0, 0xfe, 0xfe, 0xf0, 0x60, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x0c, 0x1c, 0x3c, 0x7c, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x7c, 0xf8, 0xe0, 0x60, 0x20, 0x10, 0x10, 0x0c, 0x0f, 0x09, 0x08, 0x00, 0x09, 0x9b, 0x5c, 0x50, 0x10, 0x20, 0x40, 0xe0, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x78, 0x38, 0x38, 0x10, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x17, 0x15, 0x3d, 0xef, 0xaf, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x10, 0x00, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x40, 0xa0, 0xbf, 0xff, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(logo, sizeof(logo));

    oled_advance_page(false);
    oled_advance_page(false);
    oled_advance_page(false);
    oled_advance_page(false);
//  oled_write_P(qmk_logo, false);

#ifdef COMBO_ENABLE
    oled_write_P(PSTR("Combos enabled: "), false);
    if (is_combo_enabled()) {
        oled_write_P(PSTR("Yes\n"), false);
    } else {
        oled_write_P(PSTR("No\n"), false);
    }
#endif

#ifdef SPLIT_MODS_ENABLE
    uint8_t mods = get_mods() | get_weak_mods();
    oled_write_P((mods & MOD_MASK_GUI) ? PSTR("GUI ") : PSTR("    "), false);
    oled_write_P((mods & MOD_MASK_ALT) ? PSTR("ALT ") : PSTR("    "), false);
    oled_write_P((mods & MOD_MASK_CTRL) ? PSTR("CTRL ") : PSTR("     "), false);
    oled_write_P((mods & MOD_MASK_SHIFT) ? PSTR("SHFT ") : PSTR("     "), false);
    oled_write_P(PSTR("\n"), false);

#endif

#ifdef WPM_ENABLE
    // Write WPM
    uint8_t n = get_current_wpm();
    wpm_str[3] = '\0';
    wpm_str[2] = '0' + n % 10;
    wpm_str[1] = '0' + (n /= 10) % 10;
    wpm_str[0] = '0' + n / 10 ;
    //oled_write_P(PSTR("\n"), false);
    oled_write_P(PSTR("       WPM: "), false);
    oled_write(wpm_str, false);
#endif
}


static void render_status(void) {
    static bool isColemak = false;
    // QMK Logo and version information
    oled_write_P(PSTR("Kyria rev1.3\n\n"), false);

    oled_write_P(isColemak ? PSTR("COLEMAK   ") : PSTR("QWERTY   "), false);

    // Host Keyboard Layer Status
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Game\n"), false);
            isColemak = false;
            break;
        case _SYMBOLS:
            oled_write_P(PSTR("Shifted Sym\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("Numbers\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("Fn\n"), false);
            break;
        case _GAME:
            oled_write_P(PSTR("Game\n"), false);
            isColemak = true;
            break;
        case _COLEMAK:
            oled_write_P(PSTR("Default\n"), false);
            isColemak = true;
            break;
        case _MEDIA:
            oled_write_P(PSTR("Media keys\n"), false);
            break;
        case _MOUSE:
            oled_write_P(PSTR("Mouse keys\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    uint8_t mods = get_mods() | get_weak_mods();
    oled_write_P(PSTR("\n"), false);
    oled_write_P((mods & MOD_MASK_GUI) ? PSTR("GUI ") : PSTR("    "), false);
    oled_write_P((mods & MOD_MASK_ALT) ? PSTR("ALT ") : PSTR("    "), false);
    oled_write_P((mods & MOD_MASK_CTRL) ? PSTR("CTRL ") : PSTR("     "), false);
    oled_write_P((mods & MOD_MASK_SHIFT) ? PSTR("SHFT ") : PSTR("     "), false);
    oled_write_P(PSTR("\n"), false);

#define I3MASK MOD_BIT(KC_LGUI)
#define I3SMASK (MOD_BIT(KC_LGUI) | MOD_BIT(KC_LSFT))
#define KMASK (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT))

    oled_write_P((mods == I3MASK) ? PSTR("I3     ") : (mods == I3SMASK) ? PSTR("I3-SFT ") : PSTR("       "), false);
    oled_write_P((mods == KMASK) ? PSTR("KITTY ") : PSTR("      "), false);
    oled_write_P(PSTR("\n"), false);

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);

}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();
    }
    return false;
}
#endif


#ifdef RAW_ENABLE
void raw_hid_receive(uint8_t *data, uint8_t length) {
    // messages from host
    // add ability to set color
    raw_hid_send(data, length);
}
#endif
