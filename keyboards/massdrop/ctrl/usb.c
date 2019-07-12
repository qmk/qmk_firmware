/*
Copyright 2019 Massdrop Inc.

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

#include "arm_atsam_protocol.h"

//Note: rp_best_index not used
void usb_set_host_kb(uint8_t con, uint8_t rp_best_index) {
    if (con == 1) {
        sr_exp_data.bit.S_UP = 0;                       //HOST to USBC-1
        sr_exp_data.bit.S_DN1 = 1;                      //EXTRA to USBC-2
        g_usb_host_port = USB_HOST_PORT_1;              //Save host port
        sr_exp_data.bit.E_VBUS_1 = 1;                   //Enable CON1 5V
        SR_EXP_WriteData();                             //Update port configuration
    } else if (con == 2) {
        sr_exp_data.bit.S_DN1 = 0;                      //HOST to USBC-2
        sr_exp_data.bit.S_UP = 1;                       //EXTRA to USBC-1
        g_usb_host_port = USB_HOST_PORT_2;              //Save host port
        sr_exp_data.bit.E_VBUS_2 = 1;                   //Enable CON2 5V
        SR_EXP_WriteData();                             //Update port configuration
    }
}

void usb_set_extra_kb(uint8_t con) {
    if (con == 1) {
        sr_exp_data.bit.SRC_1 = 0;                      //Set CON1 CC A5/B5 as Rp 56k
        sr_exp_data.bit.E_VBUS_1 = 0;                   //Disable CON1 5V
        SR_EXP_WriteData();                             //Update port configuration
    } else if (con == 2) {
        sr_exp_data.bit.SRC_2 = 0;                      //Set CON2 CC A5/B5 as Rp 56k
        sr_exp_data.bit.E_VBUS_2 = 0;                   //Disable CON2 5V
        SR_EXP_WriteData();                             //Update port configuration
    }
}

void usb_init_host_detection_kb(void) {
    //Disable 5V
    sr_exp_data.bit.E_VBUS_1 = 0;                       //Disable CON1 5V
    sr_exp_data.bit.E_VBUS_2 = 0;                       //Disable CON2 5V

    //Configure default paths
    sr_exp_data.bit.S_UP = 0;                           //HOST to USBC-1
    sr_exp_data.bit.S_DN1 = 1;                          //EXTRA to USBC-2

    //Configure CC lines
    sr_exp_data.bit.SRC_1 = 1;                          //Set CON1 CC A5/B5 as Rd 5.1k
    sr_exp_data.bit.SRC_2 = 1;                          //Set CON2 CC A5/B5 as Rd 5.1k

    //Enable ports
    sr_exp_data.bit.E_UP_N = 0;                         //Enable HOST for use
    sr_exp_data.bit.E_DN1_N = 0;                        //Enable EXTRA for use

    SR_EXP_WriteData();                                 //Update port configuration
}

//Return 1 if configuration successful
//Return 0 otherwise
uint8_t usb_attach_port_configure_kb(uint8_t g_usb_host_port, uint16_t usbc_cc_a5_v, uint16_t usbc_cc_b5_v) {
    if (USB_HOST_IS_1(g_usb_host_port)) {               //If host is port 1
        //Set up port 2
        usb_set_extra_kb(2);
        return 1;
    } else if (USB_HOST_IS_2(g_usb_host_port)) {        //If host is on port 2
        //Set up port 1
        usb_set_extra_kb(1);
        return 1;
    }

    return 0;
}
