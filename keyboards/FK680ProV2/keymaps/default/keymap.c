
#include QMK_KEYBOARD_H

typedef union {
  uint32_t raw;
  struct {
    bool top_rgb_change :1;
    bool bottom_rgb_change :1;
  };
} user_config_t;

user_config_t user_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_GRV,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

	[1] = LAYOUT(
		RGB_TOG, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, RGB_MOD,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F23,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAI, KC_F24,
		MO(2), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_HUI, RGB_VAD, RGB_HUD),

	[2] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET),

	[3] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};



void keyboard_post_init_user(void) {
  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_F23:
      if (record->event.pressed) {
        // Do something when pressed
        user_config.top_rgb_change ^= 1; // Toggles the status
        eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    case KC_F24:
      if (record->event.pressed) {
        // Do something when pressed
        user_config.bottom_rgb_change ^= 1; // Toggles the status
        eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (user_config.top_rgb_change)
    {
        for (size_t i = 0; i < 70; i++)
        {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0);
        }
    }

    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(26, 0, 255, 255); // assuming caps lock is at led #5
    }

    if (user_config.bottom_rgb_change)
    {
        for (size_t i = 70; i < 110; i++)
        {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0);
        }
    }
}

// #ifdef RAW_ENABLE
// void set_led_range(int start, int stop, uint8_t r, uint8_t g, uint8_t b) {
//     for (int i = start; i <= stop; i++) {
//         rgb_matrix_set_color(i, r, g, b);
//     }
// }

// void raw_hid_receive(uint8_t *data, uint8_t length) {
//     switch (data[0]) {
//         // Set RGB state
//         case 1:
//             switch (data[1]) {
//                 case 2:
//                     rgb_matrix_enable_noeeprom();
//                     rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
//                     break;
//                 case 3:
//                     rgb_matrix_enable_noeeprom();
//                     rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
//                     break;
//                 case 4:
//                     rgb_matrix_set_flags(LED_FLAG_NONE);
//                     rgb_matrix_disable_noeeprom();
//                     break;
//                 case 5:
//                     rgb_matrix_set_flags(LED_FLAG_ALL);
//                     rgb_matrix_step();
//                     break;
//                 default:
//                     rgb_matrix_set_flags(LED_FLAG_ALL);
//                     rgb_matrix_enable_noeeprom();
//                     break;
//             }
//             break;
//         // Notifications
//         // Note: caller is expected to reset RGB to previous state
//         // TODO: set flags on single LEDs so RGB animation isn't interrupted on underglow
//         case 2:
//             switch (data[1]) {
//                 // Bottom underglow
//                 case 1: {
//                     uint8_t r = data[2];
//                     uint8_t g = data[3];
//                     uint8_t b = data[4];
//                     switch (rgb_matrix_get_flags()) {
//                         case LED_FLAG_ALL:
//                             rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
//                             break;
//                         case LED_FLAG_UNDERGLOW:
//                             rgb_matrix_set_flags(LED_FLAG_NONE);
//                             break;
//                         case LED_FLAG_NONE:
//                             rgb_matrix_enable_noeeprom();
//                             break;
//                     }
//                     for (int i = 67; i <= 81; i++) {
//                         rgb_matrix_set_color(i, r, g, b);
//                     }
//                     break;
//                 }
//                 // Full color change
//                 case 2: {
//                     uint8_t r = data[2];
//                     uint8_t g = data[3];
//                     uint8_t b = data[4];
//                     rgb_matrix_set_flags(LED_FLAG_NONE);
//                     rgb_matrix_set_color_all(r, g, b);
//                     break;
//                 }
//                 // Full underglow
//                 case 3: {
//                     uint8_t r = data[2];
//                     uint8_t g = data[3];
//                     uint8_t b = data[4];
//                     switch (rgb_matrix_get_flags()) {
//                         case LED_FLAG_ALL:
//                             rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
//                             break;
//                         case LED_FLAG_UNDERGLOW:
//                             rgb_matrix_set_flags(LED_FLAG_NONE);
//                             break;
//                         case LED_FLAG_NONE:
//                             rgb_matrix_enable_noeeprom();
//                             break;
//                     }
//                     for (int i = 67; i <= 105; i++) {
//                         rgb_matrix_set_color(i, r, g, b);
//                     }
//                     break;
//                 }
//             }
//             break;
//         // Get RGB state
//         case 3:
//             switch (rgb_matrix_get_flags()) {
//                 case LED_FLAG_ALL:
//                     data[0] = 1;
//                     break;
//                 case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR:
//                     data[0] = 2;
//                     break;
//                 case LED_FLAG_UNDERGLOW:
//                     data[0] = 3;
//                     break;
//                 case LED_FLAG_NONE:
//                     data[0] = 4;
//                     break;
//                 default:
//                     data[0] = 0;
//                     break;
//             }
//             raw_hid_send(data, RAW_EPSIZE);
//             break;
//         // Single LED control
//         case 4: {
//             // TODO: set only the specific LED(s) flag
//             rgb_matrix_set_flags(LED_FLAG_NONE);
//             uint8_t index = data[2];
//             uint8_t r     = data[3];
//             uint8_t g     = data[4];
//             uint8_t b     = data[5];
//             switch (data[1]) {
//                 // Set one led to color
//                 case 1:
//                     rgb_matrix_set_color(index, r, g, b);
//                     break;
//                 // Set one row to color
//                 case 2:
//                     switch (index) {
//                         case 1:  // First row
//                             set_led_range(0, 14, r, g, b);
//                             break;
//                         case 2:  // Second row
//                             set_led_range(15, 29, r, g, b);
//                             break;
//                         case 3:  // Third row
//                             set_led_range(30, 43, r, g, b);
//                             break;
//                         case 4:  // Fourth row
//                             set_led_range(44, 57, r, g, b);
//                             break;
//                         case 5:  // Fifth row
//                             set_led_range(58, 66, r, g, b);
//                             break;
//                         case 6:  // Bottom underglow
//                             set_led_range(67, 81, r, g, b);
//                             break;
//                         case 7:  // Right underglow
//                             set_led_range(82, 86, r, g, b);
//                             break;
//                         case 8:  // Top underglow
//                             set_led_range(87, 99, r, g, b);
//                             break;
//                         case 9:  // Left underglow
//                             set_led_range(100, 104, r, g, b);
//                             break;
//                     }
//                     break;
//             }
//         }
//     }
// }
// #endif
