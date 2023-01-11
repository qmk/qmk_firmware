/*  A library to output the right key shortcut in any common app.
Given a global variable babble_mode to show the environment and a
key that calls the paste macro, do the right type of paste.
Setting the context is done by another macro, or TBD interaction with the host.

Nano mode is probably most useful for people who don't usually use Nano, but
sometimes find themselves using it.

https://www.nano-editor.org/dist/latest/cheatsheet.html
*/

#include QMK_KEYBOARD_H

#ifdef USE_BABBLEPASTE
#    include "babblePaste.h"

#    ifdef BABL_NANO

// probably should allow meta to not be ALT
#        define DMETA IMALT

bool babblePaste_nano(uint16_t keycode) {
#        ifdef BABL_MOVE
    BABLM(BABL_GO_LEFT_1C, SS_LCTL("b"));
    BABLM(BABL_GO_RIGHT_1C, SS_LCTL("f"));
    BABLM(BABL_GO_LEFT_WORD, IMCTL(X_LEFT));
    BABLM(BABL_GO_RIGHT_WORD, IMCTL(X_RIGHT));
    BABLM(BABL_GO_START_LINE, SS_LCTL("a"));
    BABLM(BABL_GO_END_LINE, SS_LCTL("e"));
    BABLM(BABL_GO_START_DOC, IMALT(X_BSLS));
    BABLM(BABL_GO_END_DOC, IMALT(X_SLASH));
    BABLM(BABL_GO_NEXT_LINE, SS_LCTL("n"));
    BABLM(BABL_GO_PREV_LINE, SS_LCTL("p"));
    BABLM(BABL_GO_PARA_START, IMCTL(X_UP));
    BABLM(BABL_GO_PARA_END, IMCTL(X_DOWN));
    BABLM(BABL_PGDN, SS_LCTL("v"));
    BABLM(BABL_PGUP, SS_LCTL("y"));
    BABLM(BABL_DEL_RIGHT_1C, SS_LCTL("d"));
    BABLM(BABL_DEL_LEFT_WORD, IMCTL(X_BSPC));
    BABLM(BABL_DEL_RIGHT_WORD, IMCTL(X_DEL));
    //   BABLM(BABL_DEL_TO_LINE_END, SS_LCTL("k"));
    //   BABLM(BABL_DEL_TO_LINE_START, SS_TAP(X_ESCAPE) "0" SS_LCTL("k"));
    BABLM(BABL_MODE, "Nano ");
#        endif
#        ifdef BABL_OSKEYS
    BABLM(BABL_UNDO, SS_LALT("u"));
    BABLM(BABL_REDO, SS_LALT("e"));
    BABLM(BABL_CUT, SS_LCTL("k"));  // arguably b/c line based, not selection
    BABLM(BABL_COPY, SS_LALT("6"));  // arguably
    BABLM(BABL_PASTE, SS_LCTL("u"));
    //  BABLM(BABL_SELECT_ALL, SS_LCTL("x") "h");
    BABLM(BABL_FIND, SS_LCTL("w"));
    BABLM(BABL_FIND_NEXT, SS_LALT("w"));
    BABLM(BABL_FIND_PREV, SS_LALT("q"));
    BABLM(BABL_FIND_REPLACE, SS_LALT("r"));
    BABLM(BABL_RUNAPP, SS_LCTL("t"));
    BABLM(BABL_WINDOW_NEXT, OMALT(IMSFT(X_DOT)));
    BABLM(BABL_WINDOW_PREV, OMALT(IMSFT(X_COMMA)));
    BABLM(BABL_WINDOW_NEW, IMCTL(X_R) IMALT(X_F));  //
    BABLM(BABL_CLOSE_APP, SS_LCTL("x"));
    BABLM(BABL_HELP, SS_LCTL("g"));

    // BABLM( BABL_LOCK,		()	); // lock buffer? Too many options.
    // BABLM( BABL_SCREENCAPTURE,		()	); // requires plugin?

#        endif

#        ifdef BABL_APP
    BABLM(BABL_APP_SAVE, SS_LCTL("s"));  // save file blurs app & os. Move?
    BABLM(BABL_APP_SET_MARK, SS_LALT("a"));
#        endif

    // Todo, ring bell, flash light, show user this isn't supported
    return false;
}
#    endif /* nano mode*/
#endif
