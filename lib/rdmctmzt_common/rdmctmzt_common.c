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

Keyboard_Info_t Keyboard_Info = {
    .Key_Mode = INIT_WORK_MODE,
    .Ble_Channel = INIT_BLE_CHANNEL,
    .Batt_Number = INIT_BATT_NUMBER,
    .Nkro = INIT_ALL_SIX_KEY,
    .Mac_Win_Mode = INIT_WIN_MAC_MODE,
    .Win_Lock = INIT_WIN_LOCK_NLOCK,
};

Keyboard_Status_t Keyboard_Status = {
    .System_Work_Status = 0x00,
    .System_Work_Mode = 0x00,
    .System_Work_Channel = 0x00,
    .System_Connect_Status = 0x00,
    .System_Led_Status = 0x00,
    .System_Sleep_Mode = 0x00
};

const uint32_t g_es_dma_ch2pri_cfg = ((MD_DMA_CHANNEL_CFG_MODE_PERIPHERAL_PRIMARY) | \
                                   ((MD_DMA_CHANNEL_CFG_RPOWER_SIZE_4) << 14) | \
                                   ((MD_DMA_CHANNEL_CFG_SRCDATA_SIZE_WORD) << 24) | \
                                   ((MD_DMA_CHANNEL_CFG_SRCINC_WORD) << 26) | \
                                   ((MD_DMA_CHANNEL_CFG_DSTDATA_SIZE_WORD) << 28) | \
                                   ((MD_DMA_CHANNEL_CFG_DSTINC_WORD) << 30));

const uint32_t g_es_dma_ch2alt_cfg = ((MD_DMA_CHANNEL_CFG_MODE_PERIPHERAL_ALTERNATE) | \
                                   ((MD_DMA_CHANNEL_CFG_RPOWER_SIZE_1) << 14) | \
                                   ((MD_DMA_CHANNEL_CFG_SRCDATA_SIZE_BYTE) << 24) | \
                                   ((MD_DMA_CHANNEL_CFG_SRCINC_BYTE) << 26) | \
                                   ((MD_DMA_CHANNEL_CFG_DSTDATA_SIZE_BYTE) << 28) | \
                                   ((MD_DMA_CHANNEL_CFG_DSTINC_NO_INC) << 30));

bool Led_Rf_Pair_Flg = false;
bool Key_2p4g_Status = false;
bool Key_Ble_1_Status = false;
bool Key_Ble_2_Status = false;
bool Key_Ble_3_Status = false;
bool Key_Reset_Status = false;
bool Keyboard_Reset = false;
bool Init_Eeprom_Flg = false;
bool Led_Off_Start = false;
bool Led_Power_Up = false;
bool Usb_If_Ok_Led = false;
uint16_t Led_Power_Up_Delay = 0;
uint8_t Temp_System_Led_Status = 0xff;
uint8_t Systick_6ms_Count = 0U;
uint8_t Systick_10ms_Count = 0x00;
uint16_t Systick_Interval_Count = 0x00;
uint8_t Systick_Led_Count = 0x00;
uint8_t Batt_Led_Count = 0x00;
uint16_t Time_3s_Count = 0;
uint16_t Func_Time_3s_Count = 0;

// Mode switch detection variables
uint8_t Current_Mode_Switch_Position = MODE_SWITCH_USB;
uint8_t Last_Mode_Switch_Position = MODE_SWITCH_USB;
bool Mode_Switch_Changed = false;
uint16_t Mode_Switch_Debounce_Timer = 0;

// Mode indicator variables
bool Show_Mode_Indicator = false;
uint16_t Mode_Indicator_Timer = 0;

//WAKEUP_IRQHandler
OSAL_IRQ_HANDLER(Vector4C) {
    md_syscfg_clear_flag_wakeup(SYSCFG);
    md_exti_clear_it_wakeup(EXTI);                   //Clear Wakeup Flag
}

//EXTI_0to1_IRQHandler
OSAL_IRQ_HANDLER(Vector54) {
    uint32_t irq_ifm;
    OSAL_IRQ_PROLOGUE();

    irq_ifm = EXTI->IFM;
    EXTI->ICR = irq_ifm;

    OSAL_IRQ_EPILOGUE();
}

//EXTI_2to3_IRQHandler
OSAL_IRQ_HANDLER(Vector58) {
    uint32_t irq_ifm;
    OSAL_IRQ_PROLOGUE();

    irq_ifm = EXTI->IFM;
    EXTI->ICR = irq_ifm;

    OSAL_IRQ_EPILOGUE();
}

//GP32C4T1_IRQHandler
OSAL_IRQ_HANDLER(Vector7C) {
    uint32_t irq_ifm;
    OSAL_IRQ_PROLOGUE();

    irq_ifm = GP32C4T1->IFM;
    GP32C4T1->ICR = irq_ifm;

    OSAL_IRQ_EPILOGUE();
}

//GP16C4T1_IRQHandler
OSAL_IRQ_HANDLER(Vector80) {
    uint32_t irq_ifm;
    OSAL_IRQ_PROLOGUE();

    irq_ifm = GP16C4T1->IFM;
    GP16C4T1->ICR = irq_ifm;

    OSAL_IRQ_EPILOGUE();
}

//GP16C4T2_IRQHandler
OSAL_IRQ_HANDLER(Vector84) {
    uint32_t irq_ifm;
    OSAL_IRQ_PROLOGUE();

    irq_ifm = GP16C4T2->IFM;
    GP16C4T2->ICR = irq_ifm;

    OSAL_IRQ_EPILOGUE();
}

//DMA1_CH12_IRQHandler
OSAL_IRQ_HANDLER(Vector68) {
    uint32_t irq_ifm;
    OSAL_IRQ_PROLOGUE();

    irq_ifm = DMA1->IFM;
    DMA1->ICR = irq_ifm;

    if(irq_ifm & (1U << 1)){
        /*DMA 收发完成*/
    }

    OSAL_IRQ_EPILOGUE();
}

//EXTI_4to15_IRQHandler
OSAL_IRQ_HANDLER(Vector5C) {
    uint32_t irq_ifm;
    OSAL_IRQ_PROLOGUE();

    irq_ifm = EXTI->IFM;
    EXTI->ICR = irq_ifm;

    if (!Init_Spi_Power_Up) {
        if(irq_ifm & (1U << 4)) {
            if (Spi_Send_Recv_Flg) {
                if (Send_Key_Type == SPI_NACK) {
                    if (!gpio_read_pin(ES_SPI_ACK_IO)) {
                        Spi_Send_Recv_Flg = 0;
                    }
                } else {
                    if (gpio_read_pin(ES_SPI_ACK_IO)) {
                        if (Spi_Send_Recv_Flg == 1) {
                            Spi_Send_Recv_Flg = 2;
                            memset((void *)g_es_spi_rx_buf, 0x00, USER_KEYBOARD_LENGTH);
                            es_spi_send_recv_by_dma(USER_KEYBOARD_LENGTH, g_es_spi_rx_buf, (void*)(0x1000));
                        }
                    } else {
                        if (Spi_Send_Recv_Flg == 2) {
                            if (Emi_Test_Start && ((USER_EMI_COMMAND == g_es_spi_rx_buf[0]) || ((USER_EMI_COMMAND & 0X7F) == g_es_spi_rx_buf[0]))) {
                                Get_Spi_Return_Data(g_es_spi_rx_buf);
                                Spi_Send_Recv_Flg = 0;
                            } else if (USER_KEYBOARD_COMMAND == g_es_spi_rx_buf[0]) {
                                Get_Spi_Return_Data(g_es_spi_rx_buf);
                                Spi_Send_Recv_Flg = 0;
                            } else {
                                Repet_Send_Count++;
                                if (Repet_Send_Count >= 3) {
                                    Repet_Send_Count = 0;
                                    Spi_Send_Recv_Flg = 0;
                                } else {
                                    Spi_Send_Recv_Flg = 1;
                                    es_spi_send_recv_by_dma(USER_KEYBOARD_LENGTH, g_es_spi_rx_buf, g_es_spi_tx_buf);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    OSAL_IRQ_EPILOGUE();
}

//BS16T1_IRQHandler 2ms
OSAL_IRQ_HANDLER(Vector78) {
    OSAL_IRQ_PROLOGUE();

    BS16T1->ICR = BS16T1->IFM;

    if (Init_Spi_Power_Up) {
        Init_Spi_100ms_Delay++;
        if (Init_Spi_100ms_Delay >= 10) {
            Init_Spi_100ms_Delay = 0;
            if (!gpio_read_pin(ES_SPI_ACK_IO)) {
                Init_Spi_Power_Up = false;
            } else {
                Init_Spi_100ms_Delay = 5;
            }
        }
    }

    if (Keyboard_Info.Key_Mode != QMK_USB_MODE) {
        if (Keyboard_Status.System_Work_Status && (!Keyboard_Status.System_Sleep_Mode)) {
            Spi_Ack_Send_Commad(USER_KEYBOARD_SLEEP);
        } else {
            Spi_Main_Loop();
        }
    }

    if (User_Batt_Power_Up_Delay) {
        User_Batt_Power_Up_Delay_100ms_Count++;
        if (User_Batt_Power_Up_Delay_100ms_Count >= 50) {
            User_Batt_Power_Up_Delay_100ms_Count = 0;
            User_Batt_Power_Up_Delay = false;
        }
    } else {
        if (User_Batt_Power_Up) {
            User_Batt_10ms_Count++;
            if (User_Batt_10ms_Count >= 4) {
                User_Batt_10ms_Count = 0;
                if((md_adc_is_active_flag_normal_status(ADC)) == 0) {
                    User_Adc_Batt[User_Adc_Batt_Count] = md_adc_get_normal_data(ADC);
                    md_adc_set_start_normal(ADC, MD_ADC_CON_NSTART_START_REGULAR);
                    User_Adc_Batt_Count++;
                    if (User_Adc_Batt_Count >= USER_BATT_POWER_SCAN_COUNT) {
                        User_Adc_Batt_Count = 0;
                        for(uint8_t i = 0; i < USER_BATT_POWER_SCAN_COUNT; i++) {
                            User_Scan_Batt[i] = User_Adc_Batt[i];
                        }
                        User_Adc_Batt_Power_Up_Init();
                    }
                }
            }
        } else {
            User_Batt_10ms_Count++;
            if (User_Batt_10ms_Count >= 20) {
                User_Batt_10ms_Count = 0;
                if((md_adc_is_active_flag_normal_status(ADC)) == 0) {
                    User_Adc_Batt[User_Adc_Batt_Count] = md_adc_get_normal_data(ADC);
                    md_adc_set_start_normal(ADC, MD_ADC_CON_NSTART_START_REGULAR);
                    User_Adc_Batt_Count++;
                    if (User_Adc_Batt_Count >= USER_BATT_SCAN_COUNT) {
                        User_Adc_Batt_Count = 0;
                        for(uint8_t i = 0; i < USER_BATT_SCAN_COUNT; i++) {
                            User_Scan_Batt[i] = User_Adc_Batt[i];
                        }
                        User_Adc_Batt_Number();
                    }
                }
                User_Batt_Time_15S_Count++;
            }
        }
    }

    Systick_6ms_Count++;
    if (Systick_6ms_Count >= 3) {
        Systick_6ms_Count = 0;

        host_driver_t * temp_driver;
        temp_driver = host_get_driver();
        if((temp_driver != (&es_user_driver))&&(temp_driver)) {
            es_qmk_driver = host_get_driver();
            host_set_driver((host_driver_t *)(&es_user_driver));
        }
    }

    Systick_10ms_Count++;
    if (Systick_10ms_Count >= 5) {
        Systick_10ms_Count = 0;

        if (Mode_Synchronization_Signal) {
            Mode_Synchronization_Signal = false;
            Mode_Synchronization();
        }

        if (Ble_Name_Spi_Send) {
            Ble_Name_Synchronization();
        }

        Systick_Led_Count++;
        if (Systick_Led_Count >= 255) {
            Systick_Led_Count = 0;
        }

        Batt_Led_Count++;
        if (Batt_Led_Count >= 255) {
            Batt_Led_Count = 0;
        }

        if (Led_Power_Up == false) {
            Led_Power_Up_Delay++;
            if (Led_Power_Up_Delay >= 50) {
                Led_Power_Up_Delay = 0;
                Led_Power_Up = true;
                if (Keyboard_Info.Key_Mode == QMK_BLE_MODE) {
                    User_Batt_Send_Spi = true;
                }
            }
        }

        Usb_Change_Mode_Delay++;
        if (Usb_Change_Mode_Delay >= USER_TIME_3S_TIME) {
            Usb_Change_Mode_Delay = 0;
            Usb_Change_Mode_Wakeup = true;
        }

        if (Save_Flash) {
            Save_Flash_3S_Count++;
            if (Save_Flash_3S_Count >= USER_TIME_3S_TIME) {
                if (Spi_Send_Recv_Flg || (gpio_read_pin(ES_SPI_ACK_IO)) || (!Led_Flash_Busy)) {
                    Save_Flash_3S_Count = (USER_TIME_3S_TIME - 10);
                } else {
                    Reset_Save_Flash = true;
                    eeprom_write_block_user((void *)&Keyboard_Info.Key_Mode, 0, sizeof(Keyboard_Info_t));
                    Reset_Save_Flash = false;
                    Save_Flash = false;
                    Save_Flash_3S_Count = 0;
                }
            }
        } else {
            Save_Flash_3S_Count = 0;
        }

        if (Keyboard_Info.Key_Mode != QMK_USB_MODE) {
            if (User_Batt_Send_Spi) {
                User_Batt_Send_Spi = false;
                Spi_Send_Commad(USER_BATTERY_DATA);
            }
            Usb_If_Ok_Led = false;
        } else {
            g_usb_sof_frame_id = ((USB->FRAME1) | (USB->FRAME2 << 8));
            Usb_Dis_Connect = true;
        }

        if (gpio_read_pin(ES_USB_POWER_IO)) {
            if (gpio_read_pin(ES_BATT_STDBY_IO)) {
                es_stdby_pin_state = 1;
            } else {
                es_stdby_pin_state = 2;
            }
        } else {
            es_stdby_pin_state = 0;
        }

        Time_3s_Count++;
        if (Time_3s_Count >= USER_TIME_3S_TIME) {
            Time_3s_Count = 0;

            if (Keyboard_Info.Key_Mode != QMK_USB_MODE) {
                if (Key_2p4g_Status || Key_Ble_1_Status || Key_Ble_2_Status || Key_Ble_3_Status) {
                    switch (Keyboard_Info.Key_Mode) {
                        case QMK_2P4G_MODE: {
                            if (Key_2p4g_Status){
                                Key_2p4g_Status = 0;
                                Spi_Send_Commad(USER_SWITCH_2P4G_PAIR);
                                Led_Rf_Pair_Flg = true;
                            }
                            break;
                        }
                        case QMK_BLE_MODE: {
                            if ((Keyboard_Info.Ble_Channel == QMK_BLE_CHANNEL_1) && Key_Ble_1_Status){
                                Key_Ble_1_Status = 0;
                                Spi_Send_Commad(USER_SWITCH_BLE_1_PAIR);
                                Led_Rf_Pair_Flg = true;
                            } else if ((Keyboard_Info.Ble_Channel == QMK_BLE_CHANNEL_2) && Key_Ble_2_Status){
                                Key_Ble_2_Status = 0;
                                Spi_Send_Commad(USER_SWITCH_BLE_2_PAIR);
                                Led_Rf_Pair_Flg = true;
                            } else if ((Keyboard_Info.Ble_Channel == QMK_BLE_CHANNEL_3) && Key_Ble_3_Status){
                                Key_Ble_3_Status = 0;
                                Spi_Send_Commad(USER_SWITCH_BLE_3_PAIR);
                                Led_Rf_Pair_Flg = true;
                            }
                            break;
                        }
                        default: {
                            break;
                        }
                    }
                }
            }
        }

        Func_Time_3s_Count++;
        if (Func_Time_3s_Count >= USER_TIME_3S_TIME) {
            Func_Time_3s_Count = 0;

            if (Key_Reset_Status) {
                Key_Reset_Status = false;
                Keyboard_Reset = true;
            }
        }
    }

    Systick_Interval_Count++;
    if (Systick_Interval_Count >= Spi_Interval) {
        Systick_Interval_Count = 0;

		if (!Keyboard_Status.System_Work_Status) {
			if(Spi_Ack_Send_Commad(USER_GET_RF_STATUS) == SPI_BUSY) {
				Systick_Interval_Count = (Spi_Interval - 10);
			}
		}
    }

    OSAL_IRQ_EPILOGUE();
}

void Init_Keyboard_Infomation(void) {
    eeprom_read_block_user((void *)&Keyboard_Info.Key_Mode, 0, sizeof(Keyboard_Info_t));

	if ((Keyboard_Info.Key_Mode == 0XFF) && (Keyboard_Info.Ble_Channel == 0XFF) && (Keyboard_Info.Batt_Number == 0XFF)  && (Keyboard_Info.Nkro == 0XFF) && (Keyboard_Info.Mac_Win_Mode == 0XFF) && (Keyboard_Info.Win_Lock == 0XFF)) {
        Keyboard_Info.Key_Mode = INIT_WORK_MODE;
        Keyboard_Info.Ble_Channel = INIT_BLE_CHANNEL;
        Keyboard_Info.Batt_Number = INIT_BATT_NUMBER;
        Keyboard_Info.Nkro = INIT_ALL_KEY;
        Keyboard_Info.Mac_Win_Mode = INIT_WIN_MODE;
        Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
    } else if ((Keyboard_Info.Key_Mode == 0) && (Keyboard_Info.Ble_Channel == 0) && (Keyboard_Info.Batt_Number == 0)  && (Keyboard_Info.Nkro == 0) && (Keyboard_Info.Mac_Win_Mode == 0) && (Keyboard_Info.Win_Lock == 0)) {
        Keyboard_Info.Key_Mode = INIT_WORK_MODE;
        Keyboard_Info.Ble_Channel = INIT_BLE_CHANNEL;
        Keyboard_Info.Batt_Number = INIT_BATT_NUMBER;
        Keyboard_Info.Nkro = INIT_ALL_KEY;
        Keyboard_Info.Mac_Win_Mode = INIT_WIN_MODE;
        Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
    } else {
        if (Keyboard_Info.Key_Mode > QMK_USB_MODE) {
            Keyboard_Info.Key_Mode = QMK_USB_MODE;
        }

        if (Keyboard_Info.Ble_Channel > QMK_BLE_CHANNEL_3) {
            Keyboard_Info.Ble_Channel = QMK_BLE_CHANNEL_3;
        }

        if (Keyboard_Info.Batt_Number > 100) {
            Keyboard_Info.Batt_Number = 100;
        }

        if (Keyboard_Info.Nkro > INIT_ALL_KEY) {
            Keyboard_Info.Nkro = INIT_ALL_KEY;
        }

        if (Keyboard_Info.Mac_Win_Mode > INIT_MAC_MODE) {
            Keyboard_Info.Mac_Win_Mode = INIT_WIN_MODE;
        }

        if (Keyboard_Info.Win_Lock > INIT_WIN_LOCK) {
            Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
        }
    }

    // Read current mode switch position and set initial mode accordingly
    Current_Mode_Switch_Position = Read_Mode_Switch_Position();
    Last_Mode_Switch_Position = Current_Mode_Switch_Position;

    // Override the stored mode with the actual switch position
    switch (Current_Mode_Switch_Position) {
        case MODE_SWITCH_USB:
            Keyboard_Info.Key_Mode = QMK_USB_MODE;
            break;
        case MODE_SWITCH_2P4G:
            Keyboard_Info.Key_Mode = QMK_2P4G_MODE;
            break;
        case MODE_SWITCH_BT:
            Keyboard_Info.Key_Mode = QMK_BLE_MODE;
            // Keep the stored BT channel or default to channel 1
            if (Keyboard_Info.Ble_Channel < QMK_BLE_CHANNEL_1 || Keyboard_Info.Ble_Channel > QMK_BLE_CHANNEL_3) {
                Keyboard_Info.Ble_Channel = QMK_BLE_CHANNEL_1;
            }
            break;
    }
}

void es_change_qmk_nkro_mode_enable(void) {
    if(!keymap_config.nkro) {
        clear_keyboard(); // clear first buffer to prevent stuck keys
        keymap_config.nkro = true;

        Keyboard_Info.Nkro = keymap_config.nkro;
        Save_Flash_Set();
    }
}

void es_change_qmk_nkro_mode_disable(void) {
    if(keymap_config.nkro) {
        clear_keyboard(); // clear first buffer to prevent stuck keys
        keymap_config.nkro = false;

        Keyboard_Info.Nkro = keymap_config.nkro;
        Save_Flash_Set();
    }
}
