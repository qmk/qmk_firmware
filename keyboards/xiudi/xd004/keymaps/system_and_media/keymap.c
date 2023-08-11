#include QMK_KEYBOARD_H

#define _BASE 0    // Base layer
#define _SYSTEM 1  // System actions
#define _VOLUME 2  // Volume actions

#define SUPER_ALT_F4_TIMER 300  // Timeout on the super alt-f4 key

/*
    The idea of this is pretty simple: base layer has four action, two of which (the outermost)
    are regular keystrokes on tap, and a momentary layer switch on hold, sending you to layers 1 and 2.

    The other bit of customization here is the 'Super Alt F4' which does Alt-F4, and then Enter if tapped
    again SUPER_ALT_F4_TIMER miliseconds after. This lets you Alt-F4 applications, and finally quickly
    double-tap it to Alt-F4+Enter to shut down the PC.
*/

bool is_alt_f4_active = false;
uint16_t alt_f4_timer = 0;

enum custom_keycodes {  // Make sure have the awesome keycode ready
    SUPER_ALT_F4 = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // 0: Base Layer
    [_BASE] = LAYOUT_ortho_1x4(LT(_SYSTEM, KC_F5), C(G(KC_LEFT)), C(G(KC_RIGHT)), LT(_VOLUME, KC_F7)),

    // 1: System actions
    [_SYSTEM] = LAYOUT_ortho_1x4(_______, SUPER_ALT_F4, G(KC_D), G(KC_L)),

    // 2: Volume actions
    [_VOLUME] = LAYOUT_ortho_1x4(KC_MEDIA_NEXT_TRACK, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, _______),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {  // This will do most of the grunt work with the keycodes.
        case SUPER_ALT_F4:
            if (record->event.pressed) {
                if (!is_alt_f4_active) {
                    is_alt_f4_active = true;
                    tap_code16(LALT(KC_F4));  // Alt-F4
                } else {
                    tap_code(KC_ENTER);  // Tap enter
                }
            }
            alt_f4_timer = timer_read();
            break;
    }
    return true;
}

void matrix_scan_user(void) {
    if (is_alt_f4_active && timer_elapsed(alt_f4_timer) > SUPER_ALT_F4_TIMER) {
        is_alt_f4_active = false;
    }
};
