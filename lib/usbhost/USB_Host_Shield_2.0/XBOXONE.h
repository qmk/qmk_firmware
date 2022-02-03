/* Copyright (C) 2012 Kristian Lauszus, TKJ Electronics. All rights reserved.
   Copyright (C) 2015 guruthree

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

 guruthree
 Web      :  https://github.com/guruthree/
 */


#ifndef _xboxone_h_
#define _xboxone_h_

#include "Usb.h"
#include "xboxEnums.h"

/* Data Xbox ONE taken from descriptors */
#define EP_MAXPKTSIZE       32 // max size for data via USB

/* Names we give to the 3 XboxONE pipes */
#define XBOX_CONTROL_PIPE    0
#define XBOX_OUTPUT_PIPE     1
#define XBOX_INPUT_PIPE      2

// PID and VID of the different devices
#define XBOX_VID                                0x045E // Microsoft Corporation
#define XBOX_ONE_PID                            0x02D1 // Microsoft One Wired controller

#define XBOX_REPORT_BUFFER_SIZE 14 // Size of the input report buffer

#define XBOX_MAX_ENDPOINTS   3

/** This class implements support for a Xbox ONE controller connected via USB. */
class XBOXONE : public USBDeviceConfig {
public:
        /**
         * Constructor for the XBOXONE class.
         * @param  pUsb   Pointer to USB class instance.
         */
        XBOXONE(USB *pUsb);

        /** @name USBDeviceConfig implementation */
        /**
         * Initialize the Xbox Controller.
         * @param  parent   Hub number.
         * @param  port     Port number on the hub.
         * @param  lowspeed Speed of the device.
         * @return          0 on success.
         */
        virtual uint8_t Init(uint8_t parent, uint8_t port, bool lowspeed);
        /**
         * Release the USB device.
         * @return 0 on success.
         */
        virtual uint8_t Release();
        /**
         * Poll the USB Input endpoins and run the state machines.
         * @return 0 on success.
         */
        virtual uint8_t Poll();

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
                return (vid == XBOX_VID && pid == XBOX_ONE_PID);
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
         * @return            getButtonClick(ButtonEnum b) will return a bool, while getButtonPress(ButtonEnum b) will return a word if reading ::L2 or ::R2.
         */
        uint16_t getButtonPress(ButtonEnum b);
        bool getButtonClick(ButtonEnum b);

        /**
         * Return the analog value from the joysticks on the controller.
         * @param  a          Either ::LeftHatX, ::LeftHatY, ::RightHatX or ::RightHatY.
         * @return            Returns a signed 16-bit integer.
         */
        int16_t getAnalogHat(AnalogHatEnum a);

        /**
         * Used to call your own function when the controller is successfully initialized.
         * @param funcOnInit Function to call.
         */
        void attachOnInit(void (*funcOnInit)(void)) {
                pFuncOnInit = funcOnInit;
        };
        /**@}*/

        /** True if a Xbox ONE controller is connected. */
        bool XboxOneConnected;

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
         */
        void onInit();
        void (*pFuncOnInit)(void); // Pointer to function called in onInit()

        bool bPollEnable;

        /* Variables to store the buttons */
        uint16_t ButtonState;
        uint16_t OldButtonState;
        uint16_t ButtonClickState;
        int16_t hatValue[4];
        uint16_t triggerValue[2];
        uint16_t triggerValueOld[2];

        bool L2Clicked; // These buttons are analog, so we use we use these bools to check if they where clicked or not
        bool R2Clicked;

        uint8_t readBuf[EP_MAXPKTSIZE]; // General purpose buffer for input data
        uint8_t writeBuf[12]; // General purpose buffer for output data

        void readReport(); // read incoming data
        void printReport(); // print incoming date - Uncomment for debugging

        /* Private commands */
        uint8_t XboxCommand(uint8_t* data, uint16_t nbytes);
};
#endif
