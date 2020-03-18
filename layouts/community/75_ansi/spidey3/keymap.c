#include QMK_KEYBOARD_H
#include "unicode.h"
#include "spidey3.h"

#define SETTINGS A(S(KC_S))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Linux / Win layout
    [_BASE] = LAYOUT_75_ansi(
        KC_ESC,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     SETTINGS,   KC_INS,     KC_DEL,
        KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,                 KC_BSPC,    KC_HOME,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,                KC_BSLS,    KC_PGUP,
        KC_CAPS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,                            KC_ENT,     KC_PGDN,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,                            KC_RSFT,    KC_UP,      KC_END,
        KC_LCTL,    KC_LGUI,    KC_LALT,                                    KC_SPC,                                             KC_RALT,    MO(_FN),    KC_RCTL,    KC_LEFT,    KC_DOWN,    KC_RGHT
    ),
    // OSX layout
    [_OSX] = LAYOUT_75_ansi(
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_EJCT,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                            _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                            _______,    _______,    _______,
        _______,    KC_LALT,    KC_LGUI,                                    _______,                                            _______,    _______,    _______,    _______,    _______,    _______
    ),
    // FN
    [_FN] = LAYOUT_75_ansi(
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_PWR,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    X_BUL,      _______,    _______,    X_DASH,     _______,                RESET,      EEP_RST,
        _______,    RGB_TOG,    RGB_MOD,    RGB_HUD,    RGB_HUI,    RGB_SAD,    RGB_SAI,    RGB_VAD,    RGB_VAI,    RGB_SPD,    RGB_SPI,    VLK_TOG,    _______,                _______,    KC_VOLU,
        _______,    RGB_M_P,    RGB_M_B,    RGB_M_R,    RGB_M_SW,   RGB_M_SN,   RGB_M_K,    RGB_M_G,    RGB_M_T,    SPI_LNX,    _______,    _______,                            _______,    KC_VOLD,
        _______,    SPI_GLO,    _______,    SPI_WIN,    _______,    _______,    _______,    SPI_OSX,    X(LARR),    X(RARR),    DEBUG,      _______,                            KC_BRIU,    KC_MUTE,
        _______,    _______,    _______,                                    _______,                                            _______,    _______,    _______,    _______,    KC_BRID,    _______
    )
};
