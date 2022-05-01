/*
 * Babblepaste select function.
 * Start a selection at current location, allow movement by the babble movement keys.
 * The effect is like kakoune word and line select, but works across OSes and apps.

 * Automatically exit selection mode when a non-movement key is pressed.
 * leave selected text ready for cut/copy/yank/pipe on the contents.

 *  This code is a set of incrementing changes to getruer's smart capslock & smart select
 *  https://getreuer.info/posts/keyboards
 *  Copyright milestogo 2022
 *  Copyright 2021 Google LLC

 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at

 * https://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include "babblepaste.h"

#ifdef BABL_SELECT

enum {
    STATE_NONE,
    STATE_SELECTED,
    STATE_WORDL,
    STATE_WORDR,
    STATE_LINEU,
    STATE_LINED,
    STATE_SELECTING,
};

// Toggle modifier .
// CTRL for most things, Gui for mac, nothing for readline.

bool do_select_mod(bool state, uint8_t lastmode) {
/// MAC is only mode that uses Alt for selection
#    ifdef BABL_MAC
    if (lastmode == BABL_MAC_MODE) {
        if (state) {
            register_code(KC_LALT);
        } else {
            unregister_code(KC_LALT);
        }
        return true;
    }
#    endif

// Most things use CTRL
#    ifdef BABL_WINDOWS
    if (lastmode == BABL_WINDOWS_MODE) {
        if (state) {
            register_code(KC_LCTL);
        } else {
            unregister_code(KC_LCTL);
        }
        return true;
    }
#    endif
#    ifdef BABL_LINUX
    if (lastmode == BABL_LINUX_MODE) {
        if (state) {
            register_code(KC_LCTL);
        } else {
            unregister_code(KC_LCTL);
        }
        return true;
    }
#    endif
#    ifdef BABL_CHROMEOS
    if (lastmode == BABL_CHROMEOS_MODE) {
        if (state) {
            register_code(KC_LCTL);
        } else {
            unregister_code(KC_LCTL);
        }
        return true;
    }
#    endif

// Some things can't use word select at all
#    if defined BABL_READLINE
    if (lastmode == BABL_READLINE_MODE) {
        return true;
    }
#    endif

    /// And some things can use word select, but they don't use arrow keys, so we've already trapped them in process_babble_select_key

    // If we got here, we're probably in a mode like VI or emacs that should't need mods in the first place
    return false;
}

// process_babble_select_keys - Provide keys to select previous or next word or line.
// Function only works where Shift + arrow keys is a selection.
// Make sure to only call function from babble_modes where that is true.
bool process_babble_select_keys(uint16_t keycode, keyrecord_t* record) {
    //   uint8_t        lastmode = 0;
    static uint8_t state = STATE_NONE;

    switch (state) {
        case STATE_NONE:
            if (record->event.pressed) {
                switch (keycode) {
                    case B_SEL_WORD_R:
                        do_select_mod(1, babble_mode);
                        SEND_STRING(SS_TAP(X_LEFT) SS_TAP(X_RIGHT));
                        register_code(KC_LSFT);
                        register_code(KC_RGHT);
                        // lastmode = babble_mode;
                        do_select_mod(0, babble_mode);
                        state = STATE_WORDR;
                        return false;

                    case B_SEL_WORD_L:
                        do_select_mod(1, babble_mode);
                        SEND_STRING(SS_TAP(X_RIGHT) SS_TAP(X_LEFT));
                        register_code(KC_LSFT);
                        register_code(KC_LEFT);
                        do_select_mod(0, babble_mode);
                        state = STATE_WORDL;
                        return false;

                    case B_SEL_LINE_U:
                        switch (babble_mode) {
#    ifdef BABL_MAC
                            case BABL_MAC_MODE:
                                SEND_STRING(SS_LCTL("e" SS_LSFT("a")));
#    endif
                            default:
                                SEND_STRING(SS_TAP(X_END) SS_LSFT(SS_TAP(X_HOME)));
                        }
                        state = STATE_SELECTED;
                        return false;

                    case B_SEL_LINE_D:
                        switch (babble_mode) {
#    ifdef BABL_MAC
                            case BABL_MAC_MODE:
                                SEND_STRING(SS_LCTL("a" SS_LSFT("e")));
#    endif
                            default:
                                SEND_STRING(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)));
                        }
                        state = STATE_SELECTED;
                        return false;

                    default: // any non select key should pass through, since we aren't in select mode yet.
                        return true;
                }
            } else { // key up in state_none
                return true;
            }

        case STATE_WORDR: {
            unregister_code(KC_RIGHT);
            unregister_code(KC_LSFT);
            state = STATE_SELECTED;
        }

        case STATE_WORDL: {
            unregister_code(KC_LEFT);
            unregister_code(KC_LSFT);
            state = STATE_SELECTED;
        }

        case STATE_LINED: {
            unregister_code(KC_DOWN);
            unregister_code(KC_LSFT);
            state = STATE_SELECTED;
        }

        case STATE_LINEU: {
            unregister_code(KC_UP);
            unregister_code(KC_LSFT);
            state = STATE_SELECTED;
        }

        case STATE_SELECTING: { // allow all other movement keys
            unregister_code(KC_LSFT);
            state = STATE_SELECTED;
        }

        case STATE_SELECTED: {
            if (record->event.pressed) {
                switch (keycode) {
                    case B_SEL_WORD_L:
                        do_select_mod(1, babble_mode);
                        register_code(KC_LSFT);
                        register_code(KC_LEFT);
                        do_select_mod(0, babble_mode);
                        state = STATE_WORDL;
                        return false;

                    case B_SEL_WORD_R:
                        do_select_mod(1, babble_mode);
                        register_code(KC_LSFT);
                        register_code(KC_RIGHT);
                        do_select_mod(0, babble_mode);
                        state = STATE_WORDR;
                        return false;

                    case B_SEL_LINE_D:
                        register_code(KC_LSFT);
                        register_code(KC_DOWN);
                        unregister_code(KC_LSFT);
                        state = STATE_LINED;
                        return false;

                    case B_SEL_LINE_U:
                        register_code(KC_LSFT);
                        register_code(KC_UP);
                        unregister_code(KC_LSFT);
                        state = STATE_LINEU;
                        return false;

                    default:
                        state = STATE_NONE;
                }
            } else { // key up of something.
                return true;
            }
            // selected mode, not key down or up.
        }
    }
    // fall through if state above didn't complete work.
    return true;
}

bool process_babble_select(uint16_t keycode, keyrecord_t* record) {
    if (keycode >= B_SEL_WORD_L && keycode <= B_SEL_LINE_D) {
        // we only need to run if this is one of the select keys.

        switch (babble_mode) {
            /* is this a babble mode that does selection with the shift key?*/
#    if defined BABL_LINUX || defined BABL_WINDOWS || defined BABL_CHROMEOS || defined BABL_MAC || defined BABL_NANO || defined BABL_READLINE

#        ifdef BABL_LINUX
            case BABL_LINUX_MODE:
#        endif
#        ifdef BABL_WINDOWS
            case BABL_WINDOWS_MODE:
#        endif
#        ifdef BABL_CHROMEOS
            case BABL_CHROMEOS_MODE:
#        endif
#        ifdef BABL_MAC
            case BABL_MAC_MODE:
#        endif

// We can handle modes that use arrow keys but don't allow selection.
#        ifdef BABL_NANO
            case BABL_NANO_MODE:
#        endif
#        ifdef BABL_READLINE
            case BABL_READLINE_MODE:
#        endif
                return (process_babble_select_keys(keycode, record));
#    endif
                /* Modes that have their own way of selecting, outside of arrow keys*/
                // Stub out for now, call local functions in babl_*  later.

#    ifdef BABL_VI
            case BABL_VI_MODE:
                return true;
#    endif
#    ifdef BABL_EMACS
            case BABL_EMACS_MODE:
                return true;
#    endif
                /* Else, we're in a mode that doesn't really do selection
                    select button isn't going to do anything.  */
                // BABL_KITY
            default:
                return true;
        }
        return true;
    } else {
        return true;
    }
}

#endif
