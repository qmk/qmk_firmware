import usb.core


from milc import cli


def _flash_caterina(mcu, file):
    command = ['avrdude', '-p', f'{mcu}', '-c', 'avr109', '-U', f'flash:w:"{file}":i', '-P', f'{port}']
    cli.run(command)


def _flash_atmel_dfu(mcu, file):
    cli.run(['dfu-programmer', f'{mcu}', 'erase', '--force'])
    cli.run(['dfu-programmer', f'{mcu}', 'flash', '--force', f'"{file}"'])
    cli.run(['dfu-programmer', f'{mcu}', 'reset'])


def flash(mcu, file):
    pass
