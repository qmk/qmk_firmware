// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#include "miketronic.h"
#include "tapdances.h"


tap_dance_action_t tap_dance_actions[] = {

  [T_BRC]  = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC), 		        // Tap once for Left Brace, twice for Right Brace
  [T_MIN]  = ACTION_TAP_DANCE_DOUBLE(KC_MINUS, KC_EQUAL),		        // Minus, Equals
  [T_UMIN]  = ACTION_TAP_DANCE_DOUBLE(KC_UNDS, KC_MINS),		        // Underscore, Minus
  [T_GESC]  = ACTION_TAP_DANCE_DOUBLE(KC_GRAVE, KC_ESCAPE),	            // Grave, Escape
  [T_SE] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT), 		            // Space, Enter
  [T_MULTDIV] = ACTION_TAP_DANCE_DOUBLE(KC_PAST, KC_PSLS),  		    // Multiply, Divide
  [T_UR] = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_RGHT),			            // Up, Right
  [T_DL] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_LEFT),		            // Down, Left
  [T_CP] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_C), LCTL(KC_V)),             // Copy, Paste
  [T_DENT] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_ENT),                   // Dot, Enter
  [T_IENT] = ACTION_TAP_DANCE_DOUBLE(KC_I, KC_ENT),                     // "I", Enter
  [T_CSPC] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_COMM),                  // Space, Comma
  [T_DSPC] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_DOT),                   // Space, Dot
  [T_QEXC] = ACTION_TAP_DANCE_DOUBLE(KC_QUES, KC_EXLM),                 // "?", "!"  
  [T_QESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),                     // "q", Escape
  [T_TE] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_ESC),                     // Tab, Escape
  [T_20] = ACTION_TAP_DANCE_DOUBLE(KC_2, KC_0),                         // "2", "0"
  [T_SL] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),                   // Slash, Backslash
  [T_XX] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),                   // Left Paren, Right Paren
  [T_YY] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),                   // Left Bracket, Right Bracket
  [T_ATH] = ACTION_TAP_DANCE_DOUBLE(KC_AT, KC_HASH),	                // "@", "#"
  [T_PRAM] = ACTION_TAP_DANCE_DOUBLE(KC_PERC, KC_AMPR)                  // "%", "&"
};

