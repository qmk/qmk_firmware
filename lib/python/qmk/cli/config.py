"""Read and write configuration settings
"""
import os
import subprocess

from milc import cli


def print_config(section, key):
    """Print a single config setting to stdout.
    """
    cli.echo('%s.%s{fg_cyan}={fg_reset}%s', section, key, cli.config[section][key])


@cli.argument('-ro', '--read-only', action='store_true', help='Operate in read-only mode.')
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
        # Walk the config tree
        for section in cli.config:
            for key in cli.config[section]:
                print_config(section, key)

        return True

    # Process config_tokens
    save_config = False

    for argument in cli.args.configs:
        # Split on space in case they quoted multiple config tokens
        for config_token in argument.split(' '):
            # Extract the section, config_key, and value to write from the supplied config_token.
            if '=' in config_token:
                key, value = config_token.split('=')
            else:
                key = config_token
                value = None

            if '.' in key:
                section, config_key = key.split('.', 1)
            else:
                section = key
                config_key = None

            # Validation
            if config_key and '.' in config_key:
                cli.log.error('Config keys may not have more than one period! "%s" is not valid.', key)
                return False

            # Do what the user wants
            if section and config_key and value:
                # Write a config key
                log_string = '%s.%s{fg_cyan}:{fg_reset} %s {fg_cyan}->{fg_reset} %s'
                if cli.args.read_only:
                    log_string += ' {fg_red}(change not written)'

                cli.echo(log_string, section, config_key, cli.config[section][config_key], value)

                if not cli.args.read_only:
                    if value == 'None':
                        del cli.config[section][config_key]
                    else:
                        cli.config[section][config_key] = value
                    save_config = True

            elif section and config_key:
                # Display a single key
                print_config(section, config_key)

            elif section:
                # Display an entire section
                for key in cli.config[section]:
                    print_config(section, key)

    # Ending actions
    if save_config:
        cli.save_config()

    return True
