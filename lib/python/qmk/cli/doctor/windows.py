import platform

from milc import cli

from .check import CheckStatus, release_info


def os_test_windows():
    """Run the Windows specific tests.
    """
    win32_ver = platform.win32_ver()
    cli.log.info("Detected {fg_cyan}Windows %s (%s){fg_reset}.", win32_ver[0], win32_ver[1])

    # MSYS really does not like "/" files - resolve manually
    file = cli.run(['cygpath', '-m', '/etc/qmk-release']).stdout.strip()
    qmk_distro_version = release_info(file).get('VERSION', None)
    if qmk_distro_version:
        cli.log.info('QMK MSYS version: %s', qmk_distro_version)

    return CheckStatus.OK
