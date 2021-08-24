"""This script automates the creation of new keyboard directories using a starter template.
"""
from datetime import date
import fileinput
from pathlib import Path
import re
import shutil

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
        user_name = question('Your Name:', default=find_user_name())

        if not user_name:
            cli.log.error('You didn\'t provide a username, and we couldn\'t find one set in your QMK or Git configs. Please try again.')

            # Exit if passed by arg
            if cli.args.username:
                return False

    # Copy all the files
    copy_templates(keyboard_type, keyboard_path)

    # Replace all the placeholders
    keyboard_basename = keyboard_path.name
    replacements = [
        ('%YEAR%', str(date.today().year)),
        ('%KEYBOARD%', keyboard_basename),
        ('%YOUR_NAME%', user_name),
    ]
    filenames = [
        keyboard_path / 'config.h',
        keyboard_path / 'info.json',
        keyboard_path / 'readme.md',
        keyboard_path / f'{keyboard_basename}.c',
        keyboard_path / f'{keyboard_basename}.h',
        keyboard_path / 'keymaps/default/readme.md',
        keyboard_path / 'keymaps/default/keymap.c',
    ]
    replace_placeholders(replacements, filenames)

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


def copy_templates(keyboard_type, keyboard_path):
    """Copies the template files from data/templates to the new keyboard directory.
    """
    template_base_path = Path('data/templates')
    keyboard_basename = keyboard_path.name

    cli.log.info('Copying base template files...')
    shutil.copytree(template_base_path / 'base', keyboard_path)

    cli.log.info(f'Copying {{fg_cyan}}{keyboard_type}{{fg_reset}} template files...')
    shutil.copytree(template_base_path / keyboard_type, keyboard_path, dirs_exist_ok=True)

    cli.log.info(f'Renaming {{fg_cyan}}keyboard.[ch]{{fg_reset}} to {{fg_cyan}}{keyboard_basename}.[ch]{{fg_reset}}...')
    shutil.move(keyboard_path / 'keyboard.c', keyboard_path / f'{keyboard_basename}.c')
    shutil.move(keyboard_path / 'keyboard.h', keyboard_path / f'{keyboard_basename}.h')


def replace_placeholders(replacements, filenames):
    """Replaces the given placeholders in each template file.
    """
    for replacement in replacements:
        cli.log.info(f'Replacing {{fg_cyan}}{replacement[0]}{{fg_reset}} with {{fg_cyan}}{replacement[1]}{{fg_reset}}...')

        with fileinput.input(files=filenames, inplace=True) as file:
            for line in file:
                print(line.replace(replacement[0], replacement[1]), end='')
