#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

#define G(X) LGUI(X)
#define A(X) LALT(X)
#define C(X) LCTL(X)
#define GC(X) G(C(X))
#define GAC(X) G(A(C(X)))
#define _______ KC_TRNS
#define XXXXXXX KC_NO

enum planck_layers {
    _COLEMAK,
    _QWERTY,
    _SYMB,
    _MOVE,
    _FUNC
};

enum planck_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  SYMB,
  MOVE,
  FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK
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
[_COLEMAK] = {
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

/* QWERTY
 * ,-----------------------------------------------------------------------.
 * |Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  -  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |Bksp |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |Shift|  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |Shift|
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |Func |Super| Alt |Ctrl |Symb |Enter|Space|Move |Ctrl | Alt |Super|Func |
 * `-----------------------------------------------------------------------'
 */
[_QWERTY] = {
  {
    KC_TAB,       KC_Q,         KC_W,         KC_E,
    KC_R,         KC_T,         KC_Y,         KC_U,
    KC_I,         KC_O,         KC_P,         KC_MINS
  },
  {
    KC_BSPC,      KC_A,         KC_S,         KC_D,
    KC_F,         KC_G,         KC_H,         KC_J,
    KC_K,         KC_L,         KC_SCLN,      KC_QUOT
  },
  {
    KC_LSFT,      KC_Z,         KC_X,         KC_C,
    KC_V,         KC_B,         KC_N,         KC_M,
    KC_COMM,      KC_DOT,       KC_SLSH,      KC_RSFT
  },
  {
    FUNC,         KC_LGUI,      KC_LALT,      KC_LCTL,
    SYMB,         KC_ENT,       KC_SPC,       MOVE,
    KC_RCTL,      KC_RALT,      KC_RGUI,      FUNC
  }
},

/* SYMB
 * ,-----------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |     |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * | Del |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |     |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     |  ~  |  `  |  +  |  =  |  |  |  \  |  [  |  ]  |  {  |  }  |     |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |     |     |     |     |     |     |     |
 * `-----------------------------------------------------------------------'
 */
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

/* MOVE
 * ,-----------------------------------------------------------------------.
 * |     |     |     |     |     |     |     |Home | Up  | End |     | Esc |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |     |     |Left |Down |Right|Caps | Del |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |     |     |PgDn |PgUp |     |     |     |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |     |     |     |     |     |     |     |
 * `-----------------------------------------------------------------------'
 */
[_MOVE] = {
  {
    GC(KC_UP),    GAC(KC_1),    G(KC_6),      G(KC_5),
    G(KC_4),      GAC(KC_UP),   GAC(KC_RGHT), KC_HOME,
    KC_UP,        KC_END,       C(KC_SPC),    KC_ESC
  },
  {
    GC(KC_DOWN),  GAC(KC_2),    G(KC_3),      G(KC_2),
    G(KC_1),      G(KC_F),      G(KC_C),      KC_LEFT,
    KC_DOWN,      KC_RGHT,      KC_CAPS,      KC_DEL
  },
  {
    _______,      GAC(KC_3),    G(KC_9),      G(KC_8),
    G(KC_7),      GAC(KC_LEFT), GAC(KC_DOWN), KC_PGDN,
    KC_PGUP,      GC(KC_LEFT),  GC(KC_RGHT),  _______
  },
  {
    _______,      _______,      _______,      _______,
    _______,      _______,      _______,      _______,
    _______,      _______,      _______,      _______
  }
},

/* FUNC
 * ,-----------------------------------------------------------------------.
 * |Reset| F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 |VolUp|
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |Power| F11 | F12 | F13 | F14 | F15 | F16 | F17 | F18 | F19 | F20 |VolDn|
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     | F21 | F22 | F23 | F24 |     |     |     |     |Clmak|Qwrty|     |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |Prev |Mute |Play |Next |     |     |     |     |
 * `-----------------------------------------------------------------------'
 */
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
    XXXXXXX,      COLEMAK,      QWERTY,       _______
  },
  {
    _______,      _______,      _______,      _______,
    KC_MPRV,      KC_MUTE,      KC_MPLY,      KC_MNXT,
    _______,      _______,      _______,      _______
  }
}

};

#ifdef AUDIO_ENABLE
  float colemak_song[][2] = SONG(COLEMAK_SOUND);
  float qwerty_song[][2] = SONG(QWERTY_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(colemak_song);
        #endif
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(qwerty_song);
        #endif
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case SYMB:
      if (record->event.pressed) {
        layer_on(_SYMB);
      } else {
        layer_off(_SYMB);
      }
      return false;
      break;
    case MOVE:
      if (record->event.pressed) {
        layer_on(_MOVE);
      } else {
        layer_off(_MOVE);
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
