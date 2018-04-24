# TADA68 layout for ISO UK

This layout has been tested on a TADA68 purchased from kbdfans in March 2018. The physical key layout includes the "double height" iso Enter key and the "short" Left Shift along side the iso Backslash key. [See this keyboard-layout-editor.com Gist](http://www.keyboard-layout-editor.com/#/gists/acf0f32f7ea0d0ed35c901663ca47919)

The Base Layer and Function layer defined here match the layout defined by the kbdfans keyboard layout tool found at http://123.57.250.164:3000/tada68

## Special mention for the ISO Hash key

When viewing tada68.h in this directory, KEYMAP_ISO does not define a key at location *k2c* (it's missing) even though this is where the ISO Hash key (KC_NUHS) physically appears on your keyboard. For some reason we have to map the KC_NUHS to key location *k1d* which is above the Enter key.

In an attempt to clarify this anomaly, the ascii image comments in keymap.c depicts the physical layout, but the definition in *[_BL] = KEYMAP_ISO* depicts the layout that the firmware operates on.

## Installation

Please see the [tada68 readme](../../readme.md) using the following command

```
make tada68:iso-uk:bin
```