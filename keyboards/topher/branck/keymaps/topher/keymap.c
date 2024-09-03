/* Copyright 2015-2017 Jack Humbert
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
//#include "muse.h"

extern keymap_config_t keymap_config;
//extern rgblight_config_t rgblight_config;

enum planck_layers {
    _QWERTY,
    _LOW,
    _LOWER,
    _LOWEST,
};

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    //My Keycodes
    COPY,
    XPASTE,
    TabLeft,
    TabRight,
    STabLeft,
    STabRight
};

enum tap_dance_keycodes {
    QS,
};

#define LOW MO(_LOW)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_ortho_4x12(
            KC_TAB,  TD(QS),    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
            KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
            MT(MOD_LSFT,KC_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RCTL,KC_ENT),
            KC_INS, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   MT(MOD_RSFT,KC_ENT),  KC_SPC,  LOW,   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
            ),

    [_LOW] = LAYOUT_ortho_4x12(
            QK_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
            KC_LCTL,  _______,  _______,   _______,  _______,   _______,  _______,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
            MT(MOD_LSFT,KC_CAPS), _______,  _______,  _______, _______,  _______,  _______, KC_PGDN, KC_PGUP, _______, _______, _______,  
            KC_PSCR, KC_LCTL, KC_LALT, KC_LGUI, _______, MT(MOD_RSFT,KC_ENT),  KC_SPC, _______, KC_END, _______, _______, KC_HOME  
            ),

    [_LOWER] = LAYOUT_ortho_4x12(
            QK_GESC, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_DEL,
            KC_LCTL,  _______, _______, _______, _______, _______, _______, KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
            MT(MOD_LSFT,KC_CAPS), _______, XPASTE, COPY, KC_LALT, _______, _______,  TabLeft, TabRight, _______, _______, _______,  
            KC_PSCR, KC_LCTL, KC_LALT, KC_LGUI, _______, MT(MOD_RSFT,KC_ENT),  KC_SPC, _______, KC_END, _______, _______, KC_HOME  
            ), 

    [_LOWEST] = LAYOUT_ortho_4x12(
        QK_BOOT, QK_RBT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______,  _______, _______, _______, 
        _______, _______, KC_F5,   KC_F6,  KC_F7,   KC_F8,  KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______,
        _______, _______,  KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______, STabLeft, STabRight, _______,  _______, _______,  
        _______,  _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______   
    )

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOW, _LOWER, _LOWEST);
}

typedef struct {     
    uint16_t tap;     
    uint16_t hold;     
    uint16_t held; 
} tap_dance_tap_hold_t; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;     
    switch (keycode) {         
        case TD(QS):  // list all tap dance keycodes with tap-hold configurations             
            action = &tap_dance_actions[TD_INDEX(keycode)];             
            if (!record->event.pressed && action->state.count && !action->state.finished) {                 
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;                 
                tap_code16(tap_hold->tap);             
            }     
            break;
        case COPY:
        if (record->event.pressed)
        {
            register_code(KC_LCTL);
            register_code(KC_C);
        }
        else
        {
            unregister_code(KC_LCTL);
            unregister_code(KC_C);
        }
        break;
        case XPASTE:
        if (record->event.pressed)
        {
            register_code(KC_LSFT);
            register_code(KC_INS);
        }
        else
        {
            unregister_code(KC_LSFT);
            unregister_code(KC_INS);
        }
        break;
        case TabLeft:
        if (record->event.pressed)
        {
            register_code(KC_LCTL);
            register_code(KC_PGUP);
        }
        else
        {
            unregister_code(KC_LCTL);
            unregister_code(KC_PGUP);
        }
        break;
        case TabRight:
        if (record->event.pressed)
        {
            register_code(KC_LCTL);
            register_code(KC_PGDN);
        }
        else
        {
            unregister_code(KC_LCTL);
            unregister_code(KC_PGDN);
        }
        break;
        case STabLeft:
        if (record->event.pressed)
        {
            register_code(KC_LSFT);
            register_code(KC_LCTL);
            register_code(KC_PGUP);
        }
        else
        {
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            unregister_code(KC_PGUP);
        }
        break;
        case STabRight:
        if (record->event.pressed)
        {
            register_code(KC_LSFT);
            register_code(KC_LCTL);
            register_code(KC_PGDN);
        }
        else
        {
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            unregister_code(KC_PGDN);
        }
        break;
        }
  return true;
  }

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {     
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;     

    if (state->pressed) {         
        if (state->count == 1 
#ifndef PERMISSIVE_HOLD             
                && !state->interrupted 
#endif         
                ) {             
            register_code16(tap_hold->hold);             
            tap_hold->held = tap_hold->hold;         
        } else {             
            register_code16(tap_hold->tap);             
            tap_hold->held = tap_hold->tap;         
        }     
    } 
} 

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {     
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;     

    if (tap_hold->held) {         
        unregister_code16(tap_hold->held);         
        tap_hold->held = 0;     
    } 
} 
#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [QS] = ACTION_TAP_DANCE_TAP_HOLD(KC_Q, KC_SCLN),
};