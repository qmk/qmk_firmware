#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "../annepro2_ble_parser.h"

static const uint8_t connect_ack[] = {
    0x7B, 0x12, 0x35, 0x00, 0x03, 0x00, 0x00, 0x7D, 0x40, 0x04, 0x00,
};

static annepro2_ble_parse_event_t feed_bytes(annepro2_ble_parser_t *parser, const uint8_t *bytes, size_t count, uint32_t start, const uint8_t **frame, uint8_t *size) {
    annepro2_ble_parse_event_t event = ANNEPRO2_BLE_PARSE_NONE;
    for (size_t i = 0; i < count; i++) {
        event = annepro2_ble_parser_feed(parser, bytes[i], start + (uint32_t)i, frame, size);
    }
    return event;
}

static void test_valid_frame_and_noise(void) {
    annepro2_ble_parser_t parser;
    const uint8_t        *frame;
    uint8_t               size;

    annepro2_ble_parser_reset(&parser);
    assert(annepro2_ble_parser_feed(&parser, 0x00, 0, &frame, &size) == ANNEPRO2_BLE_PARSE_NONE);
    assert(feed_bytes(&parser, connect_ack, sizeof(connect_ack), 1, &frame, &size) == ANNEPRO2_BLE_PARSE_FRAME);
    assert(size == sizeof(connect_ack));
    assert(memcmp(frame, connect_ack, size) == 0);
    assert(parser.size == 0);
}

static void test_payload_may_contain_header_byte(void) {
    const uint8_t source[] = {
        0x7B, 0x12, 0x35, 0x00, 0x03, 0x00, 0x00, 0x7D, 0x20, 0x07, 0x7B,
    };
    annepro2_ble_parser_t parser;
    const uint8_t        *frame;
    uint8_t               size;

    annepro2_ble_parser_reset(&parser);
    assert(feed_bytes(&parser, source, sizeof(source), 0, &frame, &size) == ANNEPRO2_BLE_PARSE_FRAME);
    assert(size == sizeof(source));
    assert(memcmp(frame, source, size) == 0);
}

static void test_timeout_and_resynchronization(void) {
    annepro2_ble_parser_t parser;
    const uint8_t        *frame;
    uint8_t               size;

    annepro2_ble_parser_reset(&parser);
    assert(feed_bytes(&parser, connect_ack, 4, 100, &frame, &size) == ANNEPRO2_BLE_PARSE_NONE);
    assert(annepro2_ble_parser_feed(&parser, 0x7B, 123, &frame, &size) == ANNEPRO2_BLE_PARSE_TIMEOUT);
    assert(parser.size == 1);
    assert(feed_bytes(&parser, connect_ack + 1, sizeof(connect_ack) - 1, 124, &frame, &size) == ANNEPRO2_BLE_PARSE_FRAME);
    assert(memcmp(frame, connect_ack, size) == 0);

    annepro2_ble_parser_reset(&parser);
    assert(feed_bytes(&parser, connect_ack, 4, UINT32_MAX - 5, &frame, &size) == ANNEPRO2_BLE_PARSE_NONE);
    assert(!annepro2_ble_parser_expire(&parser, 10));
    assert(annepro2_ble_parser_expire(&parser, 18));
}

static void test_invalid_lengths(void) {
    uint8_t               invalid[sizeof(connect_ack)];
    annepro2_ble_parser_t parser;
    const uint8_t        *frame;
    uint8_t               size;

    memcpy(invalid, connect_ack, sizeof(invalid));
    invalid[4] = ANNEPRO2_BLE_RX_MAX_PAYLOAD + 1;
    annepro2_ble_parser_reset(&parser);
    assert(feed_bytes(&parser, invalid, 7, 0, &frame, &size) == ANNEPRO2_BLE_PARSE_INVALID_LENGTH);
    assert(parser.size == 0);

    memcpy(invalid, connect_ack, sizeof(invalid));
    invalid[5] = 1;
    annepro2_ble_parser_reset(&parser);
    assert(feed_bytes(&parser, invalid, 7, 0, &frame, &size) == ANNEPRO2_BLE_PARSE_INVALID_LENGTH);
    assert(parser.size == 0);

    memcpy(invalid, connect_ack, sizeof(invalid));
    invalid[6] = 1;
    annepro2_ble_parser_reset(&parser);
    assert(feed_bytes(&parser, invalid, 7, 0, &frame, &size) == ANNEPRO2_BLE_PARSE_INVALID_LENGTH);
    assert(parser.size == 0);
}

static void test_invalid_delimiter_and_zero_payload(void) {
    uint8_t               invalid[sizeof(connect_ack)];
    const uint8_t         empty[] = {0x7B, 0x12, 0x35, 0x00, 0x00, 0x00, 0x00, 0x7D};
    annepro2_ble_parser_t parser;
    const uint8_t        *frame;
    uint8_t               size;

    memcpy(invalid, connect_ack, sizeof(invalid));
    invalid[7] = 0;
    annepro2_ble_parser_reset(&parser);
    assert(feed_bytes(&parser, invalid, 8, 0, &frame, &size) == ANNEPRO2_BLE_PARSE_INVALID_DELIMITER);
    assert(parser.size == 0);

    assert(feed_bytes(&parser, empty, sizeof(empty), 20, &frame, &size) == ANNEPRO2_BLE_PARSE_FRAME);
    assert(size == sizeof(empty));
    assert(memcmp(frame, empty, size) == 0);
}

int main(void) {
    test_valid_frame_and_noise();
    test_payload_may_contain_header_byte();
    test_timeout_and_resynchronization();
    test_invalid_lengths();
    test_invalid_delimiter_and_zero_payload();
    return 0;
}
