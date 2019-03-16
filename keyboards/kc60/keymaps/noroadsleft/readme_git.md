# @noroadsleft's Git aliases

[Return to the directory index.](./)

```
[alias]
    # Change branches
    co = checkout
    cob = checkout -b

    # Cherry Pick
    cp = cherry-pick

    # Check out a Pull Request
    cop = "!f() { git fetch upstream pull/$1/head:pr/$1; git checkout pr/$1; }; f"

    # Sync master branch
    sync = !git checkout master && git fetch upstream 2> /dev/null && git pull -n upstream master && git push origin master

    # Return the abbreviated SHA-1 of the last three commits, oldest to newest
    rl = rev-list -n 3 --abbrev-commit --reverse HEAD

    # Add remote repo (for sending PRs to other forks, or checking out someone else's developments)
    ar = "!f() { git remote add $1 https://github.com/$2/qmk_firmware.git; }; f"

    # Return the last five commits on the branch, in a more compact format
    hist  = log --pretty=format:\"%C(yellow)%h%Creset %Cgreen%ad%Creset %Cblue[%an%Cgreen% GK%Cblue]%C(yellow)%d%Creset%n  %w(100,0,2)%s%n\" --graph --date=iso-local -n 5
    histt = log --pretty=format:\"* %C(yellow)%h%Creset %<(58,trunc)%s %Cblue%>(18,trunc)%an%Cgreen% G?%Creset @ %Cgreen%ad%Creset\" --date=iso-local -n 5
    histb = log --reverse --pretty=format:\"- %Cblue%>(20,trunc)%an %Creset%<(97,trunc)%s\" --date=iso-local -n 5

    # Follow a file's filename history
    follow = log --follow --name-only --pretty=format:\"%C(yellow)commit %H%Creset%d\nAuthor: %an <%ae>\nDate:   %ad%n%n    %s%n\" --date=iso-local

    # compact diff
    df = "diff --compact-summary"

    # List all the files changed in a commit
    dt = "diff-tree --no-commit-id --name-only -r"

    # Short-form status
    st = "!git status --short --untracked-files=no"

    # Returns the name of the current branch
    branch-name = "!git rev-parse --abbrev-ref HEAD"
    bn          = "!git branch-name"                 # short-form of the above

    # Compare commit counts between current branch and QMK master
    cc = "!f() { git fetch upstream; echo \"[0;32m$(git branch-name)[0m vs. [0;31mupstream/master[0m\"; git rev-list --left-right --count $(git branch-name)...upstream/master; }; f"

    # Push to origin repo
    po = "push origin $(git branch-name)"

    # List the stashes
    sl = "stash list"

    # Unstage a file
    unstage = "reset HEAD"

    # Restore a file to the state it was in when checked out
    restore = "checkout --"

    # Compare local master repo to its upstream branch. If anything is returned, local branch has diverged from upstream.
    cm = "!f() { git fetch upstream master; git diff $(git branch-name) upstream/master --compact-summary; }; f"
    cml = "!f() { git fetch upstream master; git diff $(git branch-name) upstream/master; }; f"

    # Delete a branch from local and remote
    del-branch = "!f() { git branch -d $1; git push origin :$1; git fetch -p origin; }; f"

    # Rebase with signatures
    rbv = rebase --exec 'git commit --amend --no-edit -n -S' -i

    # Force push without overwriting established history
    pushf = push --force-with-lease


```
