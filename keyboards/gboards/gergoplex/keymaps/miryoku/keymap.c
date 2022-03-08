/* Copyright 2022 Micheal Waltz
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

/* Miryoku Keymap Layout for GergoPlex
 * https://github.com/manna-harbour/miryoku
 * https://www.gboards.ca/product/gergoplex
 */

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

enum {
    _BASE,   // default (Colemak DHm)
    _NAV,    // Navigation
    _MOUSE,  // Mouse Emulation
    _MEDIA,  // Media Controls
    _NUM,    // Numbers
    _SYM,    // Symbols
    _FUN     // Functions
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Base layer / Colemak DHm
     *
     * ,-----------------------------------.      ,------------------------------------.
     * |   Q   |   W  |   F  |   P  |   B  |      |   J   |   L   |   U  |  Y   |  '   |
     * |-------+------+------+------+------|      |-------+-------+------+------+------|
     * |   A   |   R  |   S  |   T  |   G  |      |   M   |   N   |   E  |  I   |  O   |
     * |-------+------+------+------+------|      |-------+-------+------+------+------|
     * |   Z   |   X  |   C  |   D  |   V  |      |   K   |   H   |   <  |  >   |  /   |
     * `-----------------------------------'      `-------------------------------------'
     *          .--------------------------.      .---------------------------.
     *          | L3 ESC | L1 SPC | L2 TAB |      | L5 ENT | L4 BSPC | L5 DEL |
     *          '--------------------------'      '---------------------------'
     */
    [_BASE] = LAYOUT_split_3x5_3(
         KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,          KC_J, KC_L,         KC_U, KC_Y,   KC_QUOTE,
         LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G,          KC_M, LSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_I),   LGUI_T(KC_O),
         KC_Z,         RALT_T(KC_X), KC_C,         KC_D,         KC_V,          KC_K, KC_H,         KC_COMMA,     RALT_T(KC_DOT), KC_SLASH,
                              LT(3,KC_ESC), LT(1,KC_SPC), LT(2,KC_TAB),         LT(5,KC_ENT), LT(4,KC_BSPC), LT(6,KC_DEL)),

    /* Keymap 1: Navigation
     *
     * ,-----------------------------------.      ,-------------------------------------.
     * | RESET |      |       |      |     |      | AGAIN | PASTE | COPY | CUT  | UNDO  |
     * |-------+------+-------+------+-----|      |-------+-------+------+------+-------|
     * | LGUI  | LALT | LCTRL | LSFT |     |      | CAPS  | LEFT | DOWN  | UP   | RIGHT |
     * |-------r------+-------+------+-----|      |-------+------+-------+------+-------|
     * |       |      |       |      |     |      | INS   | HOME | PGDN  | PGUP | END   |
     * `-----------------------------------'      `-------------------------------------'
     *                .--------------------.      .---------------------.
     *                |      |      |      |      |  ENT  |  BSPC | DEL |
     *                '--------------------'      '---------------------'
     */
    [_NAV] = LAYOUT_split_3x5_3(
         RESET,   KC_NO,   KC_NO,   KC_NO,   KC_NO,          KC_AGAIN, KC_PASTE, KC_COPY, KC_CUT, KC_UNDO,
         KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,          KC_CAPS,  KC_LEFT,  KC_DOWN, KC_UP,  KC_RIGHT,
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,          KC_INS,   KC_HOME,  KC_PGDN, KC_PGUP,KC_END,
                               KC_NO, KC_NO, KC_NO,          KC_ENT, KC_BSPC,KC_DEL),

    /* Keymap 2: Mouse Emulation
     *
     * ,-----------------------------------.      ,------------------------------------.
     * | RESET |      |       |      |     |      | AGAIN | PASTE | COPY | CUT  | UNDO |
     * |-------+------+-------+------+-----|      |-------+-------+------+------+------|
     * | LGUI  | LALT | LCTRL | LSFT |     |      |       | MS_L  | MS_D | MS_U | MS_R |
     * |-------+------+-------+---- -+-----|      |-------+-------+------+------+------|
     * |       |      |       |      |     |      |       | WH_L  | WH_D | WH_U | WH_R |
     * `-----------------------------------'      `------------------------------------'
     *                .--------------------.      .---------------------.
     *                |       |      |     |      | BTN1  | BTN3 | BTN2 |
     *                '--------------------'      '----- ---------------'
     */
    [_MOUSE] = LAYOUT_split_3x5_3(
         RESET,   KC_NO,   KC_NO,   KC_NO,   KC_NO,          KC_AGAIN, KC_PASTE, KC_COPY, KC_CUT, KC_UNDO,
         KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,          KC_NO,    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,          KC_NO,    KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
                               KC_NO, KC_NO, KC_NO,          KC_BTN1, KC_BTN3,  KC_BTN2),

    /* Keymap 3: Media Controls
     *
     * ,-----------------------------------.      ,------------------------------------.
     * | RESET |      |       |      |     |      |       |      |      |      |       |
     * |-------+------+-------+------+-----|      |-------+------+------+------+-------|
     * | LGUI  | LALT | LCTRL | LSFT |     |      |       | PREV | VOL- | VOL+ | NEXT  |
     * |-------+------+-------+---- -+-----|      |-------+------+------+------+-------|
     * |       |      |       |      |     |      |       |      |      |      |       |
     * `-----------------------------------'      `------------------------------------'
     *                .--------------------.      .---------------------.
     *                |       |      |     |      | STOP  | PLAY | MUTE |
     *                '--------------------'      '---------------------'
     */
    [_MEDIA] = LAYOUT_split_3x5_3(
         RESET,   KC_NO,   KC_NO,   KC_NO,   KC_NO,          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,          KC_NO,   KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                               KC_NO, KC_NO, KC_NO,          KC_MSTP, KC_MPLY, KC_MUTE),

    /* Keymap 4: Numbers
     *
     * ,-----------------------------------.      ,------------------------------------.
     * |   [  |   7  |   8  |   9  |   ]   |      |     |       |       |      | RESET |
     * |------+------+------+------+-------|      |-----+-------+-------+------+-------|
     * |   ;  |   4  |   5  |   6  |   =   |      |     | SHIFT | LCTRL | LALT | LGUI  |
     * |-------+------+-----+------+-------|      |-----+-------+-------+------+-------|
     * |   `   |  1   |  2  |   3  |   \   |      |     |       |       |      |       |
     * `-----------------------------------'      `------------------------------------'
     *                .--------------------.      .---------------------.
     *                |  .  |   0  |   -   |      |     |       |       |
     *                '--------------------'      '---------------------'
     */
    [_NUM] = LAYOUT_split_3x5_3(
         KC_LBRC, KC_7, KC_8, KC_9, KC_RBRC,         KC_NO, KC_NO,   KC_NO,   KC_NO,   RESET,
         KC_SCLN, KC_4, KC_5, KC_6, KC_EQL,          KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
         KC_GRV,  KC_1, KC_2, KC_3, KC_BSLS,         KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,
                      KC_DOT, KC_0, KC_MINS,         KC_NO, KC_NO, KC_NO),

    /* Keymap 5: Symbols
     *
     * ,-----------------------------------.      ,------------------------------------.
     * |   {  |   &  |   *  |   (  |   }   |      |     |       |       |      | RESET |
     * |------+------+------+------+-------|      |-----+-------+-------+------+-------|
     * |   :  |   $  |   %  |   ^  |   +   |      |     | SHIFT | LCTRL | LALT | LGUI  |
     * |-------+------+-----+------+-------|      |-----+-------+-------+------+-------|
     * |   ~   |  !   |  @  |   #  |   |   |      |     |       |       |      |       |
     * `-----------------------------------'      `------------------------------------'
     *                .--------------------.      .---------------------.
     *                |  (  |   )  |   _   |      |     |       |       |
     *                '--------------------'      '---------------------'
     */
    [_SYM] = LAYOUT_split_3x5_3(
         KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,         KC_NO, KC_NO,   KC_NO,   KC_NO,   RESET,
         KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,         KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
         KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE,         KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,
                           KC_LPRN, KC_RPRN, KC_UNDS,         KC_NO, KC_NO, KC_NO),

    /* Keymap 6: Functions
     *
     * ,-----------------------------------.      ,------------------------------------.
     * |  F12  |  F7  |  F8  |  F9  | PSCR |      |     |       |       |      | RESET |
     * |------+------+------+------+-------|      |-----+-------+-------+------+-------|
     * |  F11  |  F4  |  F5  |  F6  | SCRL |      |     | SHIFT | LCTRL | LALT | LGUI  |
     * |-------+------+-----+------+-------|      |-----+-------+-------+------+-------|
     * |  F10  |  F1   | F2  |  F3  | PAUS |      |     |       |       |      |       |
     * `-----------------------------------'      `------------------------------------'
     *              .----------------------.      .---------------------.
     *              |  MENU  |  SPC | TAB  |      |     |       |       |
     *              '----------------------'      '---------------------'
     */
    [_FUN] = LAYOUT_split_3x5_3(
         KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR,         KC_NO, KC_NO,   KC_NO,   KC_NO,   RESET,
         KC_F11, KC_F4, KC_F5, KC_F6, KC_SCRL,         KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
         KC_F10, KC_F1, KC_F2, KC_F3, KC_PAUS,         KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,
                      KC_MENU, KC_SPC, KC_TAB,         KC_NO, KC_NO, KC_NO)
};
