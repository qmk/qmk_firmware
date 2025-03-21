import contextlib
from argcomplete.completers import FilesCompleter
from pathlib import Path

from milc import cli

import qmk.path
from qmk.info import get_modules
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.commands import dump_lines
from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE
from qmk.community_modules import module_api_list, load_module_jsons, find_module_path


@contextlib.contextmanager
def _render_api_guard(lines, api):
    if api.guard:
        lines.append(f'#if {api.guard}')
    yield
    if api.guard:
        lines.append(f'#endif  // {api.guard}')


def _render_api_header(api):
    lines = []
    if api.header:
        lines.append('')
        with _render_api_guard(lines, api):
            lines.append(f'#include <{api.header}>')
    return lines


def _render_keycodes(module_jsons):
    lines = []
    lines.append('')
    lines.append('enum {')
    first = True
    for module_json in module_jsons:
        module_name = Path(module_json['module']).name
        keycodes = module_json.get('keycodes', [])
        if len(keycodes) > 0:
            lines.append(f'    // From module: {module_name}')
            for keycode in keycodes:
                key = keycode.get('key', None)
                if first:
                    lines.append(f'    {key} = QK_COMMUNITY_MODULE,')
                    first = False
                else:
                    lines.append(f'    {key},')
                for alias in keycode.get('aliases', []):
                    lines.append(f'    {alias} = {key},')
            lines.append('')
    lines.append('    LAST_COMMUNITY_MODULE_KEY')
    lines.append('};')
    lines.append('_Static_assert((int)LAST_COMMUNITY_MODULE_KEY <= (int)(QK_COMMUNITY_MODULE_MAX+1), "Too many community module keycodes");')
    return lines


def _render_api_declarations(api, module, user_kb=True):
    lines = []
    lines.append('')
    with _render_api_guard(lines, api):
        if user_kb:
            lines.append(f'{api.ret_type} {api.name}_{module}_user({api.args});')
            lines.append(f'{api.ret_type} {api.name}_{module}_kb({api.args});')
        lines.append(f'{api.ret_type} {api.name}_{module}({api.args});')
    return lines


def _render_api_implementations(api, module):
    module_name = Path(module).name
    lines = []
    lines.append('')
    with _render_api_guard(lines, api):
        # _user
        lines.append(f'__attribute__((weak)) {api.ret_type} {api.name}_{module_name}_user({api.args}) {{')
        if api.ret_type == 'bool':
            lines.append('    return true;')
        else:
            pass
        lines.append('}')
        lines.append('')

        # _kb
        lines.append(f'__attribute__((weak)) {api.ret_type} {api.name}_{module_name}_kb({api.args}) {{')
        if api.ret_type == 'bool':
            lines.append(f'    if(!{api.name}_{module_name}_user({api.call_params})) {{ return false; }}')
            lines.append('    return true;')
        else:
            lines.append(f'    {api.name}_{module_name}_user({api.call_params});')
        lines.append('}')
        lines.append('')

        # module (non-suffixed)
        lines.append(f'__attribute__((weak)) {api.ret_type} {api.name}_{module_name}({api.args}) {{')
        if api.ret_type == 'bool':
            lines.append(f'    if(!{api.name}_{module_name}_kb({api.call_params})) {{ return false; }}')
            lines.append('    return true;')
        else:
            lines.append(f'    {api.name}_{module_name}_kb({api.call_params});')
        lines.append('}')
    return lines


def _render_core_implementation(api, modules):
    lines = []
    lines.append('')
    with _render_api_guard(lines, api):
        lines.append(f'{api.ret_type} {api.name}_modules({api.args}) {{')
        if api.ret_type == 'bool':
            lines.append('    return true')
        for module in modules:
            module_name = Path(module).name
            if api.ret_type == 'bool':
                lines.append(f'        && {api.name}_{module_name}({api.call_params})')
            else:
                lines.append(f'    {api.name}_{module_name}({api.call_params});')
        if api.ret_type == 'bool':
            lines.append('    ;')
        lines.append('}')
    return lines


@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', arg_only=True, type=keyboard_folder, completer=keyboard_completer, help='Keyboard to generate community_modules.h for.')
@cli.argument('filename', nargs='?', type=qmk.path.FileType('r'), arg_only=True, completer=FilesCompleter('.json'), help='Configurator JSON file')
@cli.subcommand('Creates a community_modules.h from a keymap.json file.')
def generate_community_modules_h(cli):
    """Creates a community_modules.h from a keymap.json file
    """
    if cli.args.output and cli.args.output.name == '-':
        cli.args.output = None

    api_list, api_version, ver_major, ver_minor, ver_patch = module_api_list()

    lines = [
        GPL2_HEADER_C_LIKE,
        GENERATED_HEADER_C_LIKE,
        '#pragma once',
        '#include <stdint.h>',
        '#include <stdbool.h>',
        '#include <keycodes.h>',
        '',
        '#define COMMUNITY_MODULES_API_VERSION_BUILDER(ver_major,ver_minor,ver_patch) (((((uint32_t)(ver_major))&0xFF) << 24) | ((((uint32_t)(ver_minor))&0xFF) << 16) | (((uint32_t)(ver_patch))&0xFF))',
        f'#define COMMUNITY_MODULES_API_VERSION COMMUNITY_MODULES_API_VERSION_BUILDER({ver_major},{ver_minor},{ver_patch})',
        f'#define ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(ver_major,ver_minor,ver_patch) _Static_assert(COMMUNITY_MODULES_API_VERSION_BUILDER(ver_major,ver_minor,ver_patch) <= COMMUNITY_MODULES_API_VERSION, "Community module requires a newer version of QMK modules API -- needs: " #ver_major "." #ver_minor "." #ver_patch ", current: {api_version}.")',
        '',
        'typedef struct keyrecord_t keyrecord_t; // forward declaration so we don\'t need to include quantum.h',
        '',
    ]

    modules = get_modules(cli.args.keyboard, cli.args.filename)
    module_jsons = load_module_jsons(modules)
    if len(modules) > 0:
        lines.extend(_render_keycodes(module_jsons))

        for api in api_list:
            lines.extend(_render_api_header(api))

        for module in modules:
            lines.append('')
            lines.append(f'// From module: {module}')
            for api in api_list:
                lines.extend(_render_api_declarations(api, Path(module).name))
        lines.append('')

        lines.append('// Core wrapper')
        for api in api_list:
            lines.extend(_render_api_declarations(api, 'modules', user_kb=False))

    dump_lines(cli.args.output, lines, cli.args.quiet, remove_repeated_newlines=True)


@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', arg_only=True, type=keyboard_folder, completer=keyboard_completer, help='Keyboard to generate community_modules.c for.')
@cli.argument('filename', nargs='?', type=qmk.path.FileType('r'), arg_only=True, completer=FilesCompleter('.json'), help='Configurator JSON file')
@cli.subcommand('Creates a community_modules.c from a keymap.json file.')
def generate_community_modules_c(cli):
    """Creates a community_modules.c from a keymap.json file
    """
    if cli.args.output and cli.args.output.name == '-':
        cli.args.output = None

    api_list, _, _, _, _ = module_api_list()

    lines = [
        GPL2_HEADER_C_LIKE,
        GENERATED_HEADER_C_LIKE,
        '',
        '#include "community_modules.h"',
    ]

    modules = get_modules(cli.args.keyboard, cli.args.filename)
    if len(modules) > 0:

        for module in modules:
            for api in api_list:
                lines.extend(_render_api_implementations(api, Path(module).name))

        for api in api_list:
            lines.extend(_render_core_implementation(api, modules))

    dump_lines(cli.args.output, lines, cli.args.quiet, remove_repeated_newlines=True)


@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', arg_only=True, type=keyboard_folder, completer=keyboard_completer, help='Keyboard to generate community_modules.c for.')
@cli.argument('filename', nargs='?', type=qmk.path.FileType('r'), arg_only=True, completer=FilesCompleter('.json'), help='Configurator JSON file')
@cli.subcommand('Creates a community_modules_introspection.h from a keymap.json file.')
def generate_community_modules_introspection_h(cli):
    """Creates a community_modules_introspection.h from a keymap.json file
    """
    if cli.args.output and cli.args.output.name == '-':
        cli.args.output = None

    lines = [
        GPL2_HEADER_C_LIKE,
        GENERATED_HEADER_C_LIKE,
        '',
    ]

    modules = get_modules(cli.args.keyboard, cli.args.filename)
    if len(modules) > 0:
        for module in modules:
            module_path = find_module_path(module)
            lines.append(f'#if __has_include("{module_path}/introspection.h")')
            lines.append(f'#include "{module_path}/introspection.h"')
            lines.append(f'#endif  // __has_include("{module_path}/introspection.h")')
            lines.append('')

    dump_lines(cli.args.output, lines, cli.args.quiet, remove_repeated_newlines=True)


@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', arg_only=True, type=keyboard_folder, completer=keyboard_completer, help='Keyboard to generate community_modules.c for.')
@cli.argument('filename', nargs='?', type=qmk.path.FileType('r'), arg_only=True, completer=FilesCompleter('.json'), help='Configurator JSON file')
@cli.subcommand('Creates a community_modules_introspection.c from a keymap.json file.')
def generate_community_modules_introspection_c(cli):
    """Creates a community_modules_introspection.c from a keymap.json file
    """
    if cli.args.output and cli.args.output.name == '-':
        cli.args.output = None

    lines = [
        GPL2_HEADER_C_LIKE,
        GENERATED_HEADER_C_LIKE,
        '',
    ]

    modules = get_modules(cli.args.keyboard, cli.args.filename)
    if len(modules) > 0:
        for module in modules:
            module_path = find_module_path(module)
            lines.append(f'#if __has_include("{module_path}/introspection.c")')
            lines.append(f'#include "{module_path}/introspection.c"')
            lines.append(f'#endif  // __has_include("{module_path}/introspection.c")')
            lines.append('')

    dump_lines(cli.args.output, lines, cli.args.quiet, remove_repeated_newlines=True)
