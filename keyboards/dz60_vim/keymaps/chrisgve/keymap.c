#include QMK_KEYBOARD_H

enum layer_names {
    _NORMAL,
    _INSERT,
    _VISUAL,
    _VIM,
    _FN
};

// Tap dance declaration
enum {
    TD_ESC_VIM,
    TD_ESC_NORMAL,
};

// Tap Dance definition
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for VIM
    [TD_ESC_VIM] = ACTION_TAP_DANCE_LAYER_MOVE(KC_ESC, _VIM),
    [TD_ESC_NORMAL] = ACTION_TAP_DANCE_LAYER_MOVE(KC_ESC, _NORMAL),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Normal
    LAYOUT(
        TD(TD_ESC_VIM), KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, KC_NO,  XXXXXXX, KC_LEFT,
        KC_TAB,  KC_Q,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    TO(_INSERT),    TO(_INSERT),    KC_NO,    KC_NO, KC_NO, KC_NO,
        KC_CAPS, TO(_INSERT),    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT,    KC_NO, KC_NO,   KC_ENT,
        KC_LSFT, XXXXXXX, KC_NO,    KC_DEL,    TO(_INSERT),    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, KC_NO,  KC_NO, KC_RSFT, XXXXXXX,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,  KC_SPC,  KC_SPC,           XXXXXXX, KC_RGUI, XXXXXXX, MO(_FN),   KC_RCTL
    ),
    // Insert
    LAYOUT(
        TO(_NORMAL), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, XXXXXXX,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,  KC_SPC,  KC_SPC,           XXXXXXX, KC_RGUI, XXXXXXX, MO(_FN),   KC_RCTL
    ),
    // Visual
    LAYOUT(
        KC_GESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, KC_DEL,
        RESET,   RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, XXXXXXX, XXXXXXX, KC_UP,   KC_HOME, KC_END,
        DEBUG,   KC_MPLY, KC_VOLD, KC_VOLU, KC_MPRV, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_LEFT, KC_RGHT,          XXXXXXX,
        XXXXXXX, XXXXXXX, BL_TOGG, BL_DEC,  BL_INC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, KC_DOWN, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    // Vim
    LAYOUT(
        TD(TD_ESC_NORMAL), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, XXXXXXX,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,  KC_SPC,  KC_SPC,           XXXXXXX, KC_RGUI, XXXXXXX, MO(_FN),   KC_RCTL
    ),
    // Functions
    LAYOUT(
        KC_GESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, KC_DEL,
        RESET,   RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, XXXXXXX, XXXXXXX, KC_UP,   KC_HOME, KC_END,
        DEBUG,   KC_MPLY, KC_VOLD, KC_VOLU, KC_MPRV, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_LEFT, KC_RGHT,          XXXXXXX,
        XXXXXXX, XXXXXXX, BL_TOGG, BL_DEC,  BL_INC,  TG(_VIM), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, KC_DOWN, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};
