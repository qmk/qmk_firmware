"""Functions that help us generate and use info.json files.
"""
import json
from collections.abc import Mapping
from functools import lru_cache
from pathlib import Path

import hjson
import jsonschema
from milc import cli


def json_load(json_file):
    """Load a json file from disk.

    Note: file must be a Path object.
    """
    try:
        # Get the IO Stream for Path objects
        # Not necessary if the data is provided via stdin
        if isinstance(json_file, Path):
            json_file = json_file.open(encoding='utf-8')
        return hjson.load(json_file)

    except (json.decoder.JSONDecodeError, hjson.HjsonDecodeError) as e:
        cli.log.error('Invalid JSON encountered attempting to load {fg_cyan}%s{fg_reset}:\n\t{fg_red}%s', json_file, e)
        exit(1)
    except Exception as e:
        cli.log.error('Unknown error attempting to load {fg_cyan}%s{fg_reset}:\n\t{fg_red}%s', json_file, e)
        exit(1)


@lru_cache(maxsize=0)
def load_jsonschema(schema_name):
    """Read a jsonschema file from disk.
    """
    if Path(schema_name).exists():
        return json_load(schema_name)

    schema_path = Path(f'data/schemas/{schema_name}.jsonschema')

    if not schema_path.exists():
        schema_path = Path('data/schemas/false.jsonschema')

    return json_load(schema_path)


@lru_cache(maxsize=0)
def compile_schema_store():
    """Compile all our schemas into a schema store.
    """
    schema_store = {}

    for schema_file in Path('data/schemas').glob('*.jsonschema'):
        schema_data = load_jsonschema(schema_file)
        if not isinstance(schema_data, dict):
            cli.log.debug('Skipping schema file %s', schema_file)
            continue
        schema_store[schema_data['$id']] = schema_data

    return schema_store


@lru_cache(maxsize=0)
def create_validator(schema):
    """Creates a validator for the given schema id.
    """
    schema_store = compile_schema_store()
    resolver = jsonschema.RefResolver.from_schema(schema_store[schema], store=schema_store)

    return jsonschema.Draft7Validator(schema_store[schema], resolver=resolver).validate


def validate(data, schema):
    """Validates data against a schema.
    """
    validator = create_validator(schema)

    return validator(data)


def deep_update(origdict, newdict):
    """Update a dictionary in place, recursing to do a depth-first deep copy.
    """
    for key, value in newdict.items():
        if isinstance(value, Mapping):
            origdict[key] = deep_update(origdict.get(key, {}), value)

        else:
            origdict[key] = value

    return origdict
