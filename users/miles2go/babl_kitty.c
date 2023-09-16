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

// #define TAB_MEANS TAB
/* #define TAB_MEANS_TAB to keep the meaning of  "tab" and "window" used in kitty documentation. .
 * Leaving tab undefined will mean that each babble window command applies to a tab,
 * and each babble tab command applies to a window inside the kitty OS window.
 */
//#define TAB_MEANS_TAB

#ifdef USE_BABBLEPASTE
#    include "babblePaste.h"

#    ifdef BABL_KITTY

bool babblePaste_kitty(uint16_t keycode) {
#        ifdef BABL_MOVE
    BABLM(BABL_GO_LEFT_1C, SS_TAP(X_LEFT));
    BABLM(BABL_GO_RIGHT_1C, SS_TAP(X_RIGHT));
    BABLM(BABL_GO_LEFT_WORD, IMCTL(X_LEFT));
    BABLM(BABL_GO_RIGHT_WORD, IMCTL(X_RIGHT));
    BABLM(BABL_GO_START_LINE, SS_TAP(X_HOME));
    BABLM(BABL_GO_END_LINE, SS_TAP(X_END));
    BABLM(BABL_GO_START_DOC, OMSFT(IMCTL(X_HOME)));
    BABLM(BABL_GO_END_DOC, OMSFT(IMCTL(X_END)));
    // leaving these for command line editing.
    BABLM(BABL_GO_NEXT_LINE, SS_TAP(X_DOWN));
    BABLM(BABL_GO_PREV_LINE, SS_TAP(X_UP));
    // These are for kitty scrolling by one line
    // BABLM(BABL_GO_NEXT_LINE, OMSFT(IMCTL(X_DOWN)));
    // BABLM(BABL_GO_PREV_LINE, OMSFT(IMCTL(X_UP)));
    // passthrough
    BABLM(BABL_PGDN, OMSFT(IMCTL(X_PGDN)));  // kitty pagedown
    BABLM(BABL_PGUP, OMSFT(IMCTL(X_PGUP)));    // kitty pageup
                                               // passthrough to commanrd line/shell.
    BABLM(BABL_DEL_RIGHT_1C, SS_LCTL("d"));
    BABLM(BABL_DEL_LEFT_WORD, SS_LCTL("w"));  // meta-DEL instead?
    BABLM(BABL_DEL_RIGHT_WORD, SS_LALT("d"));
    BABLM(BABL_DEL_TO_LINE_END, SS_LCTL("k"));
    BABLM(BABL_DEL_TO_LINE_START, SS_LCTL("u"));
    BABLM(BABL_GO_PARA_START, IMCTL(X_UP));
    BABLM(BABL_GO_PARA_END, IMCTL(X_DOWN));
    BABLM(BABL_MODE, "Kitty! ");
#        endif
#        ifdef BABL_OSKEYS
    // cut isn't real, undo/redo are passthrough.
    BABLM(BABL_UNDO, SS_LCTL("z"));
    BABLM(BABL_REDO, SS_LCTL("y"));
    BABLM(BABL_CUT, OMSFT(IMCTL(X_X)));
    BABLM(BABL_COPY, OMSFT(IMCTL(X_C)));
    BABLM(BABL_PASTE, OMSFT(IMCTL(X_V)));
    BABLM(BABL_SELECT_ALL, SS_LCTL("a"));
    BABLM(BABL_FIND, SS_LCTL("f"));  // passthrough.
    // BABLM(BABL_CLOSE_APP, IMALT(X_F4)); // gnome.
    // BABLM(BABL_HELP, SS_TAP(X_F1)); // script to pop open kitty web page?
    // 2 passthrough.
    BABLM(BABL_FIND_NEXT, SS_LCTL("g"));       // Gnome*/
    BABLM(BABL_FIND_PREV, OMSFT(IMCTL(X_G)));  // Gnome*/
                                               // BABLM(BABL_FIND_NEXT  (SS_LALT(X_F3))    ); //KDE */
    /* BABLM( BABL_FIND_REPLACE , (SS_LCTL("r"))	); // KDE */
    // BABLM(BABL_FIND_REPLACE, SS_LCTL("h"));  // Gnome*/
    BABLM(BABL_RUNAPP, OMSFT(IMCTL(X_O)));  // pass current selection to program.
    BABLM(BABL_SWITCH_APP_NEXT, IMGUI(X_TAB));
    // BABLM(BABL_SWITCH_APP_LAST, OMSFT(IMALT(X_TAB)));
    BABLM(BABL_WINDOW_NEXT, IMGUI(X_GRAVE));         // next OS window of kitty.
    BABLM(BABL_WINDOW_PREV, OMSFT(IMGUI(X_GRAVE)));  // NA?
#            ifdef TAB_MEANS_TAB
    BABLM(BABL_WINDOW_NEW, OMSFT(IMCTL(X_ENTER)));  // a window is a window
#            else
    BABLM(BABL_WINDOW_NEW, OMSFT(IMCTL(X_T)));  // a window is a tab
#            endif
                                                    // KITTY - missing close window.
    // BABLM( BABL_HELP,		(SS_TAP(X_F1))	); // NA?
    // BABLM(BABL_LOCK, OMCTL(IMALT(X_L))); // NA passthrough
    // BABLM(BABL_SCREENCAPTURE, IMSFT(X_PRINT_SCREEN)); // NA passthrough
#        endif
#        ifdef BABL_BROWSER

#            ifdef TAB_MEANS_TAB
    // option A  - do tab when I say tab.
    BABLM(BABL_BROWSER_NEW_TAB, OMSFT(IMCTL(X_T)));
    BABLM(BABL_BROWSER_CLOSE_TAB, OMSFT(IMCTL(X_Q)));
    BABLM(BABL_BROWSER_NEXT_TAB, OMSFT(IMCTL(X_RIGHT)));
    BABLM(BABL_BROWSER_PREV_TAB, OMSFT(IMCTL(X_LEFT)));
    // ok, this is a bit of a stretch, overloading meaning of forwards/backwards
    BABLM(BABL_BROWSER_FORWARD, OMSFT(IMCTL(X_DOT)));  // move current kitty tab forwards
    BABLM(BABL_BROWSER_BACK, OMSFT(IMCTL(X_COMMA)));   // move current kitty tab back
     // requires kitty config  of "map ctrl+shift+f7 detach_window"
    BABLM(BABL_BROWSER_REOPEN_LAST_TAB, IMCTL(X_F7));  // pop current frame into a window
#            else                                      // tab means window/frame.
                                                // option B - do Kitty window  (frame) when I say tab
    BABLM(BABL_BROWSER_NEW_TAB, OMSFT(IMCTL(X_ENTER)));
    BABLM(BABL_BROWSER_NEXT_TAB, OMSFT(IMCTL(X_LBRC)));
    BABLM(BABL_BROWSER_PREV_TAB, OMSFT(IMCTL(X_RBRC)));
    // ok, this is a bit of a stretch, overloading meaning of forwards/backwards
    BABLM(BABL_BROWSER_FORWARD, OMSFT(IMCTL(X_F)));
    BABLM(BABL_BROWSER_BACK, OMSFT(IMCTL(X_B)));
    // kitty - questionable mental model - reopen current frame as a window
    // requires kitty config  of "map ctrl+shift+f6 detach_frame"
    BABLM(BABL_BROWSER_REOPEN_LAST_TAB, IMCTL(X_F6));  // pop current frame into a window
#            endif                                     // tab means tab

    //   BABLM(BABL_BROWSER_FIND, SS_LCTL("f"));
    BABLM(BABL_BROWSER_BOOKMARK, SS_LCTL(SS_LSFT(SS_LALT("t"))));  // bookmark == set tab title.
    BABLM(BABL_BROWSER_DEV_TOOLS, OMSFT(IMCTL(X_F2)));             // edit kitty config.
    BABLM(BABL_BROWSER_RELOAD, OMSFT(IMCTL(X_DEL)));               // reset terminal
    BABLM(BABL_BROWSER_FULLSCREEN, OMSFT(IMCTL(X_F11)));
    BABLM(BABL_BROWSER_ZOOM_IN, OMSFT(IMCTL(X_EQUAL)));
    BABLM(BABL_BROWSER_ZOOM_OUT, OMSFT(IMCTL(X_MINUS)));
    // Again, breaking model to overload "view source"
    BABLM(BABL_BROWSER_VIEWSRC, OMSFT(IMCTL(X_O)));  // open URL in browser

#        endif
#        ifdef BABL_APP
    BABLM(BABL_APP_SAVE, SS_LCTL("s"));                   // passthrough.
#            ifdef TAB_MEANS_TAB                          // frames are called  windows.
    BABLM(BABL_SPLIT_FRAME_VERT, OMSFT(IMCTL(X_ENTER)));  // add new frame in kitty window
    BABLM(BABL_UNSPLIT_FRAME_VERT, OMSFT(IMCTL(X_W)));    // close window
    // BUG, this breaks the mental model.  move the current frame forward/back in rotation
    BABLM(BABL_SPLIT_FRAME_HORIZONTAL, OMSFT(IMCTL(X_F)));
    BABLM(BABL_UNSPLIT_FRAME_HORIZONTAL, OMSFT(IMCTL(X_B)));
    // KITTY - missing ctrl shift ` = move frame to top.
    BABLM(BABL_NEXT_FRAME, OMSFT(IMCTL(X_RBRC)));
    BABLM(BABL_PREV_FRAME, OMSFT(IMCTL(X_LBRC)));
#            else   // splits are tabs
    BABLM(BABL_SPLIT_FRAME_VERT, OMSFT(IMCTL(X_T)));
    BABLM(BABL_UNSPLIT_FRAME_VERT, OMSFT(IMCTL(X_Q)));  // close Tab
    BABLM(BABL_NEXT_FRAME, OMSFT(IMCTL(X_RIGHT)));
    BABLM(BABL_PREV_FRAME, OMSFT(IMCTL(X_LEFT)));
    // ok, this is a bit of a stretch, overloading meaning of forwards/backwards
    BABLM(BABL_SPLIT_FRAME_HORIZONTAL, OMSFT(IMCTL(X_DOT)));      // move current kitty tab forwards
    BABLM(BABL_UNSPLIT_FRAME_HORIZONTAL, OMSFT(IMCTL(X_COMMA)));  // move current kitty tab back
#            endif  // tab means tab
#        endif

    // Todo, ring bell, flash light, show user this isn't supported
    return false;
}

#    endif /* kitty mode */
#endif
