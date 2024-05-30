# QMK CLI Development

This document has useful information for developers wishing to write new `qmk` subcommands.

# Overview

The QMK CLI operates using the subcommand pattern made famous by git. The main `qmk` script is simply there to setup the environment and pick the correct entrypoint to run. Each subcommand is a self-contained module with an entrypoint (decorated by `@cli.subcommand()`) that performs some action and returns a shell returncode, or None.

## Developer mode:

If you intend to maintain keyboards and/or contribute to QMK, you can enable the CLI's "Developer" mode:

`qmk config user.developer=True`

This will allow you to see all available subcommands.  
**Note:** You will have to install additional requirements:  
```
python3 -m pip install -r requirements-dev.txt
```

# Subcommands

[MILC](https://github.com/clueboard/milc) is the CLI framework `qmk` uses to handle argument parsing, configuration, logging, and many other features. It lets you focus on writing your tool without wasting your time writing glue code.

Subcommands in the local CLI are always found in `qmk_firmware/lib/python/qmk/cli`.

Let's start by looking at an example subcommand. This is `lib/python/qmk/cli/hello.py`:

```python
"""QMK Python Hello World

This is an example QMK CLI script.
"""
from milc import cli


@cli.argument('-n', '--name', default='World', help='Name to greet.')
@cli.subcommand('QMK Hello World.')
def hello(cli):
    """Log a friendly greeting.
    """
    cli.log.info('Hello, %s!', cli.config.hello.name)
```

First we import the `cli` object from `milc`. This is how we interact with the user and control the script's behavior. We use `@cli.argument()` to define a command line flag, `--name`. This also creates a configuration variable named `hello.name` (and the corresponding `user.name`) which the user can set so they don't have to specify the argument. The `cli.subcommand()` decorator designates this function as a subcommand. The name of the subcommand will be taken from the name of the function.

Once inside our function we find a typical "Hello, World!" program. We use `cli.log` to access the underlying [Logger Object](https://docs.python.org/3.7/library/logging.html#logger-objects), whose behavior is user controllable. We also access the value for name supplied by the user as `cli.config.hello.name`. The value for `cli.config.hello.name` will be determined by looking at the `--name` argument supplied by the user, if not provided it will use the value in the `qmk.ini` config file, and if neither of those is provided it will fall back to the default supplied in the `cli.argument()` decorator.

# User Interaction

MILC and the QMK CLI have several nice tools for interacting with the user. Using these standard tools will allow you to colorize your text for easier interactions, and allow the user to control when and how that information is displayed and stored.

## Printing Text

There are two main methods for outputting text in a subcommand- `cli.log` and `cli.echo()`. They operate in similar ways but you should prefer to use `cli.log.info()` for most general purpose printing.

You can use special tokens to colorize your text, to make it easier to understand the output of your program. See [Colorizing Text](#colorizing-text) below.

Both of these methods support built-in string formatting using python's [printf style string format operations](https://docs.python.org/3.7/library/stdtypes.html#old-string-formatting). You can use tokens such as `%s` and `%d` within your text strings then pass the values as arguments. See our Hello, World program above for an example.

You should never use the format operator (`%`) directly, always pass values as arguments.

### Logging (`cli.log`)

The `cli.log` object gives you access to a [Logger Object](https://docs.python.org/3.7/library/logging.html#logger-objects). We have configured our log output to show the user a nice emoji for each log level (or the log level name if their terminal does not support unicode.) This way the user can tell at a glance which messages are most important when something goes wrong.

The default log level is `INFO`. If the user runs `qmk -v <subcommand>` the default log level will be set to `DEBUG`.

| Function | Emoji |
|----------|-------|
| cli.log.critical | `{bg_red}{fg_white}¬_¬{style_reset_all}` |
| cli.log.error | `{fg_red}☒{style_reset_all}` |
| cli.log.warning | `{fg_yellow}⚠{style_reset_all}` |
| cli.log.info | `{fg_blue}Ψ{style_reset_all}` |
| cli.log.debug | `{fg_cyan}☐{style_reset_all}` |
| cli.log.notset | `{style_reset_all}¯\\_(o_o)_/¯` |

### Printing (`cli.echo`)

Sometimes you simply need to print text outside of the log system. This is appropriate if you are outputting fixed data or writing out something that should never be logged. Most of the time you should prefer `cli.log.info()` over `cli.echo`.

### Colorizing Text

You can colorize the output of your text by including color tokens within text. Use color to highlight, not to convey information. Remember that the user can disable color, and your subcommand should still be usable if they do.

You should generally avoid setting the background color, unless it's integral to what you are doing. Remember that users have a lot of preferences when it comes to their terminal color, so you should pick colors that work well against both black and white backgrounds.

Colors prefixed with 'fg' will affect the foreground (text) color. Colors prefixed with 'bg' will affect the background color.

| Color | Background | Extended Background | Foreground | Extended Foreground|
|-------|------------|---------------------|------------|--------------------|
| Black | {bg_black} | {bg_lightblack_ex} | {fg_black} | {fg_lightblack_ex} |
| Blue | {bg_blue} | {bg_lightblue_ex} | {fg_blue} | {fg_lightblue_ex} |
| Cyan | {bg_cyan} | {bg_lightcyan_ex} | {fg_cyan} | {fg_lightcyan_ex} |
| Green | {bg_green} | {bg_lightgreen_ex} | {fg_green} | {fg_lightgreen_ex} |
| Magenta | {bg_magenta} | {bg_lightmagenta_ex} | {fg_magenta} | {fg_lightmagenta_ex} |
| Red | {bg_red} | {bg_lightred_ex} | {fg_red} | {fg_lightred_ex} |
| White | {bg_white} | {bg_lightwhite_ex} | {fg_white} | {fg_lightwhite_ex} |
| Yellow | {bg_yellow} | {bg_lightyellow_ex} | {fg_yellow} | {fg_lightyellow_ex} |

There are also control sequences that can be used to change the behavior of
ANSI output:

| Control Sequences | Description |
|-------------------|-------------|
| {style_bright} | Make the text brighter |
| {style_dim} | Make the text dimmer |
| {style_normal} | Make the text normal (neither `{style_bright}` nor `{style_dim}`) |
| {style_reset_all} | Reset all text attributes to default. (This is automatically added to the end of every string.) |
| {bg_reset} | Reset the background color to the user's default |
| {fg_reset} | Reset the foreground color to the user's default |

# Arguments and Configuration

QMK handles the details of argument parsing and configuration for you. When you add a new argument it is automatically incorporated into the config tree based on your subcommand's name and the long name of the argument. You can access this configuration in `cli.config`, using either attribute-style access (`cli.config.<subcommand>.<argument>`) or dictionary-style access (`cli.config['<subcommand>']['<argument>']`).

Under the hood QMK uses [ConfigParser](https://docs.python.org/3/library/configparser.html) to store configurations. This gives us an easy and straightforward way to represent the configuration in a human-editable way. We have wrapped access to this configuration to provide some nicities that ConfigParser does not normally have.

## Reading Configuration Values

You can interact with `cli.config` in all the ways you'd normally expect. For example the `qmk compile` command gets the keyboard name from `cli.config.compile.keyboard`. It does not need to know whether that value came from the command line, an environment variable, or the configuration file.

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

The configuration is not written out when it is changed. Most commands do not need to do this. We prefer to have the user change their configuration deliberately using `qmk config`.

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

# Testing, and Linting, and Formatting (oh my!)

We use nose2, flake8, and yapf to test, lint, and format code. You can use the `pytest` and `format-python` subcommands to run these tests:

### Testing and Linting

```
qmk pytest
```

### Formatting

```
qmk format-python
```

## Formatting Details

We use [yapf](https://github.com/google/yapf) to automatically format code. Our configuration is in the `[yapf]` section of `setup.cfg`.

::: tip
Tip- Many editors can use yapf as a plugin to automatically format code as you type.
:::

## Testing Details

Our tests can be found in `lib/python/qmk/tests/`. You will find both unit and integration tests in this directory. We hope you will write both unit and integration tests for your code, but if you do not please favor integration tests. 

If your PR does not include a comprehensive set of tests please add comments like this to your code so that other people know where they can help:

```python
    # TODO(unassigned/<your_github_username>): Write <unit|integration> tests
```

We use [nose2](https://nose2.readthedocs.io/en/latest/getting_started.html) to run our tests. You can refer to the nose2 documentation for more details on what you can do in your test functions.

## Linting Details

We use flake8 to lint our code. Your code should pass flake8 before you open a PR. This will be checked when you run `qmk pytest` and by CI when you submit a PR.
