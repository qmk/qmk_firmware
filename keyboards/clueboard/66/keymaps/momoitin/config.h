#define GRAVE_ESC_CTRL_OVERRIDE /* Always send escape if control is pressed */


#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(PLANCK_SOUND)
  
  #define GOODBY_SONG(TERMINAL_SOUND)
#endif

#define MUSIC_MAP				/*Enables the Music Map in keymap.c*/
#define AUDIO_CLICKY			/*Enables Audio*/
#define TAPPING_TOGGLE 2		/*Sets Tap Toggle "TT()" Layers to only require 2 taps before switching on*/
#define DAC_SAMPLE_MAX 65535U	/*Sets Volume for ARM device, must be a value of [(2^x) - 1] to function*/git pu