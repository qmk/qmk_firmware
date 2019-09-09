# QMK CLI Configuration

This document explains how `qmk config` works for both users and developers.

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

# Scripting Documenting

This section is only relevant to developers working on QMK subcommands. If you are not writing python code for QMK you can skip this, unless it interests you.

QMK handles the details of argument parsing and configuration for you. When you add a new argument it is automatically incorporated into the config tree based on your subcommand's name and the long name of the argument. You can access this configuration in `cli.config`, using either attribute-style access (`cli.config.<subcommand>.<argument>`) or dictionary-style access (`cli.config['<subcommand>']['<argument>']`).

Under the hood QMK uses [ConfigParser](https://docs.python.org/3/library/configparser.html) to store configurations. This gives us an easy and straightforward way to represent the configuration in a human-editable way. We have wrapped access to this configuration to provide some nicities that ConfigParser does not normally have.

## Reading Configuration Values

You can interact with `cli.config` in all the ways you'd normally expect. For example the `qmk compile` comand gets the keyboard name from `cli.config.compile.keyboard`. It does not need to know whether that value came from the command line, an environment variable, or the configuration file.

Iteration is also supported:

```
for section in cli.config:
    for key in cli.config[section]:
        cli.log.info('%s.%s: %s', section, key, cli.config[section][key])
```

## Setting Configuration Values

You can set configuration values in the usual ways.

Dictionary style:

```
cli.config['<section>']['<key>'] = <value>
```

Attribute style:

```
cli.config.<section>.<key> = <value>
```

## Deleting Configuration Values

You can delete configuration values in the usual ways.

Dictionary style:

```
del(cli.config['<section>']['<key>'])
```

Attribute style:

```
del(cli.config.<section>.<key>)
```

## Writing The Configuration File

The configuration is not written out when it is changed. Most commands do not need to do this. We prefer to have the user change their configuration deliberitely using `qmk config`.

You can use `cli.save_config()` to write out the configuration.

## Excluding Arguments From Configuration

Some arguments should not be propagated to the configuration file. These can be excluded by adding `arg_only=True` when creating the argument.

Example:

```
@cli.argument('-o', '--output', arg_only=True, help='File to write to')
@cli.argument('filename', arg_only=True, help='Configurator JSON file')
@cli.subcommand('Create a keymap.c from a QMK Configurator export.')
def json_keymap(cli):
    pass
```

You will only be able to access these arguments using `cli.args`. For example:

```
cli.log.info('Reading from %s and writing to %s', cli.args.filename, cli.args.output)
```
