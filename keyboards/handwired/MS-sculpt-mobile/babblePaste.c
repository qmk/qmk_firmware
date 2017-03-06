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

		
// Today I learned that the preprocessor can not create a switch statement label from an argument
// And else statements have problems, see https://gcc.gnu.org/onlinedocs/gcc-3.0.1/cpp_3.html#SEC15
#define BABLM(ent, macro...) \
	if ( ent == shortcut ) \
		 {  action_macro_play( MACRO(macro)); return MACRO_NONE; }   


const  macro_t *babblePaste (keyrecord_t *record,  uint8_t shortcut) {
/* this function runs the appropriate babblepaste macro, given
the global babble_mode, and a shortcut from the ENUM in babblePaste.h 
TODO, the pointers in this function should be stored in a PROGMEM array, not ram. 
But that requires even more clever preprocessor foo.
*/

	 if ( shortcut < BABL_START_NUM || \
			 shortcut >= (BABL_START_NUM + BABL_NUM_MACROS ) ) {
			return MACRO_NONE;
		}


  switch(babble_mode) {
     	
#ifdef MS_MODE

	 case MS_MODE:	
		BABLM( BABL_DEL_RIGHT_1C,	T(DEL), END );
		BABLM( BABL_DEL_LEFT_WORD,	D(LCTRL), T(BSPACE), U(LCTRL), END );
		BABLM( BABL_DEL_RIGHT_WORD,D(LCTRL), T(DEL), U(LCTRL), END );
		BABLM( BABL_GO_LEFT_1C,	T(LEFT), END );
		BABLM( BABL_GO_RIGHT_1C ,	T(RIGHT), END );
		BABLM( BABL_GO_LEFT_WORD,	D(LCTRL), T(LEFT), U(LCTRL), END );
		BABLM( BABL_GO_RIGHT_WORD, D(LCTRL), T(RIGHT), U(LCTRL), END );
		BABLM( BABL_GO_START_LINE,	T(HOME), END );
		BABLM( BABL_GO_START_DOC,	D(LCTRL),T(HOME),  U(LCTRL),END );
		BABLM( BABL_GO_END_LINE,	T(END), END );
		BABLM( BABL_GO_END_DOC,	D(LCTRL),T(END),  U(LCTRL),END );
		BABLM( BABL_GO_NEXT_LINE,	T(DOWN), END );
		BABLM( BABL_GO_PREV_LINE,	T(UP), END );
		BABLM( BABL_PGDN,			T(PGDN), END );
		BABLM( BABL_PGUP,			T(PGUP), END );
#ifndef BABL_MOVEMENTONLY
		BABLM( BABL_UNDO, 		D(LCTRL), T(Z), U(LCTRL), END );
		BABLM( BABL_REDO, 		D(LCTRL), T(Y), U(LCTRL), END );
		BABLM( BABL_CUT, 		D(LCTRL), T(X), U(LCTRL), END );
		BABLM( BABL_COPY, 		D(LCTRL), T(C), U(LCTRL), END );
		BABLM( BABL_PASTE, 		D(LCTRL), T(V), U(LCTRL), END );		
		BABLM( BABL_SELECT_ALL, D(LCTRL), T(A), U(LCTRL), END );
		BABLM( BABL_UNDO, 		D(LCTRL), T(Z), U(LCTRL), END );
		BABLM( BABL_REDO, 		D(LCTRL), T(Y), U(LCTRL), END );
		BABLM( BABL_CUT, 		D(LCTRL), T(X), U(LCTRL), END );
		BABLM( BABL_COPY, 		D(LCTRL), T(C), U(LCTRL), END );
		BABLM( BABL_PASTE, 		D(LCTRL), T(V), U(LCTRL), END );			
		BABLM( BABL_SELECT_ALL, 		D(LCTRL), T(A), U(LCTRL), END );
		BABLM( BABL_FIND, 		D(LCTRL),T(F),  U(LCTRL),END );
		BABLM( BABL_FIND_NEXT, 			T(F3),END );
		BABLM( BABL_FIND_REPLACE,		D(LCTRL),T(H),  U(LCTRL),END );
		BABLM( BABL_RUNAPP, 	D(LGUI),T(R),  U(LGUI),END );
		BABLM( BABL_SWITCH_APP_NEXT, D(LALT),T(TAB), U(LALT),END );
		BABLM( BABL_SWITCH_APP_LAST, D(LSFT),D(LALT),T(TAB), U(LALT), U(LSFT),END );
		BABLM( BABL_CLOSE_APP, 	D(LALT),T(F4), U(LALT),END );
		BABLM( BABL_HELP,		T(F1),END );
#endif


		return MACRO_NONE;
		
	 	
#endif /* MS_MODE*/


#ifdef LINUX_MODE
	 case LINUX_MODE:
	
		BABLM( BABL_DEL_RIGHT_1C  , 	D(DEL), END );	 
		BABLM( BABL_DEL_LEFT_WORD  ,	D(LCTRL), T(BSPACE), U(LCTRL), END );
		BABLM( BABL_DEL_RIGHT_WORD  , D(LCTRL), T(DEL), U(LCTRL), END );
		BABLM( BABL_GO_LEFT_1C  , 	T(LEFT), END );
		BABLM( BABL_GO_RIGHT_1C  , 	T(RIGHT), END );
		BABLM( BABL_GO_LEFT_WORD  , 	D(LCTRL), T(LEFT), U(LCTRL), END );
		BABLM( BABL_GO_RIGHT_WORD  , D(LCTRL), T(RIGHT), U(LCTRL), END );
		BABLM( BABL_GO_START_LINE , 	T(HOME), END );
		BABLM( BABL_GO_START_DOC  , 	D(LCTRL),T(HOME),  U(LCTRL),END );
		BABLM( BABL_GO_END_LINE  ,	T(END), END );
		BABLM( BABL_GO_END_DOC  , 	D(LCTRL),T(END),  U(LCTRL),END );
		BABLM( BABL_GO_NEXT_LINE  , 	T(DOWN), END );
		BABLM( BABL_GO_PREV_LINE  , 	T(UP), END );
		BABLM( BABL_PGDN  , 			T(PGDN), END );
		BABLM( BABL_PGUP  , 			T(PGUP), END );
#ifndef BABL_MOVEMENTONLY
		BABLM( BABL_UNDO  , 	D(LCTRL), T(Z), U(LCTRL), END );
		BABLM( BABL_REDO  , 	D(LCTRL), T(Y), U(LCTRL), END );
		BABLM( BABL_CUT  , 	D(LCTRL), T(X), U(LCTRL), END );
		BABLM( BABL_COPY  , 	D(LCTRL), T(C), U(LCTRL), END );
		BABLM( BABL_PASTE  ,	D(LCTRL), T(V), U(LCTRL), END );			
		BABLM( BABL_SELECT_ALL, D(LCTRL), T(A), U(LCTRL), END );	
		BABLM( BABL_FIND,	D(LCTRL),T(F),  U(LCTRL),END );
		/* BABLM(BABL_FIND_NEXT  , T(F3),END ); KDE */
		BABLM( BABL_FIND_NEXT,	D(LCTRL),T(G),  U(LCTRL),END ); // Gnome*/
		/* BABLM(  , D(LCTRL),T(R),  U(LCTRL),END ); KDE */
		BABLM( BABL_FIND_REPLACE,	D(LCTRL),T(H),  U(LCTRL),END ); // Gnome*/
		BABLM( BABL_RUNAPP,			D(LALT),T(F2),  U(LALT),END );
		BABLM( BABL_SWITCH_APP_NEXT,	D(LCTL),T(TAB), U(LCTL),END );
		BABLM( BABL_SWITCH_APP_LAST,	D(LSFT),D(LCTL),T(TAB), U(LCTL), U(LSFT),END );
		BABLM( BABL_CLOSE_APP,	D(LALT),T(F4), U(LALT),END );
		BABLM( BABL_HELP, 		END ); 
#endif
	 return MACRO_NONE;
	
#endif 
	  
#ifdef MAC_MODE
	 case MAC_MODE:
		BABLM( BABL_DEL_RIGHT_1C ,	D(DEL), END );	 
		BABLM( BABL_DEL_LEFT_WORD ,	D(LALT), T(BSPACE), U(LALT), END );
		BABLM( BABL_DEL_RIGHT_WORD,	D(LALT), T(DEL), U(LALT), END );
		BABLM( BABL_GO_LEFT_1C ,	T(LEFT), END );
		BABLM( BABL_GO_RIGHT_1C,	T(RIGHT), END );
		BABLM( BABL_GO_LEFT_WORD ,	D(LALT), T(LEFT), U(LALT), END );
		BABLM( BABL_GO_RIGHT_WORD ,	D(LALT), T(RIGHT), U(LALT), END );
		BABLM( BABL_GO_START_LINE ,	D(LGUI), T(LEFT), U(LGUI),  END );
		BABLM( BABL_GO_START_DOC ,	D(LGUI),T(UP),  U(LGUI),END );
		BABLM( BABL_GO_END_LINE ,	D(LGUI), T(RIGHT), U(LGUI), END );
		BABLM( BABL_GO_END_DOC ,	D(LGUI),T(DOWN),  U(LGUI),END );
		BABLM( BABL_GO_NEXT_LINE ,	T(DOWN), END );
		BABLM( BABL_GO_PREV_LINE ,	T(UP), END );
		BABLM( BABL_PGDN ,		D(LALT),T(DOWN), U(LALT), END );
		BABLM( BABL_PGUP ,  	D(LALT),T(UP), U(LALT), END );
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
#endif
			
	 return MACRO_NONE;
#endif 	
	
#ifdef EMACS_MODE
	 case EMACS_MODE:
	 	switch(shortcut) {
//probably should allow meta to not be ALT
			
			case BABL_DEL_RIGHT_1C:
				 BABLM(  , D(LCTL), T(D), U(LCTL),END );	 
			case BABL_DEL_LEFT_WORD:
 				BABLM(  , D(LCTL), T(BSPACE), U(LCTL), END );
			case BABL_DEL_RIGHT_WORD:
 				BABLM(  , D(LALT), T(D), U(LALT), END );
			case BABL_GO_LEFT_1C:
 				BABLM(  , T(LEFT), END );
			case BABL_GO_RIGHT_1C:
 				BABLM(  , T(RIGHT), END );
			case BABL_GO_LEFT_WORD:
 				BABLM(  , D(LALT), T(B), U(LALT), END );
			case BABL_GO_RIGHT_WORD:
 				BABLM(  , D(LALT), T(F), U(LALT), END );
			case BABL_GO_START_LINE:
 				BABLM(  ,  D(LCTRL), T(A), U(LCTRL),  END );
			case BABL_GO_START_DOC:
 				BABLM(  , D(LALT), D(LSFT), T(COMM),U(LSFT), U(LALT) ,END );
			case BABL_GO_END_LINE:
 				BABLM(  ,  D(LCTRL), T(E), U(LCTRL), END );
			case BABL_GO_END_DOC:
 				BABLM(  , D(LALT), D(LSFT), T(DOT),U(LSFT), U(LALT) ,END );
			case BABL_GO_NEXT_LINE:
 				BABLM(  ,  D(LCTRL), T(N), U(LCTRL), END );
			case BABL_GO_PREV_LINE:
				BABLM(  ,  D(LCTRL), T(P), U(LCTRL), END );
			case BABL_PGDN:
 				BABLM(  ,D(LCTRL), T(V), U(LCTRL), END );
			case BABL_PGUP:
				BABLM(  ,  D(LALT), T(V), U(LALT), END );
#ifndef BABL_MOVEMENTONLY
			case BABL_UNDO:
					BABLM(  , D(LCTL), T(X), U(LCTL),T(C), END );
			case BABL_REDO:
 					BABLM(  , D(LCTL), T(X), U(LCTL),T(C), END ); // arguably
			case BABL_CUT:
 					BABLM(  , D(LCTL), T(W), U(LCTL), END );
			case BABL_COPY:
 					BABLM(  , D(LALT), T(W), U(LALT), END ); //really?
			case BABL_PASTE:
 					BABLM(  ,  D(LCTL), T(Y), U(LCTL), END );			
			case BABL_SELECT_ALL:
 					BABLM(  ,D(LCTL), T(X), U(LCTL),T(H), END );	 
 			case BABL_FIND:
 				BABLM(  , D(LCTRL), T(S), U(LCTRL),END );
			case BABL_FIND_NEXT:
 				BABLM(  , D(LCTRL), T(S), U(LCTRL),END );
			case BABL_FIND_REPLACE:
 				BABLM(  ,  D(LALT),D(LSFT), T(5),U(LSFT),  U(LALT), END );
			case BABL_RUNAPP:
				BABLM(  , D(LALT), T(X), U(LALT),T(S),T(H),T(E),T(L),T(L),END );// arguably
			case BABL_SWITCH_APP_NEXT:
				BABLM(  , D(LCTL), T(X), U(LCTL),T(RIGHT), END ); // arguably
			case BABL_SWITCH_APP_LAST:
				BABLM(  , D(LCTL), T(X), U(LCTL),T(LEFT), END ); // arguably
	 		case BABL_CLOSE_APP:
				BABLM(  ,D(LCTL), T(X), U(LCTL),T(C),END );
	 		case BABL_HELP:
				BABLM(  , D(LCTL),T(H), U(LCTL),T(A),END); // start search in help
#endif
				break;
	 
	 return MACRO_NONE;
	}
	
#endif 	
#ifdef VI_MODE
	 case VI_MODE:
//assume esc is already called
			
			BABLM( BABL_DEL_RIGHT_1C ,  T(X),END );	 
			BABLM( BABL_DEL_LEFT_WORD ,  T(D),T(G),T(E),END );
			BABLM( BABL_DEL_RIGHT_WORD ,  T(D),T(W),END );
			BABLM( BABL_GO_LEFT_1C , T(H), END );
			BABLM( BABL_GO_RIGHT_1C , T(L), END );
			BABLM( BABL_GO_LEFT_WORD , T(B),END );
			BABLM( BABL_GO_RIGHT_WORD , T(W), END );
			BABLM( BABL_GO_START_LINE , D(LSFT), T(6),U(LSFT), END ); //^
			BABLM( BABL_GO_START_DOC , T(G),T(G) ,END );
			BABLM( BABL_GO_END_LINE ,   D(LSFT), T(4),U(LSFT) , END ); //$
			BABLM( BABL_GO_END_DOC , D(LSFT), T(G),U(LSFT),END );
			BABLM( BABL_GO_NEXT_LINE ,  T(J), END );
			BABLM( BABL_GO_PREV_LINE,  T(K), END );
			BABLM( BABL_PGDN ,D(LCTRL), T(F), U(LCTRL), END );
			BABLM( BABL_PGUP , D(LCTRL), T(B), U(LCTRL), END );
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
#endif	 
		 return MACRO_NONE;	
#endif




#ifdef READMUX_MODE
// Readline command line editing + tmux windowing
// I havent decided how much to do readline and how much tmux
	case READMUX_MODE:		
		BABLM( BABL_DEL_RIGHT_1C , D(LCTL), T(D), U(LCTL),END );	 
		BABLM( BABL_DEL_LEFT_WORD , D(LCTL), T(W), U(LCTL), END );
		BABLM( BABL_DEL_RIGHT_WORD , D(LALT), T(D), U(LALT), END );
		BABLM( BABL_GO_LEFT_1C , T(LEFT), END );
		BABLM( BABL_GO_RIGHT_1C , T(RIGHT), END );
		BABLM( BABL_GO_LEFT_WORD , D(LALT), T(B), U(LALT), END );
		BABLM( BABL_GO_RIGHT_WORD , D(LALT), T(F), U(LALT), END );
		BABLM( BABL_GO_START_LINE ,  D(LCTRL), T(A), U(LCTRL),  END );
		BABLM( BABL_GO_START_DOC		,END );// tmux?
		BABLM( BABL_GO_END_LINE ,  D(LCTRL), T(E), U(LCTRL), END );
		BABLM( BABL_GO_END_DOC		,END );  // tmux?
		BABLM( BABL_GO_NEXT_LINE ,  D(LCTRL), T(N), U(LCTRL), END );
		BABLM( BABL_GO_PREV_LINE ,  D(LCTRL), T(P), U(LCTRL), END );
		BABLM( BABL_PGDN , T(PGDN), END );
		BABLM( BABL_PGUP , T(PGUP), END );
#ifndef BABL_MOVEMENTONLY
		BABLM( BABL_UNDO , D(LALT), T(R), U(LALT) , END );
		BABLM( BABL_REDO , D(LCTL), T(X), U(LCTL),T(C), END ); // arguably
		BABLM( BABL_CUT , D(LCTL), T(K), U(LCTL), END ); // wrong half the time
		BABLM( BABL_COPY		,END ); 
		BABLM( BABL_PASTE ,  D(LCTL), T(Y), U(LCTL), END );			
		BABLM( BABL_SELECT_ALL ,D(LCTL), T(A), T(K), T(Y), U(LCTL) , END );	 
		BABLM( BABL_FIND ,  D(LCTRL), T(R), U(LCTRL), END ); // search history
		BABLM(BABL_FIND_NEXT,  D(LCTRL), T(S), U(LCTRL), END );
		BABLM( BABL_FIND_REPLACE		,END ); 
		BABLM( BABL_RUNAPP ,  D(LCTRL), T(B), U(LCTRL),  T(C),END );  //tmux
		BABLM( BABL_SWITCH_APP_NEXT ,  D(LCTRL), T(B), U(LCTRL),  T(N),END );  //tmux
		BABLM( BABL_SWITCH_APP_LAST ,  D(LCTRL), T(B), U(LCTRL),  T(P),END );  //tmux
		BABLM( BABL_CLOSE_APP , D(LCTRL), T(B), U(LCTRL),  T(D),END); // usually what I want
		BABLM( BABL_HELP		,END ); 
#endif
		
	return MACRO_NONE;
	
#endif 			

	default:	
    	return MACRO_NONE;
    }

}


#endif