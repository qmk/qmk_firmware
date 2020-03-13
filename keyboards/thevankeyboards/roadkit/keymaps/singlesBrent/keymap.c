#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _NP 0
#define _L1 1
#define _L2 2
#define _L3 3

// Macro name shortcuts
#define NUMPAD M(_NP)
#define LAYER1 M(_L1)
#define LAYER2 M(_L2)
#define LAYER3 M(_L3)

void matrix_init_user(void) {
	backlight_level(4);
}



//Tap Dance Declarations

enum {

  TD_EQUAL_NP = 0,
  TD_KP_PLUS_L1,
  TD_DOT_L2,
  TD_0_L3

};

//Tap Dance Definitions


	//TD equal to turn on layer NP
void _td_equal_tg_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_EQUAL);
  } else if (state->count == 2) {
    backlight_set(3);
	layer_on(_NP);
	layer_off(_L1);
	layer_off(_L2);
	layer_off(_L3);
  }
}

void _td_equal_tg_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_EQUAL);
  }
}


	//TD kp plus to toggle layer 1
void _td_kp_plus_tg_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_KP_PLUS);
  } else if (state->count == 2) {
//    layer_invert(_L1);
    backlight_set(2);
	layer_on(_L1);
	layer_off(_L2);
	layer_off(_L3);
  }
}

void _td_kp_plus_tg_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_KP_PLUS);
  }
}


	//TD dot to toggle layer 2
void _td_dot_tg_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_DOT);
  } else if (state->count == 2) {
    backlight_set(1);
	layer_on(_L2);
	layer_off(_L1);
	layer_off(_L3);
  }
}

void _td_dot_tg_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_DOT);
  }
}

	//TD 0 to toggle layer 3
void _td_0_tg_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_0);
  } else if (state->count == 2) {
    backlight_set(0);
	layer_on(_L3);
	layer_off(_L1);
	layer_off(_L2);
  }
}

void _td_0_tg_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_0);
  }
}

//TD Actions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_EQUAL_NP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, _td_equal_tg_finished, _td_equal_tg_reset),
  [TD_KP_PLUS_L1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, _td_kp_plus_tg_finished, _td_kp_plus_tg_reset),
  [TD_DOT_L2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, _td_dot_tg_finished, _td_dot_tg_reset),
  [TD_0_L3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, _td_0_tg_finished, _td_0_tg_reset)
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Numberpad
   * ,-----------------------.
   * |  7  |  8  |  9  |  /  |
   * |-----`-----`-----`-----|
   * |  4  |  5  |  6  |  *  |
   * |-----`-----`-----`-----|
   * |  1  |  2  |  3  |  -  |
   * |-----`-----`-----`-----|
   * |  0  |  .  |  +  |  =  |
   * `-----`-----`-----`-----'
   * Tapdances:
   * | L3  | L2  | L1  | NP  |
   * `-----`-----`-----`-----'
   */
  [_NP] = LAYOUT_ortho_4x4( /* Numpad */
    KC_7,        KC_8,          KC_9,              KC_SLASH, \
    KC_4,        KC_5,          KC_6,              KC_KP_ASTERISK, \
    KC_1,        KC_2,          KC_3,              KC_MINUS, \
    TD(TD_0_L3), TD(TD_DOT_L2), TD(TD_KP_PLUS_L1), TD(TD_EQUAL_NP)
  ),

  /* L1
   * ,-----------------------.
   * | Esc |Bksp |Home |PgUp |
   * |-----`-----`-----`-----|
   * | Tab | Up  | End |PgDn |
   * |-----`-----`-----`-----|
   * |Left |Down |Right|Enter|
   * |-----`-----`-----`-----|
   * |  0  |  .  |  +  |  =  |
   * `-----`-----`-----`-----'
   */
  [_L1] = LAYOUT_ortho_4x4( /* LAYER 1 */
    KC_ESCAPE, KC_BSPACE, KC_HOME,  KC_PGUP, \
    KC_TAB,    KC_UP,     KC_END,   KC_PGDOWN, \
    KC_LEFT,   KC_DOWN,   KC_RIGHT, KC_KP_ENTER, \
    _______,   _______,   _______,  _______
  ),

  /* L2
   * ,-----------------------.
   * |Sleep|LClik|RClik|VolUp|
   * |-----`-----`-----`-----|
   * |AltF4| F11 |WinTb|VolDn|
   * |-----`-----`-----`-----|
   * |PrvTk|Play |NxtTk|Mute |
   * |-----`-----`-----`-----|
   * |  0  |  .  |  +  |  =  |
   * `-----`-----`-----`-----'
   */
  [_L2] = LAYOUT_ortho_4x4( /* LAYER 2 */
    KC_SYSTEM_SLEEP,     KC_MS_BTN1,          KC_MS_BTN2,          KC_AUDIO_VOL_UP, \
    LALT(KC_F4),         KC_F11,              LGUI(KC_TAB),        KC_AUDIO_VOL_DOWN, \
    KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE, \
    _______,             _______,             _______,             _______
  ),

  /* L3 needs cut, copy, paste, undo, again (redo), find, calc, www back, www forward, F5
   * ,-----------------------.
   * |WBack|WHome|WFor | F5  |
   * |-----`-----`-----`-----|
   * |Calc |Undo |Redo |WSrch|
   * |-----`-----`-----`-----|
   * | Cut |Copy |Paste|Find |
   * |-----`-----`-----`-----|
   * |  0  |  .  |  +  |  =  |
   * `-----`-----`-----`-----'
   */
  [_L3] = LAYOUT_ortho_4x4( /* LAYER 3 */
    KC_SYSTEM_SLEEP,     KC_MS_BTN1,          KC_MS_BTN2,          KC_AUDIO_VOL_UP, \
    LALT(KC_F4),         KC_F11,              LGUI(KC_TAB),        KC_AUDIO_VOL_DOWN, \
    KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE, \
    _______,             _______,             _______,             _______
  ),
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t * action_get_macro(keyrecord_t * record, uint8_t id, uint8_t opt) {
  switch (id) {
  case _L3:
    if (record->event.pressed) {
      persistent_default_layer_set(1UL<<_L3);
    }
    break;
  case _L2:
    if (record->event.pressed) {
      persistent_default_layer_set(1UL<<_L2);
    }
    break;
  case _L1:
    if (record->event.pressed) {
      persistent_default_layer_set(1UL<<_L1);
    }
    break;
  case _NP:
    if (record->event.pressed) {
      persistent_default_layer_set(1UL<<_NP);
    }
    break;
  }
  return MACRO_NONE;
};
