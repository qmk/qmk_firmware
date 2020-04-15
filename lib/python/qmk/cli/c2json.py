"""Generate a keymap.json from a keymap.c file.
"""
import json

from milc import cli

import qmk.keymap
import qmk.path


@cli.argument('--no-cpp', arg_only=True, action='store_false', help='Do not use \'cpp\' on keymap.c')
@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('filename', arg_only=True, help='keymap.c file')
@cli.subcommand('Creates a keymap.json from a keymap.c file.')
def c2json(cli):
    """Generate a keymap.json from a keymap.c file.

    This command uses the `qmk.keymap` module to generate a keymap.json from a keymap.c file. The generated keymap is written to stdout, or to a file if -o is provided.
    """
    cli.args.filename = qmk.path.normpath(cli.args.filename)

    # Error checking
    if not cli.args.filename.exists():
        cli.log.error('C file does not exist!')
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

    keymap_json = qmk.keymap.parse_keymap_c(cli.args.filename, use_cpp=cli.args.no_cpp)

    if cli.args.output:
        cli.args.output.parent.mkdir(parents=True, exist_ok=True)
        if cli.args.output.exists():
            cli.args.output.replace(cli.args.output.name + '.bak')
        cli.args.output.write_text(json.dumps(keymap_json))

        if not cli.args.quiet:
            cli.log.info('Wrote keymap to %s.', cli.args.output)

    else:
        print(json.dumps(keymap_json))
