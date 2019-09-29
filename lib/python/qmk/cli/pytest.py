"""QMK Python Unit Tests

QMK script to run unit and integration tests against our python code.
"""
import sys
from milc import cli


@cli.subcommand('QMK Python Unit Tests')
def pytest(cli):
    """Use nose2 to run unittests
    """
    try:
        import nose2

    except ImportError:
        cli.log.error('Could not import nose2! Please install it with {fg_cyan}pip3 install nose2')
        return False

    nose2.discover(argv=['nose2', '-v'])
