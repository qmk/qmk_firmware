#include "333fred.h"
#include "quantum.h"
#include "action.h"

typedef enum {
    SINGLE_TAP, SINGLE_HOLD, DOUBLE
} tap_dance_state_enum;

static tap_dance_state_enum tap_dance_state;
static bool tap_dance_active = false;

void tap_dance_sym_vim_finished(qk_tap_dance_state_t *state, void *user_data) {
    // Determine the current state
    if (state->count == 1) {
        if (state->interrupted || state->pressed == 0) tap_dance_state = SINGLE_TAP;
        else tap_dance_state = SINGLE_HOLD;
    } else {
        // Handle any number of other taps as a VIM movement hold
        tap_dance_state = DOUBLE;
    }

    switch (tap_dance_state) {
        case SINGLE_TAP:
            if (tap_dance_active) {
                reset_oneshot_layer();
                tap_dance_active = false;
            } else {
                set_oneshot_layer(SYMB, ONESHOT_START);
                tap_dance_active = true;
            }
            break;
        case SINGLE_HOLD:
            layer_on(SYMB);
            break;
        case DOUBLE:
            layer_on(VIM);
            break;
    }
}

void tap_dance_sym_vim_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch(tap_dance_state) {
        case SINGLE_TAP:
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case SINGLE_HOLD:
            layer_off(SYMB);
            break;
        case DOUBLE:
            layer_off(VIM);
            break;
    }
}

void tap_dance_copy_paste_finished(qk_tap_dance_state_t *state, void *user_data) {
    bool is_paste = state->count == 2;
    // If either the one-shot shift is set, or if shift is being held, count as shift being held.
    // We'll clear the one-shot shift if it was held
    uint8_t one_shot_mods = get_oneshot_mods();
    bool is_shift = false;

    if (get_mods() & MOD_MASK_SHIFT) {
        is_shift = true;
    } else if (one_shot_mods & MOD_MASK_SHIFT) {
        set_oneshot_mods(one_shot_mods & ~MOD_MASK_SHIFT);
        is_shift = true;
    }

    if (is_paste) {
        if (is_shift) {
            SEND_STRING(SS_LSFT(SS_TAP(X_INSERT)));
        } else {
            SEND_STRING(SS_LCTRL("v"));
        }
    } else {
        if (is_shift) {
            SEND_STRING(SS_LCTRL(SS_TAP(X_INSERT)));
        } else {
            SEND_STRING(SS_LCTRL("c"));
        }
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SYM_VIM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_dance_sym_vim_finished, tap_dance_sym_vim_reset),
    [TD_COPY_PASTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_dance_copy_paste_finished, NULL)
};

void tap_dance_process_keycode(uint16_t keycode) {
    if (tap_dance_state == SINGLE_TAP && keycode != TD(TD_SYM_VIM)) {
        tap_dance_active = false;
    }
}

__attribute__ ((weak))
void layer_state_set_rgb(uint32_t state) {}

uint32_t layer_state_set_user(uint32_t state) {
  layer_state_set_rgb(state);
  return state;
}

bool try_handle_macro(uint16_t keycode, keyrecord_t *record) {
    switch (keycode)
    {
        case DLEFT:
            if (record->event.pressed)
                SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_LEFT))));
            return true;
        case DRIGHT:
            if (record->event.pressed)
                SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_RIGHT))));
            return true;
        case PSCREEN_APP:
            if (record->event.pressed)
                SEND_STRING(SS_LALT(SS_TAP(X_PSCREEN)));
            return true;

        default:
            return false;
    }
}
