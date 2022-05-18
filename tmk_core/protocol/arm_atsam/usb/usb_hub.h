/*
Copyright 2018 Massdrop Inc.

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

#ifndef _USB2422_H_
#define _USB2422_H_

#define REV_USB2422 0x100

#define PORT_DETECT_RETRY_INTERVAL 2000

#define USB_EXTRA_ADC_THRESHOLD 900

#define USB_EXTRA_STATE_DISABLED 0
#define USB_EXTRA_STATE_ENABLED 1
#define USB_EXTRA_STATE_UNKNOWN 2
#define USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG 3

#define USB_HOST_PORT_1 0
#define USB_HOST_PORT_2 1
#define USB_HOST_PORT_UNKNOWN 2

extern uint8_t usb_host_port;
extern uint8_t usb_extra_state;
extern uint8_t usb_extra_manual;
extern uint8_t usb_gcr_auto;

void     USB_Hub_init(void);
uint8_t  USB_Hub_Port_Detect_Init(void);
void     USB_reset(void);
void     USB_configure(void);
uint16_t USB_active(void);
void     USB_set_host_by_voltage(void);
uint16_t adc_get(uint8_t muxpos);
void     USB_HandleExtraDevice(void);
void     USB_ExtraSetState(uint8_t state);

#endif //_USB2422_H_
