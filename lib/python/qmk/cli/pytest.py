"""QMK Python Unit Tests

QMK script to run unit and integration tests against our python code.
"""
import subprocess
#import os
#import sys

from milc import cli


@cli.subcommand('QMK Python Unit Tests')
def pytest(cli):
    """Run several linting/testing commands.
    """
    #parrent_env = os.environ.copy()
    #parrent_env["PYTHONPATH"] = ":".join(sys.path[1:])

    flake8 = subprocess.run(['flake8', 'lib/python', 'bin/qmk'])
    nose2 = subprocess.run(['nose2', '-v'])#, env=parrent_env)
    return flake8.returncode | nose2.returncode
