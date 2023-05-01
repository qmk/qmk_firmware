"""Serve QMK documentation locally
"""
from qmk.docs import prepare_docs_build_area, run_docs_command

from milc import cli


@cli.subcommand('Run a local webserver for QMK documentation.', hidden=False if cli.config.user.developer else True)
def docs(cli):
    """Spin up a local HTTP server for the QMK docs.
    """
    prepare_docs_build_area()
    run_docs_command('start', False)
