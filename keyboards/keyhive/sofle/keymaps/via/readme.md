# VIA keymap for Sofle

Features:

-   Symmetric modifiers (CMD/Super, Alt/Opt, Ctrl, Shift)
-   The OLED on master half shows selected mode and caps lock state and is rotated.
-   Left encoder controls volume up/down/mute. Right encoder PGUP/PGDOWN.
-   VIA support
-   Per-key and RGB underglow support

## Flashing

Use the corresponding commands below to flash the firmware based on your controller type:

```sh
# for pro micro-based builds
qmk flash -kb keyhive/sofle -km via

# for Elite C or dfu bootloader builds
qmk flash -kb keyhive/sofle -km via -bl dfu
```

## VIA json

Until this the corresponding code is merged to VIA, you can load the `keyhive-sofle.json` file to the VIA 'Design' tab in order to make changes.
