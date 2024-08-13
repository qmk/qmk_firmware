"""Used by the make system to generate dependency lists for each of the generated files.
"""
from pathlib import Path
from milc import cli

from argcomplete.completers import FilesCompleter

from qmk.commands import dump_lines
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.keymap import keymap_completer, locate_keymap
from qmk.path import normpath, FileType


@cli.argument('filename', nargs='?', arg_only=True, type=FileType('r'), completer=FilesCompleter('.json'), help='A configurator export JSON.')
@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, required=True, help='Keyboard to generate dependency file for.')
@cli.argument('-km', '--keymap', completer=keymap_completer, help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.subcommand('Generates the list of dependencies associated with a keyboard build and its generated files.', hidden=True)
def generate_make_dependencies(cli):
    """Generates the list of dependent config files for a keyboard.
    """
    interesting_files = [
        'info.json',
        'keyboard.json',
        'rules.mk',
        'post_rules.mk',
        'config.h',
        'post_config.h',
    ]

    check_files = []

    # Walk up the keyboard's directory tree looking for the files we're interested in
    keyboards_root = Path('keyboards')
    parent_path = Path('keyboards') / cli.args.keyboard
    while parent_path != keyboards_root:
        for file in interesting_files:
            check_files.append(parent_path / file)
        parent_path = parent_path.parent

    # Find the keymap and include any of the interesting files
    if cli.args.keymap is not None:
        km = locate_keymap(cli.args.keyboard, cli.args.keymap)
        if km is not None:
            # keymap.json is only valid for the keymap, so check this one separately
            check_files.append(km.parent / 'keymap.json')
            # Add all the interesting files
            for file in interesting_files:
                check_files.append(km.parent / file)

    # If we have a matching userspace, include those too
    for file in interesting_files:
        check_files.append(Path('users') / cli.args.keymap / file)

    dump_lines(cli.args.output, [f'generated-files: $(wildcard {found})\n' for found in check_files])
