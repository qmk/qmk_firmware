#include QMK_KEYBOARD_H

enum layer_names {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _UTIL,
  _MOUSE,
  _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
};

#define MOUSE  MO(_MOUSE)
#define ESC_UT LT(_UTIL, KC_ESC)
#define SPC_LO LT(_LOWER, KC_SPC)
#define SPC_RA LT(_RAISE, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
* ,--------------------------------------------------------------------------.
* | Tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  Bksp |
* |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
* | Lo/Esc|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |   '  |
* |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
* | Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  | /   |Enter|
* |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
* | Ctrl | Alt  |  GUI  | Space/LOWER | Space/RAISE |Mouse |  [  |  ]  |     |
* `--------------------------------------------------------------------------'
*/
[_QWERTY] = LAYOUT_arrow(
KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
ESC_UT,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
KC_LCTL, KC_LALT, KC_LGUI,                   SPC_LO,  SPC_RA,           MOUSE,   KC_LBRC, KC_RBRC, XXXXXXX
),

/* Colemak
* ,--------------------------------------------------------------------------.
* | Tab  |  Q  |  W  |  F  |  P  |  G  |  J  |  L  |  U  |  Y  |  ;  |  Del  |
* |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
* | Lo/Esc|  A  |  R  |  S  |  T  |  D  |  H  |  N  |  E  |  I  |  O  |   '  |
* |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
* | Shift  |  Z  |  X  |  C  |  V  |  B  |  K  |  M  |  ,  |  .  | /   |Enter|
* |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
* | Ctrl | Alt  |  GUI  | Space/LOWER | Space/RAISE |Mouse |  [  |  ]  |     |
* `--------------------------------------------------------------------------'
*/
[_COLEMAK] = LAYOUT_arrow(
KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
ESC_UT,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
KC_LCTL, KC_LALT, KC_LGUI,                   SPC_LO,  SPC_RA,           MOUSE,   KC_LBRC, KC_RBRC, XXXXXXX
),

/* Dvorak
* ,--------------------------------------------------------------------------.
* | Tab  |  /  |  ,  |  .  |  P  |  Y  |  F  |  G  |  C  |  R  |  L  |  Del  |
* |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
* | Lo/Esc|  A  |  O  |  E  |  U  |  I  |  D  |  H  |  T  |  N  |  S  |   '  |
* |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
* | Shift  |  ;  |  Q  |  J  |  K  |  X  |  B  |  M  |  W  |  V  | Z   |Enter|
* |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
* | Ctrl | Alt  |  GUI  | Space/LOWER | Space/RAISE |Mouse |  [  |  ]  |     |
* `--------------------------------------------------------------------------'
*/
[_DVORAK] = LAYOUT_arrow(
KC_TAB,  KC_SLSH, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
ESC_UT,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_QUOT,
KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT,
KC_LCTL, KC_LALT, KC_LGUI,                   SPC_LO,  SPC_RA,           MOUSE,   KC_LBRC, KC_RBRC, XXXXXXX
),

/* Lower
* ,--------------------------------------------------------------------------.
* |   ~  |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |  Del  |
* |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
* | Del   | F1  | F2  | F3  | F4  | F5  | F6  |  _  |  +  |  {  |  }  |   |  |
* |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
* |        | F7  | F8  | F9  | F10 | F11 | F12 |ISO ~|ISO ||     |     |     |
* |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
* |      |      |       |             |             | Next |Vol- |Vol+ |Play |
* `--------------------------------------------------------------------------'
*/
[_LOWER] = LAYOUT_arrow(
KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),_______, _______, _______,
_______, _______, _______,                   _______, _______,          KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
* ,--------------------------------------------------------------------------.
* |   `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  Del  |
* |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
* | Del   | F1  | F2  | F3  | F4  | F5  | F6  |  -  |  =  |  [  |  ]  |   \  |
* |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
* |        | F7  | F8  | F9  | F10 | F11 | F12 |ISO #|ISO /|     |     |     |
* |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
* |      |      |       |             |             | Next |Vol- |Vol+ |Play |
* `--------------------------------------------------------------------------'
*/
[_RAISE] = LAYOUT_arrow(
KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______,
_______, _______, _______,                   _______, _______,          KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Util
* ,--------------------------------------------------------------------------.
* |      |     |     |     |     |     |     |     |     |     |     |       |
* |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
* |       |     |     |     |     |     |LEFT | UP  |DOWN |RIGHT|     |      |
* |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
* |        |     |     |     |     |     |     |     |     |     |     |     |
* |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
* |      |      |       |             |             |      |     |     |     |
* `--------------------------------------------------------------------------'
*/
[_UTIL] = LAYOUT_arrow(
_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
_______, _______, _______,                   _______, _______,          _______, _______, _______, _______
),

/* Mouse
* ,--------------------------------------------------------------------------.
* |      |     | M U |     |     |     |     |     |     |L Clk|R Clk| W Up  |
* |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
* |       | M L | M D | M R |     |     |     |     |     |     |     |W Dwn |
* |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
* |        |     |     |     |     |     |     |     |     |     |     |     |
* |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
* |      |      |       |             |             |      |     |     |     |
* `--------------------------------------------------------------------------'
*/
[_MOUSE] = LAYOUT_arrow(
XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2, KC_WH_U,
XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_D,
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust
* ,--------------------------------------------------------------------------.
* |      |     |     |     |     |QWRTY|COLMK|DVRAK|     |     |     | QK_BOOT |
* |------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-------|
* |       |     |     |     |     |     |     |     |     |     |     |      |
* |-------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`------|
* |        |     |     |     |     |     |     |     |     |     |     |     |
* |--------`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----`-----|
* |      |      |       |             |             |      |     |     |     |
* `--------------------------------------------------------------------------'
*/
[_ADJUST] = LAYOUT_arrow(
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QWERTY,  COLEMAK, DVORAK,  XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
)


};

void keyboard_post_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    // set up rgb effects on only the third led (index 2)
    rgblight_set_effect_range(2, 1);

    // set led effects to breathing mode in warm white
    rgblight_sethsv_noeeprom(38, 191, 198);
    rgblight_mode_noeeprom(RGBLIGHT_EFFECT_BREATHING + 2);

    // set other led's to off
    setrgb(0, 0, 0, (rgb_led_t *)&led[0]);
    setrgb(0, 0, 0, (rgb_led_t *)&led[1]);
    rgblight_set();
  #endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  #ifdef RGBLIGHT_ENABLE
    if (layer_state_cmp(state, _ADJUST)) {
      setrgb(70, 255, 200, (rgb_led_t *)&led[0]);
      setrgb(255, 70, 100, (rgb_led_t *)&led[1]);
    } else if (layer_state_cmp(state, _LOWER)) {
      setrgb(70, 255, 200, (rgb_led_t *)&led[0]);
      setrgb(0, 0, 0, (rgb_led_t *)&led[1]);
    } else if (layer_state_cmp(state, _RAISE)) {
      setrgb(0, 0, 0, (rgb_led_t *)&led[0]);
      setrgb(255, 70, 100, (rgb_led_t *)&led[1]);
    } else if (layer_state_cmp(state, _UTIL)) {
      setrgb(200, 70, 225, (rgb_led_t *)&led[0]);
      setrgb(200, 70, 225, (rgb_led_t *)&led[1]);
    } else if (layer_state_cmp(state, _MOUSE)) {
      setrgb(255, 145, 5, (rgb_led_t *)&led[0]);
      setrgb(255, 145, 5, (rgb_led_t *)&led[1]);
    } else {
      setrgb(0, 0, 0, (rgb_led_t *)&led[0]);
      setrgb(0, 0, 0, (rgb_led_t *)&led[1]);
    }

    rgblight_set();
  #endif

  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
  }
  return true;
}
