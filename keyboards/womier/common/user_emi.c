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
#include "rdmctmzt_common.h"

bool Emi_Test_Start = false;

void Emi_Init(void) {
    Spi_Interval = SPI_DELAY_USB_TIME;
    Keyboard_Status.System_Work_Status = 0;
    Keyboard_Status.System_Sleep_Mode = 0;
    Mode_Synchronization_Signal = false;
    Led_Rf_Pair_Flg = false;
    Ble_Name_Spi_Send = false;           
}

void Emi_Read_Data(uint8_t *User_Data, uint8_t User_Length) {
    if (Emi_Test_Start == false) {
        return;
    }

    if (Init_Spi_Power_Up) {
        return;
    }

    if (Spi_Send_Recv_Flg || (gpio_read_pin(ES_SPI_ACK_IO))) {
        return;
    }

    Spi_Send_Recv_Flg = 1;
    Send_Key_Type = SPI_ACK;
    Repet_Send_Count = 0;

    /*将需要发送的指令发送到680*/
    for (uint8_t i = 0; i < User_Length; i++) {
        g_es_spi_tx_buf[i] = User_Data[i];
    }
    es_spi_send_recv_by_dma(USER_KEYBOARD_LENGTH, g_es_spi_rx_buf, g_es_spi_tx_buf);
    return;
}

void Emi_Write_Data(uint8_t *User_Data, uint8_t User_Length) {
    if (Emi_Test_Start == false) {
        return;
    }

    if (User_Data[0] == USER_KEYBOARD_COMMAND) {
        return;
    }
    User_Data[0] = USER_EMI_COMMAND;
}
