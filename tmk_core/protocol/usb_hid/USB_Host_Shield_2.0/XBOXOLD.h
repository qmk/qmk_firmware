/* Copyright (C) 2013 Kristian Lauszus, TKJ Electronics. All rights reserved.

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

#ifndef _xboxold_h_
#define _xboxold_h_

#include "Usb.h"
#include "hid.h"
#include "controllerEnums.h"

/* Data Xbox taken from descriptors */
#define EP_MAXPKTSIZE       32 // Max size for data via USB

/* Names we give to the 3 Xbox pipes */
#define XBOX_CONTROL_PIPE    0
#define XBOX_INPUT_PIPE      1
#define XBOX_OUTPUT_PIPE     2

// PID and VID of the different devices
#define XBOX_VID                                0x045E // Microsoft Corporation
#define MADCATZ_VID                             0x1BAD // For unofficial Mad Catz controllers
#define JOYTECH_VID                             0x162E // For unofficial Joytech controllers

#define XBOX_OLD_PID1                           0x0202 // Original Microsoft Xbox controller (US)
#define XBOX_OLD_PID2                           0x0285 // Original Microsoft Xbox controller (Japan)
#define XBOX_OLD_PID3                           0x0287 // Microsoft Microsoft Xbox Controller S
#define XBOX_OLD_PID4                           0x0289 // Smaller Microsoft Xbox controller (US)

#define XBOX_MAX_ENDPOINTS   3

/** This class implements support for a the original Xbox controller via USB. */
class XBOXOLD : public USBDeviceConfig {
public:
        /**
         * Constructor for the XBOXOLD class.
         * @param  pUsb   Pointer to USB class instance.
         */
        XBOXOLD(USB *pUsb);

        /** @name USBDeviceConfig implementation */
        /**
         * Initialize the Xbox Controller.
         * @param  parent   Hub number.
         * @param  port     Port number on the hub.
         * @param  lowspeed Speed of the device.
         * @return          0 on success.
         */
        uint8_t Init(uint8_t parent, uint8_t port, bool lowspeed);
        /**
         * Release the USB device.
         * @return 0 on success.
         */
        uint8_t Release();
        /**
         * Poll the USB Input endpoins and run the state machines.
         * @return 0 on success.
         */
        uint8_t Poll();

        /**
         * Get the device address.
         * @return The device address.
         */
        virtual uint8_t GetAddress() {
                return bAddress;
        };

        /**
         * Used to check if the controller has been initialized.
         * @return True if it's ready.
         */
        virtual bool isReady() {
                return bPollEnable;
        };

        /**
         * Used by the USB core to check what this driver support.
         * @param  vid The device's VID.
         * @param  pid The device's PID.
         * @return     Returns true if the device's VID and PID matches this driver.
         */
        virtual bool VIDPIDOK(uint16_t vid, uint16_t pid) {
                return ((vid == XBOX_VID || vid == MADCATZ_VID || vid == JOYTECH_VID) && (pid == XBOX_OLD_PID1 || pid == XBOX_OLD_PID2 || pid == XBOX_OLD_PID3 || pid == XBOX_OLD_PID4));
        };
        /**@}*/

        /** @name Xbox Controller functions */
        /**
         * getButtonPress(ButtonEnum b) will return true as long as the button is held down.
         *
         * While getButtonClick(ButtonEnum b) will only return it once.
         *
         * So you instance if you need to increase a variable once you would use getButtonClick(ButtonEnum b),
         * but if you need to drive a robot forward you would use getButtonPress(ButtonEnum b).
         * @param  b          ::ButtonEnum to read.
         * @return            getButtonClick(ButtonEnum b) will return a bool, while getButtonPress(ButtonEnum b) will return a byte if reading ::L2 or ::R2.
         */
        uint8_t getButtonPress(ButtonEnum b);
        bool getButtonClick(ButtonEnum b);
        /**@}*/

        /** @name Xbox Controller functions */
        /**
         * Return the analog value from the joysticks on the controller.
         * @param  a          Either ::LeftHatX, ::LeftHatY, ::RightHatX or ::RightHatY.
         * @return            Returns a signed 16-bit integer.
         */
        int16_t getAnalogHat(AnalogHatEnum a);

        /** Turn rumble off the controller. */
        void setRumbleOff() {
                setRumbleOn(0, 0);
        };
        /**
         * Turn rumble on.
         * @param lValue     Left motor (big weight) inside the controller.
         * @param rValue     Right motor (small weight) inside the controller.
         */
        void setRumbleOn(uint8_t lValue, uint8_t rValue);

        /**
         * Used to call your own function when the controller is successfully initialized.
         * @param funcOnInit Function to call.
         */
        void attachOnInit(void (*funcOnInit)(void)) {
                pFuncOnInit = funcOnInit;
        };
        /**@}*/

        /** True if a Xbox controller is connected. */
        bool XboxConnected;

protected:
        /** Pointer to USB class instance. */
        USB *pUsb;
        /** Device address. */
        uint8_t bAddress;
        /** Endpoint info structure. */
        EpInfo epInfo[XBOX_MAX_ENDPOINTS];

private:
        /**
         * Called when the controller is successfully initialized.
         * Use attachOnInit(void (*funcOnInit)(void)) to call your own function.
         * This is useful for instance if you want to set the LEDs in a specific way.
         */
        void (*pFuncOnInit)(void); // Pointer to function called in onInit()

        bool bPollEnable;

        /* Variables to store the digital buttons */
        uint8_t ButtonState;
        uint8_t OldButtonState;
        uint8_t ButtonClickState;

        /* Variables to store the analog buttons */
        uint8_t buttonValues[8]; // A, B, X, Y, BLACK, WHITE, L1, and R1
        uint8_t oldButtonValues[8];
        bool buttonClicked[8];

        int16_t hatValue[4]; // Joystick values

        uint8_t readBuf[EP_MAXPKTSIZE]; // General purpose buffer for input data

        void readReport(); // Read incoming data
        void printReport(uint16_t length); // Print incoming date

        /* Private commands */
        void XboxCommand(uint8_t* data, uint16_t nbytes);
};
#endif
