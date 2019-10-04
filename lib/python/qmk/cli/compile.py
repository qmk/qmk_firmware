"""Compile a QMK Firmware.

You can compile a keymap already in the repo or using a QMK Configurator export.
"""
import subprocess
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
    keyboard = ""
    keymap = "default"

    # Set path for '/keyboards/' directory
    keyboards_path = os.path.join(qmk_path , "keyboards")
    layouts_path = os.path.join(qmk_path, "layouts")

    # If below 'keyboards' and not in 'keyboards', get current keyboard name
    if cwd.startswith(keyboards_path):
        if current_folder != "keyboards" and current_folder != "keymaps":
            if os.path.basename(os.path.abspath(os.path.join(cwd, ".."))) == "keymaps":
                relative_path = cwd[len(keyboards_path):][1:]
                keyboard = str(relative_path).split("/keymaps", 1)[0]
                keymap = str(relative_path.rsplit("/", 1)[-1])
            else:
                keyboard = str(cwd[len(keyboards_path):])[1:]

            in_keyboard= True

    # If in layouts dir
    if cwd.startswith(layouts_path):
        if current_folder != "layouts":
            layout = str(cwd[len(keyboards_path):])[1:]
            in_layout=True

    if cli.args.filename:
        # Parse the configurator json
        user_keymap = parse_configurator_json(cli.args.filename)

        # Generate the keymap
        keymap_path = qmk.path.keymap(user_keymap['keyboard'])
        cli.log.info('Creating {fg_cyan}%s{style_reset_all} keymap in {fg_cyan}%s', user_keymap['keymap'], keymap_path)

        # Compile the keymap
        command = compile_configurator_json(cli.args.filename)

        cli.log.info('Wrote keymap to {fg_cyan}%s/%s/keymap.c', keymap_path, user_keymap['keymap'])

    elif cli.config.compile.keyboard and cli.config.compile.keymap:
        # Generate the make command for a specific keyboard/keymap.
        command = ['make', ':'.join((cli.config.compile.keyboard, cli.config.compile.keymap))]
    
    elif in_keyboard:   
        # Get path for keyboard directory
        keymap_path = qmk.path.keymap(keyboard) 

        # Check for global keymap config first
        if cli.config.compile.keymap:
            command = ['make', ':'.join((keyboard, cli.config.compile.keymap))]

        # Check if keyboard has default layout
        elif os.path.exists(keymap_path + "/default"):
            
            # Generate the make command for the current directories keyboard
            command = ['make', ':'.join((keyboard, keymap))]

        else:
            # If no default keymap exists and none provided
            cli.log.error('This directory does not contain a default keymap. Set one with `qmk config` or supply `--keymap` ')
            return False

    elif in_layout:
        if cli.config.compile.keyboard:
            keymap = current_folder
            command = ['make', ':'.join((cli.config.compile.keyboard, keymap))]


    else:
        cli.log.error('You must supply a configurator export or both `--keyboard` and `--keymap`, or be a directory for a keyboard or keymap.')
        return False

    cli.log.info('Compiling keymap with {fg_cyan}%s\n\n', ' '.join(command))
    subprocess.run(command)
