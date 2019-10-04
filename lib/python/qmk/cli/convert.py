"""Convert KLE to JSON

"""
import json
from qmk.kle2xy import KLE2xy
from milc import cli
from argparse import FileType
from collections import OrderedDict
from decimal import Decimal
from flask.json import JSONEncoder

def kle_to_qmk(kle):
    """Convert a kle layout to qmk's layout format.
    """
    layout = []

    for row in kle:
        for key in row:
            if key['decal']:
                continue

            qmk_key = OrderedDict(
                label="",
                x=key['column'],
                y=key['row'],
            )

            if key['width'] != 1:
                qmk_key['w'] = key['width']
            if key['height'] != 1:
                qmk_key['h'] = key['height']
            if 'name' in key and key['name']:
                qmk_key['label'] = key['name'].split('\n', 1)[0]
            else:
                del (qmk_key['label'])

            layout.append(qmk_key)

    return layout

class CustomJSONEncoder(JSONEncoder):
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
        layout = json.dumps(kle_to_qmk(kle), separators=(', ', ':'), cls=CustomJSONEncoder)
        keyboard = keyboard.replace('"LAYOUT_JSON_HERE"', layout)

        file = open("info.json","w")
        file.write(keyboard)
        file.close()





