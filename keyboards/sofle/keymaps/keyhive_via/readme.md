# VIA keymap for Sofle

Layout in [Keyboard Layout Editor](http://www.keyboard-layout-editor.com/#/gists/76efb423a46cbbea75465cb468eef7ff) and [adjust layer](http://www.keyboard-layout-editor.com/#/gists/4bcf66f922cfd54da20ba04905d56bd4)

Features:

-   Symmetric modifiers (CMD/Super, Alt/Opt, Ctrl, Shift)
-   Modes for Qwerty and Colemak support
-   The OLED on master half shows selected mode and caps lock state and is rotated.
-   Left encoder controls volume up/down/mute. Right encoder PGUP/PGDOWN.
-   Via support
-   RGB underglow support

## Flashing

Flash using the correct command below:

```sh
# for pro micro-based builds
qmk flash -kb sofle/rev2 -km keyhive_via -bl avrdude-split-left
qmk flash -kb sofle/rev2 -km keyhive_via -bl avrdude-split-right

# for Elite C or dfu bootloader builds
qmk flash -kb sofle/rev2 -km keyhive_via -bl dfu-split-left
qmk flash -kb sofle/rev2 -km keyhive_via -bl dfu-split-right
```

These commands can be mixed if, for example, you have an Elite C on the left and a pro micro on the right.

> Note: its not recommended to try to use QMK Toolbox as
