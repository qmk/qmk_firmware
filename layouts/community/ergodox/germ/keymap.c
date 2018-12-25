/* Good on you for modifying your layout! if you don't have 
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#define IGNORE_MOD_TAP_INTERRUPT
#define BASE 0 // default layer
#define SYMB 1 // symbols
#define NUMB 2 // numbers/motion

// Blank template at the bottom
/*  ---------- LEFT HAND -----------   ---------- RIGHT HAND ---------- */
#define LAYOUT_GERGO(                                                    \
    L00,L01,L02,L03,L04,L05,                   R00,R01,R02,R03,R04,R05,  \
    L10,L11,L12,L13,L14,L15,L16,           R10,R11,R12,R13,R14,R15,R16,  \
    L20,L21,L22,L23,L24,L25,L26,           R20,R21,R22,R23,R24,R25,R26,  \
                L31,L32,                           R33,R34,              \
                            L30,           R30,                          \
                        L33,L34,           R31,R32)                      \
                                                                         \
   /* matrix positions */                                                \
    {                               \
    { KC_NO, L16,   L26,  L30},     \
    { L05,   L15,   L25,  L34},     \
    { L04,   L14,   L24,  L33},     \
    { L03,   L13,   L23,  L32},     \
    { L02,   L12,   L22,  L31},     \
    { L01,   L11,   L21,  KC_NO},   \
    { L00,   L10,   L20,  KC_NO},   \
                                    \
    { R10,   KC_NO, R20, R30},      \
    { R00,   R11,   R21, R31},      \
    { R01,   R12,   R22, R32},      \
    { R02,   R13,   R23, R33},      \
    { R03,   R14,   R24, R34},      \
    { R04,   R15,   R25, KC_NO},    \
    { R05,   R16,   R26, KC_NO},    \
}

enum customKeycodes {
	URL  = 1
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * | L1/ESC |   Q  |   W  |   E  |   R  |   T  |                         |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |Ctrl/BS |   A  |   S  |  D   |   F  |   G  | RMB  |           |      |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | LMB  |           |      |   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                    .----------.   .-------.                                 .------.   .-----.
 *                    | Super/Del|   |Ent/ALT|                                 | Tab  |   |BKSP |
 *                    '----------'   '-------'                                 `------.   '-----'
 *                                        ,-------.                      ,-------.
 *                                        | MMB   |                      | PgUp  |
 *                                 ,------|-------|                      |-------|------.
 *                                 | SYMB | NUMB  |                      | SYMB  | NUMB |
 *                                 | Space| Escape|                      | Mod   |Space |
 *                                 |      |       |                      |       |      |
 *                                 `--------------'                      `--------------'
 */
[BASE] = LAYOUT_GERGO(  
LT(NUMB, KC_ESC),          KC_Q,  KC_W,   KC_E,   KC_R, KC_T,                       KC_Y,    KC_U, KC_I, KC_O,   KC_P,    KC_PIPE, 
MT(MOD_LCTL, KC_BSPC),  KC_A,  KC_S,   KC_D,   KC_F, KC_G, KC_BTN2,       KC_TRNS,  KC_H,    KC_J, KC_K, KC_L,   KC_SCLN, KC_QUOT, 
KC_RSFT,                KC_Z,  KC_X,   KC_C,   KC_V, KC_B, KC_BTN1,       KC_BSPC,  KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS, 
                                      
			              MT(MOD_LGUI, KC_DEL), MT(MOD_LALT, KC_ENT),       KC_TAB, KC_BSPC,

                                                           KC_BTN3,       KC_PGUP,
                                LT(SYMB, KC_SPC), LT(NUMB, KC_ESC),       LT(SYMB, KC_ENT), LT(NUMB, KC_SPC)),
/* Keymap 1: Symbols layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                         |      |      |      |      |      |  \ |   |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |      |           |      |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |      |           |      |   &  |  =   |  ,   |  .   |  / ? | - _    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   | DEL |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.                     ,-------.
 *                                        |       |                     | PgDn  |
 *                                 ,------|-------|                     |-------|------.
 *                                 |      |       |                     |       |      |
 *                                 |   ;  |   =   |                     |   =   |   ;  |
 *                                 |      |       |                     |       |      |
 *                                 `--------------'                     `--------------'
 */
[SYMB] = LAYOUT_GERGO(  
KC_TRNS, KC_EXLM, KC_AT,  KC_LCBR,KC_RCBR, KC_PIPE,                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, 
KC_TRNS, KC_HASH, KC_DLR, KC_LPRN,KC_RPRN, KC_GRV,  KC_TRNS,       KC_TRNS,  KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT, 
KC_TRNS, KC_PERC, KC_CIRC,KC_LBRC,KC_RBRC, KC_TILD, KC_TRNS,       KC_TRNS,  KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS, 

                                                  KC_TRNS, KC_TRNS,       KC_PGDN, KC_DEL,
                                                           KC_TRNS,       KC_TRNS,
                                             	  KC_SCLN, KC_EQL,        KC_EQL, KC_SCLN),
/* Keymap 2: Pad/Function layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                         |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |  F1    |  F2  | F3   | F4   | F5   | F6   | BTN1 |           | LEFT | DOWN |  UP  | RIGHT|      |VolDn | VolUp  |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |  F7    |  F8  | F9   | F10  | F11  | F12  | BTN2 |           | MLFT | MDWN | MUP  | MRGHT|      |Ply/Pa|  Skip  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.                     ,-------.
 *                                        |       |                     | PgUp  |
 *                                 ,------|-------|                     |-------|------.
 *                                 |      |       |                     |       |      |
 *                                 |      |       |                     |       |      |
 *                                 |      |       |                     |       |      |
 *                                 `--------------'                     `--------------'
 */
[NUMB] = LAYOUT_GERGO(  
KC_TRNS, KC_1, 	  KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS, 
KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_TRNS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLD, KC_VOLU, 
KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,        KC_TRNS,  KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_MPLY, KC_MNXT, 

                                                  KC_TRNS, KC_TRNS,       KC_PGUP, KC_TRNS,
                                                           KC_TRNS,       KC_TRNS,
                                             	  KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS)
};

const uint16_t PROGMEM fn_actions[] = {
    //[1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
    if (record->event.pressed) {
      register_code(KC_RSFT);
    } else {
      unregister_code(KC_RSFT);
    }
    break;
  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    //uint8_t layer = biton32(layer_state);
    biton32(layer_state);
};


/* Keymap template 
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |      |      |      |      |      |                         |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.       ,-------.
 *                                        |       |       |       |
 *                                 ,------|-------|       |-------|------.
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 `--------------'       `--------------'
[SYMB] = LAYOUT_GERGO(  
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, 

                                                  KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS,
                                                           KC_TRNS,       KC_TRNS,
                                             	  KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS),
 */
