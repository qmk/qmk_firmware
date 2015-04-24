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


#ifndef USBMSD_H
#define USBMSD_H

/* These headers are included for child class. */
#include "USBEndpoints.h"
#include "USBDescriptor.h"
#include "USBDevice_Types.h"

#include "USBDevice.h"

/**
 * USBMSD class: generic class in order to use all kinds of blocks storage chip
 *
 * Introduction
 *
 * The USBMSD implements the MSD protocol. It permits to access a memory chip (flash, sdcard,...)
 * from a computer over USB. But this class doesn't work standalone, you need to subclass this class
 * and define virtual functions which are called in USBMSD.
 *
 * How to use this class with your chip ?
 *
 * You have to inherit and define some pure virtual functions (mandatory step):
 *   - virtual int disk_read(char * data, int block): function to read a block
 *   - virtual int disk_write(const char * data, int block): function to write a block
 *   - virtual int disk_initialize(): function to initialize the memory
 *   - virtual int disk_sectors(): return the number of blocks
 *   - virtual int disk_size(): return the memory size
 *   - virtual int disk_status(): return the status of the storage chip (0: OK, 1: not initialized, 2: no medium in the drive, 4: write protection)
 *
 * All functions names are compatible with the fat filesystem library. So you can imagine using your own class with
 * USBMSD and the fat filesystem library in the same program. Just be careful because there are two different parts which
 * will access the sd card. You can do a master/slave system using the disk_status method.
 *
 * Once these functions defined, you can call connect() (at the end of the constructor of your class for instance)
 * of USBMSD to connect your mass storage device. connect() will first call disk_status() to test the status of the disk.
 * If disk_status() returns 1 (disk not initialized), then disk_initialize() is called. After this step, connect() will collect information
 * such as the number of blocks and the memory size.
 */
class USBMSD: public USBDevice {
public:

    /**
    * Constructor
    *
    * @param vendor_id Your vendor_id
    * @param product_id Your product_id
    * @param product_release Your preoduct_release
    */
    USBMSD(uint16_t vendor_id = 0x0703, uint16_t product_id = 0x0104, uint16_t product_release = 0x0001);

    /**
    * Connect the USB MSD device. Establish disk initialization before really connect the device.
    *
    * @param blocking if not configured
    * @returns true if successful
    */
    bool connect(bool blocking = true);

    /**
    * Disconnect the USB MSD device.
    */
    void disconnect();

    /**
    * Destructor
    */
    ~USBMSD();

protected:

    /*
    * read one or more blocks on a storage chip
    *
    * @param data pointer where will be stored read data
    * @param block starting block number
    * @param count number of blocks to read
    * @returns 0 if successful
    */
    virtual int disk_read(uint8_t* data, uint64_t block, uint8_t count) = 0;

    /*
    * write one or more blocks on a storage chip
    *
    * @param data data to write
    * @param block starting block number
    * @param count number of blocks to write
    * @returns 0 if successful
    */
    virtual int disk_write(const uint8_t* data, uint64_t block, uint8_t count) = 0;

    /*
    * Disk initilization
    */
    virtual int disk_initialize() = 0;

    /*
    * Return the number of blocks
    *
    * @returns number of blocks
    */
    virtual uint64_t disk_sectors() = 0;

    /*
    * Return memory size
    *
    * @returns memory size
    */
    virtual uint64_t disk_size() = 0;


    /*
    * To check the status of the storage chip
    *
    * @returns status: 0: OK, 1: disk not initialized, 2: no medium in the drive, 4: write protected
    */
    virtual int disk_status() = 0;

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
    * Callback called when a packet is received
    */
    virtual bool EPBULK_OUT_callback();

    /*
    * Callback called when a packet has been sent
    */
    virtual bool EPBULK_IN_callback();

    /*
    * Set configuration of device. Add endpoints
    */
    virtual bool USBCallback_setConfiguration(uint8_t configuration);

    /*
    * Callback called to process class specific requests
    */
    virtual bool USBCallback_request();


private:

    // MSC Bulk-only Stage
    enum Stage {
        READ_CBW,     // wait a CBW
        ERROR,        // error
        PROCESS_CBW,  // process a CBW request
        SEND_CSW,     // send a CSW
        WAIT_CSW,     // wait that a CSW has been effectively sent
    };

    // Bulk-only CBW
    typedef struct {
        uint32_t Signature;
        uint32_t Tag;
        uint32_t DataLength;
        uint8_t  Flags;
        uint8_t  LUN;
        uint8_t  CBLength;
        uint8_t  CB[16];
    } PACKED CBW;

    // Bulk-only CSW
    typedef struct {
        uint32_t Signature;
        uint32_t Tag;
        uint32_t DataResidue;
        uint8_t  Status;
    } PACKED CSW;

    //state of the bulk-only state machine
    Stage stage;

    // current CBW
    CBW cbw;

    // CSW which will be sent
    CSW csw;

    // addr where will be read or written data
    uint32_t addr;

    // length of a reading or writing
    uint32_t length;

    // memory OK (after a memoryVerify)
    bool memOK;

    // cache in RAM before writing in memory. Useful also to read a block.
    uint8_t * page;

    int BlockSize;
    uint64_t MemorySize;
    uint64_t BlockCount;

    void CBWDecode(uint8_t * buf, uint16_t size);
    void sendCSW (void);
    bool inquiryRequest (void);
    bool write (uint8_t * buf, uint16_t size);
    bool readFormatCapacity();
    bool readCapacity (void);
    bool infoTransfer (void);
    void memoryRead (void);
    bool modeSense6 (void);
    void testUnitReady (void);
    bool requestSense (void);
    void memoryVerify (uint8_t * buf, uint16_t size);
    void memoryWrite (uint8_t * buf, uint16_t size);
    void reset();
    void fail();
};

#endif
