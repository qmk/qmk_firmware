"""QMK Doctor

Check out the user's QMK environment and make sure it's ready to compile.
"""
import platform

from milc import cli
from milc.questions import yesno

from qmk import submodules
from qmk.constants import QMK_FIRMWARE, QMK_FIRMWARE_UPSTREAM, QMK_USERSPACE, HAS_QMK_USERSPACE
from .check import CheckStatus, check_binaries, check_binary_versions, check_submodules
from qmk.git import git_check_repo, git_get_branch, git_get_tag, git_get_last_log_entry, git_get_common_ancestor, git_is_dirty, git_get_remotes, git_check_deviation
from qmk.commands import in_virtualenv
from qmk.userspace import qmk_userspace_paths, qmk_userspace_validate, UserspaceValidationError


def distrib_tests():
    def _load_kvp_file(file):
        """Load a simple key=value file into a dictionary
        """
        vars = {}
        with open(file, 'r') as f:
            for line in f:
                if '=' in line:
                    key, value = line.split('=', 1)
                    vars[key.strip()] = value.strip()
        return vars

    def _parse_toolchain_release_file(file):
        """Parse the QMK toolchain release info file
        """
        try:
            vars = _load_kvp_file(file)
            return f'{vars.get("TOOLCHAIN_HOST", "unknown")}:{vars.get("TOOLCHAIN_TARGET", "unknown")}:{vars.get("COMMIT_HASH", "unknown")}'
        except Exception as e:
            cli.log.warning('Error reading QMK toolchain release info file: %s', e)
            return f'Unknown toolchain release info file: {file}'

    def _parse_flashutils_release_file(file):
        """Parse the QMK flashutils release info file
        """
        try:
            vars = _load_kvp_file(file)
            return f'{vars.get("FLASHUTILS_HOST", "unknown")}:{vars.get("COMMIT_HASH", "unknown")}'
        except Exception as e:
            cli.log.warning('Error reading QMK flashutils release info file: %s', e)
            return f'Unknown flashutils release info file: {file}'

    try:
        from qmk.cli import QMK_DISTRIB_DIR
        if (QMK_DISTRIB_DIR / 'etc').exists():
            cli.log.info('Found QMK tools distribution directory: {fg_cyan}%s', QMK_DISTRIB_DIR)

            toolchains = [_parse_toolchain_release_file(file) for file in (QMK_DISTRIB_DIR / 'etc').glob('toolchain_release_*')]
            if len(toolchains) > 0:
                cli.log.info('Found QMK toolchains: {fg_cyan}%s', ', '.join(toolchains))
            else:
                cli.log.warning('No QMK toolchains manifest found.')

            flashutils = [_parse_flashutils_release_file(file) for file in (QMK_DISTRIB_DIR / 'etc').glob('flashutils_release_*')]
            if len(flashutils) > 0:
                cli.log.info('Found QMK flashutils: {fg_cyan}%s', ', '.join(flashutils))
            else:
                cli.log.warning('No QMK flashutils manifest found.')
    except ImportError:
        cli.log.info('QMK tools distribution not found.')

    return CheckStatus.OK


def os_tests():
    """Determine our OS and run platform specific tests
    """
    platform_id = platform.platform().lower()

    if 'darwin' in platform_id or 'macos' in platform_id:
        from .macos import os_test_macos
        return os_test_macos()
    elif 'linux' in platform_id:
        from .linux import os_test_linux
        return os_test_linux()
    elif 'windows' in platform_id:
        from .windows import os_test_windows
        return os_test_windows()
    else:
        cli.log.warning('Unsupported OS detected: %s', platform_id)
        return CheckStatus.WARNING


def git_tests():
    """Run Git-related checks
    """
    status = CheckStatus.OK

    # Make sure our QMK home is a Git repo
    git_ok = git_check_repo()
    if not git_ok:
        cli.log.warning("{fg_yellow}QMK home does not appear to be a Git repository! (no .git folder)")
        status = CheckStatus.WARNING
    else:
        git_branch = git_get_branch()
        if git_branch:
            cli.log.info('Git branch: %s', git_branch)

            repo_version = git_get_tag()
            if repo_version:
                cli.log.info('Repo version: %s', repo_version)

            git_dirty = git_is_dirty()
            if git_dirty:
                cli.log.warning('{fg_yellow}Git has unstashed/uncommitted changes.')
                status = CheckStatus.WARNING
            git_remotes = git_get_remotes()
            if 'upstream' not in git_remotes.keys() or QMK_FIRMWARE_UPSTREAM not in git_remotes['upstream'].get('url', ''):
                cli.log.warning('{fg_yellow}The official repository does not seem to be configured as git remote "upstream".')
                status = CheckStatus.WARNING
            else:
                git_deviation = git_check_deviation(git_branch)
                if git_branch in ['master', 'develop'] and git_deviation:
                    cli.log.warning('{fg_yellow}The local "%s" branch contains commits not found in the upstream branch.', git_branch)
                    status = CheckStatus.WARNING
                for branch in [git_branch, 'upstream/master', 'upstream/develop']:
                    cli.log.info('- Latest %s: %s', branch, git_get_last_log_entry(branch))
                for branch in ['upstream/master', 'upstream/develop']:
                    cli.log.info('- Common ancestor with %s: %s', branch, git_get_common_ancestor(branch, 'HEAD'))

    return status


def output_submodule_status():
    """Prints out information related to the submodule status.
    """
    cli.log.info('Submodule status:')
    sub_status = submodules.status()
    for s in sub_status.keys():
        sub_info = sub_status[s]
        if 'name' in sub_info:
            sub_name = sub_info['name']
            sub_shorthash = sub_info['shorthash'] if 'shorthash' in sub_info else ''
            sub_describe = sub_info['describe'] if 'describe' in sub_info else ''
            sub_last_log_timestamp = sub_info['last_log_timestamp'] if 'last_log_timestamp' in sub_info else ''
            if sub_last_log_timestamp != '':
                cli.log.info(f'- {sub_name}: {sub_last_log_timestamp} -- {sub_describe} ({sub_shorthash})')
            else:
                cli.log.error(f'- {sub_name}: <<< missing or unknown >>>')


def userspace_tests(qmk_firmware):
    if qmk_firmware:
        cli.log.info(f'QMK home: {{fg_cyan}}{qmk_firmware}')

    for path in qmk_userspace_paths():
        try:
            qmk_userspace_validate(path)
            cli.log.info(f'Testing userspace candidate: {{fg_cyan}}{path}{{fg_reset}} -- {{fg_green}}Valid `qmk.json`')
        except FileNotFoundError:
            cli.log.warning(f'Testing userspace candidate: {{fg_cyan}}{path}{{fg_reset}} -- {{fg_red}}Missing `qmk.json`')
        except UserspaceValidationError as err:
            cli.log.warning(f'Testing userspace candidate: {{fg_cyan}}{path}{{fg_reset}} -- {{fg_red}}Invalid `qmk.json`')
            cli.log.warning(f' -- {{fg_cyan}}{path}/qmk.json{{fg_reset}} validation error: {err}')

    if QMK_USERSPACE is not None:
        cli.log.info(f'QMK userspace: {{fg_cyan}}{QMK_USERSPACE}')
    cli.log.info(f'Userspace enabled: {{fg_cyan}}{HAS_QMK_USERSPACE}')


@cli.argument('-y', '--yes', action='store_true', arg_only=True, help='Answer yes to all questions.')
@cli.argument('-n', '--no', action='store_true', arg_only=True, help='Answer no to all questions.')
@cli.subcommand('Basic QMK environment checks')
def doctor(cli):
    """Basic QMK environment checks.

    This is currently very simple, it just checks that all the expected binaries are on your system.

    TODO(unclaimed):
        * [ ] Compile a trivial program with each compiler
    """
    cli.log.info('QMK Doctor is checking your environment.')
    cli.log.info('Python version: %s', platform.python_version())
    cli.log.info('CLI version: %s', cli.version)
    cli.log.info('QMK home: {fg_cyan}%s', QMK_FIRMWARE)

    status = os_status = os_tests()
    distrib_tests()

    userspace_tests(None)

    git_status = git_tests()

    if git_status == CheckStatus.ERROR or (os_status == CheckStatus.OK and git_status == CheckStatus.WARNING):
        status = git_status

    if in_virtualenv():
        cli.log.info('CLI installed in virtualenv.')

    # Make sure the basic CLI tools we need are available and can be executed.
    bin_ok = check_binaries()
    if bin_ok == CheckStatus.OK:
        cli.log.info('All dependencies are installed.')
    elif bin_ok == CheckStatus.WARNING:
        cli.log.warning('Issues encountered while checking dependencies.')
    else:
        status = CheckStatus.ERROR

    # Make sure the tools are at the correct version
    ver_ok = check_binary_versions()
    if CheckStatus.ERROR in ver_ok:
        status = CheckStatus.ERROR
    elif CheckStatus.WARNING in ver_ok and status == CheckStatus.OK:
        status = CheckStatus.WARNING

    # Check out the QMK submodules
    sub_ok = check_submodules()
    if sub_ok == CheckStatus.OK:
        cli.log.info('Submodules are up to date.')
    else:
        if git_check_repo() and yesno('Would you like to clone the submodules?', default=True):
            submodules.update()
            sub_ok = check_submodules()

        if sub_ok == CheckStatus.ERROR:
            status = CheckStatus.ERROR
        elif sub_ok == CheckStatus.WARNING and status == CheckStatus.OK:
            status = CheckStatus.WARNING

    output_submodule_status()

    # Report a summary of our findings to the user
    if status == CheckStatus.OK:
        cli.log.info('{fg_green}QMK is ready to go')
        return 0
    elif status == CheckStatus.WARNING:
        cli.log.info('{fg_yellow}QMK is ready to go, but minor problems were found')
        return 1
    else:
        cli.log.info('{fg_red}Major problems detected, please fix these problems before proceeding.{fg_reset}')
        cli.log.info('{fg_blue}If you\'re missing dependencies, try following the instructions on: https://docs.qmk.fm/newbs_getting_started{fg_reset}')
        cli.log.info('{fg_blue}Additionally, check out the FAQ (https://docs.qmk.fm/#/faq_build) or join the QMK Discord (https://discord.gg/qmk) for help.{fg_reset}')
        return 2
