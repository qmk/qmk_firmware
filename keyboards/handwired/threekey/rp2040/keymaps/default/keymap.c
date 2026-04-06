#include QMK_KEYBOARD_H
#include "quantum.h"

// Enums for TapDances:
enum {
    TD_01
};

void dance_flsh_media(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_MEDIA_PLAY_PAUSE);
    }
}
void dance_flsh_stop(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        tap_code16(KC_MEDIA_STOP);
    }
}
void dance_flsh_flash(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 5) {
         tap_code16(QK_BOOT);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_01] = ACTION_TAP_DANCE_FN_ADVANCED(dance_flsh_media, dance_flsh_stop, dance_flsh_flash)
};

// Define a custom keycode
enum custom_keycodes {
    CSH = SAFE_RANGE, // Ctrl+Shift+H to close video meeting in Teams
    CSM  // Ctrl+Shift+M to toggle mute in Teams
    //BOOT
};


// Combine multiple keycodes into one action for CSM and CSH
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

    case CSM:
        if (record->event.pressed) {
                // Send Ctrl+Shift+H
                tap_code16(C(S(KC_M)));
        } else {
            // when keycode CSM is released
        }
        break;

    case CSH:
           if (record->event.pressed) {
                // Send Ctrl+Shift+H
                tap_code16(C(S(KC_H)));
            } else {
            // when keycode CSH is released
        }
        break;
    
    
    return false; // Skip normal key processing
    
//    case MY_OTHER_MACRO:
//        if (record->event.pressed) {
//           SEND_STRING(SS_LCTL("ac")); // selects all and copies
//        }
//        break;
    }
    return true;
};
//QK_BOOTLOADER


enum layers {
  NORMAL_LAYER = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [NORMAL_LAYER] = LAYOUT_ortho_1x3(
        CSM, TD(TD_01), CSH
    )
};

