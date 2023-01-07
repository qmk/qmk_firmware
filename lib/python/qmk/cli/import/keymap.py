from milc import cli

from qmk.importers import import_keymap as _import_keymap
from qmk.path import FileType
from qmk.json_schema import json_load


@cli.argument('filename', type=FileType('r'), nargs='+', arg_only=True, help='file')
@cli.subcommand('Import data-driven keymap')
def import_keymap(cli):
    filename = cli.args.filename[0]

    data = json_load(filename)

    cli.log.info(f'{{style_bright}}Importing {filename.name}.{{style_normal}}')
    cli.echo('')

    kb_name, km_name = _import_keymap(data)

    cli.log.info(f'{{fg_green}}Imported a new keymap named {{fg_cyan}}{km_name}{{fg_green}}.{{fg_reset}}')
    cli.log.info(f'To start working on things, `cd` into {{fg_cyan}}keyboards/{kb_name}/keymaps/{km_name}{{fg_reset}},')
    cli.log.info('or open the directory in your preferred text editor.')
    cli.log.info(f"And build with {{fg_yellow}}qmk compile -kb {kb_name} -km {km_name}{{fg_reset}}.")
