"""Update dependencies/environment/EVERYTHING???
"""
import argparse
from enum import Enum

from milc import cli
from milc.questions import yesno

from qmk import submodules
from qmk.commands import get_git_branch, get_git_remotes, git_is_dirty, run
from qmk.constants import QMK_FIRMWARE_URL


class WorkflowType(Enum):
    UNKNOWN = 0
    FORK = 1
    ORIGIN = 2


def _get_workflow_type():
    remotes = get_git_remotes()
    if (QMK_FIRMWARE_URL in remotes['upstream']["url"]) and ("/qmk_firmware.git" in remotes['origin']["url"]):
        return WorkflowType.FORK

    if (QMK_FIRMWARE_URL in remotes['origin']["url"]) and len(remotes) == 1:
        return WorkflowType.ORIGIN

    return WorkflowType.UNKNOWN


def update_repo():
    branch = get_git_branch()
    workflow = _get_workflow_type()

    cmds = None

    if workflow == WorkflowType.FORK:
        if branch == 'master':
            cmds = ["git fetch upstream", "git pull upstream master", "git push origin master"]
        else:
            cmds = ["git fetch upstream", "git rebase --autostash upstream/master"]
    elif workflow == WorkflowType.ORIGIN:
        cmds = ["git fetch origin", "git pull --rebase --autostash"]

    if not cmds:
        cli.log.warning("Update scenario not supported!")
        return False

    for cmd in cmds:
        run(cmd.split())


@cli.argument('-f', '--force', action='store_true', help='Flag to overwrite current info.json')
@cli.argument('-r', '--update-repo', action=argparse.BooleanOptionalAction, default=False, help='update repo')
@cli.argument('-s', '--update-submodules', action=argparse.BooleanOptionalAction, default=True, help='update submodules')
@cli.subcommand('Update everything QMK.')
def up(cli):
    if git_is_dirty() and not cli.config.up.force:
        if not yesno('Dirty state detected! It is recommended that you work from a clean state. Do you want to continue anyway?', default=False):
            return False

    if cli.config.up.update_repo:
        cli.log.info('Making sure repo is up to date')
        update_repo()

    if cli.config.up.update_submodules:
        cli.log.info('Making sure latest submodules are downloaded')
        # 'git submodule foreach git checkout .'?
        submodules.update()
