/*  Keyboard mappings for Kitty terminal
https://sw.kovidgoyal.net/kitty/index.html#

 A library to output the right key shortcut in any common app.
Given a global variable babble_mode to show the environment and a
key that calls the paste macro, do the right type of paste.
Setting the context is done by another macro, or TBD interaction with the host.

Huge thanks to https://en.wikipedia.org/wiki/Table_of_keyboard_shortcuts
and
https://github.com/qmk/qmk_firmware/blob/master/keyboards/planck/keymaps/jeebak/keymap.c
*/

#include QMK_KEYBOARD_H

#ifdef USE_BABBLEPASTE
#    include "babblePaste.h"

#    ifdef BABL_LINUX

bool babblePaste_linux(uint16_t keycode) {
#        ifdef BABL_MOVE
    BABLM(BABL_GO_LEFT_1C, SS_TAP(X_LEFT));
    BABLM(BABL_GO_RIGHT_1C, SS_TAP(X_RIGHT));
    BABLM(BABL_GO_LEFT_WORD, IMCTL(X_LEFT));
    BABLM(BABL_GO_RIGHT_WORD, IMCTL(X_RIGHT));
    BABLM(BABL_GO_START_LINE, SS_TAP(X_HOME));
    BABLM(BABL_GO_END_LINE, SS_TAP(X_END));
    BABLM(BABL_GO_START_DOC, OMSFT(IMCTL(X_HOME)); 
    BABLM(BABL_GO_END_DOC, OMSFT(IMCTL(X_END));
 // leaving these for command line editing. 
    BABLM(BABL_GO_NEXT_LINE, SS_TAP(X_DOWN));
    BABLM(BABL_GO_PREV_LINE, SS_TAP(X_UP));
// These are for kitty scrolling by one line  
   // BABLM(BABL_GO_NEXT_LINE, OMSFT(IMCTL(X_DOWN)));
   // BABLM(BABL_GO_PREV_LINE, OMSFT(IMCTL(X_UP)));
// passthrough 
    BABLM(BABL_GO_PARA_START, IMCTL(X_UP));
    BABLM(BABL_GO_PARA_END, IMCTL(X_DOWN)); 
    BABLM(BABL_PGDN, OMSFT(IMCTL(X_PGDOWN)) ); // kitty pagedown
    BABLM(BABL_PGUP, OMSFT(IMCTL((X_PGUP)) ); // kitty pageup
// passthrough to command line/shell. 
    BABLM(BABL_DEL_RIGHT_1C, SS_TAP(X_DELETE));
    BABLM(BABL_DEL_LEFT_WORD, IMCTL(X_BSPACE));
    BABLM(BABL_DEL_RIGHT_WORD, IMCTL(X_DELETE));
    BABLM(BABL_DEL_TO_LINE_END, IMSFT(X_HOME) SS_TAP(X_DELETE));
    BABLM(BABL_DEL_TO_LINE_START, IMSFT(X_END) SS_TAP(X_DELETE));
    BABLM(BABL_MODE, "Linux ");
#        endif
#        ifdef BABL_OSKEYS
    // cut isn't real, undo/redo are passthrough. 
    BABLM(BABL_UNDO, SS_LCTL("z"));
    BABLM(BABL_REDO, SS_LCTL("y"));
    BABLM(BABL_CUT, OMSFT(IMCTL(X_X));
    BABLM(BABL_COPY, OMSFT(IMCTL(X_C));
    BABLM(BABL_PASTE, OMSFT(IMCTL(X_V));
    BABLM(BABL_SELECT_ALL, SS_LCTL("a"));
    // passthrough. 
    BABLM(BABL_FIND, SS_LCTL("f"));
    BABLM(BABL_CLOSE_APP, IMALT(X_F4));
    BABLM(BABL_HELP, SS_TAP(X_F1));
    // 2 passthrough. 
    BABLM(BABL_FIND_NEXT, SS_LCTL("g"));       // Gnome*/
    BABLM(BABL_FIND_PREV, OMSFT(IMCTL(X_G)));  // Gnome*/
    // BABLM(BABL_FIND_NEXT  (SS_LALT(X_F3))    ); //KDE */
    /* BABLM( BABL_FIND_REPLACE , (SS_LCTL("r"))	); // KDE */
    BABLM(BABL_FIND_REPLACE, SS_LCTL("h"));  // Gnome*/
    //BABLM(BABL_RUNAPP, IMALT(X_F2));         // Gnome
    // 2 passthrough. 
    BABLM(BABL_SWITCH_APP_NEXT, IMALT(X_TAB));
    BABLM(BABL_SWITCH_APP_LAST, OMSFT(IMALT(X_TAB)));
    BABLM(BABL_WINDOW_NEXT, OMGUI(X_GRAV)   );  // next OS window of kitty. 
    BABLM(BABL_WINDOW_PREV, OMSFT(IMGUI(X_GRAV))    ); // NA?
    BABLM(BABL_WINDOW_NEW, OMSFT(IMCTL(X_ENTER));
        // KITTY - missing close window. 
    // BABLM( BABL_HELP,		(SS_TAP(X_F1))	); // NA?
    BABLM(BABL_LOCK, OMCTL(IMALT(X_L))); // NA passthrough
    BABLM(BABL_SCREENCAPTURE, IMSFT(X_PSCREEN)); // NA passthrough
#        endif
#        ifdef BABL_BROWSER
    BABLM(BABL_BROWSER_NEW_TAB, OMSFT(IMCTL(X_T)) );
    BABLM(BABL_BROWSER_CLOSE_TAB, OMSFT(IMCTL((X_Q)) );
        // kitty - questionable mental model - reopen current frame as a window
        // requires kitty config  of "map ctrl+ft detach_window"
    BABLM(BABL_BROWSER_REOPEN_LAST_TAB, OMCTL(X_F2) ); // NA
    BABLM(BABL_BROWSER_NEXT_TAB, OMSFT(IMCTL(X_RIGHT)) );
    BABLM(BABL_BROWSER_PREV_TAB, OMSFT(IMCTL(X_LEFT)) );
    BABLM(BABL_BROWSER_URL_BAR, OMSFT(IMCTL(X_ESC)) );   // kitty shell
    // ok, this is a bit of a stretch, overloading meaning of forwards/backwards
    BABLM(BABL_BROWSER_FORWARD, OMSFT(IMCTL(X_DOT)) ); //move current kitty tab forwards
    BABLM(BABL_BROWSER_BACK, OMSFT(IMCTL(X_COMMA)) ); // move current kitty tab back
 //   BABLM(BABL_BROWSER_FIND, SS_LCTL("f"));
    BABLM(BABL_BROWSER_BOOKMARK, OMSFT(IMCTL(SS_LALT(X_T))) ); // bookmark == set tab title. 
    BABLM(BABL_BROWSER_DEV_TOOLS, OMSFT(IMCTL(X_F2)) );  // edit kitty config. 
    BABLM(BABL_BROWSER_RELOAD, OMSFT(IMCTL(X_DEL)) ); // reset terminal
    BABLM(BABL_BROWSER_FULLSCREEN, OMSFT(IMCTL(X_F11)) );  
    BABLM(BABL_BROWSER_ZOOM_IN, OMSFT(IMCTL(X_EQUAL)) );  // ctr+ +
    BABLM(BABL_BROWSER_ZOOM_OUT, IMCTL(X_MINUS));
    //BABLM(BABL_BROWSER_VIEWSRC, OMSFT(IMCTL(X_F2));

#        endif
#        ifdef BABL_APP
    BABLM(BABL_APP_SAVE, SS_LCTL("s")); // passthrough. 
    BABLM( BABL_SPLIT_FRAME_VERT,		OMSFT(IMCTL(X_ENTER)))  ); // add new frame in kitty window
    BABLM( BABL_UNSPLIT_FRAME_VERT,		OMSFT(IMCTL(X_W)))  ); // close window
    // BUG, this breaks the mental model.  move the current frame forward/back in rotation
    BABLM( BABL_SPLIT_FRAME_HORIZONTAL, OMSFT(IMCTL(X_F))	);
    BABLM( BABL_UNSPLIT_FRAME_HORIZONTAL, OMSFT(IMCTL(X_B)) );
    // KITTY - Missing - close framef CTL sft X_W
    // KITTY - missing ctrl shift ` = move frame to top. 
    BABLM( BABL_NEXT_FRAME, OMSFT(IMCTL(X_RBRC))	);
    BABLM( BABL_PREV_FRAME, OMSFT(IMCTL(X_LBRC)))	);
#        endif

    // Todo, ring bell, flash light, show user this isn't supported
    return false;
}

#    endif /* linux mode */
#endif
