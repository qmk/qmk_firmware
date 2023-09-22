from milc import cli

from qmk.constants import QMK_FIRMWARE
from qmk.cli.doctor.main import userspace_tests


@cli.subcommand('Checks userspace configuration.')
def userspace_doctor(cli):
    userspace_tests(QMK_FIRMWARE)
