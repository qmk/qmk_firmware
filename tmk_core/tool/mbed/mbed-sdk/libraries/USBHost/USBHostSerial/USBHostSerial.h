/* mbed USBHost Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef USBHOSTSERIAL_H
#define USBHOSTSERIAL_H

#include "USBHostConf.h"

#if USBHOST_SERIAL

#include "USBHost.h"
#include "Stream.h"
#include "MtxCircBuffer.h"

/**
 * A class to communicate a USB virtual serial port
 */
class USBHostSerialPort : public Stream {
public:
    /**
    * Constructor
    */
    USBHostSerialPort();

    enum IrqType {
        RxIrq,
        TxIrq
    };

    enum Parity {
        None = 0,
        Odd,
        Even,
        Mark,
        Space
    };

    void connect(USBHost* _host, USBDeviceConnected * _dev,
        uint8_t _serial_intf, USBEndpoint* _bulk_in, USBEndpoint* _bulk_out);

    /**
    * Check the number of bytes available.
    *
    * @returns the number of bytes available
    */
    uint8_t available();

    /**
     *  Attach a member function to call when a packet is received.
     *
     *  @param tptr pointer to the object to call the member function on
     *  @param mptr pointer to the member function to be called
     *  @param irq irq type
     */
    template<typename T>
    inline void attach(T* tptr, void (T::*mptr)(void), IrqType irq = RxIrq) {
        if ((mptr != NULL) && (tptr != NULL)) {
            if (irq == RxIrq) {
                rx.attach(tptr, mptr);
            } else {
                tx.attach(tptr, mptr);
            }
        }
    }

    /**
     * Attach a callback called when a packet is received
     *
     * @param ptr function pointer
     */
    inline void attach(void (*fn)(void), IrqType irq = RxIrq) {
        if (fn != NULL) {
            if (irq == RxIrq) {
                rx.attach(fn);
            } else {
                tx.attach(fn);
            }
        }
    }

    /** Set the baud rate of the serial port
     *
     *  @param baudrate The baudrate of the serial port (default = 9600).
     */
    void baud(int baudrate = 9600);

    /** Set the transmission format used by the Serial port
     *
     *  @param bits The number of bits in a word (default = 8)
     *  @param parity The parity used (USBHostSerialPort::None, USBHostSerialPort::Odd, USBHostSerialPort::Even, USBHostSerialPort::Mark, USBHostSerialPort::Space; default = USBHostSerialPort::None)
     *  @param stop The number of stop bits (1 or 2; default = 1)
     */
    void format(int bits = 8, Parity parity = USBHostSerialPort::None, int stop_bits = 1);
    virtual int writeBuf(const char* b, int s);
    virtual int readBuf(char* b, int s);

protected:
    virtual int _getc();
    virtual int _putc(int c);

private:
    USBHost * host;
    USBDeviceConnected * dev;

    USBEndpoint * bulk_in;
    USBEndpoint * bulk_out;
    uint32_t size_bulk_in;
    uint32_t size_bulk_out;

    void init();

    MtxCircBuffer<uint8_t, 128> circ_buf;

    uint8_t buf[64];

    typedef struct {
        uint32_t baudrate;
        uint8_t stop_bits;
        uint8_t parity;
        uint8_t data_bits;
    } PACKED LINE_CODING;

    LINE_CODING line_coding;

    void rxHandler();
    void txHandler();
    FunctionPointer rx;
    FunctionPointer tx;

    uint8_t serial_intf;
};

#if (USBHOST_SERIAL <= 1)

class USBHostSerial : public IUSBEnumerator, public USBHostSerialPort
{
public:
    USBHostSerial();

    /**
     * Try to connect a serial device
     *
     * @return true if connection was successful
     */
    bool connect();

    void disconnect();

    /**
    * Check if a any serial port is connected
    *
    * @returns true if a serial device is connected
    */
    bool connected();

protected:
    USBHost* host;
    USBDeviceConnected* dev;
    uint8_t port_intf;
    int ports_found;

    //From IUSBEnumerator
    virtual void setVidPid(uint16_t vid, uint16_t pid);
    virtual bool parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol); //Must return true if the interface should be parsed
    virtual bool useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir); //Must return true if the endpoint will be used

private:
    bool dev_connected;
};

#else // (USBHOST_SERIAL > 1)

class USBHostMultiSerial : public IUSBEnumerator {
public:
    USBHostMultiSerial();
    virtual ~USBHostMultiSerial();

    USBHostSerialPort* getPort(int port)
    {
        return port < USBHOST_SERIAL ? ports[port] : NULL;
    }

    /**
     * Try to connect a serial device
     *
     * @return true if connection was successful
     */
    bool connect();

    void disconnect();

    /**
    * Check if a any serial port is connected
    *
    * @returns true if a serial device is connected
    */
    bool connected();

protected:
    USBHost* host;
    USBDeviceConnected* dev;
    USBHostSerialPort* ports[USBHOST_SERIAL];
    uint8_t port_intf[USBHOST_SERIAL];
    int ports_found;

    //From IUSBEnumerator
    virtual void setVidPid(uint16_t vid, uint16_t pid);
    virtual bool parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol); //Must return true if the interface should be parsed
    virtual bool useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir); //Must return true if the endpoint will be used

private:
    bool dev_connected;
};
#endif // (USBHOST_SERIAL <= 1)

#endif

#endif
