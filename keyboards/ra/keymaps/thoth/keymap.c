#include "quantum.h"
#include "config.h"

enum _layers { _INSERT, _NAVIGATE, _NUMBERS, _FUNCTION, _MACRO };

enum _keycodes {
    DM_REC = SAFE_RANGE,
    DM_PLAY,
};


/*══════════════════════════════════════════════════════════════════════════════════════════════╗
     FEATURE FLAGS                                                                              ║
 *══════════════════════════════════════════════════════════════════════════════════════════════╣           */

#include "print.h"
#include "g/keymap_combo.h"
#include "raw_hid.h"
#include "eeprom_driver.h"

#include "feature/shift_keys/custom_shift_keys.h"


/*══════════════════════════════════════════════════════════════════════════════════════════════╗
     BASIC FUNCTIONS                                                                            ║
 *══════════════════════════════════════════════════════════════════════════════════════════════╣           */

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

#define _F1 KC_F1
#define _F2 KC_F2
#define _F3 KC_F3
#define _F4 KC_F4
#define _F5 KC_F5
#define _F6 KC_F6
#define _F7 KC_F7
#define _F8 KC_F8
#define _F9 KC_F9
#define _F10 KC_F10
#define _F11 KC_F11
#define _F12 KC_F12

#define ___ KC_TRNS
#define FROM KC_TRNS

#define S_TAB LSFT_T(KC_TAB)
#define SHTAB LSFT(KC_TAB)
#define M_SHTAB LT(3,SHTAB)
#define N_SPC LT(1,KC_SPACE)

void repeat(uint16_t keycode, int rep) {
    for (int n = rep; n > 0; n--) {
        register_code16(keycode);
        unregister_code16(keycode);
    }
}

void indicator(void) {
        clear_mods();
        for (int j = 0; j < 3; j++) {
           tap_code16(KC_DOT);
        }
        tap_code16(KC_SPACE);
        wait_ms(80);
        for (int j = 0; j < 3; j++) {
          tap_code16(KC_BSPC);
        }
        set_mods(mod_state);
}

void raw_hid_receive(uint8_t *data, uint8_t len) {
  // Print the received data to the console
  for (int i = 0; i < len; i++) {
    printf("%02x ", data[i]);
  }
  printf("\n");
}

//  CUSTOM SHIFT  //
const custom_shift_key_t custom_shift_keys[] = {
    {KC_DOT, KC_EXLM},                // Shift . is !
    {KC_COMM, KC_QUES},               // Shift , is ?
    {KC_COLN, KC_SCLN},               // Shift : is ;
    {LT(5,KC_COMM), KC_QUES},         // Shift , is ?
    {KC_DQUO, KC_QUOT},               // Shift " is '
    {LT(1, KC_SPACE), KC_TAB},        // Shift SPACE is TAB
    {KC_LPRN, KC_RPRN},               // Shift ( is )
    {KC_RPRN, KC_LPRN},               // Shift ) is (
    {KC_LCBR, KC_RCBR},               // Shift { is }
    {KC_RCBR, KC_LCBR},               // Shift { is }
    {KC_LBRC, KC_RBRC},               // Shift [ is ]
    {KC_RBRC, KC_LBRC},               // Shift [ is ]
    {KC_LT, KC_GT},                   // Shift < is >
    {KC_GT, KC_LT},                   // Shift < is >
    {KC_DEL, KC_BSPC},                // Shift del is bspace
    {KC_BSPC, LGUI(KC_Z)},            // Shift bspace is undo
    {LGUI(KC_V), LCTL(KC_V)},         // Shift paste is pasteboard
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

#define EECONFIG_MACRO_START    (EEPROM_SIZE - 32)
#define EECONFIG_MACRO_SLOT_SIZE sizeof(uint32_t)
#define EECONFIG_MACRO_END      (EECONFIG_MACRO_START + 10 * EECONFIG_MACRO_SLOT_SIZE)
#define EEPROM_SIZE 2048
#define EECONFIG_MACRO 0x08080C00

static bool is_recording = false;
static uint16_t recording_buffer[32];
static uint8_t recording_index = 0;

uint32_t eeconfig_read_macro(uint8_t index) {
  if (index >= 10) {
    return 0;
  }
  uint32_t macro = 0;
  eeprom_read_block(&macro, (void*)(EECONFIG_MACRO_START + index * EECONFIG_MACRO_SLOT_SIZE), EECONFIG_MACRO_SLOT_SIZE);
  return macro;
}

void eeconfig_update_macro(uint8_t index, uint32_t macro) {
  if (index >= 10) {
    return;
  }
  eeprom_update_block(&macro, (void*)(EECONFIG_MACRO_START + index * EECONFIG_MACRO_SLOT_SIZE), EECONFIG_MACRO_SLOT_SIZE);
}

void del_macro(uint8_t macro_index) {
  if (macro_index >= 10) {
    return;
  }
  // Shift the existing macros down to remove the designated macro.
  for (uint8_t i = macro_index; i < 9; i++) {
    eeconfig_update_macro(i, eeconfig_read_macro(i + 1));
  }
  // Clear the last macro slot.
  eeconfig_update_macro(9, 0);
}

void process_macro(uint8_t macro_index) {
  // If the macro index is valid, loop through the corresponding macro and
  // send each key in turn.
  if (macro_index < 10) {
    uint16_t macro = eeconfig_read_macro(macro_index);
    printf("macro process");
    while (macro) {
      uint16_t keycode = macro & 0xFF;
      if (keycode) {
        register_code(keycode);
        unregister_code(keycode);
      }
      macro >>= 8;
    }
  }
}

void add_macro(uint8_t macro_index, const uint16_t *macro_buffer, uint8_t macro_length) {
  if (macro_index >= 10) {
    return;
  }
  // Shift the existing macros up to make room for the new macro.
  for (uint8_t i = 9; i > macro_index; i--) {
    eeconfig_update_macro(i, eeconfig_read_macro(i - 1));
  }
  // Save the new macro to the designated slot.
  uint32_t macro = 0;
  for (uint8_t i = 0; i < macro_length; i++) {
    macro |= ((uint32_t)macro_buffer[i]) << (i * 8);
  }
  eeconfig_update_macro(macro_index, macro);
}

int elapsed_time = 0;
uint8_t mod_state;
char* log_format          = "{\n\t\"kc\":\"0x%04X\",\n\t\"rw\":%2u,\n\t\"cl\":%2u,\n\t\"ly\":%u,\n\t\"md\":\"%02X\",\n\t\"om\":\"%02X\",\n\t\"tp\":%u,\n\t\"ts\":%5d\n}\n";
int   last_key_event_time = 0;


/*══════════════════════════════════════════════════════════════════════════════════════════════╗
     PROCESS RECORD USER                                                                        ║
 *══════════════════════════════════════════════════════════════════════════════════════════════╣           */

//  Callback function: runs every time a key is pressed or released
//      from 0000 to 7E00

bool process_record_user(uint16_t keycode, keyrecord_t* record) {

    mod_state = get_mods();

    uint32_t elapsed_time = timer_elapsed(last_key_event_time);
    last_key_event_time   = timer_read();
    uprintf(log_format, keycode, record->event.key.row, record->event.key.col, get_highest_layer(layer_state), get_mods(), get_oneshot_mods(), record->tap.count, (last_key_event_time + elapsed_time));


  static uint8_t selected_macro = 0;

  if (keycode == DM_REC && record->event.pressed) {
    if (is_recording && selected_macro) {
      // If we're already recording and a number key is pressed, stop recording.
      is_recording = false;
      del_macro(selected_macro - 1);
    } else {
      // If we're not already recording or a number key is not pressed, start recording.
      is_recording = true;
      recording_index = 0;
      selected_macro = 0;
    }
    return false;
  }

  if (keycode == DM_PLAY && record->event.pressed) {
    // If the user presses DM_PLAY and a number key, play the corresponding macro.
    if (selected_macro) {
      process_macro(selected_macro - 1);
    }
    return false;
  }

  if (is_recording && record->event.pressed) {
    // If we're recording and a key is pressed, add it to the recording buffer.
    if (recording_index < sizeof(recording_buffer) / sizeof(recording_buffer[0])) {
      recording_buffer[recording_index] = keycode;
      recording_index++;
    } else {
      // If the recording buffer is full, do nothing and type an elipsis
      // to indicate that the buffer is full.
        indicator();
    }
    return true;
  }

  // If the user presses a number key, select the corresponding macro.
  if (selected_macro && record->event.pressed && keycode >= KC_1 && keycode <= KC_0) {
    uint8_t new_macro_index = keycode - KC_1 + 1;
    if (selected_macro == new_macro_index) {
      // If the user presses the same number key while recording, stop recording
      // and save the macro to the corresponding slot.
      is_recording = false;
      add_macro(selected_macro - 1, recording_buffer, recording_index);
    } else {
      selected_macro = new_macro_index;
    }
    return false;
  }


#ifdef PROCESS_CUSTOM_SHIFT_KEYS
    if (!process_custom_shift_keys(keycode, record)) {
        uprintf("\n{\n\"SHIFTED\": {\n\t\"key\":%04x\n}\n\t}\n}\n", keycode);
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

uint8_t LAYER_STATE = 1;
uint8_t APP_STATE = 0;
uint8_t USER_VAR = 0;

layer_state_t layer_state_set_user(layer_state_t state) {

    switch (get_highest_layer(state)) {
        case _INSERT:
            LAYER_STATE = 0x01;
            break;
        case _NAVIGATE:
            LAYER_STATE = 0x02;
            break;
        case _NUMBERS:
            LAYER_STATE = 0x03;
            break;
        case _MACRO:
            LAYER_STATE = 0x04;
            break;
        default:
            break;
    }

    uprintf("\n{\n\tRAW SEND: {\n\t\tlayer:%u\n\t\tapp:%u\n\t\tuser:%u\n}\n", LAYER_STATE, APP_STATE, USER_VAR);

    {
        uint8_t data[] = {LAYER_STATE, APP_STATE, USER_VAR};
        raw_hid_send(data, sizeof(data));
    }

    return state;
}


/*══════════════════════════════════════════════════════════════════════════════════════════════╗
     KEYMAPS                                                                                    ║
 *══════════════════════════════════════════════════════════════════════════════════════════════╣           */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*══════════════════════════════════════════════════════════════════════════════════════════════╣
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
                               ║SHTAB║ TAB ║       ║/SPCE║LEADR║                                ║
                               ╚═════╩═════╝       ╚═════╩═════╝                                ║
                                                                                                ║        */
    [_INSERT] = LAYOUT(/* INSERT :0 ════════════════════════════════════════════════════════════╣        */
                    CLN_, CM_, DT_, P_,  Y_,        F_, G_, C_, R_, L_,
                    A_,   AO_, CE_, GU_, I_,        D_, H_, T_, N_, S_,
                    DQ_,  Q_,  J_,  K_,  X_,        B_, M_, W_, V_, Z_,

                               M_SHTAB, S_TAB,        N_SPC, QK_LEAD

    ),

/*══════════════════════════════════════════════════════════════════════════════════════════════╣
                        NAVIGATE:1                                                              ║
        ╔══════╦══════╦══════╦══════╦══════╗       ╔══════╦══════╦══════╦══════╦══════╗         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ╠══════╬══════╬══════╬══════╬══════╣       ╠══════╬══════╬══════╬══════╬══════╣         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ║      ║      ║      ║      ║      ║       ║      ║   ←  ║   ↓  ║   ↑  ║    → ║         ║
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

/*══════════════════════════════════════════════════════════════════════════════════════════════╣
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
                    ___, ___, ___, ___, ___,        DT_, _7, _8, _9, KC_LGUI,
                    ___, ___, ___, ___, ___,        _0,  _4, _5, _6, KC_LCTL,
                    ___, ___, ___, ___, ___,        CM_, _1, _2, _3, KC_LALT,

                            DM_REC, DM_PLAY,        MO(3), ___

    ),

/*══════════════════════════════════════════════════════════════════════════════════════════════╣
                        FUNCTION:3                                                              ║
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
    [_FUNCTION] = LAYOUT(/* FUNCTION :3 ════════════════════════════════════════════════════════╣        */
                    ___, ___, ___, ___, ___,        _F12, _F7, _F8, _F9, KC_LGUI,
                    ___, ___, ___, ___, ___,        _F10, _F4, _F5, _F6, KC_LCTL,
                    ___, ___, ___, ___, ___,        _F11, _F1, _F2, _F3, KC_LALT,

                                   ___, ___,        ___, ___

    ),

/*══════════════════════════════════════════════════════════════════════════════════════════════╣
                        MACRO:4                                                                 ║
        ╔══════╦══════╦══════╦══════╦══════╗       ╔══════╦══════╦══════╦══════╦══════╗         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ╠══════╬══════╬══════╬══════╬══════╣       ╠══════╬══════╬══════╬══════╬══════╣         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ║      ║      ║  M2  ║  M1  ║      ║       ║      ║      ║      ║      ║      ║         ║
        ╠══════╬══════╬══════╬══════╬══════╣       ╠══════╬══════╬══════╬══════╬══════╣         ║
        ║      ║      ║      ║      ║      ║       ║      ║      ║      ║      ║      ║         ║
        ║      ║      ║  M2R ║  M1R ║      ║       ║      ║      ║      ║      ║      ║         ║
        ╚══════╩══════╩══════╩══════╩══════╝       ╚══════╩══════╩══════╩══════╩══════╝         ║
                               ╔═════╦═════╗       ╔═════╦═════╗                                ║
                               ║     ║     ║       ║     ║     ║                                ║
                               ║     ║     ║       ║     ║     ║                                ║
                               ╚═════╩═════╝       ╚═════╩═════╝                                ║
                                                                                                ║        */
    [_MACRO] = LAYOUT(/*     MACRO :4 ══════════════════════════════════════════════════════════╣        */
             ___, ___, ___, ___, ___,              ___, ___, ___, ___, ___,
             ___, ___, DM_PLY2, DM_PLY1, ___,      ___, ___, ___, ___, ___,
             ___, ___, DM_REC2, DM_REC1, ___,      ___, ___, ___, ___, ___,

                                   ___, ___,        ___, ___

    )
/*══════════════════════════════════════════════════════════════════════════════════════════════╣
                                                                                         ║
 *══════════════════════════════════════════════════════════════════════════════════════════════╝        */
};
