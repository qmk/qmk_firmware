"""This script automates the creation of new keyboard directories using a starter template.
"""
import re
import json
import shutil
from datetime import date
from pathlib import Path
from dotty_dict import dotty

from milc import cli
from milc.questions import choice, question

from qmk.git import git_get_username
from qmk.json_schema import load_jsonschema
from qmk.path import keyboard
from qmk.json_encoders import InfoJSONEncoder
from qmk.json_schema import deep_update, json_load
from qmk.constants import MCU2BOOTLOADER, QMK_FIRMWARE

COMMUNITY = Path('layouts/default/')
TEMPLATE = Path('data/templates/keyboard/')

# defaults
schema = dotty(load_jsonschema('keyboard'))
mcu_types = sorted(schema["properties.processor.enum"], key=str.casefold)
dev_boards = sorted(schema["properties.development_board.enum"], key=str.casefold)
available_layouts = sorted([x.name for x in COMMUNITY.iterdir() if x.is_dir()])


def mcu_type(mcu):
    """Callable for argparse validation.
    """
    if mcu not in (dev_boards + mcu_types):
        raise ValueError
    return mcu


def layout_type(layout):
    """Callable for argparse validation.
    """
    if layout not in available_layouts:
        raise ValueError
    return layout


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


def select_default_bootloader(mcu):
    """Provide sane defaults for bootloader
    """
    return MCU2BOOTLOADER.get(mcu, "custom")


def replace_placeholders(src, dest, tokens):
    """Replaces the given placeholders in each template file.
    """
    content = src.read_text()
    for key, value in tokens.items():
        content = content.replace(f'%{key}%', value)

    dest.write_text(content)


def augment_community_info(src, dest):
    """Splice in any additional data into info.json
    """
    info = json.loads(src.read_text())
    template = json.loads(dest.read_text())

    # merge community with template
    deep_update(info, template)

    # avoid assumptions on macro name by using the first available
    first_layout = next(iter(info["layouts"].values()))["layout"]

    # guess at width and height now its optional
    width, height = (0, 0)
    for item in first_layout:
        width = max(width, int(item["x"]) + 1)
        height = max(height, int(item["y"]) + 1)

    info["matrix_pins"] = {
        "cols": ["C2"] * width,
        "rows": ["D1"] * height,
    }

    # assume a 1:1 mapping on matrix to electrical
    for item in first_layout:
        item["matrix"] = [int(item["y"]), int(item["x"])]

    # finally write out the updated info.json
    dest.write_text(json.dumps(info, cls=InfoJSONEncoder, sort_keys=True))


def _question(*args, **kwargs):
    """Ugly workaround until 'milc' learns to display a repromt msg
    """
    # TODO: Remove this once milc.questions.question handles reprompt messages

    reprompt = kwargs["reprompt"]
    del kwargs["reprompt"]
    validate = kwargs["validate"]
    del kwargs["validate"]

    prompt = args[0]
    ret = None
    while not ret:
        ret = question(prompt, **kwargs)
        if not validate(ret):
            ret = None
            prompt = reprompt

    return ret


def prompt_keyboard():
    prompt = """{fg_yellow}Name Your Keyboard Project{style_reset_all}
For more infomation, see:
https://docs.qmk.fm/#/hardware_keyboard_guidelines?id=naming-your-keyboardproject

Keyboard Name? """

    errmsg = 'Keyboard already exists! Please choose a different name:'

    return _question(prompt, reprompt=errmsg, validate=lambda x: not keyboard(x).exists())


def prompt_user():
    prompt = """
{fg_yellow}Attribution{style_reset_all}
Used for maintainer, copyright, etc

Your GitHub Username? """
    return question(prompt, default=git_get_username())


def prompt_name(def_name):
    prompt = """
{fg_yellow}More Attribution{style_reset_all}
Used for maintainer, copyright, etc

Your Real Name? """
    return question(prompt, default=def_name)


def prompt_layout():
    prompt = """
{fg_yellow}Pick Base Layout{style_reset_all}
As a starting point, one of the common layouts can be used to bootstrap the process

Default Layout? """
    # avoid overwhelming user - remove some?
    filtered_layouts = [x for x in available_layouts if not any(xs in x for xs in ['_split', '_blocker', '_tsangan', '_f13'])]
    filtered_layouts.append("none of the above")

    return choice(prompt, filtered_layouts, default=len(filtered_layouts) - 1)


def prompt_mcu():
    prompt = """
{fg_yellow}What Powers Your Project{style_reset_all}
For more infomation, see:
https://docs.qmk.fm/#/compatible_microcontrollers

MCU? """
    # remove any options strictly used for compatibility
    filtered_mcu = [x for x in (dev_boards + mcu_types) if not any(xs in x for xs in ['cortex', 'unknown'])]

    return choice(prompt, filtered_mcu, default=filtered_mcu.index("atmega32u4"))


@cli.argument('-kb', '--keyboard', help='Specify the name for the new keyboard directory', arg_only=True, type=keyboard_name)
@cli.argument('-l', '--layout', help='Community layout to bootstrap with', arg_only=True, type=layout_type)
@cli.argument('-t', '--type', help='Specify the keyboard MCU type (or "development_board" preset)', arg_only=True, type=mcu_type)
@cli.argument('-u', '--username', help='Specify your username (default from Git config)', dest='name')
@cli.argument('-n', '--realname', help='Specify your real name if you want to use that. Defaults to username', arg_only=True)
@cli.subcommand('Creates a new keyboard directory')
def new_keyboard(cli):
    """Creates a new keyboard.
    """
    cli.log.info('{style_bright}Generating a new QMK keyboard directory{style_normal}')
    cli.echo('')

    kb_name = cli.args.keyboard if cli.args.keyboard else prompt_keyboard()
    if not validate_keyboard_name(kb_name):
        cli.log.error('Keyboard names must contain only {fg_cyan}lowercase a-z{fg_reset}, {fg_cyan}0-9{fg_reset}, and {fg_cyan}_{fg_reset}! Please choose a different name.')
        return 1

    if keyboard(kb_name).exists():
        cli.log.error(f'Keyboard {{fg_cyan}}{kb_name}{{fg_reset}} already exists! Please choose a different name.')
        return 1

    user_name = cli.config.new_keyboard.name if cli.config.new_keyboard.name else prompt_user()
    real_name = cli.args.realname or cli.config.new_keyboard.name if cli.args.realname or cli.config.new_keyboard.name else prompt_name(user_name)
    default_layout = cli.args.layout if cli.args.layout else prompt_layout()
    mcu = cli.args.type if cli.args.type else prompt_mcu()

    # Preprocess any development_board presets
    if mcu in dev_boards:
        defaults_map = json_load(Path('data/mappings/defaults.hjson'))
        board = defaults_map['development_board'][mcu]

        mcu = board['processor']
        bootloader = board['bootloader']
    else:
        bootloader = select_default_bootloader(mcu)

    tokens = {  # Comment here is to force multiline formatting
        'YEAR': str(date.today().year),
        'KEYBOARD': kb_name,
        'USER_NAME': user_name,
        'REAL_NAME': real_name,
        'LAYOUT': default_layout,
        'MCU': mcu,
        'BOOTLOADER': bootloader
    }

    if cli.config.general.verbose:
        cli.log.info("Creating keyboard with:")
        for key, value in tokens.items():
            cli.echo(f"    {key.ljust(10)}:   {value}")

    # TODO: detach community layout and rename to just "LAYOUT"
    if default_layout == 'none of the above':
        default_layout = "ortho_4x4"

    # begin with making the deepest folder in the tree
    keymaps_path = keyboard(kb_name) / 'keymaps/'
    keymaps_path.mkdir(parents=True)

    # copy in keymap.c or keymap.json
    community_keymap = Path(COMMUNITY / f'{default_layout}/default_{default_layout}/')
    shutil.copytree(community_keymap, keymaps_path / 'default')

    # process template files
    for file in list(TEMPLATE.iterdir()):
        replace_placeholders(file, keyboard(kb_name) / file.name, tokens)

    # merge in infos
    community_info = Path(COMMUNITY / f'{default_layout}/info.json')
    augment_community_info(community_info, keyboard(kb_name) / community_info.name)

    cli.log.info(f'{{fg_green}}Created a new keyboard called {{fg_cyan}}{kb_name}{{fg_green}}.{{fg_reset}}')
    cli.log.info(f"Build Command: {{fg_yellow}}qmk compile -kb {kb_name} -km default{{fg_reset}}.")
    cli.log.info(f'Project Location: {{fg_cyan}}{QMK_FIRMWARE}/{keyboard(kb_name)}{{fg_reset}},')
    cli.log.info("{{fg_yellow}}Now update the config files to match the hardware!{{fg_reset}}")
