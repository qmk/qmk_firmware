"""Generate a keymap.c from a configurator export.
"""
import json

from milc import cli

import qmk.keymap
import qmk.path
from qmk.info import info_json, _find_all_layouts


@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('filename', type=qmk.path.normpath, arg_only=True, help='VIA Backup JSON file')
@cli.argument('-kb', '--keyboard', arg_only=True, required=True, help='The keyboard\'s name')
# @cli.argument('-km', '--keymap', arg_only=True, required=True, help='The keymap\'s name')
@cli.argument('-l', '--layout', arg_only=True, required=True, help='The keymap\'s layout')
@cli.subcommand('Convert a VIA backup json to keymap.json format.')
def via2json(cli):
    """Convert a VIA backup json to keymap.json format.

    This command uses the `qmk.keymap` module to generate a keymap.json from a VIA backup json. The generated keymap is written to stdout, or to a file if -o is provided.
    """
    # Error checking
    if cli.args.filename and cli.args.filename.name == '-':
        # TODO(skullydazed/anyone): Read file contents from STDIN
        cli.log.error('Reading from STDIN is not (yet) supported.')
        cli.print_usage()
        exit(1)

    if not cli.args.filename.exists():
        cli.log.error('JSON file does not exist!')
        cli.print_usage()
        exit(1)

    if not qmk.path.is_keyboard(cli.args.keyboard):
        cli.log.error('Keyboard %s does not exist!', cli.args.keyboard)
        exit(1)

    # Environment processing
    if cli.args.output and cli.args.output.name == '-':
        cli.args.output = None

    # Parse the configurator json
    with cli.args.filename.open('r') as fd:
        via_backup = json.load(fd)

    # breakpoint()
    layout_data, macro_data = _find_all_layouts(cli.args.keyboard)

    temp_keycodes = []
    for layer in via_backup['layers']:
        temp_layer = {}
        for m in macro_data[cli.args.layout]['matrix']:
            for pos in m:
                kc = layer.pop(0)
                if pos != 'KC_NO':
                    temp_layer[pos] = kc if not kc.startswith('MACRO') else 'KC_NO'
        temp_keycodes.append(temp_layer)

    keycodes = []
    index_map = {v: i for i, v in enumerate(macro_data['LAYOUT_all']['layout'])}
    for layer in temp_keycodes:
        keycodes.append([kc[1] for kc in sorted(layer.items(), key=lambda pair: index_map[pair[0]])])



    # Try to figure out a name for the keymap
    keymap_name = cli.config.via2json.name or cli.config.via2json.keymap or 'via2json'
    # Generate the keymap
    keymap_json = qmk.keymap.generate(cli.args.keyboard, cli.args.layout, keycodes, 'json', keymap_name)

    if cli.args.output:
        cli.args.output.parent.mkdir(parents=True, exist_ok=True)
        if cli.args.output.exists():
            cli.args.output.replace(cli.args.output.name + '.bak')
        cli.args.output.write_text(json.dumps(keymap_json))

        if not cli.args.quiet:
            cli.log.info('Wrote keymap to %s.', cli.args.output)

    else:
        print(keymap_json)
