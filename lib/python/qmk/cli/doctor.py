"""QMK Doctor

Check out the user's QMK environment and make sure it's ready to compile.
"""
import platform
import shutil
import subprocess
from pathlib import Path

from milc import cli
from qmk import submodules
from qmk.questions import yesno

ESSENTIAL_BINARIES = {
    'dfu-programmer': {},
    'avrdude': {},
    'dfu-util': {},
    'avr-gcc': {},
    'arm-none-eabi-gcc': {},
    'bin/qmk': {},
}
ESSENTIAL_SUBMODULES = ['lib/chibios', 'lib/lufa']


def _udev_rule(vid, pid=None):
    """ Helper function that return udev rules
    """
    if pid:
        return 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="%s", ATTRS{idProduct}=="%s", MODE:="0666"' % (vid, pid)
    else:
        return 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="%s", MODE:="0666"' % vid


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
    ok = True

    for submodule in submodules.status().values():
        if submodule['status'] is None:
            if submodule['name'] in ESSENTIAL_SUBMODULES:
                cli.log.error('Submodule %s has not yet been cloned!', submodule['name'])
                ok = False
            else:
                cli.log.warn('Submodule %s is not available.', submodule['name'])
        elif not submodule['status']:
            if submodule['name'] in ESSENTIAL_SUBMODULES:
                cli.log.warn('Submodule %s is not up to date!')

    return ok


def check_udev_rules():
    """Make sure the udev rules look good.
    """
    ok = True
    udev_dir = Path("/etc/udev/rules.d/")
    desired_rules = {
        'dfu': {_udev_rule("03eb", "2ff4"), _udev_rule("03eb", "2ffb"), _udev_rule("03eb", "2ff0")},
        'tmk': {_udev_rule("feed")},
        'input_club': {_udev_rule("1c11")},
        'stm32': {_udev_rule("1eaf", "0003"), _udev_rule("0483", "df11")},
        'caterina': {'ATTRS{idVendor}=="2a03", ENV{ID_MM_DEVICE_IGNORE}="1"', 'ATTRS{idVendor}=="2341", ENV{ID_MM_DEVICE_IGNORE}="1"'},
    }

    if udev_dir.exists():
        udev_rules = [str(rule_file) for rule_file in udev_dir.glob('*.rules')]
        current_rules = set()

        # Collect all rules from the config files
        for rule_file in udev_rules:
            with open(rule_file, "r") as fd:
                for line in fd.readlines():
                    line = line.strip()
                    if not line.startswith("#") and len(line):
                        current_rules.add(line)

        # Check if the desired rules are among the currently present rules
        for bootloader, rules in desired_rules.items():
            if not rules.issubset(current_rules):
                # If the rules for catalina are not present, check if ModemManager is running
                if bootloader == "caterina":
                    if check_modem_manager():
                        ok = False
                        cli.log.warn("{bg_yellow}Detected ModemManager without udev rules. Please either disable it or set the appropriate udev rules if you are using a Pro Micro.")
                else:
                    cli.log.warn("{bg_yellow}Missing udev rules for '%s' boards. You'll need to use `sudo` in order to flash them.", bootloader)

    return ok


def check_modem_manager():
    """Returns True if ModemManager is running.
    """
    if shutil.which("systemctl"):
        mm_check = subprocess.run(["systemctl", "--quiet", "is-active", "ModemManager.service"], timeout=10)
        if mm_check.returncode == 0:
            return True

    else:
        cli.log.warn("Can't find systemctl to check for ModemManager.")


def is_executable(command):
    """Returns True if command exists and can be executed.
    """
    # Make sure the command is in the path.
    res = shutil.which(command)
    if res is None:
        cli.log.error("{fg_red}Can't find %s in your path.", command)
        return False

    # Make sure the command can be executed
    check = subprocess.run([command, '--version'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=5, universal_newlines=True)
    ESSENTIAL_BINARIES[command]['output'] = check.stdout

    if check.returncode in [0, 1]:  # Older versions of dfu-programmer exit 1
        cli.log.debug('Found {fg_cyan}%s', command)
        return True

    cli.log.error("{fg_red}Can't run `%s --version`", command)
    return False


def os_test_linux():
    """Run the Linux specific tests.
    """
    cli.log.info("Detected {fg_cyan}Linux.")
    ok = True

    if not check_udev_rules():
        ok = False

    return ok


def os_test_macos():
    """Run the Mac specific tests.
    """
    cli.log.info("Detected {fg_cyan}macOS.")

    return True


def os_test_windows():
    """Run the Windows specific tests.
    """
    cli.log.info("Detected {fg_cyan}Windows.")

    return True


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
    ok = True

    # Determine our OS and run platform specific tests
    OS = platform.platform().lower()  # noqa (N806), uppercase name is ok in this instance

    if 'darwin' in OS or 'macos' in OS:
        if not os_test_macos():
            ok = False
    elif 'linux' in OS:
        if not os_test_linux():
            ok = False
    elif 'windows' in OS:
        if not os_test_windows():
            ok = False
    else:
        cli.log.error('Unsupported OS detected: %s', OS)
        ok = False

    # Make sure the basic CLI tools we need are available and can be executed.
    bin_ok = check_binaries()

    if not bin_ok:
        if yesno('Would you like to install dependencies?', default=True):
            subprocess.run(['util/qmk_install.sh'])
            bin_ok = check_binaries()

    if bin_ok:
        cli.log.info('All dependencies are installed.')
    else:
        ok = False

    # Make sure the tools are at the correct version
    if 'output' in ESSENTIAL_BINARIES['avr-gcc']:
        first_line = ESSENTIAL_BINARIES['avr-gcc']['output'].split('\n')[0]
        version_number = first_line.split()[2]
        major, minor, rest = version_number.split('.', 2)
        if int(major) > 8:
            cli.log.error('We do not recommend avr-gcc newer than 8. Recommend you downgrade.')
        else:
            cli.log.info('Found avr-gcc version %s', version_number)

    if 'output' in ESSENTIAL_BINARIES['arm-none-eabi-gcc']:
        first_line = ESSENTIAL_BINARIES['arm-none-eabi-gcc']['output'].split('\n')[0]
        second_half = first_line.split(')', 1)[1].strip()
        version_number = second_half.split()[0]
        cli.log.info('Found arm-none-eabi-gcc version %s', version_number)

    # Check out the QMK submodules
    sub_ok = check_submodules()

    if sub_ok:
        cli.log.info('Submodules are up to date.')
    else:
        if yesno('Would you like to clone the submodules?', default=True):
            submodules.update()
            sub_ok = check_submodules()

        if not sub_ok:
            ok = False

    # Report a summary of our findings to the user
    if ok:
        cli.log.info('{fg_green}QMK is ready to go')
    else:
        cli.log.info('{fg_yellow}Problems detected, please fix these problems before proceeding.')
        # FIXME(skullydazed/unclaimed): Link to a document about troubleshooting, or discord or something
