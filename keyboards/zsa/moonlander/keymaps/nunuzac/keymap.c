/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include <stdint.h>
#include "nunuzac.h"
#include "tap_dances.h"
#include "caps_word.h"
#include "secrets.h"

enum combo_events {
    CAPS_COMBO,
    LPWD_COMBO,
    SPWD_COMBO,
    MAIL_COMBO,
    WMAL_COMBO,
    LNAM_COMBO,
    SNAM_COMBO,
    COMBO_LENGTH
};

enum custom_keycodes {
    KC_PRIM = SAFE_RANGE,
    KC_SECN,
    KC_UNDX,
    KC_REDX,
    SW_OS,
    SW_PG,
    SW_LY,
    SW_GM,
    SW_SY,
};

uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM caps_combo[] = {KC_RGHT, KC_UP, COMBO_END};
const uint16_t PROGMEM lpwd_combo[] = {KC_P, KC_W, KC_D, COMBO_END};
const uint16_t PROGMEM spwd_combo[] = {KC_P, KC_W, COMBO_END};
const uint16_t PROGMEM mail_combo[] = {KC_M, KC_L, COMBO_END};
const uint16_t PROGMEM wmal_combo[] = {KC_W, KC_M, KC_L, COMBO_END};
const uint16_t PROGMEM lnam_combo[] = {KC_N, KC_A, KC_M, COMBO_END};
const uint16_t PROGMEM snam_combo[] = {KC_N, KC_M, COMBO_END};

combo_t key_combos[] = {
    [CAPS_COMBO] = COMBO_ACTION(caps_combo),
    [LPWD_COMBO] = COMBO_ACTION(lpwd_combo),
    [SPWD_COMBO] = COMBO_ACTION(spwd_combo),
    [MAIL_COMBO] = COMBO_ACTION(mail_combo),
    [WMAL_COMBO] = COMBO_ACTION(wmal_combo),
    [LNAM_COMBO] = COMBO_ACTION(lnam_combo),
    [SNAM_COMBO] = COMBO_ACTION(snam_combo),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = LAYOUT_moonlander(
        KC_TDEC, KC_TD1N,  KC_TD2N,  KC_TD3N,  KC_TD4N,  KC_TD5N, SW_OS,              SW_GM,   KC_TD6N,  KC_TD7N,  KC_TD8N,  KC_TD9N,  KC_TD0N,  KC_TDLG,
        KC_TDUH, KC_Q,     KC_W,     KC_TDE,   KC_R,     KC_T,    SW_PG,              SW_SY,   KC_Y,     KC_TDU,   KC_TDI,   KC_TDO,   KC_P,     KC_TDSL,
        KC_TDDE, KC_TDA,   KC_S,     KC_D,     KC_F,     KC_G,    SW_LY,              _______, KC_H,     KC_J,     KC_K,     KC_L,     KC_TDEP,  KC_TDQT,
        KC_LSFT, KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                                 KC_TDN,   KC_M,     KC_TDCL,  KC_TDDG,  KC_TDCN,  KC_TDLN,
        KC_PRIM, KC_SECN,  KC_LALT,  KC_LEFT,  KC_RGHT,           KC_TAB,             KC_ENT,            KC_UP,    KC_DOWN,  KC_TDCB,  KC_TDRB,  KC_TDSB,
                                               KC_SPC,   KC_TDCC, KC_TDPS,            QK_LEAD, KC_DEL,   KC_BSPC
    ),

    [WORKMAN] = LAYOUT_moonlander(
        KC_TDEC, KC_TD1N,  KC_TD2N,  KC_TD3N,  KC_TD4N,  KC_TD5N,  SW_OS,             SW_GM,   KC_TD6N,  KC_TD7N,  KC_TD8N,  KC_TD9N,  KC_TD0N,  KC_TDLG,
        KC_TDUH, KC_Q,     KC_D,     KC_R,     KC_W,     KC_B,     SW_PG,             SW_SY,   KC_J,     KC_F,     KC_TDU,   KC_P,     KC_TDCN,  KC_TDSL,
        KC_TDDE, KC_TDA,   KC_S,     KC_H,     KC_T,     KC_G,     SW_LY,             _______, KC_Y,     KC_TDN,   KC_TDE,   KC_TDO,   KC_TDI,   KC_TDQT,
        KC_LSFT, KC_Z,     KC_X,     KC_M,     KC_C,     KC_V,                                 KC_K,     KC_L,     KC_TDCL,  KC_TDDG,  KC_TDEP,  KC_TDLN,
        KC_PRIM, KC_SECN,  KC_LALT,  KC_LEFT,  KC_RGHT,            KC_TAB,            KC_ENT,            KC_UP,    KC_DOWN,  KC_TDCB,  KC_TDRB,  KC_TDSB,
                                               KC_SPC,   KC_TDCC,  KC_TDPS,           QK_LEAD, KC_DEL,  KC_BSPC
    ),

    [QWERTY_PG] = LAYOUT_moonlander(
        KC_TDEC, KC_TDN1,  KC_TDN2,  KC_TDN3,  KC_TDN4,  KC_TDN5, SW_OS,              KC_UNDX, KC_TDN6,  KC_TDN7,  KC_TDN8,  KC_TDN9,  KC_TDN0,  KC_TDLG,
        KC_TDUH, KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,    SW_PG,              KC_REDX, KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_TDSL,
        KC_TDDE, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,    SW_LY,              QK_LEAD, KC_H,     KC_J,     KC_K,     KC_L,     KC_TDEP,  KC_TDQT,
        KC_LSFT, KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                                 KC_N,     KC_M,     KC_TDCL,  KC_TDDG,  KC_TDCN,  KC_TDLN,
        KC_PRIM, KC_SECN,  KC_LALT,  KC_LEFT,  KC_RGHT,           KC_TAB,             KC_ENT,            KC_UP,    KC_DOWN,  KC_TDCB,  KC_TDRB,  KC_TDSB,
                                               KC_SPC,   KC_TDCC, KC_TDPS,            KC_TDFR, KC_DEL,   KC_BSPC
    ),

    [WORKMAN_PG] = LAYOUT_moonlander(
        KC_TDEC, KC_TDN1,  KC_TDN2,  KC_TDN3,  KC_TDN4,  KC_TDN5,  SW_OS,             KC_UNDX, KC_TDN6,  KC_TDN7,  KC_TDN8,  KC_TDN9,  KC_TDN0,  KC_TDLG,
        KC_TDUH, KC_Q,     KC_D,     KC_R,     KC_W,     KC_B,     SW_PG,             KC_REDX, KC_J,     KC_F,     KC_U,     KC_P,     KC_TDCN,  KC_TDSL,
        KC_TDDE, KC_A,     KC_S,     KC_H,     KC_T,     KC_G,     SW_LY,             QK_LEAD, KC_Y,     KC_N,     KC_E,     KC_O,     KC_I,     KC_TDQT,
        KC_LSFT, KC_Z,     KC_X,     KC_M,     KC_C,     KC_V,                                 KC_K,     KC_L,     KC_TDCL,  KC_TDDG,  KC_TDEP,  KC_TDLN,
        KC_PRIM, KC_SECN,  KC_LALT,  KC_LEFT,  KC_RGHT,            KC_TAB,            KC_ENT,            KC_UP,    KC_DOWN,  KC_TDCB,  KC_TDRB,  KC_TDSB,
                                               KC_SPC,   KC_TDCC,  KC_TDPS,           KC_TDFR, KC_DEL,  KC_BSPC
    ),

    [GAMES] = LAYOUT_moonlander(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,                SW_GM,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        KC_LALT, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______,                _______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______,                _______, KC_H,    KC_J,    KC_K,    KC_L,    _______, _______,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                     KC_N,    KC_M,    _______, _______, _______, _______,
        _______, _______, _______, KC_LEFT, KC_RGHT,          KC_TAB,                 KC_ENT,           KC_UP,   KC_DOWN, _______, _______, _______,
                                            KC_SPC,  _______, _______,                _______, KC_DEL,  KC_BSPC
    ),

    [SYMBOLS] = LAYOUT_moonlander(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,                SW_GM,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        KC_LALT, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______,                _______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______,                _______, KC_H,    KC_J,    KC_K,    KC_L,    _______, _______,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                     KC_N,    KC_M,    _______, _______, _______, _______,
        _______, _______, _______, KC_LEFT, KC_RGHT,          KC_TAB,                 KC_ENT,           KC_UP,   KC_DOWN, _______, _______, _______,
                                            KC_SPC,  _______, _______,                _______, KC_DEL,  KC_BSPC
    ),
};

void set_autoshift(void) {
    clear_keyboard();
    if (layer_state_is(QWERTY) || layer_state_is(WORKMAN))
        autoshift_enable();
    else
        autoshift_disable();
}


void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case CAPS_COMBO:
            if (pressed)
                caps_word_set(true);
        break;
        case LPWD_COMBO:
            if(!pressed)
                send_long_password();
        break;
        case SPWD_COMBO:
            if(!pressed)
                send_short_password();
        break;
        case MAIL_COMBO:
            if(!pressed)
                send_mail();
        break;
        case WMAL_COMBO:
            if(!pressed)
                send_work_mail();
        break;
        case LNAM_COMBO:
            if(!pressed)
                send_long_name();
        break;
        case SNAM_COMBO:
            if(!pressed)
                send_short_name();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_caps_word(keycode, record)) { return false; }
    switch (keycode) {
        case KC_UNDX:
        case KC_REDX:
            ;
            enum mods_5bit to_press = get_current_os() == OSX ? MOD_LGUI : MOD_LCTL;
            if(record->event.pressed) {
                register_mods(to_press);
                if(keycode == KC_REDX)
                    register_mods(MOD_LSFT);
                register_code(KC_Z);
            } else {
                unregister_mods(to_press);
                if(keycode == KC_REDX)
                    unregister_mods(MOD_LSFT);
                unregister_code(KC_Z);
            }
        break;
        case KC_PRIM:
        case KC_SECN:
            ;
            enum mods_5bit to_hold = MOD_LCTL;
            if ((keycode == KC_PRIM && get_current_os() == OSX) || (keycode == KC_SECN && get_current_os() != OSX))
                to_hold = MOD_LGUI;
            if(record->event.pressed)
                register_mods(to_hold);
            else
                unregister_mods(to_hold);
        break;
        case SW_OS:
            if(!record->event.pressed) {
                set_current_os((get_current_os() + 1) % 2);
                ML_LED_1(get_current_os() == OSX);
            }
        break;
        case SW_PG:
            if(!record->event.pressed) {
                if(layer_state_is(QWERTY))
                    layer_move(QWERTY_PG);
                else if(layer_state_is(QWERTY_PG))
                    layer_move(QWERTY);
                else if(layer_state_is(WORKMAN))
                    layer_move(WORKMAN_PG);
                else if(layer_state_is(WORKMAN_PG))
                    layer_move(WORKMAN);
                else
                    layer_move(QWERTY);
            }
        break;
        case SW_LY:
            if(!record->event.pressed) {
                if(layer_state_is(QWERTY))
                    layer_move(WORKMAN);
                else if(layer_state_is(QWERTY_PG))
                    layer_move(WORKMAN_PG);
                else if(layer_state_is(WORKMAN))
                    layer_move(QWERTY);
                else if(layer_state_is(WORKMAN_PG))
                    layer_move(QWERTY_PG);
                else
                    layer_move(QWERTY);
            }
        break;
        case SW_GM:
            if(!record->event.pressed) {
                if(layer_state_is(GAMES))
                    layer_off(GAMES);
                else
                    layer_on(GAMES);
            }
        break;
    }
    if(keycode >= SW_OS)
        set_autoshift();
    return true;
}

void leader_end_user(void) {
    if(leader_sequence_one_key(KC_PRIM)) {
        SEND_STRING("clear");
        tap_code(KC_ENT);
    } else if(leader_sequence_one_key(KC_TAB)){
        SEND_STRING(SS_LCTL(SS_LSFT("t")));
    } else if(leader_sequence_two_keys(KC_TAB, KC_TAB)){
        SEND_STRING(SS_LCTL("t"));
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    bool LED_2 = false;
    bool LED_3 = false;
    bool LED_4 = false;
    bool LED_5 = false;
    bool LED_6 = false;
    uint8_t layer = get_highest_layer(state);
    if(layer == WORKMAN_PG || layer == QWERTY_PG)
        LED_2 = true;
    if(layer == WORKMAN || layer == WORKMAN_PG)
        LED_3 = true;
    switch(layer) {
        case GAMES:
            LED_4 = true;
        break;
        case SYMBOLS:
            LED_5 = true;
        break;
        default:
        break;
    }
    ML_LED_2(LED_2);
    ML_LED_3(LED_3);
    ML_LED_4(LED_4);
    ML_LED_5(LED_5);
    ML_LED_6(LED_6);
    return state;
}
