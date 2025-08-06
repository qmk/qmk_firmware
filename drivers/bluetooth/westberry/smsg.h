// Copyright 2025 emolitor (github.com/emolitor)
// Copyright 2024 Su (@isuua)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifndef SMSG_PAYLOAD_LEN
#    define SMSG_PAYLOAD_LEN 50
#endif

typedef struct {
    uint8_t  data[SMSG_PAYLOAD_LEN];
    uint32_t size;
} smsg_message_t;

typedef enum { smsg_state_free = 0, smsg_state_busy, smsg_state_retry, smsg_state_replied } smsg_states_t;

void            smsg_init(void);
smsg_message_t *smsg_take(void);
void            smsg_return(smsg_message_t *msg);
void            smsg_send(smsg_message_t *msg);
smsg_message_t *smsg_receive(void);
smsg_states_t   smsg_get_state(void);
void            smsg_set_state(smsg_states_t state);
bool            smsg_is_busy(void);
