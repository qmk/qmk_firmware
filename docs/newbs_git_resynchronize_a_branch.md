# Resynchronizing an Out-of-Sync Git Branch

Suppose you have committed to your `master` branch, and now need to update your QMK repository. You could `git pull` QMK's `master` branch into your own, but GitHub will tell you that your commit is a number of commits ahead of `qmk:master`, which can create issues if you want to make a pull request to QMK.

!> This document builds upon the concepts detailed in [Best Practices](newbs_best_practices.md). If you are not familiar with that document, please read it first, then return here.

## Backing Up the Changes on Your Own Master Branch (Optional)

No one wants to lose work if it can be helped. If you want to save the changes you've already made to your `master` branch, the simplest way to do so is to simply rename your branch:

```sh
$ git branch -m old_master  # Renames the current branch
```

Now you have a branch named `old_master`, but no `master` branch. To create a new `master` branch, enter:

```sh
$ git branch master  # Creates a new branch
```

When you create a branch, the new branch matches the state of the current branch.

Now it's time to resynchronize your `master` branch. First, it needs to be checked out:

```sh
$ git checkout master
```

?> You can use `git checkout -b master` to create a new branch named `master`, in place of running `git branch master` followed by `git checkout master`.

## Resynchronizing Your Branch

For this step, you'll want to have the upstream repository configured as a remote in Git. To check your configured remotes, run `git remote -v`, which should return something similar to:

```sh
QMKuser ~/qmk_firmware (master)
$ git remote -v
origin  https://github.com/<your_username>/qmk_firmware.git (fetch)
origin  https://github.com/<your_username>/qmk_firmware.git (push)
upstream        https://github.com/qmk/qmk_firmware.git (fetch)
upstream        https://github.com/qmk/qmk_firmware.git (push)
```

If you only see one fork referenced:

```sh
QMKuser ~/qmk_firmware (master)
$ git remote -v
origin  https://github.com/qmk/qmk_firmware.git (fetch)
origin  https://github.com/qmk/qmk_firmware.git (push)
```

add a new remote with:

```sh
$ git remote add upstream https://github.com/qmk/qmk_firmware.git
```

Then, redirect the `origin` remote to your own fork with:

```sh
$ git remote set-url origin https://github.com/<your_username>/qmk_firmware.git
```

Now that you have both remotes configured, run `git fetch upstream` to update the references for the upstream repository, which is QMK's. At this point, run `git reset --hard upstream/master` to resynchronize your branch to QMK's.

This will update the repository on your computer, but your GitHub fork will still be out-of-sync. To resynchronize your fork on GitHub, you need to push to your fork, instructing Git to override any remote changes that are not reflected in your local repository. To do this, run `git push --force-with-lease`.

!> **DO NOT** run `git push --force-with-lease` on a fork to which other users post commits. This will erase their commits.

Now your GitHub fork, your local files, and QMK's repository are all the same. From here you can make further needed changes ([use a branch!](.md)) and post them as normal.
