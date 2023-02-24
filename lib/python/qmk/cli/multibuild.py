"""Compile all keyboards.

This will compile everything in parallel, for testing purposes.
"""
import os
import re
from pathlib import Path
from subprocess import DEVNULL

from milc import cli

from qmk.constants import QMK_FIRMWARE
from qmk.commands import _find_make, get_make_parallel_args
import qmk.keyboard
import qmk.keymap


def _make_rules_mk_filter(key, value):
    def _rules_mk_filter(keyboard_name):
        rules_mk = qmk.keyboard.rules_mk(keyboard_name)
        return True if key in rules_mk and rules_mk[key].lower() == str(value).lower() else False

    return _rules_mk_filter


def _is_split(keyboard_name):
    rules_mk = qmk.keyboard.rules_mk(keyboard_name)
    return True if 'SPLIT_KEYBOARD' in rules_mk and rules_mk['SPLIT_KEYBOARD'].lower() == 'yes' else False


@cli.argument('-t', '--no-temp', arg_only=True, action='store_true', help="Remove temporary files during build.")
@cli.argument('-j', '--parallel', type=int, default=1, help="Set the number of parallel make jobs; 0 means unlimited.")
@cli.argument('-c', '--clean', arg_only=True, action='store_true', help="Remove object files before compiling.")
@cli.argument('-f', '--filter', arg_only=True, action='append', default=[], help="Filter the list of keyboards based on the supplied value in rules.mk. Supported format is 'SPLIT_KEYBOARD=yes'. May be passed multiple times.")
@cli.argument('-km', '--keymap', type=str, default='default', help="The keymap name to build. Default is 'default'.")
@cli.argument('-e', '--env', arg_only=True, action='append', default=[], help="Set a variable to be passed to make. May be passed multiple times.")
@cli.subcommand('Compile QMK Firmware for all keyboards.', hidden=False if cli.config.user.developer else True)
def multibuild(cli):
    """Compile QMK Firmware against all keyboards.
    """

    make_cmd = _find_make()
    if cli.args.clean:
        cli.run([make_cmd, 'clean'], capture_output=False, stdin=DEVNULL)

    builddir = Path(QMK_FIRMWARE) / '.build'
    makefile = builddir / 'parallel_kb_builds.mk'

    keyboard_list = qmk.keyboard.list_keyboards()

    filter_re = re.compile(r'^(?P<key>[A-Z0-9_]+)\s*=\s*(?P<value>[^#]+)$')
    for filter_txt in cli.args.filter:
        f = filter_re.match(filter_txt)
        if f is not None:
            keyboard_list = filter(_make_rules_mk_filter(f.group('key'), f.group('value')), keyboard_list)

    keyboard_list = list(sorted(keyboard_list))

    if len(keyboard_list) == 0:
        return

    builddir.mkdir(parents=True, exist_ok=True)
    with open(makefile, "w") as f:
        for keyboard_name in keyboard_list:
            if qmk.keymap.locate_keymap(keyboard_name, cli.args.keymap) is not None:
                keyboard_safe = keyboard_name.replace('/', '_')
                # yapf: disable
                f.write(
                    f"""\
all: {keyboard_safe}_binary
{keyboard_safe}_binary:
	@rm -f "{QMK_FIRMWARE}/.build/failed.log.{keyboard_safe}" || true
	@echo "Compiling QMK Firmware for target: '{keyboard_name}:{cli.args.keymap}'..." >>"{QMK_FIRMWARE}/.build/build.log.{os.getpid()}.{keyboard_safe}"
	+@$(MAKE) -C "{QMK_FIRMWARE}" -f "{QMK_FIRMWARE}/builddefs/build_keyboard.mk" KEYBOARD="{keyboard_name}" KEYMAP="{cli.args.keymap}" REQUIRE_PLATFORM_KEY= COLOR=true SILENT=false {' '.join(cli.args.env)} \\
		>>"{QMK_FIRMWARE}/.build/build.log.{os.getpid()}.{keyboard_safe}" 2>&1 \\
		|| cp "{QMK_FIRMWARE}/.build/build.log.{os.getpid()}.{keyboard_safe}" "{QMK_FIRMWARE}/.build/failed.log.{os.getpid()}.{keyboard_safe}"
	@{{ grep '\[ERRORS\]' "{QMK_FIRMWARE}/.build/build.log.{os.getpid()}.{keyboard_safe}" >/dev/null 2>&1 && printf "Build %-64s \e[1;31m[ERRORS]\e[0m\\n" "{keyboard_name}:{cli.args.keymap}" ; }} \\
		|| {{ grep '\[WARNINGS\]' "{QMK_FIRMWARE}/.build/build.log.{os.getpid()}.{keyboard_safe}" >/dev/null 2>&1 && printf "Build %-64s \e[1;33m[WARNINGS]\e[0m\\n" "{keyboard_name}:{cli.args.keymap}" ; }} \\
		|| printf "Build %-64s \e[1;32m[OK]\e[0m\\n" "{keyboard_name}:{cli.args.keymap}"
	@rm -f "{QMK_FIRMWARE}/.build/build.log.{os.getpid()}.{keyboard_safe}" || true
"""# noqa
                )
                # yapf: enable

                if cli.args.no_temp:
                    # yapf: disable
                    f.write(
                        f"""\
	@rm -rf "{QMK_FIRMWARE}/.build/{keyboard_safe}_{cli.args.keymap}.elf" 2>/dev/null || true
	@rm -rf "{QMK_FIRMWARE}/.build/{keyboard_safe}_{cli.args.keymap}.map" 2>/dev/null || true
	@rm -rf "{QMK_FIRMWARE}/.build/{keyboard_safe}_{cli.args.keymap}.hex" 2>/dev/null || true
	@rm -rf "{QMK_FIRMWARE}/.build/{keyboard_safe}_{cli.args.keymap}.bin" 2>/dev/null || true
	@rm -rf "{QMK_FIRMWARE}/.build/{keyboard_safe}_{cli.args.keymap}.uf2" 2>/dev/null || true
	@rm -rf "{QMK_FIRMWARE}/.build/obj_{keyboard_safe}" || true
	@rm -rf "{QMK_FIRMWARE}/.build/obj_{keyboard_safe}_{cli.args.keymap}" || true
"""# noqa
                    )
                    # yapf: enable
                f.write('\n')

    cli.run([make_cmd, *get_make_parallel_args(cli.args.parallel), '-f', makefile.as_posix(), 'all'], capture_output=False, stdin=DEVNULL)

    # Check for failures
    failures = [f for f in builddir.glob(f'failed.log.{os.getpid()}.*')]
    if len(failures) > 0:
        return False
