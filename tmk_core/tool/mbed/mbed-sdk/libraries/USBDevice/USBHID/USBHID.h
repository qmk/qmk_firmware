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

#ifndef USB_HID_H
#define USB_HID_H

/* These headers are included for child class. */
#include "USBEndpoints.h"
#include "USBDescriptor.h"
#include "USBDevice_Types.h"

#include "USBHID_Types.h"
#include "USBDevice.h"


/**
 * USBHID example
 * @code
 * #include "mbed.h"
 * #include "USBHID.h"
 *
 * USBHID hid;
 * HID_REPORT recv;
 * BusOut leds(LED1,LED2,LED3,LED4);
 *
 * int main(void) {
 *    while (1) {
 *        hid.read(&recv);
 *        leds = recv.data[0];
 *    }
 * }
 * @endcode
 */

class USBHID: public USBDevice {
public:

    /**
    * Constructor
    *
    * @param output_report_length Maximum length of a sent report (up to 64 bytes) (default: 64 bytes)
    * @param input_report_length Maximum length of a received report (up to 64 bytes) (default: 64 bytes)
    * @param vendor_id Your vendor_id
    * @param product_id Your product_id
    * @param product_release Your preoduct_release
    * @param connect Connect the device
    */
    USBHID(uint8_t output_report_length = 64, uint8_t input_report_length = 64, uint16_t vendor_id = 0x1234, uint16_t product_id = 0x0006, uint16_t product_release = 0x0001, bool connect = true);


    /**
    * Send a Report. warning: blocking
    *
    * @param report Report which will be sent (a report is defined by all data and the length)
    * @returns true if successful
    */
    bool send(HID_REPORT *report);


    /**
    * Send a Report. warning: non blocking
    *
    * @param report Report which will be sent (a report is defined by all data and the length)
    * @returns true if successful
    */
    bool sendNB(HID_REPORT *report);

    /**
    * Read a report: blocking
    *
    * @param report pointer to the report to fill
    * @returns true if successful
    */
    bool read(HID_REPORT * report);

    /**
    * Read a report: non blocking
    *
    * @param report pointer to the report to fill
    * @returns true if successful
    */
    bool readNB(HID_REPORT * report);

protected:
    uint16_t reportLength;

    /*
    * Get the Report descriptor
    *
    * @returns pointer to the report descriptor
    */
    virtual uint8_t * reportDesc();

    /*
    * Get the length of the report descriptor
    *
    * @returns the length of the report descriptor
    */
    virtual uint16_t reportDescLength();

    /*
    * Get string product descriptor
    *
    * @returns pointer to the string product descriptor
    */
    virtual uint8_t * stringIproductDesc();

    /*
    * Get string interface descriptor
    *
    * @returns pointer to the string interface descriptor
    */
    virtual uint8_t * stringIinterfaceDesc();

    /*
    * Get configuration descriptor
    *
    * @returns pointer to the configuration descriptor
    */
    virtual uint8_t * configurationDesc();


    /*
    * HID Report received by SET_REPORT request. Warning: Called in ISR context
    * First byte of data will be the report ID
    *
    * @param report Data and length received
    */
    virtual void HID_callbackSetReport(HID_REPORT *report){};


    /*
    * Called by USBDevice on Endpoint0 request. Warning: Called in ISR context
    * This is used to handle extensions to standard requests
    * and class specific requests
    *
    * @returns true if class handles this request
    */
    virtual bool USBCallback_request();


    /*
    * Called by USBDevice layer. Set configuration of the device.
    * For instance, you can add all endpoints that you need on this function.
    *
    * @param configuration Number of the configuration
    * @returns true if class handles this request
    */
    virtual bool USBCallback_setConfiguration(uint8_t configuration);

private:
    HID_REPORT outputReport;
    uint8_t output_length;
    uint8_t input_length;
};

#endif
