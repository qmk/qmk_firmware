"""This script automates the generation of the QMK API data.
"""
from pathlib import Path
from shutil import copyfile
import json

from milc import cli

from qmk.datetime import current_datetime
from qmk.info import info_json
from qmk.info_json_encoder import InfoJSONEncoder
from qmk.keyboard import list_keyboards


@cli.subcommand('Creates a new keymap for the keyboard of your choosing', hidden=False if cli.config.user.developer else True)
def generate_api(cli):
    """Generates the QMK API data.
    """
    api_data_dir = Path('api_data')
    v1_dir = api_data_dir / 'v1'
    keyboard_list = v1_dir / 'keyboard_list.json'
    keyboard_all = v1_dir / 'keyboards.json'
    usb_file = v1_dir / 'usb.json'

    if not api_data_dir.exists():
        api_data_dir.mkdir()

    kb_all = {'last_updated': current_datetime(), 'keyboards': {}}
    usb_list = {'last_updated': current_datetime(), 'devices': {}}

    # Generate and write keyboard specific JSON files
    for keyboard_name in list_keyboards():
        kb_all['keyboards'][keyboard_name] = info_json(keyboard_name)
        keyboard_dir = v1_dir / 'keyboards' / keyboard_name
        keyboard_info = keyboard_dir / 'info.json'
        keyboard_readme = keyboard_dir / 'readme.md'
        keyboard_readme_src = Path('keyboards') / keyboard_name / 'readme.md'

        keyboard_dir.mkdir(parents=True, exist_ok=True)
        keyboard_info.write_text(json.dumps({'last_updated': current_datetime(), 'keyboards': {keyboard_name: kb_all['keyboards'][keyboard_name]}}))

        if keyboard_readme_src.exists():
            copyfile(keyboard_readme_src, keyboard_readme)

        if 'usb' in kb_all['keyboards'][keyboard_name]:
            usb = kb_all['keyboards'][keyboard_name]['usb']

            if 'vid' in usb and usb['vid'] not in usb_list['devices']:
                usb_list['devices'][usb['vid']] = {}

            if 'pid' in usb and usb['pid'] not in usb_list['devices'][usb['vid']]:
                usb_list['devices'][usb['vid']][usb['pid']] = {}

            if 'vid' in usb and 'pid' in usb:
                usb_list['devices'][usb['vid']][usb['pid']][keyboard_name] = usb

    # Write the global JSON files
    keyboard_list.write_text(json.dumps({'last_updated': current_datetime(), 'keyboards': sorted(kb_all['keyboards'])}, cls=InfoJSONEncoder))
    keyboard_all.write_text(json.dumps(kb_all, cls=InfoJSONEncoder))
    usb_file.write_text(json.dumps(usb_list, cls=InfoJSONEncoder))
