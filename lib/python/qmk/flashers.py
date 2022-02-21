import usb.core


from qmk.constants import BOOTLOADER_VIDS_PIDS
from milc import cli


_PID_TO_MCU = {
    '2fef': 'atmega16u2',
    '2ff0': 'atmega32u2',
    '2ff3': 'atmega16u4',
    '2ff4': 'atmega32u4',
    '2ff9': 'at90usb64',
    '2ffa': 'at90usb162',
    '2ffb': 'at90usb128'
}


def _find_bootloader():
    for bl in BOOTLOADER_VIDS_PIDS:
        for vid, pid in BOOTLOADER_VIDS_PIDS[bl]:
            vid_hex = int(f'0x{vid}', 0)
            pid_hex = int(f'0x{pid}', 0)
            dev = usb.core.find(idVendor = vid_hex, idProduct = pid_hex)
            if dev:
                if bl == 'atmel-dfu':
                    details = _PID_TO_MCU[pid]
                elif bl == 'caterina':
                    details = (vid_hex, pid_hex)
                else:
                    mcu = None
                return (bl, details)
    return (None, None)


def _find_serial_port(vid, pid):
    if  'windows' in cli.platform.lower():
        from serial.tools.list_ports_windows import comports
    else:
        from serial.tools.list_ports_posix import comports
    for port in comports():
        port, desc, hwid = port
        if f'{vid:04x}:{pid:04x}' in hwid:
            return port
    return None


def _flash_caterina(details, file):
    port = _find_serial_port(details[0], details[1])
    cli.run(['avrdude', '-p', 'atmega32u4', '-c', 'avr109', '-U', f'flash:w:{file}:i', '-P', f'{port}'])


def _flash_atmel_dfu(mcu, file):
    cli.run(['dfu-programmer', f'{mcu}', 'erase', '--force'], capture_output = False)
    cli.run(['dfu-programmer', f'{mcu}', 'flash', '--force', f'{file}'], capture_output = False)
    cli.run(['dfu-programmer', f'{mcu}', 'reset'], capture_output = False)


def flasher(controller, file):
    bl, details = _find_bootloader()
    if bl == 'atmel-dfu':
        _flash_atmel_dfu(details, file.name)
    elif bl == 'caterina':
        _flash_caterina(details, file.name)
    pass
