#include QMK_KEYBOARD_H

// rask's BananaSplit60 layout

#define L_BASE      0
#define L_BASE_ALT  1
#define L_ONE       2
#define L_TWO       3
#define L_LOCK      4

#define ______  KC_TRNS
#define XXXXXX  KC_NO

// L_BASE
// Initial layer with default keymap
//
// L_BASE_ALT
// Layer with some standardisation e.g. make
// space key "full" to make gaming less of a
// chore
//
// L_ONE
// General things like F-row and navigation
//
// L_TWO
// Media controls and more exotic keybinds
//
// L_LOCK
// Lock the keyboard, release to unlock

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_BASE] = LAYOUT_hhkb_arrow( \
        KC_GRV,     KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSLS,    KC_DEL,     \
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,                KC_BSPC,    \
        MO(L_ONE),  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,       KC_L,       KC_SCLN,    KC_QUOT,                            KC_ENT,     \
        KC_LSFT,            KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,       KC_COMM,    KC_DOT,     MT(MOD_RSFT, KC_SLSH),  KC_UP,      MO(L_TWO),  \
        KC_LCTRL,   KC_LGUI,    KC_LALT,    KC_BSPC,        MO(L_BASE_ALT), KC_SPACE,   KC_RALT,    MO(L_LOCK),             KC_LEFT,    KC_DOWN,    KC_RIGHT    \
    ),

    [L_BASE_ALT] = LAYOUT_hhkb_arrow( \
        ______,     ______, ______, ______, ______, ______, ______, ______, ______,     ______,     ______,     ______,     ______,     ______,     ______,     \
        ______,     ______, ______, ______, ______, ______, ______, ______, ______,     ______,     ______,     ______,     ______,                 ______,     \
        ______,     ______, ______, ______, ______, ______, ______, ______, ______,     ______,     ______,     ______,                             ______,     \
        ______,             ______, ______, ______, ______, ______, ______, ______,     ______,     ______,     ______,                 ______,     ______,     \
        ______,     ______,     ______,     KC_SPACE,       ______,         ______,     ______,     ______,                 ______,     ______,     ______      \
    ),

    [L_ONE] = LAYOUT_hhkb_arrow( \
        KC_ESC,     KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_PSCR,    KC_INS,     \
        ______,     ______, ______, ______, ______, ______, ______, ______, ______,     ______,     ______,     ______,     ______,                 ______,     \
        ______,     ______, ______, ______, ______, ______, ______, ______, ______,     ______,     ______,     ______,                             ______,     \
        ______,             ______, ______, ______, ______, ______, ______, ______,     ______,     ______,     ______,                 KC_PGUP,    ______,     \
        ______,     ______,     ______,     ______,         ______,         ______,     ______,     ______,                 KC_HOME,    KC_PGDN,    KC_END      \

    ),

    [L_TWO] = LAYOUT_hhkb_arrow( \
        ______,     ______, ______, ______, ______, ______, ______, ______, ______,     ______,     ______,     ______,     ______,     ______,     ______,     \
        ______,     ______, ______, ______, ______, ______, ______, ______, ______,     KC_MPRV,    KC_MPLY,    KC_MNXT,    ______,                 ______,     \
        KC_CAPS,    ______, ______, ______, ______, ______, ______, ______, ______,     KC_VOLD,    KC_VOLU,    KC_MUTE,                            ______,     \
        ______,             ______, ______, ______, ______, ______, ______, ______,     KC_MSTP,    ______,     ______,                 ______,     ______,     \
        ______,     KC_APP,     ______,     ______,         ______,         ______,     ______,     ______,                 ______,     ______,     ______      \
    ),

    [L_LOCK] = LAYOUT_hhkb_arrow( \
        XXXXXX,     XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX,     XXXXXX,     XXXXXX,     XXXXXX,     XXXXXX,     XXXXXX,     XXXXXX,     \
        XXXXXX,     XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX,     XXXXXX,     XXXXXX,     XXXXXX,     XXXXXX,                 XXXXXX,     \
        XXXXXX,     XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX,     XXXXXX,     XXXXXX,     XXXXXX,                             XXXXXX,     \
        XXXXXX,             XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX,     XXXXXX,     XXXXXX,     XXXXXX,                 XXXXXX,     XXXXXX,     \
        XXXXXX,     XXXXXX,     XXXXXX,     XXXXXX,         XXXXXX,         XXXXXX,     XXXXXX,     ______,                 XXXXXX,     XXXXXX,     XXXXXX      \
    ),
};
