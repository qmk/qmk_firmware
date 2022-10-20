/*
 *
 * An Italian ANSI layout
 * Version 0.3
 *
 * Created by Silvio Gulizia on the basis of the default Planck keymap.
 * Thanks to SomeBuddyOnReddit, gepeirl, fauxpark, BXO511, drashna, and ridingqwerty.
 *
 * The layout is based on the original Planck layout when used with language set to Italian on your Mac.
 * Accented vowels have been moverd on RAISE ("�", "�", and "�") and LOWER ("�", "�", and "�")
 *
 */

#include QMK_KEYBOARD_H
#include "muse.h"
#include "keymap_italian_mac_ansi.h"
#include "sigul.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |Tab/FN|   Q  |   W  |  E   |  R   |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Esc/FN|   A  |   S  |  D  |   F   |   G  |   H  |   J  |   K  |   L  |  ;:  |  '"  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |  C   |  V   | MS/B |   N  |   M  |  ,<  |  .>  |  /!  |S/Ent |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | FN   | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
    TABFN,   IT_Q,    IT_W,    IT_E,      IT_R,  IT_T,    IT_Y,    IT_U,  IT_I,    IT_O,    IT_P,    KC_BSPC,
    ESCFN,   IT_A,    IT_S,    IT_D,      IT_F,  IT_G,    IT_H,    IT_J,  IT_K,    IT_L,    IT_SCCL, IT_APDQ,
    KC_LSFT, IT_Z,    IT_X,    IT_C,      IT_V,  MS_B,    IT_N,    IT_M,  IT_CMLS, IT_DTMR, IT_SLQS, MT(MOD_RSFT, KC_ENT),
    FN,      KC_LCTL, KC_LALT, KC_LGUI,   LOWER, KC_SPC,  KC_SPC,  RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  ~   |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |  (   |  )   | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Enter |  F1  |  F2  |  F3  |  F4  |  F5  |      |   _  |   =  |  �   |  �   |  �   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  |      |NUMPAD|   �  |   �  |  {   |  }   |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */

[_LOWER] = LAYOUT_ortho_4x12(
    IT_TILD,  IT_EXLM, IT_AT,   IT_HASH, IT_DLR,  IT_PERC, IT_CIRC, IT_AMPR,    IT_ASTR, IT_LPRN,    IT_RPRN, KC_DEL,
    KC_ENT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, S(IT_MINS), IT_EQL,  S(IT_EGRV), IT_OGRV, IT_AGRV,
    _______,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   _______, NUMPAD,  S(IT_UGRV), IT_PLMN, IT_LCBR,    IT_RCBR, IT_PIPE,
    _______,  _______, _______, _______, _______, _______, _______, _______,    KC_MNXT, KC_VOLD,    KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | SGCOM| DESK |      |      |      |   -  |   +  |   �  |   �  |  �   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Caps |      | PHONE| SVIV |VIVERE|      |NUMPAD|      |      |  [   |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
    IT_GRV,   IT_1,    IT_2,    IT_3,	 IT_4,    IT_5,    IT_6,    IT_7,    IT_8,    IT_9,    IT_0,    _______,
    _______,  _______, SECRET0, SECRET1, _______, _______, _______, IT_MINS, IT_PLUS, IT_EGRV, IT_IGRV, IT_UGRV,
    KC_CAPS,  _______, SECRET2, SECRET3, SECRET4, _______, NUMPAD,  SECRET5, _______, IT_LBRC, IT_RBRC, IT_BSLS,
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
    _______, DF(QWERTY), _______, EE_CLR,  QK_BOOT, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,    _______, DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______,
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
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_FN] = LAYOUT_ortho_4x12(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_DEL,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
),

/* MOUSE
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | But1 |Scr Up|Scr Do| But2 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Left | Down | Up   |Right |
 * `-----------------------------------------------------------------------------------'
 */

[_MOUSE] = LAYOUT_ortho_4x12(
    _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,       _______,     _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,       _______,     _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_BTN1, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_BTN2,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_LEFT, KC_MS_DOWN,    KC_MS_UP,    KC_MS_RIGHT
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif


bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
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
    return true;
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
