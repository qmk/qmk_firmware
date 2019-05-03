# Testing and Debugging

Once you've flashed your keyboard with a custom firmware you're ready to test it out. With a little bit of luck everything will work perfectly, but if not this document will help you figure out what's wrong.

## Testing

Testing your keyboard is usually pretty straightforward. Press every single key and make sure it sends the keys you expect. There are even programs that will help you make sure that no key is missed.

Note: These programs are not provided by or endorsed by QMK.

* [Switch Hitter](https://elitekeyboards.com/switchhitter.php) (Windows Only)
* [Keyboard Viewer](https://www.imore.com/how-use-keyboard-viewer-your-mac) (Mac Only)
* [Keyboard Tester](http://www.keyboardtester.com) (Web Based)
* [Keyboard Checker](http://keyboardchecker.com) (Web Based)

## Debugging With QMK Toolbox

[QMK Toolbox](https://github.com/qmk/qmk_toolbox) will show messages from your keyboard if you have `CONSOLE_ENABLE = yes` in your `rules.mk`. By default the output is very limited, but you can turn on debug mode to increase the amount of debug output. Use the `DEBUG` keycode in your keymap, or use the [Command](feature_command.md) feature to enable debug mode.

<!-- FIXME: Describe the debugging messages here. -->

## Sending Your Own Debug Messages

Sometimes it's useful to print debug messages from within your [custom code](custom_quantum_functions.md). Doing so is pretty simple. Start by including `print.h` at the top of your file:

    #include <print.h>

After that you can use a few different print functions:

* `print("string")`: Print a simple string.
* `sprintf("%s string", var)`: Print a formatted string
* `dprint("string")` Print a simple string, but only when debug mode is enabled
* `dprintf("%s string", var)`: Print a formatted string, but only when debug mode is enabled
