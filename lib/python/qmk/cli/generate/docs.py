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

    if not shutil.which('npm'):
        cli.log.error('npm is not installed. Please install it and try again.')
        return

    prepare_docs_build_area()

    cli.log.info('Building docusaurus docs')
    run_docs_command('build')
    cli.log.info('Successfully generated docs to %s.', BUILD_DOCS_PATH)

    if cli.args.serve:
        run_docs_command('serve', False)
