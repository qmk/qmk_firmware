#include QMK_KEYBOARD_H

#define BL 0
#define FN 1
#define MV 2
#define MAC 3
#define MAC_MV 4

static void set_default_layer_color(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case BL:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case MAC:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv_noeeprom(HSV_RED);
            break;
    }
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    set_default_layer_color(state);
    return state;
}

void keyboard_post_init_user(void) {
    set_default_layer_color(default_layer_state);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * 0: Windows/Linux (BL)
     * Esc  1  2  3  4  5  6  7  8  9  0  -  =  \  `
     * Tab  Q  W  E  R  T  Y  U  I  O  P  [  ]  Backspace
     * Ctrl A  S  D  F  G  H  J  K  L  ;  '  Enter
     * Shift   Z  X  C  V  B  N  M  ,  .  /  Shift  Fn
     *         GUI Alt      Space      Alt GUI
     */
    [BL] = LAYOUT_60_hhkb(
        KC_ESC,    KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS, KC_GRV,
        KC_TAB,    KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL,   KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,       KC_ENT,
        KC_LSFT,            KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M, KC_COMM,  KC_DOT, KC_SLSH,      KC_RSFT,     MO(FN),
             KC_LGUI, KC_LALT,              LT(MV, KC_SPC),                         KC_RALT, KC_RGUI),
    /*
     * 1: Function layer (hold Fn)
     * Fn+Z: select Mac mode; Fn+X: select Windows/Linux mode.
     */
    [FN] = LAYOUT_60_hhkb(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
        KC_TAB,   UG_TOGG, UG_NEXT, UG_PREV, BL_TOGG, BL_STEP, KC_TRNS, KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS,  KC_UP,   KC_TRNS, QK_BOOT,
        KC_TRNS,  KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, KC_TRNS, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,    KC_ENT,
        KC_TRNS,          DF(MAC), DF(BL),  KC_TRNS, KC_TRNS, KC_TRNS, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN,    KC_TRNS,          KC_TRNS,
             KC_TRNS, KC_TRNS,                   KC_TRNS,                         KC_TRNS, KC_TRNS),
    /*
     * 2: Windows/Linux movement (hold Space)
     * A  Space | S  Alt | D  Ctrl | F  Shift
     * H  Left  | J  Down| K  Up   | L  Right
     */
    [MV] = LAYOUT_60_hhkb(
        KC_ESC,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS, KC_DEL,
        KC_TAB,   XXXXXXX, XXXXXXX, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX, KC_PSCR, XXXXXXX, KC_TRNS, KC_DEL,
        KC_TRNS,  KC_SPC,  KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, KC_ENT,
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, XXXXXXX, XXXXXXX, KC_HOME, KC_END,  KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
             KC_TRNS, KC_TRNS,                   KC_TRNS,                         KC_TRNS, KC_TRNS),
    /*
     * 3: Mac typing layer
     * Esc  1  2  3  4  5  6  7  8  9  0  -  =  \  `
     * Tab  Q  W  E  R  T  Y  U  I  O  P  [  ]  Backspace
     * Cmd  A  S  D  F  G  H  J  K  L  ;  '  Enter
     * Shift   Z  X  C  V  B  N  M  ,  .  /  Shift  Fn
     *         Ctrl Option    Space    Option Cmd
     */
    [MAC] = LAYOUT_60_hhkb(
        KC_ESC,    KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS, KC_GRV,
        KC_TAB,    KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LGUI,   KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,       KC_ENT,
        KC_LSFT,            KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M, KC_COMM,  KC_DOT, KC_SLSH,      KC_RSFT,     MO(FN),
             KC_LCTL, KC_LALT,              LT(MAC_MV, KC_SPC),                    KC_RALT, KC_RGUI),
    /*
     * 4: Mac movement (hold Space while in Mac mode)
     * A  Space | S  Option | D  Command | F  Shift
     * H  Left  | J  Down   | K  Up      | L  Right
     */
    [MAC_MV] = LAYOUT_60_hhkb(
        KC_ESC,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS, KC_DEL,
        KC_TAB,   XXXXXXX, XXXXXXX, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX, KC_PSCR, XXXXXXX, KC_TRNS, KC_DEL,
        KC_TRNS,  KC_SPC,  KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, KC_ENT,
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, XXXXXXX, XXXXXXX, KC_HOME, KC_END,  KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
             KC_TRNS, KC_TRNS,                   KC_TRNS,                         KC_TRNS, KC_TRNS),
};