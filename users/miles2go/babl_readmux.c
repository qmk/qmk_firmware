// Readline command line editing + tmux windowing
// I haven't decided how much to do readline and how much tmux
// see https://tiswww.case.edu/php/chet/readline/rluserman.html for other possible
// keybindings.

#include QMK_KEYBOARD_H

#ifdef USE_BABBLEPASTE
#    include "babblePaste.h"

#    ifdef BABL_READMUX

// Redefine if you use something other than CTRL-B to activate tmux.
#        define TMUX SS_LCTL("b")

bool babblePaste_readmux(uint16_t keycode) {
#        ifdef BABL_MOVE
    BABLM(BABL_GO_LEFT_1C, SS_TAP(X_LEFT));
    BABLM(BABL_GO_RIGHT_1C, SS_TAP(X_RIGHT));
    BABLM(BABL_GO_LEFT_WORD, SS_LALT("b"));
    BABLM(BABL_GO_RIGHT_WORD, SS_LALT("f"));
    BABLM(BABL_GO_START_LINE, SS_LCTL("a"));
    BABLM(BABL_GO_END_LINE, SS_LCTL("e"));
    // BABLM( BABL_GO_START_DOC		,END );// tmux?
    // BABLM( BABL_GO_END_DOC		,END );  // tmux?
    BABLM(BABL_GO_NEXT_LINE, SS_LCTL("n"));
    BABLM(BABL_GO_PREV_LINE, SS_LCTL("p"));
    // BABLM( BABL_GO_PARA_START,	// undefined
    // BABLM( BABL_GO_PARA_END,	 	// undefinedBABLM( BABL_PGDN ,

    BABLM(BABL_PGUP, SS_TAP(X_PGUP));
    BABLM(BABL_PGDN, SS_TAP(X_PGDN));
    BABLM(BABL_DEL_RIGHT_1C, SS_LCTL("d"));
    BABLM(BABL_DEL_LEFT_WORD, SS_LCTL("w"));  // meta-DEL instead?
    BABLM(BABL_DEL_RIGHT_WORD, SS_LALT("d"));
    BABLM(BABL_DEL_TO_LINE_END, SS_LCTL("k"));
    BABLM(BABL_DEL_TO_LINE_START, SS_LCTL("u"));
    BABLM(BABL_MODE, "Readline ");
#        endif
#        ifdef BABL_OSKEYS
    BABLM(BABL_UNDO, SS_LALT("r"));
    BABLM(BABL_REDO, SS_LCTL("x") "c");  // arguably
    BABLM(BABL_CUT, SS_LCTL("k"));       // wrong half the time
    // BABLM( BABL_COPY		,END );
    BABLM(BABL_PASTE, SS_LCTL("y"));
    BABLM(BABL_SELECT_ALL, SS_LCTL("aky"));
    BABLM(BABL_FIND, SS_LCTL("r"));  // search history
    BABLM(BABL_FIND_NEXT, SS_LCTL("r"));
    BABLM(BABL_FIND_PREV, SS_LCTL("s"));
    // BABLM( BABL_FIND_REPLACE		,END ); // not offered in readline
    BABLM(BABL_RUNAPP, TMUX "c");           // tmux
    BABLM(BABL_SWITCH_APP_NEXT, TMUX "n");  // tmux
    BABLM(BABL_SWITCH_APP_LAST, TMUX "p");  // tmux
    BABLM(BABL_CLOSE_APP, TMUX "d");        // usually what I want
    BABLM(BABL_HELP, TMUX IMSFT(X_SLASH));
    BABLM(BABL_LOCK, TMUX "L");  // assuming you set up VLOCK yourself
    BABLM(BABL_SCREENCAPTURE, TMUX ":capture-pane");
#        endif
#        ifdef BABL_BROWSER
/* Add lynx shortcuts, brow.sh?
 */
#            ifdef BABL_MAC
    // this is stock OS X Terminal, alter for windows &etc.
    BABLM(BABL_BROWSER_NEW_TAB, IMGUI(X_T));
    BABLM(BABL_BROWSER_CLOSE_TAB, SS_LGUI("w"));
    BABLM(BABL_BROWSER_NEXT_TAB, IMCTL(X_TAB));
    BABLM(BABL_BROWSER_PREV_TAB, OMSFT(IMCTL(X_TAB)));
#            endif
#        endif
#        ifdef BABL_APP
    // Save makes no sense here
    BABLM(BABL_SPLIT_FRAME_VERT, TMUX IMSFT(X_5));
    // BUG - misleading. This is currently set to convert frame to a window.
    BABLM(BABL_UNSPLIT_FRAME_VERT, TMUX IMSFT(X_1));
    BABLM(BABL_SPLIT_FRAME_HORIZONTAL, TMUX IMSFT(X_QUOTE));
    // This one closes the current pane.
    BABLM(BABL_UNSPLIT_FRAME_HORIZONTAL, SS_LCTL("b") "x");
    BABLM(BABL_NEXT_FRAME, SS_LCTL("b") "o");
    BABLM(BABL_PREV_FRAME, SS_LCTL("w") SS_TAP(X_SEMICOLON));
#        endif

    // Todo, ring bell, flash light, show user this isn't supported
    return false;
}
#    endif /* readmux*/
#endif
