#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _COLEMAK 1
#define _GAME 2
#define _NUMB 3
#define _CODE 4
#define _SYS 5
#define _FN4 6
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  GAME,
  NUMB,
  CODE,
  SYS,
  FN4,
  ADJUST,
};

#define KC_X1 CODE
#define KC_X2 NUMB
#define KC_X3 MO(_SYS)
#define KC_X4 MT(MOD_LSFT, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,      KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     KC_BSPC, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,      KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,      KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH, KC_X4 ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      KC_X3 ,KC_LCTL,KC_LALT,KC_LGUI, KC_X1 ,KC_LALT,     KC_SPC , KC_X2 ,KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_COLEMAK] = LAYOUT(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     KC_TAB , KC_Q  , KC_W  , KC_F  , KC_P  , KC_G  ,      KC_J  , KC_L  , KC_U  , KC_Y  ,KC_SCLN,KC_MINS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     KC_BSPC, KC_A  , KC_R  , KC_S  , KC_T  , KC_D  ,      KC_H  , KC_N  , KC_E  , KC_I  , KC_O  ,KC_QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,      KC_K  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH, KC_X4 ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      KC_X3 ,KC_LCTL,KC_LALT,KC_LGUI, KC_X1 ,KC_LALT,     KC_SPC , KC_X2 ,KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_GAME] = LAYOUT(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,      KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     KC_ESC , KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,      KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,      KC_N  , KC_M  ,KC_COMM,KC_DOT , KC_UP ,KC_ENT ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     KC_LCTL, KC_X3 ,KC_LGUI,KC_LALT,KC_SPC , KC_X2 ,     KC_BSPC, KC_X1 ,KC_SLSH,KC_LEFT,KC_DOWN,KC_RGHT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_NUMB] = LAYOUT(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,     KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN, KC_DEL,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     KC_GRV , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,      KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_UNDS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     _______,_______,KC_MPRV,KC_MNXT,KC_MPLY,_______,     _______,KC_VOLD,KC_VOLU,KC_MUTE,_______,_______,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     _______,_______,_______,_______,_______,KC_LALT,     _______,_______,_______,_______,_______,_______
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_CODE] = LAYOUT(
  //,----+------+----+----+----+----.    ,----+----+----+----+----+----.
     KC_ESC ,  _______,_______, KC_UP ,_______,_______,     KC_PGUP,KC_HOME,KC_LPRN,KC_RPRN,KC_BSLS,KC_PIPE,
  //|----+------+----+----+----+----|    |----+----+----+----+----+----|
     KC_CAPS,KC_SELECT,KC_LEFT,KC_DOWN,KC_RGHT,KC_DEL ,     KC_PGDN, KC_END,KC_LBRC,KC_RBRC,KC_MINS,KC_UNDS,
  //|----+------+----+----+----+----|    |----+----+----+----+----+----|
     KC_LSFT, KC_UNDO ,KC_CUT ,KC_COPY,KC_PASTE,   _______,     KC_LEFT,KC_RGHT,KC_LCBR,KC_RCBR,KC_PLUS, KC_EQL,
  //|----+------+----+----+----+----|    |----+----+----+----+----+----|
     _______,  _______,_______,_______,_______,KC_LALT,     _______,_______,_______,_______,_______,_______
  //`----+------+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_SYS] = LAYOUT(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     _______,_______,_______,_______,_______,_______,     _______,_______,_______,_______,_______,_______,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,      KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     _______,_______,_______,_______,_______,_______,     _______,_______,_______,_______,_______,_______,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     _______,_______,_______,_______,_______,_______,     _______,_______,_______,_______,_______,_______
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|RGB Tg|RGB Md|Hue Up|Hue Dn|Sat Up|Sat Dn|Val Up|Val Dn|      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
  [_ADJUST] = LAYOUT_ortho_4x12( \
    _______, QK_BOOT, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
    _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, GAME  ,  _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
  )


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case GAME:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_GAME);
      }
      return false;
      break;
    case NUMB:
      if (record->event.pressed) {
        layer_on(_NUMB);
        update_tri_layer(_NUMB, _CODE, _ADJUST);
      } else {
        layer_off(_NUMB);
        update_tri_layer(_NUMB, _CODE, _ADJUST);
      }
      return false;
      break;
    case CODE:
      if (record->event.pressed) {
        layer_on(_CODE);
        update_tri_layer(_NUMB, _CODE, _ADJUST);
      } else {
        layer_off(_CODE);
        update_tri_layer(_NUMB, _CODE, _ADJUST);
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
