/* Copyright 2021 Richard Nunez <antebios1@gmail.com>
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
#include "print.h"

// Keep track of key presses for Modifier
typedef struct {
  bool is_press_action;
  int state;
} tap;

// Key Tap enumerator
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_layer {
  _QWERTY,
  _ALT,
  _CTRL,
  _LOWER,
  _RAISE,
  _MOUSE,
  _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  ALT,
  CTRL,
  LOWER,
  RAISE,
  MOUSE,
  ADJUST
};

// TAP DANCE ***********************************************************
//Tap Dance Declarations
enum {
  ALT_OSL1 = 0,
  CTL_OSL1,
  TD_DEL_BSPC ,
  TD_ESC_GRAVE,
  TD_TAB_TILDE,
  TD_9_LPRN,
  TD_0_RPRN,
  TD_MINS_UNDS,
  TD_EQL_PLUS,
  TD_LBRC_LCBR,
  TD_RBRC_RCBR,
  TD_SCLN_COLN,
  TD_QUOT_DQT,
  TD_COMM_LABK,
  TD_DOT_RABK,
  TD_SLSH_QUES,
  TD_BSLS_PIPE,

  TD_PGUP_HOME,
  TD_PGDN_END,

  TD_Q_LrALT,
  TD_W_Lyr2,
  TD_E_Lyr3,
  TD_R_LrKey,
  TD_T_LrMS,

  TD_SHIFT_CAPS,
  TD_SPC_ENT,
  TD_SPC_BKSPC,
  TD_LSPACE,
  TD_RSPACE,

  TD_LayerDn,
  TD_LayerUp
};


// Alt key action:
// SINGLE_TAP = toggle layer, then wait for keypress on called layer, then switch back to original layer.
// SINGLE_HOLD = will work as normal sending the keypress.
// DOUBLE_TAP = 3,
// DOUBLE_HOLD = will then toggle layer and keep sending the Alt keycode until next keypress, then switch back to original layer.
// TRIPLE_TAP = 5,
// TRIPLE_HOLD = 6
// // Alt held down, then use as normal.
//
// Alt tapped, then hold Alt,
int cur_dance (qk_tap_dance_state_t *state);
void alt_finished (qk_tap_dance_state_t *state, void *user_data);
void alt_reset (qk_tap_dance_state_t *state, void *user_data);

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed) return SINGLE_HOLD;
    else return SINGLE_TAP;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

static tap alttap_state = {
  .is_press_action = true,
  .state = 0
};

void alt_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: set_oneshot_layer(_ALT, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case SINGLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_TAP: set_oneshot_layer(_ALT, ONESHOT_START); set_oneshot_layer(_ALT, ONESHOT_PRESSED); break;
    case DOUBLE_HOLD: register_code(KC_LALT); layer_on(_ALT); break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void alt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: unregister_code(KC_LALT); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_off(_ALT); unregister_code(KC_LALT); break;
  }
  alttap_state.state = 0;
}

// Ctrl tapped, then hold Ctrl,
void ctl_finished (qk_tap_dance_state_t *state, void *user_data);
void ctl_reset (qk_tap_dance_state_t *state, void *user_data);

static tap ctltap_state = {
  .is_press_action = true,
  .state = 0
};

void ctl_finished (qk_tap_dance_state_t *state, void *user_data) {
  ctltap_state.state = cur_dance(state);
  switch (ctltap_state.state) {
    case SINGLE_TAP: set_oneshot_mods(MOD_BIT(KC_LCTL)); break;
    case SINGLE_HOLD: register_code(KC_LCTL); break;
    case DOUBLE_TAP: set_oneshot_layer(_ALT, ONESHOT_START); set_oneshot_layer(_ALT, ONESHOT_PRESSED); break;
    case DOUBLE_HOLD: register_code(KC_LCTL); layer_on(_ALT); break;
    case TRIPLE_TAP: register_mods(MOD_BIT(KC_LCTL)); register_mods(MOD_BIT(KC_LSFT)); break;
  }
}

void ctl_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ctltap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: unregister_code(KC_LCTL); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_off(_ALT); unregister_code(KC_LCTL); break;
    case TRIPLE_TAP: break;
  }
  ctltap_state.state = 0;
}


// Layer Down tap dance
void layerDown_finished (qk_tap_dance_state_t *state, void *user_data);
void layerDown_reset (qk_tap_dance_state_t *state, void *user_data);

static tap layerdn_tap_state = {
  .is_press_action = true,
  .state = 0
};

void layerDown_finished (qk_tap_dance_state_t *state, void *user_data) {
  layerdn_tap_state.state = cur_dance(state);
  switch (layerdn_tap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: layer_on(_LOWER); break;
    case DOUBLE_TAP: layer_move(_QWERTY); break;
    case DOUBLE_HOLD: break;
    case TRIPLE_TAP: reset_keyboard(); break;
  }
}

void layerDown_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (layerdn_tap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: layer_off(_LOWER); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
  }
  layerdn_tap_state.state = 0;
}

// Layer Up tap dance
void layerUp_finished (qk_tap_dance_state_t *state, void *user_data);
void layerUp_reset (qk_tap_dance_state_t *state, void *user_data);

static tap layerup_tap_state = {
  .is_press_action = true,
  .state = 0
};

void layerUp_finished (qk_tap_dance_state_t *state, void *user_data) {
  layerup_tap_state.state = cur_dance(state);
  switch (layerup_tap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: layer_on(_RAISE); break;
    case DOUBLE_TAP: layer_move(_RAISE); break;
    case DOUBLE_HOLD: break;
    case TRIPLE_TAP: layer_move(_MOUSE); break;
  }
}

void layerUp_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (layerup_tap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: layer_off(_RAISE); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
    case TRIPLE_TAP: break;
  }
  layerup_tap_state.state = 0;
}


// Shift key action:
// Shift held down, then use as normal and use Shift Mode of key.
// Shift tapped, then Capitlize next keystroke only.
// Shift double-tapped, then CAPSLOCK
// Shift double-tapped again, CAPS UNLOCKED
// void dance_onshot_lsft(qk_tap_dance_state_t *state, void *user_data) {
void lshift_finished (qk_tap_dance_state_t *state, void *user_data);
void lshift_reset (qk_tap_dance_state_t *state, void *user_data);

static tap lshifttap_state = {
  .is_press_action = true,
  .state = 0
};

void lshift_finished (qk_tap_dance_state_t *state, void *user_data) {
  lshifttap_state.state = cur_dance(state);
  switch (lshifttap_state.state) {
    case SINGLE_TAP: set_oneshot_mods(MOD_BIT(KC_LSFT)); break;
    case SINGLE_HOLD: register_code(KC_LSFT); break;
    case DOUBLE_TAP: tap_code (KC_CAPS); break;
    case DOUBLE_HOLD: break;
  }
}

void lshift_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (lshifttap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: unregister_code(KC_LSFT); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
  }
  lshifttap_state.state = 0;
}

//TD_LSPACE
void lspace_finished (qk_tap_dance_state_t *state, void *user_data);
void lspace_reset (qk_tap_dance_state_t *state, void *user_data);

static tap lspacetap_state = {
  .is_press_action = true,
  .state = 0
};

void lspace_finished (qk_tap_dance_state_t *state, void *user_data) {
  lspacetap_state.state = cur_dance(state);
  switch (lspacetap_state.state) {
    case SINGLE_TAP: tap_code (KC_SPACE); break;
    case SINGLE_HOLD: layer_on(_LOWER); break;
    case DOUBLE_TAP: tap_code (KC_ENT);break;
    case DOUBLE_HOLD: break;
  }
}

void lspace_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (lspacetap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: layer_off(_LOWER); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: break;
  }
  lspacetap_state.state = 0;
}

//TD_RSPACE



//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
   [TD_DEL_BSPC]  = ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_BSPC),
   [TD_ESC_GRAVE]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRAVE),
   [TD_TAB_TILDE]  = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_TILDE),

   [TD_9_LPRN]  = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_LPRN),
   [TD_0_RPRN]  = ACTION_TAP_DANCE_DOUBLE(KC_0, KC_RPRN),

   [TD_MINS_UNDS]  = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS),
   [TD_EQL_PLUS]  = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_PLUS),

   [TD_LBRC_LCBR]  = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LCBR),
   [TD_RBRC_RCBR]  = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RCBR),

   [TD_SCLN_COLN]  = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
   [TD_QUOT_DQT]  = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQT),

   [TD_COMM_LABK]  = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_LABK),
   [TD_DOT_RABK]  = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_RABK),
   [TD_SLSH_QUES]  = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
   [TD_BSLS_PIPE]  = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_PIPE),

   [TD_PGUP_HOME]  = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, KC_HOME),
   [TD_PGDN_END]   = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, KC_END),

   [TD_Q_LrALT] = ACTION_TAP_DANCE_LAYER_MOVE(KC_Q, _ALT),
   [TD_R_LrKey] = ACTION_TAP_DANCE_LAYER_MOVE(KC_R, _RAISE),
   [TD_T_LrMS]  = ACTION_TAP_DANCE_LAYER_MOVE(KC_T, _MOUSE),

   [TD_SHIFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,lshift_finished, lshift_reset),
   [TD_SPC_ENT]    = ACTION_TAP_DANCE_DOUBLE(KC_SPACE, KC_ENT),
   [TD_SPC_BKSPC]  = ACTION_TAP_DANCE_DOUBLE(KC_SPACE, KC_BSPACE),
   [TD_LSPACE]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,lspace_finished,lspace_reset),

   [ALT_OSL1]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_finished, alt_reset),
   [CTL_OSL1]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,ctl_finished, ctl_reset),
   [TD_LayerDn]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL,layerDown_finished, layerDown_reset),
   [TD_LayerUp]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL,layerUp_finished, layerUp_reset)
};

// Fillers to make layering more clear
// #define _______ KC_TRNS
// #define XXXXXXX KC_NO

#define KC_L1 LOWER
#define KC_L2 RAISE
// MO(_LOWER)
// MO(_RAISE)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-------------------------------------------------------------------------------------------------.
 * | DEL  | Bksp |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | PGUP | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |   ]  |
 * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
 * | PGDN | Enter|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  | Enter|
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | Shift| Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |   \  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Win  | Alt  |Lower |Raise | Space/Enter | Space/Bkspc | <--  |   v  |   ^  | -->  | Esc  |
 * `-------------------------------------------------------------------------------------------------'
 */
  [_QWERTY] = LAYOUT(
  //,-----------------+-----------------+---------------+--------------+--------------+--------------+--------------+------+-----------+-----------------+----------------+-----------------+-----------------+------------------.
     TD(TD_DEL_BSPC)  , KC_BSPACE       , KC_1           , KC_2        , KC_3         , KC_4         , KC_5         , KC_6 , KC_7      , KC_8            , TD(TD_9_LPRN)  , TD(TD_0_RPRN)   ,TD(TD_MINS_UNDS) , TD(TD_EQL_PLUS),
  //|-----------------+-----------------+---------------+--------------+--------------+--------------+--------------+------+-----------+-----------------+----------------+-----------------+-----------------+------------------|
     TD(TD_PGUP_HOME) , TD(TD_TAB_TILDE), TD(TD_Q_LrALT), KC_W         , KC_E         , KC_R         , KC_T         , KC_Y , KC_U      , KC_I            , KC_O           , KC_P            ,TD(TD_LBRC_LCBR) , TD(TD_RBRC_RCBR),
  //|-----------------+-----------------+---------------+--------------+--------------+--------------+--------------+------+-----------+-----------------+----------------+-----------------+-----------------+------------------|
     TD(TD_PGDN_END)  , KC_ENT          , KC_A          , KC_S         , KC_D         , KC_F         , KC_G         , KC_H , KC_J      , KC_K            , KC_L           ,TD(TD_SCLN_COLN) ,TD(TD_QUOT_DQT)  , KC_ENT,
  //|-----------------+-----------------+---------------+--------------+--------------+--------------+--------------+------+-----------+-----------------+----------------+-----------------+-----------------+------------------|
     TD(TD_SHIFT_CAPS),TD(TD_SHIFT_CAPS), KC_Z          , KC_X         , KC_C         , KC_V         , KC_B         , KC_N , KC_M      ,TD(TD_COMM_LABK) ,TD(TD_DOT_RABK) ,TD(TD_SLSH_QUES) ,TD(TD_BSLS_PIPE) , KC_RSFT,
  //|-----------------+-----------------+---------------+--------------+--------------+--------------+--------------+------+-----------+-----------------+--------+-------+-----------------+-----------------+------------------|
      TD(CTL_OSL1)    , OSM(MOD_LGUI)   , TD(ALT_OSL1)  ,TD(TD_LayerDn),TD(TD_LayerUp),        TD(TD_LSPACE)        , TD(TD_SPC_BKSPC) , KC_LEFT         , KC_DOWN        , KC_UP           ,  KC_RIGHT      ,TD(TD_ESC_GRAVE)
  //`-----------------+-----------------+---------------+--------------+--------------+-----------------------------+----------------------------------+--------+-------+-----------------+----------------+-------------------'
  ),

/* ALT Layout
 * ,-----------------------------------------------------------------------------------------------------.
 * | DEL      | Bksp |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |
 * |----------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | PGUP     | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |   ]  |
 * |----------+------+------+------+------+------+-------------+------+------+------+------+------+------|
 * | PGDN     | Enter|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  | Enter|
 * |----------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | Shift    | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |   \  | Shift|
 * |----------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl     | Win  | Alt  |Lower |Raise | Space/Enter | Space/Bkspc | <--  |   v  |   ^  | -->  | Esc  |
 * `----------------------------------------------------------------------------------------------------'
 */
  [_ALT] = LAYOUT(
  //,---------------+---------------+-------------+---------------+--------------+---------+-----------------+-----------------+---------+---------+----------------+---------------+---------------+----------------.
     KC_TRNS        , KC_TRNS       , KC_F1       , KC_F2         , KC_F3        , KC_F4   , KC_F5           , KC_F6           , KC_F7   , KC_F8    , KC_F9         , KC_F10        , KC_F11        , KC_F12,
  //|---------------+---------------+-------------+---------------+--------------+---------+-----------------+-----------------+---------+---------+----------------+---------------+---------------+----------------|
     KC_TRNS        , KC_TRNS       , KC_TRNS     , KC_TRNS       , KC_TRNS      , KC_TRNS , KC_TRNS         , KC_TRNS         , KC_TRNS , KC_TRNS , KC_TRNS        , KC_TRNS       , KC_TRNS       , KC_TRNS,
  //|---------------+---------------+-------------+---------------+--------------+---------+-----------------+-----------------+---------+---------+----------------+---------------+---------------+----------------|
     KC_TRNS        , KC_TRNS       , KC_TRNS     , KC_TRNS       , KC_TRNS      , KC_TRNS , KC_TRNS         , KC_TRNS         , KC_TRNS , KC_TRNS , KC_TRNS        , KC_TRNS       , KC_TRNS       , KC_TRNS,
  //|---------------+---------------+-------------+---------------+--------------+---------+-----------------+-----------------+---------+---------+----------------+---------------+---------------+----------------|
     KC_TRNS        , KC_TRNS       , KC_TRNS     , KC_TRNS       , KC_TRNS      , KC_TRNS , KC_TRNS         , KC_TRNS         , KC_TRNS , KC_TRNS , KC_TRNS        , KC_TRNS       , KC_TRNS       , KC_TRNS,
  //|---------------+---------------+-------------+---------------+--------------+---------+-----------------+-----------------+---------+---------+----------------+---------------+---------------+----------------|
     TD(CTL_OSL1)   , OSM(MOD_LGUI) , TD(ALT_OSL1), TD(TD_LayerDn),TD(TD_LayerUp),   TD(TD_SPC_ENT)          ,         TD(TD_SPC_BKSPC)  , KC_TRNS , KC_TRNS        , KC_TRNS       , KC_TRNS       ,TD(TD_ESC_GRAVE)
  //`---------------+---------------+-------------+---------------+--------------+---------------------------+---------------------------+---------+----------------+---------------+---------------+----------------'
  ),

/* CTRL Layout
 * ,-----------------------------------------------------------------------------------------------------.
 * | DEL/Bksp |  F1  |  F2  |  F3  |  F4  |  F5  |  DEL | Bksp |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |----------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab      |   Q  |   W  |   E  |   R  |   T  |  [   |   ]  |   Y  |   U  |   I  |   O  |   P  |  F12 |
 * |----------+------+------+------+------+------+-------------+------+------+------+------+------+------|
 * | Enter    |   A  |   S  |   D  |   F  |   G  | PGUP | HOME |   H  |   J  |   K  |   L  |   ;  |   '  |
 * |----------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * | Shift    |   Z  |   X  |   C  |   V  |   B  | PGDN | END  |   N  |   M  |   ,  |   .  |   /  |   \  |
 * |----------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl     | Win  | Alt  |  Fn  |Lower | Space/Enter |    Space    | <--  |   v  |   ^  | -->  | Esc  |
 * `----------------------------------------------------------------------------------------------------'
 */
//   [_CTRL] = LAYOUT(
//   //,-----------------+-------------+-------------+--------------+--------------+---------+-----------------+-----------------+---------+---------+----------------+---------------+---------------+----------------.
//      KC_TRNS          , KC_TRNS     , KC_F1       , KC_F2        , KC_F3        , KC_F4   , KC_F5           , KC_F6           , KC_F7   , KC_F8   , KC_F9          , KC_F10       , KC_F11         , KC_F12,
//   //|-----------------+-------------+-------------+--------------+--------------+---------+-----------------+-----------------+---------+---------+----------------+---------------+---------------+----------------|
//      KC_TRNS          , KC_TRNS     , KC_TRNS     , KC_TRNS      , KC_TRNS      , KC_TRNS , KC_TRNS         , KC_TRNS         , KC_TRNS , KC_TRNS , KC_TRNS        , KC_TRNS       , KC_TRNS       , KC_TRNS,
//   //|-----------------+-------------+-------------+--------------+--------------+---------+-----------------+-----------------+---------+---------+----------------+---------------+---------------+----------------|
//      KC_TRNS          , KC_TRNS     , KC_TRNS     , KC_TRNS      , KC_TRNS      , KC_TRNS , KC_TRNS         , KC_TRNS         , KC_TRNS , KC_TRNS , KC_TRNS        , KC_TRNS       , KC_TRNS       , KC_TRNS,
//   //|-----------------+-------------+-------------+--------------+--------------+---------+-----------------+-----------------+---------+---------+----------------+---------------+---------------+----------------|
//      KC_TRNS          , KC_TRNS     , KC_TRNS     , KC_TRNS      , KC_TRNS      , KC_TRNS , KC_TRNS         , KC_TRNS         , KC_TRNS , KC_TRNS , KC_TRNS        , KC_TRNS       , KC_TRNS       , KC_TRNS,
//   //|-----------------+-------------+-------------+--------------+--------------+---------+-----------------+-----------------+---------+---------+----------------+---------------+---------------+----------------|
//      TD(CTL_OSL1)     , KC_LGUI     , TD(ALT_OSL1),TD(TD_LayerDn),TD(TD_LayerUp),   TD(TD_SPC_ENT)          ,         TD(TD_SPC_ENT)    , KC_TRNS , KC_TRNS        , KC_TRNS       , KC_TRNS       ,TD(TD_ESC_GRAVE)
//   //`-----------------+-------------+-------------+--------------+--------------+---------------------------+---------------------------+---------+----------------+---------------+---------------+----------------'
//   ),

/* Lower
 * ,-------------------------------------------------------------------------------------------------.
 * |  `   |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |
 * |------+------+------+------+------+------+------+-------------+------+------+------+------+------|
 * |  ~   |      |      |      |  UP  |      |      |      | Prev | Next | Vol- | Vol+ | Play |      |
 * |------+------+------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |Enter |      | LEFT | DOWN |RIGHT |      |      |      |      | MUTE |      |      |      |
 * |------+------+------+------+------+------+------|------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |             |      |      |      |      |      |
 * `------------------------------------------------------------------------------------------+------'
 */
[_LOWER] = LAYOUT(
  KC_GRV , _______, KC_F1  , KC_F2   , KC_F3   ,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_F11, KC_F12,
  KC_TILD, _______, _______, _______ , KC_UP   , _______, _______, _______, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______,
  _______, KC_ENT , _______, KC_LEFT, KC_DOWN , KC_RIGHT, _______, _______, _______, _______, KC_MUTE, _______, _______, _______,
  _______, _______, _______, _______ , _______ , _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______ , _______ ,      _______    ,      _______    , _______, _______, _______, _______, _______
),

/* Raise
 * ,-------------------------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|

 * ,-------------------------------------------------------------------------------------------------.
 * | Ins  |      |Brite+|Brite-|      |      |      |      |  7   |  8   |  9   |  /   |  -   |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Home | PrtSc|      |      |      |Reset |      |      |  4   |  5   |  6   |  *   |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------|
 * | End  | ScLk |      |      |Debug |      |      |      |  1   |  2   |  3   |  -   |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------+------+------|
 * |      | Pause|      |      |      |      |      |      |  0   |  ,   |  .   |  +   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |CtAlDl|      |      |      |      |             |       Enter |      |      |      |      |      |
 * `-------------------------------------------------------------------------------------------------'
 */
/*
KC_INS
KC_PSCR
KC_SLCK
KC_PAUS

*/

[_RAISE] = LAYOUT(
  KC_INS            , XXXXXXX  , KC_BRIU, KC_BRID, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_7 , KC_8   , KC_9     , KC_SLASH , KC_MINUS, KC_EQUAL,
  KC_HOME           , KC_PSCR  , XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX, XXXXXXX,  KC_4 , KC_5   , KC_6     , KC_ASTR  , XXXXXXX , XXXXXXX,
  KC_END            , KC_SLCK  , XXXXXXX, XXXXXXX, DEBUG  , XXXXXXX, XXXXXXX, XXXXXXX,  KC_1 , KC_2   , KC_3     , KC_MINUS , XXXXXXX , XXXXXXX,
  XXXXXXX           , KC_PAUSE , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_0 , KC_DOT , KC_COMMA , KC_PLUS  , XXXXXXX , XXXXXXX,
  LALT(LCTL(KC_DEL)), _______  , _______, _______, _______,     _______     ,   KC_KP_ENTER  , _______, _______  , _______  , _______ , _______
),

/* Adjust (Lower + Raise)
 * ,-------------------------------------------------------------------------------------------------.
 * |  Del |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Reset|      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |Audoff|Aud on|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |Voice-|Voice+|Musoff|Mus on|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |             |      |      |      |      |      |
 * `-------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT(
  KC_DEL  , _______,  KC_F1,   KC_F2,   KC_F3, KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,  KC_F10,  KC_F11,  KC_F12,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, _______, _______,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AU_ON,  AU_OFF, AG_NORM, AG_SWAP, QWERTY,    XXXXXXX, XXXXXXX, XXXXXXX, _______,
  XXXXXXX, XXXXXXX, XXXXXXX, MUV_DE,  MUV_IN,  MU_ON,  MU_OFF,   MI_ON,  MI_OFF,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, _______, _______, _______, _______,     _______,        _______,       _______, _______, _______, _______, _______
)
,

/* Layer 3 - Mouse Controls
 * ,-------------------------------------------------------------------------------------------------.
 * |      |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | PGUP |      |      |      |MS UP |      |SPEED0|      |      |WHUP  |      |      |      |      |
 * |------+------+------+------+------+------+------+-------------+------+------+------+------+------|
 * | PGDN |      |      |MSLeft|MS DN |MSRite|SPEED1|      |WHLeft|WHDN  |WHRite|      |      |      |
 * |------+------+------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |SPEED2|      | BTN1 | BTN2 | BTN3 |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Win  | Alt  |Lower |Raise | Space/Enter |     BTN1    | <--  |   v  |   ^  | -->  | Esc  |
 * `-------------------------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT(
  _______     , XXXXXXX      , KC_F1       , KC_F2          , KC_F3        , KC_F4      , KC_F5        , KC_F6  , KC_F7         , KC_F8        , KC_F9         , KC_F10  , KC_F11  , KC_F12,
  _______     , XXXXXXX      , XXXXXXX     , XXXXXXX        , KC_MS_UP     , XXXXXXX    , KC_MS_ACCEL0 , XXXXXXX, XXXXXXX       , KC_MS_WH_UP  , XXXXXXX       , XXXXXXX , XXXXXXX , XXXXXXX,
  _______     , XXXXXXX      , XXXXXXX     , KC_MS_LEFT     , KC_MS_DOWN   , KC_MS_RIGHT, KC_MS_ACCEL1 , XXXXXXX, KC_MS_WH_LEFT , KC_MS_WH_DOWN, KC_MS_WH_RIGHT, XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX     , XXXXXXX      , XXXXXXX     , XXXXXXX        , XXXXXXX      , XXXXXXX    , KC_MS_ACCEL2 , XXXXXXX, KC_MS_BTN1    , KC_MS_BTN2   , KC_MS_BTN3    , XXXXXXX , XXXXXXX , XXXXXXX,
  TD(CTL_OSL1), OSM(MOD_LGUI), TD(ALT_OSL1), TD(TD_LayerDn) ,TD(TD_LayerUp),      TD(TD_SPC_ENT)       ,    KC_MS_BTN1          , KC_LEFT      , KC_DOWN       , KC_UP   , KC_RIGHT, TD(TD_ESC_GRAVE)
)

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef CONSOLE_ENABLE
    //uprintf("%s keycode\n", keycode);
    dprintf("process --> KL: kc: 0x%04X, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  #endif

  switch (keycode) {
    case KC_TRNS:
    case KC_NO:
      /* Always cancel one-shot layer when another key gets pressed */
      if (record->event.pressed && is_oneshot_layer_active())
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      return true;
    case QK_BOOT:
      /* Don't allow reset from oneshot layer state */
      if (record->event.pressed && is_oneshot_layer_active()){
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        return false;
      }
      return true;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
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
    case MOUSE:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_MOUSE);
      }
      return false;
      break;
  }
  return true;
};

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef CONSOLE_ENABLE
    //print("Running post_process_record_user.\n");
    dprintf("post_process --> KL: kc: 0x%04X, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  #endif
  if (!record->event.pressed) {
    if(keyboard_report->mods & MOD_BIT(KC_LCTL)) {
      #ifdef CONSOLE_ENABLE
        dprint("FOUND 2nd challenge:  KC_LCTL is enabled.\n");
      #endif
      if(keyboard_report->mods & MOD_BIT(KC_LSFT)) {
        #ifdef CONSOLE_ENABLE
          dprint("FOUND 3rd challenge:  KC_LSFT is enabled.\n");
        #endif
        // Remove Left Ctrl and Left Shift keys from Triple Tap of Left Ctrl key.
        // Works with 'ctl_finished' function, Triple Tap.
        unregister_mods(MOD_BIT(KC_LCTL));
        unregister_mods(MOD_BIT(KC_LSFT));
        #ifdef CONSOLE_ENABLE
          dprint("** MODs for LCTL and LSFT have been released.\n");
        #endif
      }
    }
  }
}

