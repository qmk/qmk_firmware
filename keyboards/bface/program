#!/usr/bin/env python
# Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>, Sebastian Kaim <sebb@sebb767.de>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

from __future__ import print_function

import os
import sys
import time
import usb


def checkForKeyboardInNormalMode():
    """Returns a device if a ps2avrGB device in normal made (that is in keyboard mode) or None if it is not found."""
    return usb.core.find(idVendor=0x20A0, idProduct=0x422D)

def checkForKeyboardInBootloaderMode():
    """Returns True if a ps2avrGB device in bootloader (flashable) mode is found and False otherwise."""
    return (usb.core.find(idVendor=0x16c0, idProduct=0x05df) is not None)

def flashKeyboard(firmware_file):
    """Calls bootloadHID to flash the given file to the device."""
    print('Flashing firmware to device ...')
    if os.system('bootloadHID -r "%s"' % firmware_file) == 0:
        print('\nDone!')
    else:
        print('\nbootloadHID returned an error.')

def printDeviceInfo(dev):
    """Prints all infos for a given USB device"""
    print('Device Information:')
    print('  idVendor: %d (0x%04x)' % (dev.idVendor, dev.idVendor))
    print('  idProduct: %d (0x%04x)' % (dev.idProduct, dev.idProduct))
    print('Manufacturer: %s' % (dev.iManufacturer))
    print('Serial: %s' % (dev.iSerialNumber))
    print('Product: %s' % (dev.iProduct), end='\n\n')

def sendDeviceToBootloaderMode(dev):
    """Tries to send a given ps2avrGB keyboard to bootloader mode to allow flashing."""
    try:
        dev.set_configuration()

        request_type = usb.util.build_request_type(
                usb.util.CTRL_OUT,
                usb.util.CTRL_TYPE_CLASS,
                usb.util.CTRL_RECIPIENT_DEVICE)

        USBRQ_HID_SET_REPORT = 0x09
        HID_REPORT_OPTION = 0x0301

        dev.ctrl_transfer(request_type, USBRQ_HID_SET_REPORT, HID_REPORT_OPTION, 0, [0, 0, 0xFF] + [0] * 5)
    except usb.core.USBError:
        # for some reason I keep getting USBError, but it works!
        pass


if len(sys.argv) < 2:
    print('Usage: %s <firmware.hex>' % sys.argv[0])
    sys.exit(1)

kb = checkForKeyboardInNormalMode()

if kb is not None:
    print('Found a keyboad in normal mode. Attempting to send it to bootloader mode ...', end='')
    sendDeviceToBootloaderMode(kb)
    print(' done.')
    print("Hint: If your keyboard can't be set to bootloader mode automatically, plug it in while pressing the bootloader key to do so manually.")
    print("      You can find more infos about this here: https://github.com/qmk/qmk_firmware/tree/master/keyboards/ps2avrGB#setting-the-board-to-bootloader-mode")

attempts = 12  # 60 seconds
found = False
for attempt in range(1, attempts + 1):
    print("Searching for keyboard in bootloader mode (%i/%i) ... " % (attempt, attempts), end='')

    if checkForKeyboardInBootloaderMode():
        print('Found', end='\n\n')
        flashKeyboard(sys.argv[1])
        found = True
        break
    else:
        print('Nothing.', end='')

        if attempt != attempts:  # no need to wait on the last attempt
            print(' Sleeping 5 seconds.', end='')
            time.sleep(5)

        # print a newline
        print()

if not found:
    print("Couldn't find a flashable keyboard. Aborting.")
    sys.exit(2)

