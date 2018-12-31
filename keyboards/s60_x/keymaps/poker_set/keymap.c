#include QMK_KEYBOARD_H

// Poker fix with set(state transition)
// Fn + Esc = `
// Fn + {left, down, up, right}  = {home, pgdown, pgup, end}
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│GRAVE│  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │▒▒▒▒▒│BKSPC│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │  \  │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│LCTRL│  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │▒▒▒▒▒│ENTER│█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│LSHFT│▒▒▒▒▒│  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │▒▒▒▒▒│RSHFT│▒▒▒▒▒│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│LCTRL│L_WIN│L_ALT│█████│█████│█████│ SPC │█████│█████│█████│ Fn0 │R_WIN│ APP │RCTRL│█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
    */
    LAYOUT_kc(
         GRV,    1,    2,   3,   4,   5,   6,   7,   8,    9,    0, MINS,  EQL,   NO, BSPC, \
         TAB,    Q,    W,   E,   R,   T,   Y,   U,   I,    O,    P, LBRC, RBRC, BSLS,       \
        LCTL,    A,    S,   D,   F,   G,   H,   J,   K,    L, SCLN, QUOT,   NO,  ENT,       \
        LSFT,   NO,    Z,   X,   C,   V,   B,   N,   M, COMM,  DOT, SLSH,   NO, RSFT,   NO, \
        LCTL, LGUI, LALT,                SPC,                  FN0, RGUI,  APP, RCTL),
    /* 1: Poker with Arrow
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │▒▒▒▒▒│     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│ Up  │▒▒▒▒▒│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │█████│█████│█████│     │█████│█████│█████│ Fn1 │Left │Down │Right│█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
    */
    LAYOUT_kc(
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       \
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       \
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,   UP, TRNS, \
        TRNS, TRNS, TRNS,                   TRNS,                    FN1, LEFT, DOWN, RGHT),
    /* 2: Poker with Esc
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │     │     │     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │▒▒▒▒▒│     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │▒▒▒▒▒│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │█████│█████│█████│     │█████│█████│█████│ Fn2 │     │     │     │█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
    */
    LAYOUT_kc(
         ESC, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
	TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       \
	TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       \
	TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
	TRNS, TRNS, TRNS,                   TRNS,                    FN2, TRNS, TRNS, TRNS),
    /* 3: Poker with Arrow and Esc
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ Esc │     │     │     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │▒▒▒▒▒│     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│ Up  │▒▒▒▒▒│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │█████│█████│█████│     │█████│█████│█████│ Fn3 │Left │Down │Right│█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
    */
    LAYOUT_kc(
         ESC, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       \
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       \
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,   UP, TRNS, \
        TRNS, TRNS, TRNS,                   TRNS,                    FN3, LEFT, DOWN, RGHT),
    /* 4: Poker Fn'd
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ Esc │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │▒▒▒▒▒│     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │ Fn6 │ Up  │     │     │     │     │     │     │ Cal │     │Home │ Ins │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │Left │Down │Right│     │     │ Psc │ Slk │Pause│     │ Fn8 │ End │▒▒▒▒▒│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │▒▒▒▒▒│ Del │     │ Web │Mute │ VoU │ VoD │     │PgUp │PgDwn│ Del │▒▒▒▒▒│     │▒▒▒▒▒│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │█████│█████│█████│ Fn5 │█████│█████│█████│ Fn4 │     │     │     │█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
    */
    LAYOUT_kc(
         ESC,   F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,  F10,  F11,  F12, TRNS, TRNS, \
        TRNS,  FN6,   UP, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, CALC, TRNS, HOME,  INS, TRNS,       \
        TRNS, LEFT, DOWN, RGHT, TRNS, TRNS, PSCR, SLCK, PAUS, TRNS,  FN8,  END, TRNS, TRNS,       \
        TRNS, TRNS,  DEL, TRNS, WHOM, MUTE, VOLU, VOLD, TRNS, PGUP, PGDN,  DEL, TRNS, TRNS, TRNS, \
        TRNS, TRNS, TRNS,                    FN5,                    FN4, TRNS, TRNS, TRNS),
    /* 5: Poker Fn'd arrow
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ Esc │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │▒▒▒▒▒│     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │ Fn7 │ Up  │     │     │     │     │     │     │ Cal │     │Home │ Ins │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │Left │Down │Right│     │     │ Psc │ Slk │Pause│     │ Fn8 │ End │▒▒▒▒▒│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │▒▒▒▒▒│ Del │     │ Web │Mute │ VoU │ VoD │     │PgUp │PgDwn│ Del │▒▒▒▒▒│PgUp │▒▒▒▒▒│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │█████│█████│█████│ Fn4 │█████│█████│█████│ Fn5 │Home │PgDwn│ End │█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
    */
    LAYOUT_kc(
         ESC,   F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,  F10,  F11,  F12, TRNS, TRNS, \
        TRNS,  FN7,   UP, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, CALC, TRNS, HOME,  INS, TRNS,       \
        TRNS, LEFT, DOWN, RGHT, TRNS, TRNS, PSCR, SLCK, PAUS, TRNS,  FN8,  END, TRNS, TRNS,       \
        TRNS, TRNS,  DEL, TRNS, WHOM, MUTE, VOLU, VOLD, TRNS, PGUP, PGDN,  DEL, TRNS, PGUP, TRNS, \
        TRNS, TRNS, TRNS,                    FN4,                    FN5, HOME, PGDN,  END),
    /* 6: Poker Fn'd Esc
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│Grave│ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │▒▒▒▒▒│     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │ Fn4 │ Up  │     │     │     │     │     │     │ Cal │     │Home │ Ins │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │Left │Down │Right│     │     │ Psc │ Slk │Pause│     │ Fn8 │ End │▒▒▒▒▒│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │▒▒▒▒▒│ Del │     │ Web │Mute │ VoU │ VoD │     │PgUp │PgDwn│ Del │▒▒▒▒▒│     │▒▒▒▒▒│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │█████│█████│█████│ Fn7 │█████│█████│█████│ Fn6 │     │     │     │█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
    */
    LAYOUT_kc(
         GRV,   F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,  F10,  F11,  F12, TRNS, TRNS, \
        TRNS,  FN4,   UP, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, CALC, TRNS, HOME,  INS, TRNS,       \
        TRNS, LEFT, DOWN, RGHT, TRNS, TRNS, PSCR, SLCK, PAUS, TRNS,  FN8,  END, TRNS, TRNS,       \
        TRNS, TRNS,  DEL, TRNS, WHOM, MUTE, VOLU, VOLD, TRNS, PGUP, PGDN,  DEL, TRNS, TRNS, TRNS, \
        TRNS, TRNS, TRNS,                    FN7,                    FN6, TRNS, TRNS, TRNS),
    /* 7: Poker Fn'd Arrow + Esc
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│Grave│ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │▒▒▒▒▒│     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │ Fn5 │ Up  │     │     │     │     │     │     │ Cal │     │Home │ Ins │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │Left │Down │Right│     │     │ Psc │ Slk │Pause│     │ Fn8 │ End │▒▒▒▒▒│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │▒▒▒▒▒│ Del │     │ Web │Mute │ VoU │ VoD │     │PgUp │PgDwn│ Del │▒▒▒▒▒│PgUp │▒▒▒▒▒│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │█████│█████│█████│ Fn6 │█████│█████│█████│ Fn7 │Home │PgDwn│ End │█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
    */
    LAYOUT_kc(
         GRV,   F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,  F10,  F11,  F12, TRNS, TRNS, \
        TRNS,  FN5,   UP, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, CALC, TRNS, HOME,  INS, TRNS,       \
        TRNS, LEFT, DOWN, RGHT, TRNS, TRNS, PSCR, SLCK, PAUS, TRNS,  FN8,  END, TRNS, TRNS,       \
        TRNS, TRNS,  DEL, TRNS, WHOM, MUTE, VOLU, VOLD, TRNS, PGUP, PGDN,  DEL, TRNS, PGUP, TRNS, \
        TRNS, TRNS, TRNS,                    FN6,                    FN7, HOME, PGDN,  END),
};

/*
 * Fn action definition
 */
const uint16_t PROGMEM fn_actions[] = {
    /* Poker Layout */
    [0] = ACTION_LAYER_SET(4, ON_PRESS),     // FN0 move to Fn'd             when press
    [1] = ACTION_LAYER_SET(5, ON_PRESS),     // FN1 move to Fn'd arrow       when press
    [2] = ACTION_LAYER_SET(6, ON_PRESS),     // FN2 move to Fn'd Esc         when press
    [3] = ACTION_LAYER_SET(7, ON_PRESS),     // FN3 move to Fn'd arrow + Esc when press

    //[4] = ACTION_LAYER_CLEAR(ON_RELEASE),    // FN4 clear overlay            when release
    [4] = ACTION_LAYER_SET(0, ON_RELEASE),   // FN4 clear overlay            when release
    [5] = ACTION_LAYER_SET(1, ON_RELEASE),   // FN5 move to arrow            when release
    [6] = ACTION_LAYER_SET(2, ON_RELEASE),   // FN6 move to Esc              when release
    [7] = ACTION_LAYER_SET(3, ON_RELEASE),   // FN7 move to arrow + Esc      when release

    [8] = ACTION_MODS_KEY(MOD_RCTL|MOD_RSFT, KC_ESC), // FN8 Task(RControl,RShift+Esc)
};
