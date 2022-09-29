"""This script generates the XAP protocol generated sources to be compiled into QMK firmware.
"""
from milc import cli

from qmk.path import normpath
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.xap.gen_firmware.blob_generator import generate_blob
from qmk.xap.gen_firmware.inline_generator import generate_inline
from qmk.xap.gen_firmware.header_generator import generate_header


@cli.argument('-o', '--output', type=normpath, help='File to write to')
@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='Name of the keyboard')
@cli.argument('-km', '--keymap', help='The keymap\'s name')
@cli.subcommand('Generates the XAP protocol include.', hidden=False if cli.config.user.developer else True)
def xap_generate_qmk_inc(cli):
    """Generates the XAP protocol inline codegen file, generated during normal build.
    """
    # Determine our keyboard/keymap
    if not cli.args.keyboard:
        cli.log.error('Missing parameter: --keyboard')
        cli.subcommands['xap-generate-qmk-inc'].print_help()
        return False
    if not cli.args.keymap:
        cli.log.error('Missing parameter: --keymap')
        cli.subcommands['xap-generate-qmk-inc'].print_help()
        return False

    generate_inline(cli.args.output, cli.args.keyboard, cli.args.keymap)


@cli.argument('-o', '--output', type=normpath, help='File to write to')
@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='Name of the keyboard')
@cli.argument('-km', '--keymap', help='The keymap\'s name')
@cli.subcommand('Generates the XAP protocol include.', hidden=False if cli.config.user.developer else True)
def xap_generate_qmk_h(cli):
    """Generates the XAP protocol header file, generated during normal build.
    """
    # Determine our keyboard/keymap
    if not cli.args.keyboard:
        cli.log.error('Missing parameter: --keyboard')
        cli.subcommands['xap-generate-qmk-h'].print_help()
        return False
    if not cli.args.keymap:
        cli.log.error('Missing parameter: --keymap')
        cli.subcommands['xap-generate-qmk-h'].print_help()
        return False

    generate_header(cli.args.output, cli.args.keyboard, cli.args.keymap)


@cli.argument('-o', '--output', type=normpath, help='File to write to')
@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='Name of the keyboard')
@cli.argument('-km', '--keymap', help='The keymap\'s name')
@cli.subcommand('Generates the XAP config payload include.', hidden=False if cli.config.user.developer else True)
def xap_generate_qmk_blob_h(cli):
    """Generates the XAP config payload header file, generated during normal build.
    """
    # Determine our keyboard/keymap
    if not cli.args.keyboard:
        cli.log.error('Missing parameter: --keyboard')
        cli.subcommands['xap-generate-qmk-blob-h'].print_help()
        return False
    if not cli.args.keymap:
        cli.log.error('Missing parameter: --keymap')
        cli.subcommands['xap-generate-qmk-blob-h'].print_help()
        return False

    generate_blob(cli.args.output, cli.args.keyboard, cli.args.keymap)
