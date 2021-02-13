/* Copyright 2020 encg
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

#include QMK_KEYBOARD_H
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

enum my_keycodes {
    SPIN = SAFE_RANGE,
    RULES,
};

enum unicode_names {
    COW,
    BTTR,
    CHIKN,
    FISH,
    SEED,
    RENV,
    MBAG,
    FACE,
    WING,
    SIGN,
    WAVE
};

const uint32_t PROGMEM unicode_map[] = {
    [COW]   = 0x1F404,  // 🐄
    [BTTR]  = 0x1F9C8,  // 🧈
    [CHIKN] = 0x1F414,  // 🐔
    [FISH]  = 0x1F3A3,  // 🎣
    [SEED]  = 0x1F331,  // 🌱
    [RENV]  = 0x1F9E7,  // 🧧
    [MBAG]  = 0x1F4B0,  // 💰
    [FACE]  = 0x1F911,  // 🤑
    [WING]  = 0x1F4B8,  // 💸
    [SIGN]  = 0x1F4B2,  // 💲
    [WAVE]  = 0x1F44B,  // 👋
};

/* Emojis stored in an array in order to be randomly accessed */
const char* emoji[5] = {"🐄", "🧈", "🐔", "🎣", "🌱"};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPIN:
            if (record->event.pressed) {
                /* Seed RNG used by rand() with timer_read() https://beta.docs.qmk.fm/developing-qmk/qmk-reference/ref_functions#software-timers */
                srand(timer_read());
                int rng1 = rand() % 5; 
                send_unicode_string(emoji[rng1]);
                wait_ms(200);    
                int rng2 = rand() % 5;
                send_unicode_string(emoji[rng2]);
                wait_ms(200);
                int rng3 = rand() % 5;
                send_unicode_string(emoji[rng3]);
                wait_ms(200);
                    if (rng1 == rng2 && rng1 == rng3) {
                        if (rng1 == 0) {
                            wait_ms(200);
                            SEND_STRING("   ");
                            send_unicode_string("🧧🧧🧧");
                            wait_ms(200);
                            SEND_STRING("\n");
                          } else if (rng1 == 1) {
                            wait_ms(200);
                            SEND_STRING("   ");
                            send_unicode_string("💰💰💰");
                            wait_ms(200);
                            SEND_STRING("\n");
                          } else if (rng1 == 2) {
                            wait_ms(200);
                            SEND_STRING("   ");
                            send_unicode_string("🤑🤑🤑");
                            wait_ms(200);
                            SEND_STRING("\n");
                          } else if (rng1 == 3) {
                            wait_ms(200);
                            SEND_STRING("   ");
                            send_unicode_string("💲💲💲");
                            wait_ms(200);
                            SEND_STRING("\n");
                          } else if (rng1 == 4) {
                            wait_ms(200);
                            SEND_STRING("   ");
                            send_unicode_string("📈📈📈");
                            wait_ms(200);
                            SEND_STRING("\n");
                        }
                    } else {
                          SEND_STRING("   ");
                          send_unicode_string("👋💸");
                          SEND_STRING("\n");
                    }
      }
            return false;
            break;
        case RULES:
            if (record->event.pressed) {
                send_unicode_string("🐄");
                wait_ms(200);
                send_unicode_string("🐄");
                wait_ms(200);
                send_unicode_string("🐄");
                wait_ms(200);
                SEND_STRING("   ");
                send_unicode_string("🧧");
                wait_ms(200);
                send_unicode_string("🧧");
                wait_ms(200);
                send_unicode_string("🧧");
                SEND_STRING("\n");
                wait_ms(100);
                send_unicode_string("🧈");
                wait_ms(200);
                send_unicode_string("🧈");
                wait_ms(200);
                send_unicode_string("🧈");
                wait_ms(200);
                SEND_STRING("   ");
                send_unicode_string("💰");
                wait_ms(200);
                send_unicode_string("💰");
                wait_ms(200);
                send_unicode_string("💰");
                SEND_STRING("\n");
                wait_ms(100);
                send_unicode_string("🐔");
                wait_ms(200);
                send_unicode_string("🐔");
                wait_ms(200);
                send_unicode_string("🐔");
                wait_ms(200);
                SEND_STRING("   ");
                send_unicode_string("🤑");
                wait_ms(200);
                send_unicode_string("🤑");
                wait_ms(200);
                send_unicode_string("🤑");
                SEND_STRING("\n");
                wait_ms(100);
                send_unicode_string("🎣");
                wait_ms(200);
                send_unicode_string("🎣");
                wait_ms(200);
                send_unicode_string("🎣");
                wait_ms(200);
                SEND_STRING("   ");
                send_unicode_string("💲");
                wait_ms(200);
                send_unicode_string("💲");
                wait_ms(200);
                send_unicode_string("💲");
                SEND_STRING("\n");
                wait_ms(100);
                send_unicode_string("🌱");
                wait_ms(200);
                send_unicode_string("🌱");
                wait_ms(200);
                send_unicode_string("🌱");
                wait_ms(200);
                SEND_STRING("   ");
                send_unicode_string("📈");
                wait_ms(200);
                send_unicode_string("📈");
                wait_ms(200);
                send_unicode_string("📈");
                SEND_STRING("\n\n");
            }
            return false;
            break;    
            }
    return false;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        SPIN, /* bottom button */
        RULES /* top button */
    )
};
