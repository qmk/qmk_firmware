"""QMK Doctor

Check out the user's QMK environment and make sure it's ready to compile.
"""
import platform
import re
import shutil
import subprocess
from pathlib import Path
from enum import Enum

from milc import cli
from milc.questions import yesno
from qmk import submodules
from qmk.constants import QMK_FIRMWARE
from qmk.commands import run


class CheckStatus(Enum):
    OK = 1
    WARNING = 2
    ERROR = 3


ESSENTIAL_BINARIES = {
    'dfu-programmer': {},
    'avrdude': {},
    'dfu-util': {},
    'avr-gcc': {
        'version_arg': '-dumpversion'
    },
    'arm-none-eabi-gcc': {
        'version_arg': '-dumpversion'
    },
    'bin/qmk': {},
}


def _udev_rule(vid, pid=None, *args):
    """ Helper function that return udev rules
    """
    rule = ""
    if pid:
        rule = 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="%s", ATTRS{idProduct}=="%s", TAG+="uaccess"' % (
            vid,
            pid,
        )
    else:
        rule = 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="%s", TAG+="uaccess"' % vid
    if args:
        rule = ', '.join([rule, *args])
    return rule


def _deprecated_udev_rule(vid, pid=None):
    """ Helper function that return udev rules

    Note: these are no longer the recommended rules, this is just used to check for them
    """
    if pid:
        return 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="%s", ATTRS{idProduct}=="%s", MODE:="0666"' % (vid, pid)
    else:
        return 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="%s", MODE:="0666"' % vid


def parse_gcc_version(version):
    m = re.match(r"(\d+)(?:\.(\d+))?(?:\.(\d+))?", version)

    return {
        'major': int(m.group(1)),
        'minor': int(m.group(2)) if m.group(2) else 0,
        'patch': int(m.group(3)) if m.group(3) else 0,
    }


def check_arm_gcc_version():
    """Returns True if the arm-none-eabi-gcc version is not known to cause problems.
    """
    if 'output' in ESSENTIAL_BINARIES['arm-none-eabi-gcc']:
        version_number = ESSENTIAL_BINARIES['arm-none-eabi-gcc']['output'].strip()
        cli.log.info('Found arm-none-eabi-gcc version %s', version_number)

    return CheckStatus.OK  # Right now all known arm versions are ok


def check_avr_gcc_version():
    """Returns True if the avr-gcc version is not known to cause problems.
    """
    rc = CheckStatus.ERROR
    if 'output' in ESSENTIAL_BINARIES['avr-gcc']:
        version_number = ESSENTIAL_BINARIES['avr-gcc']['output'].strip()

        cli.log.info('Found avr-gcc version %s', version_number)
        rc = CheckStatus.OK

        parsed_version = parse_gcc_version(version_number)
        if parsed_version['major'] > 8:
            cli.log.warning('{fg_yellow}We do not recommend avr-gcc newer than 8. Downgrading to 8.x is recommended.')
            rc = CheckStatus.WARNING

    return rc


def check_avrdude_version():
    if 'output' in ESSENTIAL_BINARIES['avrdude']:
        last_line = ESSENTIAL_BINARIES['avrdude']['output'].split('\n')[-2]
        version_number = last_line.split()[2][:-1]
        cli.log.info('Found avrdude version %s', version_number)

    return CheckStatus.OK


def check_dfu_util_version():
    if 'output' in ESSENTIAL_BINARIES['dfu-util']:
        first_line = ESSENTIAL_BINARIES['dfu-util']['output'].split('\n')[0]
        version_number = first_line.split()[1]
        cli.log.info('Found dfu-util version %s', version_number)

    return CheckStatus.OK


def check_dfu_programmer_version():
    if 'output' in ESSENTIAL_BINARIES['dfu-programmer']:
        first_line = ESSENTIAL_BINARIES['dfu-programmer']['output'].split('\n')[0]
        version_number = first_line.split()[1]
        cli.log.info('Found dfu-programmer version %s', version_number)

    return CheckStatus.OK


def check_binaries():
    """Iterates through ESSENTIAL_BINARIES and tests them.
    """
    ok = True

    for binary in sorted(ESSENTIAL_BINARIES):
        if not is_executable(binary):
            ok = False

    return ok


def check_submodules():
    """Iterates through all submodules to make sure they're cloned and up to date.
    """
    for submodule in submodules.status().values():
        if submodule['status'] is None:
            cli.log.error('Submodule %s has not yet been cloned!', submodule['name'])
            return CheckStatus.ERROR
        elif not submodule['status']:
            cli.log.warning('Submodule %s is not up to date!', submodule['name'])
            return CheckStatus.WARNING

    return CheckStatus.OK


def check_udev_rules():
    """Make sure the udev rules look good.
    """
    rc = CheckStatus.OK
    udev_dir = Path("/etc/udev/rules.d/")
    desired_rules = {
        'atmel-dfu': {
            _udev_rule("03eb", "2fef"),  # ATmega16U2
            _udev_rule("03eb", "2ff0"),  # ATmega32U2
            _udev_rule("03eb", "2ff3"),  # ATmega16U4
            _udev_rule("03eb", "2ff4"),  # ATmega32U4
            _udev_rule("03eb", "2ff9"),  # AT90USB64
            _udev_rule("03eb", "2ffb")  # AT90USB128
        },
        'kiibohd': {_udev_rule("1c11", "b007")},
        'stm32': {
            _udev_rule("1eaf", "0003"),  # STM32duino
            _udev_rule("0483", "df11")  # STM32 DFU
        },
        'bootloadhid': {_udev_rule("16c0", "05df")},
        'usbasploader': {_udev_rule("16c0", "05dc")},
        'massdrop': {_udev_rule("03eb", "6124", 'ENV{ID_MM_DEVICE_IGNORE}="1"')},
        'caterina': {
            # Spark Fun Electronics
            _udev_rule("1b4f", "9203", 'ENV{ID_MM_DEVICE_IGNORE}="1"'),  # Pro Micro 3V3/8MHz
            _udev_rule("1b4f", "9205", 'ENV{ID_MM_DEVICE_IGNORE}="1"'),  # Pro Micro 5V/16MHz
            _udev_rule("1b4f", "9207", 'ENV{ID_MM_DEVICE_IGNORE}="1"'),  # LilyPad 3V3/8MHz (and some Pro Micro clones)
            # Pololu EleCTRONICS
            _udev_rule("1ffb", "0101", 'ENV{ID_MM_DEVICE_IGNORE}="1"'),  # A-Star 32U4
            # Arduino SA
            _udev_rule("2341", "0036", 'ENV{ID_MM_DEVICE_IGNORE}="1"'),  # Leonardo
            _udev_rule("2341", "0037", 'ENV{ID_MM_DEVICE_IGNORE}="1"'),  # Micro
            # Adafruit INDUSTRIES llC
            _udev_rule("239a", "000c", 'ENV{ID_MM_DEVICE_IGNORE}="1"'),  # Feather 32U4
            _udev_rule("239a", "000d", 'ENV{ID_MM_DEVICE_IGNORE}="1"'),  # ItsyBitsy 32U4 3V3/8MHz
            _udev_rule("239a", "000e", 'ENV{ID_MM_DEVICE_IGNORE}="1"'),  # ItsyBitsy 32U4 5V/16MHz
            # dog hunter ag
            _udev_rule("2a03", "0036", 'ENV{ID_MM_DEVICE_IGNORE}="1"'),  # Leonardo
            _udev_rule("2a03", "0037", 'ENV{ID_MM_DEVICE_IGNORE}="1"')  # Micro
        }
    }

    # These rules are no longer recommended, only use them to check for their presence.
    deprecated_rules = {
        'atmel-dfu': {_deprecated_udev_rule("03eb", "2ff4"), _deprecated_udev_rule("03eb", "2ffb"), _deprecated_udev_rule("03eb", "2ff0")},
        'kiibohd': {_deprecated_udev_rule("1c11")},
        'stm32': {_deprecated_udev_rule("1eaf", "0003"), _deprecated_udev_rule("0483", "df11")},
        'bootloadhid': {_deprecated_udev_rule("16c0", "05df")},
        'caterina': {'ATTRS{idVendor}=="2a03", ENV{ID_MM_DEVICE_IGNORE}="1"', 'ATTRS{idVendor}=="2341", ENV{ID_MM_DEVICE_IGNORE}="1"'},
        'tmk': {_deprecated_udev_rule("feed")}
    }

    if udev_dir.exists():
        udev_rules = [rule_file for rule_file in udev_dir.glob('*.rules')]
        current_rules = set()

        # Collect all rules from the config files
        for rule_file in udev_rules:
            for line in rule_file.read_text().split('\n'):
                line = line.strip()
                if not line.startswith("#") and len(line):
                    current_rules.add(line)

        # Check if the desired rules are among the currently present rules
        for bootloader, rules in desired_rules.items():
            if not rules.issubset(current_rules):
                deprecated_rule = deprecated_rules.get(bootloader)
                if deprecated_rule and deprecated_rule.issubset(current_rules):
                    cli.log.warning("{fg_yellow}Found old, deprecated udev rules for '%s' boards. The new rules on https://docs.qmk.fm/#/faq_build?id=linux-udev-rules offer better security with the same functionality.", bootloader)
                else:
                    # For caterina, check if ModemManager is running
                    if bootloader == "caterina":
                        if check_modem_manager():
                            rc = CheckStatus.WARNING
                            cli.log.warning("{fg_yellow}Detected ModemManager without the necessary udev rules. Please either disable it or set the appropriate udev rules if you are using a Pro Micro.")
                    rc = CheckStatus.WARNING
                    cli.log.warning("{fg_yellow}Missing or outdated udev rules for '%s' boards. Run 'sudo cp %s/util/udev/50-qmk.rules /etc/udev/rules.d/'.", bootloader, QMK_FIRMWARE)

    else:
        cli.log.warning("{fg_yellow}'%s' does not exist. Skipping udev rule checking...", udev_dir)

    return rc


def check_systemd():
    """Check if it's a systemd system
    """
    return bool(shutil.which("systemctl"))


def check_modem_manager():
    """Returns True if ModemManager is running.

    """
    if check_systemd():
        mm_check = run(["systemctl", "--quiet", "is-active", "ModemManager.service"], timeout=10)
        if mm_check.returncode == 0:
            return True
    else:
        """(TODO): Add check for non-systemd systems
        """
    return False


def is_executable(command):
    """Returns True if command exists and can be executed.
    """
    # Make sure the command is in the path.
    res = shutil.which(command)
    if res is None:
        cli.log.error("{fg_red}Can't find %s in your path.", command)
        return False

    # Make sure the command can be executed
    version_arg = ESSENTIAL_BINARIES[command].get('version_arg', '--version')
    check = run([command, version_arg], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=5, universal_newlines=True)

    ESSENTIAL_BINARIES[command]['output'] = check.stdout

    if check.returncode in [0, 1]:  # Older versions of dfu-programmer exit 1
        cli.log.debug('Found {fg_cyan}%s', command)
        return True

    cli.log.error("{fg_red}Can't run `%s %s`", command, version_arg)
    return False


def os_test_linux():
    """Run the Linux specific tests.
    """
    cli.log.info("Detected {fg_cyan}Linux.")

    return check_udev_rules()


def os_test_macos():
    """Run the Mac specific tests.
    """
    cli.log.info("Detected {fg_cyan}macOS.")

    return CheckStatus.OK


def os_test_windows():
    """Run the Windows specific tests.
    """
    cli.log.info("Detected {fg_cyan}Windows.")

    return CheckStatus.OK


@cli.argument('-y', '--yes', action='store_true', arg_only=True, help='Answer yes to all questions.')
@cli.argument('-n', '--no', action='store_true', arg_only=True, help='Answer no to all questions.')
@cli.subcommand('Basic QMK environment checks')
def doctor(cli):
    """Basic QMK environment checks.

    This is currently very simple, it just checks that all the expected binaries are on your system.

    TODO(unclaimed):
        * [ ] Compile a trivial program with each compiler
    """
    cli.log.info('QMK Doctor is checking your environment.')
    status = CheckStatus.OK

    # Determine our OS and run platform specific tests
    platform_id = platform.platform().lower()

    if 'darwin' in platform_id or 'macos' in platform_id:
        status = os_test_macos()
    elif 'linux' in platform_id:
        status = os_test_linux()
    elif 'windows' in platform_id:
        status = os_test_windows()
    else:
        cli.log.warning('Unsupported OS detected: %s', platform_id)
        status = CheckStatus.WARNING

    cli.log.info('QMK home: {fg_cyan}%s', QMK_FIRMWARE)

    # Make sure the basic CLI tools we need are available and can be executed.
    bin_ok = check_binaries()

    if not bin_ok:
        if yesno('Would you like to install dependencies?', default=True):
            run(['util/qmk_install.sh'])
            bin_ok = check_binaries()

    if bin_ok:
        cli.log.info('All dependencies are installed.')
    else:
        status = CheckStatus.ERROR

    # Make sure the tools are at the correct version
    ver_ok = []
    for check in (check_arm_gcc_version, check_avr_gcc_version, check_avrdude_version, check_dfu_util_version, check_dfu_programmer_version):
        ver_ok.append(check())

    if CheckStatus.ERROR in ver_ok:
        status = CheckStatus.ERROR
    elif CheckStatus.WARNING in ver_ok and status == CheckStatus.OK:
        status = CheckStatus.WARNING

    # Check out the QMK submodules
    sub_ok = check_submodules()

    if sub_ok == CheckStatus.OK:
        cli.log.info('Submodules are up to date.')
    else:
        if yesno('Would you like to clone the submodules?', default=True):
            submodules.update()
            sub_ok = check_submodules()

        if CheckStatus.ERROR in sub_ok:
            status = CheckStatus.ERROR
        elif CheckStatus.WARNING in sub_ok and status == CheckStatus.OK:
            status = CheckStatus.WARNING

    # Report a summary of our findings to the user
    if status == CheckStatus.OK:
        cli.log.info('{fg_green}QMK is ready to go')
        return 0
    elif status == CheckStatus.WARNING:
        cli.log.info('{fg_yellow}QMK is ready to go, but minor problems were found')
        return 1
    else:
        cli.log.info('{fg_red}Major problems detected, please fix these problems before proceeding.')
        cli.log.info('{fg_blue}Check out the FAQ (https://docs.qmk.fm/#/faq_build) or join the QMK Discord (https://discord.gg/Uq7gcHh) for help.')
        return 2
