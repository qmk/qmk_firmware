# Frequently Asked Questions

## What is QMK?

[QMK](https://github.com/qmk), short for Quantum Mechanical Keyboard, is a group of people building tools for custom keyboards. We started with the [QMK firmware](https://github.com/qmk/qmk_firmware), a heavily modified fork of [TMK](https://github.com/tmk/tmk_keyboard).

## I don't know where to start!

If this is the case, then you should start with our [Newbs Guide](newbs.md). There is a lot of great info there, and that should cover everything you need to get started.

If that's an issue, hop onto the [QMK Configurator](https://config.qmk.fm), as that will handle a majority of what you need there.

## How can I flash the firmware I built?

First, head to the [Compiling/Flashing FAQ Page](faq_build.md). There is a good deal of info there, and you'll find a bunch of solutions to common issues there.

## What if I have an issue that isn't covered here?

Okay, that's fine. Then please check the [open issues in our GitHub](https://github.com/qmk/qmk_firmware/issues) to see if somebody is experiencing the same thing (make sure it's not just similar, but actually the same).

If you can't find anything, then please open a [new issue](https://github.com/qmk/qmk_firmware/issues/new)!

## What if I found a bug?

Then please open an [issue](https://github.com/qmk/qmk_firmware/issues/new), and if you know how to fix it, open up a Pull Request on GitHub with the fix.

## But `git` and `GitHub` are intimidating!

Don't worry, we have some pretty nice [Guidelines](newbs_git_best_practices.md) on how to start using `git` and GitHub to make things easier to develop.

Additionally, you can find additional `git` and GitHub related links [here](newbs_learn_more_resources.md).

## I have a Keyboard that I want to add support for

Awesome! Open up a Pull Request for it. We'll review the code, and merge it!

### What if I want to do brand it with `QMK`?

That's amazing! We would love to assist you with that!

In fact, we have a [whole page](https://qmk.fm/powered/) dedicated to adding QMK Branding to your page and keyboard. This covers pretty much everything you need (knowledge and images) to officially support QMK.

If you have any questions about this, open an issue or head to [Discord](https://discord.gg/Uq7gcHh).

## What Differences Are There Between QMK and TMK?

TMK was originally designed and implemented by [Jun Wako](https://github.com/tmk). QMK started as [Jack Humbert](https://github.com/jackhumbert)'s fork of TMK for the Planck. After a while Jack's fork had diverged quite a bit from TMK, and in 2015 Jack decided to rename his fork to QMK.

From a technical standpoint QMK builds upon TMK by adding several new features. Most notably QMK has expanded the number of available keycodes and uses these to implement advanced features like `S()`, `LCTL()`, and `MO()`. You can see a complete list of these keycodes in [Keycodes](keycodes.md).

From a project and community management standpoint TMK maintains all the officially supported keyboards by himself, with a bit of community support. Separate community maintained forks exist or can be created for other keyboards. Only a few keymaps are provided by default, so users typically don't share keymaps with each other. QMK encourages sharing of both keyboards and keymaps through a centrally managed repository, accepting all pull requests that follow the quality standards. These are mostly community maintained, but the QMK team also helps when necessary.

Both approaches have their merits and their drawbacks, and code flows freely between TMK and QMK when it makes sense.
