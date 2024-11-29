/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
#include <keymap_german.h>
#include <keymap_HomeRowMod.h>

enum layers{
    QWERTZ_BASE,
    NEO_BASE,
    _FN0,
    _NEO3,
    _FN1,
    _FN2,
    _FN3
};

#define KC_WAVE S(KC_GRV)
#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTZ_BASE] = LAYOUT_iso_68(
        KC_ESC,   DE_1,    DE_2,    DE_3,    DE_4,    DE_5,    DE_6,    DE_7,    DE_8,    DE_9,    DE_0,    DE_SS,    DE_ACUT,  KC_BSPC,          KC_MUTE,
        KC_TAB,   DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,    DE_Z,    DE_U,    DE_I,    DE_O,    DE_P,    DE_UDIA,  DE_PLUS,                    KC_DEL,
        MO(_FN0), HRQ_L1,  HRQ_L2,  HRQ_L3,  HRQ_L4,  DE_G,    DE_H,    HRQ_R1,  HRQ_R2,  HRQ_R3,  HRQ_R4,  DE_ADIA,  DE_HASH,  KC_ENT,           KC_HOME,
        KC_LSFT,  DE_LABK, DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,    DE_N,    DE_M,    DE_COMM, DE_DOT,  DE_MINS,            KC_RSFT, KC_UP,
        KC_LCTL,  KC_LGUI, KC_LALT,                            LT(_FN0, KC_SPC),                   KC_RALT, MO(_FN2), MO(_FN3), KC_LEFT, KC_DOWN, KC_RGHT),

    [NEO_BASE] = LAYOUT_iso_68(
        _______,  DE_1,    DE_2,    DE_3,    DE_4,    DE_5,    DE_6,    DE_7,    DE_8,    DE_9,    DE_0,    DE_MINS, DE_ACUT, _______,          _______,
        _______,  DE_X,    DE_V,    DE_L,    DE_C,    DE_W,    DE_K,    DE_H,    DE_G,    DE_F,    DE_Q,    DE_SS,   XXXXXXX,                   _______,
        MO(_NEO3),HRN_L1,  HRN_L2,  HRN_L3,  HRN_L4,  DE_O,    DE_S,    HRN_R1,  HRN_R2,  HRN_R3,  HRN_R4,  DE_Y,   MO(_NEO3),_______,          _______,
        _______,  XXXXXXX, DE_UDIA, DE_ODIA, DE_ADIA, DE_P,    DE_Z,    DE_B,    DE_M,    DE_COMM, DE_DOT,  DE_J,             _______, _______,
        _______,  _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______),

    [_FN0] = LAYOUT_iso_68(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,   KC_DEL,           _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______,  _______,                    _______,
        _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,  _______,  _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______,
        _______, _______, _______,                            _______,                            _______, _______,  _______,  _______, _______, _______),

    [_NEO3] = LAYOUT_iso_68(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,   _______,          _______,
        _______, _______, DE_UNDS, DE_LBRC, DE_RBRC, DE_CIRC, DE_EXLM, DE_LABK, DE_RABK, DE_EQL , DE_AMPR, _______,  _______,                    _______,
        _______, KC_BSLS, DE_SLSH, DE_LCBR, DE_RCBR, DE_ASTR, DE_QUES, DE_LPRN, DE_RPRN, DE_MINS, DE_COLN, DE_AT  ,MO(_NEO3),  _______,          _______,
        _______, DE_HASH, DE_DLR , DE_PIPE, DE_TILD, DE_GRV , DE_PLUS, DE_PERC, DE_DQUO, DE_QUOT, DE_SCLN, _______,            _______, _______,
        _______, _______, _______,                            _______,                            _______, _______,  _______,  _______, _______, _______),        

    [_FN1] = LAYOUT_iso_68(
        KC_GRV,  KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD,  KC_VOLU,  KC_TRNS,          KC_TRNS,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,                    KC_TRNS,
        KC_TRNS, RGB_RMOD,RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS),

    [_FN2] = LAYOUT_iso_68(
        KC_GRV,  KC_BRID, KC_BRIU, KC_TASK, KC_FLXP, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD,  KC_VOLU,  KC_TRNS,          KC_TRNS,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,                    KC_TRNS,
        KC_TRNS, RGB_RMOD,RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS),

    [_FN3] = LAYOUT_iso_68(
        KC_WAVE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,   KC_TRNS,          QK_BOOT,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,                    KC_TRNS,
        KC_TRNS, RGB_RMOD,RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [QWERTZ_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [NEO_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_NEO3]     = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN1]     = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN2]     = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN3]     = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif