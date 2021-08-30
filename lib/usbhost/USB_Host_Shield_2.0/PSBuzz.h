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

#ifndef _psbuzz_h_
#define _psbuzz_h_

#include "hiduniversal.h"
#include "controllerEnums.h"

#define PSBUZZ_VID 0x054C // Sony Corporation
#define PSBUZZ_PID 0x1000 // PS Buzz Controller

/** Struct used to easily read the different buttons on the controllers */
union PSBUZZButtons {
        struct {
                uint8_t red : 1;
                uint8_t yellow : 1;
                uint8_t green : 1;
                uint8_t orange : 1;
                uint8_t blue : 1;
        } __attribute__((packed)) btn[4];
        uint32_t val : 20;
} __attribute__((packed));

/**
 * This class implements support for the PS Buzz controllers via USB.
 * It uses the HIDUniversal class for all the USB communication.
 */
class PSBuzz : public HIDUniversal {
public:
        /**
         * Constructor for the PSBuzz class.
         * @param  p   Pointer to the USB class instance.
         */
        PSBuzz(USB *p) :
        HIDUniversal(p) {
                Reset();
        };

        /**
         * Used to check if a PS Buzz controller is connected.
         * @return Returns true if it is connected.
         */
        bool connected() {
                return HIDUniversal::isReady() && HIDUniversal::VID == PSBUZZ_VID && HIDUniversal::PID == PSBUZZ_PID;
        };

        /**
         * Used to call your own function when the device is successfully initialized.
         * @param funcOnInit Function to call.
         */
        void attachOnInit(void (*funcOnInit)(void)) {
                pFuncOnInit = funcOnInit;
        };

        /** @name PS Buzzer Controller functions */
        /**
         * getButtonPress(ButtonEnum b) will return true as long as the button is held down.
         *
         * While getButtonClick(ButtonEnum b) will only return it once.
         *
         * So you instance if you need to increase a variable once you would use getButtonClick(ButtonEnum b),
         * but if you need to drive a robot forward you would use getButtonPress(ButtonEnum b).
         * @param  b          ::ButtonEnum to read.
         * @param  controller The controller to read from. Default to 0.
         * @return            getButtonPress(ButtonEnum b) will return a true as long as a button is held down, while getButtonClick(ButtonEnum b) will return true once for each button press.
         */
        bool getButtonPress(ButtonEnum b, uint8_t controller = 0);
        bool getButtonClick(ButtonEnum b, uint8_t controller = 0);
        /**@}*/
        /** @name PS Buzzer Controller functions */
        /**
         * Set LED value without using ::LEDEnum.
         * @param value See: ::LEDEnum.
         */
        /**
         * Set LED values directly.
         * @param value      Used to set whenever the LED should be on or off
         * @param controller The controller to control. Defaults to 0.
         */
        void setLedRaw(bool value, uint8_t controller = 0);

        /** Turn all LEDs off. */
        void setLedOffAll() {
                for (uint8_t i = 1; i < 4; i++) // Skip first as it will be set in setLedRaw
                        ledState[i] = false; // Just an easy way to set all four off at the same time
                setLedRaw(false); // Turn the LED off, on all four controllers
        };

        /**
         * Turn the LED off on a specific controller.
         * @param controller The controller to turn off. Defaults to 0.
         */
        void setLedOff(uint8_t controller = 0) {
                setLedRaw(false, controller);
        };


        /** Turn all LEDs on. */
        void setLedOnAll() {
                for (uint8_t i = 1; i < 4; i++) // Skip first as it will be set in setLedRaw
                        ledState[i] = true; // Just an easy way to set all four off at the same time
                setLedRaw(true); // Turn the LED on, on all four controllers
        };

        /**
         * Turn the LED on on a specific controller.
         * @param controller The controller to turn off. Defaults to 0.
         */
        void setLedOn(uint8_t controller = 0) {
                setLedRaw(true, controller);
        };

        /**
         * Toggle the LED on a specific controller.
         * @param controller The controller to turn off. Defaults to 0.
         */
        void setLedToggle(uint8_t controller = 0) {
                setLedRaw(!ledState[controller], controller);
        };
        /**@}*/

protected:
        /** @name HIDUniversal implementation */
        /**
         * Used to parse USB HID data.
         * @param hid       Pointer to the HID class.
         * @param is_rpt_id Only used for Hubs.
         * @param len       The length of the incoming data.
         * @param buf       Pointer to the data buffer.
         */
        void ParseHIDData(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);

        /**
         * Called when a device is successfully initialized.
         * Use attachOnInit(void (*funcOnInit)(void)) to call your own function.
         * This is useful for instance if you want to set the LEDs in a specific way.
         */
        uint8_t OnInitSuccessful();
        /**@}*/

        /** Used to reset the different buffers to their default values */
        void Reset() {
                psbuzzButtons.val = 0;
                oldButtonState.val = 0;
                buttonClickState.val = 0;
                for (uint8_t i = 0; i < sizeof(ledState); i++)
                        ledState[i] = 0;
        };

        /** @name USBDeviceConfig implementation */
        /**
         * Used by the USB core to check what this driver support.
         * @param  vid The device's VID.
         * @param  pid The device's PID.
         * @return     Returns true if the device's VID and PID matches this driver.
         */
        virtual bool VIDPIDOK(uint16_t vid, uint16_t pid) {
                return (vid == PSBUZZ_VID && pid == PSBUZZ_PID);
        };
        /**@}*/

private:
        void (*pFuncOnInit)(void); // Pointer to function called in onInit()

        void PSBuzz_Command(uint8_t *data, uint16_t nbytes);

        PSBUZZButtons psbuzzButtons, oldButtonState, buttonClickState;
        bool ledState[4];
};
#endif
