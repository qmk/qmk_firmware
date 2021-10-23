"""Check for specific programs.
"""
from enum import Enum
import re
import shutil
from subprocess import DEVNULL

from milc import cli
from qmk import submodules
from qmk.constants import QMK_FIRMWARE


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
    if 'output' in ESSENTIAL_BINARIES['arm-none-eabi-gcc']:
        version_number = ESSENTIAL_BINARIES['arm-none-eabi-gcc']['output'].strip()
        cli.log.info('Found arm-none-eabi-gcc version %s', version_number)

    return CheckStatus.OK  # Right now all known arm versions are ok


def _check_avr_gcc_version():
    """Returns True if the avr-gcc version is not known to cause problems.
    """
    rc = CheckStatus.ERROR
    if 'output' in ESSENTIAL_BINARIES['avr-gcc']:
        version_number = ESSENTIAL_BINARIES['avr-gcc']['output'].strip()

        cli.log.info('Found avr-gcc version %s', version_number)
        rc = CheckStatus.OK

        parsed_version = _parse_gcc_version(version_number)
        if parsed_version['major'] > 8:
            cli.log.warning('{fg_yellow}We do not recommend avr-gcc newer than 8. Downgrading to 8.x is recommended.')
            rc = CheckStatus.WARNING

    return rc


def _check_avrdude_version():
    if 'output' in ESSENTIAL_BINARIES['avrdude']:
        last_line = ESSENTIAL_BINARIES['avrdude']['output'].split('\n')[-2]
        version_number = last_line.split()[2][:-1]
        cli.log.info('Found avrdude version %s', version_number)

    return CheckStatus.OK


def _check_dfu_util_version():
    if 'output' in ESSENTIAL_BINARIES['dfu-util']:
        first_line = ESSENTIAL_BINARIES['dfu-util']['output'].split('\n')[0]
        version_number = first_line.split()[1]
        cli.log.info('Found dfu-util version %s', version_number)

    return CheckStatus.OK


def _check_dfu_programmer_version():
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


def check_binary_versions():
    """Check the versions of ESSENTIAL_BINARIES
    """
    versions = []
    for check in (_check_arm_gcc_version, _check_avr_gcc_version, _check_avrdude_version, _check_dfu_util_version, _check_dfu_programmer_version):
        versions.append(check())
    return versions


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


def check_git_repo():
    """Checks that the .git directory exists inside QMK_HOME.

    This is a decent enough indicator that the qmk_firmware directory is a
    proper Git repository, rather than a .zip download from GitHub.
    """
    dot_git = QMK_FIRMWARE / '.git'

    return CheckStatus.OK if dot_git.exists() else CheckStatus.WARNING
