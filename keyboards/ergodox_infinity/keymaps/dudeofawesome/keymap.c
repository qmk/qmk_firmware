#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

enum custom_layers {
    _QWERTY,
    _DVORAK,
    _WORKMAN,
    _GAME,
    _MOUSE,
    _NUM,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    DVORAK,
    WORKMAN,
    LOWER,
    RAISE,
    GAME,
    MOUSE,
    NUM,
    EPRM,
    VRSN,
    RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic QWERTY layer
 *
 * ,---------------------------------------------.           ,---------------------------------------------.
 * |   -    |  1  |  2  |  3  |  4  |  5  | Esc  |           | Esc  |  6  |  7  |  8  |  9  |  0  |   =    |
 * |--------+-----+-----+-----+-----+------------|           |------+-----+-----+-----+-----+-----+--------|
 * |  Tab   |  Q  |  W  |  E  |  R  |  T  |  [{  |           |  ]}  |  Y  |  U  |  I  |  O  |  P  |  BSPC  |
 * |--------+-----+-----+-----+-----+-----|      |           |      |-----+-----+-----+-----+-----+--------|
 * |  ESC   |  A  |  S  |  D  |  F  |  G  |------|           |------|  H  |  J  |  K  |  L  |  ;  |   '"   |
 * |--------+-----+-----+-----+-----+-----|  L1  |           |  L1  |-----+-----+-----+-----+-----+--------|
 * | LShift |  Z  |  X  |  C  |  V  |  B  |      |           |      |  N  |  M  |  ,  |  .  |  /  | Enter  |
 * `--------+-----+-----+-----+-----+------------'           `------------+-----+-----+-----+-----+--------'
 *   | Num  |Ctrl | Alt |LGUI |Lower|                                     |Raise|Left |Down | Up  |Right |
 *   `------------------------------'                                     `------------------------------'
 *                                   ,------------.          ,------------.
 *                                   |Play |Mouse |          | Num  |Mouse|
 *                              ,----|-----|------|          |------+-----+-----.
 *                              |    |     | Alt  |          | Alt  |     |     |
 *                              |BSPC|LOWER|------|          |------|RAISE|Space|
 *                              |    |     | LGUI |          | LGUI |     |     |
 *                              `-----------------'          `------------------'
 */
[_QWERTY] = LAYOUT_ergodox(
  // left hand
  KC_MINUS, KC_1,    KC_2,    KC_3,    KC_4,  KC_5, KC_ESC,
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,  KC_T, KC_LBRACKET,
  KC_ESC,   KC_A,    KC_S,    KC_D,    KC_F,  KC_G,
  KC_LSPO,  KC_Z,    KC_X,    KC_C,    KC_V,  KC_B, KC_FN1,
  TG(_NUM), KC_LCTL, KC_LALT, KC_LGUI, LOWER,

                                                  KC_MPLY,   TG(_MOUSE),
                                                             KC_LALT,
                                          LOWER,  KC_BSPACE, KC_LGUI,

  // right hand
  KC_ESC,      KC_6, KC_7,  KC_8,    KC_9,    KC_0,                KC_EQUAL,
  KC_RBRACKET, KC_Y, KC_U,  KC_I,    KC_O,    KC_P,                KC_BSPACE,
               KC_H, KC_J,  KC_K,    KC_L,    KC_SCOLON,           KC_QUOTE,
  KC_FN1,      KC_N, KC_M,  KC_COMM, KC_DOT,  LT(_MOUSE, KC_SLSH), KC_ENTER,
                     RAISE, KC_LEFT, KC_DOWN, KC_UP,               KC_RIGHT,

  TG(_NUM), TG(_MOUSE),
  KC_LALT,
  KC_LGUI,  KC_SPACE,   RAISE
),

/* Keymap 0: Basic Dvorak layer
 *
 * ,---------------------------------------------.           ,--------------------------------------------.
 * |   -    |  1  |  2  |  3  |  4  |  5  | Esc  |           | Esc  |  6  |  7  |  8  |  9  |  0  |   =    |
 * |--------+-----+-----+-----+-----+------------|           |------+-----+-----+-----+-----+-----+--------|
 * |  Tab   |  '  |  ,  |  .  |  P  |  Y  |  [{  |           |  ]}  |  F  |  G  |  C  |  R  |  L  |  BSPC  |
 * |--------+-----+-----+-----+-----+-----|      |           |      |-----+-----+-----+-----+-----+--------|
 * |  ESC   |  A  |  O  |  E  |  U  |  I  |------|           |------|  D  |  H  |  T  |  N  |  S  |   /    |
 * |--------+-----+-----+-----+-----+-----|  L1  |           |  L1  |-----+-----+-----+-----+-----+--------|
 * | LShift |  ;  |  Q  |  J  |  K  |  X  |      |           |      |  B  |  M  |  W  |  V  |  Z  | Enter  |
 * `--------+-----+-----+-----+-----+------------'           `------------+-----+-----+-----+-----+--------'
 *   | Num  |Ctrl | Alt |LGUI |Lower|                                     |Raise|Left |Down | Up  |Right |
 *   `------------------------------'                                     `------------------------------'
 *                                   ,------------.          ,------------.
 *                                   |Play |Mouse |          | Num  |Mouse|
 *                              ,----|-----|------|          |------+-----+-----.
 *                              |    |     | Alt  |          | Alt  |     |     |
 *                              |BSPC|LOWER|------|          |------|RAISE|Space|
 *                              |    |     | LGUI |          | LGUI |     |     |
 *                              `-----------------'          `------------------'
 */
[_DVORAK] = LAYOUT_ergodox(
  // left hand
  KC_MINUS, KC_1,      KC_2,    KC_3,    KC_4,  KC_5, KC_ESC,
  KC_TAB,   KC_QUOT,   KC_COMM, KC_DOT,  KC_P,  KC_Y, KC_LBRACKET,
  KC_ESC,   KC_A,      KC_O,    KC_E,    KC_U,  KC_I,
  KC_LSPO,  KC_SCOLON, KC_Q,    KC_J,    KC_K,  KC_X, KC_FN1,
  TG(_NUM), KC_LCTL,   KC_LALT, KC_LGUI, LOWER,

                                                  KC_MPLY, TG(_MOUSE),
                                                           KC_LALT,
                                      KC_BSPACE,  LOWER,   KC_LGUI,

  // right hand
  KC_ESC,      KC_6, KC_7,  KC_8,    KC_9,    KC_0,  KC_EQUAL,
  KC_RBRACKET, KC_F, KC_G,  KC_C,    KC_R,    KC_L,  KC_BSPACE,
               KC_D, KC_H,  KC_T,    KC_N,    KC_S,  LT(MOUSE, KC_SLSH),
  KC_FN1,      KC_B, KC_M,  KC_W,    KC_V,    KC_Z,  KC_ENTER,
                     RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,

  TG(_NUM), TG(_MOUSE),
  KC_LALT,
  KC_LGUI,  RAISE,      KC_SPACE
),

/* Keymap 0: Basic Workman layer
 *
 * ,---------------------------------------------.           ,--------------------------------------------.
 * |   -    |  1  |  2  |  3  |  4  |  5  | Esc  |           | Esc  |  6  |  7  |  8  |  9  |  0  |   =    |
 * |--------+-----+-----+-----+-----+------------|           |------+-----+-----+-----+-----+-----+--------|
 * |  Tab   |  Q  |  D  |  R  |  W  |  B  |  [{  |           |  ]}  |  J  |  F  |  U  |  P  |  ;  |  BSPC  |
 * |--------+-----+-----+-----+-----+-----|      |           |      |-----+-----+-----+-----+-----+--------|
 * |  ESC   |  A  |  S  |  H  |  T  |  G  |------|           |------|  Y  |  N  |  E  |  O  |  I  |   '"   |
 * |--------+-----+-----+-----+-----+-----|  L1  |           |  L1  |-----+-----+-----+-----+-----+--------|
 * | LShift |  Z  |  X  |  M  |  C  |  V  |      |           |      |  K  |  L  |  ,  |  .  |  /  | Enter  |
 * `--------+-----+-----+-----+-----+------------'           `------------+-----+-----+-----+-----+--------'
 *   | Num  |Ctrl | Alt |LGUI |Lower|                                     |Raise|Left |Down | Up  |Right |
 *   `------------------------------'                                     `------------------------------'
 *                                   ,------------.          ,------------.
 *                                   |Play |Mouse |          | Num  |Mouse|
 *                              ,----|-----|------|          |------+-----+-----.
 *                              |    |     | Alt  |          | Alt  |     |     |
 *                              |BSPC|LOWER|------|          |------|RAISE|Space|
 *                              |    |     | LGUI |          | LGUI |     |     |
 *                              `-----------------'          `------------------'
 */
[_WORKMAN] = LAYOUT_ergodox(
  // left hand
  KC_MINUS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_ESC,
  KC_TAB,   KC_Q,    KC_D,    KC_R,    KC_W,    KC_B, KC_LBRACKET,
  KC_ESC,   KC_A,    KC_S,    KC_H,    KC_T,    KC_G,
  KC_LSPO,  KC_Z,    KC_X,    KC_M,    KC_C,    KC_V, KC_FN1,
  TG(_NUM), KC_LCTL, KC_LALT, KC_LGUI, LOWER,

                                                  KC_MPLY, TG(_MOUSE),
                                                            KC_LALT,
                                      KC_BSPACE,  LOWER,   KC_LGUI,

  // right hand
  KC_ESC,      KC_6, KC_7,  KC_8,    KC_9,    KC_0,                KC_EQUAL,
  KC_RBRACKET, KC_J, KC_F,  KC_U,    KC_P,    KC_SCOLON,           KC_BSPACE,
               KC_Y, KC_N,  KC_E,    KC_O,    KC_I,                KC_QUOTE,
  KC_FN1,      KC_K, KC_L,  KC_COMM, KC_DOT,  LT(_MOUSE, KC_SLSH), KC_ENTER,
                     RAISE, KC_LEFT, KC_DOWN, KC_UP,               KC_RIGHT,

  NUM,     TG(_MOUSE),
  KC_LALT,
  KC_LGUI, RAISE,      KC_SPACE
),

/* Lower
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * | Version |  F1  |  F2  |  F3  |  F4  |  F5  | F11  |           | F12  |  F6  |  F7  |  F8  |  F9  | F10  |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |    ~    |  !   |  @   |  #   |  $   |  %   |      |           |      |  ^   |  &   |  *   |  (   |  )   |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   Del   |  F1  |  F2  |  F3  |  F4  |  F5  |------|           |------|  F6  |  _   |  +   |  {   |  }   |   |    |
 * |---------+------+------+------+------+------|  L2  |           |  L2  |------+------+------+------+------+--------|
 * |         |  F7  |  F8  |  F9  | F10  | F11  |      |           |      | F12  |ISO ~ |ISO | | Home | End  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      | Next | Vol- | Vol+ | Play |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                       ,-------------.           ,-------------.
 *                                       |Animat|      |           |Toggle|Solid |
 *                                ,------|------|------|           |------+------+------.
 *                                |Bright|Bright|      |           |      |Hue-  |Hue+  |
 *                                |ness- |ness+ |------|           |------|      |      |
 *                                |      |      |      |           |      |      |      |
 *                                `--------------------'           `--------------------'
 */
[_LOWER] = LAYOUT_ergodox(
  // left hand
  VRSN,    KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F11,
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,   KC_PERC, _______,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  _______,
  _______, _______, _______, _______, _______,

                                       _______, _______,
                                                _______,
                              _______, _______, _______,

  // right hand
  KC_F12,  KC_F6,   KC_F7,      KC_F8,      KC_F9,   KC_F10,  KC_F11,
  _______, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, _______,
           KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
  _______, KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
                    _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY,

  _______, _______,
  _______,
  _______, _______, _______
),

/* Raise
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * | Version |  F1  |  F2  |  F3  |  F4  |  F5  | F11  |           | F12  |  F6  |  F7  |  F8  |  F9  | F10  |  F11   |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |    `    |  1   |  2   |  3   |  4   |  5   |      |           |      |  6   |  7   |  8   |  9   |  0   |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   Del   |  F1  |  F2  |  F3  |  F4  |  F5  |------|           |------|  F6  |  -   |  =   |  [   |  ]   |   \    |
 * |---------+------+------+------+------+------|  L2  |           |  L2  |------+------+------+------+------+--------|
 * |         |  F7  |  F8  |  F9  | F10  | F11  |      |           |      | F12  |ISO # |ISO / |Pg Up |Pg Dn |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      | Next | Vol- | Vol+ | Play |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                       ,-------------.           ,-------------.
 *                                       |Animat|      |           |Toggle|Solid |
 *                                ,------|------|------|           |------+------+------.
 *                                |Bright|Bright|      |           |      |Hue-  |Hue+  |
 *                                |ness- |ness+ |------|           |------|      |      |
 *                                |      |      |      |           |      |      |      |
 *                                `--------------------'           `--------------------'
 */
[_RAISE] = LAYOUT_ergodox(
  // left hand
  VRSN,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______,
  _______, _______, _______, _______, _______,

                                               _______, _______,
                                                        _______,
                                      _______, _______, _______,

  // right hand
  KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
           KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
                    _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,

  _______, _______,
  _______,
  _______, _______,  _______
),

/* Adjust
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |Version |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |Reset |Debug |      |      |      |      |           |      |      |TRM on|TRMoff|      |      |  Del   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |AG Nrm|------|           |------|AG Swp|QWERTY|Wrkman|Dvorak|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                      ,-------------.           ,-------------.
 *                                      |      |      |           |      |      |
 *                               ,------|------|------|           |------+------+------.
 *                               |      |      |      |           |      |      |      |
 *                               |      |      |------|           |------|      |      |
 *                               |      |      |      |           |      |      |      |
 *                               `--------------------'           `--------------------'
 */
[_ADJUST] = LAYOUT_ergodox(
  // left hand
  VRSN,    _______, _______, _______, _______, _______, _______,
  _______, RESET,   DEBUG,   _______, _______, _______, _______,
  _______, _______, _______, _______, _______, AG_NORM,
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,

                                               _______, _______,
                                                        _______,
                                      _______, _______, _______,

  // right hand
  _______, _______, _______, _______,  _______, _______, _______,
  _______, _______, TERM_ON, TERM_OFF, _______, _______, KC_DEL,
           AG_SWAP, QWERTY,  WORKMAN,  DVORAK,  _______, _______,
  _______, _______, _______, _______,  _______, _______, _______,
                    _______, _______,  _______, _______, _______,

  _______, _______,
  _______,
  _______, _______,  _______
),

/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | Lclk | MsUp | Rclk |Wh Up |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|Wh Dn |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                      ,-------------.           ,-------------.
 *                                      |      |      |           |      |      |
 *                               ,------|------|------|           |------+------+------.
 *                               |      |      |      |           |      |Brwser|Brwser|
 *                               | Lclk | Rclk |------|           |------|Back  |Fwd   |
 *                               |      |      |      |           |      |      |      |
 *                               `--------------------'           `--------------------'
 */
// MOUSE
[_MOUSE] = LAYOUT_ergodox(
  // left hand
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_D, _______,
  _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,
  _______, _______, KC_WH_L, KC_BTN3, KC_WH_R, _______, TO(_GAME),
  _______, _______, _______, _______, _______,

                                       _______, _______,
                                                KC_WH_D,
                              KC_BTN1, KC_BTN2, KC_WH_U,

  // right hand
  _______,   _______, _______, _______, _______, _______, _______,
  _______,   _______, _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______, KC_MPLY,
  TO(_GAME), _______, _______, KC_MPRV, KC_MNXT, _______, _______,
                      KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,

  _______, _______,
  _______,
  _______, KC_WBAK, KC_WFWD
),

/* Keymap 2: GAME
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | Lclk | MsUp | Rclk |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                      ,-------------.           ,-------------.
 *                                      |      |      |           |      |      |
 *                               ,------|------|------|           |------+------+------.
 *                               |      |      |      |           |      |Brwser|Brwser|
 *                               | Lclk | Rclk |------|           |------|Back  |Fwd   |
 *                               |      |      |      |           |      |      |      |
 *                               `--------------------'           `--------------------'
 */
[_GAME] = LAYOUT_ergodox(
  // left hand
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,

                                                  _______, _______,
                                                           _______,
                                        KC_SPACE, KC_LGUI, KC_LALT,

  // right hand
  _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______,

  TG(_MOUSE), TG(_NUM),
  _______,
  _______,    _______,  _______
),


/* Keymap 2: NUMPAD
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  | F11  |           | F12  |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |  !   |  @   |  {   |  }   |  |   |      |           |      |      |  7   |  8   |  9   |  *   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |------|           |------|      |  4   |  5   |  6   |  +   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |      |           |      |      |  1   |  2   |  3   |  \   |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |  .   |  0   |  0   |  =   |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                      ,-------------.           ,-------------.
 *                                      |      |      |           |      |      |
 *                               ,------|------|------|           |------+------+------.
 *                               |      |      |      |           |      |      |      |
 *                               |      |      |------|           |------|      |      |
 *                               |      |      |      |           |      |      |      |
 *                               `--------------------'           `--------------------'
 */
[_NUM] = LAYOUT_ergodox(
  // left hand
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,
  _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, _______,
  _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,
  _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______,
  _______, _______, _______, _______, _______,

                                               _______, _______,
                                                        _______,
                                      _______, _______, _______,

  // right hand
  KC_F12,  KC_F6,   KC_F7,     KC_F8,   KC_F9,   KC_F10,         KC_F11,
  _______, _______, KC_KP_7,   KC_KP_8, KC_KP_9, KC_KP_ASTERISK, _______,
           _______, KC_KP_4,   KC_KP_5, KC_KP_6, KC_KP_PLUS,     _______,
  _______, _______, KC_KP_1,   KC_KP_2, KC_KP_3, KC_KP_SLASH,    _______,
                    KC_KP_DOT, KC_KP_0, KC_KP_0, KC_KP_EQUAL,    _______,

  _______, _______,
  _______,
  _______, _______,  _______
),

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
    if (record->event.pressed) {
      SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
    }
    break;
    case 1:
    if (record->event.pressed) { // For resetting EEPROM
      eeconfig_init();
    }
    break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case WORKMAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (IS_LAYER_ON(_ADJUST)) {
          layer_off(_LOWER);
          layer_off(_RAISE);
        }
      } else {
        layer_off(_LOWER);
        if (IS_LAYER_ON(_ADJUST)) {
          layer_off(_ADJUST);
          layer_on(_RAISE);
        }
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (IS_LAYER_ON(_ADJUST)) {
          layer_off(_RAISE);
          layer_off(_LOWER);
        }
      } else {
        layer_off(_RAISE);
        if (IS_LAYER_ON(_ADJUST)) {
          layer_off(_ADJUST);
          layer_on(_LOWER);
        }
      }
      return false;
      break;
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
        rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

/**
 * Runs just one time when the keyboard initializes.
 */
void matrix_init_user(void) {

};

/**
 * Runs constantly in the background, in a loop.
 */
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  switch (layer) {
    case _LOWER:
      ergodox_right_led_1_on();
      break;
    case _RAISE:
      ergodox_right_led_2_on();
      break;
    case _ADJUST:
      ergodox_right_led_3_on();
      break;
  }
};
