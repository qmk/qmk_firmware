/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#define DPI_UP POINTER_DEFAULT_DPI_FORWARD
#define DPI_DOWN POINTER_DEFAULT_DPI_REVERSE

enum layers {
    BASE,
    LOWER,
    RAISE,
    AUTO_MOUSE,
};

enum custom_keycodes {
    A_TAB = CHARYBDIS_SAFE_RANGE,
};

// bool nav_columns = false;
// bool alt_tabber = false;

// void q_esc(qk_tap_dance_state_t *state, void *user_data) {
//     switch (state->count) {
//         case 1:
//             if (nav_columns == false) {
//                 tap_code(KC_Q);
//             } else {
//                 tap_code(KC_ESC);
//             }
//             break;
//         case 2:
//             if (nav_columns == false) {
//                 tap_code(KC_ESC);
//             } else {
//                 tap_code(KC_Q);
//             }
//     }
// }

// void a_tab(qk_tap_dance_state_t *state, void *user_data) {
//     switch (state->count) {
//         case 1:
//             if (nav_columns == false && alt_tabber == false) {
//                 tap_code(KC_A);
//             } else {
//                 tap_code(KC_TAB);
//             }
//             break;
//         case 2:
//             if (nav_columns == false && alt_tabber == false) {
//                 tap_code(KC_TAB);
//             } else {
//                 tap_code(KC_A);
//             }
//     }
// }

// void p_bspc(qk_tap_dance_state_t *state, void *user_data) {
//     switch (state->count) {
//         case 1:
//             if (nav_columns == false) {
//                 tap_code(KC_P);
//             } else {
//                 tap_code(KC_BSPC);
//             }
//             break;
//         case 2:
//             if (nav_columns == false) {
//                 tap_code(KC_BSPC);
//             } else {
//                 tap_code(KC_P);
//             }
//     }
// }

// void quot_ent(qk_tap_dance_state_t *state, void *user_data) {
//     switch (state->count) {
//         case 1:
//             if (nav_columns == false) {
//                 tap_code(KC_QUOT);
//             } else {
//                 tap_code(KC_ENT);
//             }
//             break;
//         case 2:
//             if (nav_columns == false) {
//                 tap_code(KC_ENT);
//             } else {
//                 tap_code(KC_QUOT);
//             }
//     }
// }

// enum tap_dances {
//     TD_Q_ESC = 0,
//     TD_A_TAB,
//     TD_P_BSPC,
//     TD_QUOT_ENT,
// };

// qk_tap_dance_action_t tap_dance_actions[] = {
//     [TD_Q_ESC] = ACTION_TAP_DANCE_FN(q_esc),
//     [TD_A_TAB] = ACTION_TAP_DANCE_FN(a_tab),
//     [TD_P_BSPC] = ACTION_TAP_DANCE_FN(p_bspc),
//     [TD_QUOT_ENT] = ACTION_TAP_DANCE_FN(quot_ent),
// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_charybdis_3x5(
        KC_Q                , KC_W    , KC_E               , KC_R            , KC_T               , KC_Y                , KC_U            , KC_I      , KC_O      , KC_P                ,
        A_TAB               , KC_S    , KC_D               , KC_F            , KC_G               , KC_H                , KC_J            , KC_K      , KC_L      , KC_QUOT             ,
        MT(MOD_LSFT,KC_Z)   , KC_X    , KC_C               , KC_V            , KC_B               , KC_N                , KC_M            , KC_COMM   , KC_DOT    , MT(MOD_RSFT,KC_SLSH),
                                        MT(MOD_LCTL,KC_ESC), LT(LOWER,KC_ENT), MT(MOD_LALT,KC_TAB), MT(MOD_LGUI,KC_BSPC), LT(LOWER,KC_SPC)
    ),
    [LOWER] = LAYOUT_charybdis_3x5(
        KC_HOME             , KC_UP  , KC_END              , KC_PLUS         , KC_LPRN            , KC_RPRN             , KC_7            , KC_8      , KC_9      , KC_DEL              ,
        KC_LEFT             , KC_DOWN, KC_RIGHT            , KC_EQL          , KC_LCBR            , KC_RCBR             , KC_4            , KC_5      , KC_6      , KC_SCLN             ,
        MT(MOD_LSFT,KC_PIPE), KC_UNDS, KC_COLN             , KC_MINS         , KC_LBRC            , KC_RBRC             , KC_1            , KC_2      , KC_3      , MT(MOD_RSFT,KC_BSLS),
                                       KC_TRNS             , MO(RAISE)       , KC_TRNS            , KC_TRNS             , LT(RAISE, KC_0)
    ),
    [RAISE] = LAYOUT_charybdis_3x5(
        KC_1                , KC_2    , KC_3               , KC_4            , KC_5               , KC_6                , KC_7            , KC_8      , KC_9      , KC_0                ,
        KC_EXLM             , KC_AT   , KC_HASH            , KC_DLR          , KC_PERC            , KC_CIRC             , KC_AMPR         , KC_ASTR   , KC_LPRN   , KC_RPRN             ,
        KC_F1               , KC_F2   , KC_F3              , KC_F4           , KC_F5              , KC_F6               , KC_F7           , KC_F8     , KC_F9     , KC_F10              ,
                                        KC_CAPS            , KC_TRNS         , KC_TRNS            , KC_TRNS             , KC_TRNS
    ),
    [AUTO_MOUSE] = LAYOUT_charybdis_3x5(
        DPI_DOWN            , KC_TRNS , KC_TRNS            , KC_TRNS         , KC_TRNS            , KC_TRNS             , KC_TRNS         , KC_TRNS   , KC_TRNS   , DPI_UP              ,
        KC_TRNS             , KC_TRNS , KC_TRNS            , KC_TRNS         , KC_TRNS            , KC_TRNS             , KC_BTN1         , KC_BTN2   , KC_TRNS   , KC_TRNS             ,
        KC_BTN2             , KC_TRNS , KC_TRNS            , KC_TRNS         , KC_TRNS            , KC_TRNS             , KC_TRNS         , KC_TRNS   , KC_TRNS   , KC_BTN1             ,
                                        KC_TRNS            , KC_TRNS         , KC_TRNS            , KC_TRNS             , KC_TRNS
    ),
};

int base_track_speed = 800;
int scroll_track_speed = 100;

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
    pointing_device_set_cpi(base_track_speed);

};

bool alt_tabber = false;
bool set_scrolling = false;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = -mouse_report.y;
        mouse_report.x = mouse_report.y = 0;
    } else {
        mouse_report.x = mouse_report.x;
        mouse_report.y = mouse_report.y;
    }
    return mouse_report;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    switch (keycode){
        case LT(LOWER,KC_ENT):
        case LT(LOWER,KC_SPC):
            if(record->event.pressed){
                set_scrolling = true;
                pointing_device_set_cpi(scroll_track_speed);

            } else {
                set_scrolling = false;
                pointing_device_set_cpi(base_track_speed);
            }
            break;
        case MT(MOD_LALT,KC_TAB):
            if(record->event.pressed){
                alt_tabber = true;
            } else {
                alt_tabber = false;
            }
            break;
        case A_TAB:
            if(record->event.pressed){
                if(alt_tabber == true){
                    register_code(KC_TAB);
                } else {
                    register_code(KC_A);
                }
            } else {
                if(alt_tabber == true){
                    unregister_code(KC_TAB);
                } else {
                    unregister_code(KC_A);
                }
            }
            return false;
    }
  return true;
};
