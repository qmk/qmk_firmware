# Actuation Point adjustment example keymap

This keymap is an example of how the actuation point adjustment functionality could be used. In `config.h`, we set `ACTUATION_DEPTH_ADJUSTMENT` to `+1`, which puts the actuation point slightly deeper, making the keys less sensitive.

If [hid_listen](https://www.pjrc.com/teensy/hid_listen.html) is running, `CAPS_LOCK + F9` prints the current RDAC setting and `CAPS_LOCK + F10` prints the default or base setting. `CAPS_LOCK + F11` and `CAPS_LOCK + F12` can be used to adjust the actuation point dynamically. Make only small adjustments and find your ideal setting. For example, if the base setting of your keyboard is 56 but you prefer a slightly lower actuation point at 58, you should set `ACTUATION_DEPTH_ADJUSTMENT` to `+2`.

If something goes wrong during adjustment, for example keys not actuating anymore or actuating spontaneously, don't panic. Just unplug the keyboard and plug it back in. This will revert all your dynamic changes made with `F11` and `F12`.

If you discover you have set a too high or low value for `ACTUATION_DEPTH_ADJUSTMENT`, you will need to recompile and reflash your keyboard.
