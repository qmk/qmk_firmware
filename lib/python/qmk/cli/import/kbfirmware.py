from milc import cli

from qmk.importers import import_kbfirmware as _import_kbfirmware
from qmk.path import FileType
from qmk.json_schema import json_load


@cli.argument('filename', type=FileType('r'), nargs='+', arg_only=True, help='file')
@cli.subcommand('Import kbfirmware json export')
def import_kbfirmware(cli):
    filename = cli.args.filename[0]

    data = json_load(filename)

    cli.log.info(f'{{style_bright}}Importing {filename.name}.{{style_normal}}')
    cli.echo('')

    cli.log.warning("Support here is basic - Consider using 'qmk new-keyboard' instead")

    kb_name = _import_kbfirmware(data)

    cli.log.info(f'{{fg_green}}Imported a new keyboard named {{fg_cyan}}{kb_name}{{fg_green}}.{{fg_reset}}')
    cli.log.info(f'To start working on things, `cd` into {{fg_cyan}}keyboards/{kb_name}{{fg_reset}},')
    cli.log.info('or open the directory in your preferred text editor.')
    cli.log.info(f"And build with {{fg_yellow}}qmk compile -kb {kb_name} -km default{{fg_reset}}.")
