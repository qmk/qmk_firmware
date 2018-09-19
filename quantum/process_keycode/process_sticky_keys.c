#include "process_sticky_keys.h"

#ifdef STICKY_KEYS_ENABLE

#include <stdbool.h>
#include "keycode.h"
#include "action.h"
#include "quantum.h"

#define SHIFT_KEY_TAPS_TO_TOGGLE 5

enum sticky_keys_activation_states {
  OFF = 0,
  ON
};

enum sticky_keys_modifier_names {
  CTRL = 0,
  SHIFT,
  ALT,
  GUI
};

enum sticky_keys_modifier_states {
  NONE = 0,
  APPLIED,
  LOCKED
};

uint16_t sticky_keys_modifier_active_states[] = {
  [CTRL] = NONE,
  [SHIFT] = NONE,
  [ALT] = NONE,
  [GUI] = NONE
};

uint16_t sticky_keys_keycodes[] = {
  [CTRL] = KC_LCTRL,
  [SHIFT] = KC_LSHIFT,
  [ALT] = KC_LALT,
  [GUI] = KC_LGUI
};

uint8_t sticky_keys_enabled = OFF;
uint8_t sticky_keys_continuous_shift_taps = 0;

void sticky_keys_toggle(void) {
  sticky_keys_enabled = sticky_keys_enabled == OFF ? ON : OFF;
  sticky_keys_continuous_shift_taps = 0;
  sticky_keys_clear_modifiers();
}

void sticky_keys_clear_modifiers() {
  for (int modifier = CTRL; modifier <= GUI; modifier++) {
    sticky_keys_modifier_active_states[modifier] = NONE;
    unregister_mods(MOD_BIT(sticky_keys_keycodes[modifier]));
  }
}

void sticky_keys_clear_non_locked_modifiers() {
  for (int modifier = CTRL; modifier <= GUI; modifier++) {
    if(sticky_keys_modifier_active_states[modifier] != LOCKED) {
      sticky_keys_modifier_active_states[modifier] = NONE;
      unregister_mods(MOD_BIT(sticky_keys_keycodes[modifier]));
    }
  }
}

void sticky_keys_cycle_modifier_state(int modifier) {
  sticky_keys_modifier_active_states[modifier] += 1 % (LOCKED + 1);
}

int sticky_keys_get_modifiers() {
  int mods = 0x00;
  for (int modifier = CTRL; modifier <= GUI; modifier++) {
    if(sticky_keys_modifier_active_states[modifier] != NONE) {
      mods |= MOD_BIT(sticky_keys_keycodes[modifier]);
    }
  }
  return mods;
}

bool process_sticky_keys(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_LCTRL:
    case KC_RCTRL:
      if (record->event.pressed && sticky_keys_enabled) {
        sticky_keys_cycle_modifier_state(CTRL);
      }
      break;
    case KC_LSHIFT:
    case KC_RSHIFT:
      if (record->event.pressed) {
        if(sticky_keys_enabled) {
          sticky_keys_cycle_modifier_state(SHIFT);
        }
        sticky_keys_continuous_shift_taps++;
        if(sticky_keys_continuous_shift_taps == SHIFT_KEY_TAPS_TO_TOGGLE) {
          sticky_keys_toggle();
        }
      }
      break;
    case KC_LALT:
    case KC_RALT:
      if (record->event.pressed && sticky_keys_enabled) {
        sticky_keys_cycle_modifier_state(ALT);
      }
      break;
    case KC_LGUI:
    case KC_RGUI:
      if (record->event.pressed && sticky_keys_enabled) {
        sticky_keys_cycle_modifier_state(GUI);
      }
      break;
    default:
      if (record->event.pressed && sticky_keys_enabled) {
        register_mods(sticky_keys_get_modifiers());
        register_code(keycode);
        sticky_keys_clear_non_locked_modifiers();
      }
      break;
  }

  if(!(keycode == KC_LSHIFT || keycode == KC_RSHIFT)) {
    sticky_keys_continuous_shift_taps = 0;
  }
  return false;
}

#endif
