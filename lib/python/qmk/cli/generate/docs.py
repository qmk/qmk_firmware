"""Build QMK documentation locally
"""
from qmk.docs import prepare_docs_build_area, run_docs_command, BUILD_DOCS_PATH

from milc import cli

@cli.argument('-s', '--serve', arg_only=True, action='store_true', help="Serves the generated docs once built.")
@cli.subcommand('Build QMK documentation.', hidden=False if cli.config.user.developer else True)
def generate_docs(cli):
    """Invoke the docs generation process

    TODO(unclaimed):
        * [ ] Add a real build step... something static docs
    """

    prepare_docs_build_area()

    cli.log.info('Building docusaurus docs')
    run_docs_command('build')
    cli.log.info('Successfully generated docs to %s.', BUILD_DOCS_PATH)

    if cli.args.serve:
        run_docs_command('serve', False)
