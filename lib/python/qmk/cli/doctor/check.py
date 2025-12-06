"""Check for specific programs.
"""
from enum import Enum
import shutil
from subprocess import DEVNULL, TimeoutExpired
from tempfile import TemporaryDirectory
from pathlib import Path

from milc import cli
from qmk import submodules
from qmk.commands import find_make


class CheckStatus(Enum):
    OK = 1
    WARNING = 2
    ERROR = 3


WHICH_MAKE = Path(find_make()).name

ESSENTIAL_BINARIES = {
    WHICH_MAKE: {},
    'git': {},
    'dos2unix': {},
    'diff': {},
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


def _check_make_version():
    last_line = ESSENTIAL_BINARIES[WHICH_MAKE]['output'].split('\n')[0]
    version_number = last_line.split()[2]
    cli.log.info('Found %s version %s', WHICH_MAKE, version_number)

    return CheckStatus.OK


def _check_git_version():
    last_line = ESSENTIAL_BINARIES['git']['output'].split('\n')[0]
    version_number = last_line.split()[2]
    cli.log.info('Found git version %s', version_number)

    return CheckStatus.OK


def _check_dos2unix_version():
    last_line = ESSENTIAL_BINARIES['dos2unix']['output'].split('\n')[0]
    version_number = last_line.split()[1]
    cli.log.info('Found dos2unix version %s', version_number)

    return CheckStatus.OK


def _check_diff_version():
    last_line = ESSENTIAL_BINARIES['diff']['output'].split('\n')[0]
    if 'Apple diff' in last_line:
        version_number = last_line
    else:
        version_number = last_line.split()[3]
    cli.log.info('Found diff version %s', version_number)

    return CheckStatus.OK


def _check_arm_gcc_version():
    """Returns True if the arm-none-eabi-gcc version is not known to cause problems.
    """
    version_number = ESSENTIAL_BINARIES['arm-none-eabi-gcc']['output'].strip()
    cli.log.info('Found arm-none-eabi-gcc version %s', version_number)

    # Right now all known ARM versions are ok, so check that it can produce binaries
    return _check_arm_gcc_installation()


def _check_arm_gcc_installation():
    """Returns OK if the arm-none-eabi-gcc is fully installed and can produce binaries.
    """
    with TemporaryDirectory() as temp_dir:
        temp_in = Path(temp_dir) / 'test.c'
        temp_out = Path(temp_dir) / 'test.elf'

        temp_in.write_text('#include <newlib.h>\nint main() { return __NEWLIB__ * __NEWLIB_MINOR__ * __NEWLIB_PATCHLEVEL__; }', encoding='utf-8')

        args = ['arm-none-eabi-gcc', '-mcpu=cortex-m0', '-mthumb', '-mno-thumb-interwork', '--specs=nosys.specs', '--specs=nano.specs', '-x', 'c', '-o', str(temp_out), str(temp_in)]
        result = cli.run(args, stdout=None, stderr=None)
        if result.returncode == 0:
            cli.log.info('Successfully compiled using arm-none-eabi-gcc')
        else:
            cli.log.error(f'Failed to compile a simple program with arm-none-eabi-gcc, return code {result.returncode}')
            cli.log.error(f'Command: {" ".join(args)}')
            return CheckStatus.ERROR

        args = ['arm-none-eabi-size', str(temp_out)]
        result = cli.run(args, stdout=None, stderr=None)
        if result.returncode == 0:
            cli.log.info('Successfully tested arm-none-eabi-binutils using arm-none-eabi-size')
        else:
            cli.log.error(f'Failed to execute arm-none-eabi-size, perhaps corrupt arm-none-eabi-binutils, return code {result.returncode}')
            cli.log.error(f'Command: {" ".join(args)}')
            return CheckStatus.ERROR

        return CheckStatus.OK


def _check_avr_gcc_version():
    """Returns True if the avr-gcc version is not known to cause problems.
    """
    version_number = ESSENTIAL_BINARIES['avr-gcc']['output'].strip()
    cli.log.info('Found avr-gcc version %s', version_number)

    # Right now all known AVR versions are ok, so check that it can produce binaries
    return _check_avr_gcc_installation()


def _check_avr_gcc_installation():
    """Returns OK if the avr-gcc is fully installed and can produce binaries.
    """
    with TemporaryDirectory() as temp_dir:
        temp_in = Path(temp_dir) / 'test.c'
        temp_out = Path(temp_dir) / 'test.elf'

        temp_in.write_text('int main() { return 0; }', encoding='utf-8')

        args = ['avr-gcc', '-mmcu=atmega32u4', '-x', 'c', '-o', str(temp_out), str(temp_in)]
        result = cli.run(args, stdout=None, stderr=None)
        if result.returncode == 0:
            cli.log.info('Successfully compiled using avr-gcc')
        else:
            cli.log.error(f'Failed to compile a simple program with avr-gcc, return code {result.returncode}')
            cli.log.error(f'Command: {" ".join(args)}')
            return CheckStatus.ERROR

        args = ['avr-size', str(temp_out)]
        result = cli.run(args, stdout=None, stderr=None)
        if result.returncode == 0:
            cli.log.info('Successfully tested avr-binutils using avr-size')
        else:
            cli.log.error(f'Failed to execute avr-size, perhaps corrupt avr-binutils, return code {result.returncode}')
            cli.log.error(f'Command: {" ".join(args)}')
            return CheckStatus.ERROR

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
    missing_from_path = []

    for binary in sorted(ESSENTIAL_BINARIES):
        try:
            if not is_in_path(binary):
                ok = CheckStatus.ERROR
                missing_from_path.append(binary)
            elif not is_executable(binary):
                ok = CheckStatus.ERROR
        except TimeoutExpired:
            cli.log.debug('Timeout checking %s', binary)
            if ok != CheckStatus.ERROR:
                ok = CheckStatus.WARNING

    if missing_from_path:
        location_noun = 'its location' if len(missing_from_path) == 1 else 'their locations'
        cli.log.error('{fg_red}' + ', '.join(missing_from_path) + f' may need to be installed, or {location_noun} added to your path.')

    return ok


def check_binary_versions():
    """Check the versions of ESSENTIAL_BINARIES
    """
    checks = {
        WHICH_MAKE: _check_make_version,
        'git': _check_git_version,
        'dos2unix': _check_dos2unix_version,
        'diff': _check_diff_version,
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


def is_in_path(command):
    """Returns True if command is found in the path.
    """
    if shutil.which(command) is None:
        cli.log.error("{fg_red}Can't find %s in your path.", command)
        return False
    return True


def is_executable(command):
    """Returns True if command can be executed.
    """
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
