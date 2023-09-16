"""Used by the make system to generate a rules.mk
"""
from pathlib import Path
from dotty_dict import dotty

from argcomplete.completers import FilesCompleter
from milc import cli

from qmk.info import info_json
from qmk.json_schema import json_load
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.commands import dump_lines, parse_configurator_json
from qmk.path import normpath, FileType
from qmk.constants import GPL2_HEADER_SH_LIKE, GENERATED_HEADER_SH_LIKE


def process_mapping_rule(kb_info_json, rules_key, info_dict):
    """Return the rules.mk line(s) for a mapping rule.
    """
    if not info_dict.get('to_c', True):
        return None

    info_key = info_dict['info_key']
    key_type = info_dict.get('value_type', 'raw')

    try:
        rules_value = kb_info_json[info_key]
    except KeyError:
        return None

    if key_type in ['array', 'list']:
        return f'{rules_key} ?= {" ".join(rules_value)}'
    elif key_type == 'bool':
        return f'{rules_key} ?= {"yes" if rules_value else "no"}'
    elif key_type == 'mapping':
        return '\n'.join([f'{key} ?= {value}' for key, value in rules_value.items()])
    elif key_type == 'str':
        return f'{rules_key} ?= "{rules_value}"'

    return f'{rules_key} ?= {rules_value}'


@cli.argument('filename', nargs='?', arg_only=True, type=FileType('r'), completer=FilesCompleter('.json'), help='A configurator export JSON to be compiled and flashed or a pre-compiled binary firmware file (bin/hex) to be flashed.')
@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-e', '--escape', arg_only=True, action='store_true', help="Escape spaces in quiet mode")
@cli.argument('-kb', '--keyboard', arg_only=True, type=keyboard_folder, completer=keyboard_completer, help='Keyboard to generate rules.mk for.')
@cli.subcommand('Used by the make system to generate rules.mk from info.json', hidden=True)
def generate_rules_mk(cli):
    """Generates a rules.mk file from info.json.
    """
    converter = None
    # Determine our keyboard/keymap
    if cli.args.filename:
        user_keymap = parse_configurator_json(cli.args.filename)
        kb_info_json = dotty(user_keymap.get('config', {}))
        converter = user_keymap.get('converter', None)
    elif cli.args.keyboard:
        kb_info_json = dotty(info_json(cli.args.keyboard))
    else:
        cli.log.error('You must supply a configurator export or `--keyboard`.')
        cli.subcommands['generate-rules-mk'].print_help()
        return False

    info_rules_map = json_load(Path('data/mappings/info_rules.hjson'))
    rules_mk_lines = [GPL2_HEADER_SH_LIKE, GENERATED_HEADER_SH_LIKE]

    # Iterate through the info_rules map to generate basic rules
    for rules_key, info_dict in info_rules_map.items():
        new_entry = process_mapping_rule(kb_info_json, rules_key, info_dict)

        if new_entry:
            rules_mk_lines.append(new_entry)

    # Iterate through features to enable/disable them
    if 'features' in kb_info_json:
        for feature, enabled in kb_info_json['features'].items():
            feature = feature.upper()
            enabled = 'yes' if enabled else 'no'
            rules_mk_lines.append(f'{feature}_ENABLE ?= {enabled}')

    # Set SPLIT_TRANSPORT, if needed
    if kb_info_json.get('split', {}).get('transport', {}).get('protocol') == 'custom':
        rules_mk_lines.append('SPLIT_TRANSPORT ?= custom')

    # Set CUSTOM_MATRIX, if needed
    if kb_info_json.get('matrix_pins', {}).get('custom'):
        if kb_info_json.get('matrix_pins', {}).get('custom_lite'):
            rules_mk_lines.append('CUSTOM_MATRIX ?= lite')
        else:
            rules_mk_lines.append('CUSTOM_MATRIX ?= yes')

    if converter:
        rules_mk_lines.append(f'CONVERT_TO ?= {converter}')

    # Show the results
    dump_lines(cli.args.output, rules_mk_lines)

    if cli.args.output:
        if cli.args.quiet:
            if cli.args.escape:
                print(cli.args.output.as_posix().replace(' ', '\\ '))
            else:
                print(cli.args.output)
        else:
            cli.log.info('Wrote rules.mk to %s.', cli.args.output)
