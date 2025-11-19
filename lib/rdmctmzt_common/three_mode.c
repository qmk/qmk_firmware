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

uint16_t Usb_Suspend_Delay = 0;
uint16_t Usb_Change_Mode_Delay = 0;
bool Usb_Change_Mode_Wakeup = false;
bool Mode_Synchronization_Signal = false;

uint16_t g_usb_sof_frame_id = 0;
uint16_t g_usb_sof_frame_id_last = 0;
bool Usb_Dis_Connect = false;

void Mode_Synchronization(void) {
    switch(Keyboard_Info.Key_Mode) {
        case QMK_BLE_MODE: {
            switch (Keyboard_Info.Ble_Channel) {
                case QMK_BLE_CHANNEL_1: Spi_Send_Commad(USER_SWITCH_BLE_1_MODE);    break;
                case QMK_BLE_CHANNEL_2: Spi_Send_Commad(USER_SWITCH_BLE_2_MODE);    break;
                case QMK_BLE_CHANNEL_3: Spi_Send_Commad(USER_SWITCH_BLE_3_MODE);    break;
                default:                                                            break;
            }
            break;
        }
        case QMK_2P4G_MODE:             Spi_Send_Commad(USER_SWITCH_2P4G_MODE);     break;
        case QMK_USB_MODE:              Spi_Send_Commad(USER_SWITCH_USB_MODE);      break;
        default:                                                                    break;
    }
}

void Ble_Name_Synchronization(void) {
    switch(Ble_Name_Spi_Count) {
        case QMK_BLE_CHANNEL_1:         Spi_Send_Commad(USER_BLE1_WRITE_NAME);      Ble_Name_Spi_Count++;   break;
        case QMK_BLE_CHANNEL_2:         Spi_Send_Commad(USER_BLE2_WRITE_NAME);      Ble_Name_Spi_Count++;   break;
        case QMK_BLE_CHANNEL_3:         Spi_Send_Commad(USER_BLE3_WRITE_NAME);      Ble_Name_Spi_Count++;   break;
        default:                                                                                            break;
    }

    if(Ble_Name_Spi_Count >  QMK_BLE_CHANNEL_3) {
        Ble_Name_Spi_Count = QMK_BLE_CHANNEL_1;
        Ble_Name_Spi_Send = false;
    }
}

uint8_t es_keyboard_leds(void) {
    switch (Keyboard_Info.Key_Mode) {
        case QMK_2P4G_MODE: break;
        case QMK_BLE_MODE:  break;
        case QMK_USB_MODE:  break;
        default:            break;
    }

    if(es_qmk_driver) {
		return((*es_qmk_driver->keyboard_leds)());
	}

    return 0;
}

void es_send_keyboard(report_keyboard_t *report) {
    switch (Keyboard_Info.Key_Mode) {
        case QMK_2P4G_MODE: User_bluetooth_send_keyboard((uint8_t *)report,sizeof(report_keyboard_t));  break;
        case QMK_BLE_MODE:  User_bluetooth_send_keyboard((uint8_t *)report,sizeof(report_keyboard_t));  break;
        case QMK_USB_MODE:  break;
        default:            break;
    }

    if(es_qmk_driver) {
		(*es_qmk_driver->send_keyboard)(report);
	}
}

void es_send_nkro(report_nkro_t *report) {
    switch (Keyboard_Info.Key_Mode) {
        case QMK_2P4G_MODE: User_bluetooth_send_keyboard((uint8_t *)report,sizeof(report_nkro_t));  break;
        case QMK_BLE_MODE:  User_bluetooth_send_keyboard((uint8_t *)report,sizeof(report_nkro_t));  break;
        case QMK_USB_MODE:  break;
        default:            break;
    }

    if(es_qmk_driver) {
		(*es_qmk_driver->send_nkro)(report);
	}
}

void es_send_mouse(report_mouse_t *report) {
    switch (Keyboard_Info.Key_Mode) {
        case QMK_2P4G_MODE: User_bluetooth_send_keyboard((uint8_t *)report,sizeof(report_mouse_t));  break;
        case QMK_BLE_MODE:  User_bluetooth_send_keyboard((uint8_t *)report,sizeof(report_mouse_t));  break;
        case QMK_USB_MODE:  break;
        default:            break;
    }


    if(es_qmk_driver) {
		(*es_qmk_driver->send_mouse)(report);
	}
}

void es_send_extra(report_extra_t *report) {
    switch (Keyboard_Info.Key_Mode) {
        case QMK_2P4G_MODE: User_bluetooth_send_keyboard((uint8_t *)report,sizeof(report_extra_t));  break;
        case QMK_BLE_MODE:  User_bluetooth_send_keyboard((uint8_t *)report,sizeof(report_extra_t));  break;
        case QMK_USB_MODE:  break;
        default:            break;
    }

    if(es_qmk_driver) {
		(*es_qmk_driver->send_extra)(report);
	}
}

#ifdef RAW_ENABLE
void es_send_raw_hid(uint8_t *data, uint8_t length) {
    if(!es_qmk_driver) {
        return;
    }

    if(es_qmk_driver && es_qmk_driver->send_raw_hid) {
		(*es_qmk_driver->send_raw_hid)(data, length);
	}
}
#endif

volatile host_driver_t * es_qmk_driver = NULL;
const host_driver_t es_user_driver  = {
    .keyboard_leds = es_keyboard_leds,
    .send_keyboard = es_send_keyboard,
    .send_nkro = es_send_nkro,
    .send_mouse = es_send_mouse,
    .send_extra = es_send_extra,
#ifdef RAW_ENABLE
    .send_raw_hid = es_send_raw_hid,
#endif
};

void User_bluetooth_send_keyboard(uint8_t *report, uint32_t len) {
	if(app_2g4_buffer_full()) {
		return;
	}

    if (len > USER_KEYBOARD_LENGTH - 3) {
        len = USER_KEYBOARD_LENGTH - 3;
    }

    uint8_t Temp_Tx_Buf[USER_KEYBOARD_LENGTH] = {0};

    Temp_Tx_Buf[0] = USER_KEYBOARD_COMMAND;
    Temp_Tx_Buf[1] = USER_KEYBOARD_LENGTH;

    if (len == sizeof(report_keyboard_t)) {  //六键
        memcpy((void *)&Temp_Tx_Buf[3], report, len);
        Temp_Tx_Buf[2] = USER_KEY_BYTE_DATA;
    } else {
        switch (report[0]) {
            case KB_REPORT_ID: {            //全键
                memcpy((void *)&Temp_Tx_Buf[3], report, len);
                Temp_Tx_Buf[2] = USER_KEY_BIT_DATA;
                break;
            }
            case SYS_REPORT_ID: {           //系统键
                memcpy((void *)&Temp_Tx_Buf[3], report, len);
                Temp_Tx_Buf[2] = USER_SYSTEM_DATA;
                break;
            }
            case CON_REPORT_ID: {           //多媒体键
                memcpy((void *)&Temp_Tx_Buf[3], report, len);
                Temp_Tx_Buf[2] = USER_CONSUMER_DATA;
                break;
            }
            case MOUSE_REPORT_ID: {         //鼠标
                memcpy((void *)&Temp_Tx_Buf[3], report, len);
                Temp_Tx_Buf[2] = USER_MOUSE_DATA;
                break;
            }
            default: {
                break;
            }
        }
    }

    memcpy(app_2g4_data[app_2g4_data_rev], Temp_Tx_Buf, USER_KEYBOARD_LENGTH);
    app_2g4_buffer_rev_add();
}

void User_Usb_Init(void) {
    /*Using USB_SOF to calibrate the internal clock*/
    md_rcu_enable_csu(RCU);
    CSU->CON |= CSU_CON_AUTOEN_MSK;
    CSU->CON |= CSU_CON_CNTEN_MSK;
}

void es_restart_usb_driver(void) {
    md_rcu_enable_usb(RCU);
    ald_usb_device_components_init();
	USB->TXIER = 0x7F;
	USB->RXIER = 0x7E;
	USB->IER = 0x2F;
	usb_lld_connect_bus(0);
	ald_usb_int_register();
}

void Usb_Disconnect(void) {
    ald_usb_int_unregister();
    usb_lld_disconnect_bus(0);

    md_rcu_enable_usb_reset(RCU);
    md_rcu_disable_usb_reset(RCU);
    md_rcu_disable_usb(RCU);
}

void User_Usb_Deinit(void) {
    md_rcu_enable_csu_reset(RCU);
    md_rcu_disable_csu_reset(RCU);
    md_rcu_disable_csu(RCU);
}
