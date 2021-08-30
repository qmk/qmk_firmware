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

#ifndef _controllerenums_h
#define _controllerenums_h

/**
 * This header file is used to store different enums for the controllers,
 * This is necessary so all the different libraries can be used at once.
 */

/** Enum used to turn on the LEDs on the different controllers. */
enum LEDEnum {
        OFF = 0,
        LED1 = 1,
        LED2 = 2,
        LED3 = 3,
        LED4 = 4,

        LED5 = 5,
        LED6 = 6,
        LED7 = 7,
        LED8 = 8,
        LED9 = 9,
        LED10 = 10,
        /** Used to blink all LEDs on the Xbox controller */
        ALL = 5,
};

/** Used to set the colors of the Move and PS4 controller. */
enum ColorsEnum {
        /** r = 255, g = 0, b = 0 */
        Red = 0xFF0000,
        /** r = 0, g = 255, b = 0 */
        Green = 0xFF00,
        /** r = 0, g = 0, b = 255 */
        Blue = 0xFF,

        /** r = 255, g = 235, b = 4 */
        Yellow = 0xFFEB04,
        /** r = 0, g = 255, b = 255 */
        Lightblue = 0xFFFF,
        /** r = 255, g = 0, b = 255 */
        Purble = 0xFF00FF,

        /** r = 255, g = 255, b = 255 */
        White = 0xFFFFFF,
        /** r = 0, g = 0, b = 0 */
        Off = 0x00,
};

enum RumbleEnum {
        RumbleHigh = 0x10,
        RumbleLow = 0x20,
};

/** This enum is used to read all the different buttons on the different controllers */
enum ButtonEnum {
        /**@{*/
        /** These buttons are available on all the the controllers */
        UP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3,
        /**@}*/

        /**@{*/
        /** Wii buttons */
        PLUS = 5,
        TWO = 6,
        ONE = 7,
        MINUS = 8,
        HOME = 9,
        Z = 10,
        C = 11,
        B = 12,
        A = 13,
        /**@}*/

        /**@{*/
        /** These are only available on the Wii U Pro Controller */
        L = 16,
        R = 17,
        ZL = 18,
        ZR = 19,
        /**@}*/

        /**@{*/
        /** PS3 controllers buttons */
        SELECT = 4,
        START = 5,
        L3 = 6,
        R3 = 7,

        L2 = 8,
        R2 = 9,
        L1 = 10,
        R1 = 11,
        TRIANGLE = 12,
        CIRCLE = 13,
        CROSS = 14,
        SQUARE = 15,

        PS = 16,

        MOVE = 17, // Covers 12 bits - we only need to read the top 8
        T = 18, // Covers 12 bits - we only need to read the top 8
        /**@}*/

        /** PS4 controllers buttons - SHARE and OPTIONS are present instead of SELECT and START */
        SHARE = 4,
        OPTIONS = 5,
        TOUCHPAD = 17,
        /**@}*/

        /**@{*/
        /** Xbox buttons */
        BACK = 4,
        X = 14,
        Y = 15,
        XBOX = 16,
        SYNC = 17,
        BLACK = 8, // Available on the original Xbox controller
        WHITE = 9, // Available on the original Xbox controller
        /**@}*/

        /** PS Buzz controllers */
        RED = 0,
        YELLOW = 1,
        GREEN = 2,
        ORANGE = 3,
        BLUE = 4,
        /**@}*/
};

/** Joysticks on the PS3 and Xbox controllers. */
enum AnalogHatEnum {
        /** Left joystick x-axis */
        LeftHatX = 0,
        /** Left joystick y-axis */
        LeftHatY = 1,
        /** Right joystick x-axis */
        RightHatX = 2,
        /** Right joystick y-axis */
        RightHatY = 3,
};

/**
 * Sensors inside the Sixaxis Dualshock 3, Move controller and PS4 controller.
 * <B>Note:</B> that the location is shifted 9 when it's connected via USB on the PS3 controller.
 */
enum SensorEnum {
        /** Accelerometer values */
        aX = 50, aY = 52, aZ = 54,
        /** Gyro z-axis */
        gZ = 56,
        gX, gY, // These are not available on the PS3 controller

        /** Accelerometer x-axis */
        aXmove = 28,
        /** Accelerometer z-axis */
        aZmove = 30,
        /** Accelerometer y-axis */
        aYmove = 32,

        /** Gyro x-axis */
        gXmove = 40,
        /** Gyro z-axis */
        gZmove = 42,
        /** Gyro y-axis */
        gYmove = 44,

        /** Temperature sensor */
        tempMove = 46,

        /** Magnetometer x-axis */
        mXmove = 47,
        /** Magnetometer z-axis */
        mZmove = 49,
        /** Magnetometer y-axis */
        mYmove = 50,
};

/** Used to get the angle calculated using the PS3 controller and PS4 controller. */
enum AngleEnum {
        Pitch = 0x01,
        Roll = 0x02,
};

#endif
