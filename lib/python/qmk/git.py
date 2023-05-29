"""Functions for working with the QMK repo.
"""
from subprocess import DEVNULL
from pathlib import Path

from milc import cli

from qmk.constants import QMK_FIRMWARE


def git_get_version(repo_dir='.', check_dir='.'):
    """Returns the current git version for a repo, or None.
    """
    git_describe_cmd = ['git', 'describe', '--abbrev=6', '--dirty', '--always', '--tags']

    if repo_dir != '.':
        repo_dir = Path('lib') / repo_dir

    if check_dir != '.':
        check_dir = repo_dir / check_dir

    if Path(check_dir).exists():
        git_describe = cli.run(git_describe_cmd, stdin=DEVNULL, cwd=repo_dir)

        if git_describe.returncode == 0:
            return git_describe.stdout.strip()

        else:
            cli.log.warn(f'"{" ".join(git_describe_cmd)}" returned error code {git_describe.returncode}')
            print(git_describe.stderr)
            return None

    return None


def git_get_username():
    """Retrieves user's username from Git config, if set.
    """
    git_username = cli.run(['git', 'config', '--get', 'user.name'])

    if git_username.returncode == 0 and git_username.stdout:
        return git_username.stdout.strip()


def git_get_branch():
    """Returns the current branch for a repo, or None.
    """
    git_branch = cli.run(['git', 'branch', '--show-current'])
    if not git_branch.returncode != 0 or not git_branch.stdout:
        # Workaround for Git pre-2.22
        git_branch = cli.run(['git', 'rev-parse', '--abbrev-ref', 'HEAD'])

    if git_branch.returncode == 0:
        return git_branch.stdout.strip()


def git_get_tag():
    """Returns the current tag for a repo, or None.
    """
    git_tag = cli.run(['git', 'describe', '--abbrev=0', '--tags'])
    if git_tag.returncode == 0:
        return git_tag.stdout.strip()


def git_get_last_log_entry(branch_name):
    """Retrieves the last log entry for the branch being worked on.
    """
    git_lastlog = cli.run(['git', '--no-pager', 'log', '--pretty=format:%ad (%h) -- %s', '--date=iso', '-n1', branch_name])

    if git_lastlog.returncode == 0 and git_lastlog.stdout:
        return git_lastlog.stdout.strip()


def git_get_common_ancestor(branch_a, branch_b):
    """Retrieves the common ancestor between for the two supplied branches.
    """
    git_merge_base = cli.run(['git', 'merge-base', branch_a, branch_b])
    git_branchpoint_log = cli.run(['git', '--no-pager', 'log', '--pretty=format:%ad (%h) -- %s', '--date=iso', '-n1', git_merge_base.stdout.strip()])

    if git_branchpoint_log.returncode == 0 and git_branchpoint_log.stdout:
        return git_branchpoint_log.stdout.strip()


def git_get_remotes():
    """Returns the current remotes for a repo.
    """
    remotes = {}

    git_remote_show_cmd = ['git', 'remote', 'show']
    git_remote_get_cmd = ['git', 'remote', 'get-url']

    git_remote_show = cli.run(git_remote_show_cmd)
    if git_remote_show.returncode == 0:
        for name in git_remote_show.stdout.splitlines():
            git_remote_name = cli.run([*git_remote_get_cmd, name])
            remotes[name.strip()] = {"url": git_remote_name.stdout.strip()}

    return remotes


def git_is_dirty():
    """Returns 1 if repo is dirty, or 0 if clean
    """
    git_diff_staged_cmd = ['git', 'diff', '--quiet']
    git_diff_unstaged_cmd = [*git_diff_staged_cmd, '--cached']

    unstaged = cli.run(git_diff_staged_cmd)
    staged = cli.run(git_diff_unstaged_cmd)

    return unstaged.returncode != 0 or staged.returncode != 0


def git_check_repo():
    """Checks that the .git directory exists inside QMK_HOME.

    This is a decent enough indicator that the qmk_firmware directory is a
    proper Git repository, rather than a .zip download from GitHub.
    """
    dot_git_dir = QMK_FIRMWARE / '.git'

    return dot_git_dir.is_dir()


def git_check_deviation(active_branch):
    """Return True if branch has custom commits
    """
    cli.run(['git', 'fetch', 'upstream', active_branch])
    deviations = cli.run(['git', '--no-pager', 'log', f'upstream/{active_branch}...{active_branch}'])
    return bool(deviations.returncode)


def git_get_ignored_files(check_dir='.'):
    """Return a list of files that would be captured by the current .gitignore
    """
    invalid = cli.run(['git', 'ls-files', '-c', '-o', '-i', '--exclude-from=.gitignore', check_dir])
    if invalid.returncode != 0:
        return []
    return invalid.stdout.strip().splitlines()


def git_get_qmk_hash():
    output = cli.run(['git', 'rev-parse', '--short', 'HEAD'])
    if output.returncode != 0:
        return None

    return output.stdout.strip()
