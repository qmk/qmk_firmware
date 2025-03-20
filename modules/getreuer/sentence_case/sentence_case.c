// Copyright 2022-2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file sentence_case.c
 * @brief Sentence Case community module implementation
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/sentence-case>
 */

#include "sentence_case.h"

#include <string.h>

#if defined(NO_ACTION_ONESHOT)
// One-shot keys must be enabled for Sentence Case. One-shot keys are enabled
// by default, but are disabled by `#define NO_ACTION_ONESHOT` in config.h. If
// your config.h includes such a line, please remove it.
#error "sentence_case: Please enable oneshot."
#else

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

// Default to a timeout of 5 seconds.
#ifndef SENTENCE_CASE_TIMEOUT
#  define SENTENCE_CASE_TIMEOUT 5000
#endif  // SENTENCE_CASE_TIMEOUT

// Number of keys of state history to retain for backspacing.
#define STATE_HISTORY_SIZE 6

// clang-format off
/** States in matching the beginning of a sentence. */
enum {
  STATE_INIT,     /**< Initial enabled state. */
  STATE_WORD,     /**< Within a word. */
  STATE_ABBREV,   /**< Within an abbreviation like "e.g.". */
  STATE_ENDING,   /**< Sentence ended. */
  STATE_PRIMED,   /**< "Primed" state, in the space following an ending. */
  STATE_DISABLED, /**< Sentence Case is disabled. */
};
// clang-format on

#if SENTENCE_CASE_TIMEOUT > 0
static uint16_t idle_timer = 0;
#endif  // SENTENCE_CASE_TIMEOUT > 0
#if SENTENCE_CASE_BUFFER_SIZE > 1
static uint16_t key_buffer[SENTENCE_CASE_BUFFER_SIZE] = {0};
#endif  // SENTENCE_CASE_BUFFER_SIZE > 1
static uint8_t state_history[STATE_HISTORY_SIZE];
static uint16_t suppress_key = KC_NO;
static uint8_t sentence_state = STATE_INIT;

// Sets the current state to `new_state`.
static void set_sentence_state(uint8_t new_state) {
#if !defined(NO_DEBUG) && defined(SENTENCE_CASE_DEBUG)
  if (debug_enable && sentence_state != new_state) {
    static const char* state_names[] = {
        "INIT", "WORD", "ABBREV", "ENDING", "PRIMED", "DISABLED",
    };
    dprintf("Sentence case: %s\n", state_names[new_state]);
  }
#endif  // !NO_DEBUG && SENTENCE_CASE_DEBUG

  const bool primed = (new_state == STATE_PRIMED);
  if (primed != (sentence_state == STATE_PRIMED)) {
    sentence_case_primed(primed);
  }
  sentence_state = new_state;
}

static void clear_state_history(void) {
#if SENTENCE_CASE_TIMEOUT > 0
  idle_timer = 0;
#endif  // SENTENCE_CASE_TIMEOUT > 0
  memset(state_history, STATE_INIT, sizeof(state_history));
  if (sentence_state != STATE_DISABLED) {
    set_sentence_state(STATE_INIT);
  }
}

void sentence_case_clear(void) {
  clear_state_history();
  suppress_key = KC_NO;
#if SENTENCE_CASE_BUFFER_SIZE > 1
  memset(key_buffer, 0, sizeof(key_buffer));
#endif  // SENTENCE_CASE_BUFFER_SIZE > 1
}

void sentence_case_on(void) {
  if (sentence_state == STATE_DISABLED) {
    sentence_state = STATE_INIT;
    sentence_case_clear();
  }
}

void sentence_case_off(void) {
  if (sentence_state != STATE_DISABLED) {
    set_sentence_state(STATE_DISABLED);
  }
}

void sentence_case_toggle(void) {
  if (sentence_state != STATE_DISABLED) {
    sentence_case_off();
  } else {
    sentence_case_on();
  }
}

bool is_sentence_case_on(void) { return sentence_state != STATE_DISABLED; }
bool is_sentence_case_primed(void) { return sentence_state == STATE_PRIMED; }

#if SENTENCE_CASE_TIMEOUT > 0
#if SENTENCE_CASE_TIMEOUT < 100 || SENTENCE_CASE_TIMEOUT > 30000
// Constrain timeout to a sensible range. With the 16-bit timer, the longest
// representable timeout is 32768 ms, rounded here to 30000 ms = half a minute.
#error "sentence_case: SENTENCE_CASE_TIMEOUT must be between 100 and 30000 ms"
#endif

void housekeeping_task_sentence_case(void) {
  if (idle_timer && timer_expired(timer_read(), idle_timer)) {
    clear_state_history();  // Timed out; clear all state.
  }
}
#endif  // SENTENCE_CASE_TIMEOUT > 0

bool process_record_sentence_case(uint16_t keycode, keyrecord_t* record) {
  // Only process while enabled, and only process press events.
  if (sentence_state == STATE_DISABLED || !record->event.pressed) {
    return true;
  }

#if SENTENCE_CASE_TIMEOUT > 0
  idle_timer = (record->event.time + SENTENCE_CASE_TIMEOUT) | 1;
#endif  // SENTENCE_CASE_TIMEOUT > 0

  switch (keycode) {
    case SENTENCE_CASE_ON:
      sentence_case_on();
      return false;
    case SENTENCE_CASE_OFF:
      sentence_case_off();
      return false;
    case SENTENCE_CASE_TOGGLE:
      sentence_case_toggle();
      return false;

    case KC_LCTL ... KC_RGUI:  // Ignore mod keys.
    case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:  // Ignore one-shot mod.
    // Ignore MO, TO, TG, TT, OSL, TL layer switch keys.
    case QK_MOMENTARY ... QK_MOMENTARY_MAX:
    case QK_TO ... QK_TO_MAX:
    case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
    case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
    case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:  // Ignore one-shot layer.
#ifdef TRI_LAYER_ENABLE  // Ignore Tri Layer keys.
    case QK_TRI_LAYER_LOWER:
    case QK_TRI_LAYER_UPPER:
#endif  // TRI_LAYER_ENABLE
      return true;

#ifndef NO_ACTION_TAPPING
    case QK_MOD_TAP ... QK_MOD_TAP_MAX:
      if (record->tap.count == 0) {
        return true;
      }
      keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
      break;
#ifndef NO_ACTION_LAYER
    case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
      if (record->tap.count == 0) {
        return true;
      }
      keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
      break;
#endif  // NO_ACTION_LAYER
#endif  // NO_ACTION_TAPPING

#ifdef SWAP_HANDS_ENABLE
    case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
      if (IS_SWAP_HANDS_KEYCODE(keycode) || record->tap.count == 0) {
        return true;
      }
      keycode = QK_SWAP_HANDS_GET_TAP_KEYCODE(keycode);
      break;
#endif  // SWAP_HANDS_ENABLE
  }

  if (keycode == KC_BSPC) {
    // Backspace key pressed. Rewind the state and key buffers.
    set_sentence_state(state_history[STATE_HISTORY_SIZE - 1]);

    memmove(state_history + 1, state_history, STATE_HISTORY_SIZE - 1);
    state_history[0] = STATE_INIT;
#if SENTENCE_CASE_BUFFER_SIZE > 1
    memmove(key_buffer + 1, key_buffer,
            (SENTENCE_CASE_BUFFER_SIZE - 1) * sizeof(uint16_t));
    key_buffer[0] = KC_NO;
#endif  // SENTENCE_CASE_BUFFER_SIZE > 1
    return true;
  }

  const uint8_t mods = get_mods() | get_weak_mods() | get_oneshot_mods();
  uint8_t new_state = STATE_INIT;

  // We search for sentence beginnings using a simple finite state machine. It
  // matches things like "a. a" and "a.  a" but not "a.. a" or "a.a. a". The
  // state transition matrix is:
  //
  //             'a'       '.'      ' '      '\''
  //           +-------------------------------------
  //   INIT    | WORD      INIT     INIT     INIT
  //   WORD    | WORD      ENDING   INIT     WORD
  //   ABBREV  | ABBREV    ABBREV   INIT     ABBREV
  //   ENDING  | ABBREV    INIT     PRIMED   ENDING
  //   PRIMED  | match!    INIT     PRIMED   PRIMED
  char code = sentence_case_press_user(keycode, record, mods);
#if defined SENTENCE_CASE_DEBUG
  dprintf("Sentence Case: code = '%c' (%d)\n", code, (int)code);
#endif  // SENTENCE_CASE_DEBUG
  switch (code) {
    case '\0':  // Current key should be ignored.
      return true;

    case 'a':  // Current key is a letter.
      switch (sentence_state) {
        case STATE_ABBREV:
        case STATE_ENDING:
          new_state = STATE_ABBREV;
          break;

        case STATE_PRIMED:
          // This is the start of a sentence.
          if (keycode != suppress_key) {
            suppress_key = keycode;
            set_oneshot_mods(MOD_BIT(KC_LSFT));  // Shift mod to capitalize.
            new_state = STATE_WORD;
          }
          break;

        default:
          new_state = STATE_WORD;
      }
      break;

    case '.':  // Current key is sentence-ending punctuation.
      switch (sentence_state) {
        case STATE_WORD:
          new_state = STATE_ENDING;
          break;

        default:
          new_state = STATE_ABBREV;
      }
      break;

    case ' ':  // Current key is a space.
      if (sentence_state == STATE_PRIMED ||
          (sentence_state == STATE_ENDING
#if SENTENCE_CASE_BUFFER_SIZE > 1
           && sentence_case_check_ending(key_buffer)
#endif  // SENTENCE_CASE_BUFFER_SIZE > 1
               )) {
        new_state = STATE_PRIMED;
        suppress_key = KC_NO;
      }
      break;

    case '\'':  // Current key is a quote.
      new_state = sentence_state;
      break;
  }

    // Slide key_buffer and state_history buffers one element to the left.
    // Optimization note: Using manual loops instead of memmove() here saved
    // ~100 bytes on AVR.
#if SENTENCE_CASE_BUFFER_SIZE > 1
  for (int8_t i = 0; i < SENTENCE_CASE_BUFFER_SIZE - 1; ++i) {
    key_buffer[i] = key_buffer[i + 1];
  }
#endif  // SENTENCE_CASE_BUFFER_SIZE > 1
  for (int8_t i = 0; i < STATE_HISTORY_SIZE - 1; ++i) {
    state_history[i] = state_history[i + 1];
  }

#if SENTENCE_CASE_BUFFER_SIZE > 1
  key_buffer[SENTENCE_CASE_BUFFER_SIZE - 1] = keycode;
  if (new_state == STATE_ENDING && !sentence_case_check_ending(key_buffer)) {
#if defined SENTENCE_CASE_DEBUG
    dprintf("Not a real ending.\n");
#endif  // SENTENCE_CASE_DEBUG
    new_state = STATE_INIT;
  }
#endif  // SENTENCE_CASE_BUFFER_SIZE > 1
  state_history[STATE_HISTORY_SIZE - 1] = sentence_state;

  set_sentence_state(new_state);
  return true;
}

bool sentence_case_just_typed_P(const uint16_t* buffer, const uint16_t* pattern,
                                int8_t pattern_len) {
#if SENTENCE_CASE_BUFFER_SIZE > 1
  buffer += SENTENCE_CASE_BUFFER_SIZE - pattern_len;
  for (int8_t i = 0; i < pattern_len; ++i) {
    if (buffer[i] != pgm_read_word(pattern + i)) {
      return false;
    }
  }
  return true;
#else
  return false;
#endif  // SENTENCE_CASE_BUFFER_SIZE > 1
}

__attribute__((weak)) bool sentence_case_check_ending(const uint16_t* buffer) {
#if SENTENCE_CASE_BUFFER_SIZE >= 5
  // Don't consider the abbreviations "vs." and "etc." to end the sentence.
  if (SENTENCE_CASE_JUST_TYPED(KC_SPC, KC_V, KC_S, KC_DOT) ||
      SENTENCE_CASE_JUST_TYPED(KC_SPC, KC_E, KC_T, KC_C, KC_DOT)) {
    return false;  // Not a real sentence ending.
  }
#endif  // SENTENCE_CASE_BUFFER_SIZE >= 5
  return true;  // Real sentence ending; capitalize next letter.
}

__attribute__((weak)) char sentence_case_press_user(uint16_t keycode,
                                                    keyrecord_t* record,
                                                    uint8_t mods) {
  if ((mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_RALT))) == 0) {
    const bool shifted = mods & MOD_MASK_SHIFT;
    switch (keycode) {
      case KC_A ... KC_Z:
        return 'a';  // Letter key.

      case KC_DOT:  // . is punctuation, Shift . is a symbol (>)
        return !shifted ? '.' : '#';
      case KC_1:
      case KC_SLSH:
        return shifted ? '.' : '#';
      case KC_EXLM:
      case KC_QUES:
        return '.';
      case KC_2 ... KC_0:  // 2 3 4 5 6 7 8 9 0
      case KC_AT ... KC_RPRN:  // @ # $ % ^ & * ( )
      case KC_MINS ... KC_SCLN:  // - = [ ] backslash ;
      case KC_UNDS ... KC_COLN:  // _ + { } | :
      case KC_GRV:
      case KC_COMM:
        return '#';  // Symbol key.

      case KC_SPC:
        return ' ';  // Space key.

      case KC_QUOT:
        return '\'';  // Quote key.
    }
  }

  // Otherwise clear Sentence Case to initial state.
  sentence_case_clear();
  return '\0';
}

__attribute__((weak)) void sentence_case_primed(bool primed) {}

#endif  // NO_ACTION_ONESHOT
