// Copyright 2021-2025 Google LLC
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
 * @file select_word.c
 * @brief Select Word community module implementation
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/select-word>
 */

#include "select_word.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

// Default to a timeout of 5 seconds.
#ifndef SELECT_WORD_TIMEOUT
#  define SELECT_WORD_TIMEOUT  5000
#endif  // SELECT_WORD_TIMEOUT

static int8_t selection_dir = 0;
static bool reset_before_next_event = false;
static uint8_t registered_hotkey = KC_NO;

// Macro `IS_MAC` determines whether to use Mac vs. Windows/Linux hotkeys:
//
// * OS Detection is used if it is enabled.
//
// * With SELECT_WORD_OS_DYNAMIC, the user may define callback
//   select_word_host_is_mac().
//
// * Otherwise, the assumed OS is set at compile time, to Window/Linux by
//   default, or to Mac with SELECT_WORD_OS_MAC.
#if defined(SELECT_WORD_OS_DYNAMIC) || defined(OS_DETECTION_ENABLE)
__attribute__((weak)) bool select_word_host_is_mac(void) {
#  ifdef OS_DETECTION_ENABLE  // Use OS Detection if enabled.
  switch (detected_host_os()) {
    case OS_LINUX:
    case OS_WINDOWS:
      return false;
    case OS_MACOS:
    case OS_IOS:
      return true;
    default:
      break;
  }
#  endif  // OS_DETECTION_ENABLE
#  ifdef SELECT_WORD_OS_MAC
  return true;
#  else
  return false;
#  endif  // SELECT_WORD_OS_MAC
}
#  define IS_MAC select_word_host_is_mac()
#else
#  ifdef SELECT_WORD_OS_MAC
#  define IS_MAC true
#  else
#  define IS_MAC false
#  endif  // SELECT_WORD_OS_MAC
#endif  // defined(SELECT_WORD_OS_DYNAMIC) || defined(OS_DETECTION_ENABLE)

// Idle timeout timer to reset Select Word after a period of inactivity.
#if SELECT_WORD_TIMEOUT > 0
# if SELECT_WORD_TIMEOUT < 100 || SELECT_WORD_TIMEOUT > 30000
// Constrain timeout to a sensible range. With the 16-bit timer, the longest
// representable timeout is 32768 ms, rounded here to 30000 ms = half a minute.
#   error "select_word: SELECT_WORD_TIMEOUT must be between 100 and 30000 ms"
# endif

static uint16_t idle_timer = 0;

static void restart_idle_timer(void) {
  idle_timer = (timer_read() + SELECT_WORD_TIMEOUT) | 1;
}

void housekeeping_task_select_word(void) {
  if (idle_timer && timer_expired(timer_read(), idle_timer)) {
    idle_timer = 0;
    selection_dir = 0;
  }
}
#endif  // SELECT_WORD_TIMEOUT > 0

static void clear_all_mods(void) {
  clear_mods();
  clear_weak_mods();
#ifndef NO_ACTION_ONESHOT
  clear_oneshot_mods();
#endif  // NO_ACTION_ONESHOT
}

static void select_word_in_dir(int8_t dir) {
  // With Windows and Linux (non-Mac) systems:
  // dir < 0: Backward word selection: Ctrl+Left, Ctrl+Right, Ctrl+Shift+Left.
  // dir > 0: Forward word selection: Ctrl+Right, Ctrl+Left, Ctrl+Shift+Right.
  // Or to extend an existing selection:
  // dir < 0: Backward word selection: Ctrl+Shift+Left.
  // dir > 0: Forward word selection: Ctrl+Shift+Right.
  //
  // With Mac OS, use Alt (Opt) instead of Ctrl:
  // dir < 0: Backward word selection: Alt+Left, Alt+Right, Alt+Shift+Left.
  // dir > 0: Forward word selection: Alt+Right, Alt+Left, Alt+Shift+Right.
  // Or to extend an existing selection:
  // dir < 0: Backward word selection: Alt+Shift+Left.
  // dir > 0: Forward word selection: Alt+Shift+Right.
  reset_before_next_event = false;
  const uint8_t saved_mods = get_mods();
  clear_all_mods();

  if (selection_dir && (selection_dir < 0) != (dir < 0)) {  // Reversal.
    send_keyboard_report();
    tap_code_delay((dir < 0) ? KC_RGHT : KC_LEFT, TAP_CODE_DELAY);
  }

  add_mods(IS_MAC ? MOD_BIT_LALT : MOD_BIT_LCTRL);

  if (selection_dir == 0) {  // Initial selection.
    send_keyboard_report();
    send_string_with_delay_P(
        (dir < 0) ? PSTR(SS_TAP(X_LEFT) SS_TAP(X_RGHT))
                  : PSTR(SS_TAP(X_RGHT) SS_TAP(X_LEFT)),
        TAP_CODE_DELAY);
  }

  register_mods(MOD_BIT_LSHIFT);
  registered_hotkey = (dir < 0) ? KC_LEFT : KC_RGHT;
  register_code(registered_hotkey);

  set_mods(saved_mods);
  selection_dir = dir;
}

static void select_line(void) {
  // With Windows and Linux (non-Mac) systems:
  // Home, Shift+End.
  // Or to extend an existing selection:
  // Shift+Down.
  //
  // With Mac OS, use GUI (Command) + arrows:
  // GUI+Left, Shift+GUI+Right.
  // Or to extend an existing selection:
  // Shift+Down.
  reset_before_next_event = false;
  const uint8_t saved_mods = get_mods();
  clear_all_mods();

  if (selection_dir != 2) {
    send_keyboard_report();
    send_string_with_delay_P(
        IS_MAC ? PSTR(SS_LGUI(SS_TAP(X_LEFT) SS_LSFT(SS_TAP(X_RGHT))))
               : PSTR(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END))),
        TAP_CODE_DELAY);
  } else {
    register_mods(MOD_BIT_LSHIFT);
    registered_hotkey = KC_DOWN;
    register_code(KC_DOWN);
  }

  set_mods(saved_mods);
  selection_dir = 2;
}

void select_word_register(char action) {
  if (registered_hotkey) {
    select_word_unregister();
  }

  switch (action) {
    case 'W':
      select_word_in_dir(1);
      break;
    case 'B':
      select_word_in_dir(-1);
      break;
    case 'L':
      select_line();
      break;
  }

#if SELECT_WORD_TIMEOUT > 0
  idle_timer = 0;
#endif  // SELECT_WORD_TIMEOUT > 0
}

void select_word_unregister(void) {
  reset_before_next_event = false;
  unregister_code(registered_hotkey);

  if (registered_hotkey == KC_DOWN) {
    // When using line selection to select multiple lines, tap Shift+End (or on
    // Mac, GUI+Shift+Right) on release to ensure the selection extends to the
    // end of the current line.
    const uint8_t saved_mods = get_mods();
    clear_all_mods();
    send_keyboard_report();
    send_string_with_delay_P(
        IS_MAC ? PSTR(SS_LGUI(SS_LSFT(SS_TAP(X_RGHT))))
               : PSTR(SS_LSFT(SS_TAP(X_END))),
        TAP_CODE_DELAY);
    set_mods(saved_mods);
  }

  registered_hotkey = KC_NO;
#if SELECT_WORD_TIMEOUT > 0
  restart_idle_timer();
#endif  // SELECT_WORD_TIMEOUT > 0
}

bool process_record_select_word(uint16_t keycode, keyrecord_t* record) {
  if (!process_record_select_word_kb(keycode, record)) {
    return false;
  }

  if (selection_dir) {
    if (reset_before_next_event) {
      selection_dir = 0;
    }

    // Ignore most modifier and layer switch keys.
    switch (keycode) {
      case MODIFIER_KEYCODE_RANGE:
      case QK_MOMENTARY ... QK_MOMENTARY_MAX:
      case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
      case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
      case QK_TO ... QK_TO_MAX:
      case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
#ifndef NO_ACTION_ONESHOT
      case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
      case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
#endif  // NO_ACTION_ONESHOT
#ifdef LAYER_LOCK_ENABLE
      case QK_LLCK:
#endif  // LAYER_LOCK_ENABLE
        return true;
#ifndef NO_ACTION_TAPPING
      // Ignore hold events on mod-tap and layer-tap keys.
      case QK_MOD_TAP ... QK_MOD_TAP_MAX:
      case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        if (record->tap.count == 0) {
          return true;
        }
        break;
#endif  // NO_ACTION_TAPPING
    }

    reset_before_next_event = true;
  }

#if SELECT_WORD_TIMEOUT > 0
  if (idle_timer) {
    restart_idle_timer();
  }
#endif  // SELECT_WORD_TIMEOUT > 0

  const bool shifted = MOD_MASK_SHIFT & (get_mods() | get_weak_mods()
#ifndef NO_ACTION_ONESHOT
     | get_oneshot_mods()
#endif  // NO_ACTION_ONESHOT
    );

  switch (keycode) {
    case SELECT_WORD:
      if (record->event.pressed) {
        select_word_register(shifted ? 'L' : 'W');
      } else {
        select_word_unregister();
      }
      return false;

    case SELECT_WORD_BACK:
      if (record->event.pressed) {
        select_word_register('B');
      } else {
        select_word_unregister();
      }
      return false;

    case SELECT_LINE:
      if (record->event.pressed) {
        select_word_register('L');
      } else {
        select_word_unregister();
      }
      return false;
  }

  return true;
}

