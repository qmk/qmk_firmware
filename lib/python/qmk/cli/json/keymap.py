"""Generate a keymap.c from a configurator export.
"""
import json
from pathlib import Path

from milc import cli

import qmk.keymap
import qmk.path


@cli.argument('-o', '--output', arg_only=True, type=Path, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('filename', arg_only=True, help='Configurator JSON file')
@cli.subcommand('Creates a keymap.c from a QMK Configurator export.')
def json_keymap(cli):
    """Generate a keymap.c from a configurator export.

    This command uses the `qmk.keymap` module to generate a keymap.c from a configurator export. The generated keymap is written to stdout, or to a file if -o is provided.
    """
    cli.args.filename = qmk.path.normpath(cli.args.filename)

    # Error checking
    if not cli.args.filename.exists():
        cli.log.error('JSON file does not exist!')
        cli.print_usage()
        exit(1)

    if str(cli.args.filename) == '-':
        # TODO(skullydazed/anyone): Read file contents from STDIN
        cli.log.error('Reading from STDIN is not (yet) supported.')
        cli.print_usage()
        exit(1)

    # Environment processing
    if cli.args.output == ('-'):
        cli.args.output = None

    # Parse the configurator json
    with cli.args.filename.open('r') as fd:
        user_keymap = json.load(fd)

    # Generate the keymap
    keymap_c = qmk.keymap.generate(user_keymap['keyboard'], user_keymap['layout'], user_keymap['layers'])

    if cli.args.output:
        cli.args.output.parent.mkdir(parents=True, exist_ok=True)
        if cli.args.output.exists():
            cli.args.output.replace(cli.args.output.name + '.bak')
        cli.args.output.write_text(keymap_c)

        if not cli.args.quiet:
            cli.log.info('Wrote keymap to %s.', cli.args.output)

    else:
        print(keymap_c)
