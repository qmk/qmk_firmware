#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER  1
#define _RAISE  2
#define _BL 4 // Backlight
// #define _ADJUST 3
#define TG_NKRO MAGIC_TOGGLE_NKRO


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  Del | Alt  | GUI  |Lower | Space|Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, \
  KC_LCTL, KC_DEL, KC_LALT, KC_LGUI, MO(_LOWER),KC_SPC,KC_SPC,  MO(_RAISE),   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Shift|PrScr |ISO ~ |ISO | |      |      |      |      |      |bl_on |bl_stp| Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | nkro | Alt  | NKRO |Lower | PgDn | PgUp |Raise | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, _______, \
  KC_LSFT, KC_PSCR, S(KC_NUHS), S(KC_NUBS), _______, _______, _______, _______, _______, BL_ON, BL_STEP, KC_ENT, \
  KC_LCTL, MAGIC_TOGGLE_NKRO, KC_LALT, TG_NKRO, _______, KC_PGDN, KC_PGUP, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | Caps |  +   |  -   |  =   |   (  |   )  |      |   7  |   8  |   9  | Bksp | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Lock |  ~   |  _   |      |   [  |   ]  |      |   4  |   5  |   6  |      |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Ins  |  `   |   \  |   |  |   {  |   }  |      |   1  |   2  |   3  |   .  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      | Alt  |      |Lower |      |      |Raise |   0  |      | Home | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12( \
  KC_CAPS, KC_MINS, KC_PLUS, KC_EQL,  KC_LPRN, KC_RPRN, _______, KC_7,  KC_8,    KC_9, KC_BSPC, KC_DEL, \
  KC_LOCK,  KC_TILD, KC_UNDS, _______,KC_LBRC, KC_RBRC, _______, KC_4,  KC_5,    KC_6, _______, _______, \
  KC_INS, KC_GRV, KC_BSLS, KC_PIPE,  KC_LCBR, KC_RCBR, _______, KC_1,  KC_2,    KC_3, KC_DOT, _______, \
  KC_LCTL, _______, KC_LALT, _______, _______, _______, _______, _______, KC_0, _______, KC_HOME, KC_END \
)

/* Adjust
 G = git
 M = mail
 * ,-----------------------------------------------------------------------------------.
 * | gAdd |gStash|      | const|      | Clog |      |      | Mstk | Mrad |Mgmail|      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | gPush|      |      | if() |      | Clog2|      |      |      |      |Mcity |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | gPull|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Lower |      |      |Raise |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */


/* Empty
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Lower |      |      |Raise |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
};

// Macro actions for each corresponding ID.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch (id) {
  case 0:
    if (record->event.pressed) {
      register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
      backlight_step();
#endif
    }
    else {
      unregister_code(KC_RSFT);
    }
    break;
  }
  return MACRO_NONE;
};

// Loop
void matrix_scan_user(void) {
  // Empty
};
