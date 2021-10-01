#pragma once

// #define LAYOUT_3x6_3
#define COMBO_COUNT 2

#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 220
//#define PERMISSIVE_HOLD
//#define TAPPING_FORCE_HOLD

#undef ENCODER_RESOLUTION 
#define ENCODER_RESOLUTION 1

#undef PS2_MOUSE_SCROLL_BTN_MASK  //shaymdev: maybe set his to middle (default?) possible good info here: https://beta.docs.qmk.fm/using-qmk/hardware-features/feature_ps2_mouse
#define PS2_MOUSE_SCROLL_MASK 0x0F