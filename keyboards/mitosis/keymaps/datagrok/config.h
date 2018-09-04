#ifndef CONFIG_USER_H
#define CONFIG_USER_H

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
#define STARTUP_SONG SONG(MARIO_MUSHROOM)
#define DEFAULT_LAYER_SONGS {                   \
    SONG(QWERTY_SOUND),                         \
    SONG(COLEMAK_SOUND),                        \
    SONG(DVORAK_SOUND),                         \
    SONG(ZELDA_TREASURE),                       \
  }
#define AUDIO_VOICES
#define AUDIO_CLICKY
#define C6_AUDIO
#endif

#endif

#define LAYOUT_bottomspace(                                           \
               k00, k01, k02, k03, k04,      k05, k06, k07, k08, k09, \
               k10, k11, k12, k13, k14,      k15, k16, k17, k18, k19, \
               k20, k21, k22, k23, k24,      k25, k26, k27, k28, k29, \
               k31, k32, k33, k34,      k35, k36, k37, k38,           \
               k41, k42, k43, k44,      k45, k46, k47, k48            \
                )                                                     \
  {                                                                   \
    { k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09   },         \
    { k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19   },         \
    { k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29   },         \
    { KC_NO, k31, k32, k43, k44, k45, k46, k37, k38, KC_NO },         \
    { KC_NO, k41, k42, k33, k34, k35, k36, k47, k48, KC_NO }          \
  }
