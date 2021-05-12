"""Compile a QMK Firmware.

You can compile a keymap already in the repo or using a QMK Configurator export.
"""
from argcomplete.completers import FilesCompleter
from milc import cli

import qmk.path
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.commands import compile_configurator_json, create_make_command, parse_configurator_json
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.keymap import keymap_completer


@cli.argument('filename', nargs='?', arg_only=True, type=qmk.path.FileType('r'), completer=FilesCompleter('.json'), help='The configurator export to compile')
@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', completer=keymap_completer, help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually build, just show the make command to be run.")
@cli.argument('-j', '--parallel', type=int, default=1, help="Set the number of parallel make jobs to run.")
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
    if cli.args.clean and not cli.args.filename and not cli.args.dry_run:
        command = create_make_command(cli.config.compile.keyboard, cli.config.compile.keymap, 'clean')
        # FIXME(skullydazed/anyone): Remove text=False once milc 1.0.11 has had enough time to be installed everywhere.
        cli.run(command, capture_output=False, text=False)

    # Build the environment vars
    envs = {}
    for env in cli.args.env:
        if '=' in env:
            key, value = env.split('=', 1)
            envs[key] = value
        else:
            cli.log.warning('Invalid environment variable: %s', env)

    # Determine the compile command
    command = None

    if cli.args.filename:
        # If a configurator JSON was provided generate a keymap and compile it
        user_keymap = parse_configurator_json(cli.args.filename)
        command = compile_configurator_json(user_keymap, parallel=cli.config.compile.parallel, **envs)

    else:
        if cli.config.compile.keyboard and cli.config.compile.keymap:
            # Generate the make command for a specific keyboard/keymap.
            command = create_make_command(cli.config.compile.keyboard, cli.config.compile.keymap, parallel=cli.config.compile.parallel, **envs)

        elif not cli.config.compile.keyboard:
            cli.log.error('Could not determine keyboard!')
        elif not cli.config.compile.keymap:
            cli.log.error('Could not determine keymap!')

    # Compile the firmware, if we're able to
    if command:
        cli.log.info('Compiling keymap with {fg_cyan}%s', ' '.join(command))
        if not cli.args.dry_run:
            cli.echo('\n')
            # FIXME(skullydazed/anyone): Remove text=False once milc 1.0.11 has had enough time to be installed everywhere.
            compile = cli.run(command, capture_output=False, text=False)
            return compile.returncode

    else:
        cli.log.error('You must supply a configurator export, both `--keyboard` and `--keymap`, or be in a directory for a keyboard or keymap.')
        cli.echo('usage: qmk compile [-h] [-b] [-kb KEYBOARD] [-km KEYMAP] [filename]')
        return False
