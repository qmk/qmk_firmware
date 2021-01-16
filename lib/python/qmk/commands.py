"""Helper functions for commands.
"""
import json
import os
import platform
import subprocess
import shlex
import shutil
from pathlib import Path

from milc import cli

import qmk.keymap
from qmk.constants import KEYBOARD_OUTPUT_PREFIX


def _find_make():
    """Returns the correct make command for this environment.
    """
    make_cmd = os.environ.get('MAKE')

    if not make_cmd:
        make_cmd = 'gmake' if shutil.which('gmake') else 'make'

    return make_cmd


def create_make_command(keyboard, keymap, target=None, parallel=1, **env_vars):
    """Create a make compile command

    Args:

        keyboard
            The path of the keyboard, for example 'plank'

        keymap
            The name of the keymap, for example 'algernon'

        target
            Usually a bootloader.

        parallel
            The number of make jobs to run in parallel

        **env_vars
            Environment variables to be passed to make.

    Returns:

        A command that can be run to make the specified keyboard and keymap
    """
    env = []
    make_args = [keyboard, keymap]
    make_cmd = _find_make()

    if target:
        make_args.append(target)

    for key, value in env_vars.items():
        env.append(f'{key}={value}')

    return [make_cmd, '-j', str(parallel), *env, ':'.join(make_args)]


def compile_configurator_json(user_keymap, parallel=1, **env_vars):
    """Convert a configurator export JSON file into a C file and then compile it.

    Args:

        user_keymap
            A deserialized keymap export

        bootloader
            A bootloader to flash

        parallel
            The number of make jobs to run in parallel

    Returns:

        A command to run to compile and flash the C file.
    """
    # Write the keymap.c file
    keyboard_filesafe = user_keymap['keyboard'].replace('/', '_')
    target = f'{keyboard_filesafe}_{user_keymap["keymap"]}'
    keyboard_output = Path(f'{KEYBOARD_OUTPUT_PREFIX}{keyboard_filesafe}')
    keymap_output = Path(f'{keyboard_output}_{user_keymap["keymap"]}')
    c_text = qmk.keymap.generate_c(user_keymap['keyboard'], user_keymap['layout'], user_keymap['layers'])
    keymap_dir = keymap_output / 'src'
    keymap_c = keymap_dir / 'keymap.c'

    keymap_dir.mkdir(exist_ok=True, parents=True)
    keymap_c.write_text(c_text)

    # Return a command that can be run to make the keymap and flash if given
    verbose = 'true' if cli.config.general.verbose else 'false'
    color = 'true' if cli.config.general.color else 'false'
    make_command = [
        _find_make(),
        '-j',
        str(parallel),
        '-r',
        '-R',
        '-f',
        'build_keyboard.mk',
    ]

    for key, value in env_vars.items():
        make_command.append(f'{key}={value}')

    make_command.extend([
        f'KEYBOARD={user_keymap["keyboard"]}',
        f'KEYMAP={user_keymap["keymap"]}',
        f'KEYBOARD_FILESAFE={keyboard_filesafe}',
        f'TARGET={target}',
        f'KEYBOARD_OUTPUT={keyboard_output}',
        f'KEYMAP_OUTPUT={keymap_output}',
        f'MAIN_KEYMAP_PATH_1={keymap_output}',
        f'MAIN_KEYMAP_PATH_2={keymap_output}',
        f'MAIN_KEYMAP_PATH_3={keymap_output}',
        f'MAIN_KEYMAP_PATH_4={keymap_output}',
        f'MAIN_KEYMAP_PATH_5={keymap_output}',
        f'KEYMAP_C={keymap_c}',
        f'KEYMAP_PATH={keymap_dir}',
        f'VERBOSE={verbose}',
        f'COLOR={color}',
        'SILENT=false',
    ])

    return make_command


def parse_configurator_json(configurator_file):
    """Open and parse a configurator json export
    """
    # FIXME(skullydazed/anyone): Add validation here
    user_keymap = json.load(configurator_file)

    return user_keymap


def run(command, *args, **kwargs):
    """Run a command with subprocess.run
    """
    platform_id = platform.platform().lower()

    if isinstance(command, str):
        raise TypeError('`command` must be a non-text sequence such as list or tuple.')

    if 'windows' in platform_id:
        safecmd = map(str, command)
        safecmd = map(shlex.quote, safecmd)
        safecmd = ' '.join(safecmd)
        command = [os.environ['SHELL'], '-c', safecmd]

    return subprocess.run(command, *args, **kwargs)
