/*
 * Copyright 2026 BHE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#define ANNEPRO2_BLE_RX_HEADER_SIZE 8
#define ANNEPRO2_BLE_RX_MAX_PAYLOAD 32
#define ANNEPRO2_BLE_RX_MAX_FRAME_SIZE (ANNEPRO2_BLE_RX_HEADER_SIZE + ANNEPRO2_BLE_RX_MAX_PAYLOAD)

#ifndef ANNEPRO2_BLE_RX_TIMEOUT
#    define ANNEPRO2_BLE_RX_TIMEOUT 20
#endif

typedef enum {
    ANNEPRO2_BLE_PARSE_NONE,
    ANNEPRO2_BLE_PARSE_FRAME,
    ANNEPRO2_BLE_PARSE_TIMEOUT,
    ANNEPRO2_BLE_PARSE_INVALID_LENGTH,
    ANNEPRO2_BLE_PARSE_INVALID_DELIMITER,
} annepro2_ble_parse_event_t;

typedef struct {
    uint8_t  frame[ANNEPRO2_BLE_RX_MAX_FRAME_SIZE];
    uint8_t  size;
    uint8_t  expected_size;
    uint32_t last_byte_timer;
} annepro2_ble_parser_t;

void annepro2_ble_parser_reset(annepro2_ble_parser_t *parser);

/*
 * Feed one UART byte. A returned frame points into parser storage and remains
 * valid until the next feed call.
 */
annepro2_ble_parse_event_t annepro2_ble_parser_feed(annepro2_ble_parser_t *parser, uint8_t byte, uint32_t now, const uint8_t **frame, uint8_t *size);

/* Drop a stale partial frame when no new UART byte arrives. */
bool annepro2_ble_parser_expire(annepro2_ble_parser_t *parser, uint32_t now);
