# Testing and Debugging

Once you've flashed your keyboard with a custom firmware you're ready to test it out. With a little bit of luck everything will work perfectly, but if not this document will help you figure out what's wrong.

## Testing

Testing your keyboard is usually pretty straightforward. Press every single key and make sure it sends the keys you expect. There are even programs that will help you make sure that no key is missed.

Note: These programs are not provided by or endorsed by QMK.

* [Switch Hitter](https://elitekeyboards.com/switchhitter.php) (Windows Only)
* [Keyboard Viewer](https://www.imore.com/how-use-keyboard-viewer-your-mac) (Mac Only)
* [Keyboard Tester](http://www.keyboardtester.com) (Web Based)
* [Keyboard Checker](http://keyboardchecker.com) (Web Based)

## Debugging

Your keyboard will output debug information if you have `CONSOLE_ENABLE = yes` in your `rules.mk`. By default the output is very limited, but you can turn on debug mode to increase the amount of debug output. Use the `DEBUG` keycode in your keymap, use the [Command](feature_command.md) feature to enable debug mode, or add the following code to your keymap.

```c
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
```

### Debugging With QMK Toolbox

For compatible platforms, [QMK Toolbox](https://github.com/qmk/qmk_toolbox) can be used to display debug messages from your keyboard.

### Debugging With hid_listen

Prefer a terminal based solution? [hid_listen](https://www.pjrc.com/teensy/hid_listen.html), provided by PJRC, can also be used to display debug messages. Prebuilt binaries for Windows,Linux,and MacOS are available.

<!-- FIXME: Describe the debugging messages here. -->

## Sending Your Own Debug Messages

Sometimes it's useful to print debug messages from within your [custom code](custom_quantum_functions.md). Doing so is pretty simple. Start by including `print.h` at the top of your file:

    #include <print.h>

After that you can use a few different print functions:

* `print("string")`: Print a simple string.
* `uprintf("%s string", var)`: Print a formatted string
* `dprint("string")` Print a simple string, but only when debug mode is enabled
* `dprintf("%s string", var)`: Print a formatted string, but only when debug mode is enabled

## Debug Examples

Below is a collection of real world debugging examples. For additional information, refer to [Debugging/Troubleshooting QMK](faq_debug.md).

### Which matrix position is this keypress?

When porting, or when attempting to diagnose pcb issues, it can be useful to know if a keypress is scanned correctly. To enable logging for this scenario, add the following code to your keymaps `keymap.c`

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 
  return true;
}
```

Example output
```text
Waiting for device:.......
Listening:
KL: kc: 169, col: 0, row: 0, pressed: 1
KL: kc: 169, col: 0, row: 0, pressed: 0
KL: kc: 174, col: 1, row: 0, pressed: 1
KL: kc: 174, col: 1, row: 0, pressed: 0
KL: kc: 172, col: 2, row: 0, pressed: 1
KL: kc: 172, col: 2, row: 0, pressed: 0
```

### How long did it take to scan for a keypress?

When testing performance issues, it can be useful to know the frequency at which the switch matrix is being scanned. To enable logging for this scenario, add the following code to your keymaps `config.h`

```c
#define DEBUG_MATRIX_SCAN_RATE
```

Example output
```text
  > matrix scan frequency: 315
  > matrix scan frequency: 313
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
```
