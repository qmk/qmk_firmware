/* Copyright 2021
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

#include "send_string.h"

#include <ctype.h>
#include <stdlib.h>

#include "quantum_keycodes.h"
#include "keycode.h"
#include "action.h"
#include "wait.h"

#if defined(AUDIO_ENABLE) && defined(SENDSTRING_BELL)
#    include "audio.h"
#    ifndef BELL_SOUND
#        define BELL_SOUND TERMINAL_SOUND
#    endif
float bell_song[][2] = SONG(BELL_SOUND);
#endif

// clang-format off

/* Bit-Packed look-up table to convert an ASCII character to whether
 * [Shift] needs to be sent with the keycode.
 */
__attribute__((weak)) const uint8_t ascii_to_shift_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 1, 1, 1, 1, 1, 1, 0),
    KCLUT_ENTRY(1, 1, 1, 1, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 1, 0, 1, 0, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 1, 1, 1, 1, 1),
    KCLUT_ENTRY(1, 1, 1, 0, 0, 0, 1, 1),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 1, 1, 1, 1, 0)
};

/* Bit-Packed look-up table to convert an ASCII character to whether
 * [AltGr] needs to be sent with the keycode.
 */
__attribute__((weak)) const uint8_t ascii_to_altgr_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0)
};

/* Bit-Packed look-up table to convert an ASCII character to whether
 * [Space] needs to be sent after the keycode
 */
__attribute__((weak)) const uint8_t ascii_to_dead_lut[16] PROGMEM = {
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),

    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0),
    KCLUT_ENTRY(0, 0, 0, 0, 0, 0, 0, 0)
};

/* Look-up table to convert an ASCII character to a keycode.
 */
__attribute__((weak)) const uint8_t ascii_to_keycode_lut[128] PROGMEM = {
    // NUL   SOH      STX      ETX      EOT      ENQ      ACK      BEL
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // BS    TAB      LF       VT       FF       CR       SO       SI
    KC_BSPC, KC_TAB,  KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // DLE   DC1      DC2      DC3      DC4      NAK      SYN      ETB
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // CAN   EM       SUB      ESC      FS       GS       RS       US
    XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

    //       !        "        #        $        %        &        '
    KC_SPC,  KC_1,    KC_QUOT, KC_3,    KC_4,    KC_5,    KC_7,    KC_QUOT,
    // (     )        *        +        ,        -        .        /
    KC_9,    KC_0,    KC_8,    KC_EQL,  KC_COMM, KC_MINS, KC_DOT,  KC_SLSH,
    // 0     1        2        3        4        5        6        7
    KC_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
    // 8     9        :        ;        <        =        >        ?
    KC_8,    KC_9,    KC_SCLN, KC_SCLN, KC_COMM, KC_EQL,  KC_DOT,  KC_SLSH,
    // @     A        B        C        D        E        F        G
    KC_2,    KC_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,
    // H     I        J        K        L        M        N        O
    KC_H,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    // P     Q        R        S        T        U        V        W
    KC_P,    KC_Q,    KC_R,    KC_S,    KC_T,    KC_U,    KC_V,    KC_W,
    // X     Y        Z        [        \        ]        ^        _
    KC_X,    KC_Y,    KC_Z,    KC_LBRC, KC_BSLS, KC_RBRC, KC_6,    KC_MINS,
    // `     a        b        c        d        e        f        g
    KC_GRV,  KC_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,
    // h     i        j        k        l        m        n        o
    KC_H,    KC_I,    KC_J,    KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
    // p     q        r        s        t        u        v        w
    KC_P,    KC_Q,    KC_R,    KC_S,    KC_T,    KC_U,    KC_V,    KC_W,
    // x     y        z        {        |        }        ~        DEL
    KC_X,    KC_Y,    KC_Z,    KC_LBRC, KC_BSLS, KC_RBRC, KC_GRV,  KC_DEL
};

// clang-format on

// Note: we bit-pack in "reverse" order to optimize loading
#define PGM_LOADBIT(mem, pos) ((pgm_read_byte(&((mem)[(pos) / 8])) >> ((pos) % 8)) & 0x01)

void send_string(const char *string) {
    send_string_with_delay(string, TAP_CODE_DELAY);
}

void send_string_with_delay(const char *string, uint8_t interval) {
    while (1) {
        char ascii_code = *string;
        if (!ascii_code) break;
        if (ascii_code == SS_QMK_PREFIX) {
            ascii_code = *(++string);

            if (ascii_code == SS_TAP_CODE) {
                // tap
                uint8_t keycode = *(++string);
                tap_code(keycode);
            } else if (ascii_code == SS_DOWN_CODE) {
                // down
                uint8_t keycode = *(++string);
                register_code(keycode);
            } else if (ascii_code == SS_UP_CODE) {
                // up
                uint8_t keycode = *(++string);
                unregister_code(keycode);
            } else if (ascii_code == SS_DELAY_CODE) {
                // delay
                int     ms      = 0;
                uint8_t keycode = *(++string);

                while (isdigit(keycode)) {
                    ms *= 10;
                    ms += keycode - '0';
                    keycode = *(++string);
                }

                wait_ms(ms);
            }

            wait_ms(interval);
        } else {
            send_char_with_delay(ascii_code, interval);
        }

        ++string;
    }
}

void send_char(char ascii_code) {
    send_char_with_delay(ascii_code, TAP_CODE_DELAY);
}

void send_char_with_delay(char ascii_code, uint8_t interval) {
#if defined(AUDIO_ENABLE) && defined(SENDSTRING_BELL)
    if (ascii_code == '\a') { // BEL
        PLAY_SONG(bell_song);
        return;
    }
#endif

    uint8_t keycode    = pgm_read_byte(&ascii_to_keycode_lut[(uint8_t)ascii_code]);
    bool    is_shifted = PGM_LOADBIT(ascii_to_shift_lut, (uint8_t)ascii_code);
    bool    is_altgred = PGM_LOADBIT(ascii_to_altgr_lut, (uint8_t)ascii_code);
    bool    is_dead    = PGM_LOADBIT(ascii_to_dead_lut, (uint8_t)ascii_code);

    if (is_shifted) {
        register_code(KC_LEFT_SHIFT);
        wait_ms(interval);
    }

    if (is_altgred) {
        register_code(KC_RIGHT_ALT);
        wait_ms(interval);
    }

    tap_code_delay(keycode, interval);
    wait_ms(interval);

    if (is_altgred) {
        unregister_code(KC_RIGHT_ALT);
        wait_ms(interval);
    }

    if (is_shifted) {
        unregister_code(KC_LEFT_SHIFT);
        wait_ms(interval);
    }

    if (is_dead) {
        tap_code(KC_SPACE);
        wait_ms(interval);
    }
}

void send_dword(uint32_t number) {
    send_word(number >> 16);
    send_word(number & 0xFFFFUL);
}

void send_word(uint16_t number) {
    send_byte(number >> 8);
    send_byte(number & 0xFF);
}

void send_byte(uint8_t number) {
    send_nibble(number >> 4);
    send_nibble(number & 0xF);
}

void send_nibble(uint8_t number) {
    switch (number & 0xF) {
        case 0 ... 9:
            send_char(number + '0');
            break;
        case 10 ... 15:
            send_char(number - 10 + 'a');
            break;
    }
}

void tap_random_base64(void) {
#if defined(__AVR_ATmega32U4__)
    uint8_t key = (TCNT0 + TCNT1 + TCNT3 + TCNT4) % 64;
#else
    uint8_t key = rand() % 64;
#endif
    switch (key) {
        case 0 ... 25:
            send_char(key + 'A');
            break;
        case 26 ... 51:
            send_char(key - 26 + 'a');
            break;
        case 52:
            send_char('0');
            break;
        case 53 ... 61:
            send_char(key - 53 + '1');
            break;
        case 62:
            send_char('+');
            break;
        case 63:
            send_char('/');
            break;
    }
}

#if defined(__AVR__)
void send_string_P(const char *string) {
    send_string_with_delay_P(string, 0);
}

void send_string_with_delay_P(const char *string, uint8_t interval) {
    while (1) {
        char ascii_code = pgm_read_byte(string);
        if (!ascii_code) break;
        if (ascii_code == SS_QMK_PREFIX) {
            ascii_code = pgm_read_byte(++string);
            if (ascii_code == SS_TAP_CODE) {
                // tap
                uint8_t keycode = pgm_read_byte(++string);
                tap_code(keycode);
            } else if (ascii_code == SS_DOWN_CODE) {
                // down
                uint8_t keycode = pgm_read_byte(++string);
                register_code(keycode);
            } else if (ascii_code == SS_UP_CODE) {
                // up
                uint8_t keycode = pgm_read_byte(++string);
                unregister_code(keycode);
            } else if (ascii_code == SS_DELAY_CODE) {
                // delay
                int     ms      = 0;
                uint8_t keycode = pgm_read_byte(++string);
                while (isdigit(keycode)) {
                    ms *= 10;
                    ms += keycode - '0';
                    keycode = pgm_read_byte(++string);
                }
                while (ms--)
                    wait_ms(1);
            }
        } else {
            send_char(ascii_code);
        }
        ++string;
        // interval
        {
            uint8_t ms = interval;
            while (ms--)
                wait_ms(1);
        }
    }
}
#endif
