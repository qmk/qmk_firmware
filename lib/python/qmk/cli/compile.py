"""Compile a QMK Firmware.

You can compile a keymap already in the repo or using a QMK Configurator export.
"""
import subprocess
import os
from argparse import FileType

from milc import cli
from qmk.commands import create_make_command
from qmk.commands import parse_configurator_json
from qmk.commands import compile_configurator_json

import qmk.keymap
import qmk.path


@cli.argument('filename', nargs='?', arg_only=True, type=FileType('r'), help='The configurator export to compile')
@cli.argument('-kb', '--keyboard', help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.subcommand('Compile a QMK Firmware.')
def compile(cli):
    """Compile a QMK Firmware.

    If a Configurator export is supplied this command will create a new keymap, overwriting an existing keymap if one exists.

    FIXME(skullydazed): add code to check and warn if the keymap already exists

    If --keyboard and --keymap are provided this command will build a firmware based on that.

    """
    # Set CWD as directory command was issued from
    cwd = os.environ['ORIG_CWD']
    qmk_path = os.getcwd()
    current_folder = os.path.basename(cwd)
    # Initialize boolean to check for being in a keyboard directory and initialize keyboard string
    in_keyboard = False
    in_layout = False
    keyboard = ""
    keymap = ""
    user_keymap = ""
    user_keyboard = ""

    # Set path for '/keyboards/' directory
    keyboards_path = os.path.join(qmk_path, "keyboards")
    layouts_path = os.path.join(qmk_path, "layouts")

    # If below 'keyboards' and not in 'keyboards' or 'keymaps', get current keyboard name
    if cwd.startswith(keyboards_path):
        if current_folder != "keyboards" and current_folder != "keymaps":
            if os.path.basename(os.path.abspath(os.path.join(cwd, ".."))) == "keymaps":
                # If in a keymap folder, set relative path, get everything before /keymaps, and the keymap name
                relative_path = cwd[len(keyboards_path):][1:]
                keyboard = str(relative_path).split("/keymaps", 1)[0]
                keymap = str(relative_path.rsplit("/", 1)[-1])
            else:
                keyboard = str(cwd[len(keyboards_path):])[1:]

            in_keyboard = True

    # If in layouts dir
    if cwd.startswith(layouts_path):
        if current_folder != "layouts":
            in_layout = True

    # If user keyboard/keymap or compile keyboard/keymap are supplied, assign those
    if cli.config.compile.keyboard:
        user_keyboard = cli.config.compile.keyboard
    if cli.config.compile.keymap and not in_layout:
        user_keymap = cli.config.compile.keymap

    if cli.args.filename:
        # Parse the configurator json
        user_keymap = parse_configurator_json(cli.args.filename)

        # Generate the keymap
        keymap_path = qmk.path.keymap(user_keymap['keyboard'])
        cli.log.info('Creating {fg_cyan}%s{style_reset_all} keymap in {fg_cyan}%s', user_keymap['keymap'], keymap_path)

        # Compile the keymap
        command = compile_configurator_json(cli.args.filename)

        cli.log.info('Wrote keymap to {fg_cyan}%s/%s/keymap.c', keymap_path, user_keymap['keymap'])

    elif user_keyboard and user_keymap:
        # Generate the make command for a specific keyboard/keymap.
        command = create_make_command(user_keyboard, user_keymap)

    elif in_keyboard:
        keyboard = user_keyboard if user_keyboard else keyboard
        keymap = user_keymap if user_keymap else keymap

        if not os.path.exists(os.path.join(keyboards_path, keyboard, "rules.mk")):
            cli.log.error('This directory does not contain a rules.mk file. Change directory or supply --keyboard with optional --keymap')
            return False

        # Get path for keyboard directory
        keymap_path = qmk.path.keymap(keyboard)

        # Check for global keymap config first
        if keymap:
            command = create_make_command(keyboard, keymap)

        else:
            # If no default keymap exists and none provided
            cli.log.error('This directory does not contain a keymap. Set one with `qmk config` or supply `--keymap` ')
            return False

    elif in_layout:
        if user_keyboard:
            keymap = current_folder
            command = create_make_command(user_keyboard, keymap)
        else:
            cli.log.error('You must supply a keyboard to compile a layout keymap. Set one with `qmk config` or supply `--keyboard` ')
            return False

    else:
        cli.log.error('You must supply a configurator export, both `--keyboard` and `--keymap`, or be in a directory for a keyboard or keymap.')
        return False

    cli.log.info('Compiling keymap with {fg_cyan}%s\n\n', ' '.join(command))
    subprocess.run(command)
