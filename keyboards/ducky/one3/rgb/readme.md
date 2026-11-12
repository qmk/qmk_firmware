# Ducky One 3 RGB

*Full-size ANSI Ducky One 3 RGB: Nuvoton NUC1261SG4AE, per-key RGB through three MBI5042 drivers, four DIP switches.*

* Keyboard Maintainer: [doombadroid](https://github.com/doombadroid)
* Hardware Supported: Ducky One 3 RGB, full-size ANSI (stock USB ID `3233:1311`)
* Hardware Availability: [Ducky](https://ducky.global/products/one-3-rgb)

Make example for this keyboard (after setting up your build environment):

    make ducky/one3/rgb:default

Flashing example for this keyboard, with the board in its bootloader (USB `0416:3f00`) and
[nu-isp-cli](https://crates.io/crates/nu-isp-cli) installed:

    nu-isp-cli 0416:3f00 flash ducky_one3_rgb_default.bin

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

The stock Ducky bootloader (LDROM, Nuvoton ISP over HID) stays installed and is never written. Enter it in 3 ways:

* **Bootmagic reset**: Hold down Escape and plug in the keyboard (also clears saved settings)
* **D + L**: Hold D and L and plug in the keyboard; handled by the bootloader itself, so it works whatever is flashed
* **Keycode in layout**: Press the key mapped to `QK_BOOT` (Fn + Esc in the default keymap)

To go back to stock, flash Ducky's APROM image (embedded in Ducky's firmware updater) the same way.

## DIP switches

The four switches on the underside are read live and keep their stock functions:

| DIP | OFF (default) | ON |
|---|---|---|
| 1 | Fn + Left Win toggles the Win-key lock | Win-key lock disabled |
| 2 | NKRO | 6-key rollover |
| 3 | unused (stock: USB vendor ID) | unused |
| 4 | Right Win is Win | Right Win sends Menu |

## Fn layer (default keymap)

| Key | Fn + key |
|---|---|
| Esc | Bootloader |
| F1-F4 | My Computer, Browser home, Mail, Calculator |
| F5-F8 | Previous, Play/Pause, Stop, Next |
| F9-F11 | Mute, Volume down, Volume up |
| Left Win | Win-key lock |
| Numpad 0 | Num Lock |
| Insert | RGB on/off |
| Home / End | RGB hue up / down |
| Page Up / Page Down | RGB saturation up / down |
| Delete | RGB effect speed down |
| Up / Down | RGB brightness up / down |
| Left / Right | Previous / next RGB effect |
