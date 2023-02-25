#include QMK_KEYBOARD_H

enum _layers { _INSERT, _NAVIGATE, _NUMBERS };

#define CLN_ KC_COLN
#define CM_ KC_COMM
#define DT_ KC_DOT
#define P_ KC_P
#define Y_ KC_Y
#define A_ KC_A
#define O_ KC_O
#define AO_ LALT_T(KC_O)
#define E_ KC_E
#define CE_ LCTL_T(KC_E)
#define U_ KC_U
#define GU_ LGUI_T(KC_U)
#define I_ KC_I
#define DQ_ KC_DQUO
#define Q_ KC_Q
#define J_ KC_J
#define K_ KC_K
#define X_ KC_X

#define F_ KC_F
#define G_ KC_G
#define C_ KC_C
#define R_ KC_R
#define L_ KC_L
#define D_ KC_D
#define H_ KC_H
#define T_ KC_T
#define N_ KC_N
#define S_ KC_S
#define B_ KC_B
#define M_ KC_M
#define W_ KC_W
#define V_ KC_V
#define Z_ KC_Z

#define ArL KC_LEFT
#define ArD KC_DOWN
#define ArU KC_UP
#define ArR KC_RIGHT

#define _0 KC_0
#define _1 KC_1
#define _2 KC_2
#define _3 KC_3
#define _4 KC_4
#define _5 KC_5
#define _6 KC_6
#define _7 KC_7
#define _8 KC_8
#define _9 KC_9

#define ___ KC_TRNS
#define FROM KC_TRNS

#define S_TAB LSFT_T(KC_TAB)
#define SHTAB LSFT(KC_TAB)
#define N_SPC LT(1,KC_SPACE)


/*══════════════════════════════════════════════════════════════════════════════════════════════╗
     FEATURE FLAGS                                                                              ║
 *══════════════════════════════════════════════════════════════════════════════════════════════╣           */

#include "print.h"
#include "g/keymap_combo.h"

/*══════════════════════════════════════════════════════════════════════════════════════════════╗
     BASIC FUNCTIONS                                                                            ║
 *══════════════════════════════════════════════════════════════════════════════════════════════╣           */

int elapsed_time = 0;

uint8_t mod_state;

char* log_format          = "{\n\t\"kc\":\"0x%04X\",\n\t\"rw\":%2u,\n\t\"cl\":%2u,\n\t\"ly\":%u,\n\t\"md\":\"%02X\",\n\t\"om\":\"%02X\",\n\t\"tp\":%u,\n\t\"ts\":%5d\n}\n";
int   last_key_event_time = 0;


void repeat(uint16_t keycode, int rep) {
    for (int n = rep; n > 0; n--) {
        register_code16(keycode);
        unregister_code16(keycode);
    }
}


/*══════════════════════════════════════════════════════════════════════════════════════════════╗
     PROCESS RECORD USER                                                                        ║
 *══════════════════════════════════════════════════════════════════════════════════════════════╣           */

//  Callback function: runs every time a key is pressed or released
//      keycode represents the key definition that qmk has mapped
//      from 0000 to 7E00

bool process_record_user(uint16_t keycode, keyrecord_t* record) {

    mod_state = get_mods();

    uint32_t elapsed_time = timer_elapsed(last_key_event_time);
    last_key_event_time   = timer_read();
    uprintf(log_format, keycode, record->event.key.row, record->event.key.col, get_highest_layer(layer_state), get_mods(), get_oneshot_mods(), record->tap.count, (last_key_event_time + elapsed_time));


#ifdef PROCESS_CUSTOM_SHIFT_KEYS
    if (!process_custom_shift_keys(keycode, record)) {
#    ifdef LOG_KEY_EVENTS
        uprintf("key 0x%04X altered by custom shift", keycode);
#    endif
        return false;
    }
#endif

    return true;
}


/*══════════════════════════════════════════════════════════════════════════════════════════════╗
     MATRIX SCAN                                                                                ║
 *══════════════════════════════════════════════════════════════════════════════════════════════╣           */

LEADER_EXTERNS();
void matrix_scan_user(void) {

    LEADER_DICTIONARY() {
        leading = false;
        leader_end();
        SEQ_TWO_KEYS(KC_E, KC_F) {
            SEND_STRING("AVONSTU1@ford.com");
        }
        SEQ_TWO_KEYS(KC_E, KC_G) {
            SEND_STRING("AVONS394@gmail.com");
        }

        SEQ_TWO_KEYS(KC_SPACE, KC_SPACE) {
            // INTJ SEARCH ALL
            register_code(KC_LSFT);
            unregister_code(KC_LSFT);
            register_code(KC_LSFT);
            unregister_code(KC_LSFT);
        }
        SEQ_ONE_KEY(KC_O) {
            // INTJ OPEN
            register_code(KC_LGUI);
            register_code(KC_LSFT);
            register_code(KC_O);
            unregister_code(KC_O);
            unregister_code(KC_LSFT);
            unregister_code(KC_LGUI);
        }
        SEQ_ONE_KEY(KC_P) {
            // VSCode Cmd
            register_code(KC_LSFT);
            register_code(KC_LGUI);
            register_code(KC_P);
            unregister_code(KC_P);
            unregister_code(KC_LGUI);
            unregister_code(KC_LSFT);
        }
        SEQ_ONE_KEY(KC_DQUO) {
            // QUOT and go between
            register_code(KC_QUOT);
            unregister_code(KC_QUOT);
            register_code(KC_QUOT);
            unregister_code(KC_QUOT);
            register_code(KC_LEFT);
            unregister_code(KC_LEFT);
        }
        SEQ_ONE_KEY(KC_H) {
            // HIDE
            register_code(KC_LGUI);
            register_code(KC_H);
            unregister_code(KC_H);
            unregister_code(KC_LGUI);
        }

        // CODE SHORTHAND
        // IF
        SEQ_TWO_KEYS(KC_I, KC_F) {
            send_string("if (  ) {  }");
            repeat(KC_LEFT, 7);
        }
        // FOR
        SEQ_TWO_KEYS(KC_F, KC_R) {
            send_string("for (  ) {  }");
            repeat(KC_LEFT, 7);
        }
        // FALSE
        SEQ_ONE_KEY(KC_F) {
            send_string("false");
        }
        // TRUE
        SEQ_ONE_KEY(KC_T) {
            send_string("true");
        }
        // INT I IN
        SEQ_THREE_KEYS(KC_I, KC_N, KC_T) {
            send_string("int i=0; i< ; i++");
            repeat(KC_LEFT, 6);
        }
        // SHEBANG
        SEQ_TWO_KEYS(KC_S, KC_H) {
            send_string("#!/usr/bin/env  ");
        }
        // SSH KEYGEN
        SEQ_THREE_KEYS(KC_S, KC_S, KC_H) {
            send_string("ssh-keygen -t ed25519 -C ");
            tap_code16(KC_DQUO);
            tap_code16(KC_DQUO);
            tap_code16(KC_LEFT);
        }
    }

}


/*══════════════════════════════════════════════════════════════════════════════════════════════╗
     LAYER SWITCH                                                                               ║
 *══════════════════════════════════════════════════════════════════════════════════════════════╣           */

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _INSERT:
            break;
        case _NAVIGATE:
            break;
        case _NUMBERS:
            break;
        default:
            break;
    }
    return state;
}


/*══════════════════════════════════════════════════════════════════════════════════════════════╗
     KEYMAPS                                                                                    ║
 *══════════════════════════════════════════════════════════════════════════════════════════════╣           */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*══════════════════════════════════════════════════════════════════════════════════════════════╗
                        INSERT:0                                                                ║
        ╔══════╦══════╦══════╦══════╦══════╗       ╔══════╦══════╦══════╦══════╦══════╗         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ║   :  ║   ,  ║  .   ║  P   ║  Y   ║       ║   F  ║   G  ║   C  ║   R  ║   L  ║         ║
        ╠══════╬══════╬══════╬══════╬══════╣       ╠══════╬══════╬══════╬══════╬══════╣         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ║   A  ║   O  ║  E   ║  U   ║  I   ║       ║   D  ║   H  ║   T  ║   N  ║   S  ║         ║
        ╠══════╬══════╬══════╬══════╬══════╣       ╠══════╬══════╬══════╬══════╬══════╣         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ║   "  ║   Q  ║  J   ║  K   ║  X   ║       ║   B  ║   M  ║   W  ║   V  ║   Z  ║         ║
        ╚══════╩══════╩══════╩══════╩══════╝       ╚══════╩══════╩══════╩══════╩══════╝         ║
                               ╔═════╦═════╗       ╔═════╦═════╗                                ║
                               ║     ║LSFT/║       ║L_NAV║     ║                                ║
                               ║MOUSE║ TAB ║       ║/SPCE║LEADR║                                ║
                               ╚═════╩═════╝       ╚═════╩═════╝                                ║
                                                                                                ║        */
    [_INSERT] = LAYOUT(/* INSERT :0 ════════════════════════════════════════════════════════════╣        */
                        CLN_, CM_, DT_, P_,  Y_,        F_, G_, C_, R_, L_,
                        A_,   AO_, CE_, GU_, I_,        D_, H_, T_, N_, S_,
                        DQ_,  Q_,  J_,  K_,  X_,        B_, M_, W_, V_, Z_,

                                   SHTAB, S_TAB,        N_SPC, QK_LEAD

    ),

/*══════════════════════════════════════════════════════════════════════════════════════════════╗
                        NAVIGATE:1                                                              ║
        ╔══════╦══════╦══════╦══════╦══════╗       ╔══════╦══════╦══════╦══════╦══════╗         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ╠══════╬══════╬══════╬══════╬══════╣       ╠══════╬══════╬══════╬══════╬══════╣         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ╠══════╬══════╬══════╬══════╬══════╣       ╠══════╬══════╬══════╬══════╬══════╣         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ╚══════╩══════╩══════╩══════╩══════╝       ╚══════╩══════╩══════╩══════╩══════╝         ║
                               ╔═════╦═════╗       ╔═════╦═════╗                                ║
                               ║     ║     ║       ║     ║     ║                                ║
                               ║     ║     ║       ║     ║     ║                                ║
                               ╚═════╩═════╝       ╚═════╩═════╝                                ║
                                                                                                ║        */
    [_NAVIGATE] = LAYOUT(/* NAVIGATE :1 ════════════════════════════════════════════════════════╣        */
                    ___, ___, ___, ___, ___,        ___, ___, ___, ___, ___,
                    ___, ___, ___, ___, ___,        ___, ArL, ArD, ArU, ArR,
                    ___, ___, ___, ___, ___,        ___, ___, ___, ___, ___,

                                   ___, ___,        FROM, ___

    ),

/*══════════════════════════════════════════════════════════════════════════════════════════════╗
                        NUMBERS:2                                                               ║
        ╔══════╦══════╦══════╦══════╦══════╗       ╔══════╦══════╦══════╦══════╦══════╗         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ║      ║      ║      ║      ║      ║       ║      ║   7  ║   9  ║   9  ║      ║         ║
        ╠══════╬══════╬══════╬══════╬══════╣       ╠══════╬══════╬══════╬══════╬══════╣         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ║      ║      ║      ║      ║      ║       ║   0  ║   4  ║   5  ║   6  ║      ║         ║
        ╠══════╬══════╬══════╬══════╬══════╣       ╠══════╬══════╬══════╬══════╬══════╣         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ║      ║      ║      ║      ║      ║       ║      ║   1  ║   2  ║   3  ║      ║         ║
        ╚══════╩══════╩══════╩══════╩══════╝       ╚══════╩══════╩══════╩══════╩══════╝         ║
                               ╔═════╦═════╗       ╔═════╦═════╗                                ║
                               ║     ║     ║       ║     ║     ║                                ║
                               ║     ║     ║       ║     ║     ║                                ║
                               ╚═════╩═════╝       ╚═════╩═════╝                                ║
                                                                                                ║        */
    [_NUMBERS] = LAYOUT(/* NUMBERS :2 ══════════════════════════════════════════════════════════╣        */
                    ___, ___, ___, ___, ___,        ___, _7, _8, _9, ___,
                    ___, ___, ___, ___, ___,        _0,  _4, _5, _6, ___,
                    ___, ___, ___, ___, ___,        ___, _1, _2, _3, ___,

                                   ___, ___,        ___, ___

    )
};
