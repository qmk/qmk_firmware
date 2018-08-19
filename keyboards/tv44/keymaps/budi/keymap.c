#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DV 0
#define _NM 1
#define _NV 2
#define _MN 3
#define _FN 4

// Requires KC_TRNS/_______ for the trigger key in the destination layer
#define NM_SP   LT(_NM, KC_SPC)
#define NV_SP   LT(_NV, KC_SPC)
#define MN_EN   LT(_MN, KC_ENT)
#define FN_EX   LT(_FN, KC_ESC)

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

// MEH
#define MEH0  MEH(KC_0)
#define MEH1  MEH(KC_1)
#define MEH2  MEH(KC_2)
#define MEH3  MEH(KC_3)
#define MEH4  MEH(KC_4)
#define MEH5  MEH(KC_5)
#define MEH6  MEH(KC_6)
#define MEH7  MEH(KC_7)
#define MEH8  MEH(KC_8)
#define MEH9  MEH(KC_9)

// CAG
#define CAG0  LCAG(KC_0)
#define CAG1  LCAG(KC_1)
#define CAG2  LCAG(KC_2)
#define CAG3  LCAG(KC_3)
#define CAG4  LCAG(KC_4)
#define CAG5  LCAG(KC_5)
#define CAG6  LCAG(KC_6)
#define CAG7  LCAG(KC_7)
#define CAG8  LCAG(KC_8)
#define CAG9  LCAG(KC_9)

// ALTS
#define ALT0   LALT(KC_0)
#define ALT1   LALT(KC_1)
#define ALT2   LALT(KC_2)
#define ALT3   LALT(KC_3)
#define ALT4   LALT(KC_4)
#define ALT5   LALT(KC_5)
#define ALT6   LALT(KC_6)
#define ALT7   LALT(KC_7)
#define ALT8   LALT(KC_8)
#define ALT9   LALT(KC_9)
#define ALTX   LALT(KC_GRV)
#define ALTL   LALT(KC_LEFT)
#define ALTR   LALT(KC_RIGHT)
#define ALTESC LALT(KC_ESC)
#define ALTEQL LALT(KC_EQL)
#define ALTMIN LALT(KC_MINS)

// BACK AND FORWARD
#define XBACK  LGUI(LALT(KC_LEFT))
#define XFFWD  LGUI(LALT(KC_RIGHT))

// Fillers to make layering more clear
#define _______ KC_TRNS
#define xxxxxxx KC_NO

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  SWTCH
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* DVORAK
 * ,---------+------+------+------+------+------+------+------+------+------+------+------------.
 * |  TAB    |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  BACKSPACE |
 * |---------`------`------`------`------`------`------`------`------`------`------`------------|
 * |  LCTL    |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  MN/ENTER |
 * |----------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |  LSHFT    |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z   |   RSHFT |
 * |-----------`------`------`------`------`------`-------`------`------`------`------`---------|
 * |  FN EX   |   GUI    |    ALT   |  NM / SPACE  | NV / SPACE |  RALT |   -   |   =   |  ESC  |
 *  `---------+----------+----------+-----^^^------+----^^^-----+-------+-------+-------+-------'
 */
  [_DV] = LAYOUT_arrow(
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
    KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    MN_EN,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
    FN_EX,   KC_LGUI, KC_LALT,                   NM_SP,   NV_SP,            KC_RALT, KC_MINS, KC_EQL,  KC_ESC
   ),



/* NUMBERS
 * ,---------+------+------+------+------+------+------+------+------+------+------+------------.
 * |   ESC   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |     DELETE |
 * |---------`------`------`------`------`------`------`------`------`------`------`------------|
 * |   LCTL   |   !  |   @  |   [  |   {  |  (   |  )   |   }  |   ]  |   | |   ?  |     ENTER  |
 * |----------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |   LSFT    |   `  |  ~   |  #   |   $  |   %  |   ^  |   &  |   *  |   _  |   +   |     =   |
 * |   LSFT    |   `  |  ~   |  #   |   $  |   %  |   ^  |   &  |   *  |   _  |   +   |     /   |
 * |-----------`------`------`------`------`------`-------`------`------`------`------`---------|
 * |          |    GUI   |   LALT   |-----TRNS-----|   SPACE    |  RALT |   -   |   =   |   \   |
 * |-----------`------`------`------`------`------`-------`------`------`------`------`---------|
 */
  [_NM] = LAYOUT_arrow(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    _______, KC_EXLM, KC_AT,   KC_LBRC, L_CURB,  KC_LPRN, KC_RPRN, R_CURB,  KC_RBRC, KC_PIPE, KC_QUES, _______,
    _______, KC_GRV,  KC_TILD, KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_PLUS, KC_SLSH,
    _______, _______, _______,                   _______, KC_SPC,           _______, KC_MINS, KC_EQL,  KC_BSLS
  ),



/* NAVIGATION
 * ,---------+------+------+------+------+------+------+------+------+------+------+------------.
 * |   ESC   |  MWU |  MWL |  MU  |  MWR | MPRV | MNXT | HOME |  UP  |  END | PGUP |    DELETE  |
 * |---------`------`------`------`------`------`------`------`------`------`------`------------|
 * |   LCTL   |  MWD |  ML  |  MD  |  MR  | MRWD | MFFD | LEFT | DOWN | RIGHT| PGDN |      MB2  |
 * |----------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |   LSFT    | HYP1 | HYP2 | HYP3 | HYP4 | HYP5 | HYP6 | HYP7 | HYP8 | HYP9 |  HYP0 |  VOLUP  |
 * |-----------`------`------`------`------`------`-------`------`------`------`------`---------|
 * |          |    GUI   |   LALT   |     MB1      |----TRNS----|  MUTE | PLAY  |  STOP | VOLDN |
 *  `---------+----------+----------+-----^^^------+----^^^-----+-------+-------+-------+-------'
 */
  [_NV] = LAYOUT_arrow(
    KC_ESC,  KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, KC_MPRV, KC_MNXT, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_DEL,
    _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_MRWD, KC_MFFD, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_BTN2,
    _______, HYP1,    HYP2,    HYP3,    HYP4,    HYP5,    HYP6,    HYP7,    HYP8,    HYP9,    HYP0,    KC_VOLU,
    _______, _______, _______,                   KC_BTN1, _______,          KC_MUTE, KC_MPLY, KC_MSTP, KC_VOLD
  ),



/* MODIFIED NUMBERS
 * ,---------+------+------+------+------+------+------+------+------+------+------+------------.
 * |  ALTESC | CAG1 | CAG2 | CAG3 | CAG4 | CAG5 | CAG6 | CAG7 | CAG8 | CAG9 | CAG0 |     SWTCH  |
 * |---------`------`------`------`------`------`------`------`------`------`------`------------|
 * |  ALT `   | ALT1 | ALT2 | ALT3 | ALT4 | ALT5 | ALT6 | ALT7 | ALT8 | ALT9 | ALT0 |----TRNS---|
 * |----------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |  ALT =    | MEH1 | MEH2 | MEH3 | MEH4 | MEH5 | MEH6 | MEH7 | MEH8 | MEH9 |  MEH0 |         |
 * |-----------`------`------`------`------`------`-------`------`------`------`------`---------|
 * |  ALT -   |          |   XBACK  |   ALT LEFT   |  ALT RIGHT | XFFWD |       |       |       |
 *  `---------+----------+----------+-----^^^------+----^^^-----+-------+-------+-------+-------'
 */
  [_MN] = LAYOUT_arrow(
    ALTESC,  CAG1,    CAG2,    CAG3,    CAG4,    CAG5,    CAG6,    CAG7,    CAG8,    CAG9,    CAG0,    SWTCH,
    ALTX,    ALT1,    ALT2,    ALT3,    ALT4,    ALT5,    ALT6,    ALT7,    ALT8,    ALT9,    ALT0,    _______,
    ALTEQL,  MEH1,    MEH2,    MEH3,    MEH4,    MEH5,    MEH6,    MEH7,    MEH8,    MEH9,    MEH0,    xxxxxxx,
    ALTMIN,  xxxxxxx, XBACK,                     ALTL,    ALTR,             XFFWD,   xxxxxxx, xxxxxxx, xxxxxxx
  ),



/* FUNCTIONS
 * ,---------+------+------+------+------+------+------+------+------+------+------+------------.
 * |   ESC   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  |    DELETE  |
 * |---------`------`------`------`------`------`------`------`------`------`------`------------|
 * |   LCTL   |  F11 |  F12 |  F13 |  F14 |  F15 |  F16 |  F17 |  F18 |  F19 |  F20 |           |
 * |----------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |   LSFT    |      |      |      |      |      |      |      |      |      |       |         |
 * |-----------`------`------`------`------`------`-------`------`------`------`------`---------|
 * |---TRNS---|   CAPS   |   LALT   |              |   SWTCH    |  RALT |       | RESET |--TRNS-|
 *  `---------+----------+----------+-----^^^------+----^^^-----+-------+-------+-------+-------'
 */
  [_FN] = LAYOUT_arrow(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
    _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  xxxxxxx,
    _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, KC_PWR,  KC_SLEP, KC_WAKE, xxxxxxx, xxxxxxx, xxxxxxx,
    _______, KC_CAPS, _______,                   xxxxxxx, SWTCH,            KC_RALT, xxxxxxx, RESET,   _______
  )



/* Transparent placeholder for more layers
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
//  [_TR] = LAYOUT_arrow(
//    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//    _______, _______, _______,                   _______, _______,          _______, _______, _______, _______
//  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case SWTCH:
        SEND_STRING(SS_DOWN(X_LGUI));
        SEND_STRING(SS_DOWN(X_LSHIFT));
        SEND_STRING(SS_TAP(X_ENTER));
        SEND_STRING(SS_UP(X_LSHIFT));
        SEND_STRING(SS_UP(X_LGUI));
        return false;
    }
  }
  return true;
}
