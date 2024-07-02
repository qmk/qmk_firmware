"""Serve QMK documentation locally
"""
import shutil
from qmk.docs import prepare_docs_build_area, run_docs_command

from milc import cli


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

    if not cli.config.general.verbose:
        cli.log.info('Serving docs at http://localhost:5173/ (Ctrl+C to stop)')
    run_docs_command('run', 'docs:dev')
