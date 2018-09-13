# Best Practices

## Or, "How I Learned to Stop Worrying and Love Git."

This document aims to instruct novices in the best ways to have a smooth experience in contributing to QMK. We will walk through the process of contributing to QMK, detailing some ways to make this task easier, and then later we'll break some things in order to teach you how to fix them.

This document assumes a few things:

1. You have a GitHub account, and have [forked the qmk_firmware repository](getting_started_github.md) to your account.
2. You've [set up your build environment](newbs_getting_started.md?id=environment-setup).

## Your fork's master: Update Often, Commit Never

It is highly recommended for QMK development, regardless of what is being done or where, to keep your `master` branch updated, but ***never*** commit to it. Instead, do all your changes in a development branch and issue pull requests from your branches when you're developing.

To reduce the chances of merge conflicts &mdash; instances where two or more users have edited the same part of a file concurrently &mdash; keep your `master` branch relatively up-to-date, and start any new developments by creating a new branch.

### Updating your master branch

To keep your `master` branch updated, it is recommended to add the QMK Firmware repository ("repo") as a remote repository in git. To do this, enter

```
git remote add upstream https://github.com/qmk/qmk_firmware.git
````

in your Git command line interface. To verify that the repository has been added, run `git remote -v`, which should return the following:

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

## Making Changes

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

## Publishing Your Changes

The last step is to push your changes to your fork. To do this, enter `git push`. Git now publishes the current state of `dev_branch` to your fork.
