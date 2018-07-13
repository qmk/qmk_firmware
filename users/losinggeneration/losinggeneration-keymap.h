#ifndef LOSINGGENERATION_KEYMAP_H
#define LOSINGGENERATION_KEYMAP_H

#include "action_layer.h"
#include "eeconfig.h"
#include "losinggeneration-common.h"

/* Tap dance keycodes */
enum tap_dance_keycodes {
  TD_CTL_CTLALT = 0,
  TD_LGUI_RGUI,
  TD_LALT_RALT,
  TD_ADJUST,
};

/*
  Used to indicate a CTRL should be pressed on one press, or CTRL+ALT on
  a double tap
*/
void dance_ctl_ctlalt_each(qk_tap_dance_state_t *state, void *user_data) {
  register_code(KC_LCTL);
  if(state->count > 1) {
    register_code(KC_LALT);
  }
}

/* Used to release CTRL or the double tapped variant CTRL+ALT */
void dance_ctl_ctlalt_reset(qk_tap_dance_state_t *state, void *user_data) {
  unregister_code(KC_LCTL);
  if(state->count > 1) {
    unregister_code(KC_LALT);
  }
}

/*
  Set ADJUST layer on the first press and off after that.
  Each is used to make sure ADJUST activates as soon as it's pressed the first
  time.
*/
void dance_adj_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    layer_on(_ADJUST);
  } else {
    layer_off(_ADJUST);
  }
}

/* Set NUMPAD layer on second tap and MOUSE layer on 3rd */
void dance_adj_finish(qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 1: break;
    case 2:
      layer_on(_NUMPAD);
      break;
    case 3:
      layer_on(_MOUSE);
      break;
    default:
      reset_tap_dance(state);
      break;
  }
}

/* Turn off any layer that may have been tapped on */
void dance_adj_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 1:
      layer_off(_ADJUST);
      break;
    case 2:
      layer_off(_NUMPAD);
      break;
    case 3:
      layer_off(_MOUSE);
      break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CTL_CTLALT] = ACTION_TAP_DANCE_FN_ADVANCED(dance_ctl_ctlalt_each, NULL, dance_ctl_ctlalt_reset),
  [TD_LGUI_RGUI]  = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_RGUI),
  [TD_LALT_RALT]  = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_RALT),
  [TD_ADJUST]     = ACTION_TAP_DANCE_FN_ADVANCED(dance_adj_each, dance_adj_finish, dance_adj_reset),
};

/*
 * ,-----------------------------------------..-----------------------------------------.
 * |Adjust| Ctrl | Alt  | GUI  |Lower | Del  ||Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'`-----------------------------------------'
 */
#define BOTTOM_GRID_ROW \
  TD_ADJ  ,TD_CTL , TD_ALT , TD_GUI , LOWER  , KC_DEL , KC_SPC , RAISE  , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT

/*
 * ,-----------------------------------------..-----------------------------------------.
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space ||Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'`-----------------------------------------'
 */
#define BOTTOM_MIT_ROW \
  TD_ADJ  ,TD_CTL , TD_ALT , TD_GUI , LOWER  , KC_SPC , KC_SPC , RAISE  , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT

#ifdef USE_MIT_LAYOUT
#define BOTTOM_ROW BOTTOM_MIT_ROW

/*
 * ,-----------------------------------------..-----------------------------------------.
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 ||  F12 | PgUp | PgDn | Home | End  |  ⏹   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      | Mute | Vol- | Vol+ |  ⏯   |
 * `-----------------------------------------'`-----------------------------------------'
 */
#define BOTTOM_RAISE_LOWER_ROWS \
  _______, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_PGUP, KC_PGDN, KC_HOME, KC_END , KC_MSTP, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY

#else
#define BOTTOM_ROW BOTTOM_GRID_ROW

/*
 * ,-----------------------------------------..-----------------------------------------.
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 ||  F12 | PgUp | PgDn | Home | End  |  ⏹   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |      |      |      |      |      || Bksp |      | Mute | Vol- | Vol+ |  ⏯   |
 * `-----------------------------------------'`-----------------------------------------'
 */
#define BOTTOM_RAISE_LOWER_ROWS \
  _______, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_PGUP, KC_PGDN, KC_HOME, KC_END , KC_MSTP, \
  _______, _______, _______, _______, _______, KC_BSPC, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY
#endif


/*
 * ,-----------------------------------------..-----------------------------------------.
 * | Tab  |                                  ||                                  | Bksp |
 * `-----------------------------------------'`-----------------------------------------'
 */
#define STD_TAB_ROW(...) KC_TAB, __VA_ARGS__, KC_BSPC

/*
 * ,-----------------------------------------..-----------------------------------------.
 * | Esc  |                                  ||                                         |
 * `-----------------------------------------'`-----------------------------------------'
 */

#define STD_ESC_ROW(...) MT_ESC, __VA_ARGS__

/*
 * ,-----------------------------------------..-----------------------------------------.
 * | Shift|                                  ||                                  |Enter |
 * `-----------------------------------------'`-----------------------------------------'
 */
#define STD_LSFT_ROW(...) OSM_LSFT, __VA_ARGS__, MT_ENT

/* Qwerty
 * ,-----------------------------------------..-----------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  ||   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  ||   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  ||   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower | Del  ||Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'`-----------------------------------------'
 */
#define QWERTY_LAYER \
  STD_TAB_ROW( KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   ),           \
  STD_ESC_ROW( KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN , KC_QUOT), \
  STD_LSFT_ROW(KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH),           \
  BOTTOM_ROW

/* Colemak
 * ,-----------------------------------------.,-----------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  ||   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  ||   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  ||   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower | Del  ||Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'`-----------------------------------------'
 */
#define COLEMAK_LAYER \
  STD_TAB_ROW( KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   , KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN),           \
  STD_ESC_ROW( KC_A   , KC_R   , KC_S   , KC_T   , KC_D   , KC_H   , KC_N   , KC_E   , KC_I   , KC_O    , KC_QUOT), \
  STD_LSFT_ROW(KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH),           \
  BOTTOM_ROW

/* Workman
 * ,-----------------------------------------..-----------------------------------------.
 * | Tab  |   Q  |   D  |   R  |   W  |   B  ||   J  |   F  |   U  |   P  |   ;  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   H  |   T  |   G  ||   Y  |   N  |   E  |   O  |   I  |  "   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   M  |   C  |   V  ||   K  |   L  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower | Del  ||Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'`-----------------------------------------'
 */
#define WORKMAN_LAYER \
  STD_TAB_ROW( KC_Q   , KC_D   , KC_R   , KC_W   , KC_B   , KC_J   , KC_F   , KC_U   , KC_P   , KC_SCLN),           \
  STD_ESC_ROW( KC_A   , KC_S   , KC_H   , KC_T   , KC_G   , KC_Y   , KC_N   , KC_E   , KC_O   , KC_I    , KC_QUOT), \
  STD_LSFT_ROW(KC_Z   , KC_X   , KC_M   , KC_C   , KC_V   , KC_K   , KC_L   , KC_COMM, KC_DOT , KC_SLSH),           \
  BOTTOM_ROW

/* Dvorak
 * ,-----------------------------------------..-----------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  ||   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  ||   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  ||   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower | Del  ||Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'`-----------------------------------------'
 */
#define DVORAK_LAYER \
  STD_TAB_ROW( KC_QUOT, KC_COMM, KC_DOT , KC_P   , KC_Y   , KC_F   , KC_G   , KC_C   , KC_R   , KC_L),           \
  STD_ESC_ROW( KC_A   , KC_O   , KC_E   , KC_U   , KC_I   , KC_D   , KC_H   , KC_T   , KC_N   , KC_S , KC_SLSH), \
  STD_LSFT_ROW(KC_SCLN, KC_Q   , KC_J   , KC_K   , KC_X   , KC_B   , KC_M   , KC_W   , KC_V   , KC_Z),           \
  BOTTOM_ROW

/* Game (Qwerty without one shot modifiers & tap dancing)
 * ,-----------------------------------------..-----------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  ||   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  ||   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  ||   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space ||Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'`-----------------------------------------'
 */
#define GAME_LAYER \
  KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC, \
  KC_ESC , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_ENT , \
  MO_ADJ , KC_LCTL, KC_LALT, KC_LGUI, LOWER  , KC_SPC , KC_SPC , RAISE  , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT

/* Number pad
 * ,-----------------------------------------..-----------------------------------------.
 * | Tab  | XXX  | XXX  | XXX  | XXX  | XXX  || NLCK |   7  |  8   |   9  |  -   | BKSP |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Esc  | XXX  | XXX  | XXX  | XXX  | XXX  ||  *   |   4  |  5   |   6  |  +   | BKSP |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Shift | XXX  | XXX  | XXX  | XXX  | XXX  ||  /   |   1  |  2   |   3  | ENT  | XXX  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  | XXX  |Space ||Space |   0  |  0   |   .  | ENT  | XXX  |
 * `-----------------------------------------''-----------------------------------------'
 */
#define NUMPAD_LAYER \
  KC_TAB , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_NLCK, KC_P7  , KC_P8  , KC_P9  , KC_PMNS, KC_BSPC, \
  KC_ESC , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAST, KC_P4  , KC_P5  , KC_P6  , KC_PPLS, KC_BSPC, \
  KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSLS, KC_P1  , KC_P2  , KC_P3  , KC_PENT, XXXXXXX, \
  TD_ADJ , TD_CTL , TD_ALT , TD_GUI , XXXXXXX, KC_SPC , KC_SPC , KC_P0  , KC_P0  , KC_PDOT, KC_PENT, XXXXXXX

/* Mouse movement
 * ,-----------------------------------------..-----------------------------------------.
 * | Tab  | MB_1 | MB_3 | MB_2 | MB_4 | MB_5 || MA_0 | MB_1 | MB_3 | MB_2 | MB_4 | MB_5 |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Esc  | MW_L | MW_U | MW_D | MW_R | XXX  || MA_1 | M_LT | M_UP | M_DN | M_RT | XXX  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Shift | MA_0 | MA_1 | MA_2 | XXX  | XXX  || MA_2 | MW_L | MW_U | MW_D | MW_R | XXX  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  | XXX  |Space || XXX  | XXX  | XXX  |  XXX | XXX  | XXX  |
 * `-----------------------------------------''-----------------------------------------'
 */
#define MOUSE_LAYER \
  KC_TAB , MS_BTN1, MS_BTN3, MS_BTN2, MS_BTN4, MS_BTN5, MS_ACL0, MS_BTN1, MS_BTN3, MS_BTN2, MS_BTN4, MS_BTN5, \
  KC_ESC , MW_LEFT, MW_DOWN, MW_UP  , MW_RGHT, XXXXXXX, MS_ACL1, MS_LEFT, MS_DOWN, MS_UP  , MS_RGHT, XXXXXXX, \
  KC_LSFT, MS_ACL0, MS_ACL1, MS_ACL2, XXXXXXX, XXXXXXX, MS_ACL2, MW_LEFT, MW_DOWN, MW_UP  , MW_RGHT, XXXXXXX, \
  TD_ADJ , TD_CTL , TD_ALT , TD_GUI , XXXXXXX, KC_SPC , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

/* Lower
 * ,-----------------------------------------..-----------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  ||   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  ||  F6  |   _  |   +  |      |   \  |  |   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 ||  F12 | PgUp | PgDn | Home | End  |  ⏹   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      | Mute | Vol- | Vol+ |  ⏯   |
 * `-----------------------------------------'`-----------------------------------------'
 */
#define LOWER_LAYER \
  KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_DEL , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  BOTTOM_RAISE_LOWER_ROWS

/* Raise
 * ,-----------------------------------------..-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  ||  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 ||  F12 | PgUp | PgDn | Home | End  |  ⏹   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      | Mute | Vol- | Vol+ |  ⏯   |
 * `-----------------------------------------''-----------------------------------------'
 */
#define RAISE_LAYER \
  KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC, \
  KC_DEL , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS, \
  BOTTOM_RAISE_LOWER_ROWS

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_workman[][2]    = SONG(PLOVER_SOUND);
#else
float tone_qwerty;
float tone_dvorak;
float tone_colemak;
float tone_workman;
#define PLAY_SONG(tone)
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  layer_state_set(default_layer);
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        PLAY_SONG(tone_qwerty);
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        PLAY_SONG(tone_colemak);
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case WORKMAN:
      if (record->event.pressed) {
        PLAY_SONG(tone_workman);
        persistent_default_layer_set(1UL<<_WORKMAN);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        PLAY_SONG(tone_dvorak);
        persistent_default_layer_set(1UL<<_DVORAK);
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

#endif
