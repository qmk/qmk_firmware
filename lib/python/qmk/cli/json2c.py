"""Generate a keymap.c from a configurator export.
"""
from argcomplete.completers import FilesCompleter
from milc import cli

import qmk.keymap
import qmk.path
from qmk.commands import dump_lines, parse_configurator_json


@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('filename', type=qmk.path.FileType('r'), arg_only=True, completer=FilesCompleter('.json'), help='Configurator JSON file')
@cli.subcommand('Creates a keymap.c from a QMK Configurator export.')
def json2c(cli):
    """Generate a keymap.c from a configurator export.

    This command uses the `qmk.keymap` module to generate a keymap.c from a configurator export. The generated keymap is written to stdout, or to a file if -o is provided.
    """

    # Parse the configurator from json file (or stdin)
    user_keymap = parse_configurator_json(cli.args.filename)

    # Generate the keymap
    keymap_c = qmk.keymap.generate_c(user_keymap)

    # Show the results
    dump_lines(cli.args.output, keymap_c.split('\n'), cli.args.quiet)
