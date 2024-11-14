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

bool Key_Fn_Status = false;
bool User_Key_Batt_Num_Show = false;
uint8_t User_Key_Batt_Count = 0;
uint8_t Led_Point_Count = 0U;
uint8_t Mac_Win_Point_Count = 0U;
bool Test_Led = false;
uint8_t Test_Colour = 0U;

uint8_t Led_Batt_Index_Tab[10] = {
    16       , 17       , 18       , 19       , 20       , 21       , 22       , 23       , 24       , 25
};


#define LED_CAP_INDEX       (45)
#define LED_WIN_L_INDEX     (73)
#define LED_BATT_INDEX      (0)

#define LED_A_INDEX         (46)
#define LED_S_INDEX         (47)

#define LED_BLE_1_INDEX     (16)
#define LED_BLE_2_INDEX     (17)
#define LED_BLE_3_INDEX     (18)
#define LED_2P4G_INDEX      (19)
#define LED_USB_INDEX       (20)

led_config_t g_led_config = { {
	{ 0        , 1        , 2        , 3        , 4        , 5        , 6        , 7        , 8        , 9        , 10       , 11       , 12       , NO_LED   , NO_LED   , NO_LED    },
	{ 15       , 16       , 17       , 18       , 19       , 20       , 21       , 22       , 23       , 24       , 25       , 26       , 27       , 28       , NO_LED   , 14        },
	{ 30       , 31       , 32       , 33       , 34       , 35       , 36       , 37       , 38       , 39       , 40       , 41       , 42       , 43       , 13       , 29        },
	{ 45       , 46       , 47       , 48       , 49       , 50       , 51       , 52       , 53       , 54       , 55       , 56       , NO_LED   , 57       , 44       , 58        },
	{ 59       , NO_LED   , 60       , 61       , 62       , 63       , 64       , 65       , 66       , 67       , 68       , 69       , NO_LED   , 70       , 71       , NO_LED    },
	{ 72       , 73       , 74       , NO_LED   , NO_LED   , 75       , NO_LED   , NO_LED   , NO_LED   , 76       , 77       , NO_LED   , NO_LED   , 78       , 79       , 80        }
},{
    // "Fine-tuned" complex configuration
    { 0,   10},   { 15,  10},  { 30,  10},  { 45,  10}, { 60,  10}, { 75,  10}, { 90, 10}, { 105, 10}, { 120, 10}, { 135, 10}, { 150, 10}, { 165, 10}, { 180, 10}, { 195, 10}, { 208, 10},
    { 0,   20},   { 15,  20},  { 30,  20},  { 45,  20}, { 60,  20}, { 75,  20}, { 90, 20}, { 105, 20}, { 120, 20}, { 135, 20}, { 150, 20}, { 165, 20}, { 180, 20}, { 195, 20}, { 208, 20},
    { 0,   30},   { 15,  30},  { 30,  30},  { 45,  30}, { 60,  30}, { 75,  30}, { 90, 30}, { 105, 30}, { 120, 30}, { 135, 30}, { 150, 30}, { 165, 30}, { 180, 30}, { 195, 30}, { 208, 30},
    { 0,   40},   { 15,  40},  { 30,  40},  { 45,  40}, { 60,  40}, { 75,  40}, { 90, 40}, { 105, 40}, { 120, 40}, { 135, 40}, { 150, 40}, { 165, 40},             { 195, 40}, { 208, 40},
    { 0,   50},                { 15,  50},  { 30,  50}, { 45,  50}, { 60,  50}, { 75, 50}, { 90, 50},  { 105, 50}, { 120, 50}, { 135, 50}, { 150, 50}, { 165, 50}, { 180, 50},
    { 0,   60},   { 15,  60},  { 30,  60},                          { 75,  60},                                    { 135, 60}, { 150, 60},             { 180, 60}, { 195, 60}, { 208, 60}
}, {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,
    1, 1, 1,       1,          1, 1,    1, 1, 1
} };

void Led_Rf_Mode_Show(void) {
    uint8_t Temp_Colour = 0,Led_Index = 0;
    if (Keyboard_Info.Key_Mode == QMK_BLE_MODE) {
        if (Keyboard_Info.Ble_Channel == QMK_BLE_CHANNEL_1) {
            Temp_Colour = 5;
            Led_Index = LED_BLE_1_INDEX;
        } else if (Keyboard_Info.Ble_Channel == QMK_BLE_CHANNEL_2) {
            Temp_Colour = 5;
            Led_Index = LED_BLE_2_INDEX;
        } else if (Keyboard_Info.Ble_Channel == QMK_BLE_CHANNEL_3) {
            Temp_Colour = 5;
            Led_Index = LED_BLE_3_INDEX;
        }
    } else if (Keyboard_Info.Key_Mode == QMK_2P4G_MODE) {
        Temp_Colour = 3;
        Led_Index = LED_2P4G_INDEX;
    }

    if (Keyboard_Status.System_Connect_Status == KB_MODE_CONNECT_PAIR) {
        if (Systick_Led_Count < 10) {
            rgb_matrix_set_color(Led_Index, Led_Colour_Tab[Temp_Colour][0], Led_Colour_Tab[Temp_Colour][1], Led_Colour_Tab[Temp_Colour][2]);
        } else {
            rgb_matrix_set_color(Led_Index, 0, 0, 0);
        }

        if (Systick_Led_Count >= 20) {
            Systick_Led_Count = 0;
        }
    } else if (Keyboard_Status.System_Connect_Status == KB_MODE_CONNECT_RETURN) {
        if (Systick_Led_Count < 25) {
            rgb_matrix_set_color(Led_Index, Led_Colour_Tab[Temp_Colour][0], Led_Colour_Tab[Temp_Colour][1], Led_Colour_Tab[Temp_Colour][2]);
        } else {
            rgb_matrix_set_color(Led_Index, 0, 0, 0);
        }

        if (Systick_Led_Count >= 50) {
            Systick_Led_Count = 0;
        }
    } else {
        rgb_matrix_set_color(Led_Index, Led_Colour_Tab[Temp_Colour][0], Led_Colour_Tab[Temp_Colour][1], Led_Colour_Tab[Temp_Colour][2]);

        if (Systick_Led_Count >= 240) {
            Systick_Led_Count = 0;
            Led_Rf_Pair_Flg = false;
            if (Keyboard_Info.Key_Mode == QMK_BLE_MODE) {
                User_Batt_Send_Spi = true;
            }
        }
    }
}

void Led_Power_Low_Show(void) {
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }

    if (Systick_Led_Count < 25) {
        rgb_matrix_set_color(LED_BATT_INDEX, U_PWM, 0x00, 0x00);
    } else {
        rgb_matrix_set_color(LED_BATT_INDEX, 0x00, 0x00, 0x00);
    }

    if (Systick_Led_Count >= 50) {
        Systick_Led_Count = 0;
    }
}

void Led_Point_Flash_Show(void) {
    if (Systick_Led_Count < 25) {
        if (Led_Point_Count) {
            rgb_matrix_driver_set_color_all(U_PWM, U_PWM, U_PWM);
        } else {
            rgb_matrix_driver_set_color_all(U_PWM, U_PWM, 0X00);
        }
    } else {
        rgb_matrix_driver_set_color_all(0X00, 0X00, 0X00);
    }

    if (Systick_Led_Count >= 50) {
        Systick_Led_Count = 0;

        if (Led_Point_Count) {
            Led_Point_Count--;
        } else if (Mac_Win_Point_Count) {
            Mac_Win_Point_Count--;
        }  
    }
}

void Led_Batt_Number_Show(void) {
    if (es_stdby_pin_state == 1) {
        if (Batt_Led_Count >= 2) {
            Batt_Led_Count = 0;

            if (User_Key_Batt_Count > 3) {
                User_Key_Batt_Count -= 3;
            } else {
                User_Key_Batt_Count = 127;
            }
        }

        uint8_t Tmep_Pwm = User_Key_Batt_Count;

        for (uint8_t i = 0; i < 10; i++) {
            rgb_matrix_set_color(Led_Batt_Index_Tab[i], 0X00, Led_Wave_Pwm_Tab[Tmep_Pwm], 0X00);
            Tmep_Pwm += 8;
            if (Tmep_Pwm >= 128) {
                Tmep_Pwm -= 128;
            }
        }
    } else if (es_stdby_pin_state == 2) {
        for (uint8_t i = 0; i < 10; i++) {
            rgb_matrix_set_color(Led_Batt_Index_Tab[i], 0X00, 0XFF, 0X00);
        }
    } else {
        uint8_t Colour_R = 0, Colour_G = 0, Colour_B = 0;
        uint8_t Temp_Count = (Keyboard_Info.Batt_Number / 10) + 1;
        if (Temp_Count >= 10) {
            Temp_Count = 10;
        }

        if (Temp_Count < 3) {
            Colour_R = 0XFF;    Colour_G = 0X00;    Colour_B = 0X00;
        } else if (Temp_Count < 6) {
            Colour_R = 0XFF;    Colour_G = 0XFF;    Colour_B = 0X00;
        } else {
            Colour_R = 0X00;    Colour_G = 0XFF;    Colour_B = 0X00;
        }

        for (uint8_t i = 0; i < Temp_Count; i++) {
            rgb_matrix_set_color(Led_Batt_Index_Tab[i], Colour_R, Colour_G, Colour_B);
        }
    }
}

void User_Point_Show(void){
    if (Led_Point_Count || Mac_Win_Point_Count) {
        Led_Point_Flash_Show();
    } else {
        Systick_Led_Count = 0;

        if (Keyboard_Info.Key_Mode == QMK_USB_MODE) {
            if (host_keyboard_led_state().caps_lock && Usb_If_Ok_Led) {
                rgb_matrix_set_color(LED_CAP_INDEX, U_PWM, U_PWM, U_PWM);
            }
        } else {
            if (Keyboard_Status.System_Led_Status & 0x02) {
                rgb_matrix_set_color(LED_CAP_INDEX, U_PWM, U_PWM, U_PWM);
            }
        }

        if (Keyboard_Info.Win_Lock) {
            rgb_matrix_set_color(LED_WIN_L_INDEX, U_PWM, U_PWM, U_PWM);
        }
    }
}

void User_Test_Colour_Show(void){
    uint8_t Test_R = 0, Test_G = 0, Test_B = 0;
    switch(Test_Colour) {
        case 0:  Test_R = RGB_MATRIX_MAXIMUM_BRIGHTNESS; Test_G = 0;                             Test_B = 0;                             break;
        case 1:  Test_R = 0;                             Test_G = RGB_MATRIX_MAXIMUM_BRIGHTNESS; Test_B = 0;                             break;
        case 2:  Test_R = 0;                             Test_G = 0;                             Test_B = RGB_MATRIX_MAXIMUM_BRIGHTNESS; break;
        case 3:  Test_R = RGB_MATRIX_MAXIMUM_BRIGHTNESS; Test_G = RGB_MATRIX_MAXIMUM_BRIGHTNESS; Test_B = RGB_MATRIX_MAXIMUM_BRIGHTNESS; break;
        default: Test_R = RGB_MATRIX_MAXIMUM_BRIGHTNESS; Test_G = RGB_MATRIX_MAXIMUM_BRIGHTNESS; Test_B = RGB_MATRIX_MAXIMUM_BRIGHTNESS; break;
    }
    rgb_matrix_driver_set_color_all(Test_R, Test_G, Test_B);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (User_Power_Low) {
        Led_Power_Low_Show();
    } else if (Test_Led) {
        User_Test_Colour_Show();
    } else if (Led_Rf_Pair_Flg && (Keyboard_Info.Key_Mode != QMK_USB_MODE)) {
        Led_Rf_Mode_Show();
    } else if (User_Key_Batt_Num_Show) {
        Led_Batt_Number_Show();
    } else {
        User_Point_Show();

        if (Key_Fn_Status) {
            switch (Keyboard_Info.Key_Mode) {
                case QMK_BLE_MODE: {
                    switch (Keyboard_Info.Ble_Channel) {
                        case QMK_BLE_CHANNEL_1: rgb_matrix_set_color(LED_BLE_1_INDEX, U_PWM, U_PWM, U_PWM); break;
                        case QMK_BLE_CHANNEL_2: rgb_matrix_set_color(LED_BLE_2_INDEX, U_PWM, U_PWM, U_PWM); break;
                        case QMK_BLE_CHANNEL_3: rgb_matrix_set_color(LED_BLE_3_INDEX, U_PWM, U_PWM, U_PWM); break;
                        default:                                                                            break;
                    } 
                } break;
                case QMK_2P4G_MODE:             rgb_matrix_set_color(LED_2P4G_INDEX, U_PWM, U_PWM, U_PWM);  break;
                case QMK_USB_MODE:              rgb_matrix_set_color(LED_USB_INDEX,  U_PWM, U_PWM, U_PWM);  break;
                default:                                                                                    break;
            }
        }
    }

    return false;
}

void notify_usb_device_state_change_user(enum usb_device_state usb_device_state)  {
    if (Keyboard_Info.Key_Mode == QMK_USB_MODE) {
        if(usb_device_state == USB_DEVICE_STATE_CONFIGURED) {
            Usb_If_Ok_Led = true;
        } else {
            Usb_If_Ok_Led = false;
        }
    } else {
        Usb_If_Ok_Led = false;
    }
}

void matrix_io_delay(void) {
}

void matrix_output_select_delay(void) {
}

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
}

void housekeeping_task_user(void) {
    if (Keyboard_Reset) {
        Keyboard_Reset = false;

        Keyboard_Info.Nkro = INIT_ALL_KEY;
        Keyboard_Info.Mac_Win_Mode = INIT_WIN_MODE;
        Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
        Reset_Save_Flash = true;
        /*将当前模式写入flash*/
        eeprom_write_block_user((void *)&Keyboard_Info.Key_Mode, 0, sizeof(Keyboard_Info_t));
        Reset_Save_Flash = false;

    #ifdef NO_RESET
        eeconfig_init();
    #else
        eeconfig_disable();
        soft_reset_keyboard();
    #endif
        return;
    }

    es_chibios_user_idle_loop_hook();
}

void board_init(void) {
    es_ble_spi_init();          //SPI

    User_Adc_Init();            //ADC

    eeprom_driver_init();       //EEPROM

    rgb_matrix_driver_init();   //PWM DMA

    Init_Gpio_Infomation();     //GPIO

    Init_Keyboard_Infomation();

    Init_Batt_Infomation();

    User_Systime_Init();

    if (Keyboard_Info.Key_Mode == QMK_USB_MODE) {   
        User_Usb_Init();
        Led_Rf_Pair_Flg = false;
    } else {
        Usb_Disconnect();
    }

    Init_Spi_Power_Up = true;
    Init_Spi_100ms_Delay = 0;
    Spi_Interval = SPI_DELAY_RF_TIME;
	NVIC_SetPriority(PendSV_IRQn, 3);
	NVIC_SetPriority(SysTick_IRQn, 3);

    Usb_If_Ok_Led = false;
    Led_Power_Up = false;
    Emi_Test_Start = false;
    Keyboard_Reset = false;
}

void keyboard_post_init_user(void) {
    if (keymap_config.nkro != Keyboard_Info.Nkro) {
        keymap_config.nkro = Keyboard_Info.Nkro;
    }

    if (Keyboard_Info.Mac_Win_Mode) {
        uint8_t current_layer = get_highest_layer(layer_state);
        if (current_layer != 1) {
            layer_on(1);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    Usb_Change_Mode_Delay = 0;
    Usb_Change_Mode_Wakeup = false;

    if (Test_Led) {
        if ((keycode != KC_SPC) && (keycode != MO(2)) && (keycode != MO(3)) && (keycode != KC_LCTL)) {
            Test_Led = false;
        }
    }

    switch (keycode) {
        case QMK_KB_MODE_2P4G: {                                    //2.4G
            if (record->event.pressed) {
                Key_2p4g_Status = true;
                Usb_Disconnect();
                if (Keyboard_Info.Key_Mode != QMK_2P4G_MODE) {
                    Keyboard_Info.Key_Mode = QMK_2P4G_MODE;
                    Spi_Send_Commad(USER_SWITCH_2P4G_MODE);
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = true;
                }
            } else {
                Key_2p4g_Status = false;
            }
            Time_3s_Count = 0;
        } return true;
        case QMK_KB_MODE_BLE1: {
            if (record->event.pressed) {
                Key_Ble_1_Status = true;
                Usb_Disconnect();
                if ((Keyboard_Info.Key_Mode != QMK_BLE_MODE) || ((Keyboard_Info.Key_Mode == QMK_BLE_MODE) && (Keyboard_Info.Ble_Channel != QMK_BLE_CHANNEL_1))) {   /*如果当前模式不是BLE模式则切换为BLE，或者BLE通道不相同*/
                    Keyboard_Info.Key_Mode = QMK_BLE_MODE;
                    Keyboard_Info.Ble_Channel = QMK_BLE_CHANNEL_1;
                    Spi_Send_Commad(USER_SWITCH_BLE_1_MODE);
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = true;
                }
            } else {
                Key_Ble_1_Status = false;
            }
            Time_3s_Count = 0;
        } return true;
        case QMK_KB_MODE_BLE2: {
            if (record->event.pressed) {
                Key_Ble_2_Status = true;
                Usb_Disconnect();
                if ((Keyboard_Info.Key_Mode != QMK_BLE_MODE) || ((Keyboard_Info.Key_Mode == QMK_BLE_MODE) && (Keyboard_Info.Ble_Channel != QMK_BLE_CHANNEL_2))) {   /*如果当前模式不是BLE模式则切换为BLE，或者BLE通道不相同*/
                    Keyboard_Info.Key_Mode = QMK_BLE_MODE;
                    Keyboard_Info.Ble_Channel = QMK_BLE_CHANNEL_2;
                    Spi_Send_Commad(USER_SWITCH_BLE_2_MODE);
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = true;
                }
            } else {
                Key_Ble_2_Status = false;
            }
            Time_3s_Count = 0;
        } return true;
        case QMK_KB_MODE_BLE3: {
            if (record->event.pressed) {
                Key_Ble_3_Status = true;
                Usb_Disconnect();
                if ((Keyboard_Info.Key_Mode != QMK_BLE_MODE) || ((Keyboard_Info.Key_Mode == QMK_BLE_MODE) && (Keyboard_Info.Ble_Channel != QMK_BLE_CHANNEL_3))) {   /*如果当前模式不是BLE模式则切换为BLE，或者BLE通道不相同*/
                    Keyboard_Info.Key_Mode = QMK_BLE_MODE;
                    Keyboard_Info.Ble_Channel = QMK_BLE_CHANNEL_3;  
                    Spi_Send_Commad(USER_SWITCH_BLE_3_MODE);
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = true;
                }
            } else {
                Key_Ble_3_Status = false;
            }
            Time_3s_Count = 0;
        } return true;
        case QMK_KB_MODE_USB: {
            if (record->event.pressed) {
                if (Keyboard_Info.Key_Mode != QMK_USB_MODE) {
                    Keyboard_Info.Key_Mode = QMK_USB_MODE;
                    Spi_Send_Commad(USER_SWITCH_USB_MODE);
                    es_restart_usb_driver();
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = false;
                }
            }
        } return true;
        case QMK_BATT_NUM: {
            if (record->event.pressed) {
                User_Key_Batt_Num_Show = true;
                User_Key_Batt_Count = 0;
            } else {
                User_Key_Batt_Num_Show = false;
                User_Key_Batt_Count = 0;
            }
        } return true;
        case QMK_WIN_LOCK: {
            if (!record->event.pressed) {
                if (Keyboard_Info.Mac_Win_Mode == INIT_MAC_MODE) {
                    if (Keyboard_Info.Win_Lock == INIT_WIN_LOCK) {
                        Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
                        Save_Flash_Set();
                    }
                } else {
                    if (Keyboard_Info.Win_Lock == INIT_WIN_NLOCK) {
                        Keyboard_Info.Win_Lock = INIT_WIN_LOCK;
                        unregister_code(KC_LGUI); unregister_code(KC_RGUI); unregister_code(KC_APP);
                    } else {
                        Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
                    }
                    Save_Flash_Set();
                }
            }
        } return true;
        case QMK_KB_SIX_N_CH: {
            if (record->event.pressed) {
                if(keymap_config.nkro) {
                    es_change_qmk_nkro_mode_disable();
                    Mac_Win_Point_Count = 3;  
                } else {
                    es_change_qmk_nkro_mode_enable();
                    Led_Point_Count = 3;
                } 
            }
        } return true;
        case QMK_TEST_COLOUR: {
            if (!record->event.pressed) {
                if (Test_Led == false) {
                    Test_Led = true;
                    Test_Colour = 0;
                }
            }
        } return true;
        case KC_SPC: {
            if (!record->event.pressed) {
                if (Test_Led) {
                    Test_Colour++;
                    if (Test_Colour >= 4) {
                        Test_Colour = 0;
                    }
                }
            }
        } return true;
        case KC_LGUI: {                                             //key_win_l
            if (Keyboard_Info.Win_Lock) {
                record->event.pressed = false;
            }
        } return true;
        case KC_RGUI: {                                             //key_win_r
            if (Keyboard_Info.Win_Lock) {
                record->event.pressed = false;
            }
        } return true;
        case KC_APP: {                                              //key_app
            if (Keyboard_Info.Win_Lock) {
                record->event.pressed = false;
            }
        } return true;
        case RGB_VAI: {
            if (!record->event.pressed) {
                if (rgb_matrix_get_val() >= RGB_MATRIX_MAXIMUM_BRIGHTNESS) {
                    Led_Point_Count = 3;
                }
            }
        } return true;
        case RGB_VAD: {
            if (!record->event.pressed) {
                if (rgb_matrix_get_val() <= 0) {
                    Led_Point_Count = 3;
                }
            }
        } return true;
        case RGB_SPI: {
            if (!record->event.pressed) {
                if (rgb_matrix_get_speed() >= 255) {
                    Led_Point_Count = 3;
                }
            }
        } return true;
        case RGB_SPD: {
            if (!record->event.pressed) {
                if (rgb_matrix_get_speed() <= 0) {
                    Led_Point_Count = 3;
                }
            }
        } return true;
        case MO(2): {                                               //FN
            if (record->event.pressed) {
                Key_Fn_Status = true;
            } else {
                Key_Fn_Status = false;
            }
        } return true;
        case MO(3): {                                               //FN
            if (record->event.pressed) {
                Key_Fn_Status = true;
            } else {
                Key_Fn_Status = false;
            }
        } return true;
        case TO(0): {                                               //WIN 
            if (!record->event.pressed) {
                if ((record->event.key.col == WIN_COL) && (record->event.key.row == WIN_ROL) && (Keyboard_Info.Mac_Win_Mode != INIT_WIN_MODE)) {
                    Keyboard_Info.Mac_Win_Mode = INIT_WIN_MODE;
                    Mac_Win_Point_Count = 1;
                    unregister_code(KC_LALT); unregister_code(KC_LGUI); unregister_code(KC_RALT); unregister_code(KC_RGUI); unregister_code(KC_APP);
                    Save_Flash_Set();
                }
            }
        } return true;
        case TO(1): {                                               //MAC
            if (!record->event.pressed) {
                if ((record->event.key.col == MAC_COL) && (record->event.key.row == MAC_ROL) && (Keyboard_Info.Mac_Win_Mode != INIT_MAC_MODE)) {
                    Keyboard_Info.Mac_Win_Mode = INIT_MAC_MODE;
                    Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
                    Mac_Win_Point_Count = 3;
                    unregister_code(KC_LALT); unregister_code(KC_LGUI); unregister_code(KC_RALT); unregister_code(KC_RGUI); unregister_code(KC_APP);
                    Save_Flash_Set();
                }
            }
        } return true;
        case EE_CLR: {
            if (record->event.pressed) {
                Key_Reset_Status = true;
                record->event.pressed = false;
            } else {
                Key_Reset_Status = false;
            }
            Func_Time_3s_Count = 0;
        } return true;
        default:    return true; // Process all other keycodes normally
    }
}
