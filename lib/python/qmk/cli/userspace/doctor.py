# Copyright 2023 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later
from milc import cli

from qmk.constants import QMK_FIRMWARE, HAS_QMK_USERSPACE
from qmk.cli.doctor.main import userspace_tests


@cli.subcommand('Checks userspace configuration.')
def userspace_doctor(cli):
    userspace_tests(QMK_FIRMWARE)

    return 0 if HAS_QMK_USERSPACE else 1
