// Copyright 2023 Your Name (@rpbaptist)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rpbaptist.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAKDH] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, BSP_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TAB_NUM,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LCTL_BR,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, RCTL_BR,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,   T_SYM, SFT_SPC,    SFT_ENT,   T_NAV, KC_RGUI \
                                      //`--------------------------'  `--------------------------'
  ),

  [_GAMING] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, KC_RCTL,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          EXTALT, KC_LSFT,  KC_SPC,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_WASD] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_T,    KC_Q,    KC_W,    KC_E,    KC_R,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_G,    KC_A,    KC_S,    KC_D,    KC_F,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_B,    KC_Z,    KC_X,    KC_C,    KC_V,                         KC_N,    KC_M, _______, _______, _______, KC_RCTL,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          EXTALT, KC_LSFT,  KC_SPC,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_GAMING_EXT] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,    KC_Y,    KC_I,    KC_J,    KC_M,    KC_N,                      _______, _______, _______, _______, _______,  KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS,    KC_6,    KC_7, KC_LBRC, KC_RBRC, KC_BSLS,                      _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_LALT, KC_ENT,     KC_ENT, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUMPAD] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, XXXXXXX, KC_MPRV, KC_VOLU, KC_MNXT, XXXXXXX,                       KC_EUR,    KC_7,    KC_8,    KC_9, _______, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        S_NUM, XXXXXXX, KC_MSTP, KC_VOLD, KC_MPLY, XXXXXXX,                      KC_UNDS,    KC_4,    KC_5,    KC_6, KC_MINS, KC_PLUS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      SC_LCPO, XXXXXXX, XXXXXXX, KC_MUTE, KC_PSCR,  KC_NUM,                       KC_EQL,    KC_1,    KC_2,    KC_3, KC_SLSH, KC_ASTR,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,    KC_0,  KC_DOT \
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYM] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_MINS, KC_PLUS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      SC_LCPO, XXXXXXX, XXXXXXX, XXXXXXX,  KC_EUR, XXXXXXX,                       KC_EQL, KC_PIPE,   KC_LT,   KC_GT, KC_EXLM, SC_RCPC,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,   S_SYM, _______,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAV] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END,  KC_INS, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TILD,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      SC_LCPO,  KC_F11,  KC_F12,  KC_F13, KC_PSCR, KC_CAPS,                      WIN_CLS, TAB_BCK, TAB_CLS, TAB_FWD, KC_BSLS, SC_RCPC,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+---------|
                                          _______, _______, _______,    _______,   S_NAV, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_UTIL] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, RGB_RST, XXXXXXX, XXXXXXX, XXXXXXX,  TYPING,                      RGB_ATG, XXXXXXX, XXXXXXX, RGB_IDL, RGB_UND, RGB_TOG,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LCK_NMP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  GAMING,                      RGB_PST, XXXXXXX, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       EE_CLR, KC_SLEP, XXXXXXX, XXXXXXX, XXXXXXX,    WASD,                      RGB_PCT, XXXXXXX, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(default_layer_state)) {
        case _COLEMAKDH:
            state = update_tri_layer_state(state, _SYM, _NAV, _UTIL);
            break;
        case _GAMING:
        case _WASD:
            state = update_tri_layer_state(state, _GAMING_EXT, _NAV, _UTIL);
            break;
    }
    return state;
}

void suspend_power_down_keymap(void) {
#ifdef OLED_ENABLE
    oled_off();
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
#endif
}

void suspend_wakeup_init_keymap(void) {
#ifdef OLED_ENABLE
    oled_on();
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(false);
#endif
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_ENT:
            return TAPPING_TERM - 20;
        default:
            return TAPPING_TERM;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t saved_mods   = 0;
    uint16_t       temp_keycode = keycode;

#ifdef RGB_MATRIX_ENABLE
    process_record_user_rgb_matrix(temp_keycode, record);
#endif

    // Filter out the actual keycode from MT and LT keys.
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        temp_keycode &= 0xFF;
    }

    switch (temp_keycode) {
        case BSP_DEL:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;

                if (saved_mods == MOD_MASK_SHIFT) { // Both shifts pressed
                    register_code(KC_DEL);
                } else if (saved_mods) {  // One shift pressed
                    del_mods(saved_mods); // Remove any Shifts present
                    register_code(KC_DEL);
                    add_mods(saved_mods); // Add shifts again
                } else {
                    register_code(KC_BSPC);
                }
            } else {
                unregister_code(KC_DEL);
                unregister_code(KC_BSPC);
            }
            return false;
        case TYPING:
            if (record->event.pressed) {
#ifdef RGB_MATRIX_ENABLE
                rgb_matrix_set_typing_defaults();
#endif
                default_layer_set(1U << _COLEMAKDH);
            }
            return true;
        case GAMING:
            if (record->event.pressed) {
#ifdef RGB_MATRIX_ENABLE
                rgb_matrix_set_gaming_defaults();
#endif
                default_layer_set(1U << _GAMING);
            }
            return true;
        case WASD:
            if (record->event.pressed) {
#ifdef RGB_MATRIX_ENABLE
                rgb_matrix_set_gaming_defaults();
#endif
                default_layer_set(1U << _WASD);
            }
            return true;
    }
    return true;
}

// Override functions to save memory
// https://docs.qmk.fm/#/squeezing_avr?id=magic-keycodes
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}

uint8_t mod_config(uint8_t mod) {
    return mod;
}
