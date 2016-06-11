/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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
#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include <stdint.h>
#include "action_code.h"
#include "keyboard.h"

/* automatically applies modifiers to keycodes */
#define S(keycode) LSFT(keycode)
#define LCTL(keycode) (MOD_LCTL << 8 | keycode)
#define LSFT(keycode) (MOD_LSFT << 8 | keycode)
#define LALT(keycode) (MOD_LALT << 8 | keycode)
#define LGUI(keycode) (MOD_LGUI << 8 | keycode)
#define RCTL(keycode) (MOD_RCTL << 8 | keycode)
#define RSFT(keycode) (MOD_RSFT << 8 | keycode)
#define RALT(keycode) (MOD_RALT << 8 | keycode)
#define RGUI(keycode) (MOD_RGUI << 8 | keycode)
#define LCAG(keycode) ((MOD_LCTL | MOD_LALT | MOD_LGUI) << 8 | keycode)
#define MEH(keycode) (MOD_MEH << 8 | keycode)
#define HYPR(keycode) (MOD_HYPR << 8 | keycode)

#define F(keycode) FUNC(keycode)
#define FUNC(number) KC_FN ## number

#define M(number) ACTION_MACRO(number)

#define MACRODOWN(...) (record->event.pressed ? MACRO(__VA_ARGS__) : MACRO_NONE)

#define LT(layer, keycode) ACTION_LAYER_TAP_KEY(layer, keycode)
#define TO(layer, when) ACTION_LAYER_SET(layer, when)
#define MO(layer) ACTION_LAYER_MOMENTARY(layer)
#define DF(layer) ACTION_DEFAULT_LAYER_SET(layer)
#define TG(layer) ACTION_LAYER_TOGGLE(layer)
#define OSL(layer) ACTION_LAYER_ONESHOT(layer)

#define OSM(modifier) ACTION_MODS_ONESHOT(modifier)

#define MT(modifier, keycode) ACTION_MODS_TAP_KEY(modifier, keycode)
#define CTL_T(keycode) MT(MOD_LCTL, keycode)
#define SFT_T(keycode) MT(MOD_LSFT, keycode)
#define ALT_T(keycode) MT(MOD_LALT, keycode)
#define GUI_T(keycode) MT(MOD_LGUI, keycode)
/* for GNOME Terminal, etc. */
#define C_S_T(keycode) MT(MOD_LCTL | MOD_LSFT, keycode)
/* Shift + Alt + GUI */
#define MEH_T(keycode) MT(MOD_MEH, keycode)
#define LCAG_T(keycode) MT(MOD_LCTL | MOD_LALT | MOD_LGUI, keycode)
/* visit http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/ */
#define ALL_T(keycode) MT(MOD_HYPR, keycode)

/* sends Unicode codes */
/* you may not send codes over 0x7FFF (this supports most of UTF-8) */
/* to have a key that sends Œ, use UC(0x152) */
#ifdef UNICODE_ENABLE
#   define UNICODE(n) (0x8000 | n)
#   define UC(n) UNICODE(n)
#endif

/* dedicated keycode versions of Hyper and Meh */
#define KC_HYPR HYPR(KC_NO)
#define KC_MEH MEH(KC_NO)

/* automatically applies Shift to keys */
#define KC_TILD S(KC_GRV)
#define KC_TILDE KC_TILD
/* ! */
#define KC_EXLM S(KC_1)
#define KC_EXCLAIM KC_EXLM
/* @ */
#define KC_AT S(KC_2)
/* # */
#define KC_HASH S(KC_3)
/* $ */
#define KC_DLR S(KC_4)
#define KC_DOLLAR KC_DLR
/* % */
#define KC_PERC S(KC_5)
#define KC_PERCENT KC_PERC
/* ^ */
#define KC_CIRC S(KC_6)
#define KC_CIRCUMFLEX KC_CIRC
/* & */
#define KC_AMPR S(KC_7)
#define KC_AMPERSAND KC_AMPR
/* * */
#define KC_ASTR S(KC_8)
#define KC_ASTERISK KC_ASTR
/* ( */
#define KC_LPRN S(KC_9)
#define KC_LEFT_PAREN KC_LPRN
/* ) */
#define KC_RPRN S(KC_0)
#define KC_RIGHT_PAREN KC_RPRN
/* _ */
#define KC_UNDS S(KC_MINS)
#define KC_UNDERSCORE KC_UNDS
/* + */
#define KC_PLUS S(KC_EQL)
/* { */
#define KC_LCBR S(KC_LBRC)
#define KC_LEFT_CURLY_BRACE KC_LCBR
/* } */
#define KC_RCBR S(KC_RBRC)
#define KC_RIGHT_CURLY_BRACE KC_RCBR
/* < */
#define KC_LABK S(KC_COMM)
#define KC_LEFT_ANGLE_BRACKET KC_LABK
/* > */
#define KC_RABK S(KC_DOT)
#define KC_RIGHT_ANGLE_BRACKET KC_RABK
/* : */
#define KC_COLN S(KC_SCLN)
#define KC_COLON KC_COLN
/* | */
#define KC_PIPE S(KC_BSLS)
/* < */
#define KC_LT S(KC_COMM)
/* > */
#define KC_GT S(KC_DOT)
/* ? */
#define KC_QUES S(KC_SLSH)
#define KC_QUESTION KC_QUES
/* " */
#define KC_DQT S(KC_QUOT)
#define KC_DOUBLE_QUOTE KC_DQT

#define KC_DELT KC_DELETE

/* controls backlight brightness */
#define BL_ON BL_9
#define BL_OFF BL_0
#define BL_0 ACTION_BACKLIGHT_LEVEL(0)
#define BL_1 ACTION_BACKLIGHT_LEVEL(1)
#define BL_2 ACTION_BACKLIGHT_LEVEL(2)
#define BL_3 ACTION_BACKLIGHT_LEVEL(3)
#define BL_4 ACTION_BACKLIGHT_LEVEL(4)
#define BL_5 ACTION_BACKLIGHT_LEVEL(5)
#define BL_6 ACTION_BACKLIGHT_LEVEL(6)
#define BL_7 ACTION_BACKLIGHT_LEVEL(7)
#define BL_8 ACTION_BACKLIGHT_LEVEL(8)
#define BL_9 ACTION_BACKLIGHT_LEVEL(9)
#define BL_10 ACTION_BACKLIGHT_LEVEL(10)
#define BL_11 ACTION_BACKLIGHT_LEVEL(11)
#define BL_12 ACTION_BACKLIGHT_LEVEL(12)
#define BL_13 ACTION_BACKLIGHT_LEVEL(13)
#define BL_14 ACTION_BACKLIGHT_LEVEL(14)
#define BL_15 ACTION_BACKLIGHT_LEVEL(15)
#define BL_DEC ACTION_BACKLIGHT_DECREASE()
#define BL_INC ACTION_BACKLIGHT_INCREASE()
#define BL_TOGG ACTION_BACKLIGHT_TOGGLE()
#define BL_STEP ACTION_BACKLIGHT_STEP()

#define AG_SWAP MAGIC_SWAP_ALT_GUI
#define AG_NORM MAGIC_UNSWAP_ALT_GUI

#define IS_LAYER_ON(layer) (layer_state & 1UL << (layer))
#define IS_LAYER_OFF(layer) (~layer_state & 1UL << (layer))

enum quantum_keycodes {
    RESET = 0x5000,
    DEBUG,
    /* keymap configuration */
    MAGIC_SWAP_CONTROL_CAPSLOCK,
    MAGIC_CAPSLOCK_TO_CONTROL,
    MAGIC_SWAP_LALT_LGUI,
    MAGIC_SWAP_RALT_RGUI,
    MAGIC_NO_GUI,
    MAGIC_SWAP_GRAVE_ESC,
    MAGIC_SWAP_BACKSLASH_BACKSPACE,
    MAGIC_HOST_NKRO,
    MAGIC_SWAP_ALT_GUI,
    MAGIC_UNSWAP_CONTROL_CAPSLOCK,
    MAGIC_UNCAPSLOCK_TO_CONTROL,
    MAGIC_UNSWAP_LALT_LGUI,
    MAGIC_UNSWAP_RALT_RGUI,
    MAGIC_UNNO_GUI,
    MAGIC_UNSWAP_GRAVE_ESC,
    MAGIC_UNSWAP_BACKSLASH_BACKSPACE,
    MAGIC_UNHOST_NKRO,
    MAGIC_UNSWAP_ALT_GUI,
    /* controls audio mode */
    AU_ON,
    AU_OFF,
    AU_TOG,
    /* controls music mode */
    MU_ON,
    MU_OFF,
    MU_TOG,
    /* controls music voice iteration */
    MUV_IN,
    MUV_DE,
    /* controls MIDI mode */
    MI_ON,
    MI_OFF,
    KC_LEAD,
    /* sends shift when held and parentheses when tapped */
    KC_LSPO,
    KC_RSPC
};

extern const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];

/* activates a third layer if two layers are active */
void update_tri_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3);
/* fetches a keycode */
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key);
/* fetches a keycode */
uint16_t keymap_fn_to_keycode(uint8_t keycode);

#endif
