"""Used by the make system to generate keycodes.h from keycodes_{version}.json
"""
from milc import cli

from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE
from qmk.commands import dump_lines
from qmk.path import normpath
from qmk.keycodes import load_spec


def _translate_group(group):
    """Fix up any issues with badly chosen values
    """
    if group == 'modifiers':
        return 'modifier'
    if group == 'media':
        return 'consumer'
    return group


def _render_key(key):
    width = 7
    if 'S(' in key:
        width += len('S()')
    if 'A(' in key:
        width += len('A()')
    if 'RCTL(' in key:
        width += len('RCTL()')
    if 'ALGR(' in key:
        width += len('ALGR()')
    return key.ljust(width)


def _render_label(label):
    label = label.replace("\\", "(backslash)")
    return label


def _generate_ranges(lines, keycodes):
    max_name_len = 0
    for key, value in keycodes["ranges"].items():
        define = value.get("define")
        if len(define) > max_name_len:
            max_name_len = len(define)

    lines.append('')
    lines.append('#define FOREACH_QK_KEYCODE_RANGE(XX) \\')
    for key, value in keycodes["ranges"].items():
        lo, mask = map(lambda x: int(x, 16), key.split("/"))
        hi = lo + mask
        define = value.get("define")
        e = f'{define},'
        lines.append(f'    XX({e.ljust(max_name_len+1)} 0x{lo:04X}, 0x{hi:04X}) \\')
    lines.append('    /* End */')
    lines.append('')

    lines.append('enum qk_keycode_ranges {')
    lines.append('#define ENUM_OUTPUT(name, lo, hi) \\')
    lines.append('    name = lo, \\')
    lines.append('    name ## _MAX = hi,')
    lines.append('FOREACH_QK_KEYCODE_RANGE(ENUM_OUTPUT)')
    lines.append('#undef ENUM_OUTPUT')
    lines.append('};')


def _generate_defines(lines, keycodes):
    max_keycode_len = 0
    max_alias_len = 0
    for key, value in keycodes["keycodes"].items():
        key_name = value.get("key")
        if len(key_name) > max_keycode_len:
            max_keycode_len = len(key_name)
        for alias in value.get("aliases", []):
            if len(alias) > max_alias_len:
                max_alias_len = len(alias)

    lines.append('')
    lines.append('/* Actual Keycodes */')
    lines.append('#define FOREACH_QK_KEYCODE_DEFINE(XX) \\')
    for key, value in keycodes["keycodes"].items():
        key_name = value.get("key")
        e = f'{key_name},'
        lines.append(f'    XX({e.ljust(max_keycode_len+1)} {key}) \\')
    lines.append('    /* End */')
    lines.append('')

    lines.append('/* Aliases */')
    lines.append('#define FOREACH_QK_KEYCODE_ALIAS(XX) \\')
    for key, value in keycodes["keycodes"].items():
        temp = value.get("key")
        for alias in value.get("aliases", []):
            e = f'{alias},'
            lines.append(f'    XX({e.ljust(max_alias_len+1)} {temp}) \\')
    lines.append('    /* End */')
    lines.append('')

    lines.append('/* Combination */')
    lines.append('#define FOREACH_QK_KEYCODE(XX) \\')
    lines.append('    FOREACH_QK_KEYCODE_DEFINE(XX) \\')
    lines.append('    FOREACH_QK_KEYCODE_ALIAS(XX)')
    lines.append('')

    lines.append('enum qk_keycode_defines {')
    lines.append('#define ENUM_OUTPUT(name, value) \\')
    lines.append('  name = value,')
    lines.append('FOREACH_QK_KEYCODE(ENUM_OUTPUT)')
    lines.append('#undef ENUM_OUTPUT')
    lines.append('};')


def _generate_helpers(lines, keycodes):
    lines.append('')
    lines.append('// Range Helpers')
    for value in keycodes["ranges"].values():
        define = value.get("define")
        lines.append(f'#define IS_{define}(code) ((code) >= {define} && (code) <= {define + "_MAX"})')

    # extract min/max
    temp = {}
    for key, value in keycodes["keycodes"].items():
        group = value.get('group', None)
        if not group:
            continue
        if group not in temp:
            temp[group] = [0xFFFF, 0]
        key = int(key, 16)
        if key < temp[group][0]:
            temp[group][0] = key
        if key > temp[group][1]:
            temp[group][1] = key

    lines.append('')
    lines.append('// Group Helpers')
    for group, codes in temp.items():
        lo = keycodes["keycodes"][f'0x{codes[0]:04X}']['key']
        hi = keycodes["keycodes"][f'0x{codes[1]:04X}']['key']
        lines.append(f'#define IS_{ _translate_group(group).upper() }_KEYCODE(code) ((code) >= {lo} && (code) <= {hi})')


def _generate_aliases(lines, keycodes):
    lines.append('')
    lines.append('// Aliases')
    for key, value in keycodes["aliases"].items():
        define = _render_key(value.get("key"))
        val = _render_key(key)
        if 'label' in value:
            lines.append(f'#define {define} {val} // {_render_label(value.get("label"))}')
        else:
            lines.append(f'#define {define} {val}')

    lines.append('')
    for key, value in keycodes["aliases"].items():
        for alias in value.get("aliases", []):
            lines.append(f'#define {alias} {value.get("key")}')


@cli.argument('-v', '--version', arg_only=True, required=True, help='Version of keycodes to generate.')
@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.subcommand('Used by the make system to generate keycodes.h from keycodes_{version}.json', hidden=True)
def generate_keycodes(cli):
    """Generates the keycodes.h file.
    """

    # Build the keycodes.h file.
    keycodes_h_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once', '// clang-format off']

    keycodes = load_spec(cli.args.version)

    _generate_ranges(keycodes_h_lines, keycodes)
    _generate_defines(keycodes_h_lines, keycodes)
    _generate_helpers(keycodes_h_lines, keycodes)

    # Show the results
    dump_lines(cli.args.output, keycodes_h_lines, cli.args.quiet)


@cli.argument('-v', '--version', arg_only=True, required=True, help='Version of keycodes to generate.')
@cli.argument('-l', '--lang', arg_only=True, required=True, help='Language of keycodes to generate.')
@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.subcommand('Used by the make system to generate keymap_{lang}.h from keycodes_{lang}_{version}.json', hidden=True)
def generate_keycode_extras(cli):
    """Generates the header file.
    """

    # Build the header file.
    keycodes_h_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once', '#include "keycodes.h"', '// clang-format off']

    keycodes = load_spec(cli.args.version, cli.args.lang)

    _generate_aliases(keycodes_h_lines, keycodes)

    # Show the results
    dump_lines(cli.args.output, keycodes_h_lines, cli.args.quiet)
