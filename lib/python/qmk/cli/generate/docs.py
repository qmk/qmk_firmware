"""Build QMK documentation locally
"""
import shutil
from pathlib import Path
from subprocess import DEVNULL

from milc import cli

DOCS_PATH = Path('docs/')
BUILD_PATH = Path('.build/')
BUILD_DOCS_PATH = BUILD_PATH / 'docs'
DOXYGEN_PATH = BUILD_PATH / 'doxygen'
MOXYGEN_PATH = BUILD_DOCS_PATH / 'internals'


@cli.subcommand('Build QMK documentation.', hidden=False if cli.config.user.developer else True)
def generate_docs(cli):
    """Invoke the docs generation process

    TODO(unclaimed):
        * [ ] Add a real build step... something static docs
    """

    if BUILD_DOCS_PATH.exists():
        shutil.rmtree(BUILD_DOCS_PATH)
    if DOXYGEN_PATH.exists():
        shutil.rmtree(DOXYGEN_PATH)

    # ignore node_modules when we're testing locally
    shutil.copytree(DOCS_PATH, BUILD_DOCS_PATH, ignore=shutil.ignore_patterns("node_modules"))

    # When not verbose we want to hide all output
    args = {
        'capture_output': False if cli.config.general.verbose else True,
        'check': True,
        'stdin': DEVNULL,
    }

    cli.log.info('Generating docs...')

    # Generate internal docs
    cli.run(['doxygen', 'Doxyfile'], **args)
    cli.run(['moxygen', '-q', '-g', '-o', MOXYGEN_PATH / '%s.md', DOXYGEN_PATH / 'xml'], **args)

    cli.log.info('Successfully generated docs to %s.', BUILD_DOCS_PATH)
