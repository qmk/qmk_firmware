/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifdef TAP_DANCES_ENABLE

#include "tap_dances.h"

#include "action.h"
#include "action_layer.h"
#include "process_keycode/process_tap_dance.h"

void tap_dance_mouse_btns (qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count){
    case 1:
        register_code(KC_BTN1);
        break;
    case 2:
        register_code(KC_BTN2);
        break;
    case 3:
        register_code(KC_BTN3);
        break;
    case 4:
        register_code(KC_BTN4);
        break;
    case 5:
        register_code(KC_BTN5);
        break;
    default:
        break;
    }
    reset_tap_dance(state);
}

// counting on all the qwerty layers to be less than dvorak_on_bepo
int on_qwerty(){
    uint8_t deflayer = (get_highest_layer(default_layer_state));
    return (deflayer < _DVORAK_BP);
}

static void switch_default_layer(uint8_t layer) {
  default_layer_set(1UL<<layer);
  clear_keyboard();
}

// so the keyboard remembers which layer it's in after power disconnect.
/*
  layer_state_t default_layer_state_set_kb(layer_state_t state) {
  eeconfig_update_default_layer(state);
  return state;
  }
*/

void tap_dance_df_bepo_layers_switch (qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count){
  case 1:
    switch_default_layer(_DVORAK_BP);
    break;
  case 2:
    switch_default_layer(_BEPO);
    break;
  case 3:
    layer_invert(_LAYERS);
    break;
  default:
    break;
  }
  reset_tap_dance(state);
}

void tap_dance_layer_switch (qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count){
  case 1:
    if(on_qwerty())
      layer_invert(_SYMB);
    else
      layer_invert(_SYMB_BP);
    break;
  case 2:
    layer_invert(_NAV);
    break;
  case 3:
    layer_invert(_LAYERS);
    break;
  case 4:
    if(on_qwerty())
      layer_invert(_KEYPAD);
    else
      layer_invert(_KEYPAD_BP);
    break;
  default:
    break;
  }
  reset_tap_dance(state);
}

void tap_dance_default_layer_switch (qk_tap_dance_state_t *state, void *user_data) {
    switch(state->count){
    case 1:
      switch_default_layer(_DVORAK);
      break;
    case 2:
      switch_default_layer(_DVORAK_BP);
      break;
    case 3:
      switch_default_layer(_BEPO);
      break;
    default:
        break;
    }
    reset_tap_dance(state);
}

// switch the default layer to another qwerty based layer.
void switch_default_layer_on_qwerty(int count) {
    switch(count){
    case 1:
      switch_default_layer(_DVORAK);
      break;
    case 2:
      switch_default_layer(_QWERTY);
      break;
    case 3:
      switch_default_layer(_COLEMAK);
      break;

      /* case 4: */
      /*   switch_default_layer(_WORKMAN); */
      /*   break; */
      /* case 5: */
      /*   switch_default_layer(_NORMAN); */
      /*   break; */

    default:
      switch_default_layer(_DVORAK);
      break;
    }
}

// switch the default layer to another bepo based layer.
void switch_default_layer_on_bepo(int count) {
    switch(count){
    case 1:
      switch_default_layer(_DVORAK_BP);
      break;
    case 2:
      switch_default_layer(_BEPO);
      break;
    default:
      switch_default_layer(_DVORAK_BP);
      break;
    }
}


// tap to change the default layer. Distinguishes between layers that are based on
// a qwerty software keyboard and a bepo software keyboard.
// if shifted, choose layers based on the other software keyboard, otherwise choose only
// layers that work on the current software keyboard.
void tap_dance_default_os_layer_switch (qk_tap_dance_state_t *state, void *user_data) {
    //uint8_t shifted = (get_mods() & MOD_BIT(KC_LSFT|KC_RSFT));
    bool shifted = ( keyboard_report->mods & (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)) );
    int qwerty = on_qwerty();


    // shifted, choose between layers on the other software keyboard
    if(shifted){
        if (qwerty)
            switch_default_layer_on_bepo(state->count);
        else
            switch_default_layer_on_qwerty(state->count);

        // not shifted, choose between layers on the same software keyboard
    } else {
        if (qwerty)
            switch_default_layer_on_qwerty(state->count);
        else
            switch_default_layer_on_bepo(state->count);
    }

    reset_tap_dance(state);
}


/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)  return SINGLE_TAP;
        //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    }
    else if (state->count == 2) {
        /*
         * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
         * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
         * keystrokes of the key, and not the 'double tap' action/macro.
         */
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    //Assumes no one is trying to type the same letter three times (at least not quickly).
    //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    }
    else return 8; //magic number. At some point this method will expand to work for more presses
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    //Tap once for Esc, twice for Caps Lock
    [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [TD_TAB_BKTAB] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, LSFT(KC_TAB)),
    [TD_RIGHT_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_RIGHT, KC_TAB),
    [TD_LEFT_BACKTAB] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, LSFT(KC_TAB)),
    [TD_UP_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_HOME),
    [TD_DOWN_END] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_END),
    [TD_MDIA_SYMB] = ACTION_TAP_DANCE_FN(tap_dance_layer_switch),
    [TD_DVORAK_BEPO] = ACTION_TAP_DANCE_FN(tap_dance_df_bepo_layers_switch),
    [TD_DEF_LAYER_SW] = ACTION_TAP_DANCE_FN(tap_dance_default_layer_switch),
    [TD_DEF_OS_LAYER_SW] = ACTION_TAP_DANCE_FN(tap_dance_default_os_layer_switch),
    [TD_HOME_END]  = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END),
    [TD_MOUSE_BTNS] = ACTION_TAP_DANCE_FN(tap_dance_mouse_btns)

};

#endif
