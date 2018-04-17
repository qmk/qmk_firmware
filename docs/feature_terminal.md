# Terminal

> This feature is currently *huge* at 4400 bytes, and should probably only be put on boards with a lot of memory, or for fun.

The terminal feature is a command-line-like interface designed to communicate through a text editor with keystrokes. It's beneficial to turn off auto-indent features in your editor.

To enable, stick this in your `rules.mk` or `Makefile`:

    TERMINAL_ENABLE = yes

And use the `TERM_ON` and `TERM_OFF` keycodes to turn it on or off.

When enabled, a `> ` prompt will appear, where you'll be able to type, backspace (a bell will ding if you reach the beginning and audio is enabled), and hit enter to send the command. Arrow keys are currently disabled so it doesn't get confused. Moving your cursor around with the mouse is discouraged.

`#define TERMINAL_HELP` enables some other output helpers that aren't really needed with this page.

Pressing "up" and "down" will allow you to cycle through the past 5 commands entered.

## Future Ideas

* Keyboard/user-extensible commands
* Smaller footprint
* Arrow key support
* Command history - Done
* SD card support
* LCD support for buffer display
* Keycode -> name string LUT
* Layer status
* *Analog/digital port read/write*
* RGB mode stuff
* Macro definitions
* EEPROM read/write
* Audio control

## Current Commands

### `about`

Prints out the current version of QMK with a build date:

```
> about
QMK Firmware
  v0.5.115-7-g80ed73-dirty
  Built: 2017-08-29-20:24:44
```


### `print-buffer`

Outputs the last 5 commands entered

```
> print-buffer
0. print-buffer
1. help
2. about
3. keymap 0
4. help 
5. flush-buffer
```

### `flush-buffer`

Clears command buffer
```
> flush-buffer
Buffer cleared!
```


### `help`


Prints out the available commands:

```
> help
commands available:
  about help keycode keymap exit print-buffer flush-buffer
```

### `keycode <layer> <row> <col>`

Prints out the keycode value of a certain layer, row, and column:

```
> keycode 0 1 0
0x29 (41)
```

### `keymap <layer>`

Prints out the entire keymap for a certain layer

```
> keymap 0
0x002b, 0x0014, 0x001a, 0x0008, 0x0015, 0x0017, 0x001c, 0x0018, 0x000c, 0x0012, 0x0013, 0x002a,
0x0029, 0x0004, 0x0016, 0x0007, 0x0009, 0x000a, 0x000b, 0x000d, 0x000e, 0x000f, 0x0033, 0x0034,
0x00e1, 0x001d, 0x001b, 0x0006, 0x0019, 0x0005, 0x0011, 0x0010, 0x0036, 0x0037, 0x0038, 0x0028,
0x5cd6, 0x00e0, 0x00e2, 0x00e3, 0x5cd4, 0x002c, 0x002c, 0x5cd5, 0x0050, 0x0051, 0x0052, 0x004f,
>
```

### `exit`

Exits the terminal - same as `TERM_OFF`.
