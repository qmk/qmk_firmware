#pragma once
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_WPM_ENABLE
#define SPLIT_OLED_ENABLE
#define OLED_BRIGHTNESS 10
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_INVERT_ON_SHIFT
#define SPLIT_TRANSACTION_IDS_KB TIME_SYNC
/* #define PET_DISABLE */

// Space saving - https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
/* #define NO_ACTION_LAYER */
/* #define NO_ACTION_TAPPING */
#define NO_ACTION_ONESHOT
