/*
 * 
 * An Italian ANSI layout
 * Version 0.3 
 * 
 * Created by Silvio Gulizia on the basis of the default Planck keymap.
 * thanks to SomeBuddyOnReddit, gepeirl, fauxpark, BXO511,  ...
 *
 * based on the original Planck layout
 * Italian accented vowels "ò" and "à" have been moved from the QWERTY layer to the LOWER layers, while "è" and "ù" remain respectively on RAISE and LOWER.
 *
 */

#include QMK_KEYBOARD_H
#include "muse.h"
#include "keymap_italian_osx_ansi.h"


enum planck_layers {
  _QWERTY,
  _LOWER, //symbols
  _RAISE, //numbers
  _ADJUST, //system
  _NUMPAD,
  _FN, 
  _MOUSE
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  // custom keycodes for personal macros
  DESK, // personal email
  VIVERE, // website
  SVIV, // website email
  SGCOM, // personal website
  PHONE, // my phone number
  // custom keycodes for an Italian ANSI layout with accented vowels
  IT_CMLS, // IT_COMM and IT_LESS when combined with shift
  IT_DTMR, // IT_DOT and IT_MORE when combined with shift
  IT_SLQS, // IT_SLSH and IT_QST when combined with shift
  IT_APDQ, // IT_APO and IT_DQOT when combined with shift
  IT_SCCL  // IT_SMCL and IT_COLN when combined with shift

};

// Defining Layer Keycodes
#define QWERTY DF(_QWERTY)
// For LOWER and RAISE I use TT instead of MO to be able to lock those layer tapping three times the key (TAPPING_TOGGLE 3 has been added in config.h)
#define LOWER TT(_LOWER)
#define RAISE TT(_RAISE)
#define NUMPAD TG(_NUMPAD)
#define FN MO(_FN)
#define MOUSE TT(_MOUSE)
#define TABFN LT(_FN, KC_TAB)
#define ESCFN LT(_FN, KC_ESC)
#define FN_D LT(_FN, IT_D)
#define MS_B LT(_MOUSE, IT_B)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |Tab/FN|   Q  |   W  |  E   |  R   |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Esc/FN|   A  |   S  | FN/D |  F   |   G  |   H  |   J  |   K  |   L  |  ;:  |  '"  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |  C   |  V   | FN/B |   N  |   M  |  ,<  |  .>  |  /!  |S/Ent |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | FN   | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
    TABFN,   IT_Q,    IT_W,    IT_E,      IT_R,  IT_T,    IT_Y,    IT_U,  IT_I,    IT_O,    IT_P,    KC_BSPC,
    ESCFN,   IT_A,    IT_S,    FN_D,      IT_F,  IT_G,    IT_H,    IT_J,  IT_K,    IT_L,    IT_SCCL, IT_APDQ,
    KC_LSFT, IT_Z,    IT_X,    IT_C,      IT_V,  MS_B,    IT_N,    IT_M,  IT_CMLS, IT_DTMR, IT_SLQS, MT(MOD_RSFT, KC_ENT),
    FN,      KC_LCTL, KC_LALT, KC_LGUI,   LOWER, KC_SPC,  KC_SPC,  RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * added ò and à that were on the default Planck Querty layer when used with a device with lang set to Italian
 * ,-----------------------------------------------------------------------------------.
 * |  ~   |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |  (   |  )   | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |   _  |   =  |  é   |  ò   |  à   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  | MOUSE|NUMPAD|   §  |   ±  |  {   |  }   |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */

[_LOWER] = LAYOUT_ortho_4x12(
    IT_TILDE, IT_EXLM, IT_AT,   IT_SHRP, IT_DLR,  IT_PERC, IT_CRC,  IT_AMPR,    IT_ASTR, IT_LPRN,    IT_RPRN, KC_DEL,
    _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, S(IT_MINS), IT_EQL,  S(IT_EACC), IT_OACC, IT_AACC,
    _______,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   MOUSE,   NUMPAD,  S(IT_UACC), IT_PLMN, IT_LCBR,    IT_RCBR, IT_PIPE,
    _______,  _______, _______, _______, _______, _______, _______, _______,    KC_MNXT, KC_VOLD,    KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | SGCOM| DESK |      |      |      |   -  |   +  |   è  |   ì  |  ù   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Caps |      | PHONE| SVIV |VIVERE|MOUSE |NUMPAD|      |      |  [   |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
    IT_GRAVE, IT_1,    IT_2,    IT_3,	 IT_4,    IT_5,    IT_6,    IT_7,    IT_8,    IT_9,    IT_0,    _______,
    _______,  _______, SGCOM,   DESK,    _______, _______, _______, IT_MINS, IT_PLUS, IT_EACC, IT_IACC, IT_UACC,
    KC_CAPS,  _______, PHONE,   SVIV,    VIVERE,  MOUSE,   NUMPAD,  _______, _______, IT_LBRC, IT_RBRC, IT_BSLS,
    _______,  _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |  7   |  8   |  9   |  -   | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  4   |  5   |  6   |  +   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |NUMPAD|  1   |  2   |  3   |  =   | Ent  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  0   |  /   |  *   |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_ortho_4x12(
    _______, _______, _______, _______, _______, _______, _______, IT_7,    IT_8, IT_9,    IT_MINS, KC_BSPC,
    _______, _______, _______, _______, _______, _______, _______, IT_4,    IT_5, IT_6,    IT_PLUS, _______,
    _______, _______, _______, _______, _______, _______, NUMPAD,  IT_1,    IT_2, IT_3,    IT_EQL,  KC_ENT,
    _______, _______, _______, _______, _______, _______, _______, _______, IT_0, IT_SLSH, IT_ASTR, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |Querty|      |ResetE|Reset |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Debug |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |Music |MusON |MusOff|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |Voice-|Aud On|Audoff|Voice+|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
    _______, DF(QWERTY), _______, EEP_RST, RESET,   _______, _______, _______, _______, _______, _______, _______,
    _______, _______,    _______, DEBUG,   _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,    _______, _______, _______, _______, MU_MOD,  MU_ON,   MU_OFF,  _______, _______, _______,
    _______, _______,    _______, _______, _______, _______, _______, _______, MUV_DE,  AU_ON,   AU_OFF,  MUV_IN
),


/* Function
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  | F5   |  F6  |  F7  |  F8  |  F9  | F10  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  | F5   | Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  | F10  |  F1  |  F2  |  F3  |  F4  | F5   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | RAISE|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_FN] = LAYOUT_ortho_4x12(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F7,      KC_F8,   KC_F9,    KC_F10,  KC_DEL,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LEFT,    KC_DOWN,    KC_UP,   KC_RIGHT, _______, _______,
    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F1,      KC_F2,      KC_F3,   KC_F4,    KC_F5,   _______,
    _______, _______, _______, _______, _______, _______, _______,    TG(_RAISE), _______, _______, _______,  _______
),

/* MOUSE
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      | MOUSE|      |      |      |Scr Up|Scr Do|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |But1  |      |      |But2  | Left | Down | Up   |Right |
 * `-----------------------------------------------------------------------------------'
 */

[_MOUSE] = LAYOUT_ortho_4x12(
    _______, _______, _______, _______, _______,    _______, _______, _______,    _______,    _______,       _______,     _______,
    _______, _______, _______, _______, _______,    _______, _______, _______,    _______,    _______,       _______,     _______,
    _______, _______, _______, _______, _______,    MOUSE,   _______, _______,    _______,    KC_MS_WH_DOWN, KC_MS_WH_UP, _______,
    _______, _______, _______, _______, KC_MS_BTN1, _______, _______, KC_MS_BTN2, KC_MS_LEFT, KC_MS_DOWN,    KC_MS_UP,    KC_MS_RIGHT
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

// original tri layer state
// layer_state_t layer_state_set_user(layer_state_t state) {
//  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
//}

// edited tri layer state to include it in userspace
// layer_state_t layer_state_set_keymap(layer_state_t state) {
//  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    
    case PHONE:
      if (record->event.pressed) {
          SEND_STRING("3931044785");
      }
      return false;
      break;
    case DESK:
      if (record->event.pressed) {
          SEND_STRING("desk" SS_LALT(";") "silviogulizia.com");
      }
      return false;
      break;
    case SGCOM:
      if (record->event.pressed) {
          SEND_STRING("https" SS_LSFT(".")SS_LSFT("7")SS_LSFT("7")"silviogulizia.com");
      }
      return false;
      break;
    case VIVERE:
      if (record->event.pressed) {
          SEND_STRING("https" SS_LSFT(".") SS_LSFT("7") SS_LSFT("7") "vivereintenzionalmente.com");
      }
      return false;
      break;
    
    case SVIV:
      if (record->event.pressed) {
          SEND_STRING("silvio" SS_LALT(";") "vivereintenzionalmente.com");
      }
      return false;
      break;
    
    case IT_SCCL:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
          register_code16(IT_COLN);
        } else {
          register_code16(IT_SCLN);
        }
      } else {
        unregister_code16(IT_COLN);
        unregister_code16(IT_SCLN);
      }
      return false;
      break;

    case IT_APDQ:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
          register_code16(IT_DQOT);
        } else {
          register_code16(IT_APOS);
        }
      } else {
        unregister_code16(IT_DQOT);
        unregister_code16(IT_APOS);
        }
      return false;
      break;
  
    case IT_CMLS:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
          unregister_code16(KC_LSFT);
          register_code16(IT_LESS);
	  register_code16(KC_LSFT);
        } else {
          register_code16(IT_COMM);
        }
      } else {
        unregister_code16(IT_LESS);
        unregister_code16(IT_COMM);
      }
      return false;
      break;
      
    case IT_DTMR:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
          register_code16(IT_MORE);
        } else {
          register_code16(IT_DOT);
        }
      } else {
        unregister_code16(IT_MORE);
        unregister_code16(IT_DOT);
      }
      return false;
      break;
      
    case IT_SLQS:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
          register_code16(IT_QST);
        } else {
          register_code16(IT_SLSH);
        }
      } else {
        unregister_code16(IT_QST);
        unregister_code16(IT_SLSH);
      }
      return false;
      break;
  }
  return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
}

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
