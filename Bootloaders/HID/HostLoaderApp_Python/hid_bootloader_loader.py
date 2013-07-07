"""
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
"""

"""
    Front-end programmer for the LUFA HID class bootloader.

    Usage:
        python hid_bootloader_loader.py <Device> <Input>.hex

    Example:
        python hid_bootloader_loader.py at90usb1287 Mouse.hex

    Requires the pywinusb (https://pypi.python.org/pypi/pywinusb/) and
    IntelHex (http://bialix.com/intelhex/) libraries.
"""

import sys
import pywinusb.hid as hid
from intelhex import IntelHex

# Device information table
device_info_map = dict()
device_info_map['at90usb1287'] = {'page_size': 256, 'flash_kb': 128}
device_info_map['at90usb1286'] = {'page_size': 256, 'flash_kb': 128}
device_info_map['at90usb647']  = {'page_size': 256, 'flash_kb': 64}
device_info_map['at90usb646']  = {'page_size': 256, 'flash_kb': 64}
device_info_map['atmega32u4']  = {'page_size': 128, 'flash_kb': 32}
device_info_map['atmega32u2']  = {'page_size': 128, 'flash_kb': 32}
device_info_map['atmega16u4']  = {'page_size': 128, 'flash_kb': 16}
device_info_map['atmega16u2']  = {'page_size': 128, 'flash_kb': 16}
device_info_map['at90usb162']  = {'page_size': 128, 'flash_kb': 16}
device_info_map['atmega8u2']   = {'page_size': 128, 'flash_kb': 8}
device_info_map['at90usb82']   = {'page_size': 128, 'flash_kb': 8}


def get_hid_device_handle():
    hid_device_filter = hid.HidDeviceFilter(vendor_id=0x03EB,
                                            product_id=0x2067)

    valid_hid_devices = hid_device_filter.get_devices()

    if len(valid_hid_devices) is 0:
        return None
    else:
        return valid_hid_devices[0]


def send_page_data(hid_device, address, data):
    output_report_data = [0]
    output_report_data.extend([address & 0xFF, address >> 8])
    output_report_data.extend(data)

    hid_device.send_output_report(output_report_data)


def main(hex_filename, device_info):
    hid_device = get_hid_device_handle()

    if hid_device is None:
        print("No valid HID device found.")
        sys.exit(1)

    try:
        hid_device.open()

        print("Connected to bootloader.")

        hex_data = IntelHex(hex_filename)

        for addr in range(0, hex_data.maxaddr(), device_info['page_size']):
            page_data = [hex_data[i] for i in range(addr, addr+device_info['page_size'])]

            print("Writing address 0x%04X-0x%04X" % (addr, addr+device_info['page_size']))

            if device_info['flash_kb'] < 64:
                send_page_data(hid_device, addr, page_data)
            else:
                send_page_data(hid_device, addr >> 8, page_data)

        print("Programming complete, starting application.")
        send_page_data(hid_device, 0xFFFF, [0] * device_info['page_size'])

    finally:
        hid_device.close()


if __name__ == '__main__':
    hex_filename = sys.argv[2]

    try:
        device_info = device_info_map[sys.argv[1]]
    except:
        print("Unknown device name specified.")
        sys.exit(1)

    main(hex_filename, device_info)
