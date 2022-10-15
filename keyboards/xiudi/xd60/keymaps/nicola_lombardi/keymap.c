#include QMK_KEYBOARD_H

#define LAYOUT_split_spacebar( \
      K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D, \
      K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1D,  \
      K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D,  \
      K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K47,  K3D,  K3C,   \
      K40,  K41,  K42,        K46,  K45,  K44,                    K4A,  K4B,  K48,  K4C,  K4D  \
) { \
    { K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D }, \
    { K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1D }, \
    { K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D }, \
    { K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C,  K3D }, \
    { K40,  K41,  K42, KC_NO, K44,  K45,  K46,  K47,  K48, KC_NO, K4A,  K4B,  K4C,  K4D }  \
}

enum {
    TD_NO_GAMINGPROFILE,
    TD_RIGHT_GAMINGPROFILE,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Right Arrow, Tap twice to toggle the gaming layer
    [TD_RIGHT_GAMINGPROFILE] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_RGHT, 3),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // 0: Base Layer
    LAYOUT_split_spacebar(
        KC_GRV,  KC_1,    KC_2,     KC_3,  KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,    KC_0,    KC_NO,  KC_NO,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,     KC_E,  KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_NO,  KC_NO, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,     KC_D,  KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT,  KC_NO,   KC_ENT,
        KC_LSFT, KC_NO,   KC_Z,     KC_X,  KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH,  KC_NO,   KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,         MO(1),    KC_SPC,     KC_RCTL, MO(2),   KC_DEL,  KC_LEFT, KC_DOWN,   KC_RGHT),

    // 1: Function Layer
    LAYOUT_split_spacebar(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_BSPC,
        KC_TAB, LSFT(KC_LBRC), LSFT(KC_RBRC), KC_LBRC, KC_RBRC, LCTL(LSFT(KC_F5)), KC_NO, KC_HOME, KC_UP, KC_END, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_CAPS, KC_MINS, LSFT(KC_MINS), KC_EQL, LSFT(KC_EQL), LCTL(LSFT(KC_F10)), KC_NO, KC_LEFT, KC_DOWN, KC_RIGHT, KC_MINS, KC_EQL, KC_NO, KC_ENT,
        KC_LSFT, KC_NO, KC_F12, LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_RIGHT)), KC_NO, KC_NO, KC_NO, KC_DEL, KC_NO, KC_NO, KC_NO, KC_NO, KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,       KC_TRNS, KC_SPC,         KC_RCTL, KC_NO,  KC_DEL,  KC_LEFT, KC_DOWN, TD(TD_RIGHT_GAMINGPROFILE)),

    // 2: Extra functions layer
    LAYOUT_split_spacebar(
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO,       KC_NO, KC_NO,         KC_NO, KC_TRNS,  RGB_TOG,  RGB_VAD, RGB_VAI, RGB_MOD),
    
    // 3: A standard layer used for gaming
    LAYOUT_split_spacebar(
        KC_GRV,  KC_1,    KC_2,     KC_3,  KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,     KC_E,  KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,     KC_D,  KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT,  KC_NO,   KC_ENT,
        KC_LSFT, KC_NO,   KC_Z,     KC_X,  KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH,  KC_NO,   KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,         KC_SPC,    KC_SPC,     KC_RCTL, KC_RALT,   KC_DEL,  KC_LEFT, KC_DOWN,   TD(TD_RIGHT_GAMINGPROFILE)),
};
