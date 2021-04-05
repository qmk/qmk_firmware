"""QMK CLI Subcommands

We list each subcommand here explicitly because all the reliable ways of searching for modules are slow and delay startup.
"""
import sys

from milc import cli

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
from . import new
from . import pyformat
from . import pytest

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
    cli.log.error('Your Python is too old! Please upgrade to Python 3.7 or later.')
    exit(127)
