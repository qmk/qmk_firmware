"""QMK Python Hello World

This is an example QMK CLI script.
"""
from milc import cli


@cli.argument('-n', '--name', default='World', help='Name to greet.')
@cli.entrypoint('QMK Python Hello World.')
def main(cli):
    cli.echo('Hello, %s!', cli.config.general.name)
