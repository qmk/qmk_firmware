"""This script automates creating the files necessary for a new QMK keyboard.
"""
import os
import shutil

from milc import cli


@cli.argument('-kb', '--keyboard', help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.argument('-mcu', '--microcontroller', help='Specify the microcontroller used for the keyboard.')
@cli.subcommand('Creates a new keyboard project.')

def new_keyboard(cli):
    """Creates a new keyboard project.
    """

    # Root path for template files
    template_root_path = os.path.join(os.getcwd(), "quantum/template")

    # ask for user input if keyboard was not provided in the command line
    keyboard = input("\nKeyboard Name: ")

    print("\nSelect the microcontroller used:")
    print("     atmega16u2    atmega32u2     atmega16u4    atmega32u4")
    print("     at90usb646    at90usb1286    atmega32a     atmega328p")
    print("     STM32F042     STM32F072      STM32F103     STM32F303")

    mcus_avr = ["atmega16u2", "atmega32u2", "atmega16u4", "atmega32u4", \
        "at90usb646", "at90usb1286", "atmega328p"]
    mcus_ps2avrgb = ["atmega32a"]
    mcus_stm = ["STM32F042", "STM32F072", "STM32F103", "STM32F303"]

    mcu = input("\nMicrocontroller: ")

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
    print(kb_path + "/configurate.h")
    shutil.copy(os.path.join(template_arch_path, "config.h"), kb_path)
    shutil.copy(os.path.join(template_arch_path, "readme.md"), kb_path)
    shutil.copy(os.path.join(template_arch_path, "rules.mk"), kb_path)
    if ( arch == "ps2avrgb" ):
        shutil.copy(os.path.join(template_arch_path, "usbconfig.h"), kb_path)
    # TODO: rewrite the rules.mk file with the requested MCU rule

    # end message to user
    cli.log.info("%s keyboard directory created in: %s", keyboard, kb_path)
    cli.log.info("Compile a firmware with your new keymap by typing: \n" + "qmk compile -kb %s -km default", keyboard)
