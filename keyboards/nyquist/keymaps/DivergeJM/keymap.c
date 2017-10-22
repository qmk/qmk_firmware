#include "nyquist.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_layers {
  _COLEMAK,
  _LOWER,
  _RAISE,
  _FUNCTION,
  _MOUSE,
  _ADJUST,
};

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  LOWER,
  RAISE,
  FUNCTION,
  MOUSE,
  ADJUST,
};
/*
// Tap Dance Declarations
enum {
  TD_ZERO_ENT = 0
};

// Tap Dance Definitions
  qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ZERO_ENT]  = ACTION_TAP_DANCE_DOUBLE(KC_0, KC_ENT)
};
*/
  // Enable these functions using FUNC(n) macro.
  const uint16_t PROGMEM fn_actions[] = { //ACTION_LAYER_TAP_TOGGLE requires that number of taps be defined in *config.h* - default set to 5
      [0] = ACTION_LAYER_TAP_KEY(_LOWER, KC_SPC),    //Hold for momentary Lower layer, Tap for Space, 
      [1] = ACTION_LAYER_TAP_KEY(_RAISE, KC_ENT),    //Hold for momentary Mouse layer, Tap for Enter,
      [2] = ACTION_LAYER_TAP_TOGGLE(_LOWER),         //Hold for momentary Lower, Tap for toggle Lower
      [3] = ACTION_LAYER_TAP_TOGGLE(_MOUSE),         //Hold for momentary Mouse, Tap for toggle Mouse
      [4] = ACTION_LAYER_MOMENTARY(_FUNCTION)       //Hold for momentary Function
   };


#define SPC_LW FUNC(0)
#define ENT_RS FUNC(1)
#define LWR FUNC(2)
#define MSE FUNC(3)
#define FNC FUNC(4)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak
 * .----------------------------------------.     .-----------------------------------------.
 * | Esc |   1  |   2  |   3  |   4  |   5  |     |   6  |   7  |   8  |   9  |   0  | Del  |
 * |-----+------+------+------+------+------|     |------+------+------+------+------+------|
 * | Tab |   Q  |   W  |   F  |   P  |   G  |     |   J  |   L  |   U  |   Y  |   ;  |   \  |
 * |-----+------+------+------+------+------|     |------+------+------+------+------+------|
 * | BS  |   A  |   R  |   S  |   T  |   D  |     |   H  |   N  |   E  |   I  |   O  |   '  |
 * |-----+------+------+------+------+------|     |------+------+------+------+------+------|
 * | LSPO|   Z  |   X  |   C  |   V  |   B  |     |   K  |   M  |   ,  |   .  |   /  | RSPC |
 * |-----+------+------+------+------+------|     |------+------+------+------+------+------|
 * | Ctrl| LGUI | LAlt | Lower| Space/Lower |     | Enter/Raise |  Fn  | Mouse| Menu | Ctrl |
 * `----------------------------------------'     `-----------------------------------------'
 */
[_COLEMAK] = KEYMAP( \
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,    KC_6,   KC_7,    KC_8,      KC_9,    KC_0,    KC_DEL, \
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,   KC_G,    KC_J,   KC_L,    KC_U,      KC_Y,    KC_SCLN, KC_BSLS , \
  KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,   KC_D,    KC_H,   KC_N,    KC_E,      KC_I,    KC_O,    KC_QUOT, \
  KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,    KC_K,   KC_M,    KC_COMM,   KC_DOT,  KC_SLSH, KC_RSPC, \
  KC_LCTL, KC_LGUI, KC_LALT, LWR,   SPC_LW, SPC_LW,  ENT_RS, ENT_RS,    FNC,       MSE,     KC_APP,  KC_RCTL \
  ),


/* Lower
 * ,-----------------------------------------.    .-----------------------------------------.
 * |  Esc |      |      |      |      |      |    |   =  |   /  |   *  |   -  |      | Del  |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |  Tab | PgUp | Home |  Up  |  End |      |    |   7  |   8  |   9  |   +  |      |   \  |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |  BS  | PgDn | Left | Down |Right |      |    |   4  |   5  |   6  | Enter|      |   '  |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | LSPO |   Z  |   X  |   C  |   V  |      |    |   1  |   2  |   3  | Enter|      | RSPC |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Ctrl | LGUI | Alt  | Lower| Space/Lower |    |      0      |   .  |  Fn  | Menu | Ctrl |
 * `-----------------------------------------'    `-----------------------------------------'
 */
[_LOWER] = KEYMAP( \
  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  KC_PEQL, KC_PSLS, KC_PAST, KC_MINS,  XXXXXXX, KC_DEL, \
  _______,  KC_PGUP,  KC_HOME,  KC_UP,    KC_END,  XXXXXXX,  KC_7,    KC_8,    KC_9,    KC_PPLS,  XXXXXXX, _______, \
  _______, KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT, XXXXXXX,  KC_4,    KC_5,    KC_6,    KC_PENT,  XXXXXXX, _______, \
  _______, _______,  _______,  _______,  _______, XXXXXXX,  KC_1,    KC_2,    KC_3,    KC_PENT,  XXXXXXX, _______, \
  _______, _______,  _______,  _______,  _______, _______,  KC_0,    KC_0,    KC_DOT,  FNC,      _______, _______ \
),


/* Raise
 * ,-----------------------------------------.     .-----------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |     |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------|     |------+------+------+------+------+------|
 * |  Tab |      |      |      |      |      |     |      |      |      |      |      |   \  |
 * |------+------+------+------+------+------|     |------+------+------+------+------+------|
 * |  BS  |   !  |   @  |   #  |   $  |   %  |     |   ^  |   &  |   *  |   -  |   +  |   "  |
 * |------+------+------+------+------+------|     |------+------+------+------+------+------|
 * | LSBO |      |      |   {  |   [  |   `  |     |   |  |   ]  |   }  |   .  |   ?  | RSBC |
 * |------+------+------+------+------+------|     |------+------+------+------+------+------|
 * | Ctrl | LGUI | Alt  |      | Space/Lower |     | Enter/Raise |  Fn  | Mouse| Menu | Ctrl |
 * `-----------------------------------------'     `-----------------------------------------' 
*/
[_RAISE] = KEYMAP( \
  _______,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    _______, \
  _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, \
  _______,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC,  KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,  _______, \
  _______,  XXXXXXX, XXXXXXX, KC_LCBR, KC_LBRC, KC_GRV,  KC_PIPE,  KC_RBRC, KC_RCBR, KC_DOT,  KC_SLSH, _______, \
  _______,  _______, _______, XXXXXXX, _______, _______, ENT_RS,   ENT_RS,  FNC,     MSE,     _______, _______ \
  ),


/*Function
 * ,-----------------------------------------.     .-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |     |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------|     |------+------+------+------+------+------|
 * | Esc  | Mute | Vol- | Vol+ |      | RESET|     | POWER|      |      |      |      | Ins  |
 * |------+------+------+------+------+------|     |------+------+------+------+------+------|
 * | Caps | Stop | |<<  | >/|| |  >>| |      |     |      |      |      |      |      |PrtSc |
 * |------+------+------+------+------+------|     |------+------+------+------+------+------|
 * | LSOB |      |      |      |      |      |     |      |      |      |      |      |ScrLk |
 * |------+------+------+------+------+------|     |------+------+------+------+------+------|
 * | Ctrl | LGUI | Alt  |      | Space/Lower |     | Enter/Raise |  Fn  | Mouse|      |PsBrk |
 * `-----------------------------------------'     `-----------------------------------------'
 */

[_FUNCTION] = KEYMAP( 
  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12, \
  _______, KC_MUTE, KC_VOLD, KC_VOLU,  XXXXXXX, RESET,   KC_PWR,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_INS , \
  KC_CAPS, KC_MSTP, KC_MPRV, KC_MPLY,  KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_PSCR, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_SLCK, \
  _______, _______, _______, _______,  _______, _______, _______, _______, FNC,     _______,  _______, KC_PAUS \
  ),

/* MOUSE
 * ,----------------------------------------.     .----------------------------------------.
 * |  Esc |      |      |      |      |     |     |     |      |      |      |      |  Del |
 * |------+------+------+------+------+-----|     |-----+------+------+------+------+------|
 * |  Tab | WhlU | WhlL | MsUp | WhlR |     |     |     |  M1  |  M2  |  M3  |      |      |
 * |------+------+------+------+------+-----|     |-----+------+------+------+------+------|
 * |      | WhlD | MsL  | MsDn | MsR  |     |     |     |LClick|RClick|      |      |      |
 * |------+------+------+------+------+-----|     |-----+------+------+------+------+------|
 * | LSPO |      |      |      |      |     |     |     |      |      |      |      | RSCB |
 * |------+------+------+------+------+-----|     |-----+------+------+------+------+------|
 * | Ctrl |      |      |      |Sensitivity |     | Sensitivity|      |MOUSE |      | Ctrl |
 * `----------------------------------------'     `----------------------------------------'
 */

[_MOUSE] = KEYMAP(
   KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_DEL, \
   KC_TAB,  KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R,  XXXXXXX, XXXXXXX, KC_BTN3, KC_BTN4,  KC_BTN5, XXXXXXX, XXXXXXX, \
   KC_BSPC, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R,  XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2,  XXXXXXX, XXXXXXX, XXXXXXX, \
   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_RSPC, \
   _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_ACL1,  KC_ACL1, KC_ACL0, KC_ACL0, XXXXXXX,  MSE,     XXXXXXX, KC_RCTL \
  ),


};

#ifdef AUDIO_ENABLE
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}