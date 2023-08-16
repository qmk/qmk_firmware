import platform
import shutil
import time
import os
import signal

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


class DelayedKeyboardInterrupt:
    # Custom interrupt handler to delay the processing of Ctrl-C
    # https://stackoverflow.com/a/21919644
    def __enter__(self):
        self.signal_received = False
        self.old_handler = signal.signal(signal.SIGINT, self.handler)

    def handler(self, sig, frame):
        self.signal_received = (sig, frame)

    def __exit__(self, type, value, traceback):
        signal.signal(signal.SIGINT, self.old_handler)
        if self.signal_received:
            self.old_handler(*self.signal_received)


# TODO: Make this more generic, so cli/doctor/check.py and flashers.py can share the code
def _check_dfu_programmer_version():
    # Return True if version is higher than 0.7.0: supports '--force'
    check = cli.run(['dfu-programmer', '--version'], combined_output=True, timeout=5)
    first_line = check.stdout.split('\n')[0]
    version_number = first_line.split()[1]
    maj, min_, bug = version_number.split('.')
    if int(maj) >= 0 and int(min_) >= 7:
        return True
    else:
        return False


def _find_usb_device(vid_hex, pid_hex):
    # WSL doesnt have access to USB - use powershell instead...?
    if 'microsoft' in platform.uname().release.lower():
        ret = cli.run(['powershell.exe', '-command', 'Get-PnpDevice -PresentOnly | Select-Object -Property InstanceId'])
        if f'USB\\VID_{vid_hex:04X}&PID_{pid_hex:04X}' in ret.stdout:
            return (vid_hex, pid_hex)
    else:
        with DelayedKeyboardInterrupt():
            # PyUSB does not like to be interrupted by Ctrl-C
            # therefore we catch the interrupt with a custom handler
            # and only process it once pyusb finished
            return usb.core.find(idVendor=vid_hex, idProduct=pid_hex)


def _find_uf2_devices():
    """Delegate to uf2conv.py as VID:PID pairs can potentially fluctuate more than other bootloaders
    """
    return cli.run(['util/uf2conv.py', '--list']).stdout.splitlines()


def _find_bootloader():
    # To avoid running forever in the background, only look for bootloaders for 10min
    start_time = time.time()
    while time.time() - start_time < 600:
        for bl in BOOTLOADER_VIDS_PIDS:
            for vid, pid in BOOTLOADER_VIDS_PIDS[bl]:
                vid_hex = int(f'0x{vid}', 0)
                pid_hex = int(f'0x{pid}', 0)
                dev = _find_usb_device(vid_hex, pid_hex)
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
                    elif bl == 'stm32-dfu' or bl == 'apm32-dfu' or bl == 'gd32v-dfu' or bl == 'kiibohd':
                        details = (vid, pid)
                    else:
                        details = None
                    return (bl, details)
        if _find_uf2_devices():
            return ('_uf2_compatible_', None)
        time.sleep(0.1)
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
    force = '--force' if _check_dfu_programmer_version() else ''
    cli.run(['dfu-programmer', mcu, 'erase', force], capture_output=False)
    cli.run(['dfu-programmer', mcu, 'flash', force, file], capture_output=False)
    cli.run(['dfu-programmer', mcu, 'reset'], capture_output=False)


def _flash_hid_bootloader(mcu, details, file):
    if details == 'halfkay':
        if shutil.which('teensy-loader-cli'):
            cmd = 'teensy-loader-cli'
        elif shutil.which('teensy_loader_cli'):
            cmd = 'teensy_loader_cli'

    # Use 'hid_bootloader_cli' for QMK HID and as a fallback for HalfKay
    if not cmd:
        if shutil.which('hid_bootloader_cli'):
            cmd = 'hid_bootloader_cli'
        else:
            return True

    cli.run([cmd, f'-mmcu={mcu}', '-w', '-v', file], capture_output=False)


def _flash_dfu_util(details, file):
    # STM32duino
    if details[0] == '1eaf' and details[1] == '0003':
        cli.run(['dfu-util', '-a', '2', '-d', f'{details[0]}:{details[1]}', '-R', '-D', file], capture_output=False)
    # kiibohd
    elif details[0] == '1c11' and details[1] == 'b007':
        cli.run(['dfu-util', '-a', '0', '-d', f'{details[0]}:{details[1]}', '-D', file], capture_output=False)
    # STM32, APM32, or GD32V DFU
    else:
        cli.run(['dfu-util', '-a', '0', '-d', f'{details[0]}:{details[1]}', '-s', '0x08000000:leave', '-D', file], capture_output=False)


def _flash_isp(mcu, programmer, file):
    programmer = 'usbasp' if programmer == 'usbasploader' else 'usbtiny'
    # Check if the provide mcu has an avrdude-specific name, otherwise pass on what the user provided
    mcu = AVRDUDE_MCU.get(mcu, mcu)
    cli.run(['avrdude', '-p', mcu, '-c', programmer, '-U', f'flash:w:{file}:i'], capture_output=False)


def _flash_mdloader(file):
    cli.run(['mdloader', '--first', '--download', file, '--restart'], capture_output=False)


def _flash_uf2(file):
    cli.run(['util/uf2conv.py', '--deploy', file], capture_output=False)


def flasher(mcu, file):
    bl, details = _find_bootloader()
    # Add a small sleep to avoid race conditions
    time.sleep(1)
    if bl == 'atmel-dfu':
        _flash_atmel_dfu(details, file)
    elif bl == 'caterina':
        if _flash_caterina(details, file):
            return (True, "The Caterina bootloader was found but is not writable. Check 'qmk doctor' output for advice.")
    elif bl == 'hid-bootloader':
        if mcu:
            if _flash_hid_bootloader(mcu, details, file):
                return (True, "Please make sure 'teensy_loader_cli' or 'hid_bootloader_cli' is available on your system.")
        else:
            return (True, "Specifying the MCU with '-m' is necessary for HalfKay/HID bootloaders!")
    elif bl == 'stm32-dfu' or bl == 'apm32-dfu' or bl == 'gd32v-dfu' or bl == 'kiibohd':
        _flash_dfu_util(details, file)
    elif bl == 'usbasploader' or bl == 'usbtinyisp':
        if mcu:
            _flash_isp(mcu, bl, file)
        else:
            return (True, "Specifying the MCU with '-m' is necessary for ISP flashing!")
    elif bl == 'md-boot':
        _flash_mdloader(file)
    elif bl == '_uf2_compatible_':
        _flash_uf2(file)
    else:
        return (True, "Known bootloader found but flashing not currently supported!")

    return (False, None)
