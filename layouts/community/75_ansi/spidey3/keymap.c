#include "spidey3.h"

#define FN_MENU LT(_FN,KC_APP)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base
    [_BASE] = LAYOUT_75_ansi(
        KC_ESC,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_PSCR,    KC_INS,     KC_DEL,
        KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,                 KC_BSPC,    KC_HOME,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,                KC_BSLS,    KC_PGUP,
        KC_CAPS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,                            KC_ENT,     KC_PGDN,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,                            KC_RSFT,    KC_UP,      KC_END,
        KC_LCTL,    KC_LGUI,    KC_LALT,                                    KC_SPC,                                             KC_RALT,    FN_MENU,    KC_RCTL,    KC_LEFT,    KC_DOWN,    KC_RGHT
    ),
    // Numpad
    [_NUMPAD] = LAYOUT_75_ansi(
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_NUMLOCK, XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_KP_0,    KC_PMNS,    KC_PEQL,                _______,    _______,
        _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_KP_4,    KC_KP_5,    KC_KP_6,    KC_PCMM,    _______,    _______,                _______,    _______,
        KC_NUMLOCK, XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_KP_1,    KC_KP_2,    KC_KP_3,    KC_PPLS,    KC_PAST,                            KC_PENT,    _______,
        _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_KP_0,    SPI_KP_00,  KC_PDOT,    KC_PSLS,                            _______,    _______,    _______,
        _______,    _______,    _______,                                    _______,                                            _______,    _______,    _______,    _______,    _______,    _______
    ),
    // FN
    [_FN] = LAYOUT_75_ansi(
        RESET,      SPI_NORMAL, SPI_WIDE,   SPI_SCRIPT, SPI_BLOCKS, SPI_CIRCLE, SPI_SQUARE, SPI_PARENS, SPI_FRAKTR, XXXXXXX,    XXXXXXX,    XXXXXXX,    SPI_GFLOCK, KC_SLEP,    CH_SUSP,    KC_PWR,
        EEP_RST,    X(SAD),     X(MEH),     X(HAPPY),   X(ANGRY),   X(THUMBDN), X(THUMBUP), X(SPIDER),  X_BUL,      X(LOL),     X(SURPRISE),X_DASH,     XXXXXXX,                KC_PAUS,    KC_SLCK,
        XXXXXXX,    RGB_TOG,    RGB_MOD,    RGB_HUD,    RGB_HUI,    RGB_SAD,    RGB_SAI,    RGB_VAD,    RGB_VAI,    RGB_SPD,    RGB_SPI,    VLK_TOG,    XXXXXXX,                XXXXXXX,    KC_BRIU,
        XXXXXXX,    RGB_M_P,    RGB_M_B,    RGB_M_R,    RGB_M_SW,   RGB_M_SN,   RGB_M_K,    RGB_M_G,    RGB_M_T,    SPI_LNX,    XXXXXXX,    XXXXXXX,                            XXXXXXX,    KC_BRID,
        _______,    SPI_GLO,    XXXXXXX,    SPI_WIN,    UC_MOD,     NK_TOGG,    TG(_NUMPAD),SPI_OSX,    X(LARR),    X(RARR),    DEBUG,      _______,                            KC_VOLU,    KC_MUTE,
        _______,    _______,    _______,                                    KC_MPLY,                                            CH_ASST,    _______,    CH_CPNL,    KC_MPRV,    KC_VOLD,    KC_MNXT
    )
};
