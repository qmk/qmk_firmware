"""Build QMK documentation locally
"""
import shutil
from qmk.docs import prepare_docs_build_area, run_docs_command, BUILD_DOCS_PATH

from milc import cli


@cli.argument('-s', '--serve', arg_only=True, action='store_true', help="Serves the generated docs once built.")
@cli.subcommand('Build QMK documentation.', hidden=False if cli.config.user.developer else True)
def generate_docs(cli):
    """Invoke the docs generation process

    TODO(unclaimed):
        * [ ] Add a real build step... something static docs
    """

    if not shutil.which('doxygen'):
        cli.log.error('doxygen is not installed. Please install it and try again.')
        return

    if not shutil.which('yarn'):
        cli.log.error('yarn is not installed. Please install it and try again.')
        return

    if not prepare_docs_build_area(is_production=True):
        return False

    cli.log.info('Building vitepress docs')
    run_docs_command('run', ['docs:build'])
    cli.log.info('Successfully generated docs to %s.', BUILD_DOCS_PATH)

    if cli.args.serve:
        run_docs_command('run', ['docs:preview'])
