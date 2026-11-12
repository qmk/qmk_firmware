// Copyright 2026 Roman Kuzmitskii (@damex)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * Tested on Freqchip FR8003A (FR800x family). UART sniffed using Miniware LA104.
 */

#include <assert.h>

#include "quantum.h"
#include "wireless_2p4ghz.h"
#include "fr800x.h"

#ifndef FR800X_DONGLE_PAIRING_TIMEOUT_MS
#    define FR800X_DONGLE_PAIRING_TIMEOUT_MS 5000 /* 2.4G pairing is chip-dongle only, no user confirmation */
#endif

#ifndef FR800X_DONGLE_LINK_PROBE_INTERVAL_MS
#    define FR800X_DONGLE_LINK_PROBE_INTERVAL_MS 5000 /* chip's 2.4G stack does not self-detect dongle loss */
#endif

#define FR800X_DONGLE_COMMAND_DESCRIPTOR_LENGTH   46
#define FR800X_DONGLE_COMMAND_MANUFACTURER         0xAB
#define FR800X_DONGLE_COMMAND_PRODUCT              0xAC
#define FR800X_DONGLE_COMMAND_VENDOR_PRODUCT_ID    0xAD

#define USBCONCAT(a, b) a##b
#define USBSTR(s) USBCONCAT(L, s)

/*
 * Packet: opcode (0xAB manufacturer or 0xAC product), length byte, UTF-16LE descriptor bytes, checksum.
 * MANUFACTURER expands to L"Weikav\0", 14 bytes in UTF-16LE.
 * Manufacturer packet: AB 0E 57 00 65 00 69 00 6B 00 61 00 76 00 00 00 20
 * PRODUCT expands to L"NUT65\0", 12 bytes in UTF-16LE.
 * Product packet: AC 0C 4E 00 55 00 54 00 36 00 35 00 00 00 1A
 */
static void fr800x_dongle_send_descriptor(uint8_t opcode, const char *descriptor, uint8_t length) {
    assert(descriptor != NULL);
    assert(length <= FR800X_DONGLE_COMMAND_DESCRIPTOR_LENGTH);
    uint8_t packet_buffer[FR800X_LENGTH_PREFIXED_PACKET_HEADER_SIZE + FR800X_DONGLE_COMMAND_DESCRIPTOR_LENGTH + FR800X_PACKET_CHECKSUM_SIZE] = {0};

    fr800x_length_prefixed_packet_t *packet = (fr800x_length_prefixed_packet_t *)packet_buffer;
    packet->opcode = opcode;
    packet->length = length;
    memcpy(packet->payload, descriptor, length);
    fr800x_packet_append_checksum(packet_buffer, FR800X_LENGTH_PREFIXED_PACKET_HEADER_SIZE + length);
    fr800x_queue_push(packet_buffer, FR800X_LENGTH_PREFIXED_PACKET_HEADER_SIZE + length + FR800X_PACKET_CHECKSUM_SIZE);
}

/*
 * Packet: opcode 0xAD, vendor_id (little-endian), product_id (little-endian), checksum.
 * vendor_id=0x342D, product_id=0xE51A gives: AD 2D 34 1A E5 0D
 */
typedef struct __attribute__((packed)) {
    uint8_t  opcode;
    uint16_t vendor_id;
    uint16_t product_id;
} fr800x_dongle_vendor_product_id_packet_t;

static void fr800x_dongle_send_vendor_product_id(uint16_t vendor_id, uint16_t product_id) {
    uint8_t packet_buffer[sizeof(fr800x_dongle_vendor_product_id_packet_t) + FR800X_PACKET_CHECKSUM_SIZE] = {0};
    fr800x_dongle_vendor_product_id_packet_t *packet = (fr800x_dongle_vendor_product_id_packet_t *)packet_buffer;
    packet->opcode     = FR800X_DONGLE_COMMAND_VENDOR_PRODUCT_ID;
    packet->vendor_id  = vendor_id;
    packet->product_id = product_id;
    fr800x_packet_append_checksum(packet_buffer, sizeof(*packet));
    fr800x_queue_push(packet_buffer, sizeof(packet_buffer));
}

static void fr800x_dongle_connect(void) {
    fr800x_dongle_send_descriptor(FR800X_DONGLE_COMMAND_MANUFACTURER, (char *)USBSTR(MANUFACTURER), sizeof(USBSTR(MANUFACTURER)));
    fr800x_dongle_send_descriptor(FR800X_DONGLE_COMMAND_PRODUCT, (char *)USBSTR(PRODUCT), sizeof(USBSTR(PRODUCT)));
    fr800x_dongle_send_vendor_product_id(VENDOR_ID, PRODUCT_ID);
}

void fr800x_dongle_select(bool reset) {
    fr800x_send_device_control(FR800X_COMMAND_DEVICE_CONTROL_DONGLE);
    /* Descriptors prime the chip's 2.4G stack for reliable link monitoring on first-after-boot
     * switches; chip otherwise enters DONGLE mode with incomplete state. */
    fr800x_dongle_connect();
    if (reset) {
        fr800x_send_device_control(FR800X_COMMAND_DEVICE_CONTROL_CLEAN);
        fr800x_send_device_control(FR800X_COMMAND_DEVICE_CONTROL_PAIR);
    }
}

void wireless_2p4ghz_init(void) {
    fr800x_init();
    fr800x_target_set_pairing_timeout(FR800X_TARGET_DONGLE, FR800X_DONGLE_PAIRING_TIMEOUT_MS);
    fr800x_target_set_probe_interval(FR800X_TARGET_DONGLE, FR800X_DONGLE_LINK_PROBE_INTERVAL_MS);
}

void wireless_2p4ghz_task(void) {
    fr800x_task();
}

bool wireless_2p4ghz_is_connected(void) {
    return fr800x_target_get_current() == FR800X_TARGET_DONGLE && fr800x_get_state() == FR800X_STATE_CONNECTED;
}

/* Switches active target to DONGLE: chip must be on dongle slot to receive CLEAN+PAIR. */
void wireless_2p4ghz_unpair(void) {
    fr800x_target_change(FR800X_TARGET_DONGLE, true);
}

bool wireless_2p4ghz_can_send_nkro(void) {
    return true;
}

uint8_t wireless_2p4ghz_keyboard_leds(void) {
    return fr800x_keyboard_leds();
}

void wireless_2p4ghz_send_keyboard(report_keyboard_t *report) {
    fr800x_route_keyboard(report);
}

void wireless_2p4ghz_send_nkro(report_nkro_t *report) {
    fr800x_route_nkro(report);
}

void wireless_2p4ghz_send_consumer(uint16_t usage) {
    fr800x_route_consumer(usage);
}

void wireless_2p4ghz_send_system(uint16_t usage) {
    fr800x_route_system(usage);
}
