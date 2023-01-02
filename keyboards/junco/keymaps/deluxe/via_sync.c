// Copyright 2022 Dane Skalski (@Daneski13)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "via_sync.h"
#include "transactions.h"
#include "print.h"

typedef struct {
    // The address that was read from
    uint32_t addr;
    // The 20 bytes of data that was read
    uint8_t data[20];
    // How many of those 20 bytes should be updated
    uint8_t num_bytes;
} via_sync_packet_t;

// How many packets we'll be sending in total (+ 1 to always round up)
const uint16_t total_packets = VIA_BLOCK_SIZE / 20 + 1;

bool via_sync(void) {
    /*
        The RPC buffer is 32 bytes and changing it caused failures in testing
        so we'll send 20 byte packets on each call. The housekeeping task will
        act as our loop for sending the next packet / retrying a failed one.
     */

    // What packet we're on
    static uint16_t packet_number = 0;

    // Count how many times retried
    static uint8_t retries = 0;
    // Allow max retries
    if (retries >= JUNCO_SYNC_RETRIES) {
        dprintf("Failure to sync VIA: too many retries\n");
        packet_number = 0;
        retries       = 0;
        return true;
    }

    // First call
    if (packet_number == 0) {
        dprintf("Attempting to sync VIA's %u bytes of data...\n", VIA_BLOCK_SIZE);
        dprintf("This will take about %u seconds\n", total_packets * VIA_SYNC_THROTTLE / 1000);
        packet_number = 1;
    }

    /* Copy the nth 20 bytes to the packet from EEPROM */
    // The address to read from, start of the VIA block offset to where the last packet left off
    uint32_t addr = START_ADDR + ((packet_number - 1) * 20);
    // How many bytes to read/update, will be 20 unless we're about to read past the end
    // of the VIA block. At which point we'll read the remaining bytes in the block, 1 + the
    // difference between the end address and the offset address.
    uint8_t num_bytes = ((addr + 20) > END_ADDR) ? (END_ADDR - addr + 1) : 20;

    via_sync_packet_t m2s = {addr, {0}, num_bytes};
    eeprom_read_block(m2s.data, (uint32_t*)addr, num_bytes);

    // Execute the RPC
    if (transaction_rpc_send(USER_VIA_SYNC, sizeof(m2s), &m2s)) {
        // If we've sent the last packet, return true
        if (packet_number == total_packets) {
            dprintf("VIA Synced!\n");
            packet_number = 0;
            retries       = 0;
            return true;
        }
        // Otherwise, increment the packet number and return false
        packet_number++;
        return false;
    } else {
        dprintf("Failure to sync VIA, RPC failed, retrying...\n");
        retries++;
        return false;
    }
}
// Slave handler for USER_VIA_SYNC
void via_sync_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const via_sync_packet_t* m2s = (const via_sync_packet_t*)in_data;
    // The address to write to
    const uint32_t addr = m2s->addr;
    // Update the EEPROM with the data
    eeprom_update_block(m2s->data, (uint32_t*)addr, m2s->num_bytes);
}

void via_sync_init(void) {
    // Register the VIA RPC
    transaction_register_rpc(USER_VIA_SYNC, via_sync_slave_handler);
}
