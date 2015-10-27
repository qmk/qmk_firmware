"""
             LUFA Library
     Copyright (C) Dean Camera, 2014.

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
from pywinusb import hid
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
    # Bootloader page data should be the HID Report ID (always zero) followed
    # by the starting address to program, then one device's flash page worth
    # of data
    output_report_data = [0]
    output_report_data.extend([address & 0xFF, address >> 8])
    output_report_data.extend(data)

    hid_device.send_output_report(output_report_data)


def program_device(hex_data, device_info):
    hid_device = get_hid_device_handle()

    if hid_device is None:
        print("No valid HID device found.")
        sys.exit(1)

    try:
        hid_device.open()
        print("Connected to bootloader.")

        # Program in all data from the loaded HEX file, in a number of device
        # page sized chunks
        for addr in range(0, hex_data.maxaddr(), device_info['page_size']):
            # Compute the address range of the current page in the device
            current_page_range = range(addr, addr+device_info['page_size'])

            # Extract the data from the hex file at the specified start page
            # address and convert it to a regular list of bytes
            page_data = [hex_data[i] for i in current_page_range]

            print("Writing address 0x%04X-0x%04X" % (current_page_range[0], current_page_range[-1]))

            # Devices with more than 64KB of flash should shift down the page
            # address so that it is 16-bit (page size is guaranteed to be
            # >= 256 bytes so no non-zero address bits are discarded)
            if device_info['flash_kb'] < 64:
                send_page_data(hid_device, addr, page_data)
            else:
                send_page_data(hid_device, addr >> 8, page_data)

        # Once programming is complete, start the application via a dummy page
        # program to the page address 0xFFFF
        print("Programming complete, starting application.")
        send_page_data(hid_device, 0xFFFF, [0] * device_info['page_size'])

    finally:
        hid_device.close()


if __name__ == '__main__':
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
