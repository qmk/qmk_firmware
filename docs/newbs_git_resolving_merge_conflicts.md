# Resolving Merge Conflicts

Sometimes when your work in a branch takes a long time to complete, changes that have been made by others conflict with changes you have made to your branch when you open a pull request. This is called a *merge conflict*, and is what happens when multiple people edit the same parts of the same files.

::: tip
This document builds upon the concepts detailed in [Your Fork's Master: Update Often, Commit Never](newbs_git_using_your_master_branch). If you are not familiar with that document, please read it first, then return here.
:::

## Rebasing Your Changes

A *rebase* is Git's way of taking changes that were applied at one point in the commit history, reversing them, and then applying the same changes at another point. In the case of a merge conflict, you can rebase your branch to grab the changes that were made between when you created your branch and the present time.

To start, run the following:

```
git fetch upstream
git rev-list --left-right --count HEAD...upstream/master
```

The `git rev-list` command entered here returns the number of commits that differ between the current branch and QMK's master branch. We run `git fetch` first to make sure we have the refs that represent the current state of the upstream repo. The output of the `git rev-list` command entered returns two numbers:

```
$ git rev-list --left-right --count HEAD...upstream/master
7       35
```

The first number represents the number of commits on the current branch since it was created, and the second number is the number of commits made to `upstream/master` since the current branch was created, and thus, the changes that are not recorded in the current branch.

Now that the current states of both the current branch and the upstream repo are known, we can start a rebase operation:

```
git rebase upstream/master
```

This tells Git to undo the commits on the current branch, and then reapply them against QMK's master branch.

```
$ git rebase upstream/master
First, rewinding head to replay your work on top of it...
Applying: Commit #1
Using index info to reconstruct a base tree...
M       conflicting_file_1.txt
Falling back to patching base and 3-way merge...
Auto-merging conflicting_file_1.txt
CONFLICT (content): Merge conflict in conflicting_file_1.txt
error: Failed to merge in the changes.
hint: Use 'git am --show-current-patch' to see the failed patch
Patch failed at 0001 Commit #1

Resolve all conflicts manually, mark them as resolved with
"git add/rm <conflicted_files>", then run "git rebase --continue".
You can instead skip this commit: run "git rebase --skip".
To abort and get back to the state before "git rebase", run "git rebase --abort".
```

This tells us that we have a merge conflict, and gives the name of the file with the conflict. Open the conflicting file in your text editor, and somewhere in the file, you'll find something like this:

```
<<<<<<< HEAD
<p>For help with any issues, email us at support@webhost.us.</p>
=======
<p>Need help? Email support@webhost.us.</p>
>>>>>>> Commit #1
```

The line `<<<<<<< HEAD` marks the beginning of a merge conflict, and the `>>>>>>> Commit #1` line marks the end, with the conflicting sections separated by `=======`. The part on the `HEAD` side is from the QMK master version of the file, and the part marked with the commit message is from the current branch and commit.

Because Git tracks *changes to files* rather than the contents of the files directly, if Git can't find the text that was in the file previous to the commit that was made, it won't know how to edit the file. Re-editing the file will solve the conflict. Make your changes, and then save the file.

```
<p>Need help? Email support@webhost.us.</p>
```

Now run:

```
git add conflicting_file_1.txt
git rebase --continue
```

Git logs the changes to the conflicting file, and continues applying the commits from our branch until it reaches the end.
