# QMK CLI

This page describes how to setup and use the QMK CLI.

# Overview

The QMK CLI makes building and working with QMK keyboards easier. We have provided a number of commands to help you work with QMK:

* `qmk compile`
* `qmk doctor`

# Setup

Simply add the `qmk_firmware/bin` directory to your `PATH`. You can run the `qmk` commands from any directory.

```
export PATH=$PATH:$HOME/qmk_firmware/bin
```

You may want to add this to your `.profile`, `.bash_profile`, `.zsh_profile`, or other shell startup scripts.

# Commands

## `qmk compile`

This command allows you to compile firmware from any directory. You can compile JSON exports from <https://config.qmk.fm> or compile keymaps in the repo.

**Usage for Configurator Exports**:

```
qmk compile <configuratorExport.json>
```

**Usage for Keymaps**:

```
qmk compile -kb <keyboard_name> -km <keymap_name>
```

## `qmk cformat`

This command formats C code using clang-format. Run it with no arguments to format all core code, or pass filenames on the command line to run it on specific files.

**Usage**:

```
qmk cformat [file1] [file2] [...] [fileN]
```
