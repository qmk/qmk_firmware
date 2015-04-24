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

#include "USBHostMIDI.h"

#if USBHOST_MIDI

#include "dbg.h"

#define SET_LINE_CODING 0x20

USBHostMIDI::USBHostMIDI() {
    host = USBHost::getHostInst();
    size_bulk_in = 0;
    size_bulk_out = 0;
    init();
}

void USBHostMIDI::init() {
    dev = NULL;
    bulk_in = NULL;
    bulk_out = NULL;
    dev_connected = false;
    midi_intf = -1;
    midi_device_found = false;
    sysExBufferPos = 0;
}

bool USBHostMIDI::connected() {
    return dev_connected;
}

bool USBHostMIDI::connect() {
    if (dev_connected) {
        return true;
    }

    for (uint8_t i = 0; i < MAX_DEVICE_CONNECTED; i++) {
        if ((dev = host->getDevice(i)) != NULL) {
            
            USB_DBG("Trying to connect MIDI device\r\n");

            if (host->enumerate(dev, this)) {
                break;
            }
            
            if (midi_device_found) {
                bulk_in = dev->getEndpoint(midi_intf, BULK_ENDPOINT, IN);
                bulk_out = dev->getEndpoint(midi_intf, BULK_ENDPOINT, OUT);
                
                if (!bulk_in || !bulk_out) {
                    break;
                }
                
                USB_INFO("New MIDI device: VID:%04x PID:%04x [dev: %p - intf: %d]", dev->getVid(), dev->getPid(), dev, midi_intf);
                dev->setName("MIDI", midi_intf);
                host->registerDriver(dev, midi_intf, this, &USBHostMIDI::init);
                
                size_bulk_in = bulk_in->getSize();
                size_bulk_out = bulk_out->getSize();
                
                bulk_in->attach(this, &USBHostMIDI::rxHandler);
                
                host->bulkRead(dev, bulk_in, buf, size_bulk_in, false);
                dev_connected = true;
                return true;
            }
        }
    }

    init();
    return false;
}

void USBHostMIDI::rxHandler() {
    uint8_t *midi;
    if (bulk_in) {
        int length = bulk_in->getLengthTransferred();
        if (bulk_in->getState() == USB_TYPE_IDLE || bulk_in->getState() == USB_TYPE_FREE) {
            // MIDI event handling
            for (int i = 0; i < length; i += 4) {
                if (i + 4 > length) {
                    // length shortage, ignored.
                    break;
                }

                // read each four bytes
                midi = &buf[i];
                // process MIDI message
                // switch by code index number
                switch (midi[0] & 0xf) {
                    case 0: // miscellaneous function codes
                        miscellaneousFunctionCode(midi[1], midi[2], midi[3]);
                        break;
                    case 1: // cable events
                        cableEvent(midi[1], midi[2], midi[3]);
                        break;
                    case 2: // two bytes system common messages 
                        systemCommonTwoBytes(midi[1], midi[2]);
                        break;
                    case 3: // three bytes system common messages 
                        systemCommonThreeBytes(midi[1], midi[2], midi[3]);
                        break;
                    case 4: // SysEx starts or continues
                        sysExBuffer[sysExBufferPos++] = midi[1];
                        if (sysExBufferPos >= 64) {
                            systemExclusive(sysExBuffer, sysExBufferPos, true);
                            sysExBufferPos = 0;
                        }
                        sysExBuffer[sysExBufferPos++] = midi[2];
                        if (sysExBufferPos >= 64) {
                            systemExclusive(sysExBuffer, sysExBufferPos, true);
                            sysExBufferPos = 0;
                        }
                        sysExBuffer[sysExBufferPos++] = midi[3];
                        // SysEx continues. don't send
                        break;
                    case 5: // SysEx ends with single byte
                        sysExBuffer[sysExBufferPos++] = midi[1];
                        systemExclusive(sysExBuffer, sysExBufferPos, false);
                        sysExBufferPos = 0;
                        break;
                    case 6: // SysEx ends with two bytes
                        sysExBuffer[sysExBufferPos++] = midi[1];
                        if (sysExBufferPos >= 64) {
                            systemExclusive(sysExBuffer, sysExBufferPos, true);
                            sysExBufferPos = 0;
                        }
                        sysExBuffer[sysExBufferPos++] = midi[2];
                        systemExclusive(sysExBuffer, sysExBufferPos, false);
                        sysExBufferPos = 0;
                        break;
                    case 7: // SysEx ends with three bytes
                        sysExBuffer[sysExBufferPos++] = midi[1];
                        if (sysExBufferPos >= 64) {
                            systemExclusive(sysExBuffer, sysExBufferPos, true);
                            sysExBufferPos = 0;
                        }
                        sysExBuffer[sysExBufferPos++] = midi[2];
                        if (sysExBufferPos >= 64) {
                            systemExclusive(sysExBuffer, sysExBufferPos, true);
                            sysExBufferPos = 0;
                        }
                        sysExBuffer[sysExBufferPos++] = midi[3];
                        systemExclusive(sysExBuffer, sysExBufferPos, false);
                        sysExBufferPos = 0;
                        break;
                    case 8:
                        noteOff(midi[1] & 0xf, midi[2], midi[3]);
                        break;
                    case 9:
                        if (midi[3]) {
                            noteOn(midi[1] & 0xf, midi[2], midi[3]);
                        } else {
                            noteOff(midi[1] & 0xf, midi[2], midi[3]);
                        }
                        break;
                    case 10:
                        polyKeyPress(midi[1] & 0xf, midi[2], midi[3]);
                        break;
                    case 11:
                        controlChange(midi[1] & 0xf, midi[2], midi[3]);
                        break;
                    case 12:
                        programChange(midi[1] & 0xf, midi[2]);
                        break;
                    case 13:
                        channelPressure(midi[1] & 0xf, midi[2]);
                        break;
                    case 14:
                        pitchBend(midi[1] & 0xf, midi[2] | (midi[3] << 7));
                        break;
                    case 15:
                        singleByte(midi[1]);
                        break;
                }
            }
            
            // read another message
            host->bulkRead(dev, bulk_in, buf, size_bulk_in, false);
        }
    }
}

bool USBHostMIDI::sendMidiBuffer(uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3) {
    if (bulk_out) {
        uint8_t midi[4];

        midi[0] = data0;
        midi[1] = data1;
        midi[2] = data2;
        midi[3] = data3;
        if (host->bulkWrite(dev, bulk_out, (uint8_t *)midi, 4) == USB_TYPE_OK) {
            return true;
        }
    }
    return false;
}

bool USBHostMIDI::sendMiscellaneousFunctionCode(uint8_t data1, uint8_t data2, uint8_t data3) {
    return sendMidiBuffer(0, data1, data2, data3);
}

bool USBHostMIDI::sendCableEvent(uint8_t data1, uint8_t data2, uint8_t data3) {
    return sendMidiBuffer(1, data1, data2, data3);
}

bool USBHostMIDI::sendSystemCommmonTwoBytes(uint8_t data1, uint8_t data2) {
    return sendMidiBuffer(2, data1, data2, 0);
}

bool USBHostMIDI::sendSystemCommmonThreeBytes(uint8_t data1, uint8_t data2, uint8_t data3) {
    return sendMidiBuffer(3, data1, data2, 0);
}

bool USBHostMIDI::sendSystemExclusive(uint8_t *buffer, int length) {
    uint8_t midi[64];
    int midiLength;
    int midiPos;
    if (bulk_out) {
        for (int i = 0; i < length; i += 48) {
            if (i + 48 >= length) {
                // contains last data
                midiLength = (((length - i) + 2) / 3) * 4;
                for (int pos = i; pos < length; pos += 3) {
                    midiPos = (pos + 2) / 3 * 4;
                    if (pos + 3 >= length) {
                        // last data
                        switch (pos % 3) {
                            case 0:
                                midi[midiPos    ] = 7;
                                midi[midiPos + 1] = buffer[pos    ];
                                midi[midiPos + 2] = buffer[pos + 1];
                                midi[midiPos + 3] = buffer[pos + 2];
                                break;
                            case 1:
                                midi[midiPos    ] = 5;
                                midi[midiPos + 1] = buffer[pos    ];
                                midi[midiPos + 2] = 0;
                                midi[midiPos + 3] = 0;
                               break;
                            case 2:
                                midi[midiPos    ] = 6;
                                midi[midiPos + 1] = buffer[pos    ];
                                midi[midiPos + 2] = buffer[pos + 1];
                                midi[midiPos + 3] = 0;
                                break;
                        }
                    } else {
                        // has more data
                        midi[midiPos    ] = 4;
                        midi[midiPos + 1] = buffer[pos    ];
                        midi[midiPos + 2] = buffer[pos + 1];
                        midi[midiPos + 3] = buffer[pos + 2];
                    }
                }
            } else {
                // has more data
                midiLength = 64;
                for (int pos = i; pos < length; pos += 3) {
                    midiPos = (pos + 2) / 3 * 4;
                    midi[midiPos    ] = 4;
                    midi[midiPos + 1] = buffer[pos    ];
                    midi[midiPos + 2] = buffer[pos + 1];
                    midi[midiPos + 3] = buffer[pos + 2];
                }
            }

            if (host->bulkWrite(dev, bulk_out, (uint8_t *)midi, midiLength) != USB_TYPE_OK) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool USBHostMIDI::sendNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
    return sendMidiBuffer(8, channel & 0xf | 0x80, note & 0x7f, velocity & 0x7f);
}

bool USBHostMIDI::sendNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
    return sendMidiBuffer(9, channel & 0xf | 0x90, note & 0x7f, velocity & 0x7f);
}

bool USBHostMIDI::sendPolyKeyPress(uint8_t channel, uint8_t note, uint8_t pressure) {
    return sendMidiBuffer(10, channel & 0xf | 0xa0, note & 0x7f, pressure & 0x7f);
}

bool USBHostMIDI::sendControlChange(uint8_t channel, uint8_t key, uint8_t value) {
    return sendMidiBuffer(11, channel & 0xf | 0xb0, key & 0x7f, value & 0x7f);
}

bool USBHostMIDI::sendProgramChange(uint8_t channel, uint8_t program) {
    return sendMidiBuffer(12, channel & 0xf | 0xc0, program & 0x7f, 0);
}

bool USBHostMIDI::sendChannelPressure(uint8_t channel, uint8_t pressure) {
    return sendMidiBuffer(13, channel & 0xf | 0xd0, pressure & 0x7f, 0);
}

bool USBHostMIDI::sendPitchBend(uint8_t channel, uint16_t value) {
    return sendMidiBuffer(14, channel & 0xf | 0xe0, value & 0x7f, (value >> 7) & 0x7f);
}

bool USBHostMIDI::sendSingleByte(uint8_t data) {
    return sendMidiBuffer(15, data, 0, 0);
}

/*virtual*/ void USBHostMIDI::setVidPid(uint16_t vid, uint16_t pid)
{
    // we don't check VID/PID for this driver
}

/*virtual*/ bool USBHostMIDI::parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol) //Must return true if the interface should be parsed
{
    // USB MIDI class/subclass
    if ((midi_intf == -1) &&
        (intf_class == AUDIO_CLASS) &&
        (intf_subclass == 0x03)) {
        midi_intf = intf_nb;
        return true;
    }
    
    // vendor specific device
    if ((midi_intf == -1) &&
        (intf_class == 0xff) &&
        (intf_subclass == 0x03)) {
        midi_intf = intf_nb;
        return true;
    }
    
    return false;
}

/*virtual*/ bool USBHostMIDI::useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir) //Must return true if the endpoint will be used
{
    if (intf_nb == midi_intf) {
        if (type == BULK_ENDPOINT) {
            midi_device_found = true;
            return true;
        }
    }
    return false;
}

#endif
