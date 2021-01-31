"""Generate the changelog for develop.

This requires the github module:
    pip3 install PyGithub
"""
from datetime import datetime
from pathlib import Path

import yaml
from milc import cli
from github import Github


def pr_body(text):
    """Returns the description from a PR body.
    """
    lines = []
    found = False

    for line in text.split('\n'):
        if line.startswith('## Description'):
            found = True
            continue

        if line.startswith('## Issues Fixed'):
            found = True
            lines.append('##### Issues Fixed or Closed by This PR')
            continue

        if not found:
            continue

        if line.startswith('##'):
            found = False
            continue

        lines.append(line.rstrip())

    new_text = '\n'.join(lines)

    return new_text.strip()


@cli.subcommand('Get a list of PRs for develop.', hidden=True)
def generate_develop_changelog(cli):
    # Setup the github api
    hub_config = yaml.safe_load(Path('~/.config/hub').expanduser().open())
    github_token = hub_config['github.com'][0]['oauth_token']
    github = Github(github_token)

    # Find our branchpoint
    master_revs = cli.run(['git', 'rev-list', '--first-parent', 'master'])
    develop_revs = cli.run(['git', 'rev-list', '--first-parent', 'develop'])
    master_commits = master_revs.stdout.split('\n')
    develop_commits = develop_revs.stdout.split('\n')

    first_commit = None
    for commit in develop_commits:
        if commit in master_commits:
            branchpoint = commit
            break

    if not branchpoint:
        cli.log.error('Could not find branchpoint!')
        exit(1)

    # Find the time of our branchpoint
    repo = github.get_repo('qmk/qmk_firmware')
    bp = repo.get_commit(branchpoint)
    last_modified = datetime.strptime(bp.last_modified, '%a, %d %b %Y %H:%M:%S %Z')

    # Get a list of PR's targetting develop since last_modified
    for pr in repo.get_pulls(state='closed', base='develop'):
        if pr.merged and pr.merged_at > last_modified:
            print(f'#### {pr.title} ([#{pr.number}](https://github.com/qmk/qmk_firmware/pull/{pr.number}))')
            print()
            print(pr_body(pr.body))
