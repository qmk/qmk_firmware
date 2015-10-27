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

#ifndef USBKEYBOARD_H
#define USBKEYBOARD_H

#include "USBHID.h"
#include "Stream.h"

/* Modifiers */
enum MODIFIER_KEY {
    KEY_CTRL = 1,
    KEY_SHIFT = 2,
    KEY_ALT = 4,
};


enum MEDIA_KEY {
    KEY_NEXT_TRACK,     /*!< next Track Button */
    KEY_PREVIOUS_TRACK, /*!< Previous track Button */
    KEY_STOP,           /*!< Stop Button */
    KEY_PLAY_PAUSE,     /*!< Play/Pause Button */
    KEY_MUTE,           /*!< Mute Button */
    KEY_VOLUME_UP,      /*!< Volume Up Button */
    KEY_VOLUME_DOWN,    /*!< Volume Down Button */
};

enum FUNCTION_KEY {
    KEY_F1 = 128,   /* F1 key */
    KEY_F2,         /* F2 key */
    KEY_F3,         /* F3 key */
    KEY_F4,         /* F4 key */
    KEY_F5,         /* F5 key */
    KEY_F6,         /* F6 key */
    KEY_F7,         /* F7 key */
    KEY_F8,         /* F8 key */
    KEY_F9,         /* F9 key */
    KEY_F10,        /* F10 key */
    KEY_F11,        /* F11 key */
    KEY_F12,        /* F12 key */

    KEY_PRINT_SCREEN,   /* Print Screen key */
    KEY_SCROLL_LOCK,    /* Scroll lock */
    KEY_CAPS_LOCK,      /* caps lock */
    KEY_NUM_LOCK,       /* num lock */
    KEY_INSERT,         /* Insert key */
    KEY_HOME,           /* Home key */
    KEY_PAGE_UP,        /* Page Up key */
    KEY_PAGE_DOWN,      /* Page Down key */

    RIGHT_ARROW,        /* Right arrow */
    LEFT_ARROW,         /* Left arrow */
    DOWN_ARROW,         /* Down arrow */
    UP_ARROW,           /* Up arrow */
};

/**
 * USBKeyboard example
 * @code
 *
 * #include "mbed.h"
 * #include "USBKeyboard.h"
 *
 * USBKeyboard key;
 *
 * int main(void)
 * {
 *   while (1)
 *   {
 *       key.printf("Hello World\r\n");
 *       wait(1);
 *   }
 * }
 *
 * @endcode
 */
class USBKeyboard: public USBHID, public Stream {
public:

    /**
    *   Constructor
    *
    *
    * @param leds Leds bus: first: NUM_LOCK, second: CAPS_LOCK, third: SCROLL_LOCK
    * @param vendor_id Your vendor_id (default: 0x1235)
    * @param product_id Your product_id (default: 0x0050)
    * @param product_release Your preoduct_release (default: 0x0001)
    *
    */
    USBKeyboard(uint16_t vendor_id = 0x1235, uint16_t product_id = 0x0050, uint16_t product_release = 0x0001):
            USBHID(0, 0, vendor_id, product_id, product_release, false) {
        lock_status = 0;
        connect();
    };

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

    /**
    * Read status of lock keys. Useful to switch-on/off leds according to key pressed. Only the first three bits of the result is important:
    *   - First bit: NUM_LOCK
    *   - Second bit: CAPS_LOCK
    *   - Third bit: SCROLL_LOCK
    *
    * @returns status of lock keys
    */
    uint8_t lockStatus();

protected:
    /*
    * Get configuration descriptor
    *
    * @returns pointer to the configuration descriptor
    */
    virtual uint8_t * configurationDesc();

private:
    //dummy otherwise it doesn,t compile (we must define all methods of an abstract class)
    virtual int _getc() {
        return -1;
    };

    uint8_t lock_status;

};

#endif
