"""QMK Python Doctor

Check up for QMK environment.
"""
import platform
import shutil
import subprocess
import glob

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
    binaries = ['dfu-programmer', 'avrdude', 'dfu-util', 'avr-gcc', 'arm-none-eabi-gcc', 'bin/qmk']
    ok = True

    for binary in binaries:
        res = shutil.which(binary)
        if res is None:
            cli.log.error("{fg_red}QMK can't find %s in your path.", binary)
            ok = False
        else:
            check = subprocess.run([binary, '--version'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=5)
            if check.returncode in [0, 1]:
                cli.log.info('Found {fg_cyan}%s', binary)
            else:
                cli.log.error("{fg_red}Can't run `%s --version`", binary)
                ok = False

    # Determine our OS and run platform specific tests
    OS = platform.system()  # noqa (N806), uppercase name is ok in this instance

    if OS == "Darwin":
        cli.log.info("Detected {fg_cyan}macOS.")

    elif OS == "Linux":
        cli.log.info("Detected {fg_cyan}Linux.")
        # Checking for udev rules
        udev_dir = "/etc/udev/rules.d/"
        # These are the recommended udev rules
        desired_rules = {"dfu": {'SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff4", MODE:="0666"',
                                 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ffb", MODE:="0666"',
                                 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff0", MODE:="0666"'},
                         "tmk": {'SUBSYSTEMS=="usb", ATTRS{idVendor}=="feed", MODE:="0666"'},
                         "input-club": {'SUBSYSTEMS=="usb", ATTRS{idVendor}=="1c11", MODE:="0666"'},
                         "stm32": {'SUBSYSTEMS=="usb", ATTRS{idVendor}=="1eaf", ATTRS{idProduct}=="0003", MODE:="0666"',
                                   'SUBSYSTEMS=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="df11", MODE:="0666"'},
                         "caterina": {'ATTRS{idVendor}=="2a03", ENV{ID_MM_DEVICE_IGNORE}="1"',
                                      'ATTRS{idVendor}=="2341", ENV{ID_MM_DEVICE_IGNORE}="1"'}}
        if os.path.exists(udev_dir):
            udev_rules = [rule for rule in glob.iglob(os.path.join(udev_dir, "*.rules")) if os.path.isfile(rule)]
            # Collect all rules from the config files
            current_rules = set()
            for rule in udev_rules:
                with open(rule, "r") as fd:
                    for line in fd.readlines():
                        line = line.strip()
                        if not line.startswith("#") and len(line):
                            current_rules.add(line)

            # Check if the desired rules are among the currently present rules
            for bootloader, rules in desired_rules.items():
                if not rules.issubset(current_rules):
                    # If the rules for catalina are not present, check if ModemManager is running
                    if bootloader == "caterina":
                        if shutil.which("systemctl"):
                            mm_check = subprocess.run(["systemctl", "--quiet", "is-active", "ModemManager.service"], timeout=10)
                            if mm_check.returncode == 0:
                                ok = False
                                cli.log.warn("{bg_yellow}Detected ModemManager without udev rules. Please either disable it or set the appropriate udev rules if you are using a Pro Micro.")
                        else:
                            cli.log.warn("Can't find systemctl to check for ModemManager.")
                    else:
                        cli.log.warn("{bg_yellow}Missing udev rules for '%s' boards. You'll need to use `sudo` in order to flash them.", bootloader)

    else:
        cli.log.info("Assuming {fg_cyan}Windows.")

    # Report a summary of our findings to the user
    if ok:
        cli.log.info('{fg_green}QMK is ready to go')
    else:
        cli.log.info('{fg_yellow}Problems detected, please fix these problems before proceeding.')
        # FIXME(skullydazed): Link to a document about troubleshooting, or discord or something
