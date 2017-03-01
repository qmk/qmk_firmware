/*  A library to output the right key shortcut in any common app. 
Given a global variable babble_mode to show the environment and a 
key that calls the paste macro, do the right type of paste. 

Setting the bable_mode is done by another macro, or TBD interaction with the host. 

Huge thanks to https://en.wikipedia.org/wiki/Table_of_keyboard_shortcuts
and jeebak & algernon's keymap
*/
#ifndef _babblePaste_h_included__
#define _babblePaste_h_included__


/*  Add this to your config.h
// Uncomment any modes you want. 
// Windows. 
//#define MS_MODE 0
//#define MAC_MODE 1
//aka gnome+KDE
//#define LINUX_MODE 2 
//#define EMACS_MODE 3
//#define VI_MODE 4
//#define WORDSTAR_MODE 5
// Readline and tmux
//#define READMUX 6 
*/

/* Macros handled by babblepaste. Most should be available for all platforms.  */
enum  {
 
	// Movement
	BABL_DEL_RIGHT_1C=200,
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




//static macro_t *babblePaste(keyrecord_t *record,  uint16_t shortcut) 
 
 #endif