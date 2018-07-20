#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVORAK 0
#define _RAISE1 1
#define _RAISE2 2
#define _RAISE3 3
#define _ARROWS 4


enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  GAMING,
  RAISE1,
  RAISE2,
  RAISE3,
  ARROWS,
  REPROGRAM_MACRO,
  SCROT
};

//Tap Dance Declarations
enum {
  TD_EQUAL_ENTER= 0
  ,TD_DASH_SLASH
  ,TD_BSLASH_EQUAL
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap for enter, double tap for equal
  [TD_EQUAL_ENTER]  = ACTION_TAP_DANCE_DOUBLE(KC_ENT, KC_EQUAL)
  //Tap for dash, double tap for slash
  ,[TD_DASH_SLASH]  = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_SLASH)
  //Tap for backslash, double tap for equal
  ,[TD_BSLASH_EQUAL]  = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_EQUAL)
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Short codes to make reading easier
#define TD_EE TD(TD_EQUAL_ENTER)
#define LT2_SP LT(2, KC_SPC)
#define LT3_SP LT(3, KC_SPC)
#define TD_BLEQ TD(TD_BSLASH_EQUAL)
#define REPROGR REPROGRAM_MACRO
#define U_ARROW LT(4, KC_U)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  GUI | Alt  |      | MO(1)|Space2|Space3| Ctrl | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_ortho_4x12( \
  KC_GESC, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,   KC_F,   KC_G,    KC_C,    KC_R,    KC_L,  KC_BSPC, \
  KC_TAB,  KC_A,    KC_O,    KC_E,    U_ARROW, KC_I,   KC_D,   KC_H,    KC_T,    KC_N,    KC_S,  TD_EE,  \
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,   KC_B,   KC_M,    KC_W,    KC_V,    KC_Z,  SFT_T(KC_SLASH),  \
  KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX, MO(1),   LT2_SP, LT3_SP, KC_LCTL, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT  \
),


/* RAISE1
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Ins  | PGDN | PGUP |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Home | Vol- | Vol+ | END  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE1] = LAYOUT_ortho_4x12( \
	KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, TD_BLEQ, \
	_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  KC_PGDN, KC_PGUP, KC_MINS, \
	_______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, KC_HOME, KC_VOLD, KC_VOLU, KC_END \
),

/* RAISE2
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |  7   |  8   |  9   | BKSP |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  4   |  5   |  6   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  1   |  2   |  3   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  0   |  0   |  P.  |ENTER |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE2] = LAYOUT_ortho_4x12( \
		_______, _______, _______, _______, _______, _______, _______, _______, KC_7, KC_8, KC_9,    KC_BSPC, \
		_______, _______, _______, _______, _______, _______, _______, _______, KC_4, KC_5, KC_6,    XXXXXXX, \
		_______, _______, _______, _______, _______, _______, _______, _______, KC_1, KC_2, KC_3,    XXXXXXX, \
		_______, _______, _______, _______, _______, _______, _______, _______, KC_0, KC_0, KC_PDOT, KC_ENT \

),

/* RAISE3
 * ,-----------------------------------------------------------------------------------.
 * |RESET |PROGRA|      |      |Static| BRI+ |SGRAD |      | F10  | F11  | F12  |Paste |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |Rainbo| BRI- |K RIDR|      |  F7  |  F8  |  F9  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |RMODE | RGB T|SWIRL |      |  F4  |  F5  |  F6  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  F1  |  F2  |  F3  |SCROT |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE3] =  LAYOUT_ortho_4x12( \
  RESET,   REPROGR, _______, _______, RGB_M_P, RGB_VAI, RGB_M_G,  _______, KC_F10, KC_F11, KC_F12, LSFT(KC_INSERT), \
  _______, _______, _______, _______, RGB_M_R, RGB_VAD, RGB_M_K,  _______, KC_F7,  KC_F8,  KC_F9,  XXXXXXX, \
  _______, _______, _______, _______, RGB_MOD, RGB_TOG, RGB_M_SW, _______, KC_F4,  KC_F5,  KC_F6,  XXXXXXX, \
  _______, _______, _______, _______, _______, _______, _______,  _______, KC_F1,  KC_F2,  KC_F3,  SCROT \
),

/* Arrows
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      | Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ARROWS] = LAYOUT_ortho_4x12( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
),

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      return false;
      break;

    case RAISE1:
      if (record->event.pressed) {
        layer_on(_RAISE1);
      }
      else {
        layer_off(_RAISE1);
      }
      return false;
      break;

    case RAISE2:
      if (record->event.pressed) {
        layer_on(_RAISE2);
      }
      else{
        layer_off(_RAISE2);
      }
      return false;
      break;

    case RAISE3:
      if (record->event.pressed) {
        layer_on(_RAISE3);
      }
      else {
        layer_off(_RAISE3);
      }
      return false;
      break;

    case ARROWS:
      if (record->event.pressed) {
        layer_on(_ARROWS);
      }
      else {
        layer_off(_ARROWS);
      }
      return false;
      break;

    case REPROGRAM_MACRO:
      if (record->event.pressed) {
      SEND_STRING(SS_LGUI(SS_TAP(X_ENTER)));
      _delay_ms(500);
      SEND_STRING("~/qmk_firmware" SS_TAP(X_ENTER));
      _delay_ms(100);
      SEND_STRING("make "QMK_KEYBOARD":"QMK_KEYMAP":dfu && exit" SS_TAP(X_ENTER));
      return false;
     }

    case SCROT:
      if (record->event.pressed) {
      _delay_ms(100);
      SEND_STRING(SS_LGUI(SS_TAP(X_R)));
      _delay_ms(100);
      SEND_STRING("scrot");
      _delay_ms(10);
      SEND_STRING(SS_TAP(X_ENTER));
      return false;
     }
  }  return true;
}
