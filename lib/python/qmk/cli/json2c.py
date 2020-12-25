"""Generate a keymap.c from a configurator export.
"""
import json
import sys

from milc import cli

import qmk.keymap
import qmk.path


@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('filename', type=qmk.path.normpath, arg_only=True, help='Configurator JSON file')
@cli.subcommand('Creates a keymap.c from a QMK Configurator export.')
def json2c(cli):
    """Generate a keymap.c from a configurator export.

    This command uses the `qmk.keymap` module to generate a keymap.c from a configurator export. The generated keymap is written to stdout, or to a file if -o is provided.
    """

    # Parse the configurator from stdin
    if cli.args.filename and cli.args.filename.name == '-':
        try:
            user_keymap = json.load(sys.stdin)
        except json.decoder.JSONDecodeError as ex:
            cli.log.error(ex.__class__.__name__)
            cli.log.error(ex)
            return False

    else:
        # Error checking
        if not cli.args.filename.exists():
            cli.log.error('JSON file does not exist!')
            cli.print_usage()
            return False

        # Parse the configurator json
        with cli.args.filename.open('r') as fd:
            try:
                user_keymap = json.load(fd)
            except json.decoder.JSONDecodeError as ex:
                cli.log.error(ex.__class__.__name__)
                cli.log.error(ex)
                return False

    # Environment processing
    if cli.args.output and cli.args.output.name == '-':
        cli.args.output = None

    # Generate the keymap
    keymap_c = qmk.keymap.generate_c(user_keymap['keyboard'], user_keymap['layout'], user_keymap['layers'])

    if cli.args.output:
        cli.args.output.parent.mkdir(parents=True, exist_ok=True)
        if cli.args.output.exists():
            cli.args.output.replace(cli.args.output.name + '.bak')
        cli.args.output.write_text(keymap_c)

        if not cli.args.quiet:
            cli.log.info('Wrote keymap to %s.', cli.args.output)

    else:
        print(keymap_c)
