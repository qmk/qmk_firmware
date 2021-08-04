
/* Copyright 2021 Jonavin Eng @Jonavin

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include QMK_KEYBOARD_H

// DEFINE MACROS
#define ARRAYSIZE(arr)  sizeof(arr)/sizeof(arr[0])


// LAYERS
__attribute__ ((weak))
enum custom_layers {
    _BASE,
    _FN1,
    _LOWER,
    _RAISE,
};

// KEYCODES
__attribute__ ((weak))
enum custom_keycodes {
  KC_00 = SAFE_RANGE,
  ENCFUNC,
  KC_WINLCK,    //Toggles Win key on and off
  RGB_TOI,   // Timeout idle time up
  RGB_TOD,   // Timeout idle time down
};

#define KC_CAD	LALT(LCTL(KC_DEL))
#define KC_AF4	LALT(KC_F4)
#define KC_TASK	LCTL(LSFT(KC_ESC))

// Win Key Lock
__attribute__ ((weak)) bool _isWinKeyDisabled = false;

#ifdef LSFT_CAPSLOCK_ENABLE
    // Tap Dance Definitions
    enum custom_tapdance {
        TD_LSFT_CAPSLOCK,
    };

    qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for shift, twice for Caps Lock
        [TD_LSFT_CAPSLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    };

    #define KC_LSFTCAPS TD(TD_LSFT_CAPSLOCK)
#else // regular Shift
    #define KC_LSFTCAPS KC_LSFT
#endif // LSFT_CAPSLOCK_ENABLE



// TIMEOUTS
#ifdef IDLE_TIMEOUT_ENABLE
    #define TIMEOUT_THRESHOLD_DEFAULT   5    // default timeout minutes
    #define TIMEOUT_THRESHOLD_MAX       140  // upper limits (2 hours and 10 minutes -- no rgb indicators above this value)
    static uint16_t timeout_timer = 0;
    static uint16_t timeout_counter = 0;  //in minute intervals
    static uint16_t timeout_threshold = TIMEOUT_THRESHOLD_DEFAULT;

    void timeout_reset_timer(void) {
        timeout_timer = timer_read();
        timeout_counter = 0;
    };

    void timeout_update_threshold(bool increase) {
        if (increase && timeout_threshold < TIMEOUT_THRESHOLD_MAX) timeout_threshold++;
        if (!increase && timeout_threshold > 0) timeout_threshold--;
    };

    void timeout_tick_timer(void) {
        if (timeout_threshold > 0) {
            if (timer_elapsed(timeout_timer) >= 60000) { // 1 minute tick
                timeout_counter++;
                timeout_timer = timer_read();
            }
            #ifdef RGB_MATRIX_ENABLE
                if (timeout_threshold > 0 && timeout_counter >= timeout_threshold) {
                    rgb_matrix_disable_noeeprom();
                }
            #endif
        } // timeout_threshold = 0 will disable timeout
    }

    __attribute__ ((weak))  void matrix_scan_user(void) {
        timeout_tick_timer();
    };

    #ifdef RGB_MATRIX_ENABLE
        __attribute__ ((weak)) void suspend_power_down_user(void) {
            rgb_matrix_set_suspend_state(true);
        }

        __attribute__ ((weak)) void suspend_wakeup_init_user(void) {
            rgb_matrix_set_suspend_state(false);
        }
    #endif // RGB_MATRIX_ENABLE

#endif // IDLE_TIMEOUT_ENABLE


#ifdef ENCODER_ENABLE       // Encoder Functionality
    #ifndef DYNAMIC_KEYMAP_LAYER_COUNT
        #define DYNAMIC_KEYMAP_LAYER_COUNT 4  //default in case this is not already defined elsewhere
    #endif
    __attribute__ ((weak)) uint8_t selected_layer = 0;

    __attribute__ ((weak)) bool encoder_update_user(uint8_t index, bool clockwise) {
        if ( clockwise ) {
            if (keyboard_report->mods & MOD_BIT(KC_LSFT) ) { // If you are holding L shift, encoder changes layers
                if(selected_layer  < (DYNAMIC_KEYMAP_LAYER_COUNT - 1)) {
                    selected_layer ++;
                    layer_move(selected_layer);
                }
            } else if (keyboard_report->mods & MOD_BIT(KC_RSFT) ) { // If you are holding R shift, Page up
                unregister_mods(MOD_BIT(KC_LSFT));
                register_code(KC_PGDN);
                register_mods(MOD_BIT(KC_LSFT));
            } else if (keyboard_report->mods & MOD_BIT(KC_LCTL)) {  // if holding Left Ctrl, navigate next word
                    tap_code16(LCTL(KC_RGHT));
            } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media next track
                tap_code(KC_MEDIA_NEXT_TRACK);
            } else  {
                switch (selected_layer) {
                case _FN1:
                    #ifdef IDLE_TIMEOUT_ENABLE
                        timeout_update_threshold(true);
                    #endif
                    break;
                default:
                    tap_code(KC_VOLU);       // Otherwise it just changes volume
                    break;
                }
            }
        } else {
            if (keyboard_report->mods & MOD_BIT(KC_LSFT) ) {
                if (selected_layer  > 0) {
                    selected_layer --;
                    layer_move(selected_layer);
                }
            } else if (keyboard_report->mods & MOD_BIT(KC_RSFT) ) {
                unregister_mods(MOD_BIT(KC_LSFT));
                register_code(KC_PGUP);
                register_mods(MOD_BIT(KC_LSFT));
            } else if (keyboard_report->mods & MOD_BIT(KC_LCTL)) {  // if holding Left Ctrl, navigate previous word
                tap_code16(LCTL(KC_LEFT));
            } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media previous track
                tap_code(KC_MEDIA_PREV_TRACK);
            } else {
                switch (selected_layer) {
                case _FN1:
                    #ifdef IDLE_TIMEOUT_ENABLE
                        timeout_update_threshold(false);
                    #endif
                    break;
                default:
                    tap_code(KC_VOLD);
                    break;
                }
            }
        }

        return true;
    }
#endif // ENCODER_ENABLE


// PROCESS KEY CODES
__attribute__ ((weak))  bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_00:
        if (record->event.pressed) {
            // when keycode KC_00 is pressed
            SEND_STRING("00");
        } else unregister_code16(keycode);
        break;
    case KC_WINLCK:
        if (record->event.pressed) {
            _isWinKeyDisabled = !_isWinKeyDisabled; //toggle status
            if(_isWinKeyDisabled) {
                process_magic(GUI_OFF, record);
            } else {
                process_magic(GUI_ON, record);
            }
        } else  unregister_code16(keycode);
        break;

#ifdef IDLE_TIMEOUT_ENABLE
    case RGB_TOI:
        if(record->event.pressed) {
            timeout_update_threshold(true);
        } else  unregister_code16(keycode);
        break;
    case RGB_TOD:
        if(record->event.pressed) {
             timeout_update_threshold(false);  //decrease timeout
        } else  unregister_code16(keycode);
        break;
#endif // IDLE_TIMEOUT_ENABLE

    default:
        if (record->event.pressed) {
            #ifdef RGB_MATRIX_ENABLE
                rgb_matrix_enable();
            #endif
            #ifdef IDLE_TIMEOUT_ENABLE
                timeout_reset_timer();  //reset activity timer
            #endif
        }
        break;
    }
    return true;
};


// Turn on/off NUM LOCK if current state is different
void activate_numlock(bool turn_on) {
    if (IS_HOST_LED_ON(USB_LED_NUM_LOCK) != turn_on) {
        tap_code(KC_NUMLOCK);
    }
}


// INITIAL STARTUP


__attribute__ ((weak))  void keyboard_post_init_user(void) {
    activate_numlock(true); // turn on Num lock by default so that the numpad layer always has predictable results
    #ifdef IDLE_TIMEOUT_ENABLE
        timeout_timer = timer_read(); // set inital time for ide timeout
    #endif
}
