/* Copyright 2025 Carlos Eduardo de Paula <carlosedp@gmail.com>
 * Copyright 2025 EPOMAKER <https://github.com/Epomaker>
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

#pragma once

#include "rdmctmzt_common.h"

// ============================================================================
// Configuration - Override these in your keyboard's config.h
// ============================================================================

// Status indicator LED indices - must be defined by each keyboard
#ifndef LED_CONNECTION_INDEX
#    error "LED_CONNECTION_INDEX must be defined in keyboard config"
#endif
#ifndef LED_CAP_INDEX
#    error "LED_CAP_INDEX must be defined in keyboard config"
#endif
#ifndef LED_WIN_L_INDEX
#    error "LED_WIN_L_INDEX must be defined in keyboard config"
#endif
#ifndef LED_BATT_INDEX
#    error "LED_BATT_INDEX must be defined in keyboard config"
#endif

// Mode indicator LED indices - must be defined by each keyboard
#ifndef LED_BLE_1_INDEX
#    error "LED_BLE_1_INDEX must be defined in keyboard config"
#endif
#ifndef LED_BLE_2_INDEX
#    error "LED_BLE_2_INDEX must be defined in keyboard config"
#endif
#ifndef LED_BLE_3_INDEX
#    error "LED_BLE_3_INDEX must be defined in keyboard config"
#endif
#ifndef LED_2P4G_INDEX
#    error "LED_2P4G_INDEX must be defined in keyboard config"
#endif
#ifndef LED_USB_INDEX
#    error "LED_USB_INDEX must be defined in keyboard config"
#endif

// Battery indicator configuration
#ifndef BATTERY_LED_COUNT
#    define BATTERY_LED_COUNT 12
#endif
#ifndef BATTERY_LOW_THRESHOLD
#    define BATTERY_LOW_THRESHOLD 20
#endif
#ifndef BATTERY_MED_THRESHOLD
#    define BATTERY_MED_THRESHOLD 50
#endif

// LED colors (RGB values)
#define COLOR_OFF 0, 0, 0
#define COLOR_WHITE U_PWM, U_PWM, U_PWM
#define COLOR_BLUE 0, 0, 255
#define COLOR_GREEN 0, 255, 0
#define COLOR_RED 255, 0, 0
#define COLOR_YELLOW 255, 255, 0

// ============================================================================
// State Variables (extern declarations)
// ============================================================================

// Key state tracking
extern bool Key_Fn_Status;

// Battery display state
extern bool    User_Key_Batt_Num_Show;
extern uint8_t User_Key_Batt_Count;

// LED feedback blink counters
extern uint8_t Led_Point_Count;
extern uint8_t Mac_Win_Point_Count;

// LED test mode state
extern bool    Test_Led;
extern uint8_t Test_Colour;

// ============================================================================
// Function Prototypes - Must be implemented by each keyboard
// ============================================================================

// Battery indicator LED indices array - must be provided by each keyboard
extern const uint8_t Led_Batt_Index_Tab[];

// ============================================================================
// Helper Functions
// ============================================================================

// Check if currently in USB mode
bool kb_is_usb_mode(void);

// Get current Caps Lock state based on mode
bool kb_get_caps_lock_state(void);

// Set LED to a specific RGB color
void kb_set_led_color(uint8_t index, uint8_t r, uint8_t g, uint8_t b);

// Turn off a specific LED
void kb_led_off(uint8_t index);

// Get battery color based on percentage
void kb_get_battery_color(uint8_t percent, uint8_t *r, uint8_t *g, uint8_t *b);

// Helper to switch to a BLE channel
void kb_switch_to_ble_channel(uint8_t channel, uint8_t spi_command, bool *key_status);

// ============================================================================
// LED Display Functions
// ============================================================================

void kb_led_rf_mode_show(void);
void kb_led_power_low_show(void);
void kb_led_point_flash_show(void);
void kb_led_batt_number_show(void);
void kb_user_point_show(void);
void kb_user_test_colour_show(void);
void kb_update_connection_indicator(void);
void kb_update_state_indicators(void);
void kb_show_current_connection_mode(void);

// ============================================================================
// QMK Callback Functions - Common implementations
// ============================================================================

// Common RGB matrix indicators handler
bool kb_rgb_matrix_indicators_common(uint8_t led_min, uint8_t led_max);

// Common USB device state change handler
void kb_notify_usb_device_state_change(struct usb_device_state usb_device_state);

// Common LED update handler - returns local caps lock state for tracking
bool kb_led_update(led_t led_state);

// Common housekeeping task
void kb_housekeeping_task(void);

// Common board initialization
void kb_board_init(void);

// Common keyboard post-init
void kb_keyboard_post_init(void);

// ============================================================================
// Keycode Processing
// ============================================================================

// Common process_record handler - returns true if keycode was handled
bool kb_process_record_common(uint16_t keycode, keyrecord_t *record);
