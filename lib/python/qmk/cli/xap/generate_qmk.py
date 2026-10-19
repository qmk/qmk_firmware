"""This script generates the XAP protocol generated sources to be compiled into QMK firmware.
"""
from milc import cli

from qmk.path import normpath
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.xap.common import render_xap_output, merge_xap_defs
from qmk.xap.gen_firmware.blob_generator import generate_blob


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

    defs = merge_xap_defs(cli.args.keyboard, cli.args.keymap)
    with open(cli.args.output, 'w', encoding='utf-8') as out_file:
        r = render_xap_output('firmware', 'xap_generated.inl.j2', defs, keyboard=cli.args.keyboard, keymap=cli.args.keymap)
        while r.find('\n\n\n') != -1:
            r = r.replace('\n\n\n', '\n\n')
        out_file.write(r)


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

    defs = merge_xap_defs(cli.args.keyboard, cli.args.keymap)
    with open(cli.args.output, 'w', encoding='utf-8') as out_file:
        r = render_xap_output('firmware', 'xap_generated.h.j2', defs, keyboard=cli.args.keyboard, keymap=cli.args.keymap)
        while r.find('\n\n\n') != -1:
            r = r.replace('\n\n\n', '\n\n')
        out_file.write(r)


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
