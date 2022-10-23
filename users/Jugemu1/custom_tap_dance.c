#include "jugemu.h"
#include "eeconfig.h"
#include "eeprom.h"
#include "modes.h"

#ifdef TAP_HOLD_ENABLE
    #include "tap_hold.h"
#endif

void dance_mo1(qk_tap_dance_state_t *state, void *user_data){
    if (state->count >= 4) {
        combo_toggle();
        reset_tap_dance(state);
    }
}

void dance_modes(qk_tap_dance_state_t *state, void *user_data){
    if(!state->finished) return;
    switch(state->count){
        case 1:
            tap_switch_language();
            break;
        case 2:
            custom_combo_toggle();
            break;
        case 3:
            cycle_mode();
            break;
#ifdef TAP_HOLD_ENABLE
        case 4:
            toggle_tap_hold();
            break;
#endif
        default:
            break;
    }
}

void dance_enter_delete(qk_tap_dance_state_t *state, void *user_data){
    if(!state->finished) return;
    switch(state->count){
        case 1:
            register_code16(KC_ENTER);
            break;
        case 2:
            register_code16(KC_DELETE);
            break;
    }
}

void dance_audio(qk_tap_dance_state_t *state, void *user_data){
    if(!state->finished) return;
    switch(state->count){
        case 1:
            tap_code(KC_MPLY);
            break;
        case 2:
            tap_code(KC_MUTE);
            break;
        case 3:
            tap_code(KC_MEDIA_NEXT_TRACK);
            break;
        case 4:
            tap_code(KC_MEDIA_PREV_TRACK);
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MODE] = ACTION_TAP_DANCE_FN(dance_modes),
    [TD_PLAY_MUTE] = ACTION_TAP_DANCE_FN(dance_audio),
    [TD_LCTL_F1] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_F1),      // this doesn't work for unknown reason
    [TD_LSFT_F7] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_F7),
    [TD_LCTL_GRV] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_GRV),
    [TD_RCTL_F1] = ACTION_TAP_DANCE_DOUBLE(KC_RCTL, KC_F1),
};
