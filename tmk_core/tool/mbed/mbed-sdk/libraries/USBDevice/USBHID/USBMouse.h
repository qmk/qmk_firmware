/* Copyright (c) 2010-2011 mbed.org, MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef USBMOUSE_H
#define USBMOUSE_H

#include "USBHID.h"

#define REPORT_ID_MOUSE   2

/* Common usage */

enum MOUSE_BUTTON
{
    MOUSE_LEFT = 1,
    MOUSE_RIGHT = 2,
    MOUSE_MIDDLE = 4,
};

/* X and Y limits */
/* These values do not directly map to screen pixels */
/* Zero may be interpreted as meaning 'no movement' */
#define X_MIN_ABS    (1)        /*!< Minimum value on x-axis */
#define Y_MIN_ABS    (1)        /*!< Minimum value on y-axis */
#define X_MAX_ABS    (0x7fff)   /*!< Maximum value on x-axis */
#define Y_MAX_ABS    (0x7fff)   /*!< Maximum value on y-axis */

#define X_MIN_REL    (-127)     /*!< The maximum value that we can move to the left on the x-axis */
#define Y_MIN_REL    (-127)     /*!< The maximum value that we can move up on the y-axis */
#define X_MAX_REL    (127)      /*!< The maximum value that we can move to the right on the x-axis */
#define Y_MAX_REL    (127)      /*!< The maximum value that we can move down on the y-axis */

enum MOUSE_TYPE
{
    ABS_MOUSE,
    REL_MOUSE,
};

/**
 *
 * USBMouse example
 * @code
 * #include "mbed.h"
 * #include "USBMouse.h"
 *
 * USBMouse mouse;
 *
 * int main(void)
 * {
 *   while (1)
 *   {
 *      mouse.move(20, 0);
 *      wait(0.5);
 *   }
 * }
 *
 * @endcode
 *
 *
 * @code
 * #include "mbed.h"
 * #include "USBMouse.h"
 * #include <math.h>
 *
 * USBMouse mouse(ABS_MOUSE);
 *
 * int main(void)
 * {
 *   uint16_t x_center = (X_MAX_ABS - X_MIN_ABS)/2;
 *   uint16_t y_center = (Y_MAX_ABS - Y_MIN_ABS)/2;
 *   uint16_t x_screen = 0;
 *   uint16_t y_screen = 0;
 *
 *   uint32_t x_origin = x_center;
 *   uint32_t y_origin = y_center;
 *   uint32_t radius = 5000;
 *   uint32_t angle = 0;
 *
 *   while (1)
 *   {
 *       x_screen = x_origin + cos((double)angle*3.14/180.0)*radius;
 *       y_screen = y_origin + sin((double)angle*3.14/180.0)*radius;
 *
 *       mouse.move(x_screen, y_screen);
 *       angle += 3;
 *       wait(0.01);
 *   }
 * }
 *
 * @endcode
 */
class USBMouse: public USBHID
{
    public:

        /**
        *   Constructor
        *
        * @param mouse_type Mouse type: ABS_MOUSE (absolute mouse) or REL_MOUSE (relative mouse) (default: REL_MOUSE)
        * @param vendor_id Your vendor_id (default: 0x1234)
        * @param product_id Your product_id (default: 0x0001)
        * @param product_release Your preoduct_release (default: 0x0001)
        *
        */
        USBMouse(MOUSE_TYPE mouse_type = REL_MOUSE, uint16_t vendor_id = 0x1234, uint16_t product_id = 0x0001, uint16_t product_release = 0x0001):
            USBHID(0, 0, vendor_id, product_id, product_release, false)
            {
                button = 0;
                this->mouse_type = mouse_type;
                connect();
            };

        /**
        * Write a state of the mouse
        *
        * @param x x-axis position
        * @param y y-axis position
        * @param buttons buttons state (first bit represents MOUSE_LEFT, second bit MOUSE_RIGHT and third bit MOUSE_MIDDLE)
        * @param z wheel state (>0 to scroll down, <0 to scroll up)
        * @returns true if there is no error, false otherwise
        */
        bool update(int16_t x, int16_t y, uint8_t buttons, int8_t z);


        /**
        * Move the cursor to (x, y)
        *
        * @param x-axis position
        * @param y-axis position
        * @returns true if there is no error, false otherwise
        */
        bool move(int16_t x, int16_t y);

        /**
        * Press one or several buttons
        *
        * @param button button state (ex: press(MOUSE_LEFT))
        * @returns true if there is no error, false otherwise
        */
        bool press(uint8_t button);

        /**
        * Release one or several buttons
        *
        * @param button button state (ex: release(MOUSE_LEFT))
        * @returns true if there is no error, false otherwise
        */
        bool release(uint8_t button);

        /**
        * Double click (MOUSE_LEFT)
        *
        * @returns true if there is no error, false otherwise
        */
        bool doubleClick();

        /**
        * Click
        *
        * @param button state of the buttons ( ex: clic(MOUSE_LEFT))
        * @returns true if there is no error, false otherwise
        */
        bool click(uint8_t button);

        /**
        * Scrolling
        *
        * @param z value of the wheel (>0 to go down, <0 to go up)
        * @returns true if there is no error, false otherwise
        */
        bool scroll(int8_t z);

        /*
        * To define the report descriptor. Warning: this method has to store the length of the report descriptor in reportLength.
        *
        * @returns pointer to the report descriptor
        */
        virtual uint8_t * reportDesc();

    protected:
        /*
        * Get configuration descriptor
        *
        * @returns pointer to the configuration descriptor
        */
        virtual uint8_t * configurationDesc();

    private:
        MOUSE_TYPE mouse_type;
        uint8_t button;
        bool mouseSend(int8_t x, int8_t y, uint8_t buttons, int8_t z);
};

#endif
