#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern rgblight_config_t rgblight_config;
extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Tap Dance Declarations
enum {
  SFT_CAP = 0,
  LFT_HOM,
  DWN_PDN,
  UPP_PUP,
  RGT_END
};

// Task Manager
#define C_S_ESC LSFT(LCTL(KC_ESC))
#define C_A_DEL LALT(LCTL(KC_DEL))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,------------------------------------------     ------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |     |  Y   |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------     -------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |     |  H   |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+-------     -------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |     |  N   |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+     +------+------+------+------+------+------|
*  |Adjust| Ctrl | Alt  | GUI  |Lower |Space |     |Space |Raise | Left | Down |  Up  |Right |
 * `------------------------------------------     ------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,        KC_O,        KC_P,        KC_BSPC, \
  CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,        KC_L,        KC_SCLN,     KC_QUOT, \
  TD(SFT_CAP),   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,     KC_DOT,      KC_SLSH,     SFT_T(KC_ENT), \
  ADJUST,        KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   TD(LFT_HOM), TD(DWN_PDN), TD(UPP_PUP), TD(RGT_END) \
),

/* Colemak
 * ,------------------------------------------     ------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |     |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------     -------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |     |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+-------     -------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |     |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+     +------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |     |Space |Raise | Left | Down |  Up  |Right |
 * `------------------------------------------     ------------------------------------------'
 */
[_COLEMAK] = KEYMAP( \
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, \
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Dvorak
 * ,------------------------------------------     ------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |     |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------     -------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |     |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+-------     -------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |     |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+     +------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |     |Space |Raise | Left | Down |  Up  |Right |
 * `------------------------------------------     ------------------------------------------'
 */
[_DVORAK] = KEYMAP( \
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC, \
  KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH, \
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT , \
  ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Lower
 * ,------------------------------------------     ------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |     |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------     -------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |     |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+-------     -------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |     |  F12 |ISO ~ |ISO | |  END | HOME |Enter |
 * |------+------+------+------+------+------+     +------+------+------+------+------+------|
 * |      |      |      |      |      |      |     |      |      | Next | Vol- | Vol+ | Play |
 * `------------------------------------------     ------------------------------------------'
 */
[_LOWER] = KEYMAP( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),KC_END, KC_HOME, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise
 * ,------------------------------------------     ------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |     |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------     -------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |     |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+-------     -------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |     |  F12 |ISO # |ISO / |PG DN |PG UP |Enter |
 * |------+------+------+------+------+------+     +------+------+------+------+------+------|
 * |      |      |      |      |      |      |     |      |      | Next | Vol- | Vol+ | Play |
 * `------------------------------------------     ------------------------------------------'
 */
[_RAISE] = KEYMAP( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGDN, KC_PGUP, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Adjust (Lower + Raise)
 * ,------------------------------------------     ------------------------------------------.
 * |      | Reset|      |      |      |      |     |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------     -------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|     |AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+-------     -------+------+------+------+------+------|
 * |      |Toggle| Mode | Hue- | Hue+ | Sat- |     | Sat+ | Val- | Val+ |      |      |      | (RGB)
 * |------+------+------+------+------+------+     +------+------+------+------+------+------|
 * |      |      |      |      |      |      |     |      |      |      |      |TskMng|CAltDe|
 * `------------------------------------------     ------------------------------------------'
 */
[_ADJUST] =  KEYMAP( \
  _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL, \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  _______, _______, \
  _______, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, C_S_ESC, C_A_DEL \
)


};

int RGB_current_mode;
int RGB_current_hue;

qk_tap_dance_action_t tap_dance_actions[] = {
  [SFT_CAP] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
  [LFT_HOM] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, KC_HOME),
  [DWN_PDN] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_PGDN),
  [UPP_PUP] = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_PGUP),
  [RGT_END] = ACTION_TAP_DANCE_DOUBLE(KC_RGHT, KC_END)
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        // Save current RGB info
        RGB_current_mode = rgblight_config.mode;
        RGB_current_hue = rgblight_config.hue;

        // Set RGB to Blue
        rgblight_mode(1);
        rgblight_setrgb(0, 0, 254);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        // Reset RGB
        rgblight_mode(RGB_current_mode);
        rgblight_sethsv(RGB_current_hue, rgblight_config.sat, rgblight_config.val);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        // Save current RGB info
        RGB_current_mode = rgblight_config.mode;
        RGB_current_hue = rgblight_config.hue;

        // Set RGB to Green
        rgblight_mode(1);
        rgblight_setrgb(0, 254, 0);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        // Reset RGB
        rgblight_mode(RGB_current_mode);
        rgblight_sethsv(RGB_current_hue, rgblight_config.sat, rgblight_config.val);
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
