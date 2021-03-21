/* Copyright 2020 Ilya Zhuravlev
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

#include "vial.h"

#include <string.h>

#include "dynamic_keymap.h"
#include "quantum.h"
#include "vial_generated_keyboard_definition.h"

#include "vial_ensure_keycode.h"

#define VIAL_UNLOCK_COUNTER_MAX 50

#ifdef VIAL_INSECURE
#pragma message "Building Vial-enabled firmware in insecure mode."
int vial_unlocked = 1;
#else
int vial_unlocked = 0;
#endif
int vial_unlock_in_progress = 0;
static int vial_unlock_counter = 0;
static uint16_t vial_unlock_timer;

#ifndef VIAL_INSECURE
static uint8_t vial_unlock_combo_rows[] = VIAL_UNLOCK_COMBO_ROWS;
static uint8_t vial_unlock_combo_cols[] = VIAL_UNLOCK_COMBO_COLS;
#define VIAL_UNLOCK_NUM_KEYS (sizeof(vial_unlock_combo_rows)/sizeof(vial_unlock_combo_rows[0]))
_Static_assert(VIAL_UNLOCK_NUM_KEYS < 15, "Max 15 unlock keys");
_Static_assert(sizeof(vial_unlock_combo_rows) == sizeof(vial_unlock_combo_cols), "The number of unlock cols and rows should be the same");
#endif

#define VIAL_RAW_EPSIZE 32

#ifndef VIAL_ENCODER_KEYCODE_DELAY
#define VIAL_ENCODER_KEYCODE_DELAY 10
#endif

void vial_handle_cmd(uint8_t *msg, uint8_t length) {
    /* All packets must be fixed 32 bytes */
    if (length != VIAL_RAW_EPSIZE)
        return;

    /* msg[0] is 0xFE -- prefix vial magic */
    switch (msg[1]) {
        /* Get keyboard ID and Vial protocol version */
        case vial_get_keyboard_id: {
            uint8_t keyboard_uid[] = VIAL_KEYBOARD_UID;

            msg[0] = VIAL_PROTOCOL_VERSION & 0xFF;
            msg[1] = (VIAL_PROTOCOL_VERSION >> 8) & 0xFF;
            msg[2] = (VIAL_PROTOCOL_VERSION >> 16) & 0xFF;
            msg[3] = (VIAL_PROTOCOL_VERSION >> 24) & 0xFF;
            memcpy(&msg[4], keyboard_uid, 8);
            break;
        }
        /* Retrieve keyboard definition size */
        case vial_get_size: {
            uint32_t sz = sizeof(keyboard_definition);
            msg[0] = sz & 0xFF;
            msg[1] = (sz >> 8) & 0xFF;
            msg[2] = (sz >> 16) & 0xFF;
            msg[3] = (sz >> 24) & 0xFF;
            break;
        }
        /* Retrieve 32-bytes block of the definition, page ID encoded within 2 bytes */
        case vial_get_def: {
            uint32_t page = msg[2] + (msg[3] << 8);
            uint32_t start = page * VIAL_RAW_EPSIZE;
            uint32_t end = start + VIAL_RAW_EPSIZE;
            if (end < start || start >= sizeof(keyboard_definition))
                return;
            if (end > sizeof(keyboard_definition))
                end = sizeof(keyboard_definition);
            memcpy_P(msg, &keyboard_definition[start], end - start);
            break;
        }
#ifdef VIAL_ENCODERS_ENABLE
        case vial_get_encoder: {
            uint8_t layer = msg[2];
            uint8_t idx = msg[3];
            uint16_t keycode = dynamic_keymap_get_encoder(layer, idx, 0);
            msg[0]  = keycode >> 8;
            msg[1]  = keycode & 0xFF;
            keycode = dynamic_keymap_get_encoder(layer, idx, 1);
            msg[2] = keycode >> 8;
            msg[3] = keycode & 0xFF;
            break;
        }
        case vial_set_encoder: {
            dynamic_keymap_set_encoder(msg[2], msg[3], msg[4], (msg[5] << 8) | msg[6]);
            break;
        }
#endif
        case vial_get_unlock_status: {
            /* Reset message to all FF's */
            memset(msg, 0xFF, length);
            /* First byte of message contains the status: whether board is unlocked */
            msg[0] = vial_unlocked;
            /* Second byte is whether unlock is in progress */
            msg[1] = vial_unlock_in_progress;
#ifndef VIAL_INSECURE
            /* Rest of the message are keys in the matrix that should be held to unlock the board */
            for (size_t i = 0; i < VIAL_UNLOCK_NUM_KEYS; ++i) {
                msg[2 + i * 2] = vial_unlock_combo_rows[i];
                msg[2 + i * 2 + 1] = vial_unlock_combo_cols[i];
            }
#endif
            break;
        }
        case vial_unlock_start: {
            vial_unlock_in_progress = 1;
            vial_unlock_counter = VIAL_UNLOCK_COUNTER_MAX;
            vial_unlock_timer = timer_read();
            break;
        }
        case vial_unlock_poll: {
#ifndef VIAL_INSECURE
            if (vial_unlock_in_progress) {
                int holding = 1;
                for (size_t i = 0; i < VIAL_UNLOCK_NUM_KEYS; ++i)
                    holding &= matrix_is_on(vial_unlock_combo_rows[i], vial_unlock_combo_cols[i]);

                if (timer_elapsed(vial_unlock_timer) > 100 && holding) {
                    vial_unlock_timer = timer_read();

                    vial_unlock_counter--;
                    if (vial_unlock_counter == 0) {
                        /* ok unlock succeeded */
                        vial_unlock_in_progress = 0;
                        vial_unlocked = 1;
                    }
                } else {
                    vial_unlock_counter = VIAL_UNLOCK_COUNTER_MAX;
                }
            }
#endif
            msg[0] = vial_unlocked;
            msg[1] = vial_unlock_in_progress;
            msg[2] = vial_unlock_counter;
            break;
        }
        case vial_lock: {
#ifndef VIAL_INSECURE
            vial_unlocked = 0;
#endif
            break;
        }
    }
}

#ifdef VIAL_ENCODERS_ENABLE
uint16_t g_vial_magic_keycode_override;

static void exec_keycode(uint16_t keycode) {
#ifdef VIAL_ENCODER_SIMPLE_TAP
    register_code16(keycode);
#if VIAL_ENCODER_KEYCODE_DELAY > 0
    wait_ms(VIAL_ENCODER_KEYCODE_DELAY);
#endif
    unregister_code16(keycode);
#else
    g_vial_magic_keycode_override = keycode;

    keyrecord_t record = {.event = (keyevent_t){.key = { VIAL_ENCODER_MATRIX_MAGIC, VIAL_ENCODER_MATRIX_MAGIC }, .pressed = true, .time = (timer_read() | 1)}};

    if (keycode <= QK_MODS_MAX)
        register_code16(keycode);
    else
        process_record_quantum_helper(keycode, &record);

#if VIAL_ENCODER_KEYCODE_DELAY > 0
    wait_ms(VIAL_ENCODER_KEYCODE_DELAY);
#endif
    record.event.time = timer_read() | 1;
    record.event.pressed = false;

    if (keycode <= QK_MODS_MAX)
        unregister_code16(keycode);
    else
        process_record_quantum_helper(keycode, &record);
#endif
}

void vial_encoder_update(uint8_t index, bool clockwise) {
    uint16_t code;

    layer_state_t layers = layer_state | default_layer_state;
    /* check top layer first */
    for (int8_t i = MAX_LAYER - 1; i >= 0; i--) {
        if (layers & (1UL << i)) {
            code = dynamic_keymap_get_encoder(i, index, clockwise);
            if (code != KC_TRNS) {
                exec_keycode(code);
                return;
            }
        }
    }
    /* fall back to layer 0 */
    code = dynamic_keymap_get_encoder(0, index, clockwise);
    exec_keycode(code);
}
#endif
