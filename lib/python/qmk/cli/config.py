"""Format C code according to QMK's style.
"""
import os
import subprocess

from milc import cli


@cli.argument('configs', nargs='*', arg_only=True, help='Configuration options to read or write.')
@cli.subcommand("Read and write config settings.")
def config(cli):
    """Read and write config settings.

    This script iterates over the config_tokens supplied as argument. Each config_token has the following form:

        section[.key][=value]

    If only a section (EG 'compile') is supplied all keys for that section will be displayed.

    If section.key is supplied the value for that single key will be displayed.

    If section.key=value is supplied the value for that single key will be set.

    No validation is done to ensure that the supplied section.key is actually used by qmk scripts.
    """
    for config_token in cli.args.configs:
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
            cli.log.error('Config keys may not have more than one period! "%s" is not valid.', config_key)
            return False

        # Do stuff
        if section and config_key and value:
            cli.log.info('Writing %s.%s -> %s', section, config_key, value)
            # FIXME: Implement
        elif section and config_key:
            cli.log.info('Displaying a single key.')
            # FIXME: Implement
        elif section:
            cli.log.info('Displaying an entire section.')
            # FIXME: Implement


    cli.log.info('sup?')
