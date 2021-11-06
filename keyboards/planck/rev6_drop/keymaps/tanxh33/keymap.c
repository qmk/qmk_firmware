#include QMK_KEYBOARD_H
#include "muse.h"

/*
enum planck_layers {
	_COLEMAK,
	_QWERTY,
	_NAV,
	_SYMBOL,
	_NUMBER,
  _FN,
	_MEDIA,
	_ADJUST
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_4x12(KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_DEL, MO(2), KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_BSPC, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LCTL, MO(6), KC_LGUI, KC_LALT, MO(3), KC_SPC, KC_SPC, MO(4), MO(5), KC_NO, KC_NO, KC_ENT),
	[1] = LAYOUT_ortho_4x12(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL, MO(2), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_BSPC, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LCTL, MO(6), KC_LGUI, KC_LALT, MO(3), KC_SPC, KC_SPC, MO(4), MO(5), KC_NO, KC_NO, KC_ENT),
	[2] = LAYOUT_ortho_4x12(KC_NO, KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_DEL, KC_INS, KC_TRNS, KC_LALT, KC_CAPS, KC_LSFT, KC_LCTL, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_BSPC, KC_NO, KC_NO, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_ENT, KC_ENT, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO),
	[3] = LAYOUT_ortho_4x12(KC_ESC, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, KC_GRV, KC_NO, KC_NO, KC_LSFT, KC_LCTL, KC_NO, KC_QUOT, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSLS, KC_RSFT, KC_NO, KC_NO, KC_NO, KC_LALT, KC_NO, KC_NO, KC_NO, MO(7), KC_NO, KC_NO, KC_NO, KC_ENT),
	[4] = LAYOUT_ortho_4x12(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, KC_NO, KC_NO, KC_NO, KC_LSFT, KC_LCTL, KC_NO, KC_PPLS, KC_4, KC_5, KC_6, KC_PMNS, KC_BSPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PAST, KC_1, KC_2, KC_3, KC_PSLS, KC_RSFT, KC_NO, KC_NO, KC_NO, KC_LALT, MO(7), KC_ENT, KC_ENT, KC_NO, KC_NO, KC_DOT, KC_EQL, KC_ENT),
	[5] = LAYOUT_ortho_4x12(KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_NO, KC_NO, KC_NO, KC_LSFT, KC_LCTL, KC_NO, KC_NO, KC_NO, KC_NO, KC_F11, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LALT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[6] = LAYOUT_ortho_4x12(KC_NO, KC_NO, KC_NO, KC_BRID, KC_BRIU, KC_NO, KC_NO, KC_BTN1, KC_MS_U, KC_BTN2, KC_MYCM, LCA(KC_DEL), KC_NO, KC_NO, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_CALC, KC_PSCR, KC_NO, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO, KC_ACL0, KC_ACL1, KC_ACL2, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[7] = LAYOUT_ortho_4x12(RESET, DEBUG, RGB_TOG, RGB_RMOD, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, KC_NO, KC_NO, AU_TOG, MU_TOG, MU_MOD, MUV_DE, MUV_IN, KC_NO, DF(0), DF(1), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TERM_ON, TERM_OFF, MI_ON, MI_OFF, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]      = SONG(QWERTY_SOUND);
float tone_colemak[][2]     = SONG(COLEMAK_SOUND);
float tone_media[][2]       = SONG(SCROLL_LOCK_ON_SOUND);
float tone_pcb[][2]         = SONG(NUM_LOCK_ON_SOUND);
float caps_on[][2]          = SONG(FAMILY_MART_ON);
float caps_off[][2]         = SONG(FAMILY_MART_OFF);
#endif

#ifdef AUDIO_ENABLE
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DF(0):
      if (record->event.pressed) {
        PLAY_SONG(tone_colemak);
        set_single_persistent_default_layer(0);
      }
      return false;
      break;
    case DF(1):
      if (record->event.pressed) {
        PLAY_SONG(tone_qwerty);
        set_single_persistent_default_layer(1);
      }
      return false;
      break;
    case MO(6):
      if (record->event.pressed) {
        PLAY_SONG(tone_media);
      }
      break;
    case MO(7):
      if (record->event.pressed) {
        PLAY_SONG(tone_pcb);
      }
      break;
  }
  return true;
}
#endif

bool led_update_user(led_t led_state) {
  #ifdef AUDIO_ENABLE
  static uint8_t caps_state = 0;
  if (caps_state != led_state.caps_lock) {
      led_state.caps_lock ? PLAY_SONG(caps_on) : PLAY_SONG(caps_off);
      caps_state = led_state.caps_lock;
  }
  #endif
  return true;
}
