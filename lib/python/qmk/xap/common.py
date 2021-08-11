"""This script handles the XAP protocol data files.
"""
import re
import hjson
from typing import OrderedDict

from qmk.constants import QMK_FIRMWARE


def _merge_ordered_dicts(dicts):
    """Merges nested OrderedDict objects resulting from reading a hjson file.

    Later input dicts overrides earlier dicts for plain values.
    Arrays will be appended. If the first entry of an array is "!reset!", the contents of the array will be cleared and replaced with RHS.
    Dictionaries will be recursively merged. If any entry is "!reset!", the contents of the dictionary will be cleared and replaced with RHS.
    """

    result = OrderedDict()

    def add_entry(target, k, v):
        if k in target and isinstance(v, OrderedDict):
            if "!reset!" in v:
                target[k] = v
            else:
                target[k] = _merge_ordered_dicts([target[k], v])
            if "!reset!" in target[k]:
                del target[k]["!reset!"]
        elif k in target and isinstance(v, list):
            if v[0] == '!reset!':
                target[k] = v[1:]
            else:
                target[k] = target[k] + v
        else:
            target[k] = v

    for d in dicts:
        for (k, v) in d.items():
            add_entry(result, k, v)

    return result


def get_xap_definition_files():
    """Get the sorted list of XAP definition files, from <QMK>/data/xap.
    """
    xap_defs = QMK_FIRMWARE / "data" / "xap"
    return list(sorted(xap_defs.glob('**/xap_*.hjson')))


def update_xap_definitions(original, new):
    """Creates a new XAP definition object based on an original and the new supplied object.

    Both inputs must be of type OrderedDict.
    Later input dicts overrides earlier dicts for plain values.
    Arrays will be appended. If the first entry of an array is "!reset!", the contents of the array will be cleared and replaced with RHS.
    Dictionaries will be recursively merged. If any entry is "!reset!", the contents of the dictionary will be cleared and replaced with RHS.
    """
    if original is None:
        original = OrderedDict()
    return _merge_ordered_dicts([original, new])


def latest_xap_defs():
    """Gets the latest version of the XAP definitions.
    """
    definitions = [hjson.load(file.open(encoding='utf-8')) for file in get_xap_definition_files()]
    return _merge_ordered_dicts(definitions)


def route_conditions(route_stack):
    """Handles building the C preprocessor conditional based on the current route.
    """
    conditions = []
    for route in route_stack:
        if 'enable_if_preprocessor' in route:
            conditions.append(route['enable_if_preprocessor'])

    if len(conditions) == 0:
        return None

    return "(" + ' && '.join([f'({c})' for c in conditions]) + ")"
