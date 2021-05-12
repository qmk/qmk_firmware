# Breaking Changes

This document describes QMK's Breaking Change process. A Breaking Change is any change which modifies how QMK behaves in a way that in incompatible or potentially dangerous. We limit these changes so that users can have confidence that updating their QMK tree will not break their keymaps.

The breaking change period is when we will merge PR's that change QMK in dangerous or unexpected ways. There is a built-in period of testing so we are confident that any problems caused are rare or unable to be predicted.

## What has been included in past Breaking Changes?

* [2021 Feb 27](ChangeLog/20210227.md)
* [2020 Nov 28](ChangeLog/20201128.md)
* [2020 Aug 29](ChangeLog/20200829.md)
* [2020 May 30](ChangeLog/20200530.md)
* [2020 Feb 29](ChangeLog/20200229.md)
* [2019 Aug 30](ChangeLog/20190830.md)

## When is the next Breaking Change?

The next Breaking Change is scheduled for May 29, 2021.

### Important Dates

* [x] 2021 Feb 27 - `develop` is created. Each push to `master` is subsequently merged to `develop`
* [ ] 2021 May 01 - `develop` closed to new PR's.
* [ ] 2021 May 01 - Call for testers.
* [ ] 2021 May 27 - `master` is locked, no PR's merged.
* [ ] 2021 May 29 - Merge `develop` to `master`.
* [ ] 2021 May 29 - `master` is unlocked. PR's can be merged again.

## What changes will be included?

To see a list of breaking change candidates you can look at the [`breaking_change` label](https://github.com/qmk/qmk_firmware/pulls?q=is%3Aopen+label%3Abreaking_change+is%3Apr). New changes might be added between now and when `develop` is closed, and a PR with that label applied is not guaranteed to be merged.

If you want your breaking change to be included in this round you need to create a PR with the `breaking_change` label and have it accepted before `develop` closes. After `develop` closes no new breaking changes will be accepted.

Criteria for acceptance:

* PR is complete and ready to merge
* PR has a ChangeLog

# Checklists

This section documents various processes we use when running the Breaking Changes process.

## Creating the `develop` branch

This happens immediately after the previous `develop` branch is merged.

* `qmk_firmware` git commands
    * [ ] `git checkout master`
    * [ ] `git pull --ff-only`
    * [ ] `git checkout -b develop`
    * [ ] Edit `readme.md`
        * [ ] Add a big notice at the top that this is a testing branch.
        * [ ] Include a link to this document
    * [ ] `git commit -m 'Branch point for <DATE> Breaking Change'`
    * [ ] `git tag breakpoint_<YYYY>_<MM>_<DD>`
    * [ ] `git tag <next_version>` # Prevent the breakpoint tag from confusing version incrementing
    * [ ] `git push origin develop`
    * [ ] `git push --tags`

## 4 Weeks Before Merge

* `develop` is now closed to new PR's, only fixes for current PR's may be merged
* Post call for testers
    * [ ] Discord
    * [ ] GitHub PR
    * [ ] https://reddit.com/r/olkb

## 1 Week Before Merge

* Announce that master will be closed from <2 Days Before> to <Day of Merge>
    * [ ] Discord
    * [ ] GitHub PR
    * [ ] https://reddit.com/r/olkb

## 2 Days Before Merge

* Announce that master is closed for 2 days
    * [ ] Discord
    * [ ] GitHub PR
    * [ ] https://reddit.com/r/olkb

## Day Of Merge

* `qmk_firmware` git commands
    * [ ] `git checkout develop`
    * [ ] `git pull --ff-only`
    * [ ] `git rebase origin/master`
    * [ ] Edit `readme.md`
        * [ ] Remove the notes about `develop`
    * [ ] Roll up the ChangeLog into one file.
    * [ ] `git commit -m 'Merge point for <DATE> Breaking Change'`
    * [ ] `git push origin develop`
* GitHub Actions
    * [ ] Create a PR for `develop`
    * [ ] Make sure travis comes back clean
    * [ ] Merge `develop` PR
