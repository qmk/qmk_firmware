#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _GAME 1
#define _LOWER 2
#define _VIM 3


enum custom_macros {
    DLEFT,
    DRIGHT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | 0(') |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  | Ö(0) | Ü(-) |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |  Z(Y)|   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  É(;)| Á(") |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Í/Shft| Y(Z) |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  -(/)| Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  GUI |  Alt |LOWER |  Spc |  Spc | Bksp | Ent  |  Alt | =(&) | GAME | Del  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_GRV,                KC_1,      KC_2,    KC_3,       KC_4,             KC_5,             KC_6,     KC_7,    KC_8,    KC_9,         KC_0,          KC_MINUS, \
  KC_TAB,                KC_Q,      KC_W,    KC_E,       KC_R,             KC_T,             KC_Y,     KC_U,    KC_I,    KC_O,         KC_P,          KC_BSPC, \
  KC_ESC,                KC_A,      KC_S,    KC_D,       KC_F,             KC_G,             KC_H,     KC_J,    KC_K,    KC_L,         KC_SCLN,       KC_QUOT, \
  MT(MOD_LSFT, KC_NUBS), KC_Z,      KC_X,    KC_C,       KC_V,             KC_B,             KC_N,     KC_M,    KC_COMM, KC_DOT,       KC_SLSH,       KC_RSFT, \
  KC_LCTL,               KC_LGUI,   KC_LALT, TT(_LOWER), LT(_VIM, KC_SPC), LT(_VIM, KC_SPC), KC_BSPC,  KC_ENT,  KC_RALT, KC_AMPERSAND, TG(_GAME),     KC_DEL \
),

/* Gaming mode
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |QWERTY|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |  Spc |  Spc |      |      | Left | Down |  Up  | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] =  LAYOUT( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(_QWERTY),    \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    \
  KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    \
  _______, _______, _______, _______, KC_SPC,  KC_SPC,  _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |  Up  |      |      |      |      |   7  |   8  |   9  |   /  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Left | Down | Right|      |      |      |   4  |   5  |   6  |   *  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |   1  |   2  |   3  |   -  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   0  |   .  |   =  |   +  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT( \
  KC_F1,     KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,   KC_F9,     KC_F10,       KC_F11,         KC_F12, \
  _______,   _______, KC_UP,   _______, _______, _______, _______,  KC_7,    KC_8,      KC_9,         KC_KP_SLASH,    _______, \
  _______,   KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______,  KC_4,    KC_5,      KC_6,         KC_KP_ASTERISK, _______, \
  KC_LSFT,   _______, _______, _______, _______, _______, _______,  KC_1,    KC_2,      KC_3,         KC_KP_MINUS,    _______, \
  _______,   _______, _______, _______, _______, _______, _______,  KC_GRV,  KC_KP_DOT, KC_KP_EQUAL,  KC_KP_PLUS,     _______ \
),


/* Vim Movement (Hold down SPACE)
 * ,-----------------------------------------------------------------------------------.
 * | Ins  | Home | PGUP |      |DM_stp|      |      |      |      |      |   Ő  |  Ű   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  | End  | PGDN |      |DM_REC|      |      |  Ú   |   Í  |   Ó  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | DLeft|DRight| LCTRL|      |      | Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | LShft|      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_VIM] =  LAYOUT( \
  KC_INS,  KC_HOME,  KC_PGUP,   _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_NUHS, \
  KC_DEL,  KC_END,   KC_PGDN,   _______, _______, _______, _______, KC_RBRC, KC_NUBS, KC_EQL , _______, _______, \
  _______, M(DLEFT), M(DRIGHT), KC_LCTL, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
  _______, _______,  _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______,  _______,   KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______ \
)


};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch(id) {
        case DLEFT:
            if (record->event.pressed) { // Windows move desktop left
                return MACRO(D(LCTL), D(LGUI), T(LEFT), U(LGUI), U(LCTL), END);
            }
            break;
        case DRIGHT:
            if (record->event.pressed) { // Windows move desktop right
                return MACRO(D(LCTL), D(LGUI), T(RIGHT), U(LGUI), U(LCTL), END);
            }
            break;
    }
    return MACRO_NONE;
}

#ifdef RGBLIGHT_ENABLE
bool rgb_layer_change = true;
#endif

#define rgblight_set_blue        rgblight_sethsv (0xFF,  0xFF, 0xFF);
#define rgblight_set_red         rgblight_sethsv (0x00,  0xFF, 0xFF);
#define rgblight_set_green       rgblight_sethsv (0x78,  0xFF, 0xFF);
#define rgblight_set_orange      rgblight_sethsv (0x1E,  0xFF, 0xFF);
#define rgblight_set_teal        rgblight_sethsv (0xC3,  0xFF, 0xFF);
#define rgblight_set_magenta     rgblight_sethsv (0x12C, 0xFF, 0xFF);
#define rgblight_set_yellow      rgblight_sethsv (0x3C,  0xFF, 0xFF);
#define rgblight_set_purple      rgblight_sethsv (0x10E, 0xFF, 0xFF);
#define rgblight_set_white       rgblight_sethsv (0x00,  0x00, 0xFF);
#define rgblight_set_black       rgblight_sethsv (0x00,  0x00, 0x00);

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
  uint8_t default_layer = eeconfig_read_default_layer();
  if (rgb_layer_change) {
    switch (biton32(state)) {
    case _LOWER:
      rgblight_set_purple;
      rgblight_mode(5);
      break;
    case _VIM:
	  rgblight_set_green;
      rgblight_mode(23);
      break;
	case _GAME:
      rgblight_mode(8);
      break;
    default:
      if (default_layer & (1UL << _GAME)) {
      }
      else
      rgblight_mode(14);
      break;
    }
  }
#endif
  return state;
}
