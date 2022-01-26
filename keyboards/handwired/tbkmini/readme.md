# TBK Mini (Handwired)

A split, compact ergonomic keyboard.

This is a handwired version of the original firmware located in `keyboards/bastardkb/tbkmini`.

The main difference from the original firmware are diode direction (this is wired like a dactyl manuform).

Example builds using this firmware:

- <https://carl-fredrik.arvidson.io/posts/tbk-mini>
- <https://carl-fredrik.arvidson.io/posts/another-tbk-mini>

Supported Micro-controllers: Pro Micro and elite-C V4

Make example for this keyboard (after setting up your build environment):

    make handwired/tbkmini:default

or

    util/docker_build.sh handwired/tbkmini
