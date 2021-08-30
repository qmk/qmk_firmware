"""Ensure text files have the proper line endings.
"""
from subprocess import CalledProcessError

from milc import cli


@cli.subcommand("Ensure text files have the proper line endings.", hidden=True)
def format_text(cli):
    """Ensure text files have the proper line endings.
    """
    try:
        file_list_cmd = cli.run(['git', 'ls-files', '-z'], check=True)
    except CalledProcessError as e:
        cli.log.error('Could not get file list: %s', e)
        exit(1)
    except Exception as e:
        cli.log.error('Unhandled exception: %s: %s', e.__class__.__name__, e)
        cli.log.exception(e)
        exit(1)

    dos2unix = cli.run(['xargs', '-0', 'dos2unix'], stdin=None, input=file_list_cmd.stdout)

    if dos2unix.returncode != 0:
        print(dos2unix.stderr)

    return dos2unix.returncode
