#include "adafruit_ble.h"

#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include "debug.h"
#include "timer.h"
#include "action_util.h"
#include "ringbuffer.hpp"
#include <string.h>
#include "spi_master.h"
#include "wait.h"
#include "analog.h"

// These are the pin assignments for the 32u4 boards.
// You may define them to something else in your config.h
// if yours is wired up differently.
#ifndef AdafruitBleResetPin
#    define AdafruitBleResetPin D4
#endif

#ifndef AdafruitBleCSPin
#    define AdafruitBleCSPin B4
#endif

#ifndef AdafruitBleIRQPin
#    define AdafruitBleIRQPin E6
#endif

#define SAMPLE_BATTERY
#define ConnectionUpdateInterval 1000 /* milliseconds */

#ifdef SAMPLE_BATTERY
#    ifndef BATTERY_LEVEL_PIN
#        define BATTERY_LEVEL_PIN 7
#    endif
#endif

static struct {
    bool is_connected;
    bool initialized;
    bool configured;

#define ProbedEvents 1
#define UsingEvents 2
    bool event_flags;

#ifdef SAMPLE_BATTERY
    uint16_t last_battery_update;
    uint32_t vbat;
#endif
    uint16_t last_connection_update;
} state;

// Commands are encoded using SDEP and sent via SPI
// https://github.com/adafruit/Adafruit_BluefruitLE_nRF51/blob/master/SDEP.md

#define SdepMaxPayload 16
struct sdep_msg {
    uint8_t type;
    uint8_t cmd_low;
    uint8_t cmd_high;
    struct __attribute__((packed)) {
        uint8_t len : 7;
        uint8_t more : 1;
    };
    uint8_t payload[SdepMaxPayload];
} __attribute__((packed));

// The recv latency is relatively high, so when we're hammering keys quickly,
// we want to avoid waiting for the responses in the matrix loop.  We maintain
// a short queue for that.  Since there is quite a lot of space overhead for
// the AT command representation wrapped up in SDEP, we queue the minimal
// information here.

enum queue_type {
    QTKeyReport,  // 1-byte modifier + 6-byte key report
    QTConsumer,   // 16-bit key code
#ifdef MOUSE_ENABLE
    QTMouseMove,  // 4-byte mouse report
#endif
};

struct queue_item {
    enum queue_type queue_type;
    uint16_t        added;
    union __attribute__((packed)) {
        struct __attribute__((packed)) {
            uint8_t modifier;
            uint8_t keys[6];
        } key;

        uint16_t consumer;
        struct __attribute__((packed)) {
            int8_t  x, y, scroll, pan;
            uint8_t buttons;
        } mousemove;
    };
};

// Items that we wish to send
static RingBuffer<queue_item, 40> send_buf;
// Pending response; while pending, we can't send any more requests.
// This records the time at which we sent the command for which we
// are expecting a response.
static RingBuffer<uint16_t, 2> resp_buf;

static bool process_queue_item(struct queue_item *item, uint16_t timeout);

enum sdep_type {
    SdepCommand       = 0x10,
    SdepResponse      = 0x20,
    SdepAlert         = 0x40,
    SdepError         = 0x80,
    SdepSlaveNotReady = 0xfe,  // Try again later
    SdepSlaveOverflow = 0xff,  // You read more data than is available
};

enum ble_cmd {
    BleInitialize = 0xbeef,
    BleAtWrapper  = 0x0a00,
    BleUartTx     = 0x0a01,
    BleUartRx     = 0x0a02,
};

enum ble_system_event_bits {
    BleSystemConnected    = 0,
    BleSystemDisconnected = 1,
    BleSystemUartRx       = 8,
    BleSystemMidiRx       = 10,
};

// The SDEP.md file says 2MHz but the web page and the sample driver
// both use 4MHz
#define SpiBusSpeed 4000000

#define SdepTimeout 150             /* milliseconds */
#define SdepShortTimeout 10         /* milliseconds */
#define SdepBackOff 25              /* microseconds */
#define BatteryUpdateInterval 10000 /* milliseconds */

static bool at_command(const char *cmd, char *resp, uint16_t resplen, bool verbose, uint16_t timeout = SdepTimeout);
static bool at_command_P(const char *cmd, char *resp, uint16_t resplen, bool verbose = false);

// Send a single SDEP packet
static bool sdep_send_pkt(const struct sdep_msg *msg, uint16_t timeout) {
    writePinLow(AdafruitBleCSPin);
    uint16_t timerStart = timer_read();
    bool     success    = false;
    bool     ready      = false;

    do {
        ready = spi_write(msg->type, 100) != SdepSlaveNotReady;
        if (ready) {
            break;
        }

        // Release it and let it initialize
        writePinHigh(AdafruitBleCSPin);
        wait_us(SdepBackOff);
        writePinLow(AdafruitBleCSPin);
    } while (timer_elapsed(timerStart) < timeout);

    if (ready) {
        // Slave is ready; send the rest of the packet
        spi_transmit(&msg->cmd_low, sizeof(*msg) - (1 + sizeof(msg->payload)) + msg->len, 100);
        success = true;
    }

    writePinHigh(AdafruitBleCSPin);

    return success;
}

static inline void sdep_build_pkt(struct sdep_msg *msg, uint16_t command, const uint8_t *payload, uint8_t len, bool moredata) {
    msg->type     = SdepCommand;
    msg->cmd_low  = command & 0xff;
    msg->cmd_high = command >> 8;
    msg->len      = len;
    msg->more     = (moredata && len == SdepMaxPayload) ? 1 : 0;

    static_assert(sizeof(*msg) == 20, "msg is correctly packed");

    memcpy(msg->payload, payload, len);
}

// Read a single SDEP packet
static bool sdep_recv_pkt(struct sdep_msg *msg, uint16_t timeout) {
    bool     success    = false;
    uint16_t timerStart = timer_read();
    bool     ready      = false;

    do {
        ready = readPin(AdafruitBleIRQPin);
        if (ready) {
            break;
        }
        wait_us(1);
    } while (timer_elapsed(timerStart) < timeout);

    if (ready) {
        writePinLow(AdafruitBleCSPin);

        do {
            // Read the command type, waiting for the data to be ready
            msg->type = spi_read(100);
            if (msg->type == SdepSlaveNotReady || msg->type == SdepSlaveOverflow) {
                // Release it and let it initialize
                writePinHigh(AdafruitBleCSPin);
                wait_us(SdepBackOff);
                writePinLow(AdafruitBleCSPin);
                continue;
            }

            // Read the rest of the header
            spi_receive(&msg->cmd_low, sizeof(*msg) - (1 + sizeof(msg->payload)), 100);

            // and get the payload if there is any
            if (msg->len <= SdepMaxPayload) {
                spi_receive(msg->payload, msg->len, 100);
            }
            success = true;
            break;
        } while (timer_elapsed(timerStart) < timeout);

        writePinHigh(AdafruitBleCSPin);
    }
    return success;
}

static void resp_buf_read_one(bool greedy) {
    uint16_t last_send;
    if (!resp_buf.peek(last_send)) {
        return;
    }

    if (readPin(AdafruitBleIRQPin)) {
        struct sdep_msg msg;

    again:
        if (sdep_recv_pkt(&msg, SdepTimeout)) {
            if (!msg.more) {
                // We got it; consume this entry
                resp_buf.get(last_send);
                dprintf("recv latency %dms\n", TIMER_DIFF_16(timer_read(), last_send));
            }

            if (greedy && resp_buf.peek(last_send) && readPin(AdafruitBleIRQPin)) {
                goto again;
            }
        }

    } else if (timer_elapsed(last_send) > SdepTimeout * 2) {
        dprintf("waiting_for_result: timeout, resp_buf size %d\n", (int)resp_buf.size());

        // Timed out: consume this entry
        resp_buf.get(last_send);
    }
}

static void send_buf_send_one(uint16_t timeout = SdepTimeout) {
    struct queue_item item;

    // Don't send anything more until we get an ACK
    if (!resp_buf.empty()) {
        return;
    }

    if (!send_buf.peek(item)) {
        return;
    }
    if (process_queue_item(&item, timeout)) {
        // commit that peek
        send_buf.get(item);
        dprintf("send_buf_send_one: have %d remaining\n", (int)send_buf.size());
    } else {
        dprint("failed to send, will retry\n");
        wait_ms(SdepTimeout);
        resp_buf_read_one(true);
    }
}

static void resp_buf_wait(const char *cmd) {
    bool didPrint = false;
    while (!resp_buf.empty()) {
        if (!didPrint) {
            dprintf("wait on buf for %s\n", cmd);
            didPrint = true;
        }
        resp_buf_read_one(true);
    }
}

static bool ble_init(void) {
    state.initialized  = false;
    state.configured   = false;
    state.is_connected = false;

    setPinInput(AdafruitBleIRQPin);
    setPinOutput(AdafruitBleCSPin);
    writePinHigh(AdafruitBleCSPin);

    spi_init();

    // Perform a hardware reset
    setPinOutput(AdafruitBleResetPin);
    writePinHigh(AdafruitBleResetPin);
    writePinLow(AdafruitBleResetPin);
    wait_ms(10);
    writePinHigh(AdafruitBleResetPin);

    wait_ms(1000);  // Give it a second to initialize

    state.initialized = true;
    return state.initialized;
}

static inline uint8_t min(uint8_t a, uint8_t b) { return a < b ? a : b; }

static bool read_response(char *resp, uint16_t resplen, bool verbose) {
    char *dest = resp;
    char *end  = dest + resplen;

    while (true) {
        struct sdep_msg msg;

        if (!sdep_recv_pkt(&msg, 2 * SdepTimeout)) {
            dprint("sdep_recv_pkt failed\n");
            return false;
        }

        if (msg.type != SdepResponse) {
            *resp = 0;
            return false;
        }

        uint8_t len = min(msg.len, end - dest);
        if (len > 0) {
            memcpy(dest, msg.payload, len);
            dest += len;
        }

        if (!msg.more) {
            // No more data is expected!
            break;
        }
    }

    // Ensure the response is NUL terminated
    *dest = 0;

    // "Parse" the result text; we want to snip off the trailing OK or ERROR line
    // Rewind past the possible trailing CRLF so that we can strip it
    --dest;
    while (dest > resp && (dest[0] == '\n' || dest[0] == '\r')) {
        *dest = 0;
        --dest;
    }

    // Look back for start of preceeding line
    char *last_line = strrchr(resp, '\n');
    if (last_line) {
        ++last_line;
    } else {
        last_line = resp;
    }

    bool              success       = false;
    static const char kOK[] PROGMEM = "OK";

    success = !strcmp_P(last_line, kOK);

    if (verbose || !success) {
        dprintf("result: %s\n", resp);
    }
    return success;
}

static bool at_command(const char *cmd, char *resp, uint16_t resplen, bool verbose, uint16_t timeout) {
    const char *    end = cmd + strlen(cmd);
    struct sdep_msg msg;

    if (verbose) {
        dprintf("ble send: %s\n", cmd);
    }

    if (resp) {
        // They want to decode the response, so we need to flush and wait
        // for all pending I/O to finish before we start this one, so
        // that we don't confuse the results
        resp_buf_wait(cmd);
        *resp = 0;
    }

    // Fragment the command into a series of SDEP packets
    while (end - cmd > SdepMaxPayload) {
        sdep_build_pkt(&msg, BleAtWrapper, (uint8_t *)cmd, SdepMaxPayload, true);
        if (!sdep_send_pkt(&msg, timeout)) {
            return false;
        }
        cmd += SdepMaxPayload;
    }

    sdep_build_pkt(&msg, BleAtWrapper, (uint8_t *)cmd, end - cmd, false);
    if (!sdep_send_pkt(&msg, timeout)) {
        return false;
    }

    if (resp == NULL) {
        auto now = timer_read();
        while (!resp_buf.enqueue(now)) {
            resp_buf_read_one(false);
        }
        auto later = timer_read();
        if (TIMER_DIFF_16(later, now) > 0) {
            dprintf("waited %dms for resp_buf\n", TIMER_DIFF_16(later, now));
        }
        return true;
    }

    return read_response(resp, resplen, verbose);
}

bool at_command_P(const char *cmd, char *resp, uint16_t resplen, bool verbose) {
    auto cmdbuf = (char *)alloca(strlen_P(cmd) + 1);
    strcpy_P(cmdbuf, cmd);
    return at_command(cmdbuf, resp, resplen, verbose);
}

bool adafruit_ble_is_connected(void) { return state.is_connected; }

bool adafruit_ble_enable_keyboard(void) {
    char resbuf[128];

    if (!state.initialized && !ble_init()) {
        return false;
    }

    state.configured = false;

    // Disable command echo
    static const char kEcho[] PROGMEM = "ATE=0";
    // Make the advertised name match the keyboard
    static const char kGapDevName[] PROGMEM = "AT+GAPDEVNAME=" STR(PRODUCT);
    // Turn on keyboard support
    static const char kHidEnOn[] PROGMEM = "AT+BLEHIDEN=1";

    // Adjust intervals to improve latency.  This causes the "central"
    // system (computer/tablet) to poll us every 10-30 ms.  We can't
    // set a smaller value than 10ms, and 30ms seems to be the natural
    // processing time on my macbook.  Keeping it constrained to that
    // feels reasonable to type to.
    static const char kGapIntervals[] PROGMEM = "AT+GAPINTERVALS=10,30,,";

    // Reset the device so that it picks up the above changes
    static const char kATZ[] PROGMEM = "ATZ";

    // Turn down the power level a bit
    static const char  kPower[] PROGMEM             = "AT+BLEPOWERLEVEL=-12";
    static PGM_P const configure_commands[] PROGMEM = {
        kEcho, kGapIntervals, kGapDevName, kHidEnOn, kPower, kATZ,
    };

    uint8_t i;
    for (i = 0; i < sizeof(configure_commands) / sizeof(configure_commands[0]); ++i) {
        PGM_P cmd;
        memcpy_P(&cmd, configure_commands + i, sizeof(cmd));

        if (!at_command_P(cmd, resbuf, sizeof(resbuf))) {
            dprintf("failed BLE command: %S: %s\n", cmd, resbuf);
            goto fail;
        }
    }

    state.configured = true;

    // Check connection status in a little while; allow the ATZ time
    // to kick in.
    state.last_connection_update = timer_read();
fail:
    return state.configured;
}

static void set_connected(bool connected) {
    if (connected != state.is_connected) {
        if (connected) {
            print("****** BLE CONNECT!!!!\n");
        } else {
            print("****** BLE DISCONNECT!!!!\n");
        }
        state.is_connected = connected;

        // TODO: if modifiers are down on the USB interface and
        // we cut over to BLE or vice versa, they will remain stuck.
        // This feels like a good point to do something like clearing
        // the keyboard and/or generating a fake all keys up message.
        // However, I've noticed that it takes a couple of seconds
        // for macOS to to start recognizing key presses after BLE
        // is in the connected state, so I worry that doing that
        // here may not be good enough.
    }
}

void adafruit_ble_task(void) {
    char resbuf[48];

    if (!state.configured && !adafruit_ble_enable_keyboard()) {
        return;
    }
    resp_buf_read_one(true);
    send_buf_send_one(SdepShortTimeout);

    if (resp_buf.empty() && (state.event_flags & UsingEvents) && readPin(AdafruitBleIRQPin)) {
        // Must be an event update
        if (at_command_P(PSTR("AT+EVENTSTATUS"), resbuf, sizeof(resbuf))) {
            uint32_t mask = strtoul(resbuf, NULL, 16);

            if (mask & BleSystemConnected) {
                set_connected(true);
            } else if (mask & BleSystemDisconnected) {
                set_connected(false);
            }
        }
    }

    if (timer_elapsed(state.last_connection_update) > ConnectionUpdateInterval) {
        bool shouldPoll = true;
        if (!(state.event_flags & ProbedEvents)) {
            // Request notifications about connection status changes.
            // This only works in SPIFRIEND firmware > 0.6.7, which is why
            // we check for this conditionally here.
            // Note that at the time of writing, HID reports only work correctly
            // with Apple products on firmware version 0.6.7!
            // https://forums.adafruit.com/viewtopic.php?f=8&t=104052
            if (at_command_P(PSTR("AT+EVENTENABLE=0x1"), resbuf, sizeof(resbuf))) {
                at_command_P(PSTR("AT+EVENTENABLE=0x2"), resbuf, sizeof(resbuf));
                state.event_flags |= UsingEvents;
            }
            state.event_flags |= ProbedEvents;

            // leave shouldPoll == true so that we check at least once
            // before relying solely on events
        } else {
            shouldPoll = false;
        }

        static const char kGetConn[] PROGMEM = "AT+GAPGETCONN";
        state.last_connection_update         = timer_read();

        if (at_command_P(kGetConn, resbuf, sizeof(resbuf))) {
            set_connected(atoi(resbuf));
        }
    }

#ifdef SAMPLE_BATTERY
    if (timer_elapsed(state.last_battery_update) > BatteryUpdateInterval && resp_buf.empty()) {
        state.last_battery_update = timer_read();

        state.vbat = analogRead(BATTERY_LEVEL_PIN);
    }
#endif
}

static bool process_queue_item(struct queue_item *item, uint16_t timeout) {
    char cmdbuf[48];
    char fmtbuf[64];

    // Arrange to re-check connection after keys have settled
    state.last_connection_update = timer_read();

#if 1
    if (TIMER_DIFF_16(state.last_connection_update, item->added) > 0) {
        dprintf("send latency %dms\n", TIMER_DIFF_16(state.last_connection_update, item->added));
    }
#endif

    switch (item->queue_type) {
        case QTKeyReport:
            strcpy_P(fmtbuf, PSTR("AT+BLEKEYBOARDCODE=%02x-00-%02x-%02x-%02x-%02x-%02x-%02x"));
            snprintf(cmdbuf, sizeof(cmdbuf), fmtbuf, item->key.modifier, item->key.keys[0], item->key.keys[1], item->key.keys[2], item->key.keys[3], item->key.keys[4], item->key.keys[5]);
            return at_command(cmdbuf, NULL, 0, true, timeout);

        case QTConsumer:
            strcpy_P(fmtbuf, PSTR("AT+BLEHIDCONTROLKEY=0x%04x"));
            snprintf(cmdbuf, sizeof(cmdbuf), fmtbuf, item->consumer);
            return at_command(cmdbuf, NULL, 0, true, timeout);

#ifdef MOUSE_ENABLE
        case QTMouseMove:
            strcpy_P(fmtbuf, PSTR("AT+BLEHIDMOUSEMOVE=%d,%d,%d,%d"));
            snprintf(cmdbuf, sizeof(cmdbuf), fmtbuf, item->mousemove.x, item->mousemove.y, item->mousemove.scroll, item->mousemove.pan);
            if (!at_command(cmdbuf, NULL, 0, true, timeout)) {
                return false;
            }
            strcpy_P(cmdbuf, PSTR("AT+BLEHIDMOUSEBUTTON="));
            if (item->mousemove.buttons & MOUSE_BTN1) {
                strcat(cmdbuf, "L");
            }
            if (item->mousemove.buttons & MOUSE_BTN2) {
                strcat(cmdbuf, "R");
            }
            if (item->mousemove.buttons & MOUSE_BTN3) {
                strcat(cmdbuf, "M");
            }
            if (item->mousemove.buttons == 0) {
                strcat(cmdbuf, "0");
            }
            return at_command(cmdbuf, NULL, 0, true, timeout);
#endif
        default:
            return true;
    }
}

bool adafruit_ble_send_keys(uint8_t hid_modifier_mask, uint8_t *keys, uint8_t nkeys) {
    struct queue_item item;
    bool              didWait = false;

    item.queue_type   = QTKeyReport;
    item.key.modifier = hid_modifier_mask;
    item.added        = timer_read();

    while (nkeys >= 0) {
        item.key.keys[0] = keys[0];
        item.key.keys[1] = nkeys >= 1 ? keys[1] : 0;
        item.key.keys[2] = nkeys >= 2 ? keys[2] : 0;
        item.key.keys[3] = nkeys >= 3 ? keys[3] : 0;
        item.key.keys[4] = nkeys >= 4 ? keys[4] : 0;
        item.key.keys[5] = nkeys >= 5 ? keys[5] : 0;

        if (!send_buf.enqueue(item)) {
            if (!didWait) {
                dprint("wait for buf space\n");
                didWait = true;
            }
            send_buf_send_one();
            continue;
        }

        if (nkeys <= 6) {
            return true;
        }

        nkeys -= 6;
        keys += 6;
    }

    return true;
}

bool adafruit_ble_send_consumer_key(uint16_t keycode, int hold_duration) {
    struct queue_item item;

    item.queue_type = QTConsumer;
    item.consumer   = keycode;

    while (!send_buf.enqueue(item)) {
        send_buf_send_one();
    }
    return true;
}

#ifdef MOUSE_ENABLE
bool adafruit_ble_send_mouse_move(int8_t x, int8_t y, int8_t scroll, int8_t pan, uint8_t buttons) {
    struct queue_item item;

    item.queue_type        = QTMouseMove;
    item.mousemove.x       = x;
    item.mousemove.y       = y;
    item.mousemove.scroll  = scroll;
    item.mousemove.pan     = pan;
    item.mousemove.buttons = buttons;

    while (!send_buf.enqueue(item)) {
        send_buf_send_one();
    }
    return true;
}
#endif

uint32_t adafruit_ble_read_battery_voltage(void) { return state.vbat; }

bool adafruit_ble_set_mode_leds(bool on) {
    if (!state.configured) {
        return false;
    }

    // The "mode" led is the red blinky one
    at_command_P(on ? PSTR("AT+HWMODELED=1") : PSTR("AT+HWMODELED=0"), NULL, 0);

    // Pin 19 is the blue "connected" LED; turn that off too.
    // When turning LEDs back on, don't turn that LED on if we're
    // not connected, as that would be confusing.
    at_command_P(on && state.is_connected ? PSTR("AT+HWGPIO=19,1") : PSTR("AT+HWGPIO=19,0"), NULL, 0);
    return true;
}

// https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le/ble-generic#at-plus-blepowerlevel
bool adafruit_ble_set_power_level(int8_t level) {
    char cmd[46];
    if (!state.configured) {
        return false;
    }
    snprintf(cmd, sizeof(cmd), "AT+BLEPOWERLEVEL=%d", level);
    return at_command(cmd, NULL, 0, false);
}
