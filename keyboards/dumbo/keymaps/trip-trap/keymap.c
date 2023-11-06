/* Copyright 2020 Adam Naldal <adamnaldal@gmail.com>
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
#include "keymap_danish.h"
#include <stdio.h>

enum layers {
    _QWERTY = 0,
    _COLEMAK,
    _NN,
    _MS,
    _SP
};

// Default layer switching
#define QWERT DF(_QWERTY)
#define COLEM DF(_COLEMAK)

// Layer tap codes
#define LT_SPC LT(_NN, KC_SPC)
#define LT_TAB LT(_MS, KC_TAB)
#define LT_ENT LT(_MS, KC_ENT)
#define LT_BSPC LT(_NN, KC_BSPC)

// Qwerty homerow mods
#define A_CTL LCTL_T(KC_A)
#define S_ALT LALT_T(KC_S)
#define D_GUI LGUI_T(KC_D)
#define F_SFT LSFT_T(KC_F)
#define J_SFT RSFT_T(KC_J)
#define K_GUI RGUI_T(KC_K)
#define L_ALT RALT_T(KC_L)
#define AE_CTL RCTL_T(DK_AE)

// Colemak homerow mods
#define R_ALT LALT_T(KC_R)
#define S_GUI LGUI_T(KC_S)
#define T_SFT LSFT_T(KC_T)
#define N_SFT RSFT_T(KC_N)
#define E_GUI RGUI_T(KC_E)
#define I_ALT RALT_T(KC_I)
#define O_CTL RCTL_T(KC_O)

// Navigation and numbers homerow mods
#define RGHT_SFT LSFT_T(KC_RGHT)
#define DOWN_GUI LGUI_T(KC_DOWN)
#define LEFT_ALT LALT_T(KC_LEFT)
#define N4_SFT RSFT_T(KC_4)
#define N5_GUI RGUI_T(KC_5)
#define N6_ALT RALT_T(KC_6)
#define OE_CTL RCTL_T(DK_OSTR)

// Undefined or wrong symbols (homebrew)
#define HB_LCBR S(A(KC_8))  // {
#define HB_RCBR S(A(KC_9))  // }
#define HB_LABR KC_GRV      // <
#define HB_RABR S(KC_GRV)   // >
#define HB_USD KC_NUBS      // $
#define HB_PRGF S(KC_NUBS)  // §
#define HB_AT A(KC_NUHS)    // @
#define HB_EUR S(KC_4)      // €


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 *     ,-------------------------------------------.                            ,-------------------------------------------.
 *     |        |   Q  |   W  |   E  |   R  |   T  |                            |   Y  |   U  |   I  |   O  |   P  |    Å   |
 *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
 *     |        |   A  |   S  |   D  |   F  |   G  |                            |   H  |   J  |   K  |   L  |   Æ  |    Ø   |
 *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
 *     |        |   Z  |   X  |   C  |   V  |   B  |                            |   N  |   M  | ,  ; | . :  | -  _ |        |
 *     `------------------------⫟------⫟------⫟------⫟------.         ,-----⫟------⫟------⫟------⫟-------------------------'
 *                              | MUTE | Esc  | Space|  Tab |         | Enter| Bksp | Caps| PLAY|
 *                              |(enc) |      |  _NN |  _MS |         | _MS  | _NN  |      |(enc)|
 *                              `---------------------------'         `---------------------------'
 */
    [_QWERTY] = LAYOUT_split_3x6_4(
      //,-----------------------------------------------------.                            ,-----------------------------------------------------.
          XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, DK_ARNG,
      //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
          XXXXXXX,   A_CTL,   S_ALT,   D_GUI,   F_SFT,    KC_G,                                 KC_H,   J_SFT,   K_GUI,   L_ALT,  AE_CTL, DK_OSTR,
      //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
          XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                 KC_N,    KC_M, KC_COMM,  KC_DOT, DK_MINS, XXXXXXX,
      //|--------+--------+-----------⫟--------⫟--------⫟--------⫟--------.   .--------⫟--------⫟--------⫟--------⫟-----------+--------+--------|
                                        KC_MUTE,  KC_ESC,  LT_SPC,   LT_TAB,      LT_ENT, LT_BSPC, KC_CAPS, KC_MPLY
                                    //`------------------------------------'  '------------------------------------'
    ),
/*
 * Base Layer: COLEMAK
 *
 *     ,-------------------------------------------.                            ,-------------------------------------------.
 *     |        |   Q  |   W  |   F  |   P  |   B  |                            |   J  |   L  |   U  |   Y  |   Å  |        |
 *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
 *     |        |   A  |   R  |   S  |   T  |   G  |                            |   M  |   N  |   E  |   I  |   O  |        |
 *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
 *     |        |   Z  |   X  |   C  |   D  |   V  |                            |   K  |   H  | ,  ; | . :  |   Æ  |        |
 *     `------------------------⫟------⫟------⫟------⫟------.         ,-----⫟------⫟------⫟------⫟-------------------------'
 *                              | MUTE | Esc  | Space|  Tab |         | Enter| Bksp | Caps |  PLAY|
 *                              |(enc) |      |  _NN |  _MS |         | _MS  | _NN  |      | (enc)|
 *                              `---------------------------'         `---------------------------'
 */
    [_COLEMAK] = LAYOUT_split_3x6_4(
      //,-----------------------------------------------------.                            ,-----------------------------------------------------.
          XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                                 KC_J,    KC_L,    KC_U,    KC_Y, DK_ARNG, XXXXXXX,
      //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
          XXXXXXX,   A_CTL,   R_ALT,   S_GUI,   T_SFT,    KC_G,                                 KC_M,   N_SFT,   E_GUI,   I_ALT,   O_CTL, XXXXXXX,
      //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
          XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                                 KC_K,    KC_H, KC_COMM,  KC_DOT,   DK_AE, XXXXXXX,
      //|--------+--------+-----------⫟--------⫟--------⫟--------⫟--------.   .--------⫟--------⫟--------⫟--------⫟-----------+--------+--------|
                                        KC_MUTE,  KC_ESC,  LT_SPC,   LT_TAB,      LT_ENT, LT_BSPC, KC_CAPS, KC_MPLY
                                    //`------------------------------------'  '------------------------------------'
    ),
  /*
   * Navigation and Numbers: _NN
   *
   *     ,-------------------------------------------.                            ,-------------------------------------------.
   *     |        |      | Home |  Up  |  End | pgUp |                            |   *  |   7  |   8  |   9  |  +   |        |
   *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
   *     |        |      | Left | Down | Right| pgDwn|                            |   /  |   4  |   5  |   6  |  Ø   |        |
   *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
   *     |        |      | Cut  | Copy |      | Paste|                            |   =  |   1  |   2  |   3  |  -   |        |
   *     `------------------------⫟------⫟------⫟------⫟------.         ,-----⫟------⫟------⫟------⫟-------------------------'
   *                              | MUTE | Del  | Space|  Tab |         | Enter| Bksp |   0  | PLAY |
   *                              |(enc) |      |  _NN |  _MS |         | _MS  | _NN  |      |(enc) |
   *                              `---------------------------'         `---------------------------'
   */
   [_NN] = LAYOUT_split_3x6_4(
     //,-----------------------------------------------------.                            ,-----------------------------------------------------.
         XXXXXXX, XXXXXXX, KC_HOME,   KC_UP,  KC_END, KC_PGUP,                              DK_ASTR,    KC_7,    KC_8,    KC_9, DK_PLUS, XXXXXXX,
     //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
         XXXXXXX, KC_LCTL,LEFT_ALT,DOWN_GUI,RGHT_SFT, KC_PGDN,                              DK_SLSH,  N4_SFT,  N5_GUI,  N6_ALT,  OE_CTL, XXXXXXX,
     //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
         XXXXXXX, XXXXXXX, G(KC_X), G(KC_C), XXXXXXX, G(KC_V),                               DK_EQL,    KC_1,    KC_2,    KC_3, DK_MINS, XXXXXXX,
     //|--------+--------+-----------⫟--------⫟--------⫟--------⫟--------.   .--------⫟--------⫟--------⫟--------⫟-----------+--------+--------|
                                       KC_MUTE,  KC_DEL,  _______, _______,     _______, _______,    KC_0, KC_MPLY
                                   //`------------------------------------'  '------------------------------------'
   ),
 /*
  * Media and Symbols: _MS
  *
  *     ,-------------------------------------------.                            ,-------------------------------------------.
  *     |        |      |      |   [  |   ]  |  F1  |                            |   $  |   /  |   (  |   )  |   ?  |        |
  *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
  *     |        |brght-|brght+|   {  |   }  |  F2  |                            |   @  |   €  |   %  |   &  |   '  |        |
  *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
  *     |        |      |      |   <  |   >  |  F3  |                            |   §  |   !  |   "  |   #  |   _  |        |
  *     `------------------------⫟------⫟------⫟------⫟------.         ,-----⫟------⫟------⫟------⫟-------------------------'
  *                              | MUTE | Esc  | Space|  Tab |         | Enter| Bksp | Caps |  PLAY|
  *                              |(enc) |      |  _NN |  _MS |         | _MS  | _NN  |      | (enc)|
  *                              `---------------------------'         `---------------------------'
  */
  [_MS] = LAYOUT_split_3x6_4(
    //,-----------------------------------------------------.                            ,-----------------------------------------------------.
        XXXXXXX, XXXXXXX, XXXXXXX, DK_LBRC, DK_RBRC,   KC_F1,                               HB_USD, DK_SLSH, DK_LPRN, DK_RPRN, DK_QUES, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
        XXXXXXX, KC_BRID, KC_BRIU, HB_LCBR, HB_RCBR,   KC_F2,                                HB_AT,  HB_EUR, DK_PERC, DK_AMPR, DK_QUOT, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, HB_LABR, HB_RABR,  KC_F3,                               HB_PRGF, DK_EXLM, DK_DQUO, DK_HASH, DK_UNDS, XXXXXXX,
    //|--------+--------+-----------⫟--------⫟--------⫟--------⫟--------.   .--------⫟--------⫟--------⫟--------⫟-----------+--------+--------|
                                      KC_MUTE,  KC_ESC,  _______, _______,     _______, _______, KC_CAPS, KC_MPLY
                                  //`------------------------------------'  '------------------------------------'
  ),
/*
 * Special functions: _SP
 *
 *     ,-------------------------------------------.                            ,-------------------------------------------.
 *     |        |QWERTY|      |      | QK_BOOT|      |                            |      |      |      |      |      |        |
 *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
 *     |        |      |      | Debug|      |      |                            |      |      |      |      |      |        |
 *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
 *     |        |      |      |COLEMK|      |      |                            |      |      |      |      |      |        |
 *     `------------------------⫟------⫟------⫟------⫟------.         ,-----⫟------⫟------⫟------⫟-------------------------'
 *                              | GUI  | Del  | Space| Nav +|         |Media+| Bksp | Enter| AltGr|
 *                              |      |      |      |Number|         |symbol|      |      |      |
 *                              `---------------------------'         `---------------------------'
 */
 [_SP] = LAYOUT_split_3x6_4(
   //,-----------------------------------------------------.                            ,-----------------------------------------------------.
       XXXXXXX,   QWERT, XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX, DB_TOGG, XXXXXXX, XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
       XXXXXXX, XXXXXXX, XXXXXXX,   COLEM, XXXXXXX, XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+-----------⫟--------⫟--------⫟--------⫟--------.   .--------⫟--------⫟--------⫟--------⫟-----------+--------+--------|
                                     KC_MUTE,  KC_ESC,  _______, _______,     _______, _______, KC_CAPS, KC_MPLY
                                 //`------------------------------------'  '------------------------------------'
 ),

};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NN, _MS, _SP);
}

#ifdef OLED_ENABLE
char wpm_str[10];

// static void render_logo(void) {
//     static const char PROGMEM qmk_logo[] = {
//         0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
//         0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
//         0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
//     };
//
//     oled_write_P(qmk_logo, false);
// }

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n"), false);
    oled_write_ln_P(PSTR("MODE"), false);
    oled_write_ln_P(PSTR(""), false);

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;
        case _COLEMAK:
            oled_write_ln_P(PSTR("Clmk"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _NN:
            oled_write_P(PSTR("Nums\n"), false);
            break;
        case _MS:
            oled_write_P(PSTR("Sym\n"), false);
            break;
        case _SP:
            oled_write_P(PSTR("Spec\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef\n"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

#define ANIM_NUM_FRAMES 2 // number of frames in the animation
#define MAX_DURATION 10000
#define ANIM_BEGIN 30
uint16_t anim_frame_duration = 100; // how long each frame lasts
//  #define ANIM_REVERSE // define this if you want the animation to run backwards at the end

#ifdef ANIM_REVERSE
#define ANIM_TOTAL_FRAMES (2*((ANIM_NUM_FRAMES)-1))
#else
#define ANIM_TOTAL_FRAMES ANIM_NUM_FRAMES
#endif

uint16_t anim_timer = 0;
uint8_t current_anim_frame = 0;

static void render_anim(void) {
    static const char PROGMEM frame[ANIM_NUM_FRAMES][512] = {
        {
          // 'pokemon experiment frame 1', 32x128px
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x10, 0x08, 0x04, 0x04, 0x02, 0x02, 0x02,
          0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x04, 0x08, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x1f, 0x3c, 0xf2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x04, 0xf2, 0x3a, 0x1c, 0x3c, 0xf8, 0xe0, 0x00, 0x00, 0x01, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x70, 0x8c, 0x03, 0x41, 0x82, 0x02, 0x03, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x07, 0x04, 0x84, 0x84, 0xc7, 0x63, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x04, 0x1c, 0x28, 0x58, 0xa4, 0xa4, 0x44, 0x42, 0x42,
          0x23, 0x97, 0x91, 0x48, 0x24, 0x23, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01,
          0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x80, 0x70, 0x08, 0x04, 0x04, 0x08, 0x08, 0x50, 0x20, 0x10, 0x10, 0x10, 0x90, 0x90,
          0x90, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0x10, 0x08, 0x08, 0x04, 0x04, 0x08, 0xf0, 0x00, 0x00,
          0x80, 0x78, 0x1f, 0x3a, 0xf2, 0xc4, 0x00, 0x00, 0x30, 0x60, 0x00, 0x06, 0x8f, 0xcf, 0xe7, 0x03,
          0x01, 0x00, 0x04, 0xf2, 0x3a, 0x1c, 0x1c, 0x78, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0,
          0x1f, 0x64, 0xb4, 0x64, 0xa7, 0x23, 0x40, 0x48, 0x50, 0x40, 0x80, 0x80, 0x91, 0x89, 0x80, 0x80,
          0x80, 0x40, 0x40, 0x47, 0x44, 0x44, 0xa4, 0x64, 0x27, 0x13, 0x08, 0x00, 0x00, 0x80, 0x60, 0x1f,
          0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x0c, 0x0c, 0x08, 0x08, 0x08, 0x0c,
          0x0c, 0x0c, 0x0a, 0x0a, 0x09, 0x05, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04,
          0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0x08, 0x08, 0x10, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0xfc, 0x1b, 0x3c, 0xfc, 0xf9, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x02, 0xf1, 0x39, 0x1c, 0x3c, 0xfc, 0xf8, 0xf0, 0x00, 0x00, 0x03, 0x0c, 0xf0,
          0x00, 0xf8, 0x06, 0x01, 0x32, 0x02, 0x03, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x07, 0x04, 0x84, 0x84, 0x47, 0xe3, 0x01, 0x00, 0x00, 0x00, 0xc0, 0x3f,
          0x00, 0x00, 0x01, 0x02, 0x06, 0x0a, 0x14, 0x28, 0x48, 0x44, 0x44, 0xc2, 0xc2, 0xc2, 0xa2, 0xa2,
          0xa1, 0x91, 0x91, 0x89, 0x49, 0x45, 0x44, 0x22, 0x21, 0x10, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

        },
        {
          // 'pokemon experiment frame 2', 32x128px
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80,
          0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x18, 0x84, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00,
          0x00, 0x80, 0x80, 0x00, 0x01, 0x01, 0x01, 0x02, 0x0c, 0x70, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x7f, 0x87, 0x8f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x01, 0xfc, 0x0e, 0x07, 0x0f, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x1c, 0x63, 0x80, 0x10, 0x20, 0x00, 0x00, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x81, 0x81, 0x41, 0x41, 0x21, 0x10, 0x00, 0x80, 0x60, 0x18, 0x07, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x06, 0x04, 0x04, 0x0a, 0x0a, 0x0a, 0x0a, 0x09,
          0x05, 0x07, 0x04, 0x02, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0x10, 0x10, 0xa0, 0x40, 0x20, 0x20, 0x20, 0x20, 0x20,
          0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x40, 0x20, 0x10, 0x10, 0x08, 0x08, 0x10, 0xe0, 0x00, 0x00,
          0x00, 0xf0, 0x3f, 0x72, 0xe2, 0x80, 0x00, 0x00, 0x60, 0xc0, 0x00, 0x0c, 0x1e, 0x9e, 0xcf, 0x07,
          0x03, 0x00, 0x00, 0xe2, 0x72, 0x38, 0x38, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x01, 0x1e, 0xe0,
          0x3f, 0xc8, 0x68, 0x48, 0x8f, 0x87, 0x00, 0x20, 0x40, 0x00, 0x00, 0x00, 0x43, 0x23, 0x01, 0x00,
          0x00, 0x00, 0x00, 0x0f, 0x08, 0x88, 0x88, 0x48, 0x4f, 0x27, 0x10, 0x00, 0x00, 0x00, 0xc0, 0x3f,
          0x00, 0x00, 0x01, 0x02, 0x02, 0x06, 0x05, 0x09, 0x09, 0x09, 0x12, 0x12, 0x12, 0x12, 0x11, 0x11,
          0x11, 0x11, 0x11, 0x09, 0x09, 0x09, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x90, 0x88, 0x88, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02,
          0x02, 0x02, 0x02, 0x82, 0x82, 0x84, 0x04, 0x04, 0x08, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00,
          0x00, 0x00, 0x00, 0xfe, 0x0d, 0x1e, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0xf8, 0x1c, 0x0e, 0x1e, 0xfe, 0xfc, 0xf8, 0x00, 0x00, 0x01, 0x06, 0xf8,
          0x00, 0x78, 0x87, 0x00, 0x31, 0x01, 0x01, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x82, 0x82, 0x43, 0x61, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1f,
          0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x04, 0x0c, 0x08, 0x14, 0x12, 0x12, 0x12, 0x22, 0x22, 0x22,
          0x21, 0x21, 0x21, 0x21, 0x11, 0x11, 0x10, 0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        }
    };

    if (get_current_wpm() > ANIM_BEGIN){
      if(timer_elapsed(anim_timer) > anim_frame_duration) {
          anim_timer = timer_read();
          current_anim_frame = (current_anim_frame + 1) % ANIM_TOTAL_FRAMES;
          oled_clear();
          oled_write_raw_P(frame[abs((ANIM_NUM_FRAMES-1)-current_anim_frame)], 512);
          if (get_current_wpm() > ANIM_BEGIN){
            anim_frame_duration = MAX_DURATION/get_current_wpm();
          }
      }
    } else {
      oled_write_raw_P(frame[0],512);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    if (is_keyboard_master() != true){
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
        sprintf(wpm_str, "%03d", get_current_wpm());
        oled_write(wpm_str, false);
    } else {
        render_anim();
    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // master side thumb encoder
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // master side pinky encoder
        // Page down / Page up
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    else if (index == 2) {
        // minion side thumb encoder
        // Next track / Previous track
        if (clockwise) {
            tap_code(KC_MFFD);
        } else {
            tap_code(KC_MRWD);
        }
    }
    else if (index == 3) {
        // minion side pinky encoder
        // Page end / Page home
        if (clockwise) {
            tap_code(KC_END);
        } else {
            tap_code(KC_HOME);
        }
    }
    return true;
}
#endif
