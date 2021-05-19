"""This script automates the creation of keyboards.
"""
import math
import json
import shutil
from pathlib import Path
from dotty_dict import dotty

from milc import cli
from milc.questions import choice, question

from qmk.json_schema import load_jsonschema
from qmk.path import keyboard
from qmk.json_encoders import InfoJSONEncoder
from qmk.json_schema import deep_update

COMMUNITY = Path('layouts/default/')
TEMPLATE = Path('quantum/template/')

# defaults
schema = dotty(load_jsonschema('keyboard'))
mcu_types = sorted(schema["properties.processor.enum"], key=str.casefold)
available_layouts = sorted([x.name for x in COMMUNITY.iterdir() if x.is_dir()])


def _replace_tokens(src, dest, tokens):
    content = src.read_text()
    for key, value in tokens.items():
        content = content.replace(f'%{key}%', value)

    dest.write_text(content)


def _augment_community_info(src, dest, tokens):
    info = json.loads(src.read_text())

    defaults = {
        "keyboard_name": tokens["KEYBOARD"],
        "manufacturer": tokens["YOUR_NAME"],
        "maintainer": tokens["YOUR_NAME"],
        "processor": tokens["MCU"],
        "diode_direction": "COL2ROW",
        "matrix_pins": {
            "cols": ["C2"] * int(math.ceil(info["width"])),
            "rows": ["D1"] * int(math.ceil(info["height"])),
        },
        "usb": {
            "vid": "0xFEED",
            "pid": "0x0000",
            "device_ver": "0x0001"
        },
        "features": {
            "bootmagic_lite": True,
            "command": False,
            "console": False,
            "extrakey": True,
            "mousekey": True,
            "nkro": True
        }
    }
    deep_update(info, defaults)

    # bodge matrix data
    _, layout = next(iter(info["layouts"].items()))
    for item in layout["layout"]:
        item["matrix"] = [int(item["y"]), int(item["x"])]

    dest.write_text(json.dumps(info, cls=InfoJSONEncoder))


def _get_git_username():
    git_config = cli.run(['git', 'config', '--get', 'user.name'])

    if git_config.returncode == 0:
        return git_config.stdout.strip()


def _prompt_keyboard():
    prompt = """{fg_yellow}Name Your Keyboard Project{style_reset_all}

For more infomation, see:
https://docs.qmk.fm/#/hardware_keyboard_guidelines?id=naming-your-keyboardproject

keyboard Name? """

    return question(prompt, validate=lambda x: not keyboard(x).exists())


def _prompt_user():
    prompt = """{fg_yellow}Attribution{style_reset_all}

Used for maintainer, copyright, etc

Your Name? """
    return question(prompt, default=_get_git_username())


def _prompt_layout():
    # avoid overwhelming user - remove some?
    filtered_layouts = [x for x in available_layouts if not any(xs in x for xs in ['_split', '_blocker', '_tsangan'])]
    filtered_layouts.append("none of the above")

    prompt = """{fg_yellow}Pick Base Layout{style_reset_all}

As a starting point, one of the common layouts can be used to bootstrap the process

Default Layout? """
    return choice(prompt, filtered_layouts, default=filtered_layouts.index("ortho_4x4"))


def _prompt_mcu():
    # avoid overwhelming user - remove some?
    filtered_mcu = [x for x in mcu_types if not any(xs in x for xs in ['cortex', 'unknown'])]

    prompt = """{fg_yellow}What Powers Your Project{style_reset_all}

For more infomation, see:
https://docs.qmk.fm/#/compatible_microcontrollers

MCU? """
    return choice(prompt, filtered_mcu, default=filtered_mcu.index("atmega32u4"))


@cli.argument('-kb', '--keyboard', arg_only=True, help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.argument('-l', '--layout', arg_only=True, help='Community layout to bootstrap with')
@cli.argument('-u', '--user', arg_only=True, help='Username. Used for maintainer, copyright, etc')
@cli.argument('-m', '--mcu', arg_only=True, help='mcu')
@cli.subcommand('Creates a new keyboard')
def new_keyboard(cli):
    """Creates a new keyboard
    """
    kb_name = cli.args.keyboard if cli.args.keyboard else _prompt_keyboard()
    user_name = cli.args.user if cli.args.user else _prompt_user()
    default_layout = cli.args.layout if cli.args.layout else _prompt_layout()
    mcu = cli.args.mcu if cli.args.mcu else _prompt_mcu()

    tokens = {
        'KEYBOARD': kb_name,
        'YOUR_NAME': user_name,
        'LAYOUT': default_layout,
        'MCU': mcu,
    }

    cli.log.info("Creating keyboard with:")
    for key, value in tokens.items():
        cli.echo(f"    {key.ljust(10)}:   {value}")

    # begin with making the deepest folder in the tree
    keymaps_path = keyboard(kb_name) / 'keymaps/default/'
    keymaps_path.mkdir(parents=True)

    # copy in keymap.c or keymap.json
    community_keymap = Path(COMMUNITY / f'{default_layout}/default_{default_layout}/')
    shutil.copytree(community_keymap, keymaps_path, dirs_exist_ok=True)

    # merge in infos
    community_info = Path(COMMUNITY / f'{default_layout}/info.json')
    _augment_community_info(community_info, keyboard(kb_name) / community_info.name, tokens)

    # process template files
    for file in list(TEMPLATE.iterdir()):
        _replace_tokens(file, keyboard(kb_name) / file.name, tokens)

    cli.log.info("Created a new keyboard called {fg_yellow}%s{style_reset_all}." % kb_name)
    cli.log.info("To start working on things, cd into {fg_yellow}keyboards/%s{style_reset_all}, or open the directory in your favorite text editor." % kb_name)
