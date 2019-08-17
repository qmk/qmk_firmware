# QMK CLI

This page describes how to setup and use the QMK CLI.

# Overview

The QMK CLI makes building and working with QMK keyboards easier. We have provided a number of commands to help you work with QMK:

* `qmk compile-json`

# Setup

Simply add the `qmk_firmware/bin` directory to your `PATH`. You can run the `qmk` commands from any directory.

```
export PATH=$PATH:$HOME/qmk_firmware/bin
```

You may want to add this to your `.profile`, `.bash_profile`, `.zsh_profile`, or other shell startup scripts.

# Commands

## `qmk compile-json`

This command allows you to compile JSON files you have downloaded from <https://config.qmk.fm>.

**Usage**:

```
qmk compile-json mine.json
```
