"""Helper functions for commands.
"""
import os
import sys
import json
import shutil
from pathlib import Path

from milc import cli
import jsonschema

from qmk.constants import QMK_FIRMWARE, INTERMEDIATE_OUTPUT_PREFIX, QMK_USERSPACE, HAS_QMK_USERSPACE
from qmk.json_schema import json_load, validate


def _find_make(make_override=None):
    """Returns the correct make command for this environment.
    """
    if make_override:
        return make_override

    make_cmd = os.environ.get('MAKE')

    if not make_cmd:
        make_cmd = 'gmake' if shutil.which('gmake') else 'make'

    return make_cmd


def create_make_target(target, dry_run=False, parallel=1, make_override=None, **env_vars):
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
    make_cmd = _find_make(make_override=make_override)

    for key, value in env_vars.items():
        env.append(f'{key}={value}')

    if HAS_QMK_USERSPACE:
        env.append(f'QMK_USERSPACE={Path(QMK_USERSPACE).resolve()}')

    if cli.config.general.verbose:
        env.append('VERBOSE=true')

    return [make_cmd, *(['-n'] if dry_run else []), *get_make_parallel_args(parallel), *env, target]


def create_make_command(keyboard, keymap, target=None, dry_run=False, parallel=1, make_override=None, **env_vars):
    """Create a make compile command

    Args:

        keyboard
            The path of the keyboard, for example 'plank'

        keymap
            The name of the keymap, for example 'algernon'

        target
            The build target to compile; usually the bootloader parameter to flash.

        dry_run
            make -n -- don't actually build

        parallel
            The number of make jobs to run in parallel

        **env_vars
            Environment variables to be passed to make.

    Returns:

        A command that can be run to make the specified keyboard and keymap
    """
    # Return a command that can be run to make the keymap and flash if given
    make_command = [_find_make(make_override=make_override)]

    if not cli.config.general.verbose:
        make_command.append('-s')

    if dry_run:
        make_command.append('-n')

    from qmk.keymap import locate_keymap
    keymap_location = locate_keymap(keyboard, keymap)
    keymap_path = keymap_location.parent

    make_command.extend([
        *get_make_parallel_args(parallel),
        '-r',
        '-R',
        '-f',
        'builddefs/build_keyboard.mk',
    ])

    if target:
        make_command.append(target)

    make_command.extend([
        f'KEYBOARD={keyboard}',
        f'KEYMAP={keymap}',
        'SILENT=false',
        'QMK_BIN="qmk"',
        f'MAIN_KEYMAP_PATH_1={keymap_path}',
        f'MAIN_KEYMAP_PATH_2={keymap_path}',
        f'MAIN_KEYMAP_PATH_3={keymap_path}',
        f'MAIN_KEYMAP_PATH_4={keymap_path}',
        f'MAIN_KEYMAP_PATH_5={keymap_path}',
    ])

    if cli.config.general.verbose:
        make_command.append('VERBOSE=true')

    if HAS_QMK_USERSPACE:
        make_command.append(f'QMK_USERSPACE={Path(QMK_USERSPACE).resolve()}')

    for key, value in env_vars.items():
        make_command.append(f'{key}={value}')

    return make_command


def get_make_parallel_args(parallel=1):
    """Returns the arguments for running the specified number of parallel jobs.
    """
    parallel_args = []

    if int(parallel) != 1:
        if int(parallel) <= 0:
            # 0 or -1 means -j without argument (unlimited jobs)
            parallel_args.append('--jobs')
        elif int(parallel) > 1:
            parallel_args.append('--jobs=' + str(parallel))
            # If more than 1 job is used, synchronize parallel output by target
        parallel_args.append('--output-sync=target')

    return parallel_args


def compile_configurator_json(user_keymap, target=None, parallel=1, make_override=None, clean=False, **env_vars):
    """Convert a configurator export JSON file into a C file and then compile it.

    Args:

        user_keymap
            A deserialized keymap export

        target
            The build target to compile; usually the bootloader parameter to flash.

        parallel
            The number of make jobs to run in parallel

    Returns:

        A command to run to compile and flash the C file.
    """
    # NOTE: this doesn't just generate the GNU Make command to execute, it also dumps the
    #       keymap.json file to the correct location for the build system to find it.
    #       Beware of using this func before executing a `make clean` -- it'll get nuked.
    #
    # In case the user passes a keymap.json from a keymap directory directly to the CLI.
    # e.g.: qmk compile - < keyboards/clueboard/california/keymaps/default/keymap.json
    user_keymap["keymap"] = user_keymap.get("keymap", "default_json")

    keyboard_filesafe = user_keymap['keyboard'].replace('/', '_')
    compile_target = f'{keyboard_filesafe}_{user_keymap["keymap"]}'
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
    make_command = [_find_make(make_override)]

    if not cli.config.general.verbose:
        make_command.append('-s')

    make_command.extend([
        *get_make_parallel_args(parallel),
        '-r',
        '-R',
        '-f',
        'builddefs/build_keyboard.mk',
    ])

    if target:
        make_command.append(target)

    make_command.extend([
        f'KEYBOARD={user_keymap["keyboard"]}',
        f'KEYMAP={user_keymap["keymap"]}',
        f'KEYBOARD_FILESAFE={keyboard_filesafe}',
        f'TARGET={compile_target}',
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

    if HAS_QMK_USERSPACE:
        make_command.append(f'QMK_USERSPACE={Path(QMK_USERSPACE).resolve()}')

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

    orig_keyboard = user_keymap['keyboard']
    aliases = json_load(Path('data/mappings/keyboard_aliases.hjson'))

    if orig_keyboard in aliases:
        if 'target' in aliases[orig_keyboard]:
            user_keymap['keyboard'] = aliases[orig_keyboard]['target']

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
