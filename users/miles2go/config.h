#pragma once

#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_SLEEP
#undef RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_BREATHING
#endif // RGBLIGHT_ENABLE

#ifndef QMK_KEYS_PER_SCAN
#define QMK_KEYS_PER_SCAN 4
#endif // !QMK_KEYS_PER_SCAN

#undef FORCE_NKRO

#ifndef TAPPING_TOGGLE
#define TAPPING_TOGGLE  3
#endif

#ifdef TAPPING_TERM
	#undef TAPPING_TERM
#endif // TAPPING_TERM
#define TAPPING_TERM 200
//if no chord during tapping term, do the keystroke
#define RETRO_TAPPING

// Disable action_get_macro and fn_actions, since we don't use these
// and it saves on space in the firmware.
// LTO_ENABLE automatically enables these
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
#define MACRO_TIMER 5



#define USE_BABBLEPASTE
// All options
#define BABL_MODSWAP
#define BABL_MOVE // Uncomment to add basic cursor movement
#define BABL_OSKEYS // This adds Cut, paste, window movement and common OS shortcuts
#define BABL_BROWSER // Browser shortcuts, with Chrome/Firefox as the default. 
// edit the appropriate OS config file to enable Safari, Edge, vimpirator &etc. 
#define BABL_APP // Application specific settings this has sub-options.
#define BABL_APP_CELLS // spreadsheets and tables
#define BABL_APP_EDITOR // Fancy editor commands 
#define BABL_APP_WINDOWSPLITTING // splitting frames & windows

//All OSes

//#define BABL_WINDOWS
#define BABL_READMUX
#define BABL_VI
#define BABL_MAC
#define BABL_LINUX
//#define BABL_EMACS
//#define BABL_CHROMEOS
#define BABL_KITTY

#ifdef FALSE
// these need to be defined per board to avoid RGB/GRB problems
	#define RGBLIGHT_COLOR_MS 0x00, 0x27, 0x88 // light blue
	#define RGBLIGHT_COLOR_MAC 0x30,0x30,0x30 // grey
	#define RGBLIGHT_COLOR_LINUX 0x0,0x0,0x0 // black
	#define RGBLIGHT_COLOR_EMACS 0x00,0x00,0x00
	#define RGBLIGHT_COLOR_VI 0x00,0x90,0x00
	#define RGBLIGHT_COLOR_READMUX 0x13,0x60,0x13 // green screen
	#define RGBLIGHT_COLOR_CHROMEOS 0xa4,0x82,0xd // google yellows
	#define RGBLIGHT_COLOR_KITTY 0x20,0x40,0x90 // rosey
#endif

