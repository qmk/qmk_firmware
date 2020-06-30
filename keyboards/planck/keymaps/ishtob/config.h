
#ifndef USERSPACE_CONFIG_H
#define USERSPACE_CONFIG_H

#ifdef AUDIO_ENABLE

// #define STARTUP_SONG SONG(E1M1_DOOM)
// #define GOODBYE_SONG  SONG(SONIC_RING)
/* #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND), \
                                }
*/
//audio clicky
    #define AUDIO_CLICKY
  // to enable clicky on startup
  //#define AUDIO_CLICKY_ON
	#define AUDIO_CLICKY_FREQ_RANDOMNESS 1.0f


#endif

#define FORCE_NKRO

#define LEADER_TIMEOUT 300

#undef DEBOUNCE
#define DEBOUNCE 0

//skip usb startup check
//#define NO_USB_STARTUP_CHECK


#endif
