/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

// Layer names
enum layers {
    _QWERTY,
    _COLEMAKDH,
    _BUTTON,
    _FUN,
    _MEDIA,
    _NAV,
    _NUM,
    _SYM,
    _MOUSE,
};

// Tap dance declarations
enum {
    U_TD_U_FUN,
    U_TD_U_MEDIA,
    U_TD_U_TAP,
    U_TD_BOOT,
    U_TD_U_BASE,
    U_TD_U_EXTRA
};

// Custom keycodes
enum custom_keycodes {
    MY_PWD1 = SAFE_RANGE,
    MY_PWD2,
};

// Send string on key press
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_PWD1:
            if (record->event.pressed) {
                SEND_STRING("My dog has 26 fleas!");
            }
            return false;
        case MY_PWD2:
            if (record->event.pressed) {
                SEND_STRING("L3ahc!m");
            }
            return false;
    }
    return true;
}

void td_nav_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_T);
    } else if (state->pressed) {
        layer_on(_NAV);
    }
}

void td_nav_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        layer_off(_NAV);
    }
}

void td_fun_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_E);
    } else if (state->pressed) {
        layer_on(_FUN);
    }
}

void td_fun_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        layer_off(_FUN);
    }
}

void td_media_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_M);
    } else if (state->pressed) {
        layer_on(_MEDIA);
    }
}

void td_media_reset(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        layer_off(_MEDIA);
    }
}

void dance_boot(tap_dance_state_t *state, void *user_data) {
    reset_keyboard();
}

tap_dance_action_t tap_dance_actions[] = {
    [U_TD_U_FUN]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_fun_finished, td_fun_reset),
    [U_TD_U_MEDIA]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_media_finished, td_media_reset),
    [U_TD_U_TAP]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_nav_finished, td_nav_reset),
    [U_TD_BOOT]     = ACTION_TAP_DANCE_FN(dance_boot),
    [U_TD_U_BASE]   = ACTION_TAP_DANCE_DOUBLE(KC_Q, TO(_QWERTY)),
    [U_TD_U_EXTRA]  = ACTION_TAP_DANCE_DOUBLE(KC_W, TO(_COLEMAKDH))
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_ENT, XXXXXXX,      KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   HMQ_A,   HMQ_S,   HMQ_D,   HMQ_F,    KC_G,    KC_F5, XXXXXXX,      KC_H,   HMQ_J,   HMQ_K,   HMQ_L,HMQ_QUOT, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         MED_ESC, NAV_BSPC, MOU_TAB,    SYM_ENT, NUM_SPC,  FUN_DEL
                                      //`--------------------------'  `--------------------------'

  ),

    [_COLEMAKDH] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,  XXXXXXX, XXXXXXX,      KC_J,    KC_L,    KC_U,    KC_Y, KC_QUOT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   HMC_A,   HMC_R,   HMC_S,   HMC_T,    KC_G,  XXXXXXX, XXXXXXX,      KC_M,   HMC_N,   HMC_E,   HMC_I,   HMC_O, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        MED_ESC, NAV_BSPC, MOU_TAB,    SYM_ENT, NUM_SPC,  FUN_DEL
                                      //`--------------------------'  `--------------------------'
  ),

    [_BUTTON] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,   U_UND,   U_CUT,   U_CPY,   U_PST,   U_RDO,  XXXXXXX, XXXXXXX,     U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,  XXXXXXX, XXXXXXX,   XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   U_UND,   U_CUT,   U_CPY,   U_PST,   U_RDO,                        U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_BTN3,  KC_BTN2,  KC_BTN1,    KC_BTN1, KC_BTN2, KC_BTN3
                                      //`--------------------------'  `--------------------------'
  ),

    [_MEDIA] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,   RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,   KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MUTE, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_NAV] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F5, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,     U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_F10, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,  XXXXXXX, XXXXXXX,   KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, CW_TOGG, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_F11,  KC_ENT, KC_BSPC, KC_DEL,   KC_SPC, XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_INS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_MOUSE] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  MY_PWD1, XXXXXXX,     U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,  MY_PWD2, XXXXXXX,   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_BTN3,  KC_BTN2,  KC_BTN1,    KC_BTN1, KC_BTN2, KC_BTN3
                                      //`--------------------------'  `--------------------------'
  ),

    [_SYM] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,  XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_COLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS,  XXXXXXX, XXXXXXX,   XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LPRN, KC_RPRN, KC_UNDS,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
 ),

    [_NUM] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC,   XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL,   XXXXXXX, XXXXXXX,   XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_DOT,    KC_0, KC_MINS,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_FUN] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------------------------------------.
      XXXXXXX,  KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,  DT_PRNT,   DT_UP,      KC_X,     TO(_QWERTY),   TO(_COLEMAKDH), TD(U_TD_U_TAP), TD(U_TD_BOOT), XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+----------------+-----------------+---------------+--------------+--------|
      XXXXXXX,  KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL,  XXXXXXX, DT_DOWN,   XXXXXXX,         KC_LSFT,          KC_LCTL,        KC_LALT,       KC_LGUI, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+----------------+-----------------+---------------+--------------+--------|
      XXXXXXX,  KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS,                      XXXXXXX,  TD(U_TD_U_FUN), TD(U_TD_U_MEDIA),        KC_ALGR,       XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+----------------+-----------------+---------------+--------------+--------|
                                           KC_APP,  KC_SPC,  KC_TAB,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif
