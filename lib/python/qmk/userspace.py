# Copyright 2023 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later
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
    if environ.get('ORIG_CWD') is not None:
        current_dir = Path(environ['ORIG_CWD'])
        while len(current_dir.parts) > 1:
            if (current_dir / 'qmk.json').is_file():
                test_dirs.append(current_dir)
            current_dir = current_dir.parent

    # If we have a QMK_USERSPACE environment variable, use that
    if environ.get('QMK_USERSPACE') is not None:
        current_dir = Path(environ['QMK_USERSPACE'])
        if current_dir.is_dir():
            test_dirs.append(current_dir)

    # If someone has configured a directory, use that
    if cli.config.user.overlay_dir is not None:
        current_dir = Path(cli.config.user.overlay_dir)
        if current_dir.is_dir():
            test_dirs.append(current_dir)

    return test_dirs


def qmk_userspace_validate(path):
    # Construct a UserspaceDefs object to ensure it validates correctly
    if (path / 'qmk.json').is_file():
        UserspaceDefs(path / 'qmk.json')
        return

    # No qmk.json file found
    raise FileNotFoundError('No qmk.json file found.')


def detect_qmk_userspace():
    # Iterate through all the detected userspace paths and return the first one that validates correctly
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
            if isinstance(e, dict):
                target_json['build_targets'].append([e['keyboard'], e['keymap']])
            elif isinstance(e, Path):
                target_json['build_targets'].append(str(e.relative_to(self.path.parent)))

        try:
            # Ensure what we're writing validates against the latest version of the schema
            validate(target_json, 'qmk.user_repo.v1')
        except jsonschema.ValidationError as err:
            cli.log.error(f'Could not save userspace file: {err}')
            return False

        # Only actually write out data if it changed
        old_data = json.dumps(json.loads(self.path.read_text()), cls=UserspaceJSONEncoder, sort_keys=True)
        new_data = json.dumps(target_json, cls=UserspaceJSONEncoder, sort_keys=True)
        if old_data != new_data:
            self.path.write_text(new_data)
            cli.log.info(f'Saved userspace file to {self.path}.')
        return True

    def add_target(self, keyboard=None, keymap=None, json_path=None, do_print=True):
        if json_path is not None:
            # Assume we're adding a json filename/path
            json_path = Path(json_path)
            if json_path not in self.build_targets:
                self.build_targets.append(json_path)
                if do_print:
                    cli.log.info(f'Added {json_path} to userspace build targets.')
            else:
                cli.log.info(f'{json_path} is already a userspace build target.')

        elif keyboard is not None and keymap is not None:
            # Both keyboard/keymap specified
            e = {"keyboard": keyboard, "keymap": keymap}
            if e not in self.build_targets:
                self.build_targets.append(e)
                if do_print:
                    cli.log.info(f'Added {keyboard}:{keymap} to userspace build targets.')
            else:
                if do_print:
                    cli.log.info(f'{keyboard}:{keymap} is already a userspace build target.')

    def remove_target(self, keyboard=None, keymap=None, json_path=None, do_print=True):
        if json_path is not None:
            # Assume we're removing a json filename/path
            json_path = Path(json_path)
            if json_path in self.build_targets:
                self.build_targets.remove(json_path)
                if do_print:
                    cli.log.info(f'Removed {json_path} from userspace build targets.')
            else:
                cli.log.info(f'{json_path} is not a userspace build target.')

        elif keyboard is not None and keymap is not None:
            # Both keyboard/keymap specified
            e = {"keyboard": keyboard, "keymap": keymap}
            if e in self.build_targets:
                self.build_targets.remove(e)
                if do_print:
                    cli.log.info(f'Removed {keyboard}:{keymap} from userspace build targets.')
            else:
                if do_print:
                    cli.log.info(f'{keyboard}:{keymap} is not a userspace build target.')

    def __load_v1(self, json):
        for e in json['build_targets']:
            if isinstance(e, list) and len(e) == 2:
                self.add_target(keyboard=e[0], keymap=e[1], do_print=False)
            if isinstance(e, str):
                p = self.path.parent / e
                if p.exists() and p.suffix == '.json':
                    self.add_target(json_path=p, do_print=False)


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
