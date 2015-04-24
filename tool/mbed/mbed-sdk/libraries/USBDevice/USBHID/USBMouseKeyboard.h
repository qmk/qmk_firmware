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

#ifndef USBMOUSEKEYBOARD_H
#define USBMOUSEKEYBOARD_H

#define REPORT_ID_KEYBOARD 1
#define REPORT_ID_MOUSE 2
#define REPORT_ID_VOLUME 3

#include "USBMouse.h"
#include "USBKeyboard.h"
#include "Stream.h"
#include "USBHID.h"

/**
 * USBMouseKeyboard example
 * @code
 *
 * #include "mbed.h"
 * #include "USBMouseKeyboard.h"
 *
 * USBMouseKeyboard key_mouse;
 *
 * int main(void)
 * {
 *   while(1)
 *   {
 *       key_mouse.move(20, 0);
 *       key_mouse.printf("Hello From MBED\r\n");
 *       wait(1);
 *   }
 * }
 * @endcode
 *
 *
 * @code
 *
 * #include "mbed.h"
 * #include "USBMouseKeyboard.h"
 *
 * USBMouseKeyboard key_mouse(ABS_MOUSE);
 *
 * int main(void)
 * {
 *   while(1)
 *   {
 *       key_mouse.move(X_MAX_ABS/2, Y_MAX_ABS/2);
 *       key_mouse.printf("Hello from MBED\r\n");
 *       wait(1);
 *   }
 * }
 * @endcode
 */
class USBMouseKeyboard: public USBHID, public Stream
{
    public:

        /**
        *   Constructor
        *
        * @param mouse_type Mouse type: ABS_MOUSE (absolute mouse) or REL_MOUSE (relative mouse) (default: REL_MOUSE)
        * @param leds Leds bus: first: NUM_LOCK, second: CAPS_LOCK, third: SCROLL_LOCK
        * @param vendor_id Your vendor_id (default: 0x1234)
        * @param product_id Your product_id (default: 0x0001)
        * @param product_release Your preoduct_release (default: 0x0001)
        *
        */
        USBMouseKeyboard(MOUSE_TYPE mouse_type = REL_MOUSE, uint16_t vendor_id = 0x0021, uint16_t product_id = 0x0011, uint16_t product_release = 0x0001):
            USBHID(0, 0, vendor_id, product_id, product_release, false)
            {
                lock_status = 0;
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
        * @param x x-axis position
        * @param y y-axis position
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

        /**
        * To send a character defined by a modifier(CTRL, SHIFT, ALT) and the key
        *
        * @code
        * //To send CTRL + s (save)
        *  keyboard.keyCode('s', KEY_CTRL);
        * @endcode
        *
        * @param modifier bit 0: KEY_CTRL, bit 1: KEY_SHIFT, bit 2: KEY_ALT (default: 0)
        * @param key character to send
        * @returns true if there is no error, false otherwise
        */
        bool keyCode(uint8_t key, uint8_t modifier = 0);

        /**
        * Send a character
        *
        * @param c character to be sent
        * @returns true if there is no error, false otherwise
        */
        virtual int _putc(int c);

        /**
        * Control media keys
        *
        * @param key media key pressed (KEY_NEXT_TRACK, KEY_PREVIOUS_TRACK, KEY_STOP, KEY_PLAY_PAUSE, KEY_MUTE, KEY_VOLUME_UP, KEY_VOLUME_DOWN)
        * @returns true if there is no error, false otherwise
        */
        bool mediaControl(MEDIA_KEY key);

        /**
        * Read status of lock keys. Useful to switch-on/off leds according to key pressed. Only the first three bits of the result is important:
        *   - First bit: NUM_LOCK
        *   - Second bit: CAPS_LOCK
        *   - Third bit: SCROLL_LOCK
        *
        * @returns status of lock keys
        */
        uint8_t lockStatus();

        /*
        * To define the report descriptor. Warning: this method has to store the length of the report descriptor in reportLength.
        *
        * @returns pointer to the report descriptor
        */
        virtual uint8_t * reportDesc();

        /*
        * Called when a data is received on the OUT endpoint. Useful to switch on LED of LOCK keys
        *
        * @returns if handle by subclass, return true
        */
        virtual bool EPINT_OUT_callback();


    private:
        bool mouseWrite(int8_t x, int8_t y, uint8_t buttons, int8_t z);
        MOUSE_TYPE mouse_type;
        uint8_t button;
        bool mouseSend(int8_t x, int8_t y, uint8_t buttons, int8_t z);

        uint8_t lock_status;

        //dummy otherwise it doesn't compile (we must define all methods of an abstract class)
        virtual int _getc() { return -1;}
};

#endif
