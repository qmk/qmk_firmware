"""JSON Formatting Script

Spits out a JSON file formatted with one of QMK's formatters.
"""
import json

from jsonschema import Draft7Validator, validators, ValidationError
from milc import cli

from qmk.info import _jsonschema, _json_load, info_json, keyboard_validate
from qmk.json_encoders import InfoJSONEncoder, KeymapJSONEncoder
from qmk.path import normpath


def pruning_validator(validator_class):
    """Extends Draft7Validator to remove properties that aren't specified in the schema.
    """
    validate_properties = validator_class.VALIDATORS["properties"]

    def remove_additional_properties(validator, properties, instance, schema):
        for prop in list(instance.keys()):
            if prop not in properties:
                del instance[prop]

        for error in validate_properties(validator, properties, instance, schema):
            yield error

    return validators.extend(validator_class, {"properties": remove_additional_properties})


def strip_info_json(kb_info_json):
    """Remove the API-only properties from the info.json.
    """
    pruning_draft_7_validator = pruning_validator(Draft7Validator)
    schema = _jsonschema('keyboard')
    validator = pruning_draft_7_validator(schema).validate

    return validator(kb_info_json)


@cli.argument('json_file', arg_only=True, type=normpath, help='JSON file to format')
@cli.argument('-f', '--format', choices=['auto', 'keyboard', 'keymap'], default='auto', arg_only=True, help='JSON formatter to use (Default: autodetect)')
@cli.subcommand('Generate an info.json file for a keyboard.', hidden=False if cli.config.user.developer else True)
def format_json(cli):
    """Format a json file.
    """
    json_file = _json_load(cli.args.json_file)

    if cli.args.format == 'auto':
        try:
            keyboard_validate(json_file)
            cli.args.format = 'keyboard'

        except ValidationError as e:
            print('hrm', e, e.__class__.__name__)
            cli.log.exception(e)
            cli.args.format = 'keymap'

    json_encoder = InfoJSONEncoder if cli.args.format == 'keyboard' else KeymapJSONEncoder

    if cli.args.format == 'keymap':
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
    print(json.dumps(json_file, cls=json_encoder))
