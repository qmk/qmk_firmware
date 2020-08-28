#include QMK_KEYBOARD_H

#define BL 0
#define FN 1

#define LCTL_ESC LCTL_T(KC_ESC)
#define FN_SPC LT(FN, KC_SPACE)

#define SLEEP LALT(LGUI(KC_MEDIA_EJECT))
#define LFT_DT LCTL(KC_LEFT)
#define RGT_DT LCTL(KC_RIGHT)
#define EXPOSE LCTL(KC_DOWN)
#define M_CTRL LCTL(KC_UP)
/*
 * Default HHKB Layout
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: Default layer
     * ,-----------------------------------------------------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|   |
     * |-----------------------------------------------------------|
     * |↹    |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    ⌫|
     * |-----------------------------------------------------------|
     * |^/⎋     |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|     ↵|
     * |-----------------------------------------------------------|
     * |⇧/(  |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|      ⇧/)|   |
     * `-----------------------------------------------------------'
     *       |  ⌥|    ⌘|         Fn/Space         |⌘    |◆  |
     *       `----------------------------------------------'
     */
[BL] = LAYOUT_60_hhkb(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7 ,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV, \
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,        KC_BSPC, \
        LCTL_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                KC_ENT, \
        KC_LSPO,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,               KC_RSPC, MO(FN), \
             KC_LALT, KC_LGUI,              FN_SPC,                         KC_RGUI, KC_HYPR),
    /* 1: HHKB Fn layer
     * ,-----------------------------------------------------------.
     * | 🔒| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|F13|F14|
     * |-----------------------------------------------------------|
     * |RESET|⏮ |⏭ |⏯ |   |   |LDt|éxp|MCt|RDt|   |   |   |  Del|
     * |-----------------------------------------------------------|
     * |       |🔉 |🔊 |🔇 |   |   |  ←|  ↓|  ↑|  →|   |   |       |
     * |-----------------------------------------------------------|
     * |_RGB:tog|mod|hue|sat|val|   |   |   |   |   |   |      |   |
     * `-----------------------------------------------------------'
     *       |   |     |                         |     |    |
     *       `----------------------------------------------'
     */
[FN]= LAYOUT_60_hhkb(
        SLEEP,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13,  KC_F14,  \
        RESET,    KC_MPRV, KC_MNXT, KC_MPLY, KC_TRNS, KC_TRNS, LFT_DT,  EXPOSE,  M_CTRL,  RGT_DT,  KC_TRNS, KC_TRNS, KC_TRNS,         KC_DEL,  \
        KC_TRNS,    KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,                KC_TRNS, \
        RGB_TOG,     RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,               KC_TRNS, KC_TRNS, \
             KC_TRNS, KC_TRNS,              KC_TRNS,                        KC_TRNS, KC_TRNS),
};



#ifdef RGBLIGHT_EFFECT_REACTIVE
const int led_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_60_hhkb(
       0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, \
       0,  0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 4, 4,   4, \
       0,   0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4,     4, \
       9,    9, 8, 8, 8, 7, 7, 7, 6, 6, 6, 5,    5, \
           9, 8,            7,            6, 5      \
);



void pre_process_action_quantum(keyevent_t event) {
    int index = led_map[event.key.row][event.key.col];
    update_reactive_led_map(index, event.pressed);
}
#endif
