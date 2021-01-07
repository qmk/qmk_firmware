"""Run unit/integration tests
"""
import subprocess
import os

from milc import cli


@cli.argument('-i', '--integration', arg_only=True, action='store_true', help='')
@cli.subcommand('Run tests')
def test(cli):
    """Run unit/integration tests
    TODO(unclaimed):
        * [ ] Add ability to specify test filter
    """
    command = ['make', 'test:all']
    env = dict(os.environ)

    if cli.args.integration:
        command = ['make', 'all']
        env = dict(os.environ, **{"KEYBOARD_DIR": "examples"})

    make = subprocess.run(command, env=env)
    return make.returncode
