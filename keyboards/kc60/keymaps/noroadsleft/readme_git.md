# @noroadsleft's Git aliases

[Return to the directory index.](./)

```
[alias]
    # change branches
    co = checkout

    # Return the last five commits on the branch, in a more compact format
    hist = log --pretty=format:\"%C(yellow)%h%Creset %Cgreen%ad%Creset%n   %w(100,0,3)%s%d [%an]\" --graph --date=iso-local -n 5

    # Short-form status
    st = "!git status --short"

    # Returns the name of the current branch
    branch-name = "!git rev-parse --abbrev-ref HEAD"

    # short-form of the above
    bn = "!git branch-name"

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

    # Compare local master repo to its upstream branch. If anything is returned, local master is out-of-sync.
    cm = "diff master upstream/master --compact-summary"
```
