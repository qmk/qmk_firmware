"""Export the initial list of PRs associated with a `develop` merge to `master`.
"""
import os
import re
from pathlib import Path
from subprocess import DEVNULL

from milc import cli

cache_timeout = 7 * 86400
fix_expr = re.compile(r'fix', flags=re.IGNORECASE)
clean1_expr = re.compile(r'\[(develop|keyboard|keymap|core|cli|bug|docs|feature)\]', flags=re.IGNORECASE)
clean2_expr = re.compile(r'^(develop|keyboard|keymap|core|cli|bug|docs|feature):', flags=re.IGNORECASE)


def _get_pr_info(cache, gh, pr_num):
    pull = cache.get(f'pull:{pr_num}')
    if pull is None:
        print(f'Retrieving info for PR #{pr_num}')
        pull = gh.pulls.get(owner='qmk', repo='qmk_firmware', pull_number=pr_num)
        cache.set(f'pull:{pr_num}', pull, cache_timeout)
    return pull


def _try_open_cache(cli):
    # These dependencies are manually handled because people complain. Fun.
    try:
        from sqlite_cache.sqlite_cache import SqliteCache
    except ImportError:
        return None

    cache_loc = Path(cli.config_file).parent
    return SqliteCache(cache_loc)


def _get_github():
    try:
        from ghapi.all import GhApi
    except ImportError:
        return None

    return GhApi()


@cli.argument('-f', '--from-ref', default='0.11.0', help='Git revision/tag/reference/branch to begin search')
@cli.argument('-b', '--branch', default='upstream/develop', help='Git branch to iterate (default: "upstream/develop")')
@cli.subcommand('Creates the develop PR list.', hidden=False if cli.config.user.developer else True)
def generate_develop_pr_list(cli):
    """Retrieves information from GitHub regarding the list of PRs associated
    with a merge of `develop` branch into `master`.

    Requires environment variable GITHUB_TOKEN to be set.
    """

    if 'GITHUB_TOKEN' not in os.environ or os.environ['GITHUB_TOKEN'] == '':
        cli.log.error('Environment variable "GITHUB_TOKEN" is not set.')
        return 1

    cache = _try_open_cache(cli)
    gh = _get_github()

    git_args = ['git', 'rev-list', '--oneline', '--no-merges', '--reverse', f'{cli.args.from_ref}...{cli.args.branch}', '^upstream/master']
    commit_list = cli.run(git_args, capture_output=True, stdin=DEVNULL)

    if cache is None or gh is None:
        cli.log.error('Missing one or more dependent python packages: "ghapi", "python-sqlite-cache"')
        return 1

    pr_list_bugs = []
    pr_list_dependencies = []
    pr_list_core = []
    pr_list_keyboards = []
    pr_list_keyboard_fixes = []
    pr_list_cli = []
    pr_list_others = []

    def _categorise_commit(commit_info):
        def fix_or_normal(info, fixes_collection, normal_collection):
            if "bug" in info['pr_labels'] or fix_expr.search(info['title']):
                fixes_collection.append(info)
            else:
                normal_collection.append(info)

        if "dependencies" in commit_info['pr_labels']:
            fix_or_normal(commit_info, pr_list_bugs, pr_list_dependencies)
        elif "core" in commit_info['pr_labels']:
            fix_or_normal(commit_info, pr_list_bugs, pr_list_core)
        elif "keyboard" in commit_info['pr_labels'] or "keymap" in commit_info['pr_labels'] or "via" in commit_info['pr_labels']:
            fix_or_normal(commit_info, pr_list_keyboard_fixes, pr_list_keyboards)
        elif "cli" in commit_info['pr_labels']:
            fix_or_normal(commit_info, pr_list_bugs, pr_list_cli)
        else:
            fix_or_normal(commit_info, pr_list_bugs, pr_list_others)

    git_expr = re.compile(r'^(?P<hash>[a-f0-9]+) (?P<title>.*) \(#(?P<pr>[0-9]+)\)$')
    for line in commit_list.stdout.split('\n'):
        match = git_expr.search(line)
        if match:
            pr_info = _get_pr_info(cache, gh, match.group("pr"))
            commit_info = {'hash': match.group("hash"), 'title': match.group("title"), 'pr_num': int(match.group("pr")), 'pr_labels': [label.name for label in pr_info.labels.items]}
            _categorise_commit(commit_info)

    def _dump_commit_list(name, collection):
        if len(collection) == 0:
            return
        print("")
        print(f"{name}:")
        for commit in sorted(collection, key=lambda x: x['pr_num']):
            title = clean1_expr.sub('', clean2_expr.sub('', commit['title'])).strip()
            pr_num = commit['pr_num']
            print(f'* {title} ([#{pr_num}](https://github.com/qmk/qmk_firmware/pull/{pr_num}))')

    _dump_commit_list("Core", pr_list_core)
    _dump_commit_list("CLI", pr_list_cli)
    _dump_commit_list("Submodule updates", pr_list_dependencies)
    _dump_commit_list("Keyboards", pr_list_keyboards)
    _dump_commit_list("Keyboard fixes", pr_list_keyboard_fixes)
    _dump_commit_list("Others", pr_list_others)
    _dump_commit_list("Bugs", pr_list_bugs)
