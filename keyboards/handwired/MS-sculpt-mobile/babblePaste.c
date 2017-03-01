/*  A library to output the right key shortcut in any common app. 
Given a global variable babble_mode to show the environment and a 
key that calls the paste macro, do the right type of paste. 
Setting the context is done by another macro, or TBD interaction with the host. 

Huge thanks to https://en.wikipedia.org/wiki/Table_of_keyboard_shortcuts
and https://github.com/qmk/qmk_firmware/blob/master/keyboards/planck/keymaps/jeebak/keymap.c 
*/

#include "babblePaste.h"
#include "action_layer.h"

// GLOBAL variable. Sets startup default if no eeppom
char babble_mode = MAC_MODE ;


const static  macro_t *babblePaste (keyrecord_t *record,  uint16_t shortcut) {

    switch(babble_mode) {
    
#ifdef MS_MODE
	 case MS_MODE:
	 	switch(shortcut) {
	  
			case BABL_DEL_RIGHT_1C:
				 return (static macro_t *) MACRO( D(DEL), END );	 
			case BABL_DEL_LEFT_WORD:
 				return MACRO( D(LCTRL), T(BSPACE), U(LCTRL), END );
			case BABL_DEL_RIGHT_WORD:
 				return MACRO( D(LCTRL), T(DEL), U(LCTRL), END );
			case BABL_GO_LEFT_1C:
 				return MACRO( T(LEFT), END );
			case BABL_GO_RIGHT_1C:
 				return MACRO( T(RIGHT), END );
			case BABL_GO_LEFT_WORD:
 				return MACRO( D(LCTRL), T(LEFT), U(LCTRL), END );
			case BABL_GO_RIGHT_WORD:
 				return MACRO( D(LCTRL), T(RIGHT), U(LCTRL), END );
			case BABL_GO_START_LINE:
 				return MACRO( T(HOME), END );
			case BABL_GO_START_DOC:
 				return MACRO( D(LCTRL),T(HOME),  U(LCTRL),END );
			case BABL_GO_END_LINE:
 				return MACRO( T(END), END );
			case BABL_GO_END_DOC:
 				return MACRO( D(LCTRL),T(END),  U(LCTRL),END );
			case BABL_GO_NEXT_LINE:
 				return MACRO( T(DOWN), END );
			case BABL_GO_PREV_LINE:
				return MACRO( T(UP), END );
			case BABL_PGDN:
 				return MACRO( T(PGDN), END );
			case BABL_PGUP:
				return MACRO( T(PGUP), END );
#ifndef BABL_MOVEMENTONLY
			case BABL_UNDO:
					return MACRO( D(LCTRL), T(Z), U(LCTRL), END );
			case BABL_REDO:
 					return MACRO( D(LCTRL), T(Y), U(LCTRL), END );
			case BABL_CUT:
 					return MACRO( D(LCTRL), T(X), U(LCTRL), END );
			case BABL_COPY:
 					return MACRO( D(LCTRL), T(C), U(LCTRL), END );
			case BABL_PASTE:
 					return MACRO( D(LCTRL), T(V), U(LCTRL), END );			
			case BABL_SELECT_ALL:
 					return MACRO( D(LCTRL), T(A), U(LCTRL), END );	 
			case BABL_UNDO:
					return MACRO( D(LCTRL), T(Z), U(LCTRL), END );
			case BABL_REDO:
 					return MACRO( D(LCTRL), T(Y), U(LCTRL), END );
			case BABL_CUT:
 					return MACRO( D(LCTRL), T(X), U(LCTRL), END );
			case BABL_COPY:
 					return MACRO( D(LCTRL), T(C), U(LCTRL), END );
			case BABL_PASTE:
 					return MACRO( D(LCTRL), T(V), U(LCTRL), END );			
			case BABL_SELECT_ALL:
 					return MACRO( D(LCTRL), T(A), U(LCTRL), END );	 
			case BABL_FIND:
 				return MACRO( D(LCTRL),T(F),  U(LCTRL),END );
			case BABL_FIND_NEXT:
 				return MACRO( T(F3),END );
			case BABL_FIND_REPLACE:
 				return MACRO( D(LCTRL),T(H),  U(LCTRL),END );
			case BABL_RUNAPP:
				return MACRO( D(LGUI),T(R),  U(LGUI),END );
			case BABL_SWITCH_APP_NEXT:
				return MACRO( D(LALT),T(TAB), U(LALT),END );
			case BABL_SWITCH_APP_LAST:
				return MACRO( D(LSFT),D(LALT),T(TAB), U(LALT), U(LSFT),END );
			case BABL_CLOSE_APP:
				return MACRO( D(LALT),T(F4), U(LALT),END );
			case BABL_HELP:
				return MACRO( T(F1),END );
#endif
	 			break;
	 
	 return MACRO_NONE;
	}
	
#endif 
#ifdef LINUX_MODE
	 case LINUX_MODE:
	 	switch(shortcut) {
 
			case BABL_DEL_RIGHT_1C:
				 return MACRO( D(DEL), END );	 
			case BABL_DEL_LEFT_WORD:
 				return MACRO( D(LCTRL), T(BSPACE), U(LCTRL), END );
			case BABL_DEL_RIGHT_WORD:
 				return MACRO( D(LCTRL), T(DEL), U(LCTRL), END );
			case BABL_GO_LEFT_1C:
 				return MACRO( T(LEFT), END );
			case BABL_GO_RIGHT_1C:
 				return MACRO( T(RIGHT), END );
			case BABL_GO_LEFT_WORD:
 				return MACRO( D(LCTRL), T(LEFT), U(LCTRL), END );
			case BABL_GO_RIGHT_WORD:
 				return MACRO( D(LCTRL), T(RIGHT), U(LCTRL), END );
			case BABL_GO_START_LINE:
 				return MACRO( T(HOME), END );
			case BABL_GO_START_DOC:
 				return MACRO( D(LCTRL),T(HOME),  U(LCTRL),END );
			case BABL_GO_END_LINE:
 				return MACRO( T(END), END );
			case BABL_GO_END_DOC:
 				return MACRO( D(LCTRL),T(END),  U(LCTRL),END );
			case BABL_GO_NEXT_LINE:
 				return MACRO( T(DOWN), END );
			case BABL_GO_PREV_LINE:
				return MACRO( T(UP), END );
			case BABL_PGDN:
 				return MACRO( T(PGDN), END );
			case BABL_PGUP:
				return MACRO( T(PGUP), END );
#ifndef BABL_MOVEMENTONLY
			case BABL_UNDO:
					return MACRO( D(LCTRL), T(Z), U(LCTRL), END );
			case BABL_REDO:
 					return MACRO( D(LCTRL), T(Y), U(LCTRL), END );
			case BABL_CUT:
 					return MACRO( D(LCTRL), T(X), U(LCTRL), END );
			case BABL_COPY:
 					return MACRO( D(LCTRL), T(C), U(LCTRL), END );
			case BABL_PASTE:
 					return MACRO( D(LCTRL), T(V), U(LCTRL), END );			
			case BABL_SELECT_ALL:
 					return MACRO( D(LCTRL), T(A), U(LCTRL), END );	
 					
			case BABL_FIND:
 				return MACRO( D(LCTRL),T(F),  U(LCTRL),END );
			case BABL_FIND_NEXT:
 				/* return MACRO( T(F3),END ); KDE */
 				return MACRO( D(LCTRL),T(G),  U(LCTRL),END ); // Gnome*/
			case BABL_FIND_REPLACE:
 				/* return MACRO( D(LCTRL),T(R),  U(LCTRL),END ); KDE */
 				return MACRO( D(LCTRL),T(H),  U(LCTRL),END ); // Gnome*/
			case BABL_RUNAPP:
				return MACRO( D(LALT),T(F2),  U(LALT),END );
			case BABL_SWITCH_APP_NEXT:
				return MACRO( D(LCTL),T(TAB), U(LCTL),END );
			case BABL_SWITCH_APP_LAST:
				return MACRO( D(LSFT),D(LCTL),T(TAB), U(LCTL), U(LSFT),END );
			case BABL_CLOSE_APP:
				return MACRO( D(LALT),T(F4), U(LALT),END );
	 		case BABL_HELP:
				return MACRO_NONE;
#endif
				break;
	 
	 return MACRO_NONE;
	}
	
#endif 
	  
#ifdef MAC_MODE
	 case MAC_MODE:
	 	switch(shortcut) {
	  
			 
			case BABL_DEL_RIGHT_1C:
				 return MACRO( D(DEL), END );	 
			case BABL_DEL_LEFT_WORD:
 				return MACRO( D(LALT), T(BSPACE), U(LALT), END );
			case BABL_DEL_RIGHT_WORD:
 				return MACRO( D(LALT), T(DEL), U(LALT), END );
			case BABL_GO_LEFT_1C:
 				return MACRO( T(LEFT), END );
			case BABL_GO_RIGHT_1C:
 				return MACRO( T(RIGHT), END );
			case BABL_GO_LEFT_WORD:
 				return MACRO( D(LALT), T(LEFT), U(LALT), END );
			case BABL_GO_RIGHT_WORD:
 				return MACRO( D(LALT), T(RIGHT), U(LALT), END );
			case BABL_GO_START_LINE:
 				return MACRO(  D(LGUI), T(LEFT), U(LGUI),  END );
			case BABL_GO_START_DOC:
 				return MACRO( D(LGUI),T(UP),  U(LGUI),END );
			case BABL_GO_END_LINE:
 				return MACRO(  D(LGUI), T(RIGHT), U(LGUI), END );
			case BABL_GO_END_DOC:
 				return MACRO( D(LGUI),T(DOWN),  U(LGUI),END );
			case BABL_GO_NEXT_LINE:
 				return MACRO( T(DOWN), END );
			case BABL_GO_PREV_LINE:
				return MACRO( T(UP), END );
			case BABL_PGDN:
 				return MACRO( D(LALT), T(DOWN), U(LALT), END );
			case BABL_PGUP:
				return MACRO(  D(LALT), T(UP), U(LALT), END );
#ifndef BABL_MOVEMENTONLY
			case BABL_UNDO:
					return MACRO( D(LGUI), T(Z), U(LGUI), END );
			case BABL_REDO:
 					return MACRO( D(LSFT),D(LGUI), T(Z), U(LSFT),U(LGUI), END );
			case BABL_CUT:
 					return MACRO( D(LGUI), T(X), U(LGUI), END );
			case BABL_COPY:
 					return MACRO( D(LGUI), T(C), U(LGUI), END );
			case BABL_PASTE:
 					return MACRO( D(LGUI), T(V), U(LGUI), END );			
			case BABL_SELECT_ALL:
 					return MACRO( D(LGUI), T(A), U(LGUI), END );
 			case BABL_FIND:
 				return MACRO( D(LGUI),T(F),  U(LGUI),END );
			case BABL_FIND_NEXT:
 				return MACRO(  D(LGUI),T(G),  U(LGUI),END );
			case BABL_FIND_REPLACE:
 				return MACRO( D(LGUI),T(F),  U(LGUI),END );
			case BABL_RUNAPP:
				return MACRO( D(LGUI),T(R), U(LGUI),END );
			case BABL_SWITCH_APP_NEXT:
				return MACRO( D(LGUI),T(TAB), U(LGUI),END );
			case BABL_SWITCH_APP_LAST:
				return MACRO( D(LSFT),D(LGUI),T(TAB), U(LGUI), U(LSFT),END );
	 		case BABL_CLOSE_APP:
				return MACRO( D(LGUI),T(Q),  U(LGUI),END );
	 		case BABL_HELP:
				return MACRO( D(LSFT),D(LGUI),T(SLASH), U(LGUI), U(LSFT),END );
#endif
				break; 
	 
	 return MACRO_NONE;
	}
	
#endif 	
	
#ifdef EMACS_MODE
	 case EMACS_MODE:
	 	switch(shortcut) {
//probably should allow meta to not be ALT
			
			case BABL_DEL_RIGHT_1C:
				 return MACRO( D(LCTL), T(D), U(LCTL),END );	 
			case BABL_DEL_LEFT_WORD:
 				return MACRO( D(LCTL), T(BSPACE), U(LCTL), END );
			case BABL_DEL_RIGHT_WORD:
 				return MACRO( D(LALT), T(D), U(LALT), END );
			case BABL_GO_LEFT_1C:
 				return MACRO( T(LEFT), END );
			case BABL_GO_RIGHT_1C:
 				return MACRO( T(RIGHT), END );
			case BABL_GO_LEFT_WORD:
 				return MACRO( D(LALT), T(B), U(LALT), END );
			case BABL_GO_RIGHT_WORD:
 				return MACRO( D(LALT), T(F), U(LALT), END );
			case BABL_GO_START_LINE:
 				return MACRO(  D(LCTRL), T(A), U(LCTRL),  END );
			case BABL_GO_START_DOC:
 				return MACRO( D(LALT), D(LSFT), T(COMM),U(LSFT), U(LALT) ,END );
			case BABL_GO_END_LINE:
 				return MACRO(  D(LCTRL), T(E), U(LCTRL), END );
			case BABL_GO_END_DOC:
 				return MACRO( D(LALT), D(LSFT), T(DOT),U(LSFT), U(LALT) ,END );
			case BABL_GO_NEXT_LINE:
 				return MACRO(  D(LCTRL), T(N), U(LCTRL), END );
			case BABL_GO_PREV_LINE:
				return MACRO(  D(LCTRL), T(P), U(LCTRL), END );
			case BABL_PGDN:
 				return MACRO(D(LCTRL), T(V), U(LCTRL), END );
			case BABL_PGUP:
				return MACRO(  D(LALT), T(V), U(LALT), END );
#ifndef BABL_MOVEMENTONLY
			case BABL_UNDO:
					return MACRO( D(LCTL), T(X), U(LCTL),T(C), END );
			case BABL_REDO:
 					return MACRO( D(LCTL), T(X), U(LCTL),T(C), END ); // arguably
			case BABL_CUT:
 					return MACRO( D(LCTL), T(W), U(LCTL), END );
			case BABL_COPY:
 					return MACRO( D(LALT), T(W), U(LALT), END ); //really?
			case BABL_PASTE:
 					return MACRO(  D(LCTL), T(Y), U(LCTL), END );			
			case BABL_SELECT_ALL:
 					return MACRO(D(LCTL), T(X), U(LCTL),T(H), END );	 
 			case BABL_FIND:
 				return MACRO( D(LCTRL), T(S), U(LCTRL),END );
			case BABL_FIND_NEXT:
 				return MACRO( D(LCTRL), T(S), U(LCTRL),END );
			case BABL_FIND_REPLACE:
 				return MACRO(  D(LALT),D(LSFT), T(5),U(LSFT),  U(LALT), END );
			case BABL_RUNAPP:
				return MACRO( D(LALT), T(X), U(LALT),T(S),T(H),T(E),T(L),T(L),END );// arguably
			case BABL_SWITCH_APP_NEXT:
				return MACRO( D(LCTL), T(X), U(LCTL),T(RIGHT), END ); // arguably
			case BABL_SWITCH_APP_LAST:
				return MACRO( D(LCTL), T(X), U(LCTL),T(LEFT), END ); // arguably
	 		case BABL_CLOSE_APP:
				return MACRO(D(LCTL), T(X), U(LCTL),T(C),END );
	 		case BABL_HELP:
				return MACRO( D(LCTL),T(H), U(LCTL),T(A),END); // start search in help
#endif
				break;
	 
	 return MACRO_NONE;
	}
	
#endif 	
#ifdef VI_MODE
	 case VI_MODE:
	 	switch(shortcut) {
//assume esc is already called
			
			case BABL_DEL_RIGHT_1C:
				 return MACRO(  T(X),END );	 
			case BABL_DEL_LEFT_WORD:
 				return MACRO(  T(D),T(G),T(E),END );
			case BABL_DEL_RIGHT_WORD:
 				return MACRO(  T(D),T(W),END );
			case BABL_GO_LEFT_1C:
 				return MACRO( T(H), END );
			case BABL_GO_RIGHT_1C:
 				return MACRO( T(L), END );
			case BABL_GO_LEFT_WORD:
 				return MACRO( T(B),END );
			case BABL_GO_RIGHT_WORD:
 				return MACRO( T(W), END );
			case BABL_GO_START_LINE:
 				return MACRO( D(LSFT), T(6),U(LSFT), END ); //^
			case BABL_GO_START_DOC:
 				return MACRO( T(G),T(G) ,END );
			case BABL_GO_END_LINE:
 				return MACRO(   D(LSFT), T(4),U(LSFT) , END ); //$
			case BABL_GO_END_DOC:
 				return MACRO( D(LSFT), T(G),U(LSFT),END );
			case BABL_GO_NEXT_LINE:
 				return MACRO(  T(J), END );
			case BABL_GO_PREV_LINE:
				return MACRO(  T(K), END );
			case BABL_PGDN:
 				return MACRO(D(LCTRL), T(F), U(LCTRL), END );
			case BABL_PGUP:
				return MACRO( D(LCTRL), T(B), U(LCTRL), END );
#ifndef BABL_MOVEMENTONLY
			case BABL_UNDO:
					return MACRO( T(U), END );
			case BABL_REDO:
 					return MACRO(  D(LCTL), T(R), U(LCTL), END );  
			case BABL_CUT:
 					return MACRO(  T(X), END );
			case BABL_COPY:
 					return MACRO( T(Y),END );
			case BABL_PASTE:
 					return MACRO(  T(P), END );			
			case BABL_SELECT_ALL:
 					return MACRO( D(LSFT), T(SCLN),U(LSFT),D(LSFT), T(5),U(LSFT),T(Y), END ); // wrong but helpful? 
 			case BABL_FIND:
 				return MACRO(   T(SLASH),END );
			case BABL_FIND_NEXT:
 				return MACRO( T(N),END );
			case BABL_FIND_REPLACE:
 				return MACRO(  D(LALT),D(LSFT), T(5),U(LSFT),  U(LALT), END );
			case BABL_RUNAPP:
				 return MACRO_NONE;
			case BABL_SWITCH_APP_NEXT:
				 return MACRO_NONE;
			case BABL_SWITCH_APP_LAST:
				 return MACRO_NONE;
	 		case BABL_CLOSE_APP:
				return MACRO(D(LSFT), T(SCLN),U(LSFT), T(Q), D(RSFT), T(1),U(RSFT), END );
	 		case BABL_HELP:
				return  MACRO(D(LSFT), T(SCLN),U(LSFT),T(H),END); // start search in help
				break;
#endif	 
	 return MACRO_NONE;
	}
	
#endif
#ifdef READMUX_MODE
// Readline command line editing + tmux windowing
// I havent decided how much to do readline and how much tmux
	 case READMUX_MODE:
	 	switch(shortcut) {
			
			case BABL_DEL_RIGHT_1C:
				 return MACRO( D(LCTL), T(D), U(LCTL),END );	 
			case BABL_DEL_LEFT_WORD:
 				return MACRO( D(LCTL), T(W), U(LCTL), END );
			case BABL_DEL_RIGHT_WORD:
 				return MACRO( D(LALT), T(D), U(LALT), END );
			case BABL_GO_LEFT_1C:
 				return MACRO( T(LEFT), END );
			case BABL_GO_RIGHT_1C:
 				return MACRO( T(RIGHT), END );
			case BABL_GO_LEFT_WORD:
 				return MACRO( D(LALT), T(B), U(LALT), END );
			case BABL_GO_RIGHT_WORD:
 				return MACRO( D(LALT), T(F), U(LALT), END );
			case BABL_GO_START_LINE:
 				return MACRO(  D(LCTRL), T(A), U(LCTRL),  END );
			case BABL_GO_START_DOC:
 				return MACRO_NONE; // tmux?
			case BABL_GO_END_LINE:
 				return MACRO(  D(LCTRL), T(E), U(LCTRL), END );
			case BABL_GO_END_DOC:
 				return MACRO_NONE; // tmux?
			case BABL_GO_NEXT_LINE:
 				return MACRO(  D(LCTRL), T(N), U(LCTRL), END );
			case BABL_GO_PREV_LINE:
				return MACRO(  D(LCTRL), T(P), U(LCTRL), END );
			case BABL_PGDN:
 				return MACRO( T(PGDN), END );
			case BABL_PGUP:
				return MACRO( T(PGUP), END );
#ifndef BABL_MOVEMENTONLY
			case BABL_UNDO:
					return MACRO( D(LALT), T(R), U(LALT) , END );
			case BABL_REDO:
 					return MACRO( D(LCTL), T(X), U(LCTL),T(C), END ); // arguably
			case BABL_CUT:
 					return MACRO( D(LCTL), T(K), U(LCTL), END ); // wrong half the time
			case BABL_COPY:
 					return MACRO_NONE;
			case BABL_PASTE:
 					return MACRO(  D(LCTL), T(Y), U(LCTL), END );			
			case BABL_SELECT_ALL:
 					return MACRO(D(LCTL), T(A), T(K), T(Y), U(LCTL) , END );	 
 			case BABL_FIND:
 				return MACRO(  D(LCTRL), T(R), U(LCTRL), END ); // search history
			case BABL_FIND_NEXT:
 				eturn MACRO(  D(LCTRL), T(S), U(LCTRL), END );
			case BABL_FIND_REPLACE:
 				return MACRO_NONE; // tmux?
			case BABL_RUNAPP:
				return MACRO(  D(LCTRL), T(B), U(LCTRL),  T(C),END );  //tmux
			case BABL_SWITCH_APP_NEXT:
				return MACRO(  D(LCTRL), T(B), U(LCTRL),  T(N),END );  //tmux
			case BABL_SWITCH_APP_LAST:
				return MACRO(  D(LCTRL), T(B), U(LCTRL),  T(P),END );  //tmux
	 		case BABL_CLOSE_APP:
				return MACRO( D(LCTRL), T(B), U(LCTRL),  T(D),END); // usually what I want
	 			break;
	 		case BABL_HELP:
				return MACRO_NONE;
#endif
				break;
				
	 return MACRO_NONE;
	}
	
#endif 			
	return MACRO_NONE;
    }


}

