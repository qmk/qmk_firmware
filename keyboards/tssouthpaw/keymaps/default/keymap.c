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
 #include "rgb_effects.h"
 
 // Define layers
 enum layers {
     BASE, // Base layer
     FN,   // Function layer
     MEDIA // Media control layer
 };
 
// Define custom keycodes
enum custom_keycodes {
    KC_MICMUTE = SAFE_RANGE, // Microphone mute key
    KC_MEDIA,                // Media layer toggle
    KC_WRKTMR,               // Work timer toggle
    KC_WRKPAU,               // Work timer pause/resume
};
 
 /**
 * Encoder mapping
 * Defines how the encoder behaves in different layers
 */
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [FN] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [MEDIA] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) }
};
#endif // ENCODER_MAP_ENABLE

 // Define combo actions for special keys
 #define KC_MUTE_PLAY (KC_MUTE | KC_MPLY << 8)  // Mute + Play/Pause combo
 
 // Variable to track encoder functionality mode
 static bool encoder_media_mode = false; // false = volume, true = media control
 
 /**
  * Rotary encoder handling
  */
 bool encoder_update_user(uint8_t index, bool clockwise) {
     // Different behavior based on encoder mode
     if (encoder_media_mode) {
         // Media control mode
         if (clockwise) {
             tap_code(KC_MNXT); // Next track
         } else {
             tap_code(KC_MPRV); // Previous track
         }
     } else {
         // Volume control mode (default)
         if (clockwise) {
             tap_code(KC_VOLU); // Volume up
         } else {
             tap_code(KC_VOLD); // Volume down
         }
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
             
         case KC_MEDIA:
             if (record->event.pressed) {
                 encoder_media_mode = !encoder_media_mode; // Toggle encoder mode
             }
             return false;
             
         default:
             return true; // Process all other keycodes normally
     }
 }
 
 /**
  * Layer state change handler
  * Can be used for layer-dependent lighting
  */
 layer_state_t layer_state_set_user(layer_state_t state) {
     uint8_t layer = get_highest_layer(state);
     
     // Layer-specific lighting could be implemented here
     switch (layer) {
         case BASE:
             // Default RGB settings for base layer
             break;
         case FN:
             // Highlight function keys on FN layer
             break;
         case MEDIA:
             // Highlight media controls on MEDIA layer
             break;
     }
     
     return state;
 }
 
 /**
  * Keymap definitions
  */
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
         _______, _______, _______, _______, KC_NO  , KC_NO  , KC_NO  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
         _______, _______, _______, RM_VALD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NO  , _______,
         _______, _______, _______, KC_NO  , _______, _______, KC_NO  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
         _______, _______, _______, RM_VALU, KC_WRKTMR, KC_WRKPAU, KC_NO  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NO  , _______,
         _______, _______, _______, KC_NO  , KC_NO  , RM_HUEU, KC_NO  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NO  , _______, KC_NO  ,
         KC_NO,   _______, _______, _______, RM_PREV, RM_HUED, RM_NEXT, KC_NO  , _______, _______, KC_NO  , KC_NO  , KC_NO  , _______, KC_NO  , KC_NO  , _______, KC_NO  , _______, _______, _______                      
     ),
     /* Media Control Layer */
     [MEDIA] = LAYOUT(
         _______, _______, _______, _______, KC_NO  , KC_NO  , KC_NO  , KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NO  , _______,
         _______, _______, _______, KC_NO  , _______, _______, KC_NO  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
         _______, _______, _______, _______, _______, _______, KC_NO  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NO  , _______,
         _______, _______, _______, KC_NO  , KC_NO  , _______, KC_NO  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NO  , _______, KC_NO  ,
         KC_NO,   _______, _______, _______, _______, _______, _______, KC_NO  , _______, _______, KC_NO  , KC_NO  , KC_NO  , _______, KC_NO  , KC_NO  , _______, KC_NO  , _______, _______, _______                      
     ),
 };
 
 /**
  * LED matrix configuration
  * Maps physical key layout to LED array
  */
 #ifdef RGB_MATRIX_ENABLE
 led_config_t g_led_config = {
     /* key_matrix to LED index (6 rows × 21 cols) */
     {
         {  0,  1,  2,  3, NO_LED, NO_LED, NO_LED, NO_LED,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16 },
         { 17, 18, 19, 20,  21,  22,  23,  24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, NO_LED, 36 },
         { 37, 38, 39, NO_LED, 40, 41, NO_LED, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55 },
         { 56, 57, 58, 59, 60, 61, NO_LED, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, NO_LED, 74 },
         { 75, 76, 77, NO_LED, NO_LED, 78, NO_LED, 79, NO_LED, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, NO_LED },
         { NO_LED, 91, 92, 93, 94, 95, 96, NO_LED, 97, 98, NO_LED, NO_LED, NO_LED, 99, NO_LED, NO_LED, 100, NO_LED, 101, 102, 103 }
     },
 
     /* LED index to physical position - scaled 0-224 × 0-64 */
     {
         {   0,  0 }, {  11,  0 }, {  22,  0 }, {  34,  0 }, {  45,  0 },
         {  56,  0 }, {  68,  0 }, {  78,  0 }, {  89,  0 }, { 100,  0 },
         { 112,  0 }, { 123,  0 }, { 134,  0 }, { 146,  0 }, { 157,  0 },
         { 168,  0 }, { 179,  0 }, { 191,  0 }, { 202,  0 }, { 213,  0 },
         { 224,  0 },
         {   0, 13 }, {  11, 13 }, {  22, 13 }, {  34, 13 }, {  45, 13 },
         {  56, 13 }, {  68, 13 }, {  78, 13 }, {  89, 13 }, { 100, 13 },
         { 112, 13 }, { 123, 13 }, { 134, 13 }, { 146, 13 }, { 157, 13 },
         { 168, 13 }, { 179, 13 }, { 191, 13 }, { 202, 13 }, { 213, 13 },
         { 224, 13 },
         {   0, 26 }, {  11, 26 }, {  22, 26 }, { NO_LED, NO_LED }, {  45, 26 },
         {  56, 26 }, { NO_LED, NO_LED }, {  78, 26 }, {  89, 26 }, { 100, 26 },
         { 112, 26 }, { 123, 26 }, { 134, 26 }, { 146, 26 }, { 157, 26 },
         { 168, 26 }, { 179, 26 }, { 191, 26 }, { 202, 26 }, { 213, 26 },
         { 224, 26 },
         {   0, 38 }, {  11, 38 }, {  22, 38 }, {  34, 38 }, {  45, 38 },
         {  56, 38 }, { NO_LED, NO_LED }, {  78, 38 }, {  89, 38 }, { 100, 38 },
         { 112, 38 }, { 123, 38 }, { 134, 38 }, { 146, 38 }, { 157, 38 },
         { 168, 38 }, { 179, 38 }, { 191, 38 }, { 202, 38 }, { NO_LED, NO_LED }, { 224, 38 },
         {   0, 51 }, {  11, 51 }, {  22, 51 }, { NO_LED, NO_LED }, { NO_LED, NO_LED }, {  56, 51 },
         { NO_LED, NO_LED }, {  78, 51 }, { NO_LED, NO_LED }, { 100, 51 }, { 112, 51 }, { 123, 51 },
         { 134, 51 }, { 146, 51 }, { 157, 51 }, { 168, 51 }, { 179, 51 }, { 191, 51 },
         { 202, 51 }, { 213, 51 }
     },
 
     /* LED flags - all keys use the keylight flag */
     {
         [0 ... 103] = LED_FLAG_KEYLIGHT
     }
 };
 #endif  /* RGB_MATRIX_ENABLE */
 
 /**
  * Custom tapping term configuration
  */
 uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
     switch (keycode) {
         case MO(FN):
             return TAPPING_TERM - 50; // Slightly faster tapping term for layer switch
         default:
             return TAPPING_TERM;
     }
 }
 
 /**
  * Keyboard initialization
  * Called once at startup
  */
 void keyboard_post_init_user(void) {
     // Initialize RGB lighting effects
     rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
     rgb_matrix_sethsv(HSV_GREEN);  // Set default color to green
     
     // Set default behavior for NKRO
     keymap_config.nkro = true;
     
     // Set encoder initial mode
     encoder_media_mode = false;
 }
 
 /**
  * Power management functions
  */
 void suspend_power_down_user(void) {
     // Disable RGB effects when computer is suspended
     rgb_matrix_set_suspend_state(true);
 }
 
 void suspend_wakeup_init_user(void) {
     // Re-enable RGB effects when computer wakes up
     rgb_matrix_set_suspend_state(false);
 }