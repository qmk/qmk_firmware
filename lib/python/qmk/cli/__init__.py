"""QMK CLI Subcommands

We list each subcommand here explicitly because all the reliable ways of searching for modules are slow and delay startup.
"""
from milc import cli

from . import cformat
from . import compile
from . import config
from . import docs
from . import doctor
from . import flash
from . import hello
from . import json
from . import json2c
from . import list
from . import kle2json
from . import new
from . import pyformat
from . import pytest

if not hasattr(cli, 'config_source'):
    cli.log.warning("Your QMK CLI is out of date. Please upgrade with `pip3 install --upgrade qmk` or by using your package manager.")
