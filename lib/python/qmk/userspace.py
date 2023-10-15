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


def qmk_userspace_validate(path):
    if (path / 'qmk.json').is_file():
        UserspaceDefs(path / 'qmk.json')
        return
    raise FileNotFoundError('No qmk.json file found.')


def detect_qmk_userspace():
    test_dirs = qmk_userspace_paths()
    for test_dir in test_dirs:
        try:
            qmk_userspace_validate(test_dir)
            return test_dir
        except FileNotFoundError:
            continue
        except UserspaceValidationError:
            continue
    return None


class UserspaceDefs:
    def __init__(self, userspace_json: Path):
        self.path = userspace_json
        self.build_targets = []
        json = json_load(userspace_json)

        exception = UserspaceValidationError()
        success = False

        try:
            validate(json, 'qmk.user_repo.v0')  # `qmk.json` must have a userspace_version at minimum
        except jsonschema.ValidationError as err:
            exception.add('qmk.user_repo.v0', err)
            raise exception

        # Iterate through each version of the schema, starting with the latest and decreasing to v1
        try:
            validate(json, 'qmk.user_repo.v1')
            self.__load_v1(json)
            success = True
        except jsonschema.ValidationError as err:
            exception.add('qmk.user_repo.v1', err)

        if not success:
            raise exception

    def save(self):
        target_json = {
            "userspace_version": "1.0",  # Needs to match latest version
            "build_targets": []
        }

        for e in self.build_targets:
            target_json['build_targets'].append([e['keyboard'], e['keymap']])

        try:
            # Ensure what we're writing validates against the latest version of the schema
            validate(target_json, 'qmk.user_repo.v1')
        except jsonschema.ValidationError as err:
            cli.log.error(f'Could not save userspace file: {err}')
            return False

        self.path.write_text(json.dumps(target_json, cls=UserspaceJSONEncoder, sort_keys=True))
        return True

    def add_target(self, keyboard, keymap):
        e = {"keyboard": keyboard, "keymap": keymap}
        if e not in self.build_targets:
            self.build_targets.append(e)

    def remove_target(self, keyboard, keymap):
        e = {"keyboard": keyboard, "keymap": keymap}
        if e in self.build_targets:
            self.build_targets.remove(e)

    def __load_v1(self, json):
        for e in json['build_targets']:
            if len(e) == 2:
                self.add_target(e[0], e[1])


class UserspaceValidationError(Exception):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.__exceptions = []

    def __str__(self):
        return self.message

    @property
    def exceptions(self):
        return self.__exceptions

    def add(self, schema, exception):
        self.__exceptions.append((schema, exception))
        errorlist = "\n\n".join([f"{schema}: {exception}" for schema, exception in self.__exceptions])
        self.message = f'Could not validate against any version of the userspace schema. Errors:\n\n{errorlist}'
