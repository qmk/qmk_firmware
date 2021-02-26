"""This script automates the creation of keyboards and import of info.json into the repo.
"""
import qmk.keymap
import qmk.path
import hjson
import json

from milc import cli
from qmk.info import keyboard_validate
from qmk.path import keyboard


def _gen_dummy_keymap(name, info_data):
    # Pick the first layout macro and just dump in KC_NOs or something?
    (layout_name, layout_data), *_ = info_data["layouts"].items()
    layout_length = len(layout_data["layout"])

    keymap_data = {
        "keyboard": name,
        "layout": layout_name,
        "layers": [["KC_NO" for _ in range(0, layout_length)]],
    }

    return json.dumps(keymap_data)


def import_info_json(name, info):
    # Validate to ensure we don't have to deal with bad data - handles stdin/file
    info_data = hjson.load(info)
    keyboard_validate(info_data)

    kb_folder = keyboard(name)
    keyboard_info = kb_folder / 'info.json'
    keyboard_rules = kb_folder / 'rules.mk'
    keyboard_keymap = kb_folder / 'keymaps' / 'default' / 'keymap.json'

    # This is the deepest folder in the expected tree
    keyboard_keymap.parent.mkdir(parents=True, exist_ok=True)

    # Dump out all those lovely files
    keyboard_info.write_text(json.dumps(info_data))
    keyboard_rules.write_text("")
    keyboard_keymap.write_text(_gen_dummy_keymap(name, info_data))


@cli.argument('-kb', '--keyboard', arg_only=True, help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.argument('filename', type=qmk.path.FileType('r'), nargs='?', arg_only=True, help='info JSON file')
@cli.subcommand('Creates a new keyboard')
def new_keyboard(cli):
    """Creates a new keyboard
    """
    if cli.args.filename:
        import_info_json(cli.args.keyboard, cli.args.filename)
    else:
        # TODO: replace this bodge to the existing script
        cli.run(['util/new_keyboard.sh'], capture_output=False)
