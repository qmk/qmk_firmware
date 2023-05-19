"""Generate a keymap.c from a configurator export.
"""
from argcomplete.completers import FilesCompleter
from milc import cli

import qmk.keymap
import qmk.path
from qmk.commands import parse_configurator_json


@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-u', '--update', arg_only=True, action='store_true', help="Update the keymap in the file specified in the --output option, rather than overwrite the whole file")
@cli.argument('filename', type=qmk.path.FileType('r'), arg_only=True, completer=FilesCompleter('.json'), help='Configurator JSON file')
@cli.subcommand('Creates a keymap.c from a QMK Configurator export.')
def json2c(cli):
    """Generate a keymap.c from a configurator export.

    This command uses the `qmk.keymap` module to generate a keymap.c from a configurator export. The generated keymap is written to stdout, or to a file if -o is provided.
    """

    # Parse the configurator from json file (or stdin)
    user_keymap = parse_configurator_json(cli.args.filename)

    # Environment processing
    if cli.args.output and cli.args.output.name == '-':
        cli.args.output = None

    # Generate the keymap
    keymap_c = qmk.keymap.generate_c(user_keymap)

    # If an output files was specified... 
    if cli.args.output:
        cli.args.output.parent.mkdir(parents=True, exist_ok=True)
        
        # If updating that file was requested...
        if cli.args.update:
            if cli.args.output.exists():
                
                # Use regex to isolate the keymap definition only and replace it in the target file
                import re
                keymap_only = (re.search('const uint16_t PROGMEM keymaps.+?};', keymap_c, re.DOTALL)).group()
                with open(cli.args.output, "r") as f:
                    keymap_old = f.read()
                keymap_new = re.sub(r"const uint16_t PROGMEM keymaps.+?};", keymap_only, keymap_old, 1, re.DOTALL)
                cli.args.output.replace(cli.args.output.parent / (cli.args.output.name + '.bak'))
                cli.args.output.write_text(keymap_new)
                if not cli.args.quiet:
                    cli.log.info('Updated keymap at %s.', cli.args.output)

            else:
                cli.log.error('Update flag given, but the target file does not exist: %s', cli.args.output)
        
        # Not updating, just overwrite or add a new file
        else:
            if cli.args.output.exists():
                cli.args.output.replace(cli.args.output.parent / (cli.args.output.name + '.bak'))
            cli.args.output.write_text(keymap_c)
            if not cli.args.quiet:
                cli.log.info('Wrote keymap to %s.', cli.args.output)
    
    # No output file specified, just print the result
    else:
        print(keymap_c)
