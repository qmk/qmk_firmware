"""Status
"""
from milc import cli

from qmk import submodules
from qmk.commands import get_git_version


def _has_dirty_submodules():
    for submodule in submodules.status().values():
        if not submodule['status']:
            return True
    return False


@cli.argument('--submodule-dirty', action='store_true', help='asdf')
@cli.subcommand('QMK status.')
def status(cli):
    info = {
        'version': get_git_version(),
        'sub_dirty': _has_dirty_submodules(),
    }

    if cli.config.status.submodule_dirty:
        return not info['sub_dirty']

    for key, value in info.items():
        cli.log.info('%s: %s', key, value)
