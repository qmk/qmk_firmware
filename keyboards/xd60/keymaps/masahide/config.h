#pragma once
#include "config_common.h"

/* Changes the number of taps required for layer toggle*/
// #define TAPPING_TOGGLE 3

//#undef RGBLIGHT_ENABLE
#ifdef RGBLIGHT_ENABLE
/* The RGB lighting will be switched off when the host goes to sleep */
//#define RGBLIGHT_SLEEP
// lighting layers
#define RGBLIGHT_LAYERS
#elif
#undef BACKLIGHT_ENABLE
#undef RGBLIGHT_LAYERS
#endif

//#define NO_ACTION_TAPPING
#undef AUTO_SHIFT_ENABLE
#undef AUTO_SHIFT_MODIFIERS
#undef BACKLIGHT_BREATHING
#undef COMBO_ENABLE
#undef MIDI_ENABLE
//#undef MOUSEKEY_ENABLE
#undef POINTING_DEVICE_ENABLE
#undef RGBLIGHT_ANIMATIONS
#undef SPLIT_KEYBOARD
#undef TAP_DANCE_ENABLE
#undef SLEEP_LED_ENABLE
#undef AUDIO_CLICKY
#define NO_MUSIC_MODE
#undef AUDIO_ENABLE

#ifdef MOUSEKEY_ENABLE
#define MK_KINETIC_SPEED
#define MOUSEKEY_DELAY 8
#define MOUSEKEY_INTERVAL 30
#define MOUSEKEY_MOVE_DELTA 4
#define MOUSEKEY_INITIAL_SPEED 1
#define MOUSEKEY_BASE_SPEED 1000
#endif

#undef PRODUCT
#define PRODUCT         XD60 3.0 masahide Split space


#define LAYOUT_masahide( \
        K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D,       \
        K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1D,       \
        K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,        K2D,       \
        K30,        K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,        K3D,       \
        K40,  K41,  K42,        K46,        K45,        K44,  K4A,  K4B,  K48,  K4C,  K4D        \
        ) { \
    { K00, K01,   K02,  K03,   K04,   K05,  K06,   K07,   K08,   K09,   K0A, K0B, K0C,   K0D },  \
    { K10, K11,   K12,  K13,   K14,   K15,  K16,   K17,   K18,   K19,   K1A, K1B, K1C,   K1D },  \
    { K20, K21,   K22,  K23,   K24,   K25,  K26,   K27,   K28,   K29,   K2A, K2B, KC_NO, K2D },  \
    { K30, KC_NO, K32,  K33,   K34,   K35,  K36,   K37,   K38,   K39,   K3A, K3B, KC_NO, K3D },  \
    { K40, K41,   K42,  KC_NO, K44,   K45,  K46,   KC_NO, K48,   KC_NO, K4A, K4B, K4C,   K4D }   \
}

