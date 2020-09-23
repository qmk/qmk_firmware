/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include "raw_hid.h"
#include <stdio.h>

char wpm_str[10];
uint16_t wpm_graph_timer = 0;

#ifdef COMBO_ENABLE
enum combos {
    ZX_COPY,
    CV_PASTE
};

const uint16_t PROGMEM copy_combo[]  = { KC_Z, KC_X, COMBO_END };
const uint16_t PROGMEM paste_combo[] = { KC_C, KC_V, COMBO_END };

combo_t key_combos[COMBO_COUNT] = {
    [ZX_COPY]  = COMBO(copy_combo, LCTL_T(KC_C)),
    [CV_PASTE] = COMBO(paste_combo, LCTL_T(KC_V))
};
#endif

enum custom_keycodes {
    KC_LCCL = SAFE_RANGE
};

enum layers {
    _QWERTY = 0,
    _GAME,
    _FN,
    _SYMBOLS,
    _NUM,
    _NAV,
    _MOUSE,
    _MEDIA
};

// shortcuts for certain keys to use LAYOUT_kc()
#define KC_TO(a)  TO(a)
#define KC_DF(a)  DF(a)
#define KC_RAISE  TT(_RAISE)
#define KC_LOWER  TT(_LOWER)
#define KC_KITTY(a)  C_S_T(KC_##a)
#define KC_I3(a)  SCMD_T(KC_##a)
#define KC_GUIBS  MT(MOD_LGUI, KC_BSPC)
#define KC_ALTCLN MT(MOD_LALT, S(KC_SCLN)) // this doesnt work. need to write a custom keycode to handle it
#define KC_RTOG   RGB_TOG
#define KC_RSAI   RGB_SAI
#define KC_RHUI   RGB_HUI
#define KC_RVAI   RGB_VAI
#define KC_RMOD   RGB_MOD
#define KC_RSAD   RGB_SAD
#define KC_RHUD   RGB_HUD
#define KC_RVAD   RGB_VAD
#define KC_RRMD   RGB_RMOD
#define KC_TT(m,a)  m##_T(KC_##a)
#define KC_CTLESC MT(MOD_LCTL, KC_ESC)
#define KC_CTLTAB MT(MOD_LCTL, KC_TAB)
#define KC_FN(a) LT(_FN, KC_##a)
#define KC_SYM(a) LT(_SYMBOLS, KC_##a)
#define KC_NUM(a) LT(_NUM, KC_##a)
#define KC_NAV(a) LT(_NAV, KC_##a)
#define KC_MED(a) LT(_MEDIA, KC_##a)
#define KC_MSE(a) LT(_MOUSE, KC_##a)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 */
    [_QWERTY] = LAYOUT_kc(
 /* ,-------------------------------------------------------------------.                                         ,--------------------------------------------------------------------. */
      GRV,         Q,          W,          E,          R,         T,                                                   Y,        U,          I,          O,            P,        BSLS,
 /* |--------+-----------+-----------+-----------+-----------+----------|                                         |---------+-----------+-----------+-----------+-------------+--------| */
      CTLTAB, TT(LGUI,A), TT(LALT,S), TT(LCTL,D), TT(LSFT,F),     G,                                                   H,    TT(RSFT,J), TT(RCTL,K), TT(RALT,L), TT(RGUI,SCLN),  QUOT,
 /* |--------+-----------+-----------+-----------+-----------+----------+---------+--------.  ,---------+---------+---------+-----------+-----------+-----------+-------------+--------| */
      EQL,         Z,          X,          C,          V,         B,       LCCL,     LGUI,       RALT,     LSFT,       N,        M,         COMM,       DOT,         SLSH,       MINS,
 /* `--------------------------------+-----------+-----------+----------+---------+--------|  |---------+---------+---------+---------+-------------+----------------------------------' */
                                       I3(LBRC),  KITTY(MINS), MSE(TAB), NAV(SPC), MED(ESC),    FN(ENT), NUM(BSPC), SYM(DEL), TO(_GAME),     PSCR
 /*                                  `-----------------------------------------------------'  `-----------------------------------------------------' */
    ),
    // symbols and mouse
    [_SYMBOLS] = LAYOUT_kc(
 /* ,-------------------------------------------.                              ,-------------------------------------------. */
       TRNS,   RCBR,  AMPR,  ASTR,  LPRN,  LCBR,                                 TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 /* |--------+------+------+------+------+------|                              |------+------+------+------+------+--------| */
       TRNS,   COLN,   DLR,  PERC,  CIRC,  PLUS,                                 TRNS,  LSFT,  LCTL,  LALT,  LGUI,  TRNS,
 /* |--------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+--------| */
       TRNS,   TILD,  EXLM,  AT,    HASH,  PIPE,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,   TRNS, RALT,  TRNS,  TRNS,
 /* `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------' */
                             TRNS,  TRNS,  LPRN,  RPRN,  UNDS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS
 /*                        `----------------------------------'  `----------------------------------' */
    ),
    [_NUM] = LAYOUT_kc(
 /* ,-------------------------------------------.                              ,-------------------------------------------. */
       TRNS,   RBRC,   7,     8,     9,    LBRC,                                 TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 /* |--------+------+------+------+------+------|                              |------+------+------+------+------+--------| */
       TRNS,   SCLN,   4,     5,     6,    EQL,                                  TRNS,  LSFT,  LCTL,  LALT,  LGUI,  TRNS,
 /* |--------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+--------| */
       TRNS,   GRV,    1,     2,     3,    BSLS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  RALT,  TRNS,  TRNS,
 /* `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------' */
                             TRNS,  TRNS,  DOT,    0,    MINS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS
 /*                        `----------------------------------'  `----------------------------------' */
      ),
    // media and fn
    [_FN] = LAYOUT_kc(
 /* ,-------------------------------------------.                              ,-------------------------------------------. */
       TRNS,   F12,    F7,    F8,    F9,  SYSREQ,                                TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 /* |--------+------+------+------+------+------|                              |------+------+------+------+------+--------| */
       TRNS,   F11,    F4,    F5,    F6,  SLCK,                                  TRNS,  LSFT,  LCTL,  LALT,  LGUI,  TRNS,
 /* |--------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+--------| */
       TRNS,   F10,    F1,    F2,    F3,  PAUSE,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  RALT,  TRNS,  TRNS,
 /* `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------' */
                             TRNS,  TRNS,  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS
 /*                        `----------------------------------'  `----------------------------------' */
      ),
    [_NAV] = LAYOUT_kc(
 /* ,-------------------------------------------.                              ,-------------------------------------------. */
       TRNS,   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                                 AGIN,  UNDO,  CUT,   COPY,  PSTE,  TRNS,
 /* |--------+------+------+------+------+------|                              |------+------+------+------+------+--------| */
       TRNS,   LGUI,  LALT,  LCTL,  LSFT,  TRNS,                                 LEFT,  DOWN,   UP,   RGHT,  CAPS,  TRNS,
 /* |--------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+--------| */
       TRNS,   TRNS,  RALT,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  HOME,  PGDN,  PGUP,  END,   INS,   TRNS,
 /* `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------' */
                             TRNS,  TRNS,  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS
 /*                        `----------------------------------'  `----------------------------------' */
      ),
    [_MOUSE] = LAYOUT_kc(
 /* ,-------------------------------------------.                              ,-------------------------------------------. */
       TRNS,   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                                 TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 /* |--------+------+------+------+------+------|                              |------+------+------+------+------+--------| */
       TRNS,   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                                 TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 /* |--------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+--------| */
       TRNS,   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 /* `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------' */
                             TRNS,  TRNS,  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS
 /*                        `----------------------------------'  `----------------------------------'                        */
      ),
    [_MEDIA] = LAYOUT_kc(
 /* ,-------------------------------------------.                              ,-------------------------------------------. */
       TRNS,   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                                 TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 /* |--------+------+------+------+------+------|                              |------+------+------+------+------+--------| */
       TRNS,   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                                 TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 /* |--------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+--------| */
       TRNS,   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 /* `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------' */
                             TRNS,  TRNS,  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS
 /*                        `----------------------------------'  `----------------------------------'                        */
     ),
 // GAME layout -- qwerty without homerow mods
    [_GAME] = LAYOUT_kc(
 /* ,-------------------------------------------.                              ,-------------------------------------------. */
      GRV,      Q,     W,     E,     R,    T,                                     Y,     U,     I,     O,     P,    BSLS,
 /* |--------+------+------+------+------+------|                              |------+------+------+------+------+--------| */
      TAB,      A,     S,     D,     F,    G,                                     H,     J,     K,     L,    SCLN,  QUOT,
 /* |--------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+--------| */
      LSPO,     Z,     X,     C,     V,    B,     LCTL,  LGUI,     RALT,  RSFT,   N,     M,    COMM,  DOT,   SLSH,  RSPC,
 /* `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------' */
           I3(LBRC),  KITTY(MINS), MSE(TAB), NAV(SPC), MED(ESC), FN(ENT), NUM(BSPC), SYM(DEL), TO(_QWERTY),     PSCR
 /*                        `----------------------------------'  `----------------------------------' */
    ),
 //  * Layer template
 //
 //    [_LAYERINDEX] = LAYOUT_kc(
 // ,-------------------------------------------.                              ,-------------------------------------------.
 //    TRNS,   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                                 TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 // |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 //    TRNS,   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                                 TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 // |--------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+--------|
 //    TRNS,   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 // `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 //                          TRNS,  TRNS,  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS
 //                        `----------------------------------'  `----------------------------------'
 //    ),
};

static void send_layer_via_hid(char *layer) {
    //raw_hid_send((uint8_t*)layer, sizeof(layer));
    return;
}

/* RGB LIGHT LAYERS
const rgblight_segment_t PROGMEM my_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_AZURE}
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_RED}
);

const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_TURQUOISE}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_PURPLE}
);
*/

void keyboard_post_init_user(void) {
    rgblight_sethsv_noeeprom(HSV_BLUE);
}


layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _QWERTY:
            send_layer_via_hid("Default");
            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        case _SYMBOLS:
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case _NUM:
            rgblight_sethsv_noeeprom(HSV_CORAL);
            break;
        case _NAV:
            rgblight_sethsv_noeeprom(HSV_GOLDENROD);
            break;
        case _FN:
            rgblight_sethsv_noeeprom(HSV_PINK);
            break;
        case _MEDIA:
            rgblight_sethsv_noeeprom(HSV_MAGENTA);
            break;
        case _MOUSE:
            //send_layer_via_hid("Raise");
            rgblight_sethsv_noeeprom(HSV_TURQUOISE);
            break;
        case _GAME:
            /*send_layer_via_hid("Game");*/
            rgblight_sethsv_noeeprom(HSV_RED);
            break;
        default:
            send_layer_via_hid("Undefined");
    }
    return state;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_logo(void) {
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

#ifdef COMBO_ENABLE
    oled_write_P(PSTR("Combos enabled: "), false);
    if (is_combo_enabled()) {
        oled_write_P(PSTR("Yes\n"), false);
    } else {
        oled_write_P(PSTR("No\n"), false);
    }
#endif

    uint8_t mods = get_mods() | get_weak_mods();
    oled_write_P((mods & MOD_MASK_GUI) ? PSTR("GUI ") : PSTR("    "), false);
    oled_write_P((mods & MOD_MASK_ALT) ? PSTR("ALT ") : PSTR("    "), false);
    oled_write_P((mods & MOD_MASK_CTRL) ? PSTR("CTRL ") : PSTR("     "), false);
    oled_write_P((mods & MOD_MASK_SHIFT) ? PSTR("SHFT ") : PSTR("     "), false);
    oled_write_P(PSTR("\n"), false);

#ifdef WPM_ENABLE
    // Write WPM
    sprintf(wpm_str, "WPM: %03d", get_current_wpm());
    //oled_write_P(PSTR("\n"), false);
    oled_write(wpm_str, false);
#endif
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.3\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
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
    oled_write_P((mods & MOD_MASK_GUI) ? PSTR("GUI ") : PSTR("    "), false);
    oled_write_P((mods & MOD_MASK_ALT) ? PSTR("ALT ") : PSTR("    "), false);
    oled_write_P((mods & MOD_MASK_CTRL) ? PSTR("CTRL ") : PSTR("     "), false);
    oled_write_P((mods & MOD_MASK_SHIFT) ? PSTR("SHFT ") : PSTR("     "), false);
    oled_write_P(PSTR("\n"), false);

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();
    }
}
#endif


#ifdef RAW_ENABLE
void raw_hid_receive(uint8_t *data, uint8_t length) {
    // messages from host
    // add ability to set color
    raw_hid_send(data, length);
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t my_colon_timer;

    switch (keycode) {
        case KC_LCCL:
            if (record->event.pressed) {
                my_colon_timer = timer_read();
                register_code(KC_LCTL);
            } else {
                unregister_code(KC_LCTL);
                if (timer_elapsed(my_colon_timer) < TAPPING_TERM) {
                    SEND_STRING(":");
                }
            }
            return false;
    }
    return true;
}
