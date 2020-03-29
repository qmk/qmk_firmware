"""Read and write configuration settings
"""
from milc import cli


def print_config(section, key):
    """Print a single config setting to stdout.
    """
    cli.echo('%s.%s{fg_cyan}={fg_reset}%s', section, key, cli.config[section][key])


def show_config():
    """Print the current configuration to stdout.
    """
    for section in cli.config:
        for key in cli.config[section]:
            print_config(section, key)


def parse_config_token(config_token):
    """Split a user-supplied configuration-token into its components.
    """
    section = option = value = None

    if '=' in config_token and '.' not in config_token:
        cli.log.error('Invalid configuration token, the key must be of the form <section>.<option>: %s', config_token)
        return section, option, value

    # Separate the key (<section>.<option>) from the value
    if '=' in config_token:
        key, value = config_token.split('=')
    else:
        key = config_token

    # Extract the section and option from the key
    if '.' in key:
        section, option = key.split('.', 1)
    else:
        section = key

    return section, option, value


def set_config(section, option, value):
    """Set a config key in the running config.
    """
    log_string = '%s.%s{fg_cyan}:{fg_reset} %s {fg_cyan}->{fg_reset} %s'
    if cli.args.read_only:
        log_string += ' {fg_red}(change not written)'

    cli.echo(log_string, section, option, cli.config[section][option], value)

    if not cli.args.read_only:
        if value == 'None':
            del cli.config[section][option]
        else:
            cli.config[section][option] = value


@cli.argument('-ro', '--read-only', arg_only=True, action='store_true', help='Operate in read-only mode.')
@cli.argument('configs', nargs='*', arg_only=True, help='Configuration options to read or write.')
@cli.subcommand("Read and write configuration settings.")
def config(cli):
    """Read and write config settings.

    This script iterates over the config_tokens supplied as argument. Each config_token has the following form:

        section[.key][=value]

    If only a section (EG 'compile') is supplied all keys for that section will be displayed.

    If section.key is supplied the value for that single key will be displayed.

    If section.key=value is supplied the value for that single key will be set.

    If section.key=None is supplied the key will be deleted.

    No validation is done to ensure that the supplied section.key is actually used by qmk scripts.
    """
    if not cli.args.configs:
        return show_config()

    # Process config_tokens
    save_config = False

    for argument in cli.args.configs:
        # Split on space in case they quoted multiple config tokens
        for config_token in argument.split(' '):
            section, option, value = parse_config_token(config_token)

            # Validation
            if option and '.' in option:
                cli.log.error('Config keys may not have more than one period! "%s" is not valid.', config_token)
                return False

            # Do what the user wants
            if section and option and value:
                # Write a configuration option
                set_config(section, option, value)
                if not cli.args.read_only:
                    save_config = True

            elif section and option:
                # Display a single key
                print_config(section, option)

            elif section:
                # Display an entire section
                for key in cli.config[section]:
                    print_config(section, key)

    # Ending actions
    if save_config:
        cli.save_config()

    return True
