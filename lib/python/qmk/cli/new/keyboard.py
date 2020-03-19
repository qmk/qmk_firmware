"""This script automates creating the files necessary for a new QMK keyboard.
"""
import os
import shutil
import hashlib
import re

from milc import cli
from pathlib import Path
from datetime import datetime


@cli.argument('-kb', '--keyboard', help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.argument('-mcu', '--microcontroller', help='Specify the microcontroller used for the keyboard.')
@cli.subcommand('Creates a new keyboard project.')

def new_keyboard(cli):
    """Creates a new keyboard project.
    """

    # Generate the USB Product ID
    def generate_pid(str):
        str = str.encode('utf-8')
        str = hashlib.sha1(str).hexdigest()[0:4].upper()
        return str

    # Rewrites the %YEAR%, %YOUR_NAME%, %KEYBOARD% and %PID% placeholders in the
    #   new files.
    def rewrite_source(file):
        rw_file = Path(kb_path) / file
        file_contents = rw_file.read_text() \
            .replace("%YEAR%", str(year)) \
            .replace("%YOUR_NAME%", user_name) \
            .replace("%KEYBOARD%", keyboard) \
            .replace("%KEYBOARD_NAME%", keyboard_name) \
            .replace("%PID%", pid)
        rw_file.write_text(file_contents)

    # Root path for template files
    template_root_path = Path.cwd() / "quantum/template"
    year = datetime.now().year

    # ask for user input if keyboard was not provided in the command line
    # TODO: figure out how to get this script to take arguments from CLI
    print("""\n** What is the project name? **

    This will be the name used to compile firmware for your keyboard.

    Files will be placed in `qmk_firmware/keyboards/<project name>/`.""")
    keyboard = input("\nProject Name: ")
    keyboard = re.sub(r'[^a-z0-9_]', "", keyboard)

    #print("Project Name ")

    print("""\n** What is the keyboard's name? **

    This is the name that people will use to refer to your keyboard. It should
    be something human-friendly, like \"Clueboard 66%\" or \"Ergodox EZ\".""")
    keyboard_name = input("\nName: ")

    print("\nSelect the microcontroller used:")
    print("     atmega16u2    atmega32u2     atmega16u4    atmega32u4")
    print("     at90usb646    at90usb1286    atmega32a     atmega328p")
    print("     STM32F042     STM32F072      STM32F103     STM32F303")

    # MCUs are saved with lowercase names to make the user input request
    #   case-insensitive
    mcus_avr = ["atmega16u2", "atmega32u2", "atmega16u4", "atmega32u4", \
        "at90usb646", "at90usb1286", "atmega328p"]
    mcus_ps2avrgb = ["atmega32a"]
    mcus_stm = ["stm32f042", "stm32f072", "stm32f103", "stm32f303"]

    mcu = input("\nMicrocontroller: ")
    mcu = mcu.lower()

    # Set the MCU Architecture
    if mcu in mcus_avr:
        arch = "avr"
    elif mcu in mcus_ps2avrgb:
        arch = "ps2avrgb"
    elif mcu in mcus_stm:
        arch = "stm32"
    else:
        print("Invalid microcontroller.")
        exit(1)

    template_arch_path = Path(template_root_path) / arch

    # Ask the user for their name
    user_name = input("\nYour Name: ")

    # generate keymap paths
    kb_path = Path.cwd() / "keyboards" / keyboard
    template_base_path = Path(template_root_path) / "base"

    # check directories
    if Path.exists(kb_path):
        cli.log.error('Keyboard %s already exists!', keyboard)
        exit(1)

    # create user directory with default keymap files
    shutil.copytree(template_base_path, kb_path, symlinks=True)
    os.rename( \
        Path(kb_path) / "keyboard.c", \
        Path(kb_path) / keyboard + ".c" \
    )
    os.rename( \
        Path(kb_path) / "keyboard.h", \
        Path(kb_path) / keyboard + ".h" \
    )
    # copy architecture files
    shutil.copy(Path(template_arch_path) / "config.h", kb_path)
    shutil.copy(Path(template_arch_path) / "readme.md", kb_path)
    shutil.copy(Path(template_arch_path) / "rules.mk", kb_path)
    if ( arch == "ps2avrgb" ):
        shutil.copy(Path(template_arch_path) / "usbconfig.h", kb_path)
    if ( arch == "stm32" ):
        # STM32 MCUs need their names in uppercase
        mcu = mcu.upper()

    # rewrite the rules.mk file with the requested MCU rule
    rules = Path(kb_path) / "rules.mk"
    file_contents = rules.read_text()
    file_contents = file_contents.replace("%MCU%", mcu)
    rules.write_text(file_contents)

    # rewrite the %YEAR%, %YOUR_NAME%, %KEYBOARD% and %PID% placeholders

    # generate and assign the Product ID value
    # Required before using rewrite_source()
    pid = generate_pid(keyboard_name)

    rewrite_source("config.h")
    rewrite_source("info.json")
    rewrite_source("readme.md")
    rewrite_source(keyboard + ".c")
    rewrite_source(keyboard + ".h")
    rewrite_source("keymaps/default/keymap.c")
    rewrite_source("keymaps/default/config.h")
    rewrite_source("keymaps/default/readme.md")


    # end message to user
    cli.log.info("%s keyboard directory created in: %s", keyboard, kb_path)
    cli.log.info("Compile a firmware with your new keymap by typing: \n" + "qmk compile -kb %s -km default", keyboard)
