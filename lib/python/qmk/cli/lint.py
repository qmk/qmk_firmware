"""Command to look over a keyboard/keymap and check for common mistakes.
"""
from milc import cli

from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.info import info_json
from qmk.keyboard import keyboard_completer
from qmk.keymap import locate_keymap
from qmk.path import is_keyboard, keyboard


@cli.argument('--strict', action='store_true', help='Treat warnings as errors.')
@cli.argument('-kb', '--keyboard', completer=keyboard_completer, help='The keyboard to check.')
@cli.argument('-km', '--keymap', help='The keymap to check.')
@cli.subcommand('Check keyboard and keymap for common mistakes.')
@automagic_keyboard
@automagic_keymap
def lint(cli):
    """Check keyboard and keymap for common mistakes.
    """
    if not cli.config.lint.keyboard:
        cli.log.error('Missing required argument: --keyboard')
        cli.print_help()
        return False

    if not is_keyboard(cli.config.lint.keyboard):
        cli.log.error('No such keyboard: %s', cli.config.lint.keyboard)
        return False

    # Gather data about the keyboard.
    ok = True
    keyboard_path = keyboard(cli.config.lint.keyboard)
    keyboard_info = info_json(cli.config.lint.keyboard)
    readme_path = keyboard_path / 'readme.md'

    # Check for errors in the info.json
    if keyboard_info['parse_errors']:
        ok = False
        cli.log.error('Errors found when generating info.json.')

    if cli.config.lint.strict and keyboard_info['parse_warnings']:
        ok = False
        cli.log.error('Warnings found when generating info.json (Strict mode enabled.)')

    # Check for a readme.md and warn if it doesn't exist
    if not readme_path.exists():
        ok = False
        cli.log.error('Missing %s', readme_path)

    # Keymap specific checks
    if cli.config.lint.keymap:
        keymap_path = locate_keymap(cli.config.lint.keyboard, cli.config.lint.keymap)

        if not keymap_path:
            ok = False
            cli.log.error("Can't find %s keymap for %s keyboard.", cli.config.lint.keymap, cli.config.lint.keyboard)
        else:
            keymap_readme = keymap_path.parent / 'readme.md'
            if not keymap_readme.exists():
                cli.log.warning('Missing %s', keymap_readme)

                if cli.config.lint.strict:
                    ok = False

    # Check and report the overall status
    if ok:
        cli.log.info('Lint check passed!')
        return True

    cli.log.error('Lint check failed!')
    return False
