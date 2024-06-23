from milc import cli
from qmk.constants import QMK_USERSPACE


@cli.subcommand('Detected path to QMK Userspace.', hidden=True)
def userspace_path(cli):
    print(QMK_USERSPACE)
    return
