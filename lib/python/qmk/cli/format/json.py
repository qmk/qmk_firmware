"""JSON Formatting Script

Spits out a JSON file formatted with one of QMK's formatters.
"""
import json
import sys

from jsonschema import ValidationError
from milc import cli

from qmk.info import info_json
from qmk.json_schema import json_load, validate
from qmk.json_encoders import InfoJSONEncoder, KeymapJSONEncoder
from . import qmk_formatter


@cli.argument('-f', '--format', choices=['auto', 'keyboard', 'keymap'], default='auto', arg_only=True, help='JSON formatter to use (Default: autodetect)')
@qmk_formatter
def format_json(cli, file):
    """Format a json file.
    """
    json_file = json_load(file)

    if cli.args.format == 'auto':
        try:
            validate(json_file, 'qmk.keyboard.v1')
            json_encoder = InfoJSONEncoder

        except ValidationError as e:
            cli.log.warning('File %s did not validate as a keyboard:\n\t%s', cli.args.json_file, e)
            cli.log.info('Treating %s as a keymap file.', cli.args.json_file)
            json_encoder = KeymapJSONEncoder
    elif cli.args.format == 'keyboard':
        json_encoder = InfoJSONEncoder
    elif cli.args.format == 'keymap':
        json_encoder = KeymapJSONEncoder
    else:
        # This should be impossible
        cli.log.error('Unknown format: %s', cli.args.format)
        return False

    if json_encoder == KeymapJSONEncoder and 'layout' in json_file:
        # Attempt to format the keycodes.
        layout = json_file['layout']
        info_data = info_json(json_file['keyboard'])

        if layout in info_data.get('layout_aliases', {}):
            layout = json_file['layout'] = info_data['layout_aliases'][layout]

        if layout in info_data.get('layouts'):
            for layer_num, layer in enumerate(json_file['layers']):
                current_layer = []
                last_row = 0

                for keymap_key, info_key in zip(layer, info_data['layouts'][layout]['layout']):
                    if last_row != info_key['y']:
                        current_layer.append('JSON_NEWLINE')
                        last_row = info_key['y']

                    current_layer.append(keymap_key)

                json_file['layers'][layer_num] = current_layer

    # Display the results
    out = open(file, "w") if cli.args.inplace else sys.stdout
    print(
        json.dumps(json_file, cls=json_encoder, sort_keys=True),
        file=out
    )
    cli.log.info(f'Json file correctly formatted! ({file})')
    out.close()
