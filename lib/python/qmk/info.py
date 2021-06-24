"""Functions that help us generate and use info.json files.
"""
from functools import lru_cache
from pathlib import Path

import jsonschema
from milc import cli

from qmk.json_schema import keyboard_api_validate
from qmk.keymap import list_keymaps
from qmk.metadata import basic_info_json, info_log_error


def _valid_community_layout(layout):
    """Validate that a declared community list exists
    """
    return (Path('layouts/default') / layout).exists()


@lru_cache(maxsize=None)
def info_json(keyboard):
    """Generate the info.json data for a specific keyboard.
    """
    info_data = basic_info_json(keyboard)

    # Populate the list of JSON keymaps
    for keymap in list_keymaps(keyboard, c=False, fullpath=True):
        info_data['keymaps'][keymap.name] = {'url': f'https://raw.githubusercontent.com/qmk/qmk_firmware/master/{keymap}/keymap.json'}

    # Validate against the jsonschema
    try:
        keyboard_api_validate(info_data)

    except jsonschema.ValidationError as e:
        json_path = '.'.join([str(p) for p in e.absolute_path])
        cli.log.error('Invalid API data: %s: %s: %s', keyboard, json_path, e.message)
        exit()

    # Make sure we have at least one layout
    if not info_data.get('layouts'):
        info_log_error(info_data, 'No LAYOUTs defined! Need at least one layout defined in the keyboard.h or info.json.')

    # Filter out any non-existing community layouts
    for layout in info_data.get('community_layouts', []):
        if not _valid_community_layout(layout):
            # Ignore layout from future checks
            info_data['community_layouts'].remove(layout)
            info_log_error(info_data, 'Claims to support a community layout that does not exist: %s' % (layout))

    # Make sure we supply layout macros for the community layouts we claim to support
    for layout in info_data.get('community_layouts', []):
        layout_name = 'LAYOUT_' + layout
        if layout_name not in info_data.get('layouts', {}) and layout_name not in info_data.get('layout_aliases', {}):
            info_log_error(info_data, 'Claims to support community layout %s but no %s() macro found' % (layout, layout_name))

    return info_data