"""This script automates creating the files necessary for a new QMK keyboard.
"""
import shutil
import re

from milc import cli
from pathlib import Path
from datetime import datetime

from qmk.constants import SUPPORTED_MCUS
from qmk.keyboard import generate_pid
from qmk.questions import question
from qmk.keymap import rewrite_source


@cli.argument('-kb', '--keyboard', help='Specify keyboard name. Example: clueboard/66')
@cli.argument('-pr', '--project', help='The human-friendly name of the keyboard. Example: Clueboard 66%%')
@cli.argument('-mcu', '--microcontroller', help='Specify the microcontroller used for the keyboard.')
@cli.argument('-u', '--username', help='Your GitHub username. Will be pasted into generated files.')
@cli.subcommand('Creates a new keyboard project.')
def new_keyboard(cli):
    """Creates a new keyboard project.
    """

    # Root path for template files
    template_root_path = Path("quantum/template")
    template_base_path = template_root_path / "base"
    year = datetime.now().year
    valid_keyboard_name = re.compile(r'^[a-z0-9][a-z0-9_/]+$')

    if cli.args.keyboard:
        keyboard = keyboard_name = cli.args.keyboard
    else:
        # ask for user input if keyboard was not provided in the command line
        cli.echo("""What is the keyboard's project name?

    This will be the name used to compile firmware for your keyboard. The
    project name may only contain lower-case letters, numbers, underscores, and
    the forward slash, and must begin with a lower-case letter or a number.

    Files will be placed in `qmk_firmware/keyboards/<project_name>/`.""")
        keyboard = question("Project Name: ")

        while valid_keyboard_name.match(keyboard) == None:
            cli.echo(keyboard + " is not a valid project name.")
            keyboard = question("Project Name: ")

    if cli.args.project:
        keyboard_name = cli.args.project
    else:
        # Ask the common name of the keyboard, if not specified by --project
        cli.echo("""What is the keyboard's common name?

    This is the name that people will use to refer to your keyboard. It should
    be something human-friendly, like \"Clueboard 66%%\" or \"Ergodox EZ\".""")
        keyboard_name = question("Common Name: ")


    if cli.args.microcontroller:
        mcu = cli.args.microcontroller
        # Currently, AVRs are lowercase and STMs are uppercase. If the makefiles
        #   are reworked to change the letter case used internally,
        #   lib/python/qmk/constants.py must be updated to match.
        if mcu.lower() in SUPPORTED_MCUS:
            mcu = mcu.lower()
            arch = SUPPORTED_MCUS[mcu]
        elif mcu.upper() in SUPPORTED_MCUS:
            mcu = mcu.upper()
            arch = SUPPORTED_MCUS[mcu]
        else:
            cli.log.error(mcu + " is not a valid microcontroller option.")
            print("  Valid Options: ", ", ".join(SUPPORTED_MCUS) )
            exit(1)
    else:
        # Ask what microcontroller is being used
        cli.echo("Select the microcontroller used:\n")
        for i, mcu in enumerate(SUPPORTED_MCUS, 1):
            cli.echo("    %s: %s (%s)", str(i).rjust(2, " "), mcu, SUPPORTED_MCUS[mcu] )

        mcu = question("Microcontroller: (1-%d): ", len(SUPPORTED_MCUS), answer_type=int)
        # user-facing text is 1-indexed, but data is 0-indexed internally
        mcu -= 1
        # create a list of tuples from the dictionary
        mcu_list = [(name, SUPPORTED_MCUS[name]) for name in SUPPORTED_MCUS]
        arch = mcu_list[mcu][1]
        mcu = mcu_list[mcu][0]
    # Set the path to the MCU architecture's template files
    template_arch_path = template_root_path / arch


    # (Erovia) introducing the user.name variable would probably be better
    if cli.config.new_keyboard.username:
        user_name = cli.config.new_keyboard.username
    elif cli.args.username:
        user_name = cli.args.username
    else:
        # Ask the user for their GitHub username
        cli.echo("""What is your GitHub username?

    This value will be pasted into the new files in copyright headers, and used
    as the listed Keyboard Maintainer in the readme file.""")
        user_name = question("GitHub Username: ")

    # generate keyboard paths
    keyboard_path = Path("keyboards") / keyboard

    # check directories
    if keyboard_path.exists():
        cli.log.error('Keyboard %s already exists!', keyboard)
        exit(1)
    # if target directory is a subdirectory (keyboard project name contains a
    #   forward slash, create the parent directory first
    elif len(keyboard_path.parts) > 1:
        keyboard_path.parent.mkdir(parents=True, exist_ok=True)
    final_directory = keyboard_path.name

    # create user directory with default keyboard files
    shutil.copytree(template_base_path, keyboard_path, symlinks=True)
    kb_c = keyboard_path / "keyboard.c"
    kb_h = keyboard_path / "keyboard.h"
    kb_c.rename( keyboard_path / Path(final_directory + ".c") )
    kb_h.rename( keyboard_path / Path(final_directory + ".h") )

    # copy architecture files
    shutil.copy(template_arch_path / "config.h", keyboard_path)
    shutil.copy(template_arch_path / "readme.md", keyboard_path)
    shutil.copy(template_arch_path / "rules.mk", keyboard_path)
    if arch == "ps2avrgb":
        # only ps2avrgb keyboards require this file
        shutil.copy(template_arch_path / "usbconfig.h", keyboard_path)

    # rewrite the %YEAR%, %YOUR_NAME%, %KEYBOARD% and %PID% placeholders

    # generate and assign the Product ID value
    # Required before using rewrite_source()
    pid = generate_pid(keyboard_name)

    files = {'config.h', 'info.json', 'readme.md', 'rules.mk', final_directory + '.c', final_directory + '.h', 'keymaps/default/keymap.c', 'keymaps/default/readme.md'}
    for file in files:
        rewrite_source(keyboard_path / file, year, user_name, keyboard, final_directory, keyboard_name, pid, mcu)

    # end message to user
    cli.log.info("%s keyboard directory created in: %s", keyboard_name, keyboard_path)
    cli.log.info("Compile a firmware with your new keymap by typing: \n" + "qmk compile -kb %s -km default", keyboard)
