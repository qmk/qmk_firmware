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
#include "features/casemodes.h"
#include "features/compose.h"

enum userspace_layers {
    LCMK = 0,
    LSYM = 1,
    LNUM = 2,
    LFUN = 3,
    LMOV = 4,
#ifdef MOUSEKEY_ENABLE
    LMSE = 5,
#endif
};

// rename some keys here to allow for the difference in keymap between US and GB
#define MY_PIPE LSFT(KC_NUBS)
#define MY_TILD KC_PIPE
#define MY_AT KC_DQUO
#define MY_DQUO LSFT(KC_2)
#define MY_GBP KC_HASH      // just shift-3
#define ALT_TAB ALT_T(KC_TAB)

// one shot mod and layer keys to make the map shorter
#define OSM_ALT OSM(MOD_LALT)
#define OSM_GUI OSM(MOD_LGUI)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_SFT OSM(MOD_LSFT)

#define SFT_BSP SFT_T(KC_BSPC)
#define CTL_SPC CTL_T(KC_SPC)

#define CTL_W CTL_T(KC_W)
#define CTL_Y CTL_T(KC_Y)
#define SFT_Z SFT_T(KC_Z)
#define SFT_SLS SFT_T(KC_SLSH)
#define MOV_SPC LT(LMOV, KC_SPC)

enum custom_keycodes {
    MY_COMP = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [LCMK] = LAYOUT_split_3x5_3(
    //,--------------------------------------------.                    ,--------------------------------------------.
          KC_Q,   CTL_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,  CTL_Y,  MY_COMP,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
          KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         SFT_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, SFT_SLS,
    //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                              //KC_LGUI, MO(LNUM), MOV_SPC,     SFT_BSP, MO(LSYM) , KC_LALT
                                KC_LGUI, MOV_SPC, MO(LNUM),     MO(LSYM), SFT_BSP, KC_LALT
                              //`--------------------------'  `--------------------------'
    ),

    [LSYM] = LAYOUT_split_3x5_3(
    //,--------------------------------------------.                    ,--------------------------------------------.
        KC_NO,  KC_QUES, KC_LPRN, KC_RPRN, KC_PERC,                      KC_EXLM, MY_PIPE, KC_UNDS,   MY_AT, KC_NUBS,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       MY_TILD,  KC_GRV, KC_LBRC, KC_RBRC, KC_ASTR,                      KC_NUHS, MY_DQUO, KC_QUOT, KC_SCLN, KC_COLN,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        KC_EQL,  MY_GBP, KC_LCBR, KC_RCBR, KC_SLSH,                      KC_AMPR,   KC_LT,   KC_GT,  KC_DLR, KC_CIRC,
    //|--------+--------+--------+--------+--------|--------|  |--------+--------+--------+--------+--------+--------|
                                 _______, CTL_SPC,  _______,     _______, _______, _______
                               //`--------------------------'  `--------------------------'
    ),

    [LNUM] = LAYOUT_split_3x5_3(
    //,--------------------------------------------.                    ,--------------------------------------------.
        KC_NO,   KC_NO, KC_UNDS,   KC_NO, KC_PERC,                       KC_PLUS,    KC_7,    KC_8,    KC_9, KC_BSPC,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT, KC_ASTR,                      KC_MINS,    KC_4,    KC_5,    KC_6, KC_ASTR,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
          KC_NO,   KC_NO, KC_COMM,  KC_DOT, KC_SLSH,                      KC_EQL,    KC_1,    KC_2,    KC_3, KC_SLSH,
    //|--------+--------+--------+--------+--------|--------|  |--------+--------+--------+--------+--------+--------|
                                 _______, _______,  _______,    _______,  KC_0, _______
                               //`--------------------------'  `--------------------------'
    ),

    [LMOV] = LAYOUT_split_3x5_3(
    //,--------------------------------------------.                    ,--------------------------------------------.
        XXXXXXX, ALT_TAB, RGB_VAD, RGB_VAI, RGB_TOG,                     KC_PGUP, KC_HOME,   KC_UP,  KC_END,  KC_DEL,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT,   KC_NO,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,  KC_ENT,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        C(KC_Z), C(KC_X), C(KC_C),   KC_NO, C(KC_V),                       KC_NO,  KC_TAB, KC_PGDN, KC_PGUP,   KC_NO,
    //|--------+--------+--------+--------+--------|--------|  |--------+--------+--------+--------+--------+--------|
                                  _______, _______,  KC_NO,      KC_NO, _______, _______
                               //`--------------------------'  `--------------------------'
    ),
#ifdef MOUSEKEY_ENABLE
    [LMSE] = LAYOUT_split_3x5_3(
    //,--------------------------------------------.                    ,--------------------------------------------.
        TO(LCMK),  KC_ESC,  KC_TAB,   KC_NO,   KC_NO,                      KC_NO,   KC_NO, KC_MS_U,   KC_NO,  KC_DEL,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT,   KC_NO,                      KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,
    //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        C(KC_Z), C(KC_X), C(KC_C),   KC_NO, C(KC_V),                     KC_WH_D,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------|--------|  |--------+--------+--------+--------+--------+--------|
                                   _______,TO(LCMK),  KC_SPC,   KC_BTN1,  KC_BTN2, KC_BTN3
                               //`--------------------------'  `--------------------------'
    ),
#endif
};


/******************************************************************************
 * user specific key processing
 ******************************************************************************/

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_compose(keycode, record, MY_COMP)) {
        return false;
    }
    if (!process_case_modes(keycode, record)) {
        return false;
    }

    return true;
}


/******************************************************************************
 * combo keys
 ******************************************************************************/
enum combo_keys {
    // naming is combo _ hand _ fingers (r=ring, m=middle, i=index) _ row (t=top, b=bottom) _ key
    // left hand only
    WF_ESC,
    CD_TAB,
    ZX_Q,

    RESET_COMBO,

    // right hand only
    UY_DEL,
    HCOM_ENT,
    JY_CTLBSP,

    // both hands, not using pl / fu any more due to typing mishits
    // moved movement (fu) to left thumb hold and function to tri state
    WY_LMSE,

    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM combo_esc[] = {CTL_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM combo_del[] = {KC_U, CTL_Y, COMBO_END};
const uint16_t PROGMEM combo_ent[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_bspc[] = {KC_J, CTL_Y, COMBO_END};
const uint16_t PROGMEM combo_q[] = {SFT_Z, KC_X, COMBO_END};
const uint16_t PROGMEM combo_mouse[] = {CTL_W, CTL_Y, COMBO_END};

combo_t key_combos[] = {
    [WF_ESC] = COMBO(combo_esc, KC_ESC),
    [CD_TAB] = COMBO(combo_tab, KC_TAB),
    [ZX_Q] = COMBO(combo_q, KC_Q),

    [UY_DEL] = COMBO(combo_del, KC_DEL),
    [HCOM_ENT] = COMBO(combo_ent, KC_ENT),
    [JY_CTLBSP] = COMBO(combo_bspc, LCTL(KC_BSPC)),
#ifdef MOUSEKEY_ENABLE
    [WY_LMSE] = COMBO(combo_mouse, TO(LMSE)),
#endif
};

/******************************************************************************
 * combo keys end
 ******************************************************************************/

/******************************************************************************
 * compose key mapping function
 ******************************************************************************/
uint8_t compose_mapping(uint16_t* sequence, uint8_t sequence_len) {
    // NOTE that the COMPOSE_MAPPING will return if there is a full or partial
    // match to the sequence.

    /**********************************************************************
     * general
     *********************************************************************/
    // caps word
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_C),
        { toggle_caps_word(); }
    )

    // quit dwm
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_Q),
        { SEND_STRING(SS_LGUI(SS_LSFT("q"))); }
    )

    /**********************************************************************
     * copy paste
     *********************************************************************/
    // copy all
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_A, KC_C),
        { SEND_STRING(SS_LCTL("ac")); }
    )
    // cut all
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_A, KC_X),
        { SEND_STRING(SS_LCTL("ax")); }
    )
    // paste
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_A, KC_P),
        { SEND_STRING(SS_LCTL("v")); }
    )

    /**********************************************************************
     * qzdev
     *********************************************************************/
    // open a file
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_O),
        { SEND_STRING(SS_LCTL(SS_LSFT("o"))); }
    )

    /**********************************************************************
     * qzdev diff
     *********************************************************************/
    // diff current
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_C),
        { SEND_STRING(SS_LCTL(SS_LSFT("g"))); }
    )
    // diff approved
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_A),
        { SEND_STRING(SS_LCTL(SS_LSFT("v"))); }
    )
    // diff prod
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_P),
        { SEND_STRING(SS_LCTL(SS_LSFT("p"))); }
    )
    // diff head
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_H),
        { SEND_STRING(SS_LCTL(SS_LSFT("e"))); }
    )
    // diff against version
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_V),
        { SEND_STRING(SS_LCTL(SS_LSFT("d"))); }
    )

    /**********************************************************************
     * qzdev vc
     *********************************************************************/
    // vc blame
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_B),
        { SEND_STRING(SS_LCTL(SS_LSFT("b"))); }
    )

    // vc log
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_L),
        { SEND_STRING(SS_LCTL(SS_LSFT("l"))); }
    )

    // vc commit
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_C),
        { SEND_STRING(SS_LCTL(SS_LSFT("c"))); }
    )

    // vc request review
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_R),
        { SEND_STRING(SS_LCTL(SS_LSFT("w"))); }
    )

    // push to
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_P),
        { SEND_STRING(SS_LCTL(SS_LSFT("s"))); }
    )

    // vc update
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_U),
        { SEND_STRING(SS_LCTL(SS_LSFT("u"))); }
    )

    /**********************************************************************
     * qzdev run test
     *********************************************************************/
    // run test function
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_T, KC_F),
        { SEND_STRING(SS_LCTL(SS_TAP(X_F10))); }
    )
    // run test class
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_T, KC_C),
        { SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_F10)))); }
    )
    // run test module
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_T, KC_S),
        { SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_F10)))); }
    )

    /**********************************************************************
     * qzdev run
     *********************************************************************/
    // run script
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_R, KC_S),
        { tap_code(KC_F9); }
    )
    // run script with restart
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_R, KC_R),
        { SEND_STRING(SS_LCTL(SS_TAP(X_F9))); }
    )

    return COMPOSE_ERROR;
}


/******************************************************************************
 * compose end
 ******************************************************************************/

