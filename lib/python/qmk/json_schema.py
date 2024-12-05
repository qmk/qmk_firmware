"""Functions that help us generate and use info.json files.
"""
import json
import hjson
import jsonschema
from collections.abc import Mapping
from functools import lru_cache
from typing import OrderedDict
from pathlib import Path
from copy import deepcopy

from milc import cli

from qmk.util import maybe_exit


def _dict_raise_on_duplicates(ordered_pairs):
    """Reject duplicate keys."""
    d = {}
    for k, v in ordered_pairs:
        if k in d:
            raise ValueError("duplicate key: %r" % (k,))
        else:
            d[k] = v
    return d


@lru_cache(maxsize=20)
def _json_load_impl(json_file, strict=True):
    """Load a json file from disk.

    Note: file must be a Path object.
    """
    try:
        # Get the IO Stream for Path objects
        # Not necessary if the data is provided via stdin
        if isinstance(json_file, Path):
            json_file = json_file.open(encoding='utf-8')
        return hjson.load(json_file, object_pairs_hook=_dict_raise_on_duplicates if strict else None)

    except (json.decoder.JSONDecodeError, hjson.HjsonDecodeError) as e:
        cli.log.error('Invalid JSON encountered attempting to load {fg_cyan}%s{fg_reset}:\n\t{fg_red}%s', json_file, e)
        maybe_exit(1)
    except Exception as e:
        cli.log.error('Unknown error attempting to load {fg_cyan}%s{fg_reset}:\n\t{fg_red}%s', json_file, e)
        maybe_exit(1)


def json_load(json_file, strict=True):
    return deepcopy(_json_load_impl(json_file=json_file, strict=strict))


@lru_cache(maxsize=20)
def load_jsonschema(schema_name):
    """Read a jsonschema file from disk.
    """
    if Path(schema_name).exists():
        return json_load(schema_name)

    schema_path = Path(f'data/schemas/{schema_name}.jsonschema')

    if not schema_path.exists():
        schema_path = Path('data/schemas/false.jsonschema')

    return json_load(schema_path)


@lru_cache(maxsize=1)
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


@lru_cache(maxsize=20)
def create_validator(schema):
    """Creates a validator for the given schema id.
    """
    schema_store = compile_schema_store()
    resolver = jsonschema.RefResolver.from_schema(schema_store[schema], store=schema_store)

    return jsonschema.Draft202012Validator(schema_store[schema], resolver=resolver).validate


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


def merge_ordered_dicts(dicts):
    """Merges nested OrderedDict objects resulting from reading a hjson file.
    Later input dicts overrides earlier dicts for plain values.
    If any value is "!delete!", the existing value will be removed from its parent.
    Arrays will be appended. If the first entry of an array is "!reset!", the contents of the array will be cleared and replaced with RHS.
    Dictionaries will be recursively merged. If any entry is "!reset!", the contents of the dictionary will be cleared and replaced with RHS.
    """
    result = OrderedDict()

    def add_entry(target, k, v):
        if k in target and isinstance(v, (OrderedDict, dict)):
            if "!reset!" in v:
                target[k] = v
            else:
                target[k] = merge_ordered_dicts([target[k], v])
            if "!reset!" in target[k]:
                del target[k]["!reset!"]
        elif k in target and isinstance(v, list):
            if v[0] == '!reset!':
                target[k] = v[1:]
            else:
                target[k] = target[k] + v
        elif v == "!delete!" and isinstance(target, (OrderedDict, dict)):
            del target[k]
        else:
            target[k] = v

    for d in dicts:
        for (k, v) in d.items():
            add_entry(result, k, v)

    return result
