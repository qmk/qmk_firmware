import json
import os

from milc import cli
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.path import is_keyboard
from pathlib import Path
from qmk.constants import KEYBOARD_OUTPUT_PREFIX
from qmk.c_parse import extract_enum_from_c_file_as_dict
from qmk.json_encoders import InfoJSONEncoder


@cli.argument("-kb", "--keyboard", type=keyboard_folder, completer=keyboard_completer)
@cli.argument('-km', '--keymap', help='keymap to evaluate')
@cli.subcommand("RGB Effect information")
@automagic_keyboard
@automagic_keymap
def rgb_effects(cli):
    """Output enabled RGB matrix effects as json list format for use with via"""

    # Determine our keyboard(s)
    if not cli.args.keyboard:
        cli.log.error('Missing parameter: --keyboard')
        cli.subcommands['rgb-effects'].print_help()
        return False

    if not is_keyboard(cli.args.keyboard):
        cli.log.error('Invalid keyboard: "%s"', cli.args.keyboard)
        return False

    if not cli.args.keymap:
        cli.log.error('Missing parameter: --keymap')
        cli.subcommands['rgb-effects'].print_help()
        return False

    keymap = cli.args.keymap
    keyboard = cli.args.keyboard
    keyboard_filesafe = keyboard.replace('/', '_')
    rgb_matrix_path = Path(f'{KEYBOARD_OUTPUT_PREFIX}{keyboard_filesafe}_{keymap}/quantum/rgb_matrix/rgb_matrix.i')

    if not os.path.exists(rgb_matrix_path):
        cli.log.error(f"{rgb_matrix_path} does not exist.")
        cli.log.error("Please compile the image first.")
        return False

    with open(rgb_matrix_path, 'r') as f:
        file_contents = f.read()
    enum_as_dict = {key: value for (key, value) in extract_enum_from_c_file_as_dict(file_contents, "rgb_matrix_effects").items() if key != "RGB_MATRIX_EFFECT_MAX"}

    max_value = max(enum_as_dict.values())

    def enum_name_to_effect_name(x):
        return x.replace("RGB_MATRIX_", "")

    formatted = [[f"{str(idx).zfill(len(str(max_value)))}. {enum_name_to_effect_name(enum_name)}", value] for idx, [enum_name, value] in enumerate(enum_as_dict.items())]
    print(json.dumps(formatted, cls=InfoJSONEncoder))
