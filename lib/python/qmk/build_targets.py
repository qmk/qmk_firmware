# Copyright 2023 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later
from typing import List
from pathlib import Path
from milc import cli
from qmk.constants import QMK_FIRMWARE
from qmk.commands import _find_make, get_make_parallel_args, parse_configurator_json, create_make_target
from qmk.cli.generate.compilation_database import write_compilation_database


class BuildTarget:
    def __init__(self, keyboard: str, keymap: str):
        self._keyboard = keyboard
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

    def prepare_build(self, build_target: str = None, dry_run: bool = False, **env_vars) -> None:
        raise NotImplementedError("prepare_build() not implemented in base class")

    def compile_commands(self, build_target: str = None, dry_run: bool = False, **env_vars) -> List[str]:
        raise NotImplementedError("compile_commands() not implemented in base class")

    def generate_compilation_database(self, skip_clean: bool = False, **env_vars) -> None:
        self.prepare_build(**env_vars)
        command = self.compile_commands(dry_run=True, **env_vars)
        write_compilation_database(command=command, output_path=QMK_FIRMWARE / 'compile_commands.json', skip_clean=skip_clean, **env_vars)

    def compile(self, build_target: str = None, dry_run: bool = False, **env_vars) -> None:
        if self._clean or self._compiledb:
            cli.run(create_make_target("clean", dry_run=dry_run, parallel=1, **env_vars), capture_output=False)

        self.prepare_build(build_target=build_target, **env_vars)

        if self._compiledb and not dry_run:
            self.generate_compilation_database(skip_clean=True, **env_vars)

        command = self.compile_commands(build_target=build_target, **env_vars)
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

    def compile_commands(self, build_target: str = None, dry_run: bool = False, **env_vars) -> List[str]:
        """This needs to be rewritten to do a full `make` invocation, rather than the old syntax!

        See commands.py for actual implementation.
        """

        compile_args = [
            _find_make(),
            *get_make_parallel_args(self._parallel),
        ]

        if dry_run:
            compile_args.append('-n')

        if not build_target:
            compile_args.append(f'{self.keyboard}:{self.keymap}')
        else:
            compile_args.append(f'{self.keyboard}:{self.keymap}:{build_target}')

        for key, value in env_vars.items():
            compile_args.append(f'{key}={value}')

        if cli.config.general.verbose:
            compile_args.append('VERBOSE=true')

        return compile_args


class JsonKeymapBuildTarget(BuildTarget):
    def __init__(self, json_path: Path, json: dict = None):
        self.json_path = Path(json_path)
        if json is None:
            json = parse_configurator_json(self.json_path)
        self.json = json
        super().__init__(self.json['keyboard'], self.json['keymap'])

    def __repr__(self):
        return f'JsonKeymapTarget(keyboard={self.keyboard}, keymap={self.keymap}, path={self.json_path})'

    def prepare_build(self, build_target: str = None, dry_run: bool = False, **env_vars) -> None:
        pass

    def compile_commands(self, build_target: str = None, dry_run: bool = False, **env_vars) -> List[str]:
        return []
