/* Copyright 2022 @ lokher (https://www.keychron.com)
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

#include "quantum.h"
#include "bluetooth.h"
#include "report_buffer.h"
#include "lpm.h"
#include "battery.h"
#include "indicator.h"
#include "transport.h"

extern uint8_t         pairing_indication;
extern host_driver_t   chibios_driver;
extern report_buffer_t kb_rpt;
extern uint32_t        retry_time_buffer;
extern uint8_t         retry;

static uint8_t host_index = 0;
static uint8_t led_state  = 0;

extern bluetooth_transport_t bluetooth_transport;
static bluetooth_state_t bt_state                  = BLUETOOTH_RESET;
static bool              pincodeEntry              = false;
uint8_t                  bluetooth_report_protocol = true;

/* declarations */
uint8_t bluetooth_keyboard_leds(void);
void    bluetooth_send_keyboard(report_keyboard_t *report);
void    bluetooth_send_mouse(report_mouse_t *report);
void    bluetooth_send_system(uint16_t data);
void    bluetooth_send_consumer(uint16_t data);
/* host struct */
host_driver_t bluetooth_driver = {bluetooth_keyboard_leds, bluetooth_send_keyboard, bluetooth_send_mouse, bluetooth_send_system, bluetooth_send_consumer};

#define BLUETOOTH_EVENT_QUEUE_SIZE 16
bluetooth_event_t bt_event_queue[BLUETOOTH_EVENT_QUEUE_SIZE];
uint8_t           bt_event_queue_head;
uint8_t           bt_event_queue_tail;

void bluetooth_bt_event_queue_init(void) {
    // Initialise the event queue
    memset(&bt_event_queue, 0, sizeof(bt_event_queue));
    bt_event_queue_head = 0;
    bt_event_queue_tail = 0;
}

bool bluetooth_event_queue_enqueue(bluetooth_event_t event) {
    uint8_t next = (bt_event_queue_head + 1) % BLUETOOTH_EVENT_QUEUE_SIZE;
    if (next == bt_event_queue_tail) {
        /* Override the first report */
        bt_event_queue_tail = (bt_event_queue_tail + 1) % BLUETOOTH_EVENT_QUEUE_SIZE;
    }
    bt_event_queue[bt_event_queue_head] = event;
    bt_event_queue_head                 = next;
    return true;
}

static inline bool bluetooth_event_queue_dequeue(bluetooth_event_t *event) {
    if (bt_event_queue_head == bt_event_queue_tail) {
        return false;
    }
    *event              = bt_event_queue[bt_event_queue_tail];
    bt_event_queue_tail = (bt_event_queue_tail + 1) % BLUETOOTH_EVENT_QUEUE_SIZE;
    return true;
}

/*
 * Bluetooth init.
 */
void bluetooth_init(void) {
    bt_state = BLUETOOTH_INITIALIZED;

    bluetooth_bt_event_queue_init();
#ifndef DISABLE_REPORT_BUFFER
    report_buffer_init();
#endif
    indicator_init();
#ifdef BLUETOOTH_INT_INPUT_PIN
    setPinInputHigh(BLUETOOTH_INT_INPUT_PIN);
#endif
 
    lpm_init();
}

/*
 * Bluetooth trasponrt init. Bluetooth module driver shall use this function to register a callback
 * to its implementation.
 */
void bluetooth_set_transport(bluetooth_transport_t *transport) {
    if (transport) memcpy(&bluetooth_transport, transport, sizeof(bluetooth_transport_t));
}

/*
 * Enter pairing with current host index
 */
void bluetooth_pairing(void) {
    if (battery_is_critical_low()) return;

    bluetooth_pairing_ex(0, NULL);
    bt_state = BLUETOOTH_PARING;
}

/*
 * Enter pairing with specified host index and param
 */
void bluetooth_pairing_ex(uint8_t host_idx, void *param) {
    if (battery_is_critical_low()) return;

    if (bluetooth_transport.pairing_ex) bluetooth_transport.pairing_ex(host_idx, param);
    bt_state = BLUETOOTH_PARING;

    host_index = host_idx;
}

/*
 * Initiate connection request to paired host
 */
void bluetooth_connect(void) {
    /*  Work around empty report after wakeup, which leads to reconneect/disconnected loop */
    if (battery_is_critical_low() || sync_timer_read32() == 0) return;

    bluetooth_transport.connect_ex(0, 0);
    bt_state = BLUETOOTH_RECONNECTING;
}

/*
 * Initiate connection request to paired host with argument
 */
void bluetooth_connect_ex(uint8_t host_idx, uint16_t timeout) {
    if (battery_is_critical_low()) return;

    if (host_idx != 0) {
        if (host_index == host_idx && bt_state == BLUETOOTH_CONNECTED) return;
        host_index = host_idx;
        led_state  = 0;
    }
    bluetooth_transport.connect_ex(host_idx, timeout);
    bt_state = BLUETOOTH_RECONNECTING;
}

/* Initiate a disconnection */
void bluetooth_disconnect(void) {
    if (bluetooth_transport.disconnect) bluetooth_transport.disconnect();
}


/* Called when the BT device is reset. */
static void bluetooth_enter_reset(uint8_t reason) {
    bt_state = BLUETOOTH_RESET;
    bluetooth_enter_reset_kb(reason);
}

/* Enters discoverable state. Upon entering this state we perform the following actions:
 *   - change state to BLUETOOTH_PARING
 *   - set pairing indication
 */
static void bluetooth_enter_discoverable(uint8_t host_idx) {
    bt_state = BLUETOOTH_PARING;
    indicator_set(bt_state, host_idx);
    bluetooth_enter_discoverable_kb(host_idx);
}

/*
 * Enters reconnecting state. Upon entering this state we perform the following actions:
 *   - change state to RECONNECTING
 *   - set reconnect indication
 */
static void bluetooth_enter_reconnecting(uint8_t host_idx) {
    bt_state = BLUETOOTH_RECONNECTING;
    indicator_set(bt_state, host_idx);
    bluetooth_enter_reconnecting_kb(host_idx);
}

/* Enters connected state. Upon entering this state we perform the following actions:
 *   - change state to CONNECTED
 *   - set connected indication
 *   - enable bluetooth NKRO is support
 */
static void bluetooth_enter_connected(uint8_t host_idx) {
    bt_state = BLUETOOTH_CONNECTED;
    indicator_set(bt_state, host_idx);
    host_index = host_idx;

    clear_keyboard();

    /* Enable NKRO since it may be disabled in pin code entry */ 
#if defined(NKRO_ENABLE) && defined(BLUETOOTH_NKRO_ENABLE)
    keymap_config.nkro = true;
#else
    keymap_config.nkro = false;
#endif

    bluetooth_enter_connected_kb(host_idx);

    if (battery_is_empty()) indicator_battery_low_enable(true);
}

/* Enters disconnected state. Upon entering this state we perform the following actions:
 *   - change state to DISCONNECTED
 *   - set disconnected indication
 */
static void bluetooth_enter_disconnected(uint8_t host_idx) {
    uint8_t previous_state = bt_state;
    bt_state               = BLUETOOTH_DISCONNECTED;
    
    if (previous_state == BLUETOOTH_CONNECTED) {
        lpm_timer_reset();
        indicator_set(BLUETOOTH_SUSPEND, host_idx);
    } else
        indicator_set(bt_state, host_idx);

#ifndef DISABLE_REPORT_BUFFER
    report_buffer_init();
#endif
    retry = 0;
    bluetooth_enter_disconnected_kb(host_idx);
    indicator_battery_low_enable(false);
}


/* Enter pin code entry state. */
static void bluetooth_enter_pin_code_entry(void) {
#if defined(NKRO_ENABLE)
    keymap_config.nkro = FALSE;
#endif
    pincodeEntry = true;
    bluetooth_enter_pin_code_entry_kb();
}

/* Exit pin code entry state. */
static void bluetooth_exit_pin_code_entry(void) {
#if defined(NKRO_ENABLE)
        keymap_config.nkro = true;
#endif
    pincodeEntry              = false;
    bluetooth_exit_pin_code_entry_kb();
}

__attribute__((weak)) void bluetooth_enter_reset_kb(uint8_t reason){};
__attribute__((weak)) void bluetooth_enter_discoverable_kb(uint8_t host_idx){};
__attribute__((weak)) void bluetooth_enter_reconnecting_kb(uint8_t host_idx){};
__attribute__((weak)) void bluetooth_enter_connected_kb(uint8_t host_idx){};
__attribute__((weak)) void bluetooth_enter_disconnected_kb(uint8_t host_idx){};
__attribute__((weak)) void bluetooth_enter_pin_code_entry_kb(void) {}
__attribute__((weak)) void bluetooth_exit_pin_code_entry_kb(void){};

/*  */
static void bluetooth_hid_set_protocol(bool report_protocol) { 
    bluetooth_report_protocol = false; 
}

uint8_t bluetooth_keyboard_leds(void) {
    if (bt_state == BLUETOOTH_CONNECTED) {
        return led_state;
    }

    return 0;
}

extern keymap_config_t keymap_config;

void bluetooth_send_keyboard(report_keyboard_t *report) {
    if (bt_state == BLUETOOTH_PARING && !pincodeEntry) return;

    if (bt_state == BLUETOOTH_CONNECTED || (bt_state == BLUETOOTH_PARING && pincodeEntry)) {
#    if defined(NKRO_ENABLE)
        if (bluetooth_report_protocol && keymap_config.nkro) {
            if (bluetooth_transport.send_nkro) {
#        ifndef DISABLE_REPORT_BUFFER
                bool firstBuffer = false;
                if (report_buffer_is_empty() && report_buffer_next_inverval() && report_buffer_get_retry() == 0) {
                    firstBuffer = true;
                }

                report_buffer_t report_buffer;
                report_buffer.type = REPORT_TYPE_NKRO;
                memcpy(&report_buffer.keyboard, report, sizeof(report_keyboard_t));
                report_buffer_enqueue(&report_buffer);

                if (firstBuffer) {
                    report_buffer_set_retry(0);
                    report_buffer_task();
                }
#        else
                bluetooth_transport.send_nkro(&report->nkro.mods);
#        endif
            }
        } else
#    endif
        {
            //#ifdef KEYBOARD_SHARED_EP
            if (bluetooth_transport.send_keyboard) {
#    ifndef DISABLE_REPORT_BUFFER
                if (report_buffer_is_empty() && report_buffer_next_inverval()) {
                    bluetooth_transport.send_keyboard(&report->mods);
                    report_buffer_update_timer();
                } else {
                    report_buffer_t report_buffer;
                    report_buffer.type = REPORT_TYPE_KB;
                    memcpy(&report_buffer.keyboard, report, sizeof(report_keyboard_t));
                    report_buffer_enqueue(&report_buffer);
                }
#    else
                bluetooth_transport.send_keyboard(&report->mods);
#    endif
            }
            //#endif
        }

    } else if (bt_state != BLUETOOTH_RESET) { 
        bluetooth_connect();
    }
}

void bluetooth_send_mouse(report_mouse_t *report) {
    if (bt_state == BLUETOOTH_CONNECTED) {
        if (bluetooth_transport.send_mouse) bluetooth_transport.send_mouse((uint8_t *)report);
    } else if (bt_state != BLUETOOTH_RESET) {
        bluetooth_connect();
    }
}

void bluetooth_send_system(uint16_t data) {
    if (bt_state == BLUETOOTH_CONNECTED) {
        if (bluetooth_transport.send_system) bluetooth_transport.send_system(data);
    } else if (bt_state != BLUETOOTH_RESET) {
        bluetooth_connect();
    }
}

void bluetooth_send_consumer(uint16_t data) {
    if (bt_state == BLUETOOTH_CONNECTED) {
#ifndef DISABLE_REPORT_BUFFER
        if (report_buffer_is_empty() && report_buffer_next_inverval()) {
            if (bluetooth_transport.send_consumer) bluetooth_transport.send_consumer(data);
            report_buffer_update_timer();
        } else {
            report_buffer_t report_buffer;
            report_buffer.type     = REPORT_TYPE_CONSUMER;
            report_buffer.consumer = data;
            report_buffer_enqueue(&report_buffer);
        }
#else
        if (bluetooth_transport.send_consumer) bluetooth_transport.send_consumer(data);
#endif
    } else if (bt_state != BLUETOOTH_RESET) {
        bluetooth_connect();
    }
}

void bluetooth_low_battery_shutdown(void) {
    indicator_battery_low_enable(false);
    bluetooth_disconnect();
}

void bluetooth_event_queue_task(void) {
    bluetooth_event_t event;
    while (bluetooth_event_queue_dequeue(&event)) {
        switch (event.evt_type) {
            case EVT_RESET:
                bluetooth_enter_reset(event.params.reason);
                break;
            case EVT_CONNECTED:
                bluetooth_enter_connected(event.params.hostIndex);
                break;
            case EVT_DISCOVERABLE:
                bluetooth_enter_discoverable(event.params.hostIndex);
                break;
            case EVT_RECONNECTING:
                bluetooth_enter_reconnecting(event.params.hostIndex);
                break;
            case EVT_DISCONNECTED:
                led_state = 0;
                bluetooth_enter_disconnected(event.params.hostIndex);
                break;
            case EVT_PINCODE_ENTRY:
                bluetooth_enter_pin_code_entry();
                break;
            case EVT_EXIT_PINCODE_ENTRY:
                bluetooth_exit_pin_code_entry();
                break;
            case EVT_HID_INDICATOR:
                led_state = event.params.led;
                break;
            case EVT_HID_SET_PROTOCOL:
                bluetooth_hid_set_protocol(event.params.protocol);
                break;
            case EVT_CONECTION_INTERVAL:
                report_buffer_set_inverval(event.params.interval);
                break;
            default:
                break;
        }
    }
}

void bluetooth_task(void) {

    bluetooth_transport.task();
    bluetooth_event_queue_task();
#ifndef DISABLE_REPORT_BUFFER
    report_buffer_task();
#endif
    indicator_task();
    battery_task();
    lpm_task();
}

bluetooth_state_t bluetooth_get_state(void) {
    return bt_state;
};

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (get_transport() == TRANSPORT_BLUETOOTH) {
        lpm_timer_reset();
    }

    return process_record_user(keycode, record);
}
