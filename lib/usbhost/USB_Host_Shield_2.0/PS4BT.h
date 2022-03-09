/* Copyright (C) 2014 Kristian Lauszus, TKJ Electronics. All rights reserved.

 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").

 Contact information
 -------------------

 Kristian Lauszus, TKJ Electronics
 Web      :  http://www.tkjelectronics.com
 e-mail   :  kristianl@tkjelectronics.com
 */

#ifndef _ps4bt_h_
#define _ps4bt_h_

#include "BTHID.h"
#include "PS4Parser.h"

/**
 * This class implements support for the PS4 controller via Bluetooth.
 * It uses the BTHID class for all the Bluetooth communication.
 */
class PS4BT : public BTHID, public PS4Parser {
public:
        /**
         * Constructor for the PS4BT class.
         * @param  p     Pointer to the BTD class instance.
         * @param  pair  Set this to true in order to pair with the device. If the argument is omitted then it will not pair with it. One can use ::PAIR to set it to true.
         * @param  pin   Write the pin to BTD#btdPin. If argument is omitted, then "0000" will be used.
         */
        PS4BT(BTD *p, bool pair = false, const char *pin = "0000") :
        BTHID(p, pair, pin) {
                PS4Parser::Reset();
        };

        /**
         * Used to check if a PS4 controller is connected.
         * @return Returns true if it is connected.
         */
        bool connected() {
                return BTHID::connected;
        };

protected:
        /** @name BTHID implementation */
        /**
         * Used to parse Bluetooth HID data.
         * @param len The length of the incoming data.
         * @param buf Pointer to the data buffer.
         */
        virtual void ParseBTHIDData(uint8_t len, uint8_t *buf) {
                PS4Parser::Parse(len, buf);
        };

        /**
         * Called when a device is successfully initialized.
         * Use attachOnInit(void (*funcOnInit)(void)) to call your own function.
         * This is useful for instance if you want to set the LEDs in a specific way.
         */
        virtual void OnInitBTHID() {
                PS4Parser::Reset();
                enable_sixaxis(); // Make the controller send out the entire output report
                if (pFuncOnInit)
                        pFuncOnInit(); // Call the user function
                else
                        setLed(Blue);
        };

        /** Used to reset the different buffers to there default values */
        virtual void ResetBTHID() {
                PS4Parser::Reset();
        };
        /**@}*/

        /** @name PS4Parser implementation */
        virtual void sendOutputReport(PS4Output *output) { // Source: https://github.com/chrippa/ds4drv
                uint8_t buf[79];
                memset(buf, 0, sizeof(buf));

                buf[0] = 0x52; // HID BT Set_report (0x50) | Report Type (Output 0x02)
                buf[1] = 0x11; // Report ID
                buf[2] = 0x80;
                buf[4]= 0xFF;

                buf[7] = output->smallRumble; // Small Rumble
                buf[8] = output->bigRumble; // Big rumble

                buf[9] = output->r; // Red
                buf[10] = output->g; // Green
                buf[11] = output->b; // Blue

                buf[12] = output->flashOn; // Time to flash bright (255 = 2.5 seconds)
                buf[13] = output->flashOff; // Time to flash dark (255 = 2.5 seconds)

                output->reportChanged = false;

                // The PS4 console actually set the four last bytes to a CRC32 checksum, but it seems like it is actually not needed

                HID_Command(buf, sizeof(buf));
        };
        /**@}*/

private:
        void enable_sixaxis() { // Command used to make the PS4 controller send out the entire output report
                uint8_t buf[2];
                buf[0] = 0x43; // HID BT Get_report (0x40) | Report Type (Feature 0x03)
                buf[1] = 0x02; // Report ID

                HID_Command(buf, 2);
        };

        void HID_Command(uint8_t *data, uint8_t nbytes) {
                pBtd->L2CAP_Command(hci_handle, data, nbytes, control_scid[0], control_scid[1]);
        };
};
#endif
