# QMK CLI Commands

# User Commands

## `qmk compile`

This command allows you to compile firmware from any directory. You can compile JSON exports from <https://config.qmk.fm>, compile keymaps in the repo, or compile the keyboard in the current working directory.

This command is directory aware. It will automatically fill in KEYBOARD and/or KEYMAP if you are in a keyboard or keymap directory.

**Usage for Configurator Exports**:

```
qmk compile [-c] <configuratorExport.json>
```

**Usage for Keymaps**:

```
qmk compile [-c] [-e <var>=<value>] [-j <num_jobs>] -kb <keyboard_name> -km <keymap_name>
```

**Usage in Keyboard Directory**:

Must be in keyboard directory with a default keymap, or in keymap directory for keyboard, or supply one with `--keymap <keymap_name>`
```
qmk compile
```

**Usage for building all keyboards that support a specific keymap**:

```
qmk compile -kb all -km <keymap_name>
```

**Example**:
```
$ qmk config compile.keymap=default
$ cd ~/qmk_firmware/keyboards/planck/rev6
$ qmk compile
Ψ Compiling keymap with make planck/rev6:default
...
```
or with optional keymap argument

```
$ cd ~/qmk_firmware/keyboards/clueboard/66/rev4
$ qmk compile -km 66_iso
Ψ Compiling keymap with make clueboard/66/rev4:66_iso
...
```
or in keymap directory

```
$ cd ~/qmk_firmware/keyboards/gh60/satan/keymaps/colemak
$ qmk compile
Ψ Compiling keymap with make gh60/satan:colemak
...
```

**Usage in Layout Directory**:

Must be under `qmk_firmware/layouts/`, and in a keymap folder.
```
qmk compile -kb <keyboard_name>
```

**Example**:
```
$ cd ~/qmk_firmware/layouts/community/60_ansi/mechmerlin-ansi
$ qmk compile -kb dz60
Ψ Compiling keymap with make dz60:mechmerlin-ansi
...
```

**Parallel Compilation**:

It is possible to speed up compilation by adding the `-j`/`--parallel` flag.
```
qmk compile -j <num_jobs> -kb <keyboard_name>
```
The `num_jobs` argument determines the maximum number of jobs that can be used. Setting it to zero will enable parallel compilation without limiting the maximum number of jobs.
```
qmk compile -j 0 -kb <keyboard_name>
```

## `qmk flash`

This command is similar to `qmk compile`, but can also target a bootloader. The bootloader is optional, and is set to `:flash` by default. To specify a different bootloader, use `-bl <bootloader>`. Visit the [Flashing Firmware](flashing.md) guide for more details of the available bootloaders.

This command is directory aware. It will automatically fill in KEYBOARD and/or KEYMAP if you are in a keyboard or keymap directory.

This command can also flash binary firmware files (hex or bin) such as the ones produced by [Configurator](https://config.qmk.fm).

**Usage for Configurator Exports**:

```
qmk flash [-bl <bootloader>] [-c] [-e <var>=<value>] [-j <num_jobs>] <configuratorExport.json>
```

**Usage for Keymaps**:

```
qmk flash -kb <keyboard_name> -km <keymap_name> [-bl <bootloader>] [-c] [-e <var>=<value>] [-j <num_jobs>]
```

**Usage for pre-compiled firmwares**:

**Note**: The microcontroller needs to be specified (`-m` argument) for keyboards with the following bootloaders:
* HalfKay
* QMK HID
* USBaspLoader

ISP flashing is also supported with the following flashers and require the microcontroller to be specified:
* USBasp
* USBtinyISP

```
qmk flash [-m <microcontroller>] <compiledFirmware.[bin|hex]>
```

**Listing the Bootloaders**

```
qmk flash -b
```

## `qmk config`

This command lets you configure the behavior of QMK. For the full `qmk config` documentation see [CLI Configuration](cli_configuration.md).

**Usage**:

```
qmk config [-ro] [config_token1] [config_token2] [...] [config_tokenN]
```

## `qmk cd`

This command opens a new shell in your `qmk_firmware` directory.

Note that if you are already somewhere within `QMK_HOME` (for example, the `keyboards/` folder), nothing will happen.

To exit out into the parent shell, simply type `exit`.

**Usage**:

```
qmk cd
```

## `qmk find`

This command allows for searching through keyboard/keymap targets, filtering by specific criteria. `info.json` and `rules.mk` files contribute to the search data, as well as keymap configurations, and the results can be filtered using "dotty" syntax matching the overall `info.json` file format.

For example, one could search for all keyboards using STM32F411:

```
qmk find -f 'processor=STM32F411'
```

...and one can further constrain the list to keyboards using STM32F411 as well as rgb_matrix support:

```
qmk find -f 'processor=STM32F411' -f 'features.rgb_matrix=true'
```

**Usage**:

```
qmk find [-h] [-km KEYMAP] [-f FILTER]

options:
  -km KEYMAP, --keymap KEYMAP
                        The keymap name to build. Default is 'default'.
  -f FILTER, --filter FILTER
                        Filter the list of keyboards based on the supplied value in rules.mk. Matches info.json structure, and accepts the formats 'features.rgblight=true' or 'exists(matrix_pins.direct)'. May be passed multiple times, all filters need to match. Value may include wildcards such as '*' and '?'.
```

## `qmk console`

This command lets you connect to keyboard consoles to get debugging messages. It only works if your keyboard firmware has been compiled with `CONSOLE_ENABLE=yes`.

**Usage**:

```
qmk console [-d <pid>:<vid>[:<index>]] [-l] [-n] [-t] [-w <seconds>]
```

**Examples**:

Connect to all available keyboards and show their console messages:

```
qmk console
```

List all devices:

```
qmk console -l
```

Show only messages from clueboard/66/rev3 keyboards:

```
qmk console -d C1ED:2370
```

Show only messages from the second clueboard/66/rev3:

```
qmk console -d C1ED:2370:2
```

Show timestamps and VID:PID instead of names:

```
qmk console -n -t
```

Disable bootloader messages:

```
qmk console --no-bootloaders
```

## `qmk doctor`

This command examines your environment and alerts you to potential build or flash problems. It can fix many of them if you want it to.

**Usage**:

```
qmk doctor [-y] [-n]
```

**Examples**:

Check your environment for problems and prompt to fix them:

    qmk doctor

Check your environment and automatically fix any problems found:

    qmk doctor -y

Check your environment and report problems only:

    qmk doctor -n

## `qmk format-json`

Formats a JSON file in a (mostly) human-friendly way. Will usually correctly detect the format of the JSON (info.json or keymap.json) but you can override this with `--format` if necessary.

**Usage**:

```
qmk format-json [-f FORMAT] <json_file>
```

## `qmk info`

Displays information about keyboards and keymaps in QMK. You can use this to get information about a keyboard, show the layouts, display the underlying key matrix, or to pretty-print JSON keymaps.

**Usage**:

```
qmk info [-f FORMAT] [-m] [-l] [-km KEYMAP] [-kb KEYBOARD]
```

This command is directory aware. It will automatically fill in KEYBOARD and/or KEYMAP if you are in a keyboard or keymap directory.

**Examples**:

Show basic information for a keyboard:

    qmk info -kb planck/rev5

Show the matrix for a keyboard:

    qmk info -kb ergodox_ez -m

Show a JSON keymap for a keyboard:

    qmk info -kb clueboard/california -km default

## `qmk json2c`

Creates a keymap.c from a QMK Configurator export.

**Usage**:

```
qmk json2c [-o OUTPUT] filename
```

## `qmk c2json`

Creates a keymap.json from a keymap.c.

**Note:** Parsing C source files is not easy, therefore this subcommand may not work with your keymap. In some cases not using the C pre-processor helps.

**Usage**:

```
qmk c2json -km KEYMAP -kb KEYBOARD [-q] [--no-cpp] [-o OUTPUT] filename
```

## `qmk lint`

Checks over a keyboard and/or keymap and highlights common errors, problems, and anti-patterns.

**Usage**:

```
qmk lint [-km KEYMAP] [-kb KEYBOARD] [--strict]
```

This command is directory aware. It will automatically fill in KEYBOARD and/or KEYMAP if you are in a keyboard or keymap directory.

**Examples**:

Do a basic lint check:

    qmk lint -kb rominronin/katana60/rev2

## `qmk list-keyboards`

This command lists all the keyboards currently defined in `qmk_firmware`

**Usage**:

```
qmk list-keyboards
```

## `qmk list-keymaps`

This command lists all the keymaps for a specified keyboard (and revision).

This command is directory aware. It will automatically fill in KEYBOARD if you are in a keyboard directory.

**Usage**:

```
qmk list-keymaps -kb planck/ez
```

## `qmk new-keyboard`

This command creates a new keyboard based on available templates.

Any arguments that are not provided will prompt for input. If `-u` is not passed and `user.name` is set in .gitconfig, it will be used as the default username in the prompt.

**Usage**:

```
qmk new-keyboard [-kb KEYBOARD] [-t {atmega32u4,STM32F303,etc}] [-l {60_ansi,75_iso,etc}] -u USERNAME
```

## `qmk new-keymap`

This command creates a new keymap based on a keyboard's existing default keymap.

This command is directory aware. It will automatically fill in KEYBOARD and/or KEYMAP if you are in a keyboard or keymap directory.

**Usage**:

```
qmk new-keymap [-kb KEYBOARD] [-km KEYMAP]
```

## `qmk clean`

This command cleans up the `.build` folder. If `--all` is passed, any .hex or .bin files present in the `qmk_firmware` directory will also be deleted.

**Usage**:

```
qmk clean [-a]
```

## `qmk via2json`

This command an generate a keymap.json from a VIA keymap backup. Both the layers and the macros are converted, enabling users to easily move away from a VIA-enabled firmware without writing any code or reimplementing their keymaps in QMK Configurator.

**Usage**:

```
qmk via2json -kb KEYBOARD [-l LAYOUT] [-km KEYMAP] [-o OUTPUT] filename
```

**Example:**

```
$ qmk via2json -kb ai03/polaris -o polaris_keymap.json polaris_via_backup.json
Ψ Wrote keymap to /home/you/qmk_firmware/polaris_keymap.json
```

## `qmk import-keyboard`

This command imports a data-driven `info.json` keyboard into the repo.

**Usage**:

```
usage: qmk import-keyboard [-h] filename
```

**Example:**

```
$ qmk import-keyboard ~/Downloads/forever60.json
Ψ Importing forever60.json.

Ψ Imported a new keyboard named forever60.
Ψ To start working on things, `cd` into keyboards/forever60,
Ψ or open the directory in your preferred text editor.
Ψ And build with qmk compile -kb forever60 -km default.
```

## `qmk import-keymap`

This command imports a data-driven `keymap.json` keymap into the repo.

**Usage**:

```
usage: qmk import-keymap [-h] filename
```

**Example:**

```
qmk import-keymap ~/Downloads/asdf2.json
Ψ Importing asdf2.json.

Ψ Imported a new keymap named asdf2.
Ψ To start working on things, `cd` into keyboards/takashicompany/dogtag/keymaps/asdf2,
Ψ or open the directory in your preferred text editor.
Ψ And build with qmk compile -kb takashicompany/dogtag -km asdf2.
```

## `qmk import-kbfirmware`

This command creates a new keyboard based on a [Keyboard Firmware Builder](https://kbfirmware.com/) export.

**Usage**:

```
usage: qmk import-kbfirmware [-h] filename
```

**Example:**

```
$ qmk import-kbfirmware ~/Downloads/gh62.json
Ψ Importing gh62.json.

⚠ Support here is basic - Consider using 'qmk new-keyboard' instead
Ψ Imported a new keyboard named gh62.
Ψ To start working on things, `cd` into keyboards/gh62,
Ψ or open the directory in your preferred text editor.
Ψ And build with qmk compile -kb gh62 -km default.
```

---

# Developer Commands

## `qmk format-text`

This command formats text files to have proper line endings.

Every text file in the repository needs to have Unix (LF) line ending.
If you are working on **Windows**, you must ensure that line endings are corrected in order to get your PRs merged.

```
qmk format-text
```

## `qmk format-c`

This command formats C code using clang-format.

Run it with no arguments to format all core code that has been changed. Default checks `origin/master` with `git diff`, branch can be changed using `-b <branch_name>`

Run it with `-a` to format all core code, or pass filenames on the command line to run it on specific files.

**Usage for specified files**:

```
qmk format-c [file1] [file2] [...] [fileN]
```

**Usage for all core files**:

```
qmk format-c -a
```

**Usage for only changed files against origin/master**:

```
qmk format-c
```

**Usage for only changed files against branch_name**:

```
qmk format-c -b branch_name
```

## `qmk generate-compilation-database`

**Usage**:

```
qmk generate-compilation-database [-kb KEYBOARD] [-km KEYMAP]
```

Creates a `compile_commands.json` file.

Does your IDE/editor use a language server but doesn't _quite_ find all the necessary include files? Do you hate red squigglies? Do you wish your editor could figure out `#include QMK_KEYBOARD_H`? You might need a [compilation database](https://clang.llvm.org/docs/JSONCompilationDatabase.html)! The qmk tool can build this for you.

This command needs to know which keyboard and keymap to build. It uses the same configuration options as the `qmk compile` command: arguments, current directory, and config files.

**Example:**

```
$ cd ~/qmk_firmware/keyboards/gh60/satan/keymaps/colemak
$ qmk generate-compilation-database
Ψ Making clean
Ψ Gathering build instructions from make -n gh60/satan:colemak
Ψ Found 50 compile commands
Ψ Writing build database to /Users/you/src/qmk_firmware/compile_commands.json
```

Now open your dev environment and live a squiggly-free life.

## `qmk docs`

This command starts a local HTTP server which you can use for browsing or improving the docs. Default port is 8936.
Use the `-b`/`--browser` flag to automatically open the local webserver in your default browser.

This command runs `docsify serve` if `docsify-cli` is installed (which provides live reload), otherwise Python's builtin HTTP server module will be used.

**Usage**:

```
qmk docs [-b] [-p PORT]
```

## `qmk generate-docs`

This command allows you to generate QMK documentation locally. It can be uses for general browsing or improving the docs. External tools such as [serve](https://www.npmjs.com/package/serve) can be used to browse the generated files.

**Usage**:

```
qmk generate-docs
```

## `qmk generate-rgb-breathe-table`

This command generates a lookup table (LUT) header file for the [RGB Lighting](feature_rgblight.md) feature's breathing animation. Place this file in your keyboard or keymap directory as `rgblight_breathe_table.h` to override the default LUT in `quantum/rgblight/`.

**Usage**:

```
qmk generate-rgb-breathe-table [-q] [-o OUTPUT] [-m MAX] [-c CENTER]
```

## `qmk kle2json`

This command allows you to convert from raw KLE data to QMK Configurator JSON. It accepts either an absolute file path, or a file name in the current directory. By default it will not overwrite `info.json` if it is already present. Use the `-f` or `--force` flag to overwrite.

**Usage**:

```
qmk kle2json [-f] <filename>
```

**Examples**:

```
$ qmk kle2json kle.txt
☒ File info.json already exists, use -f or --force to overwrite.
```

```
$ qmk kle2json -f kle.txt -f
Ψ Wrote out to info.json
```

## `qmk format-python`

This command formats python code in `qmk_firmware`.

**Usage**:

```
qmk format-python
```

## `qmk pytest`

This command runs the python test suite. If you make changes to python code you should ensure this runs successfully.

**Usage**:

```
qmk pytest [-t TEST]
```

**Examples**:

Run entire test suite:

    qmk pytest

Run test group:

    qmk pytest -t qmk.tests.test_cli_commands

Run single test:

    qmk pytest -t qmk.tests.test_cli_commands.test_c2json
    qmk pytest -t qmk.tests.test_qmk_path

## `qmk painter-convert-graphics`

This command converts images to a format usable by QMK, i.e. the QGF File Format. See the [Quantum Painter](quantum_painter.md?id=quantum-painter-cli) documentation for more information on this command.

## `qmk painter-make-font-image`

This command converts a TTF font to an intermediate format for editing, before converting to the QFF File Format. See the [Quantum Painter](quantum_painter.md?id=quantum-painter-cli) documentation for more information on this command.

## `qmk painter-convert-font-image`

This command converts an intermediate font image to the QFF File Format. See the [Quantum Painter](quantum_painter.md?id=quantum-painter-cli) documentation for more information on this command.

