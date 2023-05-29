#include QMK_KEYBOARD_H

enum layers {
  _QW,
  _LW,
  _RS,
  _AD,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  MKITPNK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------.    ,-----------------------------------------.
 * | Esc  |  Q   |  W   |  E   |  R   |  T   |    |  Y   |  U   |  I   |  O   |  P   | Del  |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Tab  |  A   |  S   |  D   |  F   |  G   |    |  H   |  J   |  K   |  L   |  ;   | Bksp |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Shift|  Z   |  X   |  C   |  V   |  B   |    |  N   |  M   |  ,   |  .   |  \   |  =   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Ctrl |      | Meta | Alt  | Lower| Enter|    | Space| Raise| Alt  | Meta |      |      |
 * `-----------------------------------------'    `-----------------------------------------'
 */
    [_QW] = LAYOUT_ortho_4x12(
        KC_ESC  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_DEL ,
        KC_TAB  , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_BSPC,
        KC_LSFT , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_BSLS, KC_EQL ,
        KC_LCTL , _______, KC_LGUI, KC_LALT, LOWER  , KC_ENT , KC_SPC , RAISE  , KC_RALT, KC_LGUI, _______, _______
        ),

/* Raise
 * ,-----------------------------------------.    ,-----------------------------------------.
 * |   ,  |  1   |  2   |  3   |  +   |  -   |    |  {   |  }   |  (   |  )   |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |   .  |  4   |  5   |  6   |  #   |  *   |    |  F1  | F2   | F3   | F4   | F5   | F6   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Shift|  7   |  8   |  9   |  /   |  =   |    |  F7  | F8   | F9   | F10  | F11  | F12  |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |  0   |      |Adjust|      |    |      | RAISE|      |      |      |      |
 * `-----------------------------------------'    `-----------------------------------------'
 */
    [_RS] = LAYOUT_ortho_4x12(
        KC_COMM , KC_1   , KC_2   , KC_3   , KC_PLUS, KC_MINS, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, _______, _______,
        KC_DOT  , KC_4   , KC_5   , KC_6   , KC_HASH, KC_ASTR, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,
        KC_LSFT , KC_7   , KC_8   , KC_9   , KC_SLSH, KC_EQL , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
        _______ , _______, KC_0   , _______, _______, _______, _______, _______, _______, _______, _______, _______
        ),

/* Lower
 * ,-----------------------------------------.    ,-----------------------------------------.
 * |  `   |  !   |  @   |  #   |  $   |  %   |    |  Home|  PgDn|  PgUp|  End |  (   |  )   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      | Vol+ | Mute | Play |      | Ins  |    |  Left|  Down|  Up  | Right|  {   |  }   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      | Vol- | < M  |  M > |      |      |    |  ^   |  &   |  *   |  '   |  [   |  ]   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |LOWER |      |    | Shift|Adjust|      |      |      |      |
 * `-----------------------------------------'    `-----------------------------------------'
 */
    [_LW] = LAYOUT_ortho_4x12(
        KC_GRV  , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,    KC_HOME , KC_PGDN, KC_PGUP, KC_END  , KC_LPRN, KC_RPRN,
        _______ , KC_VOLU, KC_MUTE, KC_MPLY, _______, KC_INS ,    KC_LEFT , KC_DOWN, KC_UP  , KC_RIGHT, KC_LCBR, KC_RCBR,
        _______ , KC_VOLD, KC_MPRV, KC_MNXT, _______, _______,    KC_CIRC , KC_AMPR, KC_ASTR, KC_QUOT , KC_LBRC, KC_RBRC ,
        _______ , _______, _______, _______, _______, _______,    KC_LSFT , _______, _______, _______ , _______, _______
        ),

/* Adjust
 * ,-----------------------------------------.    ,-----------------------------------------.
 * | Reset|      |  Up  |      |      | Rec1 |    | Rec2 | Plain| Snake|Gradnt|      | Del  |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Caps | Left | Down | Right|MkItPk| Play1|    | Play2| RGB  | HUE+ | SAT+ | BRI+ |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      | Stop1|    | Stop2| MODE | HUE- | SAT- | BRI- |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * `-----------------------------------------'    `-----------------------------------------'
 */
    [_AD] = LAYOUT_ortho_4x12(
        QK_BOOT, XXXXXXX,  KC_UP , XXXXXXX, XXXXXXX, DM_REC1,    DM_REC2, RGB_M_P, RGB_M_SN,RGB_M_G, XXXXXXX, KC_DEL ,
        KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, MKITPNK, DM_PLY1,    DM_PLY2, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DM_RSTP,    DM_RSTP, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______,
        _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______
        )
};

void make_it_pink_blue(void) {
    uint16_t blue_hue = 210;
    uint16_t pink_hue = 315;

    /* key is pressed */
    uint16_t hue = rgblight_get_hue();
    uint8_t sat = rgblight_get_sat();
    uint8_t val = rgblight_get_val();

    if (hue != blue_hue)
        rgblight_sethsv(blue_hue, sat, val);
    else
        rgblight_sethsv(pink_hue, sat, val);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case QWERTY:
          if (record->event.pressed) {
              set_single_persistent_default_layer(_QW);
          }
          return false;
          break;
      case LOWER:
          if (record->event.pressed) {
              layer_on(_LW);
              update_tri_layer(_LW, _RS, _AD);
          } else {
              layer_off(_LW);
              update_tri_layer(_LW, _RS, _AD);
          }
          return false;
          break;
      case RAISE:
          if (record->event.pressed) {
              layer_on(_RS);
              update_tri_layer(_LW, _RS, _AD);
          } else {
              layer_off(_RS);
              update_tri_layer(_LW, _RS, _AD);
          }
          return false;
          break;
      case ADJUST:
          if (record->event.pressed) {
              layer_on(_AD);
          } else {
              layer_off(_AD);
          }
          return false;
          break;
      case MKITPNK:
          if (record->event.pressed)
              make_it_pink_blue();
          return false;
          break;
    }
    return true;
}
