"""Serve QMK documentation locally
"""
import shutil
from qmk.docs import prepare_docs_build_area, run_docs_command

from milc import cli


@cli.argument('-p', '--port', default=8936, type=int, help='Port number to use.')
@cli.argument('-b', '--browser', action='store_true', help='Open the docs in the default browser.')
@cli.subcommand('Run a local webserver for QMK documentation.', hidden=False if cli.config.user.developer else True)
def docs(cli):
    """Spin up a local HTTP server for the QMK docs.
    """

    if not shutil.which('doxygen'):
        cli.log.error('doxygen is not installed. Please install it and try again.')
        return

    if not shutil.which('yarn'):
        cli.log.error('yarn is not installed. Please install it and try again.')
        return

    if not prepare_docs_build_area(is_production=False):
        return False

    cmd = ['docs:dev', '--port', f'{cli.args.port}']
    if cli.args.browser:
        cmd.append('--open')
    run_docs_command('run', cmd)
