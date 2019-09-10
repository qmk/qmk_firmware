# QMK CLI Configuration

This document explains how `qmk config` works.

# Introduction

Configuration for QMK CLI is a key/value system. Each key consists of a subcommand and an argument name separated by a period. This allows for a straightforward and direct translation between config keys and the arguments they set.

## Simple Example

As an example let's look at the command `qmk compile --keyboard clueboard/66/rev4 --keymap default`.

There are two command line arguments that could be read from configuration instead:

* `compile.keyboard`
* `compile.keymap`

Let's set these now:

```
$ qmk config compile.keyboard=clueboard/66/rev4 compile.keymap=default
compile.keyboard: None -> clueboard/66/rev4
compile.keymap: None -> default
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

Now I can run `qmk compile` without specifying my keyboard and keymap each time.

## Setting Defaults

Sometimes you want to share a setting between multiple commands. For example, multiple subcomands take the argument `--keyboard`. Rather than setting this value for every command you can set a default value which will be used by any command that takes that argument.

Example:

```
$ qmk config default.keyboard=clueboard/66/rev4 default.keymap=default
default.keyboard: None -> clueboard/66/rev4
default.keymap: None -> default
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

# CLI Documentation (`qmk config`)

The `qmk config` command is used by users to interact with the underlying configuration. When run with no argument it shows the current configuration. When arguments are supplied they are assumed to be configuration tokens, which are strings containing no spaces with the following form:

    <subcommand|general|default>[.<key>][=<value>]

## Setting Configuration Values

You can set configuration values by putting an equal sign (=) into your config key. The key must always be the full `<section>.<key>` form.

Example:

```
$ qmk config default.keymap=default
default.keymap: None -> default
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

## Reading Configuration Values

You can read configuration values for a single key or for an entire section.

Single Key Example:

    qmk config compile.keyboard

Whole Section Example:

    qmk config compile

## Deleting Configuration Values

You can delete a configuration value by setting it to the special string `None`.

Example:

```
$ qmk config default.keymap=None
default.keymap: default -> None
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

## Multiple Operations

You can combine multiple read and write operations into a single command. They will be executed and displayed in order:

```
$ qmk config compile default.keymap=default compile.keymap=None
compile.keymap=skully
compile.keyboard=clueboard/66_hotswap/gen1
default.keymap: None -> default
compile.keymap: skully -> None
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```
