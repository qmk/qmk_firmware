"""QMK Python Doctor

Check up for QMK environment.
"""
import os
import platform
import shutil
import subprocess
from glob import glob

from milc import cli


@cli.entrypoint('Basic QMK environment checks')
def main(cli):
    """Basic QMK environment checks.

    This is currently very simple, it just checks that all the expected binaries are on your system.

    TODO(unclaimed):
        * [ ] Compile a trivial program with each compiler
        * [ ] Check for udev entries on linux
    """

    binaries = ['dfu-programmer', 'avrdude', 'dfu-util', 'avr-gcc', 'arm-none-eabi-gcc']
    binaries += glob('bin/qmk-*')

    cli.log.info('QMK Doctor is checking your environment')

    ok = True
    for binary in binaries:
        res = shutil.which(binary)
        if res is None:
            cli.log.error("{fg_red}QMK can't find %s in your path", binary)
            ok = False
        else:
            try:
                subprocess.run([binary, '--version'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=5, check=True)
            except subprocess.CalledProcessError:
                cli.log.error("{fg_red}Can't run `%s --version`", binary)
                ok = False

    OS = platform.system()
    if OS == "Darwin":
        cli.log.info("Detected {fg_cyan}macOS")
    elif OS == "Linux":
        cli.log.info("Detected {fg_cyan}linux")
        if shutil.which('systemctl'):
            test = 'systemctl list-unit-files | grep enabled | grep -i ModemManager'
            if os.system(test) == 0:
                cli.log.warn("{bg_yellow}Detected modem manager. Please disable it if you are using Pro Micros")
        else:
            cli.log.warn("Can't find systemctl to check for ModemManager.")
    else:
        cli.log.info("Assuming {fg_cyan}Windows")

    if ok:
        cli.log.info('{fg_green}QMK is ready to go')
    else:
        cli.log.info('{fg_yellow}Problems detected, please fix these problems before proceeding.')
        # FIXME(skullydazed): Link to a document about troubleshooting, or discord or something
