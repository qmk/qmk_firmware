// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Bluetooth through TEX's BLE4 add-on board (a TI CC2541 module, sold for the Shinobi),
// protocol as used by the Shinobi's stock firmware 3.01: USART0 at 115,942 baud 8N1,
// unframed messages. The keyboard sends a command byte 0xA0-0xAF and a fixed payload; the
// module sends 0xBA-0xBF messages with a length fixed by the first byte. Commands that
// expect an answer wait for any module message; reports are not answered.
//
//   AE 55                    hello              -> BE 'v' d d (version)
//   AA n                     slot n name        -> BA n len name
//   AB 55                    bonded slots       -> BB s1 s2 s3 s4
//   AC 55, AD 55             resume, connected  -> BC slot status, BD x (x stayed 00, even
//                                                  with host Caps Lock on: no LED relay)
//   A7 n / A6 n              connect / pair slot n
//   A1 mods 00 k1..k6        keyboard boot report
//   A3 buttons dx dy v h     mouse
//   A2 code                  consumer key (00 releases)
//   A0 vid pid ver 55 55     identity, sent when the module asks with BF
//   BC slot status           link status, pushed by the module
#include QMK_KEYBOARD_H
#include "bluetooth.h"
#include "connection.h"

#include <string.h>

#define BLE_SD SD0
#define BLE_BAUD 115942
// FROM_MCU: a low pulse wakes the module, which then takes UART input for about 10 s from the
// pulse (measured: messages sent later are mostly lost, however busy the line). Pulse again
// before a message once this much time has passed since the last pulse.
#define BLE_WAKE_LINE SHURA_BLE_FROM_MCU_PIN
#define BLE_WAKE_EVERY_MS 2000
#define BLE_WAKE_LOW_US 2
#define BLE_RESUME_SETTLE_MS 12
#define BLE_DISCONNECTED_MS 25000UL
#define BLE_SLOT_WINDOW_MS 120000UL
#define BLE_WAKE_SETTLE_MS 2
#define BLE_REPLY_MS 3000
#define BLE_HELLO_TRIES 10
// After a report the module needs about 1.5 ms before the next message.
#define BLE_GAP_MS 3
#define BLE_PAIR_HOLD_MS 3000
#define BLE_PAIR_BLINK_MS 100
#define BLE_FLUSH_MS 250
#define BLE_RESET_LOW_US 10
#define BLE_RESET_HIGH_US 20

#define REPORT_QUEUE 16
// Each entry holds motion for one uninterrupted button mask, not one UART packet.
#define MOUSE_QUEUE 8

enum { LINK_UNKNOWN, LINK_RECONNECTING, LINK_PAIRING, LINK_CONNECTED, LINK_QUERY_BONDS, LINK_ASLEEP, LINK_ABSENT };
enum { START_HELLO, START_NAME1, START_NAME2, START_NAME3, START_NAME4, START_BONDS, START_RESUME, START_DONE };

static const SerialConfig serial_config = {.speed = BLE_BAUD};
// Module codes for consumer usages, from the stock firmware's table.
static const uint16_t consumer_usages[] = {TRANSPORT_NEXT_TRACK, TRANSPORT_PREV_TRACK, TRANSPORT_STOP, TRANSPORT_PLAY_PAUSE, AUDIO_MUTE, AUDIO_VOL_UP, AUDIO_VOL_DOWN, AL_CC_CONFIG, AL_EMAIL, AL_CALCULATOR, AL_LOCAL_BROWSER, AC_SEARCH, AC_HOME, AC_BACK, AC_FORWARD, AC_STOP, AC_REFRESH, AC_BOOKMARKS};
static const uint8_t  identity[]        = {0xA0, 0xD9, 0x04, 0x32, 0x05, 0x00, 0x01, 0x55, 0x55};

typedef struct {
    uint8_t length;
    uint8_t data[9];
} message_t;

typedef struct {
    int16_t motion[4];
    uint8_t buttons;
} mouse_segment_t;

static message_t       keyboard_queue[REPORT_QUEUE];
static uint8_t         keyboard_head, keyboard_count;
static uint8_t         consumer_queue[REPORT_QUEUE];
static uint8_t         consumer_head, consumer_count;
static uint8_t         last_consumer;
static mouse_segment_t mouse_queue[MOUSE_QUEUE];
static uint8_t         mouse_head, mouse_count, mouse_buttons;
static uint8_t         command[2];
static bool            command_pending, identity_pending;

static uint8_t  start_state, hello_tries, link_state, slot = 1, host_leds;
static bool     slot_selected;
static bool     awaiting_reply;
static uint16_t reply_deadline_at, gap_at;
static uint32_t woken_at;
static uint32_t sleep_deadline;
static uint8_t  busy_low_samples;
static uint8_t  rx[24], rx_count;

static uint16_t slot_key, slot_since;
static bool     slot_paired, blinking;
static uint16_t blink_at;

static void queue_command(uint8_t code, uint8_t argument) {
    command[0]      = code;
    command[1]      = argument;
    command_pending = true;
}

static void wake_module(uint8_t settle_ms) {
    gpio_write_pin_low(BLE_WAKE_LINE);
    wait_us(BLE_WAKE_LOW_US);
    gpio_write_pin_high(BLE_WAKE_LINE);
    wait_ms(settle_ms);
    woken_at = timer_read32();
}

static void send(const uint8_t *data, uint8_t length, bool reply) {
    if (timer_elapsed32(woken_at) >= BLE_WAKE_EVERY_MS) {
        wake_module(BLE_WAKE_SETTLE_MS);
    }
    sdWrite(&BLE_SD, data, length);
    gap_at = timer_read();
    if (reply) {
        awaiting_reply    = true;
        reply_deadline_at = timer_read() + BLE_REPLY_MS;
    }
}

static void resume_module(void) {
    static const uint8_t resume[] = {0xAC, 0x55};
    wake_module(BLE_RESUME_SETTLE_MS);
    link_state     = LINK_RECONNECTING;
    sleep_deadline = timer_read32() + BLE_DISCONNECTED_MS;
    send(resume, sizeof(resume), true);
}

// No host is receiving edges. Drop their motion and reconcile just the current state
// on reconnect, including an unsent release after a previously transmitted press.
static void sync_mouse(uint8_t buttons) {
    mouse_head    = 0;
    mouse_count   = mouse_count || mouse_buttons || buttons;
    mouse_buttons = buttons;
    if (mouse_count) {
        mouse_queue[0] = (mouse_segment_t){.buttons = buttons};
    }
}

static void select_slot(uint8_t code, uint8_t target) {
    if (link_state == LINK_ASLEEP) {
        resume_module();
    }
    if (target != slot) {
        // The old host may report its disconnect after A7 has left the command queue.
        link_state     = LINK_RECONNECTING;
        keyboard_count = consumer_count = last_consumer = mouse_count = mouse_buttons = 0;
    }
    slot          = target;
    slot_selected = true;
    queue_command(code, target);
    sleep_deadline = timer_read32() + BLE_SLOT_WINDOW_MS;
    connection_set_host_noeeprom(CONNECTION_HOST_BLUETOOTH);
}

static void reset_module(void) {
    // Pulse RESET_N low, then release it to the module's pull-up, as Shinobi 3.01 does.
    gpio_write_pin_low(SHURA_BLE_RESET_PIN);
    palSetLineMode(SHURA_BLE_RESET_PIN, PAL_HT32_MODE_AF(AFIO_GPIO) | PAL_MODE_OUTPUT_PUSHPULL);
    wait_us(BLE_RESET_LOW_US);
    palSetLineMode(SHURA_BLE_RESET_PIN, PAL_HT32_MODE_AF(AFIO_GPIO) | PAL_MODE_INPUT);
    wait_us(BLE_RESET_HIGH_US);
}

// The module keeps its host connection while the keyboard restarts (after flashing, say), so
// it is only reset when it stops answering.
static void restart(void) {
    sync_mouse(mouse_buttons);
    start_state    = START_HELLO;
    awaiting_reply = false;
    if (++hello_tries == 2) {
        reset_module();
    }
    if (hello_tries > BLE_HELLO_TRIES) {
        link_state = LINK_ABSENT;
    }
}

static void handle_status(uint8_t new_slot, uint8_t status) {
    uint8_t previous = link_state;
    // Before the first selection, adopt the module's saved slot. Afterwards only the
    // requested host may update our link state or trigger an automatic reconnect.
    if (slot_selected && new_slot != slot) {
        return;
    }
    if (new_slot >= 1 && new_slot <= 4) {
        slot = new_slot;
    }
    switch (status) {
        case 0x00:
            // Disconnected: ask the module to reconnect to the slot's host.
            link_state = LINK_RECONNECTING;
            if (!command_pending) {
                queue_command(0xA7, slot);
            }
            break;
        case 0x01:
        case 0x10:
        case 0x12:
        case 0x13:
        case 0x17:
            link_state = LINK_PAIRING;
            break;
        case 0x02:
        case 0x15:
        case 0x19:
            link_state = LINK_CONNECTED;
            break;
        case 0x14:
        case 0x18:
            link_state = LINK_QUERY_BONDS;
            if (!command_pending) {
                queue_command(0xAB, 0x55);
            }
            break;
    }
    if (link_state != previous) {
        sleep_deadline = timer_read32() + BLE_DISCONNECTED_MS;
    }
    if (previous == LINK_CONNECTED && link_state != LINK_CONNECTED) {
        sync_mouse(mouse_buttons);
    }
    // Never carry queued passkey digits into a host session, or old typing into a new pairing.
    if ((previous == LINK_PAIRING) != (link_state == LINK_PAIRING)) {
        keyboard_count = 0;
    }
}

static uint8_t message_length(void) {
    switch (rx[0]) {
        case 0xBA:
            return rx_count < 3 ? 3 : 3 + rx[2];
        case 0xBB:
            return 5;
        case 0xBC:
            return 3;
        case 0xBD:
            return 2;
        case 0xBE:
            return 4;
        case 0xBF:
            return 9;
    }
    return 0;
}

static void receive(uint8_t byte) {
    uint8_t length;
    if (link_state == LINK_ASLEEP) {
        return; // In stock state 0xFF even a late status must not start a reconnect.
    }

    rx[rx_count++] = byte;
    length         = message_length();
    if (length == 0 || length > sizeof(rx)) {
        rx_count = 0;
        return;
    }
    if (rx_count < length) {
        return;
    }
    rx_count       = 0;
    awaiting_reply = false;
    switch (rx[0]) {
        case 0xBC:
            handle_status(rx[1], rx[2]);
            break;
        case 0xBD:
            host_leds = rx[1];
            break;
        case 0xBE:
            if (rx[1] == 'v' && start_state == START_HELLO) {
                hello_tries = 0;
                start_state = START_NAME1;
            }
            break;
        case 0xBF:
            identity_pending = true;
            break;
    }
}

static bool send_startup(void) {
    static const uint8_t steps[][2] = {{0xAE, 0x55}, {0xAA, 1}, {0xAA, 2}, {0xAA, 3}, {0xAA, 4}, {0xAB, 0x55}, {0xAC, 0x55}};

    if (start_state == START_DONE) {
        return false;
    }
    send(steps[start_state], 2, true);
    if (start_state != START_HELLO) {
        start_state++;
    }
    return true;
}

static void send_mouse(void) {
    mouse_segment_t *segment    = &mouse_queue[mouse_head];
    uint8_t          message[6] = {0xA3, segment->buttons};
    bool             remaining  = false;

    for (uint8_t i = 0; i < 4; i++) {
        int16_t value  = segment->motion[i] > 127 ? 127 : (segment->motion[i] < -127 ? -127 : segment->motion[i]);
        message[2 + i] = value;
        segment->motion[i] -= value;
        remaining |= segment->motion[i] != 0;
    }
    if (!remaining) {
        mouse_head = (mouse_head + 1) % MOUSE_QUEUE;
        mouse_count--;
    }
    send(message, sizeof(message), false);
}

static void send_next(void) {
    static const uint8_t sleep[] = {0xAF, 0x5A, 0x01, 0x03, 0x05};
    if (link_state == LINK_ABSENT || link_state == LINK_ASLEEP) {
        return;
    }
    if (awaiting_reply) {
        if ((int16_t)(timer_read() - reply_deadline_at) >= 0) {
            restart();
        }
        return;
    }
    if (timer_elapsed(gap_at) < BLE_GAP_MS || send_startup()) {
        return;
    }
    // Stock's link-state countdown, not a typing-idle timeout. No acknowledgement for AF.
    if (link_state != LINK_UNKNOWN && link_state != LINK_CONNECTED && !slot_key && (int32_t)(timer_read32() - sleep_deadline) >= 0) {
        send(sleep, sizeof(sleep), false);
        link_state      = LINK_ASLEEP;
        command_pending = identity_pending = false;
        keyboard_count = consumer_count = last_consumer = mouse_count = mouse_buttons = rx_count = 0;
        return;
    }
    if (identity_pending) {
        identity_pending = false;
        send(identity, sizeof(identity), false);
    } else if (command_pending) {
        command_pending = false;
        send(command, sizeof(command), true);
    } else if (keyboard_count && (link_state == LINK_PAIRING || link_state == LINK_CONNECTED)) {
        // The module consumes the host's passkey as normal A1 reports before the bond exists.
        message_t *message = &keyboard_queue[keyboard_head];
        send(message->data, message->length, false);
        keyboard_head = (keyboard_head + 1) % REPORT_QUEUE;
        keyboard_count--;
    } else if (link_state != LINK_CONNECTED) {
        // Without a host, keep only the latest key and button state for when it reconnects;
        // replaying stale presses and motion would be worse than losing them.
        if (keyboard_count > 1) {
            keyboard_head  = (keyboard_head + keyboard_count - 1) % REPORT_QUEUE;
            keyboard_count = 1;
        }
        if (consumer_count > 1) {
            consumer_head  = (consumer_head + consumer_count - 1) % REPORT_QUEUE;
            consumer_count = 1;
        }
    } else if (mouse_count) {
        send_mouse();
    } else if (consumer_count) {
        uint8_t message[2] = {0xA2, consumer_queue[consumer_head]};
        send(message, sizeof(message), false);
        consumer_head = (consumer_head + 1) % REPORT_QUEUE;
        consumer_count--;
    }
}

static void start_uart(void) {
    gpio_write_pin_high(BLE_WAKE_LINE);
    // Select the pin mux explicitly; UART RX also needs its HT32 input buffer enabled.
    palSetLineMode(BLE_WAKE_LINE, PAL_HT32_MODE_AF(AFIO_GPIO) | PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(SHURA_BLE_TO_MCU_PIN, PAL_HT32_MODE_AF(AFIO_GPIO) | PAL_MODE_INPUT_PULLDOWN);
    palSetLineMode(SHURA_BLE_TX_PIN, PAL_MODE_HT32_AF(SHURA_BLE_AF));
    palSetLineMode(SHURA_BLE_RX_PIN, PAL_MODE_HT32_AF(SHURA_BLE_AF) | PAL_HT32_MODE_INE);
    sdStart(&BLE_SD, &serial_config);
    woken_at = timer_read32() - BLE_WAKE_EVERY_MS;
}

void bluetooth_init(void) {
    start_uart();
}

void bluetooth_task(void) {
    msg_t byte;

    for (uint8_t i = 0; i < sizeof(rx); i++) {
        byte = sdGetTimeout(&BLE_SD, TIME_IMMEDIATE);
        if (byte < 0) {
            break;
        }
        receive(byte);
    }
    send_next();
}

void ble_flush_keys(uint8_t settle_ms) {
    uint16_t start = timer_read();

    while ((keyboard_count || consumer_count) && link_state == LINK_CONNECTED && timer_elapsed(start) < BLE_FLUSH_MS) {
        bluetooth_task();
    }
    start = timer_read();
    while (timer_elapsed(start) < settle_ms) {
        bluetooth_task();
    }
}

bool ble_pairing(void) {
    return link_state == LINK_PAIRING;
}

// The stock BLE4 firmware never reports a battery level to the module.
void ble_set_battery(uint8_t percent) {}

bool ble4_radio_asleep(void) {
    return link_state == LINK_ASLEEP;
}

bool ble4_can_sleep(void) {
    if (link_state == LINK_ABSENT) {
        return true;
    }
    if (gpio_read_pin(SHURA_BLE_TO_MCU_PIN)) {
        busy_low_samples = 0;
    } else if (busy_low_samples < 3) {
        busy_low_samples++;
    }
    // Do not cut off an active transaction, a user slot window, or the last bytes on TX.
    return busy_low_samples == 3 && (link_state == LINK_CONNECTED || link_state == LINK_ASLEEP) && !slot_key && !awaiting_reply && !command_pending && !identity_pending && !keyboard_count && !consumer_count && !mouse_count && timer_elapsed(gap_at) >= BLE_GAP_MS;
}

void ble_sleep(void) {
    sdStop(&BLE_SD);
    palSetLineMode(SHURA_BLE_TX_PIN, PAL_HT32_MODE_AF(AFIO_GPIO) | PAL_MODE_INPUT);
    palSetLineMode(BLE_WAKE_LINE, PAL_HT32_MODE_AF(AFIO_GPIO) | PAL_MODE_INPUT);
}

void ble_wake(void) {
    start_uart();
    busy_low_samples = 0;
    rx_count         = 0;
    if (link_state == LINK_ASLEEP) {
        resume_module();
    } else if (link_state == LINK_ABSENT) {
        link_state  = LINK_UNKNOWN;
        hello_tries = 0;
        restart();
    } else {
        wake_module(BLE_WAKE_SETTLE_MS);
    }
}

bool bluetooth_is_connected(void) {
    // QMK must keep routing keys to the module while it waits for passkey entry.
    return link_state != LINK_ABSENT;
}

uint8_t bluetooth_keyboard_leds(void) {
    return host_leds;
}

void bluetooth_send_keyboard(report_keyboard_t *report) {
    message_t *message;

    if (link_state == LINK_ASLEEP || keyboard_count == REPORT_QUEUE) {
        return;
    }
    message          = &keyboard_queue[(keyboard_head + keyboard_count++) % REPORT_QUEUE];
    message->length  = 9;
    message->data[0] = 0xA1;
    message->data[1] = report->mods;
    message->data[2] = 0;
    memcpy(&message->data[3], report->keys, 6);
}

// The module only takes 6KRO boot reports.
bool bluetooth_can_send_nkro(void) {
    return false;
}

void bluetooth_send_nkro(report_nkro_t *report) {}

static int16_t add_motion(int16_t queued, int16_t delta) {
    int32_t sum = (int32_t)queued + delta;
    return sum > INT16_MAX ? INT16_MAX : (sum < INT16_MIN ? INT16_MIN : sum);
}

void bluetooth_send_mouse(report_mouse_t *report) {
    if (link_state == LINK_ASLEEP) {
        return;
    }
    if (link_state != LINK_CONNECTED || start_state != START_DONE) {
        if (report->buttons != mouse_buttons) {
            sync_mouse(report->buttons);
        }
        return;
    }

    uint8_t next = (mouse_head + mouse_count) % MOUSE_QUEUE;
    if (mouse_count) {
        uint8_t          last = (next + MOUSE_QUEUE - 1) % MOUSE_QUEUE;
        mouse_segment_t *tail = &mouse_queue[last];
        if (tail->buttons == report->buttons) {
            tail->motion[0] = add_motion(tail->motion[0], report->x);
            tail->motion[1] = add_motion(tail->motion[1], report->y);
            tail->motion[2] = add_motion(tail->motion[2], report->v);
            tail->motion[3] = add_motion(tail->motion[3], report->h);
            return;
        }
        if (mouse_count == MOUSE_QUEUE) {
            // Keep the FIFO prefix. Replace the tail (including its motion) so even
            // under sustained overflow the host eventually sees the latest release.
            next = last;
        }
    }
    if (mouse_count < MOUSE_QUEUE) {
        mouse_count++;
    }
    mouse_buttons     = report->buttons;
    mouse_queue[next] = (mouse_segment_t){.motion = {report->x, report->y, report->v, report->h}, .buttons = mouse_buttons};
}

void bluetooth_send_consumer(uint16_t usage) {
    uint8_t code = 0;
    if (link_state == LINK_ASLEEP) {
        return;
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(consumer_usages); i++) {
        if (consumer_usages[i] == usage) {
            code = i + 1;
        }
    }
    if (code == last_consumer || consumer_count == REPORT_QUEUE) {
        return;
    }
    consumer_queue[(consumer_head + consumer_count++) % REPORT_QUEUE] = code;
    last_consumer                                                     = code;
}

// The module has no system-control report.
void bluetooth_send_system(uint16_t usage) {}

bool ble_process_record(uint16_t keycode, keyrecord_t *record) {
    if (keycode == BLE_USB) {
        if (record->event.pressed) {
            connection_set_host_noeeprom(CONNECTION_HOST_AUTO);
        }
        return false;
    }
    if (keycode < BLE_SLOT1 || keycode > BLE_PAIR) {
        return true;
    }
    if (record->event.pressed) {
        if (slot_key == 0) {
            slot_key    = keycode;
            slot_since  = timer_read();
            slot_paired = false;
        }
    } else if (slot_key == keycode) {
        // A tap connects to the slot's host; holding (see ble_housekeeping) pairs instead.
        if (!slot_paired && keycode != BLE_PAIR) {
            select_slot(0xA7, keycode - BLE_SLOT1 + 1);
        }
        slot_key = 0;
    }
    return false;
}

void ble_housekeeping(void) {
    bool pairing = ble_pairing();

    if (slot_key != 0 && !slot_paired && timer_elapsed(slot_since) >= BLE_PAIR_HOLD_MS) {
        slot_paired = true;
        select_slot(0xA6, slot_key == BLE_PAIR ? slot : slot_key - BLE_SLOT1 + 1);
    }
    if (pairing && timer_elapsed(blink_at) >= BLE_PAIR_BLINK_MS) {
        blink_at = timer_read();
        gpio_toggle_pin(SHURA_CAPS_LED_PIN);
    } else if (!pairing && blinking) {
        led_update_ports(host_keyboard_led_state());
    }
    blinking = pairing;
}
