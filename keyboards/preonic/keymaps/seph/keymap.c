#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _LO 1
#define _RA 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  -   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | Left |Right |Lower |    Space    |Raise |  Up  | Down |  GUI |Enter |
 * `-----------------------------------------------------------------------------------'
 */
[_QW] = LAYOUT_ortho_5x12 ( \
   KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL , \
   KC_MINS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
   KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT, MO(_LO), KC_SPC,  KC_SPC,  MO(_RA), KC_UP,   KC_DOWN, KC_RGUI, KC_ENT  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |      |      |      |      |      |      |      |      |      |      |  |   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Caps |      | Mute | Vol- | Vol+ |      |      |      |   +  |   {  |   }  | PrSc |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      | Prev | Play | Next |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite|      | Home |  End |      |     Ins     |      | PgUp | PgDN |      |Enter |
 * `-----------------------------------------------------------------------------------'
 */
[_LO] = LAYOUT_ortho_5x12 ( \
   KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12 , \
   KC_TILD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PIPE, \
   KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, KC_PLUS, KC_LCBR, KC_RCBR, KC_PSCR, \
   _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, \
   BL_STEP, _______, KC_HOME, KC_END,  _______, KC_INS,  KC_INS,  _______, KC_PGUP, KC_PGDN, _______, _______ \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |      |      |      |      |      |      |      |      |      |      |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Caps |      | Mute | Vol- | Vol+ |      |      |      |   =  |   [  |   ]  | PrSc |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      | Prev | Play | Next |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite|      | Home |  End |      |     Ins     |      | PgUp | PgDN |      |Enter |
 * `-----------------------------------------------------------------------------------'
 */
[_RA] = LAYOUT_ortho_5x12 ( \
   KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12 , \
   KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, \
   KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, KC_EQL,  KC_LBRC, KC_RBRC, KC_PSCR, \
   _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, \
   BL_STEP, _______, KC_HOME, KC_END,  _______, KC_INS,  KC_INS,  _______, KC_PGUP, KC_PGDN, _______, _______ \
)

};
