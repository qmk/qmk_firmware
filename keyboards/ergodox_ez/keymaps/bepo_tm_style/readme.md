# Bépo compatible keymap for the Ergodox EZ, *TypeMatrix* style.

This keymap is meant to be used with a [Bépo](http://bepo.fr) layout. It is
designed to be somewhat similar to a TypeMatrix keyboard so that switching
between one and the other is easy.

![The Keymap](https://i.imgur.com/yChIbaK.png)

## Build instruction

To build this on Windows, under Cygwin, provided that you have installed the
Arduino environment and Teensy loaded in the default path, you can do:

```shell
PATH=/cygdrive/c/Program\ Files\ \(x86\)/Arduino/hardware/tools/avr/bin:$PATH
make ergodox_ez:bepo_tm_style:all
```

## Debug

See https://github.com/tmk/tmk_keyboard#magic-commands for command that can help
debug, together with the [hid_listen tool](https://docs.qmk.fm/faq_debug.html).