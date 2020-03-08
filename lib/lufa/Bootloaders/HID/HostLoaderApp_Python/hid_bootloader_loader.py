#!/usr/bin/env python

"""
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
"""

"""
    Front-end programmer for the LUFA HID class bootloader.

    Usage:
        python hid_bootloader_loader.py <Device> <Input>.hex

    Example:
        python hid_bootloader_loader.py at90usb1287 Mouse.hex

    Requires the hidapi (https://pypi.python.org/pypi/hidapi) and
    IntelHex (https://pypi.python.org/pypi/IntelHex) libraries.
"""

import sys
import hid
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
    all_hid_devices = hid.enumerate()

    lufa_hid_devices = [d for d in all_hid_devices if d['vendor_id'] == 0x03EB and d['product_id'] == 0x2067]

    if len(lufa_hid_devices) is 0:
        return None

    device_handle = hid.device()
    device_handle.open_path(lufa_hid_devices[0]['path'])
    return device_handle


def send_page_data(hid_device, address, data):
    # Bootloader page data should be the HID Report ID (always zero) followed
    # by the starting address to program, then one device's flash page worth
    # of data
    output_report_data = bytearray(65)
    output_report_data[0] = 0
    output_report_data[1] = address & 0xFF
    output_report_data[2] = address >> 8
    output_report_data[3 : ] = data

    hid_device.write(output_report_data)


def program_device(hex_data, device_info):
    hid_device = get_hid_device_handle()

    if hid_device is None:
        print("No valid HID device found.")
        sys.exit(1)

    try:
        print("Connected to bootloader.", flush=True)

        # Program in all data from the loaded HEX file, in a number of device
        # page sized chunks
        for addr in range(0, hex_data.maxaddr(), device_info['page_size']):
            # Compute the address range of the current page in the device
            current_page_range = range(addr, addr+device_info['page_size'])

            # Extract the data from the hex file at the specified start page
            # address and convert it to a regular list of bytes
            page_data = [hex_data[i] for i in current_page_range]

            print("Writing address 0x%04X-0x%04X" % (current_page_range[0], current_page_range[-1]), flush=True)

            # Devices with more than 64KB of flash should shift down the page
            # address so that it is 16-bit (page size is guaranteed to be
            # >= 256 bytes so no non-zero address bits are discarded)
            if device_info['flash_kb'] < 64:
                send_page_data(hid_device, addr, page_data)
            else:
                send_page_data(hid_device, addr >> 8, page_data)

        # Once programming is complete, start the application via a dummy page
        # program to the page address 0xFFFF
        print("Programming complete, starting application.", flush=True)
        send_page_data(hid_device, 0xFFFF, [0] * device_info['page_size'])

    finally:
        hid_device.close()


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage:")
        print("\t{} device file.hex".format(sys.argv[0]))
        sys.exit(1)

    # Load the specified HEX file
    try:
        hex_data = IntelHex(sys.argv[2])
    except:
        print("Could not open the specified HEX file.")
        sys.exit(1)

    # Retrieve the device information entry for the specified device
    try:
        device_info = device_info_map[sys.argv[1]]
    except:
        print("Unknown device name specified.")
        sys.exit(1)

    program_device(hex_data, device_info)
