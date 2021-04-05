"""Functions that help us generate and use info.json files.
"""
import json
from collections.abc import Mapping
from pathlib import Path

import hjson
import jsonschema
from milc import cli


def json_load(json_file):
    """Load a json file from disk.

    Note: file must be a Path object.
    """
    try:
        return hjson.load(json_file.open(encoding='utf-8'))

    except json.decoder.JSONDecodeError as e:
        cli.log.error('Invalid JSON encountered attempting to load {fg_cyan}%s{fg_reset}:\n\t{fg_red}%s', json_file, e)
        exit(1)


def load_jsonschema(schema_name):
    """Read a jsonschema file from disk.

    FIXME(skullydazed/anyone): Refactor to make this a public function.
    """
    schema_path = Path(f'data/schemas/{schema_name}.jsonschema')

    if not schema_path.exists():
        schema_path = Path('data/schemas/false.jsonschema')

    return json_load(schema_path)


def keyboard_validate(data):
    """Validates data against the keyboard jsonschema.
    """
    schema = load_jsonschema('keyboard')
    validator = jsonschema.Draft7Validator(schema).validate

    return validator(data)


def keyboard_api_validate(data):
    """Validates data against the api_keyboard jsonschema.
    """
    base = load_jsonschema('keyboard')
    relative = load_jsonschema('api_keyboard')
    resolver = jsonschema.RefResolver.from_schema(base)
    validator = jsonschema.Draft7Validator(relative, resolver=resolver).validate

    return validator(data)


def deep_update(origdict, newdict):
    """Update a dictionary in place, recursing to do a deep copy.
    """
    for key, value in newdict.items():
        if isinstance(value, Mapping):
            origdict[key] = deep_update(origdict.get(key, {}), value)

        else:
            origdict[key] = value

    return origdict
