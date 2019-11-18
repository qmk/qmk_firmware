# Best Practices

## Or, "How I Learned to Stop Worrying and Love Git."

This document aims to instruct novices in the best ways to have a smooth experience in contributing to QMK. We will walk through the process of contributing to QMK, detailing some ways to make this task easier, and then later we'll break some things in order to teach you how to fix them.

This document assumes a few things:

1. You have a GitHub account, and have [forked the qmk_firmware repository](getting_started_github.md) to your account.
2. You've [set up your build environment](newbs_getting_started.md#set-up-your-environment).


## Your fork's master: Update Often, Commit Never

It is highly recommended for QMK development, regardless of what is being done or where, to keep your `master` branch updated, but ***never*** commit to it. Instead, do all your changes in a development branch and issue pull requests from your branches when you're developing.

To reduce the chances of merge conflicts &mdash; instances where two or more users have edited the same part of a file concurrently &mdash; keep your `master` branch relatively up-to-date, and start any new developments by creating a new branch.

### Updating your master branch

To keep your `master` branch updated, it is recommended to add the QMK Firmware repository ("repo") as a remote repository in git. To do this, open your Git command line interface and enter:

```
git remote add upstream https://github.com/qmk/qmk_firmware.git
```

To verify that the repository has been added, run `git remote -v`, which should return the following:

```
$ git remote -v
origin  https://github.com/<your_username>/qmk_firmware.git (fetch)
origin  https://github.com/<your_username>/qmk_firmware.git (push)
upstream        https://github.com/qmk/qmk_firmware.git (fetch)
upstream        https://github.com/qmk/qmk_firmware.git (push)
```

Now that this is done, you can check for updates to the repo by running `git fetch upstream`. This retrieves the branches and tags &mdash; collectively referred to as "refs" &mdash; from the QMK repo, which now has the nickname `upstream`. We can now compare the data on our fork `origin` to that held by QMK.

To update your fork's master, run the following, hitting the Enter key after each line:

```
git checkout master
git fetch upstream
git pull upstream master
git push origin master
```

This switches you to your `master` branch, retrieves the refs from the QMK repo, downloads the current QMK `master` branch to your computer, and then uploads it to your fork.

### Making Changes

To make changes, create a new branch by entering:

```
git checkout -b dev_branch
git push --set-upstream origin dev_branch
```

This creates a new branch named `dev_branch`, checks it out, and then saves the new branch to your fork. The `--set-upstream` argument tells git to use your fork and the `dev_branch` branch every time you use `git push` or `git pull` from this branch. It only needs to be used on the first push; after that, you can safely use `git push` or `git pull`, without the rest of the arguments.

!> With `git push`, you can use `-u` in place of `--set-upstream` &mdash; `-u` is an alias for `--set-upstream`.

You can name your branch nearly anything you want, though it is recommended to name it something related to the changes you are going to make.

By default `git checkout -b` will base your new branch on the branch that is checked out. You can base your new branch on an existing branch that is not checked out by adding the name of the existing branch to the command:

```
git checkout -b dev_branch master
```

Now that you have a development branch, open your text editor and make whatever changes you need to make. It is recommended to make many small commits to your branch; that way, any change that causes issues can be more easily traced and undone if needed. To make your changes, edit and save any files that need to be updated, add them to Git's *staging area*, and then commit them to your branch:

```
git add path/to/updated_file
git commit -m "My commit message."
```

`git add` adds files that have been changed to Git's *staging area*, which is Git's "loading zone." This contains the changes that are going to be *committed* by `git commit`, which saves the changes to the repo. Use descriptive commit messages so you can know what was changed at a glance.

!> If you've changed a lot of files, but all the files are part of the same change, you can use `git add .` to add all the changed files that are in your current directory, rather than having to add each file individually.

### Publishing Your Changes

The last step is to push your changes to your fork. To do this, enter `git push`. Git now publishes the current state of `dev_branch` to your fork.


## Resolving Merge Conflicts

Sometimes when your work in a branch takes a long time to complete, changes that have been made by others conflict with changes you have made to your branch when you open a pull request. This is called a *merge conflict*, and is what happens when multiple people edit the same parts of the same files.

### Rebasing Your Changes

A *rebase* is Git's way of taking changes that were applied at one point, reversing them, and then applying the same changes to another point. In the case of a merge conflict, you can rebase your branch to grab the changes that were made between when you created your branch and the present time.

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
