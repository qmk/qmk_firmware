"""QMK Python Doctor

Check up for QMK environment.
"""
import os
import platform
import shutil
import subprocess
from glob import glob

from milc import cli


@cli.subcommand('Basic QMK environment checks')
def doctor(cli):
    """Basic QMK environment checks.

    This is currently very simple, it just checks that all the expected binaries are on your system.

    TODO(unclaimed):
        * [ ] Compile a trivial program with each compiler
        * [ ] Check for udev entries on linux
    """
    cli.log.info('QMK Doctor is checking your environment.')

    # Make sure the basic CLI tools we need are available and can be executed.
    binaries = ['dfu-programmer', 'avrdude', 'dfu-util', 'avr-gcc', 'arm-none-eabi-gcc']
    binaries += glob('bin/qmk-*')
    ok = True

    for binary in binaries:
        res = shutil.which(binary)
        if res is None:
            cli.log.error("{fg_red}QMK can't find %s in your path.", binary)
            ok = False
        else:
            try:
                subprocess.run([binary, '--version'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=5, check=True)
                cli.log.info('Found {fg_cyan}%s', binary)
            except subprocess.CalledProcessError:
                cli.log.error("{fg_red}Can't run `%s --version`", binary)
                ok = False

    # Determine our OS and run platform specific tests
    OS = platform.system()

    if OS == "Darwin":
        cli.log.info("Detected {fg_cyan}macOS.")

    elif OS == "Linux":
        cli.log.info("Detected {fg_cyan}Linux.")
        if shutil.which('systemctl'):
            mm_check = subprocess.run(['systemctl', 'list-unit-files'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=10)
            if mm_check.returncode == 0:
                mm = True
                for line in mm_check.stdout.split('\n'):
                    if 'ModemManager' in line and 'enabled' in line:
                        mm = False

                if mm:
                    cli.log.warn("{bg_yellow}Detected ModemManager. Please disable it if you are using a Pro-Micro.")

            else:
                cli.log.error('{bg_red}Could not run `systemctl list-unit-files`:')
                cli.log.error(mm_check.stderr)

        else:
            cli.log.warn("Can't find systemctl to check for ModemManager.")

    else:
        cli.log.info("Assuming {fg_cyan}Windows.")

    # Report a summary of our findings to the user
    if ok:
        cli.log.info('{fg_green}QMK is ready to go')
    else:
        cli.log.info('{fg_yellow}Problems detected, please fix these problems before proceeding.')
        # FIXME(skullydazed): Link to a document about troubleshooting, or discord or something
