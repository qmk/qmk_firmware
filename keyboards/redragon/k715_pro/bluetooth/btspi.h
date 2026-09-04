/* Copyright 2023 temp4gh
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

#pragma once
#include "quantum.h"

#define ENABLE_SPI_BLE_MODULE

#define SPI_MODE 3
#define SPI_DIVISOR 32

#define IS31FL3733_POWERON_PIN     B2
#define EXT_IS31FL3733_SUSPEND_PIN (IS31FL3733_POWERON_PIN)

#define EXT_READ_DIP_PIN_USB_MODE C13
#define EXT_READ_DIP_PIN_BT_MODE  C14

#define CAPS_LOCK_DRV_PIN B8
#define set_caps_lock_on()  palClearLine(CAPS_LOCK_DRV_PIN)
#define set_caps_lock_off() palSetLine(CAPS_LOCK_DRV_PIN)

#define EXT_READ_SPI_SLAVE_INT_PIN   B9
#define EXT_READ_SPI_SLAVE_GPIO_INIT (PAL_MODE_INPUT_PULLUP)
#define EXT_READ_SPI_SLAVE_READY     (PAL_LOW)
#define EXT_READ_SPI_SLAVE_NOT_READY (PAL_HIGH)

#define KBD_BT_MODE       0
#define KBD_USB_MODE      2
#define KBD_POWEROFF_MODE 8
#define INVALID_DIP_DEVICE_MODE 0xFF

#define DEVICE_MODE_BT    KBD_BT_MODE
#define DEVICE_MODE_2D4G  KBD_24G_MODE
#define DEVICE_MODE_USB   KBD_USB_MODE

#define BTSTATEDISCONN      0
#define BTSTATEDISCOVER     1
#define BTSTATECONNECTED    2
#define BTSTATERECONN       3

#define BT_CHANNEL_1       1
#define BT_CHANNEL_INVALID 0xFF

#define BT_BACK_TIMEOUT 60000
#define BT_BACK_TIMEOUT_MS ((BT_BACK_TIMEOUT) / 1000)

#define BT_BP_TIMEOUT 60000
#define BT_BP_TIMEOUT_MS ((BT_BP_TIMEOUT) / 1000)

//means use default value
#define DEFAULT_BT_BP_TIMEOUT 0

//based on ms
#define RF_TIMEOUT_OFFSET 1000

#define MAX_SPI_BLE_SINGLE_PACKET_LENGTH 12
#define MAX_SPI_BLE_MUL_PACKET_LENGTH    11
#define MAX_SPI_BLE_SINGLE_PACKET_LOAD_LENGTH 13
#define MAX_BLE_SPI_RX_FRAME_MAX_SIZE 16
#define MAX_BLE_SPI_TX_FRAME_MAX_SIZE (MAX_BLE_SPI_RX_FRAME_MAX_SIZE)
#define MAX_BLE_SPI_NOTIFY_CMD_BUF_SIZE (32)

#define SPI_BLE_PACKET_HEADER 0x5A

#define SEND_BT_NAME_DELAY_MS 10

#define KBD_CMD_UNKNOW           0x0
#define KBD_CMD_MODE_SET         0x11
#define KBD_CMD_BT_PAIR          0x21
#define KBD_CMD_BT_BACK          0x22
#define KBD_CMD_BT_DISCONNECT    0x23
#define KBD_CMD_BT_SETNAME       0x25
#define KBD_CMD_BT_GETNAME       0x26
#define KBD_CMD_BT_SETCHN        0x27
#define KBD_CMD_GET_INFO         0x51
#define KBD_CMD_INVALID          0x0

#define KBD_CMD_BT_QUERY_KEY_STATE   0x66
#define KBD_CMD_MCU_RESP_KEY_STATE   0x67
#define KBD_CMD_QUERY_LOST_KEY_STATE 0x68

#define KBD_CMD_SEND_BT_TEST_RF      0x71
#define KBD_CMD_MCU_REQ_BT_FWVER     0x72
#define KBD_CMD_MCU_RECV_BT_FWVER    0x72
#define KBD_CMD_BT_REQ_MCU_FWVER     0x73
#define KBD_CMD_SEND_BT_MCU_FWVER    0x73
#define KBD_CMD_BT_REQ_DEV_STATUS    0x74
#define KBD_CMD_SEND_BT_DEV_STATUS   0x74
#define KBD_CMD_BT_REQ_LIGHT_CONTROL 0x75
#define KBD_CMD_BT_REQ_DEEP_SLEEP    0x76
#define KBD_CMD_BT_SET_TEST_MODE     0x77

typedef struct
{
    uint32_t NumLock: 1;
    uint32_t CapsLock: 1;
    uint32_t ScrollLock: 1;
    uint32_t red: 1;
    uint32_t green: 1;
    uint32_t blue: 1;
    uint32_t win_lock: 1;
    uint32_t kbd_lock: 1;

    uint32_t btstate: 2;
    uint32_t wifistate: 3;
    uint32_t btpair: 1;
    uint32_t btback: 1;
    uint32_t lowVoltage: 1;

    uint32_t devmode: 7;
    uint32_t btconnected: 1;

    uint32_t usbstate: 3;
    uint32_t fn_down: 1;
    uint32_t pair: 1;
    uint32_t res_bt_isr: 1;
    uint32_t usb_connected: 2;

    uint32_t last_key_ms;
    uint32_t bt_timeout;
} tDevInfo;

#define BLE_SPI_RX_BUF_MAX_SIZE 20
typedef struct
{
    uint8_t spi_read_buf[BLE_SPI_RX_BUF_MAX_SIZE];
    uint8_t spi_read_length;
} spi_read_data_t;

typedef struct __attribute__((__packed__))
{
    uint32_t NumLock: 1;
    uint32_t CapsLock: 1;
    uint32_t ScrollLock: 1;
    uint32_t res: 1;
    uint32_t remote_btn_down: 1;
    uint32_t remote_btn_dec: 1;
    uint32_t remote_btn_add: 1;
    uint32_t remote_chg: 1;
    uint32_t state_bt: 8;
    uint32_t state_24g: 8;
    uint32_t state_usb: 8;
    uint8_t  mode;
    uint8_t  eff_mode;
    uint8_t  eff_bright;
    uint8_t  eff_speed;
    uint8_t  eff_r;
    uint8_t  eff_g;
    uint8_t  eff_b;
    uint8_t  ch;
}
spi_slave_dev_info_t;

#define KB_MAGIC_NUMBER 0xBE
typedef struct
{
    uint8_t magic_num;

    uint8_t caps_lock: 1;
    uint8_t num_lock: 1;
    uint8_t scroll_lock: 1;
    uint8_t winlock_state: 1;

    uint8_t kbd_lock: 1;
    uint8_t reset_factory: 1;
    uint8_t reserved_bit: 2;

    uint8_t kbd_dev_mode;
    uint8_t bt_ch;
    uint8_t bt_used;
    uint8_t bt_last_connected;

    uint8_t reset_reason;
    uint8_t unused;
} user_settings_config;

#define spi_use_begin()  do{}while(0)
#define spi_use_end()    do{}while(0)

#define kbd_spi_send_byte(_t_) spi_write(_t_)
#define kbd_spi_rec_byte(_t_) spi_read()

void set_dev_info_bt_pair_timeout(void);
void set_dev_info_bt_reconn_timeout(void);
void check_read_spi_data(void);
void update_caps_led(void);
void k715_bt_start_pair(uint8_t chn);
bool is_usb_mode_enabled(void);
bool is_bt_mode_enabled(void);
void k715_ble_spi_init(void);
void k715bt_send_spi_extend_single_packet(uint8_t param_type, uint8_t *param_data, uint8_t param_len);
