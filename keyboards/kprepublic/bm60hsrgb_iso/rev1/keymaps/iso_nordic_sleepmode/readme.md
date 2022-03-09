# Nordic keymap for BM60rgb_iso
Very few changes from default keyboard, apart from the button right of leftshift,
and adding some more buttons on the second layer (function keys, home/end, pg up/down and media keys).

On the default layout, the top left button is RESET on the second layer,
this board has a reset button on the back. So I feel like it serves a better
purpose as the grave key (because grave-escape doesn't really
work with mac and norwegian layout). It could of course also be on the base layer.
But as a regular vim user I use escape more than the grave key.

I have also added mod-tap to the right shift, with the "default" position for
`KC_SLSH` beeing on the far right, that works fine.

There is also a "sleep-mode" function added,
this can be enabled defining `SLEEPMODE_ENABLE` in `config.h`.
This makes the keyboard backlight turn off after 10 minutes without any
keypresses, and turn on again on keypress. (This is something different than `USB_SUSPEND`)
