/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
#include "ckbt51.h"
#include "bluetooth.h"
#include "battery.h"
#include "raw_hid.h"
#include "report_buffer.h"

#ifndef CKBT51_INT_INPUT_PIN
#    error "CKBT51_INT_INPUT_PIN is not defined"
#endif

#ifndef CKBT51_TX_RETRY_COUNT
#    define CKBT51_TX_RETRY_COUNT 3
#endif

/* CKBT51 disable its uart peripheral to save power if uart inactivity for 3s, need to
 * assert this pin and wait some time for its uart getting ready before sending  data*/
#define CKBT51_WAKE_WAIT_TIME 3000  // us

enum {
    /* HID Report  */ 
    CKBT51_CMD_SEND_KB       = 0x11,
    CKBT51_CMD_SEND_KB_NKRO  = 0x12,
    CKBT51_CMD_SEND_CONSUMER = 0x13,
    CKBT51_CMD_SEND_SYSTEM   = 0x14,
    CKBT51_CMD_SEND_FN       = 0x15,    // Not used currently
    CKBT51_CMD_SEND_MOUSE    = 0x16,    // Not used currently
    CKBT51_CMD_SEND_BOOT_KB  = 0x17,
    /* Bluetooth connections */
    CKBT51_CMD_PAIRING        = 0x21,
    CKBT51_CMD_CONNECT        = 0x22,
    CKBT51_CMD_DISCONNECT     = 0x23,
    CKBT51_CMD_SWITCH_HOST    = 0x24,
    CKBT51_CMD_READ_STATE_REG = 0x25,
    /* Battery */
    CKBT51_CMD_BATTERY_MANAGE = 0x31,
    CKBT51_CMD_UPDATE_BAT_LVL = 0x32,
     /* Set/get parameters */
    CKBT51_CMD_GET_MODULE_INFO   = 0x40,
    CKBT51_CMD_SET_CONFIG        = 0x41,
    CKBT51_CMD_GET_CONFIG        = 0x42,
    CKBT51_CMD_SET_BDA           = 0x43,
    CKBT51_CMD_GET_BDA           = 0x44,
    CKBT51_CMD_SET_NAME          = 0x45,
    CKBT51_CMD_GET_NAME          = 0x46,
    /* DFU */
    CKBT51_CMD_GET_DFU_VER      = 0x60,
    CKBT51_CMD_HAND_SHAKE_TOKEN = 0x61,
    CKBT51_CMD_START_DFU        = 0x62,
    CKBT51_CMD_SEND_FW_DATA     = 0x63,
    CKBT51_CMD_VERIFY_CRC32     = 0x64,
    CKBT51_CMD_SWITCH_FW        = 0x65,
    /* Factory test */
    CKBT51_CMD_FACTORY_RESET = 0x71,
    CKBT51_CMD_INT_PIN_TEST  = 0x72,
    /* Event */
    CKBT51_EVT_CKBT51_CMD_RECEIVED = 0xA1,
    CKBT51_EVT_OTA_RSP        = 0xA3,
    CKBT51_CONNECTION_EVT_ACK = 0xA4,
};

enum {
    CKBT51_EVT_ACK           = 0xA1,
    CKBT51_EVT_QUERY_RSP     = 0xA2,
    CKBT51_EVT_RESET         = 0xB0,
    CKBT51_EVT_LE_CONNECTION = 0xB1,
    CKBT51_EVT_HOST_TYPE     = 0xB2,
    CKBT51_EVT_CONNECTION    = 0xB3,
    CKBT51_EVT_HID_EVENT     = 0xB4,
    CKBT51_EVT_BATTERY       = 0xB5,
};

enum { 
    CKBT51_CONNECTED = 0x20, 
    CKBT51_DISCOVERABLE = 0x21, 
    CKBT51_RECONNECTING = 0x22, 
    CKBT51_DISCONNECTED = 0x23, 
    CKBT51_PINCODE_ENTRY = 0x24, 
    CKBT51_EXIT_PINCODE_ENTRY = 0x25 
};

enum {
    ACK_SUCCESS = 0x00,
    ACK_CHECKSUM_ERROR,
    ACK_FIFO_HALF_WARNING,
    ACK_FIFO_FULL_ERROR,
};

static uint8_t payload[PACKET_MAX_LEN];
static uint8_t reg_offset = 0xFF;

bluetooth_transport_t bluetooth_transport = {
    ckbt51_init, 
    ckbt51_connect, 
    ckbt51_become_discoverable, 
    ckbt51_disconnect, 
    ckbt51_send_keyboard, 
    ckbt51_send_nkro, 
    ckbt51_send_consumer, 
    ckbt51_send_system, 
    NULL, 
    ckbt51_task
};

void ckbt51_init(bool wakeup_from_low_power_mode) {
#if (HAL_USE_SERIAL == TRUE)
    SerialConfig config = {460800, 0, USART_CR2_STOP1_BITS, 0};

    if (wakeup_from_low_power_mode) {
        sdInit();
        sdStart(&BT_DRIVER, &config);

        return;
    }

    sdStart(&BT_DRIVER, &config);
    palSetPadMode(BT_DRIVER_UART_TX_BANK, BT_DRIVER_UART_TX, PAL_MODE_ALTERNATE(BT_DRIVER_UART_TX_PAL_MODE));
    palSetPadMode(BT_DRIVER_UART_RX_BANK, BT_DRIVER_UART_RX, PAL_MODE_ALTERNATE(BT_DRIVER_UART_RX_PAL_MODE));
#endif

    setPinOutput(CKBT51_INT_INPUT_PIN);
    writePinHigh(CKBT51_INT_INPUT_PIN);
}

void ckbt51_send_cmd(uint8_t* payload, uint8_t len, bool ack_enable) {
    static uint8_t sn = 1;
    uint8_t        i;
    uint8_t        pkt[PACKET_MAX_LEN] = {0};
    memset(pkt, 0, PACKET_MAX_LEN);

    systime_t start = 0;

    for (i=0; i< 3; i++) {
        writePin(CKBT51_INT_INPUT_PIN, i % 2);
        start = chVTGetSystemTime();
        while (chTimeI2US(chVTTimeElapsedSinceX(start)) < CKBT51_WAKE_WAIT_TIME / 3) {};
    }
    writePinHigh(CKBT51_INT_INPUT_PIN);
    
    uint16_t checksum = 0;
    for (i = 0; i < len; i++) checksum += payload[i];

    i        = 0;
    pkt[i++] = 0xAA;
    pkt[i++] = ack_enable ? 0x56 : 0x55;
    pkt[i++] = len + 2;
    pkt[i++] = ~(len + 2) & 0xFF;
    pkt[i++] = sn++;
    memcpy(pkt + i, payload, len);
    i += len;
    pkt[i++] = checksum & 0xFF;
    pkt[i++] = (checksum >> 8) & 0xFF;

    sdWrite(&BT_DRIVER, pkt, i);

    if (sn == 0) sn = 1;
}

void ckbt51_send_keyboard(uint8_t* report) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = CKBT51_CMD_SEND_KB;
    memcpy(payload + i, report, 8);
    i += 8;

    ckbt51_send_cmd(payload, i, true);
}

void ckbt51_send_nkro(uint8_t* report) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = CKBT51_CMD_SEND_KB_NKRO;
    memcpy(payload + i, report, 20);         // NKRO report lenght is limited to 20 bytes
    i += 20;

    ckbt51_send_cmd(payload, i, true);
}

void ckbt51_send_consumer(uint16_t report) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = CKBT51_CMD_SEND_CONSUMER;
    payload[i++] = report & 0xFF;
    payload[i++] = ((report) >> 8) & 0xFF;
    i += 4;   // QMK doesn't send multiple consumer reports, just skip 2nd and 3rd consumer reports

    ckbt51_send_cmd(payload, i, true);
}

void ckbt51_send_system(uint16_t report) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = CKBT51_CMD_SEND_SYSTEM;
    payload[i++] = report & 0xFF;

    ckbt51_send_cmd(payload, i, true);
}

/* Send ack to connection event, bluetooth module will retry 2 times if no ack received */
void ckbt51_send_conn_evt_ack(void) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = CKBT51_CONNECTION_EVT_ACK;

    ckbt51_send_cmd(payload, i, false);
}

void ckbt51_become_discoverable(uint8_t host_idx, void* param) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);
    
    pairing_param_t default_pairing_param = {0, 0, PAIRING_MODE_LESC_OR_SSP, BT_MODE_CLASSIC, 0, NULL};

    if (param == NULL) {
        param = &default_pairing_param;
    }
    pairing_param_t* p = (pairing_param_t*)param;

    payload[i++] = CKBT51_CMD_PAIRING;  // Cmd type
    payload[i++] = host_idx;            // Host Index
    payload[i++] = p->timeout & 0xFF;   // Timeout
    payload[i++] = (p->timeout >> 8) & 0xFF;
    payload[i++] = p->pairingMode;
    payload[i++] = p->BRorLE;           // BR/LE
    payload[i++] = p->txPower;          // LE TX POWER
    if (p->leName) {
        memcpy(&payload[i], p->leName, strlen(p->leName));
        i += strlen(p->leName);
    }

    ckbt51_send_cmd(payload, i, true);
}

/* Timeout : 2 ~ 255 seconds */
void ckbt51_connect(uint8_t hostIndex, uint16_t timeout) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = CKBT51_CMD_CONNECT;
    payload[i++] = hostIndex;           // Host index
    payload[i++] = timeout & 0xFF;      // Timeout
    payload[i++] = (timeout >> 8) & 0xFF;

    ckbt51_send_cmd(payload, i, true);
}

void ckbt51_disconnect(void) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = CKBT51_CMD_DISCONNECT;
    payload[i++] = 0;                      // Sleep mode

    ckbt51_send_cmd(payload, i, true);
}

void ckbt51_switch_host(uint8_t hostIndex) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = CKBT51_CMD_SWITCH_HOST;
    payload[i++] = hostIndex;

    ckbt51_send_cmd(payload, i, true);
}

void ckbt51_read_state_reg(uint8_t reg, uint8_t len) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = CKBT51_CMD_READ_STATE_REG;
    payload[i++] = reg_offset = reg;
    payload[i++]              = len;

    // TODO
    ckbt51_send_cmd(payload, i, false);
}

void ckbt51_get_info(module_info_t* info) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = CKBT51_CMD_GET_MODULE_INFO; 
    ckbt51_send_cmd(payload, i, false);
}

void ckbt51_set_param(module_param_t* param) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = CKBT51_CMD_SET_CONFIG;
    memcpy(payload + i, param, sizeof(module_param_t));
    i += sizeof(module_param_t);

    ckbt51_send_cmd(payload, i, false);
}

void ckbt51_get_param(module_param_t* param) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = CKBT51_CMD_GET_CONFIG;

    ckbt51_send_cmd(payload, i, false);
}

void ckbt51_set_local_name(const char* name) {
    uint8_t i   = 0;
    uint8_t len = strlen(name);
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = CKBT51_CMD_SET_NAME;
    memcpy(payload + i, name, len);
    i += len;
    ckbt51_send_cmd(payload, i, false);
}

void ckbt51_get_local_name(char* name) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = CKBT51_CMD_GET_NAME;

    ckbt51_send_cmd(payload, i, false);
}

void ckbt51_factory_reset(void) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);
    
    payload[i++] = CKBT51_CMD_FACTORY_RESET; 
    
    ckbt51_send_cmd(payload, i, false);
}

void ckbt51_int_pin_test(bool enable) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);
    payload[i++] = CKBT51_CMD_INT_PIN_TEST;
    payload[i++] = enable;

    ckbt51_send_cmd(payload, i, false);
}

void ckbt51_dfu_tx(uint8_t rsp, uint8_t* data, uint8_t len, uint8_t sn) {
    uint16_t checksum        = 0;
    uint8_t  buf[RAW_EPSIZE] = {0};
    uint8_t  i               = 0;

    buf[i++] = 0x03;
    buf[i++] = 0xAA;
    buf[i++] = 0x57;
    buf[i++] = len;
    buf[i++] = ~len;
    buf[i++] = sn;
    buf[i++] = rsp;
    memcpy(&buf[i], data, len);
    i += len;

    for (uint8_t k = 0; k < i; k++) checksum += buf[i];

    raw_hid_send(buf, RAW_EPSIZE);

    if (len > 25) {
        i = 0;
        memset(buf, 0, RAW_EPSIZE);
        buf[i++] = 0x03;
        memcpy(&buf[i], data + 25, len - 25);
        i = i + len - 25;
        raw_hid_send(buf, RAW_EPSIZE);
    }
}

void ckbt51_dfu_rx(uint8_t* data, uint8_t length) {
    if (data[0] == 0xAA && (data[1] == 0x55 || data[1] == 0x56) && data[2] == (~data[3] & 0xFF)) {
        uint16_t checksum    = 0;
        uint8_t  payload_len = data[2];

        /* Check payload_len validity */
        if (payload_len > RAW_EPSIZE - PACKECT_HEADER_LEN) return;

        uint8_t* payload = &data[PACKECT_HEADER_LEN];

        for (uint8_t i = 0; i < payload_len - 2; i++) {
            checksum += payload[i];
        }
        
        /* Verify checksum */
        if ((checksum & 0xFF) != payload[payload_len - 2] || checksum >> 8 != payload[payload_len - 1]) return;

        if ((payload[0] & 0xF0) == 0x60) {
            ckbt51_send_cmd(payload, payload_len - 2, data[1] == 0x56);
        }
    }
}

static void ack_handler(uint8_t* data, uint8_t len) {
    switch (data[1]) {
        case CKBT51_CMD_SEND_KB:
        case CKBT51_CMD_SEND_KB_NKRO:
        case CKBT51_CMD_SEND_CONSUMER:
        case CKBT51_CMD_SEND_SYSTEM:
        case CKBT51_CMD_SEND_MOUSE:
            switch (data[2]) {
                case ACK_SUCCESS:
                    report_buffer_set_retry(0);
                    report_buffer_set_inverval(DEFAULT_REPORT_INVERVAL_MS);
                    break;
                case ACK_FIFO_HALF_WARNING:
                    report_buffer_set_retry(0);
                    report_buffer_set_inverval(DEFAULT_REPORT_INVERVAL_MS + 5);
                    break;
                case ACK_FIFO_FULL_ERROR:
                    report_buffer_set_retry(10);
                    break;
            }
            break;
        default: break;
    }
}

static void query_rsp_handler(uint8_t* data, uint8_t len) {

    if (data[2]) return;

    switch (data[1]) {
        case CKBT51_CMD_READ_STATE_REG:
            switch (reg_offset) {
                case 0x05:
                    battery_calculte_voltage(data[3] | (data[4] << 8));
                    break;
            }
            reg_offset = 0xFF;
            break;
        default:
            break;
    }
}

static void ckbt51_event_handler(uint8_t evt_type, uint8_t* data, uint8_t len, uint8_t sn) {
    bluetooth_event_t event = {0};

    switch (evt_type) {
        case CKBT51_EVT_ACK:
            ack_handler(data, len);
            break;
        case CKBT51_EVT_RESET:
            dprintf("CKBT51_EVT_RESET\n");
            event.evt_type      = EVT_RESET;
            event.params.reason = data[0];
            break;
        case CKBT51_EVT_LE_CONNECTION:
            dprintf("CKBT51_EVT_LE_CONNECTION\n");
            break;
        case CKBT51_EVT_HOST_TYPE:
            dprintf("CKBT51_EVT_HOST_TYPE\n");
            break;
        case CKBT51_EVT_CONNECTION:
            dprintf("CKBT51_EVT_CONNECTION %d\n", data[0]);
            /* Only connection status change message will retry 2 times if no ack  */
            ckbt51_send_conn_evt_ack();
            switch (data[0]) {
                case CKBT51_CONNECTED:
                    event.evt_type = EVT_CONNECTED;
                    break;
                case CKBT51_DISCOVERABLE:
                    event.evt_type = EVT_DISCOVERABLE;
                    break;
                case CKBT51_RECONNECTING:
                    event.evt_type = EVT_RECONNECTING;
                    break;
                case CKBT51_DISCONNECTED:
                    event.evt_type = EVT_DISCONNECTED;
                    break;
                case CKBT51_PINCODE_ENTRY:
                    event.evt_type = EVT_PINCODE_ENTRY;
                    break;
                case CKBT51_EXIT_PINCODE_ENTRY:
                    event.evt_type = EVT_EXIT_PINCODE_ENTRY;
                    break;
            }
            event.params.hostIndex = data[2];
            break;
        case CKBT51_EVT_HID_EVENT:
            dprintf("CKBT51_EVT_HID_EVENT\n");
            event.evt_type   = EVT_HID_INDICATOR;
            event.params.led = data[0];
            break;
        case CKBT51_EVT_QUERY_RSP:
            dprintf("CKBT51_EVT_QUERY_RSP\n");
            query_rsp_handler(data, len);
            break;
        case CKBT51_EVT_OTA_RSP:
            dprintf("CKBT51_EVT_OTA_RSP\n");
            ckbt51_dfu_tx(CKBT51_EVT_OTA_RSP, data, len, sn);
            break;
        case CKBT51_EVT_BATTERY:
            if (data[0] == 0x01) {
                dprintf("CKBT51_EVT_BATTERY\n");
                battery_calculte_voltage(data[1] | (data[2] << 8));
            }
            break;
        default:
            dprintf("Unknown event!!!\n");
            break;
    }

    if (event.evt_type) bluetooth_event_queue_enqueue(event);
}

void ckbt51_task(void) {
    static bool    wait_for_new_pkt = true;
    static uint8_t len              = 0xff;
    static uint8_t sn               = 0;

    if (wait_for_new_pkt && BT_DRIVER.iqueue.q_counter >= PACKECT_HEADER_LEN) {
        uint8_t buf[32] = {0};

        if (wait_for_new_pkt) {
            if (sdGet(&BT_DRIVER) == 0xAA && sdGet(&BT_DRIVER) == 0x57) {
                for (uint8_t i = 0; i < 3; i++) {
                    buf[i] = sdGet(&BT_DRIVER);
                }
                // Check wheather len is valid
                if ((~buf[0] & 0xFF) == buf[1]) {
                    len = buf[0];
                    sn  = buf[2];

                    wait_for_new_pkt = false;
                }
            }
        }
    }

    if (!wait_for_new_pkt && BT_DRIVER.iqueue.q_counter >= len) {
        uint8_t buf[32] = {0};

        for (uint8_t i = 0; i < len; i++) {
            buf[i] = sdGetTimeout(&BT_DRIVER, TIME_IMMEDIATE);

        }

        wait_for_new_pkt = true;

        uint16_t checksum = 0;
        for (int i = 0; i < len - 2; i++) checksum += buf[i];

        if ((checksum & 0xff) == buf[len - 2] && ((checksum >> 8) & 0xff) == buf[len - 1]) {
            ckbt51_event_handler(buf[0], buf + 1, len - 2, sn);
        } else {
            // TODO: Error handle
        }
    }
}
