"""QMK Python Unit Tests

QMK script to run unit and integration tests against our python code.
"""
from milc import cli


@cli.entrypoint('QMK Python Unit Tests')
def main(cli):
    """Use nose2 to run unittests
    """
    try:
        import nose2
    except ImportError:
        cli.log.error('Could not import nose2! Please install it with {fg_cyan}pip3 install nose2')
        return False

    nose2.discover()
