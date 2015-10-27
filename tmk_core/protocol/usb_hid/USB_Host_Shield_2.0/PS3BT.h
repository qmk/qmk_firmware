/* Copyright (C) 2012 Kristian Lauszus, TKJ Electronics. All rights reserved.

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

#ifndef _ps3bt_h_
#define _ps3bt_h_

#include "BTD.h"
#include "PS3Enums.h"

#define HID_BUFFERSIZE 50 // Size of the buffer for the Playstation Motion Controller

/**
 * This BluetoothService class implements support for all the official PS3 Controllers:
 * Dualshock 3, Navigation or a Motion controller via Bluetooth.
 *
 * Information about the protocol can be found at the wiki: https://github.com/felis/USB_Host_Shield_2.0/wiki/PS3-Information.
 */
class PS3BT : public BluetoothService {
public:
        /**
         * Constructor for the PS3BT class.
         * @param  pBtd   Pointer to BTD class instance.
         * @param  btadr5,btadr4,btadr3,btadr2,btadr1,btadr0
         * Pass your dongles Bluetooth address into the constructor,
         * This will set BTD#my_bdaddr, so you don't have to plug in the dongle before pairing with your controller.
         */
        PS3BT(BTD *pBtd, uint8_t btadr5 = 0, uint8_t btadr4 = 0, uint8_t btadr3 = 0, uint8_t btadr2 = 0, uint8_t btadr1 = 0, uint8_t btadr0 = 0);

        /** @name BluetoothService implementation */
        /** Used this to disconnect any of the controllers. */
        void disconnect();
        /**@}*/

        /** @name PS3 Controller functions */
        /**
         * getButtonPress(ButtonEnum b) will return true as long as the button is held down.
         *
         * While getButtonClick(ButtonEnum b) will only return it once.
         *
         * So you instance if you need to increase a variable once you would use getButtonClick(ButtonEnum b),
         * but if you need to drive a robot forward you would use getButtonPress(ButtonEnum b).
         * @param  b          ::ButtonEnum to read.
         * @return            getButtonPress(ButtonEnum b) will return a true as long as a button is held down, while getButtonClick(ButtonEnum b) will return true once for each button press.
         */
        bool getButtonPress(ButtonEnum b);
        bool getButtonClick(ButtonEnum b);
        /**@}*/
        /** @name PS3 Controller functions */
        /**
         * Used to get the analog value from button presses.
         * @param  a The ::ButtonEnum to read.
         * The supported buttons are:
         * ::UP, ::RIGHT, ::DOWN, ::LEFT, ::L1, ::L2, ::R1, ::R2,
         * ::TRIANGLE, ::CIRCLE, ::CROSS, ::SQUARE, and ::T.
         * @return   Analog value in the range of 0-255.
         */
        uint8_t getAnalogButton(ButtonEnum a);
        /**
         * Used to read the analog joystick.
         * @param  a ::LeftHatX, ::LeftHatY, ::RightHatX, and ::RightHatY.
         * @return   Return the analog value in the range of 0-255.
         */
        uint8_t getAnalogHat(AnalogHatEnum a);
        /**
         * Used to read the sensors inside the Dualshock 3 and Move controller.
         * @param  a
         * The Dualshock 3 has a 3-axis accelerometer and a 1-axis gyro inside.
         * The Move controller has a 3-axis accelerometer, a 3-axis gyro, a 3-axis magnetometer
         * and a temperature sensor inside.
         * @return   Return the raw sensor value.
         */
        int16_t getSensor(SensorEnum a);
        /**
         * Use this to get ::Pitch and ::Roll calculated using the accelerometer.
         * @param  a Either ::Pitch or ::Roll.
         * @return   Return the angle in the range of 0-360.
         */
        double getAngle(AngleEnum a);
        /**
         * Read the sensors inside the Move controller.
         * @param  a ::aXmove, ::aYmove, ::aZmove, ::gXmove, ::gYmove, ::gZmove, ::mXmove, ::mYmove, and ::mXmove.
         * @return   The value in SI units.
         */
        double get9DOFValues(SensorEnum a);
        /**
         * Get the status from the controller.
         * @param  c The ::StatusEnum you want to read.
         * @return   True if correct and false if not.
         */
        bool getStatus(StatusEnum c);
        /** Read all the available statuses from the controller and prints it as a nice formated string. */
        void printStatusString();
        /**
         * Read the temperature from the Move controller.
         * @return The temperature in degrees Celsius.
         */
        String getTemperature();

        /** Used to set all LEDs and rumble off. */
        void setAllOff();
        /** Turn off rumble. */
        void setRumbleOff();
        /**
         * Turn on rumble.
         * @param mode Either ::RumbleHigh or ::RumbleLow.
         */
        void setRumbleOn(RumbleEnum mode);
        /**
         * Turn on rumble using custom duration and power.
         * @param rightDuration The duration of the right/low rumble effect.
         * @param rightPower The intensity of the right/low rumble effect.
         * @param leftDuration The duration of the left/high rumble effect.
         * @param leftPower The intensity of the left/high rumble effect.
         */
        void setRumbleOn(uint8_t rightDuration, uint8_t rightPower, uint8_t leftDuration, uint8_t leftPower);

        /**
         * Set LED value without using ::LEDEnum.
         * @param value See: ::LEDEnum.
         */
        void setLedRaw(uint8_t value);

        /** Turn all LEDs off. */
        void setLedOff() {
                setLedRaw(0);
        };
        /**
         * Turn the specific LED off.
         * @param a The ::LEDEnum to turn off.
         */
        void setLedOff(LEDEnum a);
        /**
         * Turn the specific LED on.
         * @param a The ::LEDEnum to turn on.
         */
        void setLedOn(LEDEnum a);
        /**
         * Toggle the specific LED.
         * @param a The ::LEDEnum to toggle.
         */
        void setLedToggle(LEDEnum a);

        /**
         * Use this to set the Color using RGB values.
         * @param r,g,b RGB value.
         */
        void moveSetBulb(uint8_t r, uint8_t g, uint8_t b);
        /**
         * Use this to set the color using the predefined colors in ::ColorsEnum.
         * @param color The desired color.
         */
        void moveSetBulb(ColorsEnum color);
        /**
         * Set the rumble value inside the Move controller.
         * @param rumble The desired value in the range from 64-255.
         */
        void moveSetRumble(uint8_t rumble);

        /** Used to get the millis() of the last message */
        uint32_t getLastMessageTime() {
                return lastMessageTime;
        };
        /**@}*/

        /** Variable used to indicate if the normal Playstation controller is successfully connected. */
        bool PS3Connected;
        /** Variable used to indicate if the Move controller is successfully connected. */
        bool PS3MoveConnected;
        /** Variable used to indicate if the Navigation controller is successfully connected. */
        bool PS3NavigationConnected;

protected:
        /** @name BluetoothService implementation */
        /**
         * Used to pass acldata to the services.
         * @param ACLData Incoming acldata.
         */
        void ACLData(uint8_t* ACLData);
        /** Used to run part of the state machine. */
        void Run();
        /** Use this to reset the service. */
        void Reset();
        /**
         * Called when the controller is successfully initialized.
         * Use attachOnInit(void (*funcOnInit)(void)) to call your own function.
         * This is useful for instance if you want to set the LEDs in a specific way.
         */
        void onInit();
        /**@}*/

private:

        void L2CAP_task(); // L2CAP state machine

        /* Variables filled from HCI event management */
        char remote_name_first; // First letter in remote name
        bool activeConnection; // Used to indicate if it's already has established a connection

        /* Variables used by high level L2CAP task */
        uint8_t l2cap_state;

        uint32_t lastMessageTime; // Variable used to store the millis value of the last message.

        uint32_t ButtonState;
        uint32_t OldButtonState;
        uint32_t ButtonClickState;

        uint32_t timer; // Timer used to limit time between messages and also used to continuously set PS3 Move controller Bulb and rumble values
        uint32_t timerHID; // Timer used see if there has to be a delay before a new HID command

        uint8_t l2capinbuf[BULK_MAXPKTSIZE]; // General purpose buffer for L2CAP in data
        uint8_t HIDBuffer[HID_BUFFERSIZE]; // Used to store HID commands
        uint8_t HIDMoveBuffer[HID_BUFFERSIZE]; // Used to store HID commands for the Move controller

        /* L2CAP Channels */
        uint8_t control_scid[2]; // L2CAP source CID for HID_Control
        uint8_t control_dcid[2]; // 0x0040
        uint8_t interrupt_scid[2]; // L2CAP source CID for HID_Interrupt
        uint8_t interrupt_dcid[2]; // 0x0041

        /* HID Commands */
        void HID_Command(uint8_t* data, uint8_t nbytes);
        void HIDMove_Command(uint8_t* data, uint8_t nbytes);
        void enable_sixaxis(); // Command used to enable the Dualshock 3 and Navigation controller to send data via Bluetooth
};
#endif
