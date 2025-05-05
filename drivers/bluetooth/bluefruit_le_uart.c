/* Copyright 2021 Kan-Ru Chen <kanru@kanru.info>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "bluefruit_le.h"
#include "bluefruit_le_uart.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alloca.h>
#include "uart.h"
#include "debug.h"
#include "timer.h"
#include "progmem.h"

#define TIMEOUT 100
#define SAMPLE_BATTERY
#define BATTERY_FULL 550
#define BATTERY_EMPTY 326
#define ConnectionUpdateInterval 1000 /* milliseconds */
#define BatteryLevelUpdateInterval 60000

#ifndef NRF51_BAUD_RATE
#    define NRF51_BAUD_RATE 76800
#endif

#ifdef SAMPLE_BATTERY
bool bluefruit_le_set_battery_level(uint8_t level);
#endif

static struct {
    bool is_connected;
    bool initialized;
    bool configured;

#ifdef SAMPLE_BATTERY
    uint16_t last_battery_update;
#endif
    uint16_t last_connection_update;
} state;

// Using a queue for the AT commands because reading the RX requires
// interrupt so can not be done in USB interrupt handler
enum queue_type {
    QTKeyReport,  // 1-byte modifier + 6-byte key report
    QTConsumer,   // 16-bit key code
#ifdef MOUSE_ENABLE
    QTMouseMove,  // 4-byte mouse report
#endif
};

struct queue_item {
    enum queue_type queue_type;
    union __attribute__((packed)) {
        struct __attribute__((packed)) {
            uint8_t modifier;
            uint8_t keys[6];
        } key;
        uint16_t consumer;
#ifdef MOUSE_ENABLE
        struct __attribute__((packed)) {
            int8_t  x, y, scroll, pan;
            uint8_t buttons;
        } mousemove;
#endif
    };
};

#define QUEUE_SIZE 32

struct circ_buf {
    struct queue_item buf[QUEUE_SIZE];
    uint8_t           head;
    uint8_t           tail;
} send_queue;

/* Return count in buffer.  */
#define CIRC_CNT(head, tail, size) (((head) - (tail)) & ((size)-1))
/* Return space available, 0..size-1.  We always leave one free char
   as a completely full buffer has head == tail, which is the same as
   empty.  */
#define CIRC_SPACE(head, tail, size) CIRC_CNT((tail), ((head) + 1), (size))

static bool enqueue(struct circ_buf *queue, struct queue_item *item) {
    uint8_t head = queue->head;
    uint8_t tail = queue->tail;
    if (CIRC_SPACE(head, tail, QUEUE_SIZE) > 0) {
        queue->buf[head] = *item;
        queue->head      = (head + 1) & (QUEUE_SIZE - 1);
        return true;
    }
    return false;
}

static bool dequeue(struct circ_buf *queue, struct queue_item *item) {
    uint8_t head = queue->head;
    uint8_t tail = queue->tail;
    if (CIRC_CNT(head, tail, QUEUE_SIZE) > 0) {
        *item       = queue->buf[tail];
        queue->tail = (tail + 1) & (QUEUE_SIZE - 1);
        return true;
    }
    return false;
}

static bool process_queue_item(struct queue_item *item);

void bluefruit_le_init(void) {
    state.initialized  = false;
    state.configured   = false;
    state.is_connected = false;
    send_queue.head    = 0;
    send_queue.tail    = 0;

    uart_init(NRF51_BAUD_RATE);

    state.initialized = true;
    return;
}

static int16_t uart_read_nonblocking(void) {
    if (uart_available()) {
        return uart_read();
    }

    return -1;
}

static void uart_gets(char *resp, uint16_t resplen, uint16_t timeout) {
    uint16_t t = timer_read();
    uint8_t  i = 0;
    int16_t  c;
    memset(resp, 0, resplen);
    while (i < resplen && timer_elapsed(t) < timeout) {
        if ((c = uart_read_nonblocking()) != -1) {
            if ((char)c == '\r') continue;
            if ((char)c == '\n') break;
            resp[i++] = c;
        }
    }
}

static bool at_command(const char *cmd, size_t len, char *resp, uint16_t resplen) {
    char ok[32];
    uart_transmit((uint8_t *)cmd, len);
    uart_write('\n');
    if (resplen) {
        uart_gets(resp, resplen, TIMEOUT);
        if (memcmp_P(resp, PSTR("ERROR"), 5) == 0) {
            return false;
        }
        if (memcmp_P(resp, PSTR("OK"), 2) == 0) {
            return true;
        }
    }

    uart_gets(ok, sizeof(ok), TIMEOUT);
    return (memcmp_P(resp, PSTR("OK"), 2) == 0);
}

static bool at_command_P(const char *cmd, char *resp, uint16_t resplen) {
    size_t len    = strlen_P(cmd) + 1;
    char * cmdbuf = (char *)alloca(len);
    memcpy_P(cmdbuf, cmd, len);
    return at_command(cmdbuf, len, resp, resplen);
}

bool bluefruit_le_enable_keyboard(void) {
    char resbuf[128];

    if (!state.initialized) {
        bluefruit_le_init();
        if (!state.initialized) {
            return false;
        }
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

    // Turn down the power level a bit
    static const char kPower[] PROGMEM = "AT+BLEPOWERLEVEL=-12";

#ifdef SAMPLE_BATTERY
    // Enable battery service
    static const char kBattEn[] PROGMEM = "AT+BLEBATTEN=1";
#endif

    // Reset the device so that it picks up the above changes
    static const char kATZ[] PROGMEM = "ATZ";

    static PGM_P const configure_commands[] PROGMEM = {
        kEcho,   kGapIntervals, kGapDevName, kHidEnOn, kPower,
#ifdef SAMPLE_BATTERY
        kBattEn,
#endif
        kATZ,
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
    state.last_battery_update    = 0;
fail:
    return state.configured;
}

bool bluefruit_le_is_connected() { return state.is_connected; }

static void set_connected(bool connected) {
    if (connected != state.is_connected) {
        state.is_connected = connected;
    }
}

void bluefruit_le_task(void) {
    char              resbuf[48];
    struct queue_item item;

    if (!state.configured && !bluefruit_le_enable_keyboard()) {
        return;
    }

    if (dequeue(&send_queue, &item)) {
        process_queue_item(&item);
    }

    if (timer_elapsed(state.last_connection_update) > ConnectionUpdateInterval) {
        static const char kGetConn[] PROGMEM = "AT+GAPGETCONN";
        state.last_connection_update         = timer_read();

        if (at_command_P(kGetConn, resbuf, sizeof(resbuf))) {
            set_connected(atoi(resbuf));
        }
    }

    if (timer_elapsed(state.last_battery_update) > BatteryLevelUpdateInterval) {
        state.last_battery_update = timer_read();

        uint8_t level = (bluefruit_le_read_battery_voltage() - BATTERY_EMPTY) / (float)(BATTERY_FULL - BATTERY_EMPTY) * 100;
        bluefruit_le_set_battery_level(level);
    }
}

static bool process_queue_item(struct queue_item *item) {
    char cmdbuf[48];

    // Arrange to re-check connection after keys have settled
    state.last_connection_update = timer_read();

    size_t len = 0;
    switch (item->queue_type) {
        case QTKeyReport:
            len = snprintf_P(cmdbuf, sizeof(cmdbuf), PSTR("AT+BLEKEYBOARDCODE=%02x-00-%02x-%02x-%02x-%02x-%02x-%02x"), item->key.modifier, item->key.keys[0], item->key.keys[1], item->key.keys[2], item->key.keys[3], item->key.keys[4], item->key.keys[5]);
            return at_command(cmdbuf, len, NULL, 0);

        case QTConsumer:
            len = snprintf_P(cmdbuf, sizeof(cmdbuf), PSTR("AT+BLEHIDCONTROLKEY=0x%04x"), item->consumer);
            return at_command(cmdbuf, len, NULL, 0);

#ifdef MOUSE_ENABLE
        case QTMouseMove:
            len = snprintf_P(cmdbuf, sizeof(cmdbuf), PSTR("AT+BLEHIDMOUSEMOVE=%d,%d,%d,%d"), item->mousemove.x, item->mousemove.y, item->mousemove.scroll, item->mousemove.pan);
            if (!at_command(cmdbuf, len, NULL, 0)) {
                return false;
            }
            len = snprintf_P(cmdbuf, sizeof(cmdbuf), PSTR("AT+BLEHIDMOUSEBUTTON=%d"), item->mousemove.buttons);
            return at_command(cmdbuf, len, NULL, 0);
#endif
        default:
            return true;
    }
}

void bluefruit_le_send_keyboard(report_keyboard_t *report) {
    struct queue_item item;

    item.queue_type   = QTKeyReport;
    item.key.modifier = report->mods;
    item.key.keys[0]  = report->keys[0];
    item.key.keys[1]  = report->keys[1];
    item.key.keys[2]  = report->keys[2];
    item.key.keys[3]  = report->keys[3];
    item.key.keys[4]  = report->keys[4];
    item.key.keys[5]  = report->keys[5];

    enqueue(&send_queue, &item);

    return;
}

void bluefruit_le_send_consumer(uint16_t usage) {
    struct queue_item item;

    item.queue_type = QTConsumer;
    item.consumer   = usage;

    enqueue(&send_queue, &item);
}

#ifdef MOUSE_ENABLE
void bluefruit_le_send_mouse(report_mouse_t *report) {
    struct queue_item item;

    item.queue_type        = QTMouseMove;
    item.mousemove.x       = report->x;
    item.mousemove.y       = report->y;
    item.mousemove.scroll  = report->v;
    item.mousemove.pan     = report->h;
    item.mousemove.buttons = report->buttons;

    enqueue(&send_queue, &item);
}
#endif

uint32_t bluefruit_le_read_battery_voltage(void) {
    char resbuf[8];
    if (!state.configured) {
        return 0;
    }
    if (at_command_P(PSTR("AT+HWADC=6"), resbuf, sizeof(resbuf))) {
        return atoi(resbuf);
    }
    return 0;
}

bool bluefruit_le_set_battery_level(uint8_t level) {
    size_t len = 0;
    char cmd[32];
    if (!state.configured) {
        return false;
    }
    len = snprintf_P(cmd, sizeof(cmd), PSTR("AT+BLEBATTVAL=%d"), level);
    return at_command(cmd, len, NULL, 0);
}

bool bluefruit_le_delbonds(void) {
    if (!state.configured) {
        return false;
    }
    return at_command_P(PSTR("AT+GAPDELBONDS"), NULL, 0);
}

bool bluefruit_le_reconnect(void) {
    if (!state.configured) {
        return false;
    }
    if (!at_command_P(PSTR("AT+GAPDISCONNECT"), NULL, 0)) {
        return false;
    }
    return at_command_P(PSTR("AT+GAPSTARTADV"), NULL, 0);
}
