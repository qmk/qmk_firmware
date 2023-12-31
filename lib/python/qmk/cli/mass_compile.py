"""Compile all keyboards.

This will compile everything in parallel, for testing purposes.
"""
import os
from typing import List
from pathlib import Path
from subprocess import DEVNULL
from milc import cli

from qmk.constants import QMK_FIRMWARE
from qmk.commands import find_make, get_make_parallel_args, build_environment
from qmk.search import search_keymap_targets, search_make_targets
from qmk.build_targets import BuildTarget, JsonKeymapBuildTarget


def mass_compile_targets(targets: List[BuildTarget], clean: bool, dry_run: bool, no_temp: bool, parallel: int, **env):
    if len(targets) == 0:
        return

    make_cmd = find_make()
    builddir = Path(QMK_FIRMWARE) / '.build'
    makefile = builddir / 'parallel_kb_builds.mk'

    if dry_run:
        cli.log.info('Compilation targets:')
        for target in sorted(targets, key=lambda t: (t.keyboard, t.keymap)):
            cli.log.info(f"{{fg_cyan}}qmk compile -kb {target.keyboard} -km {target.keymap}{{fg_reset}}")
    else:
        if clean:
            cli.run([make_cmd, 'clean'], capture_output=False, stdin=DEVNULL)

        builddir.mkdir(parents=True, exist_ok=True)
        with open(makefile, "w") as f:
            for target in sorted(targets, key=lambda t: (t.keyboard, t.keymap)):
                keyboard_name = target.keyboard
                keymap_name = target.keymap
                target.configure(parallel=1)  # We ignore parallelism on a per-build basis as we defer to the parent make invocation
                target.prepare_build(**env)  # If we've got json targets, allow them to write out any extra info to .build before we kick off `make`
                command = target.compile_command(**env)
                command[0] = '+@$(MAKE)'  # Override the make so that we can use jobserver to handle parallelism
                keyboard_safe = keyboard_name.replace('/', '_')
                build_log = f"{QMK_FIRMWARE}/.build/build.log.{os.getpid()}.{keyboard_safe}.{keymap_name}"
                failed_log = f"{QMK_FIRMWARE}/.build/failed.log.{os.getpid()}.{keyboard_safe}.{keymap_name}"
                # yapf: disable
                f.write(
                    f"""\
all: {keyboard_safe}_{keymap_name}_binary
{keyboard_safe}_{keymap_name}_binary:
	@rm -f "{build_log}" || true
	@echo "Compiling QMK Firmware for target: '{keyboard_name}:{keymap_name}'..." >>"{build_log}"
	{' '.join(command)} \\
		>>"{build_log}" 2>&1 \\
		|| cp "{build_log}" "{failed_log}"
	@{{ grep '\[ERRORS\]' "{build_log}" >/dev/null 2>&1 && printf "Build %-64s \e[1;31m[ERRORS]\e[0m\\n" "{keyboard_name}:{keymap_name}" ; }} \\
		|| {{ grep '\[WARNINGS\]' "{build_log}" >/dev/null 2>&1 && printf "Build %-64s \e[1;33m[WARNINGS]\e[0m\\n" "{keyboard_name}:{keymap_name}" ; }} \\
		|| printf "Build %-64s \e[1;32m[OK]\e[0m\\n" "{keyboard_name}:{keymap_name}"
	@rm -f "{build_log}" || true
"""# noqa
                )
                # yapf: enable

                if no_temp:
                    # yapf: disable
                    f.write(
                        f"""\
	@rm -rf "{QMK_FIRMWARE}/.build/{keyboard_safe}_{keymap_name}.elf" 2>/dev/null || true
	@rm -rf "{QMK_FIRMWARE}/.build/{keyboard_safe}_{keymap_name}.map" 2>/dev/null || true
	@rm -rf "{QMK_FIRMWARE}/.build/obj_{keyboard_safe}_{keymap_name}" || true
"""# noqa
                    )
                    # yapf: enable
                f.write('\n')

        cli.run([find_make(), *get_make_parallel_args(parallel), '-f', makefile.as_posix(), 'all'], capture_output=False, stdin=DEVNULL)

        # Check for failures
        failures = [f for f in builddir.glob(f'failed.log.{os.getpid()}.*')]
        if len(failures) > 0:
            return False


@cli.argument('builds', nargs='*', arg_only=True, help="List of builds in form <keyboard>:<keymap> to compile in parallel. Specifying this overrides all other target search options.")
@cli.argument('-t', '--no-temp', arg_only=True, action='store_true', help="Remove temporary files during build.")
@cli.argument('-j', '--parallel', type=int, default=1, help="Set the number of parallel make jobs; 0 means unlimited.")
@cli.argument('-c', '--clean', arg_only=True, action='store_true', help="Remove object files before compiling.")
@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually build, just show the commands to be run.")
@cli.argument(
    '-f',
    '--filter',
    arg_only=True,
    action='append',
    default=[],
    help=  # noqa: `format-python` and `pytest` don't agree here.
    "Filter the list of keyboards based on the supplied value in rules.mk. Matches info.json structure, and accepts the formats 'features.rgblight=true' or 'exists(matrix_pins.direct)'. May be passed multiple times, all filters need to match. Value may include wildcards such as '*' and '?'."  # noqa: `format-python` and `pytest` don't agree here.
)
@cli.argument('-km', '--keymap', type=str, default='default', help="The keymap name to build. Default is 'default'.")
@cli.argument('-e', '--env', arg_only=True, action='append', default=[], help="Set a variable to be passed to make. May be passed multiple times.")
@cli.subcommand('Compile QMK Firmware for all keyboards.', hidden=False if cli.config.user.developer else True)
def mass_compile(cli):
    """Compile QMK Firmware against all keyboards.
    """
    if len(cli.args.builds) > 0:
        json_like_targets = list([Path(p) for p in filter(lambda e: Path(e).exists() and Path(e).suffix == '.json', cli.args.builds)])
        make_like_targets = list(filter(lambda e: Path(e) not in json_like_targets, cli.args.builds))
        targets = search_make_targets(make_like_targets)
        targets.extend([JsonKeymapBuildTarget(e) for e in json_like_targets])
    else:
        targets = search_keymap_targets([('all', cli.config.mass_compile.keymap)], cli.args.filter)

    return mass_compile_targets(targets, cli.args.clean, cli.args.dry_run, cli.args.no_temp, cli.config.mass_compile.parallel, **build_environment(cli.args.env))
