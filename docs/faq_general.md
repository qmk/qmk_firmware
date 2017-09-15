# Frequently Asked Questions

## What is QMK?

[QMK](https://github.com/qmk), short for Quantum Mechanical Keyboard, is a group of people building tools for custom keyboards. We started with the [QMK firmware](https://github.com/qmk/qmk_firmware), a heavily modified fork of [TMK](https://github.com/tmk/tmk_keyboard).

### Why the name Quantum?

<!-- FIXME -->

## What Differences Are There Between QMK and TMK?

TMK was originally designed and implemented by [Jun Wako](https://github.com/tmk). QMK started as [Jack Humbert's](https://github.com/jackhumbert) fork of TMK for the Planck. After a while Jack's fork had diverged quite a bit from TMK, and in 2015 Jack decided to rename his fork to QMK.

From a technical standpoint QMK builds upon TMK by adding several new features. Most notably QMK has expanded the number of available keycodes and uses these to implement advanced features like `S()`, `LCTL()`, and `MO()`. You can see a complete list of these keycodes in [Keycodes](keycodes.md).

From a project and community management standpoint TMK maintains all the officially supported keyboards by himself, with a bit of community support. Separate community maintained forks exist or can be created for other keyboards. Only a few keymaps are provided by default, so users typically don't share keymaps with each other. QMK encourages sharing of both keyboards and keymaps through a centrally managed repository, accepting all pull requests that follow the quality standards. These are mostly community maintained, but the QMK team also helps when necessary.

Both approaches have their merits and their drawbacks, and code flows freely between TMK and QMK when it makes sense.

