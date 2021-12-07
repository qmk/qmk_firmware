"""Generate a keymap.c from a configurator export.
"""
import json

from argcomplete.completers import FilesCompleter
from milc import cli

from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.info import info_json
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.keymap import locate_keymap
import qmk.keymap
import qmk.path


@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='Keyboard to convert keymap for')
@cli.argument('-km', '--keymap', help='Keymap to save the output of json2c')
@cli.argument('-s', '--save', arg_only=True, action='store_true', help="Save the keymap file")
@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('filename', type=qmk.path.FileType('r'), arg_only=True, completer=FilesCompleter('.json'), help='Configurator JSON file')
@cli.subcommand('Creates a keymap.c from a QMK Configurator export.')
@automagic_keyboard
@automagic_keymap
def json2c(cli):
    """Generate a keymap.c from a configurator export.

    This command uses the `qmk.keymap` module to generate a keymap.c from a configurator export. The generated keymap is written to stdout, or to a file if -o is provided.
    """

    try:
        # Parse the configurator from json file (or stdin)
        user_keymap = json.load(cli.args.filename)

    except json.decoder.JSONDecodeError as ex:
        cli.log.error('The JSON input does not appear to be valid.')
        cli.log.error(ex)
        return False

    # Environment processing
    if cli.args.output and cli.args.output.name == '-':
        cli.args.output = None

    # Generate the keymap
    kb_info_json = None
    if cli.config.info.keyboard:
        kb_info_json = info_json(cli.config.info.keyboard)

    keymap_c = qmk.keymap.generate_c(user_keymap, kb_info_json)

    if cli.config.info.keyboard and cli.config.info.keymap and cli.args.save:
        keymap_path = locate_keymap(cli.config.info.keyboard, cli.config.info.keymap)
        if keymap_path and keymap_path.suffix == '.c':
            keymap_path.replace(keymap_path.parent / (keymap_path.name + '.bak'))
            keymap_path.write_text(keymap_c)
        cli.log.info("Wrote keymap to %s. ", keymap_path)
    elif cli.args.output:
        cli.args.output.parent.mkdir(parents=True, exist_ok=True)
        if cli.args.output.exists():
            cli.args.output.replace(cli.args.output.parent / (cli.args.output.name + '.bak'))
        cli.args.output.write_text(keymap_c)

        if not cli.args.quiet:
            cli.log.info('Wrote keymap to %s.', cli.args.output)

    else:
        print(keymap_c)
