"""QMK Python Hello World

This is an example QMK CLI script.
"""
from milc import cli


@cli.argument('-n', '--name', default='World', help='Name to greet.')
@cli.subcommand('QMK Hello World.')
def hello(cli):
    """Log a friendly greeting.
    """
    cli.log.info('Hello, %s!', cli.config.hello.name)
