"""Handlers for the QMK documentation generator (docusaurus).
"""
import shutil
from subprocess import DEVNULL
from os import chdir, environ, makedirs, pathsep
from milc import cli

from qmk.constants import QMK_FIRMWARE

DOCS_PATH = QMK_FIRMWARE / 'docs'
BUILDDEFS_PATH = QMK_FIRMWARE / 'builddefs' / 'docsgen'
BUILD_PATH = QMK_FIRMWARE / '.build'
CACHE_PATH = BUILD_PATH / 'cache'
NODE_MODULES_PATH = BUILD_PATH / 'node_modules'
BUILD_DOCS_PATH = BUILD_PATH / 'docs'
DOXYGEN_PATH = BUILD_DOCS_PATH / 'static' / 'doxygen'


def run_docs_command(cmd, capture_output=False if cli.config.general.verbose else True):
    cli.run(['yarn', 'run', cmd], capture_output=capture_output, check=True, stdin=DEVNULL)


def prepare_docs_build_area():
    if BUILD_DOCS_PATH.exists():
        shutil.rmtree(BUILD_DOCS_PATH)

    # When not verbose we want to hide all output
    args = {'capture_output': False if cli.config.general.verbose else True, 'check': True, 'stdin': DEVNULL}

    makedirs(DOXYGEN_PATH)
    cli.log.info('Generating doxygen docs at %s', DOXYGEN_PATH)
    cli.run(['doxygen', 'Doxyfile'], **args)

    environ['PATH'] += pathsep + str(NODE_MODULES_PATH / '.bin')

    docs_env = environ.copy()
    if cli.config.general.verbose:
        docs_env['DEBUG'] = 'vitepress:*,vite:*'
    args['env'] = docs_env

    chdir(BUILDDEFS_PATH)
    cli.log.info('Installing vitepress dependencies')
    cli.run(['yarn', 'install'], **args)
