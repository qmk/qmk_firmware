/* Copyright (c) 2014 mbed.org, MIT License
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

#ifndef USBHOSTMIDI_H
#define USBHOSTMIDI_H

#include "USBHostConf.h"

#if USBHOST_MIDI

#include "USBHost.h"

/** 
 * A class to communicate a USB MIDI device
 */
class USBHostMIDI : public IUSBEnumerator {
public:
    /**
     * Constructor
     */
    USBHostMIDI();

    /**
     * Check if a USB MIDI device is connected
     *
     * @returns true if a midi device is connected
     */
    bool connected();
    
    /**
     * Try to connect a midi device
     *
     * @return true if connection was successful
     */
    bool connect();
    
    /**
     * Attach a callback called when miscellaneous function code is received
     *
     * @param ptr function pointer
     *   prototype: void onMiscellaneousFunctionCode(uint8_t data1, uint8_t data2, uint8_t data3);
     */
    inline void attachMiscellaneousFunctionCode(void (*fn)(uint8_t, uint8_t, uint8_t)) {
        miscellaneousFunctionCode = fn;
    }

    /**
     * Attach a callback called when cable event is received
     *
     * @param ptr function pointer
     *   prototype: void onCableEvent(uint8_t data1, uint8_t data2, uint8_t data3);
     */
    inline void attachCableEvent(void (*fn)(uint8_t, uint8_t, uint8_t)) {
        cableEvent = fn;
    }

    /**
     * Attach a callback called when system exclusive is received
     *
     * @param ptr function pointer
     *   prototype: void onSystemCommonTwoBytes(uint8_t data1, uint8_t data2);
     */
    inline void attachSystemCommonTwoBytes(void (*fn)(uint8_t, uint8_t)) {
        systemCommonTwoBytes = fn;
    }
    
    /**
     * Attach a callback called when system exclusive is received
     *
     * @param ptr function pointer
     *   prototype: void onSystemCommonThreeBytes(uint8_t data1, uint8_t data2, uint8_t data3);
     */
    inline void attachSystemCommonThreeBytes(void (*fn)(uint8_t, uint8_t, uint8_t)) {
        systemCommonThreeBytes = fn;
    }
    
    /**
     * Attach a callback called when system exclusive is received
     *
     * @param ptr function pointer
     *   prototype: void onSystemExclusive(uint8_t *data, uint16_t length, bool hasNextData);
     */
    inline void attachSystemExclusive(void (*fn)(uint8_t *, uint16_t, bool)) {
        systemExclusive = fn;
    }

    /**
     * Attach a callback called when note on is received
     *
     * @param ptr function pointer
     *   prototype: void onNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
     */
    inline void attachNoteOn(void (*fn)(uint8_t, uint8_t, uint8_t)) {
        noteOn = fn;
    }

    /**
     * Attach a callback called when note off is received
     *
     * @param ptr function pointer
     *   prototype: void onNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
     */
    inline void attachNoteOff(void (*fn)(uint8_t, uint8_t, uint8_t)) {
        noteOff = fn;
    }

    /**
     * Attach a callback called when poly keypress is received
     *
     * @param ptr function pointer
     *   prototype: void onPolyKeyPress(uint8_t channel, uint8_t note, uint8_t pressure);
     */
    inline void attachPolyKeyPress(void (*fn)(uint8_t, uint8_t, uint8_t)) {
        polyKeyPress = fn;
    }

    /**
     * Attach a callback called when control change is received
     *
     * @param ptr function pointer
     *   prototype: void onControlChange(uint8_t channel, uint8_t key, uint8_t value);
     */
    inline void attachControlChange(void (*fn)(uint8_t, uint8_t, uint8_t)) {
        controlChange = fn;
    }

    /**
     * Attach a callback called when program change is received
     *
     * @param ptr function pointer
     *   prototype: void onProgramChange(uint8_t channel, uint8_t program);
     */
    inline void attachProgramChange(void (*fn)(uint8_t, uint8_t)) {
        programChange = fn;
    }

    /**
     * Attach a callback called when channel pressure is received
     *
     * @param ptr function pointer
     *   prototype: void onChannelPressure(uint8_t channel, uint8_t pressure);
     */
    inline void attachChannelPressure(void (*fn)(uint8_t, uint8_t)) {
        channelPressure = fn;
    }

    /**
     * Attach a callback called when pitch bend is received
     *
     * @param ptr function pointer
     *   prototype: void onPitchBend(uint8_t channel, uint16_t value);
     */
    inline void attachPitchBend(void (*fn)(uint8_t, uint16_t)) {
        pitchBend = fn;
    }

    /**
     * Attach a callback called when single byte is received
     *
     * @param ptr function pointer
     *   prototype: void onSingleByte(uint8_t value);
     */
    inline void attachSingleByte(void (*fn)(uint8_t)) {
        singleByte = fn;
    }

    /**
     * Send a cable event with 3 bytes event
     *
     * @param data1 0-255
     * @param data2 0-255
     * @param data3 0-255
     * @return true if message sent successfully
     */
    bool sendMiscellaneousFunctionCode(uint8_t data1, uint8_t data2, uint8_t data3);

    /**
     * Send a cable event with 3 bytes event
     *
     * @param data1 0-255
     * @param data2 0-255
     * @param data3 0-255
     * @return true if message sent successfully
     */
    bool sendCableEvent(uint8_t data1, uint8_t data2, uint8_t data3);

    /**
     * Send a system common message with 2 bytes event
     *
     * @param data1 0-255
     * @param data2 0-255
     * @return true if message sent successfully
     */
    bool sendSystemCommmonTwoBytes(uint8_t data1, uint8_t data2);

    /**
     * Send a system common message with 3 bytes event
     *
     * @param data1 0-255
     * @param data2 0-255
     * @param data3 0-255
     * @return true if message sent successfully
     */
    bool sendSystemCommmonThreeBytes(uint8_t data1, uint8_t data2, uint8_t data3);

    /**
     * Send a system exclusive event
     *
     * @param buffer, starts with 0xF0, and end with 0xf7
     * @param length
     * @return true if message sent successfully
     */
    bool sendSystemExclusive(uint8_t *buffer, int length);

    /**
     * Send a note off event
     *
     * @param channel 0-15
     * @param note 0-127
     * @param velocity 0-127
     * @return true if message sent successfully
     */
    bool sendNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);

    /**
     * Send a note on event
     *
     * @param channel 0-15
     * @param note 0-127
     * @param velocity 0-127 (0 means note off)
     * @return true if message sent successfully
     */
    bool sendNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);

    /**
     * Send a poly keypress event
     *
     * @param channel 0-15
     * @param note 0-127
     * @param pressure 0-127
     * @return true if message sent successfully
     */
    bool sendPolyKeyPress(uint8_t channel, uint8_t note, uint8_t pressure);

    /**
     * Send a control change event
     *
     * @param channel 0-15
     * @param key 0-127
     * @param value 0-127
     * @return true if message sent successfully
     */
    bool sendControlChange(uint8_t channel, uint8_t key, uint8_t value);

    /**
     * Send a program change event
     *
     * @param channel 0-15
     * @param program 0-127
     * @return true if message sent successfully
     */
    bool sendProgramChange(uint8_t channel, uint8_t program);

    /**
     * Send a channel pressure event
     *
     * @param channel 0-15
     * @param pressure 0-127
     * @return true if message sent successfully
     */
    bool sendChannelPressure(uint8_t channel, uint8_t pressure);

    /**
     * Send a control change event
     *
     * @param channel 0-15
     * @param key 0(lower)-8191(center)-16383(higher)
     * @return true if message sent successfully
     */
    bool sendPitchBend(uint8_t channel, uint16_t value);

    /**
     * Send a single byte event
     *
     * @param data 0-255
     * @return true if message sent successfully
     */
    bool sendSingleByte(uint8_t data);

protected:
    //From IUSBEnumerator
    virtual void setVidPid(uint16_t vid, uint16_t pid);
    virtual bool parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol); //Must return true if the interface should be parsed
    virtual bool useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir); //Must return true if the endpoint will be used

private:
    USBHost * host;
    USBDeviceConnected * dev;
    USBEndpoint * bulk_in;
    USBEndpoint * bulk_out;
    uint32_t size_bulk_in;
    uint32_t size_bulk_out;

    bool dev_connected;

    void init();

    uint8_t buf[64];

    void rxHandler();

    uint16_t sysExBufferPos;
    uint8_t sysExBuffer[64];

    void (*miscellaneousFunctionCode)(uint8_t, uint8_t, uint8_t);
    void (*cableEvent)(uint8_t, uint8_t, uint8_t);
    void (*systemCommonTwoBytes)(uint8_t, uint8_t);
    void (*systemCommonThreeBytes)(uint8_t, uint8_t, uint8_t);
    void (*systemExclusive)(uint8_t *, uint16_t, bool);
    void (*noteOff)(uint8_t, uint8_t, uint8_t);
    void (*noteOn)(uint8_t, uint8_t, uint8_t);
    void (*polyKeyPress)(uint8_t, uint8_t, uint8_t);
    void (*controlChange)(uint8_t, uint8_t, uint8_t);
    void (*programChange)(uint8_t, uint8_t);
    void (*channelPressure)(uint8_t, uint8_t);
    void (*pitchBend)(uint8_t, uint16_t);
    void (*singleByte)(uint8_t);

    bool sendMidiBuffer(uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3);

    int midi_intf;
    bool midi_device_found;

};

#endif /* USBHOST_MIDI */

#endif /* USBHOSTMIDI_H */
