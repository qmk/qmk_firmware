"""Command to search through all keyboards and keymaps for a given search criteria.
"""
from milc import cli
from qmk.search import search_keymap_targets


@cli.argument(
    '-f',
    '--filter',
    arg_only=True,
    action='append',
    default=[],
    help=  # noqa: `format-python` and `pytest` don't agree here.
    "Filter the list of keyboards based on the supplied value in rules.mk. Matches info.json structure, and accepts the formats 'features.rgblight=true' or 'exists(matrix_pins.direct)'. May be passed multiple times, all filters need to match. Value may include wildcards such as '*' and '?'."  # noqa: `format-python` and `pytest` don't agree here.
)
@cli.argument('-km', '--keymap', type=str, default='default', help="The keymap name to build. Default is 'default'.")
@cli.subcommand('Find builds which match supplied search criteria.')
def find(cli):
    """Search through all keyboards and keymaps for a given search criteria.
    """
    targets = search_keymap_targets(cli.args.keymap, cli.args.filter)
    for target in targets:
        print(f'{target[0]}:{target[1]}')
