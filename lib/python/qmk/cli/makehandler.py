"""Generate a make command from a `keyboard:keymap` pair.
"""
import os

from milc import cli

from qmk.path import is_keyboard

def parse_rule(rule):
    """Parses a QMK make rule into its compononent parts.
    
    Expects rule to be in the form `<keyboard>:<keyboard>[:<COMMAND>]`
    """
    rule = rule.split(':')
    if len(rule) == 1:
        return rule + ['all', '']

    if len(rule) == 2:
        return rule + ['']

    if len(rule) == 3:
        return rule

    raise IndexError('rule %s has too many parts!' % rule)


@cli.argument('arguments', arg_only=True, nargs='+', help='Make arguments.')
@cli.subcommand('QMK Hello World.', hidden=True)
def makehandler(cli):
    """Turn a `make keyboard:keymap` command into a full make command.
    """
    environment = os.environ.copy()  # FIXME: We should sanitize this
    print('***', 'environment')
    for key, value in environment.items():
        cli.log.info('%s=%s', key, value)
    environment['COLOR'] = '1' if cli.config.general.color else '0'
    environment['SILENT_MODE'] = '0'
    environment['VERBOSE'] = '1' if cli.config.general.verbose else '0'
    compile_targets = []

    # Check submodules and warn if dirty
    pass

    # Parse the command line (PARSE_RULE)
    for argument in cli.args.arguments:
        if "=" in argument:
            key, value = argument.split('=', 1)
            environment[key] = value

        else:
            keyboard, keymap, command = parse_rule(argument)
            keyboard_env = environment.copy()

            # Check the keyboard
            if not (keyboard in ['all', 'test'] or is_keyboard(keyboard)):
                cli.log.error('Invalid keyboard: %s', keyboard)
                continue

            # Check the keymap
            if not (keymap in ['all'] or True):  # FIXME: Replace True with is_keymap(keyboard, keymap)
                cli.log.error('Invalid keymap: %s', keymap)
                continue

            # Add this compile target
            keyboard_env['CURRENT_KB'] = keyboard_env['DEFAULT_FOLDER'] = keyboard_env['KEYBOARD_RULE'] = keyboard
            compile_targets.append([keyboard, keymap, command, keyboard_env])

    # Determine if we should turn on SILENT_MODE.
    if 'SILENT' in environment:
        for target in compile_targets:
            target[3]['SILENT_MODE'] = environment['SILENT']
    elif len(compile_targets) > 1:
        for target in compile_targets:
            target[3]['SILENT_MODE'] = environment['SILENT']

    # Iterate through our compile targets and generate make commands.
    compiles_ok = True
    for keyboard, keymap, command, environment in compile_targets:
        print('***', repr(keyboard), repr(keymap), repr(command))
        for key, value in environment.items():
            cli.log.info('%s=%s', key, value)

    if not compiles_ok:
        cli.log.error('{fg_red}Make finished with errors')
        exit(1)

    # $(foreach TEST,$(sort $(TESTS)),$(RUN_TEST))
    tests_ok = False  # FIXME: Set to true when all tests are true
    
    if not tests_ok:
        # printf "$(MSG_ERRORS)" & exit 1
        pass
