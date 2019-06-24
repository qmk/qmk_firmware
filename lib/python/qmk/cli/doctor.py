"""QMK Python Doctor

Check up for QMK environment.
"""
from milc import cli

import shutil
import platform
import os


@cli.entrypoint('Basic QMK environment checks')
def main(cli):

    binaries = ['dfu-programmer', 'avrdude', 'dfu-util', 'avr-gcc', 'arm-none-eabi-gcc']

    cli.log.info('QMK Doctor is Checking your environment')

    ok = True
    for binary in binaries:
        res = shutil.which(binary)
        if res is None:
            cli.log.error('{fg_red}QMK can\'t find ' + binary + ' in your path')
            ok = False

    OS = platform.system()
    if OS == "Darwin":
        cli.log.info("Detected {fg_cyan}macOS")
    elif OS == "Linux":
        cli.log.info("Detected {fg_cyan}linux")
        test = 'systemctl list-unit-files | grep enabled | grep -i ModemManager'
        if os.system(test) == 0:
            cli.log.warn("{bg_yellow}Detected modem manager. Please disable it if you are using Pro Micros")
    else:
        cli.log.info("Assuming {fg_cyan}Windows")

    if ok:
        cli.log.info('{fg_green}QMK is ready to go')
