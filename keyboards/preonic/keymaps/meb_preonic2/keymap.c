/* Copyright 2015-2021 Jack Humbert
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

enum layers {
    BASE,
    NAV_NUM,
    NUM_SYM_FN,
    GAMING,
};

// TAP DANCE SETUP------------------------------------------------------------------------------------------------------------------------------------------------

void td_music_fn(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16(KC_MPLY);
            break;
        case 2:
            tap_code16(KC_MNXT);
            break;
        case 3:
            tap_code16(KC_MPRV);}
}

void td_gaming_tog_fn(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            if(IS_LAYER_ON(GAMING)){
                layer_off(GAMING);
            } else {
                layer_on(GAMING);
            }

            rgblight_toggle_noeeprom();
    }
}


enum tap_dances {
    TD_MUSIC = 0,
    TD_GAMING_TOG
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MUSIC] = ACTION_TAP_DANCE_FN(td_music_fn),
    [TD_GAMING_TOG] = ACTION_TAP_DANCE_FN(td_gaming_tog_fn),
};

// CONVENIENCE MACROS---------------------------------------------------------------------------------------------------------------------------------------------

#define BASE_SPACE LT(NAV_NUM,KC_SPC)
#define NAV_NUM_SPACE LT(NUM_SYM_FN,KC_SPC)
#define ALT_DEL LALT_T(KC_DEL)
#define DESKTOP_LEFT LCTL(LGUI(KC_LEFT))
#define DESKTOP_RIGHT LCTL(LGUI(KC_RIGHT))
#define ALT_F4 LALT(KC_F4)
#define MUSIC TD(TD_MUSIC)
#define GAMING_TOG TD(TD_GAMING_TOG)

// KEYMAP AND LAYERS----------------------------------------------------------------------------------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE]= LAYOUT_preonic_grid(
        MUSIC     , KC_1      , KC_2      , KC_3      , KC_4      , KC_5      , KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , GAMING_TOG,
        KC_ESC    , KC_Q      , KC_W      , KC_E      , KC_R      , KC_T      , KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      , KC_BSPC   ,
        KC_TAB    , KC_A      , KC_S      , KC_D      , KC_F      , KC_G      , KC_H      , KC_J      , KC_K      , KC_L      , KC_QUOT   , KC_ENT    ,
        KC_LSFT   , KC_Z      , KC_X      , KC_C      , KC_V      , KC_B      , KC_N      , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   , KC_RSFT   ,
        KC_LCTL   , KC_PGUP   , KC_PGDN   , KC_LGUI   , ALT_DEL   , BASE_SPACE, BASE_SPACE, ALT_DEL   , KC_RGUI   , KC_HOME   , KC_END    , KC_RCTL
    ),

    [NAV_NUM] = LAYOUT_preonic_grid(
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS      , KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS     , ALT_F4       ,
        KC_GRV    , KC_HOME   , KC_UP     , KC_END    , KC_PLUS   , KC_LPRN      , KC_RPRN      , KC_7      , KC_8      , KC_9         , KC_DEL      , KC_BSPC      ,
        KC_TAB    , KC_LEFT   , KC_DOWN   , KC_RIGHT  , KC_EQL    , KC_LCBR      , KC_RCBR      , KC_4      , KC_5      , KC_6         , KC_SCLN     , KC_ENT       ,
        KC_LSFT   , KC_PIPE   , KC_UNDS   , KC_COLN   , KC_MINS   , KC_LBRC      , KC_RBRC      , KC_1      , KC_2      , KC_3         , KC_BSLS     , KC_RSFT      ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , NAV_NUM_SPACE, NAV_NUM_SPACE, KC_0      , KC_DOT    , KC_COMM      , DESKTOP_LEFT, DESKTOP_RIGHT
    ),

    [NUM_SYM_FN] = LAYOUT_preonic_grid(
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   ,
        KC_1      , KC_2      , KC_3      , KC_4      , KC_5      , KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , KC_MINS   , KC_EQL    ,
        KC_EXLM   , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   , KC_CIRC   , KC_AMPR   , KC_ASTR   , KC_LPRN   , KC_RPRN   , KC_UNDS   , KC_PLUS   ,
        KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     , KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F11    , KC_F12    ,
        KC_CAPS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS
    ),

    [GAMING] = LAYOUT_preonic_grid(
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS    , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS  ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS    , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS  ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS    , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS  ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS    , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS  ,
        KC_LCTL   , KC_NO     , KC_NO     , KC_NO     , KC_LALT   , KC_SPC    , BASE_SPACE, KC_RALT    , KC_NO     , KC_NO     , KC_NO     , KC_RCTL
    ),
};
