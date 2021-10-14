#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _NUMPAD 0

enum custom_keycodes {
  NUMPAD = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* NUMPAD
 * ,----------------------------------.
 * |PPause|SkpBk |SkpFwd|      |Power |
 * | Esc  | Home | End  |Eject |Sleep |
 * | Bksp | Del  |  /   |  *   |  =   |
 * | Tab  |  7   |  8   |  9   |  -   |
 * |Pg Up |  4   |  5   |  6   |  +   |
 * |Pg Dn |  1   |  2   |  3   |XXXXXX|
 * |Space |  0   | Cmd  |  .   |Enter |
 * `----------------------------------'
 */
  [_NUMPAD] = LAYOUT_ortho_7x5(
    KC_MPLY, KC_MRWD, KC_MFFD, KC_INS,  KC_POWER,
    KC_ESC,  KC_HOME, KC_END,  KC_EJCT, KC_SLEP,
    KC_BSPC, KC_DEL,  KC_PSLS, KC_PAST, KC_PEQL,
    KC_TAB,  KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
    KC_PGUP, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_PGDN, KC_P1,   KC_P2,   KC_P3,   XXXXXXX,
    KC_SPC,  KC_P0,   KC_RCMD, KC_PDOT, KC_PENT
  ),
};
