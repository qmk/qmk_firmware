/*  -*-  eval: (turn-on-orgtbl); -*-
 * default HHKB Layout
 */
#include QMK_KEYBOARD_H

#define BASE 0
#define HHKB 1
#define MOVEMENT 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* BASE Level: Default Layer
     |--------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+-----|
     | ESC    | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | -     | =   | Backs |Backs|
     |--------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+-----|
     | Tab    | Q | W | E | R | T | Y | U | I | O | P | [     | ]   | \     |     |
     |--------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+-----|
     |Ctrl/ESC| A | S | D | F | G | H | J | K | L | ; | '     | Ent |       |     |
     |--------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+-----|
     | Shift  | Z | X | C | V | B | N | M | , | . | / | Shift | Fn0 |       |     |
     |--------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+-----|
            |------+------+-----------------------+------+------|
            | LAlt | LGUI | ******* Space ******* | MOUSE| RAlt |
            |------+------+-----------------------+------+------|
    */

    [BASE] = LAYOUT( //  default layer
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Z, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        CTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Y, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(HHKB),
        KC_LALT, KC_LCMD, /*          */ KC_SPC, /*       */ MO(MOVEMENT), KC_RALT),

    /* Layer HHKB: HHKB mode (HHKB Fn)
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      | Pwr  | F1  | F2  | F3  | F4 | F5 | F6 | F7 | F8  | F9  | F10 | F11 | F12   | DEL   | DEL |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      | Caps |     |     |     |    |    |    |    | Psc | Slk | Pus | Up  |       | Backs |     |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      |      | VoD | VoU | Mut |    |    | *  | /  | Hom | PgU | Lef | Rig | Enter |       |     |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      |      |     |     |     |    |    | +  | -  | End | PgD | Dow |     |       |       |     |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
                 |------+------+----------------------+------+------+
                 | **** | **** | ******************** | **** | **** |
                 |------+------+----------------------+------+------+
     */

    [HHKB] = LAYOUT(
        KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_DEL,
        KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP, KC_TRNS, KC_BSPC,
        KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_PENT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PPLS, KC_PMNS, KC_END, KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    /* Layer MOUSE: MOUSE mode (MOUSE Fn)
      |------+-----+-----+-----+----+----+--------+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      | `~   |ACC1 |ACC2 |ACC3 |    |    |        |                |              |           |             |     |       | DEL   | DEL |
      |------+-----+-----+-----+----+----+--------+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      |      |MBTN2|     | up  |    | PgU|        |                |              |           |             |     |       |       |     |
      |------+-----+-----+-----+----+----+--------+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      |      |MBTN1|right|down |left| PgD|  <-    |  down arrow    |   up arrow   |  ->       |             |     |       |       |     |
      |------+-----+-----+-----+----+----+--------+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
      |      |MBTN3|     |     |    |    |        |     ~ (N)      |              |           |             |     |       |       |     |
      |------+-----+-----+-----+----+----+--------+----------------+--------------+-----------+-------------+-----+-------+-------+-----|
                 |------+------+----------------------+------+------+
                 | **** | **** | ******************** | **** | **** |
                 |------+------+----------------------+------+------+
     */

    [MOVEMENT] = LAYOUT(
        KC_GRV, KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_BTN2, KC_TRNS, KC_MS_U, KC_TRNS, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_PGDN, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_BTN3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TILD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)};