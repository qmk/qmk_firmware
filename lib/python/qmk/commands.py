"""Helper functions for commands.
"""
import os
import sys
import shutil
from pathlib import Path

from milc import cli
import jsonschema

from qmk.json_schema import json_load, validate


def find_make():
    """Returns the correct make command for this environment.
    """
    make_cmd = os.environ.get('MAKE')

    if not make_cmd:
        make_cmd = 'gmake' if shutil.which('gmake') else 'make'

    return make_cmd


def get_make_parallel_args(parallel=1):
    """Returns the arguments for running the specified number of parallel jobs.
    """
    parallel_args = []

    if int(parallel) <= 0:
        # 0 or -1 means -j without argument (unlimited jobs)
        parallel_args.append('--jobs')
    elif int(parallel) > 1:
        parallel_args.append('--jobs=' + str(parallel))

    if int(parallel) != 1:
        # If more than 1 job is used, synchronize parallel output by target
        parallel_args.append('--output-sync=target')

    return parallel_args


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
