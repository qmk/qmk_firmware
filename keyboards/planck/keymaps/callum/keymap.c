#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _BASE 0
#define _MOVE 1
#define _SYMB 2
#define _MORE 3
#define _FUNC 4
#define G(X) LGUI(X)
#define A(X) LALT(X)
#define C(X) LCTL(X)
#define GC(X) G(C(X))
#define GAC(X) G(A(C(X)))
#define _______ KC_TRNS
#define XXXXXXX KC_NO

enum planck_keycodes {
  MOVE = SAFE_RANGE,
  SYMB,
  FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE
 * ,-----------------------------------------------------------------------.
 * |Tab  |  Q  |  W  |  F  |  P  |  G  |  J  |  L  |  U  |  Y  |  ;  |  -  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |Bksp |  A  |  R  |  S  |  T  |  D  |  H  |  N  |  E  |  I  |  O  |  '  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |Shift|  Z  |  X  |  C  |  V  |  B  |  K  |  M  |  ,  |  .  |  /  |Shift|
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |Func |Super| Alt |Ctrl |Symb |Enter|Space|Move |Ctrl | Alt |Super|Func |
 * `-----------------------------------------------------------------------'
 */
[_BASE] = {
  {
    KC_TAB,       KC_Q,         KC_W,         KC_F,
    KC_P,         KC_G,         KC_J,         KC_L,
    KC_U,         KC_Y,         KC_SCLN,      KC_MINS
  },
  {
    KC_BSPC,      KC_A,         KC_R,         KC_S,
    KC_T,         KC_D,         KC_H,         KC_N,
    KC_E,         KC_I,         KC_O,         KC_QUOT
  },
  {
    KC_LSFT,      KC_Z,         KC_X,         KC_C,
    KC_V,         KC_B,         KC_K,         KC_M,
    KC_COMM,      KC_DOT,       KC_SLSH,      KC_RSFT
  },
  {
    FUNC,         KC_LGUI,      KC_LALT,      KC_LCTL,
    SYMB,         KC_ENT,       KC_SPC,       MOVE,
    KC_RCTL,      KC_RALT,      KC_RGUI,      FUNC
  }
},

[_MOVE] = {
  {
    GC(KC_UP),    GAC(KC_1),    G(KC_6),      G(KC_5),
    G(KC_4),      GAC(KC_UP),   GAC(KC_RGHT), KC_HOME,
    KC_UP,        KC_END,       G(KC_BSPC),   KC_ESC
  },
  {
    GC(KC_DOWN),  GAC(KC_2),    G(KC_3),      G(KC_2),
    G(KC_1),      G(KC_F),      G(KC_C),      KC_LEFT,
    KC_DOWN,      KC_RGHT,      KC_CAPS,      KC_DEL
  },
  {
    _______,      G(KC_3),      G(KC_9),      G(KC_8),
    G(KC_7),      G(KC_LEFT),   G(KC_DOWN),   KC_PGDN,
    KC_PGUP,      GC(KC_LEFT),  GC(KC_RGHT),  _______
  },
  {
    _______,      _______,      _______,      _______,
    _______,      GC(KC_ENT),   _______,      _______,
    _______,      _______,      _______,      _______
  }
},

[_SYMB] = {
  {
    KC_ESC,       KC_1,         KC_2,         KC_3,
    KC_4,         KC_5,         KC_6,         KC_7,
    KC_8,         KC_9,         KC_0,         _______
  },
  {
    KC_DEL,       KC_EXLM,      KC_AT,        KC_HASH,
    KC_DLR,       KC_PERC,      KC_CIRC,      KC_AMPR,
    KC_ASTR,      KC_LPRN,      KC_RPRN,      _______
  },
  {
    _______,      KC_TILD,      KC_GRV,       KC_PLUS,
    KC_EQL,       KC_PIPE,      KC_BSLS,      KC_LBRC,
    KC_RBRC,      KC_LCBR,      KC_RCBR,      _______
  },
  {
    _______,      _______,      _______,      _______,
    _______,      _______,      _______,      _______,
    _______,      _______,      _______,      _______
  }
},

[_MORE] = {
  {
    XXXXXXX,      A(KC_1),      A(KC_2),      A(KC_3),
    A(KC_4),      A(KC_5),      A(KC_6),      A(KC_7),
    A(KC_8),      A(KC_9),      A(KC_0),      XXXXXXX
  },
  {
    XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,
    XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,
    XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX
  },
  {
    _______,      XXXXXXX,      XXXXXXX,      XXXXXXX,
    XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,
    XXXXXXX,      XXXXXXX,      XXXXXXX,      _______
  },
  {
    _______,      _______,      _______,      _______,
    _______,      _______,      _______,      _______,
    _______,      _______,      _______,      _______
  }
},

[_FUNC] = {
  {
    RESET,        KC_F1,        KC_F2,        KC_F3,
    KC_F4,        KC_F5,        KC_F6,        KC_F7,
    KC_F8,        KC_F9,        KC_F10,       KC_VOLU
  },
  {
    KC_POWER,     KC_F11,       KC_F12,       KC_F13,
    KC_F14,       KC_F15,       KC_F16,       KC_F17,
    KC_F18,       KC_F19,       KC_F20,       KC_VOLD
  },
  {
    _______,      KC_F21,       KC_F22,       KC_F23,
    KC_F24,       XXXXXXX,      XXXXXXX,      XXXXXXX,
    XXXXXXX,      XXXXXXX,      XXXXXXX,      _______
  },
  {
    _______,      _______,      _______,      _______,
    KC_MPRV,      KC_MUTE,      KC_MPLY,      KC_MNXT,
    _______,      _______,      _______,      _______
  }
}

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MOVE:
      if (record->event.pressed) {
        layer_on(_MOVE);
        update_tri_layer(_MOVE, _SYMB, _MORE);
      } else {
        layer_off(_MOVE);
        update_tri_layer(_MOVE, _SYMB, _MORE);
      }
      return false;
      break;
    case SYMB:
      if (record->event.pressed) {
        layer_on(_SYMB);
        update_tri_layer(_MOVE, _SYMB, _MORE);
      } else {
        layer_off(_SYMB);
        update_tri_layer(_MOVE, _SYMB, _MORE);
      }
      return false;
      break;
    case FUNC:
      if (record->event.pressed) {
        layer_on(_FUNC);
      } else {
        layer_off(_FUNC);
      }
      return false;
      break;
  }
  return true;
}
