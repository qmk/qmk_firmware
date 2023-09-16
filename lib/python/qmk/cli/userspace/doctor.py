from milc import cli

from qmk.constants import QMK_FIRMWARE, QMK_USERSPACE, HAS_QMK_USERSPACE
from qmk.userspace import qmk_userspace_paths, qmk_userspace_validate

@cli.subcommand('Checks userspace configuration.')
def userspace_doctor(cli):
    cli.log.info('Checking userspace configuration...')
    cli.log.info(f'Detected QMK Firmware directory: {{fg_cyan}}{QMK_FIRMWARE}{{fg_reset}}')
    cli.log.info(f'Detected QMK Userspace directory: {{fg_cyan}}{QMK_USERSPACE}{{fg_reset}}')
    cli.log.info(f'QMK Userspace is enabled: {{fg_cyan}}{HAS_QMK_USERSPACE}{{fg_reset}}')

    for path in qmk_userspace_paths():
        if qmk_userspace_validate(path):
            cli.log.info(f'Testing {{fg_cyan}}{path}{{fg_reset}} -- {{fg_green}}Valid `qmk.json`{{fg_reset}}')
        else:
            cli.log.warn(f'Testing {{fg_cyan}}{path}{{fg_reset}} -- {{fg_red}}Invalid `qmk.json`{{fg_reset}}')
