"""Build QMK documentation locally
"""
import shutil
from pathlib import Path
from subprocess import DEVNULL

from milc import cli

DOCS_PATH = Path('docs/')
BUILD_PATH = Path('.build/')


@cli.subcommand('Build QMK documentation.', hidden=False if cli.config.user.developer else True)
def generate_docs(cli):
    """Invoke the docs generation process

    TODO(unclaimed):
        * [ ] Add a real build step... something static docs
    """

    if BUILD_PATH.exists():
        shutil.rmtree(BUILD_PATH / 'docs')

    shutil.copytree(DOCS_PATH, BUILD_PATH / 'docs')

    # When not verbose we want to hide all output
    args = {
        'capture_output': False if cli.config.general.verbose else True,
        'check': True,
        'stdin': DEVNULL,
    }

    cli.log.info('Generating internal docs...')

    # Generate internal docs
    cli.run(['doxygen', 'Doxyfile'], **args)
    cli.run(['moxygen', '-q', '-g', '-o', BUILD_PATH / 'docs/internals_%s.md', BUILD_PATH / 'doxygen/xml'], **args)

    cli.log.info('Successfully generated internal docs to %s.', BUILD_PATH / 'docs')
