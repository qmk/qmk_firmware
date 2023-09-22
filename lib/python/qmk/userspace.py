from os import environ
from pathlib import Path
import json
import jsonschema

from milc import cli

from qmk.json_schema import validate, json_load
from qmk.json_encoders import UserspaceJSONEncoder


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


def qmk_userspace_validate(path, validation_error_callback=None):
    try:
        if (path / 'qmk.json').is_file():
            userspace_defs = UserspaceDefs(path / 'qmk.json')
            if userspace_defs is not None:
                return True
    except jsonschema.ValidationError as err:
        if validation_error_callback is not None:
            validation_error_callback(err)
        pass
    return False


def detect_qmk_userspace():
    test_dirs = qmk_userspace_paths()
    for test_dir in test_dirs:
        if qmk_userspace_validate(test_dir):
            return test_dir
    return None


class UserspaceDefs:
    def __init__(self, userspace_json: Path):
        self.path = userspace_json
        json = json_load(userspace_json)
        validate(json, 'qmk.user_repo.v0')  # `qmk.json` must have a userspace_version at minimum

        # TODO: validate different versions of json when we're ready to deal with versioning
        # Start at highest version, then run down the list to v1
        try:
            validate(json, 'qmk.user_repo.v1')
            self.__load_v1(json)
        except jsonschema.ValidationError:
            raise  # v1 always needs to raise here -- higher versions shouldn't bother and should just `pass`

    def save(self):
        target_json = {
            "userspace_version": "1.0",  # Needs to match latest version
            "build_targets":
                self.build_targets  # Only other field needed in v1
        }

        try:
            # Ensure what we're writing validates against the latest version of the schema
            validate(target_json, 'qmk.user_repo.v1')
        except jsonschema.ValidationError as err:
            cli.log.error(f'Could not save userspace file: {err}')

        self.path.write_text(json.dumps(target_json, cls=UserspaceJSONEncoder, sort_keys=True))

    def __load_v1(self, json):
        self.build_targets = json['build_targets']
