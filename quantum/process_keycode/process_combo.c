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
#include "print.h"


#define COMBO_TIMER_ELAPSED -1


__attribute__ ((weak))
combo_t key_combos[COMBO_COUNT] = {

};

__attribute__ ((weak))
void process_combo_event(uint8_t combo_index, bool pressed) {

}

static uint8_t current_combo_index = 0;

static inline void send_combo(uint16_t action, bool pressed)
{
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

#define ALL_COMBO_KEYS_ARE_DOWN     (((1<<count)-1) == combo->state)
#define NO_COMBO_KEYS_ARE_DOWN      (0 == combo->state)
#define KEY_STATE_DOWN(key)         do{ combo->state |= (1<<key); } while(0)
#define KEY_STATE_UP(key)           do{ combo->state &= ~(1<<key); } while(0)
static bool process_single_combo(combo_t *combo, uint16_t keycode, keyrecord_t *record) 
{
    uint8_t count = 0;
    uint8_t index = -1;
    /* Find index of keycode and number of combo keys */
    for (const uint16_t *keys = combo->keys; ;++count) {
        uint16_t key = pgm_read_word(&keys[count]);
        if (keycode == key) index = count;
        if (COMBO_END == key) break;
    }

    /* Return if not a combo key */
    if (-1 == (int8_t)index) return false;

    /* The combos timer is used to signal whether the combo is active */
    bool is_combo_active = COMBO_TIMER_ELAPSED == combo->timer ? false : true;

    if (record->event.pressed) {
        KEY_STATE_DOWN(index);

        if (is_combo_active) {
            if (ALL_COMBO_KEYS_ARE_DOWN) { /* Combo was pressed */
                send_combo(combo->keycode, true);
                combo->timer = COMBO_TIMER_ELAPSED;
            } else { /* Combo key was pressed */
                combo->timer = timer_read();
#ifdef COMBO_ALLOW_ACTION_KEYS
                combo->prev_record = *record;
#else
                combo->prev_key = keycode;
#endif
            }
        }
    } else {
        if (ALL_COMBO_KEYS_ARE_DOWN) { /* Combo was released */
            send_combo(combo->keycode, false);
        }

        if (is_combo_active) { /* Combo key was tapped */
#ifdef COMBO_ALLOW_ACTION_KEYS
            record->event.pressed = true;
            process_action(record, store_or_get_action(record->event.pressed, record->event.key));
            record->event.pressed = false;
            process_action(record, store_or_get_action(record->event.pressed, record->event.key));
#else
            register_code16(keycode);
            send_keyboard_report();
            unregister_code16(keycode);
#endif
            combo->timer = 0;            
        }

        KEY_STATE_UP(index);        
    }

    if (NO_COMBO_KEYS_ARE_DOWN) {
        combo->timer = 0;
    }

    return is_combo_active;
}

bool process_combo(uint16_t keycode, keyrecord_t *record)
{
    bool is_combo_key = false;

    for (current_combo_index = 0; current_combo_index < COMBO_COUNT; ++current_combo_index) {
        combo_t *combo = &key_combos[current_combo_index];
        is_combo_key |= process_single_combo(combo, keycode, record);
    }    

    return !is_combo_key;
}

void matrix_scan_combo(void)
{
    for (int i = 0; i < COMBO_COUNT; ++i) {
        // Do not treat the (weak) key_combos too strict.
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Warray-bounds"
        combo_t *combo = &key_combos[i];
        #pragma GCC diagnostic pop
        if (combo->timer &&
            combo->timer != COMBO_TIMER_ELAPSED && 
            timer_elapsed(combo->timer) > COMBO_TERM) {
            
            /* This disables the combo, meaning key events for this
             * combo will be handled by the next processors in the chain 
             */
            combo->timer = COMBO_TIMER_ELAPSED;

#ifdef COMBO_ALLOW_ACTION_KEYS
            process_action(&combo->prev_record, 
                store_or_get_action(combo->prev_record.event.pressed, 
                                    combo->prev_record.event.key));
#else
            unregister_code16(combo->prev_key);
            register_code16(combo->prev_key);
#endif
        }
    }
}
