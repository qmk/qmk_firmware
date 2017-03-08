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
#include "quantum_keycodes.h"
#include "config.h"

#ifdef USE_BABLPASTE

/* ***************************

// Uncomment any modes you want. Whatever mode = 0 will be the default on boot
// Expect to get errors if you comment a feature out and leave it in your keymap. 

#define USE_BABLPASTE

//#define MS_MODE 0 // Windows. 
//#define MAC_MODE 1
//#define LINUX_MODE 2 //aka gnome+KDE
//#define EMACS_MODE 3
//#define VI_MODE 4
//#define WORDSTAR_MODE 5
//#define READMUX 6  // Readline and tmux

// This removes everything but cursor movement
//#define BABL_MOVEMENTONLY
// and this just removes browser shortcuts
//#define BABL_NOBROWSER
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
// Movement macros
	// left & right
	BABL_GO_LEFT_1C= BABL_START_NUM,
	BABL_GO_RIGHT_1C,
	BABL_GO_LEFT_WORD,	
	BABL_GO_RIGHT_WORD,
	BABL_GO_START_LINE,
	BABL_GO_END_LINE,
	// now up & down
	BABL_GO_START_DOC,
	BABL_GO_END_DOC,
	BABL_GO_NEXT_LINE,
	BABL_GO_PREV_LINE,
	BABL_PGDN,
	BABL_PGUP,
	// And the delete options
	//BABL_DEL_LEFT_1C == backspace, so why bother. 
	BABL_DEL_RIGHT_1C, // usually = Del
	BABL_DEL_LEFT_WORD,
	BABL_DEL_RIGHT_WORD,
	BABL_DEL_TO_LINE_END, // delete from cursor to end of line
	BABL_DEL_TO_LINE_START, // delete from cursor to begining line
#ifndef BABL_MOVEMENTONLY
	   // Cut & Paste
    BABL_UNDO,
	BABL_REDO,
	BABL_CUT,
	BABL_COPY,
	BABL_PASTE,
	BABL_SELECT_ALL,
	/* not yet implemented
	BABL_SWAP_LAST2C // swap last characters before the cursor
	BABL_SWAP_LAST2W // Swap the last two words before the cursor
	*/
		// find & replace
	BABL_FIND,
	BABL_FIND_NEXT,
	BABL_FIND_REPLACE,
		// GUI or app
	BABL_RUNAPP,
	BABL_SWITCH_APP_NEXT,
	BABL_SWITCH_APP_LAST, // previous
	BABL_CLOSE_APP,
	BABL_HELP,

#ifndef BABL_NOBROWSER
	BABL_BROWSER_NEW_TAB,
	BABL_BROWSER_CLOSE_TAB,
	BABL_BROWSER_REOPEN_LAST_TAB,
	BABL_BROWSER_NEXT_TAB,
	BABL_BROWSER_PREV_TAB,
	BABL_BROWSER_URL_BAR,
	BABL_BROWSER_FORWARD,
	BABL_BROWSER_BACK,
	BABL_BROWSER_FIND,
	BABL_BROWSER_BOOKMARK,
	BABL_BROWSER_DEV_TOOLS, // hard one to remember
	BABL_BROWSER_RELOAD,
	BABL_BROWSER_FULLSCREEN,
	BABL_BROWSER_ZOOM_IN,
	BABL_BROWSER_ZOOM_OUT,
	
#endif

#endif
// Macros for mode switching
#ifdef MS_MODE
	BABL_WINDOWS,
#endif
#ifdef MAC_MODE
	BABL_MAC,
#endif
#ifdef LINUX_MODE
	BABL_LINUX,
#endif
#ifdef EMACS_MODE
	BABL_EMACS,
#endif
#ifdef VI_MODE
	BABL_VI,
#endif
#ifdef READMUX_MODE
	BABL_READLINE,
#endif


};

// BUG, used to jump to babble functiion. Surely there is a way to calculate size of enum? 
#define BABL_NUM_MACROS 48+4 // 48 + # of defined modes. 

/* And all the shorthand keymap ready versions */
// First the mode switching macros
#ifdef MS_MODE
#define B_WIN  	M(BABL_WINDOWS)
#endif
#ifdef MAC_MODE
#define B_MAC 	M(BABL_MAC)
#endif
#ifdef LINUX_MODE
#define B_LNX 	M(BABL_LINUX)
#endif
#ifdef EMACS_MODE
#define B_EMAX  M(BABL_EMACS)
#endif
#ifdef VI_MODE
#define B_VI  	M(BABL_VI)
#endif
#ifdef READMUX_MODE
#define B_READ  M(BABL_READLINE)
#endif

// and all the movement & action. 

#define B_L1C  M(BABL_GO_LEFT_1C)
#define B_R1C  M(BABL_GO_RIGHT_1C)
#define B_L1W  M(BABL_GO_LEFT_WORD)
#define B_R1W  M(BABL_GO_RIGHT_WORD)
#define B_GSOL  M(BABL_GO_START_LINE)
#define B_GEOL  M(BABL_GO_END_LINE)
#define B_GTOP  M(BABL_GO_START_DOC)
#define B_GEND  M(BABL_GO_END_DOC)
#define B_DOWN  M(BABL_GO_NEXT_LINE)
#define B_UP  M(BABL_GO_PREV_LINE)
#define B_PGDN  M(BABL_PGDN)
#define B_PGUP  M(BABL_PGUP)
//#define B_BKSP  M(BABL_DEL_LEFT_1C) == backspace so why bother. 
#define B_DEL  M(BABL_DEL_RIGHT_1C) // usually = Del
#define B_DLW  M(BABL_DEL_LEFT_WORD)
#define B_DRW  M(BABL_DEL_RIGHT_WORD)
#define B_DEOL  M(BABL_DEL_TO_LINE_END) // delete from cursor to end of line
#define B_DSOL  M(BABL_DEL_TO_LINE_START) // delete from cursor to begining line
#define B_UNDO  M(BABL_UNDO)
#define B_REDO  M(BABL_REDO)
#define B_CUT  M(BABL_CUT)
#define B_COPY  M(BABL_COPY)
#define B_PAST  M(BABL_PASTE)
#define B_SELA  M(BABL_SELECT_ALL)
#define B_FIND  M(BABL_FIND)
#define B_FINDN  M(BABL_FIND_NEXT)
#define B_FINDR  M(BABL_FIND_REPLACE)
#define B_RAPP  M(BABL_RUNAPP)
#define B_NAPP  M(BABL_SWITCH_APP_NEXT)
#define B_PAPP M(BABL_SWITCH_APP_LAST) // previous
#define B_CAPP  M(BABL_CLOSE_APP)
#define B_HELP  M(BABL_HELP)
#define B_NTAB  M(BABL_BROWSER_NEW_TAB)
#define B_CTAB  M(BABL_BROWSER_CLOSE_TAB)
#define B_ROTB  M(BABL_BROWSER_REOPEN_LAST_TAB)
#define B_NXTB  M(BABL_BROWSER_NEXT_TAB)
#define B_PTAB  M(BABL_BROWSER_PREV_TAB)
#define B_NURL M(BABL_BROWSER_URL_BAR)
#define B_BFWD  M(BABL_BROWSER_FORWARD)
#define B_BBAK  M(BABL_BROWSER_BACK)
#define B_BFND  M(BABL_BROWSER_FIND)
#define B_BOOK  M(BABL_BROWSER_BOOKMARK)
#define B_BDEV  M(BABL_BROWSER_DEV_TOOLS) // hard one to remember
#define B_BRLD  M(BABL_BROWSER_RELOAD)
#define B_BFUlL  M(BABL_BROWSER_FULLSCREEN)
#define B_ZMIN  M(BABL_BROWSER_ZOOM_IN)
#define B_ZMOT  M(BABL_BROWSER_ZOOM_OUT)
 
 





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

