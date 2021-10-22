/* Copyright 2020 Ilya Zhuravlev
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

#include "vial.h"

#include <string.h>

#include "dynamic_keymap.h"
#include "quantum.h"
#include "vial_generated_keyboard_definition.h"

#include "vial_ensure_keycode.h"

#define VIAL_UNLOCK_COUNTER_MAX 50

#ifdef VIAL_INSECURE
#pragma message "Building Vial-enabled firmware in insecure mode."
int vial_unlocked = 1;
#else
int vial_unlocked = 0;
#endif
int vial_unlock_in_progress = 0;
static int vial_unlock_counter = 0;
static uint16_t vial_unlock_timer;

#ifndef VIAL_INSECURE
static uint8_t vial_unlock_combo_rows[] = VIAL_UNLOCK_COMBO_ROWS;
static uint8_t vial_unlock_combo_cols[] = VIAL_UNLOCK_COMBO_COLS;
#define VIAL_UNLOCK_NUM_KEYS (sizeof(vial_unlock_combo_rows)/sizeof(vial_unlock_combo_rows[0]))
_Static_assert(VIAL_UNLOCK_NUM_KEYS < 15, "Max 15 unlock keys");
_Static_assert(sizeof(vial_unlock_combo_rows) == sizeof(vial_unlock_combo_cols), "The number of unlock cols and rows should be the same");
#endif

#ifndef VIAL_ENCODER_KEYCODE_DELAY
#define VIAL_ENCODER_KEYCODE_DELAY 10
#endif

#include "qmk_settings.h"

#ifdef VIAL_TAP_DANCE_ENABLE
static void reload_tap_dance(void);
#endif

#ifdef VIAL_COMBO_ENABLE
static void reload_combo(void);
#endif

void vial_init(void) {
#ifdef VIAL_TAP_DANCE_ENABLE
    reload_tap_dance();
#endif
#ifdef VIAL_COMBO_ENABLE
    reload_combo();
#endif
}

void vial_handle_cmd(uint8_t *msg, uint8_t length) {
    /* All packets must be fixed 32 bytes */
    if (length != VIAL_RAW_EPSIZE)
        return;

    /* msg[0] is 0xFE -- prefix vial magic */
    switch (msg[1]) {
        /* Get keyboard ID and Vial protocol version */
        case vial_get_keyboard_id: {
            uint8_t keyboard_uid[] = VIAL_KEYBOARD_UID;

            memset(msg, 0, length);
            msg[0] = VIAL_PROTOCOL_VERSION & 0xFF;
            msg[1] = (VIAL_PROTOCOL_VERSION >> 8) & 0xFF;
            msg[2] = (VIAL_PROTOCOL_VERSION >> 16) & 0xFF;
            msg[3] = (VIAL_PROTOCOL_VERSION >> 24) & 0xFF;
            memcpy(&msg[4], keyboard_uid, 8);
#ifdef VIALRGB_ENABLE
            msg[12] = 1; /* bit flag to indicate vialrgb is supported - so third-party apps don't have to query json */
#endif
            break;
        }
        /* Retrieve keyboard definition size */
        case vial_get_size: {
            uint32_t sz = sizeof(keyboard_definition);
            msg[0] = sz & 0xFF;
            msg[1] = (sz >> 8) & 0xFF;
            msg[2] = (sz >> 16) & 0xFF;
            msg[3] = (sz >> 24) & 0xFF;
            break;
        }
        /* Retrieve 32-bytes block of the definition, page ID encoded within 2 bytes */
        case vial_get_def: {
            uint32_t page = msg[2] + (msg[3] << 8);
            uint32_t start = page * VIAL_RAW_EPSIZE;
            uint32_t end = start + VIAL_RAW_EPSIZE;
            if (end < start || start >= sizeof(keyboard_definition))
                return;
            if (end > sizeof(keyboard_definition))
                end = sizeof(keyboard_definition);
            memcpy_P(msg, &keyboard_definition[start], end - start);
            break;
        }
#ifdef VIAL_ENCODERS_ENABLE
        case vial_get_encoder: {
            uint8_t layer = msg[2];
            uint8_t idx = msg[3];
            uint16_t keycode = dynamic_keymap_get_encoder(layer, idx, 0);
            msg[0]  = keycode >> 8;
            msg[1]  = keycode & 0xFF;
            keycode = dynamic_keymap_get_encoder(layer, idx, 1);
            msg[2] = keycode >> 8;
            msg[3] = keycode & 0xFF;
            break;
        }
        case vial_set_encoder: {
            dynamic_keymap_set_encoder(msg[2], msg[3], msg[4], (msg[5] << 8) | msg[6]);
            break;
        }
#endif
        case vial_get_unlock_status: {
            /* Reset message to all FF's */
            memset(msg, 0xFF, length);
            /* First byte of message contains the status: whether board is unlocked */
            msg[0] = vial_unlocked;
            /* Second byte is whether unlock is in progress */
            msg[1] = vial_unlock_in_progress;
#ifndef VIAL_INSECURE
            /* Rest of the message are keys in the matrix that should be held to unlock the board */
            for (size_t i = 0; i < VIAL_UNLOCK_NUM_KEYS; ++i) {
                msg[2 + i * 2] = vial_unlock_combo_rows[i];
                msg[2 + i * 2 + 1] = vial_unlock_combo_cols[i];
            }
#endif
            break;
        }
        case vial_unlock_start: {
            vial_unlock_in_progress = 1;
            vial_unlock_counter = VIAL_UNLOCK_COUNTER_MAX;
            vial_unlock_timer = timer_read();
            break;
        }
        case vial_unlock_poll: {
#ifndef VIAL_INSECURE
            if (vial_unlock_in_progress) {
                int holding = 1;
                for (size_t i = 0; i < VIAL_UNLOCK_NUM_KEYS; ++i)
                    holding &= matrix_is_on(vial_unlock_combo_rows[i], vial_unlock_combo_cols[i]);

                if (timer_elapsed(vial_unlock_timer) > 100 && holding) {
                    vial_unlock_timer = timer_read();

                    vial_unlock_counter--;
                    if (vial_unlock_counter == 0) {
                        /* ok unlock succeeded */
                        vial_unlock_in_progress = 0;
                        vial_unlocked = 1;
                    }
                } else {
                    vial_unlock_counter = VIAL_UNLOCK_COUNTER_MAX;
                }
            }
#endif
            msg[0] = vial_unlocked;
            msg[1] = vial_unlock_in_progress;
            msg[2] = vial_unlock_counter;
            break;
        }
        case vial_lock: {
#ifndef VIAL_INSECURE
            vial_unlocked = 0;
#endif
            break;
        }
        case vial_qmk_settings_query: {
#ifdef QMK_SETTINGS
            uint16_t qsid_greater_than = msg[2] | (msg[3] << 8);
            qmk_settings_query(qsid_greater_than, msg, length);
#else
            memset(msg, 0xFF, length); /* indicate that we don't support any qsid */
#endif
            break;
        }
#ifdef QMK_SETTINGS
        case vial_qmk_settings_get: {
            uint16_t qsid = msg[2] | (msg[3] << 8);
            msg[0] = qmk_settings_get(qsid, &msg[1], length - 1);

            break;
        }
        case vial_qmk_settings_set: {
            uint16_t qsid = msg[2] | (msg[3] << 8);
            msg[0] = qmk_settings_set(qsid, &msg[4], length - 4);

            break;
        }
        case vial_qmk_settings_reset: {
            qmk_settings_reset();
            break;
        }
#endif
        case vial_dynamic_entry_op: {
            switch (msg[2]) {
            case dynamic_vial_get_number_of_entries: {
                memset(msg, 0, length);
                msg[0] = VIAL_TAP_DANCE_ENTRIES;
                msg[1] = VIAL_COMBO_ENTRIES;
                break;
            }
#ifdef VIAL_TAP_DANCE_ENABLE
            case dynamic_vial_tap_dance_get: {
                uint8_t idx = msg[3];
                vial_tap_dance_entry_t td = { 0 };
                msg[0] = dynamic_keymap_get_tap_dance(idx, &td);
                memcpy(&msg[1], &td, sizeof(td));
                break;
            }
            case dynamic_vial_tap_dance_set: {
                uint8_t idx = msg[3];
                vial_tap_dance_entry_t td;
                memcpy(&td, &msg[4], sizeof(td));
                msg[0] = dynamic_keymap_set_tap_dance(idx, &td);
                reload_tap_dance();
                break;
            }
#endif
#ifdef VIAL_COMBO_ENABLE
            case dynamic_vial_combo_get: {
                uint8_t idx = msg[3];
                vial_combo_entry_t entry = { 0 };
                msg[0] = dynamic_keymap_get_combo(idx, &entry);
                memcpy(&msg[1], &entry, sizeof(entry));
                break;
            }
            case dynamic_vial_combo_set: {
                uint8_t idx = msg[3];
                vial_combo_entry_t entry;
                memcpy(&entry, &msg[4], sizeof(entry));
                msg[0] = dynamic_keymap_set_combo(idx, &entry);
                reload_combo();
                break;
            }
#endif
            }

            break;
        }
    }
}

uint16_t g_vial_magic_keycode_override;

static void vial_keycode_down(uint16_t keycode) {
    g_vial_magic_keycode_override = keycode;

    if (keycode <= QK_MODS_MAX) {
        register_code16(keycode);
    } else {
        action_exec((keyevent_t){
            .key = (keypos_t){.row = VIAL_MATRIX_MAGIC, .col = VIAL_MATRIX_MAGIC}, .pressed = 1, .time = (timer_read() | 1) /* time should not be 0 */
        });
    }
}

static void vial_keycode_up(uint16_t keycode) {
    g_vial_magic_keycode_override = keycode;

    if (keycode <= QK_MODS_MAX) {
        unregister_code16(keycode);
    } else {
        action_exec((keyevent_t){
            .key = (keypos_t){.row = VIAL_MATRIX_MAGIC, .col = VIAL_MATRIX_MAGIC}, .pressed = 0, .time = (timer_read() | 1) /* time should not be 0 */
        });
    }
}

static void vial_keycode_tap(uint16_t keycode) __attribute__((unused));

static void vial_keycode_tap(uint16_t keycode) {
    vial_keycode_down(keycode);
    qs_wait_ms(QS_tap_code_delay);
    vial_keycode_up(keycode);
}

#ifdef VIAL_ENCODERS_ENABLE
static void exec_keycode(uint16_t keycode) {
    vial_keycode_down(keycode);

#if VIAL_ENCODER_KEYCODE_DELAY > 0
    wait_ms(VIAL_ENCODER_KEYCODE_DELAY);
#endif

    vial_keycode_up(keycode);
}

bool vial_encoder_update(uint8_t index, bool clockwise) {
    uint16_t code;

    layer_state_t layers = layer_state | default_layer_state;
    /* check top layer first */
    for (int8_t i = MAX_LAYER - 1; i >= 0; i--) {
        if (layers & (1UL << i)) {
            code = dynamic_keymap_get_encoder(i, index, clockwise);
            if (code != KC_TRNS) {
                exec_keycode(code);
                return true;
            }
        }
    }
    /* fall back to layer 0 */
    code = dynamic_keymap_get_encoder(0, index, clockwise);
    exec_keycode(code);

    return true;
}
#endif

#ifdef VIAL_TAP_DANCE_ENABLE
#include "process_tap_dance.h"

/* based on ZSA configurator generated code */

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static uint8_t dance_state[VIAL_TAP_DANCE_ENTRIES];
static vial_tap_dance_entry_t td_entry;

static uint8_t dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

static void on_dance(qk_tap_dance_state_t *state, void *user_data) {
    uint8_t index = (uintptr_t)user_data;
    if (dynamic_keymap_get_tap_dance(index, &td_entry) != 0)
        return;
    uint16_t kc = td_entry.on_tap;
    if (kc) {
        if (state->count == 3) {
            vial_keycode_tap(kc);
            vial_keycode_tap(kc);
            vial_keycode_tap(kc);
        } else if (state->count > 3) {
            vial_keycode_tap(kc);
        }
    }
}

static void on_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
    uint8_t index = (uintptr_t)user_data;
    if (dynamic_keymap_get_tap_dance(index, &td_entry) != 0)
        return;
    dance_state[index] = dance_step(state);
    switch (dance_state[index]) {
        case SINGLE_TAP: {
            if (td_entry.on_tap)
                vial_keycode_down(td_entry.on_tap);
            break;
        }
        case SINGLE_HOLD: {
            if (td_entry.on_hold)
                vial_keycode_down(td_entry.on_hold);
            else if (td_entry.on_tap)
                vial_keycode_down(td_entry.on_tap);
            break;
        }
        case DOUBLE_TAP: {
            if (td_entry.on_double_tap) {
                vial_keycode_down(td_entry.on_double_tap);
            } else if (td_entry.on_tap) {
                vial_keycode_tap(td_entry.on_tap);
                vial_keycode_down(td_entry.on_tap);
            }
            break;
        }
        case DOUBLE_HOLD: {
            if (td_entry.on_tap_hold) {
                vial_keycode_down(td_entry.on_tap_hold);
            } else {
                if (td_entry.on_tap) {
                    vial_keycode_tap(td_entry.on_tap);
                    if (td_entry.on_hold)
                        vial_keycode_down(td_entry.on_hold);
                    else
                        vial_keycode_down(td_entry.on_tap);
                } else if (td_entry.on_hold) {
                    vial_keycode_down(td_entry.on_hold);
                }
            }
            break;
        }
        case DOUBLE_SINGLE_TAP: {
            if (td_entry.on_tap) {
                vial_keycode_tap(td_entry.on_tap);
                vial_keycode_down(td_entry.on_tap);
            }
            break;
        }
    }
}

static void on_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
    uint8_t index = (uintptr_t)user_data;
    if (dynamic_keymap_get_tap_dance(index, &td_entry) != 0)
        return;
    qs_wait_ms(QS_tap_code_delay);
    uint8_t st = dance_state[index];
    state->count = 0;
    dance_state[index] = 0;
    switch (st) {
        case SINGLE_TAP: {
            if (td_entry.on_tap)
                vial_keycode_up(td_entry.on_tap);
            break;
        }
        case SINGLE_HOLD: {
            if (td_entry.on_hold)
                vial_keycode_up(td_entry.on_hold);
            else if (td_entry.on_tap)
                vial_keycode_up(td_entry.on_tap);
            break;
        }
        case DOUBLE_TAP: {
            if (td_entry.on_double_tap) {
                vial_keycode_up(td_entry.on_double_tap);
            } else if (td_entry.on_tap) {
                vial_keycode_up(td_entry.on_tap);
            }
            break;
        }
        case DOUBLE_HOLD: {
            if (td_entry.on_tap_hold) {
                vial_keycode_up(td_entry.on_tap_hold);
            } else {
                if (td_entry.on_tap) {
                    if (td_entry.on_hold)
                        vial_keycode_up(td_entry.on_hold);
                    else
                        vial_keycode_up(td_entry.on_tap);
                } else if (td_entry.on_hold) {
                    vial_keycode_up(td_entry.on_hold);
                }
            }
            break;
        }
        case DOUBLE_SINGLE_TAP: {
            if (td_entry.on_tap) {
                vial_keycode_up(td_entry.on_tap);
            }
            break;
        }
    }
}

qk_tap_dance_action_t tap_dance_actions[VIAL_TAP_DANCE_ENTRIES] = { };

/* Load timings from eeprom into custom_tapping_term */
static void reload_tap_dance(void) {
    for (size_t i = 0; i < VIAL_TAP_DANCE_ENTRIES; ++i) {
        vial_tap_dance_entry_t td;
        tap_dance_actions[i].fn.on_each_tap = on_dance;
        tap_dance_actions[i].fn.on_dance_finished = on_dance_finished;
        tap_dance_actions[i].fn.on_reset = on_dance_reset;
        tap_dance_actions[i].user_data = (void*)i;
        if (dynamic_keymap_get_tap_dance(i, &td) == 0) {
            tap_dance_actions[i].custom_tapping_term = td.custom_tapping_term;
        }
    }
}
#endif

#ifdef VIAL_COMBO_ENABLE
combo_t key_combos[VIAL_COMBO_ENTRIES] = { };
uint16_t key_combos_keys[VIAL_COMBO_ENTRIES][5];

static void reload_combo(void) {
    /* initialize with all keys = COMBO_END */
    memset(key_combos_keys, 0, sizeof(key_combos_keys));
    memset(key_combos, 0, sizeof(key_combos));

    /* reload from eeprom */
    for (size_t i = 0; i < VIAL_COMBO_ENTRIES; ++i) {
        uint16_t *seq = key_combos_keys[i];
        key_combos[i].keys = seq;

        vial_combo_entry_t entry;
        if (dynamic_keymap_get_combo(i, &entry) == 0) {
            memcpy(seq, entry.input, sizeof(entry.input));
            key_combos[i].keycode = entry.output;
        }
    }
}
#endif

#ifdef VIAL_TAP_DANCE_ENABLE
void process_tap_dance_action_on_dance_finished(qk_tap_dance_action_t *action);
#endif

bool process_record_vial(uint16_t keycode, keyrecord_t *record) {
#ifdef VIAL_TAP_DANCE_ENABLE
    /* process releases before tap-dance timeout arrives */
    if (!record->event.pressed && keycode >= QK_TAP_DANCE && keycode <= QK_TAP_DANCE_MAX) {
        uint16_t idx = keycode - QK_TAP_DANCE;
        if (dynamic_keymap_get_tap_dance(idx, &td_entry) != 0)
            return true;

        qk_tap_dance_action_t *action = &tap_dance_actions[idx];

        /* only care about 2 possibilities here
           - tap and hold set, everything else unset: process first release early (count == 1)
           - double tap set: process second release early (count == 2)
         */
        if ((action->state.count == 1 && td_entry.on_tap && td_entry.on_hold && !td_entry.on_double_tap && !td_entry.on_tap_hold)
            || (action->state.count == 2 && td_entry.on_double_tap)) {
                action->state.pressed = false;
                process_tap_dance_action_on_dance_finished(action);
                /* reset_tap_dance() will get called in process_tap_dance() */
            }
    }
#endif

    return true;
}
