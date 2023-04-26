#pragma once

#ifdef COMMAND_ENABLE
#define IS_COMMAND() (get_mods() == MOD_MASK_CTRL) //debug commands accessed by holding down both CTRLs: https://github.com/qmk/qmk_firmware/blob/master/docs/feature_command.md
#endif

// Caps Word configuration
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
// #define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_MUSIC_MODE
#define LAYER_STATE_16BIT
