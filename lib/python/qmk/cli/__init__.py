"""QMK CLI Subcommands

We list each subcommand here explicitly because all the reliable ways of searching for modules are slow and delay startup.
"""
import sys

from milc import cli

from . import cformat
from . import compile
from . import config
from . import doctor
from . import flash
from . import hello
from . import info
from . import json
from . import json2c
from . import list
from . import kle2json
from . import new
from . import pyformat
from . import pytest

if sys.version_info[0] != 3 or sys.version_info[1] < 6:
    cli.log.error('Your Python is too old! Please upgrade to Python 3.6 or later.')
    exit(127)
