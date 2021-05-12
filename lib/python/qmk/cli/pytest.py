"""QMK Python Unit Tests

QMK script to run unit and integration tests against our python code.
"""
import subprocess

from milc import cli


@cli.subcommand('QMK Python Unit Tests', hidden=False if cli.config.user.developer else True)
def pytest(cli):
    """Run several linting/testing commands.
    """
    nose2 = subprocess.run(['nose2', '-v'])
    flake8 = subprocess.run(['flake8', 'lib/python', 'bin/qmk'])

    return flake8.returncode | nose2.returncode
