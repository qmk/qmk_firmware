/*
 * Copyright 2021 milestogo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

 /* 
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
    BABLM(BABL_GO_LEFT_1C, SS_LCTRL("b"));
    BABLM(BABL_GO_RIGHT_1C, SS_LCTL("f"));
    BABLM(BABL_GO_LEFT_WORD, IMCTL(X_LEFT));
    BABLM(BABL_GO_RIGHT_WORD, IMCTL(X_RIGHT));
    BABLM(BABL_GO_START_LINE, SS_LCTRL("a"));
    BABLM(BABL_GO_END_LINE, SS_LCTRL("e"));
    BABLM(BABL_GO_START_DOC, IMALT(X_BSLS));
    BABLM(BABL_GO_END_DOC, IMALT(X_SLASH));
    BABLM(BABL_GO_NEXT_LINE, SS_LCTRL("n"));
    BABLM(BABL_GO_PREV_LINE, SS_LCTRL("p"));
    BABLM(BABL_GO_PARA_START, IMCTL(X_UP));
    BABLM(BABL_GO_PARA_END, IMCTL(X_DOWN));
    BABLM(BABL_PGDN, SS_LCTRL("v"));
    BABLM(BABL_PGUP, SS_LCTRL("y"));
    BABLM(BABL_DEL_RIGHT_1C, SS_LCTRL("d"));
    BABLM(BABL_DEL_LEFT_WORD, IMCTL(X_BSPC));
    BABLM(BABL_DEL_RIGHT_WORD, IMCTL(X_DEL));
    //   BABLM(BABL_DEL_TO_LINE_END, SS_LCTRL("k"));
    //   BABLM(BABL_DEL_TO_LINE_START, SS_TAP(X_ESCAPE) "0" SS_LCTRL("k"));
    BABLM(BABL_MODE, "Nano ");
#        endif
#        ifdef BABL_OSKEYS
    BABLM(BABL_UNDO, SS_LALT("u"));
    BABLM(BABL_REDO, SS_LALT("e"));
    BABLM(BABL_CUT, SS_LCTRL("k"));  // arguably b/c line based, not selection
    BABLM(BABL_COPY, SS_LALT("6"));  // arguably
    BABLM(BABL_PASTE, SS_LCTRL("u"));
    //  BABLM(BABL_SELECT_ALL, SS_LCTRL("x") "h");
    BABLM(BABL_FIND, SS_LCTRL("w"));
    BABLM(BABL_FIND_NEXT, SS_LALT("w"));
    BABLM(BABL_FIND_PREV, SS_LALT("q"));
    BABLM(BABL_FIND_REPLACE, SS_LALT("r"));
    BABLM(BABL_RUNAPP, SS_LCTL("t"));
    BABLM(BABL_WINDOW_NEXT, OMALT(IMSFT(X_DOT)));
    BABLM(BABL_WINDOW_PREV, OMALT(IMSFT(X_COMMA)));
    BABLM(BABL_WINDOW_NEW, IMCTL(X_R) IMALT(X_F));  //
    BABLM(BABL_CLOSE_APP, SS_LCTRL("x"));
    BABLM(BABL_HELP, SS_LCTRL("g"));

    // BABLM( BABL_LOCK,		()	); // lock buffer? Too many options.
    // BABLM( BABL_SCREENCAPTURE,		()	); // requires plugin?

#        endif

#        ifdef BABL_APP
    BABLM(BABL_APP_SAVE, SS_LCTRL("s"));  // save file blurs app & os. Move?
    BABLM(BABL_APP_SET_MARK, SS_LALT("a"));
#        endif

    // Todo, ring bell, flash light, show user this isn't supported
    return false;
}
#    endif /* nano mode*/
#endif
