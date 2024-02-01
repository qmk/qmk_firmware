"""Generate a keymap.json from a keymap.c file.
"""
import re
import json

from argcomplete.completers import FilesCompleter
from milc import cli

import qmk.path
from qmk.json_encoders import InfoJSONEncoder
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.keymap import locate_keymap, find_keymap_from_dir, generate_json, c2json as c2json_impl
from qmk.errors import CppError
from qmk.commands import dump_lines


@cli.argument('--no-cpp', arg_only=True, action='store_false', help='Do not use \'cpp\' on keymap.c')
@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='The keyboard\'s name')
@cli.argument('-km', '--keymap', help='The keymap\'s name')
@cli.argument('filename', nargs='?', type=qmk.path.FileType('r'), arg_only=True, completer=FilesCompleter('.c'), help='keymap.c file')
@cli.subcommand('Creates a keymap.json from a keymap.c file.')
@automagic_keyboard
@automagic_keymap
def c2json(cli):
    """Generate a keymap.json from a keymap.c file.

    This command uses the `qmk.keymap` module to generate a keymap.json from a keymap.c file. The generated keymap is written to stdout, or to a file if -o is provided.
    """
    filename = cli.args.filename
    keyboard = cli.config.c2json.keyboard
    keymap = cli.config.c2json.keymap

    if filename:
        if not keyboard and not keymap:
            # fallback to inferring keyboard/keymap from path
            (keymap, found_type) = find_keymap_from_dir(filename)
            if found_type == 'keymap_directory':
                keyboard = re.search(fr"keyboards/(.+)/keymaps/{keymap}/.*", filename.as_posix()).group(1)

    elif keyboard and keymap:
        if not filename:
            # fallback to inferring keyboard/keymap from path
            filename = locate_keymap(keyboard, keymap)

    if not all((filename, keyboard, keymap)):
        cli.log.error('You must supply keyboard and keymap, a path to a keymap.c within qmk_firmware, or absolute filename and keyboard and keymap')
        cli.print_help()
        return False

    try:
        keymap_json = c2json_impl(keyboard, keymap, filename, use_cpp=cli.args.no_cpp)
    except CppError as e:
        if cli.config.general.verbose:
            cli.log.debug('The C pre-processor ran into a fatal error: %s', e)
        cli.log.error('Something went wrong. Try to use --no-cpp.\nUse the CLI in verbose mode to find out more.')
        return False

    # Generate the keymap.json
    try:
        keymap_json = generate_json(keymap_json['keymap'], keymap_json['keyboard'], keymap_json['layout'], keymap_json['layers'])
    except KeyError:
        cli.log.error('Something went wrong. Try to use --no-cpp.')
        return False

    if cli.args.output:
        keymap_lines = [json.dumps(keymap_json, cls=InfoJSONEncoder, sort_keys=True)]
    else:
        keymap_lines = [json.dumps(keymap_json)]

    dump_lines(cli.args.output, keymap_lines, cli.args.quiet)
