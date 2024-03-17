/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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
#include "pogues.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [LCMK] = LAYOUT_split_3x5_3(
    //,--------------------------------------------.                    ,--------------------------------------------.
          KC_Q,   CTL_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,  CTL_Y,  MY_COMP,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
          KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         SFT_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, SFT_SLS,
    //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                KC_LGUI, OSL(LNUM), MOV_SPC,    SFT_BSP, OSL(LSYM), KC_LALT
                              //`--------------------------'  `--------------------------'
    ),

    [LSYM] = LAYOUT_split_3x5_3(
    //,--------------------------------------------.                    ,--------------------------------------------.
        KC_NO, CTL_QUES, KC_LPRN, KC_RPRN, KC_PERC,                      KC_EXLM, MY_PIPE, KC_UNDS,  CTL_AT, KC_NUBS,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       MY_TILD,  KC_GRV, KC_LBRC, KC_RBRC, KC_ASTR,                      KC_NUHS, MY_DQUO, KC_QUOT, KC_SCLN, KC_COLN,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        KC_EQL,  MY_GBP, KC_LCBR, KC_RCBR, KC_SLSH,                      KC_AMPR,   KC_LT,   KC_GT,  KC_DLR, KC_CIRC,
    //|--------+--------+--------+--------+--------|--------|  |--------+--------+--------+--------+--------+--------|
                                  _______, TO(LCMK), KC_SPC,    _______, _______, _______
                               //`--------------------------'  `--------------------------'
    ),

    [LNUM] = LAYOUT_split_3x5_3(
    //,--------------------------------------------.                    ,--------------------------------------------.
       MO(LFUN), KC_LCTL, KC_UNDS, KC_INS, KC_PERC,                       KC_PLUS,    KC_7,    KC_8,    KC_9, KC_EXLM,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT, KC_ASTR,                       KC_MINS,    KC_4,    KC_5,    KC_6, KC_ASTR,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       KC_BSPC,  KC_SPC, KC_COMM,  KC_DOT, KC_SLSH,                        KC_EQL,    KC_1,    KC_2,    KC_3, KC_SLSH,
    //|--------+--------+--------+--------+--------|--------|  |--------+--------+--------+--------+--------+--------|
                                 _______, _______,  KC_SPC,      _______, KC_0, _______
                               //`--------------------------'  `--------------------------'
    ),

    [LFUN] = LAYOUT_split_3x5_3(
    //,--------------------------------------------.                    ,--------------------------------------------.
         KC_NO, KC_LCTL,   KC_NO,   KC_NO,   KC_NO,                       KC_F10,   KC_F7,   KC_F8,   KC_F9, KC_NO,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT,   KC_NO,                       KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_NO,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                       KC_F12,   KC_F1,   KC_F2,   KC_F3, KC_NO,
    //|--------+--------+--------+--------+--------|--------|  |--------+--------+--------+--------+--------+--------|
                                 _______, TO(LCMK),  KC_SPC,    _______, TO(LCMK), _______
                               //`--------------------------'  `--------------------------'
    ),

    [LMOV] = LAYOUT_split_3x5_3(
    //,--------------------------------------------.                    ,--------------------------------------------.
        XXXXXXX, KC_LCTL, ALT_TAB,   KC_NO,   KC_NO,                     KC_PGUP, KC_HOME,   KC_UP,  KC_END,  KC_DEL,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT,   KC_NO,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,  KC_ENT,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        C(KC_Z), C(KC_X), C(KC_C),   KC_NO, C(KC_V),                       KC_NO,  KC_PGDN, KC_PGUP, KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------|--------|  |--------+--------+--------+--------+--------+--------|
                                  _______,  KC_NO, _______,      _______, KC_NO, _______
                               //`--------------------------'  `--------------------------'
    ),
#ifdef MOUSEKEY_ENABLE
    [LMSE] = LAYOUT_split_3x5_3(
    //,--------------------------------------------.                    ,--------------------------------------------.
         KC_NO,  KC_ESC,  KC_TAB,   KC_NO,   KC_NO,                      KC_NO,   KC_NO, KC_MS_U,   KC_NO,  KC_DEL,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT,   KC_NO,                      KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        C(KC_Z), C(KC_X), C(KC_C),   KC_NO, C(KC_V),                     KC_WH_D, KC_WH_D,  KC_WH_U,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------|--------|  |--------+--------+--------+--------+--------+--------|
                                   _______,TO(LCMK),  KC_SPC,   KC_BTN1,  KC_BTN2, KC_BTN3
                               //`--------------------------'  `--------------------------'
    ),
#endif
};


/******************************************************************************
 * user specific key processing
 ******************************************************************************/

// method to process a tap and hold key.  generally should use the MT(mod, tap) methods but they
// have a limitation in that they do not work for shifted values so handle those cases here
// TODO - refactor with crkbd.  need to separate the set_mods_lights
void process_tap_and_hold(uint16_t keycode, keyrecord_t* record, uint16_t tap_key, uint16_t hold_key) {
    if (record->tap.count > 0) { // tapped
        if (record->event.pressed) {
            tap_code16(tap_key);
        }
    } else { // held
        if (record->event.pressed) {
            register_code16(hold_key);
        } else {
            unregister_code16(hold_key);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_achordion(keycode, record)) {
        return false;
    }
    if (!process_compose(keycode, record, MY_COMP)) {
        return false;
    }
    switch (keycode) {
        case CTL_QUES:
            process_tap_and_hold(keycode, record, KC_QUES, KC_LCTL);
            return false;
        case CTL_AT:
            process_tap_and_hold(keycode, record, MY_AT, KC_LCTL);
            return false;
    }

    return true;
}


void matrix_scan_user(void) {
    achordion_task();
}


/******************************************************************************
 * combo keys
 * TODO - match with crkbd
 ******************************************************************************/
enum combo_keys {
    // left hand only
    CMK_ESC,        // wf

    CMK_TAB,        // cd
    NUM_TAB,

    // uy on all layers for delete
    CMK_DEL,   // uy
    SYM_DEL,
    NUM_DEL,
    FUN_DEL,
    // h, on all layers for enter
    CMK_ENT,
    SYM_ENT,
    NUM_ENT,
    FUN_ENT,

    // both hands, not using pl / fu any more due to typing mishits
    WY_LFUN,
    SS_LMSE,

    // put the board into bootloader mode  (needs mouse layer)
    RESET_COMBO,

    // for skeletyl have alternates for upper row pinkie
    ZX_Q,
    DOTSLSH_COMPOSE,

    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM combo_esc[] = {CTL_W, KC_F, COMBO_END};

const uint16_t PROGMEM combo_tab[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM combo_ntab[] = {KC_COMM, KC_DOT, COMBO_END};

const uint16_t PROGMEM combo_del[] = {KC_U, CTL_Y, COMBO_END};
const uint16_t PROGMEM combo_sdel[] = {KC_UNDS, MY_AT, COMBO_END};
const uint16_t PROGMEM combo_ndel[] = {KC_8, KC_9, COMBO_END};
const uint16_t PROGMEM combo_fdel[] = {KC_F8, KC_F9, COMBO_END};

const uint16_t PROGMEM combo_ent[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_sent[] = {KC_LT, KC_GT, COMBO_END};
const uint16_t PROGMEM combo_fent[] = {KC_F1, KC_F2, COMBO_END};
const uint16_t PROGMEM combo_nent[] = {KC_1, KC_2, COMBO_END};

const uint16_t PROGMEM combo_function[] = {CTL_W, CTL_Y, COMBO_END};
const uint16_t PROGMEM combo_mouse[] = {SFT_Z, SFT_SLS, COMBO_END};

const uint16_t PROGMEM combo_q[] = {SFT_Z, KC_X, COMBO_END};
const uint16_t PROGMEM combo_compose[] = {KC_DOT, SFT_SLS, COMBO_END};

const uint16_t PROGMEM combo_reset[] = {KC_ESC, KC_TAB, COMBO_END};

combo_t key_combos[] = {
    [CMK_ESC] = COMBO(combo_esc, KC_ESC),

    [CMK_TAB] = COMBO(combo_tab, KC_TAB),
    [NUM_TAB] = COMBO(combo_ntab, KC_TAB),

    [CMK_DEL] = COMBO(combo_del, KC_DEL),
    [SYM_DEL] = COMBO(combo_sdel, KC_DEL),
    [NUM_DEL] = COMBO(combo_ndel, KC_DEL),
    [FUN_DEL] = COMBO(combo_fdel, KC_DEL),

    [CMK_ENT] = COMBO(combo_ent, KC_ENT),
    [SYM_ENT] = COMBO(combo_sent, KC_ENT),
    [NUM_ENT] = COMBO(combo_nent, KC_ENT),
    [FUN_ENT] = COMBO(combo_fent, KC_ENT),

    [WY_LFUN] = COMBO(combo_function, TO(LFUN)),
#ifdef MOUSEKEY_ENABLE
    [SS_LMSE] = COMBO(combo_mouse, TO(LMSE)),
    [RESET_COMBO] = COMBO(combo_reset, QK_BOOTLOADER),
#endif

    [ZX_Q] = COMBO(combo_q, KC_Q),
    [DOTSLSH_COMPOSE] = COMBO(combo_compose, MY_COMP),
};

/******************************************************************************
 * combo keys end
 ******************************************************************************/

