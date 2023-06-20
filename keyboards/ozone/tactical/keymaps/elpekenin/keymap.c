/*
Copyright 2020 Dimitris Mantzouranis
Copyright 2022 Philip Mourdjis
Copyright 2023 Pablo Martinez Bernal

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

#include QMK_KEYBOARD_H
#include "keymap_spanish.h"
#include "sendstring_spanish.h"

#define XXXXX KC_NO

enum layer_names {
    _QWERTY,
    _FN,
};

enum {
    TD_L, // ´ { [ (
    TD_R, // } ] ) ç
    TD_S, // 4x space
    TD_C, // code block
};


void td_left_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16(ES_ACUT); // {
            break;

        case 2:
            tap_code16(ES_LBRC); // [
            break;

        case 3:
            clear_mods();
            unregister_code16(KC_ALGR);
            tap_code16(ES_LPRN); // (
            break;

        default: // +3 times -> nothing
            break;
    }

    return;
}

void td_rght_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16(ES_RCBR); // }
            break;

        case 2:
            tap_code16(ES_RBRC); // ]
            break;

        case 3:
            clear_mods();
            unregister_code16(KC_ALGR);
            tap_code16(ES_RPRN); // )
            break;

        default:
            tap_code16(ES_CCED); // ç
    }

    return;
}

void td_spc_each(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_SPC);
    register_code16(KC_SPC);

    if ((state->count % 2) == 0) {
        unregister_code16(KC_SPC);
        tap_code16(KC_SPC);
        register_code16(KC_SPC);
    }

    return;
}

void td_spc_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_SPC);

    return;
}

void td_code_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(ES_GRV);
    } else {
        SEND_STRING("```" SS_LSFT("\n\n") "```");
        tap_code16(KC_UP);
    }

    return;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_L] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_left_finished, NULL),
    [TD_R] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_rght_finished, NULL),
    [TD_S] = ACTION_TAP_DANCE_FN_ADVANCED(td_spc_each, NULL, td_spc_reset),
    [TD_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_code_finished, NULL),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_65_iso(
                    KC_ESC,  KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6,   KC_7, KC_8, KC_9,    KC_0,    ES_QUOT,  ES_IEXL,  KC_BSPC, ES_MORD,
                    KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R, KC_T, KC_Y,   KC_U, KC_I, KC_O,    KC_P,    TD(TD_C), ES_PLUS,           KC_DEL,
                    KC_CAPS, KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H,   KC_J, KC_K, KC_L,    ES_NTIL, TD(TD_L), TD(TD_R), KC_ENT,  KC_VOLU,
                    KC_LSFT, ES_LABK, KC_Z,    KC_X, KC_C, KC_V, KC_B,   KC_N, KC_M, ES_COMM, ES_DOT,  ES_MINS,  KC_RSFT,  KC_UP,   KC_VOLD,
                    KC_LCTL, KC_LGUI, KC_LALT,                 TD(TD_S),             KC_ALGR, MO(_FN), KC_RCTL,  KC_LEFT,  KC_DOWN, KC_RGHT
                ),

    [_FN] = LAYOUT_65_iso(
                QK_BOOT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,  XXXXX,   A(KC_PSCR),
                XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,   XXXXX, XXXXX,            XXXXX,
                EE_CLR,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,   XXXXX, RGB_MOD, XXXXX,   XXXXX,
                XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, RGB_HUI, XXXXX, XXXXX,   RGB_VAI, XXXXX,
                XXXXX,   XXXXX, XXXXX,                      XXXXX,               XXXXX, KC_TRNS, XXXXX, RGB_SPD, RGB_VAD, RGB_SPI
            )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_4:
            if (get_mods() & MOD_BIT(KC_LALT)) {
                if (record->event.pressed) {
                    register_code(KC_F4);
                } else {
                    unregister_code(KC_F4);
                }
                return false;
            }
            break;

        default:
            break;
    }

    return true;
}

bool rgb_matrix_indicators_user(void) {
    if (get_highest_layer(layer_state) == _FN) {
        rgb_matrix_set_color_all(RGB_OFF);
        rgb_matrix_set_color(0, RGB_RED);
    }

    return true;
}

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(HSV_BLUE);
    } else {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_LEFT_RIGHT);
    }

    return false;
}
