import shutil
from qmk.path import normpath

from milc import cli

REMOVE_DIRS = [
    'lib/ugfx',
    'lib/pico-sdk',
    'lib/chibios-contrib/ext/mcux-sdk',
    'lib/lvgl',
]


@cli.subcommand('Git Submodule actions.')
def git_submodule(cli):
    for folder in REMOVE_DIRS:
        if normpath(folder).is_dir():
            print(f"Removing '{folder}'")
            shutil.rmtree(folder)

    cli.run(['git', 'submodule', 'sync', '--recursive'], capture_output=False)
    cli.run(['git', 'submodule', 'update', '--init', '--recursive', '--progress'], capture_output=False)
