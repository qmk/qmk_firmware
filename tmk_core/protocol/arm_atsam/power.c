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

#ifndef MD_BOOTLOADER

#include "arm_atsam_protocol.h"

uint64_t v_5v_cat_timer;        //Timer for recovery period post 5v catastrophic low voltage detected (and LED driver disable)(-1 indicates timer not active)
uint64_t v_5v_low_timer;        //Timer for disabling USB extra device after causing a low voltage situation for an amount of time (-1 indicates timer not active)

//Returns 1 if the 5v bus is in a catastrophic low voltage condition
//Returns 0 if the 5v bus is OK
uint8_t power_5v_check(void) {
    if (g_v_5v < V5_CAT) {                                                          //If the 5v bus has reached a catastrophic low level
        //See if this is a spike condition due to noise by re-testing a few times
        uint8_t v_5v_tests;                                                         //Current 5v bus test number
        uint16_t v_5v_test_cat;                                                     //Current 5v bus reading
        for (v_5v_tests = 0; v_5v_tests < POWER_5V_SPIKE_TESTS; v_5v_tests++) {     //Run spike tests
            v_5v_test_cat = adc_get(ADC_5V);                                        //Get new 5v bus reading
            if (v_5v_test_cat > V5_CAT) {                                           //If the reading is not catastrophic
                g_v_5v = v_5v_test_cat;                                             //Spike was temporary so update to new reading
                break;                                                              //Break from spike testing
            }
        }
    }

    if (g_v_5v < V5_CAT) {
        //The spike is a sustained event, so begin cutting back power where possible to recover
        //If the LED drivers are on, disable them briefly, set GCR to minimum, and assert auto GCR mode is enabled
        if (I2C3733_Control_Get()) {
            I2C3733_Control_Set(0);                                                 //Disable all LED drivers
            v_5v_cat_timer = timer_read64() + 250;                                  //Begin the catastrophic low voltage timer
            gcr_actual = 0;                                                         //Minimize GCR
            usb_gcr_auto = 1;                                                       //Force auto GCR mode enabled
            dprintf("USB: WARNING: 5V catastrophic level reached! Disabling LED drivers!\n");   //Debug output
        } else {    //Else the LED drivers are already disabled or at zero GCR, so the extra port is taking too much power, cut its 5v
            if (usbc.state == USB_STATE_ATTACHED_SRC) {                             //If a device is attached
                if (usbc.state != USB_STATE_DISABLED_UNTIL_DETACH) {                //If not already in disabled waiting state
                    usbc.state = USB_STATE_DISABLED_UNTIL_DETACH;                   //Set state to disable until the device is unplugged
                    usbc_task();                                                    //Immediately update USBC state to disable 5V
                    dprintf("USB: Disabling extra port until device unplugged!\n"); //Debug output
                }
            }
        }
    }

    if (((uint16_t)g_v_5v_avg < V5_LOW) && (usbc.state == USB_STATE_ATTACHED_SRC))  //If 5v bus is low and a USB device is attached
    {
        if (v_5v_low_timer == -1) {                                                 //If the low voltage timer is not already running
            v_5v_low_timer = timer_read64() + 1000;                                 //Set the low voltage timer for 1s
        }
        if (timer_read64() > v_5v_low_timer) {                                      //If the low voltage timer has expired
            usbc.state = USB_STATE_DISABLED_UNTIL_DETACH;                           //Set usbc state to remove the load
            usbc_task();                                                            //Immediately update USBC state to disable 5V
            dprintf("USB: Disabling extra port until device unplugged!\n");         //Debug output
            v_5v_low_timer = -1;                                                    //Disable the low voltage timer
        }
    } else {                                                                        //else 5v bus is not low or USB device is not attached
        v_5v_low_timer = -1;                                                        //Disable the low voltage timer
    }

    if (v_5v_cat_timer != -1) {                                                     //If the catastrophic timer is active
        if (timer_read64() > v_5v_cat_timer) {                                      //If the catastrophic timer has expired
            if (!I2C3733_Control_Get()) {                                           //If LED drivers are enabled by the user
                I2C3733_Control_Set(1);                                             //Re-enable the LED drivers
            }
            dprintf("USB: WARNING: Re-enabling LED drivers\n");                     //Debug output
            v_5v_cat_timer = -1;                                                    //Disable the timer
        } else {                                                                    //Else the catastrophic timer is still running
            return 1;                                                               //Return catastrophic state
        }
    }

    return 0;                                                                       //Return OK state
}

void power_init(void) {
    v_5v_cat_timer = -1;                                                            //Disable the catastrophic low voltage timer
    v_5v_low_timer = -1;                                                            //Disable the low voltage timer
}

void power_run(void) {
    power_5v_check();                                                               //Run 5v bus check
}

#endif //MD_BOOTLOADER
