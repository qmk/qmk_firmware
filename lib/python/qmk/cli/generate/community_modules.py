from argcomplete.completers import FilesCompleter

from milc import cli
from milc.attrdict import AttrDict

import qmk.path
from qmk.commands import dump_lines, parse_configurator_json
from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE

class ModuleAPI(AttrDict):
    def __init__(self, **kwargs):
        super().__init__()
        for key, value in kwargs.items():
            self[key] = value

MODULE_API_LIST = [
    ModuleAPI(ret_type='void', name='keyboard_pre_init', args='void', call_params='', ret_val=None),
    ModuleAPI(ret_type='void', name='keyboard_post_init', args='void', call_params='', ret_val=None),
    ModuleAPI(ret_type='void', name='housekeeping_task', args='void', call_params='', ret_val=None),
    ModuleAPI(ret_type='bool', name='process_record', args='uint16_t keycode, keyrecord_t *record', call_params='keycode, record', ret_val='true'),
]

@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('filename', type=qmk.path.FileType('r'), arg_only=True, completer=FilesCompleter('.json'), help='Configurator JSON file')
@cli.subcommand('Creates a community_modules.h from a keymap.json file.')
def generate_community_modules_h(cli):
    """Creates a community_modules.h from a keymap.json file
    """
    if cli.args.output and cli.args.output.name == '-':
        cli.args.output = None

    lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once', '']
    keymap_json = parse_configurator_json(cli.args.filename)
    if keymap_json and 'modules' in keymap_json:
        for module in keymap_json['modules']:
            for api in MODULE_API_LIST:
                lines.append(f'{api.ret_type} {api.name}_{module}({api.args});')
    dump_lines(cli.args.output, lines, cli.args.quiet)

@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('filename', type=qmk.path.FileType('r'), arg_only=True, completer=FilesCompleter('.json'), help='Configurator JSON file')
@cli.subcommand('Creates a community_modules.c from a keymap.json file.')
def generate_community_modules_c(cli):
    """Creates a community_modules.c from a keymap.json file
    """
    if cli.args.output and cli.args.output.name == '-':
        cli.args.output = None

    lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#include QMK_KEYBOARD_H', '#include "community_modules.h"']
    keymap_json = parse_configurator_json(cli.args.filename)
    if keymap_json and 'modules' in keymap_json:
        for module in keymap_json['modules']:
            for api in MODULE_API_LIST:
                lines.append('')
                lines.append(f'__attribute__((weak)) {api.ret_type} {api.name}_{module}({api.args}) {{ ')
                if api.ret_val:
                    lines.append(f'    return {api.ret_val};')
                lines.append('}')

        for api in MODULE_API_LIST:
            lines.append('')
            lines.append(f'{api.ret_type} {api.name}_modules({api.args}) {{')
            if api.ret_type == 'bool':
                lines.append('    return true')
            for module in keymap_json['modules']:
                if api.ret_type == 'bool':
                    lines.append(f'       && {api.name}_{module}({api.call_params})')
                else:
                    lines.append(f'    {api.name}_{module}({api.call_params});')
            if api.ret_type == 'bool':
                lines.append('    ;')
            lines.append('}')
    dump_lines(cli.args.output, lines, cli.args.quiet)
