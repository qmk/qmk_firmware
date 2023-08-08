"""Format C code according to QMK's style.
"""
from shutil import which
from subprocess import CalledProcessError, DEVNULL, Popen, PIPE

from milc import cli
from . import qmk_formatter


def find_clang_format():
    """Returns the path to clang-format.
    """
    for clang_version in range(20, 6, -1):
        binary = f'clang-format-{clang_version}'

        if which(binary):
            return binary

    return 'clang-format'


def find_diff(file, verbose=True):
    """Run clang-format and diff it against a file.
    """
    found_diffs = False

    cli.log.debug('Checking for changes in %s', file)
    clang_format = Popen([find_clang_format(), file], stdout=PIPE, stderr=PIPE, universal_newlines=True)
    diff = cli.run(['diff', '-u', f'--label=a/{file}', f'--label=b/{file}', str(file), '-'], stdin=clang_format.stdout, capture_output=True)

    if diff.returncode != 0:
        if verbose:
            print(diff.stdout)
        found_diffs = True

    return found_diffs


def cformat_run(file):
    """Spawn clang-format subprocess with proper arguments
    """
    # Determine which version of clang-format to use
    clang_format = [find_clang_format(), '-i']

    # early stop if no change to be made
    if not find_diff(file, verbose=False):
        return True

    try:
        cli.run([*clang_format, file], check=True, capture_output=False, stdin=DEVNULL)
        cli.log.info(f'Successfully formatted the C code. ({file})')
        return True

    except CalledProcessError as e:
        cli.log.error(f'Error formatting C code! ({file})')
        cli.log.debug('%s exited with returncode %s', e.cmd, e.returncode)
        cli.log.debug('STDOUT:')
        cli.log.debug(e.stdout)
        cli.log.debug('STDERR:')
        cli.log.debug(e.stderr)
        return False


@qmk_formatter
def format_c(cli, file):
    """
    Format a single C file according to QMK's style.
    Itrating over target files is handled in decorator.
    """

    if cli.args.inplace:
        return cformat_run(file)

    return not find_diff(file)
