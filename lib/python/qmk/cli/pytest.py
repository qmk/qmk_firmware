"""QMK Python Unit Tests

QMK script to run unit and integration tests against our python code.
"""
import subprocess

from milc import cli


@cli.subcommand('QMK Python Unit Tests')
def pytest(cli):
    """Run several linting/testing commands.
    """
    flake8 = subprocess.run(['flake8', 'lib/python', 'bin/qmk'])
    nose2 = subprocess.run(['nose2', '-v'])
    return flake8.returncode | nose2.returncode
