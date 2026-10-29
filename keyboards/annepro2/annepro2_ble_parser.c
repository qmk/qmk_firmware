/*
 * Copyright 2026 BHE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#include "annepro2_ble_parser.h"

#include <string.h>

static uint32_t elapsed(uint32_t now, uint32_t then) {
    return now - then;
}

static void start_if_header(annepro2_ble_parser_t *parser, uint8_t byte, uint32_t now) {
    if (byte == 0x7B) {
        parser->frame[0]        = byte;
        parser->size            = 1;
        parser->last_byte_timer = now;
    }
}

void annepro2_ble_parser_reset(annepro2_ble_parser_t *parser) {
    memset(parser, 0, sizeof(*parser));
}

bool annepro2_ble_parser_expire(annepro2_ble_parser_t *parser, uint32_t now) {
    if (parser->size == 0 || elapsed(now, parser->last_byte_timer) < ANNEPRO2_BLE_RX_TIMEOUT) {
        return false;
    }

    parser->size          = 0;
    parser->expected_size = 0;
    return true;
}

annepro2_ble_parse_event_t annepro2_ble_parser_feed(annepro2_ble_parser_t *parser, uint8_t byte, uint32_t now, const uint8_t **frame, uint8_t *size) {
    *frame = NULL;
    *size  = 0;

    const bool timed_out = annepro2_ble_parser_expire(parser, now);
    if (parser->size == 0) {
        start_if_header(parser, byte, now);
        return timed_out ? ANNEPRO2_BLE_PARSE_TIMEOUT : ANNEPRO2_BLE_PARSE_NONE;
    }

    if (parser->size >= ANNEPRO2_BLE_RX_MAX_FRAME_SIZE) {
        parser->size          = 0;
        parser->expected_size = 0;
        start_if_header(parser, byte, now);
        return ANNEPRO2_BLE_PARSE_INVALID_LENGTH;
    }

    parser->frame[parser->size++] = byte;
    parser->last_byte_timer       = now;

    /*
     * Liana encodes payload length in bytes 4..6. Supported BLE UART frames
     * are small, so non-zero high bytes are corrupt rather than truncatable.
     */
    if (parser->size == 7) {
        const uint8_t payload_size = parser->frame[4];
        if (parser->frame[5] != 0 || parser->frame[6] != 0 || payload_size > ANNEPRO2_BLE_RX_MAX_PAYLOAD) {
            parser->size          = 0;
            parser->expected_size = 0;
            start_if_header(parser, byte, now);
            return ANNEPRO2_BLE_PARSE_INVALID_LENGTH;
        }
        parser->expected_size = ANNEPRO2_BLE_RX_HEADER_SIZE + payload_size;
    }

    if (parser->size == ANNEPRO2_BLE_RX_HEADER_SIZE && parser->frame[7] != 0x7D) {
        parser->size          = 0;
        parser->expected_size = 0;
        start_if_header(parser, byte, now);
        return ANNEPRO2_BLE_PARSE_INVALID_DELIMITER;
    }

    if (parser->expected_size != 0 && parser->size == parser->expected_size) {
        *frame                = parser->frame;
        *size                 = parser->size;
        parser->size          = 0;
        parser->expected_size = 0;
        return ANNEPRO2_BLE_PARSE_FRAME;
    }

    return timed_out ? ANNEPRO2_BLE_PARSE_TIMEOUT : ANNEPRO2_BLE_PARSE_NONE;
}
