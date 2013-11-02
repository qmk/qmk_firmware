"""
             LUFA Library
     Copyright (C) Dean Camera, 2013.

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
import pywinusb.hid as hid

# Generic HID device VID, PID and report payload length (length is increased
# by one to account for the Report ID byte that must be pre-pended)
device_vid = 0x03EB
device_pid = 0x204F
report_length = 1 + 8


def get_hid_device_handle():
    hid_device_filter = hid.HidDeviceFilter(vendor_id=device_vid,
                                            product_id=device_pid)

    valid_hid_devices = hid_device_filter.get_devices()

    if len(valid_hid_devices) is 0:
        return None
    else:
        return valid_hid_devices[0]


def send_led_pattern(device, led1, led2, led3, led4):
    # Report data for the demo is the report ID (always zero) followed by the
    # LED on/off data
    report_data = [0, led1, led2, led3, led4]

    # Zero-extend the array to the length the report should be
    report_data.extend([0] * (report_length - len(report_data)))

    # Send the generated report to the device
    device.send_output_report(report_data)

    print("Sent LED Pattern: {0}".format(report_data[1:5]))


def received_led_pattern(report_data):
    print("Received LED Pattern: {0}".format(report_data[1:5]))


def main():
    hid_device = get_hid_device_handle()

    if hid_device is None:
        print("No valid HID device found.")
        sys.exit(1)

    try:
        hid_device.open()

        print("Connected to device 0x%04X/0x%04X - %s [%s]" %
              (hid_device.vendor_id, hid_device.product_id,
               hid_device.product_name, hid_device.vendor_name))

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
