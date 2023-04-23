"""This script automates the copying of the default keymap into your own keymap.
"""
import shutil

from milc import cli
from milc.questions import question

from qmk.path import is_keyboard, keymap
from qmk.git import git_get_username
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.keyboard import keyboard_completer, keyboard_folder


def prompt_keyboard():
    prompt = """{fg_yellow}Select Keyboard{style_reset_all}
If you`re unsure you can view a full list of supported keyboards with {fg_yellow}qmk list-keyboards{style_reset_all}.

Keyboard Name? """

    return question(prompt)


def prompt_user():
    prompt = """
{fg_yellow}Name Your Keymap{style_reset_all}
Used for maintainer, copyright, etc

Your GitHub Username? """
    return question(prompt, default=git_get_username())


@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.argument('-km', '--keymap', help='Specify the name for the new keymap directory')
@cli.subcommand('Creates a new keymap for the keyboard of your choosing')
@automagic_keyboard
@automagic_keymap
def new_keymap(cli):
    """Creates a new keymap for the keyboard of your choosing.
    """
    cli.log.info('{style_bright}Generating a new keymap{style_normal}')
    cli.echo('')

    # ask for user input if keyboard or keymap was not provided in the command line
    kb_name = cli.config.new_keymap.keyboard if cli.config.new_keymap.keyboard else prompt_keyboard()
    user_name = cli.config.new_keymap.keymap if cli.config.new_keymap.keymap else prompt_user()

    # check directories
    if not is_keyboard(kb_name):
        cli.log.error(f'Keyboard {{fg_cyan}}{kb_name}{{fg_reset}} does not exist! Please choose a valid name.')
        return False

    # generate keymap paths
    km_path = keymap(kb_name)
    keymap_path_default = km_path / 'default'
    keymap_path_new = km_path / user_name

    if not keymap_path_default.exists():
        cli.log.error(f'Default keymap {{fg_cyan}}{keymap_path_default}{{fg_reset}} does not exist!')
        return False

    if keymap_path_new.exists():
        cli.log.error(f'Keymap {{fg_cyan}}{user_name}{{fg_reset}} already exists! Please choose a different name.')
        return False

    # create user directory with default keymap files
    shutil.copytree(keymap_path_default, keymap_path_new, symlinks=True)

    # end message to user
    cli.log.info(f'{{fg_green}}Created a new keymap called {{fg_cyan}}{user_name}{{fg_green}} in: {{fg_cyan}}{keymap_path_new}.{{fg_reset}}')
    cli.log.info(f"Compile a firmware with your new keymap by typing: {{fg_yellow}}qmk compile -kb {kb_name} -km {user_name}{{fg_reset}}.")
