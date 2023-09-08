"""Format python code according to QMK's style.
"""
from subprocess import CalledProcessError, DEVNULL

from milc import cli
from . import qmk_formatter, CORE_DIRS

py_dirs = CORE_DIRS.get('python')


def yapf_run(file, inplace):
    edit = '--in-place' if inplace else '--diff'
    yapf_cmd = ['yapf', '-vv', edit, file]
    try:
        cli.run(yapf_cmd, check=True, capture_output=False, stdin=DEVNULL)
        cli.log.info(f'Successfully formatted the python code. ({file})')

    except CalledProcessError:
        cli.log.error(f'Python code incorrectly formatted! ({file})')
        return False


@qmk_formatter
def format_python(cli, file):
    """
    Format a single Python file according to QMK's style.
    Itrating over target files is handled in decorator.
    """

    return yapf_run(file, cli.args.inplace)
