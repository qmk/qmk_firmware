/*  -*-  eval: (turn-on-orgtbl); -*-
 * Brettm12345 HHKB Layout
 */
#include QMK_KEYBOARD_H
#include "brett.h"

enum layers {
   BASE = 0,
   HHKB = 1,
   PROG = 2,
   MOUSE = 3
};

// Tap for tab hold for MOUSE
#define TAB_MOUSE LT(MOUSE, KC_TAB)

// Tap for space hold for PROG
#define SPACE_PROG LT(PROG, KC_SPC)

// Tap for ESC hold for CTRL
#define CTL_ESC CTL_T(KC_ESC)

// Tab for ; hold for PROG
#define PROG_SCLN LT(PROG, KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* BASE Level: Default Layer
     |---------+---+---+---+---+---+---+---+---+---+---+--------+--------+-----------+---|
     | Esc     | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | -      | =      | \         | ` |
     |---------+---+---+---+---+---+---+---+---+---+---+--------+--------+-----------+---|
     | Tab     | Q | W | E | R | T | Y | U | I | O | P | [      | ]      | Backspace | * |
     |---------+---+---+---+---+---+---+---+---+---+---+--------+--------+-----------+---|
     | Control | A | S | D | F | G | H | J | K | L | ; | '      | Return | ******    | * |
     |---------+---+---+---+---+---+---+---+---+---+---+--------+--------+-----------+---|
     | LShift  | Z | X | C | V | B | N | M | , | . | / | RShift | HHKB   | ******    | * |
     |---------+---+---+---+---+---+---+---+---+---+---+--------+--------+-----------+---|

                |------+------+----------------------------+------+------|
                | LAlt | LGUI | ******* Space/Prog ******* | RGUI | RAlt |
                |------+------+----------------------------+------+------|
    */

	[BASE] = LAYOUT(
    KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV,
    TAB_MOUSE, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC,
    CTL_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, PROG_SCLN, KC_QUOT, KC_ENT,
    KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, MO(HHKB),
    KC_LALT, KC_LGUI, SPACE_PROG, KC_RGUI, KC_RALT),

    /* HHKB Level: Function Layer
     |---------+------+------+--------+---------+-------+-----------+---------+---------+---------+----------------+--------+------+--------+-----|
     | PWR     | F1   | F2   | F3     | F4      | F5    | F6        | F7      | F8      | F9      | F10            | F11    | F12  | Ins    | Del |
     |---------+------+------+--------+---------+-------+-----------+---------+---------+---------+----------------+--------+------+--------+-----|
     | Caps    | Calc | Mail | Media  | Browser | My PC | Browser   | u       | i       | o       | Print          | [      | ]    | Backsp | *   |
     |         |      |      | Player | Refresh |       | Favorites |         |         |         | Screen         |        |      |        |     |
     |---------+------+------+--------+---------+-------+-----------+---------+---------+---------+----------------+--------+------+--------+-----|
     | Control | Prev | Next | Find   | f       | g     | Browser   | Browser | Browser | Browser | ;              | '      | Exec | ****** | *   |
     |         |      |      |        |         |       | Back      | Home    | Search  | Forward |                |        |      |        |     |
     |---------+------+------+--------+---------+-------+-----------+---------+---------+---------+----------------+--------+------+--------+-----|
     | LShift  | Vol+ | Vol- | Mute   | Select  | b     | n         | m       | ,       | Again   | Browser Search | RShift | HHKB | ****** | *   |
     |---------+------+------+--------+---------+-------+-----------+---------+---------+---------+----------------+--------+------+--------+-----|

                |------+------+----------------------+------+------|
                | Menu | LGUI | ******* Play ******* | RGUI | Menu |
                |------+------+----------------------+------+------|
    */
	[HHKB] = LAYOUT(
    KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
    KC_CAPS, KC_CALC, KC_MAIL, KC_MSEL, KC_WREF, KC_MYCM, KC_WFAV, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_TRNS, KC_TRNS, KC_BSPC,
    KC_TRNS, KC_MPRV, KC_MNXT, KC_FIND, KC_TRNS, KC_TRNS, KC_WBAK, KC_WHOM, KC_WSCH, KC_WFWD, KC_TRNS, KC_TRNS, KC_EXEC,
    KC_TRNS, KC__VOLUP, KC_VOLD, KC_MUTE, KC_SLCT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_AGIN, KC_WSCH, KC_TRNS, KC_TRNS,
    KC_MENU, KC_TRNS, KC_MPLY, KC_TRNS, KC_MENU),


    /* Programming Level: Symbols Layer
     |-------------+----+---+-----+-----+----+------+------+-----+-------+-----+-------+--------+--------+---|
     | Esc         | 1  | 2 | 3   | 4   | 5  | 6    | 7    | 8   | 9     | 0   | -     | =      | \      | ` |
     |-------------+----+---+-----+-----+----+------+------+-----+-------+-----+-------+--------+--------+---|
     | Tab/Mouse   | => | @ | >>= | =<< | ‖  | <>   | <｜> | <*> | <@>   | ｜> | <$    | $>     | Backsp | * |
     |-------------+----+---+-----+-----+----+------+------+-----+-------+-----+-------+--------+--------+---|
     | Esc/Control | -> | * | <$> | <#> | && | Left | Down | Up  | Right | ::  | `     | Return | ****** | * |
     |-------------+----+---+-----+-----+----+------+------+-----+-------+-----+-------+--------+--------+---|
     | LShift      | z  | x | c   | v   | b  | n    | m    | <-  | ->    | <>  | Shift | HHKB   | ****** | * |
     |-------------+----+---+-----+-----+----+------+------+-----+-------+-----+-------+--------+--------+---|

                |------+------+----------------------------+------+------|
                | LAlt | LGUI | ******* Space/Prog ******* | RGUI | RAlt |
                |------+------+----------------------------+------+------|
    */
	[PROG] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, FAT_ARROW, KC_AT, BIND, BIND_FLIPPED, OR, CONCAT, ALT, APPLY, FLAP, PIPE, VOID_LEFT, VOID_RIGHT, KC_TRNS,
    KC_TRNS, SKINNY_ARROW, KC_ASTR, MAP, MAP_FLIPPED, AND, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, DOUBLE_COLON, KC_GRV, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, REVERSE_ARROW, SKINNY_ARROW, CONCAT, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),


    /* Mouse Level: Mouse Layer
     |--------------+---+---+---+---+---+------+------+---------+---------+---------+-----------+-----------------+--------+---|
     | Esc          | 1 | 2 | 3 | 4 | 5 | 6    | 7    | 8       | 9       | 0       | -         | =               | \      | ` |
     |--------------+---+---+---+---+---+------+------+---------+---------+---------+-----------+-----------------+--------+---|
     | Mouse(Tab)   | Q | W | E | R | T | Y    | U    | I       | O       | P       | [         | ]               | Backsp | * |
     |--------------+---+---+---+---+---+------+------+---------+---------+---------+-----------+-----------------+--------+---|
     | Control(Esc) | A | S | D | F | G | Left | Down | Up      | Right   | Button1 | Button2   | Control(Return) | ****** | * |
     |--------------+---+---+---+---+---+------+------+---------+---------+---------+-----------+-----------------+--------+---|
     | LShift(()    | Z | X | C | V | B | N    | M    | Button5 | Button4 | Button3 | RShift()) | HHKB            | ****** | * |
     |--------------+---+---+---+---+---+------+------+---------+---------+---------+-----------+-----------------+--------+---|

                |---------+---------+----------------------------+---------+---------|
                | LAlt([) | LGUI({) | ******* Space/Prog ******* | RGUI(}) | RAlt(]) |
                |---------+---------+----------------------------+---------+---------|
    */
	[MOUSE] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, KC_BTN2, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN5, KC_BTN4, KC_BTN3, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

