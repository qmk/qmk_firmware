"""Generate a message to ping people responsible for one or more files.
"""
from pathlib import Path

from milc import cli

from qmk.maintainers import maintainers


@cli.argument("files", type=Path, arg_only=True, nargs='*', help="File to ping maintainers for.")
@cli.subcommand("Ping the maintainers for one or more files.")
def ping_maintainers(cli):
    """List the maintainers for one or more files.
    """
    github_maintainers = set()

    for file in cli.args.files:
        for maintainer in maintainers(file):
            if maintainer != 'qmk/collaborators':
                github_maintainers.add(maintainer)

    if github_maintainers:
        print(f'If you were pinged by this comment you have one or more files being changed by this PR: {" ".join(sorted(github_maintainers))}')
