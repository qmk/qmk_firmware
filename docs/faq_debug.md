# Debugging FAQ

This page details various common questions people have about troubleshooting their keyboards.

## Debugging {#debugging}

Your keyboard will output debug information if you have `CONSOLE_ENABLE = yes` in your `rules.mk`. By default the output is very limited, but you can turn on debug mode to increase the amount of debug output. Use the `DB_TOGG` keycode in your keymap, use the [Command](features/command) feature to enable debug mode, or add the following code to your keymap.

```c
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
```

## Debugging Tools

Various tools are available to debug your keyboard.

### Debugging With QMK Toolbox

For compatible platforms, [QMK Toolbox](https://github.com/qmk/qmk_toolbox) can be used to display debug messages from your keyboard.

### Debugging with QMK CLI

Prefer a terminal based solution? The [QMK CLI console command](cli_commands#qmk-console) can be used to display debug messages from your keyboard.

### Debugging With hid_listen

Something stand-alone? [hid_listen](https://www.pjrc.com/teensy/hid_listen.html), provided by PJRC, can also be used to display debug messages. Prebuilt binaries for Windows,Linux,and MacOS are available.

## Sending Your Own Debug Messages {#debug-api}

Sometimes it's useful to print debug messages from within your [custom code](custom_quantum_functions). Doing so is pretty simple. Start by including `print.h` at the top of your file:

```c
#include "print.h"
```

After that you can use a few different print functions:

* `print("string")`: Print a simple string.
* `uprintf("%s string", var)`: Print a formatted string
* `dprint("string")` Print a simple string, but only when debug mode is enabled
* `dprintf("%s string", var)`: Print a formatted string, but only when debug mode is enabled

## Debug Examples

Below is a collection of real world debugging examples. For additional information, refer to [Debugging/Troubleshooting QMK](faq_debug).

### Which matrix position is this keypress?

When porting, or when attempting to diagnose pcb issues, it can be useful to know if a keypress is scanned correctly. To enable logging for this scenario, add the following code to your keymaps `keymap.c`

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
  return true;
}
```

Example output
```
Waiting for device:.......
Listening:
KL: kc: 169, col: 0, row: 0, pressed: 1, time: 15505, int: 0, count: 0
KL: kc: 169, col: 0, row: 0, pressed: 0, time: 15510, int: 0, count: 0
KL: kc: 174, col: 1, row: 0, pressed: 1, time: 15703, int: 0, count: 0
KL: kc: 174, col: 1, row: 0, pressed: 0, time: 15843, int: 0, count: 0
KL: kc: 172, col: 2, row: 0, pressed: 1, time: 16303, int: 0, count: 0
KL: kc: 172, col: 2, row: 0, pressed: 0, time: 16411, int: 0, count: 0
```

### How long did it take to scan for a keypress?

When testing performance issues, it can be useful to know the frequency at which the switch matrix is being scanned. To enable logging for this scenario, add the following code to your keymaps `config.h`

```c
#define DEBUG_MATRIX_SCAN_RATE
```

Example output
```
  > matrix scan frequency: 315
  > matrix scan frequency: 313
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
```

## `hid_listen` Can't Recognize Device
When debug console of your device is not ready you will see like this:

```
Waiting for device:.........
```

Once the device is plugged in then *hid_listen* finds it you will get this message:

```
Waiting for new device:.........................
Listening:
```

If you can't get this 'Listening:' message try building with `CONSOLE_ENABLE=yes` in [Makefile]

You may need privileges to access the device an OS like Linux. Try `sudo hid_listen`.

On many Linux distros you can avoid having to run hid_listen as root
by creating a file called `/etc/udev/rules.d/70-hid-listen.rules` with
the following content:

```
SUBSYSTEM=="hidraw", ATTRS{idVendor}=="abcd", ATTRS{idProduct}=="def1", TAG+="uaccess", RUN{builtin}+="uaccess"
```

Replace abcd and def1 with your keyboard's vendor and product id,
letters must be lowercase. The `RUN{builtin}+="uaccess"` part is only
needed for older distros.


## Can't Get Message on Console
Check:
- *hid_listen* finds your device. See above.
- Enable debug by pressing **Magic**+d. See [Magic Commands](https://github.com/tmk/tmk_keyboard/wiki#magic-commands-for-debug).
- Set `debug_enable=true`. See [Debugging](#debugging)
- Try using `print` function instead of debug print. See **common/print.h**.
- Disconnect other devices with console function. See [Issue #97](https://github.com/tmk/tmk_keyboard/issues/97).
- Ensure all strings end with a newline character (`\n`). QMK Toolbox prints console output on a per-line basis.
