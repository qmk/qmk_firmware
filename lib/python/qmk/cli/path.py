"""QMK Python Hello World

This is an example QMK CLI script.
"""
from milc import cli
from qmk.constants import QMK_FIRMWARE


@cli.subcommand('Detected path to QMK Firmware.', hidden=True)
def path(cli):
    print(QMK_FIRMWARE)
    return
