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

 /* BABL library for Visual Studio Code
  * Not complete or tested. Plan is to set up windows codes on all OSes. 
  * Remember to check  https://github.com/qmk/qmk_firmware/blob/master/quantum/send_string_keycodes.h

  * To  set up windows codes. 
  * https://code.visualstudio.com/shortcuts/keyboard-shortcuts-windows.pdf
  */

// todo
// map terminal commands to  tabs? 
// probably want an ergonomic based layout for cursor operations. Like delmode? 


#include QMK_KEYBOARD_H

#ifdef USE_BABBLEPASTE
#    include "babblePaste.h"

#    ifdef BABL_WINDOWS

bool babblePaste_win(uint16_t keycode) {
#        ifdef BABL_MOVE
    BABLM(BABL_GO_LEFT_1C, SS_TAP(X_LEFT));
    BABLM(BABL_GO_RIGHT_1C, SS_TAP(X_RIGHT));
    BABLM(BABL_GO_LEFT_WORD, IMCTL(X_LEFT));
    BABLM(BABL_GO_RIGHT_WORD,IMCTL(X_RIGHT));
    BABLM(BABL_GO_START_LINE,IMGUI(X_LEFT));
    BABLM(BABL_GO_END_LINE,  IMGUI(X_RIGHT));
    BABLM(BABL_GO_START_DOC, IMCTL(X_HOME));
    BABLM(BABL_GO_END_DOC,   IMCTL(X_END));
    BABLM(BABL_GO_NEXT_LINE, IMCTL(X_DOWN));
    BABLM(BABL_GO_PREV_LINE, IMCTL(X_UP));
    BABLM(BABL_GO_PARA_START, SS_TAP(X_HOME));
    BABLM(BABL_GO_PARA_END,   SS_TAP(X_END));
    BABLM(BABL_PGDN, SS_TAP(X_PGDOWN)); // alt pgup for scroll?
    BABLM(BABL_PGUP, SS_TAP(X_PGUP));
    BABLM(BABL_DEL_RIGHT_1C, SS_TAP(X_DELETE));
    BABLM(BABL_DEL_LEFT_WORD, IMCTL(X_BSPACE));
    BABLM(BABL_DEL_RIGHT_WORD, IMCTL(X_DELETE));
    BABLM(BABL_DEL_TO_LINE_END, IMSFT(X_END) SS_TAP(X_DELETE));
    BABLM(BABL_DEL_TO_LINE_START, IMSFT(X_HOME) SS_TAP(X_DELETE));
    BABLM(BABL_MODE, "VSCode ");
#        endif

#        ifdef BABL_OSKEYS
    BABLM(BABL_UNDO, SS_LCTRL("z"));
    BABLM(BABL_REDO, SS_LCTRL("y"));
    BABLM(BABL_CUT, SS_LCTRL("x"));
    BABLM(BABL_COPY, SS_LCTRL("c"));
    BABLM(BABL_PASTE, SS_LCTRL("v"));
    BABLM(BABL_SELECT_ALL, SS_LCTRL("a"));
    BABLM(BABL_FIND, SS_LCTRL("f"));
    BABLM(BABL_FIND_NEXT, SS_TAP(X_F3));
    BABLM(BABL_FIND_PREV, IMSFT(X_F3)); 
    BABLM(BABL_FIND_REPLACE, SS_LCTRL("h"));
    BABLM(BABL_RUNAPP, SS_TAPLGUI("r"));// fire off terminal
    BABLM(BABL_SWITCH_APP_NEXT, IMALT(X_TAB));
    BABLM(BABL_SWITCH_APP_LAST, OMSFT(IMALT(X_TAB)));
    BABLM(BABL_WINDOW_NEXT, IMCTL(X_TAB));
    BABLM(BABL_WINDOW_PREV, OMSFT(IMCTL(X_TAB)));
    BABLM(BABL_WINDOW_NEW, IMCTL(X_N));
    //BABLM(BABL_CLOSE_APP, IMALT(X_F4));
    //BABLM(BABL_HELP, SS_TAP(X_F1));
    //BABLM(BABL_LOCK, SS_LGUI("l"));
    //BABLM(BABL_SCREENCAPTURE, OMSFT(SS_LGUI("s")));
    //BABLM(BABL_SWITCH_KEYBOARD_LAYOUT, IMGUI(X_SPACE));

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
#    endif /* BABL_VSCODE */
#endif     /* babblepaste */
