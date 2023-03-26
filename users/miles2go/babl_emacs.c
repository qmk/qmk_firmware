/*  A library to output the right key shortcut in any common app.
Given a global variable babble_mode to show the environment and a
key that calls the paste macro, do the right type of paste.
Setting the context is done by another macro, or TBD interaction with the host.

Emacs mode is probably most useful for people who don't usually use emacs

https://www.ast.cam.ac.uk/~vasily/idl/emacs_commands_list.html
*/

#include QMK_KEYBOARD_H

#ifdef USE_BABBLEPASTE
#    include "babblePaste.h"

#    ifdef BABL_EMACS

// probably should allow meta to not be ALT
#        define DMETA IMALT

bool babblePaste_emacs(uint16_t keycode) {
#        ifdef BABL_MOVE
    BABLM(BABL_GO_LEFT_1C, SS_TAP(X_LEFT));
    BABLM(BABL_GO_RIGHT_1C, SS_TAP(X_RIGHT));
    BABLM(BABL_GO_LEFT_WORD, IMALT(X_B));
    BABLM(BABL_GO_RIGHT_WORD, IMALT(X_F));
    BABLM(BABL_GO_START_LINE, SS_LCTL("a"));
    BABLM(BABL_GO_END_LINE, SS_LCTL("e"));
    BABLM(BABL_GO_START_DOC, OMALT(IMSFT(X_COMMA)));
    BABLM(BABL_GO_END_DOC, OMALT(IMSFT(X_DOT)));
    BABLM(BABL_GO_NEXT_LINE, SS_LCTL("n"));
    BABLM(BABL_GO_PREV_LINE, SS_LCTL("p"));
    BABLM(BABL_GO_PARA_START, OMALT(IMSFT(X_LEFT_BRACKET)));
    BABLM(BABL_GO_PARA_END, OMALT(IMSFT(X_RIGHT_BRACKET)));
    BABLM(BABL_PGDN, SS_LCTL("v"));
    BABLM(BABL_PGUP, IMALT(X_V));
    BABLM(BABL_DEL_RIGHT_1C, SS_LCTL("d"));
    BABLM(BABL_DEL_LEFT_WORD, IMCTL(X_BACKSPACE));
    BABLM(BABL_DEL_RIGHT_WORD, IMALT(X_D));
    BABLM(BABL_DEL_TO_LINE_END, SS_LCTL("k"));
    BABLM(BABL_DEL_TO_LINE_START, SS_TAP(X_ESCAPE) "0" SS_LCTL("k"));
    BABLM(BABL_MODE, "Emacs ");
#        endif
#        ifdef BABL_OSKEYS
    BABLM(BABL_UNDO, SS_LCTL("x") "c");
    BABLM(BABL_REDO, SS_LCTL("x") "c");  // arguably
    BABLM(BABL_CUT, SS_LCTL("w"));
    BABLM(BABL_COPY, SS_LALT("w"));  // really?
    BABLM(BABL_PASTE, SS_LCTL("y"));
    BABLM(BABL_SELECT_ALL, SS_LCTL("x") "h");
    BABLM(BABL_FIND, SS_LCTL("s"));
    BABLM(BABL_FIND_NEXT, SS_LCTL("s"));
    BABLM(BABL_FIND_PREV, SS_LCTL("r"));
    BABLM(BABL_FIND_REPLACE, OMALT(IMSFT(X_5)));
    // BABLM( BABL_RUNAPP , 			//(SS_LALT("x") "shell")	 );// arguably
    BABLM(BABL_RUNAPP, IMALT(X_X) "split-window" SS_TAP(X_ENTER));  // arguably
    BABLM(BABL_WINDOW_NEXT, SS_LCTL("x") "o");
    BABLM(BABL_WINDOW_PREV, SS_LCTL("x") "o");  // arguably
    //	BABLM( BABL_WINDOW_NEW,		IMCTL(X_X)"n" ); //
    BABLM(BABL_CLOSE_APP, SS_LCTL("x") "c");
    BABLM(BABL_HELP, SS_LCTL("h") "a");  // start search in help
                                          // BABLM( BABL_LOCK,		()	); // lock buffer? Too many options.
    // BABLM( BABL_SCREENCAPTURE,		()	); // requires plugin?

#        endif
#        ifdef BABL_BROWSER
/* you get to figure w3 out */
#        endif

#        ifdef BABL_APP
    BABLM(BABL_APP_SAVE, SS_LCTL("x") SS_LCTL("s"));
    BABLM(BABL_APP_SET_MARK, IMCTL(X_SPACE));
    /// BABLM( BABL_APP_MULTI_SELECT, 	SS_LCTL("x") "rt" ); // arguably
    BABLM(BABL_SPLIT_FRAME_VERT, SS_LCTL("x") "3");
    BABLM(BABL_UNSPLIT_FRAME_VERT, SS_LCTL("u") SS_LCTL("x") "0");
    BABLM(BABL_SPLIT_FRAME_HORIZONTAL, SS_LCTL("x") "2");
    BABLM(BABL_UNSPLIT_FRAME_HORIZONTAL, SS_LCTL("u") SS_LCTL("x") "0");
    BABLM(BABL_NEXT_FRAME, SS_LCTL("x") "o");
    BABLM(BABL_PREV_FRAME, SS_LCTL("u") "-1" SS_LCTL("x") "o");
#        endif

    // Todo, ring bell, flash light, show user this isn't supported
    return false;
}
#    endif /* emacs mode*/
#endif
