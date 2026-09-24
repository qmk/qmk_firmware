"""Migrate keyboard configuration to "Data Driven"
"""
import json
from pathlib import Path
from dotty_dict import dotty

from milc import cli

from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.info import info_json, find_info_json
from qmk.json_encoders import InfoJSONEncoder
from qmk.json_schema import json_load


def _candidate_files(keyboard):
    kb_dir = Path(keyboard)

    cur_dir = Path('keyboards')
    files = []
    for dir in kb_dir.parts:
        cur_dir = cur_dir / dir
        files.append(cur_dir / 'config.h')
        files.append(cur_dir / 'rules.mk')

    return [file for file in files if file.exists()]


@cli.argument('-f', '--filter', arg_only=True, action='append', default=[], help="Filter the performed migrations based on the supplied value. Supported format is 'KEY' located from 'data/mappings'. May be passed multiple times.")
@cli.argument('-kb', '--keyboard', arg_only=True, type=keyboard_folder, completer=keyboard_completer, required=True, help='The keyboard\'s name')
@cli.subcommand('Migrate keyboard config to "Data Driven".', hidden=True)
def migrate(cli):
    """Migrate keyboard configuration to "Data Driven"
    """
    # Merge mappings as we do not care to where "KEY" is found just that its removed
    info_config_map = json_load(Path('data/mappings/info_config.hjson'))
    info_rules_map = json_load(Path('data/mappings/info_rules.hjson'))
    info_map = {**info_config_map, **info_rules_map}

    # Parse target info.json which will receive updates
    target_info = Path(find_info_json(cli.args.keyboard)[0])
    info_data = dotty(json_load(target_info))

    # Already parsed used for updates
    kb_info_json = dotty(info_json(cli.args.keyboard))

    # List of candidate files
    files = _candidate_files(cli.args.keyboard)

    # Filter down keys if requested
    keys = list(filter(lambda key: info_map[key].get("to_json", True), info_map.keys()))
    if cli.args.filter:
        keys = list(set(keys) & set(cli.args.filter))
        rejected = set(cli.args.filter) - set(keys)
        for key in rejected:
            cli.log.info(f'{{fg_yellow}}Skipping {key} as migration not possible...')

    cli.log.info(f'{{fg_green}}Migrating keyboard {{fg_cyan}}{cli.args.keyboard}{{fg_green}}.{{fg_reset}}')

    # Start migration
    for file in files:
        cli.log.info(f'  Migrating file {file}')
        file_contents = file.read_text(encoding='utf-8').split('\n')
        for key in keys:
            for num, line in enumerate(file_contents):
                if line.startswith(f'{key} =') or line.startswith(f'#define {key} '):
                    cli.log.info(f'    Migrating {key}...')

                    while line.rstrip().endswith('\\'):
                        file_contents.pop(num)
                        line = file_contents[num]
                    file_contents.pop(num)

                    update_key = info_map[key]["info_key"]
                    if update_key in kb_info_json:
                        info_data[update_key] = kb_info_json[update_key]

        file.write_text('\n'.join(file_contents), encoding='utf-8')

    # Finally write out updated info.json
    cli.log.info(f'  Updating {target_info}')
    target_info.write_text(json.dumps(info_data.to_dict(), cls=InfoJSONEncoder, sort_keys=True))

    cli.log.info(f'{{fg_green}}Migration of keyboard {{fg_cyan}}{cli.args.keyboard}{{fg_green}} complete!{{fg_reset}}')
    cli.log.info(f"Verify build with {{fg_yellow}}qmk compile -kb {cli.args.keyboard} -km default{{fg_reset}}.")
