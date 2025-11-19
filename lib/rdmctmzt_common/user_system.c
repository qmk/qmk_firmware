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

void es_mcu_reset(void) {
    uint16_t Time_Delay = 0;
    while (Spi_Send_Recv_Flg || (gpio_read_pin(ES_SPI_ACK_IO)) || Reset_Save_Flash) {
        Time_Delay++;
        if (Time_Delay >= 36000) {
            Time_Delay = 0;
            break;
        }
    }
    gpio_write_pin_low(ES_LED_POWER_IO);

    NVIC_SystemReset();
}

void bootloader_jump(void) {
    uint16_t Time_Delay = 0;
    while (Spi_Send_Recv_Flg || (gpio_read_pin(ES_SPI_ACK_IO)) || Reset_Save_Flash) {
        Time_Delay++;
        if (Time_Delay >= 36000) {
            Time_Delay = 0;
            break;
        }
    }

    gpio_write_pin_low(ES_LED_POWER_IO);

    /*Remap EFLASH,remap to boot*/
    md_fc_lock();
    md_syscfg_set_memory_mapping(SYSCFG, MD_SYSCFG_MEMMOD_MAIN);
    md_syscfg_set_flash_remap_base(SYSCFG, 0);
    md_syscfg_enable_memory_remap(SYSCFG);
    NVIC_SystemReset();
}

void mcu_reset(void) {
    uint16_t Time_Delay = 0;
    while (Spi_Send_Recv_Flg || (gpio_read_pin(ES_SPI_ACK_IO)) || Reset_Save_Flash) {
        Time_Delay++;
        if (Time_Delay >= 36000) {
            Time_Delay = 0;
            break;
        }
    }

    gpio_write_pin_low(ES_LED_POWER_IO);

    NVIC_SystemReset();
}

void User_Systime_Init(void) {	//2ms
    md_rcu_enable_bs16t1(RCU);
    BS16T1->PRES = 48 - 1;
    BS16T1->AR = 2000;
    BS16T1->IER = 0x1;
    BS16T1->CON1 = 0x1;
	NVIC_SetPriority(BS16T1_IRQn, 2);
	NVIC_EnableIRQ(BS16T1_IRQn);
}

void User_Systime_Deinit(void) {
    md_rcu_enable_bs16t1_reset(RCU);
    md_rcu_disable_bs16t1_reset(RCU);
    md_rcu_disable_bs16t1(RCU);
}

void User_Sleep(void) {
    gpio_set_pin_output(ES_LED_POWER_IO);
    gpio_write_pin_low(ES_LED_POWER_IO);

    gpio_set_pin_output(ES_SDB_POWER_IO);
    gpio_write_pin_low(ES_SDB_POWER_IO);

    gpio_set_pin_output(ES_WUKEUP_IO);
    gpio_write_pin_low(ES_WUKEUP_IO);
}

void User_Wakeup(void) {
    gpio_set_pin_output(ES_WUKEUP_IO);
    gpio_write_pin_high(ES_WUKEUP_IO);
}

void Init_Gpio_Infomation(void) {
    gpio_write_pin_low(ES_LED_POWER_IO);
    gpio_set_pin_output(ES_LED_POWER_IO);
    gpio_write_pin_low(ES_LED_POWER_IO);

    gpio_write_pin_high(ES_SDB_POWER_IO);
    gpio_set_pin_output(ES_SDB_POWER_IO);
    gpio_write_pin_high(ES_SDB_POWER_IO);

    gpio_write_pin_high(ES_WUKEUP_IO);
    gpio_set_pin_output(ES_WUKEUP_IO);
    gpio_write_pin_high(ES_WUKEUP_IO);

    //STDBT
    gpio_set_pin_input_high(ES_BATT_STDBY_IO);

    //USB POWER
    gpio_set_pin_input(ES_USB_POWER_IO);

    //Mode switch pins (from original working implementation)
    gpio_set_pin_input_high(MODE_2P4G_IO);  // 2.4G mode switch
    gpio_set_pin_input_high(MODE_BLE_IO);   // BLE mode switch

    md_gpio_inittypedef gpiox;

    gpiox.Pin   = MD_GPIO_PIN_4;
    gpiox.Mode  = MD_GPIO_MODE_INPUT;
    gpiox.OutputType = MD_GPIO_OUTPUT_PUSHPULL;
    gpiox.Pull  = MD_GPIO_PULL_DOWN;
    gpiox.OutDrive = MD_GPIO_DRIVING_8MA;
    gpiox.Function = MD_GPIO_AF0;
    md_gpio_init(GPIOA, &gpiox);

    md_exti_set_interrupt_pin_0_7(EXTI, MD_EXTI_GPIOA4);
    md_exti_enable_it_gpio_pin(EXTI, MD_EXTI_GPIO4);
    md_exti_enable_rising_edge_trigger(EXTI, MD_EXTI_GPIO4);
    md_exti_enable_falling_edge_trigger(EXTI, MD_EXTI_GPIO4);

	NVIC_SetPriority(EXTI_4to15_IRQn, 3);
    NVIC_EnableIRQ((IRQn_Type) EXTI_4to15_IRQn);   /* EXTI_4to15_IRQn interrupt */
}

void Board_Wakeup_Init(void) {
    /*Using USB_SOF to calibrate the internal clock*/
    md_rcu_enable_csu(RCU);
    CSU->CON |= CSU_CON_AUTOEN_MSK;
    CSU->CON |= CSU_CON_CNTEN_MSK;

    es_ble_spi_init();          //SPI

    User_Adc_Init();            //ADC

    rgb_matrix_driver_init();   //PWM DMA

    Init_Gpio_Infomation();     //GPIO

    User_Systime_Init();        //time

    if (Keyboard_Info.Key_Mode == QMK_USB_MODE) {
        User_Usb_Init();        //USB
    } else {
        Usb_Disconnect();
    }

    Init_Spi_Power_Up = true;
    Init_Spi_100ms_Delay = 0;
    Spi_Interval = SPI_DELAY_RF_TIME;

	NVIC_SetPriority(PendSV_IRQn, 3);
	NVIC_SetPriority(SysTick_IRQn, 3);

    Keyboard_Status.System_Work_Status = 0;
    Keyboard_Status.System_Sleep_Mode = 0;
    Usb_Change_Mode_Wakeup = false;

    Init_Batt_Infomation();

    Led_Power_Up = false;
    Emi_Test_Start = false;
}

void es_chibios_user_idle_loop_hook(void) {
    uint32_t i;

    // Check for mode switch changes
    Check_Mode_Switch_Changed();

	if(Keyboard_Info.Key_Mode == QMK_USB_MODE) {
        if (Usb_Dis_Connect) {
            Usb_Dis_Connect = false;

            if((g_usb_sof_frame_id != g_usb_sof_frame_id_last) || (Usb_Change_Mode_Wakeup == false)) { //正常通信
                g_usb_sof_frame_id_last = g_usb_sof_frame_id;
                Usb_Suspend_Delay = 0;
                return;
            } else {
                Usb_If_Ok_Led = false;
                Usb_Suspend_Delay++;
			    if (Usb_Suspend_Delay < 800) {        //8S
                    return;
			    }
			    Usb_Suspend_Delay = 0;

                while ((DMA1->CHENSET) & 0x4);

                User_Sleep();
                uint32_t delay = 0;
                while (SPI_IDLE != Spi_Ack_Send_Commad(USER_KEYBOARD_SLEEP)) {
                    delay++;
                    if(delay >= 3600) {
                        delay = 0;
                        User_Wakeup();
                        Usb_Suspend_Delay = 6000;
                        return;
                    }
                }

                delay = 0;
                while (Spi_Send_Recv_Flg) {
                    delay++;
                    if(delay >= 36000) {
                        delay = 0;
                        User_Wakeup();
                        return;
                    }
                }
            }
        } else {
            return;
        }
	} else {
	    if(!Keyboard_Status.System_Sleep_Mode) {    //无线休眠
		    return;
	    }
    }

	/*等待SPI数据发送完成*/
	if(Spi_Send_Recv_Flg) {
		return;
	}

    /*680进入休眠之后，1.2ms 之后 ACK_IO 会高电平，说明休眠完成*/
    uint32_t delay = 0;
    while (!gpio_read_pin(ES_SPI_ACK_IO)) {
        wait_ms(1);
        delay++;
        if(delay >= 100) {
            delay = 0;
            return;
        }
    }

    gpio_set_pin_input_high(ES_SPI_ACK_IO);     //ACK_IO

    md_tick_disable_csr_tickie(TICK);
    NVIC_DisableIRQ((IRQn_Type) SysTick_IRQn);

    User_Systime_Deinit();

    es_ble_spi_deinit();

    User_Pwm_Deinit();

    User_Usb_Deinit();

    User_Adc_Deinit();

    Save_Flash = false;
    Save_Flash_3S_Count = 0;
    Usb_Change_Mode_Wakeup = false;
    Usb_Change_Mode_Delay = 0;
    Led_Power_Up = false;

    ioline_t User_Pin_Tab_Col[KEYBOARD_COL] = MATRIX_USER_COL_PINS;
    ioline_t User_Pin_Tab_Rol[KEYBOARD_ROL] = MATRIX_USER_ROW_PINS;

	//唤醒源配置
    for(i = 0; i < KEYBOARD_COL; i++) { //COL
        gpio_set_pin_output(User_Pin_Tab_Col[i]);
        gpio_write_pin_low(User_Pin_Tab_Col[i]);
    }

    for(i = 0; i < KEYBOARD_ROL; i++) { //ROL
        gpio_set_pin_input_high(User_Pin_Tab_Rol[i]);
    }

    gpio_set_pin_input(ES_USB_POWER_IO);

    /*B0 B3 B4 B6 B7 B1*/
    uint32_t Gpio_Enable = 0X000000DB;
    uint32_t Gpio_Status_H = 0X00000000;
    uint32_t Gpio_Status_L = 0X000000DB;

    if (gpio_read_pin(ES_USB_POWER_IO)) {   //USB C5
        Gpio_Status_L |= 0X20;
    } else {
        Gpio_Status_H |= 0X20;
    }
    Gpio_Enable |= 0X20;

    //GP16C4T2_CH2 PB5
    /*PB5 和 PC5 冲突只能用一个*/
    GPIOB->MOD &= 0xFFFFF3FF;   //选择复用模式 GP16C4T2_CH2
    GPIOB->MOD |= 0x00000800;   //选择复用模式 NABLE:1 DISABLE:0

    GPIOB->AFL &= 0xFF0FFFFF;   //选择复用功能
    GPIOB->AFL |= 0x00300000;   //选择复用模式 NABLE:1 DISABLE:0

    md_exti_set_interrupt_pin_0_7(EXTI, MD_EXTI_GPIOB0 | MD_EXTI_GPIOB1 | MD_EXTI_GPIOB3 | MD_EXTI_GPIOB4 | MD_EXTI_GPIOC5 | MD_EXTI_GPIOB6 | MD_EXTI_GPIOB7);
    //md_exti_set_interrupt_pin_8_15(EXTI, MD_EXTI_GPIOB10);

    md_exti_enable_it_gpio_pin(EXTI, Gpio_Enable);	                            /*0~7 , 10*/
    md_exti_enable_rising_edge_trigger(EXTI, Gpio_Status_H);                    /*0~7 , 10*/
    md_exti_enable_falling_edge_trigger(EXTI, Gpio_Status_L);                   /*0~7 , 10*/

    NVIC_EnableIRQ((IRQn_Type) EXTI_0to1_IRQn); 	                            /* EXTI_0to1_IRQn interrupt */
    NVIC_EnableIRQ((IRQn_Type) EXTI_2to3_IRQn); 	                            /* EXTI_2to3_IRQn interrupt */
    NVIC_EnableIRQ((IRQn_Type) EXTI_4to15_IRQn);	                            /* EXTI_4to15_IRQn interrupt */

    //GP16C4T2_CH2 PB5
    md_rcu_enable_gp16c4t2(RCU);
    md_timer_set_prescaler_value_pscv(GP16C4T2, 1);								//分频系数
    md_timer_set_auto_reload_value_arrv(GP16C4T2, 0xffff);						//计数最大值
    md_timer_set_cc2_func_cc2ssel(GP16C4T2, MD_TIMER_CHMODE_INPUT_DIRECT);		//使用当前通道
    md_timer_set_cc2_input_edge_cc2pol(GP16C4T2, MD_TIMER_OUTPUTPOLARITY_LOW);	//捕捉极性
    md_timer_enable_cc2_output_cc2en(GP16C4T2);									//通道使能
    md_timer_enable_counter_cnten(GP16C4T2);									//定时器使能
    md_timer_enable_it_ch2(GP16C4T2);                                           //通道中断使能
    NVIC_EnableIRQ((IRQn_Type) GP16C4T2_IRQn);                                  /* GP16C4T2_IRQHandler */
	md_rcu_enable_gp16c4t2_in_sleep_mode(RCU);                                  /*保持休眠下工作*/

    uint8_t Usb_Sleep_Status = 0XAA;
    if (!gpio_read_pin(ES_USB_POWER_IO) && (Keyboard_Info.Key_Mode == QMK_USB_MODE)) {
        NVIC_DisableIRQ((IRQn_Type) USB_IRQn);          /* USB_IRQHandler */
        Usb_Sleep_Status = 0XFF;
    }

	//进入低功耗
    SCB->SCR &= ~(1UL << 2);    // SCR[2] = 0 (SLEEP)

    md_rcu_set_system_clock_source(RCU, MD_RCU_SW_SYSCLK_HRC);
    md_rcu_disable_pll0(RCU);

    if(Keyboard_Info.Key_Mode != QMK_USB_MODE) {
        md_rcu_disable_usb(RCU);
        md_rcu_disable_hrc48(RCU);

        __WFI();                //Wait For Interrupt

        /*唤醒*/
        md_rcu_enable_hrc48(RCU);
        for(i = 0;i < 99999;) {
            if(md_rcu_is_active_flag_hrc48_ready(RCU) == MD_RCU_HRC48RDY_READY)
                break;
            i++;
        }
        md_rcu_enable_usb(RCU);
    } else {                    //在USB模式下
        md_rcu_enable_usb_in_sleep_mode(RCU);
        __WFI();                //Wait For Interrupt
    }

    md_rcu_set_system_clock_source(RCU, MD_RCU_SW_SYSCLK_HRC48);

    if ((Keyboard_Info.Key_Mode == QMK_USB_MODE) && (Usb_Sleep_Status == 0XFF)) {
        NVIC_EnableIRQ((IRQn_Type) USB_IRQn);
        Usb_Sleep_Status = 0XAA;
    }

    /*休眠唤醒之后记录唤醒按下按键的位置*/
    uint8_t Sleep_Status = 0x00;
    for(i = 0; i < KEYBOARD_ROL; i++) { //ROL
        if (!gpio_read_pin(User_Pin_Tab_Rol[i])) {
            Sleep_Status |= (1 << i);
        }
    }

    NVIC_DisableIRQ((IRQn_Type) EXTI_0to1_IRQn);    /* EXTI_0to1_IRQn interrupt */
    NVIC_DisableIRQ((IRQn_Type) EXTI_2to3_IRQn);    /* EXTI_2to3_IRQn interrupt */
    NVIC_DisableIRQ((IRQn_Type) EXTI_4to15_IRQn);   /* EXTI_4to15_IRQn interrupt */
    NVIC_DisableIRQ((IRQn_Type) GP16C4T2_IRQn);     /* GP16C4T2_IRQHandler */

	//唤醒源配置输出高电平
    for(i = 0; i < KEYBOARD_COL; i++) { //COL
        gpio_write_pin_high(User_Pin_Tab_Col[i]);
    }

    delay = 50;
    while(delay--);

    uint8_t Rol_Count = 0,Col_Count = 0;
    for (i = 0; i < KEYBOARD_ROL; i++) {
        if ((1 << i) & Sleep_Status) {
            for(uint8_t j = 0; j < KEYBOARD_COL; j++) {
                gpio_write_pin_low(User_Pin_Tab_Col[j]);

                delay = 50;
                while(delay--);

                if (!gpio_read_pin(User_Pin_Tab_Rol[i])) {
                    Rol_Count = i;
                    Col_Count = j;
                    break;
                }

                for(uint8_t k = 0; k < KEYBOARD_COL; k++) {
                    gpio_write_pin_high(User_Pin_Tab_Col[j]);
                }

                delay = 50;
                while(delay--);
            }
        }
    }

	//唤醒源配置输出高电平
    for(i = 0; i < KEYBOARD_COL; i++) { //COL
        gpio_write_pin_high(User_Pin_Tab_Col[i]);
    }

    gpio_set_pin_input_low(ES_SPI_ACK_IO);     //ACK_IO

    md_tick_enable_csr_tickie(TICK);
	NVIC_EnableIRQ((IRQn_Type) SysTick_IRQn);

	//在USB模式下
    if(Keyboard_Info.Key_Mode == QMK_USB_MODE) {
        if (USBD1.status & 0x2) {
            usb_lld_wakeup_host(0);

            uint16_t cnt = 200;
			while(cnt--) {
                if(USBD1.state != USB_ACTIVE) {
                    wait_ms(10);
                }
			}
        }

        register_code(dynamic_keymap_get_keycode(0, Rol_Count, Col_Count));
        wait_ms(2);
        unregister_code(dynamic_keymap_get_keycode(0, Rol_Count, Col_Count));
        wait_ms(2);
    }

	Board_Wakeup_Init();
}

// Mode switch detection implementation
uint8_t Read_Mode_Switch_Position(void) {
    bool mode_2p4g = gpio_read_pin(MODE_2P4G_IO);  // 2.4G switch
    bool mode_ble = gpio_read_pin(MODE_BLE_IO);    // BLE switch

    // Switch logic based on original implementation
    // When switch is in USB position: both pins should be HIGH (not selected)
    // When switch is in 2.4G position: MODE_2P4G_IO is LOW, MODE_BLE_IO is HIGH
    // When switch is in BT position: MODE_2P4G_IO is HIGH, MODE_BLE_IO is LOW

    if (!mode_2p4g && mode_ble) {
        return MODE_SWITCH_2P4G;
    } else if (mode_2p4g && !mode_ble) {
        return MODE_SWITCH_BT;
    } else if (mode_2p4g && mode_ble) {
        return MODE_SWITCH_USB;
    }

    // Default to current mode if reading is unclear
    return Current_Mode_Switch_Position;
}

void Check_Mode_Switch_Changed(void) {
    uint8_t current_position = Read_Mode_Switch_Position();

    if (current_position != Current_Mode_Switch_Position) {
        if (!Mode_Switch_Changed) {
            // Start debounce timer
            Mode_Switch_Changed = true;
            Mode_Switch_Debounce_Timer = timer_read();
            Last_Mode_Switch_Position = Current_Mode_Switch_Position;
            Current_Mode_Switch_Position = current_position;
        } else {
            // Check if debounce time has passed
            if (timer_elapsed(Mode_Switch_Debounce_Timer) >= MODE_SWITCH_DEBOUNCE_TIME) {
                // Confirm the change is stable
                if (current_position == Current_Mode_Switch_Position) {
                    Handle_Mode_Switch_Change(Current_Mode_Switch_Position);
                    Mode_Switch_Changed = false;
                } else {
                    // Reading changed again, restart debounce
                    Current_Mode_Switch_Position = current_position;
                    Mode_Switch_Debounce_Timer = timer_read();
                }
            }
        }
    } else {
        // Position is stable, reset debounce
        Mode_Switch_Changed = false;
    }
}

void Handle_Mode_Switch_Change(uint8_t new_position) {
    uint8_t target_mode;
    uint8_t target_channel = Keyboard_Info.Ble_Channel; // Keep current BT channel

    switch (new_position) {
        case MODE_SWITCH_USB:
            target_mode = QMK_USB_MODE;
            break;

        case MODE_SWITCH_2P4G:
            target_mode = QMK_2P4G_MODE;
            break;

        case MODE_SWITCH_BT:
            target_mode = QMK_BLE_MODE;
            // Use last BT channel or default to channel 1
            if (target_channel < QMK_BLE_CHANNEL_1 || target_channel > QMK_BLE_CHANNEL_3) {
                target_channel = QMK_BLE_CHANNEL_1;
            }
            break;

        default:
            return; // Unknown position, do nothing
    }

    // Only switch if different from current mode
    if ((target_mode != Keyboard_Info.Key_Mode) ||
        (target_mode == QMK_BLE_MODE && target_channel != Keyboard_Info.Ble_Channel)) {

        if (target_mode == QMK_USB_MODE) {
            // Switch to USB mode
            Keyboard_Info.Key_Mode = QMK_USB_MODE;
            Spi_Send_Commad(USER_SWITCH_USB_MODE);
            es_restart_usb_driver();
            Save_Flash_Set();
            Led_Rf_Pair_Flg = false;

        } else if (target_mode == QMK_2P4G_MODE) {
            // Switch to 2.4G mode
            Usb_Disconnect();
            Keyboard_Info.Key_Mode = QMK_2P4G_MODE;
            Spi_Send_Commad(USER_SWITCH_2P4G_MODE);
            Save_Flash_Set();
            Led_Rf_Pair_Flg = true;

        } else if (target_mode == QMK_BLE_MODE) {
            // Switch to Bluetooth mode
            Usb_Disconnect();
            Keyboard_Info.Key_Mode = QMK_BLE_MODE;
            Keyboard_Info.Ble_Channel = target_channel;

            switch (target_channel) {
                case QMK_BLE_CHANNEL_1:
                    Spi_Send_Commad(USER_SWITCH_BLE_1_MODE);
                    break;
                case QMK_BLE_CHANNEL_2:
                    Spi_Send_Commad(USER_SWITCH_BLE_2_MODE);
                    break;
                case QMK_BLE_CHANNEL_3:
                    Spi_Send_Commad(USER_SWITCH_BLE_3_MODE);
                    break;
            }
            Save_Flash_Set();
            Led_Rf_Pair_Flg = true;
        }

        // Show mode indicator for 1 second
        Show_Mode_Indicator = true;
        Mode_Indicator_Timer = timer_read();
    }
}

void Debug_Mode_Switch_Position(void) {
    bool mode_2p4g = gpio_read_pin(MODE_2P4G_IO);
    bool mode_ble = gpio_read_pin(MODE_BLE_IO);
    uint8_t position = Read_Mode_Switch_Position();

    // This can be viewed in QMK Console output
    // Format: 2P4G:x BLE:x POS:x MODE:x
    printf("2P4G:%d BLE:%d POS:%d MODE:%d\n", mode_2p4g, mode_ble, position, Keyboard_Info.Key_Mode);
}
