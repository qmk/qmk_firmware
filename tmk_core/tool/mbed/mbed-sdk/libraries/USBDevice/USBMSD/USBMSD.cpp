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
#include "USBMSD.h"

#define DISK_OK         0x00
#define NO_INIT         0x01
#define NO_DISK         0x02
#define WRITE_PROTECT   0x04

#define CBW_Signature   0x43425355
#define CSW_Signature   0x53425355

// SCSI Commands
#define TEST_UNIT_READY            0x00
#define REQUEST_SENSE              0x03
#define FORMAT_UNIT                0x04
#define INQUIRY                    0x12
#define MODE_SELECT6               0x15
#define MODE_SENSE6                0x1A
#define START_STOP_UNIT            0x1B
#define MEDIA_REMOVAL              0x1E
#define READ_FORMAT_CAPACITIES     0x23
#define READ_CAPACITY              0x25
#define READ10                     0x28
#define WRITE10                    0x2A
#define VERIFY10                   0x2F
#define READ12                     0xA8
#define WRITE12                    0xAA
#define MODE_SELECT10              0x55
#define MODE_SENSE10               0x5A

// MSC class specific requests
#define MSC_REQUEST_RESET          0xFF
#define MSC_REQUEST_GET_MAX_LUN    0xFE

#define DEFAULT_CONFIGURATION (1)

// max packet size
#define MAX_PACKET  MAX_PACKET_SIZE_EPBULK

// CSW Status
enum Status {
    CSW_PASSED,
    CSW_FAILED,
    CSW_ERROR,
};


USBMSD::USBMSD(uint16_t vendor_id, uint16_t product_id, uint16_t product_release): USBDevice(vendor_id, product_id, product_release) {
    stage = READ_CBW;
    memset((void *)&cbw, 0, sizeof(CBW));
    memset((void *)&csw, 0, sizeof(CSW));
    page = NULL;
}

USBMSD::~USBMSD() {
    disconnect();
}


// Called in ISR context to process a class specific request
bool USBMSD::USBCallback_request(void) {

    bool success = false;
    CONTROL_TRANSFER * transfer = getTransferPtr();
    static uint8_t maxLUN[1] = {0};

    if (transfer->setup.bmRequestType.Type == CLASS_TYPE) {
        switch (transfer->setup.bRequest) {
            case MSC_REQUEST_RESET:
                reset();
                success = true;
                break;
            case MSC_REQUEST_GET_MAX_LUN:
                transfer->remaining = 1;
                transfer->ptr = maxLUN;
                transfer->direction = DEVICE_TO_HOST;
                success = true;
                break;
            default:
                break;
        }
    }

    return success;
}


bool USBMSD::connect(bool blocking) {
    //disk initialization
    if (disk_status() & NO_INIT) {
        if (disk_initialize()) {
            return false;
        }
    }

    // get number of blocks
    BlockCount = disk_sectors();

    // get memory size
    MemorySize = disk_size();

    if (BlockCount > 0) {
        BlockSize = MemorySize / BlockCount;
        if (BlockSize != 0) {
            free(page);
            page = (uint8_t *)malloc(BlockSize * sizeof(uint8_t));
            if (page == NULL)
                return false;
        }
    } else {
        return false;
    }

    //connect the device
    USBDevice::connect(blocking);
    return true;
}

void USBMSD::disconnect() {
    USBDevice::disconnect();
    //De-allocate MSD page size:
    free(page);
    page = NULL;
}

void USBMSD::reset() {
    stage = READ_CBW;
}


// Called in ISR context called when a data is received
bool USBMSD::EPBULK_OUT_callback() {
    uint32_t size = 0;
    uint8_t buf[MAX_PACKET_SIZE_EPBULK];
    readEP(EPBULK_OUT, buf, &size, MAX_PACKET_SIZE_EPBULK);
    switch (stage) {
            // the device has to decode the CBW received
        case READ_CBW:
            CBWDecode(buf, size);
            break;

            // the device has to receive data from the host
        case PROCESS_CBW:
            switch (cbw.CB[0]) {
                case WRITE10:
                case WRITE12:
                    memoryWrite(buf, size);
                    break;
                case VERIFY10:
                    memoryVerify(buf, size);
                    break;
            }
            break;

            // an error has occured: stall endpoint and send CSW
        default:
            stallEndpoint(EPBULK_OUT);
            csw.Status = CSW_ERROR;
            sendCSW();
            break;
    }

    //reactivate readings on the OUT bulk endpoint
    readStart(EPBULK_OUT, MAX_PACKET_SIZE_EPBULK);
    return true;
}

// Called in ISR context when a data has been transferred
bool USBMSD::EPBULK_IN_callback() {
    switch (stage) {

            // the device has to send data to the host
        case PROCESS_CBW:
            switch (cbw.CB[0]) {
                case READ10:
                case READ12:
                    memoryRead();
                    break;
            }
            break;

            //the device has to send a CSW
        case SEND_CSW:
            sendCSW();
            break;

        // the host has received the CSW -> we wait a CBW
        case WAIT_CSW:
            stage = READ_CBW;
            break;

        // an error has occured
        default:
            stallEndpoint(EPBULK_IN);
            sendCSW();
            break;
    }
    return true;
}


void USBMSD::memoryWrite (uint8_t * buf, uint16_t size) {

    if ((addr + size) > MemorySize) {
        size = MemorySize - addr;
        stage = ERROR;
        stallEndpoint(EPBULK_OUT);
    }

    // we fill an array in RAM of 1 block before writing it in memory
    for (int i = 0; i < size; i++)
        page[addr%BlockSize + i] = buf[i];

    // if the array is filled, write it in memory
    if (!((addr + size)%BlockSize)) {
        if (!(disk_status() & WRITE_PROTECT)) {
            disk_write(page, addr/BlockSize, 1);
        }
    }

    addr += size;
    length -= size;
    csw.DataResidue -= size;

    if ((!length) || (stage != PROCESS_CBW)) {
        csw.Status = (stage == ERROR) ? CSW_FAILED : CSW_PASSED;
        sendCSW();
    }
}

void USBMSD::memoryVerify (uint8_t * buf, uint16_t size) {
    uint32_t n;

    if ((addr + size) > MemorySize) {
        size = MemorySize - addr;
        stage = ERROR;
        stallEndpoint(EPBULK_OUT);
    }

    // beginning of a new block -> load a whole block in RAM
    if (!(addr%BlockSize))
        disk_read(page, addr/BlockSize, 1);

    // info are in RAM -> no need to re-read memory
    for (n = 0; n < size; n++) {
        if (page[addr%BlockSize + n] != buf[n]) {
            memOK = false;
            break;
        }
    }

    addr += size;
    length -= size;
    csw.DataResidue -= size;

    if ( !length || (stage != PROCESS_CBW)) {
        csw.Status = (memOK && (stage == PROCESS_CBW)) ? CSW_PASSED : CSW_FAILED;
        sendCSW();
    }
}


bool USBMSD::inquiryRequest (void) {
    uint8_t inquiry[] = { 0x00, 0x80, 0x00, 0x01,
                          36 - 4, 0x80, 0x00, 0x00,
                          'M', 'B', 'E', 'D', '.', 'O', 'R', 'G',
                          'M', 'B', 'E', 'D', ' ', 'U', 'S', 'B', ' ', 'D', 'I', 'S', 'K', ' ', ' ', ' ',
                          '1', '.', '0', ' ',
                        };
    if (!write(inquiry, sizeof(inquiry))) {
        return false;
    }
    return true;
}


bool USBMSD::readFormatCapacity() {
    uint8_t capacity[] = { 0x00, 0x00, 0x00, 0x08,
                           (uint8_t)((BlockCount >> 24) & 0xff),
                           (uint8_t)((BlockCount >> 16) & 0xff),
                           (uint8_t)((BlockCount >> 8) & 0xff),
                           (uint8_t)((BlockCount >> 0) & 0xff),

                           0x02,
                           (uint8_t)((BlockSize >> 16) & 0xff),
                           (uint8_t)((BlockSize >> 8) & 0xff),
                           (uint8_t)((BlockSize >> 0) & 0xff),
                         };
    if (!write(capacity, sizeof(capacity))) {
        return false;
    }
    return true;
}


bool USBMSD::readCapacity (void) {
    uint8_t capacity[] = {
        (uint8_t)(((BlockCount - 1) >> 24) & 0xff),
        (uint8_t)(((BlockCount - 1) >> 16) & 0xff),
        (uint8_t)(((BlockCount - 1) >> 8) & 0xff),
        (uint8_t)(((BlockCount - 1) >> 0) & 0xff),

        (uint8_t)((BlockSize >> 24) & 0xff),
        (uint8_t)((BlockSize >> 16) & 0xff),
        (uint8_t)((BlockSize >> 8) & 0xff),
        (uint8_t)((BlockSize >> 0) & 0xff),
    };
    if (!write(capacity, sizeof(capacity))) {
        return false;
    }
    return true;
}

bool USBMSD::write (uint8_t * buf, uint16_t size) {

    if (size >= cbw.DataLength) {
        size = cbw.DataLength;
    }
    stage = SEND_CSW;

    if (!writeNB(EPBULK_IN, buf, size, MAX_PACKET_SIZE_EPBULK)) {
        return false;
    }

    csw.DataResidue -= size;
    csw.Status = CSW_PASSED;
    return true;
}


bool USBMSD::modeSense6 (void) {
    uint8_t sense6[] = { 0x03, 0x00, 0x00, 0x00 };
    if (!write(sense6, sizeof(sense6))) {
        return false;
    }
    return true;
}

void USBMSD::sendCSW() {
    csw.Signature = CSW_Signature;
    writeNB(EPBULK_IN, (uint8_t *)&csw, sizeof(CSW), MAX_PACKET_SIZE_EPBULK);
    stage = WAIT_CSW;
}

bool USBMSD::requestSense (void) {
    uint8_t request_sense[] = {
        0x70,
        0x00,
        0x05,   // Sense Key: illegal request
        0x00,
        0x00,
        0x00,
        0x00,
        0x0A,
        0x00,
        0x00,
        0x00,
        0x00,
        0x30,
        0x01,
        0x00,
        0x00,
        0x00,
        0x00,
    };

    if (!write(request_sense, sizeof(request_sense))) {
        return false;
    }

    return true;
}

void USBMSD::fail() {
    csw.Status = CSW_FAILED;
    sendCSW();
}


void USBMSD::CBWDecode(uint8_t * buf, uint16_t size) {
    if (size == sizeof(cbw)) {
        memcpy((uint8_t *)&cbw, buf, size);
        if (cbw.Signature == CBW_Signature) {
            csw.Tag = cbw.Tag;
            csw.DataResidue = cbw.DataLength;
            if ((cbw.CBLength <  1) || (cbw.CBLength > 16) ) {
                fail();
            } else {
                switch (cbw.CB[0]) {
                    case TEST_UNIT_READY:
                        testUnitReady();
                        break;
                    case REQUEST_SENSE:
                        requestSense();
                        break;
                    case INQUIRY:
                        inquiryRequest();
                        break;
                    case MODE_SENSE6:
                        modeSense6();
                        break;
                    case READ_FORMAT_CAPACITIES:
                        readFormatCapacity();
                        break;
                    case READ_CAPACITY:
                        readCapacity();
                        break;
                    case READ10:
                    case READ12:
                        if (infoTransfer()) {
                            if ((cbw.Flags & 0x80)) {
                                stage = PROCESS_CBW;
                                memoryRead();
                            } else {
                                stallEndpoint(EPBULK_OUT);
                                csw.Status = CSW_ERROR;
                                sendCSW();
                            }
                        }
                        break;
                    case WRITE10:
                    case WRITE12:
                        if (infoTransfer()) {
                            if (!(cbw.Flags & 0x80)) {
                                stage = PROCESS_CBW;
                            } else {
                                stallEndpoint(EPBULK_IN);
                                csw.Status = CSW_ERROR;
                                sendCSW();
                            }
                        }
                        break;
                    case VERIFY10:
                        if (!(cbw.CB[1] & 0x02)) {
                            csw.Status = CSW_PASSED;
                            sendCSW();
                            break;
                        }
                        if (infoTransfer()) {
                            if (!(cbw.Flags & 0x80)) {
                                stage = PROCESS_CBW;
                                memOK = true;
                            } else {
                                stallEndpoint(EPBULK_IN);
                                csw.Status = CSW_ERROR;
                                sendCSW();
                            }
                        }
                        break;
                    case MEDIA_REMOVAL:
                        csw.Status = CSW_PASSED;
                        sendCSW();
                        break;
                    default:
                        fail();
                        break;
                }
            }
        }
    }
}

void USBMSD::testUnitReady (void) {

    if (cbw.DataLength != 0) {
        if ((cbw.Flags & 0x80) != 0) {
            stallEndpoint(EPBULK_IN);
        } else {
            stallEndpoint(EPBULK_OUT);
        }
    }

    csw.Status = CSW_PASSED;
    sendCSW();
}


void USBMSD::memoryRead (void) {
    uint32_t n;

    n = (length > MAX_PACKET) ? MAX_PACKET : length;

    if ((addr + n) > MemorySize) {
        n = MemorySize - addr;
        stage = ERROR;
    }

    // we read an entire block
    if (!(addr%BlockSize))
        disk_read(page, addr/BlockSize, 1);

    // write data which are in RAM
    writeNB(EPBULK_IN, &page[addr%BlockSize], n, MAX_PACKET_SIZE_EPBULK);

    addr += n;
    length -= n;

    csw.DataResidue -= n;

    if ( !length || (stage != PROCESS_CBW)) {
        csw.Status = (stage == PROCESS_CBW) ? CSW_PASSED : CSW_FAILED;
        stage = (stage == PROCESS_CBW) ? SEND_CSW : stage;
    }
}


bool USBMSD::infoTransfer (void) {
    uint32_t n;

    // Logical Block Address of First Block
    n = (cbw.CB[2] << 24) | (cbw.CB[3] << 16) | (cbw.CB[4] <<  8) | (cbw.CB[5] <<  0);

    addr = n * BlockSize;

    // Number of Blocks to transfer
    switch (cbw.CB[0]) {
        case READ10:
        case WRITE10:
        case VERIFY10:
            n = (cbw.CB[7] <<  8) | (cbw.CB[8] <<  0);
            break;

        case READ12:
        case WRITE12:
            n = (cbw.CB[6] << 24) | (cbw.CB[7] << 16) | (cbw.CB[8] <<  8) | (cbw.CB[9] <<  0);
            break;
    }

    length = n * BlockSize;

    if (!cbw.DataLength) {              // host requests no data
        csw.Status = CSW_FAILED;
        sendCSW();
        return false;
    }

    if (cbw.DataLength != length) {
        if ((cbw.Flags & 0x80) != 0) {
            stallEndpoint(EPBULK_IN);
        } else {
            stallEndpoint(EPBULK_OUT);
        }

        csw.Status = CSW_FAILED;
        sendCSW();
        return false;
    }

    return true;
}





// Called in ISR context
// Set configuration. Return false if the
// configuration is not supported.
bool USBMSD::USBCallback_setConfiguration(uint8_t configuration) {
    if (configuration != DEFAULT_CONFIGURATION) {
        return false;
    }

    // Configure endpoints > 0
    addEndpoint(EPBULK_IN, MAX_PACKET_SIZE_EPBULK);
    addEndpoint(EPBULK_OUT, MAX_PACKET_SIZE_EPBULK);

    //activate readings
    readStart(EPBULK_OUT, MAX_PACKET_SIZE_EPBULK);
    return true;
}


uint8_t * USBMSD::stringIinterfaceDesc() {
    static uint8_t stringIinterfaceDescriptor[] = {
        0x08,                           //bLength
        STRING_DESCRIPTOR,              //bDescriptorType 0x03
        'M',0,'S',0,'D',0               //bString iInterface - MSD
    };
    return stringIinterfaceDescriptor;
}

uint8_t * USBMSD::stringIproductDesc() {
    static uint8_t stringIproductDescriptor[] = {
        0x12,                                           //bLength
        STRING_DESCRIPTOR,                              //bDescriptorType 0x03
        'M',0,'b',0,'e',0,'d',0,' ',0,'M',0,'S',0,'D',0 //bString iProduct - Mbed Audio
    };
    return stringIproductDescriptor;
}


uint8_t * USBMSD::configurationDesc() {
    static uint8_t configDescriptor[] = {

        // Configuration 1
        9,      // bLength
        2,      // bDescriptorType
        LSB(9 + 9 + 7 + 7), // wTotalLength
        MSB(9 + 9 + 7 + 7),
        0x01,   // bNumInterfaces
        0x01,   // bConfigurationValue: 0x01 is used to select this configuration
        0x00,   // iConfiguration: no string to describe this configuration
        0xC0,   // bmAttributes
        100,    // bMaxPower, device power consumption is 100 mA

        // Interface 0, Alternate Setting 0, MSC Class
        9,      // bLength
        4,      // bDescriptorType
        0x00,   // bInterfaceNumber
        0x00,   // bAlternateSetting
        0x02,   // bNumEndpoints
        0x08,   // bInterfaceClass
        0x06,   // bInterfaceSubClass
        0x50,   // bInterfaceProtocol
        0x04,   // iInterface

        // endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
        7,                          // bLength
        5,                          // bDescriptorType
        PHY_TO_DESC(EPBULK_IN),     // bEndpointAddress
        0x02,                       // bmAttributes (0x02=bulk)
        LSB(MAX_PACKET_SIZE_EPBULK),// wMaxPacketSize (LSB)
        MSB(MAX_PACKET_SIZE_EPBULK),// wMaxPacketSize (MSB)
        0,                          // bInterval

        // endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
        7,                          // bLength
        5,                          // bDescriptorType
        PHY_TO_DESC(EPBULK_OUT),    // bEndpointAddress
        0x02,                       // bmAttributes (0x02=bulk)
        LSB(MAX_PACKET_SIZE_EPBULK),// wMaxPacketSize (LSB)
        MSB(MAX_PACKET_SIZE_EPBULK),// wMaxPacketSize (MSB)
        0                           // bInterval
    };
    return configDescriptor;
}
