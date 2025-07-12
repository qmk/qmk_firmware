// /* Copyright 2024 Jacky
//  *
//  * This program is free software: you can redistribute it and/or modify
//  * it under the terms of the GNU General Public License as published by
//  * the Free Software Foundation, either version 2 of the License, or
//  * (at your option) any later version.
//  *
//  * This program is distributed in the hope that it will be useful,
//  * but WITHOUT ANY WARRANTY; without even the implied warranty of
//  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  * GNU General Public License for more details.
//  *
//  * You should have received a copy of the GNU General Public License
//  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
//  */

#include "uart.h"
#include "ch.h"
#include "hal.h"
#include "host.h"
#include "host_driver.h"
#include "report.h"
#include "smart_ble.h"

static uint8_t sc_ble_leds(void) {
    return 0;    // TODO: Get LED status  BLE
}

static void sc_ble_mouse(report_mouse_t *report) {
    static uint8_t last_report[sizeof(report_mouse_t)]={0};

    if (!has_mouse_report_changed((report_mouse_t *)last_report, report)) return;
    memcpy(last_report,report,sizeof(report_mouse_t));
    uart_write(0x55);
    uart_write(sizeof(report_mouse_t));
    uart_transmit(last_report,sizeof(report_mouse_t));
}


static void sc_ble_extra(report_extra_t *report) {
    uart_write(0x55);
    uart_write(sizeof(report_extra_t));
    uart_transmit((uint8_t *)report,sizeof(report_extra_t));
}

static void sc_ble_keyboard(report_keyboard_t *report) {
    uart_write(0x55);
    uart_write(0x09);
    uart_write(0x01);
    uart_transmit((uint8_t *)report,KEYBOARD_REPORT_SIZE);
}

static void sc_send_nkro(report_nkro_t *report)
{
    uart_write(0x55);
    uart_write(0x12);
    uart_transmit((uint8_t *)report,0x12);
}

static host_driver_t *last_host_driver = NULL;
static host_driver_t sc_ble_driver = {
    sc_ble_leds, sc_ble_keyboard,sc_send_nkro,sc_ble_mouse, sc_ble_extra
};


void smart_ble_startup(void) {     
    if (host_get_driver() == &sc_ble_driver) {
        return;
    }
    clear_keyboard();
    last_host_driver = host_get_driver();
    host_set_driver(&sc_ble_driver);
}

void smart_ble_disconnect(void) {
    if (host_get_driver() != &sc_ble_driver) {
        return;
    }
    clear_keyboard();
    host_set_driver(last_host_driver);
}


void sc_ble_battary(uint8_t batt_level) {
        uart_write(0x55);
        uart_write(0x02);
        uart_write(0x09);  
        uart_write(batt_level);
}

void WIRELESS_START(uint32_t mode)
{
    uint8_t ble_command[24]; 
    smart_ble_startup();
    if(mode<1 || mode>4)
    {
        mode=1;
    }
    ble_command[0]=0x55;  
    ble_command[1]=20;   
    ble_command[2]=0;       
    ble_command[3]=mode;    
    strcpy((char * restrict)(ble_command+4),PRODUCT);  
    ble_command[strlen(PRODUCT)+4]='-';   
    ble_command[strlen(PRODUCT)+5]='0' + mode;   
    ble_command[strlen(PRODUCT)+6]= 0;
    uart_transmit(ble_command,sizeof(ble_command));
}

void WIRELESS_STOP(void)
{
    smart_ble_disconnect();
    uart_write(0x55);  
    uart_write(0x02);   
    uart_write(0x00);
    uart_write(0x00);
}







