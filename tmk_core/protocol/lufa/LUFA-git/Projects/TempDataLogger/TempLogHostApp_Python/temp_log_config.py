"""
             LUFA Library
     Copyright (C) Dean Camera, 2014.

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
import pywinusb.hid as hid

# Generic HID device VID, PID and report payload length (length is increased
# by one to account for the Report ID byte that must be pre-pended)
device_vid = 0x03EB
device_pid = 0x2063
report_length = 1 + 7


def get_hid_device_handle():
    hid_device_filter = hid.HidDeviceFilter(vendor_id=device_vid,
                                            product_id=device_pid)

    valid_hid_devices = hid_device_filter.get_devices()

    if len(valid_hid_devices) is 0:
        return None
    else:
        return valid_hid_devices[0]


def configure_temp_log_device(device, time_date, log_interval_500ms):
    # Report data for the demo is the report ID (always zero)
    report_data = [0]

    # Followed by the time/date data
    report_data.extend([time_date.hour, time_date.minute,
                        time_date.second, time_date.day,
                        time_date.month, time_date.year - 2000])

    # Lastly the log interval in 500ms units of time
    report_data.extend([log_interval_500ms])

    # Zero-extend the array to the length the report should be
    report_data.extend([0] * (report_length - len(report_data)))

    # Send the generated report to the device
    device.send_output_report(report_data)


def main(time_date, log_interval_500ms):
    hid_device = get_hid_device_handle()

    if hid_device is None:
        print("No valid HID device found.")
        sys.exit(1)

    try:
        hid_device.open()

        print("Connected to device 0x%04X/0x%04X - %s [%s]" %
              (hid_device.vendor_id, hid_device.product_id,
               hid_device.product_name, hid_device.vendor_name))

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
