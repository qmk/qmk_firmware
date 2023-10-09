# Copyright 2023 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later
import json
from typing import List
from pathlib import Path
from milc import cli
from qmk.constants import QMK_FIRMWARE, INTERMEDIATE_OUTPUT_PREFIX
from qmk.commands import _find_make, get_make_parallel_args, parse_configurator_json, create_make_target
from qmk.cli.generate.compilation_database import write_compilation_database


class BuildTarget:
    def __init__(self, keyboard: str, keymap: str):
        self._keyboard = keyboard
        self._keyboard_safe = keyboard.replace('/', '_')
        self._keymap = keymap
        self._parallel = 1
        self._clean = False
        self._compiledb = False

    def __str__(self):
        return f'{self.keyboard}:{self.keymap}'

    def __repr__(self):
        return f'BuildTarget(keyboard={self.keyboard}, keymap={self.keymap})'

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

    def _common_make_args(self):
        compile_args = [
            _find_make(),
            *get_make_parallel_args(self._parallel),
            '-r',
            '-R',
            '-f',
            'builddefs/build_keyboard.mk',
        ]

        if not cli.config.general.verbose:
            compile_args.append('-s')

        return compile_args

    def _common_make_vars(self):
        verbose = 'true' if cli.config.general.verbose else 'false'
        color = 'true' if cli.config.general.color else 'false'

        target = f'{self._keyboard_safe}_{self.keymap}'
        intermediate_output = Path(f'{INTERMEDIATE_OUTPUT_PREFIX}{self._keyboard_safe}_{self.keymap}')

        make_args = [
            f'KEYBOARD={self.keyboard}',
            f'KEYMAP={self.keymap}',
            f'KEYBOARD_FILESAFE={self._keyboard_safe}',
            f'TARGET={target}',
            f'INTERMEDIATE_OUTPUT={intermediate_output}',
            f'VERBOSE={verbose}',
            f'COLOR={color}',
            'SILENT=false',
            'QMK_BIN="qmk"',
        ]

        return make_args

    def prepare_build(self, build_target: str = None, dry_run: bool = False, **env_vars) -> None:
        raise NotImplementedError("prepare_build() not implemented in base class")

    def compile_command(self, build_target: str = None, dry_run: bool = False, **env_vars) -> List[str]:
        raise NotImplementedError("compile_command() not implemented in base class")

    def generate_compilation_database(self, build_target: str = None, skip_clean: bool = False, **env_vars) -> None:
        self.prepare_build(build_target=build_target, **env_vars)
        command = self.compile_command(build_target=build_target, dry_run=True, **env_vars)
        write_compilation_database(command=command, output_path=QMK_FIRMWARE / 'compile_commands.json', skip_clean=skip_clean, **env_vars)

    def compile(self, build_target: str = None, dry_run: bool = False, **env_vars) -> None:
        if self._clean or self._compiledb:
            command = create_make_target("clean", dry_run=dry_run, parallel=1, **env_vars)
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
    def __init__(self, keyboard: str, keymap: str):
        super().__init__(keyboard, keymap)

    def __repr__(self):
        return f'KeyboardKeymapTarget(keyboard={self.keyboard}, keymap={self.keymap})'

    def prepare_build(self, build_target: str = None, dry_run: bool = False, **env_vars) -> None:
        pass

    def compile_command(self, build_target: str = None, dry_run: bool = False, **env_vars) -> List[str]:
        compile_args = self._common_make_args()

        if dry_run:
            compile_args.append('-n')

        if build_target:
            compile_args.append(build_target)

        compile_args.extend(self._common_make_vars())

        for key, value in env_vars.items():
            compile_args.append(f'{key}={value}')

        return compile_args


class JsonKeymapBuildTarget(BuildTarget):
    def __init__(self, json_path):
        if isinstance(json_path, Path):
            self.json_path = json_path
        else:
            self.json_path = None

        self.json = parse_configurator_json(json_path)  # Will load from stdin if provided

        # In case the user passes a keymap.json from a keymap directory directly to the CLI.
        # e.g.: qmk compile - < keyboards/clueboard/california/keymaps/default/keymap.json
        self.json["keymap"] = self.json.get("keymap", "default_json")

        super().__init__(self.json['keyboard'], self.json['keymap'])

    def __repr__(self):
        return f'JsonKeymapTarget(keyboard={self.keyboard}, keymap={self.keymap}, path={self.json_path})'

    def prepare_build(self, build_target: str = None, dry_run: bool = False, **env_vars) -> None:
        intermediate_output = Path(f'{INTERMEDIATE_OUTPUT_PREFIX}{self._keyboard_safe}_{self.json["keymap"]}')
        keymap_dir = intermediate_output / 'src'
        keymap_json = keymap_dir / 'keymap.json'

        # begin with making the deepest folder in the tree
        keymap_dir.mkdir(exist_ok=True, parents=True)

        # Compare minified to ensure consistent comparison
        new_content = json.dumps(self.json, separators=(',', ':'))
        if keymap_json.exists():
            old_content = json.dumps(json.loads(keymap_json.read_text(encoding='utf-8')), separators=(',', ':'))
            if old_content == new_content:
                new_content = None

        # Write the keymap.json file if different
        if new_content:
            keymap_json.write_text(new_content, encoding='utf-8')

    def compile_command(self, build_target: str = None, dry_run: bool = False, **env_vars) -> List[str]:
        compile_args = self._common_make_args()

        if dry_run:
            compile_args.append('-n')

        if build_target:
            compile_args.append(build_target)

        compile_args.extend(self._common_make_vars())

        intermediate_output = Path(f'{INTERMEDIATE_OUTPUT_PREFIX}{self._keyboard_safe}_{self.json["keymap"]}')
        keymap_dir = intermediate_output / 'src'
        keymap_json = keymap_dir / 'keymap.json'

        compile_args.extend([
            f'MAIN_KEYMAP_PATH_1={intermediate_output}',
            f'MAIN_KEYMAP_PATH_2={intermediate_output}',
            f'MAIN_KEYMAP_PATH_3={intermediate_output}',
            f'MAIN_KEYMAP_PATH_4={intermediate_output}',
            f'MAIN_KEYMAP_PATH_5={intermediate_output}',
            f'KEYMAP_JSON={keymap_json}',
            f'KEYMAP_PATH={keymap_dir}',
        ])

        for key, value in env_vars.items():
            compile_args.append(f'{key}={value}')

        return compile_args
