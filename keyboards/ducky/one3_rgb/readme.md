# Ducky One 3 RGB (full-size)

QMK port for the full-size ANSI Ducky One 3 RGB (Nuvoton NUC1261SG4AE, stock USB ID `3233:1311`).

* Keyboard Maintainer: [doombadroid](https://github.com/doombadroid)
* Hardware Supported: Ducky One 3 RGB, full-size ANSI (108 keys incl. the 4 media keys)
* Hardware Availability: retail

Working: typing (NKRO), per-key RGB (3x MBI5042, 24 RGB Matrix effects), Num/Caps/Scroll/Win-lock
indicators, media keys, Fn layer, settings saved to flash, Fn+Esc bootloader entry.
Untested: RGB off during host suspend.

## Build

    make ducky/one3_rgb:default

## Flashing

The stock Ducky bootloader (LDROM, USB `0416:3f00`, Nuvoton ISP_HID) stays installed and is never
touched. Flash with [nu-isp-cli](https://crates.io/crates/nu-isp-cli) (`cargo install nu-isp-cli`):

    nu-isp-cli 0416:3f00 flash ducky_one3_rgb_default.bin

Enter the bootloader with any of:

* **Fn + Esc** while QMK is running (a plain replug without flashing boots QMK again)
* hold **Esc** while plugging in (bootmagic; also resets saved settings)
* unplug, hold **D + L**, plug in. Handled by Ducky's LDROM, so it works whatever is flashed.

**Back to stock:** D + L, then flash Ducky's own APROM image (it is embedded in Ducky's official
updater) with the same command. `flash` launches the image when it finishes.

QMK only writes its EEPROM pages (`0x30000`-`0x31FFF`) and the stock LDROM request word at
`0x3F800`; CONFIG and LDROM are never written. The stock firmware's data flash (`0x33200`+) is left alone.

Linux needs access to the bootloader's hidraw node, e.g. a udev rule:

    SUBSYSTEM=="hidraw", ATTRS{idVendor}=="0416", ATTRS{idProduct}=="3f00", MODE="0660", GROUP="plugdev"

## Fn layer

| Key | Fn + key |
|---|---|
| Esc | Bootloader |
| F1-F4 | My Computer, Browser home, Mail, Calculator |
| F5-F8 | Previous, Play/Pause, Stop, Next |
| F9-F11 | Mute, Volume down, Volume up |
| Left Win | Win key lock |
| Numpad 0 | Num Lock |
| Insert | RGB on/off |
| Home / End | RGB hue up / down |
| Page Up / Page Down | RGB saturation up / down |
| Delete | RGB effect speed down |
| Up / Down | RGB brightness up / down |
| Left / Right | Previous / next RGB effect |

See [the keyboard build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and
[make instructions](https://docs.qmk.fm/#/getting_started_make_guide) if you are new to QMK.
