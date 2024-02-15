# Copyright 2023 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later
import json
import shutil
from typing import List, Union
from pathlib import Path
from dotty_dict import dotty, Dotty
from milc import cli
from qmk.constants import QMK_FIRMWARE, INTERMEDIATE_OUTPUT_PREFIX, HAS_QMK_USERSPACE, QMK_USERSPACE
from qmk.commands import find_make, get_make_parallel_args, parse_configurator_json
from qmk.keyboard import keyboard_folder
from qmk.info import keymap_json
from qmk.keymap import locate_keymap
from qmk.path import is_under_qmk_firmware, is_under_qmk_userspace


class BuildTarget:
    def __init__(self, keyboard: str, keymap: str, json: Union[dict, Dotty] = None):
        self._keyboard = keyboard_folder(keyboard)
        self._keyboard_safe = self._keyboard.replace('/', '_')
        self._keymap = keymap
        self._parallel = 1
        self._clean = False
        self._compiledb = False
        self._target = f'{self._keyboard_safe}_{self.keymap}'
        self._intermediate_output = Path(f'{INTERMEDIATE_OUTPUT_PREFIX}{self._target}')
        self._generated_files_path = self._intermediate_output / 'src'
        self._json = json.to_dict() if isinstance(json, Dotty) else json

    def __str__(self):
        return f'{self.keyboard}:{self.keymap}'

    def __repr__(self):
        return f'BuildTarget(keyboard={self.keyboard}, keymap={self.keymap})'

    def __eq__(self, __value: object) -> bool:
        if not isinstance(__value, BuildTarget):
            return False
        return self.__repr__() == __value.__repr__()

    def __ne__(self, __value: object) -> bool:
        return not self.__eq__(__value)

    def __hash__(self) -> int:
        return self.__repr__().__hash__()

    def configure(self, parallel: int = None, clean: bool = None, compiledb: bool = None) -> None:
        if parallel is not None:
            self._parallel = parallel
        if clean is not None:
            self._clean = clean
        if compiledb is not None:
            self._compiledb = compiledb

    @property
    def keyboard(self) -> str:
        return self._keyboard

    @property
    def keymap(self) -> str:
        return self._keymap

    @property
    def json(self) -> dict:
        if not self._json:
            self._load_json()
        if not self._json:
            return {}
        return self._json

    @property
    def dotty(self) -> Dotty:
        return dotty(self.json)

    def _common_make_args(self, dry_run: bool = False, build_target: str = None):
        compile_args = [
            find_make(),
            *get_make_parallel_args(self._parallel),
            '-r',
            '-R',
            '-f',
            'builddefs/build_keyboard.mk',
        ]

        if not cli.config.general.verbose:
            compile_args.append('-s')

        verbose = 'true' if cli.config.general.verbose else 'false'
        color = 'true' if cli.config.general.color else 'false'

        if dry_run:
            compile_args.append('-n')

        if build_target:
            compile_args.append(build_target)

        compile_args.extend([
            f'KEYBOARD={self.keyboard}',
            f'KEYMAP={self.keymap}',
            f'KEYBOARD_FILESAFE={self._keyboard_safe}',
            f'TARGET={self._target}',
            f'INTERMEDIATE_OUTPUT={self._intermediate_output}',
            f'VERBOSE={verbose}',
            f'COLOR={color}',
            'SILENT=false',
            'QMK_BIN="qmk"',
        ])

        return compile_args

    def prepare_build(self, build_target: str = None, dry_run: bool = False, **env_vars) -> None:
        raise NotImplementedError("prepare_build() not implemented in base class")

    def compile_command(self, build_target: str = None, dry_run: bool = False, **env_vars) -> List[str]:
        raise NotImplementedError("compile_command() not implemented in base class")

    def generate_compilation_database(self, build_target: str = None, skip_clean: bool = False, **env_vars) -> None:
        self.prepare_build(build_target=build_target, **env_vars)
        command = self.compile_command(build_target=build_target, dry_run=True, **env_vars)
        from qmk.cli.generate.compilation_database import write_compilation_database  # Lazy load due to circular references
        output_path = QMK_FIRMWARE / 'compile_commands.json'
        write_compilation_database(command=command, output_path=output_path, skip_clean=skip_clean, **env_vars)
        if output_path.exists() and HAS_QMK_USERSPACE:
            shutil.copy(str(output_path), str(QMK_USERSPACE / 'compile_commands.json'))

    def compile(self, build_target: str = None, dry_run: bool = False, **env_vars) -> None:
        if self._clean or self._compiledb:
            command = [find_make(), "clean"]
            if dry_run:
                command.append('-n')
            cli.log.info('Cleaning with {fg_cyan}%s', ' '.join(command))
            cli.run(command, capture_output=False)

        if self._compiledb and not dry_run:
            self.generate_compilation_database(build_target=build_target, skip_clean=True, **env_vars)

        self.prepare_build(build_target=build_target, dry_run=dry_run, **env_vars)
        command = self.compile_command(build_target=build_target, **env_vars)
        cli.log.info('Compiling keymap with {fg_cyan}%s', ' '.join(command))
        if not dry_run:
            cli.echo('\n')
            ret = cli.run(command, capture_output=False)
            if ret.returncode:
                return ret.returncode


class KeyboardKeymapBuildTarget(BuildTarget):
    def __init__(self, keyboard: str, keymap: str, json: dict = None):
        super().__init__(keyboard=keyboard, keymap=keymap, json=json)

    def __repr__(self):
        return f'KeyboardKeymapTarget(keyboard={self.keyboard}, keymap={self.keymap})'

    def _load_json(self):
        self._json = keymap_json(self.keyboard, self.keymap)

    def prepare_build(self, build_target: str = None, dry_run: bool = False, **env_vars) -> None:
        pass

    def compile_command(self, build_target: str = None, dry_run: bool = False, **env_vars) -> List[str]:
        compile_args = self._common_make_args(dry_run=dry_run, build_target=build_target)

        for key, value in env_vars.items():
            compile_args.append(f'{key}={value}')

        # Need to override the keymap path if the keymap is a userspace directory.
        # This also ensures keyboard aliases as per `keyboard_aliases.hjson` still work if the userspace has the keymap
        # in an equivalent historical location.
        keymap_location = locate_keymap(self.keyboard, self.keymap)
        if is_under_qmk_userspace(keymap_location) and not is_under_qmk_firmware(keymap_location):
            keymap_directory = keymap_location.parent
            compile_args.extend([
                f'MAIN_KEYMAP_PATH_1={keymap_directory}',
                f'MAIN_KEYMAP_PATH_2={keymap_directory}',
                f'MAIN_KEYMAP_PATH_3={keymap_directory}',
                f'MAIN_KEYMAP_PATH_4={keymap_directory}',
                f'MAIN_KEYMAP_PATH_5={keymap_directory}',
            ])

        return compile_args


class JsonKeymapBuildTarget(BuildTarget):
    def __init__(self, json_path):
        if isinstance(json_path, Path):
            self.json_path = json_path
        else:
            self.json_path = None

        json = parse_configurator_json(json_path)  # Will load from stdin if provided

        # In case the user passes a keymap.json from a keymap directory directly to the CLI.
        # e.g.: qmk compile - < keyboards/clueboard/california/keymaps/default/keymap.json
        json["keymap"] = json.get("keymap", "default_json")

        super().__init__(keyboard=json['keyboard'], keymap=json['keymap'], json=json)

        self._keymap_json = self._generated_files_path / 'keymap.json'

    def __repr__(self):
        return f'JsonKeymapTarget(keyboard={self.keyboard}, keymap={self.keymap}, path={self.json_path})'

    def _load_json(self):
        pass  # Already loaded in constructor

    def prepare_build(self, build_target: str = None, dry_run: bool = False, **env_vars) -> None:
        if self._clean:
            if self._intermediate_output.exists():
                shutil.rmtree(self._intermediate_output)

        # begin with making the deepest folder in the tree
        self._generated_files_path.mkdir(exist_ok=True, parents=True)

        # Compare minified to ensure consistent comparison
        new_content = json.dumps(self.json, separators=(',', ':'))
        if self._keymap_json.exists():
            old_content = json.dumps(json.loads(self._keymap_json.read_text(encoding='utf-8')), separators=(',', ':'))
            if old_content == new_content:
                new_content = None

        # Write the keymap.json file if different so timestamps are only updated
        # if the content changes -- running `make` won't treat it as modified.
        if new_content:
            self._keymap_json.write_text(new_content, encoding='utf-8')

    def compile_command(self, build_target: str = None, dry_run: bool = False, **env_vars) -> List[str]:
        compile_args = self._common_make_args(dry_run=dry_run, build_target=build_target)
        compile_args.extend([
            f'MAIN_KEYMAP_PATH_1={self._intermediate_output}',
            f'MAIN_KEYMAP_PATH_2={self._intermediate_output}',
            f'MAIN_KEYMAP_PATH_3={self._intermediate_output}',
            f'MAIN_KEYMAP_PATH_4={self._intermediate_output}',
            f'MAIN_KEYMAP_PATH_5={self._intermediate_output}',
            f'KEYMAP_JSON={self._keymap_json}',
            f'KEYMAP_PATH={self._generated_files_path}',
        ])

        for key, value in env_vars.items():
            compile_args.append(f'{key}={value}')

        return compile_args
