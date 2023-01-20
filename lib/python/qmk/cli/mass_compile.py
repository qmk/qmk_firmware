"""Compile all keyboards.

This will compile everything in parallel, for testing purposes.
"""
import fnmatch
import logging
import multiprocessing
import os
import re
from pathlib import Path
from subprocess import DEVNULL
from dotty_dict import dotty
from milc import cli

from qmk.constants import QMK_FIRMWARE
from qmk.commands import _find_make, get_make_parallel_args
from qmk.info import keymap_json
import qmk.keyboard
import qmk.keymap


def _set_log_level(level):
    cli.acquire_lock()
    old = cli.log_level
    cli.log_level = level
    cli.log.setLevel(level)
    logging.root.setLevel(level)
    cli.release_lock()
    return old


def _all_keymaps(keyboard):
    old = _set_log_level(logging.CRITICAL)
    keymaps = qmk.keymap.list_keymaps(keyboard)
    _set_log_level(old)
    return (keyboard, keymaps)


def _keymap_exists(keyboard, keymap):
    old = _set_log_level(logging.CRITICAL)
    ret = keyboard if qmk.keymap.locate_keymap(keyboard, keymap) is not None else None
    _set_log_level(old)
    return ret


def _load_keymap_info(keyboard, keymap):
    old = _set_log_level(logging.CRITICAL)
    ret = (keyboard, keymap, keymap_json(keyboard, keymap))
    _set_log_level(old)
    return ret


@cli.argument('-t', '--no-temp', arg_only=True, action='store_true', help="Remove temporary files during build.")
@cli.argument('-j', '--parallel', type=int, default=1, help="Set the number of parallel make jobs; 0 means unlimited.")
@cli.argument('-c', '--clean', arg_only=True, action='store_true', help="Remove object files before compiling.")
@cli.argument(
    '-f',
    '--filter',
    arg_only=True,
    action='append',
    default=[],
    help=  # noqa: `format-python` and `pytest` don't agree here.
    "Filter the list of keyboards based on the supplied value in rules.mk. Matches info.json structure, and accepts the format 'features.rgblight=true'. May be passed multiple times, all filters need to match. Value may include wildcards such as '*' and '?'."  # noqa: `format-python` and `pytest` don't agree here.
)
@cli.argument('-km', '--keymap', type=str, default='default', help="The keymap name to build. Default is 'default'.")
@cli.argument('-e', '--env', arg_only=True, action='append', default=[], help="Set a variable to be passed to make. May be passed multiple times.")
@cli.subcommand('Compile QMK Firmware for all keyboards.', hidden=False if cli.config.user.developer else True)
def mass_compile(cli):
    """Compile QMK Firmware against all keyboards.
    """
    make_cmd = _find_make()
    if cli.args.clean:
        cli.run([make_cmd, 'clean'], capture_output=False, stdin=DEVNULL)

    builddir = Path(QMK_FIRMWARE) / '.build'
    makefile = builddir / 'parallel_kb_builds.mk'

    targets = []

    with multiprocessing.Pool() as pool:
        cli.log.info(f'Retrieving list of keyboards with keymap "{cli.args.keymap}"...')
        target_list = []
        if cli.args.keymap == 'all':
            kb_to_kms = pool.map(_all_keymaps, qmk.keyboard.list_keyboards())
            for targets in kb_to_kms:
                keyboard = targets[0]
                keymaps = targets[1]
                target_list.extend([(keyboard, keymap) for keymap in keymaps])
        else:
            target_list = [(kb, cli.args.keymap) for kb in filter(lambda kb: kb is not None, pool.starmap(_keymap_exists, [(kb, cli.args.keymap) for kb in qmk.keyboard.list_keyboards()]))]

        if len(cli.args.filter) == 0:
            targets = target_list
        else:
            cli.log.info('Parsing data for all matching keyboard/keymap combinations...')
            valid_keymaps = [(e[0], e[1], dotty(e[2])) for e in pool.starmap(_load_keymap_info, target_list)]

            filter_re = re.compile(r'^(?P<key>[a-zA-Z0-9_\.]+)\s*=\s*(?P<value>[^#]+)$')
            for filter_txt in cli.args.filter:
                f = filter_re.match(filter_txt)
                if f is not None:
                    key = f.group('key')
                    value = f.group('value')
                    cli.log.info(f'Filtering on condition ("{key}" == "{value}")...')

                    def _make_filter(k, v):
                        expr = fnmatch.translate(v)
                        rule = re.compile(expr, re.IGNORECASE)

                        def f(e):
                            lhs = e[2].get(k)
                            lhs = str(False if lhs is None else lhs)
                            return rule.search(lhs) is not None

                        return f

                    valid_keymaps = filter(_make_filter(key, value), valid_keymaps)

            targets = [(e[0], e[1]) for e in valid_keymaps]

    if len(targets) == 0:
        return

    builddir.mkdir(parents=True, exist_ok=True)
    with open(makefile, "w") as f:
        for target in sorted(targets):
            keyboard_name = target[0]
            keymap_name = target[1]
            keyboard_safe = keyboard_name.replace('/', '_')
            # yapf: disable
            f.write(
                f"""\
all: {keyboard_safe}_{keymap_name}_binary
{keyboard_safe}_{keymap_name}_binary:
	@rm -f "{QMK_FIRMWARE}/.build/failed.log.{keyboard_safe}.{keymap_name}" || true
	@echo "Compiling QMK Firmware for target: '{keyboard_name}:{keymap_name}'..." >>"{QMK_FIRMWARE}/.build/build.log.{os.getpid()}.{keyboard_safe}"
	+@$(MAKE) -C "{QMK_FIRMWARE}" -f "{QMK_FIRMWARE}/builddefs/build_keyboard.mk" KEYBOARD="{keyboard_name}" KEYMAP="{keymap_name}" COLOR=true SILENT=false {' '.join(cli.args.env)} \\
		>>"{QMK_FIRMWARE}/.build/build.log.{os.getpid()}.{keyboard_safe}.{keymap_name}" 2>&1 \\
		|| cp "{QMK_FIRMWARE}/.build/build.log.{os.getpid()}.{keyboard_safe}.{keymap_name}" "{QMK_FIRMWARE}/.build/failed.log.{os.getpid()}.{keyboard_safe}.{keymap_name}"
	@{{ grep '\[ERRORS\]' "{QMK_FIRMWARE}/.build/build.log.{os.getpid()}.{keyboard_safe}.{keymap_name}" >/dev/null 2>&1 && printf "Build %-64s \e[1;31m[ERRORS]\e[0m\\n" "{keyboard_name}:{keymap_name}" ; }} \\
		|| {{ grep '\[WARNINGS\]' "{QMK_FIRMWARE}/.build/build.log.{os.getpid()}.{keyboard_safe}.{keymap_name}" >/dev/null 2>&1 && printf "Build %-64s \e[1;33m[WARNINGS]\e[0m\\n" "{keyboard_name}:{keymap_name}" ; }} \\
		|| printf "Build %-64s \e[1;32m[OK]\e[0m\\n" "{keyboard_name}:{keymap_name}"
	@rm -f "{QMK_FIRMWARE}/.build/build.log.{os.getpid()}.{keyboard_safe}.{keymap_name}" || true
"""# noqa
            )
            # yapf: enable

            if cli.args.no_temp:
                # yapf: disable
                f.write(
                    f"""\
	@rm -rf "{QMK_FIRMWARE}/.build/{keyboard_safe}_{keymap_name}.elf" 2>/dev/null || true
	@rm -rf "{QMK_FIRMWARE}/.build/{keyboard_safe}_{keymap_name}.map" 2>/dev/null || true
	@rm -rf "{QMK_FIRMWARE}/.build/{keyboard_safe}_{keymap_name}.hex" 2>/dev/null || true
	@rm -rf "{QMK_FIRMWARE}/.build/{keyboard_safe}_{keymap_name}.bin" 2>/dev/null || true
	@rm -rf "{QMK_FIRMWARE}/.build/{keyboard_safe}_{keymap_name}.uf2" 2>/dev/null || true
	@rm -rf "{QMK_FIRMWARE}/.build/obj_{keyboard_safe}" || true
	@rm -rf "{QMK_FIRMWARE}/.build/obj_{keyboard_safe}_{keymap_name}" || true
"""# noqa
                )
                # yapf: enable
            f.write('\n')

    cli.run([make_cmd, *get_make_parallel_args(cli.args.parallel), '-f', makefile.as_posix(), 'all'], capture_output=False, stdin=DEVNULL)

    # Check for failures
    failures = [f for f in builddir.glob(f'failed.log.{os.getpid()}.*')]
    if len(failures) > 0:
        return False
