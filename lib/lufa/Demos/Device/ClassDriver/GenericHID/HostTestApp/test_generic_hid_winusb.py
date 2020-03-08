#!/usr/bin/env python

"""
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
"""

"""
    LUFA Generic HID device demo host test script. This script will send a
    continuous stream of generic reports to the device, to show a variable LED
    pattern on the target board. Send and received report data is printed to
    the terminal.

    Requires the pywinusb library (https://pypi.python.org/pypi/pywinusb/).
"""

import sys
from time import sleep
import hid


def get_hid_device_handle():
    all_hid_devices = hid.enumerate()

    lufa_hid_devices = [d for d in all_hid_devices if d['vendor_id'] == 0x03EB and d['product_id'] == 0x204F]

    if len(lufa_hid_devices) is 0:
        return None

    device_handle = hid.device()
    device_handle.open_path(lufa_hid_devices[0]['path'])
    return device_handle


def send_led_pattern(device, led1, led2, led3, led4):
    # Report data for the demo is the report ID (always zero) followed by the
    # LED on/off data
    report_data = bytearray(9)
    report_data[0] = 0
    report_data[1] = led1
    report_data[2] = led2
    report_data[3] = led3
    report_data[4] = led4

    # Send the generated report to the device
    device.write(report_data)

    print("Sent LED Pattern: {0}".format(report_data[1:5]))


def received_led_pattern(report_data):
    print("Received LED Pattern: {0}".format(report_data[1:5]))


def main():
    hid_device = get_hid_device_handle()

    if hid_device is None:
        print("No valid HID device found.")
        sys.exit(1)

    try:
        print("Connected to device.", flush=True)

        # Set up the HID input report handler to receive reports
        hid_device.set_raw_data_handler(received_led_pattern)

        p = 0
        while (hid_device.is_plugged()):
            # Convert the current pattern index to a bit-mask and send
            send_led_pattern(hid_device,
                             (p >> 3) & 1,
                             (p >> 2) & 1,
                             (p >> 1) & 1,
                             (p >> 0) & 1)

            # Compute next LED pattern in sequence
            p = (p + 1) % 16

            # Delay a bit for visual effect
            sleep(.2)

    finally:
        hid_device.close()


if __name__ == '__main__':
    main()
