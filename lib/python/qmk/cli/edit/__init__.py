"""QMK Edit

Edit keyboard info.json files in a TUI.
"""
from milc import cli

from qmk.decorators import automagic_keyboard
from qmk.keyboard import keyboard_folder, keyboard_completer
from qmk.cli.edit.editor import run_editor
from qmk.cli.edit.config import EditorConfig


@cli.argument('--no-confirm-delete', action='store_true', help='Skip confirmation prompts when deleting array items')
@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, required=True, help='Keyboard to edit')
@cli.subcommand('Edit keyboard configuration in a TUI.')
@automagic_keyboard
def edit(cli):
    """Launch the keyboard configuration editor.
    """
    keyboard = cli.config.edit.keyboard
    config = EditorConfig(no_confirm_delete=getattr(cli.config.edit, 'no_confirm_delete', False))
    return run_editor(keyboard, config)
