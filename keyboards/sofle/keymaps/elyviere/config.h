#pragma once
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_INVERT_ON_SHIFT
#define OLED_BRIGHTNESS 10
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_TRANSACTION_IDS_KB TIME_SYNC
#define SPLIT_WPM_ENABLE
#define TAPPING_TOGGLE 3
#define MOUSEKEY_DELAY 1
#define MOUSEKEY_INTERVAL 8
#define MOUSEKEY_MOVE_DELTA 4
#define MOUSEKEY_MAX_SPEED 8
#define MOUSEKEY_WHEEL_DELAY 0
/* #define PET_DISABLE */
#define SNEAK_DISABLE

// Space saving - https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
// #define NO_ACTION_LAYER // Doesn't compile without this
// #define NO_ACTION_TAPPING //disables holding to swap layer
#define NO_ACTION_ONESHOT
