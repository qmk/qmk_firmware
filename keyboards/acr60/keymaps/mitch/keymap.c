#include "acr60.h"

#define _DEFAULT 0
#define _FN 1
#define _SFX 2

// Fillers to make layering more clear
#define ______ KC_TRNS

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

#define MITCHSPLIT( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012,       K014, \
	K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
	K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213,       \
	K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K314, \
	K400, K401,       K403, K404,       K406,       K408,       K410, K411,       K413, K414  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  KC_NO, K014 }, \
	{ K100,  KC_NO, K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114 }, \
	{ K200,  KC_NO, K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  KC_NO }, \
	{ K300,  KC_NO, K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  KC_NO, K313,  K314 }, \
	{ K400,  K401,  KC_NO, K403,  K404,  KC_NO, K406,  KC_NO, K408,  KC_NO, K410,  K411,  KC_NO, K413,  K414 }  \
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty gui/alt/space/alt/gui
 * ,-----------------------------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
 * |-----------------------------------------------------------------------------------------+
 * | Tab   |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   \    |
 * |-----------------------------------------------------------------------------------------+
 * |   Fn   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  / | RShift    | FN  |
 * |-----------------------------------------------------------------------------------------+
 * | LCtrl | LAlt | LGUI  |  (2.75u)  | (1.25u) | Space (2.25u) | RGUI |  Fn  | RAlt | RCtrl |
 * `-----------------------------------------------------------------------------------------'
 */
  [_DEFAULT] = MITCHSPLIT( /* Basic QWERTY */
      F(0),    KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
      KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,  \
      MO(_FN), KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  \
      KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN), \
      KC_LCTL, KC_LALT, KC_LGUI,        KC_SPC, KC_SPC, KC_SPC,         KC_RGUI, MO(_FN), LT(_SFX, KC_RALT), KC_RCTL \
      ),

/* Fn Layer / Layer 1
 * ,-----------------------------------------------------------------------------------------.
 * |KC_GRV| F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |   Del   |
 * |-----------------------------------------------------------------------------------------+
 * | CAPS  |     |     |     |     |     |    | Home| Up  |Pgup |     |     |     |  RESET  |
 * |-----------------------------------------------------------------------------------------+
 * |        | Vol-| Vol+| Mute|     |     |     | Left| Down|Right|     |     |             |
 * |-----------------------------------------------------------------------------------------+
 * |           |Prev |Play |Next |     |     |     |End  |     |PgDn |     |          |     |
 * |-----------------------------------------------------------------------------------------+
 * |      |      |       |               |       |              |      |      |      |      |
 * `-----------------------------------------------------------------------------------------'
 */
 /* Layer 1 */
  [_FN] = MITCHSPLIT(
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,   KC_F7,   KC_F8,   KC_F9,     KC_F10, KC_F11, KC_F12, KC_DEL, \
      KC_CAPS, ______,  ______,  ______,  ______, ______, ______,  KC_HOME, KC_UP ,  KC_PGUP ,  ______, ______, ______, RESET,  \
      ______,  KC_VOLD, KC_VOLU, KC_MUTE, ______, ______, ______,  KC_LEFT, KC_DOWN, KC_RIGHT,  ______, ______, ______,   \
      ______,  KC_MPRV, KC_MPLY, KC_MNXT, ______, ______, ______,  KC_END,  ______,  KC_PGDOWN, ______, ______, ______,  \
      ______,  ______,  ______,           ______, ______, ______,                    ______,    ______, TG(_SFX), ______  \
      ),

/* Fn Layer / Layer 1
 * ,-----------------------------------------------------------------------------------------.
 * |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
 * |-----------------------------------------------------------------------------------------+
 * |        | BL  |BLSTEP| BL- | BL+ |    |     |     |     |     |     |     |     |        |
 * |-----------------------------------------------------------------------------------------+
 * |         | RGBT| RGBM|     |     |     |     |     |     |     |     |     |             |
 * |-----------------------------------------------------------------------------------------+
 * |           | Hue+| Hue-| Sat+| Sat-| Val+| Val-|     |      |    |     |           |     |
 * |-----------------------------------------------------------------------------------------+
 * |      |      |       |               |       |              |      |      |      |      |
 * `-----------------------------------------------------------------------------------------'
 */
 /* Layer 2 */
  [_SFX] = MITCHSPLIT(
      ______,  RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, ______, ______, ______, ______, ______,  \
      ______,  BL_TOGG, BL_STEP, BL_DEC,  BL_INC,  ______,  ______,  ______,  ______, ______, ______, ______, ______, ______,  \
      ______,  RGB_TOG, RGB_SMOD,______,  ______,  ______,  ______,  ______,  ______, ______, ______, ______, ______,  \
      KC_LSFT, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ______,  ______, ______, ______, KC_RSFT,______,  \
      ______,  ______,  ______,             ______, ______, ______,                   ______, ______,TO(_DEFAULT), ______   \
      )

};

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}
