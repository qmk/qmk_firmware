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

#include "process_combo.h"

#include "action_tapping.h"

#ifdef DEBUG_COMBO
#    include "debug.h"
#else
#    include "nodebug.h"
#endif

#include "quantum.h"

// to be defined using make_combo.hpp
extern const combo_storage                       combos;
__attribute__((weak)) const combo_storage combos PROGMEM = {.keys = {}, .layer_count = 0, .layers = NULL, .combos = NULL};

// customization point
__attribute__((weak)) uint16_t key_combo_term(uint16_t keycode, const keyrecord_t *record) { return 0; }

static const combo_data *COMBO_RELEASED = (const combo_data *)-1;
static const uint8_t     CMB_NO         = 0xff;

typedef struct {
    keyrecord_t       record;
    uint16_t          deadline;  // the time until which a combo must be fired, or else it's considered a non-combo key
    const combo_data *combo;     // the active (!) combo this key is a part of, or NULL, or COMBO_RELEASED
} key_entry_t;

static bool        b_combo_enable  = true;  // toggles the whole combo feature
static bool        is_deadline_set = false;
static uint16_t    next_deadline   = 0;  // the next time when some combo term expires, if is_deadline_set
static key_entry_t key_buffer[COMBO_BUFFER_SIZE];
static uint8_t     key_buffer_size = 0;
static uint16_t    key_mask[COMBO_KEY_BLOCKS_COUNT];  // accounts for currently pressed combo keys, except for ones in active combos
static uint8_t     last_pressed_layer = 0;            // the layer that was active while the latest key was pressed down

#ifndef NO_ACTION_TAPPING
static bool mt_lt_pressed = false;
#endif

static void debug_combo_key_mask(void) {
    dprintf("key_mask: ");
    for (uint8_t i = 0; i < COMBO_KEY_COUNT; ++i) {
        dprintf("%u", (key_mask[i / 16] >> (i % 16)) & 1);
    }
    dprintf("\n");
}

static inline combo_metadata get_combo_metadata(const combo_data *combo) {
    const uint16_t word = pgm_read_word(&combo->metadata);
    combo_metadata metadata;
    metadata.packed = word;
    return metadata;
}

static inline void add_key_to_mask(uint8_t combo_key) {
    dprintf("add_key_to_mask combo_key=%u\n", combo_key);
    if (combo_key != CMB_NO) key_mask[combo_key / 16] |= (1 << (combo_key % 16));
    debug_combo_key_mask();
}

static inline void remove_key_from_mask(uint8_t combo_key) {
    dprintf("remove_key_from_mask combo_key=%u\n", combo_key);
    if (combo_key != CMB_NO) key_mask[combo_key / 16] &= ~(1 << (combo_key % 16));
    debug_combo_key_mask();
}

static inline uint8_t get_combo_key(const keyrecord_t *record) {
    const keypos_t pos = record->event.key;
    if (pos.row >= MATRIX_ROWS || pos.col >= MATRIX_COLS) return 0xff;
    return pgm_read_byte(&combos.keys[pos.row][pos.col]);
}

static inline bool time_less(uint16_t less, uint16_t greater) { return timer_expired(greater, less); }

static inline bool combo_contains_key(uint8_t combo_key, const combo_data *combo) { return pgm_read_word(&combo->key_mask[combo_key / 16]) & (1 << (combo_key % 16)); }

// O(COMBO_KEY_BLOCKS_COUNT)
static bool is_combo_pressed(const combo_data *combo) {
    for (uint8_t i = 0; i < COMBO_KEY_BLOCKS_COUNT; ++i) {
        if (pgm_read_word(&combo->key_mask[i]) & ~key_mask[i]) return false;
    }
    return true;
}

// O(COMBO_KEY_BLOCKS_COUNT)
static bool are_nested_combos(const combo_data *inner, const combo_data *outer) {
    for (uint8_t i = 0; i < COMBO_KEY_BLOCKS_COUNT; ++i) {
        const uint16_t inner_mask = pgm_read_word(&inner->key_mask[i]);
        const uint16_t outer_mask = pgm_read_word(&outer->key_mask[i]);
        if (inner_mask & ~outer_mask) return false;
    }
    return true;
}

static inline keyrecord_t combo_record(uint16_t keycode, uint16_t time, bool pressed) {
    keyrecord_t record = {
        .event =
            {
                .key     = {.col = 254, .row = 254},  // col/row == 255 is reserved for noop
                .time    = time | 1,                  // time == 0 is reserved for noop
                .pressed = pressed,
            },
        .keycode = keycode,
    };
    return record;
}

static inline void prepare_action_tap(uint16_t keycode, const keyrecord_t *record) {
#ifndef NO_ACTION_TAPPING
    switch (action_for_keycode(keycode).kind.id) {
        case ACT_LAYER_TAP:
        case ACT_LAYER_TAP_EXT:
        case ACT_LMODS_TAP:
        case ACT_RMODS_TAP:
            if (record->event.pressed) mt_lt_pressed = true;
            dprintf("prepare_action_tap pressed=%u\n", record->event.pressed);
            break;
        default:
            break;
    }
#endif
}

static inline void trigger_prepared_action_tap(uint16_t now) {
#ifndef NO_ACTION_TAPPING
    if (!mt_lt_pressed) return;
    dprintf("trigger_prepared_action_tap: tapping CMB_DUMMY\n");
    mt_lt_pressed = false;

    // Feed the dummy into action tapping to trigger the layer tap
    keyrecord_t record = combo_record(CMB_DUMMY, now, true);
    action_tapping_process(record);
    record.event.pressed = false;
    action_tapping_process(record);
#endif
}

static inline bool process_special_keys(uint16_t keycode, const keyrecord_t *record) {
    const bool pressed = record->event.pressed;

    switch (keycode) {
        case CMB_ON:
            if (pressed) combo_enable();
            return true;
        case CMB_OFF:
            if (pressed) combo_disable();
            return true;
        case CMB_TOG:
            if (pressed) combo_toggle();
            return true;
        default:
            return false;
    }
}

static inline void emit_keypress(uint16_t keycode, const keyrecord_t *record) {
    if (!IS_NOEVENT(record->event)) dprintf("emit_keypress keycode=%u pressed=%u\n", keycode, record->event.pressed);
    if (process_special_keys(keycode, record)) return;

#ifndef NO_ACTION_TAPPING
    if (!IS_NOEVENT(record->event)) prepare_action_tap(keycode, record);
    action_tapping_process(*record);
#else
    process_record(record);
#endif
}

static void send_combo(const combo_data *combo, bool pressed, uint16_t time) {
    switch (get_combo_metadata(combo).unpacked.action_type) {
        case COMBO_ACTION_KEYCODE: {
            const uint16_t keycode = pgm_read_word(&combo->action.keycode);
            dprintf("send_combo keycode=%u pressed=%u\n", keycode, pressed);
            keyrecord_t record = combo_record(keycode, time, pressed);
            emit_keypress(keycode, &record);
            break;
        }
        case COMBO_ACTION_FUNCTION: {
            const combo_callback function = (combo_callback)pgm_read_ptr(&combo->action.function);
            dprintf("send_combo function pressed=%u\n", pressed);
            function(pressed);
            break;
        }
        case COMBO_ACTION_STRING: {
            const char *string = (const char *)pgm_read_ptr(&combo->action.string);
            dprintf("send_combo string pressed=%u\n", pressed);
            if (pressed) send_string_P(string);
            break;
        }
        default: {
            break;
        }
    }
}

static inline void bump_next_deadline(uint16_t deadline) {
    if (!is_deadline_set) {
        is_deadline_set = true;
        next_deadline   = deadline;
    } else if (time_less(deadline, next_deadline)) {
        next_deadline = deadline;
    }
}

static const uint8_t KEY_NOT_FOUND = 0xff;

// O(COMBO_BUFFER_SIZE)
static uint8_t find_position_in_key_buffer(keypos_t pos) {
    for (uint8_t idx = 0; idx < key_buffer_size; ++idx) {
        if (KEYEQ(key_buffer[idx].record.event.key, pos)) {
            return idx;
        }
    }
    return KEY_NOT_FOUND;
}

// O(COMBO_BUFFER_SIZE)
static void remove_from_key_buffer(uint8_t key_buffer_pos) {
    if (key_buffer_pos == KEY_NOT_FOUND) return;
    for (uint8_t idx = key_buffer_pos + 1; idx < key_buffer_size; ++idx) {
        key_buffer[idx - 1] = key_buffer[idx];
    }
    --key_buffer_size;
}

static inline void put_key_into_key_buffer(uint16_t keycode, const keyrecord_t *record, uint16_t key_deadline) {
    if (key_buffer_size >= COMBO_BUFFER_SIZE) {
        dprintf("put_key_into_key_buffer: key buffer overflow keycode=%u\n", keycode);
        return;
    }

    key_buffer[key_buffer_size].record         = *record;
    key_buffer[key_buffer_size].record.keycode = keycode;
    key_buffer[key_buffer_size].deadline       = key_deadline;
    key_buffer[key_buffer_size].combo          = NULL;
    ++key_buffer_size;

    bump_next_deadline(key_deadline);
}

// A combo has been completely pressed, and (usually) its combo term has passed - emit the combo's keycode
// O(COMBO_BUFFER_SIZE)
static void fire_combo(const combo_data *combo) {
    dprintln("fire_combo");
    uint16_t combo_pressed_time = 0;

    // point related keys from key buffer to this combo, also find the time when the combo was fully pressed
    for (uint8_t idx = 0; idx < key_buffer_size; ++idx) {
        const uint8_t combo_key = get_combo_key(&key_buffer[idx].record);

        if (combo_contains_key(combo_key, combo)) {
            key_buffer[idx].combo = combo;

            // remove from pressed keys to prevent other combos from taking the key
            remove_key_from_mask(combo_key);

            const uint16_t key_pressed_time = key_buffer[idx].record.event.time;
            if (combo_pressed_time == 0 || time_less(combo_pressed_time, key_pressed_time)) {
                combo_pressed_time = key_pressed_time;
            }
        }
    }

    // press the virtual key
    send_combo(combo, true, combo_pressed_time);
}

// A key has not participated in any combo in time
// O(COMBO_BUFFER_SIZE)
static void fire_key(uint8_t key_buffer_pos) {
    dprintf("fire_key keycode=%u\n", key_buffer[key_buffer_pos].record.keycode);

    keyrecord_t *  record  = &key_buffer[key_buffer_pos].record;
    const uint16_t keycode = record->keycode;
    if (!record->event.pressed) record->keycode = 0;  // action tap expects non-combo keys to have keycode=0
    emit_keypress(keycode, record);
    remove_from_key_buffer(key_buffer_pos);
}

// O(COMBO_BUFFER_SIZE)
static void process_foreign_key(uint16_t keycode, const keyrecord_t *record) {
    if (record->event.pressed) {
        uint16_t combo_term = key_combo_term(keycode, record);
        if (combo_term != 0) {
            put_key_into_key_buffer(keycode, record, record->event.time + combo_term);
        } else {
            emit_keypress(keycode, record);
        }
    } else {
        const uint8_t pos = find_position_in_key_buffer(record->event.key);
        if (pos != KEY_NOT_FOUND) {
            fire_key(pos);                   // process the previous press as a non-combo
            emit_keypress(keycode, record);  // process the current release
        } else {
            // the released key does not belong to any combos
            emit_keypress(keycode, record);
        }
    }
}

// O(COMBO_BUFFER_SIZE)
static void release_owning_combo(const combo_data *combo, uint16_t now) {
    if (combo == COMBO_RELEASED) return;

    send_combo(combo, false, now);

    for (uint8_t idx = 0; idx < key_buffer_size; ++idx) {
        if (key_buffer[idx].combo == combo) {
            key_buffer[idx].combo = COMBO_RELEASED;
        }
    }
}

typedef struct {
    const combo_data *best_combo;
    bool              is_combo_part;
    uint16_t          combo_term;
} find_combo_result;

// NOTE combo_key must be present in key_flags!
// O(layer.combo_count * COMBO_KEY_BLOCKS_COUNT)
static find_combo_result find_combo_with_key(uint8_t combo_key) {
    const uint8_t layer_count = pgm_read_byte(&combos.layer_count);

    if (last_pressed_layer >= layer_count || combo_key == CMB_NO) {
        return (find_combo_result){.best_combo = NULL, .is_combo_part = false, .combo_term = 0};
    };

    const combo_layer_data *layer_data    = (const combo_layer_data *)pgm_read_ptr(&combos.layers) + last_pressed_layer;
    const uint16_t          combos_offset = pgm_read_word(&layer_data->combo_offset);
    const uint16_t          combo_count   = pgm_read_word(&layer_data->combo_count);
    const combo_data *      combo_begin   = (const combo_data *)pgm_read_ptr(&combos.combos) + combos_offset;

    find_combo_result result = {.best_combo = NULL, .is_combo_part = false, .combo_term = 0};
    dprintf("find_combo_with_key: searching combos with combo_key=%u\n", combo_key);

    for (uint16_t i = 0; i < combo_count; ++i) {
        const combo_data *combo = combo_begin + i;

        if (!combo_contains_key(combo_key, combo)) continue;
        result.is_combo_part = true;

        const uint16_t curr_combo_term = get_combo_metadata(combo).unpacked.combo_term;
        if (curr_combo_term > result.combo_term) result.combo_term = curr_combo_term;

        if (!is_combo_pressed(combo)) {  // O(COMBO_KEY_BLOCKS_COUNT)
            // skip non-pressed combo
            dprintf("find_combo_with_key: discarding non-pressed combo combo_index=%u\n", i);
        } else if (result.best_combo == NULL) {
            // first pressed combo found
            dprintf("find_combo_with_key: new best combo combo_index=%u\n", i);
            result.best_combo = combo;
        } else if (are_nested_combos(result.best_combo, combo)) {  // O(COMBO_KEY_BLOCKS_COUNT)
            // the new combo contains the old one and thus is better
            dprintf("find_combo_with_key: new best combo combo_index=%u\n", i);
            result.best_combo = combo;
        } else {
            // the old combo contains the new one, or they are disjoint
            dprintf("find_combo_with_key: discarding combo combo_index=%u\n", i);
        }
    }

    if (result.best_combo == NULL) dprintf("find_combo_with_key: pressed combo not found\n");
    if (!result.is_combo_part) dprintf("find_combo_with_key: no combo contains the key\n");

    return result;
}

static void check_combo_key_buffer(bool flush_all, uint16_t now) {
    is_deadline_set = false;
    next_deadline   = 0;

    for (uint8_t idx = 0; idx < key_buffer_size; ++idx) {
        key_entry_t *entry = &key_buffer[idx];
        if (entry->combo != NULL) continue;  // key participates in an active combo

        if (flush_all || time_less(now, entry->deadline)) {
            bump_next_deadline(entry->deadline);
            continue;
        }

        const uint8_t combo_key = get_combo_key(&entry->record);

        const find_combo_result result = find_combo_with_key(combo_key);

        if (result.best_combo != NULL) {
            dprintf("check_combo_key_buffer firing combo keycode=%u\n", entry->record.keycode);
            fire_combo(result.best_combo);
        } else {
            dprintf("check_combo_key_buffer firing key keycode=%u\n", entry->record.keycode);
            remove_key_from_mask(combo_key);
            fire_key(idx);
            --idx;  // revisit the same key buffer pos
        }
    }
}

static inline void flush_on_layer_switch(void) {
    const uint8_t current_layer = get_highest_layer(layer_state);
    if (current_layer == last_pressed_layer) return;

    dprintf("process_combo layer switched, firing keys from key buffer\n");
    check_combo_key_buffer(true, 0);
    last_pressed_layer = current_layer;
}

// The entry point to combos
void process_combo(const keyrecord_t *record) {
    const bool pressed = record->event.pressed;

    if (IS_NOEVENT(record->event) || (pressed && !b_combo_enable)) {
        const uint16_t keycode = get_record_keycode(record, pressed);
        emit_keypress(keycode, record);
        return;
    }

    dprintf("BEGIN process_combo key_buffer_size=%u pressed=%u\n", key_buffer_size, pressed);

    if (pressed) {
        trigger_prepared_action_tap(record->event.time);
        flush_on_layer_switch();
        const uint16_t keycode = get_record_keycode(record, pressed);
        dprintf("process_combo keycode=%u\n", keycode);

        const uint8_t combo_key = get_combo_key(record);
        if (combo_key == CMB_NO) {
            process_foreign_key(keycode, record);
            dprintf("END process_combo path=1 key_buffer_size=%u\n\n", key_buffer_size);
            return;
        }
        add_key_to_mask(combo_key);

        const find_combo_result result = find_combo_with_key(combo_key);

        if (!result.is_combo_part) {
            process_foreign_key(keycode, record);
            remove_key_from_mask(combo_key);
            dprintf("END process_combo path=2 key_buffer_size=%u\n\n", key_buffer_size);
            return;
        }

        put_key_into_key_buffer(keycode, record, record->event.time + result.combo_term);

        if (result.best_combo != NULL && get_combo_metadata(result.best_combo).unpacked.urgent) {
            fire_combo(result.best_combo);
        }
        dprintf("END process_combo path=3 key_buffer_size=%u\n\n", key_buffer_size);
    } else {
        const uint8_t key_buffer_pos = find_position_in_key_buffer(record->event.key);

        if (key_buffer_pos == KEY_NOT_FOUND) {
            const uint16_t keycode = get_record_keycode(record, pressed);
            dprintf("process_combo keycode=%u\n", keycode);

            process_foreign_key(keycode, record);
            dprintf("END process_combo path=4 key_buffer_size=%u\n\n", key_buffer_size);
            return;
        }

        const uint16_t keycode = key_buffer[key_buffer_pos].record.keycode;
        dprintf("process_combo keycode=%u\n", keycode);

        const uint8_t combo_key = get_combo_key(record);

        const combo_data *owning_combo = key_buffer[key_buffer_pos].combo;
        if (owning_combo == NULL) {
            const find_combo_result result = find_combo_with_key(combo_key);
            if (result.best_combo == NULL) {
                fire_key(key_buffer_pos);        // process the previous press as a non-combo
                emit_keypress(keycode, record);  // process the current release
                remove_key_from_mask(combo_key);
                dprintf("END process_combo path=5 key_buffer_size=%u\n\n", key_buffer_size);
                return;
            }
            fire_combo(result.best_combo);
            owning_combo = result.best_combo;
        }

        remove_from_key_buffer(key_buffer_pos);
        release_owning_combo(owning_combo, record->event.time);
        dprintf("END process_combo path=6 key_buffer_size=%u\n\n", key_buffer_size);
    }
}

// Executes periodically
void matrix_scan_combo(void) {
    const uint16_t now = timer_read();
    if (!is_deadline_set || !time_less(next_deadline, now)) return;

    dprint("BEGIN matrix_scan_combo\n");
    check_combo_key_buffer(false, now);
    dprint("END matrix_scan_combo\n\n");
}

void combo_enable(void) { b_combo_enable = true; }

void combo_disable(void) { b_combo_enable = false; }

void combo_toggle(void) { b_combo_enable = !b_combo_enable; }

bool is_combo_enabled(void) { return b_combo_enable; }
