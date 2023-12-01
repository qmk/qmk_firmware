"""Compile a QMK Firmware.

You can compile a keymap already in the repo or using a QMK Configurator export.
"""
from argcomplete.completers import FilesCompleter

from milc import cli

import qmk.path
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.commands import build_environment
from qmk.keyboard import keyboard_completer, keyboard_folder_or_all, is_all_keyboards
from qmk.keymap import keymap_completer, locate_keymap
from qmk.build_targets import KeyboardKeymapBuildTarget, JsonKeymapBuildTarget


@cli.argument('filename', nargs='?', arg_only=True, type=qmk.path.FileType('r'), completer=FilesCompleter('.json'), help='The configurator export to compile')
@cli.argument('-kb', '--keyboard', type=keyboard_folder_or_all, completer=keyboard_completer, help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', completer=keymap_completer, help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually build, just show the make command to be run.")
@cli.argument('-j', '--parallel', type=int, default=1, help="Set the number of parallel make jobs; 0 means unlimited.")
@cli.argument('-e', '--env', arg_only=True, action='append', default=[], help="Set a variable to be passed to make. May be passed multiple times.")
@cli.argument('-c', '--clean', arg_only=True, action='store_true', help="Remove object files before compiling.")
@cli.argument('-t', '--target', type=str, default=None, help="Intended alternative build target, such as `production` in `make planck/rev4:default:production`.")
@cli.argument('--compiledb', arg_only=True, action='store_true', help="Generates the clang compile_commands.json file during build. Implies --clean.")
@cli.subcommand('Compile a QMK Firmware.')
@automagic_keyboard
@automagic_keymap
def compile(cli):
    """Compile a QMK Firmware.

    If a Configurator export is supplied this command will create a new keymap, overwriting an existing keymap if one exists.

    If a keyboard and keymap are provided this command will build a firmware based on that.
    """

    # If we've received `-kb all`, reroute it to mass-compile.
    if is_all_keyboards(cli.args.keyboard):
        from .mass_compile import mass_compile
        cli.args.builds = []
        cli.args.filter = []
        cli.config.mass_compile.keymap = cli.config.compile.keymap
        cli.config.mass_compile.parallel = cli.config.compile.parallel
        cli.config.mass_compile.no_temp = False
        return mass_compile(cli)

    # If we've received `-km all`, reroute it to mass-compile.
    if cli.args.keymap == 'all':
        from .mass_compile import mass_compile
        cli.args.builds = [f'{cli.args.keyboard}:all']
        cli.args.filter = []
        cli.config.mass_compile.keymap = None
        cli.config.mass_compile.parallel = cli.config.compile.parallel
        cli.config.mass_compile.no_temp = False
        return mass_compile(cli)

    # Build the environment vars
    envs = build_environment(cli.args.env)

    # Handler for the build target
    target = None

    if cli.args.filename:
        # if we were given a filename, assume we have a json build target
        target = JsonKeymapBuildTarget(cli.args.filename)

    elif cli.config.compile.keyboard and cli.config.compile.keymap:
        # if we got a keyboard and keymap, attempt to find it
        if not locate_keymap(cli.config.compile.keyboard, cli.config.compile.keymap):
            cli.log.error('Invalid keymap argument.')
            cli.print_help()
            return False

        # If we got here, then we have a valid keyboard and keymap for a build target
        target = KeyboardKeymapBuildTarget(cli.config.compile.keyboard, cli.config.compile.keymap)

    if not target:
        cli.log.error('You must supply a configurator export, both `--keyboard` and `--keymap`, or be in a directory for a keyboard or keymap.')
        cli.print_help()
        return False

    target.configure(parallel=cli.config.compile.parallel, clean=cli.args.clean, compiledb=cli.args.compiledb)
    target.compile(cli.args.target, dry_run=cli.args.dry_run, **envs)
