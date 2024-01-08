/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

typedef enum {
    RX_Idle,
    RX_Receiving,
    RX_Done,
    RX_Fail,
    RX_OV_ERR,
    RX_SUM_ERR,
    RX_CMD_ERR,
    RX_DATA_ERR,
    RX_DATA_OV,
    RX_FORMAT_ERR,

    TX_OK = 0XE0,
    TX_DONE,
    TX_BUSY,
    TX_TIMEOUT,
    TX_DATA_ERR,

} TYPE_RX_STATE;


#define RF_IDLE                 0
#define RF_PAIRING              1
#define RF_LINKING              2
#define RF_CONNECT              3
#define RF_DISCONNECT           4
#define RF_SLEEP                5
#define RF_SNIF                 6
#define RF_INVAILD              0XFE
#define RF_ERR_STATE            0XFF

#define CMD_POWER_UP            0XF0
#define CMD_SLEEP               0XF1
#define CMD_HAND                0XF2
#define CMD_SNIF                0XF3
#define CMD_24G_SUSPEND         0XF4
#define CMD_IDLE_EXIT           0XFE

#define CMD_RPT_MS              0XE0
#define CMD_RPT_BYTE_KB         0XE1
#define CMD_RPT_BIT_KB          0XE2
#define CMD_RPT_CONSUME         0XE3
#define CMD_RPT_SYS             0XE4

#define CMD_SET_LINK            0XC0
#define CMD_SET_CONFIG          0XC1
#define CMD_GET_CONFIG          0XC2
#define CMD_SET_NAME            0XC3
#define CMD_GET_NAME            0XC4
#define CMD_CLR_DEVICE          0XC5
#define CMD_NEW_ADV             0XC7
#define CMD_RF_STS_SYSC         0XC9
#define CMD_SET_24G_NAME        0XCA
#define CMD_GO_TEST             0XCF
#define CMD_RF_DFU              0XB1

#define CMD_WRITE_DATA          0X80
#define CMD_READ_DATA           0X81

#define LINK_RF_24              0
#define LINK_BT_1               1
#define LINK_BT_2               2
#define LINK_BT_3               3
#define LINK_USB                4

#define UART_HEAD               0x5A
#define FUNC_VALID_LEN          32
#define UART_MAX_LEN            64

#define SYS_SW_WIN              0xa1
#define SYS_SW_MAC              0xa2

#define RF_LINK_SHOW_TIME       300

#define HOST_USB_TYPE           0
#define HOST_BLE_TYPE           1
#define HOST_RF_TYPE            2

#define LINK_TIMEOUT            (100 * 120)
#define SLEEP_TIME_DELAY        (100 * 360)
#define POWER_DOWN_DELAY        (24)

#define RF_LONG_PRESS_DELAY     30
#define DEV_RESET_PRESS_DELAY   30
#define RGB_TEST_PRESS_DELAY    30

typedef struct
{
    uint8_t RXDState;
    uint8_t RXDLen;
    uint8_t RXDOverTime;
    uint8_t TXDLenBack;
    uint8_t TXDOffset;
    uint8_t TXDBuf[UART_MAX_LEN];
    uint8_t RXDBuf[UART_MAX_LEN];
} USART_MGR_STRUCT;

typedef struct
{
    uint8_t link_mode;
    uint8_t rf_channel;
    uint8_t ble_channel;
    uint8_t rf_state;
    uint8_t rf_charge;
    uint8_t rf_led;
    uint8_t rf_baterry;
    uint8_t sys_sw_state;
} DEV_INFO_STRUCT;

typedef struct
{
    uint8_t default_brightness_flag;
    uint8_t ee_side_mode;
    uint8_t ee_side_light;
    uint8_t ee_side_speed;
    uint8_t ee_side_rgb;
    uint8_t ee_side_colour;
    uint8_t sleep_enable;
    uint8_t retain1;
    uint8_t retain2;
} user_config_t;

void    dev_sts_sync(void);
void    rf_uart_init(void);
void    rf_device_init(void);
void    uart_send_report_repeat(void);
void    uart_receive_pro(void);
void    uart_send_report(uint8_t report_type, uint8_t *report_buf, uint8_t report_size);
void    side_speed_contol(uint8_t dir);
void    side_light_contol(uint8_t dir);
void    side_colour_control(uint8_t dir);
void    side_mode_control(uint8_t dir);
void    side_led_show(void);
void    sleep_handle(void);
void    bat_led_close(void);
void    num_led_show(void);
void    rgb_test_show(void);
void    gpio_init(void);
void    long_press_key(void);
void    break_all_key(void);
void    switch_dev_link(uint8_t mode);
void    dial_sw_scan(void);
void    dial_sw_fast_scan(void);
void    timer_pro(void);
void    londing_eeprom_data(void);
uint8_t uart_send_cmd(uint8_t cmd, uint8_t ack_cnt, uint8_t delayms);
