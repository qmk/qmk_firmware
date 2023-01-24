/* Copyright 2023 Yiancar-Designs, Bit-Shifter
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
#include "v4.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            // [daughter board] row 1 POS key macros
            case H_HELP:
                SEND_STRING("[HELP] key");
                break;
            case H_MACRO:
                SEND_STRING("[MACRO] key");
                break;
            case H_TERMINAL:
                SEND_STRING("[TERMINAL] key");
                break;
            case H_QUOTE:
                // wraps selected (editable) text in quotation marks
                SEND_STRING(SS_LCTL(SS_TAP(X_X))SS_TAP(X_QUOTE)SS_LCTL(SS_TAP(X_V))SS_TAP(X_QUOTE));
                break;
            case H_OVERSTRIKE:
                // toggles insert/overstrike
                SEND_STRING(SS_TAP(X_INSERT));
                break;
            case H_CLEAR_INPUT:
                // terminal: clears from the cursor to the beginning of the current command
                SEND_STRING(SS_LCTL(SS_TAP(X_U)));
                break;
            case H_CLEAR_SCREEN:
                SEND_STRING(SS_LCTL(SS_TAP(X_L)));
                // ^ linux/osx shell specific, for windows command replace with
                // SEND_STRING(SS_TAP(X_C)SS_TAP(X_L)SS_TAP(X_S)SS_TAP(KC_ENTER));
                break;
            case H_HOLD_OUTPUT:
                SEND_STRING("[HOLD OUTPUT] key");
                break;
            case H_STOP_OUTPUT:
                SEND_STRING("[STOP OUTPUT] key");
                break;
            case H_ABORT:
                SEND_STRING(SS_LCTL(SS_TAP(X_C)));
                break;
            case H_BREAK:
                SEND_STRING(SS_TAP(X_PAUSE));
                break;
            case H_RESUME:
                SEND_STRING(SS_TAP(X_F)SS_TAP(X_G)SS_TAP(X_ENTER));
                break;
            case H_CALL:
                SEND_STRING("[CALL] key");
                break;

            // [daughter board] row 2 POS key macros
            case H_LOCAL:
                SEND_STRING("[LOCAL] key");
                break;
            case H_NETWORK:
                SEND_STRING("[NETWORK] key");
                break;
            case H_SYSTEM:
                SEND_STRING("[SYSTEM] key");
                break;
            case H_REFRESH:
                SEND_STRING(SS_LCTL(SS_TAP(X_R)));
                break;
            case H_BUFFER:
                SEND_STRING("[BUFFER] key");
                break;
            case H_SQUARE:
                SEND_STRING("[SQUARE] key");
                break;
            case H_CIRCLE:
                SEND_STRING("[CIRCLE] key");
                break;
            case H_TRIANGLE:
                SEND_STRING("[TRIANGLE] key");
                break;
            case H_DIAMOND:
                SEND_STRING("[DIAMOND] key");
                break;
            case H_REPEAT:
                SEND_STRING("[REPEAT] key");
                break;
            case H_TRANSMIT:
                SEND_STRING("[TRANSMIT] key");
                break;
            case H_STATUS:
                SEND_STRING("[STATUS] key");
                break;
            case H_SUSPEND:
                SEND_STRING(SS_LCTL(SS_TAP(X_Z)));
                break;

            // [daughter board] row 3
            case H_CLOSE:
                // ctrl-w: closes a tab/panel within an application
                SEND_STRING(SS_LCTL(SS_TAP(X_W)));
                break;
            case H_OPEN:
                // ctrl-n: opens a tab/panel
                SEND_STRING(SS_LCTL(SS_TAP(X_N)));
                break;
            case H_COMPLETE:
                // tab tab: bash command line completion
                SEND_STRING(SS_TAP(X_TAB)SS_TAP(X_TAB));
                break;

            // [main board] row 1
            case H_WRITE:
                SEND_STRING(SS_LCTL(SS_TAP(X_S)));
                break;

            case H_DOUBLE_QUOTE__PLUS_MINUS:
                if (get_mods() & MODS_SHIFT_MASK) {
                    send_unicode_string("±");
                } else {
                    send_unicode_string("\"");
                }
                break;

            case H_COLON__TILDE:
                if (get_mods() & MODS_SHIFT_MASK) {
                    send_unicode_string("∼");
                } else {
                    SEND_STRING(":");
                }
                break;

            case H_L_BRACE__L_CHEVRON:
                if (get_mods() & MODS_SHIFT_MASK) {
                    send_unicode_string("‹");
                } else {
                    SEND_STRING("{");
                }
                break;

            case H_R_BRACE__R_CHEVRON:
                if (get_mods() & MODS_SHIFT_MASK) {
                    send_unicode_string("›");
                } else {
                    SEND_STRING("}");
                }
                break;

            // [main board] row 2
            case H_MARK:
                SEND_STRING("[MARK] key");
                break;
            case H_LEFT_PAREN__LEFT_BRACKET:
                if (get_mods() & MODS_SHIFT_MASK) {
                    CLEAN_MODS(
                    send_string(SS_TAP(X_LBRC))
                    );
                } else {
                    send_string("(");
                }
                break;
            case H_RIGHT_PAREN__RIGHT_BRACKET:
                if (get_mods() & MODS_SHIFT_MASK) {
                    CLEAN_MODS(
                    send_string(SS_TAP(X_RBRC))
                    );
                } else {
                    send_string(")");
                }
                break;

            // [main board] row 3
            case H_SELECT:
                SEND_STRING("[SELECT] key");
                break;
            case H_DEBUG:
                SEND_STRING("[DEBUG] key");
                break;
            case H_SEMI_COLON__BACK_TICK:
                if (get_mods() & MODS_SHIFT_MASK) {
                    CLEAN_MODS(
                    SEND_STRING("`");
                    );
                } else {
                    SEND_STRING(";");
                }
                break;
            case H_TICK__QUOTE:
                if (get_mods() & MODS_SHIFT_MASK) {
                    // host configured for uk layout, for ansi, switch to X_QUOT
                    SEND_STRING(SS_TAP(X_2));
                } else {
                    SEND_STRING("'");
                }
                break;
            case H_LINE:
                SEND_STRING("[LINE] key");
                break;
            case H_PAGE:
                if (get_mods() & MODS_SHIFT_MASK) {
                    CLEAN_MODS(
                    SEND_STRING(SS_TAP(X_PGUP));
                    );
                } else {
                    SEND_STRING(SS_TAP(X_PGDN));
                }
                break;

            // [main board] row 4
            case H_TTY:
                SEND_STRING("[TTY] key");
                break;
            case H_LOCK:
                SEND_STRING("[LOCK] key");
                break;

            // [main board] row 5
            case H_EOF:
                SEND_STRING(SS_LCTL(SS_TAP(X_END)));
                break;
            case H_7BIT:
                SEND_STRING("[7BIT] key");
                break;
            case H_CIRCLE_SM:
                SEND_STRING("[CIRCLE_SM] key");
                break;
        }
    }
    return true;
};
