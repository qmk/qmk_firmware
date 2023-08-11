"""Used by the make system to generate a keycode lookup table from keycodes_{version}.json
"""
from milc import cli

from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE
from qmk.commands import dump_lines
from qmk.path import normpath
from qmk.keycodes import load_spec


def _generate_defines(lines, keycodes):
    lines.append('')
    lines.append('std::map<uint16_t, std::string> KEYCODE_ID_TABLE = {')
    for key, value in keycodes["keycodes"].items():
        lines.append(f'    {{{value.get("key")}, "{value.get("key")}"}},')
    lines.append('};')


@cli.argument('-v', '--version', arg_only=True, required=True, help='Version of keycodes to generate.')
@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.subcommand('Used by the make system to generate a keycode lookup table from keycodes_{version}.json', hidden=True)
def generate_keycodes_tests(cli):
    """Generates a keycode to identifier lookup table for unit test output.
    """

    # Build the keycodes.h file.
    keycodes_h_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '// clang-format off']
    keycodes_h_lines.append('extern "C" {\n#include <keycode.h>\n}')
    keycodes_h_lines.append('#include <map>')
    keycodes_h_lines.append('#include <string>')
    keycodes_h_lines.append('#include <cstdint>')

    keycodes = load_spec(cli.args.version)

    _generate_defines(keycodes_h_lines, keycodes)

    # Show the results
    dump_lines(cli.args.output, keycodes_h_lines, cli.args.quiet)
