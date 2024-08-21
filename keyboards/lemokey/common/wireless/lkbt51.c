/* Copyright 2022~2024 @ Keychron (https://www.keychron.com)
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
#include "lkbt51.h"
#include "wireless.h"
#include "wireless_event_type.h"
#include "battery.h"
#include "raw_hid.h"
#include "report_buffer.h"
#include "factory_test.h"

extern void factory_test_send(uint8_t* payload, uint8_t length);

#ifndef RAW_EPSIZE
#    define RAW_EPSIZE 32
#endif

#ifndef SPI_SCK_PIN
#    define SPI_SCK_PIN A5
#endif
#ifndef SPI_MISO_PIN
#    define SPI_MISO_PIN A6
#endif
#ifndef SPI_MOSI_PIN
#    define SPI_MOSI_PIN A7
#endif

#ifndef SPI_CLK_PAL_MODE
#    define SPI_CLK_PAL_MODE 5
#endif
#ifndef SPI_MISO_PAL_MODE
#    define SPI_MISO_PAL_MODE 5
#endif
#ifndef SPI_MOSI_PAL_MODE
#    define SPI_MOSI_PAL_MODE 5
#endif

#ifndef LKBT51_INT_INPUT_PIN
#    error "LKBT51_INT_INPUT_PIN is not defined"
#endif

#ifndef LKBT51_TX_RETRY_COUNT
#    define LKBT51_TX_RETRY_COUNT 3
#endif

// clang-format off
enum {
    /* HID Report  */
    LKBT51_CMD_SEND_KB       = 0x11,
    LKBT51_CMD_SEND_KB_NKRO  = 0x12,
    LKBT51_CMD_SEND_CONSUMER = 0x13,
    LKBT51_CMD_SEND_SYSTEM   = 0x14,
    LKBT51_CMD_SEND_FN       = 0x15, // Not used currently
    LKBT51_CMD_SEND_MOUSE    = 0x16,
    LKBT51_CMD_SEND_BOOT_KB  = 0x17,
    /* Bluetooth connections */
    LKBT51_CMD_PAIRING        = 0x21,
    LKBT51_CMD_CONNECT        = 0x22,
    LKBT51_CMD_DISCONNECT     = 0x23,
    LKBT51_CMD_SWITCH_HOST    = 0x24,
    LKBT51_CMD_READ_STATE_REG = 0x25,
    /* Battery */
    LKBT51_CMD_BATTERY_MANAGE = 0x31,
    LKBT51_CMD_UPDATE_BAT_LVL = 0x32,
    LKBT51_CMD_UPDATE_BAT_STATE = 0x33,
    /* Set/get parameters */
    LKBT51_CMD_GET_MODULE_INFO = 0x40,
    LKBT51_CMD_SET_CONFIG      = 0x41,
    LKBT51_CMD_GET_CONFIG      = 0x42,
    LKBT51_CMD_SET_BDA         = 0x43,
    LKBT51_CMD_GET_BDA         = 0x44,
    LKBT51_CMD_SET_NAME        = 0x45,
    LKBT51_CMD_GET_NAME        = 0x46,
    LKBT51_CMD_WRTE_CSTM_DATA  = 0x49,
    /* DFU */
    LKBT51_CMD_GET_DFU_VER      = 0x60,
    LKBT51_CMD_HAND_SHAKE_TOKEN = 0x61,
    LKBT51_CMD_START_DFU        = 0x62,
    LKBT51_CMD_SEND_FW_DATA     = 0x63,
    LKBT51_CMD_VERIFY_CRC32     = 0x64,
    LKBT51_CMD_SWITCH_FW        = 0x65,
    /* Factory test */
    LKBT51_CMD_FACTORY_RESET = 0x71,
    LKBT51_CMD_IO_TEST       = 0x72,
    LKBT51_CMD_RADIO_TEST    = 0x73,
    /* Event */
    LKBT51_EVT_LKBT51_CMD_RECEIVED = 0xA1,
    LKBT51_EVT_OTA_RSP             = 0xA3,
    LKBT51_CONNECTION_EVT_ACK      = 0xA4,
};

enum {
    LKBT51_EVT_ACK           = 0xA1,
    LKBT51_EVT_QUERY_RSP     = 0xA2,
    LKBT51_EVT_RESET         = 0xB0,
    LKBT51_EVT_LE_CONNECTION = 0xB1,
    LKBT51_EVT_HOST_TYPE     = 0xB2,
    LKBT51_EVT_CONNECTION    = 0xB3,
    LKBT51_EVT_HID_EVENT     = 0xB4,
    LKBT51_EVT_BATTERY       = 0xB5,
};

enum {
    LKBT51_CONNECTED = 0x20,
    LKBT51_DISCOVERABLE = 0x21,
    LKBT51_RECONNECTING = 0x22,
    LKBT51_DISCONNECTED = 0x23,
    LKBT51_PINCODE_ENTRY = 0x24,
    LKBT51_EXIT_PINCODE_ENTRY = 0x25,
    LKBT51_SLEEP = 0x26
};

enum {
    ACK_SUCCESS = 0x00,
    ACK_CHECKSUM_ERROR,
    ACK_FIFO_HALF_WARNING,
    ACK_FIFO_FULL_ERROR,
};

enum{
    LK_EVT_MSK_CONNECTION = 0x01 << 0,
    LK_EVT_MSK_LED = 0x01 << 1,
    LK_EVT_MSK_BATT = 0x01 << 2,
    LK_EVT_MSK_RESET = 0x01 << 3,
    LK_EVT_MSK_RPT_INTERVAL = 0x01 << 4,
    LK_EVT_MSK_MD = 0x01 << 7,
};

// clang-format on
static uint8_t  payload[PACKET_MAX_LEN];
static uint8_t  reg_offset          = 0xFF;
static uint8_t  expect_len          = 22;
static uint16_t connection_interval = 1;
static uint32_t wake_time;
static uint32_t factory_reset = 0;

// clang-format off
wt_func_t wireless_transport = {
    lkbt51_init,
    lkbt51_connect,
    lkbt51_become_discoverable,
    lkbt51_disconnect,
    lkbt51_send_keyboard,
    lkbt51_send_nkro,
    lkbt51_send_consumer,
    lkbt51_send_system,
    lkbt51_send_mouse,
    lkbt51_update_bat_lvl,
    lkbt51_task
};
// clang-format on

#if defined(MCU_STM32)
/* Init SPI */
const SPIConfig spicfg = {
    .circular = false,
    .slave    = false,
    .data_cb  = NULL,
    .error_cb = NULL,
    .ssport   = PAL_PORT(BLUETOOTH_INT_OUTPUT_PIN),
    .sspad    = PAL_PAD(BLUETOOTH_INT_OUTPUT_PIN),
    .cr1      = SPI_CR1_MSTR | SPI_CR1_BR_1 | SPI_CR1_BR_0,
    .cr2      = 0U,
};
#endif

#if defined(WB32F3G71xx)
/* Init SPI */
const SPIConfig spicfg = {
    .ssport                = PAL_PORT(BLUETOOTH_INT_OUTPUT_PIN),
    .sspad                 = PAL_PAD(BLUETOOTH_INT_OUTPUT_PIN),
    .SPI_CPOL              = 0U,
    .SPI_CPHA              = 0U,
    .SPI_BaudRatePrescaler = 32U,
};
#endif

void lkbt51_init(bool wakeup_from_low_power_mode) {
#ifdef LKBT51_RESET_PIN
    if (!wakeup_from_low_power_mode) {
        setPinOutput(LKBT51_RESET_PIN);
        writePinLow(LKBT51_RESET_PIN);
        wait_ms(1);
        writePinHigh(LKBT51_RESET_PIN);
    }
#endif

#if (HAL_USE_SPI == TRUE)
    palSetLineMode(SPI_SCK_PIN, PAL_MODE_ALTERNATE(SPI_CLK_PAL_MODE));
    palSetLineMode(SPI_MISO_PIN, PAL_MODE_ALTERNATE(SPI_MISO_PAL_MODE));
    palSetLineMode(SPI_MOSI_PIN, PAL_MODE_ALTERNATE(SPI_MOSI_PAL_MODE));

    if (WT_DRIVER.state == SPI_UNINIT) {
        if (wakeup_from_low_power_mode) {
            spiInit();
            return;
        }

        spiInit();
    }
#endif

    setPinOutput(BLUETOOTH_INT_OUTPUT_PIN);
    writePinHigh(BLUETOOTH_INT_OUTPUT_PIN);

    setPinInputHigh(LKBT51_INT_INPUT_PIN);
}

static inline void lkbt51_wake(void) {
    if (timer_elapsed32(wake_time) > 3000) {
        wake_time = timer_read32();

        palWriteLine(BLUETOOTH_INT_OUTPUT_PIN, 0);
        wait_ms(10);
        palWriteLine(BLUETOOTH_INT_OUTPUT_PIN, 1);
        wait_ms(300);
    }
}

void lkbt51_send_protocol_ver(uint16_t ver) {
    uint8_t pkt[PACKET_MAX_LEN] = {0};
    memset(pkt, 0, PACKET_MAX_LEN);

    uint8_t i = 0;

    pkt[i++] = 0x84;
    pkt[i++] = 0x7e;
    pkt[i++] = 0x00;
    pkt[i++] = 0x00;
    pkt[i++] = 0xAA;
    pkt[i++] = 0x54;
    pkt[i++] = ver & 0xFF;
    pkt[i++] = (ver >> 8) & 0xFF;
    pkt[i++] = (uint8_t)(~0x54);
    pkt[i++] = (uint8_t)(~0xAA);

#if HAL_USE_SPI
    expect_len = 10;
    spiStart(&WT_DRIVER, &spicfg);
    spiSelect(&WT_DRIVER);
    spiSend(&WT_DRIVER, i, pkt);
    spiUnselectI(&WT_DRIVER);
    spiStop(&WT_DRIVER);
#endif
}

void lkbt51_send_cmd(uint8_t* payload, uint8_t len, bool ack_enable, bool retry) {
    static uint8_t sn = 0;
    uint8_t        i;
    uint8_t        pkt[PACKET_MAX_LEN] = {0};
    memset(pkt, 0, PACKET_MAX_LEN);

    if (!retry) ++sn;
    if (sn == 0) ++sn;

    uint16_t checksum = 0;
    for (i = 0; i < len; i++)
        checksum += payload[i];

    i        = 0;
    pkt[i++] = 0x84;
    pkt[i++] = 0x7e;
    pkt[i++] = 0x00;
    pkt[i++] = 0x00;
    pkt[i++] = 0xAA;
    pkt[i++] = ack_enable ? 0x56 : 0x55;
    pkt[i++] = len + 2;
    pkt[i++] = ~(len + 2) & 0xFF;
    pkt[i++] = sn;

    memcpy(pkt + i, payload, len);
    i += len;
    pkt[i++] = checksum & 0xFF;
    pkt[i++] = (checksum >> 8) & 0xFF;
#if HAL_USE_SPI
    if ((payload[0] & 0xF0) == 0x60)
        expect_len = 64;
    else
        expect_len = 64;

    spiStart(&WT_DRIVER, &spicfg);
    spiSelect(&WT_DRIVER);
    spiSend(&WT_DRIVER, i, pkt);
    spiUnselectI(&WT_DRIVER);
    spiStop(&WT_DRIVER);
#endif
}

void lkbt51_read(uint8_t* payload, uint8_t len) {
    uint8_t i;
    uint8_t pkt[PACKET_MAX_LEN] = {0};
    memset(pkt, 0, PACKET_MAX_LEN);

    i        = 0;
    pkt[i++] = 0x84;
    pkt[i++] = 0x7f;
    pkt[i++] = 0x00;
    pkt[i++] = 0x80;

    i += len;

#if HAL_USE_SPI
    spiStart(&WT_DRIVER, &spicfg);
    spiSelect(&WT_DRIVER);
    spiExchange(&WT_DRIVER, i, pkt, payload);
    spiUnselect(&WT_DRIVER);
    spiStop(&WT_DRIVER);
#endif
}

void lkbt51_send_keyboard(uint8_t* report) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_SEND_KB;
    memcpy(payload + i, report, 8);
    i += 8;

    lkbt51_send_cmd(payload, i, true, false);
}

void lkbt51_send_nkro(uint8_t* report) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_SEND_KB_NKRO;
    memcpy(payload + i, report, 20); // NKRO report lenght is limited to 20 bytes
    i += 20;

    lkbt51_send_cmd(payload, i, true, false);
}

void lkbt51_send_consumer(uint16_t report) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_SEND_CONSUMER;
    payload[i++] = report & 0xFF;
    payload[i++] = ((report) >> 8) & 0xFF;
    i += 4; // QMK doesn't send multiple consumer reports, just skip 2nd and 3rd consumer reports

    lkbt51_send_cmd(payload, i, true, false);
}

void lkbt51_send_system(uint16_t report) {
    uint8_t hid_usage = report & 0xFF;

    if (hid_usage < 0x81 || hid_usage > 0x83) return;

    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_SEND_SYSTEM;
    payload[i++] = 0x01 << (hid_usage - 0x81);

    lkbt51_send_cmd(payload, i, true, false);
}

void lkbt51_send_mouse(uint8_t* report) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_SEND_MOUSE;            // Cmd type
    payload[i++] = report[1];                        // Button
    payload[i++] = report[2];                        // X
    payload[i++] = (report[2] & 0x80) ? 0xff : 0x00; // lkbt51 use 16bit report, set high byte
    payload[i++] = report[3];                        // Y
    payload[i++] = (report[3] & 0x80) ? 0xff : 0x00; // lkbt51 use 16bit report, set high byte
    payload[i++] = report[4];                        // V wheel
    payload[i++] = report[5];                        // H wheel

    lkbt51_send_cmd(payload, i, false, false);
}

/* Send ack to connection event, wireless module will retry 2 times if no ack received */
void lkbt51_send_conn_evt_ack(void) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CONNECTION_EVT_ACK;

    lkbt51_send_cmd(payload, i, false, false);
}

void lkbt51_become_discoverable(uint8_t host_idx, void* param) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    pairing_param_t default_pairing_param = {0, 0, PAIRING_MODE_LESC_OR_SSP, BT_MODE_CLASSIC, 0, NULL};

    if (param == NULL) {
        param = &default_pairing_param;
    }
    pairing_param_t* p = (pairing_param_t*)param;

    payload[i++] = LKBT51_CMD_PAIRING; // Cmd type
    payload[i++] = host_idx;           // Host Index
    payload[i++] = p->timeout & 0xFF;  // Timeout
    payload[i++] = (p->timeout >> 8) & 0xFF;
    payload[i++] = p->pairingMode;
    payload[i++] = p->BRorLE;  // BR/LE
    payload[i++] = p->txPower; // LE TX POWER
    if (p->leName) {
        memcpy(&payload[i], p->leName, strlen(p->leName));
        i += strlen(p->leName);
    }

    lkbt51_wake();
    lkbt51_send_cmd(payload, i, true, false);
}

/* Timeout : 2 ~ 255 seconds */
void lkbt51_connect(uint8_t hostIndex, uint16_t timeout) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_CONNECT;
    payload[i++] = hostIndex;      // Host index
    payload[i++] = timeout & 0xFF; // Timeout
    payload[i++] = (timeout >> 8) & 0xFF;

    lkbt51_wake();
    lkbt51_send_cmd(payload, i, true, false);
}

void lkbt51_disconnect(void) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_DISCONNECT;
    payload[i++] = 0; // Sleep mode

    if (WT_DRIVER.state != SPI_READY) spiStart(&WT_DRIVER, &spicfg);

    wait_ms(30);
    // spiUnselect(&SPID1);
    wait_ms(70);

    lkbt51_send_cmd(payload, i, true, false);
}

void lkbt51_switch_host(uint8_t hostIndex) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_SWITCH_HOST;
    payload[i++] = hostIndex;

    lkbt51_send_cmd(payload, i, true, false);
}

void lkbt51_read_state_reg(uint8_t reg, uint8_t len) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_READ_STATE_REG;
    payload[i++] = reg_offset = reg;
    payload[i++]              = len;

    // TODO
    lkbt51_send_cmd(payload, i, false, false);
}

void lkbt51_update_bat_lvl(uint8_t bat_lvl) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_UPDATE_BAT_LVL;
    payload[i++] = bat_lvl;
    lkbt51_send_cmd(payload, i, false, false);
}

void lkbt51_update_bat_state(uint8_t bat_state) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_UPDATE_BAT_STATE;
    payload[i++] = bat_state;
    lkbt51_send_cmd(payload, i, false, false);
}

void lkbt51_get_info(module_info_t* info) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_GET_MODULE_INFO;
    lkbt51_send_cmd(payload, i, false, false);
}

void lkbt51_set_param(module_param_t* param) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_SET_CONFIG;
    memcpy(payload + i, param, sizeof(module_param_t));
    i += sizeof(module_param_t);

    lkbt51_send_cmd(payload, i, false, false);
}

void lkbt51_get_param(module_param_t* param) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_GET_CONFIG;

    lkbt51_send_cmd(payload, i, false, false);
}

void lkbt51_set_local_name(const char* name) {
    uint8_t i   = 0;
    uint8_t len = strlen(name);
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_SET_NAME;
    memcpy(payload + i, name, len);
    i += len;
    lkbt51_send_cmd(payload, i, false, false);
}

void lkbt51_get_local_name(void) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_GET_NAME;

    lkbt51_send_cmd(payload, i, false, false);
}

void lkbt51_factory_reset(uint8_t p2p4g_clr_msk) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);

    payload[i++] = LKBT51_CMD_FACTORY_RESET;
    payload[i++] = p2p4g_clr_msk;

    lkbt51_wake();
    lkbt51_send_cmd(payload, i, false, false);
    factory_reset = timer_read32();
}

void lkbt51_int_pin_test(bool enable) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);
    payload[i++] = LKBT51_CMD_IO_TEST;
    payload[i++] = enable;

    lkbt51_send_cmd(payload, i, false, false);
}

void lkbt51_radio_test(uint8_t channel) {
    uint8_t i = 0;
    memset(payload, 0, PACKET_MAX_LEN);
    payload[i++] = LKBT51_CMD_RADIO_TEST;
    payload[i++] = channel;
    payload[i++] = 0;

    lkbt51_send_cmd(payload, i, false, false);
}

bool lkbt51_read_customize_data(uint8_t* data, uint8_t len) {
    uint8_t i;
    uint8_t buf[20] = {0};

    i        = 0;
    buf[i++] = 0x84;
    buf[i++] = 0x7a;
    buf[i++] = 0x00;
    buf[i++] = 0x80;

#if HAL_USE_SPI
    spiStart(&WT_DRIVER, &spicfg);
    spiSelect(&WT_DRIVER);
    spiExchange(&WT_DRIVER, 20, buf, payload);
    uint16_t state = buf[5] | (buf[6] << 8);
    if (state == 0x9527) spiExchange(&WT_DRIVER, len, data, payload);
    spiUnselect(&WT_DRIVER);
    spiStop(&WT_DRIVER);
#endif

    return true;
}

void lkbt51_write_customize_data(uint8_t* data, uint8_t len) {
    uint8_t i;
    uint8_t pkt[PACKET_MAX_LEN] = {0};

    i        = 0;
    pkt[i++] = 0x84;
    pkt[i++] = 0x7a;
    pkt[i++] = 0x00;
    pkt[i++] = 0x00;

#if HAL_USE_SPI
    spiStart(&WT_DRIVER, &spicfg);
    spiSelect(&WT_DRIVER);
    spiSend(&WT_DRIVER, i, pkt);
    spiSend(&WT_DRIVER, len, data);
    spiUnselectI(&WT_DRIVER);
    spiStop(&WT_DRIVER);
#endif

    i = 0;
    memset(payload, 0, PACKET_MAX_LEN);
    payload[i++] = LKBT51_CMD_WRTE_CSTM_DATA;

    lkbt51_send_cmd(payload, i, false, false);
}
#ifdef RAW_ENABLE
void lkbt51_dfu_tx(uint8_t rsp, uint8_t* data, uint8_t len, uint8_t sn) {
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

    for (uint8_t k = 0; k < i; k++)
        checksum += buf[i];

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
#endif
void lkbt51_dfu_rx(uint8_t* data, uint8_t length) {
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
        static uint8_t sn = 0;

        bool retry = true;
        if (sn != data[4]) {
            sn    = data[4];
            retry = false;
        }

        if ((payload[0] & 0xF0) == 0x60) {
            lkbt51_wake();
            lkbt51_send_cmd(payload, payload_len - 2, data[1] == 0x56, retry);
        }
    }
}

static void ack_handler(uint8_t* data, uint8_t len) {
    switch (data[1]) {
        case LKBT51_CMD_SEND_KB:
        case LKBT51_CMD_SEND_KB_NKRO:
        case LKBT51_CMD_SEND_CONSUMER:
        case LKBT51_CMD_SEND_SYSTEM:
        case LKBT51_CMD_SEND_MOUSE:
            switch (data[2]) {
                case ACK_SUCCESS:
                    report_buffer_set_retry(0);
                    report_buffer_set_inverval(connection_interval);
                    break;
                case ACK_FIFO_HALF_WARNING:
                    report_buffer_set_retry(0);
                    report_buffer_set_inverval(connection_interval + 5);
                    break;
                case ACK_FIFO_FULL_ERROR:
                    report_buffer_set_inverval(connection_interval + 10);
                    break;
            }
            break;
        default:
            break;
    }
}

static void query_rsp_handler(uint8_t* data, uint8_t len) {
    if (data[2]) return;

    switch (data[1]) {
        case LKBT51_CMD_IO_TEST:
            factory_test_send(data, len);
            break;
        default:
            break;
    }
}

static void lkbt51_event_handler(uint8_t evt_type, uint8_t* data, uint8_t len, uint8_t sn) {
    wireless_event_t event = {0};

    switch (evt_type) {
        case LKBT51_EVT_ACK:
            ack_handler(data, len);
            break;
        case LKBT51_EVT_RESET:
            kc_printf("LKBT51_EVT_RESET\n");
            event.evt_type      = EVT_RESET;
            event.params.reason = data[0];
            break;
        case LKBT51_EVT_LE_CONNECTION:
            kc_printf("LKBT51_EVT_LE_CONNECTION\n");
            break;
        case LKBT51_EVT_HOST_TYPE:
            kc_printf("LKBT51_EVT_HOST_TYPE\n");
            break;
        case LKBT51_EVT_HID_EVENT:
            kc_printf("LKBT51_EVT_HID_EVENT\n");
            event.evt_type   = EVT_HID_INDICATOR;
            event.params.led = data[0];
            break;
        case LKBT51_EVT_QUERY_RSP:
            kc_printf("LKBT51_EVT_QUERY_RSP\n\r");
            query_rsp_handler(data, len);
            break;
        case LKBT51_EVT_OTA_RSP:
#ifdef RAW_ENABLE
            kc_printf("LKBT51_EVT_OTA_RSP\n");
            lkbt51_dfu_tx(LKBT51_EVT_OTA_RSP, data, len, sn);
#endif
            break;
        default:
            kc_printf("Unknown event!!!\n");
            break;
    }

    if (event.evt_type) wireless_event_enqueue(event);
}

void lkbt51_task(void) {
#define VALID_DATA_START_INDEX 4
#define BUFFER_SIZE 64

    static bool    wait_for_new_pkt = true;
    static uint8_t len              = 0xff;
    static uint8_t sn               = 0;

    if (readPin(LKBT51_INT_INPUT_PIN) == 0) {
        uint8_t buf[BUFFER_SIZE] = {0};
        lkbt51_read(buf, expect_len);

        uint8_t* pbuf = buf + VALID_DATA_START_INDEX;

        if (pbuf[0] == 0xAA && pbuf[1] == 0x54 && pbuf[4] == (uint8_t)(~0x54) && pbuf[5] == (uint8_t)(~0xAA)) {
            uint16_t protol_ver = pbuf[3] << 8 | pbuf[2];
            kc_printf("protol_ver: %x\n\r", protol_ver);
            (void)protol_ver;
        } else if (pbuf[0] == 0xAA) {
            wireless_event_t event    = {0};
            uint8_t          evt_mask = pbuf[1];

            if (evt_mask & LK_EVT_MSK_RESET) {
                event.evt_type      = EVT_RESET;
                event.params.reason = pbuf[2];
                wireless_event_enqueue(event);
            }

            if (evt_mask & LK_EVT_MSK_CONNECTION) {
                lkbt51_send_conn_evt_ack();
                switch (pbuf[2]) {
                    case LKBT51_CONNECTED:
                        event.evt_type = EVT_CONNECTED;
                        break;
                    case LKBT51_DISCOVERABLE:
                        event.evt_type = EVT_DISCOVERABLE;
                        break;
                    case LKBT51_RECONNECTING:
                        event.evt_type = EVT_RECONNECTING;
                        break;
                    case LKBT51_DISCONNECTED:
                        event.evt_type = EVT_DISCONNECTED;
                        if (factory_reset && timer_elapsed32(factory_reset) < 3000) {
                            factory_reset = 0;
                            event.data = 1;
                        }
                        break;
                    case LKBT51_PINCODE_ENTRY:
                        event.evt_type = EVT_BT_PINCODE_ENTRY;
                        break;
                    case LKBT51_EXIT_PINCODE_ENTRY:
                        event.evt_type = EVT_EXIT_BT_PINCODE_ENTRY;
                        break;
                    case LKBT51_SLEEP:
                        event.evt_type = EVT_SLEEP;
                        break;
                }
                event.params.hostIndex = pbuf[3];

                wireless_event_enqueue(event);
            }

            if (evt_mask & LK_EVT_MSK_LED) {
                memset(&event, 0, sizeof(event));
                event.evt_type   = EVT_HID_INDICATOR;
                event.params.led = pbuf[4];
                wireless_event_enqueue(event);
            }

            if (evt_mask & LK_EVT_MSK_RPT_INTERVAL) {
                uint32_t interval;
                if (pbuf[8] & 0x80) {
                    interval = (pbuf[8] & 0x7F) * 1250;
                } else {
                    interval = (pbuf[8] & 0x7F) * 125;
                }

                connection_interval = interval / 1000;
                if (connection_interval > 7) connection_interval /= 3;

                memset(&event, 0, sizeof(event));
                event.evt_type        = EVT_CONECTION_INTERVAL;
                event.params.interval = connection_interval;
                wireless_event_enqueue(event);
            }

            if (evt_mask & LK_EVT_MSK_BATT) {
                battery_calculate_voltage(true, pbuf[6] << 8 | pbuf[5]);
            }
        }

        pbuf = buf;
        if (wait_for_new_pkt) {
            for (uint8_t i = 10; i < BUFFER_SIZE - 5; i++) {
                if (buf[i] == 0xAA && buf[i + 1] == 0x57     // Packet Head
                    && (~buf[i + 2] & 0xFF) == buf[i + 3]) { // Check wheather len is valid
                    len              = buf[i + 2];
                    sn               = buf[i + 4];
                    pbuf             = &buf[i + 5];
                    wait_for_new_pkt = false;
                }
            }
        }

        if (!wait_for_new_pkt && BUFFER_SIZE - 5 >= len) {
            wait_for_new_pkt = true;

            uint16_t checksum = 0;
            for (int i = 0; i < len - 2; i++) {
                checksum += pbuf[i];
            }

            if ((checksum & 0xff) == pbuf[len - 2] && ((checksum >> 8) & 0xff) == pbuf[len - 1]) {
                lkbt51_event_handler(pbuf[0], pbuf + 1, len - 3, sn);
            } else {
                // TODO: Error handle
            }
        }
    }
}
