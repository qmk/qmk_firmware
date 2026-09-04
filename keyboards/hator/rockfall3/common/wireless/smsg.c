/* Copyright (C) 2024 koosikus
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

#include "smsg.h"
#include <string.h>

#ifndef SMSG_NUM
#    define SMSG_NUM 40
#endif

#ifndef SMSG_PAYLOAD_LEN
#    define SMSG_PAYLOAD_LEN 50
#endif

#define SMSG_BUF_SIZE (SMSG_NUM * SMSG_PAYLOAD_LEN)
#define END_PTR ((smsg_ptr_t *)&smsg_instance.ptr[SMSG_NUM - 1])
#define FREE_SPACE ((uint32_t)(&smsg_buffer[SMSG_BUF_SIZE - 1] - smsg_instance.buffer))

typedef struct {
    uint8_t *head;
    uint8_t *tail;
} smsg_ptr_t;

typedef struct {
    smsg_states_t state;
    smsg_ptr_t *ptr;
    smsg_ptr_t *in_ptr;
    smsg_ptr_t *out_ptr;
    uint8_t *buffer;
} smsg_t;

static smsg_ptr_t smsg_ptr[SMSG_NUM];
static uint8_t smsg_buffer[SMSG_BUF_SIZE];
static smsg_t smsg_instance;

void smsg_init(void) {

    smsg_instance.buffer    = smsg_buffer;
    smsg_instance.ptr       = smsg_ptr;
    smsg_instance.ptr->head = smsg_instance.buffer;
    smsg_instance.ptr->tail = smsg_instance.buffer;
    smsg_instance.in_ptr    = smsg_instance.ptr;
    smsg_instance.out_ptr   = smsg_instance.ptr;
    smsg_instance.state     = smsg_state_free;
}

bool smsg_push(uint8_t *buf, uint32_t size) {

    if (smsg_instance.in_ptr == END_PTR) {
        if (smsg_instance.ptr == smsg_instance.out_ptr) {
            return false;
        }
    } else {
        if ((smsg_instance.in_ptr + 1) == smsg_instance.out_ptr) {
            return false;
        }
    }

    if (FREE_SPACE < SMSG_PAYLOAD_LEN) {
        smsg_instance.buffer = smsg_buffer;
    }

    if (size > SMSG_PAYLOAD_LEN) {
        return false;
    }

    memcpy(smsg_instance.buffer, buf, size);
    smsg_instance.in_ptr->head = smsg_instance.buffer;
    smsg_instance.buffer += size;
    smsg_instance.in_ptr->tail = smsg_instance.buffer;
    if (smsg_instance.in_ptr == END_PTR) {
        smsg_instance.in_ptr = smsg_instance.ptr;
    } else {
        smsg_instance.in_ptr++;
    }

    return true;
}

uint32_t smsg_peek(uint8_t *buf) {

    if (smsg_instance.out_ptr != smsg_instance.in_ptr) {
        uint32_t size;

        size = smsg_instance.out_ptr->tail - smsg_instance.out_ptr->head;
        memcpy(buf, smsg_instance.out_ptr->head, size);

        return size;
    }

    return 0;
}

void smsg_pop(void) {

    if (smsg_instance.out_ptr != smsg_instance.in_ptr) {
        if (smsg_instance.out_ptr == END_PTR) {
            smsg_instance.out_ptr = smsg_instance.ptr;
        } else {
            smsg_instance.out_ptr++;
        }
    }
}

smsg_states_t smsg_get_state(void) {

    return smsg_instance.state;
}

void smsg_set_state(smsg_states_t state) {

    smsg_instance.state = state;
}

bool smsg_is_busy(void) {

    if (smsg_instance.out_ptr != smsg_instance.in_ptr) {
        return true;
    }

    return false;
}
