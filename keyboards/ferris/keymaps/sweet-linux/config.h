#pragma once
#define MASTER_RIGTH
#define USB_DEVICE_DESCRIPTOR_STRING       "Ferris Sweep RP2040"
#define USB_MANUFACTURER                   "DPB"
#define USB_MAX_POWER_CONSUMPTION          500  // Set higher for better boot stability

// Pick good defaults for enabling homerow modifiers
#define TAPPING_TERM 175
#define HOLD_ON_OTHER_KEY_PRESS
#define TAPPING_FORCE_HOLD
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 3000  /* Time (in ms) before the one shot key is released */

// // Add these settings to improve split keyboard detection
// #define USB_POLLING_INTERVAL_MS 1  // Default is 1, increase for better detection
// #define USB_SUSPEND_WAKEUP_DELAY 0
// #define FORCE_NKRO  // Force N-key rollover which can help with detection 
// #define SPLIT_USB_DETECT
// #define SPLIT_USB_TIMEOUT 2000  // Wait 2 seconds for split detection

// Remove problematic pin definitions that caused compiler errors
// #define SPLIT_HAND_PIN B0  // Not using pin for split detection
// #define USB_VBUS_PIN GP29  // This caused the error
// #define USB_DETECT_PIN GP29  // This would cause an error too

// Instead, use proper ChibiOS/QMK pin naming
// #define SPLIT_TRANSPORT_MIRROR  // Mirror state between sides

// Add a simple wait at startup
#define KEYBOARD_INIT_DELAY 1000  // Wait 500ms at startup
// RP2040 specific settings
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET  // Enable double-tap reset
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U  // Timeout window in ms
