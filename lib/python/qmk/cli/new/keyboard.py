"""This script automates creating the files necessary for a new QMK keyboard.
"""
import os
import shutil

from milc import cli
from pathlib import Path
from datetime import datetime
#from . import edit_file
import hashlib


@cli.argument('-kb', '--keyboard', help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.argument('-mcu', '--microcontroller', help='Specify the microcontroller used for the keyboard.')
@cli.subcommand('Creates a new keyboard project.')

def new_keyboard(cli):
    """Creates a new keyboard project.
    """

    # Root path for template files
    template_root_path = os.path.join(os.getcwd(), "quantum/template")
    year = datetime.now().year

    # ask for user input if keyboard was not provided in the command line
    keyboard = input("\nKeyboard Name: ")

    print("\nSelect the microcontroller used:")
    print("     atmega16u2    atmega32u2     atmega16u4    atmega32u4")
    print("     at90usb646    at90usb1286    atmega32a     atmega328p")
    print("     STM32F042     STM32F072      STM32F103     STM32F303")

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

    template_arch_path = os.path.join(template_root_path, arch)

    # Ask the user for their name
    user_name = input("\nYour Name: ")

    # generate keymap paths
    kb_path = os.path.join(os.getcwd(), "keyboards", keyboard)
    template_base_path = os.path.join(template_root_path, "base")

    # check directories
    if os.path.exists(kb_path):
        cli.log.error('Keyboard %s already exists!', keyboard)
        exit(1)

    # create user directory with default keymap files
    shutil.copytree(template_base_path, kb_path, symlinks=True)
    os.rename( \
        os.path.join(kb_path, "keyboard.c"), \
        os.path.join(kb_path, keyboard + ".c")
    )
    os.rename( \
        os.path.join(kb_path, "keyboard.h"), \
        os.path.join(kb_path, keyboard + ".h")
    )
    # copy architecture files
    shutil.copy(os.path.join(template_arch_path, "config.h"), kb_path)
    shutil.copy(os.path.join(template_arch_path, "readme.md"), kb_path)
    shutil.copy(os.path.join(template_arch_path, "rules.mk"), kb_path)
    if ( arch == "ps2avrgb" ):
        shutil.copy(os.path.join(template_arch_path, "usbconfig.h"), kb_path)
    if ( arch == "stm32" ):
        mcu = mcu.upper()

    # TODO: rewrite the rules.mk file with the requested MCU rule
    rules = Path(os.path.join(kb_path, "rules.mk"))
    file_contents = rules.read_text()
    file_contents = file_contents.replace("%MCU%", mcu)
    rules.write_text(file_contents)
    # edit_file(kb_path, "rules.mk")

    # rewrite the %YEAR%, %YOUR_NAME%, %KEYBOARD% and %PID% placeholders
    # TODO: write a reusable function for all this
    pid = hashlib.sha1(b'keyboard')

    # Define the files to rewrite
    config = Path(os.path.join(kb_path, "config.h"))
    info = Path(os.path.join(kb_path, "info.json"))
    readme = Path(os.path.join(kb_path, "readme.md"))
    source = Path(os.path.join(kb_path, keyboard + ".c"))
    header = Path(os.path.join(kb_path, keyboard + ".h"))
    keymap = Path(os.path.join(kb_path, "keymaps/default", "keymap.c"))
    keymap2 = Path(os.path.join(kb_path, "keymaps/default", "config.h"))
    keymap3 = Path(os.path.join(kb_path, "keymaps/default", "readme.md"))

    file_contents = config.read_text() \
        .replace("%YEAR%", str(year)) \
        .replace("%YOUR_NAME%", user_name) \
        .replace("%KEYBOARD%", keyboard)
        #.replace("%PID%", keyboard)
    config.write_text(file_contents)

    file_contents = info.read_text() \
        .replace("%YOUR_NAME%", user_name) \
        .replace("%KEYBOARD%", keyboard)
    info.write_text(file_contents)

    file_contents = readme.read_text() \
        .replace("%YOUR_NAME%", user_name) \
        .replace("%KEYBOARD%", keyboard)
    readme.write_text(file_contents)

    file_contents = source.read_text() \
        .replace("%YEAR%", str(year)) \
        .replace("%YOUR_NAME%", user_name) \
        .replace("%KEYBOARD%", keyboard)
    source.write_text(file_contents)

    file_contents = header.read_text() \
        .replace("%YOUR_NAME%", user_name) \
        .replace("%KEYBOARD%", keyboard)
    header.write_text(file_contents)

    file_contents = keymap.read_text() \
        .replace("%YEAR%", str(year)) \
        .replace("%YOUR_NAME%", user_name)
    keymap.write_text(file_contents)

    file_contents = keymap2.read_text() \
        .replace("%YEAR%", str(year)) \
        .replace("%YOUR_NAME%", user_name)
    keymap2.write_text(file_contents)

    file_contents = keymap3.read_text() \
        .replace("%KEYBOARD%", keyboard)
    keymap3.write_text(file_contents)

    # end message to user
    cli.log.info("%s keyboard directory created in: %s", keyboard, kb_path)
    cli.log.info("Compile a firmware with your new keymap by typing: \n" + "qmk compile -kb %s -km default", keyboard)
