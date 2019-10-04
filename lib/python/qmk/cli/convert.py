"""Convert KLE to JSON

"""
import json
import os
from pathlib import Path
from argparse import FileType
from decimal import Decimal
from collections import OrderedDict

from milc import cli
from kle2xy import KLE2xy

from qmk.converter import kle2qmk

class CustomJSONEncoder(json.JSONEncoder):
    def default(self, obj):
        try:
            if isinstance(obj, Decimal):
                if obj % 2 in (Decimal(0), Decimal(1)):
                    return int(obj)
                return float(obj)
        except TypeError:
            pass
        return JSONEncoder.default(self, obj)

@cli.argument('filename', nargs='?', arg_only=True, type=FileType('r'), help='The KLE raw txt to convert')
@cli.subcommand('Convert a KLE layout to a configurator JSON')
def convert(cli):
    """Convert a KLE layout to QMK's layout format.
    """
    if cli.args.filename:
        if cli.args.filename.name[0] == "/" or cli.args.filename.name[0] == "./":
            file_path = Path(cli.args.filename.name)
            out_path = file_path.parent
        raw_code = str(cli.args.filename.read())
        try:
            kle = KLE2xy(raw_code)
        except Exception as e:
            cli.log.error('Could not parse KLE raw data: %s', raw_code)
            cli.log.exception(e)
            return cli.log.error('Could not parse KLE raw data.')  # FIXME: This should be better

        keyboard = OrderedDict(
            keyboard_name=kle.name,
            url='',
            maintainer='qmk',
            width=kle.columns,
            height=kle.rows,
            layouts={'LAYOUT': {
                'layout': 'LAYOUT_JSON_HERE'
            }},
        )
        keyboard = json.dumps(keyboard, indent=4, separators=(', ', ': '), sort_keys=False, cls=CustomJSONEncoder)
        layout = json.dumps(kle2qmk(kle), separators=(', ', ':'), cls=CustomJSONEncoder)
        keyboard = keyboard.replace('"LAYOUT_JSON_HERE"', layout)

        file = open(str(out_path) + "/info.json","w")
        file.write(keyboard)
        file.close()
        cli.log.info('Wrote keymap to {fg_cyan}%s/info.json', str(out_path))
    else:
        cli.log.error('You must supply a KLE raw export.')
        return False

