"""QMK Doctor

Check out the user's QMK environment and make sure it's ready to compile.
"""
import platform

from milc import cli
from qmk.constants import QMK_FIRMWARE
from qmk.os_helpers import CheckStatus, check_userspace, repo_test, tooling_test


def os_tests():
    """Determine our OS and run platform specific tests
    """
    platform_id = platform.platform().lower()

    if 'darwin' in platform_id or 'macos' in platform_id:
        return os_test_macos()
    elif 'linux' in platform_id:
        return os_test_linux()
    elif 'windows' in platform_id:
        return os_test_windows()
    else:
        cli.log.warning('Unsupported OS detected: %s', platform_id)
        return CheckStatus.WARNING


def os_test_linux():
    """Run the Linux specific tests.
    """
    cli.log.info("Detected {fg_cyan}Linux.")
    from qmk.os_helpers.linux import check_udev_rules

    return check_udev_rules()


def os_test_macos():
    """Run the Mac specific tests.
    """
    cli.log.info("Detected {fg_cyan}macOS.")

    return CheckStatus.OK


def os_test_windows():
    """Run the Windows specific tests.
    """
    cli.log.info("Detected {fg_cyan}Windows.")

    return CheckStatus.OK


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

    cli.log.info('QMK home: {fg_cyan}%s', QMK_FIRMWARE)

    status = CheckStatus.OK

    # List of checks we need to run
    checks = (os_tests, check_userspace, repo_test, tooling_test)

    # Run the checks and update 'status' based on their output
    for check in checks:
        check_status = check()
        if check_status == CheckStatus.ERROR:
            status = CheckStatus.ERROR
        elif check_status == CheckStatus.WARNING:
            status = CheckStatus.WARNING

    # Report a summary of our findings to the user
    if status == CheckStatus.OK:
        cli.log.info('{fg_green}QMK is ready to go')
        return 0
    elif status == CheckStatus.WARNING:
        cli.log.info('{fg_yellow}QMK is ready to go, but minor problems were found')
        return 1
    else:
        cli.log.info('{fg_red}Major problems detected, please fix these problems before proceeding.')
        cli.log.info('{fg_blue}Check out the FAQ (https://docs.qmk.fm/#/faq_build) or join the QMK Discord (https://discord.gg/Uq7gcHh) for help.')
        return 2
