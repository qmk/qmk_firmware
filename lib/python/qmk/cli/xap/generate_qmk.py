"""This script generates the XAP protocol generated sources to be compiled into QMK firmware.
"""
from milc import cli

from qmk.path import normpath
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.xap.gen_firmware.info_generator import generate_info
from qmk.xap.gen_firmware.inline_generator import generate_inline
from qmk.xap.gen_firmware.header_generator import generate_header


@cli.argument('-o', '--output', type=normpath, help='File to write to')
@cli.subcommand('Generates the XAP protocol include.', hidden=False if cli.config.user.developer else True)
def xap_generate_qmk_inc(cli):
    """Generates the XAP protocol inline codegen file, generated during normal build.
    """
    generate_inline(cli.args.output)


@cli.argument('-o', '--output', type=normpath, help='File to write to')
@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='Name of the keyboard')
@cli.subcommand('Generates the XAP protocol include.', hidden=False if cli.config.user.developer else True)
def xap_generate_qmk_h(cli):
    """Generates the XAP protocol header file, generated during normal build.
    """
    # Determine our keyboard
    if not cli.args.keyboard:
        cli.log.error('Missing parameter: --keyboard')
        cli.subcommands['xap-generate-qmk-h'].print_help()
        return False
    generate_header(cli.args.output, cli.args.keyboard)


@cli.argument('-o', '--output', type=normpath, help='File to write to')
@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='Name of the keyboard')
@cli.argument('-km', '--keymap', help='The keymap\'s name')
@cli.subcommand('Generates the XAP info.json payload include.', hidden=False if cli.config.user.developer else True)
def xap_generate_info_h(cli):
    """Generates the XAP info.json payload header file, generated during normal build.
    """
    # Determine our keyboard/keymap
    if not cli.args.keyboard:
        cli.log.error('Missing parameter: --keyboard')
        cli.subcommands['xap-generate-info-h'].print_help()
        return False
    if not cli.args.keymap:
        cli.log.error('Missing parameter: --keymap')
        cli.subcommands['xap-generate-info-h'].print_help()
        return False

    generate_info(cli.args.output, cli.args.keyboard, cli.args.keymap)
