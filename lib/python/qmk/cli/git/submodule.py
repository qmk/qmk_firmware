import shutil

from milc import cli

from qmk.path import normpath
from qmk import submodules

REMOVE_DIRS = [
    'lib/ugfx',
    'lib/pico-sdk',
    'lib/chibios-contrib/ext/mcux-sdk',
    'lib/lvgl',
]


@cli.argument('--check', arg_only=True, action='store_true', help='Check if the submodules are dirty, and display a warning if they are.')
@cli.argument('--sync', arg_only=True, action='store_true', help='Shallow clone any missing submodules.')
@cli.subcommand('Git Submodule actions.')
def git_submodule(cli):
    """Git Submodule actions
    """
    if cli.args.check:
        return all(item['status'] for item in submodules.status().values())

    if cli.args.sync:
        cli.run(['git', 'submodule', 'sync', '--recursive'])
        for name, item in submodules.status().items():
            if item['status'] is None:
                cli.run(['git', 'submodule', 'update', '--depth=50', '--init', name], capture_output=False)
        return True

    for folder in REMOVE_DIRS:
        if normpath(folder).is_dir():
            print(f"Removing '{folder}'")
            shutil.rmtree(folder)

    cli.run(['git', 'submodule', 'sync', '--recursive'], capture_output=False)
    cli.run(['git', 'submodule', 'update', '--init', '--recursive', '--progress'], capture_output=False)
