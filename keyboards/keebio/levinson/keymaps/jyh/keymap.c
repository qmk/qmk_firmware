#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3																/* Symbols, Media */
#define _RAISE 4																/* Numbers, Arrows */
#define _FUNC  5																/* Function Keys */
#define _NUMS  6																/* Numpad */
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// tap toggle numpad on
#define NUMPAD TT(_NUMS)

// Mod Tap Definitions
// -------------------
                                      //  Tap     Hold
                                      //  ------------------
#define CTL_ESC MT(MOD_LCTL, KC_ESC)  //  Esc     Left Control
#define SFT_ENT MT(MOD_RSFT, KC_ENT)  //  Enter   Right Shift
#define CTL_SPC MT(MOD_LCTL, KC_SPC)  //  Space   Left Control
#define ALT_SPC MT(MOD_LALT, KC_SPC)  //  Space   Left Alt
#define ALT_BSP MT(MOD_LALT, KC_BSPC) //  Bkspace Left Alt
#define HPR_TAB MT(MOD_HYPR, KC_TAB)  //  Tab     Hyper (Super+Ctrl+Alt+Shift)
#define HPR_GRV MT(MOD_HYPR, KC_GRV)  //  `       Hyper
#define HPR_TIL MT(MOD_HYPR, KC_TILD) //  ~       Hyper
#define MEH_TIL MT(MOD_MEH,  KC_GRV)  //  `       Meh (Ctrl+Alt+Shift)
#define SFT_MIN MT(MOD_LSFT, KC_MINS) //  -       Left Shift
#define NPD_UND LT(_NUMS,    KC_UNDS) //  _       Layer Numpad
#define FNC_PIP LT(_FUNC,    KC_PIPE) //  |       Layer Function Keys

#define CTL_DEL MT(MOD_LCTL, KC_DEL)  //  Del     Left Control
#define CTL_QOT MT(MOD_RCTL, KC_QUOT) //  '       Right Control
#define CTL_BSL MT(MOD_RCTL, KC_BSLS) //  \       Right Control
#define CTL_PIP MT(MOD_RCTL, KC_PIPE) //  |       Right Control


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,-----------------------------------------.    ,-----------------------------------------.
 * | Tab  |  Q   |  W   |  E   |  R   |  T   |    |  Y   |  U   |  I   |  O   |  P   | Bksp |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Esc  |  A   |  S   |  D   |  F   |  G   |    |  H   |  J   |  K   |  L   |  ;   |  '   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |  -   |  Z   |  X   |  C   |  V   |  B   |    |  N   |  M   |  ,   |  .   |  /   | Enter|
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Numpd| Meh  | Meta | Alt  | Lower| Space|    | Space| Raise| Alt  | Meta | Hyper| Func |
 * `-----------------------------------------'    `-----------------------------------------'
 *
 * with Hold (Emacs-oriented)
 * ,-----------------------------------------.    ,-----------------------------------------.
 * | Hyper|      |      |      |      |      |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Ctrl |      |      |      |      |      |    |      |      |      |      |      | Ctrl |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |    |      |      |      |      |      | Shift|
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * `-----------------------------------------'    `-----------------------------------------'
 */
    [_QWERTY] = LAYOUT_ortho_4x12(
        HPR_TAB, KC_Q   , KC_W   , KC_E   , KC_R , KC_T   ,    KC_Y   , KC_U , KC_I   , KC_O   , KC_P   , KC_BSPC,
        CTL_ESC, KC_A   , KC_S   , KC_D   , KC_F , KC_G   ,    KC_H   , KC_J , KC_K   , KC_L   , KC_SCLN, CTL_QOT,
        SFT_MIN, KC_Z   , KC_X   , KC_C   , KC_V , KC_B   ,    KC_N   , KC_M , KC_COMM, KC_DOT , KC_SLSH, SFT_ENT,
        NUMPAD , KC_MEH , KC_LGUI, KC_LALT, LOWER, CTL_SPC,    KC_SPC, RAISE, KC_RALT, KC_RGUI, KC_HYPR, MO(_FUNC)
        ),


/* Raise
 * ,-----------------------------------------.    ,-----------------------------------------.
 * |  `   |  1   |  2   |  3   |  4   |  5   |    |  6   |  7   |  8   |  9   |  0   |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      | Left |  Up  | Down | Right|  (   |    |  )   |  -   |  =   |  [   |  ]   |  |   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |  ;   |  '   |  *   |  ,   |  {   |    |  }   |  _   |  +   |  .   |  /   |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * `-----------------------------------------'    `-----------------------------------------'
 */
    [_RAISE] = LAYOUT_ortho_4x12(
        HPR_GRV, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,    KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
        _______, KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, KC_LPRN,    KC_RPRN, KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, CTL_PIP,
        _______, KC_COLN, KC_QUOT, KC_ASTR, KC_COMM, KC_LCBR,    KC_RCBR, KC_UNDS, KC_PLUS, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______
        ),

/* Lower
 * ,-----------------------------------------.    ,-----------------------------------------.
 * |  ~   |  !   |  @   |  #   |  $   |  %   |    |  ^   |  &   |  *   |  (   |  )   |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Del  | Vol+ | Mute | Play | PgUp |  :   |    |  '   |  -   |  =   |  [   |  ]   |  \   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      | Vol- | < M  |  M > | PgDn |  ;   |    |  "   |  |   |  ,   |  .   |  /   |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * `-----------------------------------------'    `-----------------------------------------'
 */
    [_LOWER] = LAYOUT_ortho_4x12(
        HPR_TIL, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        CTL_DEL, KC_VOLU, KC_MUTE, KC_MPLY, KC_PGUP, KC_COLN,    KC_QUOT, KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, CTL_BSL,
        _______, KC_VOLD, KC_MPRV, KC_MNXT, KC_PGDN, KC_SCLN,    KC_DQUO, KC_PIPE, KC_COMM, KC_DOT , KC_SLSH, _______,
        _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______
        ),

    [_FUNC] = LAYOUT_ortho_4x12(
        _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,    KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______,
        _______, KC_F11 , KC_F12 , KC_F13 , KC_F14 , KC_F15 ,    KC_F16 , KC_F17 , KC_F18 , KC_F19 , KC_F20 , _______,
        _______, KC_F21 , KC_F22 , KC_F23 , KC_F24 , KC_NO  ,    KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______,
        _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______
        ),

    [_NUMS] = LAYOUT_ortho_4x12(
        _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,    KC_6   , KC_7   , KC_8   , KC_9   , KC_SLSH, _______,
        _______, KC_CAPS, KC_INS , KC_HOME, KC_PGUP, KC_LPRN,    KC_RPRN, KC_4   , KC_5   , KC_6   , KC_ASTR, _______,
        _______, KC_NUM , KC_DEL , KC_END , KC_PGDN, KC_SCLN,    KC_COMM, KC_1   , KC_2   , KC_3   , KC_MINS, _______,
        _______, _______, _______, _______, _______, _______,    _______, KC_0   , KC_DOT , KC_EQL , KC_PLUS, _______
        ),

    [_ADJUST] = LAYOUT_ortho_4x12(
        QK_BOOT, XXXXXXX, KC_UP  , XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL ,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,    BL_TOGG, BL_STEP, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______
        )
};

/* Template
 *
 * ,-----------------------------------------.    ,-----------------------------------------.
 * | Hyper|      |      |      |      |      |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Ctrl |      |      |      |      |      |    |      |      |      |      |      | Ctrl |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |    |      |      |      |      |      | Shift|
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * `-----------------------------------------'    `-----------------------------------------'
 *
 *
 */
//     ,-------+--------+--------+--------+--------+--------.   ,-------+--------+--------+--------+--------+--------.
//     |       |        |        |        |        |        |   |       |        |        |        |        |        |
//     ,-------+--------+--------+--------+--------+--------.   ,-------+--------+--------+--------+--------+--------.
//     |       |        |        |        |        |        |   |       |        |        |        |        |        |
//     ,-------+--------+--------+--------+--------+--------.   ,-------+--------+--------+--------+--------+--------.
//     |       |        |        |        |        |        |   |       |        |        |        |        |        |
//     ,-------+--------+--------+--------+--------+--------.   ,-------+--------+--------+--------+--------+--------.
//     |       |        |        |        |        |        |   |       |        |        |        |        |        |
//     `-------+--------+--------+--------+--------+--------'   `-------+--------+--------+--------+--------+--------,

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
