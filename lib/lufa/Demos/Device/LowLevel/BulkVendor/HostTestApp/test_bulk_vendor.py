"""
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
"""

"""
    LUFA Bulk Vendor device demo host test script. This script will send and
    receive a continuous stream of packets to/from to the device, to show
    bidirectional communications.

    Requires PyUSB >= 1.0.0 (https://github.com/pyusb/pyusb).
"""

import sys
from time import sleep
import usb.core
import usb.util

# Bulk Vendor HID device VID and PID
device_vid = 0x03EB
device_pid = 0x206C
device_in_ep  = 3
device_out_ep = 4


def get_vendor_device_handle():
	dev_handle = usb.core.find(idVendor=device_vid, idProduct=device_pid)
	return dev_handle


def write(device, packet):
    device.write(usb.util.ENDPOINT_OUT | device_out_ep, packet, 0, 1000)
    print("Sent Packet: {0}".format(packet))


def read(device):
    packet = device.read(usb.util.ENDPOINT_IN | device_in_ep, 64, 0, 1000)
    print("Received Packet: {0}".format(''.join([chr(x) for x in packet])))
    return packet


def main():
    vendor_device = get_vendor_device_handle()

    if vendor_device is None:
        print("No valid Vendor device found.")
        sys.exit(1)

    vendor_device.set_configuration()

    print("Connected to device 0x%04X/0x%04X - %s [%s]" %
          (vendor_device.idVendor, vendor_device.idProduct,
           usb.util.get_string(vendor_device, vendor_device.iProduct),
           usb.util.get_string(vendor_device, vendor_device.iManufacturer)))

    x = 0
    while 1:
    	x = x + 1 % 255
    	write(vendor_device, "TEST PACKET %d" % x)
    	read(vendor_device)
    	sleep(1)

if __name__ == '__main__':
    main()
