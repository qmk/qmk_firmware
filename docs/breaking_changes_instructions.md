# Breaking Changes: My Pull Request Was Flagged

A QMK member may have replied to your pull request stating that your submission is a breaking change. In their judgment, the changes you have proposed have greater implications for either QMK, or its users.

Some things that may cause a pull request to be flagged are:

- **Edits to User Keymaps**
  A user may submit their keymap to QMK, then some time later open a pull request with further updates, only to find it can't be merged because it was edited in the `qmk/qmk_firmware` repository. As not all users are proficient at using Git or GitHub, the user may find themself unable to fix the issue on their own.
- **Changes to Expected Behavior**
  Changes to QMK behavior may cause users to believe their hardware or QMK is broken if they flash new firmware that incorporates changes to existing QMK features, and find themselves without a means to restore the desired behavior.
- **Changes Requiring User Action**
  Changes may also require action to be taken by users, such as updating a toolchain or taking some action in Git.
- **Changes Necessitating Increased Scrutiny**
  On occasion, a submission may have implications for QMK as a project. This could be copyright/licensing issues, coding conventions, large feature overhauls, "high-risk" changes that need wider testing by our community, or something else entirely.
- **Changes Requiring Communication to End Users**
  This includes warnings about future deprecations, outdated practices, and anything else that needs to be communicated but doesn't fit into one of the above categories.

## What Do I Do?

If it is determined that your submission is a breaking change, there are a few things you can do to smooth the process:

### Consider Splitting Up Your PR

If you are contributing core code, and the only reason it needs to go through breaking changes is that you are updating keymaps to match your change, consider whether you can submit your feature in a way that the old keymaps continue to work. Then submit a separate PR that goes through the breaking changes process to remove the old code.

### Contribute a ChangeLog Entry

We require submissions that go through the Breaking Change process to include a changelog entry. The entry should be a short summary of the changes your pull request makes &ndash; [each section here started as a changelog](ChangeLog/20190830.md "n.b. This should link to the 2019 Aug 30 Breaking Changes doc  - @noroadsleft").

Your changelog should be located at `docs/ChangeLog/YYYYMMDD/PR####.md`, where `YYYYMMDD` is the date on which QMK's breaking change branch &ndash; usually named `develop` &ndash; will be merged into the `master` branch, and `####` is the number of your pull request.

If your submission requires action on the part of users, your changelog should instruct users what action(s) must be taken, or link to a location that does so.

### Document Your Changes

Understanding the purpose for your submission, and possible implications or actions it will require can make the review process more straightforward. A changelog may suffice for this purpose, but more extensive changes may require a level of detail that is ill-suited for a changelog.

Commenting on your pull request and being responsive to questions, comments, and change requests is much appreciated.

### Ask for Help

Having your submission flagged may have caught you off guard. If you find yourself intimidated or overwhelmed, let us know. Comment on your pull request, or [reach out to the QMK team on Discord](https://discord.gg/Uq7gcHh).
