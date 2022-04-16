/* Copyright 2022 elliotpatros
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 2 of the License, or 
 * (at your option) any later version. 
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */ 

#include QMK_KEYBOARD_H

// Layer definitions
enum custom_layers {
    _COLEMAK,
    _FUNCTION,
};

// Custom keycodes, implemented later, in function: process_record_user()
enum custom_keycodes {
    CTL_ESC = SAFE_RANGE,   // mod tap: left control / esc
    SFT_ENT,                // mod tap: left shift / enter
    LST_PRN,                // mod tap: left shift / left parenthesis
    RST_PRN,                // mod tap: right shift / right parenthesis
};

// Shorthand keycode definitions
#define OSM_CAG OSM(MOD_LCTL | MOD_LALT | MOD_LGUI)
#define LT_BSFN LT(_FUNCTION, KC_BSLS)

// The layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
    // Default layer
    [_COLEMAK] = LAYOUT (

// ┌────────┬────────┬────────┬────────┬────────┬────────┐                  ┌────────┬────────┬────────┬────────┬────────┬────────┐
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
// ├────────┼────────┼────────┼────────┼────────┼────────┤                  ├────────┼────────┼────────┼────────┼────────┼────────┤
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_EQL,
// ├────────┼────────┼────────┼────────┼────────┼────────┤                  ├────────┼────────┼────────┼────────┼────────┼────────┤
    CTL_ESC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                       KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    LST_PRN, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_SPC,   KC_ENT,  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RST_PRN,
// └────────┴────────┴────────┴────────┼────────┼────────┼────────┘└────────┼────────┴────────┴────────┴────────┴────────┴────────┘
                                        KC_LALT, KC_LGUI, SFT_ENT,  KC_SPC,  LT_BSFN, KC_BSPC
//                                     └────────┴────────┴────────┘└────────┴────────┴────────┘
    ),

    // Function (and I guess also media & navigation) layer
    [_FUNCTION] = LAYOUT (

// ┌────────┬────────┬────────┬────────┬────────┬────────┐                  ┌────────┬────────┬────────┬────────┬────────┬────────┐
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
// ├────────┼────────┼────────┼────────┼────────┼────────┤                  ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______, KC_GRV,  KC_LPRN, KC_RPRN, KC_F11,  KC_F12,                     KC_INS,  KC_HOME, KC_UP,   KC_PGUP, _______, _______,
// ├────────┼────────┼────────┼────────┼────────┼────────┤                  ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______, KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, OSM_CAG,                    KC_VOLU, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, _______,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______, _______, _______, _______, _______, KC_MUTE, _______,  _______, KC_VOLD, KC_DEL,  KC_END,  KC_PGDN, _______, _______,
// └────────┴────────┴────────┴────────┼────────┼────────┼────────┘└────────┼────────┴────────┴────────┴────────┴────────┴────────┘
                                        _______, _______, _______,  _______, _______, _______
//                                     └────────┴────────┴────────┘└────────┴────────┴────────┘
    )

};

static inline bool dualfunckey_was_tapped(const uint16_t time_when_pressed) {
    return timer_elapsed(time_when_pressed) < TAPPING_TERM;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    
    // Static variables
    static uint16_t timer_control_escape = 0;
    static uint16_t timer_shift_enter = 0;
    static uint16_t timer_shift_lparen = 0;
    static uint16_t timer_shift_rparen = 0;

    static bool dualfunckey_pending = false;

    static bool shift_enter_is_pressed = false;
    static bool shift_lparen_is_pressed = false;

    // Was this function called to handle a keydown? If not, it was called by a 
    // key up.
    const bool pressed = record->event.pressed;

    // Any keydown (at all) spends a pending dual function key check. Why? If,
    // for example, you use shift to type a capital letter, and shift keys down
    // and up faster than the tapping term, did you mean to call shift's tapping
    // key? No. You just meant to call shift.
    if (pressed) {
        dualfunckey_pending = false;
    }

    // Only keycodes >= SAFE_RANGE are handled in this function
    if (keycode < SAFE_RANGE) {
        // This keypress was not handled
        return true;
    }

    // Handle custom keypresses here
    switch (keycode) {

    // -------------------------------------------------------------------------
    // Dual function key (hold: left shift; tap: enter)
    // -------------------------------------------------------------------------
    case SFT_ENT:
            
        // There are multiple keys that are mapped to left shift. Keep track of
        // which are pressed
        shift_enter_is_pressed = pressed;

        // Handle keypress routine
        if (pressed) {
            
            // The [left shift/enter] key was pressed
            register_code(KC_LSFT);

            // Save keydown time for checking hold/tap on keyup
            timer_shift_enter = timer_read();

            // Pressing a dual function key requires a hold/tap check on key up
            dualfunckey_pending = true;
            
        } else {
            
            // The [left shift/enter] key was unpressed
            // Note: unregister shift before pressing ENT so that ENT registers
            // correctly

            // If no other left shift keys are currently pressed, unregister it
            if (! shift_lparen_is_pressed) {
                unregister_code(KC_LSFT);
            }

            // If a pending dual function key hasn't been used yet, use it here
            if (dualfunckey_pending && dualfunckey_was_tapped(timer_shift_enter)) {
                tap_code(KC_ENT);
                dualfunckey_pending = false;
            }
        }

        // This keypress was handled
        return false;

    // -------------------------------------------------------------------------
    // Dual function key (hold: left control; tap: escape)
    // -------------------------------------------------------------------------
    case CTL_ESC:

        // Handle keypress routine
        if (pressed) {
            
            // Control/escape key was pressed
            register_code(KC_LCTL);

            // Save keydown time for checking hold/tap on keyup
            timer_control_escape = timer_read();

            // Pressing a dual function key requires a hold/tap check on key up
            dualfunckey_pending = true;
            
        } else {
            
            // Control/escape key was unpressed
            unregister_code(KC_LCTL);

            // If a pending dual function key hasn't been used yet, use it here
            if (dualfunckey_pending && dualfunckey_was_tapped(timer_control_escape)) {
                tap_code(KC_ESC);
                dualfunckey_pending = false;
            }
        }

        // This keypress was handled
        return false;

    // -------------------------------------------------------------------------
    // Dual function key (hold: left shift; tap: left parenthesis)
    // -------------------------------------------------------------------------
    case LST_PRN:

        // There are multiple keys that are mapped to left shift. Keep track of
        // which are pressed
        shift_lparen_is_pressed = pressed;

        // Handle keypress routine
        if (pressed) {
            
            // The [left shift/left parenthesis] key was pressed
            register_code(KC_LSFT);

            // Save keydown time for checking hold/tap on keyup
            timer_shift_lparen = timer_read();

            // Pressing a dual function key requires a hold/tap check on key up
            dualfunckey_pending = true;
            
        } else {
            
            // The [left shift/left parenthesis] key was unpressed
            // Note: unregister shift after tapping 9 so that left parenthesis
            // registers correctly

            // If a pending dual function key hasn't been used yet, use it here
            if (dualfunckey_pending && dualfunckey_was_tapped(timer_shift_lparen)) {
                tap_code(KC_9);
                dualfunckey_pending = false;
            }

            // If no other left shift keys are currently pressed, unregister it
            if (! shift_enter_is_pressed) {
                unregister_code(KC_LSFT);
            }
        }

        // This keypress was handled
        return false;

    // -------------------------------------------------------------------------
    // Dual function key (hold: right shift; tap: right parenthesis)
    // -------------------------------------------------------------------------
    case RST_PRN:

        // Handle keypress routine
        if (pressed) {
            
            // The [right shift/right parenthesis] key was pressed
            register_code(KC_RSFT);

            // Save keydown time for checking hold/tap on keyup
            timer_shift_rparen = timer_read();

            // Pressing a dual function key requires a hold/tap check on key up
            dualfunckey_pending = true;
            
        } else {
            
            // The [right shift/right parenthesis] key was unpressed
            // Note: unregister shift after tapping 0 so that right parenthesis
            // registers correctly

            // If a pending dual function key hasn't been used yet, use it here
            if (dualfunckey_pending && dualfunckey_was_tapped(timer_shift_rparen)) {
                
                // Space cadet shift: If the [left shift/left parenthesis] key
                // is currently pressed, then tap the sequence ()
                if (shift_lparen_is_pressed) {
                    tap_code(KC_9);
                }

                tap_code(KC_0);
                dualfunckey_pending = false;
            }

            unregister_code(KC_RSFT);
        }

        // This keypress was handled
        return false;

    // -------------------------------------------------------------------------
    // Some other key was pressed (this shouldn't happen)
    // -------------------------------------------------------------------------
    default:
        // This keypress was not handled
        return true;        
    }
}
