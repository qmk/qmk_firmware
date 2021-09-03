import platform

from milc import cli

from .check import CheckStatus


def os_test_macos():
    """Run the Mac specific tests.
    """
    cli.log.info("Detected {fg_cyan}macOS %s{fg_reset}.", platform.mac_ver()[0])

    return CheckStatus.OK
