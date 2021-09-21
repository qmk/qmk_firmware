"""Generate a message to ping people responsible for one or more files.
"""
from pathlib import Path

from milc import cli

from qmk.maintainers import maintainers


@cli.argument('--pr', type=int, arg_only=True, help="PR to send ping to (optional)")
@cli.argument('--owner', default='qmk', arg_only=True, help="Owner for the repo (Default: qmk)")
@cli.argument('--repo', default='qmk_firmware', arg_only=True, help="Repo to send pings to (Default: qmk_firmware)")
@cli.argument("files", type=Path, arg_only=True, nargs='*', help="File to ping maintainers for.")
@cli.subcommand("Ping the maintainers and request reviews for one or more files.")
def ping_maintainers(cli):
    """Ping the maintainers for one or more files.
    """
    github_maintainers = set()
    github_teams = set()

    for file in cli.args.files:
        for maintainer in maintainers(file):
            if '/' in maintainer:
                github_teams.add(maintainer)
            else:
                github_maintainers.add(maintainer)

    if cli.args.pr:
        from ghapi.all import GhApi

        ghapi = GhApi(owner=cli.args.owner, repo=cli.args.repo)
        pr = ghapi.pulls(cli.args.pr)

        if not pr.draft:
            for team in pr.requested_teams:
                team_name = f'@{cli.args.owner}/{team.slug}'

                if team_name in github_teams:
                    cli.log.info('Found %s in reviews already, skipping', team_name)
                    github_teams.remove(team_name)

            for team in github_teams:
                cli.log.info('Requesting review from team %s', team.split('/', 1)[1])
                ghapi.pulls.request_reviewers(pull_number=cli.args.pr, team_reviewers=team.split('/', 1)[1])

            if github_maintainers:
                ghapi.issues.create_comment(cli.args.pr, f'If you were pinged by this comment you have one or more files being changed by this PR: {" ".join(sorted(github_maintainers))}')

    else:
        print(f'Team Reviews: {" ".join(sorted(github_teams))}')
        print(f'Individual Reviews: {" ".join(sorted(github_maintainers))}')
