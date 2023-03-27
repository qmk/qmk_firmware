"""Migrate info.json keys
"""
import json
from pathlib import Path
from dotty_dict import dotty

from milc import cli

from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.info import find_info_json
from qmk.json_encoders import InfoJSONEncoder
from qmk.json_schema import json_load


@cli.argument('-f', '--from', arg_only=True, help="The old info.json key")
@cli.argument('-t', '--to', arg_only=True, help="The new info.json key")
@cli.argument('-kb', '--keyboard', arg_only=True, type=keyboard_folder, completer=keyboard_completer, required=True, help='The keyboard\'s name')
@cli.subcommand('Migrate info.json keys.', hidden=True)
def info_migrate(cli):
    """Migrate info.json keys
    """

    # Find all the info.json files for this keyboard
    target_infos = find_info_json(cli.args.keyboard)
    info_datas = [(target_info, dotty(json_load(Path(target_info)))) for target_info in target_infos]

    for file, info_data in info_datas:
        value = info_data.get(cli.args['from'])

        # Does this info.json have the "from" key?
        if value is not None:
            cli.log.info(f"Updating {cli.args['from']} -> {cli.args.to} (value: {value}) in {file}")

            # Remove the old key, add the new key with the same value
            del info_data[cli.args['from']]
            info_data[cli.args.to] = value

            file.write_text(json.dumps(info_data.to_dict(), cls=InfoJSONEncoder) + '\n', newline='\n')
