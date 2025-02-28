/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

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

#pragma once

/* period of tapping(ms) */
#ifndef TAPPING_TERM
#    define TAPPING_TERM 200
#endif

/* period of quick tap(ms) */
#if !defined(QUICK_TAP_TERM) || QUICK_TAP_TERM > TAPPING_TERM
#    define QUICK_TAP_TERM TAPPING_TERM
#endif

/* tap count needed for toggling a feature */
#ifndef TAPPING_TOGGLE
#    define TAPPING_TOGGLE 5
#endif

#define WAITING_BUFFER_SIZE 8

#ifndef NO_ACTION_TAPPING
uint16_t get_record_keycode(keyrecord_t *record, bool update_layer_cache);
uint16_t get_event_keycode(keyevent_t event, bool update_layer_cache);
void     action_tapping_process(keyrecord_t record);
#endif

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record);
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record);
bool     get_permissive_hold(uint16_t keycode, keyrecord_t *record);
bool     get_retro_tapping(uint16_t keycode, keyrecord_t *record);
bool     get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record);

#ifdef CHORDAL_HOLD
/**
 * Callback to say when a key chord before the tapping term may be held.
 *
 * In keymap.c, define the callback
 *
 *     bool get_chordal_hold(uint16_t tap_hold_keycode,
 *                           keyrecord_t* tap_hold_record,
 *                           uint16_t other_keycode,
 *                           keyrecord_t* other_record) {
 *        // Conditions...
 *     }
 *
 * This callback is called when:
 *
 * 1. `tap_hold_keycode` is pressed.
 * 2. `other_keycode` is pressed while `tap_hold_keycode` is still held,
 *     provided `other_keycode` is *not* also a tap-hold key and it is pressed
 *     before the tapping term.
 *
 * If false is returned, this has the effect of immediately settling the
 * tap-hold key as tapped. If true is returned, the tap-hold key is still
 * unsettled, and may be settled as held depending on configuration and
 * subsequent events.
 *
 * @param tap_hold_keycode   Keycode of the tap-hold key.
 * @param tap_hold_record    Record from the tap-hold press event.
 * @param other_keycode      Keycode of the other key.
 * @param other_record       Record from the other key's press event.
 * @return True if the tap-hold key may be considered held; false if tapped.
 */
bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record);

/**
 * Default "opposite hands rule" for whether a key chord may settle as held.
 *
 * This function returns true when the tap-hold key and other key are on
 * "opposite hands." In detail, handedness of the two keys are compared. If
 * handedness values differ, or if either handedness is '*', the function
 * returns true, indicating that it may be held. Otherwise, it returns false,
 * in which case the tap-hold key is immediately settled at tapped.
 *
 * @param tap_hold_record  Record of the active tap-hold key press.
 * @param other_record     Record of the other, interrupting key press.
 * @return True if the tap-hold key may be considered held; false if tapped.
 */
bool get_chordal_hold_default(keyrecord_t *tap_hold_record, keyrecord_t *other_record);

/**
 * Gets the handedness of a key.
 *
 * This function returns:
 *   'L' for keys pressed by the left hand,
 *   'R' for keys on the right hand,
 *   '*' for keys exempt from the "opposite hands rule." This could be used
 *       perhaps on thumb keys or keys that might be pressed by either hand.
 *
 * @param key   A key matrix position.
 * @return Handedness value.
 */
char chordal_hold_handedness(keypos_t key);

extern const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM;
#endif

#ifdef DYNAMIC_TAPPING_TERM_ENABLE
extern uint16_t g_tapping_term;
#endif

#if defined(TAPPING_TERM_PER_KEY) && !defined(NO_ACTION_TAPPING)
#    define GET_TAPPING_TERM(keycode, record) get_tapping_term(keycode, record)
#elif defined(DYNAMIC_TAPPING_TERM_ENABLE) && !defined(NO_ACTION_TAPPING)
#    define GET_TAPPING_TERM(keycode, record) g_tapping_term
#else
#    define GET_TAPPING_TERM(keycode, record) (TAPPING_TERM)
#endif

#ifdef QUICK_TAP_TERM_PER_KEY
#    define GET_QUICK_TAP_TERM(keycode, record) get_quick_tap_term(keycode, record)
#else
#    define GET_QUICK_TAP_TERM(keycode, record) (QUICK_TAP_TERM)
#endif
