"""This script automates the copying of the default keymap into your own keymap.
"""
import re
import json
import shutil
from pathlib import Path

from milc import cli
from milc.questions import question, choice

from qmk.constants import HAS_QMK_USERSPACE, QMK_USERSPACE
from qmk.errors import NoSuchKeyboardError
from qmk.path import is_keyboard, keymaps, keymap
from qmk.git import git_get_username
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.userspace import UserspaceDefs
from qmk.json_schema import json_load
from qmk.json_encoders import KeymapJSONEncoder
from qmk.info import info_json


def _list_available_converters(kb_name):
    """Search for converters that can be applied to a given keyboard
    """
    if not is_keyboard(kb_name):
        return None

    info = info_json(kb_name)
    pin_compatible = info.get('pin_compatible')
    if not pin_compatible:
        return None

    return sorted(folder.name.split('_to_')[-1] for folder in Path('platforms').glob(f'*/converters/{pin_compatible}_to_*'))


def _set_converter(file, converter):
    """add/overwrite any existing converter specified in keymap.json
    """
    json_data = json_load(file) if file.exists() else {}

    json_data['converter'] = converter

    output = json.dumps(json_data, cls=KeymapJSONEncoder, sort_keys=True)
    file.write_text(output + '\n', encoding='utf-8')


def validate_keymap_name(name):
    """Returns True if the given keymap name contains only a-z, 0-9 and underscore characters.
    """
    regex = re.compile(r'^[a-zA-Z0-9][a-zA-Z0-9_]+$')
    return bool(regex.match(name))


def prompt_keyboard():
    prompt = """{fg_yellow}Select Keyboard{style_reset_all}
If you're unsure you can view a full list of supported keyboards with {fg_yellow}qmk list-keyboards{style_reset_all}.

Keyboard Name? """
    return question(prompt)


def prompt_user():
    prompt = """
{fg_yellow}Name Your Keymap{style_reset_all}

Keymap name? """
    return question(prompt, default=git_get_username())


def prompt_converter(kb_name):
    prompt = """
{fg_yellow}Configure Development Board{style_reset_all}
For more information, see:
https://docs.qmk.fm/feature_converters

Use converter? """

    converters = _list_available_converters(kb_name)
    if not converters:
        return None

    choices = ['No (default)', *converters]

    answer = choice(prompt, options=choices, default=0)
    return None if choices.index(answer) == 0 else answer


@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.argument('-km', '--keymap', help='Specify the name for the new keymap directory')
@cli.argument('--converter', help='Specify the name of a converter to configure')
@cli.argument('--skip-converter', arg_only=True, action='store_true', help='Skip converter')
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
    converter = cli.config.new_keymap.converter if cli.args.skip_converter or cli.config.new_keymap.converter else prompt_converter(kb_name)

    # check directories
    try:
        kb_name = keyboard_folder(kb_name)
    except ValueError:
        cli.log.error(f'Keyboard {{fg_cyan}}{kb_name}{{fg_reset}} does not exist! Please choose a valid name.')
        return False

    # validate before any keymap ops
    try:
        keymaps_dirs = keymaps(kb_name)
        keymap_path_new = keymaps_dirs[0] / user_name
    except NoSuchKeyboardError:
        cli.log.error(f'Keymap folder for {{fg_cyan}}{kb_name}{{fg_reset}} does not exist!')
        return False

    keymap_path_default = keymap(kb_name, 'default')

    if not keymap_path_default:
        cli.log.error(f'Default keymap for {{fg_cyan}}{kb_name}{{fg_reset}} does not exist!')
        return False

    if not validate_keymap_name(user_name):
        cli.log.error('Keymap names must contain only {fg_cyan}a-z{fg_reset}, {fg_cyan}0-9{fg_reset} and {fg_cyan}_{fg_reset}! Please choose a different name.')
        return False

    if keymap_path_new.exists():
        cli.log.error(f'Keymap {{fg_cyan}}{user_name}{{fg_reset}} already exists! Please choose a different name.')
        return False

    # create user directory with default keymap files
    shutil.copytree(keymap_path_default, keymap_path_new, symlinks=True)

    if converter:
        _set_converter(keymap_path_new / 'keymap.json', converter)

    # end message to user
    cli.log.info(f'{{fg_green}}Created a new keymap called {{fg_cyan}}{user_name}{{fg_green}} in: {{fg_cyan}}{keymap_path_new}{{fg_reset}}.')
    cli.log.info(f"Compile a firmware with your new keymap by typing: {{fg_yellow}}qmk compile -kb {kb_name} -km {user_name}{{fg_reset}}.")

    # Add to userspace compile if we have userspace available
    if HAS_QMK_USERSPACE:
        userspace = UserspaceDefs(QMK_USERSPACE / 'qmk.json')
        userspace.add_target(keyboard=kb_name, keymap=user_name, do_print=False)
        return userspace.save()
