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

#ifndef MIDIMESSAGE_H
#define MIDIMESSAGE_H

#include "mbed.h"

#define MAX_MIDI_MESSAGE_SIZE 256 // Max message size. SysEx can be up to 65536 but 256 should be fine for most usage

// MIDI Message Format
//
// [ msg(4) | channel(4) ] [ 0 | n(7) ] [ 0 | m(7) ]
//
// MIDI Data Messages (Channel Specific)
//
// Message               msg n          m
// ---------------------------------------------
// Note Off              0x8 Key        Velocity
// Note On               0x9 Key        Velocity
// Polyphonic Aftertouch 0xA Key        Pressure
// Control Change        0xB Controller Value
// Program Change        0xC Program    -
// Channel Aftertouch    0xD Pressure   -
// Pitch Wheel           0xE LSB        MSB

#define CABLE_NUM (0<<4)

/** A MIDI message container */
class MIDIMessage {
public:
    MIDIMessage() : length(4) {}

    MIDIMessage(uint8_t *buf) : length(4) {
        for (int i = 0; i < 4; i++)
            data[i] = buf[i];
    }

    // New constructor, buf is a true MIDI message (not USBMidi message) and buf_len true message length.
    MIDIMessage(uint8_t *buf, int buf_len) {
        length=buf_len+1;
        // first byte keeped for retro-compatibility
        data[0]=0;

        for (int i = 0; i < buf_len; i++)
            data[i+1] = buf[i];
    }

    // create messages

    /** Create a NoteOff message
     * @param key Key ID
     * @param velocity Key velocity (0-127, default = 127)
     * @param channel Key channel (0-15, default 0)
     * @returns A MIDIMessage
     */
    static MIDIMessage NoteOff(int key, int velocity = 127, int channel = 0) {
        MIDIMessage msg;
        msg.data[0] = CABLE_NUM | 0x08;
        msg.data[1] = 0x80 | (channel & 0x0F);
        msg.data[2] = key & 0x7F;
        msg.data[3] = velocity & 0x7F;
        return msg;
    }

    /** Create a NoteOn message
     * @param key Key ID
     * @param velocity Key velocity (0-127, default = 127)
     * @param channel Key channel (0-15, default 0)
     * @returns A MIDIMessage
     */
    static MIDIMessage NoteOn(int key, int velocity = 127, int channel = 0) {
        MIDIMessage msg;
        msg.data[0] = CABLE_NUM | 0x09;
        msg.data[1] = 0x90 | (channel & 0x0F);
        msg.data[2] = key & 0x7F;
        msg.data[3] = velocity & 0x7F;
        return msg;
    }

    /** Create a PolyPhonic Aftertouch message
     * @param key Key ID
     * @param pressure Aftertouch pressure (0-127)
     * @param channel Key channel (0-15, default 0)
     * @returns A MIDIMessage
     */
    static MIDIMessage PolyphonicAftertouch(int key, int pressure, int channel = 0) {
        MIDIMessage msg;
        msg.data[0] = CABLE_NUM | 0x0A;
        msg.data[1] = 0xA0 | (channel & 0x0F);
        msg.data[2] = key & 0x7F;
        msg.data[3] = pressure & 0x7F;
        return msg;
    }

    /** Create a Control Change message
     * @param control Controller ID
     * @param value Controller value (0-127)
     * @param channel Controller channel (0-15, default 0)
     * @returns A MIDIMessage
     */
    static MIDIMessage ControlChange(int control, int value, int channel = 0) {
        MIDIMessage msg;
        msg.data[0] = CABLE_NUM | 0x0B;
        msg.data[1] = 0xB0 | (channel & 0x0F);
        msg.data[2] = control & 0x7F;
        msg.data[3] = value & 0x7F;
        return msg;
    }

    /** Create a Program Change message
     * @param program Program ID
     * @param channel Channel (0-15, default 0)
     * @returns A MIDIMessage
     */
    static MIDIMessage ProgramChange(int program, int channel = 0) {
        MIDIMessage msg;
        msg.data[0] = CABLE_NUM | 0x0C;
        msg.data[1] = 0xC0 | (channel & 0x0F);
        msg.data[2] = program & 0x7F;
        msg.data[3] = 0x00;
        return msg;
    }

    /** Create a Channel Aftertouch message
     * @param pressure Pressure
     * @param channel Key channel (0-15, default 0)
     * @returns A MIDIMessage
     */
    static MIDIMessage ChannelAftertouch(int pressure, int channel = 0) {
        MIDIMessage msg;
        msg.data[0] = CABLE_NUM | 0x0D;
        msg.data[1] = 0xD0 | (channel & 0x0F);
        msg.data[2] = pressure & 0x7F;
        msg.data[3] = 0x00;
        return msg;
    }

    /** Create a Pitch Wheel message
     * @param pitch Pitch (-8192 - 8191, default = 0)
     * @param channel Channel (0-15, default 0)
     * @returns A MIDIMessage
     */
    static MIDIMessage PitchWheel(int pitch = 0, int channel = 0) {
        MIDIMessage msg;
        int p = pitch + 8192;    // 0 - 16383, 8192 is center
        msg.data[0] = CABLE_NUM | 0x0E;
        msg.data[1] = 0xE0 | (channel & 0x0F);
        msg.data[2] = p & 0x7F;
        msg.data[3] = (p >> 7) & 0x7F;
        return msg;
    }

    /** Create an All Notes Off message
     * @param channel Channel (0-15, default 0)
     * @returns A MIDIMessage
     */
    static MIDIMessage AllNotesOff(int channel = 0) {
        return ControlChange(123, 0, channel);
    }

     /** Create a SysEx message
     * @param data SysEx data (including 0xF0 .. 0xF7)
     * @param len SysEx data length
     * @returns A MIDIMessage
     */
    static MIDIMessage SysEx(uint8_t *data, int len) {
        MIDIMessage msg=MIDIMessage(data,len);
        return msg;
    }

    // decode messages

    /** MIDI Message Types */
    enum MIDIMessageType {
        ErrorType,
        NoteOffType,
        NoteOnType,
        PolyphonicAftertouchType,
        ControlChangeType,
        ProgramChangeType,
        ChannelAftertouchType,
        PitchWheelType,
        AllNotesOffType,
        SysExType
    };

    /** Read the message type
     * @returns MIDIMessageType
     */
    MIDIMessageType type() {
        switch((data[1] >> 4) & 0xF) {
            case 0x8: return NoteOffType;
            case 0x9: return NoteOnType;
            case 0xA: return PolyphonicAftertouchType;
            case 0xB:
                if(controller() < 120) { // standard controllers
                    return ControlChangeType;
                } else if(controller() == 123) {
                    return AllNotesOffType;
                } else {
                    return ErrorType; // unsupported atm
                }
            case 0xC: return ProgramChangeType;
            case 0xD: return ChannelAftertouchType;
            case 0xE: return PitchWheelType;
            case 0xF: return SysExType;
            default: return ErrorType;
        }
    }

    /** Read the channel number */
    int channel() {
        return (data[1] & 0x0F);
    }

    /** Read the key ID */
    int key() {
        return (data[2] & 0x7F);
    }

    /** Read the velocity */
    int velocity() {
        return (data[3] & 0x7F);
    }

    /** Read the controller value */
    int value() {
        return (data[3] & 0x7F);
    }

    /** Read the aftertouch pressure */
    int pressure() {
        if(type() == PolyphonicAftertouchType) {
            return (data[3] & 0x7F);
        } else {
            return (data[2] & 0x7F);
        }
    }

    /** Read the controller number */
    int controller() {
        return (data[2] & 0x7F);
    }

    /** Read the program number */
    int program() {
        return (data[2] & 0x7F);
    }

    /** Read the pitch value */
    int pitch() {
        int p = ((data[3] & 0x7F) << 7) | (data[2] & 0x7F);
        return p - 8192; // 0 - 16383, 8192 is center
    }

    uint8_t data[MAX_MIDI_MESSAGE_SIZE+1];
    uint8_t length;
};

#endif
