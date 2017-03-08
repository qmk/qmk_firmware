/*  A library to output the right key shortcut in any common app. 
Given a global variable babble_mode to show the environment and a 
key that calls the paste macro, do the right type of paste. 
Setting the context is done by another macro, or TBD interaction with the host. 

Huge thanks to https://en.wikipedia.org/wiki/Table_of_keyboard_shortcuts
and https://github.com/qmk/qmk_firmware/blob/master/keyboards/planck/keymaps/jeebak/keymap.c 
*/

#include "babblePaste.h"
#include "action_macro.h"

#ifdef USE_BABLPASTE

// GLOBAL variable to determine mode.  Sets startup default if no eeppom
uint8_t babble_mode =0 ;

// small function that we might also want to call from a keymap. 

macro_t* switch_babble_mode( uint8_t id) {
 babble_mode= id;
 return MACRO_NONE; //less typing where called
}

		
// Today I learned that the preprocessor can not create a switch statement label from an argument
// And else statements have problems, see https://gcc.gnu.org/onlinedocs/gcc-3.0.1/cpp_3.html#SEC15
#define BABLM(ent, macro...) \
	if ( ent == shortcut ) \
		 {  action_macro_play( MACRO(macro)); return MACRO_NONE; }   


/* this function runs the appropriate babblepaste macro, given
the global babble_mode, and a shortcut from the ENUM in babblePaste.h 
TODO, the pointers in this function should be stored in a PROGMEM array, not ram. 
But that requires even more clever preprocessor foo.
*/
const  macro_t *babblePaste (keyrecord_t *record,  uint8_t shortcut) {
/*
	 if ( shortcut < BABL_START_NUM || \
			 shortcut >= (BABL_START_NUM + BABL_NUM_MACROS ) ) {
			return MACRO_NONE;
		}
*/
 

#ifdef MS_MODE
	if ( BABL_WINDOWS  == shortcut ) { return switch_babble_mode(MS_MODE);  } 
#endif    
#ifdef MAC_MODE
	if ( BABL_MAC == shortcut) { return switch_babble_mode(MAC_MODE);  } 
#endif
#ifdef LINUX_MODE
	if ( BABL_LINUX == shortcut ) { return switch_babble_mode(LINUX_MODE);  }
#endif	    
 #ifdef READMUX_MODE
	if ( BABL_READLINE == shortcut  ) { switch_babble_mode(READMUX_MODE); return MACRO_NONE; }
#endif   
#ifdef VI_MODE
	if ( BABL_VI == shortcut  ) { return switch_babble_mode(VI_MODE);   }
#endif
#ifdef EMACS_MODE
	if ( BABL_EMACS == shortcut  ) { return switch_babble_mode(EMACS_MODE);   }
#endif



    switch(babble_mode) {  

#ifdef MS_MODE
		
	 case MS_MODE:	
		BABLM( BABL_GO_LEFT_1C,	T(LEFT), END );
		BABLM( BABL_GO_RIGHT_1C ,	T(RIGHT), END );
		BABLM( BABL_GO_LEFT_WORD,	D(LCTL), T(LEFT), U(LCTL), END );
		BABLM( BABL_GO_RIGHT_WORD, D(LCTL), T(RIGHT), U(LCTL), END );
		BABLM( BABL_GO_START_LINE,	T(HOME), END );
		BABLM( BABL_GO_END_LINE,	T(END), END );
		BABLM( BABL_GO_START_DOC,	D(LCTL),T(HOME),  U(LCTL),END );
		BABLM( BABL_GO_END_DOC,	D(LCTL),T(END),  U(LCTL),END );
		BABLM( BABL_GO_NEXT_LINE,	T(DOWN), END );
		BABLM( BABL_GO_PREV_LINE,	T(UP), END );
		BABLM( BABL_PGDN,			T(PGDN), END );
		BABLM( BABL_PGUP,			T(PGUP), END );
		BABLM( BABL_DEL_RIGHT_1C,	T(DEL), END );
		BABLM( BABL_DEL_LEFT_WORD,	D(LCTL), T(BSPACE), U(LCTL), END );
		BABLM( BABL_DEL_RIGHT_WORD,		D(LCTL), T(DEL), U(LCTL), END );
		BABLM( BABL_DEL_TO_LINE_END,	D(RSFT), T(HOME), U(RSFT), T(DEL),  END);
		BABLM( BABL_DEL_TO_LINE_START,	D(RSFT), T(END), U(RSFT), T(DEL),  END );
#ifndef BABL_MOVEMENTONLY
		BABLM( BABL_UNDO, 		D(LCTL), T(Z), U(LCTL), END );
		BABLM( BABL_REDO, 		D(LCTL), T(Y), U(LCTL), END );
		BABLM( BABL_CUT, 		D(LCTL), T(X), U(LCTL), END );
		BABLM( BABL_COPY, 		D(LCTL), T(C), U(LCTL), END );
		BABLM( BABL_PASTE, 		D(LCTL), T(V), U(LCTL), END );		
		BABLM( BABL_SELECT_ALL, D(LCTL), T(A), U(LCTL), END );
		BABLM( BABL_FIND, 		D(LCTL),T(F),  U(LCTL),END );
		BABLM( BABL_FIND_NEXT, 			T(F3),END );
		BABLM( BABL_FIND_REPLACE,		D(LCTL),T(H),  U(LCTL),END );
		BABLM( BABL_RUNAPP, 	D(LGUI),T(R),  U(LGUI),END );
		BABLM( BABL_SWITCH_APP_NEXT, D(LALT),T(TAB), U(LALT),END );
		BABLM( BABL_SWITCH_APP_LAST, D(LSFT),D(LALT),T(TAB), U(LALT), U(LSFT),END );
		BABLM( BABL_CLOSE_APP, 	D(LALT),T(F4), U(LALT),END );
		BABLM( BABL_HELP,		T(F1),END );
#ifndef BABL_NOBROWSER
		BABLM( BABL_BROWSER_NEW_TAB,		D(LCTL), T(T), U(LCTL),END );
		BABLM( BABL_BROWSER_CLOSE_TAB,		D(LCTL), T(W), U(LCTL),END );
		BABLM( BABL_BROWSER_REOPEN_LAST_TAB,		D(LCTL), D(RSFT),T(T), U(RSFT),U(LCTL),END );
		BABLM( BABL_BROWSER_NEXT_TAB,		D(LCTL), T(TAB), U(LCTL),END );
		BABLM( BABL_BROWSER_PREV_TAB,		D(LCTL), D(RSFT), T(TAB), U(RSFT), U(LCTL),END );
		BABLM( BABL_BROWSER_URL_BAR,		D(LCTL), T(L), U(LCTL),END );
		BABLM( BABL_BROWSER_FORWARD,		D(LALT), T(RIGHT), U(LALT),END );
		BABLM( BABL_BROWSER_BACK,			D(LALT), T(LEFT), U(LALT),END );
		BABLM( BABL_BROWSER_FIND,			D(LCTL), T(F), U(LCTL),END );
		BABLM( BABL_BROWSER_BOOKMARK,		D(LCTL), T(D), U(LCTL),END );
		//BABLM( BABL_BROWSER_DEV_TOOLS,	T(F12), U(LCTL),END  ); // EDGE 
		BABLM( BABL_BROWSER_DEV_TOOLS,		D(LCTL), T(T), U(LCTL),END  ); // Chrome
		// Chrome
		BABLM( BABL_BROWSER_RELOAD,			D(LCTL), T(F5), U(LCTL),END ); // hard reload w/o cache
		BABLM( BABL_BROWSER_FULLSCREEN,		T(F11),END ); //command shift F
		BABLM( BABL_BROWSER_ZOOM_IN,		D(LCTL), D(RSFT), T(EQL), U(RSFT), U(LCTL),END ); // ctr+ +
		BABLM( BABL_BROWSER_ZOOM_OUT,		D(LCTL), T(MINS), U(LCTL),END );
#endif
#endif

		// Todo, ring bell, flash light, show user this isn't supported
		return MACRO_NONE;
		
	 	
#endif /* MS_MODE*/


#ifdef LINUX_MODE

	 case LINUX_MODE:
		BABLM( BABL_GO_LEFT_1C  , 	T(LEFT), END );
		BABLM( BABL_GO_RIGHT_1C  , 	T(RIGHT), END );
		BABLM( BABL_GO_LEFT_WORD  , 	D(LCTL), T(LEFT), U(LCTL), END );
		BABLM( BABL_GO_RIGHT_WORD  , D(LCTL), T(RIGHT), U(LCTL), END );
		BABLM( BABL_GO_START_LINE , 	T(HOME), END );
		BABLM( BABL_GO_END_LINE  ,	T(END), END );
		BABLM( BABL_GO_START_DOC  , 	D(LCTL),T(HOME),  U(LCTL),END );
		BABLM( BABL_GO_END_DOC  , 	D(LCTL),T(END),  U(LCTL),END );
		BABLM( BABL_GO_NEXT_LINE  , 	T(DOWN), END );
		BABLM( BABL_GO_PREV_LINE  , 	T(UP), END );
		BABLM( BABL_PGDN  , 			T(PGDN), END );
		BABLM( BABL_PGUP  , 			T(PGUP), END );
		BABLM( BABL_DEL_RIGHT_1C  , 	D(DEL), END );	 
		BABLM( BABL_DEL_LEFT_WORD  ,	D(LCTL), T(BSPACE), U(LCTL), END );
		BABLM( BABL_DEL_RIGHT_WORD  , D(LCTL), T(DEL), U(LCTL), END );
		BABLM( BABL_DEL_TO_LINE_END,	D(RSFT), T(HOME), U(RSFT), T(DEL),  END);
		BABLM( BABL_DEL_TO_LINE_START,	D(RSFT), T(END), U(RSFT), T(DEL),  END );
#ifndef BABL_MOVEMENTONLY
		BABLM( BABL_UNDO  , 	D(LCTL), T(Z), U(LCTL), END );
		BABLM( BABL_REDO  , 	D(LCTL), T(Y), U(LCTL), END );
		BABLM( BABL_CUT  , 	D(LCTL), T(X), U(LCTL), END );
		BABLM( BABL_COPY  , 	D(LCTL), T(C), U(LCTL), END );
		BABLM( BABL_PASTE  ,	D(LCTL), T(V), U(LCTL), END );			
		BABLM( BABL_SELECT_ALL, D(LCTL), T(A), U(LCTL), END );	
		BABLM( BABL_FIND,	D(LCTL),T(F),  U(LCTL),END );
		/* BABLM(BABL_FIND_NEXT  , T(F3),END ); KDE */
		BABLM( BABL_FIND_NEXT,	D(LCTL),T(G),  U(LCTL),END ); // Gnome*/
		/* BABLM(  , D(LCTL),T(R),  U(LCTL),END ); KDE */
		BABLM( BABL_FIND_REPLACE,	D(LCTL),T(H),  U(LCTL),END ); // Gnome*/
		BABLM( BABL_RUNAPP,			D(LALT),T(F2),  U(LALT),END );
		BABLM( BABL_SWITCH_APP_NEXT,	D(LCTL),T(TAB), U(LCTL),END );
		BABLM( BABL_SWITCH_APP_LAST,	D(LSFT),D(LCTL),T(TAB), U(LCTL), U(LSFT),END );
		BABLM( BABL_CLOSE_APP,	D(LALT),T(F4), U(LALT),END );
		//BABLM( BABL_HELP, 		END ); 

#ifndef BABL_NOBROWSER
		BABLM( BABL_BROWSER_NEW_TAB,		D(LCTL), T(T), U(LCTL),END );
		BABLM( BABL_BROWSER_CLOSE_TAB,		D(LCTL), T(W), U(LCTL),END );
		BABLM( BABL_BROWSER_REOPEN_LAST_TAB,		D(LCTL), D(RSFT),T(T), U(RSFT),U(LCTL),END );
		BABLM( BABL_BROWSER_NEXT_TAB,		D(LCTL), T(TAB), U(LCTL),END );
		BABLM( BABL_BROWSER_PREV_TAB,		D(LCTL), D(RSFT), T(TAB), U(RSFT), U(LCTL),END );
		BABLM( BABL_BROWSER_URL_BAR,		D(LCTL), T(L), U(LCTL),END );
		BABLM( BABL_BROWSER_FORWARD,		D(LALT), T(RIGHT), U(LALT),END );
		BABLM( BABL_BROWSER_BACK,			D(LALT), T(LEFT), U(LALT),END );
		BABLM( BABL_BROWSER_FIND,			D(LCTL), T(F), U(LCTL),END );
		BABLM( BABL_BROWSER_BOOKMARK,		D(LCTL), T(D), U(LCTL),END );
		BABLM( BABL_BROWSER_DEV_TOOLS,		D(LCTL), T(T), U(LCTL),END  ); // Chrome
		BABLM( BABL_BROWSER_RELOAD,			D(LCTL), T(F5), U(LCTL),END ); // hard reload w/o cache
		BABLM( BABL_BROWSER_FULLSCREEN,		T(F11),END ); //command shift F
		BABLM( BABL_BROWSER_ZOOM_IN,		D(LCTL), T(PLUS), U(LCTL),END );
		BABLM( BABL_BROWSER_ZOOM_OUT,		D(LCTL), T(MINS), U(LCTL),END );
#endif
#endif
	 return MACRO_NONE;
	
#endif 
	  
#ifdef MAC_MODE

	 case MAC_MODE:
		BABLM( BABL_GO_LEFT_1C ,	T(LEFT), END );
		BABLM( BABL_GO_RIGHT_1C,	T(RIGHT), END );
		BABLM( BABL_GO_LEFT_WORD ,	D(LALT), T(LEFT), U(LALT), END );
		BABLM( BABL_GO_RIGHT_WORD ,	D(LALT), T(RIGHT), U(LALT), END );
		BABLM( BABL_GO_START_LINE ,	D(LGUI), T(LEFT), U(LGUI),  END );
		BABLM( BABL_GO_END_LINE ,	D(LGUI), T(RIGHT), U(LGUI), END );
		BABLM( BABL_GO_START_DOC ,	D(LGUI),T(UP),  U(LGUI),END );
		BABLM( BABL_GO_END_DOC ,	D(LGUI),T(DOWN),  U(LGUI),END );
		BABLM( BABL_GO_NEXT_LINE ,	T(DOWN), END );
		BABLM( BABL_GO_PREV_LINE ,	T(UP), END );
		BABLM( BABL_PGDN ,		D(LALT),T(DOWN), U(LALT), END );
		BABLM( BABL_PGUP ,  	D(LALT),T(UP), U(LALT), END );
		BABLM( BABL_DEL_RIGHT_1C ,	D(DEL), END );	 
		BABLM( BABL_DEL_LEFT_WORD ,	D(LALT), T(BSPACE), U(LALT), END );
		BABLM( BABL_DEL_RIGHT_WORD,	D(LALT), T(DEL), U(LALT), END );
		BABLM( BABL_DEL_TO_LINE_END,	D(LCTL), T(K), U(LCTL), END );// there must be another way
		BABLM( BABL_DEL_TO_LINE_START,	D(LGUI), T(BSPACE), U(LGUI),   END );
#ifndef BABL_MOVEMENTONLY
		BABLM( BABL_UNDO , 		D(1), D(LGUI), T(Z), U(LGUI), END );
		BABLM( BABL_REDO , 		D(LSFT),D(LGUI), T(Z), U(LSFT),U(LGUI), END );
		BABLM( BABL_CUT ,		D(LGUI), T(X), U(LGUI), END );
		BABLM( BABL_COPY ,		D(LGUI), T(C), U(LGUI), END );
		BABLM( BABL_PASTE ,		D(LGUI), T(V), U(LGUI), END );			
		BABLM( BABL_SELECT_ALL ,	D(LGUI), T(A), U(LGUI), END );
		BABLM( BABL_FIND ,			D(LGUI),T(F),  U(LGUI),END );
		BABLM( BABL_FIND_NEXT, 		D(LGUI),T(G),  U(LGUI),END );
		BABLM( BABL_FIND_REPLACE,	D(LGUI),T(F),  U(LGUI),END );
		BABLM( BABL_RUNAPP ,		D(LGUI),T(R), U(LGUI),END );
		BABLM( BABL_SWITCH_APP_NEXT ,	D(LGUI),T(TAB), U(LGUI),END );
		BABLM( BABL_SWITCH_APP_LAST ,	D(LSFT),D(LGUI),T(TAB), U(LGUI), U(LSFT),END );
		BABLM( BABL_CLOSE_APP ,			D(LGUI),T(Q),  U(LGUI),END );
		BABLM( BABL_HELP ,				D(LSFT),D(LGUI),T(SLASH), U(LGUI), U(LSFT),END );

#ifndef BABL_NOBROWSER
		BABLM( BABL_BROWSER_NEW_TAB,		D(LGUI), T(T), U(LGUI),END );
		BABLM( BABL_BROWSER_CLOSE_TAB,		D(LGUI), T(W), U(LGUI),END );
		BABLM( BABL_BROWSER_REOPEN_LAST_TAB,		D(LGUI), D(RSFT),T(T), U(RSFT),U(LGUI),END );
		BABLM( BABL_BROWSER_NEXT_TAB,		D(LGUI),D(LALT), T(RIGHT),U(LALT), U(LGUI),END );
		BABLM( BABL_BROWSER_PREV_TAB,		D(LGUI), D(RSFT), T(LEFT), U(RSFT), U(LGUI),END );
		BABLM( BABL_BROWSER_URL_BAR,		D(LGUI), T(L), U(LGUI),END );
		BABLM( BABL_BROWSER_FORWARD,		D(LGUI), T(RIGHT), U(LGUI),END );
		BABLM( BABL_BROWSER_BACK,			D(LGUI), T(LEFT), U(LGUI),END );
		BABLM( BABL_BROWSER_FIND,			D(LGUI), T(F), U(LGUI),END );
		BABLM( BABL_BROWSER_BOOKMARK,		D(LGUI), T(D), U(LGUI),END );
		//BABLM( BABL_BROWSER_DEV_TOOLS,	T(F12), U(LGUI),END  ); // EDGE 
		BABLM( BABL_BROWSER_DEV_TOOLS,		D(LGUI), D(LALT), T(I), U(LALT),U(LGUI),END  ); // Chrome
		// Chrome
		BABLM( BABL_BROWSER_RELOAD,			D(LGUI), T(R), U(LGUI),END ); // add shift for reload w/o cache
		BABLM( BABL_BROWSER_FULLSCREEN,		D(LGUI), D(LCTL), T(P), U(LCTL), U(LGUI),END ); //command shift F
		BABLM( BABL_BROWSER_ZOOM_IN,		D(LGUI), D(RSFT), T(EQL), U(RSFT), U(LGUI),END ); // ctr+ +
		BABLM( BABL_BROWSER_ZOOM_OUT,		D(LGUI), T(MINS), U(LGUI),END );
#endif
#endif
			
	 return MACRO_NONE;
#endif 	
	
#ifdef EMACS_MODE

	 case EMACS_MODE:
	 	switch(shortcut) {
//probably should allow meta to not be ALT

		BABLM( BABL_GO_LEFT_1C,			T(LEFT), END );
		BABLM( BABL_GO_RIGHT_1C, 		T(RIGHT), END );
		BABLM( BABL_GO_LEFT_WORD, 		D(LALT), T(B), U(LALT), END );
		BABLM( BABL_GO_RIGHT_WORD ,		D(LALT), T(F), U(LALT), END );
		BABLM( BABL_GO_START_LINE ,  	D(LCTL), T(A), U(LCTL),  END );
		BABLM( BABL_GO_END_LINE ,  		D(LCTL), T(E), U(LCTL), END );
		BABLM( BABL_GO_START_DOC , 		D(LALT), D(LSFT), T(COMM),U(LSFT), U(LALT) ,END );
		BABLM( BABL_GO_END_DOC , 		D(LALT), D(LSFT), T(DOT), U(LSFT), U(LALT) ,END );
		BABLM( BABL_GO_NEXT_LINE , 		D(LCTL), T(N), U(LCTL), END );
		BABLM( BABL_GO_PREV_LINE ,  	D(LCTL), T(P), U(LCTL), END );
		BABLM( BABL_PGDN ,				D(LCTL), T(V), U(LCTL), END );
		BABLM( BABL_PGUP ,  			D(LALT), T(V), U(LALT), END );
		BABLM( BABL_DEL_RIGHT_1C, 		D(LCTL), T(D), U(LCTL),END );	 
		BABLM( BABL_DEL_LEFT_WORD , 	D(LCTL), T(BSPACE), U(LCTL), END );
		BABLM( BABL_DEL_RIGHT_WORD , 	D(LALT), T(D), U(LALT), END );
		BABLM( BABL_DEL_TO_LINE_END,	D(LCTL), T(K), U(LCTL), END ); 
		BABLM( BABL_DEL_TO_LINE_START,	T(ESC),  T(0), D(LCTL), T(K), U(LCTL),  END );
#ifndef BABL_MOVEMENTONLY
		BABLM( BABL_UNDO , 		D(LCTL), T(X), U(LCTL),T(C), END );
		BABLM( BABL_REDO , 		D(LCTL), T(X), U(LCTL),T(C), END ); // arguably
		BABLM( BABL_CUT , 		D(LCTL), T(W), U(LCTL), END );
		BABLM( BABL_COPY , 		D(LALT), T(W), U(LALT), END ); //really?
		BABLM( BABL_PASTE ,  	D(LCTL), T(Y), U(LCTL), END );			
		BABLM( BABL_SELECT_ALL ,D(LCTL), T(X), U(LCTL),T(H), END );	 
		BABLM( BABL_FIND , 		D(LCTL), T(S), U(LCTL),END );
		BABLM( BABL_FIND_NEXT , D(LCTL), T(S), U(LCTL),END );
		BABLM( BABL_FIND_REPLACE , 		D(LALT),D(LSFT), T(5),U(LSFT),  U(LALT), END );
		BABLM( BABL_RUNAPP , 			D(LALT), T(X), U(LALT),T(S),T(H),T(E),T(L),T(L),END );// arguably
		BABLM( BABL_SWITCH_APP_NEXT , 	D(LCTL), T(X), U(LCTL),T(RIGHT), END ); // arguably
		BABLM( BABL_SWITCH_APP_LAST , 	D(LCTL), T(X), U(LCTL),T(LEFT), END ); // arguably
		BABLM( BABL_CLOSE_APP ,			D(LCTL), T(X), U(LCTL),T(C),END );
		BABLM( BABL_HELP , 				D(LCTL),T(H), U(LCTL),T(A),END); // start search in help
#ifndef BABL_NOBROWSER
/* you get to figure w3 out 
		BABLM( BABL_BROWSER_NEW_TAB,		D(LGUI), T(T), U(LGUI),END );
		BABLM( BABL_BROWSER_CLOSE_TAB,		D(LGUI), T(W), U(LGUI),END );
		BABLM( BABL_BROWSER_REOPEN_LAST_TAB,		D(LGUI), D(RSFT),T(T), U(RSFT),U(LGUI),END );
		BABLM( BABL_BROWSER_NEXT_TAB,		D(LGUI),D(LALT), T(RIGHT),U(LALT), U(LGUI),END );
		BABLM( BABL_BROWSER_PREV_TAB,		D(LGUI), D(RSFT), T(LEFT), U(RSFT), U(LGUI),END );
		BABLM( BABL_BROWSER_URL_BAR,		D(LGUI), T(L), U(LGUI),END );
		BABLM( BABL_BROWSER_FORWARD,		D(LGUI), T(RIGHT), U(LGUI),END );
		BABLM( BABL_BROWSER_BACK,			D(LGUI), T(LEFT), U(LGUI),END );
		BABLM( BABL_BROWSER_FIND,			D(LGUI), T(F), U(LGUI),END );
		BABLM( BABL_BROWSER_BOOKMARK,		D(LGUI), T(D), U(LGUI),END );
		//BABLM( BABL_BROWSER_DEV_TOOLS,	T(F12), U(LGUI),END  ); // EDGE 
		BABLM( BABL_BROWSER_DEV_TOOLS,		D(LGUI), D(LALT), T(I), U(LALT),U(LGUI),END  ); // Chrome
		// Chrome
		BABLM( BABL_BROWSER_RELOAD,			D(LGUI), T(R), U(LGUI),END ); // add shift for reload w/o cache
		BABLM( BABL_BROWSER_FULLSCREEN,		D(LGUI), D(LCTL), T(P), U(LCTL), U(LGUI),END ); //command shift F
		BABLM( BABL_BROWSER_ZOOM_IN,		D(LGUI), D(RSFT), T(EQL), U(RSFT), U(LGUI),END ); // ctr+ +
		BABLM( BABL_BROWSER_ZOOM_OUT,		D(LGUI), T(MINS), U(LGUI),END );
*/
#endif
#endif
				break;
	 
	 return MACRO_NONE;
	}
	
#endif 	


#ifdef VI_MODE
	 case VI_MODE:
// you have to track the modes yourself. Otherwise motion is awful (bell, bell, bell)
			
			
			BABLM( BABL_GO_LEFT_1C , T(H), END );
			BABLM( BABL_GO_RIGHT_1C , T(L), END );
			BABLM( BABL_GO_LEFT_WORD , T(B),END );
			BABLM( BABL_GO_RIGHT_WORD , T(W), END );
			BABLM( BABL_GO_START_LINE , D(LSFT), T(6),U(LSFT), END ); //^
			BABLM( BABL_GO_END_LINE ,   D(LSFT), T(4),U(LSFT) , END ); //$
			BABLM( BABL_GO_START_DOC , T(G),T(G) ,END );
			BABLM( BABL_GO_END_DOC , D(LSFT), T(G),U(LSFT),END );
			BABLM( BABL_GO_NEXT_LINE ,  T(J), END );
			BABLM( BABL_GO_PREV_LINE,  T(K), END );
			BABLM( BABL_PGDN ,D(LCTL), T(F), U(LCTL), END );
			BABLM( BABL_PGUP , D(LCTL), T(B), U(LCTL), END );
			BABLM( BABL_DEL_RIGHT_1C ,  T(X),END );	 
			BABLM( BABL_DEL_LEFT_WORD ,  T(D),T(G),T(E),END );
			BABLM( BABL_DEL_RIGHT_WORD ,  T(D),T(W),END );
			BABLM( BABL_DEL_TO_LINE_END,	T(D),D(LSFT), T(4),U(LSFT) ,END ); // d$
			BABLM( BABL_DEL_TO_LINE_START,	T(D),D(LSFT), T(6),U(LSFT) ,END ); 
#ifndef BABL_MOVEMENTONLY
			BABLM( BABL_UNDO , T(U), END );
 			BABLM( BABL_REDO ,  D(LCTL), T(R), U(LCTL), END );  
 			BABLM( BABL_CUT ,  T(X), END );
 			BABLM( BABL_COPY , T(Y),END );
			BABLM( BABL_PASTE ,  T(P), END );			
			BABLM( BABL_SELECT_ALL , D(LSFT), T(SCLN),U(LSFT),D(LSFT), T(5),U(LSFT),T(Y), END ); // wrong but helpful? 
			BABLM( BABL_FIND ,   T(SLASH),END );
			BABLM( BABL_FIND_NEXT , T(N),END );
			BABLM( BABL_FIND_REPLACE ,  D(LALT),D(LSFT), T(5),U(LSFT),  U(LALT), END );
			BABLM( BABL_RUNAPP,END );
			BABLM( BABL_SWITCH_APP_NEXT		,END );
			BABLM( BABL_SWITCH_APP_LAST		,END );
			BABLM(BABL_CLOSE_APP,	D(LSFT), T(SCLN),U(LSFT), T(Q), D(RSFT), T(1),U(RSFT), END );
			BABLM(BABL_HELP,	 D(LSFT), T(SCLN),U(LSFT),T(H),END); // start search in help
#ifndef BABL_NOBROWSER
/* you get to figure this out 
		BABLM( BABL_BROWSER_NEW_TAB,		D(LGUI), T(T), U(LGUI),END );
		BABLM( BABL_BROWSER_CLOSE_TAB,		D(LGUI), T(W), U(LGUI),END );
		BABLM( BABL_BROWSER_REOPEN_LAST_TAB,		D(LGUI), D(RSFT),T(T), U(RSFT),U(LGUI),END );
		BABLM( BABL_BROWSER_NEXT_TAB,		D(LGUI),D(LALT), T(RIGHT),U(LALT), U(LGUI),END );
		BABLM( BABL_BROWSER_PREV_TAB,		D(LGUI), D(RSFT), T(LEFT), U(RSFT), U(LGUI),END );
		BABLM( BABL_BROWSER_URL_BAR,		D(LGUI), T(L), U(LGUI),END );
		BABLM( BABL_BROWSER_FORWARD,		D(LGUI), T(RIGHT), U(LGUI),END );
		BABLM( BABL_BROWSER_BACK,			D(LGUI), T(LEFT), U(LGUI),END );
		BABLM( BABL_BROWSER_FIND,			D(LGUI), T(F), U(LGUI),END );
		BABLM( BABL_BROWSER_BOOKMARK,		D(LGUI), T(D), U(LGUI),END );
		//BABLM( BABL_BROWSER_DEV_TOOLS,	T(F12), U(LGUI),END  ); // EDGE 
		BABLM( BABL_BROWSER_DEV_TOOLS,		D(LGUI), D(LALT), T(I), U(LALT),U(LGUI),END  ); // Chrome
		// Chrome
		BABLM( BABL_BROWSER_RELOAD,			D(LGUI), T(R), U(LGUI),END ); // add shift for reload w/o cache
		BABLM( BABL_BROWSER_FULLSCREEN,		D(LGUI), D(LCTL), T(P), U(LCTL), U(LGUI),END ); //command shift F
		BABLM( BABL_BROWSER_ZOOM_IN,		D(LGUI), T(PLUS), U(LGUI),END );
		BABLM( BABL_BROWSER_ZOOM_OUT,		D(LGUI), T(MINS), U(LGUI),END );
*/
#endif
#endif	 
		 return MACRO_NONE;	
#endif




#ifdef READMUX_MODE
// Readline command line editing + tmux windowing
// I havent decided how much to do readline and how much tmux
	
	
	case READMUX_MODE:		
		
		BABLM( BABL_GO_LEFT_1C , 		T(LEFT), END );
		BABLM( BABL_GO_RIGHT_1C , 		T(RIGHT), END );
		BABLM( BABL_GO_LEFT_WORD , 		D(LALT), T(B), U(LALT), END );
		BABLM( BABL_GO_RIGHT_WORD , 	D(LALT), T(F), U(LALT), END );
		BABLM( BABL_GO_START_LINE ,  	D(LCTL), T(A), U(LCTL),  END );
		BABLM( BABL_GO_END_LINE ,  		D(LCTL), T(E), U(LCTL), END );
		//BABLM( BABL_GO_START_DOC		,END );// tmux?
		//BABLM( BABL_GO_END_DOC		,END );  // tmux?
		BABLM( BABL_GO_NEXT_LINE ,  	D(LCTL), T(N), U(LCTL), END );
		BABLM( BABL_GO_PREV_LINE ,  	D(LCTL), T(P), U(LCTL), END );
		BABLM( BABL_PGDN , 			T(PGDN), END );
		BABLM( BABL_PGUP , 			T(PGUP), END );
		BABLM( BABL_DEL_RIGHT_1C , 	D(LCTL), T(D), U(LCTL),END );	 
		BABLM( BABL_DEL_LEFT_WORD , D(LCTL), T(W), U(LCTL), END );
		BABLM( BABL_DEL_RIGHT_WORD , 	D(LALT), T(D), U(LALT), END );
		BABLM( BABL_DEL_TO_LINE_END,	D(LCTL), T(K), U(LCTL), END ); 
		BABLM( BABL_DEL_TO_LINE_START,	D(LCTL), T(U), U(LCTL),  END );
#ifndef BABL_MOVEMENTONLY
		BABLM( BABL_UNDO , 			D(LALT), T(R), U(LALT) , END );
		BABLM( BABL_REDO , 			D(LCTL), T(X), U(LCTL),T(C), END ); // arguably
		BABLM( BABL_CUT , 			D(LCTL), T(K), U(LCTL), END ); // wrong half the time
		//BABLM( BABL_COPY		,END ); 
		BABLM( BABL_PASTE ,  		D(LCTL), T(Y), U(LCTL), END );			
		BABLM( BABL_SELECT_ALL ,	D(LCTL), T(A), T(K), T(Y), U(LCTL) , END );	 
		BABLM( BABL_FIND ,  		D(LCTL), T(R), U(LCTL), END ); // search history
		BABLM(BABL_FIND_NEXT,  		D(LCTL), T(S), U(LCTL), END );
		//BABLM( BABL_FIND_REPLACE		,END ); 
		BABLM( BABL_RUNAPP ,  		D(LCTL), T(B), U(LCTL),  T(C),END );  //tmux
		BABLM( BABL_SWITCH_APP_NEXT ,  D(LCTL), T(B), U(LCTL),  T(N),END );  //tmux
		BABLM( BABL_SWITCH_APP_LAST ,  D(LCTL), T(B), U(LCTL),  T(P),END );  //tmux
		BABLM( BABL_CLOSE_APP , 		D(LCTL), T(B), U(LCTL),  T(D),END); // usually what I want
		// BABLM( BABL_HELP		,END ); 
#ifndef BABL_NOBROWSER
/* Add lynx shortcuts? 
		BABLM( BABL_BROWSER_NEW_TAB,		D(LGUI), T(T), U(LGUI),END );
		BABLM( BABL_BROWSER_CLOSE_TAB,		D(LGUI), T(W), U(LGUI),END );
		BABLM( BABL_BROWSER_REOPEN_LAST_TAB,		D(LGUI), D(RSFT),T(T), U(RSFT),U(LGUI),END );
		BABLM( BABL_BROWSER_NEXT_TAB,		D(LGUI),D(LALT), T(RIGHT),U(LALT), U(LGUI),END );
		BABLM( BABL_BROWSER_PREV_TAB,		D(LGUI), D(RSFT), T(LEFT), U(RSFT), U(LGUI),END );
		BABLM( BABL_BROWSER_URL_BAR,		D(LGUI), T(L), U(LGUI),END );
		BABLM( BABL_BROWSER_FORWARD,		D(LGUI), T(RIGHT), U(LGUI),END );
		BABLM( BABL_BROWSER_BACK,			D(LGUI), T(LEFT), U(LGUI),END );
		BABLM( BABL_BROWSER_FIND,			D(LGUI), T(F), U(LGUI),END );
		BABLM( BABL_BROWSER_BOOKMARK,		D(LGUI), T(D), U(LGUI),END );
		//BABLM( BABL_BROWSER_DEV_TOOLS,	T(F12), U(LGUI),END  ); // EDGE 
		BABLM( BABL_BROWSER_DEV_TOOLS,		D(LGUI), D(LALT), T(I), U(LALT),U(LGUI),END  ); // Chrome
		// Chrome
		BABLM( BABL_BROWSER_RELOAD,			D(LGUI), T(R), U(LGUI),END ); // add shift for reload w/o cache
		BABLM( BABL_BROWSER_FULLSCREEN,		D(LGUI), D(LCTL), T(P), U(LCTL), U(LGUI),END ); //command shift F
		BABLM( BABL_BROWSER_ZOOM_IN,		D(LGUI), T(PLUS), U(LGUI),END );
		BABLM( BABL_BROWSER_ZOOM_OUT,		D(LGUI), T(MINS), U(LGUI),END );
*/
#endif
#endif
		
	return MACRO_NONE;
	
#endif 			

	default:	
    	return MACRO_NONE;
    }

}


#endif