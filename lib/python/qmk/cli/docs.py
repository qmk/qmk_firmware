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

    if not shutil.which('npm'):
        cli.log.error('npm is not installed. Please install it and try again.')
        return

    prepare_docs_build_area()
    run_docs_command('start', False)
