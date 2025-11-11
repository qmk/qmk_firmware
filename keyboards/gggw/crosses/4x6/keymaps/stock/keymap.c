// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/*
 * Keycodes, combos, and layers! oh my!
 */

enum CROSSES_LAYERS { _BASE, _NUM, _NAV, _MEDIA, _FUNC, _MOUS, _CUST };

enum crosses_keycode { C_MINC = QK_KB_0, C_MDEC, C_MTOGG, C_DRAG };

#define CTAB LCTL_T(KC_TAB)
#define SCLM LT(_MEDIA, KC_SCLN)
#define C_SMOUS LT(_MOUS, KC_SPC)
#define LNAV MO(_NAV)
#define RENTR LT(_NUM, KC_ENT)
#define LNUM MO(_NUM)
#define RALTD RALT_T(KC_DEL)

/*
 * Keymaps!
 */

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_4x6(
     //,-------------------------------------------------------.                      ,--------------------------------------------------------.
        KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5      ,                       KC_6  , KC_7   ,KC_8    ,KC_9       ,KC_0    ,KC_MINUS  ,
     //|--------+--------+--------+--------+--------+----------|                      |------+--------+--------+-----------+--------+----------|
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                             KC_Y,  KC_U,    KC_I,    KC_O,       KC_P,    KC_BSPC   ,
     //|--------+--------+--------+--------+--------+----------|                      |------+--------+--------+-----------+--------+----------|
        CTAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                             KC_H,  KC_J,    KC_K,    KC_L,       SCLM,    KC_QUOT   ,
     //|--------+--------+--------+--------+--------+----------|                      |------+--------+--------+-----------+--------+----------|
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                             KC_N,  KC_M,    KC_COMM, KC_DOT,     KC_SLSH, KC_RSFT   ,
     //|--------+--------+--------+--------+--------+----------+---------|    |-------+------+--------+--------+-----------+--------+----------|
                                            KC_LGUI,  LNAV,     C_SMOUS,       RENTR,    LNUM,  RALTD
                                         //`-----------------------------'    `-----------------------'
    ),
    [_NUM] = LAYOUT_4x6(
     //,-------------------------------------------------------.                      ,--------------------------------------------------------.
        KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO  ,KC_NO      ,                       KC_NO   , KC_NO  ,KC_NO   ,KC_NO      ,KC_NO   ,KC_NO   ,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_ESC,  S(KC_8), KC_7,    KC_8,    KC_9,    KC_SLSH,                          KC_BSLS, S(KC_9), S(KC_0), S(KC_BSLS), KC_TRNS, KC_BSPC,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_LCTL, KC_MINS, KC_4,    KC_5,    KC_6,    S(KC_EQL),                        S(KC_5), KC_LBRC, KC_RBRC, S(KC_SCLN), KC_SCLN, KC_QUOT,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_LSFT, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_EQL,                           KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS,    KC_TRNS, KC_RSFT,
     //|--------+--------+--------+--------+--------+----------+---------|   |--------+--------+--------+--------+-----------+--------+--------|
                                            KC_TRNS, KC_0,       KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
                                         //`-----------------------------'   `--------------------------'
    ),
    [_NAV] = LAYOUT_4x6(
     //,-------------------------------------------------------.                      ,--------------------------------------------------------.
        KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO  ,KC_NO      ,                       KC_NO   , KC_NO  ,KC_NO   ,KC_NO      ,KC_NO   ,KC_NO   ,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                            KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_NO,   KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                            KC_NO,   KC_LEFT, KC_DOWN, KC_UP,      KC_RGHT, KC_NO,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_COPY, KC_PSTE, KC_NO,                            KC_NO,   KC_HOME, KC_END,  KC_PGDN,    KC_PGUP, KC_NO,
     //|--------+--------+--------+--------+--------+----------+---------|   |--------+--------+--------+--------+-----------+--------+--------|
                                            KC_NO,   KC_NO,     KC_NO,        KC_NO,   KC_NO,   KC_NO
                                         //`-----------------------------'   `--------------------------'
    ),
    [_MEDIA] = LAYOUT_4x6(
     //,-------------------------------------------------------.                      ,--------------------------------------------------------.
        KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO  ,KC_NO      ,                       KC_NO   , KC_NO  ,KC_NO   ,KC_NO      ,KC_NO   ,KC_NO   ,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                            KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_NO,   KC_MPRV, KC_VOLD, KC_MPLY, KC_VOLU, KC_MNXT ,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                            KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,
     //|--------+--------+--------+--------+--------+----------+---------|   |--------+--------+--------+--------+-----------+--------+--------|
                                            KC_NO,   KC_NO,     KC_NO,        KC_NO,   KC_NO,   KC_NO
                                         //`-----------------------------'   `--------------------------'
    ),
    [_FUNC] = LAYOUT_4x6(
     //,-------------------------------------------------------.                      ,--------------------------------------------------------.
        KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO  ,KC_NO      ,                       KC_NO   , KC_NO  ,KC_NO   ,KC_NO      ,KC_NO   ,KC_NO   ,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_NO   ,KC_F11  ,KC_F12  ,KC_F13  ,KC_F14,  KC_F15    ,                       KC_TRNS, KC_TRNS ,KC_TRNS ,KC_TRNS    ,KC_TRNS ,KC_NO   ,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_NO   , KC_F6  ,KC_F7   ,KC_F8   ,KC_F9,   KC_F10    ,                       KC_TRNS ,KC_RSFT ,KC_RCTL ,KC_RALT    ,KC_RGUI ,KC_NO   ,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_NO   ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   , KC_F5    ,                       KC_TRNS ,KC_TRNS , KC_TRNS,KC_TRNS    ,KC_TRNS, KC_NO   ,
     //|--------+--------+--------+--------+--------+----------+---------|   |--------+--------+--------+--------+-----------+--------+--------|
                                            KC_TRNS , KC_TRNS  , KC_TRNS ,    KC_TRNS ,KC_TRNS ,KC_TRNS
                                         //`-----------------------------'   `--------------------------'
    ),
    [_MOUS] = LAYOUT_4x6(
     //,-------------------------------------------------------.                      ,--------------------------------------------------------.
        KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO  ,KC_NO      ,                       KC_NO   , KC_NO  ,KC_NO   ,KC_NO      ,KC_NO   ,KC_NO   ,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_NO   ,KC_LSFT ,KC_LALT ,KC_NO   ,KC_NO   ,KC_NO     ,                       KC_NO   ,C_MINC   ,C_MDEC ,KC_NO      ,KC_NO   ,C_MTOGG ,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_NO   ,KC_LCTL ,MS_BTN3 ,MS_BTN2 ,MS_BTN1 ,KC_NO     ,                       KC_NO   ,KC_RSFT ,KC_RCTL ,KC_RALT    ,KC_RGUI ,KC_NO   ,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_NO   ,KC_LGUI ,KC_NO   ,KC_NO   ,C_DRAG  ,KC_NO     ,                       KC_NO   ,KC_NO   ,KC_NO   ,KC_NO      ,KC_NO   ,KC_NO   ,
     //|--------+--------+--------+--------+--------+----------+---------|   |--------+--------+--------+--------+-----------+--------+--------|
                                            KC_TRNS ,KC_NO     , KC_NO   ,    KC_NO   ,KC_NO   ,KC_NO
                                         //`-----------------------------'   `--------------------------'
    ),
    [_CUST] = LAYOUT_4x6(
     //,-------------------------------------------------------.                      ,--------------------------------------------------------.
        KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO  ,KC_NO      ,                       KC_NO   , KC_NO  ,KC_NO   ,KC_NO      ,KC_NO   ,KC_NO   ,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO  ,KC_NO      ,                       KC_NO   , KC_NO  ,KC_NO   ,KC_NO      ,KC_NO   ,KC_NO   ,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO  ,KC_NO      ,                       KC_NO   , KC_NO  ,KC_NO   ,KC_NO      ,KC_NO   ,KC_NO   ,
     //|--------+--------+--------+--------+--------+----------|                      |--------+--------+--------+-----------+--------+--------|
        KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO  ,KC_NO      ,                       KC_NO   , KC_NO  ,KC_NO   ,KC_NO      ,KC_NO   ,KC_NO   ,
     //|--------+--------+--------+--------+--------+----------+---------|   |--------+--------+--------+--------+-----------+--------+--------|
                                            KC_NO  ,KC_NO      ,KC_NO    ,    KC_NO   ,KC_NO   , KC_NO
                                         //`-----------------------------'   `--------------------------'
    )
};

// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case RSFT_T(KC_LBRC):
            if (record->tap.count && record->event.pressed) {
                tap_code16(S(KC_LBRC));
                return false;
            }
            break;

        case RCTL_T(KC_RBRC):
            if (record->tap.count && record->event.pressed) {
                tap_code16(S(KC_RBRC));
                return false;
            }
            break;

        case C_MINC:
            if (record->event.pressed) {
                change_pointer_dpi(&global_user_config, true);
                debug_config_to_console(&global_user_config);

                return false;
            }
            break;

        case C_MDEC:
            if (record->event.pressed) {
                change_pointer_dpi(&global_user_config, false);
                debug_config_to_console(&global_user_config);

                return false;
            }
            break;

        case C_MTOGG:
            if (record->event.pressed) {
                bool current_state = get_auto_mouse_enable();
                set_auto_mouse_enable(!current_state);

                return false;
            }
            break;

        case C_DRAG:
            if (record->event.pressed) {
                set_scrolling = record->event.pressed;
                return true;
            }
            break;
    }

    return true;
}
