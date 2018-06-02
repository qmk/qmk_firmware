/* to do
 * 1) how to move to default layer? TO(0)?
 * 2) transfer keycodes over from pc, mac and ios layouts
 * 3) pick numlock sounds
 * 4) make meh key the menu key
 */
/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

#define RA_TAB LT(_RAISE, KC_TAB)
#define MRA_TAB LT(_MRAISE, KC_TAB)
#define LO_MIN LT(_LOWER, KC_MINS)
#define DV_LOW TD(TD_DV)
#define MDV_LOW TD(TD_MDV)
#define AD_MEH TD(TD_MA)
#define RA_CTL TD(TD_CR)
#define RA_GUI TD(TD_GMR)
#define LO_ALT TD(TD_AL)
#define CSHIFT TD(TD_SFT_CAPS)
#define P_ALL LCTL(KC_A)
#define M_ALL LGUI(KC_A)
#define P_CUT LCTL(KC_X)
#define M_CUT LGUI(KC_X)
#define P_CPY LCTL(KC_C)
#define M_CPY LGUI(KC_C)
#define P_PSTE LCTL(KC_V)
#define M_PSTE LGUI(KC_V)
#define P_UNDO LCTL(KC_Z)
#define M_UNDO LGUI(KC_Z)
#define P_REDO LCTL(KC_Y)
#define M_REDO LGUI(LSFT(KC_Z))
#define P_FIND LCTL(KC_F)
#define M_FIND LGUI(KC_F)
#define M_HOME LGUI(KC_LEFT)
#define M_END LGUI(KC_RGHT)
#define M_PSCR LGUI(LSFT(KC_3))

enum planck_layers {
  _DVORAK,
  _MDVORAK,
  _MUSICL,
  _LOWER,
  _RAISE,
  _MRAISE,
  _ADJUST
};

enum planck_keycodes {
  DVORAK = SAFE_RANGE,
  MDVORAK,
  MUSICL,
  LOWER,
  RAISE,
  BACKLIT,
  NUMLOCK
};

//Tap Dance Declarations

enum {
  TD_DV,       //Dvorak layer tap, Lower hold
  TD_MDV,      //Mac Dvorak layer tap, lower hold
  TD_SFT_CAPS, //Capslock tap, shift hold
  TD_AL,       //Lower layer tap, alt hold
  TD_CR,       //Raise layer tap, ctrl hold
  TD_GMR,      //Mac Raise layer tap, gui hold
  TD_MA        //Adjust layer tap, meh hold
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Dvorak (0 PC, 1 mac)
   *      ,-----------------------------------------------------------------------------------.
   *      | Esc  |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  /   |
   *      |------+------+------+------+------+-------------+------+------+------+------+------|
   *      | Tab  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  -   |
   *      |------+------+------+------+------+------|------+------+------+------+------+------|
   *Dvorak|alpha |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  | Up   |
   *      |------+------+------+------+------+------+------+------+------+------+------+------|
   *      | GUI  |Adjust|Raise |Lower |Caps  |Space | Enter| Bksp | Del  | Left | Down |Right |
   *      `-----------------------------------------------------------------------------------'
   *               Meh    Ctrl   Alt   Shift
   */
  [_DVORAK] = {
    {KC_ESC,  KC_QUOT, KC_COMM, KC_DOT, KC_P,   KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH},
    {RA_TAB,  KC_A,    KC_O,    KC_E,   KC_U,   KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    LO_MIN},
    {DV_LOW,  KC_SCLN, KC_Q,    KC_J,   KC_K,   KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_UP},
    {KC_LGUI, AD_MEH,  RA_CTL,  LO_ALT, CSHIFT, KC_SPC,  KC_ENT,  KC_BSPC, KC_DEL,  KC_LEFT, KC_RGHT, KC_DOWN}
  },

  [_MDVORAK] = {
    {KC_ESC,  KC_QUOT, KC_COMM, KC_DOT, KC_P,   KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH},
    {MRA_TAB, KC_A,    KC_O,    KC_E,   KC_U,   KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    LO_MIN},
    {MDV_LOW, KC_SCLN, KC_Q,    KC_J,   KC_K,   KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_UP},
    {KC_LCTL, AD_MEH,  RA_GUI,  LO_ALT, CSHIFT, KC_SPC,  KC_ENT,  KC_BSPC, KC_DEL,  KC_LEFT, KC_RGHT, KC_DOWN}
  },

  /* Music Layer (2)
   * ,-----------------------------------------------------------------------------------.
   * |NUMLK |   -  |   7  |   8  |   9  |   /  |   @  |   [  |   ]  |   &  |   ~  |   %  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |   `  |   +  |   4  |   5  |   6  |   *  |   \  |   (  |   )  |   !  |   ^  |      |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |   0  |   1  |   2  |   3  |   =  |   $  |   {  |   }  |   |  |   #  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-----------------------------------------------------------------------------------'
   */

  [_MUSICL] = {
    {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
    {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
    {MU_OFF,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX},
    {MU_ON,   TO(6),   TO(0),   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX}
  },

/* Lower, minus hold, alpha hold (3)
 * ,-----------------------------------------------------------------------------------.
 * |NUMLK |   -  |   7  |   8  |   9  |   /  |   @  |   [  |   ]  |   &  |   ~  |   %  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   `  |   +  |   4  |   5  |   6  |   *  |   \  |   (  |   )  |   !  |   ^  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   0  |   1  |   2  |   3  |   =  |   $  |   {  |   }  |   |  |   #  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {NUMLOCK, KC_MINS, KC_KP_7, KC_KP_8, KC_KP_9, KC_SLSH, KC_AT,   KC_LBRC, KC_RBRC, KC_AMPR, KC_TILD, KC_PERC},
  {KC_GRV,  KC_PLUS, KC_KP_4, KC_KP_5, KC_KP_6, KC_ASTR, KC_BSLS, KC_LPRN, KC_RPRN, KC_EXLM, KC_CIRC, _______},
  {_______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_EQL,  KC_DLR,  KC_LCBR, KC_RCBR, KC_PIPE, KC_HASH, _______},
  {_______, _______, _______, KC_LALT, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Raise, tab hold (4 PC, 5 mac)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      | Home | Up   | End  |Pg Up |VolUp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |SelAll| Cut  | Copy |Paste |      |      | Left | Down |Right |Pg Dn |VolDn |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Undo | Redo | Find |PrtScr|Mute  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_VOLU},
  {_______, P_ALL,   P_CUT,   P_CPY,   P_PSTE,  XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_VOLD},
  {_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, P_UNDO,  P_REDO,  P_FIND,  KC_PSCR, KC_MUTE},
  {_______, _______, KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

[_MRAISE] = {
  {_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, M_HOME,  KC_UP,   M_END,   KC_PGUP, KC__VOLUP},
  {_______, M_ALL,   M_CUT,   M_CPY,   M_PSTE,  XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC__VOLDOWN},
  {_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, M_UNDO,  M_REDO,  M_FIND,  M_PSCR,  KC__MUTE},
  {_______, _______, KC_LGUI, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Adjust (Lower + Raise) (6)
 * ,-----------------------------------------------------------------------------------.
 * |Sleep | Reset| Music| mac  | PC   |      |      |  F1  |  F2  |  F3  |  F4  |VolUp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|      |      |  F5  |  F6  |  F7  |  F8  |VolDn |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|      |      |      |      |  F9  |  F10 |  F11 |  F12 |Mute  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {KC_SLEP, RESET,   MUSICL,  MDVORAK, DVORAK,  XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______},
  {_______, XXXXXXX, XXXXXXX, AU_ON,   AU_OFF,  XXXXXXX, XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______},
  {_______, MUV_DE,  MUV_IN,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______},
  {_______, KC_MEH,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
  float tone_caps_off[][2]   = SONG(NUM_LOCK_OFF_SOUND);
  float tone_caps_on[][2]    = SONG(CAPS_LOCK_ON_SOUND);
  float tone_nums_off[][2]   = SONG(SCROLL_LOCK_OFF_SOUND);
  float tone_nums_on[][2]    = SONG(COIN_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
        layer_off(_MDVORAK);
      }
      return false;
      break;
    case MDVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_MDVORAK);
        layer_off(_DVORAK);
      }
      return false;
      break;
    case MUSICL:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_MUSICL);
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
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        PORTE &= ~(1<<6);
      } else {
        unregister_code(KC_RSFT);
        PORTE |= (1<<6);
      }
      return false;
      break;
    case NUMLOCK:
      if (record->event.pressed) {
        register_code (KC_NLCK);
    	  if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)){
    		    #ifdef AUDIO_ENABLE
    			     PLAY_SONG(tone_nums_off);
    		    #endif
        } else {
          #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_nums_on);
          #endif
        }
      } else {
          unregister_code(KC_NLCK);
      }
      return false;
      break;
  }
  return true;
}


//layer changes backlight level
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _RAISE:
        #ifdef BACKLIGHT_ENABLE
        backlight_set(1);
        #endif
        break;
    case _MRAISE:
        #ifdef BACKLIGHT_ENABLE
        backlight_set(1);
        #endif
        break;
    case _LOWER:
        #ifdef BACKLIGHT_ENABLE
        backlight_set(2);
        #endif
        break;
    case _ADJUST:
        #ifdef BACKLIGHT_ENABLE
        backlight_set(0);
        #endif
        break;
    case _MUSICL:
        #ifdef BACKLIGHT_ENABLE
        backlight_set(0);
        #endif
        break;
    default: //  for any other layers, or the default layer
        #ifdef BACKLIGHT_ENABLE
        backlight_set(3);
        #endif
        break;
    }
  return state;
}

//Tap Dance Definitions
typedef struct {
  bool alt;
  bool finished_once;
} td_dv_state_t;

typedef struct {
  bool alt;
  bool finished_once;
} td_mdv_state_t;

typedef struct {
  bool alt;
  bool finished_once;
} td_sftcaps_state_t;

typedef struct {
  bool alt;
  bool finished_once;
} td_alb_state_t;

typedef struct {
  bool alt;
  bool finished_once;
} td_cr_state_t;

typedef struct {
  bool alt;
  bool finished_once;
} td_gmr_state_t;

typedef struct {
  bool alt;
  bool finished_once;
} td_ma_state_t;

//TD Lower on hold, dvorak layer on tap
void _td_dv_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_dv_state_t *s = (td_dv_state_t *)user_data;

  if (s->finished_once)
    return;

  s->finished_once = true;
  if (state->pressed) {
    s->alt = true;
    layer_on(_LOWER);
  } else {
    s->alt = false;
	layer_on(_DVORAK);
  layer_off(_MDVORAK);
	layer_off(_LOWER);
	layer_off(_RAISE);
	layer_off(_ADJUST);
  }
}

void _td_dv_reset (qk_tap_dance_state_t *state, void *user_data) {
  td_dv_state_t *s = (td_dv_state_t *)user_data;

  if (s->alt) {
	layer_off(_LOWER);
  }

  s->finished_once = false;
}

//TD Lower on hold, mdvorak layer on tap
void _td_mdv_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_mdv_state_t *s = (td_mdv_state_t *)user_data;

  if (s->finished_once)
    return;

  s->finished_once = true;
  if (state->pressed) {
    s->alt = true;
    layer_on(_LOWER);
  } else {
    s->alt = false;
  layer_off(_DVORAK);
  layer_on(_MDVORAK);
	layer_off(_LOWER);
	layer_off(_MRAISE);
	layer_off(_ADJUST);
  }
}

void _td_mdv_reset (qk_tap_dance_state_t *state, void *user_data) {
  td_mdv_state_t *s = (td_mdv_state_t *)user_data;

  if (s->alt) {
	layer_off(_LOWER);
  }

  s->finished_once = false;
}

//TD shift on hold, capslock on tap
void _td_sftcaps_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_sftcaps_state_t *s = (td_sftcaps_state_t *)user_data;

  if (s->finished_once)
    return;

  s->finished_once = true;
  if (state->pressed) {
    s->alt = true;
    register_code (KC_LSFT);
  } else {
    s->alt = false;
    register_code (KC_CAPS);
	if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)){
		#ifdef AUDIO_ENABLE
			PLAY_SONG(tone_caps_off);
		#endif
	} else {
		#ifdef AUDIO_ENABLE
			PLAY_SONG(tone_caps_on);
		#endif
	}
  }
}

void _td_sftcaps_reset (qk_tap_dance_state_t *state, void *user_data) {
  td_sftcaps_state_t *s = (td_sftcaps_state_t *)user_data;

  if (s->alt) {
    unregister_code (KC_LSFT);
  } else {
    unregister_code (KC_CAPS);
  }

  s->finished_once = false;
}

//TD alt on hold, lower on tap
void _td_alb_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_alb_state_t *s = (td_alb_state_t *)user_data;

  if (s->finished_once)
    return;

  s->finished_once = true;
  if (state->pressed) {
    s->alt = true;
    register_code (KC_LALT);
  } else {
    s->alt = false;
	layer_on(_LOWER);
	layer_off(_RAISE);
	layer_off(_ADJUST);
  }
}

void _td_alb_reset (qk_tap_dance_state_t *state, void *user_data) {
  td_alb_state_t *s = (td_alb_state_t *)user_data;

  if (s->alt) {
    unregister_code (KC_LALT);
  }

  s->finished_once = false;
}

//TD ctrl on hold, raise on tap
void _td_cr_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_cr_state_t *s = (td_cr_state_t *)user_data;

  if (s->finished_once)
    return;

  s->finished_once = true;
  if (state->pressed) {
    s->alt = true;
    register_code (KC_LCTL);
  } else {
    s->alt = false;
	layer_off(_LOWER);
	layer_on(_RAISE);
	layer_off(_ADJUST);
  }
}

void _td_cr_reset (qk_tap_dance_state_t *state, void *user_data) {
  td_cr_state_t *s = (td_cr_state_t *)user_data;

  if (s->alt) {
    unregister_code (KC_LCTL);
  }

  s->finished_once = false;
}

//TD gui on hold, mraise on tap
void _td_gmr_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_gmr_state_t *s = (td_gmr_state_t *)user_data;

  if (s->finished_once)
    return;

  s->finished_once = true;
  if (state->pressed) {
    s->alt = true;
    register_code (KC_LGUI);
  } else {
    s->alt = false;
	layer_off(_LOWER);
	layer_on(_MRAISE);
	layer_off(_ADJUST);
  }
}

void _td_gmr_reset (qk_tap_dance_state_t *state, void *user_data) {
  td_gmr_state_t *s = (td_gmr_state_t *)user_data;

  if (s->alt) {
    unregister_code (KC_LGUI);
  }

  s->finished_once = false;
}

//TD meh on hold, adjust layer on tap
void _td_ma_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_ma_state_t *s = (td_ma_state_t *)user_data;

  if (s->finished_once)
    return;

  s->finished_once = true;
  if (state->pressed) {
    s->alt = true;
    register_code (KC_LSFT);
	register_code (KC_LALT);
	register_code (KC_LCTL);
  } else {
    s->alt = false;
	layer_off(_LOWER);
	layer_off(_RAISE);
	layer_on(_ADJUST);
  }
}

void _td_ma_reset (qk_tap_dance_state_t *state, void *user_data) {
  td_ma_state_t *s = (td_ma_state_t *)user_data;

  if (s->alt) {
	unregister_code (KC_LCTL);
	unregister_code (KC_LALT);
	unregister_code (KC_LSFT);
  }

  s->finished_once = false;
}

//TD Actions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_DV] = {
    .fn = { NULL, _td_dv_finished, _td_dv_reset },
    .user_data = (void *)&((td_dv_state_t) { false, false })
  },

  [TD_MDV] = {
    .fn = { NULL, _td_mdv_finished, _td_mdv_reset },
    .user_data = (void *)&((td_mdv_state_t) { false, false })
  },

  [TD_SFT_CAPS] = {
    .fn = { NULL, _td_sftcaps_finished, _td_sftcaps_reset },
    .user_data = (void *)&((td_sftcaps_state_t) { false, false })
  },

  [TD_AL]  = {
    .fn = { NULL, _td_alb_finished, _td_alb_reset },
    .user_data = (void *)&((td_alb_state_t) { false, false })
  },

  [TD_CR]  = {
    .fn = { NULL, _td_cr_finished, _td_cr_reset },
    .user_data = (void *)&((td_cr_state_t) { false, false })
  },

  [TD_GMR]  = {
    .fn = { NULL, _td_gmr_finished, _td_gmr_reset },
    .user_data = (void *)&((td_gmr_state_t) { false, false })
  },

  [TD_MA]  = {
    .fn = { NULL, _td_ma_finished, _td_ma_reset },
    .user_data = (void *)&((td_ma_state_t) { false, false })
  }
};
