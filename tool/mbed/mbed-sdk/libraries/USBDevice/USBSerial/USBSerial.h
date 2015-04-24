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

#ifndef USBSERIAL_H
#define USBSERIAL_H

#include "USBCDC.h"
#include "Stream.h"
#include "CircBuffer.h"


/**
* USBSerial example
*
* @code
* #include "mbed.h"
* #include "USBSerial.h"
*
* //Virtual serial port over USB
* USBSerial serial;
*
* int main(void) {
*
*    while(1)
*    {
*        serial.printf("I am a virtual serial port\n");
*        wait(1);
*    }
* }
* @endcode
*/
class USBSerial: public USBCDC, public Stream {
public:

    /**
    *   Constructor
    *
    * @param vendor_id Your vendor_id (default: 0x1f00)
    * @param product_id Your product_id (default: 0x2012)
    * @param product_release Your preoduct_release (default: 0x0001)
    * @param connect_blocking define if the connection must be blocked if USB not plugged in
    *
    */
    USBSerial(uint16_t vendor_id = 0x1f00, uint16_t product_id = 0x2012, uint16_t product_release = 0x0001, bool connect_blocking = true): USBCDC(vendor_id, product_id, product_release, connect_blocking){
        settingsChangedCallback = 0;
    };


    /**
    * Send a character. You can use puts, printf.
    *
    * @param c character to be sent
    * @returns true if there is no error, false otherwise
    */
    virtual int _putc(int c);

    /**
    * Read a character: blocking
    *
    * @returns character read
    */
    virtual int _getc();

    /**
    * Check the number of bytes available.
    *
    * @returns the number of bytes available
    */
    uint8_t available();

    /** Determine if there is a character available to read
     *
     *  @returns
     *    1 if there is a character available to read,
     *    0 otherwise
     */
    int readable() { return available() ? 1 : 0; }

    /** Determine if there is space available to write a character
     *
     *  @returns
     *    1 if there is space to write a character,
     *    0 otherwise
     */
    int writeable() { return 1; } // always return 1, for write operation is blocking

    /**
    * Write a block of data.
    *
    * For more efficiency, a block of size 64 (maximum size of a bulk endpoint) has to be written.
    *
    * @param buf pointer on data which will be written
    * @param size size of the buffer. The maximum size of a block is limited by the size of the endpoint (64 bytes)
    *
    * @returns true if successfull
    */
    bool writeBlock(uint8_t * buf, uint16_t size);

    /**
     *  Attach a member function to call when a packet is received.
     *
     *  @param tptr pointer to the object to call the member function on
     *  @param mptr pointer to the member function to be called
     */
    template<typename T>
    void attach(T* tptr, void (T::*mptr)(void)) {
        if((mptr != NULL) && (tptr != NULL)) {
            rx.attach(tptr, mptr);
        }
    }

    /**
     * Attach a callback called when a packet is received
     *
     * @param fptr function pointer
     */
    void attach(void (*fptr)(void)) {
        if(fptr != NULL) {
            rx.attach(fptr);
        }
    }

    /**
     * Attach a callback to call when serial's settings are changed.
     *
     * @param fptr function pointer
     */
    void attach(void (*fptr)(int baud, int bits, int parity, int stop)) {
        settingsChangedCallback = fptr;
    }

protected:
    virtual bool EPBULK_OUT_callback();
    virtual void lineCodingChanged(int baud, int bits, int parity, int stop){
        if (settingsChangedCallback) {
            settingsChangedCallback(baud, bits, parity, stop);
        }
    }

private:
    FunctionPointer rx;
    CircBuffer<uint8_t,128> buf;
    void (*settingsChangedCallback)(int baud, int bits, int parity, int stop);
};

#endif
