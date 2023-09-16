#include QMK_KEYBOARD_H
#include "spacebarracecar.h"

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

enum layers {
  _BASE,
  _RAISE,
  _LOWER,
  _MUSICMODE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base
,-----------------------------------------------------------------------------------------------------------------------.
|Tab      |Q        |W        |E        |R        |T        |Z        |U        |I        |O        |P        |Backspace|
|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
|Esc/Nav  |A        |S        |D        |F        |G        |H        |J        |K        |L        |;        |'        |
|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
|Shift    |Y        |X        |C        |V        |B        |N        |M        |,        |.        |/        |Shift    |
|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
|LCtrl    |         |Win      |Alt      |Lower    |Space    |Enter    |Raise    |AltGr    |Win      |Menu     |RCtrl    |
`-----------------------------------------------------------------------------------------------------------------------'
*/

[_BASE] = LAYOUT_ortho_4x12(
  KC_TAB,   DE_Q,     DE_W,     DE_E,     DE_R,     DE_T,     CU_Z,     DE_U,     DE_I,     DE_O,     DE_P,     KC_BSPC,
  CU_NAV,   DE_A,     DE_S,     DE_D,     DE_F,     DE_G,     DE_H,     DE_J,     DE_K,     DE_L,     CU_SCLN,  CU_QUOT,
  CU_LSFT,  CU_Y,     DE_X,     DE_C,     DE_V,     DE_B,     DE_N,     DE_M,     CU_COMM,  CU_DOT,   CU_SLSH,  CU_RSFT,
  KC_LCTL,  XXXXXXX,  KC_LGUI,  KC_LALT,  LOWER,    KC_SPC,   CTLENT,   RAISE,    KC_RALT,  KC_RGUI,  KC_APP,   KC_RCTL
),

/* Lower
,-----------------------------------------------------------------------------------------------------------------------.
|~        |!        |"        |#        |$        |%        |^        |&        |*        |(        |)        |         |
|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
|         |@        |Strg+X   |Strg+C   |Strg+V   |         |         |_        |+        |{        |}        ||        |
|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
|         |?        |         |         |         |         |         |         |         |         |         |         |
|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
|         |         |         |         |         |         |         |         |         |         |         |         |
`-----------------------------------------------------------------------------------------------------------------------'
*/
[_LOWER] = LAYOUT_ortho_4x12(
  DE_TILD,  DE_EXLM,  DE_DQUO,  DE_HASH,  DE_DLR,   DE_PERC,  CU_CIRC,  DE_AMPR,  DE_ASTR,  DE_LPRN,  DE_RPRN,  _______,
  _______,  DE_AT,    CTRLX,    CTRLC,    CTRLV,    XXXXXXX,  XXXXXXX,  DE_UNDS,  DE_PLUS,  DE_LCBR,  DE_RCBR,  DE_PIPE,
  _______,  DE_EURO,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  DE_MINS,  CU_EQL,   CU_LBRC,  CU_RBRC,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
),

/* Raise
,-----------------------------------------------------------------------------------------------------------------------.
|`        |1        |2        |3        |4        |5        |6        |7        |8        |9        |0        |         |
|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
|         |F1       |F2       |F3       |F4       |F5       |F6       |-        |=        |[        |]        |\        |
|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
|         |F7       |F8       |F9       |F10      |F11      |F12      |         |         |         |         |         |
|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
|         |         |         |         |         |         |         |         |         |         |         |         |
`-----------------------------------------------------------------------------------------------------------------------'
*/

[_RAISE] = LAYOUT_ortho_4x12(
  CU_GRV,   DE_1,     DE_2,     CU_3,     DE_4,     DE_5,     CU_6,     CU_7,     CU_8,     CU_9,     CU_0,     _______,
  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    DE_MINS,  CU_EQL,   CU_LBRC,  CU_RBRC,  CU_BSLS,
  _______,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   XXXXXXX,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
),

[_MUSICMODE] = LAYOUT_ortho_4x12(
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  KC_LCTL,  KC_LALT,  KC_LGUI,  KC_DOWN,  KC_UP,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  MU_NEXT,  MU_OFF
),

/* Deadkey
,-----------------------------------------------------------------------------------------------------------------------.
|         |         |         |         |         |         |         |Ü        |         |Ö        |         |         |
|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
|         |Ä        |ß        |         |         |         |         |         |         |         |         |         |
|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
|         |         |         |         |         |         |         |         |         |         |         |         |
|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
|         |         |         |         |         |"        |"        |         |         |         |         |         |
`-----------------------------------------------------------------------------------------------------------------------'
*/

[_DEADKEY] = LAYOUT_ortho_4x12(
  KC_TAB,   CU_ED,    CU_ED,    CU_ED,    CU_ED,    CU_ED,    CU_ED,    CU_UE,    CU_ED,    CU_OE,    CU_ED,    KC_BSPC,
  CU_NAV,   CU_AE,    CU_SS,    CU_ED,    CU_ED,    CU_ED,    CU_ED,    CU_ED,    CU_ED,    CU_ED,    CU_ED,    CU_DDQ,
  CU_LSFT,  CU_ED,    CU_ED,    CU_ED,    CU_ED,    CU_ED,    CU_ED,    CU_ED,    CU_ED,    CU_ED,    CU_ED,    CU_RSFT,
  KC_LCTL,  XXXXXXX,  KC_LGUI,  KC_LALT,  LOWER,    CU_DDQ,   CU_DDQ,   RAISE,    KC_RALT,  KC_RGUI,  KC_APP,   KC_RCTL
),

/* Navigation
,-----------------------------------------------------------------------------------------------------------------------.
|ALT F4   |PageDown |Up       |PageUp   |Home     |         |         |         |Win+Up   |         |         |Del      |
|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
|         |Left     |Down     |Right    |End      |         |         |Win+Left |Win+Down |Win+Right|         |Enter    |
|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
|         |Prev     |Pause    |Next     |LowerVol |RaiseVol |Mute     |         |         |         |         |         |
|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
|QK_BOOT    |ESCT     |         |         |         |         |         |         |         |         |         |Game     |
`-----------------------------------------------------------------------------------------------------------------------'
*/

[_NAV] = LAYOUT_ortho_4x12(
  _______,  KC_PGDN,  KC_UP,    KC_PGUP,  KC_HOME,  XXXXXXX,  XXXXXXX,  XXXXXXX,  GUIU,     XXXXXXX,  XXXXXXX,  KC_DEL,
  _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_END,   XXXXXXX,  XXXXXXX,  GUIL,     GUID,     GUIR,     EMOJI,    KC_ENT,
  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_VOLD,  KC_VOLU,  KC_MUTE,  MU_ON,    XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,
  QK_BOOT,  CU_ESCT,  ALTF4,    _______,  _______,  KC_SPC,   CTLENT,   _______,  _______,  _______,  _______,  CU_GAME
)

};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
switch (keycode) {
  case MO(_LOWER):
    if (game){
      if(record->event.pressed) {
        register_code(KC_SPC);
      } else {
        unregister_code(KC_SPC);
      }
      return false;
    } else {
      return true;
    }
  case KC_LALT:
    if (game) {
      if (record->event.pressed){
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
    } else {
      return true;
    }
  case MU_ON:
    if(record->event.pressed) {
      layer_off(_LOWER);
      layer_off(_RAISE);
      layer_off(_NAV);
      layer_off(_DEADKEY);
      layer_on(_MUSICMODE);
    }
    return true;
  case MU_OFF:
    if(record->event.pressed) {
      layer_off(_MUSICMODE);
    }
    return true;
  default:
    return true;
  }
}
