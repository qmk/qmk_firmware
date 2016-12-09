#include "process_combo.h"
#include "print.h"

// __attribute__ ((weak))
// combo_t key_combos[] = {

// };

#define SEND_KEY(key) \
do { \
    register_code16(key); \
    send_keyboard_report(); \
    unregister_code16(key); \
} while(0)


#define ALL_COMBO_KEYS_ARE_DOWN (((1<<count)-1) == combo->state)
static bool process_single_combo(combo_t *combo, uint16_t keycode, keyrecord_t *record) 
{
    uint8_t count = 0;
    bool is_combo_key = false;
    // bool combo_key_released = false;

    // Count the number of combo keys
    for (const uint16_t *key = combo->keys; COMBO_END != pgm_read_word(key); ++key, ++count);

    for (uint8_t i = 0; i < count; ++i) {
        uint16_t key = pgm_read_word(&combo->keys[i]);

        if (key == keycode) {
            is_combo_key = true;

            if (record->event.pressed) {
                combo->state |= (1<<i);
            } else { // Combo key released
                if (!combo->state) {
                    // The combo was sent, no need to send released key
                    return true;
                }

                combo->state &= ~(1<<i);
                SEND_KEY(key);
            }
        }
    }

    if (ALL_COMBO_KEYS_ARE_DOWN) {
        SEND_KEY(combo->action);
        combo->state = 0;    
    }

    return is_combo_key;
}


bool process_combo(uint16_t keycode, keyrecord_t *record)
{
    bool is_combo_key = false;

    for (int i = 0; i < NUM_ELEMS(key_combos); ++i) {
        combo_t *combo = &key_combos[i];
        is_combo_key |= process_single_combo(combo, keycode, record);
    }    

    return !is_combo_key;
}