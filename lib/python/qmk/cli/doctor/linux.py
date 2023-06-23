"""OS-specific functions for: Linux
"""
import platform
import shutil
from pathlib import Path

from milc import cli

from qmk.constants import QMK_FIRMWARE, BOOTLOADER_VIDS_PIDS
from .check import CheckStatus, release_info


def _is_wsl():
    return 'microsoft' in platform.uname().release.lower()


def _udev_rule(vid, pid=None, *args):
    """ Helper function that return udev rules
    """
    rule = ""
    if pid:
        rule = 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="%s", ATTRS{idProduct}=="%s", TAG+="uaccess"' % (
            vid,
            pid,
        )
    else:
        rule = 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="%s", TAG+="uaccess"' % vid
    if args:
        rule = ', '.join([rule, *args])
    return rule


def _generate_desired_rules(bootloader_vids_pids):
    rules = dict()
    for bl in bootloader_vids_pids.keys():
        rules[bl] = set()
        for vid_pid in bootloader_vids_pids[bl]:
            if bl == 'caterina' or bl == 'md-boot':
                rules[bl].add(_udev_rule(vid_pid[0], vid_pid[1], 'ENV{ID_MM_DEVICE_IGNORE}="1"'))
            else:
                rules[bl].add(_udev_rule(vid_pid[0], vid_pid[1]))
    return rules


def _deprecated_udev_rule(vid, pid=None):
    """ Helper function that return udev rules

    Note: these are no longer the recommended rules, this is just used to check for them
    """
    if pid:
        return 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="%s", ATTRS{idProduct}=="%s", MODE:="0666"' % (vid, pid)
    else:
        return 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="%s", MODE:="0666"' % vid


def check_udev_rules():
    """Make sure the udev rules look good.
    """
    rc = CheckStatus.OK
    udev_dirs = [
        Path("/usr/lib/udev/rules.d/"),
        Path("/usr/local/lib/udev/rules.d/"),
        Path("/run/udev/rules.d/"),
        Path("/etc/udev/rules.d/"),
    ]

    desired_rules = _generate_desired_rules(BOOTLOADER_VIDS_PIDS)

    # These rules are no longer recommended, only use them to check for their presence.
    deprecated_rules = {
        'atmel-dfu': {_deprecated_udev_rule("03eb", "2ff4"), _deprecated_udev_rule("03eb", "2ffb"), _deprecated_udev_rule("03eb", "2ff0")},
        'kiibohd': {_deprecated_udev_rule("1c11")},
        'stm32': {_deprecated_udev_rule("1eaf", "0003"), _deprecated_udev_rule("0483", "df11")},
        'bootloadhid': {_deprecated_udev_rule("16c0", "05df")},
        'caterina': {'ATTRS{idVendor}=="2a03", ENV{ID_MM_DEVICE_IGNORE}="1"', 'ATTRS{idVendor}=="2341", ENV{ID_MM_DEVICE_IGNORE}="1"'},
        'tmk': {_deprecated_udev_rule("feed")}
    }

    if any(udev_dir.exists() for udev_dir in udev_dirs):
        udev_rules = [rule_file for udev_dir in udev_dirs for rule_file in udev_dir.glob('*.rules')]
        current_rules = set()

        # Collect all rules from the config files
        for rule_file in udev_rules:
            try:
                for line in rule_file.read_text(encoding='utf-8').split('\n'):
                    line = line.strip()
                    if not line.startswith("#") and len(line):
                        current_rules.add(line)
            except PermissionError:
                cli.log.debug("Failed to read: %s", rule_file)

        # Check if the desired rules are among the currently present rules
        for bootloader, rules in desired_rules.items():
            if not rules.issubset(current_rules):
                deprecated_rule = deprecated_rules.get(bootloader)
                if deprecated_rule and deprecated_rule.issubset(current_rules):
                    cli.log.warning("{fg_yellow}Found old, deprecated udev rules for '%s' boards. The new rules on https://docs.qmk.fm/#/faq_build?id=linux-udev-rules offer better security with the same functionality.", bootloader)
                else:
                    # For caterina, check if ModemManager is running
                    if bootloader == "caterina" and check_modem_manager():
                        cli.log.warning("{fg_yellow}Detected ModemManager without the necessary udev rules. Please either disable it or set the appropriate udev rules if you are using a Pro Micro.")

                    rc = CheckStatus.WARNING
                    cli.log.warning("{fg_yellow}Missing or outdated udev rules for '%s' boards. Run 'sudo cp %s/util/udev/50-qmk.rules /etc/udev/rules.d/'.", bootloader, QMK_FIRMWARE)

    else:
        cli.log.warning("{fg_yellow}Can't find udev rules, skipping udev rule checking...")
        cli.log.debug("Checked directories: %s", ', '.join(str(udev_dir) for udev_dir in udev_dirs))

    return rc


def check_systemd():
    """Check if it's a systemd system
    """
    return bool(shutil.which("systemctl"))


def check_modem_manager():
    """Returns True if ModemManager is running.

    """
    if check_systemd():
        mm_check = cli.run(["systemctl", "--quiet", "is-active", "ModemManager.service"], timeout=10)
        if mm_check.returncode == 0:
            return True
    else:
        """(TODO): Add check for non-systemd systems
        """
    return False


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
