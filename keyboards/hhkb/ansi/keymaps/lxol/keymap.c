/*  -*-  eval: (turn-on-orgtbl); -*-
 * lxol HHKB Layout
 */
#include QMK_KEYBOARD_H

#define BASE 0
#define WIN 1
#define HHKB 2
#define RGUILEV 3
#define LGUILEV 4
#define RALTLEV 5
#define LALTLEV 6

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Layer 0: Default Layer
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Esc    | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0   | -     | =        | \     | ` |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Tab    | Q | W | E | R | T | Y | U | I | O | P   | [     | ]        | Backs |   |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Contro | A | S | D | F | G | H | J | K | L | ;   | '     | RCtl/Ent |       |   |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Shift  | Z | X | C | V | B | N | M | , | . | Fn2 | Shift | Fn0      |       |   |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|

                 |------+------+-------+------+------|
                 | LAlt | LGUI | Space | RGUI | RAlt |
                 |------+------+-------+------+------|
    */

    [BASE] = LAYOUT( // layer 0 : default

        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, LT(LALTLEV, KC_A), LT(LGUILEV, KC_S), KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, LT(RGUILEV, KC_L), LT(RALTLEV, KC_SCLN), KC_QUOT, MT(MOD_RCTL, KC_ENT),
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(HHKB),
        KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, KC_RALT),

    /* Layer 1: HHKB mode (HHKB Fn)
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      | Pwr  | F1  | F2  | F3  | F4 | F5 | F6 | F7 | F8  | F9  | F10 | F11 | F12   | Ins   | Del |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      | Caps |     |     |     |    |    |    |    | Psc | Slk | Pus | Up  |       | Backs |     |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      |      | VoD | VoU | Mut |    |    | *  | /  | Hom | PgU | Lef | Rig | Enter |       |     |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      |      |     |     |     |    |    | +  | -  | End | PgD | Dow |     |       |       |     |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|

                      |---+---+---+---+---|
                      |   |   |   |   |   |
                      |---+---+---+---+---|
     */

    [HHKB] = LAYOUT(
        KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP, KC_TRNS, KC_BSPC,
        KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_PENT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PPLS, KC_PMNS, KC_END, KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    /* Layer LGUI: All keys with RGUI modifier
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Esc    | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0   | -     | =        | \     | ` |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Tab    | Q | W | E | R | T | Y | U | I | O | P   | [     | ]        | Backs |   |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Contro | A | S | D | F | G | H | J | K |   | ;   | '     | RCtl/Ent |       |   |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Shift  | Z | X | C | V | B | N | M | , | . | Fn2 | Shift | Fn0      |       |   |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|

                 |------+------+-------+------+------|
                 | LAlt | LGUI | Space | RGUI | RAlt |
                 |------+------+-------+------+------|
    */

    [RGUILEV] = LAYOUT( // Right GUI layer  by KC_L

        RGUI(KC_ESC), RGUI(KC_1), RGUI(KC_2), RGUI(KC_3), RGUI(KC_4), RGUI(KC_5), RGUI(KC_6), RGUI(KC_7), RGUI(KC_8), RGUI(KC_9), RGUI(KC_0), RGUI(KC_MINS), RGUI(KC_EQL), RGUI(KC_BSLS), RGUI(KC_GRV),
        RGUI(KC_TAB), RGUI(KC_Q), RGUI(KC_W), RGUI(KC_E), RGUI(KC_R), RGUI(KC_T), RGUI(KC_Y), RGUI(KC_U), RGUI(KC_I), RGUI(KC_O), RGUI(KC_P), RGUI(KC_LBRC), RGUI(KC_RBRC), RGUI(KC_BSPC),
        RGUI(KC_LCTL), RGUI(KC_A), RGUI(KC_S), RGUI(KC_D), RGUI(KC_F), RGUI(KC_G), RGUI(KC_H), RGUI(KC_J), RGUI(KC_K), KC_TRNS, KC_TRNS, RGUI(KC_QUOT), MT(MOD_RCTL, KC_ENT),
        RGUI(KC_LSFT), RGUI(KC_Z), RGUI(KC_X), RGUI(KC_C), RGUI(KC_V), RGUI(KC_B), RGUI(KC_N), RGUI(KC_M), RGUI(KC_COMM), RGUI(KC_DOT), RGUI(KC_SLSH), RGUI(KC_RSFT), KC_TRNS,
        KC_LALT, KC_LGUI, RGUI(KC_SPC), KC_RGUI, KC_RALT),

    /* Layer LGUI: All keys with LGUI modifier
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Esc    | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0   | -     | =        | \     | ` |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Tab    | Q | W | E | R | T | Y | U | I | O | P   | [     | ]        | Backs |   |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Contro | A | S | D | F | G | H | J | K |   | ;   | '     | RCtl/Ent |       |   |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Shift  | Z | X | C | V | B | N | M | , | . | Fn2 | Shift | Fn0      |       |   |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|

                 |------+------+-------+------+------|
                 | LAlt | LGUI | Space | LGUI | RAlt |
                 |------+------+-------+------+------|
    */

    [LGUILEV] = LAYOUT( // Right GUI layer  by KC_L

        LGUI(KC_ESC), LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), LGUI(KC_6), LGUI(KC_7), LGUI(KC_8), LGUI(KC_9), LGUI(KC_0), LGUI(KC_MINS), LGUI(KC_EQL), LGUI(KC_BSLS), LGUI(KC_GRV),
        LGUI(KC_TAB), LGUI(KC_Q), LGUI(KC_W), LGUI(KC_E), LGUI(KC_R), LGUI(KC_T), LGUI(KC_Y), LGUI(KC_U), LGUI(KC_I), LGUI(KC_O), LGUI(KC_P), LGUI(KC_LBRC), LGUI(KC_RBRC), LGUI(KC_BSPC),
        LGUI(KC_LCTL), KC_TRNS, KC_TRNS, LGUI(KC_D), LGUI(KC_F), LGUI(KC_G), LGUI(KC_H), LGUI(KC_J), LGUI(KC_K), LGUI(KC_L), LGUI(KC_SCLN), LGUI(KC_QUOT), MT(MOD_RCTL, KC_ENT),
        KC_LSFT, LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), LGUI(KC_B), LGUI(KC_N), LGUI(KC_M), LGUI(KC_COMM), LGUI(KC_DOT), LGUI(KC_SLSH), KC_RSFT, KC_TRNS,
        KC_LALT, KC_LGUI, LGUI(KC_SPC), KC_LGUI, KC_RALT),

    /* Layer LALT: All keys with RALT modifier
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Esc    | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0   | -     | =        | \     | ` |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Tab    | Q | W | E | R | T | Y | U | I | O | P   | [     | ]        | Backs |   |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Contro | A | S | D | F | G | H | J | K |   | ;   | '     | RCtl/Ent |       |   |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Shift  | Z | X | C | V | B | N | M | , | . | Fn2 | Shift | Fn0      |       |   |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|

                 |------+------+-------+------+------|
                 | LAlt | LGUI | Space | RGUI | RAlt |
                 |------+------+-------+------+------|
    */

    [RALTLEV] = LAYOUT( // Right ALT layer  by KC_L

        RALT(KC_ESC), RALT(KC_1), RALT(KC_2), RALT(KC_3), RALT(KC_4), RALT(KC_5), RALT(KC_6), RALT(KC_7), RALT(KC_8), RALT(KC_9), RALT(KC_0), RALT(KC_MINS), RALT(KC_EQL), RALT(KC_BSLS), RALT(KC_GRV),
        RALT(KC_TAB), RALT(KC_Q), RALT(KC_W), RALT(KC_E), RALT(KC_R), RALT(KC_T), RALT(KC_Y), RALT(KC_U), RALT(KC_I), RALT(KC_O), RALT(KC_P), RALT(KC_LBRC), RALT(KC_RBRC), RALT(KC_BSPC),
        RALT(KC_LCTL), RALT(KC_A), RALT(KC_S), RALT(KC_D), RALT(KC_F), RALT(KC_G), RALT(KC_H), RALT(KC_J), RALT(KC_K), KC_TRNS, KC_TRNS, RALT(KC_QUOT), MT(MOD_RCTL, KC_ENT),
        RALT(KC_LSFT), RALT(KC_Z), RALT(KC_X), RALT(KC_C), RALT(KC_V), RALT(KC_B), RALT(KC_N), RALT(KC_M), RALT(KC_COMM), RALT(KC_DOT), RALT(KC_SLSH), RALT(KC_RSFT), KC_TRNS,
        KC_LALT, KC_LGUI, RALT(KC_SPC), KC_RGUI, KC_RALT),

    /* Layer LALT: All keys with LALT modifier
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Esc    | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0   | -     | =        | \     | ` |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Tab    | Q | W | E | R | T | Y | U | I | O | P   | [     | ]        | Backs |   |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Contro | A | S | D | F | G | H | J | K |   | ;   | '     | RCtl/Ent |       |   |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|
     | Shift  | Z | X | C | V | B | N | M | , | . | Fn2 | Shift | Fn0      |       |   |
     |--------+---+---+---+---+---+---+---+---+---+-----+-------+----------+-------+---|

                 |------+------+-------+------+------|
                 | LAlt | LGUI | Space | LGUI | RAlt |
                 |------+------+-------+------+------|
    */

    [LALTLEV] = LAYOUT( // Right ALT layer  by KC_L

        LALT(KC_ESC), LALT(KC_1), LALT(KC_2), LALT(KC_3), LALT(KC_4), LALT(KC_5), LALT(KC_6), LALT(KC_7), LALT(KC_8), LALT(KC_9), LALT(KC_0), LALT(KC_MINS), LALT(KC_EQL), LALT(KC_BSLS), LALT(KC_GRV),
        LALT(KC_TAB), LALT(KC_Q), LALT(KC_W), LALT(KC_E), LALT(KC_R), LALT(KC_T), LALT(KC_Y), LALT(KC_U), LALT(KC_I), LALT(KC_O), LALT(KC_P), LALT(KC_LBRC), LALT(KC_RBRC), LALT(KC_BSPC),
        LALT(KC_LCTL), KC_TRNS, KC_TRNS, LALT(KC_D), LALT(KC_F), LALT(KC_G), LALT(KC_H), LALT(KC_J), LALT(KC_K), LALT(KC_L), LALT(KC_SCLN), LALT(KC_QUOT), MT(MOD_RCTL, KC_ENT),
        KC_LSFT, LALT(KC_Z), LALT(KC_X), LALT(KC_C), LALT(KC_V), LALT(KC_B), LALT(KC_N), LALT(KC_M), LALT(KC_COMM), LALT(KC_DOT), LALT(KC_SLSH), KC_RSFT, KC_TRNS,
        KC_LALT, KC_LGUI, LALT(KC_SPC), KC_LGUI, KC_RALT),

    /* Layer WIN: Win layer
     |--------+---+---+---+---+---+---+---+---+---+---+-------+----------+-------+---|
     | Esc    | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | -     | =        | \     | ` |
     |--------+---+---+---+---+---+---+---+---+---+---+-------+----------+-------+---|
     | Tab    | Q | W | E | R | T | Y | U | I | O | P | [     | ]        | Backs |   |
     |--------+---+---+---+---+---+---+---+---+---+---+-------+----------+-------+---|
     | Contro | A | S | D | F | G | H | J | K | L | ; | '     | RCtl/Ent |       |   |
     |--------+---+---+---+---+---+---+---+---+---+---+-------+----------+-------+---|
     | Shift  | Z | X | C | V | B | N | M | , | . | / | Shift | Fn0      |       |   |
     |--------+---+---+---+---+---+---+---+---+---+---+-------+----------+-------+---|

                 |------+------+-------+------+------|
                 | LGui | LAlt | Space | RGui | Ralt |
                 |------+------+-------+------+------|
    */

    [WIN] = LAYOUT( // BASE level with swapped GUI/ALT

        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, LT(LGUILEV, KC_A), LT(LALTLEV, KC_S), KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, LT(RALTLEV, KC_L), LT(RGUILEV, KC_SCLN), KC_QUOT, MT(MOD_RCTL, KC_ENT),
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(HHKB),
        KC_RGUI, KC_RALT, KC_SPC, KC_RALT, KC_RGUI)};
