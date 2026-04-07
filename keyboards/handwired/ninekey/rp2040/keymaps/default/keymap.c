#include QMK_KEYBOARD_H
#include "quantum.h"

// =============================================================================
// TAP DANCE DEFINITIONS
// =============================================================================

enum {
    TD_01
};

// Tap dance: tap = play/pause, double tap = stop, 5+ taps = bootloader
void dance_flsh_media(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_MEDIA_PLAY_PAUSE);
    }
}

// Stop media on double tap
void dance_flsh_stop(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        tap_code16(KC_MEDIA_STOP);
    }
}

// Enter bootloader mode on 5+ taps
void dance_flsh_flash(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 5) {
        tap_code16(QK_BOOT);
    }
}

// Configure tap dance behavior
tap_dance_action_t tap_dance_actions[] = {
    [TD_01] = ACTION_TAP_DANCE_FN_ADVANCED(dance_flsh_media, dance_flsh_stop, dance_flsh_flash)
};

// =============================================================================
// COMBO DEFINITIONS
// =============================================================================

enum combo_events {
    BOOT_COMBO
};

// Combo: VOL_DOWN + MUTE = QK_BOOT
const uint16_t PROGMEM boot_combo_keys[] = {KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, COMBO_END};

combo_t key_combos[] = {
    [BOOT_COMBO] = COMBO(boot_combo_keys, QK_BOOT)
};

// Require combo keys to be held
#ifdef COMBO_MUST_HOLD_PER_COMBO
bool get_combo_must_hold(uint16_t combo_index, combo_t *combo) {
    (void)combo;
    switch (combo_index) {
        case BOOT_COMBO:
            return true;
    }
    return false;
}
#endif

// =============================================================================
// CUSTOM KEYCODE DEFINITIONS
// =============================================================================

enum custom_keycodes {
    CSM = SAFE_RANGE,  // Ctrl+Shift+M: toggle mute in Teams
    CSH,               // Ctrl+Shift+H: close video call in Teams
    PREV_TRK,          // Tap: previous track | Hold 500ms: rewind
    NEXT_TRK           // Tap: next track | Hold 500ms: fast forward
};

// Media track hold state tracking
static uint16_t prev_trk_timer = 0;
static bool     prev_trk_active = false;
static bool     prev_trk_held = false;
static uint16_t next_trk_timer = 0;
static bool     next_trk_active = false;
static bool     next_trk_held = false;

// =============================================================================
// KEYPRESS PROCESSING
// =============================================================================

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CSM:
            if (record->event.pressed) {
                tap_code16(C(S(KC_M)));
            }
            break;

        case CSH:
            if (record->event.pressed) {
                tap_code16(C(S(KC_H)));
            }
            break;

        // Previous track: tap = prev track, hold 500ms = rewind
        case PREV_TRK:
            if (record->event.pressed) {
                prev_trk_timer = timer_read();
                prev_trk_active = true;
                prev_trk_held = false;
            } else {
                if (prev_trk_held) {
                    unregister_code(KC_MEDIA_REWIND);
                } else {
                    tap_code(KC_MEDIA_PREV_TRACK);
                }
                prev_trk_active = false;
                prev_trk_held = false;
            }
            return false;

        // Next track: tap = next track, hold 500ms = fast forward
        case NEXT_TRK:
            if (record->event.pressed) {
                next_trk_timer = timer_read();
                next_trk_active = true;
                next_trk_held = false;
            } else {
                if (next_trk_held) {
                    unregister_code(KC_MEDIA_FAST_FORWARD);
                } else {
                    tap_code(KC_MEDIA_NEXT_TRACK);
                }
                next_trk_active = false;
                next_trk_held = false;
            }
            return false;
    }
    return true;
};


// =============================================================================
// MATRIX SCANNING - TIMER-BASED HOLD DETECTION
// =============================================================================

void matrix_scan_user(void) {
    // Detect PREV_TRK hold after 500ms
    if (prev_trk_active && !prev_trk_held && timer_elapsed(prev_trk_timer) >= 500) {
        prev_trk_held = true;
        register_code(KC_MEDIA_REWIND);
    }
    // Detect NEXT_TRK hold after 500ms
    if (next_trk_active && !next_trk_held && timer_elapsed(next_trk_timer) >= 500) {
        next_trk_held = true;
        register_code(KC_MEDIA_FAST_FORWARD);
    }
};

// =============================================================================
// KEYMAP DEFINITIONS
// =============================================================================

enum layers {
    NORMAL_LAYER = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Default layer: 3x3 ortholinear
    // Row 0: PrtScn, CSM, CSH
    // Row 1: PREV_TRK, Media Ctrl (tap dance), NEXT_TRK
    // Row 2: Volume Down, Volume Up, Mute
    [NORMAL_LAYER] = LAYOUT_ortho_3x3(
        KC_PSCR,          CSM,              CSH,
        PREV_TRK,         TD(TD_01),        NEXT_TRK,
        KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_AUDIO_MUTE
    )
};

