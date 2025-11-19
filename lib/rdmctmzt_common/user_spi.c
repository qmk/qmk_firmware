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

volatile uint8_t Spi_Send_Recv_Flg   = 0U;
uint8_t          g_es_spi_rx_buf[64] = {0};
uint8_t          g_es_spi_tx_buf[64] = {0};
uint8_t          Repet_Send_Count    = 0x00;
uint8_t          Send_Key_Type       = SPI_NACK;

bool     Init_Spi_Power_Up    = true;
uint8_t  Init_Spi_100ms_Delay = 0;
uint16_t Spi_Interval         = SPI_DELAY_RF_TIME;
bool     Ble_Name_Spi_Send    = false;
uint8_t  Ble_Name_Spi_Count   = QMK_BLE_CHANNEL_1;

uint8_t          app_2g4_data[APP_2G4_BUF_CNT][APP_2G4_BUF_SIZE];
volatile uint8_t app_2g4_data_send = 0;
volatile uint8_t app_2g4_data_rev  = 0;

const md_spi_inittypedef SPI2_InitStruct = /**< SPI init structure */
    {
        MD_SPI_MODE_MASTER, MD_SPI_PHASE_2EDGE, MD_SPI_POLARITY_HIGH, MD_SPI_BAUDRATEPRESCALER_DIV8, MD_SPI_MSB_FIRST, MD_SPI_FULL_DUPLEX, MD_SPI_FRAME_FORMAT_8BIT, MD_SPI_NSS_HARD,
};

uint8_t app_2g4_buffer_full(void) {
    uint8_t tmp_rev = app_2g4_data_rev + 1;
    if (tmp_rev == APP_2G4_BUF_CNT) {
        tmp_rev = 0;
    }
    return (tmp_rev == app_2g4_data_send);
}

uint8_t app_2g4_buffer_empty(void) {
    return (app_2g4_data_rev == app_2g4_data_send);
}

void app_2g4_buffer_rev_add(void) {
    app_2g4_data_rev++;
    if (app_2g4_data_rev >= APP_2G4_BUF_CNT) app_2g4_data_rev = 0;
}

void app_2g4_buffer_send_add(void) {
    app_2g4_data_send++;
    if (app_2g4_data_send >= APP_2G4_BUF_CNT) app_2g4_data_send = 0;
}

void Spi_Main_Loop(void) {
    if (Init_Spi_Power_Up || Keyboard_Status.System_Work_Status) {
        return;
    }

    if ((!app_2g4_buffer_empty()) && (!Spi_Send_Recv_Flg) && (!gpio_read_pin(ES_SPI_ACK_IO))) {
        Spi_Send_Recv_Flg = 1;
        Send_Key_Type     = SPI_NACK;
        es_spi_send_recv_by_dma(USER_KEYBOARD_LENGTH, g_es_spi_rx_buf, app_2g4_data[app_2g4_data_send]);
        app_2g4_buffer_send_add();
    }
}

void es_ble_spi_init(void) {
    md_gpio_inittypedef gpiox;

    md_rcu_enable_spi2(RCU);

    gpiox.Pin        = MD_GPIO_PIN_0;
    gpiox.Mode       = MD_GPIO_MODE_FUNCTION;
    gpiox.OutputType = MD_GPIO_OUTPUT_PUSHPULL;
    gpiox.Pull       = MD_GPIO_PULL_UP;
    gpiox.OutDrive   = MD_GPIO_DRIVING_8MA;
    gpiox.Function   = MD_GPIO_AF0;
    md_gpio_init(GPIOC, &gpiox);

    gpiox.Pin = MD_GPIO_PIN_1;
    md_gpio_init(GPIOC, &gpiox);

    gpiox.Pin = MD_GPIO_PIN_2;
    md_gpio_init(GPIOC, &gpiox);

    gpiox.Pin = MD_GPIO_PIN_3;
    md_gpio_init(GPIOC, &gpiox);

    md_spi_init(SPI2, (md_spi_inittypedef *)(&SPI2_InitStruct));
}

void es_ble_spi_deinit(void) {
    md_rcu_enable_spi2_reset(RCU);
    md_rcu_disable_spi2_reset(RCU);
    md_rcu_disable_spi2(RCU);

    GPIOC->MOD |= 0x000000FF;
    GPIOC->PUD &= 0xFFFFFF00;
    GPIOC->OT &= 0xFFFFFF00;
    GPIOC->DS &= 0xFFFFFF00;
    GPIOC->IST &= 0xFFFFFF00;
}

void es_spi_send_recv_by_dma(uint32_t num, uint8_t *rx_buf, uint8_t *tx_buf) {
    uint32_t tx_index = 0;
    uint32_t rx_index = 0;

    __disable_irq();

    if (((uint32_t)tx_buf) >= 0x20000000) {
        if (num & 0x1) {
            SPI2->DATA = tx_buf[tx_index++];
        }

        while (tx_index < num) {
            if (md_spi_get_txfifo_value(SPI2) <= 2) {
                SPI2->DATA = tx_buf[tx_index++];
                SPI2->DATA = tx_buf[tx_index++];
            }

            if (md_spi_get_rxfifo_value(SPI2)) {
                rx_buf[rx_index++] = SPI2->DATA;
            }
        }

        while (rx_index < num) {
            if (md_spi_get_rxfifo_value(SPI2)) {
                rx_buf[rx_index++] = SPI2->DATA;
            }
        }
    } else {
        if (num & 0x1) {
            SPI2->DATA = 0X00;
        }

        while (tx_index < num) {
            if (md_spi_get_txfifo_value(SPI2) <= 2) {
                SPI2->DATA = 0X00;
                SPI2->DATA = 0X00;
                tx_index += 2;
            }

            if (md_spi_get_rxfifo_value(SPI2)) {
                rx_buf[rx_index++] = SPI2->DATA;
            }
        }

        while (rx_index < num) {
            if (md_spi_get_rxfifo_value(SPI2)) {
                rx_buf[rx_index++] = SPI2->DATA;
            }
        }
    }

    __enable_irq();
}

void Spi_Send_Commad(uint8_t Commad) {
    if (Init_Spi_Power_Up || Keyboard_Status.System_Work_Status) {
        return;
    }

    uint16_t Time_Delay = 0;
    while (Spi_Send_Recv_Flg || (gpio_read_pin(ES_SPI_ACK_IO))) {
        Time_Delay++;
        if (Time_Delay >= 2000) {
            Time_Delay = 0;
            return;
        }
    }

    Spi_Send_Recv_Flg = 1;
    Send_Key_Type     = SPI_NACK;
    Spi_Interval      = SPI_DELAY_RF_TIME;

    g_es_spi_tx_buf[0] = USER_KEYBOARD_COMMAND;
    g_es_spi_tx_buf[1] = USER_KEYBOARD_LENGTH;
    g_es_spi_tx_buf[2] = Commad;
    if (Commad == USER_BATTERY_DATA) {
        g_es_spi_tx_buf[3] = Keyboard_Info.Batt_Number;
    } else if (Commad == USER_BLE1_WRITE_NAME) {
        g_es_spi_tx_buf[3] = ((USER_BLE_ID >> 8) & 0XFF);
        g_es_spi_tx_buf[4] = (USER_BLE_ID & 0X00FF);
        g_es_spi_tx_buf[5] = strlen(USER_BLE1_NAME);
        for (uint8_t len = 0; len < strlen(USER_BLE1_NAME); len++) {
            g_es_spi_tx_buf[6 + len] = USER_BLE1_NAME[len];
        }
    } else if (Commad == USER_BLE2_WRITE_NAME) {
        g_es_spi_tx_buf[3] = ((USER_BLE_ID >> 8) & 0XFF);
        g_es_spi_tx_buf[4] = (USER_BLE_ID & 0X00FF);
        g_es_spi_tx_buf[5] = strlen(USER_BLE2_NAME);
        for (uint8_t len = 0; len < strlen(USER_BLE2_NAME); len++) {
            g_es_spi_tx_buf[6 + len] = USER_BLE2_NAME[len];
        }
    } else if (Commad == USER_BLE3_WRITE_NAME) {
        g_es_spi_tx_buf[3] = ((USER_BLE_ID >> 8) & 0XFF);
        g_es_spi_tx_buf[4] = (USER_BLE_ID & 0X00FF);
        g_es_spi_tx_buf[5] = strlen(USER_BLE3_NAME);
        for (uint8_t len = 0; len < strlen(USER_BLE3_NAME); len++) {
            g_es_spi_tx_buf[6 + len] = USER_BLE3_NAME[len];
        }
    }

    es_spi_send_recv_by_dma(USER_KEYBOARD_LENGTH, g_es_spi_rx_buf, g_es_spi_tx_buf);
}

uint8_t Spi_Ack_Send_Commad(uint8_t Commad) {
    if (Init_Spi_Power_Up) {
        return SPI_BUSY;
    }

    if (Spi_Send_Recv_Flg || (gpio_read_pin(ES_SPI_ACK_IO))) {
        return SPI_BUSY;
    }

    Spi_Send_Recv_Flg = 1;
    Send_Key_Type     = SPI_ACK;
    Repet_Send_Count  = 0;

    g_es_spi_tx_buf[0] = USER_KEYBOARD_COMMAND;
    g_es_spi_tx_buf[1] = USER_KEYBOARD_LENGTH;
    g_es_spi_tx_buf[2] = Commad;
    es_spi_send_recv_by_dma(USER_KEYBOARD_LENGTH, g_es_spi_rx_buf, g_es_spi_tx_buf);
    return SPI_IDLE;
}

void Get_Spi_Return_Data(uint8_t *Data) {
    if (Emi_Test_Start) {
        Emi_Write_Data(Data, USER_KEYBOARD_LENGTH);
    } else {
        if (Data[2] == USER_GET_RF_STATUS) {
            Keyboard_Status.System_Work_Status = Data[3];
            if (Keyboard_Status.System_Work_Status) {
                if (Keyboard_Info.Key_Mode != QMK_USB_MODE) {
                    if (Usb_Change_Mode_Wakeup) {
                        User_Sleep();
                    } else {
                        Keyboard_Status.System_Work_Status = 0;
                    }
                } else {
                    Keyboard_Status.System_Work_Status = 0;
                    Spi_Interval                       = SPI_DELAY_USB_TIME;
                }
            }

            Keyboard_Status.System_Work_Mode = Data[4];
            if (Keyboard_Info.Key_Mode != Keyboard_Status.System_Work_Mode) {
                Mode_Synchronization_Signal = true;
                if (Keyboard_Status.System_Work_Status) {
                    Keyboard_Status.System_Work_Status = 0;
                }
            } else {
                if (Keyboard_Info.Key_Mode == QMK_USB_MODE) {
                    Spi_Interval = SPI_DELAY_USB_TIME;
                }
            }

            Keyboard_Status.System_Work_Channel = Data[5];
            if ((Keyboard_Info.Ble_Channel != Keyboard_Status.System_Work_Channel) && (Keyboard_Info.Key_Mode == QMK_BLE_MODE)) {
                Mode_Synchronization_Signal = true;
                if (Keyboard_Status.System_Work_Status) {
                    Keyboard_Status.System_Work_Status = 0;
                }
            }

            Keyboard_Status.System_Connect_Status = Data[6];
            if (Temp_System_Led_Status != Keyboard_Status.System_Connect_Status) {
                Temp_System_Led_Status = Keyboard_Status.System_Connect_Status;
                if (Keyboard_Info.Key_Mode != QMK_USB_MODE) {
                    Led_Rf_Pair_Flg = true;
                } else {
                    Led_Rf_Pair_Flg = false;
                }
            }

            Keyboard_Status.System_Led_Status = Data[7];

            uint16_t Ble_ID = ((Data[8] << 8) | (Data[9]));
            if (Ble_ID != USER_BLE_ID) {
                if (Ble_Name_Spi_Send == false) {
                    Ble_Name_Spi_Send  = true;
                    Ble_Name_Spi_Count = QMK_BLE_CHANNEL_1;
                }
            }
        } else if (Data[2] == USER_KEYBOARD_SLEEP) {
            if (Keyboard_Status.System_Work_Status && (Data[3] == USER_SLEEP_PASS)) {
                if (Keyboard_Info.Key_Mode != QMK_USB_MODE) {
                    Keyboard_Status.System_Sleep_Mode = 1;
                } else {
                    Keyboard_Status.System_Sleep_Mode = 0;
                }
            } else if (Data[3] == USER_SLEEP_FIAL) {
                Keyboard_Status.System_Work_Status = 0;
                Keyboard_Status.System_Sleep_Mode  = 0;
            }
        }

        if (0XBB == Data[10]) {
            Emi_Test_Start = true;
            Emi_Init();
        }
    }
}
