"""Build QMK documentation locally
"""
import shutil
import subprocess
from pathlib import Path

from milc import cli

DOCS_PATH = Path('docs/')
BUILD_PATH = Path('.build/docs/')


@cli.subcommand('Build QMK documentation.', hidden=False if cli.config.user.developer else True)
def generate_docs(cli):
    """Invoke the docs generation process

    TODO(unclaimed):
        * [ ] Add a real build step... something static docs
    """

    if BUILD_PATH.exists():
        shutil.rmtree(BUILD_PATH)

    shutil.copytree(DOCS_PATH, BUILD_PATH)

    # When not verbose we want to hide all output
    args = {'check': True}
    if not cli.args.verbose:
        args.update({'stdout': subprocess.DEVNULL, 'stderr': subprocess.STDOUT})

    cli.log.info('Generating internal docs...')

    # Generate internal docs
    subprocess.run(['doxygen', 'Doxyfile'], **args)
    subprocess.run(['moxygen', '-q', '-a', '-g', '-o', BUILD_PATH / 'internals_%s.md', 'doxygen/xml'], **args)

    cli.log.info('Successfully generated internal docs to %s.', BUILD_PATH)
