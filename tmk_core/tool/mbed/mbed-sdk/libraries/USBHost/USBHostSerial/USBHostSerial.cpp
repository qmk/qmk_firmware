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

#include "USBHostSerial.h"

#if USBHOST_SERIAL

#include "dbg.h"

#define CHECK_INTERFACE(cls,subcls,proto) \
        (((cls == 0xFF)         && (subcls == 0xFF) && (proto == 0xFF)) /* QUALCOM CDC */  || \
         ((cls == SERIAL_CLASS) && (subcls == 0x00) && (proto == 0x00)) /* STANDARD CDC */ )

#if (USBHOST_SERIAL <= 1)

USBHostSerial::USBHostSerial()
{
    host = USBHost::getHostInst();
    ports_found = 0;
    dev_connected = false;
}

bool USBHostSerial::connected()
{
    return dev_connected;
}

void USBHostSerial::disconnect(void)
{
    ports_found = 0;
    dev = NULL;
}

bool USBHostSerial::connect() {

    if (dev)
    {
        for (uint8_t i = 0; i < MAX_DEVICE_CONNECTED; i++)
        {
            USBDeviceConnected* d = host->getDevice(i);
            if (dev == d)
                return true;
        }
        disconnect();
    }
    for (uint8_t i = 0; i < MAX_DEVICE_CONNECTED; i++)
    {
        USBDeviceConnected* d = host->getDevice(i);
        if (d != NULL) {

            USB_DBG("Trying to connect serial device \r\n");
            if(host->enumerate(d, this))
                break;

            USBEndpoint* bulk_in  = d->getEndpoint(port_intf, BULK_ENDPOINT, IN);
            USBEndpoint* bulk_out = d->getEndpoint(port_intf, BULK_ENDPOINT, OUT);
            if (bulk_in && bulk_out)
            {
                USBHostSerialPort::connect(host,d,port_intf,bulk_in, bulk_out);
                dev = d;
                dev_connected = true;
            }
        }
    }
    return dev != NULL;
}

/*virtual*/ void USBHostSerial::setVidPid(uint16_t vid, uint16_t pid)
{
    // we don't check VID/PID for MSD driver
}

/*virtual*/ bool USBHostSerial::parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol) //Must return true if the interface should be parsed
{
    if (!ports_found &&
        CHECK_INTERFACE(intf_class, intf_subclass, intf_protocol)) {
        port_intf = intf_nb;
        ports_found = true;
        return true;
    }
    return false;
}

/*virtual*/ bool USBHostSerial::useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir) //Must return true if the endpoint will be used
{
    if (ports_found && (intf_nb == port_intf)) {
        if (type == BULK_ENDPOINT)
            return true;
    }
    return false;
}

#else // (USBHOST_SERIAL > 1)

//------------------------------------------------------------------------------

USBHostMultiSerial::USBHostMultiSerial()
{
    host = USBHost::getHostInst();
    dev = NULL;
    memset(ports, NULL, sizeof(ports));
    ports_found = 0;
    dev_connected = false;
}

USBHostMultiSerial::~USBHostMultiSerial()
{
    disconnect();
}

bool USBHostMultiSerial::connected()
{
    return dev_connected;
}

void USBHostMultiSerial::disconnect(void)
{
    for (int port = 0; port < USBHOST_SERIAL; port ++)
    {
        if (ports[port])
        {
            delete ports[port];
            ports[port] = NULL;
        }
    }
    ports_found = 0;
    dev = NULL;
}

bool USBHostMultiSerial::connect() {

    if (dev)
    {
        for (uint8_t i = 0; i < MAX_DEVICE_CONNECTED; i++)
        {
            USBDeviceConnected* d = host->getDevice(i);
            if (dev == d)
                return true;
        }
        disconnect();
    }
    for (uint8_t i = 0; i < MAX_DEVICE_CONNECTED; i++)
    {
        USBDeviceConnected* d = host->getDevice(i);
        if (d != NULL) {

            USB_DBG("Trying to connect serial device \r\n");
            if(host->enumerate(d, this))
                break;

            for (int port = 0; port < ports_found; port ++)
            {
                USBEndpoint* bulk_in  = d->getEndpoint(port_intf[port], BULK_ENDPOINT, IN);
                USBEndpoint* bulk_out = d->getEndpoint(port_intf[port], BULK_ENDPOINT, OUT);
                if (bulk_in && bulk_out)
                {
                    ports[port] = new USBHostSerialPort();
                    if (ports[port])
                    {
                        ports[port]->connect(host,d,port_intf[port],bulk_in, bulk_out);
                        dev = d;
                        dev_connected = true;
                    }
                }
            }
        }
    }
    return dev != NULL;
}

/*virtual*/ void USBHostMultiSerial::setVidPid(uint16_t vid, uint16_t pid)
{
    // we don't check VID/PID for MSD driver
}

/*virtual*/ bool USBHostMultiSerial::parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol) //Must return true if the interface should be parsed
{
    if ((ports_found < USBHOST_SERIAL) &&
        CHECK_INTERFACE(intf_class, intf_subclass, intf_protocol)) {
        port_intf[ports_found++] = intf_nb;
        return true;
    }
    return false;
}

/*virtual*/ bool USBHostMultiSerial::useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir) //Must return true if the endpoint will be used
{
    if ((ports_found > 0) && (intf_nb == port_intf[ports_found-1])) {
        if (type == BULK_ENDPOINT)
            return true;
    }
    return false;
}

#endif

//------------------------------------------------------------------------------

#define SET_LINE_CODING 0x20

USBHostSerialPort::USBHostSerialPort(): circ_buf()
{
    init();
}

void USBHostSerialPort::init(void)
{
    host = NULL;
    dev = NULL;
    serial_intf = NULL;
    size_bulk_in = 0;
    size_bulk_out = 0;
    bulk_in = NULL;
    bulk_out = NULL;
    line_coding.baudrate = 9600;
    line_coding.data_bits = 8;
    line_coding.parity = None;
    line_coding.stop_bits = 1;
    circ_buf.flush();
}

void USBHostSerialPort::connect(USBHost* _host, USBDeviceConnected * _dev,
        uint8_t _serial_intf, USBEndpoint* _bulk_in, USBEndpoint* _bulk_out)
{
    host = _host;
    dev = _dev;
    serial_intf = _serial_intf;
    bulk_in = _bulk_in;
    bulk_out = _bulk_out;

    USB_INFO("New Serial device: VID:%04x PID:%04x [dev: %p - intf: %d]", dev->getVid(), dev->getPid(), dev, serial_intf);
    dev->setName("Serial", serial_intf);
    host->registerDriver(dev, serial_intf, this, &USBHostSerialPort::init);
    baud(9600);
    size_bulk_in = bulk_in->getSize();
    size_bulk_out = bulk_out->getSize();
    bulk_in->attach(this, &USBHostSerialPort::rxHandler);
    bulk_out->attach(this, &USBHostSerialPort::txHandler);
    host->bulkRead(dev, bulk_in, buf, size_bulk_in, false);
}

void USBHostSerialPort::rxHandler() {
    if (bulk_in) {
        int len = bulk_in->getLengthTransferred();
        if (bulk_in->getState() == USB_TYPE_IDLE) {
            for (int i = 0; i < len; i++) {
                circ_buf.queue(buf[i]);
            }
            rx.call();
            host->bulkRead(dev, bulk_in, buf, size_bulk_in, false);
        }
    }
}

void USBHostSerialPort::txHandler() {
    if (bulk_out) {
        if (bulk_out->getState() == USB_TYPE_IDLE) {
            tx.call();
        }
    }
}

int USBHostSerialPort::_putc(int c) {
    if (bulk_out) {
        if (host->bulkWrite(dev, bulk_out, (uint8_t *)&c, 1) == USB_TYPE_OK) {
            return 1;
        }
    }
    return -1;
}

void USBHostSerialPort::baud(int baudrate) {
    line_coding.baudrate = baudrate;
    format(line_coding.data_bits, (Parity)line_coding.parity, line_coding.stop_bits);
}

void USBHostSerialPort::format(int bits, Parity parity, int stop_bits) {
    line_coding.data_bits = bits;
    line_coding.parity = parity;
    line_coding.stop_bits = (stop_bits == 1) ? 0 : 2;

    // set line coding
    host->controlWrite( dev,
                        USB_RECIPIENT_INTERFACE | USB_HOST_TO_DEVICE | USB_REQUEST_TYPE_CLASS,
                        SET_LINE_CODING,
                        0, serial_intf, (uint8_t *)&line_coding, 7);
}

int USBHostSerialPort::_getc() {
    uint8_t c = 0;
    if (bulk_in == NULL) {
        init();
        return -1;
    }
    while (circ_buf.isEmpty());
    circ_buf.dequeue(&c);
    return c;
}

int USBHostSerialPort::writeBuf(const char* b, int s)
{
    int c = 0;
    if (bulk_out)
    {
        while (c < s)
        {
            int i = (s < size_bulk_out) ? s : size_bulk_out;
            if (host->bulkWrite(dev, bulk_out, (uint8_t *)(b+c), i) == USB_TYPE_OK)
                c += i;
        }
    }
    return s;
}

int USBHostSerialPort::readBuf(char* b, int s)
{
    int i = 0;
    if (bulk_in)
    {
        for (i = 0; i < s; )
            b[i++] = getc();
    }
    return i;
}

uint8_t USBHostSerialPort::available() {
    return circ_buf.available();
}



#endif
