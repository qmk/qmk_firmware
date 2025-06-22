/* Copyright 2023 Etienne Collin (@etiennecollin)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum custom_layers {
    COL,
    QWE,
    GAM,
    MED,
    NAV,
    MOS,
    SYM,
    NUM,
    FUN,
    SYS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [COL] = LAYOUT_split_3x5_3(
    KC_Q,               KC_W,               KC_F,               KC_P,               KC_B,               KC_J,               KC_L,               KC_U,               KC_Y,               KC_QUOT,
    KC_A,               KC_R,               KC_S,               KC_T,               KC_G,               KC_M,               KC_N,               KC_E,               KC_I,               KC_O,
    LGUI_T(KC_Z),       LALT_T(KC_X),       LCTL_T(KC_C),       LSFT_T(KC_D),       KC_V,               KC_K,               RSFT_T(KC_H),       RCTL_T(KC_COMM),    RALT_T(KC_DOT),     RGUI_T(KC_SLSH),
                                            LT(MED, KC_ESC),    LT(NAV, KC_SPC),    LT(MOS, KC_TAB),    LT(SYM, KC_ENT),    LT(NUM, KC_BSPC),    LT(FUN, KC_DEL)
  ),
  [QWE] = LAYOUT_split_3x5_3(
    KC_Q,               KC_W,               KC_E,               KC_R,               KC_T,               KC_Y,               KC_U,               KC_I,               KC_O,               KC_P,
    KC_A,               KC_S,               KC_D,               KC_F,               KC_G,               KC_H,               KC_J,               KC_K,               KC_L,               KC_QUOT,
    LGUI_T(KC_Z),       LALT_T(KC_X),       LCTL_T(KC_C),       LSFT_T(KC_V),       KC_B,               KC_N,               RSFT_T(KC_M),       RCTL_T(KC_COMM),    RALT_T(KC_DOT),     RGUI_T(KC_SLSH),
                                            LT(MED, KC_ESC),    LT(NAV, KC_SPC),    LT(MOS, KC_TAB),    LT(SYM, KC_ENT),    LT(NUM, KC_BSPC),    LT(FUN, KC_DEL)
  ),
  [GAM] = LAYOUT_split_3x5_3(
    KC_TAB,             KC_Q,               KC_W,               KC_E,               KC_R,               KC_T,               KC_Y,               KC_U,               KC_I,               KC_O,
    KC_LSFT,            KC_A,               KC_S,               KC_D,               KC_F,               KC_G,               KC_H,               KC_J,               KC_K,               KC_L,
    KC_LCTL,            KC_Z,               KC_X,               KC_C,               KC_V,               KC_B,               KC_N,               KC_M,               KC_COMM,            KC_DOT,
                                            KC_LALT,            KC_CAPS,            KC_SPC,             LT(SYM, KC_ENT),    LT(NUM, KC_BSPC),   LT(FUN, KC_ESC)
  ),
  [MED] = LAYOUT_split_3x5_3(
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            KC_MPRV,            KC_VOLD,            KC_VOLU,            KC_MNXT,
    KC_LGUI,            KC_LALT,            KC_LCTL,            KC_LSFT,            XXXXXXX,            XXXXXXX,            KC_MRWD,            XXXXXXX,            XXXXXXX,            KC_MFFD,
                                            _______,            XXXXXXX,            XXXXXXX,            KC_MSTP,            KC_MPLY,            KC_MUTE
  ),
  [NAV] = LAYOUT_split_3x5_3(
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            KC_CAPS,            KC_LEFT,            KC_DOWN,            KC_UP,              KC_RGHT,
    KC_LGUI,            KC_LALT,            KC_LCTL,            KC_LSFT,            XXXXXXX,            KC_INS,             KC_HOME,            KC_PGDN,            KC_PGUP,            KC_END,
                                            XXXXXXX,            _______,            XXXXXXX,            KC_ENT,             KC_BSPC,            KC_DEL
  ),
  [MOS] = LAYOUT_split_3x5_3(
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            KC_ACL0,            KC_ACL1,            KC_ACL2,            XXXXXXX,
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            KC_MS_L,            KC_MS_D,            KC_MS_U,            KC_MS_R,
    KC_LGUI,            KC_LALT,            KC_LCTL,            KC_LSFT,            XXXXXXX,            XXXXXXX,            KC_WH_L,            KC_WH_D,            KC_WH_U,            KC_WH_R,
                                            XXXXXXX,            XXXXXXX,            _______,            KC_BTN1,            KC_BTN2,            KC_BTN3
  ),
  [SYM] = LAYOUT_split_3x5_3(
    KC_PIPE,            KC_AMPR,            KC_ASTR,            KC_LPRN,            KC_LCBR,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    KC_COLN,            KC_DLR,             KC_PERC,            KC_CIRC,            KC_PLUS,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    KC_TILD,            KC_EXLM,            KC_AT,              KC_HASH,            KC_UNDS,            XXXXXXX,            KC_RSFT,            KC_RCTL,            KC_RALT,            KC_RGUI,
                                            KC_LPRN,            KC_RPRN,            KC_RCBR,            _______,            XXXXXXX,            XXXXXXX
  ),
  [NUM] = LAYOUT_split_3x5_3(
    KC_BSLS,            KC_7,               KC_8,               KC_9,               KC_LBRC,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    KC_SCLN,            KC_4,               KC_5,               KC_6,               KC_EQL,             XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    KC_GRV,             KC_1,               KC_2,               KC_3,               KC_MINS,            XXXXXXX,            KC_RSFT,            KC_RCTL,            KC_RALT,            KC_RGUI,
                                            KC_DOT,             KC_0,               KC_RBRC,            XXXXXXX,            _______,            XXXXXXX
  ),
  [FUN] = LAYOUT_split_3x5_3(
    KC_PSCR,             KC_F7,              KC_F8,              KC_F9,             KC_F12,             XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    KC_PAUS,             KC_F4,              KC_F5,              KC_F6,             KC_F11,             XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    KC_SCRL,             KC_F1,              KC_F2,              KC_F3,             KC_F10,             XXXXXXX,            KC_RSFT,            KC_RCTL,            KC_RALT,            KC_RGUI,
                                             KC_APP,             KC_SPC,            KC_TAB,             XXXXXXX,            XXXXXXX,            _______
  ),
  [SYS] = LAYOUT_split_3x5_3(
    QK_BOOT,            XXXXXXX,            DF(GAM),            DF(QWE),            DF(COL),            DF(COL),            DF(QWE),            DF(GAM),            XXXXXXX,            QK_BOOT,
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    XXXXXXX,            XXXXXXX,            NK_OFF,             NK_ON,              NK_TOGG,            NK_TOGG,            NK_ON,              NK_OFF,             XXXXXXX,            XXXXXXX,
                                            _______,            XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,            _______
  )
};

const uint16_t PROGMEM combo_sys[] = {LT(MED, KC_ESC), LT(FUN, KC_DEL), COMBO_END};
const uint16_t PROGMEM combo_sys_gam[] = {KC_LALT, LT(FUN, KC_ESC), COMBO_END};

combo_t key_combos[] = {
  COMBO(combo_sys, MO(SYS)),
  COMBO(combo_sys_gam, MO(SYS))
};
