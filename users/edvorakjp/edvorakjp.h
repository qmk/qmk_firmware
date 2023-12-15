#pragma once

#include "quantum.h"
#include "action_layer.h"

#define EECONFIG_EDVORAK (uint8_t *)20

// clang-format off
#define __EDVORAKJP_BASE_L1__               KC_QUOTE,      KC_COMMA,               KC_DOT,           KC_Y,          KC_Q
#define __EDVORAKJP_BASE_L2__                   KC_A,  LALT_T(KC_O),         LGUI_T(KC_E),   LCTL_T(KC_I),          KC_U
#define __EDVORAKJP_BASE_L3__                KC_SCLN,          KC_X,                 KC_C,           KC_V,          KC_Z

#define __EDVORAKJP_BASE_R1__                   KC_F,          KC_G,                 KC_R,           KC_W,          KC_P
#define __EDVORAKJP_BASE_R2__                   KC_D,  RSFT_T(KC_T),         RGUI_T(KC_N),   RALT_T(KC_S),          KC_M
#define __EDVORAKJP_BASE_R3__                   KC_H,          KC_J,                 KC_K,           KC_L,          KC_B

#define __EDVORAKJP_NUMBER_L__                  KC_1,  LALT_T(KC_2),         LGUI_T(KC_3),   LCTL_T(KC_4),          KC_5
#define __EDVORAKJP_NUMBER_R__                  KC_6,  RSFT_T(KC_7),         RGUI_T(KC_8),   RALT_T(KC_9),          KC_0

#define __EDVORAKJP_FUNCTION_L__               KC_F1,         KC_F2,        LALT_T(KC_F3),  LGUI_T(KC_F4), LCTL_T(KC_F5),  KC_F6
#define __EDVORAKJP_FUNCTION_R__               KC_F7, RSFT_T(KC_F8),        RGUI_T(KC_F9), RALT_T(KC_F10),        KC_F11, KC_F12

#define __EDVORAKJP_SYMBOL_L__            KC_EXCLAIM,         KC_AT,              KC_HASH,      KC_DOLLAR
#define __EDVORAKJP_SYMBOL_R__            KC_PERCENT, KC_CIRCUMFLEX,         KC_AMPERSAND,    KC_ASTERISK

#define __EDVORAKJP_BRACKET_L__  KC_LEFT_CURLY_BRACE,   KC_LBRC,            KC_LEFT_PAREN
#define __EDVORAKJP_BRACKET_R__       KC_RIGHT_PAREN,   KC_RBRC, KC_RIGHT_CURLY_BRACE

#define __EDVORAKJP_PAGE__                   KC_HOME,       KC_PGDN,              KC_PGUP,         KC_END
#define __EDVORAKJP_CURSOR__                 KC_LEFT,       KC_DOWN,                KC_UP,       KC_RIGHT

#define LA_TAB  LALT_T(KC_TAB)
#define LS_SPC  LSFT_T(KC_SPACE)
#define RC_BSPC RCTL_T(KC_BACKSPACE)
#define RC_DEL  RCTL_T(KC_DELETE)
#define RG_ENT  RGUI_T(KC_ENTER)

#define LOWER_TD TD(TD_EDVORAKJP_LOWER)
#define RAISE_TD TD(TD_EDVORAKJP_RAISE)
// clang-format on

extern keymap_config_t keymap_config;

enum edvorakjp_layers {
    L_EDVORAKJP_BASE = 0,
    L_EDVORAKJP_LOWER,
    L_EDVORAKJP_RAISE,
    L_EDVORAKJP_ADJUST,
    L_EDVORAKJP_EXTRA,
};

enum edvorakjp_keycodes {
    KC_EDVORAKJP_LOWER = SAFE_RANGE,
    KC_EDVORAKJP_RAISE,
    KC_MAC,
    KC_WIN,
    KC_JPN,
    KC_ENG,
    NEW_SAFE_RANGE,
};

enum tap_dance_code {
    TD_EDVORAKJP_LOWER = 0,
    TD_EDVORAKJP_RAISE,
};

// base
void     matrix_init_user(void);
void     matrix_init_keymap(void);
layer_state_t layer_state_set_user(layer_state_t state);
layer_state_t layer_state_set_keymap(layer_state_t state);
bool     process_record_user(uint16_t keycode, keyrecord_t *record);
bool     process_record_keymap(uint16_t keycode, keyrecord_t *record);

// status
void edvorakjp_status_init(void);
bool get_enable_kc_lang(void);
void set_enable_kc_lang(bool new_state);
bool get_japanese_mode(void);
void set_japanese_mode(bool new_state);

/*
 * Each process_record_* methods defined here are
 * return false if processed, or return true if not processed.
 * You can add your original macros in process_record_keymap() in keymap.c.
 */
bool process_record_edvorakjp_swap_scln(uint16_t keycode, keyrecord_t *record);
bool process_record_edvorakjp_config(uint16_t keycode, keyrecord_t *record);
bool process_record_layer(uint16_t keycode, keyrecord_t *record);
bool process_record_ime(uint16_t keycode, keyrecord_t *record);
