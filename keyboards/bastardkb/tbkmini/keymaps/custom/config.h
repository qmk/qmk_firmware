#pragma once

// ============================================================================
// Custom - Size Optimized Configuration
// ============================================================================

// Split keyboard configuration
#define MASTER_LEFT

// Reduce VIA layers to save space
#define DYNAMIC_KEYMAP_LAYER_COUNT 5 // Reduced from 8

// Disable Vial for now to save space (can re-enable later if needed)
// #define VIAL_KEYBOARD_UID {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0}

// Tapping configuration (keep essential settings only)
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD

// Per-key hold-on-other-key-press. Enables get_hold_on_other_key_press() in
// keymap.c, which applies it to the two thumb layer-taps only so ENTER + SPACE
// reaches UTILITY in any order (and pressed together) without waiting out
// TAPPING_TERM. Letters and the other mod-taps keep the default behaviour.
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// ============================================================================
// Size Reduction Settings
// ============================================================================

// Disable unused features to save space
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_MUSIC_MODE
#define NO_ACTION_ONESHOT

// Disable RGB features if not using them
#define RGBLIGHT_DISABLE
#define RGB_MATRIX_DISABLE

// Don't define OLED_ENABLE here - handle it in rules.mk

// Reduce mouse key settings to minimum
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MAX_SPEED 3    // Reduced from 6
#define MOUSEKEY_TIME_TO_MAX 32 // Reduced from 64

// Minimal combo settings
#define COMBO_COUNT 3
#define COMBO_TERM 30 // Reduced from 50

// Disable debugging features
#undef CONSOLE_ENABLE
#undef DEBUG_MATRIX_SCAN_RATE
