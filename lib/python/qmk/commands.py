"""Helper functions for commands.
"""
from functools import lru_cache
import json
import os
import shutil
import threading
from pathlib import Path
from subprocess import DEVNULL
from time import sleep, strftime

from dotty_dict import dotty
from milc import cli

import qmk.keymap
from qmk.constants import KEYBOARD_OUTPUT_PREFIX
from qmk.info import info_json
from qmk.json_schema import json_load
from qmk.keyboard import list_keyboards

time_fmt = '%Y-%m-%d-%H:%M:%S'


@lru_cache(maxsize=0)
def _find_make():
    """Returns the correct make command for this environment.
    """
    make_cmd = os.environ.get('MAKE')

    if not make_cmd:
        make_cmd = 'gmake' if shutil.which('gmake') else 'make'

    return make_cmd


def create_make_command(keyboard, keymap, target=None, parallel=1, silent=False, **env_vars):
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
    make_cmd = [_find_make(), '--no-print-directory', '-r', '-R', '-C', './', '-f', 'build_keyboard.mk']

    env_vars['KEYBOARD'] = keyboard
    env_vars['KEYMAP'] = keymap
    env_vars['QMK_BIN'] = 'bin/qmk' if 'DEPRECATED_BIN_QMK' in os.environ else 'qmk'
    env_vars['VERBOSE'] = 'true' if cli.config.general.verbose else ''
    env_vars['SILENT'] = 'true' if silent else 'false'
    env_vars['COLOR'] = 'true' if cli.config.general.color else ''

    if parallel > 1:
        make_cmd.append('-j')
        make_cmd.append(str(parallel))

    if target:
        make_cmd.append(target)

    for key, value in env_vars.items():
        make_cmd.append(f'{key}={value}')

    return make_cmd


@lru_cache(maxsize=0)
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

    return user_keymap['keyboard'], user_keymap['keymap'], make_command


@lru_cache(maxsize=0)
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


def do_compile(keyboard, keymap, parallel, target=None, filters=None, environment=None):
    """Shared code between `qmk compile` and `qmk flash`.
    """
    if keyboard is None:
        keyboard = ''

    if environment is None:
        environment = {}

    all_keyboards = keyboard == 'all' or keyboard.startswith('all-')
    all_keymaps = keymap == 'all'
    multiple_compiles = all_keyboards or all_keymaps

    # Setup the environment
    envs = {'REQUIRE_PLATFORM_KEY': ''}

    for env in environment:
        if '=' in env:
            key, value = env.split('=', 1)
            if key in envs:
                cli.log.warning('Overwriting existing environment variable %s=%s with %s=%s!', key, envs[key], key, value)
            envs[key] = value
        else:
            cli.log.warning('Invalid environment variable: %s', env)

    if keyboard.startswith('all-'):
        envs['REQUIRE_PLATFORM_KEY'] = keyboard[4:]

    # Run clean if necessary
    if cli.args.clean and not cli.args.filename and not cli.args.dry_run:
        for kb, km in keyboard_keymap_iter(keyboard, keymap, {}):
            cli.log.info('Cleaning previous build files for keyboard {fg_cyan}%s{fg_reset} keymap {fg_cyan}%s', kb, km)
            make_cmd = create_make_command(kb, km, 'clean', 1, multiple_compiles, **envs)
            cli.run(make_cmd, capture_output=False, stdin=DEVNULL)

    # Determine the compile command(s)
    command = None

    if cli.args.filename:
        if cli.args.keyboard:
            cli.log.warning('Ignoring --keyboard because a keymap.json was provided.')

        if cli.args.keymap:
            cli.log.warning('Ignoring --keymap because a keymap.json was provided.')

        # If a configurator JSON was provided generate a keymap and compile it
        user_keymap = parse_configurator_json(cli.args.filename)
        command = compile_configurator_json(user_keymap, parallel=parallel, **envs)

    elif keyboard and keymap:
        if multiple_compiles:
            command = 'multiple'
        else:
            command = create_make_command(keyboard, keymap, target=target, parallel=parallel, silent=multiple_compiles, **envs)

    elif not keyboard:
        cli.log.error('Could not determine keyboard!')

    elif not keymap:
        cli.log.error('Could not determine keymap!')

    # Compile the firmware, if we're able to
    if command == 'multiple':
        cli.log.info('Building {fg_cyan}%s{fg_reset} with keymap {fg_cyan}%s', keyboard, keymap)

        returncodes = []
        for keyboard, keymap in keyboard_keymap_iter(keyboard, keymap, filters):
            command = create_make_command(keyboard, keymap, target=target, parallel=1, silent=multiple_compiles, **envs)
            while threading.active_count() >= parallel + 1:
                sleep(1)
            threading.Thread(target=_execute_compile, args=(keyboard, keymap, command, target, returncodes)).start()

        while threading.active_count() > 1:
            sleep(1)

        if any(returncodes):
            print()
            cli.log.error('Could not compile all targets, look above this message for more details. Failing target(s):')

            for i, returncode in enumerate(returncodes):
                if returncode != 0:
                    keyboard, keymap, command = commands[i]
                    cli.echo('\tkeyboard: {fg_cyan}%s{fg_reset} keymap: {fg_cyan}%s', keyboard, keymap)

    elif command:
        if target:
            cli.log.info('Building {fg_cyan}%s{fg_reset} with keymap {fg_cyan}%s{fg_reset} and target {fg_cyan}%s', keyboard, keymap, target)
        else:
            cli.log.info('Building {fg_cyan}%s{fg_reset} with keymap {fg_cyan}%s', keyboard, keymap)

        if _execute_compile(keyboard, keymap, command, target) != 0:
            print()
            cli.log.error('Could not compile all targets, look above this message for more details. Failing target(s):')
            cli.echo('\tkeyboard: {fg_cyan}%s{fg_reset} keymap: {fg_cyan}%s', keyboard, keymap)

    elif filters:
        cli.log.error('No keyboards found after applying filter(s)!')
        return False

    else:
        cli.log.error('You must supply a configurator export, both `--keyboard` and `--keymap`, or be in a directory for a keyboard or keymap.')
        cli.print_help()
        return False


def _execute_compile(keyboard, keymap, command, target, returncodes=None):
    if not returncodes:
        returncodes = []

    if keymap not in qmk.keymap.list_keymaps(keyboard):
        cli.log.debug('Skipping keyboard %s, no %s keymap found.', keyboard, keymap)
        return 0

    cli.log.debug('Running make command: {fg_blue}%s', ' '.join(command))

    if not cli.args.dry_run:
        compile = cli.run(command, combined_output=True)

        cli.acquire_lock()
        returncodes.append(compile.returncode)
        cli.release_lock()

        if compile.returncode != 0:
            cli.log.info('Could not build firmware for {fg_cyan}%s{fg_reset} with keymap {fg_cyan}%s', keyboard, keymap)
            print(compile.stdout)


@lru_cache()
def _keyboard_list(keyboard):
    """Returns a list of keyboards matching keyboard.
    """
    if keyboard == 'all' or keyboard.startswith('all-'):
        return list_keyboards()

    return [keyboard]


def keyboard_keymap_iter(cli_keyboard, cli_keymap, filters):
    """Iterates over the keyboard/keymap for this command and yields a pairing of each.
    """
    for keyboard in _keyboard_list(cli_keyboard):
        continue_flag = False

        if filters:
            info_data = dotty(info_json(keyboard))

            for key, value in filters.items():
                if info_data.get(key) != value:
                    continue_flag = True
                    break

            if continue_flag:
                continue

        if cli_keymap == 'all':
            for keymap in qmk.keymap.list_keymaps(keyboard):
                yield keyboard, keymap

        else:
            yield keyboard, cli_keymap
