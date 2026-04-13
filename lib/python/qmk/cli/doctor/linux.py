"""OS-specific functions for: Linux
"""
import platform
from pathlib import Path

from milc import cli

from qmk.constants import QMK_FIRMWARE
from .check import CheckStatus, release_info

QMK_UDEV_INSTALL_SCRIPT = 'util/install_udev.sh'


def _is_wsl():
    return 'microsoft' in platform.uname().release.lower()


def check_udev_rules():
    """Make sure the udev rules look good.
    """
    udev_dirs = [
        Path("/usr/lib/udev/rules.d/"),
        Path("/usr/local/lib/udev/rules.d/"),
        Path("/run/udev/rules.d/"),
        Path("/etc/udev/rules.d/"),
    ]

    if not any(udev_dir.exists() for udev_dir in udev_dirs):
        cli.log.warning("{fg_yellow}Can't find udev rules directories, skipping udev rule checking...")
        cli.log.debug("Checked directories: %s", ', '.join(str(udev_dir) for udev_dir in udev_dirs))
        return CheckStatus.WARNING

    # Collect all non-comment lines from QMK-related rules files
    current_rules = set()
    for udev_dir in udev_dirs:
        for rule_file in udev_dir.glob('*qmk*'):
            try:
                for line in rule_file.read_text(encoding='utf-8').split('\n'):
                    line = line.strip()
                    if not line.startswith("#") and len(line):
                        current_rules.add(line)
            except (PermissionError, FileNotFoundError):
                cli.log.debug("Failed to read: %s", rule_file)

    if not current_rules:
        cli.log.warning("{fg_yellow}Missing udev rules for QMK boards. Please run '%s' to install the rules", QMK_UDEV_INSTALL_SCRIPT)
        return CheckStatus.WARNING

    # Check for the qmk_udev ID_QMK marker
    if any('ID_QMK' in rule for rule in current_rules):
        return CheckStatus.OK

    # Legacy rules found (TAG+="uaccess" without ID_QMK)
    cli.log.warning("{fg_yellow}Found legacy udev rules. Please run '%s' to install the latest rules", QMK_UDEV_INSTALL_SCRIPT)
    return CheckStatus.WARNING


def os_test_linux():
    """Run the Linux specific tests.
    """
    info = release_info()
    release_id = info.get('PRETTY_NAME', info.get('ID', 'Unknown'))
    plat = 'WSL, ' if _is_wsl() else ''

    cli.log.info(f"Detected {{fg_cyan}}Linux ({plat}{release_id}){{fg_reset}}.")

    # Don't bother with udev on WSL, for now
    if _is_wsl():
        # https://github.com/microsoft/WSL/issues/4197
        if QMK_FIRMWARE.as_posix().startswith("/mnt"):
            cli.log.warning("I/O performance on /mnt may be extremely slow.")
            return CheckStatus.WARNING

    else:
        rc = check_udev_rules()
        if rc != CheckStatus.OK:
            return rc

    return CheckStatus.OK
