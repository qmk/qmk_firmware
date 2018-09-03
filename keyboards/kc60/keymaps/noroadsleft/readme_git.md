# @noroadsleft's Git aliases

[Return to the directory index.](./)

```
[alias]
    # change branches
    co = checkout
    cob = checkout -b

    # sync master
    sync = "!f() { if [ $(git branch-name) != "master" ]; then git checkout master; fi; git pull upstream master; git push origin master; }; f"

    # Return the last five commits on the branch, in a more compact format
    hist = log --pretty=format:\"%C(yellow)%h%Creset %Cgreen%ad%Creset%n   %w(100,0,3)%s%d [%an]%n\" --graph --date=iso-local -n 5
    histm = log --pretty=format:\"%C(yellow)%h%Creset %w(100,0,3)%s%d [%an]\" --graph --date=iso-local -n 5
    histt = log --pretty=format:\"%C(yellow)%h%Creset %<(88,trunc)%s [%an]\" --graph --date=iso-local -n 5
    histb = log --reverse --pretty=format:\"- %<(98,trunc)%s [%an]\" --date=iso-local -n 5

    # compact diff
    df = "diff --compact-summary"

    # Short-form status
    st = "!git status --short"

    # Returns the name of the current branch
    branch-name = "!git rev-parse --abbrev-ref HEAD"

    # short-form of the above
    bn = "!git branch-name"

    po = "push origin ($(git branch-name))"

    # List the stashes
    sl = "stash list"

    # Show the contents of a numbered stash
    # Syntax:
    #   git st-show <int>
    st-show = "!f() { git stash show stash@{$1} -p; }; f"

    # Apply a stash, without deleting it from the list of stashes
    # Syntax:
    #   git st-copy <int>
    st-copy = "!f() { git stash apply stash@{$1}; }; f"

    # Unstage a file
    unstage = "reset HEAD"

    # Restore a file to the state it was in when checked out
    restore = "checkout --"

    # Compare local master repo to its upstream branch. If anything is returned, local branch has diverged from upstream.
    cm = "!f() { git fetch upstream master; git diff $(git branch-name) upstream/master --compact-summary; }; f"
    cml = "!f() { git fetch upstream master; git diff $(git branch-name) upstream/master; }; f"
```
