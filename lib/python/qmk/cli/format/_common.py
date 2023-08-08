"""
Shared functionality across all formatters.
"""

import functools
from pathlib import Path
from subprocess import DEVNULL

from argcomplete.completers import FilesCompleter
from milc import cli

from qmk.path import normpath

ALL_FILES = "__all__"  # identifier to format every file in the repo

CORE_DIRS = {
    'c': ('drivers', 'quantum', 'tests', 'tmk_core', 'platforms'),
    'python': ('lib/python', 'util/ci'),
    'text': ALL_FILES,
}
IGNORED_DIRS = {
    'c': ('tmk_core/protocol/usb_hid', 'platforms/chibios/boards'),
}

FILE_SUFFIXES = {
    'c': ('c', 'h', 'cpp', 'hpp'),
    'python': ('py', ),
    'text': ('', ),  # '' matches with everything
    'json': ('json', ),
}

def source_files(dir_names, suffixes):
    """Returns a list of all source files for a given list of directories, given their suffixes

    Args:

        dir_names
            List of directories relative to `qmk_firmware`.

        suffixes
            List of file suffixes to find.
    """
    files = []
    for dir in dir_names:
        # suffix contains dot, remove it
        files.extend(file for file in Path(dir).glob('**/*') if file.suffix[1:] in suffixes)
    return files


def is_relative_to(file, other):
    """Provide similar behavior to PurePath.is_relative_to in Python > 3.9
    """
    return str(normpath(file).resolve()).startswith(str(normpath(other).resolve()))


def qmk_formatter(func):
    """
    This decorator defines flags and behaviour common to all formatters.
    """
    def _filter_files(_files, core_only=False):
        """
        Helper to yield only files to be formatted and skip the rest
        """

        _files = list(map(normpath, filter(None, _files)))

        for file in _files:
            # The following statement checks each file to see if the file path is
            # - in the core directories
            # - not in the ignored directories
            # ... when core_only is flagged
            if (
                core_only
                and (
                    not any(is_relative_to(file, i) for i in core_dirs)
                    or any(is_relative_to(file, i) for i in ignored_dirs)
                )
            ):
                    cli.log.debug("Skipping non-core file %s, as '--core-only' is used.", file)
                    continue

            if file.suffix[1:] in suffixes:
                yield file
            else:
                cli.log.debug('Skipping file %s', file)

    def _get_files(_cli):
        """
        Helper to get the list of files to be format, according to CLI args
        """

        files = []
        # List of files was supplied
        if _cli.args.files:
            files = list(_filter_files(_cli.args.files, _cli.args.core_only))

            if _cli.args.all_files:
                _cli.log.warning('Filename passed along -a, ignoring -a')

        # All core files
        elif _cli.args.all_files:
            # all files in repo vs all core files
            if core_dirs == ALL_FILES:
                git_ls_cmd = ['git', 'ls-files']
                git_ls = cli.run(git_ls_cmd, stdin=DEVNULL)
                files = list(filter(None, git_ls.stdout.split('\n')))
            else:
                files = source_files(core_dirs, suffixes)

        # Git diff
        else:
            git_diff_cmd = ['git', 'diff', '--name-only', _cli.args.base_branch, *core_dirs]
            git_diff = _cli.run(git_diff_cmd, stdin=DEVNULL)

            if git_diff.returncode != 0:
                _cli.log.error('Error running %s', git_diff_cmd)
                print(git_diff.stderr)
                exit(git_diff.returncode)

            files = git_diff.stdout.strip().split('\n')
            files = list(_filter_files(files, True))

        # remove empty values and then sort them
        return sorted(files)

    # funcs are named format_<file_extension>
    func_name: str = func.__name__
    lang_name = func_name[func_name.index("_") + 1:]

    suffixes = FILE_SUFFIXES.get(lang_name)
    if suffixes is None:
        cli.log.error(f"Unknown file extensions for language: '{lang_name}'")

    # default: no folders to be formatted nor ignored
    core_dirs = CORE_DIRS.get(lang_name, [])


    ignored_dirs = IGNORED_DIRS.get(lang_name, [])


    @cli.argument('-i', '--inplace', arg_only=True, action='store_true', help='Edit the file instead of showing changes.')
    @cli.argument('-b', '--base-branch', default='origin/master', help='Branch to compare to, to get diffs.')
    @cli.argument('-a', '--all-files', arg_only=True, action='store_true', help='Format all core files.')
    @cli.argument('--core-only', arg_only=True, action='store_true', help='Format core files only.')
    @cli.argument('files', nargs='*', arg_only=True, type=normpath, completer=FilesCompleter(suffixes), help='Filename(s) to format.')
    @cli.subcommand(f"Format {lang_name} code according to QMK's style.", hidden=not cli.config.user.developer)
    @functools.wraps(func)
    def wrapper(cli):
        """
        Actual logic to format code according to QMK's style.
        """

        files = _get_files(cli)
        if not files:
            cli.log.error('No files to be formatted found')
            exit(0)


        # Done one file at a time because JSON (and potentially others in the future) only supports it
        for file in files:
            output = func(cli, file)
            if not output:  # halt on errors
                return output

    return wrapper

__all__ = [
    "qmk_formatter",
    "CORE_DIRS",
]
