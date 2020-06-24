#include "snowkuma.h"
#include "process_records.h"

// Tap Dance Definitions
void kraken_safe_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 3) {
        // Reset the keyboard if you tap the key more than three times
        reset_keyboard();
        reset_tap_dance(state);
    } else {
        SEND_STRING(SS_LGUI(" "));
        SEND_STRING("GitKraken.app\n");
    }
};

void zoom_toggle(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(G(S(KC_A)));
    } else if (state->count >= 2) {
        tap_code16(G(S(KC_V)));
    }
}

void anki_assimil(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING(SS_LGUI(" "));
        SEND_STRING("Anki.app\n");
    } else if (state->count > 1) {
        SEND_STRING(SS_LGUI(" "));
        SEND_STRING("PlayAssimil.app\n");
    }
}

void copy_cut(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        tap_code16(G(KC_X));
    } else {
        tap_code16(G(KC_C));
    }
};

void tilde_home(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        // Outputs ~/ if tilde tapped twice
        tap_code16(KC_TILD);
        tap_code16(KC_SLSH);
    } else {
        tap_code16(KC_TILD);
    }
}

void typefu_telegram(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING(SS_LGUI(" "));
        SEND_STRING("TypeFu.app\n");
    } else if (state->count > 1) {
        SEND_STRING(SS_LGUI(" "));
        SEND_STRING("Telegram.app\n");
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ANKASS] = ACTION_TAP_DANCE_FN(anki_assimil),
    [TD_COPYCUT] = ACTION_TAP_DANCE_FN(copy_cut),
    [TD_LBRC_BACK] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, LGUI(KC_LBRC)),
    [TD_RBRC_FWD] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, LGUI(KC_RBRC)),
    [TD_KRAKEN] = ACTION_TAP_DANCE_FN(kraken_safe_reset),
    [TD_TILD] = ACTION_TAP_DANCE_FN(tilde_home),
    [TD_TYPTEL] = ACTION_TAP_DANCE_FN(typefu_telegram),
    [TD_ZOOM] = ACTION_TAP_DANCE_FN(zoom_toggle)};
