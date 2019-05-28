/* Copyright 2016 Jack Humbert
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

#include "print.h"
#include "process_combo.h"

__attribute__((weak)) combo_t key_combos[COMBO_COUNT] = {

};

__attribute__((weak)) void process_combo_event(uint8_t combo_index,
                                               bool pressed) {}

static uint16_t timer = 0;
static uint8_t current_combo_index = 0;
static bool drop_buffer = false;
static bool is_active = false;

static uint8_t buffer_size = 0;
#ifdef COMBO_ALLOW_ACTION_KEYS
static keyrecord_t key_buffer[MAX_COMBO_LENGTH];
#else
static uint16_t key_buffer[MAX_COMBO_LENGTH];
#endif

static inline void send_combo(uint16_t action, bool pressed) {
  if (action) {
    if (pressed) {
      register_code16(action);
    } else {
      unregister_code16(action);
    }
  } else {
    process_combo_event(current_combo_index, pressed);
  }
}

static inline void dump_key_buffer(bool emit) {
  if (buffer_size == 0) {
    return;
  }

  if (emit) {
    for (uint8_t i = 0; i < buffer_size; i++) {
#ifdef COMBO_ALLOW_ACTION_KEYS
      const action_t action = store_or_get_action(key_buffer[i].event.pressed,
                                                  key_buffer[i].event.key);
      process_action(&(key_buffer[i]), action);
#else
      register_code16(key_buffer[i]);
      send_keyboard_report();
#endif
    }
  }

  buffer_size = 0;
}

#define ALL_COMBO_KEYS_ARE_DOWN (((1 << count) - 1) == combo->state)
#define KEY_STATE_DOWN(key)                                                    \
  do {                                                                         \
    combo->state |= (1 << key);                                                \
  } while (0)
#define KEY_STATE_UP(key)                                                      \
  do {                                                                         \
    combo->state &= ~(1 << key);                                               \
  } while (0)

static bool process_single_combo(combo_t *combo, uint16_t keycode,
                                 keyrecord_t *record) {
  uint8_t count = 0;
  uint8_t index = -1;
  /* Find index of keycode and number of combo keys */
  for (const uint16_t *keys = combo->keys;; ++count) {
    uint16_t key = pgm_read_word(&keys[count]);
    if (keycode == key)
      index = count;
    if (COMBO_END == key)
      break;
  }

  /* Continue processing if not a combo key */
  if (-1 == (int8_t)index)
    return false;

  bool is_combo_active = is_active;

  if (record->event.pressed) {
    KEY_STATE_DOWN(index);

    if (is_combo_active) {
      if (ALL_COMBO_KEYS_ARE_DOWN) { /* Combo was pressed */
        send_combo(combo->keycode, true);
        drop_buffer = true;
      }
    }
  } else {
    if (ALL_COMBO_KEYS_ARE_DOWN) { /* Combo was released */
      send_combo(combo->keycode, false);
    } else {
      /* continue processing without immediately returning */
      is_combo_active = false;
    }

    KEY_STATE_UP(index);
  }

  return is_combo_active;
}

#define NO_COMBO_KEYS_ARE_DOWN (0 == combo->state)

bool process_combo(uint16_t keycode, keyrecord_t *record) {
  bool is_combo_key = false;
  drop_buffer = false;
  bool no_combo_keys_pressed = true;

  for (current_combo_index = 0; current_combo_index < COMBO_COUNT;
       ++current_combo_index) {
    combo_t *combo = &key_combos[current_combo_index];
    is_combo_key |= process_single_combo(combo, keycode, record);
    no_combo_keys_pressed = no_combo_keys_pressed && NO_COMBO_KEYS_ARE_DOWN;
  }

  if (drop_buffer) {
    /* buffer is only dropped when we complete a combo, so we refresh the timer
     * here */
    timer = timer_read();
    dump_key_buffer(false);
  } else if (!is_combo_key) {
    /* if no combos claim the key we need to emit the keybuffer */
    dump_key_buffer(true);

    // reset state if there are no combo keys pressed at all
    if (no_combo_keys_pressed) {
      timer = 0;
      is_active = true;
    }
  } else if (record->event.pressed && is_active) {
    /* otherwise the key is consumed and placed in the buffer */
    timer = timer_read();

    if (buffer_size < MAX_COMBO_LENGTH) {
#ifdef COMBO_ALLOW_ACTION_KEYS
      key_buffer[buffer_size++] = *record;
#else
      key_buffer[buffer_size++] = keycode;
#endif
    }
  }

  return !is_combo_key;
}

void matrix_scan_combo(void) {
  if (is_active && timer && timer_elapsed(timer) > COMBO_TERM) {

    /* This disables the combo, meaning key events for this
     * combo will be handled by the next processors in the chain
     */
    is_active = false;
    dump_key_buffer(true);
  }
}
