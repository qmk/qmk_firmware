"""Generate and run a make command for building a keyboard.
"""
import os
from time import time

from milc import cli

from qmk.info import find_info_json

file_stale_secs = 86400  # How many seconds old generated files are before being regenerated


def is_stale(file_path, *dependencies):
    """Checks to see if a file is stale and should be regenerated.
    """
    if not os.path.exists(file_path):
        return True

    file_mtime = os.stat(file_path).st_mtime

    # If the file is more than 24 hours old we consider it stale anyway
    if time() - file_mtime > file_stale_secs:
        return True

    # Iterate through dependencies, if we find one that's newer return True
    for dep in dependencies:
        dep_mtime = os.stat(dep).st_mtime
        if dep_mtime > file_mtime:
            return True

    return False


@cli.argument('targets', nargs='*', arg_only=True, help='Make targets to run')
@cli.argument('-f', '--makefile', arg_only=True, default='build_keyboard.mk', help="The makefile to use")
@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually build, just show the make command to be run")
@cli.subcommand('Parse and run a QMK make command', hidden=True)
def make(cli):
    """Run a qmk make command.
    """
    # Determine the keyboard
    silent = False
    keyboard = None
    build_dir = '.build'

    for target in cli.args.targets:
        if target.startswith('KEYBOARD='):
            keyboard = target.split('=', 1)[1]

        if target.startswith('BUILD_DIR='):
            build_dir = target.split('=', 1)[1]

        if target == 'SILENT=true':
            silent = True

        if target == 'SILENT=false':
            silent = False

    if not keyboard:
        cli.log.error('Could not identify a keyboard for this compile!')
        return False

    keyboard_filesafe = keyboard.replace('/', '_')
    keyboard_output = f'{build_dir}/obj_{keyboard_filesafe}'

    # Generate the include files
    info_json_files = find_info_json(keyboard)
    config_h_file = f'{keyboard_output}/src/info_config.h'
    layouts_h_file = f'{keyboard_output}/src/layouts.h'

    if 'clean' not in cli.args.targets:
        config_h_cmd = ['bin/qmk', 'generate-config-h', '--keyboard', keyboard, '--output', config_h_file]
        layouts_h_cmd = ['bin/qmk', 'generate-layouts', '--keyboard', keyboard, '--output', layouts_h_file]

        if silent:
            config_h_cmd.append('-q')
            layouts_h_cmd.append('-q')

        if is_stale(config_h_file, *info_json_files):
            cli.run(config_h_cmd, capture_output=False)

        if is_stale(layouts_h_file, *info_json_files):
            cli.run(layouts_h_cmd, capture_output=False)

    # Call make
    jobs = '1'
    if '-j' in os.environ.get('MAKEFLAGS', ''):
        for word in os.environ['MAKEFLAGS'].split():
            if word.startswith('-j'):
                jobs = word[2:]
                break

    shell_env = os.environ.copy()
    for key in ('MAKEFLAGS', 'MAKELEVEL', 'MAKE_TERMERR', 'MFLAGS'):
        if key in shell_env:
            del shell_env[key]

    make_cmd = ['make', '-j', jobs, '-r', '-R', '-f', cli.args.makefile, *cli.args.targets]
    cli.log.debug('Running: %s', ' '.join(make_cmd))
    cli.run(make_cmd, capture_output=False, env=shell_env)
