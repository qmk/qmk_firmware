# Breaking Changes

This document describes QMK's Breaking Change process. A Breaking Change is any change which modifies how QMK behaves in a way that in incompatible or potentially dangerous. We limit these changes so that users can have confidence that updating their QMK tree will not break their keymaps.

This also includes any keyboard moves within the repository.

The breaking change period is when we will merge PRs that change QMK in dangerous or unexpected ways. There is a built-in period of testing so we are confident that any problems caused are rare or unable to be predicted.

Practically, this means QMK merges the `develop` branch into the `master` branch on a 3-month cadence.

## What has been included in past Breaking Changes?

* [2025 Aug 31](ChangeLog/20250831)
* [2025 May 25](ChangeLog/20250525)
* [2025 Feb 23](ChangeLog/20250223)
* [Older Breaking Changes](breaking_changes_history)

## When is the next Breaking Change?

The next Breaking Change is scheduled for November 30, 2025.

### Important Dates

* 2025 Aug 31 - `develop` is tagged with a new release version. Each push to `master` is subsequently merged to `develop` by GitHub actions.
* 2025 Nov 2 - `develop` closed to new PRs.
* 2025 Nov 2 - Call for testers.
* 2025 Nov 16 - Last day for merges -- after this point `develop` is locked for testing and accepts only bugfixes
* 2025 Nov 23 - `develop` is locked, only critical bugfix PRs merged.
* 2025 Nov 28 - `master` is locked, no PRs merged.
* 2025 Nov 30 - Merge `develop` to `master`.
* 2025 Nov 30 - `master` is unlocked. PRs can be merged again.

## What changes will be included?

To see a list of breaking changes merge candidates you can look at the [`core` label](https://github.com/qmk/qmk_firmware/pulls?q=is%3Aopen+label%3Acore+is%3Apr). This label is applied whenever a PR is raised or changed, but only if the PR includes changes to core areas of QMK Firmware. A PR with that label applied is not guaranteed to be merged in the current cycle. New changes might be added between now and when `develop` is closed, and it is generally the responsibility of the submitter to handle conflicts. There is also another label used by QMK Collaborators -- `breaking_change_YYYYqN` -- which signifies to maintainers that it is a strong candidate for inclusion, and should be prioritized for review.

If you want your breaking change to be included in this round you need to create a PR and have it accepted by QMK Collaborators before `develop` closes. After `develop` closes, new submissions will be deferred to the next breaking changes cycle.

The simpler your PR is, the easier it is for maintainers to review, thus a higher likelihood of a faster merge. Large PRs tend to require a lot of attention, refactoring, and back-and-forth with subsequent reviews -- with other PRs getting merged in the meantime larger unmerged PRs are far more likely to be susceptible to conflicts.

Criteria for acceptance:

* The PR is complete and ready to merge
* GitHub checks for the PR are green whenever possible
    * A "red" check may be disregarded by maintainers if the items flagged are unrelated to the change proposed in the PR
        * Modifications to existing files should not need to add license headers to pass lint, for instance.
        * If it's not directly related to your PR's functionality, prefer avoiding making a change.

Strongly suggested:

* The PR has a ChangeLog file describing the changes under `<qmk_firmware>/docs/Changelog/20241124`.
    * This should be in Markdown format, with a name in the format `PR12345.md`, substituting the digits for your PRs ID.
    * One strong recommendation that the ChangeLog document matches the PR description on GitHub, so as to ensure traceability.

## Checklists

This section documents various processes we use when running the Breaking Changes process.

### 4 Weeks Before Merge

* `develop` is now closed to new PRs, only fixes for current PRs may be merged
* Post call for testers: message `@Breaking Changes Updates` on `#qmk_firmware` in Discord:
    * `@Breaking Changes Updates -- Hey folks, last day for functional PRs to be raised against qmk_firmware for this breaking changes cycle is today.`

### 2 Weeks Before Merge

* `develop` is now closed to existing PR merges, only bugfixes for previous merges may be included
* Post call for testers: message `@Breaking Changes Updates` on `#qmk_firmware` in Discord.
    * `@Breaking Changes Updates -- Hey folks, last day for functional PRs to be merged into qmk_firmware for this breaking changes cycle is today. After that, we're handling bugfixes only.`

### 1 Week Before Merge

* `develop` is now closed to PR merges, only critical bugfixes may be included
* Announce that master will be closed from `<2 Days Before>` to `<Day of Merge>` -- message `@Breaking Changes Updates` on `#qmk_firmware` in Discord:
    * `@Breaking Changes Updates -- Hey folks, last day for functional PRs to be merged into qmk_firmware for this breaking changes cycle is today. After that, we're handling bugfixes only.`

### 2 Days Before Merge

* `master` is now closed to PR merges
* Announce that master is closed for 2 days
    * `@Breaking Changes Updates -- Hey folks, the master branch of qmk_firmware is now locked for the next couple of days while we prepare to merge the newest batch of changes from develop.`

### Day Of Merge

* `qmk_firmware` git commands
    * `git checkout develop`
    * `git pull --ff-only`
    * Edit `readme.md`
        * Remove the notes about `develop`
    * Roll up the ChangeLog into one file.
    * `git commit -m 'Merge point for <DATE> Breaking Change'`
    * `git push upstream develop`
* GitHub Actions
    * Create a PR for `develop`
    * **Turn off 'Automatically delete head branches' for the repository** -- confirm with @qmk/directors that it is done before continuing
* `qmk_firmware` git commands
    * `git checkout master`
    * `git pull --ff-only`
    * `git merge --no-ff develop`
    * `git tag <next_version>` # Prevent the breakpoint tag from confusing version incrementing
    * `git push upstream <next_version>`
    * `git push upstream master`

## Post-merge operations

### Updating the `develop` branch

This happens immediately after the previous `develop` branch is merged to `master`.

* `qmk_firmware` git commands
    * `git checkout master`
    * `git pull --ff-only`
    * `git checkout develop`
    * `git pull --ff-only`
    * `git merge --no-ff master`
    * Edit `readme.md`
        * Add a big notice at the top that this is a testing branch. See previous revisions of the `develop` branch.
        * Include a link to this document
    * `git commit -m 'Branch point for <DATE> Breaking Change'`
    * `git tag breakpoint_<YYYY>_<MM>_<DD>`
    * `git push upstream breakpoint_<YYYY>_<MM>_<DD>`
    * `git push upstream develop`

* All submodules under `lib` now need to be checked against their QMK-based forks:
    * `git submodule foreach git log -n1`
    * Validate each submodule SHA1 matches the qmk fork, e.g. for ChibiOS:
        * Go to [qmk/ChibiOS](https://github.com/qmk/ChibiOS)
        * Compare the commit hash in the above output to the commit hash in the repository
        * If there's a mismatch, that repository needs to have its `qmk-master` branch updated to match (otherwise Configurator won't work):
            * `cd lib/chibios`
            * `git fetch --all`
            * `git checkout qmk-master`
            * `git reset --hard <commit hash>`
            * `git push origin qmk-master --force-with-lease`

* Announce that both `master` and `develop` are now unlocked -- message `@Breaking Changes Updates` on `#qmk_firmware` in Discord:
    * `@Breaking Changes Updates -- Hey folks, develop has now been merged into master -- newest batch of changes are now available for everyone to use!`

* (Optional) [update ChibiOS + ChibiOS-Contrib on `develop`](chibios_upgrade_instructions)


### Set up Discord events for the next cycle

* Update this file with the new dates: `docs/breaking_changes.md`
* Create Events on the QMK Discord - "Somewhere Else" => "GitHub":
    * Event #1:
        | Field       | Value                                                                                                                                                                                                                 |
        |-------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
        | Topic       | Last `develop` functionality PRs to be raised                                                                                                                                                                         |
        | Start Date  | ((5 weeks before merge)), 12:00am                                                                                                                                                                                     |
        | End Date    | ((4 weeks before merge)), 12:00am                                                                                                                                                                                     |
        | Description | This is the last window for functional PRs to be raised against `develop` for the current breaking changes cycle. After ((4 weeks before merge)), any new PRs targeting `develop` will be deferred to the next cycle. |
    * Event #2:
        | Field       | Value                                                                                                                                                                                                            |
        |-------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
        | Topic       | Last `develop` functionality PRs to be merged                                                                                                                                                                    |
        | Start Date  | ((4 weeks before merge)), 12:00am                                                                                                                                                                                |
        | End Date    | ((2 weeks before merge)), 12:00am                                                                                                                                                                                |
        | Description | This is the last window for functional PRs to be merged into `develop` for the current breaking changes cycle. After ((2 weeks before merge)), only bugfix PRs targeting `develop` will be considered for merge. |
    * Event #3:
        | Field       | Value                                                                                                                                                                                                                           |
        |-------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
        | Topic       | `develop` closed for merges                                                                                                                                                                                                     |
        | Start Date  | ((2 weeks before merge)), 12:00am                                                                                                                                                                                               |
        | End Date    | ((day of merge)), 12:00am                                                                                                                                                                                                       |
        | Description | This is the deadline for functionality bugfix PRs to be merged into `develop` for the current breaking changes cycle. After ((1 week before merge)), only critical bugfix PRs targeting `develop` will be considered for merge. |
    * Event #4:
        | Field       | Value                                                                                                                |
        |-------------|----------------------------------------------------------------------------------------------------------------------|
        | Topic       | `master` closed for merges                                                                                           |
        | Start Date  | ((2 days before merge)), 12:00am                                                                                     |
        | End Date    | ((day of merge)), 12:00am                                                                                            |
        | Description | This is the period that no PRs are to be merged to `master`, so that the merge of `develop` into `master` is stable. |
    * Event #5:
        | Field       | Value                                                                                                                                      |
        |-------------|--------------------------------------------------------------------------------------------------------------------------------------------|
        | Topic       | `develop` merges to `master`                                                                                                               |
        | Start Date  | ((day of merge)), 12:00am                                                                                                                  |
        | End Date    | ((day of merge)), 11:45pm                                                                                                                  |
        | Description | At some point, QMK will merge `develop` into `master` and everyone will be able to reap the benefits of the newest batch of functionality. |
