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
    "Filter the list of keyboards based on their info.json data. Accepts the formats key=value, function(key), or function(key,value), eg. 'features.rgblight=true'. Valid functions are 'absent', 'contains', 'exists' and 'length'. May be passed multiple times; all filters need to match. Value may include wildcards such as '*' and '?'."  # noqa: `format-python` and `pytest` don't agree here.
)
@cli.argument('-p', '--print', arg_only=True, action='append', default=[], help="For each matched target, print the value of the supplied info.json key. May be passed multiple times.")
@cli.argument('-km', '--keymap', type=str, default='default', help="The keymap name to build. Default is 'default'.")
@cli.subcommand('Find builds which match supplied search criteria.')
def find(cli):
    """Search through all keyboards and keymaps for a given search criteria.
    """
    targets = search_keymap_targets([('all', cli.config.find.keymap)], cli.args.filter)
    for target in sorted(targets, key=lambda t: (t.keyboard, t.keymap)):
        print(f'{target}')

        for key in cli.args.print:
            print(f'    {key}={target.dotty.get(key, None)}')
