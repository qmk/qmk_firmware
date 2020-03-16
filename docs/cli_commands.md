# QMK CLI Commands

# CLI Commands

## `qmk cformat`

This command formats C code using clang-format. 

Run it with no arguments to format all core code that has been changed. Default checks `origin/master` with `git diff`, branch can be changed using `-b <branch_name>`

Run it with `-a` to format all core code, or pass filenames on the command line to run it on specific files.

**Usage for specified files**:

```
qmk cformat [file1] [file2] [...] [fileN]
```

**Usage for all core files**:

```
qmk cformat -a
```

**Usage for only changed files against origin/master**:

```
qmk cformat
```

**Usage for only changed files against branch_name**:

```
qmk cformat -b branch_name
```

## `qmk compile`

This command allows you to compile firmware from any directory. You can compile JSON exports from <https://config.qmk.fm>, compile keymaps in the repo, or compile the keyboard in the current working directory.

**Usage for Configurator Exports**:

```
qmk compile <configuratorExport.json>
```

**Usage for Keymaps**:

```
qmk compile -kb <keyboard_name> -km <keymap_name>
```

**Usage in Keyboard Directory**:  

Must be in keyboard directory with a default keymap, or in keymap directory for keyboard, or supply one with `--keymap <keymap_name>`
```
qmk compile
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
Ψ Compiling keymap with make make gh60/satan:colemak
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

## `qmk flash`

This command is similar to `qmk compile`, but can also target a bootloader. The bootloader is optional, and is set to `:flash` by default.
To specify a different bootloader, use `-bl <bootloader>`. Visit the [Flashing Firmware](flashing.md) guide for more details of the available bootloaders.

**Usage for Configurator Exports**:

```
qmk flash <configuratorExport.json> -bl <bootloader>
```

**Usage for Keymaps**:

```
qmk flash -kb <keyboard_name> -km <keymap_name> -bl <bootloader>
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

## `qmk docs`

This command starts a local HTTP server which you can use for browsing or improving the docs. Default port is 8936.

**Usage**:

```
qmk docs [-p PORT]
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

## `qmk json2c`

Creates a keymap.c from a QMK Configurator export.

**Usage**:

```
qmk json2c [-o OUTPUT] filename
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

## `qmk list-keyboards`

This command lists all the keyboards currently defined in `qmk_firmware`

**Usage**:

```
qmk list-keyboards
```

## `qmk list-keymaps`

This command lists all the keymaps for a specified keyboard (and revision).

**Usage**:

```
qmk list-keymaps -kb planck/ez
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
