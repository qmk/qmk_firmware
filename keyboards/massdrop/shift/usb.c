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

void usb_set_host_kb(uint8_t con, uint8_t rp_best_index) {
    if (con == 1) {
        //DN1 to A (CON2/EX2), UP to B (CON1/EX1)
        sr_exp_data.bit.S_A_UP = 1;                     //0 = DN1 to B and UP to A, 1 = DN1 to A and UP to B (SAI-SBI)

        if (ADC_USBC_IS_ONB(rp_best_index)) {           //Check if the port detected is onboard
            sr_exp_data.bit.S_B_EXT = 0;                //Onboard port
            g_usb_host_port = USB_HOST_PORT_1;          //Save host port
        } else {                                        //Port is external
            sr_exp_data.bit.S_B_EXT = 1;                //External port
            g_usb_host_port = USB_HOST_PORT_1_EXT;      //Save host port
        }

        sr_exp_data.bit.E_VBUS_1 = 1;                   //Enable CON1 5V

        SR_EXP_WriteData();                             //Update port configuration
    } else if (con == 2) {
        //DN1 to B (CON1/EX1), UP to A (CON2/EX2)
        sr_exp_data.bit.S_A_UP = 0;                     //0 = DN1 to B and UP to A, 1 = DN1 to A and UP to B (SAI-SBI)

        if (ADC_USBC_IS_ONB(rp_best_index)) {           //Check if the port detected is onboard
            sr_exp_data.bit.S_A_EXT = 1;                //Onboard port
            g_usb_host_port = USB_HOST_PORT_2;          //Save host port
        } else {                                        //Port is external
            sr_exp_data.bit.S_A_EXT = 0;                //External port
            g_usb_host_port = USB_HOST_PORT_2_EXT;      //Save host port
        }

        sr_exp_data.bit.E_VBUS_2 = 1;                   //Enable CON2 5V

        SR_EXP_WriteData();                             //Update port configuration
    }
}

void usb_set_extra_kb(uint8_t con) {
    if (con == 1) {
        sr_exp_data.bit.SRC_1_A5 = 0;                   //Set CON1 CC A5 as Rp 56k
        sr_exp_data.bit.SRC_1_B5 = 0;                   //Set CON1 CC B5 as Rp 56k
        sr_exp_data.bit.E_VBUS_1 = 0;                   //Disable CON1 5V
        SR_EXP_WriteData();                             //Update port configuration
    } else if (con == 2) {
        sr_exp_data.bit.SRC_2_A5 = 0;                   //Set CON2 CC A5 as Rp 56k
        sr_exp_data.bit.SRC_2_B5 = 0;                   //Set CON2 CC B5 as Rp 56k
        sr_exp_data.bit.E_VBUS_2 = 0;                   //Disable CON2 5V
        SR_EXP_WriteData();                             //Update port configuration
    }
}

void usb_init_host_detection_kb(void) {
    //Disable 5V
    sr_exp_data.bit.E_VBUS_1 = 0;                       //Disable CON1 5V
    sr_exp_data.bit.E_VBUS_2 = 0;                       //Disable CON2 5V

    //Configure default paths
    sr_exp_data.bit.S_A_UP = 0;                         //DN1 TO A & UP TO B WHEN 1, DN1 TO B & UP TO A WHEN 0
    sr_exp_data.bit.S_A_EXT = 1;                        //1 = Onboard, 0 = Offboard (SAO)
    sr_exp_data.bit.S_B_EXT = 0;                        //0 = Onboard, 1 = Offboard (SBO)

    //Configure CC lines
    sr_exp_data.bit.SRC_1_A5 = 1;                       //Set CON1 CC A5 as Rd 5.1k
    sr_exp_data.bit.SRC_1_B5 = 1;                       //Set CON1 CC B5 as Rd 5.1k
    sr_exp_data.bit.SRC_2_A5 = 1;                       //Set CON2 CC A5 as Rd 5.1k
    sr_exp_data.bit.SRC_2_B5 = 1;                       //Set CON2 CC B5 as Rd 5.1k

    //Enable ports
    sr_exp_data.bit.ENB = 1;                            //Enable CON1/EX1 for use
    sr_exp_data.bit.ENA = 1;                            //Enable CON2/EX2 for use

    SR_EXP_WriteData();                                 //Update port configuration
}

//Return 1 if configuration successful
//Return 0 otherwise
uint8_t usb_attach_port_configure_kb(uint8_t g_usb_host_port, uint16_t usbc_cc_a5_v, uint16_t usbc_cc_b5_v) {
    if (USB_HOST_IS_1(g_usb_host_port)) {                               //If host is port 1
        //Set up port 2
        if (USBC_IS_SINK_ONB(usbc_cc_a5_v, usbc_cc_b5_v)) {             //If onboard port detected
            sr_exp_data.bit.S_A_EXT = 1;                                //Set port 2 as onboard port
            SR_EXP_WriteData();                                         //Update port configuration
            return 1;
        } else if (USBC_IS_SINK_EXT(usbc_cc_a5_v, usbc_cc_b5_v)) {      //If external port detected
            sr_exp_data.bit.S_A_EXT = 0;                                //Set port 2 as onboard port
            SR_EXP_WriteData();                                         //Update port configuration
            return 1;
        }
    } else if (USB_HOST_IS_2(g_usb_host_port)) {                        //If host is on port 2
        //Set up port 1
        if (USBC_IS_SINK_ONB(usbc_cc_a5_v, usbc_cc_b5_v)) {             //If onboard port detected
            sr_exp_data.bit.S_B_EXT = 0;                                //Set port 1 as onboard port
            SR_EXP_WriteData();                                         //Update port configuration
            return 1;
        } else if (USBC_IS_SINK_EXT(usbc_cc_a5_v, usbc_cc_b5_v)) {      //If external port detected
            sr_exp_data.bit.S_B_EXT = 1;                                //Set port 1 as external port
            SR_EXP_WriteData();                                         //Update port configuration
            return 1;
        }
    }

    return 0;
}
