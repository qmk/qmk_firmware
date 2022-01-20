"""Functions for working with QMK's submodules.
"""
from milc import cli


def status():
    """Returns a dictionary of submodules.

    Each entry is a dict of the form:

        {
            'name': 'submodule_name',
            'status': None/False/True,
            'githash': '<sha-1 hash for the submodule>
        }

    status is None when the submodule doesn't exist, False when it's out of date, and True when it's current
    """
    submodules = {}
    git_cmd = cli.run(['git', 'submodule', 'status'], timeout=30)

    for line in git_cmd.stdout.split('\n'):
        if not line:
            continue

        status = line[0]
        githash, submodule = line[1:].split()[:2]
        submodules[submodule] = {'name': submodule, 'githash': githash}

        if status == '-':
            submodules[submodule]['status'] = None
        elif status == '+':
            submodules[submodule]['status'] = False
        elif status == ' ':
            submodules[submodule]['status'] = True
        else:
            raise ValueError('Unknown `git submodule status` sha-1 prefix character: "%s"' % status)

    return submodules


def update(submodules=None):
    """Update the submodules.

        submodules
            A string containing a single submodule or a list of submodules.
    """
    git_sync_cmd = ['git', 'submodule', 'sync']
    git_update_cmd = ['git', 'submodule', 'update', '--init']

    if submodules is None:
        # Update everything
        git_sync_cmd.append('--recursive')
        git_update_cmd.append('--recursive')
        cli.run(git_sync_cmd, check=True)
        cli.run(git_update_cmd, check=True)

    else:
        if isinstance(submodules, str):
            # Update only a single submodule
            git_sync_cmd.append(submodules)
            git_update_cmd.append(submodules)
            cli.run(git_sync_cmd, check=True)
            cli.run(git_update_cmd, check=True)

        else:
            # Update submodules in a list
            for submodule in submodules:
                cli.run([*git_sync_cmd, submodule], check=True)
                cli.run([*git_update_cmd, submodule], check=True)
