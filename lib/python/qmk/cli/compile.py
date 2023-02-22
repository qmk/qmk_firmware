"""Compile a QMK Firmware.

You can compile a keymap already in the repo or using a QMK Configurator export.
"""
from argcomplete.completers import FilesCompleter

from milc import cli

import qmk.path
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.commands import compile_configurator_json, create_make_command, parse_configurator_json, build_environment
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.keymap import keymap_completer


@cli.argument('filename', nargs='?', arg_only=True, type=qmk.path.FileType('r'), completer=FilesCompleter('.json'), help='The configurator export to compile')
@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', completer=keymap_completer, help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually build, just show the make command to be run.")
@cli.argument('-j', '--parallel', type=int, default=1, help="Set the number of parallel make jobs; 0 means unlimited.")
@cli.argument('-e', '--env', arg_only=True, action='append', default=[], help="Set a variable to be passed to make. May be passed multiple times.")
@cli.argument('-c', '--clean', arg_only=True, action='store_true', help="Remove object files before compiling.")
@cli.subcommand('Compile a QMK Firmware.')
@automagic_keyboard
@automagic_keymap
def compile(cli):
    """Compile a QMK Firmware.

    If a Configurator export is supplied this command will create a new keymap, overwriting an existing keymap if one exists.

    If a keyboard and keymap are provided this command will build a firmware based on that.
    """
    # Build the environment vars
    envs = build_environment(cli.args.env)

    # Determine the compile command
    commands = []

    if cli.args.filename:
        # If a configurator JSON was provided generate a keymap and compile it
        user_keymap = parse_configurator_json(cli.args.filename)
        commands = [compile_configurator_json(user_keymap, parallel=cli.config.compile.parallel, clean=cli.args.clean, **envs)]

    elif cli.config.compile.keyboard and cli.config.compile.keymap:
        # Generate the make command for a specific keyboard/keymap.
        if cli.args.clean:
            commands.append(create_make_command(cli.config.compile.keyboard, cli.config.compile.keymap, 'clean', **envs))
        commands.append(create_make_command(cli.config.compile.keyboard, cli.config.compile.keymap, parallel=cli.config.compile.parallel, **envs))

    if not commands:
        cli.log.error('You must supply a configurator export, both `--keyboard` and `--keymap`, or be in a directory for a keyboard or keymap.')
        cli.print_help()
        return False

    cli.log.info('Compiling keymap with {fg_cyan}%s', ' '.join(commands[-1]))
    if not cli.args.dry_run:
        cli.echo('\n')
        for command in commands:
            ret = cli.run(command, capture_output=False)
            if ret.returncode:
                return ret.returncode
