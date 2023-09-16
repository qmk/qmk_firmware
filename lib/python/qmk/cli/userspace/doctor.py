from milc import cli

from qmk.constants import QMK_FIRMWARE, QMK_USERSPACE, HAS_QMK_USERSPACE
from qmk.userspace import userspace_doctor_checks


@cli.subcommand('Checks userspace configuration.')
def userspace_doctor(cli):
    userspace_doctor_checks(QMK_FIRMWARE, QMK_USERSPACE, HAS_QMK_USERSPACE)
