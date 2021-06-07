#include "vs_dz60rgb_ansi.h"

// Set up keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Main Alphanumeric layer for Mac
    [MAC_BASE] = LAYOUT_60_ansi(
        KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSPC, // 14
         KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_BSLS, // 14
        TD_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,     KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,           KC_ENT, // 13
          TD_LS,             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,            TD_RS, // 12
        KC_LCTL, KC_LALT, KC_LCMD,                             L_MSFN,                             KC_RCMD, KC_RALT,  L_MFN1, KC_RCTL  // 8
    ),
    // SpaceFN layer for Mac
    [MAC_SPACEFN] = LAYOUT_60_ansi(
         KC_GRV, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_7,    KC_8,    KC_9,   TD_QM, KC_VOLU,  KC_DEL, // 14
        XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, KC_PGUP, KC_BTN1, KC_MS_U, KC_BTN2,    KC_4,    KC_5,    KC_6, KC_BRMD, KC_BRMU, RGB_TOG, // 14
        XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_MS_L, KC_MS_D, KC_MS_R,    KC_1,    KC_2,    KC_3, XXXXXXX,          XXXXXXX, // 13
          TD_LS,          KC_MPRV, KC_MNXT, KC_MPLY, XXXXXXX,  KC_SPC, XXXXXXX, XXXXXXX,    KC_0,    KC_0,  KC_DOT,            TD_RS, // 12
        XXXXXXX, XXXXXXX, XXXXXXX,                            _______,                            _______, _______, _______, _______  // 8
    ),
    // Fn1 Layer for Mac
    [MAC_FN1] = LAYOUT_60_ansi(
        RGB_TOG,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,   KC_F12,  KC_DEL, // 14
           L_WB, XXXXXXX,   KC_UP, XXXXXXX, KC_PGUP, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_RMOD, XXXXXXX, // 14
        XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX, RGB_SPI, RGB_SPD,           XXXXXXX, // 13
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, // 12
          RESET, _______, _______,                             KC_SPC,                            _______, _______,  _______, XXXXXXX  // 8
    ),
    // Main Alphanumeric layer for Windows
    [WINDOWS_BASE] = LAYOUT_60_ansi(
        KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSPC, // 14
         KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_BSLS, // 14
        TD_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,           KC_ENT, // 13
          TD_LS,             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,            TD_RS, // 12
        KC_LCTL, KC_LWIN, KC_LALT,                             KC_SPC,                             KC_RALT, KC_RWIN, L_WFN1, KC_RCTL  // 8
    ),
    // Fn1 Layer for Windows
    [WINDOWS_FN1] = LAYOUT_60_ansi(
         KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL, // 14
           L_MB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, // 14
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, // 13
          L_WGB,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, // 12
        _______, _______, _______,                             KC_SPC,                            _______, _______, _______, _______  // 8
    ),
    // Gaming layer for Windows
    [WINDOWS_GAMING] = LAYOUT_60_ansi(
        KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSPC, // 14
         KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_BSLS, // 14
        TD_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,           KC_ENT, // 13
          TD_LS,             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,            TD_RS, // 12
        KC_LCTL,  L_WGFN, KC_LALT,                             KC_SPC,                             KC_RALT, L_WGFN,  L_WGFN, KC_RCTL  // 8
    ),
    // Gaming Fn layer for Windows
    [WINDOWS_GAMING_FN] = LAYOUT_60_ansi(
         KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL, // 14
           L_WB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, // 14
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,          XXXXXXX, // 13
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, // 12
        _______, _______, _______,                            _______,                            _______, _______, _______, _______  // 8
    ),
    // Blank layer (should never really be used)
    [BLANK] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, // 14
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, // 14
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, // 13
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, // 12
        _______, _______, _______,                            _______,                            _______, _______, _______, _______  // 8
    ),
    // No-op Layer (should never really be used)
    [NOOP] = LAYOUT_60_ansi(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, // 14
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, // 14
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, // 13
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, // 12
        XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  // 8
    )
};
