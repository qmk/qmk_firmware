"""Check for specific programs.
"""
from enum import Enum
import re
import shutil
from subprocess import DEVNULL, TimeoutExpired

from milc import cli
from qmk import submodules


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
}


def _parse_gcc_version(version):
    m = re.match(r"(\d+)(?:\.(\d+))?(?:\.(\d+))?", version)

    return {
        'major': int(m.group(1)),
        'minor': int(m.group(2)) if m.group(2) else 0,
        'patch': int(m.group(3)) if m.group(3) else 0,
    }


def _check_arm_gcc_version():
    """Returns True if the arm-none-eabi-gcc version is not known to cause problems.
    """
    version_number = ESSENTIAL_BINARIES['arm-none-eabi-gcc']['output'].strip()
    cli.log.info('Found arm-none-eabi-gcc version %s', version_number)

    return CheckStatus.OK  # Right now all known arm versions are ok


def _check_avr_gcc_version():
    """Returns True if the avr-gcc version is not known to cause problems.
    """
    version_number = ESSENTIAL_BINARIES['avr-gcc']['output'].strip()
    cli.log.info('Found avr-gcc version %s', version_number)

    return CheckStatus.OK


def _check_avrdude_version():
    last_line = ESSENTIAL_BINARIES['avrdude']['output'].split('\n')[-2]
    version_number = last_line.split()[2][:-1]
    cli.log.info('Found avrdude version %s', version_number)

    return CheckStatus.OK


def _check_dfu_util_version():
    first_line = ESSENTIAL_BINARIES['dfu-util']['output'].split('\n')[0]
    version_number = first_line.split()[1]
    cli.log.info('Found dfu-util version %s', version_number)

    return CheckStatus.OK


def _check_dfu_programmer_version():
    first_line = ESSENTIAL_BINARIES['dfu-programmer']['output'].split('\n')[0]
    version_number = first_line.split()[1]
    cli.log.info('Found dfu-programmer version %s', version_number)

    return CheckStatus.OK


def check_binaries():
    """Iterates through ESSENTIAL_BINARIES and tests them.
    """
    ok = CheckStatus.OK

    for binary in sorted(ESSENTIAL_BINARIES):
        try:
            if not is_executable(binary):
                ok = CheckStatus.ERROR
        except TimeoutExpired:
            cli.log.debug('Timeout checking %s', binary)
            if ok != CheckStatus.ERROR:
                ok = CheckStatus.WARNING

    return ok


def check_binary_versions():
    """Check the versions of ESSENTIAL_BINARIES
    """
    checks = {
        'arm-none-eabi-gcc': _check_arm_gcc_version,
        'avr-gcc': _check_avr_gcc_version,
        'avrdude': _check_avrdude_version,
        'dfu-util': _check_dfu_util_version,
        'dfu-programmer': _check_dfu_programmer_version,
    }

    versions = []
    for binary in sorted(ESSENTIAL_BINARIES):
        if 'output' not in ESSENTIAL_BINARIES[binary]:
            cli.log.warning('Unknown version for %s', binary)
            versions.append(CheckStatus.WARNING)
            continue

        check = checks[binary]
        versions.append(check())
    return versions


def check_submodules():
    """Iterates through all submodules to make sure they're cloned and up to date.
    """
    for submodule in submodules.status().values():
        if submodule['status'] is None:
            return CheckStatus.ERROR
        elif not submodule['status']:
            return CheckStatus.WARNING

    return CheckStatus.OK


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
    check = cli.run([command, version_arg], combined_output=True, stdin=DEVNULL, timeout=5)

    ESSENTIAL_BINARIES[command]['output'] = check.stdout

    if check.returncode in [0, 1]:  # Older versions of dfu-programmer exit 1
        cli.log.debug('Found {fg_cyan}%s', command)
        return True

    cli.log.error("{fg_red}Can't run `%s %s`", command, version_arg)
    return False


def release_info(file='/etc/os-release'):
    """Parse release info to dict
    """
    ret = {}
    try:
        with open(file) as f:
            for line in f:
                if '=' in line:
                    key, value = map(str.strip, line.split('=', 1))
                    if value.startswith('"') and value.endswith('"'):
                        value = value[1:-1]
                    ret[key] = value
    except (PermissionError, FileNotFoundError):
        pass

    return ret
