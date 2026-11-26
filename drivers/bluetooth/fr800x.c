// Copyright 2026 Roman Kuzmitskii (@damex)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * Tested on Freqchip FR8003A (FR800x family). UART sniffed using Miniware LA104.
 */

#include <assert.h>

#include "quantum.h"
#include "fr800x.h"

#ifndef FR800X_BLUETOOTH_PAIRING_TIMEOUT_MS
#    define FR800X_BLUETOOTH_PAIRING_TIMEOUT_MS 30000 /* BLE pairing waits on host passkey confirmation */
#endif

#define FR800X_BLUETOOTH_COMMAND_SEND_DEVICE_INFORMATION    0xA9
#define FR800X_BLUETOOTH_COMMAND_DEVICE_INFORMATION_LENGTH  18

#define FR800X_BLUETOOTH_COMMAND_DEVICE_CONTROL_SLOT1     0x31
#define FR800X_BLUETOOTH_COMMAND_DEVICE_CONTROL_SLOT2     0x32
#define FR800X_BLUETOOTH_COMMAND_DEVICE_CONTROL_SLOT3     0x33

/*
 * Packet: opcode 0xA9, length byte, device name bytes, checksum.
 * PRODUCT expands to "NUT65", 5 bytes.
 * Queued packet: A9 05 4E 55 54 36 35 10
 */
static void fr800x_bluetooth_send_device_information(const char *name) {
    assert(name != NULL);
    uint8_t packet_buffer[FR800X_LENGTH_PREFIXED_PACKET_HEADER_SIZE + FR800X_BLUETOOTH_COMMAND_DEVICE_INFORMATION_LENGTH + FR800X_PACKET_CHECKSUM_SIZE] = {0};
    size_t  full_length                                                                                            = strlen(name);

    assert(full_length <= FR800X_BLUETOOTH_COMMAND_DEVICE_INFORMATION_LENGTH);
    uint8_t name_length = (uint8_t)full_length;

    fr800x_length_prefixed_packet_t *packet = (fr800x_length_prefixed_packet_t *)packet_buffer;
    packet->opcode = FR800X_BLUETOOTH_COMMAND_SEND_DEVICE_INFORMATION;
    packet->length = name_length;
    memcpy(packet->payload, name, name_length);
    fr800x_packet_append_checksum(packet_buffer, FR800X_LENGTH_PREFIXED_PACKET_HEADER_SIZE + name_length);
    fr800x_queue_push(packet_buffer, FR800X_LENGTH_PREFIXED_PACKET_HEADER_SIZE + name_length + FR800X_PACKET_CHECKSUM_SIZE);
}

static const uint8_t bluetooth_pair_slot_commands[] = {
    FR800X_BLUETOOTH_COMMAND_DEVICE_CONTROL_SLOT1,
    FR800X_BLUETOOTH_COMMAND_DEVICE_CONTROL_SLOT2,
    FR800X_BLUETOOTH_COMMAND_DEVICE_CONTROL_SLOT3,
};

void fr800x_bluetooth_slot_select(uint8_t slot, bool reset) {
    if (slot >= ARRAY_SIZE(bluetooth_pair_slot_commands)) {
        return;
    }
    fr800x_send_device_control(bluetooth_pair_slot_commands[slot]);

    if (reset) {
        fr800x_send_device_control(FR800X_COMMAND_DEVICE_CONTROL_CLEAN);
        fr800x_bluetooth_send_device_information(PRODUCT);
        fr800x_send_device_control(FR800X_COMMAND_DEVICE_CONTROL_PAIR);
    }
}

void bluetooth_init(void) {
    fr800x_init();
    for (fr800x_target_t target = FR800X_TARGET_BLUETOOTH1; target <= FR800X_TARGET_BLUETOOTH3; target++) {
        fr800x_target_set_pairing_timeout(target, FR800X_BLUETOOTH_PAIRING_TIMEOUT_MS);
    }
}

void bluetooth_task(void) {
    fr800x_task();
}

static uint8_t bluetooth_current_profile = 0;

uint8_t bluetooth_get_max_profile(void) {
    return FR800X_BLUETOOTH_PROFILE_COUNT;
}

bool bluetooth_set_profile(uint8_t profile) {
    if (profile >= FR800X_BLUETOOTH_PROFILE_COUNT) {
        return false;
    }
    bluetooth_current_profile = profile;
    return true;
}

uint8_t bluetooth_get_profile(void) {
    return bluetooth_current_profile;
}

/* Switches active target to the current bluetooth slot: chip must be on that slot to receive CLEAN+PAIR. */
void bluetooth_unpair(void) {
    fr800x_target_change(fr800x_target_from_bluetooth_profile(bluetooth_current_profile), true);
}

bool bluetooth_is_connected(void) {
    return fr800x_target_is_bluetooth(fr800x_target_get_current()) && fr800x_get_state() == FR800X_STATE_CONNECTED;
}

bool bluetooth_can_send_nkro(void) {
    return true;
}

uint8_t bluetooth_keyboard_leds(void) {
    return fr800x_keyboard_leds();
}

void bluetooth_send_keyboard(report_keyboard_t *report) {
    fr800x_route_keyboard(report);
}

void bluetooth_send_nkro(report_nkro_t *report) {
    fr800x_route_nkro(report);
}

void bluetooth_send_consumer(uint16_t usage) {
    fr800x_route_consumer(usage);
}

void bluetooth_send_system(uint16_t usage) {
    fr800x_route_system(usage);
}
