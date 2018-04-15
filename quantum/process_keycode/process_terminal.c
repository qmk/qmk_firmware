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

#ifndef CMD_BUFF_SIZE
  #define CMD_BUFF_SIZE 5
#endif


bool terminal_enabled = false;
char buffer[80] = "";
char cmd_buffer[CMD_BUFF_SIZE][80];
bool cmd_buffer_enabled = true; //replace with ifdef?
char newline[2] = "\n";
char arguments[6][20];
bool firstTime = true;

signed int cmd_buffer_pos = 0;
short int current_cmd_buffer_pos = 1;

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
    memset(cmd_buffer,0,CMD_BUFF_SIZE * 80);
    for (int i = 0; i < 6; i++)
        strcpy(arguments[i], "");
    // select all text to start over
    // SEND_STRING(SS_LCTRL("a"));
    send_string(terminal_prompt);
}

void disable_terminal(void) {
    terminal_enabled = false;
    SEND_STRING("\n");
}

void push_to_cmd_buffer(void) {
if (cmd_buffer_enabled) {
    if (cmd_buffer == NULL) {
      return;
    } else {
    /* works ish, buffer misses out on 0 occasionally
    0-----a  |0->
    1----ab  |+80->
    2---abc  |+160->
    3--abcd  |+240->
    4-abcde  |+320->400
    */

   if (firstTime) {
     firstTime = false;
   } else {
    for (int i= CMD_BUFF_SIZE - 1;i > 0 ;--i) {
      strncpy(cmd_buffer[i],cmd_buffer[i-1],79); //try reversing orders ; make print_buff go from 0-4 rather than 4-0, probably easier......
    }
   }

   if (cmd_buffer_pos < 4) {
     cmd_buffer_pos = 0;
   }

    strcpy(cmd_buffer[cmd_buffer_pos],buffer);
    ++cmd_buffer_pos;

    }
  }
}

void terminal_about(void) {
    SEND_STRING("QMK Firmware\n");
    SEND_STRING("  v");
    SEND_STRING(QMK_VERSION);
    SEND_STRING("\n"SS_TAP(X_HOME)"  Built: ");
    SEND_STRING(QMK_BUILDDATE);
    send_string(newline);
    #ifdef TERMINAL_HELP
        if (strlen(arguments[1]) != 0) {
            SEND_STRING("You entered: ");
            send_string(arguments[1]);
            send_string(newline);
        }
    #endif
}

void terminal_help(void);

extern const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];

void terminal_keycode(void) {
    if (strlen(arguments[1]) != 0 && strlen(arguments[2]) != 0 && strlen(arguments[3]) != 0) {
        char keycode_dec[5];
        char keycode_hex[5];
        uint16_t layer = strtol(arguments[1], (char **)NULL, 10);
        uint16_t row = strtol(arguments[2], (char **)NULL, 10);
        uint16_t col = strtol(arguments[3], (char **)NULL, 10);
        uint16_t keycode = pgm_read_word(&keymaps[layer][row][col]);
        itoa(keycode, keycode_dec, 10);
        itoa(keycode, keycode_hex, 16);
        SEND_STRING("0x");
        send_string(keycode_hex);
        SEND_STRING(" (");
        send_string(keycode_dec);
        SEND_STRING(")\n");
    } else {
        #ifdef TERMINAL_HELP
            SEND_STRING("usage: keycode <layer> <row> <col>\n");
        #endif
    }
}

void terminal_keymap(void) {
    if (strlen(arguments[1]) != 0) {
        uint16_t layer = strtol(arguments[1], (char **)NULL, 10);
        for (int r = 0; r < MATRIX_ROWS; r++) {
            for (int c = 0; c < MATRIX_COLS; c++) {
                uint16_t keycode = pgm_read_word(&keymaps[layer][r][c]);
                char keycode_s[8];
                sprintf(keycode_s, "0x%04x, ", keycode);
                send_string(keycode_s);
            }
            send_string(newline);
        }
    } else {
        #ifdef TERMINAL_HELP
            SEND_STRING("usage: keymap <layer>\n");
        #endif
    }
}

void print_cmd_buff(void) {
  for(int i=0;i<CMD_BUFF_SIZE;i++){
    char a = ' ';
    itoa(i ,&a,10);
    const char * x = &a;
    send_string(x);
    SEND_STRING(". ");
    send_string(cmd_buffer[i]);
    SEND_STRING("\n");
  }
}

stringcase terminal_cases[] = {
    { "about", terminal_about },
    { "help", terminal_help },
    { "keycode", terminal_keycode },
    { "keymap", terminal_keymap },
    //{ "flush-buffer" , flush_cmd_buff},
    { "p" , print_cmd_buff},
    { "exit", disable_terminal }
};

void terminal_help(void) {
    SEND_STRING("commands available:\n  ");
    for( stringcase* case_p = terminal_cases; case_p != terminal_cases + sizeof( terminal_cases ) / sizeof( terminal_cases[0] ); case_p++ ) {
        send_string(case_p->string);
        SEND_STRING(" ");
    }
    send_string(newline);
}

void command_not_found(void) {
    SEND_STRING("command \"");
    send_string(buffer);
    SEND_STRING("\" not found\n");
}

void process_terminal_command(void) {
    // we capture return bc of the order of events, so we need to manually send a newline
    send_string(newline);

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
                    push_to_cmd_buffer();
                    current_cmd_buffer_pos = CMD_BUFF_SIZE - 1;
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
                if (current_cmd_buffer_pos >= 0) { //once we get to the top, dont do anything
                  str_len = strlen(buffer);
                  for(int  i= 0;i < str_len ;++i) {
                      send_string(SS_TAP(X_BSPACE)); //clear w/e is on the line already
                      //process_terminal(KC_BSPC,record);
                  }
                  strncpy(buffer,cmd_buffer[current_cmd_buffer_pos],79);

                  send_string(buffer);
                  --current_cmd_buffer_pos; //get ready to access the above cmd is up is pressed again
                }
                    return false; break;
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
