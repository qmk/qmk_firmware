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

#ifdef SPECULATIVE_HOLD
/** Gets the currently active speculative mods. */
uint8_t get_speculative_mods(void);

/**
 * Callback to say if a mod-tap key may be speculatively held.
 *
 * By default, speculative hold is enabled for mod-tap keys where the mod is
 * Ctrl, Shift, and Ctrl+Shift for either hand.
 *
 * @param keycode  Keycode of the mod-tap key.
 * @param record   Record associated with the mod-tap press event.
 * @return True if the mod-tap key may be speculatively held.
 */
bool get_speculative_hold(uint16_t keycode, keyrecord_t *record);

/**
 * Handler to be called on press events after tap-holds are settled.
 *
 * This function is to be called in process_record() in action.c, that is, just
 * after tap-hold events are settled as either tapped or held. When `record`
 * corresponds to a speculatively-held key, the speculative mod is cleared.
 *
 * @param record   Record associated with the mod-tap press event.
 */
void speculative_key_settled(keyrecord_t *record);
#else
#    define get_speculative_mods() 0
#endif // SPECULATIVE_HOLD

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

#ifdef FLOW_TAP_TERM
/**
 * Callback to specify the keys where Flow Tap is enabled.
 *
 * Flow Tap is constrained to certain keys by the following rule: this callback
 * is called for both the tap-hold key *and* the key press immediately preceding
 * it. If the callback returns true for both keycodes, Flow Tap is enabled.
 *
 * The default implementation of this callback corresponds to
 *
 *     bool is_flow_tap_key(uint16_t keycode) {
 *       switch (get_tap_keycode(keycode)) {
 *         case KC_SPC:
 *         case KC_A ... KC_Z:
 *         case KC_DOT:
 *         case KC_COMM:
 *         case KC_SCLN:
 *         case KC_SLSH:
 *           return true;
 *       }
 *       return false;
 *     }
 *
 * @param keycode Keycode of the key.
 * @return Whether to enable Flow Tap for this key.
 */
bool is_flow_tap_key(uint16_t keycode);

/**
 * Callback to customize Flow Tap filtering.
 *
 * Flow Tap acts only when key events are closer together than this time.
 *
 * Return a time of 0 to disable filtering. In this way, Flow Tap may be
 * disabled for certain tap-hold keys, or when following certain previous keys.
 *
 * The default implementation of this callback is
 *
 *     uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t* record,
 *                                uint16_t prev_keycode) {
 *       if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
 *         return g_flow_tap_term;
 *       }
 *       return 0;
 *     }
 *
 * NOTE: If both `is_flow_tap_key()` and `get_flow_tap_term()` are defined, then
 * `get_flow_tap_term()` takes precedence.
 *
 * @param keycode Keycode of the tap-hold key.
 * @param record keyrecord_t of the tap-hold event.
 * @param prev_keycode Keycode of the previously pressed key.
 * @return Time in milliseconds.
 */
uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode);

/** Updates the Flow Tap last key and timer. */
void flow_tap_update_last_event(keyrecord_t *record);

/**
 * Checks if the pressed key is within the flow tap term.
 * Can be used to avoid triggering combos or other actions within the flow tap term.
 *
 * @param keycode The keycode of the pressed key.
 * @param record The keyrecord of the pressed key.
 * @return True if the pressed key is within the flow tap term; false otherwise.
 */
bool within_flow_tap_term(uint16_t keycode, keyrecord_t *record);
#endif // FLOW_TAP_TERM

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
