/*
Copyright 2017 Joshua Broekhuijsen <snipeye+qmk@gmail.com>

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

#include <stdint.h>
#include "report.h"
#include "host.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "pointing_device.h"

void pointingdevice_init(void){
    //initialize device, if that needs to be done.
}

void pointing_device_send(mouse_report_t mouseReport){
    //If you need to do other things, like debugging, this is the place to do it.
    host_mouse_send(mouseReport);
}

void pointing_device_task(void){
    mouse_report_t mouseReport = {};
    //gather info and put it in:
    SERIAL_UART_INIT();
    uint32_t timeout = 0;

    //the m character requests the RF slave to send the mouse report
    SERIAL_UART_DATA = 'm';

    //trust the external inputs completely, erase old data
    uint8_t uart_data[11] = {0};

    //there are 10 bytes corresponding to 10 columns, and an end byte
    for (uint8_t i = 0; i < 11; i++) {
        //wait for the serial data, timeout if it's been too long
        //this only happened in testing with a loose wire, but does no
        //harm to leave it in here
        while(!SERIAL_UART_RXD_PRESENT){
            timeout++;
            if (timeout > 10000){
                break;
            }
        } 
        uart_data[i] = SERIAL_UART_DATA;
    }

    //check for the end packet, the key state bytes use the LSBs, so 0xE0
    //will only show up here if the correct bytes were recieved
    if (uart_data[10] == 0xE0)
    {
        //shifting and transferring the info to the mouse report varaible
        //mouseReport.x = 127 max -127 min
        //mouseReport.y = 127 max -127 min
        //mouseReport.v = 127 max -127 min (scroll vertical)
        //mouseReport.h = 127 max -127 min (scroll horizontal)
        //mouseReport.buttons = 0x31 max (bitmask for mouse buttons 1-5) 0x00 min
    }

    //send the report
    pointing_device_send(mouseReport);
}   
