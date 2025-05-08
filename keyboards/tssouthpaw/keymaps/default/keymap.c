/* Copyright 2025 TS Design Works LLC
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
 #include "rgb_effects/rgb_effects.h"
 #include "rgb_effects/work_timer.h"
  
 // Define layers
 enum layers {
     BASE, // Base layer
     FN,   // Function layer
 };
  
 // Define custom keycodes
 enum custom_keycodes {
     KC_MICMUTE = SAFE_RANGE, // Microphone mute key
     KC_MEDIA,                // Media layer toggle
     KC_WRKTMR,               // Work timer toggle
     KC_WRKPAU,               // Work timer pause/resume
     KC_CPSWRD,               // Caps word toggle
     KC_30MIN,                // 30-minute timer
     KC_1HR,                  // 1-hour timer
     KC_4HR,                  // 4-hour timer
     KC_8HR,                  // 8-hour timer
     KC_10HR,                 // 10-hour timer
 };
 
 // Function to handle rotary encoder updates
 bool encoder_update_user(uint8_t index, bool clockwise) {
     if (clockwise) {
         tap_code(KC_VOLU); // Rotate right: Volume up
     } else {
         tap_code(KC_VOLD); // Rotate left: Volume down
     }
     return true;
 }
  
 /**
  * Key processing function
  * Handles custom keycodes and effects
  */
 bool process_record_user(uint16_t keycode, keyrecord_t *record) {
     // Handle ESC key with ripple effect
     if (keycode == KC_ESC) {
         if (record->event.pressed) {
             start_esc_ripple_effect();
             return true; // Let QMK handle the actual keypress
         } else {
             stop_esc_ripple_effect();
             return true;
         }
     }
     
     // Handle other custom keycodes
     switch (keycode) {
         case KC_MUTE:
             if (record->event.pressed) {
                 tap_code(KC_MUTE); // Trigger mute on key press
                 tap_code(KC_MPLY); // Play/pause on key press
             }
             return false;
             
         case KC_MICMUTE:
             if (record->event.pressed) {
                 tap_code16(LCTL(LSFT(KC_M))); // MS Teams mic mute shortcut
                 toggle_mic_mute_effect();      // Toggle the red-pulse effect
             }
             return false;
             
         // Work timer keycodes
         case KC_WRKTMR:
         if (record->event.pressed) {
             toggle_work_timer();  // Toggle timer on/off
         }
         return false;
             
         case KC_30MIN:
             if (record->event.pressed) {
                 start_timer(TIMER_TYPE_30MIN);
             }
             return false;
             
         case KC_1HR:
             if (record->event.pressed) {
                 start_timer(TIMER_TYPE_1HR);
             }
             return false;
             
         case KC_4HR:
             if (record->event.pressed) {
                 start_timer(TIMER_TYPE_4HR);
             }
             return false;
             
         case KC_8HR:
             if (record->event.pressed) {
                 start_timer(TIMER_TYPE_8HR);
             }
             return false;
             
         case KC_10HR:
             if (record->event.pressed) {
                 start_timer(TIMER_TYPE_10HR);
             }
             return false;
             
         case KC_WRKPAU:
             if (record->event.pressed) {
                 toggle_pause_work_timer(); // Pause/resume the work timer
             }
             return false;
             
         case KC_CPSWRD:
             if (record->event.pressed) {
                 caps_word_toggle();       // Toggle caps word mode
             }
             return false;
             
         default:
             return true; // Process all other keycodes normally
     }
 }
     
 /**
  * Caps Word Callback
  * Determine which keys should maintain caps word mode
  */
 bool caps_word_press_user(uint16_t keycode) {
     switch (keycode) {
         // These keys don't disable Caps Word
         case KC_A ... KC_Z:
         case KC_MINS:
             return true;
     }
     return false;
 }
  
 // Keymap definitions
 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /* Base Layer */
     [BASE] = LAYOUT(
         KC_ESC,  KC_DEL,  KC_NUM_LOCK, KC_MICMUTE, KC_NO,   KC_NO,   KC_NO,    KC_MUTE, KC_F1,   KC_F2,   KC_F3, KC_F4, KC_F5,  KC_F6,  KC_F7, KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  LGUI(KC_L), 
         KC_BSPC, KC_PSLS, KC_PAST,     KC_PMNS,    DM_REC1, DM_REC2, KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,  KC_5,  KC_6,   KC_7,   KC_8,  KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_NO,   KC_BSPC,       
         KC_P7,   KC_P8,   KC_P9,       KC_NO,      KC_CALC, KC_PSCR, KC_NO,    KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,      
         KC_P4,   KC_P5,   KC_P6,       KC_PPLS,    DM_PLY1, DM_PLY2, KC_NO,    KC_CAPS, KC_A,    KC_S,    KC_D,  KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NO,   KC_ENT,                 
         KC_P1,   KC_P2,   KC_P3,       KC_NO,      KC_NO,   KC_UP,   KC_NO,    KC_LSFT, KC_NO,   KC_Z,    KC_X,  KC_C,  KC_V,   KC_B,   KC_N,  KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_NO,                        
         KC_NO,   KC_P0,   KC_PDOT,     KC_PENT,    KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO,   KC_LCTL, KC_LALT, KC_NO, KC_NO, KC_NO,  KC_SPC, KC_NO, KC_NO,   KC_RALT, KC_NO,   KC_RGUI, MO(FN),  KC_RCTL
     ),
 
     /* Function Layer */
     [FN] = LAYOUT(
         _______, _______, _______,  _______, KC_NO  ,  KC_NO  , KC_NO  , _______,   _______, _______,   _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
         _______, _______, _______,  RGB_VAD, _______,  _______, _______, _______,   _______, _______,   _______, _______, _______, _______,   _______, _______, _______, _______, _______, KC_NO  , _______,
         _______, KC_8HR , KC_10HR,  KC_NO  , _______,  _______, KC_NO  , _______,   _______, _______,   _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
         KC_4HR , _______, _______,  RGB_VAI, _______,  _______, KC_NO  , KC_CPSWRD, _______, KC_WRKTMR, _______, _______, _______, _______,   _______, _______, _______, _______, _______, KC_NO  , _______,
         KC_1HR , _______, KC_30MIN, KC_NO  , KC_NO  ,  RGB_HUI, KC_NO  , _______,   _______, _______,   _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, KC_NO  ,
         KC_NO  , _______, _______,  _______, RGB_RMOD, RGB_HUD, RGB_MOD, KC_NO  ,   _______, _______,   KC_NO  , KC_NO  , KC_NO  , KC_WRKPAU, KC_NO  , KC_NO  , _______, KC_NO  , _______, _______, _______                      
     ),
 };