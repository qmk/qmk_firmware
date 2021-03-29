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
            if module_name == "pep8-naming":
                module_import = "pep8ext_naming"

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
    print('Error: Your Python is too old! Please upgrade to Python 3.7 or later.')
    exit(127)

milc_version = __VERSION__.split('.')

if int(milc_version[0]) < 2 and int(milc_version[1]) < 3:
    from pathlib import Path

    requirements = Path('requirements.txt').resolve()

    print(f'Your MILC library is too old! Please upgrade: python3 -m pip install -U -r {str(requirements)}')
    exit(127)

# Check to make sure we have all our dependencies
msg_install = 'Please run `python3 -m pip install -r %s` to install required python dependencies.'

if _broken_module_imports('requirements.txt'):
    if yesno('Would you like to install the required Python modules?'):
        _run_cmd(sys.executable, '-m', 'pip', 'install', '-r', 'requirements.txt')
    else:
        print()
        print(msg_install % (str(Path('requirements.txt').resolve()),))
        print()
        exit(1)

if cli.config.user.developer and _broken_module_imports('requirements-dev.txt'):
    if yesno('Would you like to install the required developer Python modules?'):
        _run_cmd(sys.executable, '-m', 'pip', 'install', '-r', 'requirements.txt')
    else:
        print()
        print(msg_install % (str(Path('requirements-dev.txt').resolve()),))
        print('You can also turn off developer mode: qmk config user.developer=None')
        print()
        exit(1)

# Import our subcommands
from . import c2json
from . import cformat
from . import chibios
from . import clean
from . import compile
from . import config
from . import docs
from . import doctor
from . import fileformat
from . import flash
from . import format
from . import generate
from . import hello
from . import info
from . import json2c
from . import lint
from . import list
from . import kle2json
from . import multibuild
from . import new
from . import pyformat
from . import pytest
