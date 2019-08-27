# Python Development in QMK

This document gives an overview of how QMK has structured its python code. You should read this before working on any of the python code.

## Script directories

There are two places scripts live in QMK: `qmk_firmware/bin` and `qmk_firmware/util`. You should use `bin` for any python scripts that utilize the `qmk` wrapper. Scripts that are standalone and not run very often live in `util`.

We discourage putting anything into `bin` that does not utilize the `qmk` wrapper. If you think you have a good reason for doing so please talk to us about your use case.

## Python Modules

Most of the QMK python modules can be found in `qmk_firmware/lib/python`. This is the path that we append to `sys.path`.

We have a module hierarchy under that path:

* `qmk_firmware/lib/python`
    * `milc.py` - The CLI library we use. Will be pulled out into its own module in the future.
    * `qmk` - Code associated with QMK
        * `cli` - Modules that will be imported for CLI commands.
        * `errors.py` - Errors that can be raised within QMK apps
        * `keymap.py` - Functions for working with keymaps

## CLI Scripts

We have a CLI wrapper that you should utilize for any user facing scripts. We think it's pretty easy to use and it gives you a lot of nice things for free.

To use the wrapper simply place a module into `qmk_firmware/lib/python/qmk/cli`, and create a symlink to `bin/qmk` named after your module. Dashes in command names will be converted into dots so you can use hierarchy to manage commands.

When `qmk` is run it checks to see how it was invoked. If it was invoked as `qmk` the module name is take from `sys.argv[1]`. If it was invoked as `qmk-<module-name>` then everything after the first dash is taken as the module name. Dashes and underscores are converted to dots, and then `qmk.cli` is prepended before the module is imported.

The module uses `@cli.entrypoint()` and `@cli.argument()` decorators to define an entrypoint, which is where execution starts.

## Example CLI Script

We have provided a QMK Hello World script you can use as an example. To run it simply run `qmk hello` or `qmk-hello`. The source code is listed below.

```
from milc import cli

@cli.argument('-n', '--name', default='World', help='Name to greet.')
@cli.entrypoint('QMK Python Hello World.')
def main(cli):
    cli.echo('Hello, %s!', cli.config.general.name)
```
