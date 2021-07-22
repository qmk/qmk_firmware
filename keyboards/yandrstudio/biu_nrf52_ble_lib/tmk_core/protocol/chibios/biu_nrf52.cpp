#include "biu_ble_common.h"
#include "report.h"
#include "timer.h"
#include "wait.h"
#include "uart.h"
#include "gpio.h"
#include "print.h"
#include "analog.h"
#include "keycode.h"
#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ring_buffer.hpp"



// These are the pin assignments for the stm32f401ccu6 boards.
// You may define them to something else in your config.h
// if yours is wired up differently.

// NRF RESET, WakeUp
#ifndef BIUNRF52ResetPin
#    define BIUNRF52ResetPin A1
#endif
#ifndef BIUNRF52WKPin
#    define BIUNRF52WKPin A3
#endif

// UART SETTING
#ifndef BIUNRF52RxPin
#    define BIUNRF52RxPin A10
#endif
#ifndef BIUNRF52TxPin
#    define BIUNRF52TxPin A9
#endif
#ifndef BIUNRF52UartBaud
#    define BIUNRF52UartBaud 115200
#endif

// ADC SETTING
#define SAMPLE_BATTERY
#ifndef BATTERY_LEVEL_PIN
#    define BATTERY_LEVEL_PIN B0 // Adc pin
#endif
// #ifndef BATTERY_LEVEL_SW_PIN
// #    define BATTERY_LEVEL_SW_PIN A1 // Adc pin
// #endif

#ifndef BATTERY_V_HEI
#    define BATTERY_V_HEI 3750 // 3.75V
#endif
#ifndef BATTERY_V_LOW
#    define BATTERY_V_LOW 3500 // 3.5V
#endif
#ifndef BATTERY_V_MAX
#    define BATTERY_V_MAX 5000 // 5V
#endif
#ifndef BATTERY_ADC_MAX
#    define BATTERY_ADC_MAX 3080
#endif

// TIMEOUT INTERVAL SETTING
#define BiuNrf52MsgTimeout               150           /* milliseconds  */
#define BiuNrf52MsgShortTimeout          10            /* milliseconds  */
#define BiuNrf52MsgRecvTimeout           2000          /* 2 second      */

#define BiuNrf52ResetTimeout             30000          /* 30 second    */
#define BiuNrf52InitTimeout              1500           /* 1.5 second   */
#define BiuNrf52KeepConnectionTimeout    30000          /* 30 second    */
#define BiuNrf52SystemOffTimeoutFast     120000         /* 2 minute     */
#define BiuNrf52SystemOffTimeout         120000         /* 5 minute     */
// #define BiuNrf52SystemOffTimeout         300000         /* 5 minute     */
#define BatteryUpdateInterval            60000          /* 1 minute     */

#define BiuStm32IdleTimeout              5000           /* 3 second     */


enum ble_msg_ht {
    BleUartHead     = 0xFF,
    BleUartTail     = 0xFE,
};

#define BiuNrf52MsgMaxPayload 64
struct biunrf52_msg {
    uint8_t type;
    uint8_t len;
    uint8_t payload[BiuNrf52MsgMaxPayload];
} __attribute__((packed));

enum queue_type {
    QTNrfSysOff,
    QTAskNrf,
    QTKeepConn,
    QTStartAdv,
    QTStopAdv,
    QTDelAllDev,
    QTDelDev,
    QTSwDev,
    QTBatVMsg,
    QTKeyReport,  // 1-byte modifier + 6-byte key report
#ifdef EXTRAKEY_ENABLE
    QTConsumer,   // 16-bit key code
    QTSystem,
#endif

#ifdef MOUSE_ENABLE
    QTMouseMove,  // 5-byte report
#endif

#ifdef NKRO_ENABLE
    QTNkro,  // KEYBOARD_REPORT_BITS+1 byte report
#endif

#ifdef JOYSTICK_ENABLE
    QTJoyStick,  // xx-byte report
#endif
};

struct queue_item {
    enum queue_type queue_type;
    uint32_t        added;
    union __attribute__((packed)) {
        uint8_t bat_lev;
        uint8_t device_id;
        struct __attribute__((packed)) {
            uint8_t modifier;
            uint8_t keys[6];
        } key;
#ifdef EXTRAKEY_ENABLE
        struct __attribute__((packed)) {
            uint8_t consumer_h, consumer_l;
        } extkey;
#endif
#ifdef MOUSE_ENABLE
        struct __attribute__((packed)) {
            uint8_t buttons;
            int8_t  x, y, v, h;
        } mousemove;
#endif
#ifdef NKRO_ENABLE
        struct __attribute__((packed)) {
            uint8_t mods;
            uint8_t bits[KEYBOARD_REPORT_BITS]; // for chibios, it is 32-2
        } nkey;
#endif
    };
};

/* HID report INDEXs */
enum hid_report_index {
    REPORT_INDEX_KEYBOARD = 0,
    REPORT_INDEX_MOUSE,   // 1
    REPORT_INDEX_SYSTEM,  // 2
    REPORT_INDEX_CONSUMER,// 3
    REPORT_INDEX_NKRO,    //4
    REPORT_INDEX_JOYSTICK // 5
};

enum ble_command_biu {
      START_ADV_WITH_WL = 6,
      START_ADV_WITHOUT_WL, // 7
      STOP_ADV, // 8
      DEL_ALL_BOUND, // 9
      DEL_BOUND, // 10 0a
      DEL_CURR_BOUND, // 11 0b
      SWITCH_BOUND, // 12 0c
      BLE_DEL_AND_ADV, // = 13 // 0d ble reset
      SET_TX_POWER, // 14 0e
      ENTER_INTO_SLEEP_MODEL, // 15 0f
      USER_DEBUG_INFO, // 16 (10)
      GET_BAT_INFO,     // 17 (11)
      ASK_CURRENT_NRF_STATE, // 18 (12)
};

enum ble_state_biu {
  NRF_WORKING    = 1,
  NRF_DISCONNECT = 2,
  NRF_ADVING     = 3,
  NRF_ERROR      = 0xee
};

static struct {
    bool is_connected;
    bool initialized;
    bool configured;
    bool is_sleeped;
    bool start_wakeup;
#ifdef SAMPLE_BATTERY
    uint32_t last_battery_update;
    uint32_t vbat;
#endif
    uint32_t last_connection_update;
    uint32_t last_system_off_update;
    uint32_t last_reset_update;
    uint32_t keep_connection_update;
    bool has_send_ask;
} state;

// Items that we wish to send , 128+1, must has an empty pos
static RingBuffer<queue_item, 129> send_buf;
// Pending response; while pending, we can't send any more requests.
// This records the time at which we sent the command for which we
// are expecting a response.
static RingBuffer<uint32_t, 8> resp_buf;

void bluetooth_clear_buf(void) {
    send_buf.clear();
    resp_buf.clear();
}

static void clear_uart_rx_buffer(void) {
    while (!sdGetWouldBlock(&SERIAL_DRIVER)) {
        uint8_t a  = uart_getchar();
    }
}
// Read a single SDEP packet
static bool receive_a_pkt(struct biunrf52_msg *msg, uint16_t timeout) {
    uint16_t timerStart = timer_read32();
    bool     ready      = false;

    do {
        ready = !sdGetWouldBlock(&SERIAL_DRIVER);
        if (ready) {
            break;
        }
        wait_ms(BiuNrf52MsgShortTimeout);
    } while (timer_elapsed(timerStart) < timeout);

    if (ready) {
        if (uart_getchar() == BleUartHead) {
            if (!sdGetWouldBlock(&SERIAL_DRIVER)) {
                msg->type = uart_getchar();
            }
            if (!sdGetWouldBlock(&SERIAL_DRIVER)) {
                msg->len = uart_getchar();
            }
            if (msg->len > BiuNrf52MsgMaxPayload) {
                clear_uart_rx_buffer();
                return false;
            }
            for (uint8_t i = 0; i < msg->len; ++i) {
                if (!sdGetWouldBlock(&SERIAL_DRIVER)) {
                    msg->payload[i] = uart_getchar();
                } else {
                    return false;
                }
            }
            if (!sdGetWouldBlock(&SERIAL_DRIVER)) {
                if(uart_getchar() != BleUartTail) {
                    clear_uart_rx_buffer();
                    return false;
                }
            } else {
                clear_uart_rx_buffer();
                return false;
            }
        } else {
            clear_uart_rx_buffer();
            return false;
        }
        return true;
    }
    return false;
}


static void process_nrf_ack_msg(struct biunrf52_msg * msg) {
    switch (msg->type)
    {
    case NRF_WORKING:
        state.initialized  = true;
        state.configured   = true;
        state.is_connected = true;
        state.is_sleeped   = false;
        break;
    case NRF_DISCONNECT:
    case NRF_ADVING:
        state.initialized  = true;
        state.configured   = true;
        state.is_connected = false;
        state.is_sleeped   = false;
        break;
    default:
        state.initialized  = false;
        state.is_connected = false;
        state.configured   = false;
        state.is_sleeped   = false;
        break;
    }
}
static void resp_buf_read_one() {
    uint32_t last_send;
    struct biunrf52_msg msg;

    // if empty, then do nothing
    if (!resp_buf.peek(last_send)) {
        return;
    }

    // determine whether uart_get is possible
    if (uart_available()) {
        if (receive_a_pkt(&msg, BiuNrf52MsgTimeout)) {
            dprintf("recv latency %dms, resp_buf size %d\n", TIMER_DIFF_32(timer_read32(), last_send), (int)resp_buf.size());
            resp_buf.get(last_send);
            process_nrf_ack_msg(&msg);
        } else {
            dprintf("Some thing wrong, resp_buf size %d\n", (int)resp_buf.size());
            // Receive Wrong: consume this entry
            resp_buf.get(last_send);
            state.initialized  = false;
            state.is_connected = false;
            state.configured   = false;
            state.is_sleeped   = false;
        }
    } else {
        dprintf("Uart get buffer is empty, resp_buf size %d\n", (int)resp_buf.size());
        // Timed out: consume this entry
        resp_buf.get(last_send);
    }
}


static bool send_a_pkt(const char *cmd, uint8_t cmd_len, uint16_t timeout, bool need_ack = false, bool need_update_conn_time = true) {
    if (need_update_conn_time) {
        state.last_connection_update = timer_read32();
    }

    uint16_t timerStart = timer_read32();
    bool     ready      = false;

    dprint("BLE SEND: ");
    for (uint8_t i = 0; i<cmd_len; ++i) {
        dprintf("%#X ", cmd[i]);
    }
    dprint("\n");

    if (cmd_len >= BiuNrf52MsgMaxPayload) {
        dprintf("ble send data to long: %d, maxlen is %d\n", cmd_len, BiuNrf52MsgMaxPayload);
        return false;
    }

    do {
        // some to confirm the uart is start and can put new data
        ready = !sdPutWouldBlock(&SERIAL_DRIVER);
        if (ready) {
            break;
        }
        wait_ms(BiuNrf52MsgShortTimeout);
    } while (timer_elapsed(timerStart) < timeout);

    if (ready) {
        // uart is ready; send the rest of the packet
        for (uint8_t i = 0; i < cmd_len; ++i) {
            uart_putchar(cmd[i]);
        }
    } else {
        return false;
    }

    if (need_ack) {
        uint32_t now = timer_read32();
        while (!resp_buf.enqueue(now)) {
            resp_buf_read_one();
        }
        dprintf("Put a time into resp buf, resp_buf size %d\n", (int)resp_buf.size());
        uint32_t later = timer_read32();
        if (TIMER_DIFF_32(later, now) > 0) {
            dprintf("waited %dms for resp_buf\n", TIMER_DIFF_32(later, now));
        }
    }

    return true;
}


static bool process_queue_item(struct queue_item *item, uint16_t timeout) {
    char cmdbuf[128] = {0};
    cmdbuf[0] = BleUartHead;

#if 1
    if (TIMER_DIFF_32(timer_read32(), item->added) > 0) {
        dprintf("send latency %dms\n", TIMER_DIFF_32(timer_read32(), item->added));
    }
#endif

    switch (item->queue_type) {
        case QTNrfSysOff:
            cmdbuf[1] = ENTER_INTO_SLEEP_MODEL;
            cmdbuf[2] = BleUartTail;
            return send_a_pkt(cmdbuf, 3, timeout, false, false);
        case QTAskNrf:
            cmdbuf[1] = ASK_CURRENT_NRF_STATE;
            cmdbuf[2] = BleUartTail;
            return send_a_pkt(cmdbuf, 3, timeout, true, true);
        case QTKeepConn:
            cmdbuf[1] = ASK_CURRENT_NRF_STATE;
            cmdbuf[2] = BleUartTail;
            return send_a_pkt(cmdbuf, 3, timeout, true, false); // need ack to update the nrf state, but do not update the connection
        case QTStartAdv:
            cmdbuf[1] = START_ADV_WITH_WL;
            cmdbuf[2] = BleUartTail;
            return send_a_pkt(cmdbuf, 3, timeout, false, false);
        case QTStopAdv:
            cmdbuf[1] = STOP_ADV;
            cmdbuf[2] = BleUartTail;
            state.is_connected = false;
            return send_a_pkt(cmdbuf, 3, timeout, false, false);
        case QTDelAllDev:
            cmdbuf[1] = DEL_ALL_BOUND;
            cmdbuf[2] = BleUartTail;
            state.is_connected = false;
            return send_a_pkt(cmdbuf, 3, timeout, false, false);
        case QTDelDev:
            cmdbuf[1] = DEL_CURR_BOUND;
            cmdbuf[2] = BleUartTail;
            state.is_connected = false;
            return send_a_pkt(cmdbuf, 3, timeout, false, false);
        case QTSwDev:
            cmdbuf[1] = SWITCH_BOUND;
            cmdbuf[2] = item->device_id;
            cmdbuf[3] = BleUartTail;
            return send_a_pkt(cmdbuf, 4, timeout, false, false);
        case QTBatVMsg:
            cmdbuf[1] = GET_BAT_INFO;
            cmdbuf[2] = item->bat_lev;
            cmdbuf[3] = BleUartTail;
            return send_a_pkt(cmdbuf, 4, timeout, false, false); // /don't update the connection time, to avoid never sleeping
        case QTKeyReport:
            cmdbuf[1] = REPORT_INDEX_KEYBOARD;
            cmdbuf[2] = item->key.modifier;
            cmdbuf[3] = 0x00; // reserved
            memcpy(cmdbuf+4, item->key.keys, 6);
            cmdbuf[10] = BleUartTail;
            return send_a_pkt(cmdbuf, 11, timeout); // do not need ack, need update the connection time
#   ifdef EXTRAKEY_ENABLE
        case QTConsumer:   // 16-bit key code
            cmdbuf[1] = REPORT_INDEX_CONSUMER;
            cmdbuf[2] = item->extkey.consumer_l;
            cmdbuf[3] = item->extkey.consumer_h;
            cmdbuf[4] = BleUartTail;
            return send_a_pkt(cmdbuf, 5, timeout);
        case QTSystem:   // 16-bit key code
            cmdbuf[1] = REPORT_INDEX_SYSTEM;
            cmdbuf[2] = item->extkey.consumer_l;
            cmdbuf[3] = item->extkey.consumer_h;
            cmdbuf[4] = BleUartTail;
            return send_a_pkt(cmdbuf, 5, timeout);
#   endif

#   ifdef MOUSE_ENABLE
        case QTMouseMove:  // 5-byte report
            cmdbuf[1] = REPORT_INDEX_MOUSE;
            cmdbuf[2] = item->mousemove.buttons;
            cmdbuf[3] = item->mousemove.x; // int8_t -> uint8_t
            cmdbuf[4] = item->mousemove.y; // int8_t -> uint8_t
            cmdbuf[5] = item->mousemove.v; // int8_t -> uint8_t
            cmdbuf[6] = item->mousemove.h; // int8_t -> uint8_t
            cmdbuf[7] = BleUartTail;
            return send_a_pkt(cmdbuf, 8, timeout);
#   endif

#   ifdef NKRO_ENABLE
        case QTNkro:  // KEYBOARD_REPORT_BITS+1 -byte report
            cmdbuf[1] = REPORT_INDEX_NKRO;
            cmdbuf[2] = item->nkey.mods;
            memcpy(cmdbuf+3, item->nkey.bits, KEYBOARD_REPORT_BITS);
            cmdbuf[KEYBOARD_REPORT_BITS+2+1] = BleUartTail;
            return send_a_pkt(cmdbuf, KEYBOARD_REPORT_BITS+2+1+1, timeout);
#   endif

#   ifdef JOYSTICK_ENABLE
        case QTJoyStick:  // xx-byte report
            cmdbuf[1] = REPORT_INDEX_NKRO;
            cmdbuf[2] = item->nkey.mods;
            memcpy(cmdbuf+3, item->nkey.bits, KEYBOARD_REPORT_BITS);
            cmdbuf[KEYBOARD_REPORT_BITS+2+1] = BleUartTail;
            return send_a_pkt(cmdbuf, KEYBOARD_REPORT_BITS+2+1+1, timeout);
#   endif

        default:
            return false;
    }
}




static void send_buf_send_one(uint16_t timeout = BiuNrf52MsgTimeout) {
    struct queue_item item;

    // Don't send anything more until we get an ACK
    // if (!resp_buf.empty()) {
    //     return;
    // }
    // if empty, then do nothing
    if (!send_buf.peek(item)) {
        return;
    }
    if (process_queue_item(&item, timeout)) {
        // commit that peek
        send_buf.get(item);
        dprintf("send_buf_send_one: have %d remaining\n", (int)send_buf.size());
    } else {
        dprint("failed to send, will retry\n");
        wait_ms(BiuNrf52MsgTimeout);
        resp_buf_read_one();
    }

}

bool bluetooth_send_report_check() {
    if (!state.is_connected) {
        // try wake up module
        bluetooth_wakeup_once();
        return true;
    }
    return false;
}

void bluetooth_send_keyboard(report_keyboard_t *report) {

    if (bluetooth_send_report_check()) return;

    struct queue_item item;

    item.queue_type   = QTKeyReport;
    item.added        = timer_read32();
    item.key.modifier = report->mods;
    memcpy(item.key.keys, report->keys, 6);

    while (!send_buf.enqueue(item)) {
        send_buf_send_one();
    }
}



#ifdef EXTRAKEY_ENABLE
void bluetooth_send_extra(uint8_t report_id, uint16_t data) {

    if (bluetooth_send_report_check()) return;

    struct queue_item item;
    if (report_id == REPORT_ID_SYSTEM) {
        item.queue_type = QTSystem;
    } else {
        item.queue_type = QTConsumer;
    }
    item.added        = timer_read32();
    item.extkey.consumer_h   = (data >> 8) & 0xff;
    item.extkey.consumer_l   = data & 0xff;

    while (!send_buf.enqueue(item)) {
        send_buf_send_one();
    }

}
#endif

#ifdef MOUSE_ENABLE
void bluetooth_send_mouse(report_mouse_t *report) {

    if (bluetooth_send_report_check()) return;

    struct queue_item item;
    item.queue_type        = QTMouseMove;
    item.added        = timer_read32();
    item.mousemove.buttons = report->buttons;
    item.mousemove.x       = report->x;
    item.mousemove.y       = report->y;
    item.mousemove.v       = report->v;
    item.mousemove.h       = report->h;

    while (!send_buf.enqueue(item)) {
        send_buf_send_one();
    }
}
#endif

#ifdef NKRO_ENABLE
void bluetooth_send_keyboard_nkro(report_keyboard_t *report) {

    if (bluetooth_send_report_check()) return;

    struct queue_item item;

    item.queue_type   = QTNkro;
    item.added        = timer_read32();
    item.nkey.mods = report->nkro.mods;
    memcpy(item.nkey.bits, report->nkro.bits, KEYBOARD_REPORT_BITS);

    while (!send_buf.enqueue(item)) {
        send_buf_send_one();
    }
}
#endif

#ifdef JOYSTICK_ENABLE
void bluetooth_send_joystick(joystick_report_t *report) {

    if (bluetooth_send_report_check()) return;


}
#endif

void bluetooth_send_battery_level() {

    if (bluetooth_send_report_check()) return;

#ifdef BATTERY_LEVEL_SW_PIN
    setPinOutput(BATTERY_LEVEL_SW_PIN);
    writePinLow(BATTERY_LEVEL_SW_PIN);
#endif

    uint16_t adc_val = analogReadPinAdc(BATTERY_LEVEL_PIN, 0);
    dprintf("ADC read value:%d \n", adc_val);

#ifdef BATTERY_LEVEL_SW_PIN
    writePinHigh(BATTERY_LEVEL_SW_PIN);
#endif

    uint16_t curr_mv = BATTERY_V_MAX*adc_val/BATTERY_ADC_MAX;
    if (curr_mv <= BATTERY_V_LOW) {
        curr_mv = BATTERY_V_LOW; // bat too low, lower than BATTERY_V_LOW, normaly 3.5v
    }
    uint8_t cur_bat_lev = (curr_mv - BATTERY_V_LOW)*100/(BATTERY_V_HEI-BATTERY_V_LOW);

    struct queue_item item;

    item.queue_type   = QTBatVMsg;
    item.added        = timer_read32();
    item.bat_lev = cur_bat_lev < 10 ? 10 : cur_bat_lev > 100 ? 100 : cur_bat_lev;
    while (!send_buf.enqueue(item)) {
        send_buf_send_one();
    }
}



void connected(void) {
    uprintf("biu ble connected\n");
    // start adv with wl
    struct queue_item item;

    item.queue_type   = QTStartAdv;
    item.added        = timer_read32();
    while (!send_buf.enqueue(item)) {
        send_buf_send_one();
    }
    state.is_connected = true;
}

void disconnected(void) {
    uprintf("biu ble disconnected\n");
    // stop adv
    struct queue_item item;

    item.queue_type   = QTStopAdv;
    item.added        = timer_read32();
    while (!send_buf.enqueue(item)) {
        send_buf_send_one();
    }
    state.is_connected = false;
}

bool bluetooth_is_connected(void) { return state.is_connected; }
bool bluetooth_is_configured(void) { return state.configured; }


void bluetooth_unpair_all(void) {
    uprintf("biu ble del all\n");
    // stop adv and del all
    struct queue_item item;

    item.queue_type   = QTDelAllDev;
    item.added        = timer_read32();
    while (!send_buf.enqueue(item)) {
        send_buf_send_one();
    }
    state.is_connected = false;
}
void bluetooth_unpair_current(void) {
    uprint("biu ble del current\n");
    // stop adv and del one
    struct queue_item item;

    item.queue_type   = QTDelDev;
    item.added        = timer_read32();
    while (!send_buf.enqueue(item)) {
        send_buf_send_one();
    }
    state.is_connected = false;
}

void bluetooth_switch_one(uint8_t device_id) {
    uprintf("biu ble pair %d\n", device_id);
    struct queue_item item;

    item.queue_type   = QTSwDev;
    item.added        = timer_read32();
    item.device_id    = device_id;
    while (!send_buf.enqueue(item)) {
        send_buf_send_one();
    }
    state.is_connected = false;
}

uint8_t bluetooth_working_state(void) {
    if (state.is_sleeped) {
        return SLEEPING;
    }
    if (state.is_connected) {
        return WORKING;
    }
    if (state.configured || state.initialized) {
        return WAITING;
    }
    return STOPWORK;
}


bool bluetooth_init_pre(void) {

    // set the ble state
    state.initialized      = false;
    state.configured       = false;
    state.is_connected     = false;
    state.has_send_ask     = false;
    state.is_sleeped       = false;


    // start the uart data trans
    uart_init(BIUNRF52UartBaud);

    // hang up the reset pin
    palSetLineMode(BIUNRF52ResetPin, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(BIUNRF52ResetPin);
    wait_ms(200);
    palSetLine(BIUNRF52ResetPin);
    wait_ms(3000);
    state.last_reset_update        = 0;
    state.last_battery_update      = 0;
    state.last_connection_update   = 0;
    state.last_system_off_update   = 0;

    // set the adc read sw off
#   ifdef BATTERY_LEVEL_SW_PIN
        setPinOutput(BATTERY_LEVEL_SW_PIN);
        writePinHigh(BATTERY_LEVEL_SW_PIN);
#   endif

    // set wakeup nrf pin
    palSetLineMode(BIUNRF52WKPin, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(BIUNRF52WKPin);

    return true;
}
bool bluetooth_wakeup_helper(void) {

    struct queue_item item;

    if (!state.has_send_ask) {
        dprint("Start Wake Up the  Nrf!!!\n");
        // performance a wakeup
        if (0 == state.last_reset_update|| TIMER_DIFF_32(timer_read32(), state.last_reset_update) >= BiuNrf52ResetTimeout) {
            palClearLine(BIUNRF52WKPin);
            wait_ms(200);
            palSetLine(BIUNRF52WKPin);
            state.last_reset_update = timer_read32();
        }
        item.queue_type   = QTAskNrf;
        item.added        = timer_read32();
        while (!send_buf.enqueue(item)) {
            send_buf_send_one();
        }
        send_buf_send_one();
        state.has_send_ask = true;
    }


    if (TIMER_DIFF_32(timer_read32(), state.last_connection_update) >= BiuNrf52InitTimeout) {
        resp_buf_read_one();
        state.has_send_ask = false;
    }
    return state.initialized;
}

void bluetooth_wakeup_once(void) {
    if (state.is_sleeped) {
        if (false == state.start_wakeup) {
            state.last_reset_update        = 0;
            state.last_battery_update      = 0;
            state.last_connection_update   = 0;
            state.last_system_off_update   = 0;
            bluetooth_clear_buf();
            state.start_wakeup = true;
        }
    }
}


bool bluetooth_init(void) {

    struct queue_item item;

    if (!state.has_send_ask) {
        dprint("Start Init the Nrf!!!\n");
        // performance a reset
        if (0 == state.last_reset_update || TIMER_DIFF_32(timer_read32(), state.last_reset_update) >= BiuNrf52ResetTimeout) {
            palClearLine(BIUNRF52ResetPin);
            wait_ms(200);
            palSetLine(BIUNRF52ResetPin);
            state.last_reset_update = timer_read32();
        }
        item.queue_type   = QTAskNrf;
        item.added        = timer_read32();
        while (!send_buf.enqueue(item)) {
            send_buf_send_one();
        }
        send_buf_send_one();
        state.has_send_ask = true;
    }


    if (TIMER_DIFF_32(timer_read32(), state.last_connection_update) >= BiuNrf52InitTimeout) {
        resp_buf_read_one();
        state.has_send_ask = false;
    }
    return state.initialized;
}


bool biu_ble_enable_keyboard(void) {
    char resbuf[128];

    if (!state.initialized && !bluetooth_init()) {
        return false;
    }

    struct queue_item item;

    if (!state.has_send_ask) {
        dprint("Start Configure the Nrf!!!\n");
        item.queue_type   = QTAskNrf;
        item.added        = timer_read32();
        while (!send_buf.enqueue(item)) {
            send_buf_send_one();
        }
        send_buf_send_one();
        state.has_send_ask = true;
    }


    if (TIMER_DIFF_32(timer_read32(), state.last_connection_update) >= BiuNrf52MsgRecvTimeout) {
        resp_buf_read_one();
        state.has_send_ask = false;
    }

    return state.configured;
}

bool biu_ble_connection_check() {
    if (!state.configured && !biu_ble_enable_keyboard()) {
        return false;
    }

    struct queue_item item;

    if (!state.has_send_ask) {
        dprint("Start Connect the Nrf!!!\n");
        item.queue_type   = QTAskNrf;
        item.added        = timer_read32();
        while (!send_buf.enqueue(item)) {
            send_buf_send_one();
        }
        send_buf_send_one();
        state.has_send_ask = true;
    }


    if (TIMER_DIFF_32(timer_read32(), state.last_connection_update) >= BiuNrf52MsgRecvTimeout) {
        resp_buf_read_one();
        state.has_send_ask = false;
    }

    return state.is_connected;
}

void inline biu_ble_system_off() {

    state.configured    = false;
    state.is_connected  = false;
    state.initialized   = false;
    state.has_send_ask  = false;
    state.is_sleeped    = true;

    state.last_battery_update    = 0;
    state.last_connection_update = 0;
    state.last_system_off_update = 0;
    state.keep_connection_update = 0;



    struct queue_item item;

    item.queue_type   = QTNrfSysOff;
    item.added        = timer_read32();
    while (!send_buf.enqueue(item)) {
        send_buf_send_one();
    }
    send_buf_send_one();
    bluetooth_clear_buf();
}

void inline check_ble_connection_state(void) {
    if (0 == state.keep_connection_update || TIMER_DIFF_32(timer_read32(), state.keep_connection_update) > BiuNrf52KeepConnectionTimeout) {
        struct queue_item item;
        item.queue_type   = QTKeepConn;
        item.added        = timer_read32();
        while (!send_buf.enqueue(item)) {
            send_buf_send_one();
        }
        send_buf_send_one();
        state.keep_connection_update = item.added;
    }
}
void inline check_ble_system_off_timer(void) {
    if (state.is_connected) {
        if (TIMER_DIFF_32(timer_read32(), state.last_connection_update) % 20000 == 1) {
            dprintf("last connection update latency %dms\n", TIMER_DIFF_32(timer_read32(), state.last_connection_update));
        }
        if (TIMER_DIFF_32(timer_read32(), state.last_connection_update) > BiuNrf52SystemOffTimeout) {
            biu_ble_system_off();
        }
    } else {
        if (0 == state.last_system_off_update) { // avoid died after last sysoff
            state.last_system_off_update = timer_read32();
        } else if (TIMER_DIFF_32(timer_read32(), state.last_system_off_update) > BiuNrf52SystemOffTimeoutFast) {
            biu_ble_system_off();
        }
    }
}


void bluetooth_power_manager(void) {

}


bool once_print = false;
void bluetooth_task(void) {
    char resbuf[128];
    if (!state.is_sleeped) {
        if (state.is_connected || biu_ble_connection_check()) {
            resp_buf_read_one();
            send_buf_send_one(BiuNrf52MsgTimeout);
        }
        check_ble_system_off_timer();
        check_ble_connection_state();
#ifdef SAMPLE_BATTERY
        if (state.initialized) {
            if (timer_elapsed32(state.last_battery_update) > BatteryUpdateInterval) {
                state.last_battery_update = timer_read32();
                bluetooth_send_battery_level();
            }
        }
#endif
    } else {
        if (state.start_wakeup) {
            if (once_print == false) {
                dprint("Wake Up module!!!!!!!!\n");
                once_print = true;
            }
            if (bluetooth_wakeup_helper()) {
                state.start_wakeup = false;
                state.is_sleeped   = false;
            }
        }
        // todo wake up
    }
}
