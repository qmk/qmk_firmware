import shutil
import time
import os

import usb.core

from qmk.constants import BOOTLOADER_VIDS_PIDS
from milc import cli

# yapf: disable
_PID_TO_MCU = {
    '2fef': 'atmega16u2',
    '2ff0': 'atmega32u2',
    '2ff3': 'atmega16u4',
    '2ff4': 'atmega32u4',
    '2ff9': 'at90usb64',
    '2ffa': 'at90usb162',
    '2ffb': 'at90usb128'
}

AVRDUDE_MCU = {
    'atmega32a': 'm32',
    'atmega328p': 'm328p',
    'atmega328': 'm328',
}
# yapf: enable


def _find_bootloader():
    # To avoid running forever in the background, only look for bootloaders for 10min
    start_time = time.time()
    while time.time() - start_time < 600:
        for bl in BOOTLOADER_VIDS_PIDS:
            for vid, pid in BOOTLOADER_VIDS_PIDS[bl]:
                vid_hex = int(f'0x{vid}', 0)
                pid_hex = int(f'0x{pid}', 0)
                dev = usb.core.find(idVendor=vid_hex, idProduct=pid_hex)
                if dev:
                    if bl == 'atmel-dfu':
                        details = _PID_TO_MCU[pid]
                    elif bl == 'caterina':
                        details = (vid_hex, pid_hex)
                    elif bl == 'hid-bootloader':
                        if vid == '16c0' and pid == '0478':
                            details = 'halfkay'
                        else:
                            details = 'qmk-hid'
                    elif bl == 'stm32-dfu' or bl == 'apm32-dfu':
                        details = (vid, pid)
                    else:
                        details = None
                    return (bl, details)
    return (None, None)


def _find_serial_port(vid, pid):
    if 'windows' in cli.platform.lower():
        from serial.tools.list_ports_windows import comports
        platform = 'windows'
    else:
        from serial.tools.list_ports_posix import comports
        platform = 'posix'

    start_time = time.time()
    # Caterina times out after 8 seconds
    while time.time() - start_time < 8:
        for port in comports():
            port, desc, hwid = port
            if f'{vid:04x}:{pid:04x}' in hwid.casefold():
                if platform == 'windows':
                    time.sleep(1)
                    return port
                else:
                    start_time = time.time()
                    # Wait until the port becomes writable before returning
                    while time.time() - start_time < 8:
                        if os.access(port, os.W_OK):
                            return port
                        else:
                            time.sleep(0.5)
                return None
    return None


def _flash_caterina(details, file):
    port = _find_serial_port(details[0], details[1])
    if port:
        cli.run(['avrdude', '-p', 'atmega32u4', '-c', 'avr109', '-U', f'flash:w:{file}:i', '-P', port], capture_output=False)
        return False
    else:
        return True


def _flash_atmel_dfu(mcu, file):
    cli.run(['dfu-programmer', mcu, 'erase', '--force'], capture_output=False)
    cli.run(['dfu-programmer', mcu, 'flash', '--force', file], capture_output=False)
    cli.run(['dfu-programmer', mcu, 'reset'], capture_output=False)


def _flash_hid_bootloader(mcu, details, file):
    if details == 'halfkay':
        if shutil.which('teensy-loader-cli'):
            cmd = 'teensy-loader-cli'
        elif shutil.which('teensy_loader_cli'):
            cmd = 'teensy_loader_cli'
    else:
        cmd = 'hid_bootloader_cli'

    if cmd:
        cli.run([cmd, f'-mmcu={mcu}', '-w', '-v', file], capture_output=False)


def _flash_stm32(details, file):
    # STM32duino
    if details[0] == '1eaf' and details[1] == '0003':
        cli.run(['dfu-util', '-a', '2', '-d', f'{details[0]}:{details[1]}', '-R', '-D', file], capture_output=False)
    # STM32 DFU or APM32 DFU
    else:
        cli.run(['dfu-util', '-a', '0', '-d', f'{details[0]}:{details[1]}', '-s', '0x08000000:leave', '-D', file], capture_output=False)


def _flash_isp(mcu, programmer, file):
    programmer = 'usbasp' if programmer == 'usbasploader' else 'usbtiny'
    # Check if the provide mcu has an avrdude-specific name, otherwise pass on what the user provided
    mcu = AVRDUDE_MCU.get(mcu, mcu)
    cli.run(['avrdude', '-p', mcu, '-c', programmer, '-U', f'flash:w:{file}:i'], capture_output=False)


def flasher(mcu, file):
    bl, details = _find_bootloader()
    if bl == 'atmel-dfu':
        _flash_atmel_dfu(details, file.name)
    elif bl == 'caterina':
        if _flash_caterina(details, file.name):
            return (True, "The Caterina bootloader was found but is not writable. Check 'qmk doctor' output for advice.")
    elif bl == 'hid-bootloader':
        if mcu:
            _flash_hid_bootloader(mcu, details, file.name)
        else:
            return (True, "Specifying the MCU with '-m' is necessary for HalfKay/HID bootloaders!")
    elif bl == 'stm32-dfu' or bl == 'apm32-dfu':
        _flash_stm32(details, file.name)
    elif bl == 'usbasploader' or bl == 'usbtinyisp':
        if mcu:
            _flash_isp(mcu, bl, file.name)
        else:
            return (True, "Specifying the MCU with '-m' is necessary for ISP flashing!")

    return (False, None)
