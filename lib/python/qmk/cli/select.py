"""Filter files for scripting purposes
"""
import subprocess
import sys
from pathlib import Path

from milc import cli

from qmk.keyboard import list_keyboards


def filter_kb(files):
    keyboards = list_keyboards()

    filtered_keyboards = set()

    for file in files:
        if file.startswith('keyboards') and 'keymaps' not in file:
            for keyboard_name in keyboards:
                if keyboard_name in file:
                    filtered_keyboards.add(keyboard_name)

    return filtered_keyboards


def filter_c(files):
    core_dirs = ['drivers', 'quantum', 'tests', 'tmk_core', 'platforms']
    ignores = ['tmk_core/protocol/usb_hid', 'quantum/template', 'platforms/chibios']

    filtered_code_files = []
    for file in files:
        p = Path(file)
        if p.exists() and p.suffix in ['.c', '.h', '.cpp']:
            if any(file.startswith(i) for i in core_dirs) and not any(i in file for i in ignores):
                filtered_code_files.append(file)

    return filtered_code_files


@cli.argument('-f', '--filter', help='Filter down the selected fileset')
@cli.argument('-a', '--all-files', arg_only=True, action='store_true', help='Select all files for filtering')
@cli.argument('-b', '--base-branch', default='origin/master', help='Branch to compare to diffs to.')
@cli.argument('files', nargs='*', arg_only=True, help='Filename(s) to filter on')
@cli.subcommand("Return a filtered list of files.", hidden=False if cli.config.user.developer else True)
def select(cli):
    """Filter files for scripting purposes

    Processing Order:
       * stdin
       * arguments
       * all files
       * current git differences
    """

    files = []

    if not sys.stdin.isatty():
        files = sys.stdin.readlines()
    elif cli.args.files:
        files = cli.args.files
    elif cli.args.all_files:
        base_args = ['git', 'ls-files']
        out = subprocess.run(base_args, check=True, stdout=subprocess.PIPE)
        files = filter(None, out.stdout.decode('UTF-8').split('\n'))
    else:
        base_args = ['git', 'diff', '--name-only', cli.args.base_branch]
        out = subprocess.run(base_args, check=True, stdout=subprocess.PIPE)
        files = filter(None, out.stdout.decode('UTF-8').split('\n'))

    # Apply filter
    if cli.args.filter:
        files = globals()["filter_%s" % cli.args.filter](files)

    # Dump back out the potentially filtered list
    print(*files, sep='\n')
