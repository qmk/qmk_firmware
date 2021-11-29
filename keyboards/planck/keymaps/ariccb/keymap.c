 /* Copyright 2021 Aric Crosson Bouwers 
  * 
  * This program is free software: you can redistribute it and/or modify 
  * it under the terms of the GNU General Public License as published by 
  * the Free Software Foundation, either version 2 of the License, or 
  * (at your option) any later version. 
  * 
  * This program is distributed in the hope that it will be useful, 
  * but WITHOUT ANY WARRANTY; without even the implied warranty of 
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
  * GNU General Public License for more details. 
  * 
  * You should have received a copy of the GNU General Public License 
  * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
  */ 

#include QMK_KEYBOARD_H
#include "muse.h"

#define AUDIO_INIT_DELAY
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers. 
#define _QWERTY 0
#define _COLEMAK 1
#define _LOWER 2  
#define _RAISE 3
#define _NUMPAD 4
#define _FN 5
#define _ADJUST 6
#define MICMUTE LCTL(LSFT(KC_M))
#define LCTRL_F1 MT(MOD_LCTL, KC_F1)
#define LSFT_F2 MT(MOD_LSFT, KC_F2)
#define LALT_F2 MT(MOD_LALT, KC_F3)

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
  FN,
  ADJUST,
  NUMPAD,
  EXT_NUM
}; 

// This is a completely modified layout that stikes a balance between muscle memory for keys, where I was coming from a standard
// Qwerty keyboard, and efficiency gained by using layers. I've switched tab and esc because it's more natural to me this way, and
// added layer switch on hold functionality for each key. Enter has moved to the key beside LOWER, to allow usage while still having
// the right hand on the mouse.

// Lower incorporates a numpad which falls in line with the numberkeys at the top as well - my muscle memory appreciates both layouts.
// I've also included ctr z,x,c,v, and f shortcuts to allow more comfy usage with thumb instead of contorting to use ctrl at bottom left. 

// Upper has a layout that's optimized for coding symbols, and has a few duplicates just to entertain my existing muscle memory. Some 
// things apparently can't be un-taught.

// CAPS has moved to the Fn layer, and a few additional shortcut modifiers like CTRL_ALT_UP and DOWN for adding additional cursors in VSCode.
// Play/Pause has a prime spot on the base layer, and the Fn version skips to next track, with left and right on the base changing to Down and Up
// on the Fn layer. Volume Up and Volume Down live on bottom left of Fn Layer.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* MIT Layout (QWERTY layer)
 *
 * ,-----------------------------------------------------------------------.
 * |FN,ESC|  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |Bspc|
 * |-----------------------------------------------------------------------|
|HYPER,Tab|  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  ' |
 * |-----------------------------------------------------------------------|
 * |shift |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |  \ |
 * |-----------------------------------------------------------------------|
 * | Ctl  | Win | Alt |Enter|LOWER|   Space   |RAISE|Menu |Play | Lft |Rght|
 * `-----------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid( /* QWERTY */
    LT(_FN, KC_ESC),      KC_Q,     KC_W,    KC_E,   KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
    MT(MOD_HYPR, KC_TAB), KC_A,     KC_S,    KC_D,   KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, 
    KC_LSFT,              KC_Z,     KC_X,    KC_C,   KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS, 
    KC_LCTL,              KC_LGUI,  KC_LALT, KC_ENT, LOWER, KC_SPC, KC_SPC, RAISE, KC_APP,  KC_MPLY, KC_LEFT, KC_RGHT
 ),

 /* MIT Layout (COLEMAK layer)
 *
 * ,-----------------------------------------------------------------------.
 * |FN,ESC|  q  |  w  |  f  |  p  |  b  |  j  |  l  |  u  |  y  |  ;  |Bspc|
 * |-----------------------------------------------------------------------|
|HYPER,Tab|  a  |  r  |  s  |  t  |  g  |  h  |  n  |  e  |  i  |  o  |  ' |
 * |-----------------------------------------------------------------------|
 * |shift |  z  |  x  |  c  |  d  |  v  |  k  |  m  |  ,  |  .  |  /  |  \ |
 * |-----------------------------------------------------------------------|
 * | Ctl  | Win | Alt |Enter|LOWER|   Space   |RAISE|Menu |Play | Lft |Rght|
 * `-----------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid( /* COLEMAK */
    LT(_FN, KC_ESC),      KC_Q,    KC_W,    KC_F,   KC_P,  KC_B,   KC_J,   KC_L,  KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    MT(MOD_HYPR, KC_TAB), KC_A,    KC_R,    KC_S,   KC_T,  KC_G,   KC_M,   KC_N,  KC_E,    KC_I,    KC_O,    KC_QUOT, 
    KC_LSFT,              KC_Z,    KC_X,    KC_C,   KC_D,  KC_V,   KC_K,   KC_H,  KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS, 
    KC_LCTL,              KC_LGUI, KC_LALT, KC_ENT, LOWER, KC_SPC, KC_SPC, RAISE, KC_APP,  KC_MPLY, KC_LEFT, KC_RGHT
 ),

/* MIT Layout (RAISED_LAYER)
 *
 * ,-----------------------------------------------------------------------.
 * |  ~  |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  =  |  :  | Bksp|
 * |-----------------------------------------------------------------------|
 * |  `  |  _  |  <  |  [  |  {  |  (  |  )  |  }  |  ]  |  >  |  -  |  "  |
 * |-----------------------------------------------------------------------|
 * |     |     |     |     |     |  %  |  ^  |  #  |  $  |  +  |  ?  |  |  |
 * |-----------------------------------------------------------------------|
 * |     |     |     |     |     |           |     |     |     |     |     |
 * `-----------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid( /* RAISE */
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_EQL,  KC_COLN, KC_BSPC,
  KC_GRV,  KC_UNDS, KC_LT,   KC_LBRC, KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_RBRC, KC_GT,   KC_MINS, KC_DQUO, 
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PERC, KC_CIRC, KC_HASH, KC_DLR,  KC_PPLS, KC_QUES, KC_PIPE, 
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* MIT Layout (LOWER)
 *.
 * ,-----------------------------------------------------------------------.
 * |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  | Bksp|
 * |-----------------------------------------------------------------------|
 * |     |     |     |     |ctr_f|     |  M  |  4  |  5  |  6  |  -  |  +  |
 * |-----------------------------------------------------------------------|
 * |     |ctr_z|ctr_x|ctr_c|ctr_v|  C  |  @  |  1  |  2  |  3  |  /  |  *  |
 * |-----------------------------------------------------------------------|
 * |     |     |     |NUMPAD|    |            |  0  |  0  |  .  |  =  |Enter|
 * `-----------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid( /* LOWER */
  KC_GRV,  KC_1,       KC_2,       KC_3,       KC_4,       KC_5,    KC_6,    KC_7,  KC_P8, KC_9,    KC_0,    KC_BSPC, 
  KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    LCTL(KC_F), KC_TRNS, KC_M,    KC_P4, KC_P5, KC_P6,   KC_PMNS, KC_PPLS, 
  KC_TRNS, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_C,    KC_AT,   KC_P1, KC_P2, KC_P3,   KC_PSLS, KC_PAST, 
  KC_TRNS, KC_TRNS,    KC_TRNS,    NUMPAD,     KC_TRNS,    KC_TRNS, KC_TRNS, KC_P0, KC_P0, KC_PDOT, KC_EQL,  KC_PENT
),

/* MIT Layout (NUMPAD)
 *.
 * ,-----------------------------------------------------------------------.
 * |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  | Bksp|
 * |-----------------------------------------------------------------------|
 * |     |     |     |     |ctr_f|     |  M  |  4  |  5  |  6  |  -  |  +  |
 * |-----------------------------------------------------------------------|
 * |     |ctr_z|ctr_x|ctr_c|ctr_v|  C  |  @  |  1  |  2  |  3  |  /  |  *  |
 * |-----------------------------------------------------------------------|
 * |     |     |     |     | Exit|            |  0  |  0  |  .  |  = |Enter|
 * `-----------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_planck_grid( /* LOWER */
  KC_GRV,  KC_1,       KC_2,        KC_3,       KC_4,       KC_5,    KC_6,    KC_7,  KC_P8, KC_9,    KC_0,    KC_BSPC, 
  KC_TRNS, KC_TRNS,    KC_TRNS,     KC_TRNS,    LCTL(KC_F), KC_TRNS, KC_M,    KC_P4, KC_P5, KC_P6,   KC_PMNS, KC_PPLS, 
  KC_TRNS, LCTL(KC_Z), LCTL(KC_X),  LCTL(KC_C), LCTL(KC_V), KC_C,    KC_AT,   KC_P1, KC_P2, KC_P3,   KC_PSLS, KC_PAST, 
  KC_TRNS, KC_TRNS,    KC_TRNS,     KC_TRNS,    EXT_NUM,    KC_TRNS, KC_TRNS, KC_P0, KC_P0, KC_PDOT, KC_EQL,  KC_PENT
),

/* MIT Layout (FN LAYER)
 *
 * ,----------------------------------------------------------------------------.
 * |    |LCTRL_F1|LSFT_F2|LALT_F3| F4  |    |    |home | up   | end |PrtScr|del |
 * |----------------------------------------------------------------------------|
 * |    |  F5    |  F6   |  F7   | F8  |    |    |left | down |right|ScrLck|Ins |
 * |----------------------------------------------------------------------------|
 * |    |  F9    | F10   | F11   | F12 |    |    |pgup |LCA_up| pgdn|      |CAPS|
 * |----------------------------------------------------------------------------|
 * |    | MICMUTE| Calc  |  MUTE |Vol- |         |Vol+ |LCA_dn| next|      |    |
 * `----------------------------------------------------------------------------'
 */
[_FN] = LAYOUT_planck_grid( /* FUNCTION */
  KC_TRNS, LCTL_T(KC_F1), LSFT_T(KC_F2), LALT_T(KC_F3), KC_F4,   KC_TRNS, KC_TRNS, KC_HOME, KC_UP,        KC_END,   KC_PSCR, KC_DEL,
  KC_TRNS, KC_F5,         KC_F6,         KC_F7,         KC_F8,   KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN,      KC_RGHT,  KC_SLCK, KC_INS, 
  KC_VOLU, KC_F9,         KC_F10,        KC_F11,        KC_F12,  KC_TRNS, KC_TRNS, KC_PGUP, LCA(KC_UP),   KC_PGDN,  KC_TRNS, KC_CAPS, 
  KC_VOLD, MICMUTE,       KC_CALC,       KC_MUTE,       KC_VOLD, KC_TRNS, KC_TRNS, KC_VOLU, LCA(KC_DOWN), KC_MNXT,  KC_TRNS, KC_TRNS
),

/* MIT Layout (ADJUST)
 *
 * ,----------------------------------------------------------------------------.
 * |reset| Ms3 | Ms2 |MsUp | Ms1  |  Hue+|   Hue-| Sat+| Sat-|Brt+ |Brt- |RGB Tg|
 * |----------------------------------------------------------------------------|
 * |debug| MWL | MsL |MDn  |MsR   |      |       |     |     |     |     |RGBMod|
 * |----------------------------------------------------------------------------|
 * |     |     |MWUp |NWDn |      |QWERTY|COLEMAK|MI_ON|MI_OF|MU_ON|MU_OF|MU_Mod|
 * |----------------------------------------------------------------------------|
 * |     |     |     |SLEEP|      |              |     |     |     |AU_ON|AU_OF |
 * `----------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid( /* ADJUST LAYER */
  RESET,   KC_BTN3, KC_BTN2, KC_MS_U, KC_BTN1, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_TOG, 
  DEBUG,   KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RGB_MOD, 
  KC_TRNS, KC_NO,   KC_NO,   KC_WH_U, KC_WH_D, QWERTY,  COLEMAK, MI_ON,   MI_OFF,  MU_ON,   MU_OFF,  MU_MOD,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_SLEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, AU_ON,   AU_OFF
)
};

#ifdef AUDIO_ENABLE
float layerswitch_song[][2] = SONG(PLANCK_SOUND);   
float tone_startup[][2]     = SONG(STARTUP_SOUND);
float tone_qwerty[][2]      = SONG(QWERTY_SOUND);
float tone_colemak[][2]     = SONG(COLEMAK_SOUND);
float music_scale[][2]      = SONG(MUSIC_SCALE_SOUND);
float tone_goodbye[][2]     = SONG(GOODBYE_SOUND);

#endif
 
layer_state_t layer_state_set_user(layer_state_t state) {
 
	static bool is_this_layer_on = false;
	if (layer_state_cmp(state, 4) != is_this_layer_on) {
		is_this_layer_on = layer_state_cmp(state, 4);
		if (is_this_layer_on) {
			PLAY_SONG(layerswitch_song);
		}
		else {
			stop_all_notes();
		}
	}
 
	switch (get_highest_layer(state)) {
		case _ADJUST:
			rgblight_setrgb (0xFF,  0x00, 0x00);
			break;
		case _LOWER:
			rgblight_setrgb (0x00,  0x00, 0xFF);
			break;
    case _NUMPAD:
			rgblight_setrgb (0x00,  0x00, 0xFF);
			break;
		case _RAISE:
			rgblight_setrgb (0x7A,  0x00, 0xFF);
			break;
		case _FN:
			rgblight_setrgb (0x00,  0xFF, 0x00);
			break;
		default: //  for any other layers, or the default layer
			rgblight_setrgb (0xFF,  0xFF, 0xFF);
			break;
		}
	  return state;
 
}

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case NUMPAD:
      if (record->event.pressed) {
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_NUMPAD);
        #ifdef AUDIO_ENABLE
          PLAY_SONG(layerswitch_song);
        #endif
      }
      return false;
      break;
    case EXT_NUM:
      if (record->event.pressed) {
        layer_off(_NUMPAD);
        #ifdef AUDIO_ENABLE
          PLAY_SONG(layerswitch_song);
        #endif
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistant_default_layer_set(1UL<<_COLEMAK);
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