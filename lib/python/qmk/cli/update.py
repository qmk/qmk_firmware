"""Update QMK CLI and  qmk_firmware on your computer.
"""
import sys
from pathlib import Path
from importlib.util import find_spec

from milc import cli
from qmk.constants import QMK_FIRMWARE


def os_check():
    """Check the OS
    """
    platform = cli.platform.lower()
    if 'darwin' in platform or 'macos' in platform:
        platform = 'macos'
    elif 'linux' in platform:
        platform = 'linux'
    elif 'windows' in platform:
        platform = 'windows'
    else:
        cli.log.error('Unsupported OS')
        sys.exit(1)

    # CLI installation mode for Linux (global/user)
    if platform == 'linux':
        install_location = Path(find_spec('qmk').origin)
        if Path('/usr') in install_location.parents and not cli.args.system:
            cli.log.error('The "qmk" package CLI seems to be installed system-wide.\nCheck if you can update it with your package manager or force its update with the "--system" argument.')
            sys.exit(2)

    return platform


def qmk_repo_check():
    # Check if QMK dir is a git repo
    if not (QMK_FIRMWARE / '.git').exists():
        cli.log.error(f'{qmk_dir} is not a "qmk_firmware clone or not a git repository.')
        sys.exit(3)

    # Check if the official repo is configured as a git remote 'upstream'
    output = cli.run(['git', 'remote', 'get-url', 'upstream'])
    if output.returncode != 0 or 'qmk/qmk_firmware' not in output.stdout:
        cli.log.error('The official repository does not seem to be configured as git remote "upstream".')
        sys.exit(4)

    # Check if master branch is checked out
    active_branch = cli.run(['git', 'branch', '--show-current']).stdout.strip()
    if active_branch not in ['master', 'develop']:
        cli.log.error('Updating is only supported for the "master" and "develop" branches.\nPlease check out one of them.')
        sys.exit(5)

    return active_branch


def in_virtualenv():
    """Check if running inside a virtualenv.
    Based on https://stackoverflow.com/a/1883251
    """
    active_prefix = getattr(sys, "base_prefix", None) or getattr(sys, "real_prefix", None) or sys.prefix
    return active_prefix != sys.prefix


@cli.argument('--system', arg_only=True, action='store_true', help='Update CLI even if installed system-wide')
@cli.subcommand('Update the QMK CLI and qmk_firmware repository.')
def update(cli):
    """Check the user's QMK environment and update it, if possible
    """
    # Pre-flight checks
    # OS
    platform = os_check()
    # QMK repo
    active_branch = qmk_repo_check()

    # Update the CLI
    cli.log.info('Updating the CLI...')
    if in_virtualenv():
        cli.run([sys.executable, '-m', 'pip', 'install', '--upgrade', 'qmk'])
    elif platform == 'macos':
        cli.run(['brew', 'upgrade', 'qmk/qmk/qmk'])
    elif platform == 'linux':
        cli.run([sys.executable, '-m', 'pip', 'install', '--upgrade', '--system' if cli.args.system else '--user', 'qmk'])
    elif platform == 'windows':
        cli.run([sys.executable, '-m', 'pip', 'install', '--upgrade', 'qmk'])

    # Update the branch
    cli.log.info('Updating the repository...')
    cli.run(['git', 'fetch', 'upstream', active_branch])
    cli.run(['git', 'merge', 'FETCH_HEAD'])
    # Sync submodules
    cli.log.info('Syncronizing the submodules...')
    cli.run(['git', 'submodule', 'sync', '--recursive'])
    cli.run(['git', 'submodule', 'update', '--init', '--recursive', '--progress'])
