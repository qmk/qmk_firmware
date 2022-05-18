"""QMK Python Unit Tests

QMK script to run unit and integration tests against our python code.
"""
from subprocess import DEVNULL

from milc import cli


@cli.argument('-t', '--test', arg_only=True, action='append', default=[], help="Mapped to nose2 'testNames' positional argument - https://docs.nose2.io/en/latest/usage.html#specifying-tests-to-run")
@cli.subcommand('QMK Python Unit Tests', hidden=False if cli.config.user.developer else True)
def pytest(cli):
    """Run several linting/testing commands.
    """
    nose2 = cli.run(['nose2', '-v', '-t'
                     'lib/python', *cli.args.test], capture_output=False, stdin=DEVNULL)
    flake8 = cli.run(['flake8', 'lib/python'], capture_output=False, stdin=DEVNULL)

    return flake8.returncode | nose2.returncode
