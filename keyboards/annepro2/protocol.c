/*
 * (c) 2021 by Tomasz bla Fortuna
 * License: GPLv2
 *
 * This file is shared with the Shine firmware. Keep it in sync (and in the
 * shine's clang formatting).
 *
 * Implementation of a robust serial protocol which can handle single dropped
 * characters during transit without locking.
 *
 * At 115200, transmitting the shortest message takes 0.043ms, at 9600 - 0.52ms.
 *
 */

#include "protocol.h"
#include "board.h"
#include "ch.h"
#include "hal.h"

/* UART communication protocol state */
protocol_t proto;

void protoInit(protocol_t *proto, void (*callback)(const message_t *)) {
    proto->previousId = 0;
    proto->callback   = callback;
    proto->state      = STATE_SYNC_1;
    proto->errors     = 0;
}

static uint8_t msgId = 0;
void           protoTx(uint8_t cmd, const unsigned char *buf, int payloadSize, int retries) {
    chDbgCheck(payloadSize <= MAX_PAYLOAD_SIZE);

    const uint8_t header[5] = {
        0x7A, 0x1D, cmd, ++msgId, payloadSize,
    };

    /* We don't implement ACKs, yet some messages should not be lost. */
    for (int i = 0; i < retries; i++) {
        sdWrite(&PROTOCOL_SD, header, sizeof(header));
        if (payloadSize) sdWrite(&PROTOCOL_SD, buf, payloadSize);
    }
}

static inline void messageReceived(protocol_t *proto) {
    if (proto->buffer.msgId != proto->previousId) {
        /* It's not a resend / duplicate */
        proto->callback(&proto->buffer);
        proto->previousId = proto->buffer.msgId;
    }
    proto->state = STATE_SYNC_1;
}

void protoConsume(protocol_t *proto, uint8_t byte) {
    switch (proto->state) {
        case STATE_SYNC_1:
            if (byte == 0x7A) {
                proto->state = STATE_SYNC_2;
            } else {
                proto->errors++;
            }
            return;

        case STATE_SYNC_2:
            if (byte == 0x1D) {
                proto->state = STATE_CMD;
            } else {
                proto->state = STATE_SYNC_1;
                proto->errors++;
            }
            return;

        case STATE_CMD:
            proto->buffer.command = byte;
            proto->state          = STATE_ID;
            return;

        case STATE_ID:
            proto->buffer.msgId = byte;
            proto->state        = STATE_PAYLOAD_SIZE;
            return;

        case STATE_PAYLOAD_SIZE:
            proto->buffer.payloadSize = byte;
            if (proto->buffer.payloadSize > MAX_PAYLOAD_SIZE) {
                proto->buffer.payloadSize = MAX_PAYLOAD_SIZE;
                proto->errors++;
            }
            proto->payloadPosition = 0;
            if (proto->buffer.payloadSize == 0) {
                /* No payload - whole message received */
                messageReceived(proto);
            } else {
                proto->state = STATE_PAYLOAD;
            }
            return;

        case STATE_PAYLOAD:
            /* NOTE: This could be read with sdReadTimeout probably, but that breaks
             * abstraction */
            proto->buffer.payload[proto->payloadPosition] = byte;
            proto->payloadPosition++;
            if (proto->payloadPosition == proto->buffer.payloadSize) {
                /* Payload read - message received */
                messageReceived(proto);
            }
            return;
    }
}

void protoSilence(protocol_t *proto) {
    if (proto->state != STATE_SYNC_1) {
        proto->state = STATE_SYNC_1;
        proto->errors++;
    }
}
