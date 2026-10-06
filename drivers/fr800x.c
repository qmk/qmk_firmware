// Copyright 2026 Roman Kuzmitskii (@damex)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * Tested on Freqchip FR8003A (FR800x family). UART sniffed using Miniware LA104.
 */

#include <assert.h>

#include "quantum.h"
#include "fr800x.h"
#include "uart.h"
#include "uart_frame.h"
#include "battery.h"
#include "battery_driver.h"

#define FR800X_COMMAND_SEND_KB         0xA1
#define FR800X_COMMAND_SEND_NKRO       0xA2
#define FR800X_COMMAND_SEND_CONSUMER   0xA3
#define FR800X_COMMAND_SEND_SYSTEM     0xA4
#define FR800X_COMMAND_DEVICE_CONTROL  0xA6
#define FR800X_COMMAND_OS_PROFILE      0xA7

#define FR800X_COMMAND_CONSUMER_LENGTH   2
#define FR800X_COMMAND_SYSTEM_LENGTH     1

/* HID System Control usages relayed from host. */
#define FR800X_HOST_POWER_DOWN 0x81
#define FR800X_HOST_SLEEP      0x82
#define FR800X_HOST_WAKE_UP    0x83

#define FR800X_HOST_POWER_DOWN_BIT 0x01
#define FR800X_HOST_SLEEP_BIT      0x02
#define FR800X_HOST_WAKE_UP_BIT    0x04

#define FR800X_EVENT_INDICATOR           0x5A
#define FR800X_EVENT_CONNECTION          0x5B
#define FR800X_EVENT_BATTERY_LEVEL       0x5C
#define FR800X_EVENT_HOST_STATE          0x60
#define FR800X_EVENT_ACK                 0x61

#define FR800X_EVENT_CONNECTION_PAIRING      0x31
#define FR800X_EVENT_CONNECTION_CONNECTED    0x32
#define FR800X_EVENT_CONNECTION_DISCONNECTED 0x33
#define FR800X_EVENT_CONNECTION_REJECT       0x36

#define FR800X_EVENT_HOST_STATE_RESUME 0x01

#define FR800X_ACK_TERMINATOR_CR 0x0D
#define FR800X_ACK_TERMINATOR_LF 0x0A

#define FR800X_FRAME_LENGTH 3

/* Per-slot drain budget while clearing pairings; above the chip's CLEAN+PAIR round-trip. */
#define FR800X_CLEAR_PAIRING_DRAIN_TIMEOUT_MS 500

typedef struct {
    fr800x_state_t state;
    uint8_t        indicator;
} fr800x_runtime_t;

static fr800x_runtime_t fr800x_runtime = {
    .state     = FR800X_STATE_NONE,
    .indicator = 0,
};

static fr800x_target_t fr800x_current_target          = FR800X_TARGET_UNINITIALIZED;
static uint8_t         battery_level                  = 100;
static uint32_t        fr800x_last_target_change_time = 0;
static uint32_t        fr800x_pairing_start_time      = 0;
static uint32_t        fr800x_pairing_timeouts[FR800X_TARGET_DONGLE + 1]      = {0};
static uint32_t        fr800x_probe_intervals[FR800X_TARGET_DONGLE + 1]       = {0};

/* Carries 6KRO state across fr800x_route_nkro calls; fr800x_clear_dropped_6kro_keys reads previous slots. */
static report_keyboard_t fr800x_nkro_6kro_state = {0};

_Static_assert(sizeof(report_keyboard_t) == FR800X_COMMAND_KB_LENGTH, "report_keyboard_t size must match wire format");

/* Caller's `data` buffer must be at least `payload_length + 1` bytes (checksum lands at data[payload_length]). */
void fr800x_packet_append_checksum(uint8_t *data, uint32_t payload_length) {
    assert(data != NULL);

    uint8_t sum = 0;
    for (uint32_t byte_index = 0; byte_index < payload_length; byte_index++) {
        sum += data[byte_index];
    }

    data[payload_length] = sum;
}

static void fr800x_set_state(fr800x_state_t new_state);

int8_t fr800x_queue_push(const uint8_t *data, uint32_t size) {
    assert(size <= UINT16_MAX);
    return uart_frame_send(data, (uint16_t)size);
}

static void send_with_opcode(uint8_t opcode, const uint8_t *data, uint8_t length) {
    assert(data != NULL);
    assert(length > 0);
    assert(length + FR800X_SIMPLE_PACKET_HEADER_SIZE + FR800X_PACKET_CHECKSUM_SIZE <= FR800X_PACKET_PAYLOAD_MAX);

    uint8_t packet_buffer[FR800X_PACKET_PAYLOAD_MAX] = {0};
    fr800x_simple_packet_t *packet = (fr800x_simple_packet_t *)packet_buffer;
    packet->opcode = opcode;
    memcpy(packet->payload, data, length);
    fr800x_packet_append_checksum(packet_buffer, FR800X_SIMPLE_PACKET_HEADER_SIZE + length);
    uart_frame_send(packet_buffer, FR800X_SIMPLE_PACKET_HEADER_SIZE + length + FR800X_PACKET_CHECKSUM_SIZE);
}

/*
 * Packet: opcode 0xA1, FR800X_COMMAND_KB_LENGTH (8) bytes HID keyboard report, checksum.
 * Empty report: A1 00 00 00 00 00 00 00 00 A1
 */
static void fr800x_send_kb(const uint8_t *data) {
    send_with_opcode(FR800X_COMMAND_SEND_KB, data, FR800X_COMMAND_KB_LENGTH);
}

/*
 * Packet: opcode 0xA2, FR800X_COMMAND_NKRO_LENGTH (14) bytes NKRO bitmap report, checksum.
 * Empty report: A2 00 00 00 00 00 00 00 00 00 00 00 00 00 00 A2
 */
static void fr800x_send_nkro(const uint8_t *data) {
    send_with_opcode(FR800X_COMMAND_SEND_NKRO, data, FR800X_COMMAND_NKRO_LENGTH);
}

/*
 * Packet: opcode 0xA3, 2 bytes consumer usage ID little-endian, checksum.
 * Mute (0x00E2): A3 E2 00 85
 */
static void fr800x_send_consumer(const uint8_t *data) {
    send_with_opcode(FR800X_COMMAND_SEND_CONSUMER, data, FR800X_COMMAND_CONSUMER_LENGTH);
}

/*
 * Packet: opcode 0xA4, 1 byte system bitmap, checksum.
 * Bit 0 Power Down, bit 1 Sleep, bit 2 Wake Up.
 * Power Down (bitmap 0x01): A4 01 A5
 */
static void fr800x_send_system(uint8_t bitmap) {
    send_with_opcode(FR800X_COMMAND_SEND_SYSTEM, &bitmap, FR800X_COMMAND_SYSTEM_LENGTH);
}

/*
 * Packet: opcode 0xA6, 1 byte device-control command, checksum.
 * Idle (FR800X_COMMAND_DEVICE_CONTROL_IDLE 0x11): A6 11 B7
 */
void fr800x_send_device_control(uint8_t command) {
    send_with_opcode(FR800X_COMMAND_DEVICE_CONTROL, &command, 1);
}

/*
 * Packet: opcode 0xA7, 1 byte OS profile, checksum.
 * Selects which BLE HID descriptor and battery report format the chip advertises.
 * Mac mode (FR800X_OS_PROFILE_MAC 0x80): A7 80 27
 * Win mode (FR800X_OS_PROFILE_WIN 0x81): A7 81 28
 */
void fr800x_send_os_profile(uint8_t profile) {
    send_with_opcode(FR800X_COMMAND_OS_PROFILE, &profile, 1);
}

fr800x_state_t fr800x_get_state(void) {
    return fr800x_runtime.state;
}

uint8_t fr800x_get_indicator(void) {
    return fr800x_runtime.indicator;
}

bool fr800x_is_busy(void) {
    return uart_frame_is_busy();
}

void fr800x_force_disconnect(void) {
    fr800x_set_state(FR800X_STATE_DISCONNECTED);
}

void fr800x_notify_transport_change(bool usb_active, fr800x_target_t target) {
    static bool            last_usb_active = false;
    static fr800x_target_t last_target     = FR800X_TARGET_UNINITIALIZED;

    if (usb_active == last_usb_active && target == last_target) {
        return;
    }
    last_usb_active = usb_active;
    last_target     = target;
    fr800x_send_device_control(FR800X_COMMAND_DEVICE_CONTROL_HANDSHAKE);
}

fr800x_target_t fr800x_target_get_current(void) {
    return fr800x_current_target;
}

void fr800x_idle(void) {
    fr800x_current_target = FR800X_TARGET_UNINITIALIZED;
    fr800x_send_device_control(FR800X_COMMAND_DEVICE_CONTROL_IDLE);
}

int8_t fr800x_request_battery(void) {
    if (fr800x_is_busy()) {
        return -1;
    }
    fr800x_send_device_control(FR800X_COMMAND_DEVICE_CONTROL_BATTERY_QUERY);
    return 0;
}

uint8_t fr800x_get_battery(void) {
    return battery_level;
}

void fr800x_relay_charging_state(battery_charging_state_t state) {
    uint8_t command;
    switch (state) {
        case BATTERY_CHARGING:
            command = FR800X_COMMAND_DEVICE_CONTROL_CHARGING;
            break;
        case BATTERY_FULL:
            command = FR800X_COMMAND_DEVICE_CONTROL_CHARGING_DONE;
            break;
        case BATTERY_NOT_CHARGING:
            command = FR800X_COMMAND_DEVICE_CONTROL_CHARGING_STOP;
            break;
        case BATTERY_CHARGING_UNKNOWN:
            return;
        default:
            assert(false);
            return;
    }
    fr800x_send_device_control(command);
}

__attribute__((weak)) void battery_driver_init(void) {}

__attribute__((weak)) uint8_t battery_driver_sample_percent(void) {
    /* Chip reports 100% on USB; cross-check via BATTERY_FULL while charging. */
    static uint8_t cached_level = 100;
    uint8_t        chip_level   = fr800x_get_battery();

    if (battery_get_charging_state() == BATTERY_FULL) {
        cached_level = 100;
    } else if (chip_level < 100) {
        cached_level = chip_level;
    }
    return cached_level;
}

__attribute__((weak)) void fr800x_receive_host_cb(bool resume) {}

__attribute__((weak)) void fr800x_receive_connection_cb(fr800x_state_t state) {}

static void fr800x_set_state(fr800x_state_t new_state) {
    if (fr800x_runtime.state == new_state) {
        return;
    }
    fr800x_runtime.state = new_state;
    if (new_state == FR800X_STATE_PAIRING) {
        fr800x_pairing_start_time = sync_timer_read32();
    }
    fr800x_receive_connection_cb(new_state);
}

static const uint8_t fr800x_disconnect_subevents[] = {
    FR800X_EVENT_CONNECTION_DISCONNECTED,
    FR800X_EVENT_CONNECTION_REJECT,
};

static void fr800x_handle_connection_subevent(uint8_t subevent) {
    if (memchr(fr800x_disconnect_subevents, subevent, sizeof(fr800x_disconnect_subevents)) != NULL) {
        fr800x_set_state(FR800X_STATE_DISCONNECTED);
        return;
    }
    switch (subevent) {
        case FR800X_EVENT_CONNECTION_PAIRING:
            fr800x_set_state(FR800X_STATE_PAIRING);
            break;
        case FR800X_EVENT_CONNECTION_CONNECTED:
            fr800x_set_state(FR800X_STATE_CONNECTED);
            break;
        default:
            dprintf("fr800x: unknown connection sub-event 0x%02X\n", subevent);
            break;
    }
}

static void fr800x_dispatch_event(const uint8_t *payload) {
    uint8_t opcode     = payload[0];
    uint8_t event_data = payload[1];

    switch (opcode) {
        case FR800X_EVENT_INDICATOR:
            fr800x_runtime.indicator = event_data;
            break;
        case FR800X_EVENT_CONNECTION:
            fr800x_handle_connection_subevent(event_data);
            break;
        case FR800X_EVENT_BATTERY_LEVEL:
            battery_level = event_data;
            break;
        case FR800X_EVENT_HOST_STATE:
            fr800x_receive_host_cb(event_data == FR800X_EVENT_HOST_STATE_RESUME);
            break;
        default:
            dprintf("fr800x: unknown event opcode 0x%02X\n", opcode);
            break;
    }
}

static const uint8_t fr800x_frame_start_opcodes[] = {
    FR800X_EVENT_INDICATOR,
    FR800X_EVENT_CONNECTION,
    FR800X_EVENT_BATTERY_LEVEL,
    FR800X_EVENT_HOST_STATE,
    FR800X_EVENT_ACK,
};

static bool fr800x_frame_starts(uint8_t opcode) {
    return memchr(fr800x_frame_start_opcodes, opcode, sizeof(fr800x_frame_start_opcodes)) != NULL;
}

static bool fr800x_frame_complete(const uint8_t *partial, uint16_t partial_length) {
    (void)partial;
    return partial_length == FR800X_FRAME_LENGTH;
}

static bool fr800x_frame_verify(const uint8_t *frame, uint16_t length) {
    if (length == 0) {
        return false;
    }

    uint8_t expected_checksum = frame[length - 1];
    uint8_t sum               = 0;
    for (uint16_t byte_index = 0; byte_index < (length - 1); byte_index++) {
        sum += frame[byte_index];
    }

    return sum == expected_checksum;
}

/*
 * ACK: fixed 3-byte sequence sent to the chip after each valid received frame.
 * Packet: 61 0D 0A
 */
static const uint8_t fr800x_ack_sequence[FR800X_FRAME_LENGTH] = {
    FR800X_EVENT_ACK,
    FR800X_ACK_TERMINATOR_CR,
    FR800X_ACK_TERMINATOR_LF,
};

static bool fr800x_frame_is_ack(const uint8_t *frame, uint16_t length) {
    return length == FR800X_FRAME_LENGTH
        && memcmp(frame, fr800x_ack_sequence, FR800X_FRAME_LENGTH) == 0;
}

static void fr800x_frame_send_ack(void) {
    uart_transmit(fr800x_ack_sequence, sizeof(fr800x_ack_sequence));
}

static void fr800x_frame_on_receive(const uint8_t *frame, uint16_t length) {
    assert(length == FR800X_FRAME_LENGTH);
    fr800x_dispatch_event(frame);
}

void fr800x_init(void) {
    /* Idempotent: bluetooth + wireless_2p4ghz both call this. */
    static bool fr800x_initialized = false;
    if (fr800x_initialized) {
        return;
    }
    fr800x_initialized = true;

    uart_init(FR800X_BAUD_RATE);

    static const uart_frame_config_t fr800x_uart_frame_config = {
        .starts         = fr800x_frame_starts,
        .complete       = fr800x_frame_complete,
        .verify         = fr800x_frame_verify,
        .is_ack         = fr800x_frame_is_ack,
        .send_ack       = fr800x_frame_send_ack,
        .on_receive     = fr800x_frame_on_receive,
        .ack_timeout_ms = FR800X_PACKET_TIMEOUT,
        .retry_max      = FR800X_PACKET_RETRY,
    };
    uart_frame_init(&fr800x_uart_frame_config);
}

void fr800x_task(void) {
    uart_frame_task();

    static uint32_t battery_sample_timer = 0;
    if (sync_timer_elapsed32(battery_sample_timer) >= FR800X_BATTERY_SAMPLE_INTERVAL) {
        if (fr800x_request_battery() == 0) {
            battery_sample_timer = sync_timer_read32();
        }
    }

    /* PAIRING can lapse silently; force DISCONNECTED so the reconnect retry below re-fires.
     * Per-target timeout registered by adapters at init (BLE waits on passkey, 2.4G is fast). */
    uint32_t pairing_timeout = fr800x_pairing_timeouts[fr800x_current_target];
    if (pairing_timeout > 0
        && fr800x_runtime.state == FR800X_STATE_PAIRING
        && sync_timer_elapsed32(fr800x_pairing_start_time) >= pairing_timeout) {
        fr800x_set_state(FR800X_STATE_DISCONNECTED);
    }

    /* Per-target link probe while CONNECTED. Adapters register per-transport: 2.4G needs HANDSHAKE
     * to prompt chip-side radio verification (chip is lazy at noticing dongle loss); BLE registers 0
     * because chip's BLE link supervision works on its own. On dead link the chip emits 0x33 which
     * fires the existing reconnect path. */
    static uint32_t link_probe_timer = 0;
    uint32_t probe_interval = fr800x_probe_intervals[fr800x_current_target];
    if (probe_interval > 0
        && fr800x_runtime.state == FR800X_STATE_CONNECTED
        && sync_timer_elapsed32(link_probe_timer) >= probe_interval) {
        fr800x_send_device_control(FR800X_COMMAND_DEVICE_CONTROL_HANDSHAKE);
        link_probe_timer = sync_timer_read32();
    }

    /* Reconnect retry. DISCONNECTED only: chip cancels in-flight advertising on a redundant slot opcode.
     * Order matches the manual switch ceremony: target opcode first, HANDSHAKE after. */
    if (fr800x_target_is_pairable(fr800x_current_target)
        && fr800x_runtime.state == FR800X_STATE_DISCONNECTED
        && sync_timer_elapsed32(fr800x_last_target_change_time) >= FR800X_RECONNECT_INTERVAL_MS) {
        fr800x_target_change(fr800x_current_target, false);
        fr800x_send_device_control(FR800X_COMMAND_DEVICE_CONTROL_HANDSHAKE);
    }
}

static bool fr800x_chip_init_called = false;

void fr800x_chip_init(void) {
    assert(!fr800x_chip_init_called);
    fr800x_chip_init_called = true;

    static const uint8_t chip_init_sequence[] = {
        FR800X_COMMAND_DEVICE_CONTROL_HANDSHAKE,
        FR800X_COMMAND_DEVICE_CONTROL_SLEEP_BLUETOOTH_ENABLE,
        FR800X_COMMAND_DEVICE_CONTROL_SLEEP_DONGLE_ENABLE,
    };
    for (size_t index = 0; index < ARRAY_SIZE(chip_init_sequence); index++) {
        fr800x_send_device_control(chip_init_sequence[index]);
    }
}

bool fr800x_is_chip_initialized(void) {
    return fr800x_chip_init_called;
}

bool fr800x_target_is_pairable(fr800x_target_t target) {
    return target >= FR800X_TARGET_BLUETOOTH1 && target <= FR800X_TARGET_DONGLE;
}

bool fr800x_target_is_bluetooth(fr800x_target_t target) {
    return target >= FR800X_TARGET_BLUETOOTH1 && target <= FR800X_TARGET_BLUETOOTH3;
}

fr800x_target_t fr800x_target_from_bluetooth_profile(uint8_t profile) {
    return (fr800x_target_t)(FR800X_TARGET_BLUETOOTH1 + profile);
}

__attribute__((weak)) void fr800x_bluetooth_slot_select(uint8_t slot, bool reset) {}
__attribute__((weak)) void fr800x_dongle_select(bool reset) {}

void fr800x_target_change(fr800x_target_t target, bool reset) {
    if (!fr800x_target_is_pairable(target)) {
        return;
    }

    fr800x_current_target          = target;
    fr800x_last_target_change_time = sync_timer_read32();

    /* HANDSHAKE before slot select: chip's RF stack wants the prompt prior to mode change.
     * Replicates the boot-order discipline (fr800x_chip_init's HANDSHAKE precedes slot select). */
    fr800x_send_device_control(FR800X_COMMAND_DEVICE_CONTROL_HANDSHAKE);

    if (target == FR800X_TARGET_DONGLE) {
        fr800x_dongle_select(reset);
        return;
    }

    fr800x_bluetooth_slot_select(target - FR800X_TARGET_BLUETOOTH1, reset);
}

void fr800x_target_set_pairing_timeout(fr800x_target_t target, uint32_t timeout_ms) {
    assert(fr800x_target_is_pairable(target));
    fr800x_pairing_timeouts[target] = timeout_ms;
}

void fr800x_target_set_probe_interval(fr800x_target_t target, uint32_t interval_ms) {
    assert(fr800x_target_is_pairable(target));
    fr800x_probe_intervals[target] = interval_ms;
}

/* Leaves fr800x_current_target = DONGLE on exit; callers must mcu_reset or reassign target before further wireless use. */
void fr800x_clear_all_pairings(void) {
    for (fr800x_target_t target = FR800X_TARGET_BLUETOOTH1; target <= FR800X_TARGET_DONGLE; target++) {
        fr800x_target_change(target, true);
        uint32_t drain_start = sync_timer_read32();
        while (fr800x_is_busy() && sync_timer_elapsed32(drain_start) < FR800X_CLEAR_PAIRING_DRAIN_TIMEOUT_MS) {
            fr800x_task();
        }
    }
}

static bool fr800x_ready_to_send(void) {
    return fr800x_get_state() == FR800X_STATE_CONNECTED;
}

/* DISCONNECTED only; PAIRING lets the press through process_record_kb (so QMK key state is
 * coherent) and the route_* paths silently drop it (not CONNECTED). DISCONNECTED is the only
 * state where dropping at process_record_kb prevents stuck-key replay on a late reconnect. */
bool fr800x_should_drop_basic(uint16_t keycode, bool usb_active) {
    if (usb_active) {
        return false;
    }
    if (fr800x_get_state() != FR800X_STATE_DISCONNECTED) {
        return false;
    }
    return IS_BASIC_KEYCODE(keycode) || IS_MODIFIER_KEYCODE(keycode);
}

uint8_t fr800x_keyboard_leds(void) {
    if (fr800x_get_state() == FR800X_STATE_CONNECTED) {
        return fr800x_get_indicator();
    }
    return 0;
}

void fr800x_route_keyboard(report_keyboard_t *report) {
    if (!fr800x_ready_to_send()) {
        return;
    }

    if (report == NULL) {
        uint8_t empty[FR800X_COMMAND_KB_LENGTH] = {0};
        fr800x_send_kb(empty);
        return;
    }
    fr800x_send_kb((const uint8_t *)report);
}

static bool fr800x_bitmap_get(const uint8_t *bitmap, size_t bitmap_bytes, uint16_t bit) {
    size_t byte_index = bit / 8;
    if (byte_index >= bitmap_bytes) {
        return false;
    }
    return (bitmap[byte_index] & (1U << (bit % 8))) != 0;
}

static void fr800x_bitmap_set(uint8_t *bitmap, size_t bitmap_bytes, uint16_t bit) {
    size_t byte_index = bit / 8;
    if (byte_index >= bitmap_bytes) {
        return;
    }
    bitmap[byte_index] |= (uint8_t)(1U << (bit % 8));
}

static void fr800x_clear_dropped_6kro_keys(report_keyboard_t *keyboard_report, const report_nkro_t *nkro) {
    for (uint8_t slot = 0; slot < KEYBOARD_REPORT_KEYS; slot++) {
        if (keyboard_report->keys[slot] != 0 && !fr800x_bitmap_get(nkro->bits, NKRO_REPORT_BITS, keyboard_report->keys[slot])) {
            keyboard_report->keys[slot] = 0;
        }
    }
}

static void fr800x_place_keys_into_6kro_or_nkro(report_keyboard_t *keyboard_report, const report_nkro_t *nkro, uint8_t *overflow_bitmap) {
    for (uint16_t bit = 0; bit < NKRO_REPORT_BITS * 8; bit++) {
        if (!fr800x_bitmap_get(nkro->bits, NKRO_REPORT_BITS, bit)) {
            continue;
        }
        uint8_t usageid = (uint8_t)bit;

        if (memchr(keyboard_report->keys, usageid, KEYBOARD_REPORT_KEYS) != NULL) {
            continue;
        }
        uint8_t *empty_slot = memchr(keyboard_report->keys, 0, KEYBOARD_REPORT_KEYS);
        if (empty_slot != NULL) {
            *empty_slot = usageid;
            continue;
        }
        fr800x_bitmap_set(overflow_bitmap, FR800X_COMMAND_NKRO_LENGTH, usageid);
    }
}

/* Chip expects hybrid: 6KRO report (host driver) + 14-byte NKRO bitmap for overflow keys. */
void fr800x_route_nkro(report_nkro_t *report) {
    uint8_t wireless_report_nkro[FR800X_COMMAND_NKRO_LENGTH] = {0};

    if (!fr800x_ready_to_send()) {
        return;
    }

    if (report != NULL) {
        fr800x_nkro_6kro_state.mods = report->mods;
        fr800x_clear_dropped_6kro_keys(&fr800x_nkro_6kro_state, report);
        fr800x_place_keys_into_6kro_or_nkro(&fr800x_nkro_6kro_state, report, wireless_report_nkro);
    } else {
        fr800x_nkro_6kro_state = (report_keyboard_t){0};
    }

    /* Queue full -> packet dropped silently; next NKRO report reflects current key state and recovers. */
    host_keyboard_send(&fr800x_nkro_6kro_state);
    fr800x_send_nkro(wireless_report_nkro);
}

/*
 * Packet payload (consumer command, after opcode + before checksum): consumer usage ID little-endian.
 * Mute (0x00E2): E2 00
 */
typedef struct __attribute__((packed)) {
    uint16_t usage;
} fr800x_consumer_payload_t;
_Static_assert(sizeof(fr800x_consumer_payload_t) == FR800X_COMMAND_CONSUMER_LENGTH, "consumer payload size must match wire format");

void fr800x_route_consumer(uint16_t usage) {
    if (!fr800x_ready_to_send()) {
        return;
    }
    fr800x_consumer_payload_t payload = {.usage = usage};
    fr800x_send_consumer((const uint8_t *)&payload);
}

void fr800x_route_system(uint16_t usage) {
    if (!fr800x_ready_to_send()) {
        return;
    }

    switch (usage) {
        case FR800X_HOST_POWER_DOWN:
            fr800x_send_system(FR800X_HOST_POWER_DOWN_BIT);
            break;
        case FR800X_HOST_SLEEP:
            fr800x_send_system(FR800X_HOST_SLEEP_BIT);
            break;
        case FR800X_HOST_WAKE_UP:
            fr800x_send_system(FR800X_HOST_WAKE_UP_BIT);
            break;
        default:
            dprintf("fr800x: unknown system usage 0x%04X\n", usage);
            break;
    }
}
