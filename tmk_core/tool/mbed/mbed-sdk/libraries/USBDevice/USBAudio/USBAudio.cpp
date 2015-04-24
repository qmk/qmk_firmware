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

#include "stdint.h"
#include "USBAudio.h"
#include "USBAudio_Types.h"



USBAudio::USBAudio(uint32_t frequency_in, uint8_t channel_nb_in, uint32_t frequency_out, uint8_t channel_nb_out, uint16_t vendor_id, uint16_t product_id, uint16_t product_release): USBDevice(vendor_id, product_id, product_release) {
    mute = 0;
    volCur = 0x0080;
    volMin = 0x0000;
    volMax = 0x0100;
    volRes = 0x0004;
    available = false;

    FREQ_IN = frequency_in;
    FREQ_OUT = frequency_out;

    this->channel_nb_in = channel_nb_in;
    this->channel_nb_out = channel_nb_out;

    // stereo -> *2, mono -> *1
    PACKET_SIZE_ISO_IN = (FREQ_IN / 500) * channel_nb_in;
    PACKET_SIZE_ISO_OUT = (FREQ_OUT / 500) * channel_nb_out;

    // STEREO -> left and right
    channel_config_in = (channel_nb_in == 1) ? CHANNEL_M : CHANNEL_L + CHANNEL_R;
    channel_config_out = (channel_nb_out == 1) ? CHANNEL_M : CHANNEL_L + CHANNEL_R;

    SOF_handler = false;

    buf_stream_out = NULL;
    buf_stream_in = NULL;

    interruptOUT = false;
    writeIN = false;
    interruptIN = false;
    available = false;

    volume = 0;

    // connect the device
    USBDevice::connect();
}

bool USBAudio::read(uint8_t * buf) {
    buf_stream_in = buf;
    SOF_handler = false;
    while (!available || !SOF_handler);
    available = false;
    return true;
}

bool USBAudio::readNB(uint8_t * buf) {
    buf_stream_in = buf;
    SOF_handler = false;
    while (!SOF_handler);
    if (available) {
        available = false;
        buf_stream_in = NULL;
        return true;
    }
    return false;
}

bool USBAudio::readWrite(uint8_t * buf_read, uint8_t * buf_write) {
    buf_stream_in = buf_read;
    SOF_handler = false;
    writeIN = false;
    if (interruptIN) {
        USBDevice::writeNB(EP3IN, buf_write, PACKET_SIZE_ISO_OUT, PACKET_SIZE_ISO_OUT);
    } else {
        buf_stream_out = buf_write;
    }
    while (!available);
    if (interruptIN) {
        while (!writeIN);
    }
    while (!SOF_handler);
    return true;
}


bool USBAudio::write(uint8_t * buf) {
    writeIN = false;
    SOF_handler = false;
    if (interruptIN) {
        USBDevice::writeNB(EP3IN, buf, PACKET_SIZE_ISO_OUT, PACKET_SIZE_ISO_OUT);
    } else {
        buf_stream_out = buf;
    }
    while (!SOF_handler);
    if (interruptIN) {
        while (!writeIN);
    }
    return true;
}


float USBAudio::getVolume() {
    return (mute) ? 0.0 : volume;
}


bool USBAudio::EPISO_OUT_callback() {
    uint32_t size = 0;
    interruptOUT = true;
    if (buf_stream_in != NULL) {
        readEP(EP3OUT, (uint8_t *)buf_stream_in, &size, PACKET_SIZE_ISO_IN);
        available = true;
        buf_stream_in = NULL;
    }
    readStart(EP3OUT, PACKET_SIZE_ISO_IN);
    return false;
}


bool USBAudio::EPISO_IN_callback() {
    interruptIN = true;
    writeIN = true;
    return true;
}



// Called in ISR context on each start of frame
void USBAudio::SOF(int frameNumber) {
    uint32_t size = 0;

    if (!interruptOUT) {
        // read the isochronous endpoint
        if (buf_stream_in != NULL) {
            if (USBDevice::readEP_NB(EP3OUT, (uint8_t *)buf_stream_in, &size, PACKET_SIZE_ISO_IN)) {
                if (size) {
                    available = true;
                    readStart(EP3OUT, PACKET_SIZE_ISO_IN);
                    buf_stream_in = NULL;
                }
            }
        }
    }

    if (!interruptIN) {
        // write if needed
        if (buf_stream_out != NULL) {
            USBDevice::writeNB(EP3IN, (uint8_t *)buf_stream_out, PACKET_SIZE_ISO_OUT, PACKET_SIZE_ISO_OUT);
            buf_stream_out = NULL;
        }
    }

    SOF_handler = true;
}


// Called in ISR context
// Set configuration. Return false if the configuration is not supported.
bool USBAudio::USBCallback_setConfiguration(uint8_t configuration) {
    if (configuration != DEFAULT_CONFIGURATION) {
        return false;
    }

    // Configure isochronous endpoint
    realiseEndpoint(EP3OUT, PACKET_SIZE_ISO_IN, ISOCHRONOUS);
    realiseEndpoint(EP3IN, PACKET_SIZE_ISO_OUT, ISOCHRONOUS);

    // activate readings on this endpoint
    readStart(EP3OUT, PACKET_SIZE_ISO_IN);
    return true;
}


// Called in ISR context
// Set alternate setting. Return false if the alternate setting is not supported
bool USBAudio::USBCallback_setInterface(uint16_t interface, uint8_t alternate) {
    if (interface == 0 && alternate == 0) {
        return true;
    }
    if (interface == 1 && (alternate == 0 || alternate == 1)) {
        return true;
    }
    if (interface == 2 && (alternate == 0 || alternate == 1)) {
        return true;
    }
    return false;
}



// Called in ISR context
// Called by USBDevice on Endpoint0 request
// This is used to handle extensions to standard requests and class specific requests.
// Return true if class handles this request
bool USBAudio::USBCallback_request() {
    bool success = false;
    CONTROL_TRANSFER * transfer = getTransferPtr();

    // Process class-specific requests
    if (transfer->setup.bmRequestType.Type == CLASS_TYPE) {

        // Feature Unit: Interface = 0, ID = 2
        if (transfer->setup.wIndex == 0x0200) {

            // Master Channel
            if ((transfer->setup.wValue & 0xff) == 0) {

                switch (transfer->setup.wValue >> 8) {
                    case MUTE_CONTROL:
                        switch (transfer->setup.bRequest) {
                            case REQUEST_GET_CUR:
                                transfer->remaining = 1;
                                transfer->ptr = &mute;
                                transfer->direction = DEVICE_TO_HOST;
                                success = true;
                                break;

                            case REQUEST_SET_CUR:
                                transfer->remaining = 1;
                                transfer->notify = true;
                                transfer->direction = HOST_TO_DEVICE;
                                success = true;
                                break;
                            default:
                                break;
                        }
                        break;
                    case VOLUME_CONTROL:
                        switch (transfer->setup.bRequest) {
                            case REQUEST_GET_CUR:
                                transfer->remaining = 2;
                                transfer->ptr = (uint8_t *)&volCur;
                                transfer->direction = DEVICE_TO_HOST;
                                success = true;
                                break;
                            case REQUEST_GET_MIN:
                                transfer->remaining = 2;
                                transfer->ptr = (uint8_t *)&volMin;
                                transfer->direction = DEVICE_TO_HOST;
                                success = true;
                                break;
                            case REQUEST_GET_MAX:
                                transfer->remaining = 2;
                                transfer->ptr = (uint8_t *)&volMax;
                                transfer->direction = DEVICE_TO_HOST;
                                success = true;
                                break;
                            case REQUEST_GET_RES:
                                transfer->remaining = 2;
                                transfer->ptr = (uint8_t *)&volRes;
                                transfer->direction = DEVICE_TO_HOST;
                                success = true;
                                break;

                            case REQUEST_SET_CUR:
                                transfer->remaining = 2;
                                transfer->notify = true;
                                transfer->direction = HOST_TO_DEVICE;
                                success = true;
                                break;
                            case REQUEST_SET_MIN:
                                transfer->remaining = 2;
                                transfer->notify = true;
                                transfer->direction = HOST_TO_DEVICE;
                                success = true;
                                break;
                            case REQUEST_SET_MAX:
                                transfer->remaining = 2;
                                transfer->notify = true;
                                transfer->direction = HOST_TO_DEVICE;
                                success = true;
                                break;
                            case REQUEST_SET_RES:
                                transfer->remaining = 2;
                                transfer->notify = true;
                                transfer->direction = HOST_TO_DEVICE;
                                success = true;
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return success;
}


// Called in ISR context when a data OUT stage has been performed
void USBAudio::USBCallback_requestCompleted(uint8_t * buf, uint32_t length) {
    if ((length == 1) || (length == 2)) {
        uint16_t data = (length == 1) ? *buf : *((uint16_t *)buf);
        CONTROL_TRANSFER * transfer = getTransferPtr();
        switch (transfer->setup.wValue >> 8) {
            case MUTE_CONTROL:
                switch (transfer->setup.bRequest) {
                    case REQUEST_SET_CUR:
                        mute = data & 0xff;
                        updateVol.call();
                        break;
                    default:
                        break;
                }
                break;
            case VOLUME_CONTROL:
                switch (transfer->setup.bRequest) {
                    case REQUEST_SET_CUR:
                        volCur = data;
                        volume = (float)volCur/(float)volMax;
                        updateVol.call();
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}



#define TOTAL_DESCRIPTOR_LENGTH ((1 * CONFIGURATION_DESCRIPTOR_LENGTH) \
                               + (5 * INTERFACE_DESCRIPTOR_LENGTH) \
                               + (1 * CONTROL_INTERFACE_DESCRIPTOR_LENGTH + 1) \
                               + (2 * INPUT_TERMINAL_DESCRIPTOR_LENGTH) \
                               + (1 * FEATURE_UNIT_DESCRIPTOR_LENGTH) \
                               + (2 * OUTPUT_TERMINAL_DESCRIPTOR_LENGTH) \
                               + (2 * STREAMING_INTERFACE_DESCRIPTOR_LENGTH) \
                               + (2 * FORMAT_TYPE_I_DESCRIPTOR_LENGTH) \
                               + (2 * (ENDPOINT_DESCRIPTOR_LENGTH + 2)) \
                               + (2 * STREAMING_ENDPOINT_DESCRIPTOR_LENGTH) )

#define TOTAL_CONTROL_INTF_LENGTH    (CONTROL_INTERFACE_DESCRIPTOR_LENGTH + 1 + \
                                      2*INPUT_TERMINAL_DESCRIPTOR_LENGTH     + \
                                      FEATURE_UNIT_DESCRIPTOR_LENGTH    + \
                                      2*OUTPUT_TERMINAL_DESCRIPTOR_LENGTH)

uint8_t * USBAudio::configurationDesc() {
    static uint8_t configDescriptor[] = {
        // Configuration 1
        CONFIGURATION_DESCRIPTOR_LENGTH,        // bLength
        CONFIGURATION_DESCRIPTOR,               // bDescriptorType
        LSB(TOTAL_DESCRIPTOR_LENGTH),           // wTotalLength (LSB)
        MSB(TOTAL_DESCRIPTOR_LENGTH),           // wTotalLength (MSB)
        0x03,                                   // bNumInterfaces
        DEFAULT_CONFIGURATION,                  // bConfigurationValue
        0x00,                                   // iConfiguration
        0x80,                                   // bmAttributes
        50,                                     // bMaxPower

        // Interface 0, Alternate Setting 0, Audio Control
        INTERFACE_DESCRIPTOR_LENGTH,            // bLength
        INTERFACE_DESCRIPTOR,                   // bDescriptorType
        0x00,                                   // bInterfaceNumber
        0x00,                                   // bAlternateSetting
        0x00,                                   // bNumEndpoints
        AUDIO_CLASS,                            // bInterfaceClass
        SUBCLASS_AUDIOCONTROL,                  // bInterfaceSubClass
        0x00,                                   // bInterfaceProtocol
        0x00,                                   // iInterface


        // Audio Control Interface
        CONTROL_INTERFACE_DESCRIPTOR_LENGTH + 1,// bLength
        INTERFACE_DESCRIPTOR_TYPE,              // bDescriptorType
        CONTROL_HEADER,                         // bDescriptorSubtype
        LSB(0x0100),                            // bcdADC (LSB)
        MSB(0x0100),                            // bcdADC (MSB)
        LSB(TOTAL_CONTROL_INTF_LENGTH),         // wTotalLength
        MSB(TOTAL_CONTROL_INTF_LENGTH),         // wTotalLength
        0x02,                                   // bInCollection
        0x01,                                   // baInterfaceNr
        0x02,                                   // baInterfaceNr

        // Audio Input Terminal (Speaker)
        INPUT_TERMINAL_DESCRIPTOR_LENGTH,       // bLength
        INTERFACE_DESCRIPTOR_TYPE,              // bDescriptorType
        CONTROL_INPUT_TERMINAL,                 // bDescriptorSubtype
        0x01,                                   // bTerminalID
        LSB(TERMINAL_USB_STREAMING),            // wTerminalType
        MSB(TERMINAL_USB_STREAMING),            // wTerminalType
        0x00,                                   // bAssocTerminal
        channel_nb_in,                          // bNrChannels
        (uint8_t)(LSB(channel_config_in)),                 // wChannelConfig
        (uint8_t)(MSB(channel_config_in)),                 // wChannelConfig
        0x00,                                   // iChannelNames
        0x00,                                   // iTerminal

        // Audio Feature Unit (Speaker)
        FEATURE_UNIT_DESCRIPTOR_LENGTH,         // bLength
        INTERFACE_DESCRIPTOR_TYPE,              // bDescriptorType
        CONTROL_FEATURE_UNIT,                   // bDescriptorSubtype
        0x02,                                   // bUnitID
        0x01,                                   // bSourceID
        0x01,                                   // bControlSize
        CONTROL_MUTE |
        CONTROL_VOLUME,                         // bmaControls(0)
        0x00,                                   // bmaControls(1)
        0x00,                                   // iTerminal

        // Audio Output Terminal (Speaker)
        OUTPUT_TERMINAL_DESCRIPTOR_LENGTH,      // bLength
        INTERFACE_DESCRIPTOR_TYPE,              // bDescriptorType
        CONTROL_OUTPUT_TERMINAL,                // bDescriptorSubtype
        0x03,                                   // bTerminalID
        LSB(TERMINAL_SPEAKER),                  // wTerminalType
        MSB(TERMINAL_SPEAKER),                  // wTerminalType
        0x00,                                   // bAssocTerminal
        0x02,                                   // bSourceID
        0x00,                                   // iTerminal


        // Audio Input Terminal (Microphone)
        INPUT_TERMINAL_DESCRIPTOR_LENGTH,       // bLength
        INTERFACE_DESCRIPTOR_TYPE,              // bDescriptorType
        CONTROL_INPUT_TERMINAL,                 // bDescriptorSubtype
        0x04,                                   // bTerminalID
        LSB(TERMINAL_MICROPHONE),               // wTerminalType
        MSB(TERMINAL_MICROPHONE),               // wTerminalType
        0x00,                                   // bAssocTerminal
        channel_nb_out,                         // bNrChannels
        (uint8_t)(LSB(channel_config_out)),                // wChannelConfig
        (uint8_t)(MSB(channel_config_out)),                // wChannelConfig
        0x00,                                   // iChannelNames
        0x00,                                   // iTerminal

        // Audio Output Terminal (Microphone)
        OUTPUT_TERMINAL_DESCRIPTOR_LENGTH,      // bLength
        INTERFACE_DESCRIPTOR_TYPE,              // bDescriptorType
        CONTROL_OUTPUT_TERMINAL,                // bDescriptorSubtype
        0x05,                                   // bTerminalID
        LSB(TERMINAL_USB_STREAMING),            // wTerminalType
        MSB(TERMINAL_USB_STREAMING),            // wTerminalType
        0x00,                                   // bAssocTerminal
        0x04,                                   // bSourceID
        0x00,                                   // iTerminal






        // Interface 1, Alternate Setting 0, Audio Streaming - Zero Bandwith
        INTERFACE_DESCRIPTOR_LENGTH,            // bLength
        INTERFACE_DESCRIPTOR,                   // bDescriptorType
        0x01,                                   // bInterfaceNumber
        0x00,                                   // bAlternateSetting
        0x00,                                   // bNumEndpoints
        AUDIO_CLASS,                            // bInterfaceClass
        SUBCLASS_AUDIOSTREAMING,                // bInterfaceSubClass
        0x00,                                   // bInterfaceProtocol
        0x00,                                   // iInterface

        // Interface 1, Alternate Setting 1, Audio Streaming - Operational
        INTERFACE_DESCRIPTOR_LENGTH,            // bLength
        INTERFACE_DESCRIPTOR,                   // bDescriptorType
        0x01,                                   // bInterfaceNumber
        0x01,                                   // bAlternateSetting
        0x01,                                   // bNumEndpoints
        AUDIO_CLASS,                            // bInterfaceClass
        SUBCLASS_AUDIOSTREAMING,                // bInterfaceSubClass
        0x00,                                   // bInterfaceProtocol
        0x00,                                   // iInterface

        // Audio Streaming Interface
        STREAMING_INTERFACE_DESCRIPTOR_LENGTH,  // bLength
        INTERFACE_DESCRIPTOR_TYPE,              // bDescriptorType
        STREAMING_GENERAL,                      // bDescriptorSubtype
        0x01,                                   // bTerminalLink
        0x00,                                   // bDelay
        LSB(FORMAT_PCM),                        // wFormatTag
        MSB(FORMAT_PCM),                        // wFormatTag

        // Audio Type I Format
        FORMAT_TYPE_I_DESCRIPTOR_LENGTH,        // bLength
        INTERFACE_DESCRIPTOR_TYPE,              // bDescriptorType
        STREAMING_FORMAT_TYPE,                  // bDescriptorSubtype
        FORMAT_TYPE_I,                          // bFormatType
        channel_nb_in,                          // bNrChannels
        0x02,                                   // bSubFrameSize
        16,                                     // bBitResolution
        0x01,                                   // bSamFreqType
        (uint8_t)(LSB(FREQ_IN)),                           // tSamFreq
        (uint8_t)((FREQ_IN >> 8) & 0xff),                  // tSamFreq
        (uint8_t)((FREQ_IN >> 16) & 0xff),                 // tSamFreq

        // Endpoint - Standard Descriptor
        ENDPOINT_DESCRIPTOR_LENGTH + 2,         // bLength
        ENDPOINT_DESCRIPTOR,                    // bDescriptorType
        PHY_TO_DESC(EPISO_OUT),                 // bEndpointAddress
        E_ISOCHRONOUS,                          // bmAttributes
        (uint8_t)(LSB(PACKET_SIZE_ISO_IN)),                   // wMaxPacketSize
        (uint8_t)(MSB(PACKET_SIZE_ISO_IN)),                   // wMaxPacketSize
        0x01,                                   // bInterval
        0x00,                                   // bRefresh
        0x00,                                   // bSynchAddress

        // Endpoint - Audio Streaming
        STREAMING_ENDPOINT_DESCRIPTOR_LENGTH,   // bLength
        ENDPOINT_DESCRIPTOR_TYPE,               // bDescriptorType
        ENDPOINT_GENERAL,                       // bDescriptor
        0x00,                                   // bmAttributes
        0x00,                                   // bLockDelayUnits
        LSB(0x0000),                            // wLockDelay
        MSB(0x0000),                            // wLockDelay







        // Interface 1, Alternate Setting 0, Audio Streaming - Zero Bandwith
        INTERFACE_DESCRIPTOR_LENGTH,            // bLength
        INTERFACE_DESCRIPTOR,                   // bDescriptorType
        0x02,                                   // bInterfaceNumber
        0x00,                                   // bAlternateSetting
        0x00,                                   // bNumEndpoints
        AUDIO_CLASS,                            // bInterfaceClass
        SUBCLASS_AUDIOSTREAMING,                // bInterfaceSubClass
        0x00,                                   // bInterfaceProtocol
        0x00,                                   // iInterface

        // Interface 1, Alternate Setting 1, Audio Streaming - Operational
        INTERFACE_DESCRIPTOR_LENGTH,            // bLength
        INTERFACE_DESCRIPTOR,                   // bDescriptorType
        0x02,                                   // bInterfaceNumber
        0x01,                                   // bAlternateSetting
        0x01,                                   // bNumEndpoints
        AUDIO_CLASS,                            // bInterfaceClass
        SUBCLASS_AUDIOSTREAMING,                // bInterfaceSubClass
        0x00,                                   // bInterfaceProtocol
        0x00,                                   // iInterface

        // Audio Streaming Interface
        STREAMING_INTERFACE_DESCRIPTOR_LENGTH,  // bLength
        INTERFACE_DESCRIPTOR_TYPE,              // bDescriptorType
        SUBCLASS_AUDIOCONTROL,                  // bDescriptorSubtype
        0x05,                                   // bTerminalLink (output terminal microphone)
        0x01,                                   // bDelay
        0x01,                                   // wFormatTag
        0x00,                                   // wFormatTag

        // Audio Type I Format
        FORMAT_TYPE_I_DESCRIPTOR_LENGTH,        // bLength
        INTERFACE_DESCRIPTOR_TYPE,              // bDescriptorType
        SUBCLASS_AUDIOSTREAMING,                // bDescriptorSubtype
        FORMAT_TYPE_I,                          // bFormatType
        channel_nb_out,                         // bNrChannels
        0x02,                                   // bSubFrameSize
        0x10,                                   // bBitResolution
        0x01,                                   // bSamFreqType
        (uint8_t)(LSB(FREQ_OUT)),                          // tSamFreq
        (uint8_t)((FREQ_OUT >> 8) & 0xff),                 // tSamFreq
        (uint8_t)((FREQ_OUT >> 16) & 0xff),                // tSamFreq

        // Endpoint - Standard Descriptor
        ENDPOINT_DESCRIPTOR_LENGTH + 2,         // bLength
        ENDPOINT_DESCRIPTOR,                    // bDescriptorType
        PHY_TO_DESC(EPISO_IN),                  // bEndpointAddress
        E_ISOCHRONOUS,                          // bmAttributes
        (uint8_t)(LSB(PACKET_SIZE_ISO_OUT)),                   // wMaxPacketSize
        (uint8_t)(MSB(PACKET_SIZE_ISO_OUT)),                   // wMaxPacketSize
        0x01,                                   // bInterval
        0x00,                                   // bRefresh
        0x00,                                   // bSynchAddress

        // Endpoint - Audio Streaming
        STREAMING_ENDPOINT_DESCRIPTOR_LENGTH,   // bLength
        ENDPOINT_DESCRIPTOR_TYPE,               // bDescriptorType
        ENDPOINT_GENERAL,                       // bDescriptor
        0x00,                                   // bmAttributes
        0x00,                                   // bLockDelayUnits
        LSB(0x0000),                            // wLockDelay
        MSB(0x0000),                            // wLockDelay

        // Terminator
        0                                       // bLength
    };
    return configDescriptor;
}

uint8_t * USBAudio::stringIinterfaceDesc() {
    static uint8_t stringIinterfaceDescriptor[] = {
        0x0c,                           //bLength
        STRING_DESCRIPTOR,              //bDescriptorType 0x03
        'A',0,'u',0,'d',0,'i',0,'o',0   //bString iInterface - Audio
    };
    return stringIinterfaceDescriptor;
}

uint8_t * USBAudio::stringIproductDesc() {
    static uint8_t stringIproductDescriptor[] = {
        0x16,                                                       //bLength
        STRING_DESCRIPTOR,                                          //bDescriptorType 0x03
        'M',0,'b',0,'e',0,'d',0,' ',0,'A',0,'u',0,'d',0,'i',0,'o',0 //bString iProduct - Mbed Audio
    };
    return stringIproductDescriptor;
}
