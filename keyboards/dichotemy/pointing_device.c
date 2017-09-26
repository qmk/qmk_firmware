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
    //mouseReport.x = 127 max -127 min
    //mouseReport.y = 127 max -127 min
    //mouseReport.v = 127 max -127 min (scroll vertical)
    //mouseReport.h = 127 max -127 min (scroll horizontal)
    //mouseReport.buttons = 0x31 max (bitmask for mouse buttons 1-5) 0x00 min
    pointing_device_send(mouseReport);
}   
