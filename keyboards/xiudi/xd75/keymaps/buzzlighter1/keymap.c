#include QMK_KEYBOARD_H
#define _QW 0
#define _FN 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | Del    | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | HOME   | CAPS   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | TT(FN) | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | \      | END    | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | Vol+   | PGUP   | UP     | PGDWN  |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | WIN    | MUTE   | LALT   |                             SPACE                            | Vol-   | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_QW] = LAYOUT_ortho_5x15( /* QWERTY */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_HOME, KC_CAPS,
    TT(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS, KC_END,  KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_VOLU, KC_PGUP, KC_UP,   KC_PGDN,
    KC_LCTL, KC_LGUI, KC_MUTE, KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,  KC_LEFT, KC_DOWN, KC_RGHT
  ),

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | GRV    | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | _______| _______|
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | _______| P7     | P8     | P9     | +      | P*     | XXXXXXX| XXXXXXX| NKRON  | NKROFF | XXXXXXX| BL_DEC | BL_INC | RGB HD | RGB HI |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | _______| P4     | P5     | P6     | NumLk  | CALC   | RESET  | BOOTLDR| CLEAREE| XXXXXXX| XXXXXXX| BL_BRTG| BL_STEP| RGB SD | RGB SI |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | _______| P1     | P2     | P3     | -      | P/     | XXXXXXX| XXXXXXX|  PREV  | NXT    | PLAY   | BL_OFF | BL_ON  | RGB VD | RGB VI |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | _______| P0     | P.     | PENT   |                             SPACE                            | BL_TOGG| RGB TG | RGB RMD| RGB MD |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
    _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_PAST, XXXXXXX, XXXXXXX, NK_ON,   NK_OFF,  XXXXXXX, BL_DEC,  BL_INC,  RGB_HUD, RGB_HUI,
    _______, KC_P4,   KC_P5,   KC_P6,   KC_LNUM, KC_CALC, QK_RBT,  QK_BOOT, EE_CLR,  XXXXXXX, XXXXXXX, BL_BRTG, BL_STEP, RGB_SAD, RGB_SAI,
    _______, KC_P1,   KC_P2,   KC_P3,   KC_PMNS, KC_PSLS, XXXXXXX, XXXXXXX, KC_MPRV, KC_MNXT, KC_MPLY, BL_OFF,  BL_ON,   RGB_VAD, RGB_VAI,
    _______, KC_P0,   KC_PDOT, KC_PENT, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, XXXXXXX, XXXXXXX, BL_TOGG, RGB_TOG, RGB_RMOD,RGB_MOD
  )
};

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        capslock_led_on();
    } else {
        capslock_led_off();
    }

    if (IS_LAYER_ON(_FN)) {
      gp100_led_on();
    } else {
      gp100_led_off();
    }

    return false;
}
