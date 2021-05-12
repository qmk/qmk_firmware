"""This script automates the generation of the QMK API data.
"""
from pathlib import Path
from shutil import copyfile
import json

from milc import cli

from qmk.datetime import current_datetime
from qmk.info import info_json
from qmk.json_encoders import InfoJSONEncoder
from qmk.json_schema import json_load
from qmk.keyboard import list_keyboards


@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't write the data to disk.")
@cli.subcommand('Creates a new keymap for the keyboard of your choosing', hidden=False if cli.config.user.developer else True)
def generate_api(cli):
    """Generates the QMK API data.
    """
    api_data_dir = Path('api_data')
    v1_dir = api_data_dir / 'v1'
    keyboard_all_file = v1_dir / 'keyboards.json'  # A massive JSON containing everything
    keyboard_list_file = v1_dir / 'keyboard_list.json'  # A simple list of keyboard targets
    keyboard_aliases_file = v1_dir / 'keyboard_aliases.json'  # A list of historical keyboard names and their new name
    keyboard_metadata_file = v1_dir / 'keyboard_metadata.json'  # All the data configurator/via needs for initialization
    usb_file = v1_dir / 'usb.json'  # A mapping of USB VID/PID -> keyboard target

    if not api_data_dir.exists():
        api_data_dir.mkdir()

    kb_all = {}
    usb_list = {}

    # Generate and write keyboard specific JSON files
    for keyboard_name in list_keyboards():
        kb_all[keyboard_name] = info_json(keyboard_name)
        keyboard_dir = v1_dir / 'keyboards' / keyboard_name
        keyboard_info = keyboard_dir / 'info.json'
        keyboard_readme = keyboard_dir / 'readme.md'
        keyboard_readme_src = Path('keyboards') / keyboard_name / 'readme.md'

        keyboard_dir.mkdir(parents=True, exist_ok=True)
        keyboard_json = json.dumps({'last_updated': current_datetime(), 'keyboards': {keyboard_name: kb_all[keyboard_name]}})
        if not cli.args.dry_run:
            keyboard_info.write_text(keyboard_json)
            cli.log.debug('Wrote file %s', keyboard_info)

            if keyboard_readme_src.exists():
                copyfile(keyboard_readme_src, keyboard_readme)
                cli.log.debug('Copied %s -> %s', keyboard_readme_src, keyboard_readme)

        if 'usb' in kb_all[keyboard_name]:
            usb = kb_all[keyboard_name]['usb']

            if 'vid' in usb and usb['vid'] not in usb_list:
                usb_list[usb['vid']] = {}

            if 'pid' in usb and usb['pid'] not in usb_list[usb['vid']]:
                usb_list[usb['vid']][usb['pid']] = {}

            if 'vid' in usb and 'pid' in usb:
                usb_list[usb['vid']][usb['pid']][keyboard_name] = usb

    # Generate data for the global files
    keyboard_list = sorted(kb_all)
    keyboard_aliases = json_load(Path('data/mappings/keyboard_aliases.json'))
    keyboard_metadata = {
        'last_updated': current_datetime(),
        'keyboards': keyboard_list,
        'keyboard_aliases': keyboard_aliases,
        'usb': usb_list,
    }

    # Write the global JSON files
    keyboard_all_json = json.dumps({'last_updated': current_datetime(), 'keyboards': kb_all}, cls=InfoJSONEncoder)
    usb_json = json.dumps({'last_updated': current_datetime(), 'usb': usb_list}, cls=InfoJSONEncoder)
    keyboard_list_json = json.dumps({'last_updated': current_datetime(), 'keyboards': keyboard_list}, cls=InfoJSONEncoder)
    keyboard_aliases_json = json.dumps({'last_updated': current_datetime(), 'keyboard_aliases': keyboard_aliases}, cls=InfoJSONEncoder)
    keyboard_metadata_json = json.dumps(keyboard_metadata, cls=InfoJSONEncoder)

    if not cli.args.dry_run:
        keyboard_all_file.write_text(keyboard_all_json)
        usb_file.write_text(usb_json)
        keyboard_list_file.write_text(keyboard_list_json)
        keyboard_aliases_file.write_text(keyboard_aliases_json)
        keyboard_metadata_file.write_text(keyboard_metadata_json)
