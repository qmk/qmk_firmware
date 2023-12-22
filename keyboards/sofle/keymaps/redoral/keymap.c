 /* Copyright 2023 Red Oral
  * Based on the via keymap and modified it to my own keymap and OLED display preference
  * TotK logo byte array from https://www.reddit.com/r/MechanicalKeyboards/comments/15v1o4b/made_a_totk_pic_for_my_oled/
  */

#include QMK_KEYBOARD_H
#include "oled.c"


#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [1] = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) },
    [2] = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) },
    [3] = { ENCODER_CCW_CW(_______, _______),           ENCODER_CCW_CW(_______, _______) },
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * BASE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  _   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '"  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |  +=  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCtl | LGui | LAlt |MO(1) | /Space  /       \Enter \  |MO(1) |  ~`  |      |  \  |
 *            |      |      |      |      |/       /         \      \ |      |      |      |     |
 *            `----------------------------------'           '------''---------------------------'
 */
[0] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                    KC_6,    KC_7,    KC_8,     KC_9,   KC_0,     KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                    KC_Y,    KC_U,    KC_I,     KC_O,   KC_P,     KC_BSPC,
  KC_CAPS,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                    KC_H,    KC_J,    KC_K,     KC_L,   KC_SCLN,  KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MPLY,   KC_MUTE,KC_N,    KC_M,    KC_COMM,  KC_DOT, KC_SLSH,  KC_EQL,
                 KC_LCTL, KC_LGUI, KC_LALT, MO(1), KC_SPC,      KC_ENT,  MO(1), KC_GRV, XXXXXXX,  KC_BSLS
),

/*
 * MO(1)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  |  F11 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | Home |  Up  | End  |      |      |                    |  Ins |  Del |  MsU |   [  |   ]  |  F12 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  Lf  |  Dn  |  Rt  |      |      |-------.    ,-------|  Ms1 |  MsL |  MsD |  MsR |  Ms2 |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------| SclU | SclD |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |     |
 *            |      |      |      |      |/       /         \      \ |      |      |      |     |
 *            `----------------------------------'           '------''---------------------------'
 */
 
[1] = LAYOUT(
  KC_TRNS, KC_F1,   KC_F2,    KC_F3,    KC_F4,   KC_F5,                       KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
  KC_TRNS, KC_HOME, KC_UP,    KC_END,   KC_TRNS, KC_TRNS,                     KC_INS,   KC_DEL,   KC_MS_U,  KC_LBRC,  KC_RBRC,  KC_F12,
  KC_TRNS, KC_LEFT, KC_DOWN,  KC_RGHT,  KC_TRNS, KC_TRNS,                     KC_BTN1,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_BTN2,  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_WH_U,  KC_WH_D,  KC_BTN3,  KC_TRNS,  KC_TRNS,  KC_TRNS,
              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* MO(2)
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|        |   |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |--------|   |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |     |
 *            |      |      |      |      |/       /         \      \ |      |      |      |     |
 *            `----------------------------------'           '------''---------------------------'
 */
[2] = LAYOUT(
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* MO(3)
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|        |   |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |--------|   |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |     |
 *            |      |      |      |      |/       /         \      \ |      |      |      |     |
 *            `----------------------------------'           '------''---------------------------'
 */
[3] = LAYOUT(
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
)
};

