"""This script generates the XAP protocol generated sources to be compiled into QMK firmware.
"""
from milc import cli

from qmk.path import normpath
from qmk.xap.gen_firmware.inline_generator import generate_inline
from qmk.xap.gen_firmware.header_generator import generate_header


@cli.argument('-o', '--output', type=normpath, help='File to write to')
@cli.subcommand('Generates the XAP protocol include.', hidden=False if cli.config.user.developer else True)
def xap_generate_qmk_inc(cli):
    """Generates the XAP protocol inline codegen file, generated during normal build.
    """
    generate_inline(cli.args.output)


@cli.argument('-o', '--output', type=normpath, help='File to write to')
@cli.argument('-kb', '--keyboard', help='Name of the keyboard')
@cli.subcommand('Generates the XAP protocol include.', hidden=False if cli.config.user.developer else True)
def xap_generate_qmk_h(cli):
    """Generates the XAP protocol header file, generated during normal build.
    """
    generate_header(cli.args.output, cli.args.keyboard)
