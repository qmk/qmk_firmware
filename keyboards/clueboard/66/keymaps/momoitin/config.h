#define GRAVE_ESC_CTRL_OVERRIDE /* Always send escape if control is pressed */

/*Timer 1
#define B5_AUDIO
#define B6_AUDIO
#define B7_AUDIO
*/
/*Timer 3
#define C4_AUDIO
#define C5_AUDIO
#define C6_AUDIO
*/

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(PLANCK_SOUND)
  
  #define GOODBY_SONG(TERMINAL_SOUND)
#endif

#define MUSIC_MAP				/*Enables the Music Map in keymap.c*/
#define AUDIO_CLICKY			/*Enables Audio*/
#define TAPPING_TOGGLE 2		/*Sets Tap Toggle "TT()" Layers to only require 2 taps before switching on*/
#define DAC_SAMPLE_MAX 65535U	/*Sets Volume for ARM device, must be a value of [(2^x) - 1] to function*/
