
#include "quantum.h"
#include "argos.h"
#include "process_tap_dance.h"
#include "argos_tapdance.h"
#include "raw_hid.h"

static uint8_t dance_state[ARGOS_TAP_DANCE_ENTRIES];
// Storage for Argos tap dances
static tap_dance_action_t argos_td_tap_actions[ARGOS_TAP_DANCE_ENTRIES];

// TODO have this also as an array of entries?
// static argos_td_entry_t td_entry;

static argos_td_entry_t argos_td_entries[ARGOS_TAP_DANCE_ENTRIES];

// Check if tap dance entry is enabled (bit 15 of custom_tapping_term)
#define TD_ENABLED(entry) ((entry).custom_tapping_term & 0x8000)


argos_td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }
    // TODO triple hold?
    return TD_UNKNOWN;
}

static void on_dance(tap_dance_state_t *state, void *user_data) {
    uint8_t index = (uintptr_t)user_data;
    // TODO replace this with loading the array from memory, instead of an EEPROM read...
    argos_td_entry_t *entry = argos_tap_dance_get(index);
    if (entry == NULL)
        return;
    if (!entry->enabled)
        return;
    uint16_t kc = entry->on_tap;
    if (kc) {
        if (state->count == 3) {
            argos_keycode_tap(kc);
            argos_keycode_tap(kc);
            argos_keycode_tap(kc);
        } else if (state->count > 3) {
            argos_keycode_tap(kc);
        }
    }
}

// TODO: dance reset and finished are the same??...
void on_dance_finished(tap_dance_state_t *state, void *user_data) {
    uint8_t index = (uintptr_t)user_data;
    // TODO replace this with loading the array from memory, instead of an EEPROM read...
    argos_td_entry_t *entry = argos_tap_dance_get(index);   
    if (entry == NULL)
        return;
    if (!entry->enabled)
        return;
    dance_state[index] = cur_dance(state);
    switch (dance_state[index]) {
        case TD_SINGLE_TAP: {
            if (entry->on_tap)
                argos_keycode_down(entry->on_tap);
            break;
        }
        case TD_SINGLE_HOLD: {
            if (entry->on_hold)
                argos_keycode_down(entry->on_hold);
            break;
        }
        case TD_DOUBLE_TAP: {
            if (entry->on_double_tap) {
                argos_keycode_down(entry->on_double_tap);
            } 
            break;
        }
        case TD_DOUBLE_HOLD: {
            if (entry->on_tap_hold) {
                argos_keycode_down(entry->on_tap_hold);
            } 
            break;
        }
        case TD_DOUBLE_SINGLE_TAP: {
            if (entry->on_tap) {
                argos_keycode_tap(entry->on_tap);
                argos_keycode_down(entry->on_tap);
            }
            break;
        }
    }
}

void on_dance_reset(tap_dance_state_t *state, void *user_data) {
    uint8_t index = (uintptr_t)user_data;
    argos_td_entry_t *entry = argos_tap_dance_get(index);
    if (entry == NULL)
        return;
    if (!entry->enabled)
        return;
    wait_ms(TAP_CODE_DELAY);
    uint8_t st = dance_state[index];
    state->count = 0;
    dance_state[index] = 0;
    switch (st) {
        case TD_SINGLE_TAP: {
            if (entry->on_tap)
                argos_keycode_up(entry->on_tap);
            break;
        }
        case TD_SINGLE_HOLD: {
            if (entry->on_hold)
                argos_keycode_up(entry->on_hold);
            break;
        }
        case TD_DOUBLE_TAP: {
            if (entry->on_double_tap) {
                argos_keycode_up(entry->on_double_tap);
            } 
            break;
        }
        case TD_DOUBLE_HOLD: {
            if (entry->on_tap_hold) {
                argos_keycode_up(entry->on_tap_hold);
            } 
            break;
        }
        case TD_DOUBLE_SINGLE_TAP: {
            if (entry->on_tap) {
                argos_keycode_up(entry->on_tap);
            }
            break;
        }
    }
}

void argos_reload_tap_dance(uint8_t index) {
    if (index >= ARGOS_TAP_DANCE_ENTRIES) return;
    argos_td_tap_actions[index].fn.on_each_tap = on_dance;
    argos_td_tap_actions[index].fn.on_dance_finished = on_dance_finished;
    argos_td_tap_actions[index].fn.on_reset = on_dance_reset;
    argos_td_tap_actions[index].fn.on_each_release = NULL;
    argos_td_tap_actions[index].user_data = (void*)(uintptr_t)index;
}

// TODO function to reload one specific tap dance
// TODO why does this exist?
void argos_reload_tap_dances(void) {
    for (size_t i = 0; i < ARGOS_TAP_DANCE_ENTRIES; ++i) {
        argos_reload_tap_dance(i);
    }
}

// Override the introspection function
uint16_t tap_dance_count(void) {
    return ARGOS_TAP_DANCE_ENTRIES;
}

// Override the introspection function
tap_dance_action_t* tap_dance_get(uint16_t index) {
    if (index >= ARGOS_TAP_DANCE_ENTRIES) {
        return NULL;
    }
    return &argos_td_tap_actions[index];
}

// Returns a pointer to the tap dance entry at the given index.
argos_td_entry_t* argos_tap_dance_get(uint8_t index) {
    if (index >= ARGOS_TAP_DANCE_ENTRIES) return NULL;
    return &argos_td_entries[index];
}

void argos_tap_dance_set(uint8_t index, argos_td_entry_t entry) {
    if (index >= ARGOS_TAP_DANCE_ENTRIES);
    else {
        memcpy(&argos_td_entries[index], &entry, sizeof(argos_td_entry_t));
    }
}

// Loads all tap dances from EEPROM into memory.
// Initializes the tap dance entries array before loading.
void argos_tap_dances_load_from_eeprom(void) {
    // initialize all tap dances
    memset(argos_td_entries, 0, sizeof(argos_td_entries));
    for (size_t i = 0; i < ARGOS_TAP_DANCE_ENTRIES; ++i) {
        argos_tap_dance_load_from_eeprom(i);
    }
}

// Loads a single tap dance entry from EEPROM to memory at the given index.
void argos_tap_dance_load_from_eeprom(uint8_t index) {
    argos_td_entry_t entry;
    if (argos_tap_dance_read_eeprom(index, &entry)) {
        memcpy(&argos_td_entries[index], &entry, sizeof(argos_td_entry_t));
    }
}

// Reads a tap dance entry from EEPROM for the specified index.
bool argos_tap_dance_read_eeprom(uint8_t index, argos_td_entry_t *entry) {
    if (index >= ARGOS_TAP_DANCE_ENTRIES) return false;
    argos_read_eeprom(ARGOS_OFFSET_TAP_DANCE + index * sizeof(argos_td_entry_t),
                       entry, sizeof(argos_td_entry_t));
    return true;
}

// Writes a tap dance entry to EEPROM at the specified index.
bool argos_tap_dance_write_eeprom(uint8_t index, const argos_td_entry_t *entry) {
    if (index >= ARGOS_TAP_DANCE_ENTRIES) return false;
    argos_write_eeprom(ARGOS_OFFSET_TAP_DANCE + index * sizeof(argos_td_entry_t),
                       entry, sizeof(argos_td_entry_t));
    return true;
}

// TODO resets (zero key)
void argos_tap_dance_set_keycode(uint8_t tap_dance_index, uint16_t keycode,
                             uint8_t key_index) {

    if (tap_dance_index >= ARGOS_TAP_DANCE_ENTRIES) return;
    // TODO move this to a table directly instead of reading/writing every time
    argos_td_entry_t *entry = argos_tap_dance_get(tap_dance_index);
    
    switch(key_index) {
        case 0: {
            entry->on_tap = keycode;
            break;
        }
        case 1: {
            entry->on_hold = keycode;
            break;
        }
        case 2: {
            entry->on_double_tap = keycode;
            break;
        }
        case 3: {
            entry->on_tap_hold = keycode;
            break;
        }
    }

    // enable the tap dance
    entry->enabled = true;
    // TODO: if all keys are zero, disable the tap dance

    // argos_tap_dance_set(tap_dance_index, entry);
    
    argos_tap_dance_write_eeprom(tap_dance_index, entry);
    argos_reload_tap_dance(tap_dance_index);
}