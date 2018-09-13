# QMK Git Conventions, or alternatively, "Git, QMK, and You: Avoiding Common Pitfalls with Contributions"

This document walks through the process of contributing to QMK, detailing some ways to make this task easier.

This document assumes a few things:

1. You have a GitHub account, and have [forked the qmk_firmware repository](getting_started_github.md) to your account.
2. You've [set up your build environment](newbs_getting_started.md?id=environment-setup).

## Your fork's master: Update Often, Commit Never

It is highly recommended for QMK development, regardless of what is being done or where, to keep your `master` branch updated, but ***never*** commit to it. Instead, do all your changes in a development branch and issue pull requests from your branches when you're developing.

To reduce the chances of merge conflicts &mdash; instances where two or more users have edited the same part of a file concurrently &mdash; keep your `master` branch relatively up-to-date, and start any new developments by creating a new branch.

### Updating your master branch

To keep your `master` branch updated, it is recommended to add the QMK Firmware repository as a remote repository in git. To do this, enter `git remote add upstream https://github.com/qmk/qmk_firmware.git` in your Git command line interface. To verify that the repository has been added, run `git remote -v`, which should return the following:

```
$ git remote -v
origin  https://github.com/<your_username>/qmk_firmware.git (fetch)
origin  https://github.com/<your_username>/qmk_firmware.git (push)
upstream        https://github.com/qmk/qmk_firmware.git (fetch)
upstream        https://github.com/qmk/qmk_firmware.git (push)
```

Now that this is done, you can check for updates to the repository by running `git fetch upstream`. This retrieves the list of commits to QMK's `master` branch- nicknamed `upstream` - which then can be compared to your own fork, nicknamed `origin`. To update your fork's master, run:

```
git checkout master
git pull upstream master
git push origin master
```

This switches you to your `master` branch, downloads the current QMK `master` branch, and uploads it to your fork.

## Making Changes

To make changes, create a new branch by entering `git checkout -b dev_branch`, which creates a new branch named `dev_branch` and checks it out. You can name your branch nearly anything you want, though it is recommended to name it something related to the changes you are going to make. By default `git checkout -b` will base your new branch on your currently-checked-out branch. You can base your new branch on an existing branch that is not checked out by adding the name of the existing branch to the command:

```
git checkout -b dev_branch master
```

Now that you have a development branch, open your text editor and make whatever changes you need to make. It is recommended to make many small commits to your branch; that way, any change that causes issues can be more easily traced and undone if needed. To make your changes, edit and save any files that need to be updated, add them to Git's staging area, and then commit them to your branch:

```
git add path/to/updated_file
git commit -m "My commit message."
```

Use descriptive commit messages so you can know what was changed at a glance.

!> If you've changed a lot of files, but all the files are part of the same change, you can use `git add .` to add all the changed files that are in your current directory, rather than having to add each file individually.

## Publishing Your Changes

The last step is to push your changes to your fork. To do this, enter `git push -u origin dev_branch`. This tells git to publish the current state of `dev_branch` to GitHub, and to use `dev_branch` on `origin` as the GitHub-hosted mirror of your local repo (the files on your computer's hard drive). You'll only need to do this once. If you make any more commits to the same branch, you only need to run `git push`; Git will know where to publish your changes.
