/*  A library to output the right key shortcut in any common app.
Given a global variable babble_mode to show the environment and a
key that calls the paste macro, do the right type of paste.
Setting the context is done by another macro, or TBD interaction with the host.

https://support.google.com/docs/answer/181110?co=GENIE.Platform%3DDesktop&hl=en

*/

#include QMK_KEYBOARD_H

#ifdef USE_BABBLEPASTE
#    include "babblePaste.h"

#    ifdef BABL_CHROMEOS

bool babblepaste_chromeos(uint16_t keycode) {
#        ifdef BABL_MOVE
    BABLM(BABL_GO_LEFT_1C, SS_TAP(X_LEFT));
    BABLM(BABL_GO_RIGHT_1C, SS_TAP(X_RIGHT));
    BABLM(BABL_GO_LEFT_WORD, IMCTL(X_LEFT));
    BABLM(BABL_GO_RIGHT_WORD, IMCTL(X_RIGHT));
    BABLM(BABL_GO_START_LINE, SS_TAP(X_HOME));
    BABLM(BABL_GO_END_LINE, SS_TAP(X_END));
    BABLM(BABL_GO_START_DOC, IMCTL(X_HOME));
    BABLM(BABL_GO_END_DOC, IMCTL(X_END));
    BABLM(BABL_GO_NEXT_LINE, SS_TAP(X_DOWN));
    BABLM(BABL_GO_PREV_LINE, SS_TAP(X_UP));
    BABLM(BABL_GO_PARA_START, IMCTL(X_UP));  // untested
    BABLM(BABL_GO_PARA_END, IMCTL(X_DOWN));  // untested
    BABLM(BABL_PGDN, IMGUI(X_DOWN));
    BABLM(BABL_PGUP, IMGUI(X_UP));
    BABLM(BABL_DEL_RIGHT_1C, IMALT(X_BSPACE));
    BABLM(BABL_DEL_LEFT_WORD, IMCTL(X_BSPACE));
    BABLM(BABL_DEL_RIGHT_WORD, OMSFT(IMCTL(X_RIGHT)) SS_TAP(X_BSPACE));
    BABLM(BABL_DEL_TO_LINE_END, OMSFT(IMGUI(X_LEFT)) SS_TAP(X_BSPACE));
    BABLM(BABL_DEL_TO_LINE_START, OMSFT(IMGUI(X_RIGHT)) SS_TAP(X_BSPACE));
    BABLM(BABL_MODE, ("ChromeOS "));
#        endif
#        ifdef BABL_OSKEYS
    BABLM(BABL_UNDO, SS_LCTRL("z"));
    BABLM(BABL_REDO, OMSFT(IMCTL(X_Z)));
    BABLM(BABL_CUT, SS_LCTRL("x"));
    BABLM(BABL_COPY, SS_LCTRL("c"));
    BABLM(BABL_PASTE, SS_LCTRL("v"));
    BABLM(BABL_SELECT_ALL, SS_LCTRL("a"));
    BABLM(BABL_FIND, SS_LCTRL("f"));
    BABLM(BABL_FIND_NEXT, SS_LCTRL("g"));
    BABLM(BABL_FIND_PREV, OMSFT(IMCTL(X_G)));
    BABLM(BABL_WINDOW_NEW, IMCTL(X_N));
    //	BABLM( BABL_FIND_REPLACE,		() ); // not part of Chrome
    // BABLM( BABL_RUNAPP, 	SS_TAP(X_LGUI) ); // not sure of this
    BABLM(BABL_SWITCH_APP_NEXT, IMALT(X_TAB));
    BABLM(BABL_SWITCH_APP_LAST, OMSFT(IMALT(X_TAB)));
    BABLM(BABL_CLOSE_APP, OMSFT(IMCTL(X_W)));
    // BABLM( BABL_HELP,		OMCTL(IMALT(X_SLASH))	); // general help
    BABLM(BABL_HELP, IMCTL(X_SLASH));  // this is keyboard accelerator lookup
    BABLM(BABL_LOCK, SS_LGUI("l"));    // should be caps?
    BABLM(BABL_SCREENCAPTURE, OMSFT(IMCTL(X_F5)));
    BABLM(BABL_SWITCH_KEYBOARD_LAYOUT, IMCTL(X_SPACE));
#        endif
#        ifdef BABL_BROWSER
    BABLM(BABL_BROWSER_NEW_TAB, SS_LCTRL("t"));
    BABLM(BABL_BROWSER_CLOSE_TAB, SS_LCTRL("w"));
    BABLM(BABL_BROWSER_REOPEN_LAST_TAB, OMSFT(IMCTL(X_T)));
    BABLM(BABL_BROWSER_NEXT_TAB, IMCTL(X_TAB));
    BABLM(BABL_BROWSER_PREV_TAB, OMSFT(IMCTL(X_TAB)));
    BABLM(BABL_BROWSER_URL_BAR, SS_LCTRL("l"));
    BABLM(BABL_BROWSER_FORWARD, IMALT(X_RIGHT));
    BABLM(BABL_BROWSER_BACK, IMALT(X_LEFT));
    ;
    BABLM(BABL_BROWSER_FIND, SS_LCTRL("f"));
    BABLM(BABL_BROWSER_BOOKMARK, SS_LCTRL("d"));
    BABLM(BABL_BROWSER_DEV_TOOLS, OMSFT(IMCTL(X_I)));
    BABLM(BABL_BROWSER_RELOAD, OMSFT(IMCTL(X_R)));       // hard reload w/o cache
    BABLM(BABL_BROWSER_FULLSCREEN, SS_TAP(X_F4));        // untested
    BABLM(BABL_BROWSER_ZOOM_IN, OMSFT(IMCTL(X_EQUAL)));  // ctr+ +
    BABLM(BABL_BROWSER_ZOOM_OUT, IMCTL(X_MINUS));
    BABLM(BABL_BROWSER_VIEWSRC, SS_LCTRL("u"));  // Chrome or firefox
#        endif

#        ifdef BABL_APP
    BABLM(BABL_APP_SAVE, SS_LCTL("s"));
    //#ifdef BABL_APP_GOOGLE  -- we're going to make an assumption.
    BABLM(BABL_APP_CENTER_ALIGN, OMSFT(IMCTL(X_E)));
    BABLM(BABL_APP_SCROLL_ACTIVE_CELL, IMCTL(X_BSPACE));
    BABLM(BABL_NEWLINE_IN_CELL, IMALT(X_ENTER));
    BABLM(BABL_INSERT_COMMENT, OMALT(IMCTL(X_M)));
    BABLM(BABL_APP_CLEAR_FORMATTING, IMCTL(X_BSLASH));
    BABLM(BABL_DELETE_ROW, IMALT(X_E) "d");
    BABLM(BABL_INSERT_COL_LEFT, IMALT(X_I) "c");  // o for to the right.
    BABLM(BABL_INSERT_ROW, IMALT(X_I) "w");       // r for above.
    BABLM(BABL_SELECT_COL, IMCTL(X_SPACE));
    BABLM(BABL_SELECT_ROW, IMSFT(X_SPACE));
    BABLM(BABL_DELETE_ROW, OMALT(IMCTL(X_KP_MINUS)));  // once selected
//#endif // BABL_APP_CELLS
#        endif  // BABL_APP

    // Todo, ring bell, flash light, show user this isn't supported
    return false;
}
#    endif
#endif /* chromeos*/
