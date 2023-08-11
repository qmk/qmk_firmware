import shutil

from milc import cli

from qmk.path import normpath
from qmk import submodules

REMOVE_DIRS = [
    'lib/ugfx',
    'lib/chibios-contrib/ext/mcux-sdk',
]

IGNORE_DIRS = [
    'lib/arm_atsam',
    'lib/fnv',
    'lib/lib8tion',
    'lib/python',
    'lib/usbhost',
]


@cli.argument('--check', arg_only=True, action='store_true', help='Check if the submodules are dirty, and display a warning if they are.')
@cli.argument('--sync', arg_only=True, action='store_true', help='Shallow clone any missing submodules.')
@cli.argument('-f', '--force', action='store_true', help='Flag to remove unexpected directories')
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

    # can be the default behavior with: qmk config git_submodule.force=True
    remove_dirs = REMOVE_DIRS
    if cli.config.git_submodule.force:
        # Also trash everything that isnt marked as "safe"
        for path in normpath('lib').iterdir():
            if not any(ignore in path.as_posix() for ignore in IGNORE_DIRS):
                remove_dirs.append(path)

    for folder in map(normpath, remove_dirs):
        if normpath(folder).is_dir():
            print(f"Removing '{folder}'")
            shutil.rmtree(folder)

    cli.run(['git', 'submodule', 'sync', '--recursive'], capture_output=False)
    cli.run(['git', 'submodule', 'update', '--init', '--recursive', '--progress'], capture_output=False)
