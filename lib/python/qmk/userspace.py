from os import environ
from pathlib import Path
import jsonschema

from milc import cli

from qmk.json_schema import validate, json_load


def qmk_userspace_paths():
    test_dirs = []

    # If we're already in a directory with a qmk.json and a keyboards or layouts directory, interpret it as userspace
    current_dir = Path(environ['ORIG_CWD'])
    while len(current_dir.parts) > 1:
        if (current_dir / 'qmk.json').is_file():
            test_dirs.append(current_dir)
        current_dir = current_dir.parent

    test_dirs.append(environ.get('QMK_USERSPACE'))
    test_dirs.append(cli.config.user.overlay_dir)
    test_dirs = list(dict.fromkeys([Path(x) for x in filter(lambda x: x is not None and Path(x).is_dir(), test_dirs)]))
    return test_dirs


def qmk_userspace_validate(path):
    try:
        if (path / 'qmk.json').is_file():
            qmkjson = json_load(path / 'qmk.json')
            validate(qmkjson, 'qmk.user_repo.v1')
            return True
    except jsonschema.ValidationError:
        pass
    return False


def detect_qmk_userspace():
    test_dirs = qmk_userspace_paths()
    for test_dir in test_dirs:
        if qmk_userspace_validate(test_dir):
            return test_dir
    return None


def userspace_doctor_checks(qmk_firmware, qmk_userspace, has_qmk_userspace):
    if qmk_firmware:
        cli.log.info(f'Detected QMK Firmware directory: {{fg_cyan}}{qmk_firmware}{{fg_reset}}')

    for path in qmk_userspace_paths():
        if qmk_userspace_validate(path):
            cli.log.info(f'Testing userspace candidate: {{fg_cyan}}{path}{{fg_reset}} -- {{fg_green}}Valid `qmk.json`{{fg_reset}}')
        else:
            cli.log.warn(f'Testing userspace candidate: {{fg_cyan}}{path}{{fg_reset}} -- {{fg_red}}Invalid `qmk.json`{{fg_reset}}')

    cli.log.info(f'Selected QMK Userspace directory: {{fg_cyan}}{qmk_userspace}{{fg_reset}}')
    cli.log.info(f'QMK Userspace is enabled: {{fg_cyan}}{has_qmk_userspace}{{fg_reset}}')
