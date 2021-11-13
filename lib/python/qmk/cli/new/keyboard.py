"""This script automates the creation of new keyboard directories using a starter template.
"""
from datetime import date
from pathlib import Path
import re

from qmk.commands import git_get_username
import qmk.path
from milc import cli
from milc.questions import choice, question

KEYBOARD_TYPES = ['avr', 'ps2avrgb']


def keyboard_name(name):
    """Callable for argparse validation.
    """
    if not validate_keyboard_name(name):
        raise ValueError
    return name


def validate_keyboard_name(name):
    """Returns True if the given keyboard name contains only lowercase a-z, 0-9 and underscore characters.
    """
    regex = re.compile(r'^[a-z0-9][a-z0-9/_]+$')
    return bool(regex.match(name))


@cli.argument('-kb', '--keyboard', help='Specify the name for the new keyboard directory', arg_only=True, type=keyboard_name)
@cli.argument('-t', '--type', help='Specify the keyboard type', arg_only=True, choices=KEYBOARD_TYPES)
@cli.argument('-u', '--username', help='Specify your username (default from Git config)', arg_only=True)
@cli.argument('-n', '--realname', help='Specify your real name if you want to use that. Defaults to username', arg_only=True)
@cli.subcommand('Creates a new keyboard directory')
def new_keyboard(cli):
    """Creates a new keyboard.
    """
    cli.log.info('{style_bright}Generating a new QMK keyboard directory{style_normal}')
    cli.echo('')

    # Get keyboard name
    new_keyboard_name = None
    while not new_keyboard_name:
        new_keyboard_name = cli.args.keyboard if cli.args.keyboard else question('Keyboard Name:')
        if not validate_keyboard_name(new_keyboard_name):
            cli.log.error('Keyboard names must contain only {fg_cyan}lowercase a-z{fg_reset}, {fg_cyan}0-9{fg_reset}, and {fg_cyan}_{fg_reset}! Please choose a different name.')

            # Exit if passed by arg
            if cli.args.keyboard:
                return False

            new_keyboard_name = None
            continue

        keyboard_path = qmk.path.keyboard(new_keyboard_name)
        if keyboard_path.exists():
            cli.log.error(f'Keyboard {{fg_cyan}}{new_keyboard_name}{{fg_reset}} already exists! Please choose a different name.')

            # Exit if passed by arg
            if cli.args.keyboard:
                return False

            new_keyboard_name = None

    # Get keyboard type
    keyboard_type = cli.args.type if cli.args.type else choice('Keyboard Type:', KEYBOARD_TYPES, default=0)

    # Get username
    user_name = None
    while not user_name:
        user_name = question('Your GitHub User Name:', default=find_user_name())

        if not user_name:
            cli.log.error('You didn\'t provide a username, and we couldn\'t find one set in your QMK or Git configs. Please try again.')

            # Exit if passed by arg
            if cli.args.username:
                return False

    real_name = None
    while not real_name:
        real_name = question('Your real name:', default=user_name)

    keyboard_basename = keyboard_path.name
    replacements = {
        "YEAR": str(date.today().year),
        "KEYBOARD": keyboard_basename,
        "USER_NAME": user_name,
        "YOUR_NAME": real_name,
    }

    template_dir = Path('data/templates')
    template_tree(template_dir / 'base', keyboard_path, replacements)
    template_tree(template_dir / keyboard_type, keyboard_path, replacements)

    cli.echo('')
    cli.log.info(f'{{fg_green}}Created a new keyboard called {{fg_cyan}}{new_keyboard_name}{{fg_green}}.{{fg_reset}}')
    cli.log.info(f'To start working on things, `cd` into {{fg_cyan}}{keyboard_path}{{fg_reset}},')
    cli.log.info('or open the directory in your preferred text editor.')


def find_user_name():
    if cli.args.username:
        return cli.args.username
    elif cli.config.user.name:
        return cli.config.user.name
    else:
        return git_get_username()


def template_tree(src: Path, dst: Path, replacements: dict):
    """Recursively copy template and replace placeholders

    Args:
        src (Path)
            The source folder to copy from
        dst (Path)
            The destination folder to copy to
        replacements (dict)
            a dictionary with "key":"value" pairs to replace.

    Raises:
        FileExistsError
            When trying to overwrite existing files
    """

    dst.mkdir(parents=True, exist_ok=True)

    for child in src.iterdir():
        if child.is_dir():
            template_tree(child, dst / child.name, replacements=replacements)

        if child.is_file():
            file_name = dst / (child.name % replacements)

            with file_name.open(mode='x') as dst_f:
                with child.open() as src_f:
                    template = src_f.read()
                    dst_f.write(template % replacements)
