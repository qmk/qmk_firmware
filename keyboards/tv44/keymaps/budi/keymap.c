#include "tv44.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "timer.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DV 0
#define _NM 1
#define _NV 2
#define _G1 3
#define _G2 4
#define _FN 5

// Requires KC_TRNS/_______ for the trigger key in the destination layer
#define NM_SP   LT(_NM, KC_SPC)
#define NV_SP   LT(_NV, KC_SPC)

// Custom macros
#define LC_ESC  LCTL_T(KC_ESC)      // Tap for Esc, Hold for L-CTRL
#define RC_ENT  RCTL_T(KC_ENT)      // Tap for Enter, Hold for R-CTRL

// Curly braces have their own keys. These are defined to make them not mess up
// the grid in layer 2.
#define L_CURB  LSFT(KC_LBRC)
#define R_CURB  LSFT(KC_RBRC)

// Hypers
#define HYP0  HYPR(KC_0)
#define HYP1  HYPR(KC_1)
#define HYP2  HYPR(KC_2)
#define HYP3  HYPR(KC_3)
#define HYP4  HYPR(KC_4)
#define HYP5  HYPR(KC_5)
#define HYP6  HYPR(KC_6)
#define HYP7  HYPR(KC_7)
#define HYP8  HYPR(KC_8)
#define HYP9  HYPR(KC_9)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define xxxxxxx KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* DVORAK
 * ,---------+------+------+------+------+------+------+------+------+------+------+------------.
 * |  TAB    |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  BACKSPACE |
 * |---------`------`------`------`------`------`------`------`------`------`------`------------|
 * |  LCTL    |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |     ENTER |
 * |----------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |  LSHFT    |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z   |   RSHFT |
 * |-----------`------`------`------`------`------`-------`------`------`------`------`---------|
 * |  MO FN   |   GUI    |    ALT   |  NM / SPACE  | NV / SPACE |  RALT |   /   |   \   |  ESC  |
 *  `---------+----------+----------+-----^^^------+----^^^-----+-------+-------+-------+-------'
 */
  [_DV] = KEYMAP_ARROW(
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
    KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
    MO(_FN), KC_LGUI, KC_LALT,                   NM_SP,   NV_SP,            KC_RALT, KC_SLSH, KC_BSLS, KC_ESC
   ),



/* NUMBERS
 * ,---------+------+------+------+------+------+------+------+------+------+------+------------.
 * |   ESC   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |     DELETE |
 * |---------`------`------`------`------`------`------`------`------`------`------`------------|
 * |   LCTL   |   !  |   @  |   [  |   {  |  (   |  )   |   }  |   ]  |   ?  |   |  |     ENTER |
 * |----------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |   LSFT    |   `  |  ~   |  #   |   $  |   %  |   ^  |   &  |   *  |   _  |   =   |     +   |
 * |-----------`------`------`------`------`------`-------`------`------`------`------`---------|
 * |          |    GUI   |   LALT   |-----TRNS-----|   SPACE    |  RALT |   /   |   \   |   -   |
 *  `---------+----------+----------+-----^^^------+----^^^-----+-------+-------+-------+-------'
 */
  [_NM] = KEYMAP_ARROW(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    _______, KC_EXLM, KC_AT,   KC_LBRC, L_CURB,  KC_LPRN, KC_RPRN, R_CURB,  KC_RBRC, KC_QUES, KC_PIPE, _______,
    _______, KC_GRV,  KC_TILD, KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_EQL,  KC_PLUS,
    _______, _______, _______,                   _______, _______,          _______, KC_SLSH, KC_BSLS, KC_MINS
  ),



/* NAVIGATION
 * ,---------+------+------+------+------+------+------+------+------+------+------+------------.
 * |   ESC   |  MWU |  MWL |  MU  |  MWR |      |      | HOME |  UP  |  END | PGUP |    DELETE  |
 * |---------`------`------`------`------`------`------`------`------`------`------`------------|
 * |   LCTL   |  MWD |  ML  |  MD  |  MR  |      |      | LEFT | DOWN | RIGHT| PGDN |      MB2  |
 * |----------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |   LSFT    | HYP1 | HYP2 | HYP3 | HYP4 | HYP5 | HYP6 | HYP7 | HYP8 | HYP9 |  HYP0 |  VOLUP  |
 * |-----------`------`------`------`------`------`-------`------`------`------`------`---------|
 * |          |    GUI   |   LALT   |     MB1      |----TRNS----|  MUTE | PLAY  |  STOP | VOLDN |
 *  `---------+----------+----------+-----^^^------+----^^^-----+-------+-------+-------+-------'
 */
  [_NV] = KEYMAP_ARROW(
    KC_ESC,  KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, xxxxxxx, xxxxxxx, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_DEL,
    _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, xxxxxxx, xxxxxxx, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_BTN2,
    _______, HYP1,    HYP2,    HYP3,    HYP4,    HYP5,    HYP6,    HYP7,    HYP8,    HYP9,    HYP0,    KC_VOLU,
    _______, _______, _______,                   KC_BTN1, _______,          KC_MUTE, KC_MPLY, KC_MSTP, KC_VOLD
  ),



/* GAME 1
 * ,---------+------+------+------+------+------+------+------+------+------+------+------------.
 * |  TAB    |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | BACKSPACE  |
 * |---------`------`------`------`------`------`------`------`------`------`------`------------|
 * |  LCTL    |  A   |  O   |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |    ENTER  |
 * |----------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |  LSFT     |  ;   |   Q  |   J  |   K  |   X  |   B  |   M  |   W   |   V  |   Z  |   RSFT  |
 * |-----------`------`------`------`------`------`-------`------`------`------`------`---------|
 * |     -    |    =     |   LALT   |    MO G2     |   SPACE    |  RALT |       |       | MO FN |
 *  `---------+----------+----------+-----^^^------+----^^^-----+-------+-------+-------+-------'
 */
  [_G1] = KEYMAP_ARROW(
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
    _______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT,
    _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
    KC_MINS, KC_EQL,  _______,                   MO(_G2), KC_SPC,           KC_RALT, xxxxxxx, xxxxxxx, MO(_FN)
  ),



/* GAME 2
 * ,---------+------+------+------+------+------+------+------+------+------+------+------------.
 * |  ESC    |   1  |   2  |   3  |   4  |   5  |  F1  |  F2  |  F3  |  F4  |  F5  |    DELETE  |
 * |---------`------`------`------`------`------`------`------`------`------`------`------------|
 * |  LCTL    |   6  |   7  |   8  |   9  |   0  |  F6  |  F7  |  F8  |  F9  | F10  |    ENTER  |
 * |----------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |  LSFT     |  `   |   /  |   [  |   ]  |   \  |  F11  | F12  | F13  |  F14 |  F15 |   RSFT  |
 * |-----------`------`------`------`------`------`-------`------`------`------`------`---------|
 * |  MB 3    |   MB 4   |   LALT   |----TRNS------|   SPACE    |  MB5  |       |       | MO FN |
 *  `---------+----------+----------+-----^^^------+----^^^-----+-------+-------+-------+-------'
 */
  [_G2] = KEYMAP_ARROW(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_DEL,
    _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
    _______, KC_GRV,  KC_SLSH, KC_LBRC, KC_RBRC, KC_BSLS, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  _______,
    KC_BTN3, KC_BTN4, _______,                   _______, _______,          KC_BTN5, xxxxxxx, xxxxxxx, _______
  ),



/* FUNCTIONS
 * ,---------+------+------+------+------+------+------+------+------+------+------+------------.
 * |   ESC   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  |    DELETE  |
 * |---------`------`------`------`------`------`------`------`------`------`------`------------|
 * |   LCTL   |  F11 |  F12 |  F13 |  F14 |  F15 |  F16 |  F17 |  F18 |  F19 |  F20 |           |
 * |----------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |   LSFT    |  _DV |  _G1 |      |      |      |      |      |      |      |       |         |
 * |-----------`------`------`------`------`------`-------`------`------`------`------`---------|
 * |---TRNS---|   CAPS   |   LALT   |              |            |  RALT |       | RESET |--TRNS-|
 *  `---------+----------+----------+-----^^^------+----^^^-----+-------+-------+-------+-------'
 */
  [_FN] = KEYMAP_ARROW(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
    _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  xxxxxxx,
    _______, TO(_DV), TO(_G1), xxxxxxx, xxxxxxx, xxxxxxx, KC_PWR,  KC_SLEP, KC_WAKE, xxxxxxx, xxxxxxx, xxxxxxx,
    _______, KC_CAPS, _______,                   xxxxxxx, xxxxxxx,          KC_RALT, xxxxxxx, RESET,   _______
  )



/* Transparent
 * ,---------+------+------+------+------+------+------+------+------+------+------+------------.
 * |         |      |      |      |      |      |      |      |      |      |      |            |
 * |---------`------`------`------`------`------`------`------`------`------`------`------------|
 * |          |      |      |      |      |      |      |      |      |      |      |           |
 * |----------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |           |      |      |      |      |      |      |      |      |      |       |         |
 * |-----------`------`------`------`------`------`-------`------`------`------`------`---------|
 * |          |          |          |              |            |       |       |       |       |
 *  `---------+----------+----------+-----^^^------+----^^^-----+-------+-------+-------+-------'
 */
//  [_TR] = KEYMAP_ARROW(
//    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//    _______, _______, _______,                   _______, _______,          _______, _______, _______, _______
//  )



};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
