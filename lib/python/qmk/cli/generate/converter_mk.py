from pathlib import Path

from milc import cli

from qmk.path import normpath
from qmk.commands import dump_lines
from qmk.json_schema import json_load
from qmk.constants import GPL2_HEADER_SH_LIKE, GENERATED_HEADER_SH_LIKE


@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-e', '--escape', arg_only=True, action='store_true', help="Escape spaces in quiet mode")
@cli.argument('-c', '--converter', required=True, arg_only=True, help='Target for conversion')
@cli.argument('-p', '--pin-compatible', required=True, arg_only=True, help='Base for conversion')
@cli.subcommand('Used by the make system to generate converter helpers from data', hidden=True)
def generate_converter_mk(cli):
    info_rules_map = json_load(Path('data/mappings/converters.hjson'))

    mk_lines = [GPL2_HEADER_SH_LIKE, GENERATED_HEADER_SH_LIKE]

    active_converter = None
    candidates = info_rules_map.get(cli.args.pin_compatible, {})
    if cli.args.converter in candidates:
        active_converter = cli.args.converter

    # if no direct match - search aliases
    if not active_converter:
        for key, value in candidates.items():
            if cli.args.converter in value.get('aliases', []):
                active_converter = key

    if active_converter:
        converter_path = next(Path('platforms/').glob(f'*/converters/{cli.args.pin_compatible}_to_{active_converter}'))
        mk_lines.append(f'CONVERTER_PATH = {converter_path}')
        mk_lines.append(f'CONVERTER_ACTIVE = {active_converter}')

    # Show the results
    dump_lines(cli.args.output, mk_lines, cli.args.quiet)

    if cli.args.output:
        if cli.args.quiet:
            if cli.args.escape:
                print(cli.args.output.as_posix().replace(' ', '\\ '))
            else:
                print(cli.args.output)
