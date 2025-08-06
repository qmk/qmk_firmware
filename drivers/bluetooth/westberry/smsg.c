// Copyright 2024 Su (@isuua)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "smsg.h"
#include <string.h>
#include <ch.h>

#ifndef SMSG_NUM
#    define SMSG_NUM 40
#endif

static smsg_message_t smsg_buffer[SMSG_NUM] __attribute__((aligned(PORT_NATURAL_ALIGN)));
static msg_t smsg_mailbox_buffer[SMSG_NUM];
static objects_fifo_t smsg_fifo;
static smsg_states_t smsg_state;

void smsg_init(void) {
    chFifoObjectInit(&smsg_fifo, sizeof(smsg_message_t), SMSG_NUM, smsg_buffer, smsg_mailbox_buffer);
    smsg_state = smsg_state_free;
}

smsg_message_t *smsg_take(void) {
    // Acquire a message to the pool
    return (smsg_message_t *)chFifoTakeObjectTimeout(&smsg_fifo, TIME_IMMEDIATE);
}


void smsg_return(smsg_message_t *msg) {
    // Return the current message to the pool
    if (msg != NULL) {
        chFifoReturnObject(&smsg_fifo, msg);
    }
}

void smsg_send(smsg_message_t *msg) {
    chFifoSendObject(&smsg_fifo, msg);
}

smsg_message_t *smsg_receive(void) {
    smsg_message_t *msg = NULL;
    msg_t result = chFifoReceiveObjectTimeout(&smsg_fifo, (void **)&msg, TIME_IMMEDIATE);
    if (result != MSG_OK) {
        return NULL;
    }
    return msg;
}

smsg_states_t smsg_get_state(void) {
    return smsg_state;
}

void smsg_set_state(smsg_states_t state) {
    smsg_state = state;
}

bool smsg_is_busy(void) {
    // Check if there are messages in the mailbox
    return (chMBGetUsedCountI(&smsg_fifo.mbx) > 0);
}
