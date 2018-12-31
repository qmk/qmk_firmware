#define KC_RESET 0x5000
#include "keymap_common.h"

enum planck_layers {
  _DVRK,
  _LOWER,
  _RAISE,
  _ADJUST
};

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * |   "  |   ,  |   .  |   P  |   Y  |   /  |   =  |   F  |   G  |   C  |   R  |   L  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   A  |   O  |   E  |   U  |   I  | ESC  | BSPC |   D  |   H  |   T  |   N  |   S  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ;  |   Q  |   J  |   K  |   X  | TAB  | ENT  |   B  |   M  |   W  |   V  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Sft  | Ctl  | Alt  | Gui  |Lower |    Space    |Raise |   <  |   v  |   ^  |   >  |
 * `-----------------------------------------------------------------------------------'
 */
    [_DVRK] = KEYMAP( 
      QUOT, COMM,  DOT,    P,    Y, SLSH,  EQL,    F,    G,    C,    R,    L,
         A,    O,    E,    U,    I,  ESC, BSPC,    D,    H,    T,    N,    S,
      SCLN,    Q,    J,    K,    X,  TAB,  ENT,    B,    M,    W,    V,    Z,
      LSFT, LCTL, LALT, LGUI,  FN1,  SPC,        FN2, LEFT, DOWN,   UP, RGHT),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | F1   |  F2  |  F3  |  F4  |  F5  |  {   |  }   |  F6  |  F7  |  F8  |  F9  | F10  | 
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  1   |   2  |   3  |   4  |   5  |  [   |  ]   |   6  |   7  |   8  |   9  |  0   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   ~  |   |  |   `  |   -  |   _  | INS  | DEL  |   (  |   )  |   +  |   =  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Sft  | Ctl  | Alt  | Gui  |Lower |    Space    |Raise |      | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
    [_LOWER] = KEYMAP( /* fn1 lower */
        F1,   F2,   F3,   F4,   F5, FN26, FN27,   F6,   F7,   F8,   F9,  F10,
         1,    2,    3,    4,    5, LBRC, RBRC,    6,    7,    8,    9,    0,
       FN23, FN25,  GRV,MINS, FN24, INS,   DEL, FN19, FN20, FN22,  EQL, BSLS,
      TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,        FN4, HOME, PGDN, PGUP,  END),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | F11  |  F12 |  F13 |  F14 |  F15 |  -   |  _   |  F16 |  F17 |  F18 |  F19 | F20  | 
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  !   |   @  |   #  |   $  |   %  |      |      |   ^  |   &  |   *  |   (  |  )   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
    [_RAISE] = KEYMAP( /* fn2 raise */
       F11,  F12,  F13,  F14,  F15,MINS,  FN24,  F16,  F17,  F18,  F19,  F20,
      FN11, FN12, FN13, FN14, FN15,  NO,    NO, FN16, FN17, FN18, FN19, FN20,
       PWR, EJCT,   NO,   NO,   NO,  NO,    NO,   NO,   NO,   NO,   NO,   NO,
      CAPS, TRNS, TRNS, TRNS,  FN4, TRNS,        FN2,   NO,   NO,   NO,   NO),
/* Adjust (Lower + Raise or SLower + SRaise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | PWR  | EJCT |      |      |      |      |      | CAPS |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |DVORAK|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = KEYMAP( 
         NO, RESET, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO,
         PWR, EJCT, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO,
         CAPS,  NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO,
           NO,  NO, NO, NO, NO, NO,     NO, NO, NO, NO, NO),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_MOMENTARY(_LOWER),  // to Fn overlay LOWER
    [2] = ACTION_LAYER_MOMENTARY(_RAISE),  // to Fn overlay RAISE
    [3] = ACTION_DEFAULT_LAYER_SET(_DVRK), 
    [4] = ACTION_LAYER_MOMENTARY(_ADJUST),  // RAISE + LOWER
    [11] = ACTION_MODS_KEY(MOD_LSFT, KC_1),     //!
    [12] = ACTION_MODS_KEY(MOD_LSFT, KC_2),     //@
    [13] = ACTION_MODS_KEY(MOD_LSFT, KC_3),     //#
    [14] = ACTION_MODS_KEY(MOD_LSFT, KC_4),     //$
    [15] = ACTION_MODS_KEY(MOD_LSFT, KC_5),     //%
    [16] = ACTION_MODS_KEY(MOD_LSFT, KC_6),     //^
    [17] = ACTION_MODS_KEY(MOD_LSFT, KC_7),     //&
    [18] = ACTION_MODS_KEY(MOD_LSFT, KC_8),     //*
    [19] = ACTION_MODS_KEY(MOD_LSFT, KC_9),     //(
    [20] = ACTION_MODS_KEY(MOD_LSFT, KC_0),     //)
    [21] = ACTION_MODS_KEY(MOD_LSFT, KC_SLSH),  //?
    [22] = ACTION_MODS_KEY(MOD_LSFT, KC_EQL),   //+
    [23] = ACTION_MODS_KEY(MOD_LSFT, KC_GRV),   //~
    [24] = ACTION_MODS_KEY(MOD_LSFT, KC_MINS),  //_
    [25] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),  //|
    [26] = ACTION_MODS_KEY(MOD_LSFT, KC_LBRC),  //{
    [27] = ACTION_MODS_KEY(MOD_LSFT, KC_RBRC),  //}
    [28] = ACTION_MODS_KEY(MOD_LSFT | MOD_RSFT, KC_PAUSE),
};
