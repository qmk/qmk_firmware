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

#ifndef USBDEVICE_H
#define USBDEVICE_H

#include "mbed.h"
#include "USBDevice_Types.h"
#include "USBHAL.h"

class USBDevice: public USBHAL
{
public:
    USBDevice(uint16_t vendor_id, uint16_t product_id, uint16_t product_release);

    /*
    * Check if the device is configured
    *
    * @returns true if configured, false otherwise
    */
    bool configured(void);

    /*
    * Connect a device
    *
    * @param blocking: block if not configured
    */
    void connect(bool blocking = true);

    /*
    * Disconnect a device
    */
    void disconnect(void);

    /*
    * Add an endpoint
    *
    * @param endpoint endpoint which will be added
    * @param maxPacket Maximum size of a packet which can be sent for this endpoint
    * @returns true if successful, false otherwise
    */
    bool addEndpoint(uint8_t endpoint, uint32_t maxPacket);

    /*
    * Start a reading on a certain endpoint.
    * You can access the result of the reading by USBDevice_read
    *
    * @param endpoint endpoint which will be read
    * @param maxSize the maximum length that can be read
    * @return true if successful
    */
    bool readStart(uint8_t endpoint, uint32_t maxSize);

    /*
    * Read a certain endpoint. Before calling this function, USBUSBDevice_readStart
    * must be called.
    *
    * Warning: blocking
    *
    * @param endpoint endpoint which will be read
    * @param buffer buffer will be filled with the data received
    * @param size the number of bytes read will be stored in *size
    * @param maxSize the maximum length that can be read
    * @returns true if successful
    */
    bool readEP(uint8_t endpoint, uint8_t * buffer, uint32_t * size, uint32_t maxSize);

    /*
    * Read a certain endpoint.
    *
    * Warning: non blocking
    *
    * @param endpoint endpoint which will be read
    * @param buffer buffer will be filled with the data received (if data are available)
    * @param size the number of bytes read will be stored in *size
    * @param maxSize the maximum length that can be read
    * @returns true if successful
    */
    bool readEP_NB(uint8_t endpoint, uint8_t * buffer, uint32_t * size, uint32_t maxSize);

    /*
    * Write a certain endpoint.
    *
    * Warning: blocking
    *
    * @param endpoint endpoint to write
    * @param buffer data contained in buffer will be write
    * @param size the number of bytes to write
    * @param maxSize the maximum length that can be written on this endpoint
    */
    bool write(uint8_t endpoint, uint8_t * buffer, uint32_t size, uint32_t maxSize);


    /*
    * Write a certain endpoint.
    *
    * Warning: non blocking
    *
    * @param endpoint endpoint to write
    * @param buffer data contained in buffer will be write
    * @param size the number of bytes to write
    * @param maxSize the maximum length that can be written on this endpoint
    */
    bool writeNB(uint8_t endpoint, uint8_t * buffer, uint32_t size, uint32_t maxSize);


    /*
    * Called by USBDevice layer on bus reset. Warning: Called in ISR context
    *
    * May be used to reset state
    */
    virtual void USBCallback_busReset(void) {};

    /*
    * Called by USBDevice on Endpoint0 request. Warning: Called in ISR context
    * This is used to handle extensions to standard requests
    * and class specific requests
    *
    * @returns true if class handles this request
    */
    virtual bool USBCallback_request() { return false; };

    /*
    * Called by USBDevice on Endpoint0 request completion
    * if the 'notify' flag has been set to true. Warning: Called in ISR context
    *
    * In this case it is used to indicate that a HID report has
    * been received from the host on endpoint 0
    *
    * @param buf buffer received on endpoint 0
    * @param length length of this buffer
    */
    virtual void USBCallback_requestCompleted(uint8_t * buf, uint32_t length) {};

    /*
    * Called by USBDevice layer. Set configuration of the device.
    * For instance, you can add all endpoints that you need on this function.
    *
    * @param configuration Number of the configuration
    */
    virtual bool USBCallback_setConfiguration(uint8_t configuration) { return false; };

    /*
     * Called by USBDevice layer. Set interface/alternate of the device.
     *
     * @param interface Number of the interface to be configured
     * @param alternate Number of the alternate to be configured
     * @returns true if class handles this request
     */
    virtual bool USBCallback_setInterface(uint16_t interface, uint8_t alternate) { return false; };

    /*
    * Get device descriptor. Warning: this method has to store the length of the report descriptor in reportLength.
    *
    * @returns pointer to the device descriptor
    */
    virtual uint8_t * deviceDesc();

    /*
    * Get configuration descriptor
    *
    * @returns pointer to the configuration descriptor
    */
    virtual uint8_t * configurationDesc(){return NULL;};

    /*
    * Get string lang id descriptor
    *
    * @return pointer to the string lang id descriptor
    */
    virtual uint8_t * stringLangidDesc();

    /*
    * Get string manufacturer descriptor
    *
    * @returns pointer to the string manufacturer descriptor
    */
    virtual uint8_t * stringImanufacturerDesc();

    /*
    * Get string product descriptor
    *
    * @returns pointer to the string product descriptor
    */
    virtual uint8_t * stringIproductDesc();

    /*
    * Get string serial descriptor
    *
    * @returns pointer to the string serial descriptor
    */
    virtual uint8_t * stringIserialDesc();

    /*
    * Get string configuration descriptor
    *
    * @returns pointer to the string configuration descriptor
    */
    virtual uint8_t * stringIConfigurationDesc();

    /*
    * Get string interface descriptor
    *
    * @returns pointer to the string interface descriptor
    */
    virtual uint8_t * stringIinterfaceDesc();

    /*
    * Get the length of the report descriptor
    *
    * @returns length of the report descriptor
    */
    virtual uint16_t reportDescLength() { return 0; };



protected:
    virtual void busReset(void);
    virtual void EP0setupCallback(void);
    virtual void EP0out(void);
    virtual void EP0in(void);
    virtual void connectStateChanged(unsigned int connected);
    virtual void suspendStateChanged(unsigned int suspended);
    uint8_t * findDescriptor(uint8_t descriptorType);
    CONTROL_TRANSFER * getTransferPtr(void);

    uint16_t VENDOR_ID;
    uint16_t PRODUCT_ID;
    uint16_t PRODUCT_RELEASE;

private:
    bool addRateFeedbackEndpoint(uint8_t endpoint, uint32_t maxPacket);
    bool requestGetDescriptor(void);
    bool controlOut(void);
    bool controlIn(void);
    bool requestSetAddress(void);
    bool requestSetConfiguration(void);
    bool requestSetFeature(void);
    bool requestClearFeature(void);
    bool requestGetStatus(void);
    bool requestSetup(void);
    bool controlSetup(void);
    void decodeSetupPacket(uint8_t *data, SETUP_PACKET *packet);
    bool requestGetConfiguration(void);
    bool requestGetInterface(void);
    bool requestSetInterface(void);

    CONTROL_TRANSFER transfer;
    USB_DEVICE device;

    uint16_t currentInterface;
    uint8_t currentAlternate;
};


#endif
