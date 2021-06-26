"""Helper functions for commands.
"""
import json
import os
import shutil
from pathlib import Path
from subprocess import DEVNULL
from time import strftime

from milc import cli

import qmk.keymap
from qmk.constants import KEYBOARD_OUTPUT_PREFIX
from qmk.json_schema import json_load

time_fmt = '%Y-%m-%d-%H:%M:%S'


def _find_make():
    """Returns the correct make command for this environment.
    """
    make_cmd = os.environ.get('MAKE')

    if not make_cmd:
        make_cmd = 'gmake' if shutil.which('gmake') else 'make'

    return make_cmd


def create_make_target(target, parallel=1, **env_vars):
    """Create a make command

    Args:

        target
            Usually a make rule, such as 'clean' or 'all'.

        parallel
            The number of make jobs to run in parallel

        **env_vars
            Environment variables to be passed to make.

    Returns:

        A command that can be run to make the specified keyboard and keymap
    """
    env = []
    make_cmd = _find_make()

    for key, value in env_vars.items():
        env.append(f'{key}={value}')

    return [make_cmd, '-j', str(parallel), *env, target]


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
    make_args = [keyboard, keymap]

    if target:
        make_args.append(target)

    return create_make_target(':'.join(make_args), parallel, **env_vars)


def get_git_version(current_time, repo_dir='.', check_dir='.'):
    """Returns the current git version for a repo, or the current time.
    """
    git_describe_cmd = ['git', 'describe', '--abbrev=6', '--dirty', '--always', '--tags']

    if repo_dir != '.':
        repo_dir = Path('lib') / repo_dir

    if check_dir != '.':
        check_dir = repo_dir / check_dir

    if Path(check_dir).exists():
        git_describe = cli.run(git_describe_cmd, stdin=DEVNULL, cwd=repo_dir)

        if git_describe.returncode == 0:
            return git_describe.stdout.strip()

        else:
            cli.log.warn(f'"{" ".join(git_describe_cmd)}" returned error code {git_describe.returncode}')
            print(git_describe.stderr)
            return current_time

    return current_time


def create_version_h(skip_git=False, skip_all=False):
    """Generate version.h contents
    """
    if skip_all:
        current_time = "1970-01-01-00:00:00"
    else:
        current_time = strftime(time_fmt)

    if skip_git:
        git_version = "NA"
        chibios_version = "NA"
        chibios_contrib_version = "NA"
    else:
        git_version = get_git_version(current_time)
        chibios_version = get_git_version(current_time, "chibios", "os")
        chibios_contrib_version = get_git_version(current_time, "chibios-contrib", "os")

    version_h_lines = f"""/* This file was automatically generated. Do not edit or copy.
 */

#pragma once

#define QMK_VERSION "{git_version}"
#define QMK_BUILDDATE "{current_time}"
#define CHIBIOS_VERSION "{chibios_version}"
#define CHIBIOS_CONTRIB_VERSION "{chibios_contrib_version}"
"""

    return version_h_lines


def compile_configurator_json(user_keymap, bootloader=None, parallel=1, **env_vars):
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

    version_h = Path('quantum/version.h')
    version_h.write_text(create_version_h())

    # Return a command that can be run to make the keymap and flash if given
    verbose = 'true' if cli.config.general.verbose else 'false'
    color = 'true' if cli.config.general.color else 'false'
    make_command = [_find_make()]

    if not cli.config.general.verbose:
        make_command.append('-s')

    make_command.extend([
        '-j',
        str(parallel),
        '-r',
        '-R',
        '-f',
        'build_keyboard.mk',
    ])

    if bootloader:
        make_command.append(bootloader)

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
        f'QMK_BIN={"bin/qmk" if "DEPRECATED_BIN_QMK" in os.environ else "qmk"}',
    ])

    return make_command


def parse_configurator_json(configurator_file):
    """Open and parse a configurator json export
    """
    # FIXME(skullydazed/anyone): Add validation here
    user_keymap = json.load(configurator_file)
    orig_keyboard = user_keymap['keyboard']
    aliases = json_load(Path('data/mappings/keyboard_aliases.json'))

    if orig_keyboard in aliases:
        if 'target' in aliases[orig_keyboard]:
            user_keymap['keyboard'] = aliases[orig_keyboard]['target']

        if 'layouts' in aliases[orig_keyboard] and user_keymap['layout'] in aliases[orig_keyboard]['layouts']:
            user_keymap['layout'] = aliases[orig_keyboard]['layouts'][user_keymap['layout']]

    return user_keymap
