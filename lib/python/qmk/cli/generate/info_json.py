"""Keyboard information script.

Compile an info.json for a particular keyboard and pretty-print it.
"""
import json

from argcomplete.completers import FilesCompleter
from jsonschema import Draft202012Validator, RefResolver, validators
from milc import cli
from pathlib import Path

from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.info import info_json
from qmk.json_encoders import InfoJSONEncoder
from qmk.json_schema import compile_schema_store
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.path import is_keyboard, normpath


def pruning_validator(validator_class):
    """Extends Draft202012Validator to remove properties that aren't specified in the schema.
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
    schema_store = compile_schema_store()
    pruning_draft_validator = pruning_validator(Draft202012Validator)
    schema = schema_store['qmk.keyboard.v1']
    resolver = RefResolver.from_schema(schema_store['qmk.keyboard.v1'], store=schema_store)
    validator = pruning_draft_validator(schema, resolver=resolver).validate

    return validator(kb_info_json)


@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='Keyboard to show info for.')
@cli.argument('-km', '--keymap', help='Show the layers for a JSON keymap too.')
@cli.argument('-o', '--output', arg_only=True, completer=FilesCompleter, help='Write the output the specified file, overwriting if necessary.')
@cli.argument('-ow', '--overwrite', arg_only=True, action='store_true', help='Overwrite the existing info.json. (Overrides the location of --output)')
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

    if cli.args.overwrite:
        output_path = (Path('keyboards') / cli.config.generate_info_json.keyboard / 'info.json').resolve()

        if cli.args.output:
            cli.log.warning('Overwriting user supplied --output with %s', output_path)

        cli.args.output = output_path

    # Build the info.json file
    kb_info_json = info_json(cli.config.generate_info_json.keyboard)
    strip_info_json(kb_info_json)
    info_json_text = json.dumps(kb_info_json, indent=4, cls=InfoJSONEncoder)

    if cli.args.output:
        # Write to a file
        output_path = normpath(cli.args.output)

        if output_path.exists():
            cli.log.warning('Overwriting output file %s', output_path)

        output_path.write_text(info_json_text + '\n')
        cli.log.info('Wrote info.json to %s.', output_path)

    else:
        # Display the results
        print(info_json_text)
