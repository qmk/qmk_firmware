/* Copyright 2017 Jack Humbert
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

#include "process_terminal.h"
#include <string.h>
#include "version.h"
#include <stdio.h>
#include <math.h>

bool terminal_enabled = false;
char buffer[80] = "";
char arguments[6][80];

__attribute__ ((weak))
const char terminal_prompt[8] = "> ";

#ifdef AUDIO_ENABLE
    #ifndef TERMINAL_SONG
        #define TERMINAL_SONG SONG(TERMINAL_SOUND)
    #endif
    float terminal_song[][2] = TERMINAL_SONG;
    #define TERMINAL_BELL() PLAY_SONG(terminal_song)
#else 
    #define TERMINAL_BELL()  
#endif

__attribute__ ((weak))
const char keycode_to_ascii_lut[58] = {
    0, 0, 0, 0,
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, 0, 0, '\t',
    ' ', '-', '=', '[', ']', '\\', 0, ';', '\'', '`', ',', '.', '/'
}; 

__attribute__ ((weak))
const char shifted_keycode_to_ascii_lut[58] = {
    0, 0, 0, 0,
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', 0, 0, 0, '\t',
    ' ', '_', '+', '{', '}', '|', 0, ':', '\'', '~', '<', '>', '?'
}; 

struct stringcase { 
    char* string; 
    void (*func)(void); 
} typedef stringcase;

void enable_terminal(void) {
    terminal_enabled = true;
    strcpy(buffer, "");
    for (int i = 0; i < 6; i++)
        strcpy(arguments[i], "");
    // select all text to start over
    // SEND_STRING(SS_LCTRL("a"));
    send_string(terminal_prompt);
}

void disable_terminal(void) {
    terminal_enabled = false;
}

void terminal_about(void) {
    SEND_STRING("QMK Firmware\n");
    SEND_STRING("  v");
    SEND_STRING(QMK_VERSION);
    SEND_STRING("\n"SS_TAP(X_HOME)"  Built: ");
    SEND_STRING(QMK_BUILDDATE);
    SEND_STRING("\n");
    if (strlen(arguments[1]) != 0) {
        SEND_STRING("You entered: ");
        send_string(arguments[1]);
        SEND_STRING("\n");
    }
}

stringcase terminal_cases[] = { 
    { "exit", disable_terminal },
    { "about", terminal_about }
};

void command_not_found(void) {
    SEND_STRING("command \"");
    send_string(buffer);
    SEND_STRING("\" not found\n");
}

void process_terminal_command(void) {
    // we capture return bc of the order of events, so we need to manually send a newline
    SEND_STRING("\n");

    char * pch;
    uint8_t i = 0;
    pch = strtok(buffer, " ");
    while (pch != NULL) {
        strcpy(arguments[i], pch);
        pch = strtok(NULL, " ");
        i++;
    }
  
    bool command_found = false;
    for( stringcase* case_p = terminal_cases; case_p != terminal_cases + sizeof( terminal_cases ) / sizeof( terminal_cases[0] ); case_p++ ) {
        if( 0 == strcmp( case_p->string, buffer ) ) {
            command_found = true;
            (*case_p->func)();
            break;
        }
    }

    if (!command_found)
        command_not_found();

    if (terminal_enabled) {
        strcpy(buffer, "");
        for (int i = 0; i < 6; i++)
            strcpy(arguments[i], "");
        SEND_STRING(SS_TAP(X_HOME));
        send_string(terminal_prompt);
    }
}

bool process_terminal(uint16_t keycode, keyrecord_t *record) {

    if (keycode == TERM_ON && record->event.pressed) {
        enable_terminal();
        return false;
    }

    if (terminal_enabled && record->event.pressed) {
        if (keycode == TERM_OFF && record->event.pressed) {
            disable_terminal();
            return false;
        }
        if (keycode < 256) {
            uint8_t str_len;
            char char_to_add;
            switch (keycode) {
                case KC_ENTER:
                    process_terminal_command();
                    return false; break;
                case KC_ESC:
                    SEND_STRING("\n");
                    enable_terminal();
                    return false; break;
                case KC_BSPC:
                    str_len = strlen(buffer);
                    if (str_len > 0) {
                        buffer[str_len-1] = 0;
                        return true;
                    } else {
                        TERMINAL_BELL();
                        return false;
                    } break;
                case KC_LEFT:
                case KC_RIGHT:
                case KC_UP:
                case KC_DOWN:
                    return false; break;
                default:
                    if (keycode <= 58) {
                        char_to_add = 0;
                        if (get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))) {
                            char_to_add = shifted_keycode_to_ascii_lut[keycode];
                        } else if (get_mods() == 0) {
                            char_to_add = keycode_to_ascii_lut[keycode];
                        }
                        if (char_to_add != 0) {
                            strncat(buffer, &char_to_add, 1);
                        } 
                    } break;
            }



        }
    }
    return true;
}