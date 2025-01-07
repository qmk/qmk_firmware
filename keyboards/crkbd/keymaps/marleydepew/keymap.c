#include QMK_KEYBOARD_H
#include "../../macro.h"
#include "../../oled.h"

enum layer_names {
    _COLEMAK_DH,
    _NUMBER,
    _SYMBOL,
    _FUNCTION,
    _NAVIGATION,
    _MOUSE,
    _RGB
};

enum custom_keycodes {
    MACRO_V = SAFE_RANGE,
    MACRO_A,
    MACRO_C,
    MACRO_TM,
    MACRO_TH,
    MACRO_WM,
    MACRO_WL,
    MACRO_1,
    MACRO_2,
    MACRO_3,
    MACRO_4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK_DH] = LAYOUT_split_3x6_3_ex2(                                                        // Colemak DH Layer
    // |-------------+-------------+-------------+-------------+-------------+-------------+-------------|   |-------------+-------------+-------------+-------------+-------------+-------------+-------------|
        XXXXXXX,      KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,         MACRO_1,          MACRO_3,      KC_J,         KC_L,         KC_U,         KC_Y,         XXXXXXX,      XXXXXXX,
    // |-------------+-------------+-------------+-------------+-------------+-------------+-------------|   |-------------+-------------+-------------+-------------+-------------+-------------+-------------|
        KC_CAPS,      LGUI_T(KC_A), LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_T), KC_G,         MACRO_2,          MACRO_4,      KC_M,         LCTL_T(KC_N), LSFT_T(KC_E), LALT_T(KC_I), LGUI_T(KC_O), KC_QUOT,
    // |-------------+-------------+-------------+-------------+-------------+-------------+-------------|   |-------------+-------------+-------------+-------------+-------------+-------------+-------------|
        KC_ESC,       KC_Z,         KC_X,         KC_C,         KC_D,         KC_V,                                         KC_K,         KC_H,         KC_COMM,      KC_DOT,       KC_SLSH,      QK_LEAD,
    // |-------------+-------------+-------------+-------------+-------------+-------------|                               |-------------+-------------+-------------+-------------+-------------+-------------|
                                                  LT(3,KC_TAB), LT(1,KC_BSPC),LT(2,KC_DEL),                                 LT(5,KC_ENT), LT(4,KC_SPC), LT(6,KC_PSCR) 
    //                                           |-------------+-------------+-------------|                               |-------------+-------------+-------------|
    ),

    [_NUMBER] = LAYOUT_split_3x6_3(                                      // Number Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    KC_1,       KC_2,       KC_3,       XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_LGUI,    KC_LALT,    KC_LSFT,    KC_LCTL,    XXXXXXX,        KC_MINS,    KC_4,       KC_5,       KC_6,       KC_COLN,    KC_GRV,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_UNDS,    KC_7,       KC_8,       KC_9,       KC_SLSH,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
                                            XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_LPRN,    KC_0,       KC_RPRN
    //                                     |-----------+-----------+-----------|   |-----------+-----------+-----------|
    ),

    [_SYMBOL] = LAYOUT_split_3x6_3(                                      // Symbols Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    KC_EXLM,    KC_AT,      KC_HASH,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_LGUI,    KC_LALT,    KC_LSFT,    KC_LCTL,    XXXXXXX,        KC_PLUS,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_SCLN,    KC_TILD,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_EQL,     KC_AMPR,    KC_ASTR,    KC_DOT,     KC_BSLS,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
                                            XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_LBRC,    XXXXXXX,    KC_RBRC
    //                                     |-----------+-----------+-----------|   |-----------+-----------+-----------|
  ),

    [_FUNCTION] = LAYOUT_split_3x6_3(                                   // Function Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    KC_F1,      KC_F2,      KC_F3,      XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_LGUI,    KC_LALT,    KC_LSFT,    KC_LCTL,    XXXXXXX,        XXXXXXX,    KC_F4,      KC_F5,      KC_F6,      KC_APP,     KC_PIPE,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    KC_F7,      KC_F8,      KC_F9,      KC_PAUS,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
                                            XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_F11,     KC_F10,     KC_F12
    //                                     |-----------+-----------+-----------|   |-----------+-----------+-----------|
  ),

    [_NAVIGATION] = LAYOUT_split_3x6_3_ex2(                                  // Navigation Layer (with macros)
    // |-----------+-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    DM_REC1,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_LEFT,    KC_UP,      KC_DOWN,    KC_RGHT,    XXXXXXX,    DM_PLY1,        XXXXXXX,    XXXXXXX,    KC_RCTL,    KC_RSFT,    KC_RALT,    KC_RGUI,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    KC_HOME,    KC_PGUP,    KC_PGDN,    KC_END,     XXXXXXX,                                XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|                           |-----------+-----------+-----------+-----------+-----------+-----------|
                                            XXXXXXX,    XXXXXXX,    XXXXXXX,                                XXXXXXX,    XXXXXXX,    XXXXXXX
    //                                     |-----------+-----------+-----------|                           |-----------+-----------+-----------|
  ),

    [_MOUSE] = LAYOUT_split_3x6_3_ex2(                                                // Mouse Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
        MACRO_V,    KC_WH_L,    KC_WH_U,    KC_WH_D,    KC_WH_R,    XXXXXXX,    DM_REC2,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
        MACRO_A,    KC_MS_L,    KC_MS_U,    KC_MS_D,    KC_MS_R,    LSFT(KC_F3),DM_PLY2,        XXXXXXX,    XXXXXXX,    KC_RCTL,    KC_RSFT,    KC_RALT,    KC_RGUI,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
        MACRO_C,    XXXXXXX,    XXXXXXX,    KC_BTN1,    KC_BTN2,    KC_BTN3,                                KC_BTN3,    KC_BTN1,    KC_BTN2,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|                           |-----------+-----------+-----------+-----------+-----------+-----------|
                                            KC_ACL0,    KC_ACL1,    KC_ACL2,                                XXXXXXX,    XXXXXXX,    XXXXXXX
    //                                     |-----------+-----------+-----------|                           |-----------+-----------+-----------|
  ),

    [_RGB] = LAYOUT_split_3x6_3(                                           // RGB Layer
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        XXXXXXX,    DT_PRNT,    DT_UP,      DT_DOWN,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        RGB_TOG,    RGB_MOD,    RGB_HUI,    RGB_SAI,    RGB_VAI,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
        RGB_M_P,    RGB_RMOD,   RGB_HUD,    RGB_SAD,    RGB_VAD,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    // |-----------+-----------+-----------+-----------+-----------+-----------|   |-----------+-----------+-----------+-----------+-----------+-----------|
                                            XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX
    //                                     |-----------+-----------+-----------|   |-----------+-----------+-----------|
  )
};

// These are my custom overrides for the shift keys
#ifdef KEY_OVERRIDE_ENABLE

// Shift + ( = < on the number layer
const key_override_t left_parenth_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_LPRN, KC_LABK, 1 << _NUMBER);

// Shift + ) = > on the number layer
const key_override_t right_parenth_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_RPRN, KC_RABK, 1 << _NUMBER);

// Shift + 9 = . on the number layer
const key_override_t nine_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_9, KC_DOT, 1 << _NUMBER);

// This globally defines all key overrides to be used
// const key_override_t **key_overrides = (const key_override_t *[]){
const key_override_t *key_overrides[] = {
    &left_parenth_override,
    &right_parenth_override,
    &nine_override,
    NULL // Null terminate the array of overrides
};

#endif // End KEY_OVERRIDE_ENABLE

// This gets called for each key.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // This is for the macros
    switch (keycode) {
        
        case MACRO_V:
            if (record->event.pressed) {
                // when keycode MACRO_V is pressed
                // The string is defined in "../../macro.h"
                SEND_STRING(MV_STRING);
            } else {
                // when keycode MACRO_V is released
            }
            break;

        case MACRO_A:
            if (record->event.pressed) {
                // when keycode MACRO_A is pressed
                // The string is defined in "../../macro.h"
                SEND_STRING(MA_STRING);
            } else {
                // when keycode MACRO_A is released
            }
            break;

        case MACRO_C:
            if (record->event.pressed) {
                // when keycode MACRO_C is pressed
                // The string is defined in "../../macro.h"
                SEND_STRING(MC_STRING);
            } else {
                // when keycode MACRO_C is released
            }
            break;

        case MACRO_1:
            if (record->event.pressed) {
                // when keycode MACRO_1 is pressed
                // Open Python in Command Prompt
                SEND_STRING(SS_RGUI("r") SS_DELAY(500) "cmd.exe" SS_TAP(X_ENT) SS_DELAY(1000) "python.exe" SS_TAP(X_ENT));
            } else {
                // when keycode MACRO_1 is released
            }
            break;

        case MACRO_2:
            if (record->event.pressed) {
                // when keycode MACRO_2 is pressed
                // The string is defined in "../../macro.h"
                SEND_STRING(SS_RGUI("r") SS_DELAY(500) "chrome.exe" SS_TAP(X_ENT) SS_DELAY(2000) "https://amgensbx-rim-test.veevavault.com" SS_TAP(X_ENT));
            } else {
                // when keycode MACRO_2 is released
            }
            break;

        case MACRO_3:
            if (record->event.pressed) {
                // when keycode MACRO_3 is pressed
            } else {
                // when keycode MACRO_3 is released
            }
            break;

        case MACRO_4:
            if (record->event.pressed) {
                // when keycode MACRO_4 is pressed
            } else {
                // when keycode MACRO_4 is released
            }
            break;

        case MACRO_TM:
            if (record->event.pressed) {
                // when keycode MS Teams Mute is pressed
                SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) "m" SS_UP(X_LSFT) SS_UP(X_LCTL));
            } else {
                // when keycode MACRO_1 is released
            }
            break;

        case MACRO_TH:
            if (record->event.pressed) {
                // when keycode MS Teams Hangup is pressed
                SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) "h" SS_UP(X_LSFT) SS_UP(X_LCTL));
            } else {
                // when keycode MACRO_2 is released
            }
            break;

        case MACRO_WM:
            if (record->event.pressed) {
                // when keycode WebEx Mute is pressed
                SEND_STRING(SS_LCTL("m"));
            } else {
                // when keycode MACRO_1 is released
            }
            break;

        case MACRO_WL:
            if (record->event.pressed) {
                // when keycode WebEx Leave is pressed
                SEND_STRING(SS_LCTL("l"));
            } else {
                // when keycode MACRO_2 is released
            }
            break;

    }

    return true;
}
