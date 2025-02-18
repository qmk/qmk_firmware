// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "lib/crosses.h"

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

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }

    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    render_logo();

    // clang-format off
    const char* layer_names[] = {
        [_BASE]  = "BASE  CPI: ",
        [_NUM]   = "PROG  CPI: ",
        [_NAV]   = "NAVI  CPI: ",
        [_MEDIA] = "MEDIA CPI: ",
        [_FUNC]  = "FUNC  CPI: ",
        [_MOUS]  = "MOUSE CPI: ",
        [_CUST]  = "CUST  CPI: ",
    };
    // clang-format on

    char     cpi_str[6];
    uint16_t current_dpi = get_pointer_dpi(&global_user_config);

    snprintf(cpi_str, sizeof(cpi_str), "%u", (unsigned int)current_dpi);

    oled_write(PSTR(layer_names[get_highest_layer(layer_state)]), false);
    oled_write(cpi_str, false);

    return false;
}
#endif /* ifdef OLED_ENABLE */

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUS);
    set_auto_mouse_enable(true);
}
