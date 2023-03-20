
typedef struct {
    bool is_press_action;
    uint8_t step;
} td_tap_t;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    TAP_AND_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};
    
uint8_t current_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) 
            return SINGLE_TAP;
        else 
            return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) 
            return DOUBLE_SINGLE_TAP; 
        else if (state->pressed)
            return TAP_AND_HOLD;
        else 
            return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

void on_tap_hold_dance(qk_tap_dance_state_t *state, void *user_data, uint16_t key) {
    if(state->count == 3) {
        tap_code16(key);
        tap_code16(key);
        tap_code16(key);
    }
    if(state->count > 3) {
        tap_code16(key);
    }
}

void on_tap_hold_dance_finished(uint8_t step, uint16_t tap_key, uint16_t hold_key) {
    switch (step) {
        case SINGLE_TAP: 
            register_code16(tap_key);
            break;
        case SINGLE_HOLD:
            register_code16(hold_key);
            break;
        case DOUBLE_TAP: 
            register_code16(tap_key);
            register_code16(tap_key);
            break;
        case DOUBLE_SINGLE_TAP: 
            tap_code16(tap_key); register_code16(tap_key);
    }
}

void on_tap_hold_dance_reset(uint8_t step, uint16_t tap_key, uint16_t hold_key) {
    wait_ms(10);
    switch (step) {
        case SINGLE_TAP:
            unregister_code16(tap_key); 
            break;
        case SINGLE_HOLD:
            unregister_code16(hold_key);
            break;
        case DOUBLE_TAP:
            unregister_code16(tap_key);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(tap_key);
            break;
    }
}

#define TD_TAP(name) static td_tap_t dance_state ##name = {.is_press_action = true, .step = 0};::

#define TD_TAP_HOLD_FUNCTIONS(name, tap_key, hold_key) \
static td_tap_t dance_state ##name = { .is_press_action = true, .step = 0 }; \
\
void tap_hold_on_dance_ ##name(qk_tap_dance_state_t *state, void *user_data) { \
    on_tap_hold_dance(state, user_data, tap_key); \
} \
\
void tap_hold_dance_finished_ ##name(qk_tap_dance_state_t *state, void *user_data) { \
    dance_state ##name.step = current_dance_step(state); \
    on_tap_hold_dance_finished(dance_state ##name.step, tap_key, hold_key); \
} \
\
void tap_hold_dance_reset_ ##name(qk_tap_dance_state_t *state, void *user_data) { \
    on_tap_hold_dance_reset(dance_state ##name.step, tap_key, hold_key); \
    dance_state ##name.step = 0; \
}

#define TD_TAP_HOLD_ACTION(name) ACTION_TAP_DANCE_FN_ADVANCED(tap_hold_on_dance_ ##name, tap_hold_dance_finished_ ##name, tap_hold_dance_reset_ ##name)

