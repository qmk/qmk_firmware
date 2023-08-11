/*  A library to output the right key shortcut in any common app.
Given a global variable babble_mode to show the environment and a
key that calls the paste macro, do the right type of paste.
Setting the context is done by another macro, or TBD interaction with the host.

Huge thanks to https://en.wikipedia.org/wiki/Table_of_keyboard_shortcuts
https://support.microsoft.com/en-gb/help/12445/windows-keyboard-shortcuts

Remember to check  https://github.com/qmk/qmk_firmware/blob/master/quantum/send_string_keycodes.h

*/

#include QMK_KEYBOARD_H

#ifdef USE_BABBLEPASTE
#    include "babblePaste.h"

#    ifdef BABL_WINDOWS

bool babblePaste_win(uint16_t keycode) {
#        ifdef BABL_MOVE
    BABLM(BABL_GO_LEFT_1C, SS_TAP(X_LEFT));
    BABLM(BABL_GO_RIGHT_1C, SS_TAP(X_RIGHT));
    BABLM(BABL_GO_LEFT_WORD, IMCTL(X_LEFT));
    BABLM(BABL_GO_RIGHT_WORD, IMCTL(X_RIGHT));
    BABLM(BABL_GO_START_LINE, IMGUI(X_LEFT));
    BABLM(BABL_GO_END_LINE, IMGUI(X_RIGHT));
    BABLM(BABL_GO_START_DOC, OMGUI(IMCTL(X_LEFT)));
    BABLM(BABL_GO_END_DOC, OMGUI(IMCTL(X_RIGHT)));
    BABLM(BABL_GO_NEXT_LINE, SS_TAP(X_DOWN));
    BABLM(BABL_GO_PREV_LINE, SS_TAP(X_UP));
    BABLM(BABL_GO_PARA_START, IMCTL(X_UP));
    BABLM(BABL_GO_PARA_END, IMCTL(X_DOWN));
    BABLM(BABL_PGDN, SS_TAP(X_PGDN));
    BABLM(BABL_PGUP, SS_TAP(X_PGUP));
    BABLM(BABL_DEL_RIGHT_1C, SS_TAP(X_DELETE));
    BABLM(BABL_DEL_LEFT_WORD, IMCTL(X_BACKSPACE));
    BABLM(BABL_DEL_RIGHT_WORD, IMCTL(X_DELETE));
    BABLM(BABL_DEL_TO_LINE_END, IMSFT(X_HOME) SS_TAP(X_DELETE));
    BABLM(BABL_DEL_TO_LINE_START, IMSFT(X_END) SS_TAP(X_DELETE));
    BABLM(BABL_MODE, "Windows ");
#        endif

#        ifdef BABL_OSKEYS
    BABLM(BABL_UNDO, SS_LCTL("z"));
    BABLM(BABL_REDO, SS_LCTL("y"));
    BABLM(BABL_CUT, SS_LCTL("x"));
    BABLM(BABL_COPY, SS_LCTL("c"));
    BABLM(BABL_PASTE, SS_LCTL("v"));
    BABLM(BABL_SELECT_ALL, SS_LCTL("a"));
    BABLM(BABL_FIND, SS_LCTL("f"));
    BABLM(BABL_FIND_NEXT, SS_TAP(X_F3));
    // BABLM( BABL_FIND_PREV, 	SS_TAP(X_F3) ); // doesn't have a standard one?
    BABLM(BABL_FIND_REPLACE, SS_LCTL("h"));
    BABLM(BABL_RUNAPP, SS_LGUI("r"));
    BABLM(BABL_SWITCH_APP_NEXT, IMALT(X_TAB));
    BABLM(BABL_SWITCH_APP_LAST, OMSFT(IMALT(X_TAB)));
    BABLM(BABL_WINDOW_NEXT, IMCTL(X_TAB));
    BABLM(BABL_WINDOW_PREV, OMSFT(IMCTL(X_TAB)));
    BABLM(BABL_WINDOW_NEW, IMCTL(X_N));
    BABLM(BABL_CLOSE_APP, IMALT(X_F4));
    BABLM(BABL_HELP, SS_TAP(X_F1));
    BABLM(BABL_LOCK, SS_LGUI("l"));
    BABLM(BABL_SCREENCAPTURE, OMSFT(SS_LGUI("s")));
    BABLM(BABL_SWITCH_KEYBOARD_LAYOUT, IMGUI(X_SPACE));

#        endif

#        ifdef BABL_BROWSER
    BABLM(BABL_BROWSER_NEW_TAB, SS_LCTL("t"));
    BABLM(BABL_BROWSER_CLOSE_TAB, SS_LCTL("w"));
    BABLM(BABL_BROWSER_REOPEN_LAST_TAB, OMSFT(IMCTL(X_T)));
    BABLM(BABL_BROWSER_NEXT_TAB, IMCTL(X_TAB));
    BABLM(BABL_BROWSER_PREV_TAB, OMSFT(IMCTL(X_TAB)));
    BABLM(BABL_BROWSER_URL_BAR, SS_LCTL("l"));
    BABLM(BABL_BROWSER_FORWARD, IMALT(X_RIGHT));
    BABLM(BABL_BROWSER_BACK, OMSFT(IMALT(X_LEFT)));
    ;
    BABLM(BABL_BROWSER_FIND, SS_LCTL("f"));
    BABLM(BABL_BROWSER_BOOKMARK, SS_LCTL("d"));
#            ifdef BABL_BROWSER_MS
    BABLM(BABL_BROWSER_DEV_TOOLS, IMCTL(X_F12));  // EDGE
#            else
    BABLM(BABL_BROWSER_DEV_TOOLS, SS_LCTL("t"));  // Chrome
    BABLM(BABL_BROWSER_VIEWSRC, SS_LCTL("u"));    // Chrome or firefox
#            endif
    // chrome
    BABLM(BABL_BROWSER_RELOAD, IMCTL(X_F5));             // hard reload w/o cache
    BABLM(BABL_BROWSER_FULLSCREEN, SS_TAP(X_F11));       // command shift F
    BABLM(BABL_BROWSER_ZOOM_IN, OMSFT(IMCTL(X_EQUAL)));  // ctr+ +
    BABLM(BABL_BROWSER_ZOOM_OUT, IMCTL(X_MINUS));

#        endif

#        ifdef BABL_APP
    BABLM(BABL_APP_SAVE, SS_LCTL("s"));
#            ifdef BABL_APP_EDITOR
#                ifdef BABL_APP_SUBLIME
    // http://sweetme.at/2013/08/08/sublime-text-keyboard-shortcuts/
    BABLM(BABL_APP_MULTI_SELECT, IMALT(X_F3));        // add all occurences of current word to select.
    BABLM(BABL_APP_PASTE_VALUES, OMSFT(IMCTL(X_V)));  // paste with proper indenting.
#                endif                                // sublime
#            endif                                    // editor

#            ifdef BABL_APP_CELLS
#                ifdef BABL_APP_MSOFFICE
#                    ifndef BABL_APP_SUBLIME
    BABLM(BABL_APP_PASTE_VALUES, OMCTL(IMALT(X_V)) "v");
#                    endif
    BABLM(BABL_APP_CENTER_ALIGN, IMALT(X_H) "ac");
    // BABLM( BABL_APP_CLEAR_FORMATTING, 	OMCTL(IMGUI(X_G)) ); // this isn't native. https://support.office.com/en-us/article/Clear-all-text-formatting-C094C4DA-7F09-4CEA-9A8D-C166949C9C80#OfficeVersion=macOS
    BABLM(BABL_APP_SCROLL_ACTIVE_CELL, IMCTL(X_BACKSPACE));
    BABLM(BABL_NEWLINE_IN_CELL, IMALT(X_ENTER));
    BABLM(BABL_INSERT_COMMENT, IMSFT(X_F2));
    BABLM(BABL_INSERT_COL_LEFT, OMCTL(IMSFT(X_KP_PLUS)));
    BABLM(BABL_INSERT_ROW, OMCTL(IMSFT(X_KP_PLUS)));
    BABLM(BABL_DELETE_ROW, IMCTL(X_KP_MINUS));
    BABLM(BABL_SELECT_COL, IMCTL(X_SPACE));
    BABLM(BABL_SELECT_ROW, IMSFT(X_SPACE));
#                endif

#                ifdef BABL_APP_GOOGLE
    BABLM(BABL_APP_CENTER_ALIGN, OMSFT(IMCTL(X_E)));
    BABLM(BABL_APP_SCROLL_ACTIVE_CELL, IMCTL(X_BACKSPACE));
    BABLM(BABL_NEWLINE_IN_CELL, IMALT(X_ENTER));
    BABLM(BABL_INSERT_COMMENT, IMSFT(X_F2));
    BABLM(BABL_APP_CLEAR_FORMATTING, IMCTL(X_BACKSLASH));
    BABLM(BABL_DELETE_ROW, IMALT(X_E) "d");
    BABLM(BABL_INSERT_COL_LEFT, OMALT(IMCTL(X_I)) "c");  // o for to the right.
    BABLM(BABL_INSERT_ROW, IMALT(IMCTL(X_I)) "w");       // r for above.
    BABLM(BABL_SELECT_COL, IMCTL(X_SPACE));
    BABLM(BABL_SELECT_ROW, IMSFT(X_SPACE));
    BABLM(BABL_DELETE_ROW, OMALT(IMCTL(X_KP_MINUS)));  // once selected
#                endif

#            endif  // BABL_APP_CELLS

    // BABLM( BABL_SPLIT_FRAME_VERT,		()  );// no windows way?
    // BABLM( BABL_UNSPLIT_FRAME_VERT,		()  );
    BABLM(BABL_SPLIT_FRAME_HORIZONTAL, OMALT(IMCTL(X_S)));    // word only
    BABLM(BABL_UNSPLIT_FRAME_HORIZONTAL, OMSFT(IMALT(X_C)));  // word
    // BABLM( BABL_NEXT_FRAME, () );//no windows way?
    // BABLM( BABL_PREV_FRAME, () );// no windows way?
#        endif

    // Todo, ring bell, flash light, show user this isn't supported
    return false;
}

#    endif /* BABL_WINDOWS*/
#endif     /* babblepaste */