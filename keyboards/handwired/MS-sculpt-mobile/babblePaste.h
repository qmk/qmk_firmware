/*  A library to output the right key shortcut in any common app. 
Given a global variable babble_mode to show the environment and a 
key that calls the paste macro, do the right type of paste. 

Setting the bable_mode is done by another macro, or TBD interaction with the host. 

Huge thanks to https://en.wikipedia.org/wiki/Table_of_keyboard_shortcuts
and jeebak & algernon's keymap
*/
#ifndef _babblePaste_h_included__
#define _babblePaste_h_included__
#include "action_layer.h"

#ifdef USE_BABLPASTE

/* ***************************

// Uncomment any modes you want. Whatever mode = 0 will be the default on boot

//#define MS_MODE 0 // Windows. 
//#define MAC_MODE 1
//#define LINUX_MODE 2 //aka gnome+KDE
//#define EMACS_MODE 3
//#define VI_MODE 4
//#define WORDSTAR_MODE 5
//#define READMUX 6  // Readline and tmux
****************************/


// Uncomment if you need more free flash space
// It removes everything but cursor movement
//#define BABL_MOVEMENTONLY


// Define starting number for BABL macros in the macro range. 
// Probably can start the default even lower
#define BABL_START_NUM 50

/* Macros handled by babblepaste. Most should be available for all platforms.
Whatever isn't defined will NOP  */
enum  {
 
	// Movement
	BABL_DEL_RIGHT_1C= BABL_START_NUM,
	BABL_DEL_LEFT_WORD,
	BABL_DEL_RIGHT_WORD,
	BABL_GO_LEFT_1C,
	BABL_GO_RIGHT_1C,
	BABL_GO_LEFT_WORD,
	BABL_GO_RIGHT_WORD,
	BABL_GO_START_LINE,
	BABL_GO_END_LINE,
	BABL_GO_START_DOC,
	BABL_GO_END_DOC,
	BABL_GO_NEXT_LINE,
	BABL_GO_PREV_LINE,
	BABL_PGDN,
	BABL_PGUP,
#ifndef BABL_MOVEMENTONLY
	   // Cut & Paste
    BABL_UNDO,
	BABL_REDO,
	BABL_CUT,
	BABL_COPY,
	BABL_PASTE,
	BABL_SELECT_ALL,
	// GUI or app
	BABL_FIND,
	BABL_FIND_NEXT,
	BABL_FIND_REPLACE,
	BABL_RUNAPP,
	BABL_SWITCH_APP_NEXT,
	BABL_SWITCH_APP_LAST, // previous
	BABL_CLOSE_APP,
	BABL_HELP
#endif
};

// How many macros/ how many array elements?
#define BABL_NUM_MACROS 28


/*  from action_macro.h
typedef uint8_t macro_t;

#define MACRO_NONE      (macro_t*)0
#define MACRO(...)      ({ static const macro_t __m[] PROGMEM = { __VA_ARGS__ }; &__m[0]; })
#define MACRO_GET(p)    pgm_read_byte(p)

#define BABL_MSTART (entry, os,  macro...) ( const macro_t bablDict[entry][os] PROGMEM = { macro... }; )

*/

const macro_t *babblePaste(keyrecord_t *record,  uint8_t shortcut);

macro_t* switch_babble_mode( uint8_t id);


#endif
#endif

