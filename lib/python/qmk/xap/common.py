"""This script handles the XAP protocol data files.
"""
import hjson
import jsonschema
from pathlib import Path
from typing import OrderedDict
from jinja2 import Environment, FileSystemLoader, select_autoescape

import qmk.constants
from qmk.git import git_get_version
from qmk.lighting import load_lighting_spec
from qmk.json_schema import validate, merge_ordered_dicts
from qmk.makefile import parse_rules_mk_file
from qmk.decorators import lru_cache
from qmk.keymap import locate_keymap
from qmk.path import keyboard
from qmk.xap.jinja2_filters import attach_filters

USERSPACE_DIR = Path('users')
XAP_SPEC = 'xap.hjson'


def _get_jinja2_env(data_templates_xap_subdir: str):
    templates_dir = qmk.constants.QMK_FIRMWARE / 'data/templates/xap' / data_templates_xap_subdir
    j2 = Environment(loader=FileSystemLoader(templates_dir), autoescape=select_autoescape(), lstrip_blocks=True, trim_blocks=True)
    return j2


def render_xap_output(data_templates_xap_subdir, file_to_render, defs=None, **kwargs):
    if defs is None:
        defs = latest_xap_defs()
    j2 = _get_jinja2_env(data_templates_xap_subdir)

    attach_filters(j2)

    specs = {}
    for feature in ['rgblight', 'rgb_matrix', 'led_matrix']:
        specs[feature] = load_lighting_spec(feature)

    return j2.get_template(file_to_render).render(xap=defs, qmk_version=git_get_version(), xap_str=hjson.dumps(defs), specs=specs, constants=qmk.constants, **kwargs)


def _find_kb_spec(kb):
    base_path = Path('keyboards')
    keyboard_parent = keyboard(kb)

    for _ in range(5):
        if keyboard_parent == base_path:
            break

        spec = keyboard_parent / XAP_SPEC
        if spec.exists():
            return spec

        keyboard_parent = keyboard_parent.parent

    # Just return something we know doesn't exist
    return keyboard(kb) / XAP_SPEC


def _find_km_spec(kb, km):
    keymap_dir = locate_keymap(kb, km).parent
    if not keymap_dir.exists():
        return None

    # Resolve any potential USER_NAME overrides - default back to keymap name
    keymap_rules_mk = parse_rules_mk_file(keymap_dir / 'rules.mk')
    username = keymap_rules_mk.get('USER_NAME', km)

    keymap_spec = keymap_dir / XAP_SPEC
    userspace_spec = USERSPACE_DIR / username / XAP_SPEC

    # In the case of both userspace and keymap - keymap wins
    return keymap_spec if keymap_spec.exists() else userspace_spec


def get_xap_definition_files():
    """Get the sorted list of XAP definition files, from <QMK>/data/xap.
    """
    xap_defs = qmk.constants.QMK_FIRMWARE / "data" / "xap"
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
    return merge_ordered_dicts([original, new])


@lru_cache(timeout=5)
def get_xap_defs(version):
    """Gets the required version of the XAP definitions.
    """
    files = get_xap_definition_files()

    # Slice off anything newer than specified version
    if version != 'latest':
        index = [idx for idx, s in enumerate(files) if version in str(s)][0]
        files = files[:(index + 1)]

    definitions = [hjson.load(file.open(encoding='utf-8')) for file in files]
    return merge_ordered_dicts(definitions)


def latest_xap_defs():
    """Gets the latest version of the XAP definitions.
    """
    return get_xap_defs('latest')


def merge_xap_defs(kb, km):
    """Gets the latest version of the XAP definitions and merges in optional keyboard/keymap specs
    """
    definitions = [get_xap_defs('latest')]

    kb_xap = _find_kb_spec(kb)
    if kb_xap.exists():
        definitions.append({'routes': {'0x02': hjson.load(kb_xap.open(encoding='utf-8'))}})

    km_xap = _find_km_spec(kb, km)
    if km_xap.exists():
        definitions.append({'routes': {'0x03': hjson.load(km_xap.open(encoding='utf-8'))}})

    defs = merge_ordered_dicts(definitions)

    try:
        validate(defs, 'qmk.xap.v1')

    except jsonschema.ValidationError as e:
        print(f'Invalid XAP spec: {e.message}')
        exit(1)

    return defs
