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

extern uint16_t Usb_Suspend_Delay;
extern uint16_t Usb_Change_Mode_Delay;
extern bool Usb_Change_Mode_Wakeup;
extern bool Mode_Synchronization_Signal;

extern uint16_t g_usb_sof_frame_id;
extern uint16_t g_usb_sof_frame_id_last;
extern bool Usb_Dis_Connect;

extern void Mode_Synchronization(void);
extern void Ble_Name_Synchronization(void);

extern uint8_t es_keyboard_leds(void);
extern void es_send_keyboard(report_keyboard_t *report);
extern void es_send_nkro(report_nkro_t *report);
extern void es_send_mouse(report_mouse_t *report);
extern void es_send_extra(report_extra_t *report);
#ifdef RAW_ENABLE
extern void es_send_raw_hid(uint8_t *data, uint8_t length);
#endif
extern void User_bluetooth_send_keyboard(uint8_t *report, uint32_t len);

extern volatile host_driver_t * es_qmk_driver;
extern const host_driver_t es_user_driver;

extern void User_Usb_Init(void);
extern void es_restart_usb_driver(void);
extern void Usb_Disconnect(void);
extern void User_Usb_Deinit(void);
