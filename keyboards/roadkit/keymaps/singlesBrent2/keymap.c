#include "roadkit.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _NP 0
#define _L1 1

// Macro name shortcuts
#define NUMPAD M(_NP)
#define LAYER1 M(_L1)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


//start at maximum led brightness
void matrix_init_user(void) {
	backlight_level(2);
}



//Tap Dance Declarations

enum {

  TD_EQUAL_NP = 0,
  TD_KP_PLUS_L1,

};

//Tap Dance Definitions


	//TD equal to turn on layer NP
void _td_equal_tg_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_KP_PLUS);
  } else if (state->count == 2) {
    backlight_set(1);
	layer_on(_NP);
	layer_off(_L1);

  }
}

void _td_equal_tg_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_KP_PLUS);
  }
}


	//TD kp plus to toggle layer 1
void _td_kp_plus_tg_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_EQUAL);
  } else if (state->count == 2) {
//    layer_invert(_L1);
    backlight_set(0);
	layer_on(_L1);

  }
}

void _td_kp_plus_tg_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_EQUAL);
  }
}


//TD Actions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_EQUAL_NP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, _td_equal_tg_finished, _td_equal_tg_reset),
  [TD_KP_PLUS_L1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, _td_kp_plus_tg_finished, _td_kp_plus_tg_reset)
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
 * |  0  |  .  |  =  |  +  |
 * `-----`-----`-----`-----'
 * Tapdances:
 *             | L1  | NP  |
 *             `-----`-----'
 */
  [_NP] = /* Numpad */
    SINGLES_KEYMAP(KC_P7,  KC_P8,   KC_P9,             KC_SLSH,  \
                   KC_P4,  KC_P5,   KC_P6,             KC_PAST, \
                   KC_P1,  KC_P2,   KC_P3,             KC_MINS, \
                   KC_P0,  KC_PDOT, TD(TD_KP_PLUS_L1), TD(TD_EQUAL_NP)),
/* L1
 * ,-----------------------.
 * |Calc |NumLK|     |VolUp|
 * |-----`-----`-----`-----|
 * |     |     |WinTb|VolDn|
 * |-----`-----`-----`-----|
 * |PrvTk|Play |NxtTk|Mute |
 * |-----`-----`-----`-----|
 * |     |     |  =  |  +  |
 * `-----`-----`-----`-----'
 */				   
  [_L1] = /* LAYER 2 */
    SINGLES_KEYMAP(KC_CALC,  KC_NLCK,  XXXXXXX,  KC_VOLU, \
                   XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_VOLD, \
                   KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE, \
                   XXXXXXX,  XXXXXXX,  KC_TRNS,  KC_TRNS),
};

const uint16_t PROGMEM fn_actions[] = {

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
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
