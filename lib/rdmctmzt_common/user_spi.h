/* Copyright 2024 Finalkey
 * Copyright 2024 LiWenLiu <https://github.com/LiuLiuQMK>
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

#define USER_EMI_COMMAND	    0XBB
#define USER_KEYBOARD_COMMAND	0X0A
#define USER_KEYBOARD_LENGTH    (64)

#define USER_SWITCH_2P4G_MODE	0X00
#define USER_SWITCH_BLE_1_MODE	0X01
#define USER_SWITCH_BLE_2_MODE	0X02
#define USER_SWITCH_BLE_3_MODE	0X03
#define USER_SWITCH_2P4G_PAIR	0X04
#define USER_SWITCH_BLE_1_PAIR	0X05
#define USER_SWITCH_BLE_2_PAIR	0X06
#define USER_SWITCH_BLE_3_PAIR	0X07
#define USER_SWITCH_USB_MODE	0X08

#define USER_KEYBOARD_SLEEP		0X09
#define USER_KEYBOARD_WAKEUP	0X0A

#define USER_KEY_BYTE_DATA		0X0B
#define USER_KEY_BIT_DATA		0X0C
#define USER_MOUSE_DATA			0X0D
#define USER_CONSUMER_DATA		0X0E
#define USER_SYSTEM_DATA		0X0F

#define USER_BATTERY_DATA		0X10

#define USER_GET_RF_STATUS	    0X11

#define USER_BLE1_WRITE_NAME    0X12
#define USER_BLE2_WRITE_NAME    0X13
#define USER_BLE3_WRITE_NAME    0X14

#define APP_2G4_BUF_SIZE        (USER_KEYBOARD_LENGTH)
#define APP_2G4_BUF_CNT         (20)

#define SPI_DELAY_RF_TIME       (60)
#define SPI_DELAY_USB_TIME      (500 * 3)

enum Custom_Spi_Ack_S {
    SPI_NACK,
    SPI_ACK
};

enum Custom_Spi_Busy_S {
    SPI_BUSY,
    SPI_IDLE
};

extern volatile uint8_t Spi_Send_Recv_Flg;
extern uint8_t g_es_spi_rx_buf[64];
extern uint8_t g_es_spi_tx_buf[64];
extern uint8_t Repet_Send_Count;
extern uint8_t Send_Key_Type;

extern bool Init_Spi_Power_Up;
extern uint8_t Init_Spi_100ms_Delay;
extern uint16_t Spi_Interval;
extern bool Ble_Name_Spi_Send;
extern uint8_t Ble_Name_Spi_Count;

extern uint8_t app_2g4_data[APP_2G4_BUF_CNT][APP_2G4_BUF_SIZE];
extern volatile uint8_t app_2g4_data_send;
extern volatile uint8_t app_2g4_data_rev;

extern const md_spi_inittypedef SPI2_InitStruct;

extern uint8_t app_2g4_buffer_full(void);
extern uint8_t app_2g4_buffer_empty(void);
extern void app_2g4_buffer_rev_add(void);
extern void app_2g4_buffer_send_add(void);
extern void Spi_Main_Loop(void);

extern void es_ble_spi_init(void);
extern void es_ble_spi_deinit(void);
extern void es_spi_send_recv_by_dma(uint32_t num, uint8_t *rx_buf, uint8_t *tx_buf);
extern void Spi_Send_Commad(uint8_t Commad);
extern uint8_t Spi_Ack_Send_Commad(uint8_t Commad);
extern void Get_Spi_Return_Data(uint8_t *Data);