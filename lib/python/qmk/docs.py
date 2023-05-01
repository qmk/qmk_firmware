"""Handlers for the QMK documentation generator (docusaurus).
"""
import shutil
from subprocess import DEVNULL
from milc import cli

from qmk.constants import QMK_FIRMWARE

DOCS_PATH = QMK_FIRMWARE / 'docs'
BUILDDEFS_PATH = QMK_FIRMWARE / 'builddefs' / 'docs'
BUILD_PATH = QMK_FIRMWARE / '.build'
BUILD_DOCS_PATH = BUILD_PATH / 'docs'
DOXYGEN_PATH = BUILD_DOCS_PATH / 'static' / 'doxygen'

def run_docs_command(cmd, capture_output = False if cli.config.general.verbose else True):
    cli.run(['npm', 'run', '--prefix', BUILD_DOCS_PATH, cmd], capture_output=capture_output, check=True, stdin=DEVNULL)

def prepare_docs_build_area():
    if BUILD_DOCS_PATH.exists():
        shutil.rmtree(BUILD_DOCS_PATH)

    cli.log.info('Copying "%s" folder to "%s"', BUILDDEFS_PATH, BUILD_DOCS_PATH)

    # ignore .gitignore'd folders when we're testing locally
    shutil.copytree(BUILDDEFS_PATH, BUILD_DOCS_PATH, ignore=shutil.ignore_patterns("node_modules", "build", ".docusaurus"))

    # When not verbose we want to hide all output
    args = {
        'capture_output': False if cli.config.general.verbose else True,
        'check': True,
        'stdin': DEVNULL,
    }

    cli.log.info('Generating doxygen docs at %s', DOXYGEN_PATH)
    cli.run(['doxygen', 'Doxyfile'], **args)

    cli.log.info('Installing docusaurus dependencies')
    cli.run(['npm', 'ci', '--prefix', BUILD_DOCS_PATH], **args)
