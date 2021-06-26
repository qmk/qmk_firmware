"""Compile a QMK Firmware.

You can compile a keymap already in the repo or using a QMK Configurator export.
"""
from subprocess import DEVNULL

from argcomplete.completers import FilesCompleter
from dotty_dict import dotty
from milc import cli

import qmk.path
from qmk.decorators import automagic_keyboard, automagic_keymap, lru_cache
from qmk.commands import compile_configurator_json, create_make_command, parse_configurator_json
from qmk.info import info_json
from qmk.keyboard import keyboard_completer, is_keyboard_target, list_keyboards
from qmk.keymap import keymap_completer, list_keymaps
from qmk.metadata import true_values, false_values


@lru_cache()
def _keyboard_list():
    """Returns a list of keyboards matching cli.config.compile.keyboard.
    """
    if cli.config.compile.keyboard == 'all':
        return list_keyboards()

    elif cli.config.compile.keyboard.startswith('all-'):
        return list_keyboards()

    return [cli.config.compile.keyboard]


def keyboard_keymap_iter():
    """Iterates over the keyboard/keymap for this command and yields a pairing of each.
    """
    for keyboard in _keyboard_list():
        continue_flag = False
        if cli.args.filter:
            info_data = dotty(info_json(keyboard))
            for filter in cli.args.filter:
                if '=' in filter:
                    key, value = filter.split('=', 1)
                    if value in true_values:
                        value = True
                    elif value in false_values:
                        value = False
                    elif value.isdigit():
                        value = int(value)
                    elif '.' in value and value.replace('.').isdigit():
                        value = float(value)

                    if info_data.get(key) != value:
                        continue_flag = True
                        break

            if continue_flag:
                continue

        if cli.config.compile.keymap == 'all':
            for keymap in list_keymaps(keyboard):
                yield keyboard, keymap
        else:
            yield keyboard, cli.config.compile.keymap


@cli.argument('filename', nargs='?', arg_only=True, type=qmk.path.FileType('r'), completer=FilesCompleter('.json'), help='The configurator export to compile')
@cli.argument('-kb', '--keyboard', type=is_keyboard_target, completer=keyboard_completer, help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', completer=keymap_completer, help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually build, just show the make command to be run.")
@cli.argument('-j', '--parallel', type=int, default=1, help="Set the number of parallel make jobs to run.")
@cli.argument('-f', '--filter', arg_only=True, action='append', default=[], help="Filter your list against info.json.")
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
    envs = {'REQUIRE_PLATFORM_KEY': ''}
    if cli.config.compile.keyboard is None:
        cli.config.compile.keyboard = ''

    silent = cli.config.compile.keyboard == 'all' or cli.config.compile.keyboard.startswith('all-') or cli.config.compile.keymap == 'all'

    # Setup the environment
    for env in cli.args.env:
        if '=' in env:
            key, value = env.split('=', 1)
            if key in envs:
                cli.log.warning('Overwriting existing environment variable %s=%s with %s=%s!', key, envs[key], key, value)
            envs[key] = value
        else:
            cli.log.warning('Invalid environment variable: %s', env)

    if cli.config.compile.keyboard.startswith('all-'):
        envs['REQUIRE_PLATFORM_KEY'] = cli.config.compile.keyboard[4:]

    # Run clean if necessary
    if cli.args.clean and not cli.args.filename and not cli.args.dry_run:
        for keyboard, keymap in keyboard_keymap_iter():
            cli.log.info('Cleaning previous build files for keyboard {fg_cyan}%s{fg_reset} keymap {fg_cyan}%s', keyboard, keymap)
            _, _, make_cmd = create_make_command(keyboard, keymap, 'clean', cli.config.compile.parallel, silent, **envs)
            cli.run(make_cmd, capture_output=False, stdin=DEVNULL)

    # If -f has been specified without a keyboard target, assume -kb all
    if cli.args.filter and not cli.args.keyboard:
        cli.log.debug('--filter supplied without --keyboard, assuming --keyboard all.')
        cli.config.compile.keyboard = 'all'

    # Determine the compile command(s)
    commands = None

    if cli.args.filename:
        # If a configurator JSON was provided generate a keymap and compile it
        user_keymap = parse_configurator_json(cli.args.filename)
        commands = [compile_configurator_json(user_keymap, parallel=cli.config.compile.parallel, **envs)]

    elif cli.config.compile.keyboard and cli.config.compile.keymap:
        if cli.args.filter:
            cli.log.info('Generating the list of keyboards to compile, this may take some time.')

        commands = [create_make_command(keyboard, keymap, parallel=cli.config.compile.parallel, silent=silent, **envs) for keyboard, keymap in keyboard_keymap_iter()]

    elif not cli.config.compile.keyboard:
        cli.log.error('Could not determine keyboard!')

    elif not cli.config.compile.keymap:
        cli.log.error('Could not determine keymap!')

    # Compile the firmware, if we're able to
    if commands:
        returncodes = []
        for keyboard, keymap, command in commands:
            if keymap not in list_keymaps(keyboard):
                cli.log.debug('Skipping keyboard %s, no %s keymap found.', keyboard, keymap)
                continue

            print()
            cli.log.info('Building firmware for {fg_cyan}%s{fg_reset} with keymap {fg_cyan}%s', keyboard, keymap)
            cli.log.debug('Running make command: {fg_blue}%s', ' '.join(command))

            if not cli.args.dry_run:
                compile = cli.run(command, capture_output=False)
                returncodes.append(compile.returncode)
                if compile.returncode == 0:
                    cli.log.info('Success!')
                else:
                    cli.log.error('Failed!')

        if any(returncodes):
            print()
            cli.log.error('Could not compile all targets, look above this message for more details. Failing target(s):')

            for i, returncode in enumerate(returncodes):
                if returncode != 0:
                    keyboard, keymap, command = commands[i]
                    cli.echo('\tkeyboard: {fg_cyan}%s{fg_reset} keymap: {fg_cyan}%s', keyboard, keymap)

    elif cli.args.filter:
        cli.log.error('No keyboards found after applying filter(s)!')
        return False

    else:
        cli.log.error('You must supply a configurator export, both `--keyboard` and `--keymap`, or be in a directory for a keyboard or keymap.')
        cli.print_help()
        return False
