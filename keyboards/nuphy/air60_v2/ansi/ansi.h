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

enum custom_keycodes {
    RF_DFU = QK_KB_0,
    LNK_USB,
    LNK_RF,
    LNK_BLE1,
    LNK_BLE2,
    LNK_BLE3,

    MAC_TASK,
    MAC_SEARCH,
    MAC_VOICE,
    MAC_CONSOLE,
    MAC_DND,
    MAC_PRT,
    MAC_PRTA,

    SIDE_VAI,
    SIDE_VAD,
    SIDE_MOD,
    SIDE_HUI,
    SIDE_SPI,
    SIDE_SPD,

    DEV_RESET,
    SLEEP_MODE,
    BAT_SHOW,
    RGB_TEST,
    SHIFT_GRV,
    BAT_NUM
};


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


#define RF_LONG_PRESS_DELAY   30
#define DEV_RESET_PRESS_DELAY 30
#define RGB_TEST_PRESS_DELAY  30


#define UART_HEAD           0x5A
#define FUNC_VALID_LEN      32

#define RF_IDLE             0
#define RF_PAIRING          1
#define RF_LINKING          2
#define RF_CONNECT          3
#define RF_DISCONNECT       4
#define RF_SLEEP            5
#define RF_SNIF             6
#define RF_INVALID          0XFE
#define RF_ERR_STATE        0XFF

#define CMD_POWER_UP     0XF0
#define CMD_SLEEP        0XF1
#define CMD_HAND         0XF2
#define CMD_SNIF         0XF3
#define CMD_24G_SUSPEND  0XF4
#define CMD_IDLE_EXIT    0XFE

#define CMD_RPT_MS       0XE0
#define CMD_RPT_BYTE_KB  0XE1
#define CMD_RPT_BIT_KB   0XE2
#define CMD_RPT_CONSUME  0XE3
#define CMD_RPT_SYS      0XE4

#define CMD_SET_LINK     0XC0
#define CMD_SET_CONFIG   0XC1
#define CMD_GET_CONFIG   0XC2
#define CMD_SET_NAME     0XC3
#define CMD_GET_NAME     0XC4
#define CMD_CLR_DEVICE   0XC5
#define CMD_NEW_ADV      0XC7
#define CMD_RF_STS_SYSC  0XC9
#define CMD_SET_24G_NAME 0XCA
#define CMD_GO_TEST      0XCF

#define CMD_RF_DFU       0XB1

#define CMD_WRITE_DATA   0X80
#define CMD_READ_DATA    0X81


#define LINK_RF_24       0
#define LINK_BT_1        1
#define LINK_BT_2        2
#define LINK_BT_3        3
#define LINK_USB         4

#define UART_MAX_LEN     64
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


#define SYS_SW_WIN        0xa1
#define SYS_SW_MAC        0xa2

#define RF_LINK_SHOW_TIME 300

#define HOST_USB_TYPE     0
#define HOST_BLE_TYPE     1
#define HOST_RF_TYPE      2

#define LINK_TIMEOUT     (uint16_t)(100 * 120)
#define SLEEP_TIME_DELAY (uint16_t)(100 * 360)
#define POWER_DOWN_DELAY (uint16_t)(24)

typedef struct
{
    uint8_t default_brightness_flag;
    uint8_t ee_side_mode;
    uint8_t ee_side_light;
    uint8_t ee_side_speed;
    uint8_t ee_side_rgb;
    uint8_t ee_side_colour;
    uint8_t sleep_enable;
    uint8_t retain2;
} user_config_t;

/* Compatibility defines for IS31FL3733 LED address constants (old → new naming) */
#define A_1  SW1_CS1
#define A_2  SW1_CS2
#define A_3  SW1_CS3
#define A_4  SW1_CS4
#define A_5  SW1_CS5
#define A_6  SW1_CS6
#define A_7  SW1_CS7
#define A_8  SW1_CS8
#define A_9  SW1_CS9
#define A_10 SW1_CS10
#define A_11 SW1_CS11
#define A_16 SW1_CS16
#define B_1  SW2_CS1
#define B_2  SW2_CS2
#define B_3  SW2_CS3
#define B_4  SW2_CS4
#define B_5  SW2_CS5
#define B_6  SW2_CS6
#define B_7  SW2_CS7
#define B_8  SW2_CS8
#define B_9  SW2_CS9
#define B_10 SW2_CS10
#define B_11 SW2_CS11
#define B_16 SW2_CS16
#define C_1  SW3_CS1
#define C_2  SW3_CS2
#define C_3  SW3_CS3
#define C_4  SW3_CS4
#define C_5  SW3_CS5
#define C_6  SW3_CS6
#define C_7  SW3_CS7
#define C_8  SW3_CS8
#define C_9  SW3_CS9
#define C_10 SW3_CS10
#define C_11 SW3_CS11
#define C_16 SW3_CS16
#define D_1  SW4_CS1
#define D_2  SW4_CS2
#define D_3  SW4_CS3
#define D_4  SW4_CS4
#define D_5  SW4_CS5
#define D_6  SW4_CS6
#define D_7  SW4_CS7
#define D_8  SW4_CS8
#define D_9  SW4_CS9
#define D_10 SW4_CS10
#define D_11 SW4_CS11
#define E_1  SW5_CS1
#define E_2  SW5_CS2
#define E_3  SW5_CS3
#define E_4  SW5_CS4
#define E_5  SW5_CS5
#define E_6  SW5_CS6
#define E_7  SW5_CS7
#define E_8  SW5_CS8
#define E_9  SW5_CS9
#define E_10 SW5_CS10
#define E_11 SW5_CS11
#define F_1  SW6_CS1
#define F_2  SW6_CS2
#define F_3  SW6_CS3
#define F_4  SW6_CS4
#define F_5  SW6_CS5
#define F_6  SW6_CS6
#define F_7  SW6_CS7
#define F_8  SW6_CS8
#define F_9  SW6_CS9
#define F_10 SW6_CS10
#define F_11 SW6_CS11
#define G_1  SW7_CS1
#define G_2  SW7_CS2
#define G_3  SW7_CS3
#define G_4  SW7_CS4
#define G_5  SW7_CS5
#define G_6  SW7_CS6
#define G_7  SW7_CS7
#define G_8  SW7_CS8
#define G_9  SW7_CS9
#define G_10 SW7_CS10
#define G_11 SW7_CS11
#define G_14 SW7_CS14
#define G_16 SW7_CS16
#define H_1  SW8_CS1
#define H_2  SW8_CS2
#define H_3  SW8_CS3
#define H_4  SW8_CS4
#define H_5  SW8_CS5
#define H_6  SW8_CS6
#define H_7  SW8_CS7
#define H_8  SW8_CS8
#define H_9  SW8_CS9
#define H_10 SW8_CS10
#define H_11 SW8_CS11
#define H_14 SW8_CS14
#define H_16 SW8_CS16
#define I_1  SW9_CS1
#define I_2  SW9_CS2
#define I_3  SW9_CS3
#define I_4  SW9_CS4
#define I_5  SW9_CS5
#define I_6  SW9_CS6
#define I_7  SW9_CS7
#define I_8  SW9_CS8
#define I_9  SW9_CS9
#define I_10 SW9_CS10
#define I_11 SW9_CS11
#define I_14 SW9_CS14
#define I_16 SW9_CS16
#define J_1  SW10_CS1
#define J_3  SW10_CS3
#define J_4  SW10_CS4
#define J_5  SW10_CS5
#define J_6  SW10_CS6
#define J_7  SW10_CS7
#define J_8  SW10_CS8
#define J_9  SW10_CS9
#define J_10 SW10_CS10
#define J_11 SW10_CS11
#define J_12 SW10_CS12
#define J_13 SW10_CS13
#define J_14 SW10_CS14
#define J_15 SW10_CS15
#define J_16 SW10_CS16
#define K_1  SW11_CS1
#define K_3  SW11_CS3
#define K_4  SW11_CS4
#define K_5  SW11_CS5
#define K_6  SW11_CS6
#define K_7  SW11_CS7
#define K_8  SW11_CS8
#define K_9  SW11_CS9
#define K_10 SW11_CS10
#define K_11 SW11_CS11
#define K_12 SW11_CS12
#define K_13 SW11_CS13
#define K_14 SW11_CS14
#define K_15 SW11_CS15
#define K_16 SW11_CS16
#define L_1  SW12_CS1
#define L_3  SW12_CS3
#define L_4  SW12_CS4
#define L_5  SW12_CS5
#define L_6  SW12_CS6
#define L_7  SW12_CS7
#define L_8  SW12_CS8
#define L_9  SW12_CS9
#define L_10 SW12_CS10
#define L_11 SW12_CS11
#define L_12 SW12_CS12
#define L_13 SW12_CS13
#define L_14 SW12_CS14
#define L_15 SW12_CS15
#define L_16 SW12_CS16

/* Compatibility wrappers for new eeconfig API (offset+length) */
#define nuphy_eeconfig_read_user(cfg)   eeconfig_read_user_datablock((cfg), 0, sizeof(user_config_t))
#define nuphy_eeconfig_update_user(cfg) eeconfig_update_user_datablock((cfg), 0, sizeof(user_config_t))
