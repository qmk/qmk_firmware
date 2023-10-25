"""Helper functions for commands.
"""
import os
import sys
import json
import shutil
from pathlib import Path

from milc import cli
import jsonschema

from qmk.constants import INTERMEDIATE_OUTPUT_PREFIX
from qmk.json_schema import json_load, validate


def _find_make():
    """Returns the correct make command for this environment.
    """
    make_cmd = os.environ.get('MAKE')

    if not make_cmd:
        make_cmd = 'gmake' if shutil.which('gmake') else 'make'

    return make_cmd


def create_make_target(target, dry_run=False, parallel=1, **env_vars):
    """Create a make command

    Args:

        target
            Usually a make rule, such as 'clean' or 'all'.

        dry_run
            make -n -- don't actually build

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

    if cli.config.general.verbose:
        env.append('VERBOSE=true')

    return [make_cmd, *(['-n'] if dry_run else []), *get_make_parallel_args(parallel), *env, target]


def create_make_command(keyboard, keymap, target=None, dry_run=False, parallel=1, **env_vars):
    """Create a make compile command

    Args:

        keyboard
            The path of the keyboard, for example 'plank'

        keymap
            The name of the keymap, for example 'algernon'

        target
            Usually a bootloader.

        dry_run
            make -n -- don't actually build

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

    return create_make_target(':'.join(make_args), dry_run=dry_run, parallel=parallel, **env_vars)


def get_make_parallel_args(parallel=1):
    """Returns the arguments for running the specified number of parallel jobs.
    """
    parallel_args = []

    if int(parallel) <= 0:
        # 0 or -1 means -j without argument (unlimited jobs)
        parallel_args.append('--jobs')
    else:
        parallel_args.append('--jobs=' + str(parallel))

    if int(parallel) != 1:
        # If more than 1 job is used, synchronize parallel output by target
        parallel_args.append('--output-sync=target')

    return parallel_args


def compile_configurator_json(user_keymap, bootloader=None, parallel=1, clean=False, **env_vars):
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
    # In case the user passes a keymap.json from a keymap directory directly to the CLI.
    # e.g.: qmk compile - < keyboards/clueboard/california/keymaps/default/keymap.json
    user_keymap["keymap"] = user_keymap.get("keymap", "default_json")

    keyboard_filesafe = user_keymap['keyboard'].replace('/', '_')
    target = f'{keyboard_filesafe}_{user_keymap["keymap"]}'
    intermediate_output = Path(f'{INTERMEDIATE_OUTPUT_PREFIX}{keyboard_filesafe}_{user_keymap["keymap"]}')
    keymap_dir = intermediate_output / 'src'
    keymap_json = keymap_dir / 'keymap.json'

    if clean:
        if intermediate_output.exists():
            shutil.rmtree(intermediate_output)

    # begin with making the deepest folder in the tree
    keymap_dir.mkdir(exist_ok=True, parents=True)

    # Compare minified to ensure consistent comparison
    new_content = json.dumps(user_keymap, separators=(',', ':'))
    if keymap_json.exists():
        old_content = json.dumps(json.loads(keymap_json.read_text(encoding='utf-8')), separators=(',', ':'))
        if old_content == new_content:
            new_content = None

    # Write the keymap.json file if different
    if new_content:
        keymap_json.write_text(new_content, encoding='utf-8')

    # Return a command that can be run to make the keymap and flash if given
    verbose = 'true' if cli.config.general.verbose else 'false'
    color = 'true' if cli.config.general.color else 'false'
    make_command = [_find_make()]

    if not cli.config.general.verbose:
        make_command.append('-s')

    make_command.extend([
        *get_make_parallel_args(parallel),
        '-r',
        '-R',
        '-f',
        'builddefs/build_keyboard.mk',
    ])

    if bootloader:
        make_command.append(bootloader)

    make_command.extend([
        f'KEYBOARD={user_keymap["keyboard"]}',
        f'KEYMAP={user_keymap["keymap"]}',
        f'KEYBOARD_FILESAFE={keyboard_filesafe}',
        f'TARGET={target}',
        f'INTERMEDIATE_OUTPUT={intermediate_output}',
        f'MAIN_KEYMAP_PATH_1={intermediate_output}',
        f'MAIN_KEYMAP_PATH_2={intermediate_output}',
        f'MAIN_KEYMAP_PATH_3={intermediate_output}',
        f'MAIN_KEYMAP_PATH_4={intermediate_output}',
        f'MAIN_KEYMAP_PATH_5={intermediate_output}',
        f'KEYMAP_JSON={keymap_json}',
        f'KEYMAP_PATH={keymap_dir}',
        f'VERBOSE={verbose}',
        f'COLOR={color}',
        'SILENT=false',
        'QMK_BIN="qmk"',
    ])

    for key, value in env_vars.items():
        make_command.append(f'{key}={value}')

    return make_command


def parse_configurator_json(configurator_file):
    """Open and parse a configurator json export
    """
    user_keymap = json_load(configurator_file)
    # Validate against the jsonschema
    try:
        validate(user_keymap, 'qmk.keymap.v1')

    except jsonschema.ValidationError as e:
        cli.log.error(f'Invalid JSON keymap: {configurator_file} : {e.message}')
        exit(1)

    keyboard = user_keymap['keyboard']
    aliases = json_load(Path('data/mappings/keyboard_aliases.hjson'))

    while keyboard in aliases:
        last_keyboard = keyboard
        keyboard = aliases[keyboard].get('target', keyboard)
        if keyboard == last_keyboard:
            break

    user_keymap['keyboard'] = keyboard
    return user_keymap


def build_environment(args):
    """Common processing for cli.args.env
    """
    envs = {}
    for env in args:
        if '=' in env:
            key, value = env.split('=', 1)
            envs[key] = value
        else:
            cli.log.warning('Invalid environment variable: %s', env)
    return envs


def in_virtualenv():
    """Check if running inside a virtualenv.
    Based on https://stackoverflow.com/a/1883251
    """
    active_prefix = getattr(sys, "base_prefix", None) or getattr(sys, "real_prefix", None) or sys.prefix
    return active_prefix != sys.prefix


def dump_lines(output_file, lines, quiet=True):
    """Handle dumping to stdout or file
    Creates parent folders if required
    """
    generated = '\n'.join(lines) + '\n'
    if output_file and output_file.name != '-':
        output_file.parent.mkdir(parents=True, exist_ok=True)
        if output_file.exists():
            output_file.replace(output_file.parent / (output_file.name + '.bak'))
        output_file.write_text(generated, encoding='utf-8')

        if not quiet:
            cli.log.info(f'Wrote {output_file.name} to {output_file}.')
    else:
        print(generated)
