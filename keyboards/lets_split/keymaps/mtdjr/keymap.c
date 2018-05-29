#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "action_macro.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  TD_ESC = 0
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


// Macro Declarations
#define UM_ROOT M(0)
#define UM_PPLY M(1)
#define UM_COPY M(2)
#define UM_INSR M(3)
#define UM_PSEF M(4)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
  * ,-----------------------------------------.  ,-----------------------------------------.
  * | Tab  |   Q  |   W  |   E  |   R  |   T  |  |   Y  |   U  |   I  |   O  |   P  | Bksp |
  * |------+------+------+------+------+------|  |------+------+------+------+------+------|
  * |Esc/~ |   A  |   S  |   D  |   F  |   G  |  |   H  |   J  |   K  |   L  |   ;  |  '/" |
  * |------+------+------+------+------+------|  |------+------+------+------+------+------|
  * | Shift|   Z  |   X  |   C  |   V  |   B  |  |   N  |   M  |   ,  |   .  |   /  |Enter |
  * |------+------+------+------+------+------|  |------+------+------+------+------+------|
  * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |  |Space |Raise | Left |  Up  | Down |Right |
  * `-----------------------------------------'  '-----------------------------------------'
  */
[_QWERTY] = KEYMAP( \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  TD(TD_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT \
),

  /* Lower
  * ,-----------------------------------------.  ,-----------------------------------------.
  * |   ~  |   1  |   2  |   3  |   4  |   5  |  |   6  |   7  |   8  |   9  |   0  | Bksp |
  * |------+------+------+------+------+------|  |------+------+------+------+------+------|
  * |      |      |   [  |   ]  |   {  |   }  |  |      |   4  |   5  |   6  |   *  |   \  |
  * |------+------+------+------+------+------|  |------+------+------+------+------+------|
  * |Shift |      |      | copy |insert|      |  |      |   1  |   2  |   3  |   +  |   -  |
  * |------+------+------+------+------+------|  |------+------+------+------+------+------|
  * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |  |Space |Raise |   0  |   .  |   =  |   _  |
  * `-----------------------------------------'  '-----------------------------------------'
  */
[_LOWER] = KEYMAP( \
  KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,  KC_9,   KC_0,    _______, \
  XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, XXXXXXX, KC_4,    KC_5,  KC_6,   KC_ASTR, KC_BSLS, \
  _______, XXXXXXX, XXXXXXX, UM_COPY, UM_INSR, XXXXXXX, XXXXXXX, KC_1,    KC_2,  KC_3,   KC_PLUS, KC_MINS, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_0,  KC_DOT, KC_EQL,  KC_UNDS \
),


/* Raise
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |   `  |   !  |   @  |   #  |   $  |   %  |  |   ^  |  &   |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |      |      |      |      |   \  |   |  |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |Shift |      |      |      |      |      |  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |  |Space |Raise | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------'  '-----------------------------------------'
 */
[_RAISE] = KEYMAP( \
  KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, KC_PIPE,\
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

  /* Adjust (Lower + Raise)
  * ,-----------------------------------------.  ,-----------------------------------------.
  * |      | Reset|      |      |      |      |  | ROOT | PPLY | PSEF |      |      |  Del |
  * |------+------+------+------+------+------|  |------+------+------+------+------+------|
  * |      |      |      |Aud on|Audoff|      |  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |
  * |------+------+------+------+------+------|  |------+------+------+------+------+------|
  * |      | UNDO | CUT  | COPY |PASTE |      |  |  F7  |  F8  |  F9  |  F10 | F11  |  F12 |
  * |------+------+------+------+------+------|  |------+------+------+------+------+------|
  * |      |      |      |      |      |      |  |      |      | Home |      |      | End  |
  * `-----------------------------------------'  '-----------------------------------------'
  */
[_ADJUST] =  KEYMAP( \
  _______, UM_ROOT, UM_PPLY, UM_PSEF, _______, _______, RESET,   _______, _______, _______, _______, KC_DEL, \
  _______, _______, _______, AU_ON,   AU_OFF,  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, \
  _______, KC_UNDO, KC_CUT,  UM_COPY, UM_INSR, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, _______, _______, KC_END \
)


};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for nothing, twice for ESC
  [TD_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_NO, KC_ESC)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
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
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  if (record->event.pressed) {
      switch(id) {
          case 0:
              SEND_STRING("sudo su -\n");
              return false; break;
          case 1:
              SEND_STRING("puppet apply /etc/puppetlabs/code/environments/production/manifests/site.pp\n");
              return false; break;
          case 2:
              return MACRO(D(LCTL), T(INS), U(LCTL), END);
              break;
          case 3:
              return MACRO(D(LSFT), T(INS), U(LSFT), END);
              break;
          case 4:
              SEND_STRING("ps -ef | grep ");
              return false; break;
      }
  }
  return MACRO_NONE;
};
