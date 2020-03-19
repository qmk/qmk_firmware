"""This script automates creating the files necessary for a new QMK keyboard.
"""
import shutil
import hashlib
import re

from milc import cli
from pathlib import Path
from datetime import datetime


@cli.argument('-kb', '--keyboard', help='Specify keyboard name. Example: clueboard/66')
@cli.argument('-pr', '--project', help='The human-friendly name of the keyboard. Example: Clueboard 66%')
@cli.argument('-mcu', '--microcontroller', help='Specify the microcontroller used for the keyboard.')
@cli.argument('-u', '--username', help='Your GitHub username. Will be pasted into generated files.')
@cli.subcommand('Creates a new keyboard project.')

def new_keyboard(cli):
    """Creates a new keyboard project.
    """

    # valid microcontroller choices
    mcus = (
        ( 'at90usb1286', 'avr' ),
        ( 'at90usb646' , 'avr' ),
        ( 'atmega16u2' , 'avr' ),
        ( 'atmega16u4' , 'avr' ),
        ( 'atmega328p' , 'avr' ),
        ( 'atmega32a'  , 'ps2avrgb' ),
        ( 'atmega32u2' , 'avr' ),
        ( 'atmega32u4' , 'avr' ),
        ( 'STM32F042'  , 'stm32' ),
        ( 'STM32F072'  , 'stm32' ),
        ( 'STM32F103'  , 'stm32' ),
        ( 'STM32F303'  , 'stm32' ),
    )

    # Generate the USB Product ID
    def generate_pid(str):
        str = str.encode('utf-8')
        str = hashlib.sha1(str).hexdigest()[0:4].upper()
        return str

    # Rewrites the %YEAR%, %YOUR_NAME%, %KEYBOARD% and %PID% placeholders in the
    #   new files.
    def rewrite_source(file):
        rw_file = Path(keyboard_path) / file
        file_contents = rw_file.read_text() \
            .replace("%YEAR%", str(year)) \
            .replace("%YOUR_NAME%", user_name) \
            .replace("%KEYBOARD%", keyboard) \
            .replace("%KEYBOARD_NAME%", keyboard_name) \
            .replace("%PID%", pid) \
            .replace("%MCU%", mcu)
        rw_file.write_text(file_contents)

    def print_microcontrollers():
        for i, mcu in enumerate(mcus, 1):
            cli.echo("     %s: %s (%s)", str(i).rjust(2, " "), mcu[0], mcu[1] )

    # Root path for template files
    template_root_path = Path("quantum/template")
    template_base_path = Path(template_root_path) / "base"
    year = datetime.now().year

    if cli.args.keyboard:
        keyboard = keyboard_name = cli.args.keyboard
    else:
        # ask for user input if keyboard was not provided in the command line
        print("""\n** What is the project name? **

        This will be the name used to compile firmware for your keyboard. The
        project name must match the regular expression `^[a-z0-9][a-z0-9_]+`.

        Files will be placed in `qmk_firmware/keyboards/<project_name>/`.""")
        keyboard = input("\n    Project Name: ")
        keyboard = re.sub(r'[^a-z0-9_]', "", keyboard.lower())

    if cli.args.project:
        keyboard_name = cli.args.project
    else:
        # Ask the common name of the keyboard, if not specified by --project
        print("""\n** What is the keyboard's name? **

        This is the name that people will use to refer to your keyboard. It should
        be something human-friendly, like \"Clueboard 66%\" or \"Ergodox EZ\".""")
        keyboard_name = input("\n    Name: ")


    if cli.args.microcontroller:
        mcu = cli.args.microcontroller.lower()
        #for k, v in enumerate(mcus):
        #    if mcu in v:
        #        arch = k
        #        break
        for key, value in enumerate(mcus):
            if mcu in value[0]:
                arch = value[1]
                break
        #print arch
    else:
    # Ask what microcontroller is being used
        print("\n** Select the microcontroller used: **\n")
        print_microcontrollers()

        # MCUs are saved with lowercase names to make the user input request
        #   case-insensitive
        mcus_avr = ["atmega16u2", "atmega32u2", "atmega16u4", "atmega32u4", \
            "at90usb646", "at90usb1286", "atmega328p"]
        mcus_ps2avrgb = ["atmega32a"]
        mcus_stm = ["stm32f042", "stm32f072", "stm32f103", "stm32f303"]

        mcu = int(input("\n    Microcontroller: (1-" + str(len(mcus)) + "): "))
        # user-facing text is 1-12, but data is 0-11 internally
        mcu = mcu - 1
        arch = mcus[mcu][1]
        mcu = mcus[mcu][0]
        mcu = mcu.lower()

        print("Debug: " + mcu + ", "+ arch)

    # Set the path to the MCU architecture's template files
    template_arch_path = Path(template_root_path) / arch

    # (Erovia) introducing the user.name variable would probably be better
    if cli.args.username:
        user_name = cli.args.username
    elif cli.config.user.keymap:
        user_name = cli.config.user.keymap
    else:
        # Ask the user for their GitHub username
        print("""\n** What is your GitHub username? **

        This value will be pasted into the new files in copyright headers, and used
        as the listed Keyboard Maintainer in the readme file.""")
        user_name = input("\n    GitHub Username: ")

    # generate keyboard paths
    keyboard_path = Path("keyboards") / keyboard

    # check directories
    if Path.exists(keyboard_path):
        cli.log.error('Keyboard %s already exists!', keyboard)
        exit(1)

    # create user directory with default keyboard files
    shutil.copytree(template_base_path, keyboard_path, symlinks=True)
    kb_c = Path(keyboard_path) / "keyboard.c"
    kb_h = Path(keyboard_path) / "keyboard.h"
    kb_c.rename( Path(keyboard_path) / Path(keyboard + ".c") )
    kb_h.rename( Path(keyboard_path) / Path(keyboard + ".h") )

    # copy architecture files
    shutil.copy(Path(template_arch_path) / "config.h", keyboard_path)
    shutil.copy(Path(template_arch_path) / "readme.md", keyboard_path)
    shutil.copy(Path(template_arch_path) / "rules.mk", keyboard_path)
    if ( arch == "ps2avrgb" ):
        # only ps2avrgb keyboards require this file
        shutil.copy(Path(template_arch_path) / "usbconfig.h", keyboard_path)
    if ( arch == "stm32" ):
        # STM32 MCUs need their names in uppercase
        mcu = mcu.upper()

    # rewrite the %YEAR%, %YOUR_NAME%, %KEYBOARD% and %PID% placeholders

    # generate and assign the Product ID value
    # Required before using rewrite_source()
    pid = generate_pid(keyboard_name)

    rewrite_source("config.h")
    rewrite_source("info.json")
    rewrite_source("readme.md")
    rewrite_source("rules.mk")
    rewrite_source(keyboard + ".c")
    rewrite_source(keyboard + ".h")
    rewrite_source("keymaps/default/keymap.c")
    rewrite_source("keymaps/default/config.h")
    rewrite_source("keymaps/default/readme.md")

    # end message to user
    print("\n")
    cli.log.info("%s keyboard directory created in: %s", keyboard, keyboard_path)
    cli.log.info("Compile a firmware with your new keymap by typing: \n" + "qmk compile -kb %s -km default", keyboard)
