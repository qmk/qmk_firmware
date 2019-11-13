# QMK CLI

This page describes how to setup and use the QMK CLI.

# Overview

The QMK CLI makes building and working with QMK keyboards easier. We have provided a number of commands to simplify and streamline tasks such as obtaining and compiling the QMK firmware, creating keymaps, and more.

* [Global CLI](#global-cli)
* [Local CLI](#local-cli)
* [CLI Commands](#cli-commands)

# Requirements

The CLI requires Python 3.5 or greater. We try to keep the number of requirements small but you will also need to install the packages listed in [`requirements.txt`](https://github.com/qmk/qmk_firmware/blob/master/requirements.txt).

# Global CLI

QMK provides an installable CLI that can be used to setup your QMK build environment, work with QMK, and which makes working with multiple copies of `qmk_firmware` easier. We recommend installing and updating this periodically.

## Install Using Homebrew (macOS, some Linux)

If you have installed [Homebrew](https://brew.sh) you can tap and install QMK:

```
brew tap qmk/qmk
brew install qmk
export QMK_HOME='~/qmk_firmware' # Optional, set the location for `qmk_firmware`
qmk setup  # This will clone `qmk/qmk_firmware` and optionally set up your build environment
```

## Install Using easy_install or pip

If your system is not listed above you can install QMK manually. First ensure that you have python 3.5 (or later) installed and have installed pip. Then install QMK with this command:

```
pip3 install qmk
export QMK_HOME='~/qmk_firmware' # Optional, set the location for `qmk_firmware`
qmk setup  # This will clone `qmk/qmk_firmware` and optionally set up your build environment
```

## Packaging For Other Operating Systems

We are looking for people to create and maintain a `qmk` package for more operating systems. If you would like to create a package for your OS please follow these guidelines:

* Follow best practices for your OS when they conflict with these guidelines
    * Document why in a comment when you do deviate
* Install using a virtualenv
* Instruct the user to set the environment variable `QMK_HOME` to have the firmware source checked out somewhere other than `~/qmk_firmware`.

# Local CLI

If you do not want to use the global CLI there is a local CLI bundled with `qmk_firmware`. You can find it in `qmk_firmware/bin/qmk`. You can run the `qmk` command from any directory and it will always operate on that copy of `qmk_firmware`.

**Example**:

```
$ ~/qmk_firmware/bin/qmk hello
Ψ Hello, World!
```

## Local CLI Limitations

There are some limitations to the local CLI compared to the global CLI:

* The local CLI does not support `qmk setup` or `qmk clone`
* The local CLI always operates on the same `qmk_firmware` tree, even if you have multiple repositories cloned.
* The local CLI does not run in a virtualenv, so it's possible that dependencies will conflict

# CLI Commands

## `qmk cformat`

This command formats C code using clang-format. Run it with no arguments to format all core code, or pass filenames on the command line to run it on specific files.

**Usage**:

```
qmk cformat [file1] [file2] [...] [fileN]
```

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

## `qmk config`

This command lets you configure the behavior of QMK. For the full `qmk config` documentation see [CLI Configuration](cli_configuration.md).

**Usage**:

```
qmk config [-ro] [config_token1] [config_token2] [...] [config_tokenN]
```

## `qmk docs`

This command starts a local HTTP server which you can use for browsing or improving the docs. Default port is 8936.

**Usage**:

```
qmk docs [-p PORT]
```

## `qmk doctor`

This command examines your environment and alerts you to potential build or flash problems.

**Usage**:

```
qmk doctor
```

## `qmk json-keymap`

Creates a keymap.c from a QMK Configurator export.

**Usage**:

```
qmk json-keymap [-o OUTPUT] filename
```

## `qmk list-keyboards`

This command lists all the keyboards currently defined in `qmk_firmware`

**Usage**:

```
qmk list-keyboards
```

## `qmk new-keymap`

This command creates a new keymap based on a keyboard's existing default keymap.

**Usage**:

```
qmk new-keymap [-kb KEYBOARD] [-km KEYMAP]
```

## `qmk pyformat`

This command formats python code in `qmk_firmware`.

**Usage**:

```
qmk pyformat
```

## `qmk pytest`

This command runs the python test suite. If you make changes to python code you should ensure this runs successfully.

**Usage**:

```
qmk pytest
```
