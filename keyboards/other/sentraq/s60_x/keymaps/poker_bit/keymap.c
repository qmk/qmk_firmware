#include QMK_KEYBOARD_H

#define KC_TG5 TG(5)
#define KC_TG6 TG(6)
#define KC_CSES C(S(KC_ESC))

// Poker fix with toggle and bit operation
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
    /* 4: Poker Default + Fn'd
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ Esc │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │▒▒▒▒▒│     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│Caps │ Fn2 │ Up  │     │     │     │     │     │     │ Cal │     │Home │ Ins │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │Left │Down │Right│     │     │ Psc │ Slk │Pause│     │ Fn4 │ End │▒▒▒▒▒│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │▒▒▒▒▒│ Del │     │ Web │Mute │ VoU │ VoD │     │PgUp │PgDwn│ Del │▒▒▒▒▒│     │▒▒▒▒▒│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │█████│█████│█████│ Fn1 │█████│█████│█████│     │     │     │     │█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
    */
    [4] = LAYOUT_kc(
        TRNS,   F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,  F10,  F11,  F12, TRNS, TRNS, \
        CAPS,  TG6,   UP, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, CALC, TRNS, HOME,  INS, TRNS,       \
        TRNS, LEFT, DOWN, RGHT, TRNS, TRNS, PSCR, SLCK, PAUS, TRNS, CSES,  END, TRNS, TRNS,       \
        TRNS, TRNS,  DEL, TRNS, WHOM, MUTE, VOLU, VOLD, TRNS, PGUP, PGDN,  DEL, TRNS, TRNS, TRNS, \
        TRNS, TRNS, TRNS,                    TG5,                   TRNS, TRNS, TRNS, TRNS),
    /* 5: Poker with Arrow
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │▒▒▒▒▒│     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│PgUp │▒▒▒▒▒│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │█████│█████│█████│     │█████│█████│█████│ Fn3 │Home │PgDwn│ End │█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
    */
    LAYOUT_kc(
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       \
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       \
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, PGUP, TRNS, \
        TRNS, TRNS, TRNS,                   TRNS,                    FN3, HOME, PGDN,  END),
    /* 6: Poker with Esc
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │     │     │     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │▒▒▒▒▒│     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │▒▒▒▒▒│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │█████│█████│█████│     │█████│█████│█████│     │     │     │     │█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
    */
    LAYOUT_kc(
         ESC, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
	TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       \
	TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       \
	TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
	TRNS, TRNS, TRNS,                   TRNS,                   TRNS, TRNS, TRNS, TRNS),
    /* 7: Poker with Arrow + Fn'd
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │▒▒▒▒▒│     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│ Up  │▒▒▒▒▒│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │█████│█████│█████│     │█████│█████│█████│     │Left │Down │Right│█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
    */
    LAYOUT_kc(
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       \
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       \
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,   UP, TRNS, \
        TRNS, TRNS, TRNS,                   TRNS,                   TRNS, LEFT, DOWN, RGHT),
};
const uint16_t PROGMEM fn_actions[] = {
    /* Poker Layout */
    [0] = ACTION_LAYER_BIT_XOR(1, 0b0101, ON_BOTH),   // Poker Fn(with fix for Esc)
    [3] = ACTION_LAYER_BIT_XOR(1, 0b1101, ON_BOTH),   // Poker Fn(with fix for Arrow)
};
