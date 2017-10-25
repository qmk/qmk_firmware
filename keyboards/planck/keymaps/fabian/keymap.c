
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
#include "keymap_german.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum planck_layers {
  _QWERTY,
  _QWERTZ,
  _WOT,
  _LOWER,
  _RAISE,
  _ADJUST,
  _FN
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  QWERTZ,
  GAMING,
  LOWER,
  RAISE,
  BACKLIT,
  FN
};

enum {
    SH_CP = 0
};


//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [SH_CP]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
  // Other declarations would go here, separated by commas, if you have them
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | FN   | Ctrl | GUI  | Alt  |Lower |Space | Bksp |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {TD(SH_CP), KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_T(KC_ENT) },
  {FN,      KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_BSPC, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   ]  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   -  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |   [  |   ]  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      | Del  |      |      | Prev | Next | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_RBRC},
  {_______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______},
  {_______, _______, _______, _______, _______, _______, KC_DEL,  _______, _______, KC_MPRV, KC_MNXT, KC_MPLY}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   4  |   5  |   6  |      |      |      |   _  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   7  |   8  |   9  |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |   0  |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______},
  {_______, KC_4,    KC_5,    KC_6,    _______, _______, _______, KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {_______, KC_7,    KC_8,    KC_9,    _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, KC_0,    _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Gaming
 * ,-----------------------------------------------------------------------------------.
 * |QWERTY|      |      |      |      |      |   1  |   2  |   3  |   4  |   5  |   6  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      | ESC  |   Q  |   W  |   E  |   R  |   7  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      | Tab  |   A  |   S  |   D  |   F  |   8  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |QWERTZ|      |      |      |      |      | Ctrl |   Y  |   X  |   C  |Space |Space |
 * `-----------------------------------------------------------------------------------'
 */
[_WOT] = {
  {QWERTY,  _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6   },
  {_______, _______, _______, _______, _______, _______, KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_7   },
  {_______, _______, _______, _______, _______, _______, KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_8   },
  {_______, _______, _______, _______, _______, _______, KC_LCTL, KC_Y,    KC_X,    KC_C,    KC_SPC,  KC_SPC }
},

/* Raise QWERTZ
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F3  |      |      |  F9  |  F10 |  F11 |  F12 |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |      |  F13 |  F14 |  F15 |  F16 |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FN] = {
  {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______},
  {_______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |Brite |      |Aud on|Audoff|      |      |Qwerty|Gaming|      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, BACKLIT, _______, AU_ON,   AU_OFF,  _______, _______, QWERTY,  GAMING,  _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}


};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif


void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case QWERTZ:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_QWERTZ);
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
    case LOWERZ:
      if (record->event.pressed) {
        layer_on(_LOWERZ);
        update_tri_layer(_LOWERZ, _RAISEZ, _ADJUST);
      } else {
        layer_off(_LOWERZ);
        update_tri_layer(_LOWERZ, _RAISEZ, _ADJUST);
      }
      return false;
      break;
    case RAISEZ:
      if (record->event.pressed) {
        layer_on(_RAISEZ);
        update_tri_layer(_LOWERZ, _RAISEZ, _ADJUST);
      } else {
        layer_off(_RAISEZ);
        update_tri_layer(_LOWERZ, _RAISEZ, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif
