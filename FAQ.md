# Degug Console
## hid_listen can't find device
When debug console of your device is not ready you will see like this:

    Waiting for device:.........

once the device is pluged in then *hid_listen* finds it you will get this message:

    Waiting for new device:.........................
    Listening:

Check if you can't get this 'Listening:' message:
- build with `CONSOLE_ENABLE=yes` in **Makefile**.

## Can't get message from console
Check:
- the device is connected to *hid_listen*. See above.
- push **LShift+RShift+d** to enable debug. See [Magic Commands](https://github.com/tmk/tmk_keyboard#magic-commands).
- `debug_enable=yes` Usually in `matrix_init()` in **matrix.c**.
- try using 'print' function instead of debug print. See **common/print.h**.
- Disconnect other devices with console function. See [Issue #97](https://github.com/tmk/tmk_keyboard/issues/97).

***

# NKRO

# PS/2 mouse support