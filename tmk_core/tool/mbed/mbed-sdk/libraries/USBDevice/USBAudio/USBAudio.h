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

#ifndef USBAudio_H
#define USBAudio_H

/* These headers are included for child class. */
#include "USBEndpoints.h"
#include "USBDescriptor.h"
#include "USBDevice_Types.h"

#include "USBDevice.h"


/**
* USBAudio example
*
* @code
* #include "mbed.h"
* #include "USBAudio.h"
*
* Serial pc(USBTX, USBRX);
*
* // frequency: 48 kHz
* #define FREQ 48000
*
* // 1 channel: mono
* #define NB_CHA 1
*
* // length of an audio packet: each ms, we receive 48 * 16bits ->48 * 2 bytes. as there is one channel, the length will be 48 * 2 * 1
* #define AUDIO_LENGTH_PACKET 48 * 2 * 1
*
* // USBAudio
* USBAudio audio(FREQ, NB_CHA);
*
* int main() {
*    int16_t buf[AUDIO_LENGTH_PACKET/2];
*
*    while (1) {
*        // read an audio packet
*        audio.read((uint8_t *)buf);
*
*
*        // print packet received
*        pc.printf("recv: ");
*        for(int i = 0; i < AUDIO_LENGTH_PACKET/2; i++) {
*            pc.printf("%d ", buf[i]);
*        }
*        pc.printf("\r\n");
*    }
* }
* @endcode
*/
class USBAudio: public USBDevice {
public:

    /**
    * Constructor
    *
    * @param frequency_in frequency in Hz (default: 48000)
    * @param channel_nb_in channel number (1 or 2) (default: 1)
    * @param frequency_out frequency in Hz (default: 8000)
    * @param channel_nb_out_in channel number (1 or 2) (default: 1)
    * @param vendor_id Your vendor_id
    * @param product_id Your product_id
    * @param product_release Your preoduct_release
    */
    USBAudio(uint32_t frequency_in = 48000, uint8_t channel_nb_in = 1, uint32_t frequency_out = 8000, uint8_t channel_nb_out = 1, uint16_t vendor_id = 0x7bb8, uint16_t product_id = 0x1111, uint16_t product_release = 0x0100);

    /**
    * Get current volume between 0.0 and 1.0
    *
    * @returns volume
    */
    float getVolume();

    /**
    * Read an audio packet. During a frame, only a single reading (you can't write and read an audio packet during the same frame)can be done using this method. Warning: Blocking
    *
    * @param buf pointer on a buffer which will be filled with an audio packet
    *
    * @returns true if successfull
    */
    bool read(uint8_t * buf);

    /**
    * Try to read an audio packet. During a frame, only a single reading (you can't write and read an audio packet during the same frame)can be done using this method. Warning: Non Blocking
    *
    * @param buf pointer on a buffer which will be filled if an audio packet is available
    *
    * @returns true if successfull
    */
    bool readNB(uint8_t * buf);

    /**
    * Write an audio packet. During a frame, only a single writing (you can't write and read an audio packet during the same frame)can be done using this method.
    *
    * @param buf pointer on the audio packet which will be sent
    * @returns true if successful
    */
    bool write(uint8_t * buf);

    /**
    * Write and read an audio packet at the same time (on the same frame)
    *
    * @param buf_read pointer on a buffer which will be filled with an audio packet
    * @param buf_write pointer on the audio packet which will be sent
    * @returns true if successful
    */
    bool readWrite(uint8_t * buf_read, uint8_t * buf_write);


    /** attach a handler to update the volume
     *
     * @param function Function to attach
     *
     */
    void attach(void(*fptr)(void)) {
        updateVol.attach(fptr);
    }

    /** Attach a nonstatic void/void member function to update the volume
     *
     * @param tptr Object pointer
     * @param mptr Member function pointer
     *
     */
    template<typename T>
    void attach(T *tptr, void(T::*mptr)(void)) {
        updateVol.attach(tptr, mptr);
    }


protected:

    /*
    * Called by USBDevice layer. Set configuration of the device.
    * For instance, you can add all endpoints that you need on this function.
    *
    * @param configuration Number of the configuration
    * @returns true if class handles this request
    */
    virtual bool USBCallback_setConfiguration(uint8_t configuration);

    /*
    * Called by USBDevice on Endpoint0 request. Warning: Called in ISR context
    * This is used to handle extensions to standard requests
    * and class specific requests
    *
    * @returns true if class handles this request
    */
    virtual bool USBCallback_request();

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
     * Called by USBDevice layer. Set interface/alternate of the device.
     *
     * @param interface Number of the interface to be configured
     * @param alternate Number of the alternate to be configured
     * @returns true if class handles this request
     */
    virtual bool USBCallback_setInterface(uint16_t interface, uint8_t alternate);

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
    virtual void USBCallback_requestCompleted(uint8_t * buf, uint32_t length);

    /*
    * Callback called on each Start of Frame event
    */
    virtual void SOF(int frameNumber);

    /*
    * Callback called when a packet is received
    */
    virtual bool EPISO_OUT_callback();

    /*
    * Callback called when a packet has been sent
    */
    virtual bool EPISO_IN_callback();

private:

    // stream available ?
    volatile bool available;

    // interrupt OUT has been received
    volatile bool interruptOUT;

    // interrupt IN has been received
    volatile bool interruptIN;

    // audio packet has been written
    volatile bool writeIN;

    // FREQ
    uint32_t FREQ_OUT;
    uint32_t FREQ_IN;

    // size of the maximum packet for the isochronous endpoint
    uint32_t PACKET_SIZE_ISO_IN;
    uint32_t PACKET_SIZE_ISO_OUT;

    // mono, stereo,...
    uint8_t channel_nb_in;
    uint8_t channel_nb_out;

    // channel config: master, left, right
    uint8_t channel_config_in;
    uint8_t channel_config_out;

    // mute state
    uint8_t mute;

    // Volume Current Value
    uint16_t volCur;

    // Volume Minimum Value
    uint16_t volMin;

    // Volume Maximum Value
    uint16_t volMax;

    // Volume Resolution
    uint16_t volRes;

    // Buffer containing one audio packet (to be read)
    volatile uint8_t * buf_stream_in;

    // Buffer containing one audio packet (to be written)
    volatile uint8_t * buf_stream_out;

    // callback to update volume
    FunctionPointer updateVol;

    // boolean showing that the SOF handler has been called. Useful for readNB.
    volatile bool SOF_handler;

    volatile float volume;

};

#endif
