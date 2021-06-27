"""QMK Python Unit Tests

QMK script to run unit and integration tests against our python code.
"""
from subprocess import DEVNULL

from milc import cli


@cli.subcommand('QMK Python Unit Tests', hidden=False if cli.config.user.developer else True)
def pytest(cli):
    """Run several linting/testing commands.
    """
    nose2 = cli.run(['nose2', '-v'], capture_output=False, stdin=DEVNULL)
    flake8 = cli.run(['flake8', 'lib/python', 'bin/qmk'], capture_output=False, stdin=DEVNULL)

    return flake8.returncode | nose2.returncode
