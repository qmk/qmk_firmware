#include "process_combo.h"
#include "print.h"

#define SEND_KEY(key) \
do { \
    register_code16(key); \
    send_keyboard_report(); \
    unregister_code16(key); \
} while(0)

#define COMBO_TIMER_ELAPSED -1

#if COMBO_TERM
#define IS_COMBO_KEY_HELD(combo)            (COMBO_TIMER_ELAPSED == combo->timer ? false : true)
#define RESET_COMBO_TIMER_AND_KEY(combo)    combo->timer = 0; combo->key = 0
#else
#define IS_COMBO_KEY_HELD(combo)            (true)
#define RESET_COMBO_TIMER_AND_KEY(combo)    do {} while (0)
#endif


__attribute__ ((weak))
combo_t key_combos[COMBO_COUNT] = {

};

static inline void reset_combo(combo_t *combo)
{
    combo->state = 0;
    RESET_COMBO_TIMER_AND_KEY(combo);
}

#define ALL_COMBO_KEYS_ARE_DOWN (((1<<count)-1) == combo->state)
#define NO_COMBO_KEYS_ARE_DOWN  (0 == combo->state)
#define KEY_STATE_DOWN(key)     do{ combo->state |= (1<<key); } while(0)
#define KEY_STATE_UP(key)       do{ combo->state &= ~(1<<key); } while(0)
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
    if (-1 == index) return false;

    bool is_combo_active = IS_COMBO_KEY_HELD(combo);

    if (record->event.pressed) {
        KEY_STATE_DOWN(index);
        
#if COMBO_TERM
        if (is_combo_active) {
            combo->timer = timer_read();
            combo->key = keycode;
        }
#endif

    } else {
        if (is_combo_active && combo->state) { /* Combo key was tapped */
            RESET_COMBO_TIMER_AND_KEY(combo);            
            SEND_KEY(keycode);
        }

#if COMBO_TERM
        if (!is_combo_active && keycode == combo->key) { /* Held combo key was released */
            unregister_code16(combo->key);
        }
#endif

        KEY_STATE_UP(index);
    }

    if (ALL_COMBO_KEYS_ARE_DOWN && is_combo_active) {
        SEND_KEY(combo->action);
        reset_combo(combo);
    } 
    
    if(NO_COMBO_KEYS_ARE_DOWN && !is_combo_active) {
        reset_combo(combo);
    }

    return is_combo_active;
}

bool process_combo(uint16_t keycode, keyrecord_t *record)
{
    bool is_combo_key = false;

    for (int i = 0; i < COMBO_COUNT; ++i) {
        combo_t *combo = &key_combos[i];
        is_combo_key |= process_single_combo(combo, keycode, record);
    }    

    return !is_combo_key;
}

void matrix_scan_combo(void)
{
#if COMBO_TERM
    for (int i = 0; i < COMBO_COUNT; ++i) {
        combo_t *combo = &key_combos[i];
        if (combo->timer && 
            combo->timer != COMBO_TIMER_ELAPSED && 
            timer_elapsed(combo->timer) > COMBO_TERM) {

            combo->timer = COMBO_TIMER_ELAPSED;
            unregister_code16(combo->key);
            register_code16(combo->key);
        }
    }
#endif
}