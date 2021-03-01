"""Keyboard information script.

Compile an info.json for a particular keyboard and pretty-print it.
"""
import json

from jsonschema import Draft7Validator, validators
from milc import cli

from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.info import info_json, _jsonschema
from qmk.info_json_encoder import InfoJSONEncoder
from qmk.path import is_keyboard


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


@cli.argument('-kb', '--keyboard', help='Keyboard to show info for.')
@cli.argument('-km', '--keymap', help='Show the layers for a JSON keymap too.')
@cli.subcommand('Generate an info.json file for a keyboard.', hidden=False if cli.config.user.developer else True)
@automagic_keyboard
@automagic_keymap
def generate_info_json(cli):
    """Generate an info.json file for a keyboard
    """
    # Determine our keyboard(s)
    if not cli.config.generate_info_json.keyboard:
        cli.log.error('Missing parameter: --keyboard')
        cli.subcommands['info'].print_help()
        return False

    if not is_keyboard(cli.config.generate_info_json.keyboard):
        cli.log.error('Invalid keyboard: "%s"', cli.config.generate_info_json.keyboard)
        return False

    # Build the info.json file
    kb_info_json = info_json(cli.config.generate_info_json.keyboard)
    strip_info_json(kb_info_json)

    # Display the results
    print(json.dumps(kb_info_json, indent=2, cls=InfoJSONEncoder))
