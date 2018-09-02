#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#ifdef MITOSIS_DATAGROK_SLOWUART
// This is the highest possible baud rate that a pro micro clocked at 8Mhz can
// support without errors. I don't notice any difference in behavior at this
// slower speed. (So I think it should maybe be the default, to allow a single
// codebase to support both available flavors of pro micro.) This requires a
// corresponding change to the wireless module firmware; see
// https://github.com/reversebias/mitosis/pull/10
#undef SERIAL_UART_BAUD // avoids redefinition warning
#define SERIAL_UART_BAUD 250000
#endif

// I want to place an underscore as tap behavior on the right shift key. But
// RSFT_T(KC_UNDS) doesn't work; mod-tap doesn't work with pre-shifted keys. So
// instead I take advantage of Space Cadet Shift that does something similar
// and just tweak it to use the -/_ key instead of 0/). See
// https://github.com/qmk/qmk_firmware/pull/2055
#define RSPC_KEY KC_MINS

// TODO: figure out which of these I can safely enable to reduce firmware size.
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT // can't; errors
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(PLANCK_SOUND)
// #define STARTUP_SONG SONG(NO_SOUND)
#define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND),   \
                              SONG(COLEMAK_SOUND),  \
                              SONG(DVORAK_SOUND)    \
  }
#define AUDIO_VOICES
#define AUDIO_CLICKY
#define C6_AUDIO
#endif

#endif
