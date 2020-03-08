#!/usr/bin/env python

"""
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
"""

"""
    Front-end configuration app for the TempDataLogger project. This script
    configures the logger to the current system time and date, with a user
    defined logging interval.

    The logging interval should be specified in milliseconds and is rounded to
    a multiple of 500ms.

    Usage:
        python temp_log_config.py <Log_Interval>

    Example:
        python temp_log_config.py 500

    Requires the pywinusb library (https://pypi.python.org/pypi/pywinusb/).
"""

import sys
from datetime import datetime
import hid


def get_hid_device_handle():
    all_hid_devices = hid.enumerate()

    lufa_hid_devices = [d for d in all_hid_devices if d['vendor_id'] == 0x03EB and d['product_id'] == 0x2063]

    if len(lufa_hid_devices) is 0:
        return None

    device_handle = hid.device()
    device_handle.open_path(lufa_hid_devices[0]['path'])
    return device_handle


def configure_temp_log_device(device, time_date, log_interval_500ms):
    report_data = bytearray(8)

    # Report data for the demo is the report ID (always zero)
    report_data[0] = 0

    # Followed by the time/date data
    report_data[1] = time_date.hour
    report_data[2] = time_date.minute,
    report_data[3] = time_date.second
    report_data[4] = time_date.day,
    report_data[5] = time_date.month
    report_data[6] = time_date.year - 2000

    # Lastly the log interval in 500ms units of time
    report_data[7] = log_interval_500ms

    # Send the generated report to the device
    device.write(report_data)


def main(time_date, log_interval_500ms):
    hid_device = get_hid_device_handle()

    if hid_device is None:
        print("No valid HID device found.")
        sys.exit(1)

    try:
        print("Connected to device.", flush=True)

        configure_temp_log_device(hid_device, time_date, log_interval_500ms)

        print("Time/Date is now set to %s" % time_date)
        print("Log interval is now set to every %0.1fs" % (log_interval_500ms * (500.0 / 1000.0)))

    finally:
        hid_device.close()


if __name__ == '__main__':
    time_date = datetime.now()
    log_interval_500ms = (int(sys.argv[1]) / 500) if len(sys.argv) > 1 else 2

    # Clamp the log interval to the allowable range
    log_interval_500ms = max(log_interval_500ms, 0x01)
    log_interval_500ms = min(log_interval_500ms, 0xFF)

    main(time_date, log_interval_500ms)
