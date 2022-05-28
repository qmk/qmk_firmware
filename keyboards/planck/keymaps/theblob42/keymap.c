#include QMK_KEYBOARD_H

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _MEDIA,
  _MOUSE,
  _MOVE,
  _FN
};

#define MOVE MO(_MOVE)
#define MEDIA MO(_MEDIA)
#define FN MO(_FN)
#define LOWER_SPACE LT(_LOWER, KC_SPC)
#define RAISE_SPACE LT(_RAISE, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty (base layer)
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc¹ |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '¹  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps²|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter²|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |Media | GUI  | Alt  |  FN  |SpcUp |SpcDn | Move | Alt  | Gui  |Mouse | Ctrl |
 * `-----------------------------------------------------------------------------------'
 * ¹ Ctrl when held
 * ² Shift when held
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,          KC_Q,  KC_W,    KC_E,    KC_R, KC_T,        KC_Y,        KC_U, KC_I,    KC_O,    KC_P,    KC_BSPC,
    LCTL_T(KC_ESC),  KC_A,  KC_S,    KC_D,    KC_F, KC_G,        KC_H,        KC_J, KC_K,    KC_L,    KC_SCLN, RCTL_T(KC_QUOT),
    LSFT_T(KC_CAPS), KC_Z,  KC_X,    KC_C,    KC_V, KC_B,        KC_N,        KC_M, KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENTER),
    KC_LCTL,         MEDIA, KC_LGUI, KC_LALT, FN,   LOWER_SPACE, RAISE_SPACE, MOVE, KC_RALT, KC_RGUI, MO(_MOUSE), KC_RCTL
),

/* MOVE
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      | PgUp |  Up  | PgDn |      |Print |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      |      |      |      |      | Home | Left | Down | Right| End  | Ctrl |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      | Home |      | End  |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      | GUI  | ALT  |      | SPC  | SPC  |      | Alt  | GUI  |      | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_MOVE] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP,   KC_UP, KC_PGDN, XXXXXXX, KC_PSCR,
    KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END, KC_RCTL,
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, XXXXXXX,  KC_END, XXXXXXX, KC_ENTER,
    KC_LCTL, XXXXXXX, KC_LGUI, KC_LALT, XXXXXXX, KC_SPC,  KC_SPC,  _______, KC_RALT, KC_RGUI, XXXXXXX, KC_RCTL
),

/* FN
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |Print |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | Ctrl |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|      |      |      |      |  F11 |  F12 |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      | GUI  | Alt  |      | SPC  | SPC  |      | Alt  | GUI  |      | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_FN] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,
    KC_LCTL, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_RCTL,
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENTER,
    KC_LCTL, XXXXXXX, KC_LGUI, KC_LALT, _______, KC_SPC,  KC_SPC,  XXXXXXX, KC_RALT, KC_RGUI, XXXXXXX, KC_RCTL
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | Del  |      |      |      |      |      |      |   [  |   ]  |   -  |   =  |  BS  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl`|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |Ctrl_\|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift| NUBS¹| NUHS²|      |      |      |      |      |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |Shift |      | Alt  | GUI  |      | Ctrl |
 * `-----------------------------------------------------------------------------------'
 * ¹ Non US \ and |
 * ² Non US # and ~
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_DEL,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL,  KC_BSPC,
    LCTL_T(KC_GRV),  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    RCTL_T(KC_BSLS),
    KC_LSFT,         KC_NUBS, KC_NUHS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_LSFT, XXXXXXX, KC_RALT, KC_RGUI, XXXXXXX, KC_RCTL
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | Del  |      |      |      |      |      |      |   [  |   ]  |   -  |   =  |  BS  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl`|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |Ctrl_\|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift| NUBS¹| NUHS²|      |      |      |      |      |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      | GUI  | Alt  |      |Shift |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 * ¹ Non US \ and |
 * ² Non US # and ~
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_DEL,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL,  KC_BSPC,
    LCTL_T(KC_GRV),  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    RCTL_T(KC_BSLS),
    KC_LSFT,         KC_NUBS, KC_NUHS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL,         XXXXXXX, KC_LGUI, KC_LALT, XXXXXXX, KC_LSFT, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Mouse
 * ,-----------------------------------------------------------------------------------.
 * |      |R_Clck| M_Up |L_Clck|ScrlUp|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |M_Left|M_Dwn |M_Rght|ScrlDn|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |M_Clck|      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_planck_grid(
    XXXXXXX, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_WH_L, KC_BTN3, KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX
),

/* Media
 * ,-----------------------------------------------------------------------------------.
 * |Reset |      |      |      |      |      |      | Bri- | Bri+ |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Prev | Play |Pause | Next |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Vol- | Vol+ | Mute |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      | GUI  | Alt  |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MEDIA] = LAYOUT_planck_grid(
    RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, KC_MUTE, XXXXXXX, XXXXXXX,
    KC_LCTL, _______, KC_LGUI, KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER_SPACE:
            return 150;
        case RAISE_SPACE:
            return 150;
        default:
            return TAPPING_TERM;
    }
}
