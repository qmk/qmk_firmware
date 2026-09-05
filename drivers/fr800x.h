// Copyright 2026 Roman Kuzmitskii (@damex)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * Tested on Freqchip FR8003A (FR800x family). UART sniffed using Miniware LA104.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "report.h"
#include "battery.h"

#ifndef FR800X_BAUD_RATE
#    define FR800X_BAUD_RATE 115200
#endif

#ifndef FR800X_PACKET_TIMEOUT
#    define FR800X_PACKET_TIMEOUT 10 /* milliseconds between retries */
#endif

#ifndef FR800X_PACKET_RETRY
#    define FR800X_PACKET_RETRY 40
#endif

#ifndef FR800X_PACKET_PAYLOAD_MAX
/* 32-byte raw payload + 3-byte length-prefixed framing (opcode + length + checksum) + 1 byte slack. */
#    define FR800X_PACKET_PAYLOAD_MAX 36
#endif

#ifndef FR800X_BATTERY_SAMPLE_INTERVAL
#    define FR800X_BATTERY_SAMPLE_INTERVAL 30000 /* milliseconds */
#endif

#ifndef FR800X_RECONNECT_INTERVAL_MS
#    define FR800X_RECONNECT_INTERVAL_MS 2000 /* milliseconds between reconnect attempts while disconnected */
#endif

/* BLUETOOTH1..BLUETOOTH3..DONGLE must stay a contiguous block: fr800x_target_is_pairable, _is_bluetooth, _change, _from_bluetooth_profile, _clear_all_pairings rely on it. */
typedef enum __attribute__((packed)) {
    FR800X_TARGET_UNINITIALIZED = 0,
    FR800X_TARGET_BLUETOOTH1    = 1,
    FR800X_TARGET_BLUETOOTH2    = 2,
    FR800X_TARGET_BLUETOOTH3    = 3,
    FR800X_TARGET_DONGLE        = 4,
} fr800x_target_t;

/* Must equal (FR800X_TARGET_BLUETOOTH3 - FR800X_TARGET_BLUETOOTH1 + 1). */
#define FR800X_BLUETOOTH_PROFILE_COUNT 3

typedef enum {
    FR800X_STATE_NONE         = 0,
    FR800X_STATE_PAIRING      = 1,
    FR800X_STATE_CONNECTED    = 2,
    FR800X_STATE_DISCONNECTED = 3,
} fr800x_state_t;

#define FR800X_COMMAND_KB_LENGTH     8
#define FR800X_COMMAND_NKRO_LENGTH   14

/* Packet framing sizes used by senders to compute buffer length and checksum offset. */
#define FR800X_SIMPLE_PACKET_HEADER_SIZE            1 /* opcode */
#define FR800X_LENGTH_PREFIXED_PACKET_HEADER_SIZE   2 /* opcode + length */
#define FR800X_PACKET_CHECKSUM_SIZE                 1 /* trailing checksum byte */

#define FR800X_COMMAND_DEVICE_CONTROL_IDLE                     0x11
#define FR800X_COMMAND_DEVICE_CONTROL_DONGLE                   0x30
#define FR800X_COMMAND_DEVICE_CONTROL_PAIR                     0x51
#define FR800X_COMMAND_DEVICE_CONTROL_CLEAN                    0x52
#define FR800X_COMMAND_DEVICE_CONTROL_BATTERY_QUERY            0x53
#define FR800X_COMMAND_DEVICE_CONTROL_SLEEP_BLUETOOTH_ENABLE   0x55
#define FR800X_COMMAND_DEVICE_CONTROL_SLEEP_DONGLE_ENABLE      0x57
#define FR800X_COMMAND_DEVICE_CONTROL_CHARGING                 0x64
#define FR800X_COMMAND_DEVICE_CONTROL_CHARGING_STOP            0x65
#define FR800X_COMMAND_DEVICE_CONTROL_CHARGING_DONE            0x66
/* Handshake sentinel; sent on boot and on every device-mode change. */
#define FR800X_COMMAND_DEVICE_CONTROL_HANDSHAKE                0xFF

#define FR800X_OS_PROFILE_MAC 0x80
#define FR800X_OS_PROFILE_WIN 0x81

/* Wire format for outgoing packets. Cast a sufficiently-sized uint8_t buffer to one of these
 * to construct the packet by field name. Checksum is appended by fr800x_packet_append_checksum. */
typedef struct __attribute__((packed)) {
    uint8_t opcode;
    uint8_t payload[];
} fr800x_simple_packet_t;

typedef struct __attribute__((packed)) {
    uint8_t opcode;
    uint8_t length;
    uint8_t payload[];
} fr800x_length_prefixed_packet_t;

void fr800x_init(void);
void fr800x_task(void);

/* Chip-side init: HANDSHAKE, SLEEP_BLUETOOTH_ENABLE, SLEEP_DONGLE_ENABLE.
 * Boards call once at keyboard_post_init_kb time before any slot select. */
void fr800x_chip_init(void);

/* True once fr800x_chip_init has been called. Boards gate chip-bound behavior on this. */
bool fr800x_is_chip_initialized(void);

/* Override to react to chip-reported host state transitions (e.g., suspend/resume). */
void fr800x_receive_host_cb(bool resume);

/* Override to react to chip-reported connection state transitions. Called after the internal state field has been updated. */
void fr800x_receive_connection_cb(fr800x_state_t state);

void fr800x_send_device_control(uint8_t command);
void fr800x_send_os_profile(uint8_t profile);

/* Low-level packet helpers exposed for bluetooth/dongle modules to enqueue length-prefixed packets. */
void   fr800x_packet_append_checksum(uint8_t *data, uint32_t payload_length);
int8_t fr800x_queue_push(const uint8_t *data, uint32_t size);

fr800x_state_t fr800x_get_state(void);
uint8_t        fr800x_get_indicator(void);
bool           fr800x_is_busy(void);

/* Force the driver's transport state machine to DISCONNECTED. Boards call this from their
 * transport-switch flow so subsequent reports gate correctly. Fires the connection callback. */
void fr800x_force_disconnect(void);

/* Notify the driver that the board-level transport has been switched. Sends HANDSHAKE
 * to re-sync the chip after the new transport is bound. */
void fr800x_notify_transport_change(bool usb_active, fr800x_target_t target);

/* Transport-aware drop predicate. Returns true when the keycode is a basic/modifier
 * report and there is no active transport (chip disconnected and USB not active). */
bool fr800x_should_drop_basic(uint16_t keycode, bool usb_active);

bool            fr800x_target_is_pairable(fr800x_target_t target);
bool            fr800x_target_is_bluetooth(fr800x_target_t target);
fr800x_target_t fr800x_target_from_bluetooth_profile(uint8_t profile);
fr800x_target_t fr800x_target_get_current(void);

/* Sets the chip's wireless transport mode (bluetooth slot or dongle) and optionally triggers re-pair. */
void fr800x_target_change(fr800x_target_t target, bool reset);

/* Quiet the chip: stop any active wireless mode. Used when host transport leaves the chip. */
void fr800x_idle(void);

void fr800x_clear_all_pairings(void);

/* Adapters register per-target PAIRING-state timeout at init. PAIRING that exceeds the
 * timeout reverts to DISCONNECTED so the reconnect retry re-fires. Timeout of 0 disables. */
void fr800x_target_set_pairing_timeout(fr800x_target_t target, uint32_t timeout_ms);

/* Adapters register per-target link-probe interval at init. The driver sends HANDSHAKE at this
 * cadence while CONNECTED to the target, prompting the chip to verify its radio peer. Interval
 * of 0 disables the probe (BLE for instance has chip-side link supervision and doesn't need it). */
void fr800x_target_set_probe_interval(fr800x_target_t target, uint32_t interval_ms);

/* Per-transport pairing-mode selection. Each transport driver overrides its own. */
void fr800x_bluetooth_slot_select(uint8_t slot, bool reset);
void fr800x_dongle_select(bool reset);

/* Transport-neutral report routing. Both bluetooth and dongle paths funnel through these. */
uint8_t fr800x_keyboard_leds(void);
void    fr800x_route_keyboard(report_keyboard_t *report);
void    fr800x_route_nkro(report_nkro_t *report);
void    fr800x_route_consumer(uint16_t usage);
void    fr800x_route_system(uint16_t usage);

/* Chip-sourced battery percentage. */
int8_t  fr800x_request_battery(void);
uint8_t fr800x_get_battery(void);

/* Board's battery_charging_state_changed_kb calls this to relay the state to the chip. */
void    fr800x_relay_charging_state(battery_charging_state_t state);
