// Copyright 2026 Quentin LEBASTARD <bstkbd@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "argos.h"
#include "eeconfig.h"
#include "eeprom.h"
#include "keymap_introspection.h"
#include "nvm_eeprom_eeconfig_internal.h"
#include "nvm_eeprom_via_internal.h"
#include "quantum.h"
#include "raw_hid.h"
#include "version.h"
#include "via.h"
#include <stdlib.h>
#include <time.h>

#include "argos_combo.h"
#include "process_combo.h"

/*
    argos_combos_QMK_data is used to store the combos
    in the same way that QMK does.
    It is loaded from eeprom, and read from eeprom.
    The limitation is that we can't modify the input keys (const),
    So instead we use a custom data storage of definite size.
*/
static combo_t argos_combos_QMK_data[ARGOS_COMBO_ENTRIES];
// +1 for COMBO_END terminator
static uint16_t argos_combo_keys[ARGOS_COMBO_ENTRIES][ARGOS_KEYS_PER_COMBO + 1];

// TODO deal with disabled combos?
// TODO deal with NULL combos?... right now we set everything to zero
// or... just communicate them to the webapp and let it handle it
void argos_combos_load_from_eeprom() {
    // initialize all combos
    memset(argos_combo_keys, 0, sizeof(argos_combo_keys));
    memset(argos_combos_QMK_data, 0, sizeof(argos_combos_QMK_data));

    for (int i = 0; i < ARGOS_COMBO_ENTRIES; i++) {
        argos_combo_load_from_eeprom(i);
    }
}

void argos_combo_load_from_eeprom(uint8_t index) {
    uint16_t *keys = argos_combo_keys[index];
    argos_combos_QMK_data[index].keys = keys;

    argos_combo_t entry;
    if (argos_combo_read_eeprom(index, &entry)) {
        memcpy(keys, entry.keys, sizeof(entry.keys));
        // Ensure null termination
        keys[ARGOS_KEYS_PER_COMBO] = COMBO_END;
        argos_combos_QMK_data[index].keycode = entry.keycode;
        // TODO manage disabled combos... with a custom array probably
    }
}

// Override
uint16_t combo_count(void) { return ARGOS_COMBO_ENTRIES; }

/*
    Since we have custom combos loaded, we want QMK to process those instead of
   the ones set during compilation. To do this, QMK provides a handy weak
   function: combo_get We can override it, and return our custom combos
*/
combo_t *combo_get(uint16_t combo_idx) {
    if (combo_idx >= ARGOS_COMBO_ENTRIES) {
        return NULL;
    }

    // Test for one key only:
    // If there's only one key in the combo, bad things happen.
    // This could happen when editing combos from the webapp interface
    // So, if there's one key only, then we don't process it
    if (argos_combos_QMK_data[combo_idx].keys[1] == 0)
        return NULL;

    return &argos_combos_QMK_data[combo_idx];
}

/*
We use regular combos -->
    typedef struct combo_t {
        const uint16_t *keys;
        uint16_t        keycode;
        bool     disabled;
        bool     active;
        uint8_t state;
    }
*/

/*
    Copies QMK's combos into eeprom, so that we can modify them later.
    Done only once ever
*/
void argos_combos_copy_from_QMK(void) {
    // TODO for now we will load all combos even if they're set to zero.
    // Later we need to find a way on how to stop when we reach the end.
    for (int i = 0; i < ARGOS_COMBO_ENTRIES; i++) {
        combo_t *combo = combo_get_raw(i);

        // we need to convert from combo_t to argos_combo_t before saving to
        // eeprom
        argos_combo_t comboNew = {.keys = {0},
                                  .keycode = combo->keycode,
                                  .disabled = combo->disabled,
                                  .active = combo->active,
                                  .state = combo->state};

        // Combos will always be returned, because we override the size of of
        // the combos array in introspection.h So instead, to test if a combo
        // exists, we test if the resulting keycode is 0 If it does not exist,
        // the keys will stay at 0 We have to do this, because otherwise QMK
        // will return garbage data for the keys
        if (combo->keycode != 0) {
            // We might have a combo that's smaller than 4 keys.
            // Then, we need to find the first key that is a 0 and set the rest
            // of them to 0
            bool last_key_reached = false;
            for (int j = 0; j < ARGOS_KEYS_PER_COMBO; j++) {
                if (last_key_reached) {
                    comboNew.keys[j] = 0;
                } else if (combo->keys[j] == 0) {
                    last_key_reached = true;
                } else {
                    comboNew.keys[j] = combo->keys[j];
                }
            }
        }

        argos_combo_write_eeprom(i, &comboNew);
    }
}

// TODO this function is quite big... but separating it into smaller functions
// would require an unpacker (since combo_t is packed), so we big function it
// is!
void argos_combo_set_keycode(uint8_t combo_index, uint16_t keycode,
                             uint8_t key_index) {
    // Send back the data to the GUI so it knows we received the command
    uint8_t data[32] = {0};
    data[0] = ARGOS_CMD_PREFIX;
    raw_hid_send(data, sizeof(data));

    argos_combo_t combo;
    argos_combo_read_eeprom(combo_index, &combo);

    bool is_valid = false;
    
    // key result
    if (key_index == 0) {
        combo.keycode = keycode;
        is_valid = true;
    }
    // key input
    else if ((key_index - 1 < ARGOS_KEYS_PER_COMBO) &&
    key_index - 1 >= 0) {
        // Test for duplicates:
        // QMK does not like it when there are multiple of the same keys in the
        // combo. So we need to find any potential duplicates and set them to
        // zero. The "zeros" will be handled right after.
        is_valid = true;
        for (int i = 0; i < ARGOS_KEYS_PER_COMBO; i++) {
            if (combo.keys[i] == keycode) {
                // We don't want to mark a 0 as duplicate, as it's used to
                // delete keys or mark the end of the combo.
                if (combo.keys[i] != 0) {
                    is_valid = false;
                    break;
                }
            }
        }

        if (is_valid) {
            combo.keys[key_index - 1] = keycode;

            // It's possible the user deleted a key in the middle of the input
            // keys, or is assigning a key with an empty key in between We don't
            // want to delete that key, otherwise QMK will end the combo
            // prematurely Instead, we want to shift the other keys to the left.
            // Then we want to delete any zeros in between, and assign the rest
            // to zeros. We don't need to process the last key, because either
            // it's set to zero, or shifted when an earlier key is deleted
            uint8_t deleted_keys = 0;
            for (int i = 0; i < ARGOS_KEYS_PER_COMBO - 1; i++) {
                if (combo.keys[i] == 0) {
                    // Shift everything by one to the left
                    for (int j = i; j < ARGOS_KEYS_PER_COMBO - 1; j++) {
                        combo.keys[j] = combo.keys[j + 1];
                    }
                    combo.keys[ARGOS_KEYS_PER_COMBO - 1 - deleted_keys] = 0;
                    deleted_keys++;
                }
            }
        }
    }

    if (is_valid) {
        // Save the newly created combo in memory
        argos_combo_write_eeprom(combo_index, &combo);

        // Reload combo: we can do this without touching eeprom, because we
        // already have the data in memory This saves on eeprom read/writes
        uint16_t *keys = argos_combo_keys[combo_index];
        // Ensure null termination
        keys[ARGOS_KEYS_PER_COMBO] = COMBO_END;
        argos_combos_QMK_data[combo_index].keys = keys;

        memcpy(keys, combo.keys, sizeof(combo.keys));
        argos_combos_QMK_data[combo_index].keycode = combo.keycode;
        // ----- End reload combo -----
    }
}

combo_t argos_combo_get(uint8_t index) {
    if (index < ARGOS_COMBO_ENTRIES) {
        return argos_combos_QMK_data[index];
    }
    return (combo_t){0};
}

bool argos_combo_read_eeprom(uint8_t index, argos_combo_t *combo) {
    if (index >= ARGOS_COMBO_ENTRIES)
        return false;
    argos_read_eeprom(ARGOS_OFFSET_COMBO + index * sizeof(argos_combo_t), combo,
                      sizeof(argos_combo_t));
    return true;
}

void argos_combo_write_eeprom(uint8_t index, argos_combo_t *combo) {
    if (index >= ARGOS_COMBO_ENTRIES)
        return;
    argos_write_eeprom(ARGOS_OFFSET_COMBO + index * sizeof(argos_combo_t),
                       combo, sizeof(argos_combo_t));
}