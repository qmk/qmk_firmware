#pragma once

#define EE_HANDS
#define USE_SERIAL_PD2

#define OLED_TIMEOUT 300000

#define NO_MUSIC_MODE

#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT

#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif
#define TAPPING_TERM 120

#ifdef COMBO_COUNT
#undef COMBO_COUNT
#endif
#define COMBO_COUNT 2
#define COMBO_TERM 20
