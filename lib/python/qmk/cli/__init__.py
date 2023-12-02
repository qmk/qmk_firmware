"""QMK CLI Subcommands

We list each subcommand here explicitly because all the reliable ways of searching for modules are slow and delay startup.
"""
import os
import shlex
import sys
from importlib.util import find_spec
from pathlib import Path
from subprocess import run

from milc import cli, __VERSION__
from milc.questions import yesno

import_names = {
    # A mapping of package name to importable name
    'pep8-naming': 'pep8ext_naming',
    'pyserial': 'serial',
    'pyusb': 'usb.core',
    'qmk-dotty-dict': 'dotty_dict',
    'pillow': 'PIL'
}

safe_commands = [
    # A list of subcommands we always run, even when the module imports fail
    'clone',
    'config',
    'doctor',
    'env',
    'setup',
]

subcommands = [
    'qmk.cli.ci.validate_aliases',
    'qmk.cli.bux',
    'qmk.cli.c2json',
    'qmk.cli.cd',
    'qmk.cli.chibios.confmigrate',
    'qmk.cli.clean',
    'qmk.cli.compile',
    'qmk.cli.docs',
    'qmk.cli.doctor',
    'qmk.cli.find',
    'qmk.cli.flash',
    'qmk.cli.format.c',
    'qmk.cli.format.json',
    'qmk.cli.format.python',
    'qmk.cli.format.text',
    'qmk.cli.generate.api',
    'qmk.cli.generate.autocorrect_data',
    'qmk.cli.generate.compilation_database',
    'qmk.cli.generate.config_h',
    'qmk.cli.generate.develop_pr_list',
    'qmk.cli.generate.dfu_header',
    'qmk.cli.generate.docs',
    'qmk.cli.generate.info_json',
    'qmk.cli.generate.keyboard_c',
    'qmk.cli.generate.keyboard_h',
    'qmk.cli.generate.keycodes',
    'qmk.cli.generate.keycodes_tests',
    'qmk.cli.generate.make_dependencies',
    'qmk.cli.generate.rgb_breathe_table',
    'qmk.cli.generate.rules_mk',
    'qmk.cli.generate.version_h',
    'qmk.cli.git.submodule',
    'qmk.cli.hello',
    'qmk.cli.import.kbfirmware',
    'qmk.cli.import.keyboard',
    'qmk.cli.import.keymap',
    'qmk.cli.info',
    'qmk.cli.json2c',
    'qmk.cli.license_check',
    'qmk.cli.lint',
    'qmk.cli.kle2json',
    'qmk.cli.list.keyboards',
    'qmk.cli.list.keymaps',
    'qmk.cli.list.layouts',
    'qmk.cli.mass_compile',
    'qmk.cli.migrate',
    'qmk.cli.new.keyboard',
    'qmk.cli.new.keymap',
    'qmk.cli.painter',
    'qmk.cli.pytest',
    'qmk.cli.userspace.add',
    'qmk.cli.userspace.compile',
    'qmk.cli.userspace.doctor',
    'qmk.cli.userspace.list',
    'qmk.cli.userspace.remove',
    'qmk.cli.via2json',
]


def _install_deps(requirements):
    """Perform the installation of missing requirements.

    If we detect that we are running in a virtualenv we can't write into we'll use sudo to perform the pip install.
    """
    command = [sys.executable, '-m', 'pip', 'install']

    if sys.prefix != sys.base_prefix:
        # We are in a virtualenv, check to see if we need to use sudo to write to it
        if not os.access(sys.prefix, os.W_OK):
            print('Notice: Using sudo to install modules to location owned by root:', sys.prefix)
            command.insert(0, 'sudo')

    elif not os.access(sys.prefix, os.W_OK):
        # We can't write to sys.prefix, attempt to install locally
        command.append('--user')

    return _run_cmd(*command, '-r', requirements)


def _run_cmd(*command):
    """Run a command in a subshell.
    """
    if 'windows' in cli.platform.lower():
        safecmd = map(shlex.quote, command)
        safecmd = ' '.join(safecmd)
        command = [os.environ['SHELL'], '-c', safecmd]

    return run(command)


def _find_broken_requirements(requirements):
    """ Check if the modules in the given requirements.txt are available.

    Args:

        requirements
            The path to a requirements.txt file

    Returns a list of modules that couldn't be imported
    """
    with Path(requirements).open() as fd:
        broken_modules = []

        for line in fd.readlines():
            line = line.strip().replace('<', '=').replace('>', '=')

            if len(line) == 0 or line[0] == '#' or line.startswith('-r'):
                continue

            if '#' in line:
                line = line.split('#')[0]

            module_name = line.split('=')[0] if '=' in line else line
            module_import = module_name.replace('-', '_')

            # Not every module is importable by its own name.
            if module_name in import_names:
                module_import = import_names[module_name]

            if not find_spec(module_import):
                broken_modules.append(module_name)

        return broken_modules


def _broken_module_imports(requirements):
    """Make sure we can import all the python modules.
    """
    broken_modules = _find_broken_requirements(requirements)

    for module in broken_modules:
        print('Could not find module %s!' % module)

    if broken_modules:
        return True

    return False


def _yesno(*args):
    """Wrapper to only prompt if interactive
    """
    return sys.stdout.isatty() and yesno(*args)


def _eprint(errmsg):
    """Wrapper to print to stderr
    """
    print(errmsg, file=sys.stderr)


# Make sure our python is new enough
#
# Supported version information
#
# Based on the OSes we support these are the minimum python version available by default.
# Last update: 2021 Jan 02
#
# Arch: 3.9
# Debian: 3.7
# Fedora 31: 3.7
# Fedora 32: 3.8
# Fedora 33: 3.9
# FreeBSD: 3.7
# Gentoo: 3.7
# macOS: 3.9 (from homebrew)
# msys2: 3.8
# Slackware: 3.7
# solus: 3.7
# void: 3.9

if sys.version_info[0] != 3 or sys.version_info[1] < 7:
    _eprint('Error: Your Python is too old! Please upgrade to Python 3.7 or later.')
    exit(127)

milc_version = __VERSION__.split('.')

if int(milc_version[0]) < 2 and int(milc_version[1]) < 4:
    requirements = Path('requirements.txt').resolve()

    _eprint(f'Your MILC library is too old! Please upgrade: python3 -m pip install -U -r {str(requirements)}')
    exit(127)

# Make sure we can run binaries in the same directory as our Python interpreter
python_dir = os.path.dirname(sys.executable)

if python_dir not in os.environ['PATH'].split(':'):
    os.environ['PATH'] = ":".join((python_dir, os.environ['PATH']))

# Check to make sure we have all our dependencies
msg_install = f'\nPlease run `{sys.executable} -m pip install -r %s` to install required python dependencies.'
args = sys.argv[1:]
while args and args[0][0] == '-':
    del args[0]

safe_command = args and args[0] in safe_commands

if not safe_command:
    if _broken_module_imports('requirements.txt'):
        if _yesno('Would you like to install the required Python modules?'):
            _install_deps('requirements.txt')
        else:
            _eprint(msg_install % (str(Path('requirements.txt').resolve()),))
            exit(1)

    if cli.config.user.developer and _broken_module_imports('requirements-dev.txt'):
        if _yesno('Would you like to install the required developer Python modules?'):
            _install_deps('requirements-dev.txt')
        elif _yesno('Would you like to disable developer mode?'):
            _run_cmd(sys.argv[0], 'config', 'user.developer=None')
        else:
            _eprint(msg_install % (str(Path('requirements-dev.txt').resolve()),))
            _eprint('You can also turn off developer mode: qmk config user.developer=None')
            exit(1)

# Import our subcommands
for subcommand in subcommands:
    try:
        __import__(subcommand)

    except (ImportError, ModuleNotFoundError) as e:
        if safe_command:
            _eprint(f'Warning: Could not import {subcommand}: {e.__class__.__name__}, {e}')
        else:
            raise
